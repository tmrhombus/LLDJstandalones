#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#get the release setup and in place
#CMSSW_RELEASE_BASE="/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw-patch/CMSSW_8_0_26_patch1"
mkdir CMSSW
tar -xzf $1.tar.gz -C CMSSW --strip-components 4
cd CMSSW
mkdir -p src
cd src
scramv1 build ProjectRename
eval `scramv1 runtime -sh` # cmsenv

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

../../runanalyzer.exe -s $2 -l $3 -e $4  -i "../.." -o "../.." -n $5 -a $6 -x $7 $8

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../
