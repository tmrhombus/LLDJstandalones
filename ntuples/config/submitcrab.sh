#voms-proxy-init --voms cms --valid 100:00

# do we submit or just generate submit scripts
dosubmit=true
doAOD=true

# start the timer
START=$(date +%s);
printf "Started at ${START}\n\n"

if [ ${doAOD} = true ]
then
 nversion="${nversion}AOD"
fi

printf "nversion is ${nversion} \n"

# make the directory where we'll submit from
thesubdir="${subdir}/gitignore/${nversion}"
mkdir -p ${thesubdir} 
printf "Making submit configurations in\n ${thesubdir}\n\n"

# copy necessary files into submit directory
if [ ${doAOD} = true ]
then
 cp "${subdir}/run_data_80XAOD.py" ${thesubdir}
 cp "${subdir}/run_mc_80XAOD.py"   ${thesubdir}
 printf "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) \n" >> "${thesubdir}/run_data_80XAOD.py" 
 printf "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) \n" >> "${thesubdir}/run_mc_80XAOD.py"   
 printf "process.MessageLogger.cerr.FwkReport.reportEvery = 1000000 \n" >> "${thesubdir}/run_data_80XAOD.py" 
 printf "process.MessageLogger.cerr.FwkReport.reportEvery = 1000000 \n" >> "${thesubdir}/run_mc_80XAOD.py"   
 # get the DAS name mapping
 thedasmap="${listdir}/ntuple/dasmapAOD.list"
else
 cp "${subdir}/run_data_80X.py" ${thesubdir}
 cp "${subdir}/run_mc_80X.py"   ${thesubdir}
 printf "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) \n" >> "${thesubdir}/run_data_80X.py" 
 printf "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) \n" >> "${thesubdir}/run_mc_80X.py"   
 printf "process.MessageLogger.cerr.FwkReport.reportEvery = 1000000 \n" >> "${thesubdir}/run_data_80X.py" 
 printf "process.MessageLogger.cerr.FwkReport.reportEvery = 1000000 \n" >> "${thesubdir}/run_mc_80X.py"   
 # get the DAS name mapping
 thedasmap="${listdir}/ntuple/dasmap.list"
fi


# sample names to run over
samples=( \
  "ZH_HToSSTobbbb_MS-55_ctauS-1"      \
)

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

# print which samples we're running over
printf "For:\n"
for samplename in ${samples[@]} 
do
 printf " ${samplename}\n"
done

# loop over mc samples
for samplename in ${samples[@]}
do
 printf "\n******************************************************\n"
 if [ ${dosubmit} = true ]
 then
  printf "** \n"
  printf "** --- SUBMITTING --- \n"
  printf "** \n"
 fi
 printf "** Sample: ${samplename} \n"
 printf "******************************************************\n"
 printf "******************************************************\n\n"

 datasetname="$(grep -P ${samplename} ${thedasmap} | sed -n -e "s@ ${samplename}    @@p")"

 submitname="submit_${samplename}"
 submitfile="${thesubdir}/${submitname}.py"

 # set veriables for submitting this specific sample
 WORKAREA="'crabsubmits_${nversion}'"

 if [[ "${samplename:0:4}" == "Data" ]]
 then
  if [ ${doAOD} = true ]
  then
   # DATA AOD
   CMSRUNCONFIG="'run_data_80XAOD.py'" 
   UPERJOB="100"
  else
   # DATA miniAOD
   CMSRUNCONFIG="'run_data_80X.py'" 
   UPERJOB="100"
  fi
  SPLITTING="'LumiBased'"
 else
  if [ ${doAOD} = true ]
  then
   # MC AOD
   CMSRUNCONFIG="'run_mc_80XAOD.py'" 
   UPERJOB="10"
  else
   # MC miniAOD
   CMSRUNCONFIG="'run_mc_80X.py'" 
   UPERJOB="1"
  fi
  SPLITTING="'FileBased'"
 fi

 NUNITS="-1"
 REQUESTNAME="'${samplename}'"
 DATASET="'${datasetname}'"
 STORESITE="'T3_US_FNALLPC'"
 OUTLFNBASE="'/store/group/lpchbb/LLDJntuples/${nversion}'"
 MAXMEM="2000"

 printf "WORKAREA      ${WORKAREA}     \n" 
 printf "CMSRUNCONFIG  ${CMSRUNCONFIG} \n" 
 printf "NUNITS        ${NUNITS}       \n" 
 printf "UPERJOB       ${UPERJOB}      \n" 
 printf "SPLITTING     ${SPLITTING}    \n" 
 printf "REQUESTNAME   ${REQUESTNAME}  \n" 
 printf "DATASET       ${DATASET}      \n" 
 printf "STORESITE     ${STORESITE}    \n" 
 printf "OUTLFNBASE    ${OUTLFNBASE}   \n" 
 printf "MAXMEM        ${MAXMEM}       \n" 

 # copy and then fill template for crab submits
 cp ${subdir}/crab_template.py             "${submitfile}"
 sed -i "s@WORKAREA@${WORKAREA}@g"         "${submitfile}"
 sed -i "s@CMSRUNCONFIG@${CMSRUNCONFIG}@g" "${submitfile}" 
 sed -i "s@NUNITS@${NUNITS}@g"             "${submitfile}" 
 sed -i "s@UPERJOB@${UPERJOB}@g"           "${submitfile}" 
 sed -i "s@SPLITTING@${SPLITTING}@g"       "${submitfile}" 
 sed -i "s@REQUESTNAME@${REQUESTNAME}@g"   "${submitfile}" 
 sed -i "s@DATASET@${DATASET}@g"           "${submitfile}" 
 sed -i "s@STORESITE@${STORESITE}@g"       "${submitfile}" 
 sed -i "s@OUTLFNBASE@${OUTLFNBASE}@g"     "${submitfile}" 
 sed -i "s@MAXMEM@${MAXMEM}@g"             "${submitfile}" 

 # submit the jobs
 if [ ${dosubmit} = true ]
 then
  pushd ${thesubdir} > /dev/null
  python ${submitfile}
  popd > /dev/null
 fi

done

# end the timer
END=$(date +%s);
printf "\nStarted at ${START}\n"
printf "Ended at   ${END}\n\n"

