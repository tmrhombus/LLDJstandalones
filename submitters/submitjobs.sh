#!/bin/bash

# script to generate submit files
# and optionally to submit to condor (@UW)

# source xx/LLDJ/setup.sh for ${aversion}

doSubmit=true
lumi=20000  #20000   #20000     #35870
nevents=-1
maxfilesperjob=200   # 500=6h

# Signal Samples
#  "ZH_HToSSTobbbb_MS-55_ctauS-1"      \
#  "ZH_HToSSTobbbb_MS-55_ctauS-10"     \
#  "ZH_HToSSTobbbb_MS-55_ctauS-100"    \
#  "ZH_HToSSTobbbb_MS-55_ctauS-1000"   \
#  "ZH_HToSSTobbbb_MS-40_ctauS-1"      \
#  "ZH_HToSSTobbbb_MS-40_ctauS-10"     \
#  "ZH_HToSSTobbbb_MS-40_ctauS-100"    \
#  "ZH_HToSSTobbbb_MS-40_ctauS-1000"   \
#  "ZH_HToSSTobbbb_MS-15_ctauS-1"      \
#  "ZH_HToSSTobbbb_MS-15_ctauS-10"     \
#  "ZH_HToSSTobbbb_MS-15_ctauS-100"    \
#  "ZH_HToSSTobbbb_MS-15_ctauS-1000"   \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-1"    \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-10"   \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-100"  \
#  "ggZH_HToSSTobbbb_MS-55_ctauS-1000" \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-1"    \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-10"   \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-100"  \
#  "ggZH_HToSSTobbbb_MS-40_ctauS-1000" \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-1"    \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-10"   \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-100"  \
#  "ggZH_HToSSTobbbb_MS-15_ctauS-1000" \

# Datasets
#  "Data_SingleEle_H_3"   \
#  "Data_SingleEle_H_2"   \
#  "Data_SingleEle_G"     \
#  "Data_SingleEle_F"     \
#  "Data_SingleEle_E"     \
#  "Data_SingleEle_D"     \
#  "Data_SingleEle_C"     \
#  "Data_SingleEle_B_2"   \
#  "Data_SingleEle_B_1"   \

#  "Data_SingleMu_H_3"    \
#  "Data_SingleMu_H_2"    \
#  "Data_SingleMu_G"      \
#  "Data_SingleMu_F"      \
#  "Data_SingleMu_E"      \
#  "Data_SingleMu_D"      \
#  "Data_SingleMu_C"      \
#  "Data_SingleMu_B_2"    \
#  "Data_SingleMu_B_1"    \

#  "Data_SinglePhoton_H_3"    \
#  "Data_SinglePhoton_H_2"    \
#  "Data_SinglePhoton_G"      \
#  "Data_SinglePhoton_F"      \
#  "Data_SinglePhoton_E"      \
#  "Data_SinglePhoton_D"      \
#  "Data_SinglePhoton_C"      \
#  "Data_SinglePhoton_B_2"    \
#  "Data_SinglePhoton_B_1"    \

# Main Backgrounds
#  "DY50_1"               \
#  "DY50_2"               \
#  "TTtoLL_1"             \
#  "TTtoLL_2"             \
#  "WJets_1"              \
#  "WJets_2"              \

# Other Backgrounds
#  "TTtoLfromT_1"         \
#  "TTtoLfromT_2"         \
#  "TTtoLfromTbar_1"      \
#  "TTtoLfromTbar_2"      \
#  "STs"                  \
#  "STtbar"               \
#  "STt"                  \
#  "STtbarW_1"            \
#  "STtbarW_2"            \
#  "STtW_1"               \
#  "STtW_2"               \
#  "WWToLNuLNu"           \
#  "WWToLNuQQ_1"          \
#  "WWToLNuQQ_2"          \
#  "WZToLNu2QorQQ2L"      \
#  "WZToLNuNuNu"          \
#  "WZToLLLNu"            \
#  "ZZToNuNuQQ"           \
#  "ZZToLLQQ"             \
#  "ZZToLLNuNu"           \
#  "ZZToLLLL"             \
#  "WG"                   \
#  "ZG"                   \
#  "ZH_Hbb_1"             \
#  "ZH_Hbb_2"             \
#  "ggZH_Hbb_1"           \
#  "ggZH_Hbb_2"           \
#  "ggZH_Hbb_3"           \
#  "GJets_HT40to100_1"    \
#  "GJets_HT40to100_2"    \
#  "GJets_HT100to200_1"   \
#  "GJets_HT100to200_2"   \
#  "GJets_HT200to400_1"   \
#  "GJets_HT200to400_2"   \
#  "GJets_HT400to600_1"   \
#  "GJets_HT400to600_2"   \
#  "GJets_HT600toInf_1"   \
#  "GJets_HT600toInf_2"   \
#  "DY5to50_HT70to100"    \
#  "DY5to50_HT100to200_1" \
#  "DY5to50_HT100to200_2" \
#  "DY5to50_HT200to400_1" \
#  "DY5to50_HT200to400_2" \
#  "DY5to50_HT400to600_1" \
#  "DY5to50_HT400to600_2" \
#  "DY5to50_HT600toInf_1" \
#  "DY5to50_HT600toInf_2" \

samples=(  \
 # "samplename"                 
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
  printf "\\" >> ${haddfile_OPTtree}           
  printf "\\" >> ${haddfile_BkgEst}

  printf "\n $(pwd)/$1_${jobfilenr}_NoSel_histograms.root" >> ${haddfile_NoSel_histograms}  
  printf "\n $(pwd)/$1_${jobfilenr}_Sig_histograms.root" >> ${haddfile_Sig_histograms}    
  printf "\n $(pwd)/$1_${jobfilenr}_ZH_histograms.root" >> ${haddfile_ZH_histograms}     
  printf "\n $(pwd)/$1_${jobfilenr}_DY_histograms.root" >> ${haddfile_DY_histograms}     
  printf "\n $(pwd)/$1_${jobfilenr}_OffZ_histograms.root" >> ${haddfile_OffZ_histograms}   
  printf "\n $(pwd)/$1_${jobfilenr}_NoPair_histograms.root" >> ${haddfile_NoPair_histograms} 
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
 if [[ ${sample} == "Single"* ]]
 then
  mc=""
 elif [[ ${sample} == "Double"* ]]
 then
  mc=""
 elif [[ ${sample} == "MuonEG"* ]]
 then
  mc=""
 else
  mc="-m"
 fi

 makeasubmitdir ${sample} ${mc}

done

