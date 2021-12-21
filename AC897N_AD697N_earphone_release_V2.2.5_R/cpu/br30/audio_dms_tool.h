#ifndef _AUDIO_ENC_TOOL_H_
#define _AUDIO_ENC_TOOL_H_

#include "generic/typedef.h"

#define	DMS_TEST_MASTER_MIC				0x01		//测试主MIC
#define	DMS_TEST_SLAVE_MIC   			0x02 		//测试副MIC
#define DMS_TEST_OPEN_ALGORITHM    		0x03		//测试dms算法

#define DMS_TEST_ACK_SUCCESS			0x01		//命令接收成功
#define DMS_TEST_ACK_FALI				0x02		//命令接收失败

#define DMS_TEST_SPP_MAGIC				0x55BB
#define DMS_SPP_PACK_NUM				sizeof(dms_spp_data_t)			//数据包总长度

typedef struct {
    u16 magic;
    u16 crc;
    u8 dat[4];
} dms_spp_data_t;

typedef struct {
    u8 parse_seq;
    dms_spp_data_t rx_buf;
    dms_spp_data_t tx_buf;
} dms_spp_t;
//dmsspp测试初始化接口
void dms_spp_init(void);
//dmsspp卸载接口
void dms_spp_unit(void);

#endif/*_AUDIO_ENC_TOOL_H_*/
