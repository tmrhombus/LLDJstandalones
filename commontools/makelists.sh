#!/bin/bash

# Makes a list of files in eos
# then greps through to separate into samples
# 
# output files are xxx/lists/<sample>.list
# formatted as one file per line: /store/group/xxx.root

# don't forget to source setup.sh (from xxx/LLDJstandalones)
mkdir -p "${listdir}"

initpath="/store/group/lpchbb/kreis/AnalysisTrees"
eos root://cmseos.fnal.gov ls ${initpath} > ${listdir}/allfiles.list
 
doDY50=true
doDY5to50=true
doTTbar=true
doSTs=true
doSTtbar=true
doSTt=true
doSTtbarW=true
doSTtW=true
doWJets=true
doZHtoLLbb=true
doWW=true
doZZ=true
doWZ=true
doSignal=true

makealist () {
 if [ $1 = true ]
 then
  printf "Making %s\n" $2
  fullsamplename=$(grep -i $3 ${listdir}/allfiles.list)
  printf "%s/%s\n" ${initpath} ${fullsamplename}
  eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${listdir}/$2.list
  sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${listdir}/$2.list
 fi
}

makemanylists () {
if [ $1 = true ]
then
 printf "Making %s\n" $2
 fullsamplename=$(grep -i $3 ${listdir}/allfiles.list)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 for sample in ${fullsamplename}
 do
  printf "%s/%s\n" ${initpath} ${sample}
  eos root://cmseos.fnal.gov ls ${initpath}/${sample} > ${listdir}/$2_${sample}.list
  sed -i -e "s@histo_@${initpath}/${sample}/histo_@" ${listdir}/$2_${sample}.list
 done
fi
}

makealist ${doDY50}     "DY50"     "DYJetsToLL_M-50_Tune"
makealist ${doDY5to50}  "DY5to50"  "DYJetsToLL_M-5to50"       
makealist ${doTTbar}    "TTbar"    "TT_TuneCUETP8M1"
makealist ${doSTs}      "STs"      "ST_s-channel_4f"          
makealist ${doSTtbar}   "STtbar"   "ST_t-channel_antitop_4f"  
makealist ${doSTt}      "STt"      "ST_t-channel_top_4f"      
makealist ${doSTtbarW}  "STtbarW"  "ST_tW_antitop_5f"         
makealist ${doSTtW}     "STtW"     "ST_tW_top_5f"             
makealist ${doWJets}    "WJets"    "WJetsToLNu"               
makealist ${doWW}       "WW"       "WW_TuneCUETP8M1"          
makealist ${doZZ}       "ZZ"       "ZZ_TuneCUETP8M1"          
makealist ${doWZ}       "WZ"       "WZ_TuneCUETP8M1"          

makemanylists ${doZHtoLLbb} "ZHtoLLbb" "ZH_HToBB_ZToLL" 
makemanylists ${doSignal}   "Signal"   "HToSSTobbbb" 

