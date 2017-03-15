#!/bin/bash

# delete anything in our "list" that doesn't have .root at the end

for sample in \
 "${listdir}/DY50.list" \
 "${listdir}/DY5to50.list" \
 "${listdir}/TTbar.list" \
 "${listdir}/STs.list" \
 "${listdir}/STtbar.list" \
 "${listdir}/STt.list" \
 "${listdir}/STtbarW.list" \
 "${listdir}/STtW.list" \
 "${listdir}/WJets.list" \
 "${listdir}/ZHtoLLbb.list" \
 "${listdir}/WW.list" \
 "${listdir}/ZZ.list" \
 "${listdir}/WZ.list" \
 $(ls ${listdir}/Signal*list)


do

 printf "%s\n" ${sample}
 sed -ne '/root/p' ${sample} > ${listdir}/temp && mv ${listdir}/temp ${sample}

done # for sample in DY50
