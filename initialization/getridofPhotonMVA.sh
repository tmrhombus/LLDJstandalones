#!/bin/bash
# the standard VID producer auto-detects AOD/miniAOD
# these use a configuarable flag instead

# disable MVA ID
cp       ${CMSSW_BASE}/src/LLDJstandalones/initialization/egmPhotonIDs_cff.py \
 ${CMSSW_BASE}/src/RecoEgamma/PhotonIdentification/python/egmPhotonIDs_cff.py

