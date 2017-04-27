#!/bin/bash


# 'Signal'
for sample in \
 'DY50' 
 #'DY5to50' 
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
# 'WZ' 

do

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
  #"INCLUSIVETAGGEDCALOJETSA"         \
  #"INCLUSIVETAGGEDCALOJETSAMATCHED"  \
  #"INCLUSIVETAGGEDCALOJETSB"         \
  #"INCLUSIVETAGGEDCALOJETSBMATCHED"  \
  #"INCLUSIVETAGGEDCALOJETSC"         \
  #"INCLUSIVETAGGEDCALOJETSCMATCHED"  \
  #"INCLUSIVETAGGEDCALOJETSD"         \
  #"INCLUSIVETAGGEDCALOJETSDMATCHED"  \
  #"INCLUSIVETAGGEDCALOJETSE"         \
  #"INCLUSIVETAGGEDCALOJETSEMATCHED"  \
  #"INCLUSIVETAGGEDCALOJETSF"         \
  #"INCLUSIVETAGGEDCALOJETSFMATCHED"  \
  #"INCLUSIVETAGGEDCALOJETSMATCHED" 
 for jettype in \
  "ALLCALOJETS"                     

 do

  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-10000" -j ${jettype} -i "../lists" -o "../roots" -n 10 -a 1 -d
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -j ${jettype} -i "../lists" -o "../roots" -n 10 -a 1 -d -m
  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "20000" -j ${jettype} -i "../lists" -o "../roots" -n 10 -a 40 -d

 done #for sample in DY50..
done #for jettype in ALLCALOJETS


