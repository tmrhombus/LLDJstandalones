#!/bin/bash

# script to generate submit files
# and optionally to submit to condor (@FNAL)

# source xx/LLDJ/setup.sh for ${aversion}

doSubmit=false
lumi=20000
nevents=-1
maxfilesperjob=300   # 500=6h

samples=(  \
 "DY50"    \
 "DY5to50" \
 "TTbar"   \
 "STs"     \
 "STtbar"  \
 "STt"     \
 "STtbarW" \
 "STtW"    \
 "WJets"   \
 "WW"      \
 "ZZ"      \
 "WZ"      \
 "ZHtoLLbb_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8"   \
 "ZHtoLLbb_ggZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8" \
 "Signal_WminusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"  \
 "Signal_WplusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"   \
 "Signal_ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"        \
 "Signal_ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8"      \
)



jets=( \
  "ALLCALOJETS"                      \
#  "ALLCALOJETSMATCHED"               \
  "BASICCALOJETS"                    \
#  "BASICCALOJETS1"                   \
#  "BASICCALOJETS1MATCHED"            \
  "BASICCALOJETS1PT20"               \
#  "BASICCALOJETS1PT20MATCHED"        \
#  "BASICCALOJETSMATCHED"             \
  "INCLUSIVETAGGEDCALOJETS"          \
#  "INCLUSIVETAGGEDCALOJETS20"        \
#  "INCLUSIVETAGGEDCALOJETS20MATCHED" \
#  "INCLUSIVETAGGEDCALOJETS60"        \
#  "INCLUSIVETAGGEDCALOJETS60MATCHED" \
#  "INCLUSIVETAGGEDCALOJETSA"         \
#  "INCLUSIVETAGGEDCALOJETSAMATCHED"  \
#  "INCLUSIVETAGGEDCALOJETSB"         \
#  "INCLUSIVETAGGEDCALOJETSBMATCHED"  \
#  "INCLUSIVETAGGEDCALOJETSC"         \
#  "INCLUSIVETAGGEDCALOJETSCMATCHED"  \
#  "INCLUSIVETAGGEDCALOJETSD"         \
#  "INCLUSIVETAGGEDCALOJETSDMATCHED"  \
#  "INCLUSIVETAGGEDCALOJETSE"         \
#  "INCLUSIVETAGGEDCALOJETSEMATCHED"  \
#  "INCLUSIVETAGGEDCALOJETSF"         \
#  "INCLUSIVETAGGEDCALOJETSFMATCHED"  \
#  "INCLUSIVETAGGEDCALOJETSMATCHED"   \
)

printf "Version: ${aversion}\n"

# tar up your present CMSSW area
if [ ! -f ${CMSSW_VERSION}.tar.gz ] 
then 
 printf "I think I need to tar, can't find ${CMSSW_VERSION}.tar.gz \n\n"
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
 printf "Transfer_Input_Files = \$ENV(CMSSW_BASE)/src/LLDJstandalones/submitters/CMSSW_8_0_18_patch1.tar.gz,\$ENV(CMSSW_BASE)/src/LLDJstandalones/analyzers/runanalyzer.exe,\$ENV(CMSSW_BASE)/src/LLDJstandalones/lists/$1.list,\$ENV(CMSSW_BASE)/src/LLDJstandalones/lists/$1.info\n" >> submitfile
 printf "notify_user = $(whoami)@cern.ch\n" >> submitfile
 printf "x509userproxy = \$ENV(X509_USER_PROXY)\n" >> submitfile
 printf "\n" >> submitfile
 printf "Output = logs/runanalyzer_\$(Cluster)_\$(Process).stdout\n" >> submitfile
 printf "Error  = logs/runanalyzer_\$(Cluster)_\$(Process).stderr\n" >> submitfile
 printf "Log    = logs/runanalyzer_\$(Cluster)_\$(Process).log\n" >> submitfile
 printf "\n" >> submitfile
 
 # make haddfile
 haddfile="./haddit.sh"
 hadddir="${rootdir}/${aversion}"
 mkdir -p ${hadddir}
 printf "#!/bin/bash\n\n" > ${haddfile}

 # make checker
 checkfile="./checker.sh"
 printf "#!/bin/bash\n\n" > ${checkfile}

 # choose your favorite jet collections to run over
 for jettype in ${jets[@]}
 do
  printf " ${jettype} \n"

  # start hadd command
  printf "hadd ${hadddir}/$1_${jettype}.root " >> ${haddfile}

  # breaking up input file list
  nfilesinlist=$( wc -l < "${CMSSW_BASE}/src/LLDJstandalones/lists/$1.list" )
  filenrlow=0
  jobfilenr=0
 
  until [ ${filenrlow} -gt ${nfilesinlist} ]
  do

   printf "Arguments = \$ENV(CMSSW_VERSION) $1 ${lumi} ${nevents} ${jettype} ${maxfilesperjob} ${filenrlow} _${jobfilenr}\n" >> submitfile
   printf "Queue\n" >> submitfile
   printf "\n" >> submitfile

   # add file to hadd
   printf "\\" >> ${haddfile}
   printf "\n $(pwd)/$1_${jettype}_${jobfilenr}.root " >> ${haddfile}

   # add file to checker
   printf "\n if [ ! -f $(pwd)/$1_${jettype}_${jobfilenr}.root ]; then printf \" $(pwd)/$1_${jettype}_${jobfilenr}.root \\n\"; fi " >> ${checkfile}

   # increment filenumber counters
   #printf "NFILES: %s %s %s\n" $nfilesinlist $filenrlow $jobfilenr
   filenrlow=$(( ${filenrlow} + ${maxfilesperjob} ))
   jobfilenr=$(( ${jobfilenr} + 1 ))

  done # until filenrlow > nfilesinlist
  printf "\n\n" >> ${haddfile}
 done # for jettype in jets

 if [ ${doSubmit} = true ]
 then
  condor_submit submitfile
 fi
 
 popd > /dev/null
}


# actuall call the function
for sample in ${samples[@]} 
do
 makeasubmitdir ${sample}
done

