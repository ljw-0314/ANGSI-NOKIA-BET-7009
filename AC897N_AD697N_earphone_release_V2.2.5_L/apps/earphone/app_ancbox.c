#include "init.h"
#include "app_config.h"
#include "system/includes.h"

#if TCFG_ANC_BOX_ENABLE

#include "audio_anc.h"
#include "asm/charge.h"
#include "asm/chargestore.h"
#include "user_cfg.h"
#include "device/vm.h"
#include "app_action.h"
#include "app_main.h"
#include "app_ancbox.h"
#include "app_power_manage.h"
#include "anc_btspp.h"
#include "user_cfg.h"

#define LOG_TAG_CONST       APP_ANCBOX
#define LOG_TAG             "[APP_ANCBOX]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

/* #define anc_coeff_total_size	sizeof(anc_coeff_t) */
#define ANC_VERSION             1//有必要时才更新该值(例如结构体数据改了)

enum {
    FILE_ID_COEFF = 0,  //系数文件ID号
    FILE_ID_PCM = 1,    //播放文件ID号
    FILE_ID_MIC_SPK = 2,//mic spk文件ID号
};

struct _ear_parm {
    u8  ts;         //训练步进
    u8  mode;       //训练模式(普通/快速)
    u16 emmtv;      //误差mic下限阈值
    u16 rmmtv;      //参考mic下限阈值
    u8  sdt;        //静音检测时间
    u8  ntt;        //噪声训练时间
    u8  emstt;      //误差mic静音训练时间
    u8  rmstt;      //参考mic静音训练时间
    u8  c1tto;      //系数一次校准超时时间
    u8  c2tto;      //系数二次校准超时时间
    u8  gen;        //增益配置使能位
    u8  gdac;       //dac增益
    s8  grmic;      //参考mic增益
    s8  gemic;      //误差mic增益
    s16 ganc;       //降噪增益
    s16 gpass;      //通透增益
};

struct _ancbox_info {
    u8 ancbox_status;//anc测试盒在线状态
    u8 err_flag;
    u8 status;
    u8 test_flag;
    u8 baud_counter;
    u8 sz_nadap_pow;
    u8 sz_adap_pow;
    u8 sz_mute_pow;
    u8 fz_nadap_pow;
    u8 fz_adap_pow;
    u8 fz_mute_pow;
    u8 wz_nadap_pow;
    u8 wz_adap_pow;
    u8 train_step_succ;
    struct _ear_parm parm;
    anc_train_para_t *para;
    u8 *coeff;
    u32 coeff_ptr;
    u8 idle_flag;
    int anc_timer;
    int baud_timer;
    u8 *file_hdl;
    u32 file_id;
    u32 file_len;
    u32 data_offset;
    u32 data_len;
    u8 *data_ptr;
    u32 type_id;
    u32 type_value;
    anc_gain_t gain;
};

#define DEFAULT_BAUDRATE            9600
#define CMD_ANC_MODULE              0x90//ANC一级命令
enum {
    CMD_ANC_STATUS = 0x00,
    CMD_ANC_SET_START,
    CMD_ANC_MUTE_TRAIN,
    CMD_ANC_SIN_TRAIN,
    CMD_ANC_NOISE_TRAIN,
    CMD_ANC_TEST_ANC_ON,
    CMD_ANC_TEST_ANC_OFF,
    CMD_ANC_SET_STOP,
    CMD_ANC_SET_PARM,
    CMD_ANC_SYS_RESET,
    CMD_ANC_SET_RUN_MODE,
    CMD_ANC_TEST_PASS,
    CMD_ANC_CHANGE_BAUD,
    CMD_ANC_DEVELOPER_MODE, //开发者模式
    CMD_ANC_ADAP,           //开关自适应
    CMD_ANC_WZ_BREAK,       //退出噪声训练
    CMD_ANC_SET_TS,         //单独设置步进
    CMD_ANC_TRAIN_STEP,
    CMD_ANC_GET_TRAIN_STEP,
    CMD_ANC_GET_MUTE_TRAIN_POW,
    CMD_ANC_GET_NOISE_TRAIN_POW,
    CMD_ANC_GET_TRAIN_POW,  //用于手动训练时实时读取收敛值
    CMD_ANC_SET_ID,
    CMD_ANC_GET_ID,
    CMD_ANC_TEST_BYPASS,
    CMD_ANC_CHANGE_MODE,
    CMD_ANC_GET_COEFF_SIZE,
    CMD_ANC_MUTE_TRAIN_ONLY,
    CMD_ANC_GET_VERSION,
    CMD_ANC_TRANS_TRAIN,	 //通透训练

    CMD_ANC_GET_MAC = 0x80,
    CMD_ANC_TOOLS_SYNC,
    CMD_ANC_SET_LINKKEY,
    CMD_ANC_SW_TO_BT,
    CMD_ANC_READ_COEFF,//read start
    CMD_ANC_READ_COEFF_CONTINUE,
    CMD_ANC_WRITE_COEFF,//write start
    CMD_ANC_WRITE_COEFF_CONTINUE,
    CMD_ANC_GET_RESULT,
    CMD_ANC_SET_GAIN,
    CMD_ANC_GET_GAIN,
    CMD_ANC_READ_FILE_START,
    CMD_ANC_READ_FILE_DATA,
    CMD_ANC_WRITE_FILE_START,
    CMD_ANC_WRITE_FILE_DATA,
    CMD_ANC_WRITE_FILE_END,
    CMD_ANC_FAIL = 0xFE,
};

#define ANC_POW_SIZE    15
static u8 anc_pow[ANC_POW_SIZE];
static struct _ancbox_info ancbox_info;
#define __this  (&ancbox_info)
extern void sys_auto_shut_down_disable(void);
extern void sys_auto_shut_down_enable(void);
extern void bt_update_mac_addr(u8 *addr);
extern void set_temp_link_key(u8 *linkkey);
extern void chargestore_set_baudrate(u32 baudrate);
extern void anc_cfg_btspp_update(u8 id, int data);
extern int anc_cfg_btspp_read(u8 id, int *data);
extern int anc_mode_change_tool(u8 dat);

static void ancbox_callback(u8 mode, u8 command)
{
    log_info("ancbox_callback: %d, %d\n", mode, command);
    if (mode & 0x80) {//train step
        __this->err_flag = ANC_EXEC_SUCC;
        __this->train_step_succ = 1;
    } else {
        __this->err_flag = command;
    }
}

static void ancbox_pow_callback(anc_ack_msg_t *msg, u8 step)
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
    case ANC_TRAIN_WZ:
        __this->wz_nadap_pow = anc_powdat_analysis(msg->pow);
        __this->wz_adap_pow = anc_powdat_analysis(msg->temp_pow);
        if (msg->status == ANC_WZ_ADAP_STATUS) {
            for (u8 i = 0; i < (ANC_POW_SIZE - 1); i++) {
                anc_pow[i] = anc_pow[i + 1];
            }
            anc_pow[ANC_POW_SIZE - 1] = anc_powdat_analysis(msg->temp_pow);
        }
        break;
    }
}

static void anc_event_to_user(u8 event, u32 value)
{
    struct sys_event e;
    e.type = SYS_DEVICE_EVENT;
    e.arg  = (void *)DEVICE_EVENT_FROM_ANC;
    e.u.ancbox.event = event;
    e.u.ancbox.value = value;
    sys_event_notify(&e);
}

static void anc_cmd_timeout_deal(void *priv)
{
    log_info("mabe takeup! sys reset!\n");
    cpu_reset();
}

static void anc_cmd_timeout_init(void)
{
    if (__this->anc_timer == 0) {
#if ANC_MIC_DMA_EXPORT
        __this->anc_timer = sys_timeout_add(NULL, anc_cmd_timeout_deal, 5000);
#else
        __this->anc_timer = sys_timeout_add(NULL, anc_cmd_timeout_deal, 1000);
#endif
    } else {
        sys_timer_modify(__this->anc_timer, 1000);
    }
}

static void anc_cmd_timeout_del(void)
{
    if (__this->anc_timer) {
        sys_timeout_del(__this->anc_timer);
        __this->anc_timer = 0;
    }
}

static void anc_baud_timer_deal(void *priv)
{
    __this->baud_counter++;
    if (__this->baud_counter > 5) {
        sys_timer_del(__this->baud_timer);
        __this->baud_timer = 0;
        __this->baud_counter = 0;
        chargestore_set_baudrate(DEFAULT_BAUDRATE);
    }
}

static void anc_wz_timeout_deal(void *priv)
{
    anc_train_api_set(ANC_TEST_WZ_BREAK, 0, __this->para);
}

static void anc_read_file_start(u8 *cmd, u32 id)
{
    u32 data_len;
    __this->file_id = id;
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        __this->file_len = anc_coeff_size_get();
        __this->file_hdl = (u8 *)anc_coeff_read();
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_READ_FILE_START;
        if (__this->file_hdl) {//判断耳机有没有系数
            memcpy(&cmd[2], (u8 *)&__this->file_len, 4);
            chargestore_api_write(cmd, 6);
            anc_cmd_timeout_del();
        } else {
            cmd[1] = CMD_ANC_FAIL;
            chargestore_api_write(cmd, 2);
        }
        break;
    case FILE_ID_MIC_SPK:
        break;
    }
}

static void anc_read_file_data(u8 *cmd, u32 offset, u32 data_len)
{
    u32 read_len;
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        if (__this->file_hdl == NULL) {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_FAIL;
            chargestore_api_write(cmd, 2);
        } else {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_READ_FILE_DATA;
            memcpy(&cmd[2], __this->file_hdl + offset, data_len);
            chargestore_api_write(cmd, data_len + 2);
            if (__this->file_len == offset + data_len) {
                __this->file_hdl = NULL;
            }
        }
        break;
    case FILE_ID_MIC_SPK:
        break;
    }
}

static void anc_write_file_start(u8 *cmd, u32 id, u32 data_len)
{
    __this->file_id = id;
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        __this->file_len = anc_coeff_size_get();
        __this->file_hdl = (u8 *)malloc(__this->file_len);
        __this->data_ptr = (u8 *)malloc(32);
        if ((__this->file_len != data_len) || (__this->file_hdl == NULL) || (__this->data_ptr == NULL)) {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_FAIL;
            chargestore_api_write(cmd, 2);
            log_info("anc coeff size err, %d != %d\n", data_len, __this->file_len);
            if (__this->file_hdl) {
                free(__this->file_hdl);
                __this->file_hdl = NULL;
            }
            if (__this->data_ptr) {
                free(__this->data_ptr);
                __this->data_ptr = NULL;
            }
            return;
        } else {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_WRITE_FILE_START;
            chargestore_api_write(cmd, 2);
            anc_cmd_timeout_del();
        }
        break;
    case FILE_ID_PCM:
        break;
    }
}

static void anc_write_file_data(u8 *cmd, u32 offset, u8 *data, u32 data_len)
{
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        if (__this->file_hdl == NULL || ((offset + data_len) > __this->file_len)) {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_FAIL;
            chargestore_api_write(cmd, 2);
        } else {
            memcpy(__this->file_hdl + offset, data, data_len);
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_WRITE_FILE_DATA;
            chargestore_api_write(cmd, 2);
        }
        break;
    case FILE_ID_PCM:
        break;
    }
}

static void anc_write_file_end(u8 *cmd)
{
    switch (__this->file_id) {
    case FILE_ID_COEFF:
        if (__this->file_hdl == NULL) {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_FAIL;
            chargestore_api_write(cmd, 2);
        } else {
            anc_coeff_write((int *)__this->file_hdl, __this->file_len);
            free(__this->file_hdl);
            free(__this->data_ptr);
            __this->file_hdl = NULL;
            __this->data_ptr = NULL;
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_WRITE_FILE_END;
            chargestore_api_write(cmd, 2);
        }
        break;
    case FILE_ID_PCM:
        break;
    }
}

int app_ancbox_event_handler(struct ancbox_event *anc_dev)
{
    u8 cmd[32], mac_addr[6];
    u32 coeff_len;
    u32 anc_coeff_total_size;
    struct application *app = get_current_app();
    switch (anc_dev->event) {
    case CMD_ANC_MUTE_TRAIN_ONLY://独立的训练模式
        log_info("event_CMD_ANC_MUTE_TRAIN_ONLY\n");
        if (__this->status != CMD_ANC_MUTE_TRAIN_ONLY) {
            __this->status = CMD_ANC_MUTE_TRAIN_ONLY;
            __this->err_flag = 0;
            sys_auto_shut_down_disable();
            anc_cmd_timeout_del();
            anc_train_api_set(ANC_MUTE_TARIN, 1, __this->para);
        }
        break;

    case CMD_ANC_TRANS_TRAIN://独立的训练模式
        log_info("event_CMD_ANC_TRANS_TRAIN\n");
        if (__this->status != CMD_ANC_TRANS_TRAIN) {
            __this->status = CMD_ANC_TRANS_TRAIN;
            __this->err_flag = 0;
            sys_auto_shut_down_disable();
            anc_cmd_timeout_del();
            anc_train_api_set(ANC_TRANS_MUTE_TARIN, 1, __this->para);
        }
        break;

    case CMD_ANC_SET_START:
        log_info("event_CMD_ANC_SET_STAR\n");
        __this->test_flag = 1;
        __this->status = CMD_ANC_SET_START;
        __this->err_flag = 0;
        sys_auto_shut_down_disable();
        anc_cmd_timeout_del();
        memset(anc_pow, 0, ANC_POW_SIZE);
        break;
    case CMD_ANC_MUTE_TRAIN:
        log_info("event_CMD_ANC_MUTE_TRAIN\n");
        if (__this->status != CMD_ANC_MUTE_TRAIN) {
            __this->status = CMD_ANC_MUTE_TRAIN;
            anc_train_api_set(ANC_MUTE_TARIN, 0, __this->para);
        }
        break;
    case CMD_ANC_SIN_TRAIN:
        log_info("event_CMD_ANC_SIN_TRAIN\n");
        if (__this->status != CMD_ANC_SIN_TRAIN) {
            __this->status = CMD_ANC_SIN_TRAIN;
            anc_train_api_set(ANC_TRAIN_STEP_1, 0, __this->para);
        }
        break;
    case CMD_ANC_NOISE_TRAIN:
        log_info("event_CMD_ANC_TRAIN_SPK_ON\n");
        if (__this->status != CMD_ANC_NOISE_TRAIN) {
            __this->status = CMD_ANC_NOISE_TRAIN;
            anc_train_api_set(ANC_NOISE_TARIN, 0, __this->para);
        }
        break;
    case CMD_ANC_TEST_ANC_ON:
        log_info("event_CMD_ANC_TEST_ANC_ON\n");
        if (__this->test_flag == 1) {
            __this->status = CMD_ANC_TEST_ANC_ON;
            anc_train_api_set(ANC_MODE_ON, 0, __this->para);
        } else {
            log_info("switch to ancon!\n");
            anc_api_set_fade_en(0);
            anc_mode_switch(ANC_ON, 0);
        }
        break;
    case CMD_ANC_TEST_ANC_OFF:
        log_info("event_CMD_ANC_TEST_ANC_OFF\n");
        if (__this->test_flag == 1) {
            __this->status = CMD_ANC_TEST_ANC_OFF;
            anc_train_api_set(ANC_MODE_OFF, 0, __this->para);
        } else {
            log_info("switch to ancoff!\n");
            anc_api_set_fade_en(0);
            anc_mode_switch(ANC_OFF, 0);
        }
        break;
    case CMD_ANC_TEST_PASS:
        log_info("event_CMD_ANC_TEST_PASS\n");
        if (__this->test_flag == 1) {
            __this->status = CMD_ANC_TEST_PASS;
            anc_train_api_set(ANC_PASS_MODE_ON, 0, __this->para);
        } else {
            log_info("switch to pass!\n");
            anc_api_set_fade_en(0);
            anc_mode_switch(ANC_TRANSPARENCY, 0);
        }
        break;
    case CMD_ANC_SET_STOP:
        log_info("event_CMD_ANC_SET_STOP\n");
        __this->status = CMD_ANC_SET_STOP;
        __this->err_flag = 0;
        if (__this->test_flag) {
            __this->test_flag = 0;
            anc_train_api_set(ANC_TRAIN_EXIT, 0, __this->para);
            sys_auto_shut_down_enable();
        }
        break;
    case CMD_ANC_SYS_RESET:
        log_info("event_CMD_ANC_SYS_RESET\n");
        os_time_dly(3);
        cpu_reset();
        break;
    case CMD_ANC_SET_RUN_MODE:
        log_info("event_CMD_ANC_SET_RUN_MODE = %d\n", anc_dev->value);
        anc_api_set_fade_en(0);
        if (anc_dev->value == 0) {
            anc_mode_switch(ANC_OFF, 0);
        } else if (anc_dev->value == 1) {
            anc_mode_switch(ANC_ON, 0);
        } else {
            anc_mode_switch(ANC_TRANSPARENCY, 0);
        }
        break;
    case CMD_ANC_TEST_BYPASS:
        log_info("event_CMD_ANC_TEST_BYPASS\n");
        anc_mode_switch(ANC_BYPASS, 0);
        //bypass,此处调用底层接口根据anc_dev->value需要切换到那个mic的bypass
        break;
    case CMD_ANC_CHANGE_MODE:
        log_info("event_CMD_ANC_CHANGE_MODE = %d\n", anc_dev->value);
        anc_mode_change_tool(anc_dev->value);
        //切换FF/FB,此处调用底层接口根据anc_dev->value需要切换到FF/FB
        break;
    case CMD_ANC_STATUS:
    case CMD_ANC_TOOLS_SYNC:
        putchar('S');
        if (app && strcmp(app->name, APP_NAME_IDLE)) {
            os_time_dly(1);
            log_info("not idle app, reset sys!\n");
            cpu_reset();
        } else {
            __this->idle_flag = 1;
        }
        anc_cmd_timeout_init();
        if (__this->para == NULL) {
            __this->para = anc_api_get_train_param();
            anc_api_set_callback(ancbox_callback, ancbox_pow_callback);
        }
        break;
    case CMD_ANC_SET_LINKKEY:
        log_info("CMD_ANC_SET_LINKKEY\n");
        if (app && strcmp(app->name, APP_NAME_BT)) {
            power_set_mode(TCFG_LOWPOWER_POWER_SEL);
            app_var.play_poweron_tone = 0;
            task_switch_to_bt();
            anc_cmd_timeout_del();
        }
        break;
    case CMD_ANC_SW_TO_BT:
        log_info("CMD_ANC_SW_TO_BT\n");
        bt_get_vm_mac_addr(mac_addr);
        bt_update_mac_addr(mac_addr);
        if (app && strcmp(app->name, APP_NAME_BT)) {
            power_set_mode(TCFG_LOWPOWER_POWER_SEL);
            app_var.play_poweron_tone = 0;
            task_switch_to_bt();
            anc_cmd_timeout_del();
        }
        break;
    case CMD_ANC_READ_COEFF://read start
        log_info("CMD_ANC_READ_COEFF\n");
        __this->coeff = (u8 *)anc_coeff_read();
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_READ_COEFF;
        if (__this->coeff == NULL) {
            coeff_len = 0;
        } else {
            anc_coeff_total_size = anc_coeff_size_get();
            coeff_len = anc_coeff_total_size;
        }
        __this->coeff_ptr = 0;
        memcpy(&cmd[2], (u8 *)&coeff_len, 4);
        chargestore_api_write(cmd, 6);
        anc_cmd_timeout_del();
        break;
    case CMD_ANC_WRITE_COEFF://write start
        log_info("CMD_ANC_WRITE_COEFF\n");
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_WRITE_COEFF;
        __this->coeff_ptr = 0;
        if (__this->coeff == NULL) {
            anc_coeff_total_size = anc_coeff_size_get();
            __this->coeff = (u8 *)malloc(anc_coeff_total_size);
            if (__this->coeff == NULL) {
                cmd[1] = CMD_ANC_FAIL;
            }
        }
        chargestore_api_write(cmd, 2);
        anc_cmd_timeout_del();
        break;
    case CMD_ANC_WRITE_COEFF_CONTINUE:
        log_info("CMD_ANC_WRITE_COEFF_CONTINUE\n");
        if (__this->coeff) {
            anc_cmd_timeout_del();
            anc_coeff_total_size = anc_coeff_size_get();
            anc_coeff_write((int *)__this->coeff, anc_coeff_total_size);
            free(__this->coeff);
            __this->coeff = NULL;
            __this->coeff_ptr = 0;
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_WRITE_COEFF_CONTINUE;
            chargestore_api_write(cmd, 2);
        }
        log_info("CMD_ANC_WRITE_COEFF_CONTINUE--------end\n");
        break;
    case CMD_ANC_READ_FILE_START:
        anc_read_file_start(cmd, __this->file_id);
        break;
    case CMD_ANC_READ_FILE_DATA:
        anc_read_file_data(cmd, __this->data_offset, __this->data_len);
        break;
    case CMD_ANC_WRITE_FILE_START:
        anc_write_file_start(cmd, __this->file_id, __this->file_len);
        break;
    case CMD_ANC_WRITE_FILE_DATA:
        anc_write_file_data(cmd, __this->data_offset, __this->data_ptr, __this->data_len);
        break;
    case CMD_ANC_WRITE_FILE_END:
        anc_write_file_end(cmd);
        break;
    case CMD_ANC_SET_GAIN:
        log_info("CMD_ANC_SET_GAIN\n");
        anc_cmd_timeout_del();
        anc_cfg_online_deal(ANC_CFG_WRITE, &__this->gain);
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_SET_GAIN;
        chargestore_api_write(cmd, 2);
        break;
    case CMD_ANC_GET_GAIN:
        log_info("CMD_ANC_GET_GAIN\n");
        anc_cfg_online_deal(ANC_CFG_READ, &__this->gain);
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_GET_GAIN;
        memcpy(&cmd[2], (u8 *)&__this->gain, sizeof(anc_gain_t));
        chargestore_api_write(cmd, 2 + sizeof(anc_gain_t));
        break;
    case CMD_ANC_CHANGE_BAUD:
        log_info("CMD_ANC_CHANGE_BAUD: %d\n", anc_dev->value);
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_CHANGE_BAUD;
        chargestore_api_write(cmd, 2);
        chargestore_api_wait_complete();
        chargestore_set_baudrate(anc_dev->value);
        if (__this->baud_timer) {
            sys_timeout_del(__this->baud_timer);
            __this->baud_timer = 0;
        }
        if (anc_dev->value != DEFAULT_BAUDRATE) {
            __this->baud_timer = sys_timer_add(NULL, anc_baud_timer_deal, 100);
            __this->baud_counter = 0;
        }
        break;
    case CMD_ANC_WZ_BREAK:
        log_info("CMD_ANC_WZ_BREAK: %d s\n", anc_dev->value);
        sys_timeout_add(NULL, anc_wz_timeout_deal, anc_dev->value * 1000);
        break;
    case CMD_ANC_SET_ID:
        log_info("CMD_ANC_SET_ID: %d ,%d\n", __this->type_id, __this->type_value);
        anc_cmd_timeout_del();
        anc_cfg_btspp_update((u8)__this->type_id, (int)__this->type_value);
        cmd[0] = CMD_ANC_MODULE;
        cmd[1] = CMD_ANC_SET_ID;
        chargestore_api_write(cmd, 2);
        break;
    case CMD_ANC_GET_ID:
        log_info("CMD_ANC_GET_ID: %d\n", __this->type_id);
        if (anc_cfg_btspp_read((u8)__this->type_id, (int *)&__this->type_value) == 0) {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_GET_ID;
            memcpy(&cmd[2], (u8 *)&__this->type_value, 4);
            chargestore_api_write(cmd, 6);
        } else {
            cmd[0] = CMD_ANC_MODULE;
            cmd[1] = CMD_ANC_FAIL;
            chargestore_api_write(cmd, 2);
        }
        break;
    }
    return false;
}

void app_ancbox_module_deal(u8 *buf, u8 len)
{
    u8 cmd, i, j;
    u8 sendbuf[32];
    u32 read_len;
    u32 baudrate;
    u32 anc_coeff_total_size;
    u32 value;
    struct _ear_parm parm;
    sendbuf[0] = CMD_ANC_MODULE;
    sendbuf[1] = buf[1];
    __this->ancbox_status = 1;
    __this->baud_counter = 0;
    cmd = buf[1];
    switch (buf[1]) {
    case CMD_ANC_SET_PARM:
        memcpy((u8 *)&parm, &buf[2], sizeof(struct _ear_parm));
        chargestore_api_write(sendbuf, 2);
        if (parm.mode == 0) {
            anc_train_api_set(ANC_CHANGE_COMMAND, ANC_TRAIN_NOMA_MODE, __this->para);
        } else {
            anc_train_api_set(ANC_CHANGE_COMMAND, parm.mode, __this->para);
        }
        anc_train_api_set(ANC_SZ_LOW_THR_SET, parm.emmtv, __this->para);
        anc_train_api_set(ANC_FZ_LOW_THR_SET, parm.rmmtv, __this->para);
        anc_train_api_set(ANC_NONADAP_TIME_SET, parm.sdt, __this->para);
        anc_train_api_set(ANC_SZ_ADAP_TIME_SET, parm.emstt, __this->para);
        anc_train_api_set(ANC_FZ_ADAP_TIME_SET, parm.rmstt, __this->para);
        anc_train_api_set(ANC_WZ_TRAIN_TIME_SET, parm.ntt, __this->para);
        anc_train_api_set(ANC_TRAIN_STEP_SET, parm.ts, __this->para);
        if (parm.gen) {
            anc_param_fill(ANC_CFG_READ, &__this->gain);
            __this->gain.dac_gain = (u8)parm.gdac;
            __this->gain.ref_mic_gain = (u8)parm.grmic;
            __this->gain.err_mic_gain = (u8)parm.gemic;
            __this->gain.anc_gain = (int)parm.ganc;
            __this->gain.transparency_gain = (int)parm.gpass;
            anc_param_fill(ANC_CFG_WRITE, &__this->gain);
        }
        return;
    case CMD_ANC_SET_START:
    case CMD_ANC_SET_STOP:
    case CMD_ANC_MUTE_TRAIN:
    case CMD_ANC_MUTE_TRAIN_ONLY:
    case CMD_ANC_SIN_TRAIN:
    case CMD_ANC_NOISE_TRAIN:
    case CMD_ANC_TEST_ANC_ON:
    case CMD_ANC_TEST_ANC_OFF:
    case CMD_ANC_TEST_PASS:
    case CMD_ANC_SYS_RESET:
        chargestore_api_write(sendbuf, 2);
        break;
    case CMD_ANC_TRANS_TRAIN:
        if (len > 2) {
            memcpy((u8 *)&value, &buf[2], 4);
            anc_api_set_trans_aim_pow(value);
        }
        chargestore_api_write(sendbuf, 2);
        break;
    case CMD_ANC_SET_RUN_MODE:
    case CMD_ANC_TEST_BYPASS:
    case CMD_ANC_CHANGE_MODE:
        anc_event_to_user(cmd, (u32)buf[2]);
        chargestore_api_write(sendbuf, 2);
        return;
    case CMD_ANC_STATUS:
    case CMD_ANC_TOOLS_SYNC:
        //在idle
        if (__this->idle_flag == 0) {
            sendbuf[1] = CMD_ANC_FAIL;
            chargestore_api_write(sendbuf, 2);
        } else {
            sendbuf[2] = ANC_VERSION;//版本
            sendbuf[3] = ANC_TRAIN_MODE;//结构
            chargestore_api_write(sendbuf, 4);
        }
        break;
    case CMD_ANC_GET_MAC:
        bt_get_vm_mac_addr(&sendbuf[2]);
        chargestore_api_write(sendbuf, 8);
        return;
    case CMD_ANC_SET_LINKKEY:
        bt_update_mac_addr(&buf[2]);
        set_temp_link_key(&buf[8]);
        chargestore_api_write(sendbuf, 2);
        break;
    case CMD_ANC_SW_TO_BT:
        chargestore_api_write(sendbuf, 2);
        break;
    case CMD_ANC_READ_COEFF://read start
        chargestore_api_set_timeout(50);
        break;
    case CMD_ANC_READ_COEFF_CONTINUE:
        if (__this->coeff == NULL) {
            sendbuf[1] = CMD_ANC_FAIL;
            chargestore_api_write(sendbuf, 2);
        } else {
            anc_coeff_total_size = anc_coeff_size_get();
            read_len = anc_coeff_total_size - __this->coeff_ptr;
            if (read_len > 30) {
                read_len = 30;
            }
            memcpy(&sendbuf[2], __this->coeff + __this->coeff_ptr, read_len);
            chargestore_api_write(sendbuf, read_len + 2);
            __this->coeff_ptr += read_len;
            if (anc_coeff_total_size == __this->coeff_ptr) {
                __this->coeff = NULL;
                __this->coeff_ptr = 0;
            }
        }
        //读操作不需要推消息处理
        return;
    case CMD_ANC_WRITE_COEFF://write start
        chargestore_api_set_timeout(50);
        memcpy((u8 *)&read_len, buf + 2, 4);
        anc_coeff_total_size = anc_coeff_size_get();
        if (read_len != anc_coeff_total_size) {
            sendbuf[1] = CMD_ANC_FAIL;
            chargestore_api_write(sendbuf, 2);
            log_info("anc coeff size err, %d != %d\n", read_len, anc_coeff_total_size);
            return;
        }
        break;
    case CMD_ANC_WRITE_COEFF_CONTINUE:
        memcpy(__this->coeff + __this->coeff_ptr, buf + 2, len - 2);
        __this->coeff_ptr += (len - 2);
        anc_coeff_total_size = anc_coeff_size_get();
        if (__this->coeff_ptr < anc_coeff_total_size) {
            //未写完成时不推消息
            chargestore_api_write(sendbuf, 2);
            return;
        }
        chargestore_api_set_timeout(1000);
        break;
    case CMD_ANC_READ_FILE_START:
        memcpy((u8 *)&__this->file_id, buf + 2, 4);
        chargestore_api_set_timeout(1000);
        break;
    case CMD_ANC_READ_FILE_DATA:
        memcpy((u8 *)&__this->data_offset, buf + 2, 4);
        memcpy((u8 *)&__this->data_len, buf + 6, 4);
        chargestore_api_set_timeout(1000);
        break;
    case CMD_ANC_WRITE_FILE_START:
        memcpy((u8 *)&__this->file_id, buf + 2, 4);
        memcpy((u8 *)&__this->file_len, buf + 6, 4);
        chargestore_api_set_timeout(1000);
        break;
    case CMD_ANC_WRITE_FILE_DATA:
        memcpy((u8 *)&__this->data_offset, buf + 2, 4);
        memcpy(__this->data_ptr, buf + 6, len - 6);
        __this->data_len = len - 6;
        chargestore_api_set_timeout(1000);
        break;
    case CMD_ANC_WRITE_FILE_END:
        chargestore_api_set_timeout(1000);
        break;
    case CMD_ANC_GET_RESULT:
        sendbuf[2] = __this->err_flag;
        sendbuf[3] = anc_api_get_train_step();
        chargestore_api_write(sendbuf, 4);
        return;//不需要app处理
    case CMD_ANC_SET_GAIN:
        if ((len - 2) != sizeof(anc_gain_t)) {
            sendbuf[1] = CMD_ANC_FAIL;
            chargestore_api_write(sendbuf, 2);
            return;
        } else {
            memcpy((u8 *)&__this->gain, &buf[2], sizeof(anc_gain_t));
            chargestore_api_set_timeout(1000);
        }
        break;
    case CMD_ANC_GET_GAIN:
        chargestore_api_set_timeout(50);
        break;
    case CMD_ANC_CHANGE_BAUD:
        chargestore_api_set_timeout(50);
        memcpy((u8 *)&baudrate, &buf[2], 4);
        anc_event_to_user(cmd, baudrate);
        return;
    case CMD_ANC_DEVELOPER_MODE:
        anc_train_api_set(ANC_DEVELOPER_MODE, (u32)buf[2], __this->para);
        chargestore_api_write(sendbuf, 2);
        return;
    case CMD_ANC_ADAP:
        if (buf[2] == 0) {
            anc_train_api_set(ANC_TEST_NADAP, 0, __this->para);
        } else {
            anc_train_api_set(ANC_TEST_ADAP, 0, __this->para);
        }
        chargestore_api_write(sendbuf, 2);
        return;
    case CMD_ANC_WZ_BREAK:
        anc_event_to_user(cmd, (u32)buf[2]);
        chargestore_api_write(sendbuf, 2);
        return;
    case CMD_ANC_SET_TS:
        anc_train_api_set(ANC_TRAIN_STEP_SET, (u32)buf[2], __this->para);
        chargestore_api_write(sendbuf, 2);
        return;
    case CMD_ANC_TRAIN_STEP:
        __this->train_step_succ = 0;
        anc_train_api_set(ANC_TRAIN_STEP_1, 0, __this->para);
        chargestore_api_write(sendbuf, 2);
        return;
    case CMD_ANC_GET_TRAIN_STEP:
        sendbuf[2] = 0;
        if (__this->train_step_succ) {
            sendbuf[2] = anc_api_get_train_step();
        } else {
            anc_train_api_set(ANC_TRAIN_STEP_CONNUTE, 0, __this->para);
        }
        chargestore_api_write(sendbuf, 3);
        return;
    case CMD_ANC_GET_MUTE_TRAIN_POW:
        sendbuf[2] = __this->sz_nadap_pow;
        sendbuf[3] = __this->sz_adap_pow;
        sendbuf[4] = __this->sz_mute_pow;
        sendbuf[5] = __this->fz_nadap_pow;
        sendbuf[6] = __this->fz_adap_pow;
        sendbuf[7] = __this->fz_mute_pow;
        chargestore_api_write(sendbuf, 8);
        return;
    case CMD_ANC_GET_NOISE_TRAIN_POW:
        sendbuf[2] = __this->wz_nadap_pow;
        sendbuf[3] = __this->wz_adap_pow;
        chargestore_api_write(sendbuf, 4);
        return;
    case CMD_ANC_GET_TRAIN_POW:
        for (i = (ANC_POW_SIZE / 3), j = 2; i < (ANC_POW_SIZE * 2 / 3); i++, j++) {
            sendbuf[j] = anc_pow[i];
        }
        chargestore_api_write(sendbuf, j);
        return;
    case CMD_ANC_SET_ID:
        memcpy((u8 *)&__this->type_id, &buf[2], 4);
        memcpy((u8 *)&__this->type_value, &buf[6], 4);
        chargestore_api_set_timeout(250);
        break;
    case CMD_ANC_GET_ID:
        memcpy((u8 *)&__this->type_id, &buf[2], 4);
        chargestore_api_set_timeout(250);
        break;
    case CMD_ANC_GET_COEFF_SIZE:
        anc_coeff_total_size = anc_coeff_size_get();
        read_len = anc_coeff_total_size;
        memcpy(&sendbuf[2], (u8 *)&read_len, 4);
        chargestore_api_write(sendbuf, 6);
        return;
    case CMD_ANC_GET_VERSION:
        sendbuf[2] = ANC_CHIP_VERSION;
        chargestore_api_write(sendbuf, 3);
        break;
    default:
        sendbuf[1] = CMD_ANC_FAIL;
        chargestore_api_write(sendbuf, 2);
        return;
    }
    anc_event_to_user(cmd, 0);
}

u8 ancbox_get_status(void)
{
    return __this->ancbox_status;
}

void ancbox_clear_status(void)
{
    __this->ancbox_status = 0;
}

#endif


