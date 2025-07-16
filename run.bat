@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

if "%1"=="" (
    echo How to install: run.bat ^<static^|dynamic^> ^<filename^> ^<info^|warning^|error^>
    echo Example: run.bat static app.log info
    goto :eof
)

set BUILD_TYPE=%1
set LOG_FILE=%2
set LOG_LEVEL=%3

if not "%BUILD_TYPE%"=="static" if not "%BUILD_TYPE%"=="dynamic" (
    echo Ошибка: первый параметр должен быть static или dynamic
    goto :eof
)

if "%LOG_FILE%"=="" (
    echo Ошибка: не указано имя файла лога
    goto :eof
)

if not "%LOG_LEVEL%"=="info" if not "%LOG_LEVEL%"=="warning" if not "%LOG_LEVEL%"=="error" (
    echo Ошибка: уровень лога должен быть info, warning или error
    goto :eof
)

echo Очистка предыдущей сборки...
rd /s /q build 2>nul

if "%BUILD_TYPE%"=="static" (
    set CMAKE_SHARED_FLAG=-DBUILD_SHARED_LIBS=OFF
    echo Сборка статической версии...
) else (
    set CMAKE_SHARED_FLAG=-DBUILD_SHARED_LIBS=ON
    echo Сборка динамической версии...
)


mkdir build
cd build

echo Генерация проекта...
cmake %CMAKE_SHARED_FLAG% ..

echo Сборка проекта...
cmake --build . --config Release

echo Запуск приложения...
echo Файл лога: %LOG_FILE%
echo Уровень важности по умолчанию: %LOG_LEVEL%
echo.
bin\Release\LoggerApp.exe %LOG_FILE% %LOG_LEVEL%

cd ..
pause