@echo off
setlocal enabledelayedexpansion
for /f "tokens=1,2 delims==" %%i in (download.ini) do (
   set %%i=%%j
)

set CheckCodeOld=
for /f "tokens=1,2 delims==" %%i in (%Backupsource%\%Copydir%\user.cfg) do (
   set %%i=%%j
)
::echo CheckCodeOld=%CheckCodeOld%

set /a a=0

set /a a+=1
echo %a%. ���������Ϣ
if not exist "%ToolPath%\user.txt" (
xcopy .\UserTool\*.* /s/h/Y %ToolPath%
rmdir /s/q .\UserTool
::rmdir UserTool
::move \UserTool\*.* %ToolPath%
echo ��������������
echo ����%ToolPath%\user.txt�ļ����޸�Writerֵ
goto Write_Label
) else (
goto Load_Label
)

:Write_Label
set /p Writer=
echo Writer=%Writer%>%ToolPath%\user.txt

:Load_Label
for /f "tokens=1,2 delims==" %%i in (%ToolPath%\user.txt) do (
   set %%i=%%j
)

echo Writer:%Writer%

set /a a+=1
echo %a%. ��⹤��Ŀ¼
set "WinRARPath=%ToolPath%\WinRAR.exe"
if not exist "%WinRARPath%" (
echo WinRAR.exe��ַ%WinRARPath%����
pause
exit
)

::��־�ļ�����
set "readme_temp=readme_temp.txt"
set "readm=readme.txt"

set Copydir=%Copydir%

set Copyname=%Copydir%\%Copyname%
set CopyBFU=%Copydir%\%CopyBFU%
set tmptxt=YIname.txt
set BINFILE=BINFILE
set FLASH=flash
set eve_path=%cd%

cd "%Copydir%\..\..\..\..\"
set svn_sdk_source=%cd%
cd %eve_path%

set /a a+=1
echo %a%. ���ؼ�������Ϣ
if not exist "%Copyname%" (
echo Copyname %Copyname% �ļ�Ŀ¼����ȷ
pause
exit
)  
if not exist "%CopyBFU%" (
echo CopyBFU %CopyBFU%�ļ�Ŀ¼����ȷ
pause
exit
)

set /a a+=1
echo %a%. ��ȡʱ��
set "timedata=%date% %time:~0,8%"
::set "outtime=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%"
set "outtime=%date:~0,4%%date:~5,2%%date:~8,2%"

set /a a+=1
echo %a%. ��ȡ���У����
::YIchecksum_2.0.0.3.exe
%ToolPath%\%TOOLNAME% "%Copyname%" > %tmptxt%
For /f "tokens=1* delims=:" %%i in ('Type %tmptxt%^|Findstr /n ".*"') do (
If "%%i"=="2" Set checksumStr=%%j
)
set "CheckCode=%checksumStr:~6,13%"
for %%i in (A B C D E F G H I J K L M N O P Q R S T U V W X Y Z) do call set CheckCode=%%CheckCode:%%i=%%i%%
echo CheckCode��%CheckCode%
::ɾ����ʱ�ļ�
if exist "YIname.txt" (del YIname.txt)

if "%CheckCode%" equ "%CheckCodeOld%" (
	echo ����У����δ�ı�
	if exist "%Backuppath%\%CheckCode%\SDK" (
		echo ��У��������Ѿ�����
		echo %cd%\%Backuppath%\%CheckCode%\SDK
		CHOICE /C YN /M "�Ƿ���� �밴 Y�����밴 N"
		if ERRORLEVEL 2 goto _EXIT
	)
)

set "NAME=%Customer%[%Project%]-����%IC%(�豸��%Bluetooth% У����%CheckCode%){������%Writer%}_%date:~2,2%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%���"
::goto test_copy

set /a a+=1
echo %a%. �༭log
::���log��־��readme.txt
(
	echo �汾У���룺%CheckCode%^(%Project%^)�ɰ汾У���룺%CheckCodeOld%
	echo ʱ�䣺%date% %time:~0,8%
	echo ��Ŀ����%Project%
	echo ��������%Bluetooth%
	echo SVNĿ¼��%SVN_SERVER_DIR%
	echo SDK�汾��%SDK_VERSION%	
	echo ���أ�%IC%
	echo ���ߣ�%Writer%
	echo �������ݣ�
	echo 1.
	echo.
)>%readme_temp%
type %readm% >>%readme_temp%
del %readm%
ren %readme_temp% %readm%

start /wait notepad %readm%

set /a a+=1
echo %a%. ����У�����ļ���
if exist "%Backuppath%\%CheckCode%" (
	echo �ļ���%CheckCode%�Ѵ���
	CHOICE /C YN /M "ȷ���밴 Y�����밴 N"
	if ERRORLEVEL 2 goto ȡ��
	if ERRORLEVEL 1 goto ɾ��
	
) else (
	::echo ����%CheckCode%....	
	md "%Backuppath%\%CheckCode%"
	goto ����
)

:ȡ��
goto _EXIT
:ɾ��
::echo ɾ����.....
rd /q /s %Backuppath%\%CheckCode% 
:����

set /a a+=1
echo %a%. �����ļ�
set BINFILE=%Backuppath%\%CheckCode%\%BINFILE%
set FLASH=%Backuppath%\%CheckCode%\%FLASH%
set DOWNDIR=%Backuppath%\%CheckCode%

if exist "%BINFILE%" (
del /q /s %BINFILE%\* 1>nul
) else (
md "%BINFILE%"
)
if exist "%FLASH%" (
del /q /s "%FLASH%" 1>nul
) else (
md "%FLASH%"
)

set "NAME=%Customer%[%Project%]_%IC%_У����%CheckCode%_������%Bluetooth%{%Writer%}%date:~2,2%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%_%���%"
copy "%Copyname%" "%BINFILE%\%NAME%.fw" 1>nul
copy  "%CopyBFU%" "%BINFILE%" 1>nul
xcopy /h /y /s /e /q "%Copydir%" "%FLASH%"  1>nul
copy "%readm%" "%Backuppath%\%CheckCode%"  1>nul
::copy "%readm%" "%Backuppath%\..\"  1>nul

REM ��ȡ���ɵ�FW�ļ���С
for /f "tokens=* delims=" %%a in ('dir /s /b "%Copyname%"') do (
set /a k=%%~za/1024
)
::echo YIname: ���ɵ������С: %k%KB

set /a a+=1
echo %a%. ���BINFILE��flashĿ¼
::��Ҫѹ��������
(
	echo %Backuppath%\%CheckCode%\*
)>R.lst
::����Ҫѹ��������
( 	echo Doc 
	echo doc 
)>X.lst

::����ļ� 
::"%WinRAR_PATH%WinRAR" a -ep1 -o+ -inul -r -m5 -ibck  -x@X.lst "%NAME%" @R.lst

if %Backup_download% EQU 1 "%ToolPath%\WinRAR" a -ep1 -o+ -inul -r -m5 -ibck  -x@X.lst "%NAME%" @R.lst
"%ToolPath%\WinRAR" a -ep1 -o+ -inul -r -m5 -ibck  -x@X.lst "%NAME%_update" %CopyBFU%
::ɾ���ļ�
del R.lst 
del X.lst 

start "" "%Backuppath%\%CheckCode%" 

::del /s /q /f "%Backuppath%\%CheckCode%\*" 1>nul
rd /s /q %FLASH% 1>nul
rd /q /s %BINFILE% 1>nul
copy "%NAME%*" "%Backuppath%\%CheckCode%\" 1>nul
::del "%Backuppath%\%CheckCode%\%readm%" 1>nul
del "%NAME%*" 1>nul
::del "%Backuppath%\tmp" 1>nul
::pause

:test_copy
if "%SVN_UPDATA_PATH%"=="" (
	goto backup_sdk
)
set /a a+=1
echo %a%. ���Ƶ�ǰ�����ļ���SVNĿ¼

CHOICE /C YN /M "�Ƿ�Ҫ�����ļ���SVNĿ¼ Y�����밴 N"
if ERRORLEVEL 2 goto exit_copy
if ERRORLEVEL 1 goto copy_to_svn_path
:copy_to_svn_path
if exist "%SVN_UPDATA_PATH%" (
	rd /q /s "%SVN_UPDATA_PATH%"	
	mkdir %SVN_UPDATA_PATH%
)

xcopy /h /y /s /e /q "%svn_sdk_source%" "%SVN_UPDATA_PATH%\" 1>nul
xcopy /h /y /s /e /q  "%Backuppath%\%CheckCode%" "%SVN_UPDATA_PATH%\"  1>nul
:exit_copy

:backup_sdk
if "%Backupsource%"=="" (
	goto no_backup_sdk
)
set /a a+=1
echo %a%. ����SDK
(
echo CheckCodeOld=%CheckCode%
)>%Copydir%\user.cfg

::xcopy /h /y /s /e /q "%Backupsource%" %Backuppath%\%CheckCode%\SDK\ 1>nul

:no_backup_sdk

::�򿪷����ͻ��ļ����ڵ��ļ���
::start /max "" "%BACKUPPATH%\%JLYZM%"
::start "" "%Backuppath%\%CheckCode%" 

set /a a+=1
echo %a%. ���


:_EXIT
pause