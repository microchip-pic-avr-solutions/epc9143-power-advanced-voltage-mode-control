@echo off 
echo ##############  DOXYGEN OUTPUT GENERATION ##############
rem  
echo build doyxgen output...
cd..\..\docs
echo 
del *.*
echo 
cd..\.mchp_private\docs_src
echo 
doxygen doxyfile
echo 
echo ##############  D O N E ##############
TIMEOUT 15
