#!/bin/bash
# the standard VID producer auto-detects AOD/miniAOD
# these use a configuarable flag instead

# Electron
cp          ${CMSSW_BASE}/src/LLDJstandalones/initialization/ElectronIDValueMapProducer.cc \
 ${CMSSW_BASE}/src/RecoEgamma/ElectronIdentification/plugins/ElectronIDValueMapProducer.cc

cp          ${CMSSW_BASE}/src/LLDJstandalones/initialization/VersionedGsfElectronIdProducer.cc \
 ${CMSSW_BASE}/src/RecoEgamma/ElectronIdentification/plugins/VersionedGsfElectronIdProducer.cc


cp         ${CMSSW_BASE}/src/LLDJstandalones/initialization/ElectronIDValueMapProducer_cfi.py \
 ${CMSSW_BASE}/src/RecoEgamma/ElectronIdentification/python/ElectronIDValueMapProducer_cfi.py

cp         ${CMSSW_BASE}/src/LLDJstandalones/initialization/ElectronRegressionValueMapProducer_cfi.py \
 ${CMSSW_BASE}/src/RecoEgamma/ElectronIdentification/python/ElectronRegressionValueMapProducer_cfi.py

# Photon
cp        ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonIDValueMapProducer.cc \
 ${CMSSW_BASE}/src/RecoEgamma/PhotonIdentification/plugins/PhotonIDValueMapProducer.cc

cp        ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonRegressionValueMapProducer.cc \
 ${CMSSW_BASE}/src/RecoEgamma/PhotonIdentification/plugins/PhotonRegressionValueMapProducer.cc


cp       ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonIDValueMapProducer_cfi.py \
 ${CMSSW_BASE}/src/RecoEgamma/PhotonIdentification/python/PhotonIDValueMapProducer_cfi.py

cp       ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonRegressionValueMapProducer_cfi.py \
 ${CMSSW_BASE}/src/RecoEgamma/PhotonIdentification/python/PhotonRegressionValueMapProducer_cfi.py

# disable MVA ID
cp       ${CMSSW_BASE}/src/LLDJstandalones/initialization/egmPhotonIDs_cff.py \
 ${CMSSW_BASE}/src/RecoEgamma/PhotonIdentification/python/egmPhotonIDs_cff.py



# # Electron
#    cp  /uscms_data/d3/tmperry/RecoEgamma/ElectronIdentification/plugins/ElectronIDValueMapProducer.cc \
#           ${CMSSW_BASE}/src/LLDJstandalones/initialization/ElectronIDValueMapProducer.cc   
# 
#    cp  /uscms_data/d3/tmperry/RecoEgamma/ElectronIdentification/plugins/VersionedGsfElectronIdProducer.cc \
#           ${CMSSW_BASE}/src/LLDJstandalones/initialization/VersionedGsfElectronIdProducer.cc   
# 
# 
#    cp  /uscms_data/d3/tmperry/RecoEgamma/ElectronIdentification/python/ElectronIDValueMapProducer_cfi.py \
#          ${CMSSW_BASE}/src/LLDJstandalones/initialization/ElectronIDValueMapProducer_cfi.py   
# 
#    cp  /uscms_data/d3/tmperry/RecoEgamma/ElectronIdentification/python/ElectronRegressionValueMapProducer_cfi.py \
#          ${CMSSW_BASE}/src/LLDJstandalones/initialization/ElectronRegressionValueMapProducer_cfi.py   
# 
# # Photon
#    cp  /uscms_data/d3/tmperry/RecoEgamma/PhotonIdentification/plugins/PhotonIDValueMapProducer.cc \
#         ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonIDValueMapProducer.cc   
# 
#    cp  /uscms_data/d3/tmperry/RecoEgamma/PhotonIdentification/plugins/PhotonRegressionValueMapProducer.cc \
#         ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonRegressionValueMapProducer.cc   
# 
# 
#    cp  /uscms_data/d3/tmperry/RecoEgamma/PhotonIdentification/python/PhotonIDValueMapProducer_cfi.py \
#        ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonIDValueMapProducer_cfi.py   
# 
#    cp  /uscms_data/d3/tmperry/RecoEgamma/PhotonIdentification/python/PhotonRegressionValueMapProducer_cfi.py \
#        ${CMSSW_BASE}/src/LLDJstandalones/initialization/PhotonRegressionValueMapProducer_cfi.py   
