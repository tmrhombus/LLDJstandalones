#voms-proxy-init --voms cms --valid 100:00

domc=false
dodata=false
dosubmit=false

# start the timer
START=$(date +%s);
printf "Started at ${START}\n\n"

# make the directory where we'll submit from
thesubdir="${subdir}/gitignore/${nversion}"
mkdir -p ${thesubdir} 
printf "Making submit configurations in\n ${thesubdir}\n\n"

# get the DAS name mapping
thedasmap="${listdir}/ntuple/dasmap.list"

#  MC sample names
samples=( \
 "ZHHbb_1"        \
 "ZHHbb_2"        \
 "ggZHHbb_1"      \
 "ggZHHbb_2"      \
 "ggZHHbb_3"      \
 "ggZHSSbbbb_01"  \
 "ggZHSSbbbb_02"  \
 "ggZHSSbbbb_03"  \
 "ggZHSSbbbb_04"  \
 "ggZHSSbbbb_05"  \
 "ggZHSSbbbb_06"  \
 "ggZHSSbbbb_07"  \
 "Data_SingleMu"  \
 "Data_SingleEle" \
)

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
 if [ ${samplename} == "Data_SingleMu" ]
 then
  CMSRUNCONFIG="'run_data_80x_SingleMu.py'" 
  INPUTFILES="'Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt', 'Summer16_23Sep2016AllV4_DATA.db' "
 elif [ ${samplename} == "Data_SingleEle" ]
 then
  CMSRUNCONFIG="'run_data_80x_SingleEle.py'" 
  INPUTFILES="'Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt', 'Summer16_23Sep2016AllV4_DATA.db' "
 else
  CMSRUNCONFIG="'run_mc_80x.py'" 
  INPUTFILES="'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC.db'"
 fi
 NUNITS="'-1'"
 REQUESTNAME="'${nversion}'"
 DATASET="'${datasetname}'"
 STORESITE="'T2_US_FNAL'"
 OUTLFNBASE="'/eos/store/tmperry/${nversion}'"

 printf "WORKAREA      ${WORKAREA}    \n" 
 printf "CMSRUNCONFIG  ${CMSRUNCONFIG} \n" 
 printf "INPUTFILES    ${INPUTFILES}   \n" 
 printf "NUNITS        ${NUNITS}       \n" 
 printf "REQUESTNAME   ${REQUESTNAME}  \n" 
 printf "DATASET       ${DATASET}      \n" 
 printf "STORESITE     ${STORESITE}      \n" 
 printf "OUTLFNBASE    ${OUTLFNBASE}   \n" 

 # copy and then fill template for crab submits
 cp ${subdir}/crab_template.py             "${submitfile}"
 sed -i "s@WORKAREA@${WORKAREA}@g"         "${submitfile}"
 sed -i "s@CMSRUNCONFIG@${CMSRUNCONFIG}@g" "${submitfile}" 
 sed -i "s@INPUTFILES@${INPUTFILES}@g"     "${submitfile}" 
 sed -i "s@NUNITS@${NUNITS}@g"             "${submitfile}" 
 sed -i "s@REQUESTNAME@${REQUESTNAME}@g"   "${submitfile}" 
 sed -i "s@DATASET@${DATASET}@g"           "${submitfile}" 
 sed -i "s@STORESITE@${STORESITE}@g"       "${submitfile}" 
 sed -i "s@OUTLFNBASE@${OUTLFNBASE}@g"     "${submitfile}" 

 # submit the jobs
 if [ ${dosubmit} = true ]
 then
  python ${submitfile}
 fi

done


# end the timer
END=$(date +%s);
printf "\nStarted at ${START}\n"
printf "Ended at   ${END}\n\n"
