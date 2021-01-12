#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git subtree pull --prefix="epc9143-avmc.X/sources/common/p33c_pral" subtree-pral main --squash 
echo Press Enter to exit
read
