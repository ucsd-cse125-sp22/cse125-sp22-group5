@REM Created by Kangming Yu on 5/23/22.

@echo off
cd /d  "%~dp0"
mkdir Build          
cmake clean Build         
set /P OPT=<cmake_option.txt    
cmake -S %~dp0 %OPT% -B Build
pause