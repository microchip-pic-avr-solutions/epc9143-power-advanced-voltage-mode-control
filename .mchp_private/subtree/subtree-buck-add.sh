#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Adding subtree repository 'subrepo-buck' ro project repository...
git remote add subrepo-buck https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-buck-converter.git
echo Adding subtree repository complete
echo 
echo Downloading subtree contents into project repository...
git subtree add --prefix="epc9143-avmc.X/sources/power_control/devices" subrepo-buck main --squash
echo Download source files complete
echo
echo Press Enter to exit
read
