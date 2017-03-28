#!/bin/bash

# just calls the hadd scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${version}/${sample}/haddit.sh

 #"DY50"     \
samples=( \
 "DY5to50"  \
 "TTbar"    \
 "STs"      \
 "STtbar"   \
 "STt"      \
 "STtbarW"  \
 "STtW"     \
 "WJets"    \
 #"ZHtoLLbb" \
 "WW"       \
 "ZZ"       \
 "WZ"       \
 #"Signal"   \
)

for sample in ${samples[@]}
do
 #chmod +x "${basedir}/submitters/gitignore/${version}/${sample}/haddit.sh"
 bash "${basedir}/submitters/gitignore/${version}/${sample}/haddit.sh"
done
