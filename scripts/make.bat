@echo off
set generator=%1

mkdir build

cd build

if "%generator%"=="" (
    cmake -G "MinGW Makefiles" ..
) else if "%generator%"=="mingw" (
    cmake -G "MinGW Makefiles" ..
) else if "%generator%"=="msvc" (
    cmake ..
) else (
    echo Invalid argument. Use 'mingw' or 'msvc'.
    exit /b 1
)

make

copy ".\SyntaxTreeGen.exe" ".."

cd ..

.\SyntaxTreeGen.exe
