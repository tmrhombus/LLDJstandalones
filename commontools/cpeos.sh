
destination="/store/group/lpchbb/LLDJntuples/${nversion}/analyzed/${aversion}/"
eos root://cmseos.fnal.gov mkdir -p  ${destination} 

source="${CMSSW_BASE}/src/LLDJstandalones/roots/${aversion}"

# copy root files over
xrdcp -r ${source}  root://cmseos.fnal.gov/${destination}

# copy info file over
aboutsource="${CMSSW_BASE}/src/LLDJstandalones/submitters/gitignore/${aversion}"
xrdcp ${aboutsource}/about.txt  root://cmseos.fnal.gov/${destination}
