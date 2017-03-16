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

git cms-init;
git clone https://github.com/DisplacedHiggs/LLDJstandalones.git;

scramv1 build -j 9;

cd LLDJstandalones;
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
2a. `./runanalyzer.exe --<flags>` call executable analyzer by hand (you must specify flags)
2b. `bash runAnalyzers.sh` loops through different options for calling `runanalyzer.exe`

### submit condor job
From `submitters` folder
1. in `submitjobs.sh` set `doSubmit=false` to be safe while testing
2. `bash submitjobs.sh` creates tarball CMSSW area and submit area in `gitignore`
The job that actually runs on the condor nodes is `runsubmitter.sh`
3. `voms-proxy-init --voms cms --valid 100:00` set up your proxy
4. set `doSubmit=true` and run 

