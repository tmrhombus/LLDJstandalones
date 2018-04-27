#!/bin/bash

# just calls the hadd scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh
mkdir -p "${rootdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}/logs"

 #"ggZH_HToSSTobbbb_MS40_ctauS1"       \
 #"ggZH_HToSSTobbbb_MS40_ctauS10"      \
 #"ggZH_HToSSTobbbb_MS40_ctauS100"     \
 #"ggZH_HToSSTobbbb_MS40_ctauS1000"    \
 #"ggZH_HToSSTobbbb_MS15_ctauS1"       \
 #"ggZH_HToSSTobbbb_MS15_ctauS1000"    \
 #"ggZH_HToSSTobbbb_MS55_ctauS1"       \
 #"ggZH_HToSSTobbbb_MS55_ctauS100"     \
 #"ZH_HToSSTobbbb_MS40_ctauS10"        \
 #"ZH_HToSSTobbbb_MS40_ctauS100"       \
 #"ZH_HToSSTobbbb_MS40_ctauS1000"      \
 #"ZH_HToSSTobbbb_MS15_ctauS1"         \
 #"ZH_HToSSTobbbb_MS15_ctauS10"        \
 #"ZH_HToSSTobbbb_MS15_ctauS100"       \
 #"ZH_HToSSTobbbb_MS15_ctauS1000"      \
 #"ZH_HToSSTobbbb_MS55_ctauS10"        \
 #"ZH_HToSSTobbbb_MS55_ctauS1000"      \
 #"DY50"                               \
 #"ST_s"                               \
 #"ST_t"                               \
 #"STbar_tW"                           \
 #"ST_tW"                              \
 #"TTtoLL"                             \
 #"TTtoLfromTbar"                      \
 #"TTtoLfromT"                         \
 #"WG"                                 \
 #"WJetsToLNu"                         \
 #"WWToLNuLNu"                         \
 #"WWToLNuQQ"                          \
 #"WZToL3Nu"                           \
 #"WZTo3LNu"                           \
 #"WZToLNu2QorQQ2L"                    \
 #"ZG"                                 \
 #"ZZToLLNuNu"                         \
 #"ZZToLLQQ"                           \
 #"ZZToNuNuQQ"                         \
 #"ZZToLLLL"                           \
 #"GJets_HT40To100"                    \
 #"GJets_HT100To200"                   \
 #"GJets_HT200To400"                   \
 #"GJets_HT400To600"                   \
 #"DY5to50_HT100To200"                 \
 #"DY5to50_HT200To400"                 \
 #"DY5to50_HT400To600"                 \
 #"DY5to50_HT600ToInf"                 \
samples=( \
 "SingleMuon"                         \
 "SinglePhoton"                       \
)
# "DY5to50_HT70To100"                \
# "DY5to50_HT100To200"               \
# "DY5to50_HT200To400"               \
# "DY5to50_HT400To600"               \
# "DY5to50_HT600ToInf"               \
# "ggZH_HToBB_ZToLL"                 \
# "ggZH_HToSSTobbbb_MS40_ctauS0"     \
# "ggZH_HToSSTobbbb_MS40_ctauS0p05"  \
# "ggZH_HToSSTobbbb_MS40_ctauS1"     \
# "ggZH_HToSSTobbbb_MS40_ctauS10"    \
# "ggZH_HToSSTobbbb_MS40_ctauS100"   \
# "ggZH_HToSSTobbbb_MS40_ctauS1000"  \
# "ggZH_HToSSTobbbb_MS40_ctauS10000" \
# "GJets_HT40To100"                  \
# "GJets_HT100To200"                 \
# "GJets_HT200To400"                 \
# "GJets_HT400To600"                 \
# "GJets_HT600ToInf"                 \

#for sample in ${samples[@]}
for sample in $(ls ${basedir}/submitters/gitignore/${aversion}/)
do
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPT.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPT.sh"
 #bash "/nfs_scratch/tperry/gitignore/${aversion}/${sample}/haddit.sh"
done
