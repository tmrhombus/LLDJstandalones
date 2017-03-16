# LLDJstandalones
standalone packages for long lived jet analyses

## Download
Fermilab uses tcsh by default even though it has bash! 

Starting point is in `LLDJstandalones` 
```bash
bash --login

export SCRAM_ARCH=slc6_amd64_gcc530;
scram pro -n LLDJ_slc6_530_CMSSW_8_0_18_patch1 CMSSW CMSSW_8_0_18_patch1;
cd LLDJ_slc6_530_CMSSW_8_0_18_patch1/src;
cmsenv;

scramv1 build -j 9;

git cms-init;

# first fork the repository to make your own workspace
git clone https://github.com/<mygithubusername>/LLDJstandalones.git;
cd LLDJstandalones;

# add DisplacedHiggs as upstream
git remote add upstream https://github.com/DisplacedHiggs/LLDJstandalones.git
# start working on your own branch
git checkout -b <mybranchname>

# do this every time to set some environment variables
source setup.sh
```

## How to use
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

