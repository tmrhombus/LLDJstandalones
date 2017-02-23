#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/roots"
 
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
 ./runanalyzer.exe -s ${sample}
done #for sample in DY50..


