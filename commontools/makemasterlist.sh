#!/bin/bash

# straight ls is too big
# ls  /hdfs/store/user/tmperry/rainday/*/*/*/*/*root > ./allfiles.list

# define output directory where lists will end up
outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

# make outlist of directories
ls -d /hdfs/store/user/tmperry/sosou/*/ > ${outdir}/dirout.list

# initialize outfile as empty (overwrite if exists)
echo "" > ${outdir}/allfiles.masterlist

# ls on each directory individually, add to allfiles.list
while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "Text read from file: $line"
    ls ${line}*/*/*/*root >> ${outdir}/allfiles.masterlist
done < ${outdir}/dirout.list



