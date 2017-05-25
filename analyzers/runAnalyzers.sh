#!/bin/bash

 #'DY50_5'                            
for sample in \
 'Test_mc'
 #'DY50'                              \
 #'DY5to50_HT100to200'                \
 #'DY5to50_HT200to400'                \
 #'DY5to50_HT400to600'                \
 #'DY5to50_HT600toInf'                \
 #'DY5to50_HT70to100'                 \
 #'GJets_HT40To100'                   \
 #'GJets_HT100To200'                  \
 #'GJets_HT200To400'                  \
 #'GJets_HT400To600'                  \
 #'GJets_HT600ToInf'                  \
 #'ST_s'                              \
 #'STbar_t'                           \
 #'ST_t'                              \
 #'STbar_tW'                          \
 #'ST_tW'                             \
 #'TTJets'                            \
 #'WW'                                \
 #'WZ'                                \
 #'ZZ'                                \
 #'ZH_HToBB_ZToLL'                    \
 #'ggZH_HToBB_ZToLL'                  \
 #'ggZH_HToSSTobbbb_MS40_ctauS100'    \
 #'ggZH_HToSSTodddd_MS40_ctauS100'    \
 #'WJetsToLNu'                     

do

#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 70 -d -m
 ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "100000" -i "../lists" -o "../roots" -n 10 -a 1 -d -m
  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "1000" -i "../lists" -o "../roots" -n 10 -a 1 -d -m

done #for sample in DY50..

#for sample in \
# 'SingleElectron'  \
# 'SingleMuon'      
#do
#  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "1000" -i "../lists" -o "../roots" -n 10 -a 1 -d
#done # for datasample               
