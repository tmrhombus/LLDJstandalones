#!/bin/bash


for sample in \
 'ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10'

do
#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "../roots/tagroots" -n 999999999 -a 1 -d -m
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "50000" -i "../lists" -o "junk" -n 30 -a 1 -d -m

done #for sample in DY50..

for sample in \
 "Data_SingleMu_G"

do
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "50000" -i "../lists" -o "junk" -n 30 -a 1 -d
done # for datasample               
