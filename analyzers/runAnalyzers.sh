#!/bin/bash

 #'DY50_5'                            
# 'DY50'
 #'ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100' \
for sample in \
 'testmc' \


do

#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 70 -d -m
  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "../roots" -n 10 -a 1 -d -m
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "1000" -i "../lists" -o "../roots" -n 10 -a 1 -d -m

done #for sample in DY50..

#for sample in \
# 'SingleElectron' \
# 'SingleMuon'
#
#do
#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 1 -d
#done # for datasample               
