#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Pushing changes to subtree 'subrepo-buck' branch 'version-update' from recently checked out working branch...
git subtree push --prefix="epc9143-avmc.X/sources/power_control/devices" subrepo-buck feature/version-update --squash
echo Pushing changes to subtree complete
echo
echo Press Enter to exit
read

