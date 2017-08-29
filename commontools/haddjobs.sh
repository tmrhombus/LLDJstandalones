#!/bin/bash

# just calls the hadd scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh
mkdir -p "${rootdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}"

samples=( \
 "DY5to50_HT70To100"                \
 "DY5to50_HT100To200"               \
 "DY5to50_HT200To400"               \
 "DY5to50_HT400To600"               \
 "DY5to50_HT600ToInf"               \
 "DY50"                             \
 "ggZH_HToBB_ZToLL"                 \
 "ggZH_HToSSTobbbb_MS40_ctauS0"     \
 "ggZH_HToSSTobbbb_MS40_ctauS0p05"  \
 "ggZH_HToSSTobbbb_MS40_ctauS1"     \
 "ggZH_HToSSTobbbb_MS40_ctauS10"    \
 "ggZH_HToSSTobbbb_MS40_ctauS100"   \
 "ggZH_HToSSTobbbb_MS40_ctauS1000"  \
 "ggZH_HToSSTobbbb_MS40_ctauS10000" \
 "GJets_HT40To100"                  \
 "GJets_HT100To200"                 \
 "GJets_HT200To400"                 \
 "GJets_HT400To600"                 \
 "GJets_HT600ToInf"                 \
 "ST_s"                             \
 "STbar_t"                          \
 "ST_t"                             \
 "STbar_tW"                         \
 "ST_tW"                            \
 "TTtoLL"                           \
 "TTtoLfromTbar"                    \
 "TTtoLfromT"                       \
 "WG"                               \
 "WJetsToLNu"                       \
 "WWToLNuLNu"                       \
 "WWToLNuQQ"                        \
 "WZToL3Nu"                         \
 "WZTo3LNu"                         \
 "WZToLNu2QorQQ2L"                  \
 "ZG"                               \
 "ZH_HToBB_ZToLL"                   \
 "ZZToLLNuNu"                       \
 "ZZToLLQQ"                         \
 "ZZToNuNuQQ"                       \
 "ZZToLLLL"                         \
 "SingleElectron"                   \
 "SingleMuon"                       \
)

for sample in ${samples[@]}
do
 #chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh"
 #bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh"
 bash "/nfs_scratch/tperry/gitignore/${aversion}/${sample}/haddit.sh"
done
