#!/bin/bash

 #'DY50_5'                            
 #'testmc'                          
for sample in \
 'ggZH_HToSSTobbbb_MS40_ctauS1'


do

#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 70 -d -m
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "../roots" -n 10 -a 1 -d -m
  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "1000" -i "../lists" -o "../roots" -n 10 -a 1 -d -m

done #for sample in DY50..

 for sample in \
 'SingleElectron' \
 'SingleMuon'

 do
   ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 1 -d
 done # for datasample               
