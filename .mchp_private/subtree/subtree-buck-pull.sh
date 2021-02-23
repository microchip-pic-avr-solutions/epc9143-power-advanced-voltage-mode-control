#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Pulling changes from subtree 'subrepo-buck' branch 'main' into recently checked out working branch...
git subtree pull --prefix="epc9143-avmc.X/sources/power_control/devices" subrepo-buck main --squash 
echo Pull complete
echo
echo Press Enter to exit
read
