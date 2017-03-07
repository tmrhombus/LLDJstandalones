#!/bin/bash

# make sure only .root files in in the lists
outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

 #'Signal'

for sample in \
 "${outdir}/DY50.txt" \
 "${outdir}/DY5to50.txt" \
 "${outdir}/TTbar.txt" \
 "${outdir}/STs.txt" \
 "${outdir}/STtbar.txt" \
 "${outdir}/STt.txt" \
 "${outdir}/STtbarW.txt" \
 "${outdir}/STtW.txt" \
 "${outdir}/WJets.txt" \
 "${outdir}/ZHtoLLbb.txt" \
 "${outdir}/WW.txt" \
 "${outdir}/ZZ.txt" \
 "${outdir}/WZ.txt" \
 $(ls ${outdir}/Signal*txt)


do

 printf "%s\n" ${sample}
 sed -ne '/root/p' ${sample} > ${outdir}/temp && mv ${outdir}/temp ${sample}

done # for sample in DY50
