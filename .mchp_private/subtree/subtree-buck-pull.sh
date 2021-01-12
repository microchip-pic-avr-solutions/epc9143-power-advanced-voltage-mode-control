#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git subtree pull --prefix="epc9143-avmc.X/sources/pwr_control/devices" subtree-buck main --squash 
echo Press Enter to exit
read
