
	. = ALIGN(4);
	audio_sync_data_begin = .;
        *(.audio_sync_data)
	audio_sync_data_end = .;
	. = ALIGN(4);
	
    *(.jlsp_data)
    *(.sbc_data)
    *(.sbc_hw_data)
    *(.msbc_data)
    *(.cvsd_data)
    *(.aac_data)
	*(.sbc_eng_data)
	*(.bt_audioplc_data)
    *(.lf_audioplc_data)
    *(.audio_syncts_data)
    *(.audio_timestamp_data)
    *(.audio_dac_data)

	/* Ó¦ÓÃ²Î¿¼ */
	*(.audio_dec_api_data)

