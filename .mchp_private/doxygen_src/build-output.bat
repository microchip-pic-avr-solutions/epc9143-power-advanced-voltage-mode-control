@echo off
:start
echo ##############  DOXYGEN OUTPUT GENERATION  ##############
echo. 
echo Toolchain Information:
echo ======================
echo.
echo Doxygen Version:
doxygen -v
echo. 
echo Graphviz Version:
rem To generate graphics like call graphs and flow charts, the Graphviz package needs to be installed.
rem You can find this package here: https://www.graphviz.org/download/
rem Please make sure the installation directory of Graphviz is registered as PATH variable
rem Should doxygen still have trouble with calling the Dot tool, execute the following line 
rem to make sure all library packages are properly registered 
dot -V
rem "C:\Program Files\Graphviz 2.44.1\bin\dot.exe" -c
echo. 
echo Preparing Output Generation...
echo. 
cd ..\..\docs
set /P yesno="Clear the output directory before generating new content (recommended) (Y/N)? "
if "%yesno%"=="Y" goto delete_output
if "%yesno%"=="y" goto delete_output
set yesno="n"
echo skipped
goto skip_delete_output
:delete_output
del /F /Q *.*
echo done
:skip_delete_output
echo. 
set /P yesno="Clear the image directory (Y/N)? "
if "%yesno%"=="Y" goto delete_images
if "%yesno%"=="y" goto delete_images
set yesno="n"
echo skipped
goto skip_delete_images
:delete_images
del /F /Q images\*.*
echo done
:skip_delete_images
echo. 
set /P yesno="Open output after generation (Y/N)? "
if "%yesno%"=="Y" goto generate_output
if "%yesno%"=="y" goto generate_output
set yesno="n"
echo skipped
:generate_output
echo. 
echo. 
echo Calling Doxygen Generator...
cd ..\.mchp_private\doxygen_src
doxygen doxyfile
echo. 
echo Copying Image Folder:
Xcopy /e /i /c /r /y ..\..\images ..\..\docs\images
echo. 
echo ##############  D O N E  ##############
echo. 
if "%yesno%"=="Y" goto open_output
if "%yesno%"=="y" goto open_output
echo Open output skipped by user (%yesno%)
goto end
:open_output
echo Open output (%yesno%)
..\..\docs\index.html
:end
timeout 10
