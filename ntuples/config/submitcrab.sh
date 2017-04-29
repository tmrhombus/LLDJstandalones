#voms-proxy-init --voms cms --valid 100:00

domc=false
dodata=false
dosubmit=false

# start the timer
START=$(date +%s);
printf "Started at `date`\n\n"

# make the directory where we'll submit from
thesubdir="${subdir}/gitignore/${nversion}"
mkdir -p ${thesubdir} 
printf "Making submit configurations in\n ${thesubdir}\n\n"

# get the DAS name mapping
thedasmap="${listdir}/ntuple/dasmap.list"

#lumi=40000. # /pb
lumi=12900. # /pb

#  MC sample names
mcsamples=( \
 "ZHHbb_1"       \
 "ZHHbb_2"       \
 "ggZHHbb_1"     \
 "ggZHHbb_2"     \
 "ggZHHbb_3"     \
 "ggZHSSbbbb_01" \
 "ggZHSSbbbb_02" \
 "ggZHSSbbbb_03" \
 "ggZHSSbbbb_04" \
 "ggZHSSbbbb_05" \
 "ggZHSSbbbb_06" \
 "ggZHSSbbbb_07" \
)

# print which samples we're running over
printf "For:\n"
for samplename in ${mcsamples[@]}
do
 printf " ${samplename}\n"
done

# loop over mc samples
for samplename in ${mcsamples[@]}
do
 printf "\n******************************************************\n"
 if [ ${dosubmit} = true ]
 then
 printf "** \n"
  printf "** --- SUBMITTING --- \n"
 fi
 printf "** \n"
 printf "** Sample: ${samplename} \n"
 printf "******************************************************\n"
 printf "******************************************************\n\n"

 datasetname="$(grep -P ${samplename} ${thedasmap} | sed -n -e "s@ ${samplename}    @@p")"

 submitname="submit_${samplename}"
 submitfile="${thesubdir}/${submitname}.py"

 # set veriables for submitting this specific sample
 WORKAREA="'crab_projects_ntuples'"
 CMSRUNCONFIG="'run_mc_80x.py'" 
 INPUTFILES="'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC.db'"
 NUNITS="'-1'"
 REQUESTNAME="'job_spring_ZZ'"
 DATASET="'${datasetname}'"
 OUTLFNBASE="'/eos/store/tmperry/${nversion}'"

 printf "WORKAREA      ${WORKAREA}    \n" 
 printf "CMSRUNCONFIG  ${CMSRUNCONFIG} \n" 
 printf "INPUTFILES    ${INPUTFILES}   \n" 
 printf "NUNITS        ${NUNITS}       \n" 
 printf "REQUESTNAME   ${REQUESTNAME}  \n" 
 printf "DATASET       ${DATASET}      \n" 
 printf "OUTLFNBASE    ${OUTLFNBASE}   \n" 

 # copy and then fill template for crab submits
 cp ${subdir}/crab_template.py             "${submitfile}"
 sed -i "s@WORKAREA@${WORKAREA}@g"         "${submitfile}"
 sed -i "s@CMSRUNCONFIG@${CMSRUNCONFIG}@g" "${submitfile}" 
 sed -i "s@INPUTFILES@${INPUTFILES}@g"     "${submitfile}" 
 sed -i "s@NUNITS@${NUNITS}@g"             "${submitfile}" 
 sed -i "s@REQUESTNAME@${REQUESTNAME}@g"   "${submitfile}" 
 sed -i "s@DATASET@${DATASET}@g"           "${submitfile}" 
 sed -i "s@OUTLFNBASE@${OUTLFNBASE}@g"     "${submitfile}" 

 # submit the jobs
 if [ ${dosubmit} = true ]
 then
  python ${submitfile}
 fi

done



