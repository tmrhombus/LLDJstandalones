#!/bin/bash
 
for sample in \
 'DY50' \
 'DY5to50' \
 'TTbar' \
 'STs' \
 'STtbar' \
 'STt' \
 'STtbarW' \
 'STtW' \
 'WJets' \
 'ZHtoLLbb' \
 'WW' \
 'ZZ' \
 'WZ' \
 'Signal'

do
 ./runanalyzer.exe -s ${sample} -l "20000" -x ""
done #for sample in DY50..


