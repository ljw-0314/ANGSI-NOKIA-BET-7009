LIBS = \
--start-group \
   $(AR_DIR)/cpu.a \
   $(AR_DIR)/system.a \
   $(AR_DIR)/btstack.a \
   $(AR_DIR)/btctrler.a \
   $(AR_DIR)/aec.a \
   $(AR_DIR)/media.a \
   $(AR_DIR)/libepmotion.a \
   $(AR_DIR)/libAptFilt_pi32v2_OnChip.a \
   $(AR_DIR)/libEchoSuppress_pi32v2_OnChip.a \
   $(AR_DIR)/libNoiseSuppress_pi32v2_OnChip.a \
   $(AR_DIR)/libSplittingFilter_pi32v2_OnChip.a \
   $(AR_DIR)/libDelayEstimate_pi32v2_OnChip.a \
   $(AR_DIR)/libOpcore_maskrom_pi32v2_OnChip.a \
   $(AR_DIR)/libDualMicSystem_pi32v2_OnChip.a \
   $(AR_DIR)/wtg_dec_lib.a \
   $(AR_DIR)/opus_enc_lib.a \
   $(AR_DIR)/sbc_eng_lib.a \
   $(AR_DIR)/libFFT_pi32v2_OnChip.a \
   $(AR_DIR)/br30_bt_aac_mask_code.a \
   $(AR_DIR)/mp3_dec_lib.a \
   $(AR_DIR)/mp3_decstream_lib.a \
   $(AR_DIR)/wma_dec_lib.a \
   $(AR_DIR)/wma_decstream_lib.a \
   $(AR_DIR)/wav_dec_lib.a \
   $(AR_DIR)/crypto_toolbox_Ospeed.a \
   $(AR_DIR)/lib_esco_repair.a \
   $(AR_DIR)/limiter_noiseGate.a \
   $(AR_DIR)/agreement.a \
   $(AR_DIR)/bt_hash_enc.a \
   $(AR_DIR)/rcsp_stack.a \
   $(AR_DIR)/tme_stack.a \
   $(AR_DIR)/math.a \
   $(AR_DIR)/JL_Phone_Call.a \
   $(AR_DIR)/mma_stack.a \
   $(AR_DIR)/speex_enc_lib.a \
   $(AR_DIR)/media_app.a \
   $(AR_DIR)/lib_sur_cal.a \
   $(AR_DIR)/lib_vbass_cal.a \
   $(AR_DIR)/lib_resample_cal.a \
   $(AR_DIR)/lib_pitchshifter.a \
   $(AR_DIR)/lfaudio_plc_lib.a \

LIBS += \
   $(AR_DIR)/update.a \

ifeq ($(CONFIG_NS_VER),DNN_NS)
LIBS += \
   $(AR_DIR)/lib_dns.a
endif

ifeq ($(FLOAT_DEBUG),y)
LIBS += \
   $(AR_DIR)/compressor_dbg.a \
   $(AR_DIR)/crossover_coff_dbg.a \
   $(AR_DIR)/limiter_dbg.a
else
LIBS += \
   $(AR_DIR)/compressor.a \
   $(AR_DIR)/crossover_coff.a \
   $(AR_DIR)/limiter.a
endif

LIBS += \
--end-group \


SRCS_C += \
	$(wildcard $(ROOT)/apps/$(APP_CASE)/board/$(CPU)/*.c)

objs += $(patsubst %.c, %.o, $(SRCS_C))

#algorithm in mask
#$(AR_DIR)/libOpcore_maskrom_pi32v2_OnChip.a \
   $(AR_DIR)/bt_aac_dec_lib_br30_seg_2.a \
   $(AR_DIR)/bfilterfun_lib.a \
