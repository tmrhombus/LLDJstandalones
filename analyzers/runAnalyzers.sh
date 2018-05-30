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
# 'DY50' \
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

# 'DY5to50_HT100To200' \
# 'DY5to50_HT200To400' \
# 'DY5to50_HT400To600' \
# 'DY5to50_HT600ToInf' \
# 'DY5to50_HT70To100' \

# 'GJets_HT100To200' \
# 'GJets_HT200To400' \
# 'GJets_HT400To600' \
# 'GJets_HT40To100' \
# 'GJets_HT600ToInf' \

# 'ST_s' \
# 'ST_t' \
# 'ST_tW ' \
# 'STbar_t' \
# 'STbar_tW' \

# 'SingleElectron' \
# 'SingleMuon' \

# 'TTtoLL' \

# 'WG' \
# 'WWToLNuLNu' \
# 'WWToLNuQQ' \
# 'WZTo3LNu' \
# 'WZToL3Nu' \
# 'WZToLNu2QorQQ2L' \
# 'ZG' \
# 'ZH_HToBB_ZToLL' \
# 'ZZToLLLL' \
# 'ZZToLLNuNu' \
# 'ZZToLLQQ' \
# 'ZZToNuNuQQ' \

# 'ggZH_HToBB_ZToLL' \

 #'ZH_HToSSTobbbb_MS15_ctauS1' \
 #'ggZH_HToSSTobbbb_MS15_ctauS1' \
 #'ZH_HToSSTobbbb_MS15_ctauS10' \
 #'ggZH_HToSSTobbbb_MS15_ctauS10' \
 #'ZH_HToSSTobbbb_MS15_ctauS100' \
 #'ggZH_HToSSTobbbb_MS15_ctauS100' \
 #'ZH_HToSSTobbbb_MS15_ctauS1000' \
 #'ggZH_HToSSTobbbb_MS15_ctauS1000' \

for sample in \
 'ggZH_HToSSTobbbb_MS40_ctauS100'

do
#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "../roots/tagroots" -n 999999999 -a 1 -d -m
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "junk" -n 10 -a 1 -d -m

done #for sample in DY50..

#for sample in \
# 'SinglePhoton_E' 
#
#do
#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "1000" -i "../lists" -o "junk" -n 10 -a 1 -d
#done # for datasample               
