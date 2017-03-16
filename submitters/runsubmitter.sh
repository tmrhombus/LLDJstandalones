#!/bin/bash

export PATH=${PATH}:/cvmfs/cms.cern.ch/common
export CMS_PATH=/cvmfs/cms.cern.ch

#get the release setup and in place
tar -xzf $1.tar.gz
cd $1/
mkdir -p src
cd src
scramv1 build ProjectRename
#scramv1 build
eval `scramv1 runtime -sh` # cmsenv

##set up local code
#tar -xzf ${_CONDOR_SCRATCH_DIR}/gmp.tar.gz
#cd WORLDSWORSESOLUTIONTOAPROBLEM


export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}

#echo "xrdcp root://cmseos.fnal.gov/$(echo $6 | sed 's|/eos/uscms||') ."
#xrdcp root://cmseos.fnal.gov/$(echo $6 | sed 's|/eos/uscms||') .

pwd

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

printf "Hi tom\n"
#./makePlots -st --condor -D $1 -N $3 -M $4 -L $5 -S SB_v1_2017
../../runanalyzer.exe -s $2 -l $3 -e $4 -j $5 -i "../.." -o "../.." 

printf "ls -lhrt \n"
ls -lhrt

printf "ls -lhrt ../ \n"
ls -lhrt ../

printf "ls -lhrt ../../ \n"
ls -lhrt ../../

