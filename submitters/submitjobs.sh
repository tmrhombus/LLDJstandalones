#!/bin/bash

# script to generate submit files
# and optionally to submit to condor (@UW)

# source xx/LLDJ/setup.sh for ${aversion}

doSubmit=true
#lumi=16226.445
lumi=10000.0
nevents=-1
maxfilesperjob=200   # 500=6h

### Data
# "Data_SingleMu_H_3"      \
# "Data_SingleMu_H_2"      \
# "Data_SingleMu_G"        \
# "Data_SingleMu_F"        \
# "Data_SingleMu_E"        \
# "Data_SingleMu_D"        \
# "Data_SingleMu_C"        \
# "Data_SingleMu_B_2"      \
#
# "Data_SingleEle_H_3"     \
# "Data_SingleEle_H_2"     \
# "Data_SingleEle_G"       \
# "Data_SingleEle_F"       \
# "Data_SingleEle_E"       \
# "Data_SingleEle_D"       \
# "Data_SingleEle_C"       \
# "Data_SingleEle_B_2"     \
#
# "Data_DoubleMu_H_3"      \
# "Data_DoubleMu_H_2"      \
# "Data_DoubleMu_G"        \
# "Data_DoubleMu_F"        \
# "Data_DoubleMu_E"        \
# "Data_DoubleMu_D"        \
# "Data_DoubleMu_C"        \
# "Data_DoubleMu_B_2"      \
#
# "Data_DoubleEG_H_3"      \
# "Data_DoubleEG_H_2"      \
# "Data_DoubleEG_G"        \
# "Data_DoubleEG_F"        \
# "Data_DoubleEG_E"        \
# "Data_DoubleEG_D"        \
# "Data_DoubleEG_C"        \
# "Data_DoubleEG_B_2"      \
#
# "Data_MuonEG_B_2"        \
# "Data_MuonEG_C"          \
# "Data_MuonEG_D"          \
# "Data_MuonEG_E"          \
# "Data_MuonEG_F"          \
# "Data_MuonEG_G"          \
# "Data_MuonEG_H_2"        \
# "Data_MuonEG_H_3"        \
#
# "Data_SinglePhoton_H_3"  \
# "Data_SinglePhoton_H_2"  \
# "Data_SinglePhoton_G"    \
# "Data_SinglePhoton_F"    \
# "Data_SinglePhoton_E"    \
# "Data_SinglePhoton_D"    \
# "Data_SinglePhoton_C"    \
# "Data_SinglePhoton_B_2"  \
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
# "WW"               \
# "WZ"               \
# "ZZ"               \
# "WWTo2L2Nu"        \
# "WWToLNuQQ"        \
# "WZTo1L3Nu"        \
# "WZTo3LNu"         \
# "WZToLNu2QorQQ2L"  \
# "ZZTo2L2Nu"        \
# "ZZTo2L2Q"         \
# "ZZTo2Q2Nu"        \
# "ZZTo4L"           \
#
## VGamma
# "ZGTo2LG"  \
# "WGToLNuG" \
#
## ZH
# "ggZH_HToBB_ZToLL"  \
# "ZH_HToBB_ZToLL"    \
#
## QCD
# "QCD_HT100to200"    \
# "QCD_HT200to300"    \
# "QCD_HT300to500"    \
# "QCD_HT500to700"    \
# "QCD_HT700to1000"    \
# "QCD_HT1000to1500"    \
# "QCD_HT1500to2000"    \
# "QCD_HT2000toInf"    \
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

samples=(  \
### Data
 "Data_SingleMu_H_3"      \
 "Data_SingleMu_H_2"      \
 "Data_SingleMu_G"        \
 "Data_SingleMu_F"        \
 "Data_SingleMu_E"        \
 "Data_SingleMu_D"        \
 "Data_SingleMu_C"        \
 "Data_SingleMu_B_2"      \
#
 "Data_SingleEle_H_3"     \
 "Data_SingleEle_H_2"     \
 "Data_SingleEle_G"       \
 "Data_SingleEle_F"       \
 "Data_SingleEle_E"       \
 "Data_SingleEle_D"       \
 "Data_SingleEle_C"       \
 "Data_SingleEle_B_2"     \
#
 "Data_DoubleMu_H_3"      \
 "Data_DoubleMu_H_2"      \
 "Data_DoubleMu_G"        \
 "Data_DoubleMu_F"        \
 "Data_DoubleMu_E"        \
 "Data_DoubleMu_D"        \
 "Data_DoubleMu_C"        \
 "Data_DoubleMu_B_2"      \
#
 "Data_DoubleEG_H_3"      \
 "Data_DoubleEG_H_2"      \
 "Data_DoubleEG_G"        \
 "Data_DoubleEG_F"        \
 "Data_DoubleEG_E"        \
 "Data_DoubleEG_D"        \
 "Data_DoubleEG_C"        \
 "Data_DoubleEG_B_2"      \
#
 "Data_MuonEG_B_2"        \
 "Data_MuonEG_C"          \
 "Data_MuonEG_D"          \
 "Data_MuonEG_E"          \
 "Data_MuonEG_F"          \
 "Data_MuonEG_G"          \
 "Data_MuonEG_H_2"        \
 "Data_MuonEG_H_3"        \
#
 "Data_SinglePhoton_H_3"  \
 "Data_SinglePhoton_H_2"  \
 "Data_SinglePhoton_G"    \
 "Data_SinglePhoton_F"    \
 "Data_SinglePhoton_E"    \
 "Data_SinglePhoton_D"    \
 "Data_SinglePhoton_C"    \
 "Data_SinglePhoton_B_2"  \
#
### MC backgrounds
#
## DY
 "DYJetsToLL_M-5to50_HT-70to100"   \
 "DYJetsToLL_M-5to50_HT-100to200"  \
 "DYJetsToLL_M-5to50_HT-200to400"  \
 "DYJetsToLL_M-5to50_HT-400to600"  \
 "DYJetsToLL_M-5to50_HT-600toInf"  \
 "DYJetsToLL_M-10to50"             \
 "DYJetsToLL_M-50"                 \
#
## WJets
 "WJetsToLNu"     \
#
## TTbar
 "TTJets"         \
 "TTtoLL"         \
 "TTtoLfromTbar"  \
 "TTtoLfromT"     \
#
## Single Top
 "ST_s-channel_4f_leptonDecays"             \
 "ST_t-channel_antitop_4f_inclusiveDecays"  \
 "ST_t-channel_top_4f_inclusiveDecays"      \
 "ST_tW_antitop_5f_NoFullyHadronicDecays"   \
 "ST_tW_top_5f_NoFullyHadronicDecays"       \
#
## GJets
 "GJets_HT-40To100"   \
 "GJets_HT-100To200"  \
 "GJets_HT-200To400"  \
 "GJets_HT-400To600"  \
 "GJets_HT-600ToInf"  \
#
## Diboson
 "WW"               \
 "WZ"               \
 "ZZ"               \
 "WWTo2L2Nu"        \
 "WWToLNuQQ"        \
 "WZTo1L3Nu"        \
 "WZTo3LNu"         \
 "WZToLNu2QorQQ2L"  \
 "ZZTo2L2Nu"        \
 "ZZTo2L2Q"         \
 "ZZTo2Q2Nu"        \
 "ZZTo4L"           \
#
## VGamma
 "ZGTo2LG"  \
 "WGToLNuG" \
#
## ZH
 "ggZH_HToBB_ZToLL"  \
 "ZH_HToBB_ZToLL"    \
#
##QCD
 "QCD_HT100to200"    \
 "QCD_HT200to300"    \
 "QCD_HT300to500"    \
 "QCD_HT500to700"    \
 "QCD_HT700to1000"    \
 "QCD_HT1000to1500"    \
 "QCD_HT1500to2000"    \
 "QCD_HT2000toInf"    \
#
## Signal Samples
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1"      \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10"     \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100"    \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000"   \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1"        \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10"       \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100"      \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000"     \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1"      \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10"     \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"    \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000"   \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1"        \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10"       \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"      \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000"     \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1"      \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10"     \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100"    \
 "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000"   \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1"        \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10"       \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100"      \
 "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000"     \
)

printf "Version: ${aversion}\n"

makeasubmitdir () {
 printf "Making submits for $1\n"
 
 # go to the directory
 submitdir=${asubdir}/gitignore/${aversion}/$1
 mkdir -p ${submitdir} 
 pushd    ${submitdir}  > /dev/null
 printf " The directory is %s\n" $(pwd)
 
 mkdir -p logs
 
 # write base for submit file
 printf "universe = vanilla\n" > submitfile
 printf "Executable = ${CMSSW_BASE}/src/LLDJstandalones/submitters/runjob.sh\n" >> submitfile
 printf "Should_Transfer_Files = YES \n" >> submitfile
 printf "WhenToTransferOutput = ON_EXIT\n" >> submitfile
 printf "Transfer_Input_Files = ${CMSSW_BASE}/src/LLDJstandalones/analyzers/runanalyzer.exe,${CMSSW_BASE}/src/LLDJstandalones/lists/$1.list,${CMSSW_BASE}/src/LLDJstandalones/lists/$1.info,${CMSSW_BASE}/src/LLDJstandalones/analyzers/puWeights_69200_24jan2017.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/egammaEffi_MoriondBH_eleTight.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/egammaEffi_MoriondBH_eleMedium.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/egammaEffi_MoriondBH_eleLoose.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/feff_ZH.root\n" >> submitfile

 printf "notify_user = $(whoami)@cern.ch\n" >> submitfile
 printf "x509userproxy = $X509_USER_PROXY\n" >> submitfile
 printf "\n" >> submitfile
 printf "Output = logs/runanalyzer_\$(Cluster)_\$(Process).stdout\n" >> submitfile
 printf "Error  = logs/runanalyzer_\$(Cluster)_\$(Process).stderr\n" >> submitfile
 printf "Log    = logs/runanalyzer_\$(Cluster)_\$(Process).log\n" >> submitfile
 printf "\n" >> submitfile
 
 # make haddfile (make now for merging expected results)
 haddfile_NoSel_histograms="./haddit_NoSel_histograms.sh"
 haddfile_Sig_histograms="./haddit_Sig_histograms.sh"
 haddfile_ZH_histograms="./haddit_ZH_histograms.sh"
 haddfile_DY_histograms="./haddit_DY_histograms.sh"
 haddfile_OffZ_histograms="./haddit_OffZ_histograms.sh"
 haddfile_NoPair_histograms="./haddit_NoPair_histograms.sh"
 haddfile_CRHeavy_histograms="./haddit_CRHeavy_histograms.sh"
 haddfile_CRLight_histograms="./haddit_CRLight_histograms.sh"
 haddfile_OPTtree="./haddit_OPTtree.sh"
 haddfile_BkgEst="./haddit_BkgEst.sh"

 hadddir="${rootdir}/${aversion}"
 mkdir -p ${hadddir}
 printf "#!/bin/bash\n\n" > ${haddfile_NoSel_histograms} 
 printf "#!/bin/bash\n\n" > ${haddfile_Sig_histograms}   
 printf "#!/bin/bash\n\n" > ${haddfile_ZH_histograms}    
 printf "#!/bin/bash\n\n" > ${haddfile_DY_histograms}    
 printf "#!/bin/bash\n\n" > ${haddfile_OffZ_histograms}  
 printf "#!/bin/bash\n\n" > ${haddfile_NoPair_histograms}
 printf "#!/bin/bash\n\n" > ${haddfile_CRHeavy_histograms}
 printf "#!/bin/bash\n\n" > ${haddfile_CRLight_histograms}
 printf "#!/bin/bash\n\n" > ${haddfile_OPTtree}          
 printf "#!/bin/bash\n\n" > ${haddfile_BkgEst}

 # make checker
 checkfile="./checker.sh"
 printf "#!/bin/bash\n\n" > ${checkfile}

 # hadd command to go in haddfile
  # name of final merged file
 printf "hadd ${hadddir}/$1_NoSel_histograms.root"  >> ${haddfile_NoSel_histograms}  
 printf "hadd ${hadddir}/$1_Sig_histograms.root"    >> ${haddfile_Sig_histograms}    
 printf "hadd ${hadddir}/$1_ZH_histograms.root"     >> ${haddfile_ZH_histograms}     
 printf "hadd ${hadddir}/$1_DY_histograms.root"     >> ${haddfile_DY_histograms}     
 printf "hadd ${hadddir}/$1_OffZ_histograms.root"   >> ${haddfile_OffZ_histograms}   
 printf "hadd ${hadddir}/$1_NoPair_histograms.root" >> ${haddfile_NoPair_histograms} 
 printf "hadd ${hadddir}/$1_CRHeavy_histograms.root">> ${haddfile_CRHeavy_histograms} 
 printf "hadd ${hadddir}/$1_CRLight_histograms.root">> ${haddfile_CRLight_histograms} 
 printf "hadd ${hadddir}/$1_OPTtree.root"           >> ${haddfile_OPTtree}           
 printf "hadd ${hadddir}/$1_BkgEst.root"            >> ${haddfile_BkgEst}           

 # breaking up input file list
 nfilesinlist=$( wc -l < "${CMSSW_BASE}/src/LLDJstandalones/lists/$1.list" )
 filenrlow=0
 jobfilenr=0

 printf " nfilesinlist = ${nfilesinlist} / ${maxfilesperjob} \n\n"
 
 until [ ${filenrlow} -gt ${nfilesinlist} ]
 do

  printf "Arguments = $1 ${lumi} ${nevents} ${maxfilesperjob} ${filenrlow} _${jobfilenr} $2 \n" >> submitfile
  printf "Queue\n" >> submitfile
  printf "\n" >> submitfile

  # add files to be produced to haddfiles
  printf "\\" >> ${haddfile_NoSel_histograms}  
  printf "\\" >> ${haddfile_Sig_histograms}    
  printf "\\" >> ${haddfile_ZH_histograms}     
  printf "\\" >> ${haddfile_DY_histograms}     
  printf "\\" >> ${haddfile_OffZ_histograms}   
  printf "\\" >> ${haddfile_NoPair_histograms} 
  printf "\\" >> ${haddfile_CRHeavy_histograms} 
  printf "\\" >> ${haddfile_CRLight_histograms} 
  printf "\\" >> ${haddfile_OPTtree}           
  printf "\\" >> ${haddfile_BkgEst}

  printf "\n $(pwd)/$1_${jobfilenr}_NoSel_histograms.root" >> ${haddfile_NoSel_histograms}  
  printf "\n $(pwd)/$1_${jobfilenr}_Sig_histograms.root" >> ${haddfile_Sig_histograms}    
  printf "\n $(pwd)/$1_${jobfilenr}_ZH_histograms.root" >> ${haddfile_ZH_histograms}     
  printf "\n $(pwd)/$1_${jobfilenr}_DY_histograms.root" >> ${haddfile_DY_histograms}     
  printf "\n $(pwd)/$1_${jobfilenr}_OffZ_histograms.root" >> ${haddfile_OffZ_histograms}   
  printf "\n $(pwd)/$1_${jobfilenr}_NoPair_histograms.root" >> ${haddfile_NoPair_histograms} 
  printf "\n $(pwd)/$1_${jobfilenr}_CRHeavy_histograms.root" >> ${haddfile_CRHeavy_histograms} 
  printf "\n $(pwd)/$1_${jobfilenr}_CRLight_histograms.root" >> ${haddfile_CRLight_histograms} 
  printf "\n $(pwd)/$1_${jobfilenr}_OPTtree.root" >> ${haddfile_OPTtree}           
  printf "\n $(pwd)/$1_${jobfilenr}_BkgEst.root" >> ${haddfile_BkgEst}

  # add file to checker, all histos are made at the same time, so only check one
  printf "\n if [ ! -f $(pwd)/$1_${jobfilenr}_OPTtree.root ]; then printf \" $(pwd)/$1_${jobfilenr}_OPTtree.root \\n\"; fi " >> ${checkfile}

  # increment filenumber counters
  #printf "NFILES: %s %s %s\n" $nfilesinlist $filenrlow $jobfilenr
  filenrlow=$(( ${filenrlow} + ${maxfilesperjob} ))
  jobfilenr=$(( ${jobfilenr} + 1 ))

 done # until filenrlow > nfilesinlist

 printf "\n\n" >> ${haddfile_NoSel_histograms}  
 printf "\n\n" >> ${haddfile_Sig_histograms}    
 printf "\n\n" >> ${haddfile_ZH_histograms}     
 printf "\n\n" >> ${haddfile_DY_histograms}     
 printf "\n\n" >> ${haddfile_OffZ_histograms}   
 printf "\n\n" >> ${haddfile_NoPair_histograms} 
 printf "\n\n" >> ${haddfile_CRHeavy_histograms} 
 printf "\n\n" >> ${haddfile_CRLight_histograms} 
 printf "\n\n" >> ${haddfile_OPTtree}           
 printf "\n\n" >> ${haddfile_BkgEst}

 if [ ${doSubmit} = true ]
 then
  condor_submit submitfile
 fi
 
 popd > /dev/null
}


# actually call the function
for sample in ${samples[@]} 
do
 # set isMC flag if MC
 if [[ ${sample} == "Data"* ]]
 then
  mc=""
 else
  mc="-m"
 fi

 makeasubmitdir ${sample} ${mc}

done

