
		. = ALIGN(4);
        media_text_start = .;

		. = ALIGN(4);
        *(.dns_16k_data)
        *(.dns_8k_data)
		*(.jlsp_const)
		*(.jlsp_code)
        /*
		*(.aec_code)
		*(.aec_const)

		. = ALIGN(4);
		*(.res_code)
		*(.res_const)

		. = ALIGN(4);
		*(.ns_code)
		*(.ns_const)

		*(.nlp_code)
		*(.nlp_const)
		*(.der_code)
		*(.der_const)
		*(.qmf_code)
		*(.qmf_const)
		*(.fft_code)
		*(.fft_const)
        */

		*(.ns_sparse_code )
		*(.aec_sparse_code)
		*(.nlp_sparse_code)
		*(.der_sparse_code)
		*(.qmf_sparse_code)
		*(.bt_audioplc_code)
		*(.bt_audioplc_sparse_code)
		*(.bt_audioplc_const)
		*(.dms_sparse_code)
        	*(.bark_const)

		. = ALIGN(4);
        *(.pcm_code)
        *(.pcm_const)
        *(.cvsd_code)
        *(.cvsd_const)
        *(.g729_code)
        *(.g729_const)
        *(.mp3_code)
        *(.mp3_const)
        *(.mp3_dec_code)
        *(.mp3_dec_const)
        *(.mp3_dec_sparse_code)

        *(.mp3_decstream_code)
        *(.mp3_decstream_const)
        *(.mp3_decstream_sparse_code)
        /**(.bfilt_code)*/
		*(.msbc_code)
		*(.msbc_const)
		/* *(.mty_code) */
		/* *(.mty_const) */
		*(.sbc_code)
		*(.sbc_const)
		*(.sbc_hw_code)
		*(.sbc_hw_const)
		*(.sine_code)
		*(.sine_const)
        *(.wav_code)
        *(.wav_const)
		*(.wav_dec_code)
		*(.wav_dec_const)
		*(.wav_dec_sparse_code)
		*(.wav_dec_sparse_const)
        *(.wma_code)
        *(.wma_const)
		*(.wma_dec_code)
		*(.wma_dec_const)
		*(.wma_dec_sparse_code)
		*(.wma_dec_sparse_const)
        *(.wma_decstream_code)
        *(.wma_decstream_const)
        *(.wma_decstream_sparse_code)

        *(.aac_code)
        *(.aac_const)
		*(.amr_code)
		*(.amr_const)
		/* *(.ape_code) */
		/* *(.ape_const) */
		*(.audio_decoder_code)
		*(.audio_decoder_const)
		/* *(.cvsd_code) */
		/* *(.cvsd_const) */
		/* *(.dts_code) */
		/* *(.dts_const) */
		/* *(.flac_code) */
		/* *(.flac_const) */
		/* *(.m4a_code) */
		/* *(.m4a_const) */
		*(.media_device_code)
		*(.media_device_const)
		*(.audio_encoder_code)
		*(.audio_encoder_const)
		*(.mixer_code)
		*(.mixer_const)
		*(.dec_server_code)
		*(.dec_server_const)
		*(.rec_server_code)
		*(.rec_server_const)
		*(.auto_mute_code)
		*(.auto_mute_const)
		*(.plc_code)
		*(.plc_const)
		*(.wireless_sync_code)
		*(.wireless_sync_const)
		*(.sbc_eng_code)
		*(.sbc_eng_const)

		*(.audio_codec_code)

		*(.bt_compressor_sparse_const)
		*(.bt_compressor_sparse_code)
		*(.compressor_sparse_code)
		*(.compressor_sparse_const)

		*(.bt_limiter_sparse_const)
		*(.bt_limiter_sparse_code)
		*(.limiter_sparse_code)
		*(.limiter_sparse_const)

		*(.bt_crossOver_sparse_const)
		*(.bt_crossOver_sparse_code)
		*(.crossOver_sparse_code)
		*(.crossOver_sparse_const)

		. = ALIGN(4);
    	_audio_decoder_begin = .;
    	PROVIDE(audio_decoder_begin = .);
    	    *(.audio_decoder)
    	_audio_decoder_end = .;
    	PROVIDE(audio_decoder_end = .);

    	_audio_encoder_begin = .;
    	PROVIDE(audio_encoder_begin = .);
    	    *(.audio_encoder)
    	_audio_encoder_end = .;
    	PROVIDE(audio_encoder_end = .);

    	_audio_package_begin = .;
    	PROVIDE(audio_package_begin = .);
    	    *(.audio_package)
    	_audio_package_end = .;
    	PROVIDE(audio_package_end = .);

    	_audio_dev_begin = .;
    	PROVIDE(audio_dev_begin = .);
    	    *(.audio_device)
    	_audio_dev_end = .;
    	PROVIDE(audio_dev_end = .);

    	_audio_hwaccel_begin = .;
    	PROVIDE(audio_hwaccel_begin = .);
    	    *(.audio_hwaccel)
    	_audio_hwaccel_end = .;
    	PROVIDE(audio_hwaccel_end = .);

		. = ALIGN(4);
    	media_code_begin = .;
    	    *(.media.*.text)
		. = ALIGN(4);
		*(.compressor_code)
		*(.compressor_const)
		*(.bt_compressor_const)
		*(.bt_compressor_code)

		*(.crossOver_code)
		*(.crossOver_const)
		*(.bt_crossOver_const)
		*(.bt_crossOver_code)

		*(.limiter_code)
		*(.limiter_const)
		*(.bt_limiter_const)
		*(.bt_limiter_code)
	. = ALIGN(4);
		*(.sur_cal_const)
		*(.sur_cal_code)
	. = ALIGN(4);
	*(.lib_pitchshift_code)
	*(.lib_pitchshift_const)
	. = ALIGN(4);
        *(.lf_audioplc_sparse_code)
        *(.lf_audioplc_code)
        *(.lf_audioplc_const)

		*(.audio_dac_code)
		*(.audio_dac_const)
#if 0
		/* 同步运行的段有：audio_syncts_code, audio_timestamp_code, audio_sync_code, */
		*(.audio_syncts_code)
		*(.audio_syncts_const)
		*(.audio_timestamp_code)
		*(.audio_timestamp_const)
    	audio_sync_code_begin = .;
        *(.audio_sync_code)
    	audio_sync_code_end = .;

		/* 解码器结构体定义在.audio_decoder中 */
		/* sbc硬件解码器结构体定义在.audio_hwaccel中 */
		*(.audio_sbc_code_run)			// sbc解码流程运行代码
		*(.audio_sbc_const_run)			// sbc解码流程运行中的const变量
		*(.audio_sbc_hw_code_run)		// sbc硬件运行代码
		/* aac解码库在.bt_aac_dec_code 中 */
		*(.audio_aac_code_run)			// aac解码流程运行代码
		*(.audio_aac_const_run)			// aac解码流程运行中的const变量
		*(.audio_dec_code_run)			// 解码运行代码
		*(.audio_dec_code_file_read)	// 文件解码读数据代码
		*(.audio_dec_code_frame_read)	// 流媒体解码（sbc\msbc等）读数据代码
		*(.audio_mixer_code_run)		// mixer运行代码
		*(.audio_pcm_edit_code_run)		// mixer中叠加函数
		*(.audio_dac_code_run)			// dac运行代码
		*(.audio_dac_code_irq)			// dac中断代码
		*(.audio_syncts_code_run)		// dac输出变量更新

		/* 应用参考 */
		*(.audio_dec_api_code)
		*(.audio_dec_api_const)

		*(.audio_dec_api_code_run)
		*(.audio_dec_api_const_run)
		*(.audio_dec_api_code_irq)
#endif

    	media_code_end = .;
		. = ALIGN(4);
		media_code_size = media_code_end - media_code_begin;

		. = ALIGN(4);
        media_text_end = .;
