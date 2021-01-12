#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git subtree push --prefix="epc9143-avmc.X/sources/common/p33c_pral" subtree-pral feature/version-update --squash 
echo Press Enter to exit
read

