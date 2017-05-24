#!/bin/bash

# script to generate submit files
# and optionally to submit to condor (@FNAL)

# source xx/LLDJ/setup.sh for ${aversion}

doSubmit=true
lumi=35870
nevents=-1
maxfilesperjob=300   # 500=6h

samples=(  \
 'DY50'                              \
 'DY5to50_HT100to200'                \
 'DY5to50_HT200to400'                \
 'DY5to50_HT400to600'                \
 'DY5to50_HT600toInf'                \
 'DY5to50_HT70to100'                 \
 'GJets_HT40To100'                   \
 'GJets_HT100To200'                  \
 'GJets_HT200To400'                  \
 'GJets_HT400To600'                  \
 'GJets_HT600ToInf'                  \
 'ST_s'                              \
 'STbar_t'                           \
 'ST_t'                              \
 'STbar_tW'                          \
 'ST_tW'                             \
 'TTJets'                            \
 'WW'                                \
 'WZ'                                \
 'ZZ'                                \
 'ZH_HToBB_ZToLL'                    \
 'ggZH_HToBB_ZToLL'                  \
 'ggZH_HToSSTobbbb_MS40_ctauS100'    \
 'ggZH_HToSSTodddd_MS40_ctauS100'    \
 'WJetsToLNu'                        \
 'SingleElectron'     \
 'SingleMuon'

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
 mkdir -p gitignore/${aversion}/$1
 pushd    gitignore/${aversion}/$1 > /dev/null
 #printf " The directory is %s\n" $(pwd)
 
 mkdir -p logs
 
 # write base for submit file
 printf "universe = vanilla\n" > submitfile
 printf "Executable = \$ENV(CMSSW_BASE)/src/LLDJstandalones/submitters/runjob.sh\n" >> submitfile
 printf "Should_Transfer_Files = YES \n" >> submitfile
 printf "WhenToTransferOutput = ON_EXIT\n" >> submitfile
 printf "Transfer_Input_Files = \$ENV(CMSSW_BASE)/src/LLDJstandalones/submitters/${CMSSW_VERSION}.tar.gz,\$ENV(CMSSW_BASE)/src/LLDJstandalones/analyzers/runanalyzer.exe,\$ENV(CMSSW_BASE)/src/LLDJstandalones/lists/$1.list,\$ENV(CMSSW_BASE)/src/LLDJstandalones/lists/$1.info\n" >> submitfile
 printf "notify_user = $(whoami)@cern.ch\n" >> submitfile
 printf "x509userproxy = \$ENV(X509_USER_PROXY)\n" >> submitfile
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
 else
  mc="-m"
 fi
 makeasubmitdir ${sample} ${mc}
done

