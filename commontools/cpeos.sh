
destination="/store/group/lpchbb/LLDJntuples/${nversion}/analyzed/${aversion}/"
eos root://cmseos.fnal.gov mkdir -p  ${destination} 

source="${CMSSW_BASE}/src/LLDJstandalones/roots/${aversion}"

xrdcp -r ${source}  root://cmseos.fnal.gov/${destination}


