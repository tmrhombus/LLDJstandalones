#!/bin/bash

# make sure only .root files in in the lists
outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

sed '/161018_170954_1705.root/d' ${outdir}/DY50.txt > temp && mv temp ${outdir}/DY50.txt

sed '/161018_171029_1326.root/d' ${outdir}/TTbar.txt > temp && mv temp ${outdir}/TTbar.txt
#
#root -l root:://cmseos.fnal.gov://store/group/lpchbb/kreis/AnalysisTrees/TT_TuneCUETP8M1_13TeV-powheg-pythia8/histo_TT_TuneCUETP8M1_13TeV-powheg-pythia8_.root
