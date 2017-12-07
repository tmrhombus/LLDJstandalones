#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists/taglistdir"

xcDY10to50="18610.0"
xcDY50="5765.4"
xcDY5to50_HT70To100="301.2"  # +-0.8  # LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z             
xcDY5to50_HT100To200="224.2" # +- 5.7
xcDY5to50_HT200To400="37.2"  # +- 1.1
xcDY5to50_HT400To600="3.581" # +-0.118 
xcDY5to50_HT600ToInf="1.124" # +-0.038 
xcGJets_HT40To100="20790"    # +-9                 
xcGJets_HT100To200="9238"    # +-4              
xcGJets_HT200To400="2305"    # +-0.7               
xcGJets_HT400To600="274.4"   # +-0.2               
xcGJets_HT600ToInf="93.46"   # +-0.06            
xcST_s="3.36"       #+0.13 -0.12 NLO                          
xcSTbar_t="26.38"   # +1.32-1.18
xcST_t="44.33"      # +1.76-1.49
xcSTbar_tW="19.56"  # from OSU - how? 35.85 +-0.9, +-1.7 NNLO
xcST_tW="19.56"     # from OSU - how? 35.85 +-0.9, +-1.7 NNLO                     
xcTTJets="831.76"   #NNLO
xcTTtoLL="87.31"          
xcTTtoLfromT="182.7"      
xcTTtoLfromTbar="182.7"   
xcWW="10.32"      # not sure VV.. https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
xcZZ="63.0"                   
xcWZ="118.7"                  

xcWWToLNuQQ="49.997"
xcWWToLNuLNu="12.178"

xcWZToL3Nu="3.03"                         
xcWZTo3LNu="4.42965"                         
xcWZToLNu2QorQQ2L="9.82423165827" # ???

xcZZToNuNuQQ="94.04"
xcZZToLLQQ="93.22"
xcZZToLLNuNu="90.5644"
xcZZToLLLL="91.256"

xcWG="9405.271"
xcZG="9117.864"
#https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV#ZH_Process
#BR(HToSSTobbbb)~20%, BR(ZToll)~10.099%
xcZH_HToBB_ZToLL="1"                 
xcggZH_HToBB_ZToLL="1"               
xcggZH_HToSSTobbbb_MS15_ctauS0="0.0024783"      
xcggZH_HToSSTobbbb_MS15_ctauS0p05="0.0024783"   
xcggZH_HToSSTobbbb_MS15_ctauS1="0.0024783"      
xcggZH_HToSSTobbbb_MS15_ctauS10="0.0024783"     
xcggZH_HToSSTobbbb_MS15_ctauS100="0.0024783"    
xcggZH_HToSSTobbbb_MS15_ctauS1000="0.0024783"   
xcggZH_HToSSTobbbb_MS15_ctauS10000="0.0024783"  
xcggZH_HToSSTobbbb_MS40_ctauS0="0.0024783"      
xcggZH_HToSSTobbbb_MS40_ctauS0p05="0.0024783"   
xcggZH_HToSSTobbbb_MS40_ctauS1="0.0024783"      
xcggZH_HToSSTobbbb_MS40_ctauS10="0.0024783"     
xcggZH_HToSSTobbbb_MS40_ctauS100="0.0024783"    
xcggZH_HToSSTobbbb_MS40_ctauS1000="0.0024783"   
xcggZH_HToSSTobbbb_MS40_ctauS10000="0.0024783"  
xcggZH_HToSSTobbbb_MS55_ctauS0="0.0024783"      
xcggZH_HToSSTobbbb_MS55_ctauS0p05="0.0024783"   
xcggZH_HToSSTobbbb_MS55_ctauS1="0.0024783"      
xcggZH_HToSSTobbbb_MS55_ctauS10="0.0024783"     
xcggZH_HToSSTobbbb_MS55_ctauS100="0.0024783"    
xcggZH_HToSSTobbbb_MS55_ctauS1000="0.0024783"   
xcggZH_HToSSTobbbb_MS55_ctauS10000="0.0024783"  

#need to fix these also I think they can be replaced with a single variable
xcZH_HToSSTobbbb_MS15_ctauS0="0.015374718"      
xcZH_HToSSTobbbb_MS15_ctauS0p05="0.015374718"   
xcZH_HToSSTobbbb_MS15_ctauS1="0.015374718"      
xcZH_HToSSTobbbb_MS15_ctauS10="0.015374718"     
xcZH_HToSSTobbbb_MS15_ctauS100="0.015374718"    
xcZH_HToSSTobbbb_MS15_ctauS1000="0.015374718"   
xcZH_HToSSTobbbb_MS15_ctauS10000="0.015374718"  
xcZH_HToSSTobbbb_MS40_ctauS0="0.015374718"      
xcZH_HToSSTobbbb_MS40_ctauS0p05="0.015374718"   
xcZH_HToSSTobbbb_MS40_ctauS1="0.015374718"      
xcZH_HToSSTobbbb_MS40_ctauS10="0.015374718"     
xcZH_HToSSTobbbb_MS40_ctauS100="0.015374718"    
xcZH_HToSSTobbbb_MS40_ctauS1000="0.015374718"   
xcZH_HToSSTobbbb_MS40_ctauS10000="0.015374718"  
xcZH_HToSSTobbbb_MS55_ctauS0="0.015374718"      
xcZH_HToSSTobbbb_MS55_ctauS0p05="0.015374718"   
xcZH_HToSSTobbbb_MS55_ctauS1="0.015374718"      
xcZH_HToSSTobbbb_MS55_ctauS10="0.015374718"     
xcZH_HToSSTobbbb_MS55_ctauS100="0.015374718"    
xcZH_HToSSTobbbb_MS55_ctauS1000="0.015374718"   
xcZH_HToSSTobbbb_MS55_ctauS10000="0.015374718"  

xcWJetsToLNu="61526.7"   # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets                  

xcSingleElectron="1"                    
xcSingleMuon="1"                        
xcDoubleEG="1"                          
xcDoubleMuon="1"                        
xcMuonEG="1"                            

countalist () {
 printf "Making %s\n" $1
 root -l -b -q 'countevents.cxx("'$1'")'
 printf "crosssection: %s\n" $2 >> ${listdir}/taglistdir/$1.info
}

countalist "DY50"                              ${xcDY50}                              
##countalist "DY5to50_HT70To100"                 ${xcDY5to50_HT70To100}                 
##countalist "DY5to50_HT100To200"                ${xcDY5to50_HT100To200}                
##countalist "DY5to50_HT200To400"                ${xcDY5to50_HT200To400}                
##countalist "DY5to50_HT400To600"                ${xcDY5to50_HT400To600}                
##countalist "DY5to50_HT600ToInf"                ${xcDY5to50_HT600ToInf}                
##countalist "ggZH_HToBB_ZToLL"                  ${xcggZH_HToBB_ZToLL}                  
#countalist "ggZH_HToSSTobbbb_MS15_ctauS0"      ${xcggZH_HToSSTobbbb_MS15_ctauS0}      
#countalist "ggZH_HToSSTobbbb_MS15_ctauS0p05"   ${xcggZH_HToSSTobbbb_MS15_ctauS0p05}   
countalist "ggZH_HToSSTobbbb_MS15_ctauS1"      ${xcggZH_HToSSTobbbb_MS15_ctauS1}      
countalist "ggZH_HToSSTobbbb_MS15_ctauS10"     ${xcggZH_HToSSTobbbb_MS15_ctauS10}     
countalist "ggZH_HToSSTobbbb_MS15_ctauS100"    ${xcggZH_HToSSTobbbb_MS15_ctauS100}    
countalist "ggZH_HToSSTobbbb_MS15_ctauS1000"   ${xcggZH_HToSSTobbbb_MS15_ctauS1000}   
#countalist "ggZH_HToSSTobbbb_MS15_ctauS10000"  ${xcggZH_HToSSTobbbb_MS15_ctauS10000}  
#countalist "ggZH_HToSSTobbbb_MS40_ctauS0"      ${xcggZH_HToSSTobbbb_MS40_ctauS0}      
#countalist "ggZH_HToSSTobbbb_MS40_ctauS0p05"   ${xcggZH_HToSSTobbbb_MS40_ctauS0p05}   
countalist "ggZH_HToSSTobbbb_MS40_ctauS1"      ${xcggZH_HToSSTobbbb_MS40_ctauS1}      
countalist "ggZH_HToSSTobbbb_MS40_ctauS10"     ${xcggZH_HToSSTobbbb_MS40_ctauS10}     
countalist "ggZH_HToSSTobbbb_MS40_ctauS100"    ${xcggZH_HToSSTobbbb_MS40_ctauS100}    
countalist "ggZH_HToSSTobbbb_MS40_ctauS1000"   ${xcggZH_HToSSTobbbb_MS40_ctauS1000}   
#countalist "ggZH_HToSSTobbbb_MS40_ctauS10000"  ${xcggZH_HToSSTobbbb_MS40_ctauS10000}  
#countalist "ggZH_HToSSTobbbb_MS55_ctauS0"      ${xcggZH_HToSSTobbbb_MS55_ctauS0}      
#countalist "ggZH_HToSSTobbbb_MS55_ctauS0p05"   ${xcggZH_HToSSTobbbb_MS55_ctauS0p05}   
countalist "ggZH_HToSSTobbbb_MS55_ctauS1"      ${xcggZH_HToSSTobbbb_MS55_ctauS1}      
countalist "ggZH_HToSSTobbbb_MS55_ctauS10"     ${xcggZH_HToSSTobbbb_MS55_ctauS10}     
countalist "ggZH_HToSSTobbbb_MS55_ctauS100"    ${xcggZH_HToSSTobbbb_MS55_ctauS100}    
countalist "ggZH_HToSSTobbbb_MS55_ctauS1000"   ${xcggZH_HToSSTobbbb_MS55_ctauS1000}   
#countalist "ggZH_HToSSTobbbb_MS55_ctauS10000"  ${xcggZH_HToSSTobbbb_MS55_ctauS10000}  
#countalist "ZH_HToSSTobbbb_MS15_ctauS0"      ${xcZH_HToSSTobbbb_MS15_ctauS0}      
#countalist "ZH_HToSSTobbbb_MS15_ctauS0p05"   ${xcZH_HToSSTobbbb_MS15_ctauS0p05}   
countalist "ZH_HToSSTobbbb_MS15_ctauS1"      ${xcZH_HToSSTobbbb_MS15_ctauS1}      
countalist "ZH_HToSSTobbbb_MS15_ctauS10"     ${xcZH_HToSSTobbbb_MS15_ctauS10}     
countalist "ZH_HToSSTobbbb_MS15_ctauS100"    ${xcZH_HToSSTobbbb_MS15_ctauS100}    
countalist "ZH_HToSSTobbbb_MS15_ctauS1000"   ${xcZH_HToSSTobbbb_MS15_ctauS1000}   
#countalist "ZH_HToSSTobbbb_MS15_ctauS10000"  ${xcZH_HToSSTobbbb_MS15_ctauS10000}  
#countalist "ZH_HToSSTobbbb_MS40_ctauS0"      ${xcZH_HToSSTobbbb_MS40_ctauS0}      
#countalist "ZH_HToSSTobbbb_MS40_ctauS0p05"   ${xcZH_HToSSTobbbb_MS40_ctauS0p05}   
countalist "ZH_HToSSTobbbb_MS40_ctauS1"      ${xcZH_HToSSTobbbb_MS40_ctauS1}      
countalist "ZH_HToSSTobbbb_MS40_ctauS10"     ${xcZH_HToSSTobbbb_MS40_ctauS10}     
countalist "ZH_HToSSTobbbb_MS40_ctauS100"    ${xcZH_HToSSTobbbb_MS40_ctauS100}    
countalist "ZH_HToSSTobbbb_MS40_ctauS1000"   ${xcZH_HToSSTobbbb_MS40_ctauS1000}   
#countalist "ZH_HToSSTobbbb_MS40_ctauS10000"  ${xcZH_HToSSTobbbb_MS40_ctauS10000}  
#countalist "ZH_HToSSTobbbb_MS55_ctauS0"      ${xcZH_HToSSTobbbb_MS55_ctauS0}      
#countalist "ZH_HToSSTobbbb_MS55_ctauS0p05"   ${xcZH_HToSSTobbbb_MS55_ctauS0p05}   
countalist "ZH_HToSSTobbbb_MS55_ctauS1"      ${xcZH_HToSSTobbbb_MS55_ctauS1}      
countalist "ZH_HToSSTobbbb_MS55_ctauS10"     ${xcZH_HToSSTobbbb_MS55_ctauS10}     
countalist "ZH_HToSSTobbbb_MS55_ctauS100"    ${xcZH_HToSSTobbbb_MS55_ctauS100}    
countalist "ZH_HToSSTobbbb_MS55_ctauS1000"   ${xcZH_HToSSTobbbb_MS55_ctauS1000}   
#countalist "ZH_HToSSTobbbb_MS55_ctauS10000"  ${xcZH_HToSSTobbbb_MS55_ctauS10000}  
##countalist "GJets_HT40To100"                   ${xcGJets_HT40To100}                   
##countalist "GJets_HT100To200"                  ${xcGJets_HT100To200}                  
##countalist "GJets_HT200To400"                  ${xcGJets_HT200To400}                  
##countalist "GJets_HT400To600"                  ${xcGJets_HT400To600}                  
##countalist "GJets_HT600ToInf"                  ${xcGJets_HT600ToInf}                  
##countalist "ST_s"                              ${xcST_s}                              
##countalist "STbar_t"                           ${xcSTbar_t}                           
##countalist "ST_t"                              ${xcST_t}                              
##countalist "STbar_tW"                          ${xcSTbar_tW}                          
##countalist "ST_tW"                             ${xcST_tW}                             
##countalist "TTtoLL"                            ${xcTTtoLL}                            
countalist "TTtoLfromTbar"                     ${xcTTtoLfromTbar}                     
countalist "TTtoLfromT"                        ${xcTTtoLfromT}                        
##countalist "WG"                                ${xcWG}                                
countalist "WJetsToLNu"                        ${xcWJetsToLNu}                        
##countalist "WWToLNuLNu"                        ${xcWWToLNuLNu}                        
##countalist "WWToLNuQQ"                         ${xcWWToLNuQQ}                         
##countalist "WZToL3Nu"                          ${xcWZToL3Nu}                          
##countalist "WZTo3LNu"                          ${xcWZTo3LNu}                          
##countalist "WZToLNu2QorQQ2L"                   ${xcWZToLNu2QorQQ2L}                   
##countalist "ZG"                                ${xcZG}                                
##countalist "ZH_HToBB_ZToLL"                    ${xcZH_HToBB_ZToLL}                    
##countalist "ZZToLLNuNu"                        ${xcZZToLLNuNu}                        
##countalist "ZZToLLQQ"                          ${xcZZToLLQQ}                          
##countalist "ZZToNuNuQQ"                        ${xcZZToNuNuQQ}                        
##countalist "ZZToLLLL"                          ${xcZZToLLLL}                          
##countalist "SingleElectron"                    ${xcSingleElectron}                    
##countalist "SingleMuon"                        ${xcSingleMuon}                        
## countalist "DoubleEG"                          ${xcDoubleEG}                          
## countalist "DoubleMuon"                        ${xcDoubleMuon}                        
## countalist "MuonEG"                            ${xcMuonEG}                            

