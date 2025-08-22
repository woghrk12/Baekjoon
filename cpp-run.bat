@echo off

set filename=%1

set outfile=temp.exe

g++ -std=c++17 -O2 -Wall %filename% -o %outfile%
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

%outfile%

del %outfile%