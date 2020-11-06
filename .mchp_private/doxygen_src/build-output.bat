@echo off
echo ##############  DOXYGEN OUTPUT GENERATION  ##############
echo 1) Clearing Output Directory:
cd ..\..\docs
echo Would you like to clear the output directory before generating new content?
del *.*
echo Would you like to clear the image directory?
del images\*.*
done
echo 2) Graphviz Package Version:
rem To generate graphics like call graphs and flow charts, the Graphviz package needs to be installed.
rem You can find this package here: https://www.graphviz.org/download/
rem Please make sure the installation directory of Graphviz is registered as PATH variable
rem Should doxygen still have trouble with calling the Dot tool, execute the following line 
rem to make sure all library packages are properly registered 
dot -V
rem "C:\Program Files\Graphviz 2.44.1\bin\dot.exe" -c
done
echo 3) Calling Doxygen Generator:
cd ..\.mchp_private\doxygen_src
doxygen doxyfile
echo 4) Copying Image Folder:
Xcopy /e /i /c /r /y ..\..\images ..\..\docs\images
echo ##############  D O N E  ##############
timeout 10
