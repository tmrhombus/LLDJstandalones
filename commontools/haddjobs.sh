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
  "DY5to50_HT100To200"              \
  "DY5to50_HT200To400"              \
  "DY5to50_HT400To600"              \
  "DY5to50_HT600ToInf"              \
  "DY10to50"                        \
  "DY50"                            \
  "ggZH_HToBB_ZToLL"                \
  "ggZH_HToSSTobbbb_MS15_ctauS1"    \
  "ggZH_HToSSTobbbb_MS15_ctauS10"   \
  "ggZH_HToSSTobbbb_MS15_ctauS100"  \
  "ggZH_HToSSTobbbb_MS15_ctauS1000" \
  "ZH_HToSSTobbbb_MS15_ctauS1"      \
  "ZH_HToSSTobbbb_MS15_ctauS10"     \
  "ZH_HToSSTobbbb_MS15_ctauS100"    \
  "ZH_HToSSTobbbb_MS15_ctauS1000"   \
  "ggZH_HToSSTobbbb_MS40_ctauS1"    \
  "ggZH_HToSSTobbbb_MS40_ctauS10"   \
  "ggZH_HToSSTobbbb_MS40_ctauS100"  \
  "ggZH_HToSSTobbbb_MS40_ctauS1000" \
  "ZH_HToSSTobbbb_MS40_ctauS1"      \
  "ZH_HToSSTobbbb_MS40_ctauS10"     \
  "ZH_HToSSTobbbb_MS40_ctauS100"    \
  "ZH_HToSSTobbbb_MS40_ctauS1000"   \
  "ggZH_HToSSTobbbb_MS55_ctauS1"    \
  "ggZH_HToSSTobbbb_MS55_ctauS10"   \
  "ggZH_HToSSTobbbb_MS55_ctauS100"  \
  "ZH_HToSSTobbbb_MS55_ctauS1"      \
  "ZH_HToSSTobbbb_MS55_ctauS10"     \
  "ZH_HToSSTobbbb_MS55_ctauS100"    \
  "GJets_HT40To100"                 \
  "GJets_HT100To200"                \
  "GJets_HT200To400"                \
  "GJets_HT400To600"                \
  "GJets_HT600ToInf"                \
  "ST_s"                            \
  "STbar_t"                         \
  "ST_t"                            \
  "STbar_tW"                        \
  "ST_tW"                           \
  "TTtoLL"                          \
  "TTJets"                          \
  "TTtoLfromTbar"                   \
  "TTtoLfromT"                      \
  "WG"                              \
  "WJetsToLNu"                      \
  "WW"                              \
  "WWToLNuLNu"                      \
  "WWToLNuQQ"                       \
  "WZ"                              \
  "WZToL3Nu"                        \
  "WZTo3LNu"                        \
  "WZToLNu2QorQQ2L"                 \
  "ZG"                              \
  "ZH_HToBB_ZToLL"                  \
  "ZZ"                              \
  "ZZToLLNuNu"                      \
  "ZZToLLQQ"                        \
  "ZZToNuNuQQ"                      \
  "ZZToLLLL"                        \
  "Data_SingleEle_B_2"              \
  "Data_SingleEle_C"                \
  "Data_SingleEle_D"                \
  "Data_SingleEle_E"                \
  "Data_SingleEle_F"                \
  "Data_SingleEle_G"                \
  "Data_SingleEle_H_2"              \
  "Data_SingleEle_H_3"              \
  "Data_SingleMu_B_2"               \
  "Data_SingleMu_C"                 \
  "Data_SingleMu_D"                 \
  "Data_SingleMu_E"                 \
  "Data_SingleMu_F"                 \
  "Data_SingleMu_G"                 \
  "Data_SingleMu_H_2"               \
  "Data_SingleMu_H_3"               \
  "Data_SinglePhoton_B_2"           \
  "Data_SinglePhoton_C"             \
  "Data_SinglePhoton_D"             \
  "Data_SinglePhoton_E"             \
  "Data_SinglePhoton_F"             \
  "Data_SinglePhoton_G"             \
  "Data_SinglePhoton_H_2"           \
  "Data_SinglePhoton_H_3"           \
  "Data_DoubleEG_B_2"              \
  "Data_DoubleEG_C"                \
  "Data_DoubleEG_D"                \
  "Data_DoubleEG_E"                \
  "Data_DoubleEG_F"                \
  "Data_DoubleEG_G"                \
  "Data_DoubleEG_H_2"              \
  "Data_DoubleEG_H_3"              \
  "Data_DoubleMu_B_2"               \
  "Data_DoubleMu_C"                 \
  "Data_DoubleMu_D"                 \
  "Data_DoubleMu_E"                 \
  "Data_DoubleMu_G"                 \
  "Data_DoubleMu_H_2"               \
  "Data_DoubleMu_H_3"               \
)
#  "Data_DoubleMu_H_3"               \
#  "Data_DoubleMu_H_2"               \
#  "Data_DoubleMu_G"                 \
#  "Data_DoubleMu_E"                 \
#  "Data_DoubleMu_D"                 \
#  "Data_DoubleMu_C"                 \
#  "Data_DoubleMu_B_2"               \
#  "Data_DoubleEG_H_3"               \
#  "Data_DoubleEG_H_2"               \
#  "Data_DoubleEG_F"                 \
#  "Data_DoubleEG_E"                 \
#  "Data_DoubleEG_D"                 \
#  "Data_DoubleEG_C"                 \
#  "Data_DoubleEG_B_2"               \

#for sample in $(ls ${basedir}/submitters/gitignore/${aversion}/) # works but dangerous?
for sample in ${samples[@]}
do

 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_DY_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoPair_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRHeavy_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRLight_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoSel_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPTtree.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_BkgEst.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OffZ_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_Sig_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_ZH_histograms.sh"

 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_DY_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoPair_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRHeavy_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRLight_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoSel_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPTtree.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_BkgEst.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OffZ_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_Sig_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_ZH_histograms.sh"

done
