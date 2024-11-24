@echo off
set ASOURCE_PATH="D:\Admin"
set USOURCE_PATH="D:\Viewer"

set DEST_PATH="C:\Viewer"

set APP_EXECUTABLE_ADMIN="duniceDesktopAdmin.exe"
set ASOURCE_PATH="D:\Admin"
set USOURCE_PATH="D:\Viewer"

set APP_EXECUTABLE_ADMIN="duniceDesktopAdmin.exe"
set APP_EXECUTABLE_VIEWER="duniceDesktop.exe"

echo Copy %USOURCE_PATH% to %DEST_PATH%...
xcopy %USOURCE_PATH% %DEST_PATH% /E /H /C /I /Y
if %errorlevel% neq 0 (
    echo Error in copy Viewer.
    pause
    exit /b 1
)

cd %DEST_PATH%
if %errorlevel% neq 0 (
    echo Can't find folder.
    pause
    exit /b 1
)

echo Запуск %APP_EXECUTABLE_VIEWER% из папки Viewer...
start "" "%DEST_PATH%\%APP_EXECUTABLE_VIEWER%"
if %errorlevel% neq 0 (
    echo Error to start app in folder Viewer.
    pause
    exit /b 1
)

echo Запуск %APP_EXECUTABLE_ADMIN% из папки Admin...
cd %ASOURCE_PATH%
if %errorlevel% neq 0 (
    echo Can't find folder Admin.
    pause
    exit /b 1
)

start "" "%ASOURCE_PATH%\%APP_EXECUTABLE_ADMIN%"
if %errorlevel% neq 0 (
    echo Can't start app in folder Admin.
    pause
    exit /b 1
)

echo Done!
pause