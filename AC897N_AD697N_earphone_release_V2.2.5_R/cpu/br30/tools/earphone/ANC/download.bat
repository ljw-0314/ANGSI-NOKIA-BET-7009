@echo off


cd %~dp0


..\..\isd_download.exe isd_config_%1.ini -tonorflash -dev br30 -boot 0x2000 -div8 -wait 300 -uboot ..\..\uboot.boot -app app.bin cfg_tool.bin  -res tone.cfg ..\..\p11_code.bin %2 -uboot_compress

:: -format all
::-reboot 2500

::-format all
::-reboot 100






@rem ���ɹ̼������ļ�
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ..\..\ota.bin -type 100 -out jl_isd.fw
@rem ������ýű��İ汾��Ϣ�� FW �ļ���
..\..\fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw


..\..\ufw_maker.exe -fw_to_ufw jl_isd.fw
copy jl_isd.ufw update.ufw
del jl_isd.ufw

@REM ���������ļ������ļ�
::ufw_maker.exe -chip AC800X %ADD_KEY% -output config.ufw -res bt_cfg.cfg

::IF EXIST jl_693x.bin del jl_693x.bin 


@rem ��������˵��
@rem -format vm        //����VM ����
@rem -format cfg       //����BT CFG ����
@rem -format 0x3f0-2   //��ʾ�ӵ� 0x3f0 �� sector ��ʼ�������� 2 �� sector(��һ������Ϊ16���ƻ�10���ƶ��ɣ��ڶ�������������10����)


