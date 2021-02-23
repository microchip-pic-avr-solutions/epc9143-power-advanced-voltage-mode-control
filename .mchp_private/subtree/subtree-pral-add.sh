#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git remote add subrepo-pral https://bitbucket.microchip.com/scm/mcu16asmpsl/p33c-peripheral-sfr-abstraction-drivers.git
git subtree add --prefix="epc9143-avmc.X/sources/common/p33c_pral" subrepo-pral main --squash 
echo Press Enter to exit
read
