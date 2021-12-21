
# make 编译并下载
# make VERBOSE=1 显示编译详细过程
# make clean 清除编译临时文件

# 工具路径设置
ifeq ($(OS), Windows_NT)
# Windows 下工具链位置
TOOL_DIR := C:/JL/pi32/bin
CC    := clang.exe
CXX   := clang.exe
LD    := pi32v2-lto-wrapper.exe
AR    := pi32v2-lto-ar.exe
MKDIR := mkdir_win -p
RM    := rm -rf

SYS_LIB_DIR := C:/JL/pi32/pi32v2-lib/r3
SYS_INC_DIR := C:/JL/pi32/pi32v2-include

## 后处理脚本
POST_SCRIPT     := cpu\br30\tools\download.bat
RUN_POST_SCRIPT := $(POST_SCRIPT)
else
# Linux 下工具链位置
TOOL_DIR := /opt/jieli/pi32v2/bin
CC    := clang
CXX   := clang++
LD    := lto-wrapper
AR    := lto-ar
MKDIR := mkdir -p
RM    := rm -rf

SYS_LIB_DIR := $(TOOL_DIR)/../lib/r3
SYS_INC_DIR := $(TOOL_DIR)/../include

## 后处理脚本
POST_SCRIPT     := cpu/br30/tools/download.sh
RUN_POST_SCRIPT := bash $(POST_SCRIPT)
endif

CC  := $(TOOL_DIR)/$(CC)
CXX := $(TOOL_DIR)/$(CXX)
LD  := $(TOOL_DIR)/$(LD)
AR  := $(TOOL_DIR)/$(AR)
# 输出文件设置
OUT_ELF   := cpu/br30/tools/sdk.elf
OBJ_FILE  := $(OUT_ELF).objs.txt
# 编译路径设置
BUILD_DIR := objs

# 编译参数设置
CFLAGS := \
	-target pi32v2 \
	-mcpu=r3 \
	-integrated-as \
	-flto \
	-Wuninitialized \
	-Wno-invalid-noreturn \
	-fno-common \
	-integrated-as \
	-Oz \
	-g \
	-flto \
	-fallow-pointer-null \
	-fprefer-gnu-section \
	-Wno-shift-negative-value \
	-Wundef \
	-fms-extensions \


# 宏定义
DEFINES := \
	-DSUPPORT_MS_EXTENSIONS \
	-DCONFIG_CPU_BR30 \
	-DCONFIG_RELEASE_ENABLE \
	-DCONFIG_SUPPORT_WIFI_DETECT \
	-DCONFIG_NEW_BREDR_ENABLE \
	-DCONFIG_FREE_RTOS_ENABLE \
	-DCONFIG_EQ_SUPPORT_ASYNC \
	-DTCFG_APP_BT_EN=1 \
	-DEVENT_HANDLER_NUM_CONFIG=2 \
	-DEVENT_TOUCH_ENABLE_CONFIG=0 \
	-DEVENT_POOL_SIZE_CONFIG=512 \
	-DCONFIG_EVENT_KEY_MAP_ENABLE=0 \
	-DTIMER_POOL_NUM_CONFIG=15 \
	-DAPP_ASYNC_POOL_NUM_CONFIG=0 \
	-DUSE_SDFILE_NEW=1 \
	-DSDFILE_STORAGE=0 \
	-DVFS_FILE_POOL_NUM_CONFIG=1 \
	-DFS_VERSION=0x020001 \
	-DFATFS_VERSION=0x020101 \
	-DSDFILE_VERSION=0x020000 \
	-DVFS_ENABLE=1 \
	-DVM_MAX_SIZE_CONFIG=16*1024 \
	-DVM_ITEM_MAX_NUM=128 \
	-DCONFIG_TWS_ENABLE \
	-DCONFIG_EARPHONE_CASE_ENABLE \
	-DAUDIO_REC_LITE \
	-DAUDIO_DEC_LITE \
	-DAUDIO_REC_POOL_NUM=1 \
	-DAUDIO_DEC_POOL_NUM=3 \
	-DSBC_CUSTOM_DECODER_BUF_SIZE=1 \
	-DCONFIG_BTCTRLER_TASK_DEL_ENABLE \
	-DCONFIG_UPDATA_ENABLE \
	-DCONFIG_OTA_UPDATA_ENABLE \
	-DCONFIG_ITEM_FORMAT_VM \
	-DCONFIG_DNS_ENABLE \
	-DCONFIG_ASR_ENABLE \
	-DCONFIG_DMS_MALLOC \
	-DCONFIG_MMU_ENABLE \
	-DCONFIG_SBC_CODEC_HW \
	-DCONFIG_MSBC_CODEC_HW \
	-DCONFIG_AEC_M=128 \
	-DCONFIG_AUDIO_ONCHIP \
	-DCONFIG_MEDIA_NEW_ENABLE \
	-D__GCC_PI32V2__ \
	-DCONFIG_NEW_ECC_ENABLE \
	-DUSB_SLAVE_SUPPORT_MSD \


# 头文件搜索路径
INCLUDES := \
	-Iinclude_lib \
	-Iinclude_lib/driver \
	-Iinclude_lib/driver/device \
	-Iinclude_lib/driver/cpu/br30 \
	-Iinclude_lib/system \
	-Iinclude_lib/system/generic \
	-Iinclude_lib/system/device \
	-Iinclude_lib/system/fs \
	-Iinclude_lib/system/ui \
	-Iinclude_lib/btctrler \
	-Iinclude_lib/btctrler/port/br30 \
	-Iinclude_lib/update \
	-Iinclude_lib/agreement \
	-Iinclude_lib/btstack/third_party/common \
	-Iinclude_lib/btstack/third_party/rcsp \
	-Iinclude_lib/media/media_new \
	-Iinclude_lib/media/media_new/media \
	-Iinclude_lib/media/media_new/media/cpu/br30 \
	-Iinclude_lib/media/media_new/media/cpu/br30/asm \
	-Iapps/common \
	-Iapps/earphone/include \
	-Iapps/common/power_manage \
	-Iapps/common/device \
	-Iapps/common/audio \
	-Iapps/common/include \
	-Iapps/common/config/include \
	-Iapps/common/dev_manager \
	-Iapps/common/third_party_profile/common \
	-Iapps/common/third_party_profile/jieli \
	-Iapps/common/third_party_profile/jieli/trans_data_demo \
	-Iapps/common/third_party_profile/jieli/online_db \
	-Iapps/common/third_party_profile/jieli/JL_rcsp \
	-Iapps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting \
	-Iapps/common/third_party_profile/jieli/JL_rcsp/bt_trans_data \
	-Iapps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol \
	-Iapps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata \
	-Iapps/earphone/board/br30 \
	-Icpu/br30 \
	-Iapps/common/third_party_profile/Tecent_LL/include \
	-Iapps/common/third_party_profile/Tecent_LL/tecent_ll_demo \
	-Iapps/common/cJSON \
	-Iapps/common/usb \
	-Iapps/common/usb/device \
	-Iapps/common/usb/host \
	-Iapps/common/third_party_profile/tm_gma_protocol \
	-Iapps/common/third_party_profile/dma_deal \
	-I$(SYS_INC_DIR) \


# 需要编译的 .c 文件
c_SRC_FILES := \
	apps/common/audio/audio_digital_vol.c \
	apps/common/audio/audio_noise_gate.c \
	apps/common/audio/audio_plc.c \
	apps/common/audio/sine_make.c \
	apps/common/audio/uartPcmSender.c \
	apps/common/audio/wm8978/iic.c \
	apps/common/audio/wm8978/wm8978.c \
	apps/common/cJSON/cJSON.c \
	apps/common/config/app_config.c \
	apps/common/config/bt_profile_config.c \
	apps/common/config/ci_transport_uart.c \
	apps/common/debug/debug.c \
	apps/common/debug/debug_lite.c \
	apps/common/dev_manager/dev_manager.c \
	apps/common/dev_manager/dev_reg.c \
	apps/common/device/gSensor/SC7A20.c \
	apps/common/device/gSensor/STK8321.c \
	apps/common/device/gSensor/da230.c \
	apps/common/device/gSensor/gSensor_manage.c \
	apps/common/device/gx8002_npu/gx8002_npu.c \
	apps/common/device/gx8002_npu/gx8002_npu_event_deal.c \
	apps/common/device/gx8002_npu/gx8002_upgrade/gx_uart_upgrade.c \
	apps/common/device/gx8002_npu/gx8002_upgrade/gx_uart_upgrade_porting.c \
	apps/common/device/gx8002_npu/gx8002_upgrade/sdfile_upgrade/gx_uart_upgrade_sdfile.c \
	apps/common/device/gx8002_npu/gx8002_upgrade/spp_upgrade/gx_fifo.c \
	apps/common/device/gx8002_npu/gx8002_upgrade/spp_upgrade/gx_uart_upgrade_spp.c \
	apps/common/device/in_ear_detect/in_ear_detect.c \
	apps/common/device/in_ear_detect/in_ear_manage.c \
	apps/common/device/ir_sensor/ir_manage.c \
	apps/common/device/ir_sensor/jsa1221.c \
	apps/common/file_operate/file_bs_deal.c \
	apps/common/file_operate/file_manager.c \
	apps/common/jl_kws/jl_kws_algo.c \
	apps/common/jl_kws/jl_kws_audio.c \
	apps/common/jl_kws/jl_kws_event.c \
	apps/common/jl_kws/jl_kws_main.c \
	apps/common/key/adkey.c \
	apps/common/key/adkey_rtcvdd.c \
	apps/common/key/ctmu_touch_key.c \
	apps/common/key/iokey.c \
	apps/common/key/irkey.c \
	apps/common/key/key_driver.c \
	apps/common/key/touch_key.c \
	apps/common/key/uart_key.c \
	apps/common/music/breakpoint.c \
	apps/common/music/music_player.c \
	apps/common/third_party_profile/TME/TME_config.c \
	apps/common/third_party_profile/TME/TME_tws.c \
	apps/common/third_party_profile/TME/TME_user_main.c \
	apps/common/third_party_profile/TME/le_tme_module.c \
	apps/common/third_party_profile/TME/tme_spp_user.c \
	apps/common/third_party_profile/Tecent_LL/tecent_ll_demo/ll_demo.c \
	apps/common/third_party_profile/Tecent_LL/tecent_ll_demo/ll_task.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_import.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_data.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_device.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_event.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_ota.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_service.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_template.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_base64.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_crc.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_hmac.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_log.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_md5.c \
	apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_sha1.c \
	apps/common/third_party_profile/common/3th_profile_api.c \
	apps/common/third_party_profile/common/custom_cfg.c \
	apps/common/third_party_profile/common/mic_rec.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_bt_name_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_eq_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_high_low_vol_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_key_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_led_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_mic_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_music_info_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_time_stamp_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_work_setting.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_bluetooth.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_customer_user.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_opt.c \
	apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_tws_sync.c \
	apps/common/third_party_profile/jieli/JL_rcsp/bt_trans_data/le_rcsp_adv_module.c \
	apps/common/third_party_profile/jieli/JL_rcsp/bt_trans_data/rcsp_adv_spp_user.c \
	apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_adv_user_update.c \
	apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_ch_loader_download.c \
	apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_user_update.c \
	apps/common/third_party_profile/jieli/online_db/online_db_deal.c \
	apps/common/third_party_profile/jieli/online_db/spp_online_db.c \
	apps/common/third_party_profile/jieli/trans_data_demo/le_trans_data.c \
	apps/common/third_party_profile/jieli/trans_data_demo/spp_trans_data.c \
	apps/common/third_party_profile/xiaomi/le_mi_server.c \
	apps/common/third_party_profile/xiaomi/mi_spp_user.c \
	apps/common/third_party_profile/xiaomi/mma_tws.c \
	apps/common/third_party_profile/xiaomi/mma_update_user.c \
	apps/common/update/update.c \
	apps/common/update/update_tws.c \
	apps/common/update/update_tws_new.c \
	apps/common/usb/device/descriptor.c \
	apps/common/usb/device/msd.c \
	apps/common/usb/device/msd_upgrade.c \
	apps/common/usb/device/task_pc.c \
	apps/common/usb/device/usb_device.c \
	apps/common/usb/device/user_setup.c \
	apps/common/usb/usb_config.c \
	apps/earphone/aec/br30/audio_aec.c \
	apps/earphone/aec/br30/audio_aec_dms.c \
	apps/earphone/aec/br30/audio_aec_online.c \
	apps/earphone/app_ancbox.c \
	apps/earphone/app_anctool.c \
	apps/earphone/app_main.c \
	apps/earphone/ble_adv.c \
	apps/earphone/board/br30/board_ac8972a_demo.c \
	apps/earphone/board/br30/board_ac8973a_anc.c \
	apps/earphone/board/br30/board_ac8976_ms70.c \
	apps/earphone/board/br30/board_ac8976a_anc.c \
	apps/earphone/board/br30/board_ac8976a_dms.c \
	apps/earphone/board/br30/board_ac8976a_npu.c \
	apps/earphone/board/br30/board_ac8976d_tws.c \
	apps/earphone/board/br30/board_ac897n_sd_demo.c \
	apps/earphone/board/br30/board_ad6973a_anc.c \
	apps/earphone/board/br30/board_ad697n_anc.c \
	apps/earphone/board/br30/board_ad697n_demo.c \
	apps/earphone/bt_auto_test.c \
	apps/earphone/bt_background.c \
	apps/earphone/bt_ble.c \
	apps/earphone/bt_tws.c \
	apps/earphone/default_event_handler.c \
	apps/earphone/earphone.c \
	apps/earphone/eartch_event_deal.c \
	apps/earphone/fs_test.c \
	apps/earphone/idle.c \
	apps/earphone/key_event_deal.c \
	apps/earphone/ll_sync_demo/ll_sync_demo.c \
	apps/earphone/log_config/app_config.c \
	apps/earphone/log_config/lib_btctrler_config.c \
	apps/earphone/log_config/lib_btstack_config.c \
	apps/earphone/log_config/lib_driver_config.c \
	apps/earphone/log_config/lib_media_config.c \
	apps/earphone/log_config/lib_system_config.c \
	apps/earphone/log_config/lib_update_config.c \
	apps/earphone/music/music.c \
	apps/earphone/pbg_demo.c \
	apps/earphone/pc/pc.c \
	apps/earphone/power_manage/app_charge.c \
	apps/earphone/power_manage/app_chargestore.c \
	apps/earphone/power_manage/app_power_manage.c \
	apps/earphone/rcsp/jl_phone_app.c \
	apps/earphone/rcsp/rcsp_adv.c \
	apps/earphone/tme/tme_earphone.c \
	apps/earphone/tme/tme_key.c \
	apps/earphone/tone_table.c \
	apps/earphone/trans_data_demo/trans_data_demo.c \
	apps/earphone/ui_manage.c \
	apps/earphone/user_cfg.c \
	apps/earphone/version.c \
	apps/earphone/vol_sync.c \
	apps/earphone/xm_mma/mma_earphone.c \
	apps/earphone/xm_mma/mma_key.c \
	cpu/br30/adc_api.c \
	cpu/br30/aec_tool.c \
	cpu/br30/app_audio.c \
	cpu/br30/audio_anc.c \
	cpu/br30/audio_capture.c \
	cpu/br30/audio_codec_clock.c \
	cpu/br30/audio_cvp_demo.c \
	cpu/br30/audio_dac_digital_volume.c \
	cpu/br30/audio_dec.c \
	cpu/br30/audio_dec/audio_dec_file.c \
	cpu/br30/audio_dms_tool.c \
	cpu/br30/audio_enc.c \
	cpu/br30/audio_iis.c \
	cpu/br30/audio_link.c \
	cpu/br30/audio_mic_capless.c \
	cpu/br30/audio_mic_codec.c \
	cpu/br30/audio_sync.c \
	cpu/br30/charge.c \
	cpu/br30/chargestore.c \
	cpu/br30/clock_manager.c \
	cpu/br30/ctmu.c \
	cpu/br30/eq_config.c \
	cpu/br30/iic_hw.c \
	cpu/br30/iic_soft.c \
	cpu/br30/irflt.c \
	cpu/br30/lp_touch_key.c \
	cpu/br30/lp_touch_key_epd.c \
	cpu/br30/overlay_code.c \
	cpu/br30/power_api.c \
	cpu/br30/pwm_led.c \
	cpu/br30/setup.c \
	cpu/br30/spi.c \
	cpu/br30/tone_player.c \
	cpu/br30/uart_dev.c \


# 需要编译的 .S 文件
S_SRC_FILES := \
	apps/earphone/sdk_version.z.S \


# 需要编译的 .s 文件
s_SRC_FILES :=


# 需要编译的 .cpp 文件
cpp_SRC_FILES :=


# 链接参数
LFLAGS := \
	--plugin-opt=-pi32v2-always-use-itblock=false \
	--plugin-opt=-enable-ipra=true \
	--plugin-opt=-pi32v2-merge-max-offset=4096 \
	--plugin-opt=-pi32v2-enable-simd=true \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-enable-movable-region=true \
	--plugin-opt=-movable-region-section-prefix=movable.slot. \
	--plugin-opt=-global-merge-on-const \
	--plugin-opt=-inline-threshold=10 \
	--plugin-opt=-inline-normal-into-special-section=true \
	--plugin-opt=-dont-used-symbol-list=malloc,free,sprintf,printf,puts,putchar \
	--plugin-opt=save-temps \
	--plugin-opt=-pi32v2-enable-rep-memop \
	--sort-common \
	--dont-complain-call-overflow \
	--plugin-opt=-used-symbol-file=cpu/br30/sdk_used_list.used \
	--start-group \
	include_lib/liba/br30/cpu.a \
	include_lib/liba/br30/system.a \
	include_lib/liba/br30/btstack.a \
	include_lib/liba/br30/btctrler.a \
	include_lib/liba/br30/aec.a \
	include_lib/liba/br30/media.a \
	include_lib/liba/br30/libepmotion.a \
	include_lib/liba/br30/libAptFilt_pi32v2_OnChip.a \
	include_lib/liba/br30/libEchoSuppress_pi32v2_OnChip.a \
	include_lib/liba/br30/libNoiseSuppress_pi32v2_OnChip.a \
	include_lib/liba/br30/libSplittingFilter_pi32v2_OnChip.a \
	include_lib/liba/br30/libDelayEstimate_pi32v2_OnChip.a \
	include_lib/liba/br30/libOpcore_maskrom_pi32v2_OnChip.a \
	include_lib/liba/br30/libDualMicSystem_pi32v2_OnChip.a \
	include_lib/liba/br30/wtg_dec_lib.a \
	include_lib/liba/br30/opus_enc_lib.a \
	include_lib/liba/br30/sbc_eng_lib.a \
	include_lib/liba/br30/libFFT_pi32v2_OnChip.a \
	include_lib/liba/br30/br30_bt_aac_mask_code.a \
	include_lib/liba/br30/mp3_dec_lib.a \
	include_lib/liba/br30/mp3_decstream_lib.a \
	include_lib/liba/br30/wma_dec_lib.a \
	include_lib/liba/br30/wma_decstream_lib.a \
	include_lib/liba/br30/wav_dec_lib.a \
	include_lib/liba/br30/crypto_toolbox_Ospeed.a \
	include_lib/liba/br30/lib_esco_repair.a \
	include_lib/liba/br30/limiter_noiseGate.a \
	include_lib/liba/br30/agreement.a \
	include_lib/liba/br30/bt_hash_enc.a \
	include_lib/liba/br30/rcsp_stack.a \
	include_lib/liba/br30/tme_stack.a \
	include_lib/liba/br30/math.a \
	include_lib/liba/br30/JL_Phone_Call.a \
	include_lib/liba/br30/mma_stack.a \
	include_lib/liba/br30/speex_enc_lib.a \
	include_lib/liba/br30/media_app.a \
	include_lib/liba/br30/lib_sur_cal.a \
	include_lib/liba/br30/lib_vbass_cal.a \
	include_lib/liba/br30/lib_resample_cal.a \
	include_lib/liba/br30/lib_pitchshifter.a \
	include_lib/liba/br30/lfaudio_plc_lib.a \
	include_lib/liba/br30/update.a \
	include_lib/liba/br30/lib_dns.a \
	include_lib/liba/br30/compressor.a \
	include_lib/liba/br30/crossover_coff.a \
	include_lib/liba/br30/limiter.a \
	--end-group \
	-Tcpu/br30/sdk.ld \
	-M=cpu/br30/tools/sdk.map \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-mattr=+fprev1 \


LIBPATHS := \
	-L$(SYS_LIB_DIR) \


LIBS := \
	$(SYS_LIB_DIR)/libm.a \
	$(SYS_LIB_DIR)/libc.a \
	$(SYS_LIB_DIR)/libm.a \
	$(SYS_LIB_DIR)/libcompiler-rt.a \



c_OBJS    := $(c_SRC_FILES:%.c=%.c.o)
S_OBJS    := $(S_SRC_FILES:%.S=%.S.o)
s_OBJS    := $(s_SRC_FILES:%.s=%.s.o)
cpp_OBJS  := $(cpp_SRC_FILES:%.cpp=%.cpp.o)

OBJS      := $(c_OBJS) $(S_OBJS) $(s_OBJS) $(cpp_OBJS)
DEP_FILES := $(OBJS:%.o=%.d)


OBJS      := $(addprefix $(BUILD_DIR)/, $(OBJS))
DEP_FILES := $(addprefix $(BUILD_DIR)/, $(DEP_FILES))


VERBOSE ?= 0
ifeq ($(VERBOSE), 1)
QUITE :=
else
QUITE := @
endif

.PHONY: all clean pre_build

all: pre_build $(OUT_ELF)
	@echo +POST-BUILD
	$(QUITE) $(RUN_POST_SCRIPT) sdk

pre_build:
	@echo +PRE-BUILD
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P cpu/br30/sdk_used_list.c -o cpu/br30/sdk_used_list.used
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P cpu/br30/sdk_ld.c -o cpu/br30/sdk.ld
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -D__LD__ -E -P cpu/br30/tools/download.c -o $(POST_SCRIPT)
	$(QUITE) tools\utils\fixbat.exe $(POST_SCRIPT)

clean:
	$(QUITE) $(RM) $(OUT_ELF)
	$(QUITE) $(RM) $(OBJS)
	$(QUITE) $(RM) $(DEP_FILES)

$(OUT_ELF): $(OBJS)
	@echo +LINK $@
	$(file >$(OBJ_FILE), $(OBJS))
	$(QUITE) $(LD) -o $(OUT_ELF) @$(OBJ_FILE) $(LFLAGS) $(LIBPATHS) $(LIBS)

$(BUILD_DIR)/%.c.o : %.c
	@echo +CC $<
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.S.o : %.S
	@echo +AS $<
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.s.o : %.s
	@echo +AS $<
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.cpp.o : %.cpp
	@echo +CXX $<
	@$(MKDIR) $(@D)
	@$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)
