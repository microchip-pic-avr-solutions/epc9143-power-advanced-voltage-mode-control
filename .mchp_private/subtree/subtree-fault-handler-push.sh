#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git subtree push --prefix="epc9143-avmc.X/sources/fault_handler/drivers" subrepo-fault feature/version-update --squash 
echo Press Enter to exit
read

