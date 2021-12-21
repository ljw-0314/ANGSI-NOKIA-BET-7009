
	. = ALIGN(4);
	audio_sync_bss_begin = .;
        *(.audio_sync_bss)
	audio_sync_bss_end = .;
	. = ALIGN(4);
	
    *(.jlsp_bss)
    *(.sbc_bss)
    *(.sbc_hw_bss)
    *(.msbc_bss)
    *(.cvsd_bss)
    *(.aac_bss)
	*(.sbc_eng_bss)
	*(.bt_audioplc_bss)
    *(.lf_audioplc_bss)
    *(.audio_syncts_bss)
    *(.audio_timestamp_bss)
    *(.audio_dac_bss)

	/* Ó¦ÓÃ²Î¿¼ */
	*(.audio_dec_api_bss)

