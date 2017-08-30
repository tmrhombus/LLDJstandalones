#!/bin/bash

# data json from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGoodLumiSectionsJSONFile gives
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt

# makes 

xcs=( \
 "69200" \
 "66017" \
 "72383" \
)

for xc in ${xcs[@]}
do

 echo "working on ${xc}\n"

 pileupCalc.py -i ./Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt --calcMode true --minBiasXsec ${xc} --maxPileupBin 75 --numPileupBins 75 ./data_${xc}.root

done



 # countalist "DY10to50"                          ${xcDY10to50}    
 # countalist "DY50"                              ${xcDY50}    
 # countalist "ggZH_HToBB_ZToLL"                  ${xcggZH_HToBB_ZToLL}    
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS0"      ${xcggZH_HToSSTobbbb_MS40_ctauS0}    
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS0p05"   ${xcggZH_HToSSTobbbb_MS40_ctauS0p05}   
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS1"      ${xcggZH_HToSSTobbbb_MS40_ctauS1}    
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS10"     ${xcggZH_HToSSTobbbb_MS40_ctauS10}    
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS100"    ${xcggZH_HToSSTobbbb_MS40_ctauS100}    
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS1000"   ${xcggZH_HToSSTobbbb_MS40_ctauS1000}   
 # countalist "ggZH_HToSSTobbbb_MS40_ctauS10000"  ${xcggZH_HToSSTobbbb_MS40_ctauS10000}  
 # countalist "GJets_HT40To100"                   ${xcGJets_HT40To100}    
 # countalist "GJets_HT100To200"                  ${xcGJets_HT100To200}    
 # countalist "GJets_HT200To400"                  ${xcGJets_HT200To400}    
 # countalist "GJets_HT400To600"                  ${xcGJets_HT400To600}    
 # countalist "GJets_HT600ToInf"                  ${xcGJets_HT600ToInf}    
 # countalist "ST_s"                              ${xcST_s}    
 # countalist "STbar_t"                           ${xcSTbar_t}    
 # countalist "ST_t"                              ${xcST_t}    
 # countalist "STbar_tW"                          ${xcSTbar_tW}    
 # countalist "ST_tW"                             ${xcST_tW}    
 # countalist "TTtoLL"                            ${xcTTtoLL}    
 # countalist "TTtoLfromTbar"                     ${xcTTtoLfromTbar}    
 # countalist "TTtoLfromT"                        ${xcTTtoLfromT}    
 # countalist "WG"                                ${xcWG}    
 # countalist "WJetsToLNu"                        ${xcWJetsToLNu}    
 # countalist "WWToLNuLNu"                        ${xcWWToLNuLNu}    
 # countalist "WWToLNuQQ"                         ${xcWWToLNuQQ}    
 # countalist "WZToL3Nu"                          ${xcWZToL3Nu}    
 # countalist "WZTo3LNu"                          ${xcWZTo3LNu}    
 # countalist "WZToLNu2QorQQ2L"                   ${xcWZToLNu2QorQQ2L}    
 # countalist "ZG"                                ${xcZG}    
 # countalist "ZH_HToBB_ZToLL"                    ${xcZH_HToBB_ZToLL}    
 # countalist "ZZToLLNuNu"                        ${xcZZToLLNuNu}    
 # countalist "ZZToLLQQ"                          ${xcZZToLLQQ}    
 # countalist "ZZToNuNuQQ"                        ${xcZZToNuNuQQ}    
 # countalist "ZZToLLLL"                          ${xcZZToLLLL}    
 # countalist "SingleElectron"                    ${xcSingleElectron}                    
 # countalist "SingleMuon"                        ${xcSingleMuon}                        
 # countalist "DoubleEG"                          ${xcDoubleEG}                          
 # countalist "DoubleMuon"                        ${xcDoubleMuon}                        
 # countalist "MuonEG"                            ${xcMuonEG}    
