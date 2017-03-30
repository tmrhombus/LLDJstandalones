#!/bin/bash

# just calls the hadd scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${version}/${sample}/haddit.sh
mkdir -p "${rootdir}/${version}"

 #"DY50"     \
samples=( \
 "DY50"     \
 "DY5to50"  \
 "TTbar"    \
 "STs"      \
 "STtbar"   \
 "STt"      \
 "STtbarW"  \
 "STtW"     \
 "WJets"    \
 "WW"       \
 "ZZ"       \
 "WZ"       \
 "Signal_WminusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8" \
 "Signal_WplusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"  \
 "Signal_ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"       \
 "Signal_ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"     \
 "ZHtoLLbb_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8"                                         \
 "ZHtoLLbb_ggZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8"                                       \
)

for sample in ${samples[@]}
do
 #chmod +x "${basedir}/submitters/gitignore/${version}/${sample}/haddit.sh"
 bash "${basedir}/submitters/gitignore/${version}/${sample}/haddit.sh"
done
