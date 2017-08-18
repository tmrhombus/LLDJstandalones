#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#get the release setup and in place
#CMSSW_RELEASE_BASE="/cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw-patch/CMSSW_8_0_26_patch2"

export SCRAM_ARCH=slc6_amd64_gcc530
scramv1 project CMSSW CMSSW_8_0_26_patch2

#mkdir CMSSW
#tar -xzf $1.tar.gz -C CMSSW --strip-components 4
cd CMSSW_8_0_26_patch2
#mkdir -p src
cd src
printf "pwd\n"
pwd

cp ../../puWeights_69200_24jan2017.root         .
cp ../../ggZH_HToSSTobbbb_MS40_ctauS10000.list  .
cp ../../ggZH_HToSSTobbbb_MS40_ctauS10000.info  .
cp ../../egammaEffi_MoriondBH_eleTight.root     .
cp ../../egammaEffi_MoriondBH_eleMedium.root    .
cp ../../egammaEffi_MoriondBH_eleLoose.root     .


scramv1 build -j 20
#scramv1 build ProjectRename
#eval `scramv1 runtime -sh` # cmsenv
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

