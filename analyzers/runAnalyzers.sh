#!/bin/bash

# 'DY50' \
# 'DY5to50' \
# 'TTbar' \
# 'STs' \
# 'STtbar' \
# 'STt' \
# 'STtbarW' \
# 'STtW' \
# 'WJets' \
# 'ZHtoLLbb' \
# 'WW' \
# 'ZZ' \
# 'WZ' \
# 'Signal'
 #testTT
 
for sample in \
 testtwo

do

  #"ALLCALOJETS"                      \
  #"ALLCALOJETSMATCHED"               \
  #"BASICCALOJETS"                    \
  #"BASICCALOJETS1"                   \
  #"BASICCALOJETS1MATCHED"            \
  #"BASICCALOJETS1PT20"               \
  #"BASICCALOJETS1PT20MATCHED"        \
  #"BASICCALOJETSMATCHED"             \
  #"INCLUSIVETAGGEDCALOJETS"          \
  #"INCLUSIVETAGGEDCALOJETS20"        \
  #"INCLUSIVETAGGEDCALOJETS20MATCHED" \
  #"INCLUSIVETAGGEDCALOJETS60"        \
  #"INCLUSIVETAGGEDCALOJETS60MATCHED" \
 for jettype in \
  "INCLUSIVETAGGEDCALOJETSA"         \
  "INCLUSIVETAGGEDCALOJETSAMATCHED"  \
  "INCLUSIVETAGGEDCALOJETSB"         \
  "INCLUSIVETAGGEDCALOJETSBMATCHED"  \
  "INCLUSIVETAGGEDCALOJETSC"         \
  "INCLUSIVETAGGEDCALOJETSCMATCHED"  \
  "INCLUSIVETAGGEDCALOJETSD"         \
  "INCLUSIVETAGGEDCALOJETSDMATCHED"  \
  "INCLUSIVETAGGEDCALOJETSE"         \
  "INCLUSIVETAGGEDCALOJETSEMATCHED"  \
  "INCLUSIVETAGGEDCALOJETSF"         \
  "INCLUSIVETAGGEDCALOJETSFMATCHED"  \
  "INCLUSIVETAGGEDCALOJETSMATCHED" 

 do

  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "60000" -j ${jettype}

 done #for sample in DY50..
done #for jettype in ALLCALOJETS


