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

if [ ${doDY50} = true ]
then
 printf "Making DY50\n" 
 printf "crosssection: %s\n" ${xcDY50} >> ${outdir}/DY50.txt
 root -l -b -q countevents.cxx\('"DY50.txt"'\)
fi

if [ ${doDY5to50} = true ]
then
 printf "Making DY5to50\n" 
 printf "crosssection: %s\n" ${xcDY5to50} >> ${outdir}/DY5to50.txt
 root -l -b -q countevents.cxx\('"DY5to50.txt"'\)
fi

if [ ${doTTbar} = true ]
then
 printf "Making TTbar\n" 
 printf "crosssection: %s\n" ${xcTTbar} >> ${outdir}/TTbar.txt
 root -l -b -q countevents.cxx\('"TTbar.txt"'\)
fi

if [ ${doSTs} = true ]
then
 printf "Making STs\n" 
 printf "crosssection: %s\n" ${xcSTs} >> ${outdir}/STs.txt
 root -l -b -q countevents.cxx\('"STs.txt"'\)
fi

if [ ${doSTtbar} = true ]
then
 printf "Making STtbar\n" 
 printf "crosssection: %s\n" ${xcSTtbar} >> ${outdir}/STtbar.txt
 root -l -b -q countevents.cxx\('"STtbar.txt"'\)
fi

if [ ${doSTt} = true ]
then
 printf "Making STt\n" 
 printf "crosssection: %s\n" ${xcSTt} >> ${outdir}/STt.txt
 root -l -b -q countevents.cxx\('"STt.txt"'\)
fi

if [ ${doSTtbarW} = true ]
then
 printf "Making STtbarW\n" 
 printf "crosssection: %s\n" ${xcSTtbarW} >> ${outdir}/STtbarW.txt
 root -l -b -q countevents.cxx\('"STtbarW.txt"'\)
fi

if [ ${doSTtW} = true ]
then
 printf "Making STtW\n" 
 printf "crosssection: %s\n" ${xcSTtW} >> ${outdir}/STtW.txt
 root -l -b -q countevents.cxx\('"STtW.txt"'\)
fi

if [ ${doWJets} = true ]
then
 printf "Making WJets\n" 
 printf "crosssection: %s\n" ${xcWJets} >> ${outdir}/WJets.txt
 root -l -b -q countevents.cxx\('"WJets.txt"'\)
fi

if [ ${doZHtoLLbb} = true ]
then
 printf "Making ZHtoLLbb\n" 
 printf "crosssection: %s\n" ${xcZHtoLLbb} >> ${outdir}/ZHtoLLbb.txt
 root -l -b -q countevents.cxx\('"ZHtoLLbb.txt"'\)
fi

if [ ${doWW} = true ]
then
 printf "Making WW\n" 
 printf "crosssection: %s\n" ${xcWW} >> ${outdir}/WW.txt
 root -l -b -q countevents.cxx\('"WW.txt"'\)
fi

if [ ${doZZ} = true ]
then
 printf "Making ZZ\n" 
 printf "crosssection: %s\n" ${xcZZ} >> ${outdir}/ZZ.txt
 root -l -b -q countevents.cxx\('"ZZ.txt"'\)
fi

if [ ${doWZ} = true ]
then
 printf "Making WZ\n" 
 printf "crosssection: %s\n" ${xcWZ} >> ${outdir}/WZ.txt
 root -l -b -q countevents.cxx\('"WZ.txt"'\)
fi

if [ ${doSignal} = true ]
then
 printf "Making Signal\n" 
 printf "crosssection: %s\n" ${xcSignal} >> ${outdir}/Signal.txt
 root -l -b -q countevents.cxx\('"Signal.txt"'\)
fi

