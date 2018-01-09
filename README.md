# LLDJstandalones
ntuple based analysis package for long lived displaced jet analyses

## Download

```bash
# Fermilab uses tcsh by default even though it has bash! 
# This framework is based in bash and
# technically maybe you don't need this,
# but tcshers be warned
bash --login

# Set up the area
export SCRAM_ARCH=slc6_amd64_gcc530;
scram pro -n LLDJ_slc6_530_CMSSW_8_0_26_patch1 CMSSW CMSSW_8_0_26_patch1;
cd LLDJ_slc6_530_CMSSW_8_0_26_patch1/src;
cmsenv;

# you may need to set up your git name first
# git config --global user.github <mygithubusername>
export CMSSW_GIT_REFERENCE=/cvmfs/cms.cern.ch/cmssw.git.daily
git cms-init;


## CMSSW imports and customizations

# EGamma Smearing
git cms-merge-topic cms-egamma:EGM_gain_v1
pushd EgammaAnalysis/ElectronTools/data
 git clone -b Moriond17_gainSwitch_unc https://github.com/ECALELFS/ScalesSmearings.git
popd

# EGamma ID
git cms-addpkg RecoEgamma
git cms-merge-topic ikrav:egm_id_80X_v2
git cms-merge-topic ikrav:egm_id_80X_v3_photons

# MET
git cms-merge-topic cms-met:METRecipe_8020 -u
git cms-merge-topic cms-met:METRecipe_80X_part2 -u

# Higgs Combine Tool
# https://www.gitbook.com/book/cms-hcomb/combine/details
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
pushd HiggsAnalysis/CombinedLimit
 git fetch origin
 git checkout v7.0.1
popd

scramv1 build -j 10;

## LLDJstandalones Framework checkout

# first fork the repository to make your own workspace
git clone https://github.com/<mygithubusername>/LLDJstandalones.git;
pushd LLDJstandalones;

 # If you want to check out a specific branch
 # git fetch origin
 # git branch -v -a # list branches available, find yours
 # git checkout -b NAMEOFBRANCH origin/NAMEOFBRANCH 

 # add DisplacedHiggs as upstream
 git remote add upstream https://github.com/DisplacedHiggs/LLDJstandalones.git

 # this is a hack to disable autodetection of (mini)AOD for VID producers
 pushd initialization
  bash getridofPhotonMVA.sh
 popd
popd

# compile a clean area
scramv1 build -j 10;


## Every time you log in
# set up some environment variables (bash)
source LLDJstandalones/setup.sh
```

## How to use

## Analyzer
### set up
Make sure to run `source setup.sh` from the `LLDJstandalones` directory first to set up environment variables used in scripts.

### list files
From `commontools` folder
1. `bash makelists.sh` makes lists of files and puts them in `lists` folder
2. `bash rmbadfiles.sh` removes a few specific corrupted files from lists
3. `bash cleanlists.sh` goes through lists and makes sure only .root files are present
4. `bash countevents.sh` calls `countevents.cxx` and makes .info files in `lists` folder

### run analyzer
From `analyzers` folder
1. `make` compiles `main.C` into executable `runanalyzer.exe` 
2. `./runanalyzer.exe --<flags>` call executable analyzer by hand (you must specify flags)
3. or edit and run `bash runAnalyzers.sh` which loops through different options for calling `runanalyzer.exe`

### submit condor job
From `submitters` folder
1. in `submitjobs.sh` set `doSubmit=false` to be safe while testing
2. `bash submitjobs.sh` creates tarball CMSSW area and submit area in `gitignore`
The job that actually runs on the condor nodes is `runsubmitter.sh`
3. `voms-proxy-init --voms cms --valid 100:00` set up your proxy
4. set `doSubmit=true` and run 

### make plots
Some scripts are available in `plotters` folder, ex. dump all plots in a file using `root -l -b -q dumpplots.C`


## Ntuplizer
To do..

