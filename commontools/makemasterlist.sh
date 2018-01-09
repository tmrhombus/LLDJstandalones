#!/bin/bash

# straight ls is too big
# ls  /hdfs/store/user/tmperry/rainday/*/*/*/*/*root > ./allfiles.list

# define output directory where lists will end up
outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

# make outlist of directories
#ls -d /hdfs/store/user/tmperry/sosou/*/ > ${outdir}/dirout.list
#eosls -d root://cmseos.fnal.gov//store/group/lpchbb/LLDJntuples/furwed/* > ${outdir}/dirout.list
#eos root://cmseos.fnal.gov ls -d /store/user/lpchbb/LLDJntuples/furwed/*/ > ${outdir}/dirout.list

#xrdfs root://cmseos.fnal.gov ls /eos/uscms/store/user/lpchbb/LLDJntuples/furwed/ > ${outdir}/dirout.list
#tempbase = ${CMSSW_BASE}/src/commontools
xrdfs root://cmseos.fnal.gov ls ${depot}${nversion} > templayer1.out #${outdir}/dirout.list

# initialize outfile as empty (overwrite if exists)
echo "" > ${outdir}/allfiles.masterlist

for lineone in $(cat templayer1.out);
do
 
 xrdfs root://cmseos.fnal.gov ls ${lineone} > templayer2.out  
 echo "Text read from file: ${depot}${nversion}/${lineone}"
 for linetwo in $(cat templayer2.out)
 do
 
  xrdfs root://cmseos.fnal.gov ls ${linetwo} > templayer3.out
  for linethree in $(cat templayer3.out)
  do
  
   xrdfs root://cmseos.fnal.gov ls ${linethree} > templayer4.out
   for linefour in $(cat templayer4.out)
   do 
   
   xrdfs root://cmseos.fnal.gov ls ${linefour} >> ${outdir}/allfiles.masterlist 
   done
  done
 done
done

mv templayer1.out ${outdir}/dir.out
rm templayer2.out
rm templayer3.out
rm templayer4.out


#old way half-way works
# # ls on each directory individually, add to allfiles.list
# while IFS='' read -r line || [[ -n "$line" ]]; do
#     echo "Text read from file: $line"
#     #eos root://cmseos.fnal.gov ls ${line}/*/*/*/*root >> ${outdir}/allfiles.masterlist
#     #xrdfs root://cmseos.fnal.gov ls ${line}/*/*/*/* >> ${outdir}/allfiles.masterlist
#     #ls ${line}/*/*/*/*root >> ${outdir}/allfiles.masterlist
#     
# 
#     #ls -d  ${line}*/*/*/*/* >> ${outdir}/allfiles.masterlist
#     #xrdfs root://cmseos.fnal.gov ls -d  ${line}*/*/*/*/* >> ${outdir}/allfiles.masterlist
#     xrdfs root://cmseos.fnal.gov// ls -d ${line}*/*/*/* >> ${outdir}/allfiles.masterlist
#     
# 
# done < ${outdir}/dirout.list



