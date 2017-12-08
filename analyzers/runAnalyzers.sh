#!/bin/bash

 #'DY50_5'                            
# 'DY50'
# 'ggZH_HToSSTobbbb_MS40_ctauS0' \
# 'ggZH_HToSSTobbbb_MS40_ctauS0p05' \
# 'ggZH_HToSSTobbbb_MS40_ctauS1' \
# 'ggZH_HToSSTobbbb_MS40_ctauS10' \
# 'ggZH_HToSSTobbbb_MS40_ctauS1000' \
# 'ggZH_HToSSTobbbb_MS40_ctauS10000' 
# 'ggZH_HToSSTobbbb_MS40_ctauS100'
# 'WJetsToLNu' \
# 'DY50' \
# "TTtoLfromTbar"
# 'ggZH_HToSSTobbbb_MS15_ctauS1' \
# 'ggZH_HToSSTobbbb_MS15_ctauS10' \
# 'ggZH_HToSSTobbbb_MS15_ctauS100' \
# 'ggZH_HToSSTobbbb_MS15_ctauS1000' \
# 'ggZH_HToSSTobbbb_MS40_ctauS1' \
# 'ggZH_HToSSTobbbb_MS40_ctauS10' \
# 'ggZH_HToSSTobbbb_MS40_ctauS100' \
# 'ggZH_HToSSTobbbb_MS40_ctauS1000' \
# 'ggZH_HToSSTobbbb_MS55_ctauS1' \
# 'ggZH_HToSSTobbbb_MS55_ctauS10' \
# 'ggZH_HToSSTobbbb_MS55_ctauS100' \
#'ggZH_HToSSTobbbb_MS55_ctauS1000' \


 #'ZH_HToSSTobbbb_MS15_ctauS1' \
 #'ggZH_HToSSTobbbb_MS15_ctauS1' \
 #'ZH_HToSSTobbbb_MS15_ctauS10' \
 #'ggZH_HToSSTobbbb_MS15_ctauS10' \
 #'ZH_HToSSTobbbb_MS15_ctauS100' \
 #'ggZH_HToSSTobbbb_MS15_ctauS100' \
 #'ZH_HToSSTobbbb_MS15_ctauS1000' \
 #'ggZH_HToSSTobbbb_MS15_ctauS1000' \
 #'WJetsToLNu' \
 #'DY50' \
 #"TTtoLfromTbar" \
 #"TTtoLfromT"

for sample in \
 'ZH_HToSSTobbbb_MS15_ctauS1'
do

#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 70 -d -m
  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "../roots" -n 10 -a 1 -d -m
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists/taglistdir" -o "../roots/tagroots/" -n 10 -a 1 -d -m

done #for sample in DY50..

#for sample in \
# 'SingleElectron' \
# 'SingleMuon'
#
#do
#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 1 -d
#done # for datasample               
