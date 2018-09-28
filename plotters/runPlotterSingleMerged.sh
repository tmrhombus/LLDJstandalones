

 # region, lepname, varname, dolog, HIP

regions=( \ 
# "EleMuOSOF"     \
 "OneEleDY"      \
# "OneEleNoPair"  \
# "OneEleOffZ"    \
# "OneEleSig"     \
# "OneEleZH"      \
# "OneMuDY"       \
# "OneMuNoPair"   \
# "OneMuOffZ"     \
# "OneMuSig"      \
# "OneMuZH"       \
# "OnePho"        \
# "TwoEleDY"      \
# "TwoEleOffZ"    \
# "TwoEleSig"     \
# "TwoEleZH"      \
# "TwoMuDY"       \
# "TwoMuOffZ"     \
# "TwoMuSig"      \
# "TwoMuZH"       \
) 

variables=( \
 "AOD_elePt"                                  \     
# "AOD_eleEta"                                 \     
# "AOD_elePhi"                                 \     
# "AOD_muPt"                                   \     
# "AOD_muEta"                                  \     
# "AOD_muPhi"                                  \     
# "htall"                                      \ 
# "htaodcalojets"                              \
# "AOD_nSelectedEle"                           \
# "AOD_nSelectedMu"                            \
# "nSelectedAODCaloJet"                        \
# "nSelectedAODCaloJetTag"                     \
# "LeadingJet_AODCaloJetPt"                    \     
# "LeadingJet_AODCaloJetEta"                   \     
# "LeadingJet_AODCaloJetPhi"                   \     
# "AllJets_AODCaloJetMedianLog10IPSig"         \
# "AllJets_AODCaloJetMedianLog10TrackAngle"    \
# "AllJets_AODCaloJetAlphaMax"                 \
# "AllJets_AODCaloJetPt"                       \     
# "AllJets_AODCaloJetEta"                      \     
# "AllJets_AODCaloJetPhi"                      \  
)

for region in ${regions[@]}
do
  for variable in ${variables[@]}
  do
   root -l -b -q  'plotter_singleMerged.C('\""${region}"\"', '\""${variable}"\"' , kFALSE, kFALSE)'
  done
done
