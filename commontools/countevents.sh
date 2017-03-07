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
 grep -v "crosssection" ${outdir}/DY50.txt > temp && mv temp ${outdir}/DY50.txt 
 grep -v "nrevents" ${outdir}/DY50.txt > temp && mv temp ${outdir}/DY50.txt 
 printf "crosssection: %s\n" ${xcDY50} >> ${outdir}/DY50.txt
 root -l -b -q countevents.cxx\('"DY50.txt"'\)
fi

if [ ${doDY5to50} = true ]
then
 printf "Making DY5to50\n" 
 grep -v "crosssection" ${outdir}/DY5to50.txt > temp && mv temp ${outdir}/DY5to50.txt 
 grep -v "nrevents" ${outdir}/DY5to50.txt > temp && mv temp ${outdir}/DY5to50.txt 
 printf "crosssection: %s\n" ${xcDY5to50} >> ${outdir}/DY5to50.txt
 root -l -b -q countevents.cxx\('"DY5to50.txt"'\)
fi

if [ ${doTTbar} = true ]
then
 printf "Making TTbar\n" 
 grep -v "crosssection" ${outdir}/TTbar.txt > temp && mv temp ${outdir}/TTbar.txt 
 grep -v "nrevents" ${outdir}/TTbar.txt > temp && mv temp ${outdir}/TTbar.txt 
 printf "crosssection: %s\n" ${xcTTbar} >> ${outdir}/TTbar.txt
 root -l -b -q countevents.cxx\('"TTbar.txt"'\)
fi

if [ ${doSTs} = true ]
then
 printf "Making STs\n" 
 grep -v "crosssection" ${outdir}/STs.txt > temp && mv temp ${outdir}/STs.txt 
 grep -v "nrevents" ${outdir}/STs.txt > temp && mv temp ${outdir}/STs.txt 
 printf "crosssection: %s\n" ${xcSTs} >> ${outdir}/STs.txt
 root -l -b -q countevents.cxx\('"STs.txt"'\)
fi

if [ ${doSTtbar} = true ]
then
 printf "Making STtbar\n" 
 grep -v "crosssection" ${outdir}/STtbar.txt > temp && mv temp ${outdir}/STtbar.txt 
 grep -v "nrevents" ${outdir}/STtbar.txt > temp && mv temp ${outdir}/STtbar.txt 
 printf "crosssection: %s\n" ${xcSTtbar} >> ${outdir}/STtbar.txt
 root -l -b -q countevents.cxx\('"STtbar.txt"'\)
fi

if [ ${doSTt} = true ]
then
 printf "Making STt\n" 
 grep -v "crosssection" ${outdir}/STt.txt > temp && mv temp ${outdir}/STt.txt 
 grep -v "nrevents" ${outdir}/STt.txt > temp && mv temp ${outdir}/STt.txt 
 printf "crosssection: %s\n" ${xcSTt} >> ${outdir}/STt.txt
 root -l -b -q countevents.cxx\('"STt.txt"'\)
fi

if [ ${doSTtbarW} = true ]
then
 printf "Making STtbarW\n" 
 grep -v "crosssection" ${outdir}/STtbarW.txt > temp && mv temp ${outdir}/STtbarW.txt 
 grep -v "nrevents" ${outdir}/STtbarW.txt > temp && mv temp ${outdir}/STtbarW.txt 
 printf "crosssection: %s\n" ${xcSTtbarW} >> ${outdir}/STtbarW.txt
 root -l -b -q countevents.cxx\('"STtbarW.txt"'\)
fi

if [ ${doSTtW} = true ]
then
 printf "Making STtW\n" 
 grep -v "crosssection" ${outdir}/STtW.txt > temp && mv temp ${outdir}/STtW.txt 
 grep -v "nrevents" ${outdir}/STtW.txt > temp && mv temp ${outdir}/STtW.txt 
 printf "crosssection: %s\n" ${xcSTtW} >> ${outdir}/STtW.txt
 root -l -b -q countevents.cxx\('"STtW.txt"'\)
fi

if [ ${doWJets} = true ]
then
 printf "Making WJets\n" 
 grep -v "crosssection" ${outdir}/WJets.txt > temp && mv temp ${outdir}/WJets.txt 
 grep -v "nrevents" ${outdir}/WJets.txt > temp && mv temp ${outdir}/WJets.txt 
 printf "crosssection: %s\n" ${xcWJets} >> ${outdir}/WJets.txt
 root -l -b -q countevents.cxx\('"WJets.txt"'\)
fi

if [ ${doZHtoLLbb} = true ]
then
 printf "Making ZHtoLLbb\n" 
 grep -v "crosssection" ${outdir}/ZHtoLLbb.txt > temp && mv temp ${outdir}/ZHtoLLbb.txt 
 grep -v "nrevents" ${outdir}/ZHtoLLbb.txt > temp && mv temp ${outdir}/ZHtoLLbb.txt 
 printf "crosssection: %s\n" ${xcZHtoLLbb} >> ${outdir}/ZHtoLLbb.txt
 root -l -b -q countevents.cxx\('"ZHtoLLbb.txt"'\)
fi

if [ ${doWW} = true ]
then
 printf "Making WW\n" 
 grep -v "crosssection" ${outdir}/WW.txt > temp && mv temp ${outdir}/WW.txt 
 grep -v "nrevents" ${outdir}/WW.txt > temp && mv temp ${outdir}/WW.txt 
 printf "crosssection: %s\n" ${xcWW} >> ${outdir}/WW.txt
 root -l -b -q countevents.cxx\('"WW.txt"'\)
fi

if [ ${doZZ} = true ]
then
 printf "Making ZZ\n" 
 grep -v "crosssection" ${outdir}/ZZ.txt > temp && mv temp ${outdir}/ZZ.txt 
 grep -v "nrevents" ${outdir}/ZZ.txt > temp && mv temp ${outdir}/ZZ.txt 
 printf "crosssection: %s\n" ${xcZZ} >> ${outdir}/ZZ.txt
 root -l -b -q countevents.cxx\('"ZZ.txt"'\)
fi

if [ ${doWZ} = true ]
then
 printf "Making WZ\n" 
 grep -v "crosssection" ${outdir}/WZ.txt > temp && mv temp ${outdir}/WZ.txt 
 grep -v "nrevents" ${outdir}/WZ.txt > temp && mv temp ${outdir}/WZ.txt 
 printf "crosssection: %s\n" ${xcWZ} >> ${outdir}/WZ.txt
 root -l -b -q countevents.cxx\('"WZ.txt"'\)
fi

if [ ${doSignal} = true ]
then
 printf "Making Signal\n" 
 grep -v "crosssection" ${outdir}/Signal.txt > temp && mv temp ${outdir}/Signal.txt 
 grep -v "nrevents" ${outdir}/Signal.txt > temp && mv temp ${outdir}/Signal.txt 
 printf "crosssection: %s\n" ${xcSignal} >> ${outdir}/Signal.txt
 root -l -b -q countevents.cxx\('"Signal.txt",kTRUE'\)
fi

