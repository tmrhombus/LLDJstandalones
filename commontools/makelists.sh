#!/bin/bash


outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"
mkdir -p "${outdir}"
 
eos root://cmseos.fnal.gov ls /store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHistos/ > ${outdir}/allfiles.txt
 
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
 printf "crosssection: %s\n" ${xcDY50} > ${outdir}/DY50.txt
 grep -i 'DYJetsToLL_M-50' ${outdir}/allfiles.txt  >> ${outdir}/DY50.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/DY50.txt
fi

if [ ${doDY5to50} = true ]
then
 printf "Making DY5to50\n" 
 printf "crosssection: %s\n" ${xcDY5to50} > ${outdir}/DY5to50.txt
 grep -i 'DYJetsToLL_M-5to50' ${outdir}/allfiles.txt  >> ${outdir}/DY5to50.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/DY5to50.txt
fi

if [ ${doTTbar} = true ]
then
 printf "Making TTbar\n" 
 printf "crosssection: %s\n" ${xcTTbar} > ${outdir}/TTbar.txt
 grep -i 'TT_TuneCUETP8M1' ${outdir}/allfiles.txt  >> ${outdir}/TTbar.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/TTbar.txt
fi

if [ ${doSTs} = true ]
then
 printf "Making STs\n" 
 printf "crosssection: %s\n" ${xcSTs} > ${outdir}/STs.txt
 grep -i 'ST_s-channel_4f' ${outdir}/allfiles.txt  >> ${outdir}/STs.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/STs.txt
fi

if [ ${doSTtbar} = true ]
then
 printf "Making STtbar\n" 
 printf "crosssection: %s\n" ${xcSTtbar} > ${outdir}/STtbar.txt
 grep -i 'ST_t-channel_antitop_4f' ${outdir}/allfiles.txt  >> ${outdir}/STtbar.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/STtbar.txt
fi

if [ ${doSTt} = true ]
then
 printf "Making STt\n" 
 printf "crosssection: %s\n" ${xcSTt} > ${outdir}/STt.txt
 grep -i 'ST_t-channel_top_4f' ${outdir}/allfiles.txt  >> ${outdir}/STt.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/STt.txt
fi

if [ ${doSTtbarW} = true ]
then
 printf "Making STtbarW\n" 
 printf "crosssection: %s\n" ${xcSTtbarW} > ${outdir}/STtbarW.txt
 grep -i 'ST_tW_antitop_5f' ${outdir}/allfiles.txt  >> ${outdir}/STtbarW.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/STtbarW.txt
fi

if [ ${doSTtW} = true ]
then
 printf "Making STtW\n" 
 printf "crosssection: %s\n" ${xcSTtW} > ${outdir}/STtW.txt
 grep -i 'ST_tW_top_5f' ${outdir}/allfiles.txt  >> ${outdir}/STtW.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/STtW.txt
fi

if [ ${doWJets} = true ]
then
 printf "Making WJets\n" 
 printf "crosssection: %s\n" ${xcWJets} > ${outdir}/WJets.txt
 grep -i 'WJetsToLNu' ${outdir}/allfiles.txt  >> ${outdir}/WJets.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/WJets.txt
fi

if [ ${doZHtoLLbb} = true ]
then
 printf "Making ZHtoLLbb\n" 
 printf "crosssection: %s\n" ${xcZHtoLLbb} > ${outdir}/ZHtoLLbb.txt
 grep -i 'ZH_HToBB_ZToLL_M125' ${outdir}/allfiles.txt  >> ${outdir}/ZHtoLLbb.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/ZHtoLLbb.txt
fi

if [ ${doWW} = true ]
then
 printf "Making WW\n" 
 printf "crosssection: %s\n" ${xcWW} > ${outdir}/WW.txt
 grep -i 'WW_TuneCUETP8M1' ${outdir}/allfiles.txt  >> ${outdir}/WW.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/WW.txt
fi

if [ ${doZZ} = true ]
then
 printf "Making ZZ\n" 
 printf "crosssection: %s\n" ${xcZZ} > ${outdir}/ZZ.txt
 grep -i 'ZZ_TuneCUETP8M1' ${outdir}/allfiles.txt  >> ${outdir}/ZZ.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/ZZ.txt
fi

if [ ${doWZ} = true ]
then
 printf "Making WZ\n" 
 printf "crosssection: %s\n" ${xcWZ} > ${outdir}/WZ.txt
 grep -i 'WZ_TuneCUETP8M1' ${outdir}/allfiles.txt  >> ${outdir}/WZ.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/WZ.txt
fi

if [ ${doSignal} = true ]
then
 printf "Making Signal\n" 
 printf "crosssection: %s\n" ${xcSignal} > ${outdir}/Signal.txt
 grep -i 'ggZH_HToSSTobbbb' ${outdir}/allfiles.txt  >> ${outdir}/Signal.txt
 sed -i -e 's@allHistos@/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHisto@' ${outdir}/Signal.txt
fi


