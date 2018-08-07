#!/bin/bash

# just calls the hadd scripts automatically generated
# submission time in ${basedir}/submitters/gitignore/${aversion}/${sample}/haddit.sh
mkdir -p "${rootdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}"
mkdir -p "${plotdir}/${aversion}/logs"

samples=( \
 # samples go here
)

### Data
# "Data_SingleMu_H_3"       \
# "Data_SingleMu_H_2"       \
# "Data_SingleMu_G"         \
# "Data_SingleMu_F"         \
# "Data_SingleMu_E"         \
# "Data_SingleMu_D"         \
# "Data_SingleMu_C"         \
# "Data_SingleMu_B_2"       \
#
# "Data_SingleEle_H_3"      \
# "Data_SingleEle_H_2"      \
# "Data_SingleEle_G"        \
# "Data_SingleEle_F"        \
# "Data_SingleEle_E"        \
# "Data_SingleEle_D"        \
# "Data_SingleEle_C"        \
# "Data_SingleEle_B_2"      \
#
# "Data_DoubleMu_H_3"       \
# "Data_DoubleMu_H_2"       \
# "Data_DoubleMu_G"         \
# "Data_DoubleMu_F"         \
# "Data_DoubleMu_E"         \
# "Data_DoubleMu_D"         \
# "Data_DoubleMu_C"         \
# "Data_DoubleMu_B_2"       \
#
# "Data_DoubleEG_H_3"       \
# "Data_DoubleEG_H_2"       \
# "Data_DoubleEG_G"         \
# "Data_DoubleEG_F"         \
# "Data_DoubleEG_E"         \
# "Data_DoubleEG_D"         \
# "Data_DoubleEG_C"         \
# "Data_DoubleEG_B_2"       \
#
# "Data_MuonEG_B_2"         \
# "Data_MuonEG_C"           \
# "Data_MuonEG_D"           \
# "Data_MuonEG_E"           \
# "Data_MuonEG_F"           \
# "MuonEG"                  \
# "Data_MuonEG_G"           \
# "Data_MuonEG_H_2"         \
# "Data_MuonEG_H_3"         \
# "Data_SinglePhoton_H_3"   \
# "Data_SinglePhoton_H_2"   \
# "Data_SinglePhoton_G"     \
# "SinglePhoton"            \
# "Data_SinglePhoton_F"     \
# "Data_SinglePhoton_E"     \
# "Data_SinglePhoton_D"     \
# "Data_SinglePhoton_C"     \
# "Data_SinglePhoton_B_2"   \
#
### MC backgrounds
#
## DY
# "DYJetsToLL_M-5to50_HT-70to100"   \
# "DYJetsToLL_M-5to50_HT-100to200"  \
# "DYJetsToLL_M-5to50_HT-200to400"  \
# "DYJetsToLL_M-5to50_HT-400to600"  \
# "DYJetsToLL_M-5to50_HT-600toInf"  \
# "DYJetsToLL_M-10to50"             \
# "DYJetsToLL_M-50"                 \
#
## WJets
# "WJetsToLNu"     \
#
## TTbar
# "TTJets"         \
# "TTtoLL"         \
# "TTtoLfromTbar"  \
# "TTtoLfromT"     \
#
## Single Top
# "ST_s-channel_4f_leptonDecays"             \
# "ST_t-channel_antitop_4f_inclusiveDecays"  \
# "ST_t-channel_top_4f_inclusiveDecays"      \
# "ST_tW_antitop_5f_NoFullyHadronicDecays"   \
# "ST_tW_top_5f_NoFullyHadronicDecays"       \
#
## GJets
# "GJets_HT-40To100"   \
# "GJets_HT-100To200"  \
# "GJets_HT-200To400"  \
# "GJets_HT-400To600"  \
# "GJets_HT-600ToInf"  \
#
## Diboson
# "WW"                 \
# "WZ"                 \
# "ZZ"                 \
# "WWTo2L2Nu"          \
# "WWToLNuQQ"          \
# "WZTo1L3Nu"          \
# "WZTo3LNu"           \
# "WZToLNu2QorQQ2L"    \
# "ZZTo2L2Nu"          \
# "ZZTo2L2Q"           \
# "ZZTo2Q2Nu"          \
# "ZZTo4L"             \
#
## VGamma
# "ZGTo2LG"            \
# "WGToLNuG"           \
#
## ZH
# "ggZH_HToBB_ZToLL"   \
# "ZH_HToBB_ZToLL"     \
#
## Signal Samples
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1"      \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10"     \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100"    \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000"   \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1"        \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10"       \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100"      \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000"     \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1"      \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10"     \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"    \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000"   \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1"        \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10"       \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"      \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000"     \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1"      \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10"     \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100"    \
# "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000"   \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1"        \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10"       \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100"      \
# "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000"     \

#for sample in $(ls ${basedir}/submitters/gitignore/${aversion}/) # works but dangerous?
for sample in ${samples[@]}
do

 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_DY_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoPair_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRHeavy_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRLight_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoSel_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPTtree.sh"
 #chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_BkgEst.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OffZ_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_Sig_histograms.sh"
 chmod +x "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_ZH_histograms.sh"

 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_DY_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoPair_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRHeavy_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_CRLight_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_NoSel_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OPTtree.sh"
 #bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_BkgEst.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_OffZ_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_Sig_histograms.sh"
 bash "${basedir}/submitters/gitignore/${aversion}/${sample}/haddit_ZH_histograms.sh"

done
