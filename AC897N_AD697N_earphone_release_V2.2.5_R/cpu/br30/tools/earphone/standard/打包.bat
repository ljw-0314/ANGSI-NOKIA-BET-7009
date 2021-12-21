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
echo %a%. 检测作者信息
if not exist "%ToolPath%\user.txt" (
xcopy .\UserTool\*.* /s/h/Y %ToolPath%
rmdir /s/q .\UserTool
::rmdir UserTool
::move \UserTool\*.* %ToolPath%
echo 请输入您的名称
echo 可在%ToolPath%\user.txt文件中修改Writer值
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
echo %a%. 检测工具目录
set "WinRARPath=%ToolPath%\WinRAR.exe"
if not exist "%WinRARPath%" (
echo WinRAR.exe地址%WinRARPath%错误
pause
exit
)

::日志文件名称
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
echo %a%. 检测关键配置信息
if not exist "%Copyname%" (
echo Copyname %Copyname% 文件目录不正确
pause
exit
)  
if not exist "%CopyBFU%" (
echo CopyBFU %CopyBFU%文件目录不正确
pause
exit
)

set /a a+=1
echo %a%. 获取时间
set "timedata=%date% %time:~0,8%"
::set "outtime=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%"
set "outtime=%date:~0,4%%date:~5,2%%date:~8,2%"

set /a a+=1
echo %a%. 读取软件校验码
::YIchecksum_2.0.0.3.exe
%ToolPath%\%TOOLNAME% "%Copyname%" > %tmptxt%
For /f "tokens=1* delims=:" %%i in ('Type %tmptxt%^|Findstr /n ".*"') do (
If "%%i"=="2" Set checksumStr=%%j
)
set "CheckCode=%checksumStr:~6,13%"
for %%i in (A B C D E F G H I J K L M N O P Q R S T U V W X Y Z) do call set CheckCode=%%CheckCode:%%i=%%i%%
echo CheckCode：%CheckCode%
::删除临时文件
if exist "YIname.txt" (del YIname.txt)

if "%CheckCode%" equ "%CheckCodeOld%" (
	echo 程序校验码未改变
	if exist "%Backuppath%\%CheckCode%\SDK" (
		echo 此校验码程序已经备份
		echo %cd%\%Backuppath%\%CheckCode%\SDK
		CHOICE /C YN /M "是否继续 请按 Y，否请按 N"
		if ERRORLEVEL 2 goto _EXIT
	)
)

set "NAME=%Customer%[%Project%]-主控%IC%(设备名%Bluetooth% 校验码%CheckCode%){负责人%Writer%}_%date:~2,2%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%左耳"
::goto test_copy

set /a a+=1
echo %a%. 编辑log
::输出log日志到readme.txt
(
	echo 版本校验码：%CheckCode%^(%Project%^)旧版本校验码：%CheckCodeOld%
	echo 时间：%date% %time:~0,8%
	echo 项目名：%Project%
	echo 蓝牙名：%Bluetooth%
	echo SVN目录：%SVN_SERVER_DIR%
	echo SDK版本：%SDK_VERSION%	
	echo 主控：%IC%
	echo 作者：%Writer%
	echo 更新内容：
	echo 1.
	echo.
)>%readme_temp%
type %readm% >>%readme_temp%
del %readm%
ren %readme_temp% %readm%

start /wait notepad %readm%

set /a a+=1
echo %a%. 创建校验码文件夹
if exist "%Backuppath%\%CheckCode%" (
	echo 文件夹%CheckCode%已存在
	CHOICE /C YN /M "确认请按 Y，否请按 N"
	if ERRORLEVEL 2 goto 取消
	if ERRORLEVEL 1 goto 删除
	
) else (
	::echo 创建%CheckCode%....	
	md "%Backuppath%\%CheckCode%"
	goto 创建
)

:取消
goto _EXIT
:删除
::echo 删除中.....
rd /q /s %Backuppath%\%CheckCode% 
:创建

set /a a+=1
echo %a%. 复制文件
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

set "NAME=%Customer%[%Project%]_%IC%_校验码%CheckCode%_蓝牙名%Bluetooth%{%Writer%}%date:~2,2%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%_%左耳%"
copy "%Copyname%" "%BINFILE%\%NAME%.fw" 1>nul
copy  "%CopyBFU%" "%BINFILE%" 1>nul
xcopy /h /y /s /e /q "%Copydir%" "%FLASH%"  1>nul
copy "%readm%" "%Backuppath%\%CheckCode%"  1>nul
::copy "%readm%" "%Backuppath%\..\"  1>nul

REM 获取生成的FW文件大小
for /f "tokens=* delims=" %%a in ('dir /s /b "%Copyname%"') do (
set /a k=%%~za/1024
)
::echo YIname: 生成的软件大小: %k%KB

set /a a+=1
echo %a%. 打包BINFILE、flash目录
::需要压缩的内容
(
	echo %Backuppath%\%CheckCode%\*
)>R.lst
::不需要压缩的内容
( 	echo Doc 
	echo doc 
)>X.lst

::打包文件 
::"%WinRAR_PATH%WinRAR" a -ep1 -o+ -inul -r -m5 -ibck  -x@X.lst "%NAME%" @R.lst

if %Backup_download% EQU 1 "%ToolPath%\WinRAR" a -ep1 -o+ -inul -r -m5 -ibck  -x@X.lst "%NAME%" @R.lst
"%ToolPath%\WinRAR" a -ep1 -o+ -inul -r -m5 -ibck  -x@X.lst "%NAME%_update" %CopyBFU%
::删除文件
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
echo %a%. 复制当前发布文件到SVN目录

CHOICE /C YN /M "是否要复制文件到SVN目录 Y，否请按 N"
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
echo %a%. 备份SDK
(
echo CheckCodeOld=%CheckCode%
)>%Copydir%\user.cfg

::xcopy /h /y /s /e /q "%Backupsource%" %Backuppath%\%CheckCode%\SDK\ 1>nul

:no_backup_sdk

::打开发给客户文件所在的文件夹
::start /max "" "%BACKUPPATH%\%JLYZM%"
::start "" "%Backuppath%\%CheckCode%" 

set /a a+=1
echo %a%. 完成


:_EXIT
pause