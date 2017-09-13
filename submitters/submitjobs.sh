#!/bin/bash

# script to generate submit files
# and optionally to submit to condor (@UW)

# source xx/LLDJ/setup.sh for ${aversion}

doSubmit=true
lumi=35870
nevents=-1
maxfilesperjob=200   # 500=6h


samples=(  \
 "ggZH_HToSSTobbbb_MS40_ctauS0"       \
 "ggZH_HToSSTobbbb_MS40_ctauS0p05"    \
 "ggZH_HToSSTobbbb_MS40_ctauS1"       \
 "ggZH_HToSSTobbbb_MS40_ctauS10"      \
 "ggZH_HToSSTobbbb_MS40_ctauS100"     \
 "ggZH_HToSSTobbbb_MS40_ctauS1000"    \
 "ggZH_HToSSTobbbb_MS40_ctauS10000"   \
 "SingleElectron"                     \
 "SingleMuon"                         \
 "DY5to50_HT70To100"                  \
 "DY5to50_HT100To200"                 \
 "DY5to50_HT200To400"                 \
 "DY5to50_HT400To600"                 \
 "DY5to50_HT600ToInf"                 \
 "DY50"                               \
 "ggZH_HToBB_ZToLL"                   \
 "GJets_HT40To100"                    \
 "GJets_HT100To200"                   \
 "GJets_HT200To400"                   \
 "GJets_HT400To600"                   \
 "GJets_HT600ToInf"                   \
 "ST_s"                               \
 "STbar_t"                            \
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
 "ZH_HToBB_ZToLL"                     \
 "ZZToLLNuNu"                         \
 "ZZToLLQQ"                           \
 "ZZToNuNuQQ"                         \
 "ZZToLLLL"                           \
)


printf "Version: ${aversion}\n"

# tar up your present CMSSW area
if [ ! -f ${CMSSW_VERSION}.tar.gz ] 
then 
 printf "I think I need to tar, couldn't find ${CMSSW_VERSION}.tar.gz \n\n"
 tar --exclude-caches-all --exclude-vcs -zcf ${CMSSW_VERSION}.tar.gz -C ${CMSSW_BASE}/.. ${CMSSW_BASE} --exclude=src --exclude=tmp
fi

makeasubmitdir () {
 printf "Making submits for $1\n"
 
 # go to the directory
 submitdir=/nfs_scratch/tperry/gitignore/${aversion}/$1
 mkdir -p ${submitdir} 
 pushd    ${submitdir}  > /dev/null
 ##mkdir -p gitignore/${aversion}/$1
 ##pushd    gitignore/${aversion}/$1 > /dev/null
 #printf " The directory is %s\n" $(pwd)
 
 mkdir -p logs
 
 # write base for submit file
 printf "universe = vanilla\n" > submitfile
 printf "Executable = ${CMSSW_BASE}/src/LLDJstandalones/submitters/runjob.sh\n" >> submitfile
 printf "Should_Transfer_Files = YES \n" >> submitfile
 printf "WhenToTransferOutput = ON_EXIT\n" >> submitfile
 printf "Transfer_Input_Files = ${CMSSW_BASE}/src/LLDJstandalones/submitters/${CMSSW_VERSION}.tar.gz,${CMSSW_BASE}/src/LLDJstandalones/analyzers/runanalyzer.exe,${CMSSW_BASE}/src/LLDJstandalones/lists/$1.list,${CMSSW_BASE}/src/LLDJstandalones/lists/$1.info,${CMSSW_BASE}/src/LLDJstandalones/analyzers/puWeights_69200_24jan2017.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/egammaEffi_MoriondBH_eleTight.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/egammaEffi_MoriondBH_eleMedium.root,${CMSSW_BASE}/src/LLDJstandalones/analyzers/egammaEffi_MoriondBH_eleLoose.root\n" >> submitfile

 printf "notify_user = $(whoami)@cern.ch\n" >> submitfile
 printf "x509userproxy = $X509_USER_PROXY\n" >> submitfile
 printf "requirements = TARGET.HAS_CMS_HDFS" >> submitfile
 #printf 'requirements =  TARGET.Arch == "X86_64" && (MY.RequiresSharedFS=!=true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN=?=true) && IsSlowSlot=!=true  && (TARGET.HasParrotCVMFS=?=true || TARGET.CMS_CVMFS_Exists) && TARGET.HAS_CMS_HDFS"' >> submitfile
 #printf 'requirements =  TARGET.Arch == "X86_64" && (MY.RequiresSharedFS=!=true || TARGET.HasAFS_OSG) && (TARGET.OSG_major =!= undefined || TARGET.IS_GLIDEIN=?=true) && IsSlowSlot=!=true  && (TARGET.HasParrotCVMFS=?=true || (TARGET.UWCMS_CVMFS_Exists  && TARGET.CMS_CVMFS_Exists) && TARGET.HAS_CMS_HDFS"' >> submitfile
 printf "\n" >> submitfile
 printf "Output = logs/runanalyzer_\$(Cluster)_\$(Process).stdout\n" >> submitfile
 printf "Error  = logs/runanalyzer_\$(Cluster)_\$(Process).stderr\n" >> submitfile
 printf "Log    = logs/runanalyzer_\$(Cluster)_\$(Process).log\n" >> submitfile
 printf "\n" >> submitfile
 
 # make haddfile (make now for merging expected results)
 haddfile="./haddit.sh"
 hadddir="${rootdir}/${aversion}"
 mkdir -p ${hadddir}
 printf "#!/bin/bash\n\n" > ${haddfile}

 # make checker
 checkfile="./checker.sh"
 printf "#!/bin/bash\n\n" > ${checkfile}


  # hadd command to go in haddfile
  printf "hadd ${hadddir}/$1.root " >> ${haddfile}

  # breaking up input file list
  nfilesinlist=$( wc -l < "${CMSSW_BASE}/src/LLDJstandalones/lists/$1.list" )
  filenrlow=0
  jobfilenr=0
 
  until [ ${filenrlow} -gt ${nfilesinlist} ]
  do

   printf "Arguments = \$ENV(CMSSW_VERSION) $1 ${lumi} ${nevents} ${maxfilesperjob} ${filenrlow} _${jobfilenr} $2 \n" >> submitfile
   printf "Queue\n" >> submitfile
   printf "\n" >> submitfile

   # add file to hadd
   printf "\\" >> ${haddfile}
   printf "\n $(pwd)/$1_${jobfilenr}.root " >> ${haddfile}

   # add file to checker
   printf "\n if [ ! -f $(pwd)/$1_${jobfilenr}.root ]; then printf \" $(pwd)/$1_${jobfilenr}.root \\n\"; fi " >> ${checkfile}

   # increment filenumber counters
   #printf "NFILES: %s %s %s\n" $nfilesinlist $filenrlow $jobfilenr
   filenrlow=$(( ${filenrlow} + ${maxfilesperjob} ))
   jobfilenr=$(( ${jobfilenr} + 1 ))

  done # until filenrlow > nfilesinlist
  printf "\n\n" >> ${haddfile}

 if [ ${doSubmit} = true ]
 then
  condor_submit submitfile
 fi
 
 popd > /dev/null
}


# actuall call the function
for sample in ${samples[@]} 
do
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

