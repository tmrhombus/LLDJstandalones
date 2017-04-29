#voms-proxy-init --voms cms --valid 100:00

# do we submit or just generate submit scripts
dosubmit=false

# start the timer
START=$(date +%s);
printf "Started at ${START}\n\n"

# make the directory where we'll submit from
thesubdir="${subdir}/gitignore/${nversion}"
mkdir -p ${thesubdir} 
printf "Making submit configurations in\n ${thesubdir}\n\n"

# copy necessary files into submit directory
cp "${subdir}/Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt"   ${thesubdir}
cp "${subdir}/Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt"   ${thesubdir} 
cp "${subdir}/Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt" ${thesubdir}  
cp "${subdir}/Summer16_23Sep2016AllV4_DATA.db"                        ${thesubdir}     
cp "${subdir}/Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt"        ${thesubdir}
cp "${subdir}/Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt"        ${thesubdir}
cp "${subdir}/Summer16_23Sep2016V4_MC.db"                             ${thesubdir}
cp "${subdir}/run_data_80X_SingleMu.py"   ${thesubdir} 
cp "${subdir}/run_data_80X_SingleEle.py"  ${thesubdir}
cp "${subdir}/run_mc_80X.py"              ${thesubdir}

# get the DAS name mapping
thedasmap="${listdir}/ntuple/dasmap.list"

#  MC sample names
samples=( \
 "ZHHbb_1"        ) #\
# "ZHHbb_2"        \
# "ggZHHbb_1"      \
# "ggZHHbb_2"      \
# "ggZHHbb_3"      \
# "ggZHSSbbbb_01"  \
# "ggZHSSbbbb_02"  \
# "ggZHSSbbbb_03"  \
# "ggZHSSbbbb_04"  \
# "ggZHSSbbbb_05"  \
# "ggZHSSbbbb_06"  \
# "ggZHSSbbbb_07"  \
# "Data_SingleMu"  \
# "Data_SingleEle" \
#)

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
  CMSRUNCONFIG="'run_data_80X_SingleMu.py'" 
  INPUTFILES="'Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt', 'Summer16_23Sep2016AllV4_DATA.db' "
 elif [ ${samplename} == "Data_SingleEle" ]
 then
  CMSRUNCONFIG="'run_data_80X_SingleEle.py'" 
  INPUTFILES="'Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt', 'Summer16_23Sep2016AllV4_DATA.db' "
 else
  CMSRUNCONFIG="'run_mc_80X.py'" 
  INPUTFILES="'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC.db'"
 fi
 NUNITS="-1"
 UPERJOB="30"
 SPLITTING="'FileBased'"
 REQUESTNAME="'${nversion}'"
 DATASET="'${datasetname}'"
 STORESITE="'T2_US_Wisconsin'"
 OUTLFNBASE="'/store/user/tmperry/${nversion}'"
 #STORESITE="'T2_US_FNAL'"
 #OUTLFNBASE="'/eos/store/tmperry/${nversion}'"

 printf "WORKAREA      ${WORKAREA}     \n" 
 printf "CMSRUNCONFIG  ${CMSRUNCONFIG} \n" 
 printf "INPUTFILES    ${INPUTFILES}   \n" 
 printf "NUNITS        ${NUNITS}       \n" 
 printf "UPERJOB       ${UPERJOB}      \n" 
 printf "SPLITTING     ${SPLITTING}    \n" 
 printf "REQUESTNAME   ${REQUESTNAME}  \n" 
 printf "DATASET       ${DATASET}      \n" 
 printf "STORESITE     ${STORESITE}    \n" 
 printf "OUTLFNBASE    ${OUTLFNBASE}   \n" 

 # copy and then fill template for crab submits
 cp ${subdir}/crab_template.py             "${submitfile}"
 sed -i "s@WORKAREA@${WORKAREA}@g"         "${submitfile}"
 sed -i "s@CMSRUNCONFIG@${CMSRUNCONFIG}@g" "${submitfile}" 
 sed -i "s@INPUTFILES@${INPUTFILES}@g"     "${submitfile}" 
 sed -i "s@NUNITS@${NUNITS}@g"             "${submitfile}" 
 sed -i "s@UPERJOB@${UPERJOB}@g"           "${submitfile}" 
 sed -i "s@SPLITTING@${SPLITTING}@g"       "${submitfile}" 
 sed -i "s@REQUESTNAME@${REQUESTNAME}@g"   "${submitfile}" 
 sed -i "s@DATASET@${DATASET}@g"           "${submitfile}" 
 sed -i "s@STORESITE@${STORESITE}@g"       "${submitfile}" 
 sed -i "s@OUTLFNBASE@${OUTLFNBASE}@g"     "${submitfile}" 

 # submit the jobs
 if [ ${dosubmit} = true ]
 then
  pushd ${thesubdir} 
  python ${submitfile}
  popd
 fi

done


# end the timer
END=$(date +%s);
printf "\nStarted at ${START}\n"
printf "Ended at   ${END}\n\n"
