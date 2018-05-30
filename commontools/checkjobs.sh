#!/bin/bash

# just calls the checker scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh

printf "Files that are not done in condor: \n"
 printf "%40s %4s %4s \n" "" Tot  Left

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
 #"SingleElectron_B_2"   \
 #"SingleElectron_C"     \
 #"SingleElectron_D"     \
 #"SingleElectron_E"     \
 #"SingleElectron_G"     \
 #"SingleElectron_H_3"   \
 #"SingleMuon_B_2"       \
 #"SingleMuon_C"         \
 #"SingleMuon_D"         \
 #"SingleMuon_E"         \
 #"SingleMuon_F"         \
 #"SingleMuon_G"         \
 #"SingleMuon_H"         \
 #"SinglePhoton_B_2"     \
 #"SinglePhoton_C"       \
 #"SinglePhoton_D"       \
 #"SinglePhoton_E"       \
 #"SinglePhoton_F"       \
 #"SinglePhoton_G"       \
 #"SinglePhoton_H"       \
samples=( \
 "ggZH_HToSSTobbbb_MS40_ctauS1"       \
 "ggZH_HToSSTobbbb_MS40_ctauS10"      \
 "ggZH_HToSSTobbbb_MS40_ctauS100"     \
 "ggZH_HToSSTobbbb_MS40_ctauS1000"    \
 "ggZH_HToSSTobbbb_MS15_ctauS1"       \
 "ggZH_HToSSTobbbb_MS15_ctauS1000"    \
 "ggZH_HToSSTobbbb_MS55_ctauS1"       \
 "ggZH_HToSSTobbbb_MS55_ctauS100"     \
 "ZH_HToSSTobbbb_MS40_ctauS10"        \
 "ZH_HToSSTobbbb_MS40_ctauS100"       \
 "ZH_HToSSTobbbb_MS40_ctauS1000"      \
 "ZH_HToSSTobbbb_MS15_ctauS1"         \
 "ZH_HToSSTobbbb_MS15_ctauS10"        \
 "ZH_HToSSTobbbb_MS15_ctauS100"       \
 "ZH_HToSSTobbbb_MS15_ctauS1000"      \
 "ZH_HToSSTobbbb_MS55_ctauS10"        \
 "ZH_HToSSTobbbb_MS55_ctauS1000"      \
 "DY50"                               \
 "ST_s"                               \
 "ST_t"                               \
 "STbar_tW"                           \
 "ST_tW"                              \
 "TTtoLL"                             \
 "TTtoLfromTbar"                      \
 "TTtoLfromT"                         \
 "WG"                                 \
 "WJetsToLNu"                         \
 "WWToLNuLNu"                         \
 "WWToLNuQQ"                          \
 "WZToL3Nu"                           \
 "WZTo3LNu"                           \
 "WZToLNu2QorQQ2L"                    \
 "ZG"                                 \
 "ZZToLLNuNu"                         \
 "ZZToLLQQ"                           \
 "ZZToNuNuQQ"                         \
 "ZZToLLLL"                           \
 "GJets_HT40To100"                    \
 "GJets_HT100To200"                   \
 "GJets_HT200To400"                   \
 "GJets_HT400To600"                   \
 "DY5to50_HT100To200"                 \
 "DY5to50_HT200To400"                 \
 "DY5to50_HT400To600"                 \
 "DY5to50_HT600ToInf"                 \
)
# "DoubleEG"                            \
# "DoubleMuon"                          \
# "MuonEG"                              \

totin=0
totleft=0

for sample in ${samples[@]}
do
 #chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh"

 #lc=$( cat  "/nfs_scratch/tperry/gitignore/${aversion}/${sample}/checker.sh" | grep "root" | wc -l )
 #left=$(bash "/nfs_scratch/tperry/gitignore/${aversion}/${sample}/checker.sh" | wc -l )

 left=$(bash "${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh" | wc -l )
 lc=$( cat "${basedir}/submitters/gitignore/${aversion}/${sample}/checker.sh" | wc -l )

 totin=$(($totin+$lc))
 totleft=$(($totleft+$left))
 
 #cp ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPT.sh
 #sed -i -e 's/\.root/_OPT.root/g' ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPT.sh 

 printf "%40s %4s %4s \n" ${sample} ${lc}  ${left}
# echo "${sample} ${lc}  ${left}"
 
done
 printf " --------------------------------------------------\n"
 printf "%40s %4s %4s \n" Total  $totin $totleft
