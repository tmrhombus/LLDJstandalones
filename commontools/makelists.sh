#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"
mkdir -p "${outdir}"

initpath="/store/group/lpchbb/kreis/AnalysisTrees"
eos root://cmseos.fnal.gov ls ${initpath} > ${outdir}/allfiles.txt
 
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

xcDY50="6025.0"                   
xcDY5to50="7160.0"                      
xcTTbar="831.76"                    
xcSTs="10.11"                   
xcSTtbar="26.23"                      
xcSTt="44.09"                   
xcSTtbarW="38.09"                       
xcSTtW="38.09"                    
xcWJets="61467.0"                   
xcZHtoLLbb="0.051"   #0.8696*0.577*0.102           
xcWW="10.32"                  
xcZZ="63.0"                   
xcWZ="118.7"                  
xcSignal="1"         

if [ ${doDY50} = true ]
then
 printf "Making DY50\n" 
 fullsamplename=$(grep -i 'DYJetsToLL_M-50_Tune' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/DY50.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/DY50.txt
fi

if [ ${doDY5to50} = true ]
then
 printf "Making DY5to50\n" 
 fullsamplename=$(grep -i 'DYJetsToLL_M-5to50' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/DY5to50.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/DY5to50.txt
fi

if [ ${doTTbar} = true ]
then
 printf "Making TTbar\n" 
 fullsamplename=$(grep -i 'TT_TuneCUETP8M1' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/TTbar.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/TTbar.txt
fi

if [ ${doSTs} = true ]
then
 printf "Making STs\n" 
 fullsamplename=$(grep -i 'ST_s-channel_4f' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/STs.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/STs.txt
fi

if [ ${doSTtbar} = true ]
then
 printf "Making STtbar\n" 
 fullsamplename=$(grep -i 'ST_t-channel_antitop_4f' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/STtbar.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/STtbar.txt
fi

if [ ${doSTt} = true ]
then
 printf "Making STt\n" 
 fullsamplename=$(grep -i 'ST_t-channel_top_4f' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/STt.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/STt.txt
fi

if [ ${doSTtbarW} = true ]
then
 printf "Making STtbarW\n" 
 fullsamplename=$(grep -i 'ST_tW_antitop_5f' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/STtbarW.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/STtbarW.txt
fi

if [ ${doSTtW} = true ]
then
 printf "Making STtW\n" 
 fullsamplename=$(grep -i 'ST_tW_top_5f' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/STtW.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/STtW.txt
fi

if [ ${doWJets} = true ]
then
 printf "Making WJets\n" 
 fullsamplename=$(grep -i 'WJetsToLNu' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/WJets.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/WJets.txt
fi

if [ ${doZHtoLLbb} = true ]
then
 printf "Making ZHtoLLbb\n" 
 fullsamplename=$(grep -i 'ZH_HToBB_ZToLL' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 for sample in ${fullsamplename}
 do
  printf "%s/%s\n" ${initpath} ${sample}
  eos root://cmseos.fnal.gov ls ${initpath}/${sample} > ${outdir}/${sample}.txt
  sed -i -e "s@histo_@${initpath}/${sample}/histo_@" ${outdir}/${sample}.txt
 done
fi

if [ ${doWW} = true ]
then
 printf "Making WW\n" 
 fullsamplename=$(grep -i 'WW_TuneCUETP8M1' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/WW.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/WW.txt
fi

if [ ${doZZ} = true ]
then
 printf "Making ZZ\n" 
 fullsamplename=$(grep -i 'ZZ_TuneCUETP8M1' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/ZZ.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/ZZ.txt
fi

if [ ${doWZ} = true ]
then
 printf "Making WZ\n" 
 fullsamplename=$(grep -i 'WZ_TuneCUETP8M1' ${outdir}/allfiles.txt)
 printf "%s/%s\n" ${initpath} ${fullsamplename}
 eos root://cmseos.fnal.gov ls ${initpath}/${fullsamplename} > ${outdir}/WZ.txt
 sed -i -e "s@histo_@${initpath}/${fullsamplename}/histo_@" ${outdir}/WZ.txt
fi

if [ ${doSignal} = true ]
then
 printf "Making Signal\n" 
 fullsamplename=$(grep -i 'HToSSTobbbb' ${outdir}/allfiles.txt)
 for sample in ${fullsamplename}
 do
  printf "%s/%s\n" ${initpath} ${sample}
  eos root://cmseos.fnal.gov ls ${initpath}/${sample} > ${outdir}/Signal_${sample}.txt
  sed -i -e "s@histo_@${initpath}/${sample}/histo_@" ${outdir}/Signal_${sample}.txt
 done
fi


