#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"
 
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

countalist () {
 if [ $1 = true ]
 then
  printf "Making %s\n" $2
  root -l -b -q 'countevents.cxx("'$2'")'
  printf "crosssection: %s\n" $3 >> ${listdir}/$2.info
 fi
}

countmanylists () {
 if [ $1 = true ]
 then
  printf "Making %s\n" $2
  for fullsample in $(ls ${listdir}/$2*list)
  do

   sample=$( printf "%s" ${fullsample} | sed -e 's/.*'$2'/'$2'/' | sed -e 's/\.list//' )
   #printf "Sample is %s\n" ${sample}

   root -l -b -q 'countevents.cxx("'${sample}'")'
   printf "crosssection: %s\n" $3 >> ${listdir}/${sample}.info
  done # for sample in Signal*txt

 fi
}

countalist ${doDY50}      "DY50"       ${xcDY50}     
countalist ${doDY5to50}   "DY5to50"    ${xcDY5to50}  
countalist ${doTTbar}     "TTbar"      ${xcTTbar}    
countalist ${doSTs}       "STs"        ${xcSTs}      
countalist ${doSTtbar}    "STtbar"     ${xcSTtbar}   
countalist ${doSTt}       "STt"        ${xcSTt}      
countalist ${doSTtbarW}   "STtbarW"    ${xcSTtbarW}  
countalist ${doSTtW}      "STtW"       ${xcSTtW}     
countalist ${doWJets}     "WJets"      ${xcWJets}    
countalist ${doZHtoLLbb}  "ZHtoLLbb"   ${xcZHtoLLbb} 
countalist ${doWW}        "WW"         ${xcWW}       
countalist ${doZZ}        "ZZ"         ${xcZZ}       
countalist ${doWZ}        "WZ"         ${xcWZ}       

countmanylists ${doSignal} "Signal" ${xcSignal}

