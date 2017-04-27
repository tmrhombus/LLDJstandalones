#!/bin/bash


# 'Signal'
for sample in \
 'DY5to50' 
 #'DY50' 
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

  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-10000" -j ${jettype} -i "../lists" -o "../roots" -n 10 -a 1 -d
  ./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "-1" -i "../lists" -o "../roots" -n 10 -a 1 -d
  #./runanalyzer.exe -s ${sample} -l "20000" -x "" -e "20000" -j ${jettype} -i "../lists" -o "../roots" -n 10 -a 40 -d

done #for sample in DY50..


