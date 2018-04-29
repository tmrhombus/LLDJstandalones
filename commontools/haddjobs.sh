#!/bin/bash

# just calls the hadd scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh
mkdir -p "${rootdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}/logs"

samples=( \
 "TTtoLL"                           \
)

#for sample in $(ls ${basedir}/submitters/gitignore/${aversion}/) # works but dangerous?
for sample in ${samples[@]}
do

 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_DY_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoPair_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoSel_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPTtree.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OffZ_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_Sig_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_ZH_histograms.sh"

 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_DY_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoPair_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoSel_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPTtree.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OffZ_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_Sig_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_ZH_histograms.sh"

done
