// *INDENT-OFF*
#include "app_config.h"



rem @echo off

@echo *****************************************************************
@echo 			SDK BR30
@echo *****************************************************************
@echo %date%

cd %~dp0

set OBJDUMP=C:\JL\pi32\bin\llvm-objdump.exe
set OBJCOPY=C:\JL\pi32\bin\llvm-objcopy.exe
set ELFFILE=sdk.elf

REM %OBJDUMP% -D -address-mask=0x1ffffff -print-dbg $1.elf > $1.lst
%OBJCOPY% -O binary -j .text %ELFFILE% text.bin
%OBJCOPY% -O binary -j .data %ELFFILE% data.bin
%OBJCOPY% -O binary -j .data_code %ELFFILE% data_code.bin
%OBJCOPY% -O binary -j .overlay_aec %ELFFILE% aec.bin
%OBJCOPY% -O binary -j .overlay_aac %ELFFILE% aac.bin

%OBJDUMP% -section-headers -address-mask=0x1ffffff %ELFFILE%
%OBJDUMP% -t %ELFFILE% >  symbol_tbl.txt

copy /b text.bin+data.bin+data_code.bin+aec.bin+aac.bin app.bin

#if TCFG_KWS_VOICE_RECOGNITION_ENABLE
set kws_cfg=..\..\jl_kws.cfg
#endif

#ifdef CONFIG_BR30_C_VERSION
copy br30c_p11_code.bin p11_code.bin
copy br30c_ota.bin ota.bin
cp br30c_ota_debug.bin ota_debug.bin
#else
copy br30_p11_code.bin p11_code.bin
copy br30_ota.bin ota.bin
cp br30_ota_debug.bin ota_debug.bin
#endif /* #ifdef CONFIG_BR30_C_VERSION */

#if CONFIG_EARPHONE_CASE_ENABLE
#ifdef CONFIG_APP_BT_ENABLE
#if CONFIG_DOUBLE_BANK_ENABLE
copy app.bin earphone\ai_double_bank\app.bin
copy br30loader.bin earphone\ai_double_bank\br30loader.bin
copy br30loader.uart earphone\ai_double_bank\br30loader.uart

earphone\ai_double_bank\download.bat CONFIG_CHIP_NAME %kws_cfg%
#else
copy app.bin earphone\ai_single_bank\app.bin
copy br30loader.bin earphone\ai_single_bank\br30loader.bin
copy br30loader.uart earphone\ai_single_bank\br30loader.uart

earphone\ai_single_bank\download.bat CONFIG_CHIP_NAME %kws_cfg%
#endif/*CONFIG_DOUBLE_BANK_ENABLE*/

#elif TCFG_AUDIO_ANC_ENABLE /*ANC下载目录*/
copy app.bin earphone\ANC\app.bin
copy br30loader.bin earphone\ANC\br30loader.bin
copy br30loader.uart earphone\ANC\br30loader.uart

earphone\ANC\download.bat CONFIG_CHIP_NAME %kws_cfg%
#else
copy app.bin earphone\standard\app.bin
copy br30loader.bin earphone\standard\br30loader.bin
copy br30loader.uart earphone\standard\br30loader.uart

earphone\standard\download.bat CONFIG_CHIP_NAME %kws_cfg%
#endif

#endif //CONFIG_EARPHONE_CASE_ENABLE

#if CONFIG_SPP_AND_LE_CASE_ENABLE || CONFIG_HID_CASE_ENABLE || CONFIG_MESH_CASE_ENABLE || CONFIG_GAMEBOX_CASE
#if RCSP_UPDATE_EN
copy app.bin bluetooth\app_ota\app.bin
copy br30loader.bin bluetooth\app_ota\br30loader.bin

bluetooth\app_ota\download.bat CONFIG_CHIP_NAME %kws_cfg%
#else
copy app.bin bluetooth\standard\app.bin
copy br30loader.bin bluetooth\standard\br30loader.bin

bluetooth\standard\download.bat CONFIG_CHIP_NAME %kws_cfg%
#endif

#endif      //endif CONFIG_SPP_AND_LE_CASE_ENABLE || CONFIG_HID_CASE_ENABLE || CONFIG_MESH_CASE_ENABLE || CONFIG_GAMEBOX_CASE





