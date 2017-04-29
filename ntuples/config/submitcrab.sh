#voms-proxy-init --voms cms --valid 100:00

domc=false
dodata=false
dosubmit=false

START=$(date +%s);
printf "Started at `date`\n\n"

mkdir -p "${subdir}/gitignore/${version}/lists"

#lumi=40000. # /pb
lumi=12900. # /pb

#  MC samples
for samplename in \
 "ggZHSSbbbb" \
 "ZHHbb" 

do
 printf "\n Sample: ${samplename} ----------------\n"
 printf "---------------------------------------\n\n"

done



