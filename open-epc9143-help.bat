@echo off
:start
set /P yesno="Would you like to open the output (Y/N)? "
if "%yesno%"=="Y" goto open
if "%yesno%"=="y" goto open
echo Skip open file...
goto end
:open
echo Open file...
docs\index.html
:end
timeout 5
