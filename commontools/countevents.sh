#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"
 
doDY50=true
doDY5to50_HT100to200=true
doDY5to50_HT200to400=true
doDY5to50_HT400to600=true
doDY5to50_HT600toInf=true
doDY5to50_HT70to100=true              
doGJets_HT40To100=true
doGJets_HT100To200=true
doGJets_HT200To400=true
doGJets_HT400To600=true
doGJets_HT600ToInf=true
doST_s=true                           
doSTbar_t=true                        
doST_t=true                           
doSTbar_tW=true                       
doST_tW=true                          
doTTJets=true                         
doWW=true                             
doWZ=true                             
doZZ=true                             
doZH_HToBB_ZToLL=true                 
doggZH_HToBB_ZToLL=true               
doggZH_HToSSTobbbb_MS40_ctauS100=true 
doggZH_HToSSTodddd_MS40_ctauS100=true 
doWJetsToLNu=true                     
doSingleElectron=false                 
doSingleMuon=false 

xcDY50="71310"              # +-70 # LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z
xcDY5to50_HT70to100="301.2"  # +-0.8  # LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z             
xcDY5to50_HT100to200="224.2" # +- 5.7
xcDY5to50_HT200to400="37.2"  # +- 1.1
xcDY5to50_HT400to600="3.581" # +-0.118 
xcDY5to50_HT600toInf="1.124" # +-0.038 
xcGJets_HT40To100="20790"    # +-9                 
xcGJets_HT100To200="9238"    # +-4              
xcGJets_HT200To400="2305"    # +-0.7               
xcGJets_HT400To600="274.4"   # +-0.2               
xcGJets_HT600ToInf="93.46"   # +-0.06            
xcST_s="3.36"       #+0.13 -0.12 NLO                          
xcSTbar_t="81.2"    # 26.3+1.32-1.18  = (LEPTON DECAY = 26.3) / ( 3 x 10.80% [PDG])
xcST_t="136.8"      # 44.33+1.76-1.49 = (LEPTON DECAY = 44.3) / ( 3 x 10.80% [PDG]) 
xcSTbar_tW="35.85"  # +-0.9, +-1.7 NNLO
xcST_tW="35.85"     # +-0.9, +-1.7 NNLO                     
xcTTJets="831.76"   #NNLO
xcWW="10.32"      # not sure VV.. https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
xcZZ="63.0"                   
xcWZ="118.7"                  
xcZH_HToBB_ZToLL="1"                 
xcggZH_HToBB_ZToLL="1"               
xcggZH_HToSSTobbbb_MS40_ctauS100="1" 
xcggZH_HToSSTodddd_MS40_ctauS100="1" 
xcWJetsToLNu="61526.7"   # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets                  
xcSingleElectron="1"                 
xcSingleMuon="1" 

countalist () {
 if [ $1 = true ]
 then
  printf "Making %s\n" $2
  root -l -b -q 'countevents.cxx("'$2'")'
  printf "crosssection: %s\n" $3 >> ${listdir}/$2.info
 fi
}
 
countalist ${doDY50}                            "DY50"                            ${xcDY50}                            
countalist ${doDY5to50_HT100to200}              "DY5to50_HT100to200"              ${xcDY5to50_HT100to200}              
countalist ${doDY5to50_HT200to400}              "DY5to50_HT200to400"              ${xcDY5to50_HT200to400}              
countalist ${doDY5to50_HT400to600}              "DY5to50_HT400to600"              ${xcDY5to50_HT400to600}              
countalist ${doDY5to50_HT600toInf}              "DY5to50_HT600toInf"              ${xcDY5to50_HT600toInf}              
countalist ${doDY5to50_HT70to100}               "DY5to50_HT70to100"               ${xcDY5to50_HT70to100}               
countalist ${doGJets_HT40To100}                 "GJets_HT40To100"                 ${xcGJets_HT40To100}                 
countalist ${doGJets_HT100To200}                "GJets_HT100To200"                ${xcGJets_HT100To200}                
countalist ${doGJets_HT200To400}                "GJets_HT200To400"                ${xcGJets_HT200To400}                
countalist ${doGJets_HT400To600}                "GJets_HT400To600"                ${xcGJets_HT400To600}                
countalist ${doGJets_HT600ToInf}                "GJets_HT600ToInf"                ${xcGJets_HT600ToInf}                
countalist ${doST_s}                            "ST_s"                            ${xcST_s}                            
countalist ${doSTbar_t}                         "STbar_t"                         ${xcSTbar_t}                         
countalist ${doST_t}                            "ST_t"                            ${xcST_t}                            
countalist ${doSTbar_tW}                        "STbar_tW"                        ${xcSTbar_tW}                        
countalist ${doST_tW}                           "ST_tW"                           ${xcST_tW}                           
countalist ${doTTJets}                          "TTJets"                          ${xcTTJets}                          
countalist ${doWW}                              "WW"                              ${xcWW}                              
countalist ${doWZ}                              "WZ"                              ${xcWZ}                              
countalist ${doZZ}                              "ZZ"                              ${xcZZ}                              
countalist ${doZH_HToBB_ZToLL}                  "ZH_HToBB_ZToLL"                  ${xcZH_HToBB_ZToLL}                  
countalist ${doggZH_HToBB_ZToLL}                "ggZH_HToBB_ZToLL"                ${xcggZH_HToBB_ZToLL}                
countalist ${doggZH_HToSSTobbbb_MS40_ctauS100}  "ggZH_HToSSTobbbb_MS40_ctauS100"  ${xcggZH_HToSSTobbbb_MS40_ctauS100}  
countalist ${doggZH_HToSSTodddd_MS40_ctauS100}  "ggZH_HToSSTodddd_MS40_ctauS100"  ${xcggZH_HToSSTodddd_MS40_ctauS100}  
countalist ${doWJetsToLNu}                      "WJetsToLNu"                      ${xcWJetsToLNu}                      
countalist ${doSingleElectron}                  "SingleElectron"                  ${xcSingleElectron}                  
countalist ${doSingleMuon}                      "SingleMuon"                      ${xcSingleMuon}                      

