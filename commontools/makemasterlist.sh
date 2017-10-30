#!/bin/bash

# straight ls is too big
# ls  /hdfs/store/user/tmperry/rainday/*/*/*/*/*root > ./allfiles.list

# define output directory where lists will end up
outdir="${CMSSW_BASE}/src/LLDJstandalones/lists/test"

# make outlist of directories
#ls -d /hdfs/store/user/tmperry/sosou/*/ > ${outdir}/dirout.list
#eosls -d root://cmseos.fnal.gov//store/group/lpchbb/LLDJntuples/furwed/* > ${outdir}/dirout.list
#eos root://cmseos.fnal.gov ls -d /store/user/lpchbb/LLDJntuples/furwed/*/ > ${outdir}/dirout.list
xrdfs root://cmseos.fnal.gov ls /eos/uscms/store/user/lpchbb/LLDJntuples/furwed/ > ${outdir}/dirout.list
# initialize outfile as empty (overwrite if exists)
echo "" > ${outdir}/allfiles.masterlist

# ls on each directory individually, add to allfiles.list
while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "Text read from file: $line"
    #eos root://cmseos.fnal.gov ls ${line}/*/*/*/*root >> ${outdir}/allfiles.masterlist
    ls -d  ${line}*/*/*/*/* >> ${outdir}/allfiles.masterlist
    #xrdfs root://cmseos.fnal.gov ls ${line}/*/*/*/* >> ${outdir}/allfiles.masterlist
    #ls ${line}/*/*/*/*root >> ${outdir}/allfiles.masterlist
done < ${outdir}/dirout.list



