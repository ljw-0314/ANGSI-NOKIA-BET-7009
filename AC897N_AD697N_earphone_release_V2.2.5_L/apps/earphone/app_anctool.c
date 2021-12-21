#include "init.h"
#include "app_config.h"
#include "system/includes.h"

#if TCFG_ANC_TOOL_DEBUG_ONLINE

#include "btstack/avctp_user.h"
#include "classic/hci_lmp.h"
#include "app_anctool.h"
#include "audio_anc.h"
#include "user_cfg.h"
#include "app_action.h"
#include "app_main.h"
#include "user_cfg.h"

#define anctool_printf  log_i
#define anctool_put_buf put_buf
#define CONFIG_VERSION  "V2.1.0"

extern void anc_cfg_btspp_update(u8 id, int data);
extern int anc_cfg_btspp_read(u8 id, int *data);
extern int anc_mode_change_tool(u8 dat);
extern

enum {
    FILE_ID_COEFF = 0,  //系数文件ID号
    FILE_ID_PCM = 1,    //播放文件ID号
    FILE_ID_MIC_SPK = 2,//mic spk文件ID号
};

enum {
    ERR_NO = 0,
    ERR_EAR_OFFLINE = 1,//耳机不在线
    ERR_EAR_FAIL = 2,   //耳机返回失败
    ERR_MIC_BUSY = 3,   //表示当前处于训练阶段,mic联通状态不允许发送命令给耳机
    ERR_COEFF_NO = 4,   //读系数时耳机没有训练系数
    ERR_COEFF_LEN = 5,  //写系数时长度异常
    ERR_PARM_LEN = 6,   //参数长度异常
    ERR_VERSION = 7,    //版本匹配异常,请更新转接板固件
    ERR_READ_FILE = 8,  //读文件失败
    ERR_WRITE_FILE = 9, //写文件失败
};

enum {
    CMD_GET_VERSION     = 0x04, //获取版本号
    CMD_ANC_OFF         = 0x13, //关闭ANC
    CMD_ANC_ON          = 0x14, //开降噪
    CMD_ANC_PASS        = 0x15, //通透模式
    CMD_READ_START      = 0x20, //开始读
    CMD_READ_DATA       = 0x21, //读取数据
    CMD_WRITE_START     = 0x22, //开始写
    CMD_WRITE_DATA      = 0x23, //写入数据
    CMD_WRITE_END       = 0x24, //数据写入完成
    CMD_SET_ID          = 0x29, //设置ID对应的数据
    CMD_GET_ID          = 0x2A, //获取ID对应的数据
    CMD_TOOLS_SET_GAIN  = 0x2B, //工具设置增益(PC下来多少数据就转发多少给耳机)
    CMD_TOOLS_GET_GAIN  = 0x2C, //工具读取增益(耳机过来多少数据就转发多少给PC)
    CMD_ANC_BYPASS      = 0x2D, //BYPASS让耳机进入bypass模式,带一个u8的参数
    CMD_GET_ANC_MODE    = 0x2E, //获取耳机训练模式,(FF,FB,HYB...)
    CMD_SET_ANC_MODE    = 0x2F, //切换耳机训练模式,仅在耳机训练模式为混合溃时才能切换为单溃或者双馈
    CMD_GET_COEFF_SIZE  = 0x30, //获取系数内容大小(不会因为小机没有系数导致失败)
    CMD_MUTE_TRAIN_ONLY = 0x31, //静音训练,耳机只跑静音训练
    CMD_MUTE_TRAIN_ONLY_END = 0x32, //静音训练,耳机只跑静音训练,结束 ear->pc
    CMD_MUTE_TRAIN_GET_POW = 0x33, //静音训练结束后获取fz sz数据接口
    CMD_READ_FILE_START = 0x34, //读文件开始,携带ID号,返回文件大小
    CMD_READ_FILE_DATA  = 0x35, //读取文件数据,地址,长度
    CMD_WRITE_FILE_START = 0x36, //写文件开始,携带ID号,及文件长度
    CMD_WRITE_FILE_DATA = 0x37, //写入文件数据,地址+数据
    CMD_WRITE_FILE_END  = 0x38, //写入文件结束
    CMD_GET_CHIP_VERSION   = 0x39, //获取耳机芯片ANC版本
    CMD_TRANS_MUTE_TRAIN	= 0x3A, //通透训练
    CMD_TRANS_MUTE_TRAIN_END	= 0x3B, //通透训练结束, EAR->PC
    CMD_FAIL            = 0xFE, //执行失败
    CMD_UNDEFINE        = 0xFF, //未定义
};

struct _anctool_info {
    anc_train_para_t *para;
    u8 mute_train_flag;
    u8 pack_flag;
    u8 sz_nadap_pow;
    u8 sz_adap_pow;
    u8 sz_mute_pow;
    u8 fz_nadap_pow;
    u8 fz_adap_pow;
    u8 fz_mute_pow;
    u8 *file_hdl;
    u32 file_len;
    u32 file_id;
};
static struct _anctool_info anctool_info;
#define __this  (&anctool_info)

static void app_anctool_send_ack(u8 cmd2pc, u8 ret, u8 err_num)
{
    u8 cmd[2];
    if (ret == TRUE) {
        cmd[0] = cmd2pc;
        anctool_api_write(cmd, 1);
    } else {
        cmd[0] = CMD_FAIL;
        cmd[1] = err_num;
        anctool_api_write(cmd, 2);
    }
}

static void app_anctool_ack_get_version(void)
{
    u8 *cmd;
    u32 datalen;
    datalen = sizeof(CONFIG_VERSION) + 1;
    cmd = anctool_api_write_alloc(datalen);
    cmd[0] = CMD_GET_VERSION;
    memcpy(&cmd[1], CONFIG_VERSION, datalen - 1);
    anctool_api_write(cmd, datalen);
}

static void app_anctool_ack_read_start(u8 head)
{
    u8 *cmd;
    u32 data_len;
    __this->file_len = anc_coeff_size_get();
    __this->file_hdl = (u8 *)anc_coeff_read();
    if (__this->file_hdl) {//判断耳机有没有系数
        data_len = __this->file_len;
        cmd = anctool_api_write_alloc(5);
        cmd[0] = head;
        memcpy(&cmd[1], (u8 *)&data_len, 4);
        anctool_api_write(cmd, 5);
    } else {
        app_anctool_send_ack(head, FALSE, ERR_COEFF_NO);
    }
}

static void app_anctool_ack_read_data(u8 head, u32 offset, u32 data_len)
{
    u8 *cmd = anctool_api_write_alloc(data_len + 1);
    cmd[0] = head;
    memcpy(&cmd[1], __this->file_hdl + offset, data_len);
    if (offset + data_len == __this->file_len) {
        __this->file_hdl = NULL;
    }
    anctool_api_write(cmd, data_len + 1);
}

static void app_anctool_ack_wirte_start(u8 cmd, u32 data_len)
{
    __this->file_len = anc_coeff_size_get();
    __this->file_hdl = malloc(data_len);
    if ((data_len == __this->file_len) && __this->file_hdl) {
        app_anctool_send_ack(cmd, TRUE, ERR_NO);
    } else {
        app_anctool_send_ack(cmd, FALSE, ERR_COEFF_LEN);
        if (__this->file_hdl) {
            free(__this->file_hdl);
            __this->file_hdl = NULL;
        }
    }
}

static void app_anctool_ack_wirte_data(u8 cmd, u32 offset, u8 *data, u32 data_len)
{
    memcpy(__this->file_hdl + offset, data, data_len);
    app_anctool_send_ack(cmd, TRUE, ERR_NO);
}

static void app_anctool_ack_write_end(u8 cmd)
{
    anc_coeff_write((int *)__this->file_hdl, __this->file_len);
    free(__this->file_hdl);
    __this->file_hdl = NULL;
    app_anctool_send_ack(cmd, TRUE, ERR_NO);
}

static void app_anctool_ack_anc_mode(u8 cmd)
{
    anc_api_set_fade_en(0);
    if (cmd == CMD_ANC_ON) {
        anc_mode_switch(ANC_ON, 0);
    } else if (cmd == CMD_ANC_OFF) {
        anc_mode_switch(ANC_OFF, 0);
    } else if (cmd == CMD_ANC_PASS) {
        anc_mode_switch(ANC_TRANSPARENCY, 0);
    } else {
        anc_mode_switch(ANC_BYPASS, 0);
    }
    app_anctool_send_ack(cmd, TRUE, ERR_NO);
}

static void app_anctool_ack_set_id(u32 id, u32 value)
{
    anc_cfg_btspp_update((u8)id, (int)value);
    app_anctool_send_ack(CMD_SET_ID, TRUE, ERR_NO);
}

static void app_anctool_ack_get_id(u32 id)
{
    u8 *cmd;
    u32 value;
    if (anc_cfg_btspp_read((u8)id, (int *)&value) == 0) {
        cmd = anctool_api_write_alloc(4 + 1);
        cmd[0] = CMD_GET_ID;
        memcpy(&cmd[1], (u8 *)&value, 4);
        anctool_api_write(cmd, 4 + 1);
    } else {
        app_anctool_send_ack(CMD_SET_ID, FALSE, ERR_EAR_FAIL);
    }
}

static void app_anctool_ack_set_gain(u8 *buf, u32 len)
{
    u8 *cmd;
    u32 data_len;
    anc_gain_t anc_gain;
    if (len != sizeof(anc_gain_t)) {
        app_anctool_send_ack(CMD_TOOLS_SET_GAIN, FALSE, ERR_PARM_LEN);
    } else {
        memcpy(&anc_gain, buf, len);
        anc_cfg_online_deal(ANC_CFG_WRITE, &anc_gain);
        app_anctool_send_ack(CMD_TOOLS_SET_GAIN, TRUE, ERR_NO);
    }
}

static void app_anctool_ack_get_gain(void)
{
    u8 *cmd;
    u32 data_len;
    anc_gain_t anc_gain;
    data_len = sizeof(anc_gain_t) + 1;
    cmd = anctool_api_write_alloc(data_len);
    cmd[0] = CMD_TOOLS_GET_GAIN;
    anc_cfg_online_deal(ANC_CFG_READ, &anc_gain);
    memcpy(&cmd[1], &anc_gain, sizeof(anc_gain_t));
    anctool_api_write(cmd, data_len);
}

static void app_anctool_ack_get_chip_version(void)
{
    u8 *cmd = anctool_api_write_alloc(2);
    cmd[0] = CMD_GET_CHIP_VERSION;
    cmd[1] = ANC_CHIP_VERSION;
    anctool_api_write(cmd, 2);
}

static void app_anctool_ack_get_train_mode(void)
{
    u8 *cmd = anctool_api_write_alloc(2);
    cmd[0] = CMD_GET_ANC_MODE;
    cmd[1] = ANC_TRAIN_MODE;
    anctool_api_write(cmd, 2);
}

static void app_anctool_ack_set_train_mode(u8 mode)
{
    anc_mode_change_tool(mode);
    app_anctool_send_ack(CMD_SET_ANC_MODE, TRUE, ERR_NO);
}

static void app_anctool_ack_get_coeff_size(void)
{
    u8 *cmd;
    u32 coeff_size = anc_coeff_size_get();
    cmd = anctool_api_write_alloc(5);
    cmd[0] = CMD_GET_COEFF_SIZE;
    memcpy(&cmd[1], &coeff_size, 4);
    anctool_api_write(cmd, 5);
}

void app_anctool_ack_mute_train_get_pow(void)
{
    u8 *cmd;
    cmd = anctool_api_write_alloc(7);
    cmd[0] = CMD_MUTE_TRAIN_GET_POW;
    cmd[1] = __this->sz_nadap_pow;
    cmd[2] = __this->sz_adap_pow;
    cmd[3] = __this->sz_mute_pow;
    cmd[4] = __this->fz_nadap_pow;
    cmd[5] = __this->fz_adap_pow;
    cmd[6] = __this->fz_mute_pow;
    anctool_api_write(cmd, 7);
}

static void anctool_ack_read_file_start(u32 id)
{
    u8 *cmd;
    __this->file_id = id;
    __this->file_len = 0;
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        app_anctool_ack_read_start(CMD_READ_FILE_START);
        break;
    case FILE_ID_MIC_SPK:
        __this->file_len = 65536;
        __this->file_hdl = NULL;
        cmd = anctool_api_write_alloc(5);
        cmd[0] = CMD_READ_FILE_START;
        memcpy(&cmd[1], (u8 *)&__this->file_len, 4);
        anctool_api_write(cmd, 5);
        break;
    }
}

static void anctool_ack_read_file_data(u32 offset, u32 data_len)
{
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        app_anctool_ack_read_data(CMD_READ_FILE_DATA, offset, data_len);
        break;
    case FILE_ID_MIC_SPK:
        if (__this->file_hdl == NULL) {
            //PENDING等待数据
        }
        break;
    }
}

static void anctool_ack_write_file_start(u32 id, u32 data_len)
{
    __this->file_id = id;
    __this->file_len = data_len;
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        app_anctool_ack_wirte_start(CMD_WRITE_FILE_START, data_len);
        break;
    case FILE_ID_PCM:
        break;
    }
}

static void anctool_ack_write_file_data(u32 offset, u8 *data, u32 data_len)
{
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        app_anctool_ack_wirte_data(CMD_WRITE_FILE_DATA, offset, data, data_len);
        break;
    case FILE_ID_PCM:
        break;
    }
}

static void anctool_ack_write_file_end(void)
{
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        app_anctool_ack_write_end(CMD_WRITE_FILE_END);
        break;
    case FILE_ID_PCM:
        break;
    }
}

static void anctool_callback(u8 mode, u8 command)
{
    u8 cmd[2];
    anctool_printf("anctool_callback: %d, %d\n", mode, command);
    if (__this->mute_train_flag == 0) {
        g_printf("%s,%d\n", __func__, __LINE__);
        return;
    }
    if (__this->mute_train_flag == 1) {
        cmd[0] = CMD_MUTE_TRAIN_ONLY_END;
        cmd[1] = command;
    } else {
        cmd[0] = CMD_TRANS_MUTE_TRAIN_END;
        cmd[1] = command;
    }
    anctool_api_set_active(1);
    anctool_api_write(cmd, 2);
    anctool_api_set_active(0);
    __this->mute_train_flag = 0;
}

static void anctool_pow_callback(anc_ack_msg_t *msg, u8 step)
{
    switch (step) {
    case ANC_TRAIN_SZ:
        __this->sz_nadap_pow = anc_powdat_analysis(msg->pow);
        __this->sz_adap_pow = anc_powdat_analysis(msg->temp_pow);
        __this->sz_mute_pow = anc_powdat_analysis(msg->mute_pow);
        break;
    case ANC_TRAIN_FZ:
        __this->fz_nadap_pow = anc_powdat_analysis(msg->pow);
        __this->fz_adap_pow = anc_powdat_analysis(msg->temp_pow);
        __this->fz_mute_pow = anc_powdat_analysis(msg->mute_pow);
        break;
    }
}

static void app_anctool_module_deal(u8 *data, u16 len)
{
    u8 cmd = data[0];
    u32 offset, data_len, id, value;
    __this->pack_flag = 1;
    anctool_printf("recv packet:\n");
    anctool_put_buf(data, len);
    switch (cmd) {
    case CMD_GET_VERSION:
        anctool_printf("CMD_GET_VERSION\n");
        app_anctool_ack_get_version();
        break;
    case CMD_READ_START:
        anctool_printf("CMD_READ_START\n");
        app_anctool_ack_read_start(CMD_READ_START);
        break;
    case CMD_READ_DATA:
        anctool_printf("CMD_READ_DATA\n");
        memcpy((u8 *)&offset, &data[1], 4);
        memcpy((u8 *)&data_len, &data[5], 4);
        app_anctool_ack_read_data(CMD_READ_DATA, offset, data_len);
        break;
    case CMD_WRITE_START:
        anctool_printf("CMD_WRITE_START\n");
        memcpy((u8 *)&data_len, &data[1], 4);
        app_anctool_ack_wirte_start(CMD_WRITE_START, data_len);
        break;
    case CMD_WRITE_DATA:
        anctool_printf("CMD_WRITE_DATA\n");
        memcpy((u8 *)&offset, &data[1], 4);
        app_anctool_ack_wirte_data(CMD_WRITE_DATA, offset, &data[5], len - 5);
        break;
    case CMD_WRITE_END:
        anctool_printf("CMD_WRITE_END\n");
        app_anctool_ack_write_end(CMD_WRITE_END);
        break;
    case CMD_ANC_OFF:
    case CMD_ANC_ON:
    case CMD_ANC_PASS:
    case CMD_ANC_BYPASS:
        anctool_printf("CMD_ANC_MODE:%d\n", cmd);
        app_anctool_ack_anc_mode(cmd);
        break;
    case CMD_SET_ID:
        memcpy((u8 *)&offset, &data[1], 4);//id
        memcpy((u8 *)&data_len, &data[5], 4);//value
        anctool_printf("CMD_SET_ID: 0x%x, %d\n", offset, data_len);
        app_anctool_ack_set_id(offset, data_len);
        break;
    case CMD_GET_ID:
        anctool_printf("CMD_GET_ID\n");
        memcpy((u8 *)&offset, &data[1], 4);
        app_anctool_ack_get_id(offset);
        break;
    case CMD_TOOLS_SET_GAIN:
        anctool_printf("CMD_TOOLS_SET_GAIN: %d\n", len - 1);
        app_anctool_ack_set_gain(&data[1], len - 1);
        break;
    case CMD_TOOLS_GET_GAIN:
        anctool_printf("CMD_TOOLS_GET_GAIN\n");
        app_anctool_ack_get_gain();
        break;
    case CMD_GET_ANC_MODE://获取耳机结构
        anctool_printf("CMD_GET_ANC_MODE\n");
        app_anctool_ack_get_train_mode();
        break;
    case CMD_SET_ANC_MODE://设置结构
        anctool_printf("CMD_SET_ANC_MODE: %d\n", data[1]);
        app_anctool_ack_set_train_mode(data[1]);
        break;
    case CMD_GET_COEFF_SIZE:
        anctool_printf("MSG_PC_GET_COEFF_SIZE\n");
        app_anctool_ack_get_coeff_size();
        break;
    case CMD_MUTE_TRAIN_ONLY:
        anctool_printf("CMD_MUTE_TRAIN_ONLY\n");
        __this->mute_train_flag = 1;
        anc_api_set_callback(anctool_callback, anctool_pow_callback);
        anc_train_api_set(ANC_DEVELOPER_MODE, 1, __this->para);//设置为开发者模式
        anc_train_api_set(ANC_MUTE_TARIN, 1, __this->para);
        break;
    case CMD_MUTE_TRAIN_GET_POW:
        anctool_printf("CMD_MUTE_TRAIN_GET_POW\n");
        app_anctool_ack_mute_train_get_pow();
        break;
    case CMD_READ_FILE_START:
        anctool_printf("CMD_READ_FILE_START\n");
        memcpy((u8 *)&id, &data[1], 4);
        anctool_ack_read_file_start(id);
        break;
    case CMD_READ_FILE_DATA:
        anctool_printf("CMD_READ_FILE_DATA\n");
        memcpy((u8 *)&offset, &data[1], 4);
        memcpy((u8 *)&data_len, &data[5], 4);
        anctool_ack_read_file_data(offset, data_len);
        break;
    case CMD_WRITE_FILE_START:
        anctool_printf("CMD_WRITE_FILE_START\n");
        memcpy((u8 *)&id, &data[1], 4);
        memcpy((u8 *)&data_len, &data[5], 4);
        anctool_ack_write_file_start(id, data_len);
        break;
    case CMD_WRITE_FILE_DATA:
        anctool_printf("CMD_WRITE_FILE_DATA\n");
        memcpy((u8 *)&offset, &data[1], 4);
        anctool_ack_write_file_data(offset, &data[5], len - 5);
        break;
    case CMD_WRITE_FILE_END:
        anctool_printf("CMD_WRITE_FILE_END\n");
        anctool_ack_write_file_end();
        break;
    //ear 2 pc cmd
    case CMD_MUTE_TRAIN_ONLY_END:
        anctool_printf("pc ack cmd=[%d]!\n", cmd);
        break;
    case CMD_GET_CHIP_VERSION:
        app_anctool_ack_get_chip_version();
        anctool_printf("CMD_GET_CHIP_VERSION\n");
        break;
    case CMD_TRANS_MUTE_TRAIN:
        anctool_printf("CMD_TOOLS_GET_GAIN\n");
        if (len > 1) {
            memcpy((u8 *)&value, &data[1], 4);
            anc_api_set_trans_aim_pow(value);
        }
        __this->mute_train_flag = 2;
        anc_api_set_callback(anctool_callback, anctool_pow_callback);
        anc_train_api_set(ANC_DEVELOPER_MODE, 1, __this->para);//设置为开发者模式
        anc_train_api_set(ANC_TRANS_MUTE_TARIN, 0, __this->para);
        break;
    default:
        cmd = CMD_UNDEFINE;
        anctool_api_write(&cmd, 1);
        break;
    }
}

static void app_anctool_spp_tx_data(u8 *data, u16 size)
{
    user_send_cmd_prepare(USER_CTRL_SPP_SEND_DATA, size, data);
}

const struct anctool_data app_anctool_data = {
    .recv_packet = app_anctool_module_deal,
    .send_packet = app_anctool_spp_tx_data,
};

u8 app_anctool_spp_rx_data(u8 *packet, u16 size)
{
    __this->pack_flag = 0;
    anctool_api_rx_data(packet, size);
    return __this->pack_flag;
}

void app_anctool_spp_connect(void)
{
    anctool_printf("%s, spp_connect!\n", __FUNCTION__);
    anctool_api_init(&app_anctool_data);
    __this->para = anc_api_get_train_param();
}

void app_anctool_spp_disconnect(void)
{
    anctool_printf("%s, spp_disconnect!\n", __FUNCTION__);
    anctool_api_uninit();
}

#endif
