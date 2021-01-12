#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git remote add subrepo-buck https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-buck-converter.git
git subtree add --prefix="epc9143-avmc.X/sources/pwr_control/devices" subrepo-buck main --squash
echo Press Enter to exit
read
