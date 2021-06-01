#!/bin/bash
CMND=$1
BOX=0
SEED=$(( $2 + $BOX ))
filename=$3
WORKPLACE=${PWD}
mkdir box
date
hostname
export LD_LIBRARY_PATH=${PWD}/lib$LD_LIBRARY_PATH
cd DRsim
echo "DRsim"
./DRsim ${CMND}.mac ${SEED} ${WORKPLACE}/${filename}
cd ../Reco
echo "Reco"
./Reco ${SEED} ${WORKPLACE}/${filename}
cd ${WORKPLACE}
date
