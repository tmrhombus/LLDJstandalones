#!/bin/bash

# just calls the checker scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh

printf "Files that are not done in condor: \n"

samples=( \
 "DY50"                               \
 "DY5to50_HT100to200"                 \
 "DY5to50_HT200to400"                 \
 "DY5to50_HT400to600"                 \
 "DY5to50_HT600toInf"                 \
 "DY5to50_HT70to100"                  \
 "GJets_HT40To100"                    \
 "GJets_HT100To200"                   \
 "GJets_HT200To400"                   \
 "GJets_HT400To600"                   \
 "GJets_HT600ToInf"                   \
 "ST_s"                               \
 "STbar_t"                            \
 "ST_t"                               \
 "STbar_tW"                           \
 "ST_tW"                              \
 "TTJets"                             \
 "WW"                                 \
 "WZ"                                 \
 "ZZ"                                 \
 "ZH_HToBB_ZToLL"                     \
 "ggZH_HToBB_ZToLL"                   \
 "ggZH_HToSSTobbbb_MS40_ctauS100"     \
 "ggZH_HToSSTodddd_MS40_ctauS100"     \
 "WJetsToLNu"                         \
 "SingleElectron"                     \
 "SingleMuon"                         \

)

for sample in ${samples[@]}
do
 #chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh"
 var=$(bash "${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh" | wc -l )
 lc=$( cat "${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh" | wc -l )
 echo "${lc}  ${var}"
 
done
