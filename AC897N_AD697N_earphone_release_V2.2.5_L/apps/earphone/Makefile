
includes += \
	-I$(ROOT)/apps/common/ \
	-I$(ROOT)/apps/$(APP_CASE)/include/ \
	-I$(ROOT)/apps/common/power_manage/ \
	-I$(ROOT)/apps/common/ \
	-I$(ROOT)/apps/common/device/ \
	-I$(ROOT)/apps/common/audio/ \
	-I$(ROOT)/apps/common/include/\
	-I$(ROOT)/apps/common/config/include/\
	-I$(ROOT)/apps/common/dev_manager/ \
	-I$(ROOT)/apps/common/third_party_profile/common/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/trans_data_demo/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/online_db/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/bt_trans_data/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/ \
	-I$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/ \
	-I$(ROOT)/apps/$(APP_CASE)/board/$(CPU)/ \
	-I$(ROOT)/cpu/$(CPU)/ \

includes += \
	-I$(ROOT)/apps/common/third_party_profile/Tecent_LL/include/ \
	-I$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_ll_demo/ \
	-I$(ROOT)/apps/common/cJSON/ \


-include $(ROOT)/apps/common/usb/Makefile.inc

includes += \
	-I$(ROOT)/apps/common/third_party_profile/tm_gma_protocol/ \
	-I$(ROOT)/apps/common/third_party_profile/dma_deal/ \

objs += \
	$(ROOT)/apps/common/key/iokey.o \
	$(ROOT)/apps/common/key/irkey.o \
	$(ROOT)/apps/common/key/adkey.o \
	$(ROOT)/apps/common/key/adkey_rtcvdd.o \
	$(ROOT)/apps/common/key/touch_key.o \
	$(ROOT)/apps/common/key/ctmu_touch_key.o \
	$(ROOT)/apps/common/key/uart_key.o \
	$(ROOT)/apps/common/key/key_driver.o \
	$(ROOT)/apps/common/debug/debug_lite.o \
	$(ROOT)/apps/common/update/update.o \
	$(ROOT)/apps/common/device/ir_sensor/jsa1221.o \
	$(ROOT)/apps/common/device/ir_sensor/ir_manage.o \
	$(ROOT)/apps/common/device/in_ear_detect/in_ear_detect.o \
	$(ROOT)/apps/common/device/in_ear_detect/in_ear_manage.o \
	$(ROOT)/apps/common/device/gSensor/da230.o \
	$(ROOT)/apps/common/device/gSensor/SC7A20.o \
	$(ROOT)/apps/common/device/gSensor/STK8321.o \
	$(ROOT)/apps/common/device/gSensor/gSensor_manage.o \
	$(ROOT)/apps/common/audio/sine_make.o \
	$(ROOT)/apps/common/audio/audio_digital_vol.o \
	$(ROOT)/apps/common/audio/audio_plc.o \
	$(ROOT)/apps/common/audio/audio_noise_gate.o \
	$(ROOT)/apps/common/audio/uartPcmSender.o \
	$(ROOT)/apps/common/audio/wm8978/iic.o \
	$(ROOT)/apps/common/audio/wm8978/wm8978.o \
	$(ROOT)/apps/common/third_party_profile/jieli/online_db/spp_online_db.o \
	$(ROOT)/apps/common/third_party_profile/jieli/online_db/online_db_deal.o \
	$(ROOT)/apps/$(APP_CASE)/app_main.o \
	$(ROOT)/apps/$(APP_CASE)/bt_ble.o \
	$(ROOT)/apps/$(APP_CASE)/fs_test.o \
	$(ROOT)/apps/$(APP_CASE)/version.o \
	$(ROOT)/apps/$(APP_CASE)/idle.o \
	$(ROOT)/apps/$(APP_CASE)/user_cfg.o \
	$(ROOT)/apps/$(APP_CASE)/ui_manage.o \
	$(ROOT)/apps/$(APP_CASE)/vol_sync.o \
	$(ROOT)/apps/$(APP_CASE)/pbg_demo.o \
	$(ROOT)/apps/$(APP_CASE)/bt_auto_test.o \
	$(ROOT)/apps/$(APP_CASE)/tone_table.o \
	$(ROOT)/apps/$(APP_CASE)/ble_adv.o \
	$(ROOT)/apps/$(APP_CASE)/rcsp/rcsp_adv.o \
	$(ROOT)/apps/$(APP_CASE)/rcsp/jl_phone_app.o \
	$(ROOT)/apps/$(APP_CASE)/trans_data_demo/trans_data_demo.o \
	$(ROOT)/apps/$(APP_CASE)/ll_sync_demo/ll_sync_demo.o \
	$(ROOT)/apps/$(APP_CASE)/tme/tme_earphone.o \
	$(ROOT)/apps/$(APP_CASE)/tme/tme_key.o \
	$(ROOT)/apps/$(APP_CASE)/xm_mma/mma_earphone.o \
	$(ROOT)/apps/$(APP_CASE)/xm_mma/mma_key.o \
	$(ROOT)/apps/$(APP_CASE)//power_manage/app_charge.o \
	$(ROOT)/apps/$(APP_CASE)//power_manage/app_chargestore.o \
	$(ROOT)/apps/$(APP_CASE)//power_manage/app_power_manage.o \


objs += \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_import.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_data.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_device.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_event.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_llsync_ota.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_service.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_base64.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_crc.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_hmac.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_log.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_md5.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_utils_sha1.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/ble_qiot_template.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_ll_demo/ll_demo.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_ll_demo/ll_task.o \
	$(ROOT)/apps/common/cJSON/cJSON.o \
#	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/qcloud_wifi_config_error_handle.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/qcloud_wifi_config_log_handle.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/HAL_BTCombo_config.o \
	$(ROOT)/apps/common/third_party_profile/Tecent_LL/tecent_protocol/HAL_Wifi_api.o \


ifeq ($(CONFIG_ANC_ENABLE),y)
objs += \
	$(ROOT)/apps/$(APP_CASE)/app_ancbox.o \
	$(ROOT)/apps/$(APP_CASE)/app_anctool.o \

endif

objs += \
	$(ROOT)/apps/common/third_party_profile/common/3th_profile_api.o \
	$(ROOT)/apps/common/third_party_profile/common/mic_rec.o \
	$(ROOT)/apps/common/third_party_profile/common/custom_cfg.o \
	$(ROOT)/apps/common/third_party_profile/jieli/trans_data_demo/spp_trans_data.o \
	$(ROOT)/apps/common/third_party_profile/jieli/trans_data_demo/le_trans_data.o \
	$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/bt_trans_data/le_rcsp_adv_module.o \
	$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/bt_trans_data/rcsp_adv_spp_user.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_bt_name_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_key_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_led_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_mic_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_time_stamp_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_work_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_eq_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_high_low_vol_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_app_setting/adv_music_info_setting.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_opt.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_tws_sync.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_bluetooth.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/adv_rcsp_protocol/rcsp_adv_customer_user.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_user_update.o \
    $(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_adv_user_update.o \
	$(ROOT)/apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_ch_loader_download.o \
	$(ROOT)/apps/common/third_party_profile/TME/le_tme_module.o \
	$(ROOT)/apps/common/third_party_profile/TME/TME_config.o \
	$(ROOT)/apps/common/third_party_profile/TME/tme_spp_user.o \
	$(ROOT)/apps/common/third_party_profile/TME/TME_tws.o \
	$(ROOT)/apps/common/third_party_profile/TME/TME_user_main.o \
	$(ROOT)/apps/common/third_party_profile/xiaomi/le_mi_server.o \
	$(ROOT)/apps/common/third_party_profile/xiaomi/mi_spp_user.o \
	$(ROOT)/apps/common/third_party_profile/xiaomi/mma_tws.o \
	$(ROOT)/apps/common/third_party_profile/xiaomi/mma_update_user.o \
	$(ROOT)/apps/common/update/update_tws.o \
	$(ROOT)/apps/common/update/update_tws_new.o \

objs += \
	$(ROOT)/apps/$(APP_CASE)/bt_tws.o \
	$(ROOT)/apps/$(APP_CASE)/earphone.o \
	$(ROOT)/apps/$(APP_CASE)/key_event_deal.o \
	$(ROOT)/apps/$(APP_CASE)/eartch_event_deal.o \



objs += \
	$(ROOT)/apps/$(APP_CASE)/log_config/lib_btctrler_config.o \
	$(ROOT)/apps/$(APP_CASE)/log_config/lib_driver_config.o \
	$(ROOT)/apps/$(APP_CASE)/log_config/lib_system_config.o \
	$(ROOT)/apps/$(APP_CASE)/log_config/lib_update_config.o \
	$(ROOT)/apps/$(APP_CASE)/log_config/lib_media_config.o \
	$(ROOT)/apps/$(APP_CASE)/log_config/lib_btstack_config.o \
	$(ROOT)/apps/$(APP_CASE)/log_config/app_config.o \



#------------- EQ config-----------------#
# objs += \
	$(ROOT)/apps/$(APP_CASE)/app_eq.o \

objs += \
	$(ROOT)/apps/common/config/app_config.o \
	$(ROOT)/apps/common/config/ci_transport_uart.o \
	$(ROOT)/apps/common/config/bt_profile_config.o \

ifeq ($(CONFIG_SD_ENABLE),y)
objs += \
	$(ROOT)/apps/$(APP_CASE)/bt_background.o \
	$(ROOT)/apps/$(APP_CASE)/default_event_handler.o \
	$(ROOT)/apps/$(APP_CASE)/music/music.o \
	$(ROOT)/apps/common/music/breakpoint.o \
	$(ROOT)/apps/common/music/music_player.o \
	$(ROOT)/apps/common/file_operate/file_bs_deal.o \
	$(ROOT)/apps/common/file_operate/file_manager.o \
	$(ROOT)/apps/common/dev_manager/dev_manager.o \
	$(ROOT)/apps/common/dev_manager/dev_reg.o \

endif

ifeq ($(USB_SLAVE_SUPPORT_MSD),y)
objs += \
$(ROOT)/apps/$(APP_CASE)/pc/pc.o \

endif


-include $(ROOT)/apps/common/device/gx8002_npu/Makefile

-include $(ROOT)/apps/common/jl_kws/Makefile

objs_ver += $(ROOT)/apps/$(APP_CASE)/sdk_version.o


#------------- TX210 config-----------------#
# includes += \
# 	-I$(ROOT)/apps/common/device/tx210/ \
#
# objs += \
# 	$(ROOT)/apps/common/device/tx210/tx210.o \


