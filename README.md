# LLDJstandalones
standalone packages for long lived jet analyses

## Download
Fermilab uses tcsh, so do I now

Download to `CMSSW_8_0_18_patch1/src`
```tcsh
setenv SCRAM_ARCH slc6_amd64_gcc530;
cmsrel CMSSW_8_0_18_patch1;
cd CMSSW_8_0_18_patch1/src/;
cmsenv;
```

## How to use
From `commontools` run `bash makelists.sh` to make lists of files from eos in `lists` directory
Then run `bash countevents.sh` which calls `countevents.cxx` and adds event counts/cross sections to the file lists
Then from `analyzers` folder, edit `main.C` to point to the list in question
Run `make` in `analyzers` folder to execute makefile 
This creates executable `runanalyzer.exe` which can be run as `./runanalyzer.exe`

The file `main.C` reads in text files of ntuple locations and makes them into a TChain that gets passed into the `Init(chain)` function of the analyzer (presently `analyzer_signal` which inherits from `analyzer_base`). The analyzer then loops through the events in the chain and applies defined cuts and prints histograms.
