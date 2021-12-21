@echo off

cd %~dp0

..\..\json_to_res.exe json.txt

..\..\md5sum.exe app.bin md5.bin

set /p "themd5=" < "md5.bin"

..\..\isd_download.exe isd_config_%1.ini -tonorflash -dev br30 -boot 0x2000 -div8 -wait 300 -uboot ..\..\uboot.boot -app app.bin cfg_tool.bin  -res tone.cfg config.dat ..\..\p11_code.bin md5.bin -uboot_compress


@REM ��������˵��
@rem -format vm         // ����VM ����
@rem -format all        // ��������
@rem -reboot 500        // reset chip, valid in JTAG debug


@REM ɾ����ʱ�ļ�
if exist *.mp3 del *.mp3 
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty


@REM ���ɹ̼������ļ�
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ..\..\ota.bin -type 100 -out jl_isd.fw
@REM ������ýű��İ汾��Ϣ�� FW �ļ���
..\..\fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw

if exist *.ufw del *.ufw
..\..\ufw_maker.exe -fw_to_ufw jl_isd.fw
copy jl_isd.ufw update_%themd5%.ufw
del jl_isd.ufw

@REM ���������ļ������ļ�
rem ufw_maker.exe -chip AC630N %ADD_KEY% -output config.ufw -res bt_cfg.cfg

