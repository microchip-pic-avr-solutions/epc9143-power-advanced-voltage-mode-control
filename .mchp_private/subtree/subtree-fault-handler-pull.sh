#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git subtree pull --prefix="epc9143-avmc.X/sources/fault_handler/drivers" subtree-fault main --squash
echo Press Enter to exit
read

