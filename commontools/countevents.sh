#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"

xcDY10to50="18610.0"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z
#Other ref: https://cms-pdmv.cern.ch/mcm/requests?prepid=*GS*&dataset_name=DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8&page=0&shown=524415
#Other ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DDYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

xcDY50="5765.4"
#Ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DDYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeV FEWZ 3.1.b2 1921.8*3

xcDY5to50_HT70To100="301.2"  # +-0.8  
xcDY5to50_HT100To200="224.2" # +- 5.7
xcDY5to50_HT200To400="37.2"  # +- 1.1
xcDY5to50_HT400To600="3.581" # +-0.118 
xcDY5to50_HT600ToInf="1.124" # +-0.038 
#Ref: LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z             

xcGJets_HT40To100="20790"    # +-9                 
xcGJets_HT100To200="9238"    # +-4              
xcGJets_HT200To400="2305"    # +-0.7               
xcGJets_HT400To600="274.4"   # +-0.2               
xcGJets_HT600ToInf="93.46"   # +-0.06            
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z

xcST_s="3.36"       #+0.13 -0.12 NLO
xcSTbar_t="26.38"   # +1.32-1.18
xcST_t="44.33"      # +1.76-1.49
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcSTbar_tW="19.56"
xcST_tW="19.56"
#Ref: this is to match OSU
#Ref for other value (35.85 +-0.9, +-1.7 NNLO): https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns 

xcTTJets="831.76"   #NNLO
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcTTtoLL="87.31"  #NNLO        
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcTTtoLfromT="182.7"      
xcTTtoLfromTbar="182.7"   
#NEED PRIMARY REFERENCE
#Other ref: 114 https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DTTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
#Other ref: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO

xcWW="118.7"      
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
#Old value: xcWW="10.32"      

xcZZ="16.523"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
#Old value: xcZZ="63.0"

xcWZ="47.13"                  
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
#Old value: xcWZ="118.7"                  

xcWWToLNuQQ="49.997"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns 

xcWWToLNuLNu="12.178"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWZToL3Nu="3.03"                         
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWZTo3LNu="4.42965"                         
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWZToLNu2QorQQ2L="9.82423165827" 
#Ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DWZToLNu2QorQQ2L_aTGC_13TeV-madgraph-pythia8

xcZZToNuNuQQ="4.04"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcZZToLLQQ="3.22"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcZZToLLNuNu="0.5644"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
#Ref: https://cms-gen-dev.cern.ch/xsdb/?columns=67108863&currentPage=0&pageSize=10&searchQuery=DAS%3DZZTo2L2Nu_13TeV_powheg_pythia8

xcZZToLLLL="1.256"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcWG="405.271"
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

xcZG="117.864"
#Ref: ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8

xcZH_HToBB_ZToLL="0.044333"
xcggZH_HToBB_ZToLL="0.0071462"
xcggZH_HToSSTobbbb="0.0024783"      
xcZH_HToSSTobbbb="0.015374718"      
#https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt13TeV#ZH_Process
#BR(HToSSTobbbb)~20%, BR(ZToll)~10.099%, BR(HToBB)~0.5767

xcWJetsToLNu="61526.7"   
#Ref: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets                  

xcData="1"

countalist () {
 printf "Making %s\n" $1
 root -l -b -q 'countevents.cxx("'$1'")'
 printf "crosssection: %s\n" $2 >> ${listdir}/$1.info
}

 countalist "DY10to50"                            ${xcDY10to50}
 countalist "DY50"                                ${xcDY50}
 countalist "GJets_HT100To200"                    ${xcGJets_HT100To200}                
 countalist "GJets_HT200To400"                    ${xcGJets_HT200To400}                
 countalist "GJets_HT400To600"                    ${xcGJets_HT400To600}                
 countalist "GJets_HT40To100"                     ${xcGJets_HT40To100}                 
 countalist "GJets_HT600ToInf"                    ${xcGJets_HT600ToInf}                
 countalist "ST_s"                                ${xcST_s}
 countalist "ST_t"                                ${xcST_t}
 countalist "ST_tW"                               ${xcST_tW}
 countalist "STbar_t"                             ${xcSTbar_t}
 countalist "STbar_tW"                            ${xcSTbar_tW}
 countalist "TTtoLL"                              ${xcTTtoLL}
 countalist "TTtoLfromT"                          ${xcTTtoLfromT}                      
 countalist "TTtoLfromTbar"                       ${xcTTtoLfromTbar}                   
 countalist "WG"                                  ${xcWG}
 countalist "WJetsToLNu"                          ${xcWJetsToLNu}                      
 countalist "WWToLNuLNu"                          ${xcWWToLNuLNu}                      
 countalist "WWToLNuQQ"                           ${xcWWToLNuQQ}                       
 countalist "WZTo3LNu"                            ${xcWZTo3LNu}
 countalist "WZToL3Nu"                            ${xcWZToL3Nu}
 countalist "WZToLNu2QorQQ2L"                     ${xcWZToLNu2QorQQ2L}                 
 countalist "ZG"                                  ${xcZG}
 countalist "ZH_HToBB_ZToLL"                      ${xcZH_HToBB_ZToLL}                  
 countalist "ZH_HToSSTobbbb_MS15_ctauS1"          ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS15_ctauS10"         ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS15_ctauS100"        ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS15_ctauS1000"       ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS40_ctauS1"          ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS40_ctauS10"         ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS40_ctauS100"        ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS40_ctauS1000"       ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS55_ctauS1"          ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS55_ctauS10"         ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS55_ctauS100"        ${xcZH_HToSSTobbbb}
 countalist "ZH_HToSSTobbbb_MS55_ctauS1000"       ${xcZH_HToSSTobbbb}
 countalist "ZZToLLLL"                            ${xcZZToLLLL}
 countalist "ZZToLLNuNu"                          ${xcZZToLLNuNu}                      
 countalist "ZZToLLQQ"                            ${xcZZToLLQQ}
 countalist "ZZToNuNuQQ"                          ${xcZZToNuNuQQ}                      
 countalist "ggZH_HToBB_ZToLL"                    ${xcggZH_HToBB_ZToLL}                
 countalist "ggZH_HToSSTobbbb_MS15_ctauS1"        ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS15_ctauS10"       ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS15_ctauS100"      ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS15_ctauS1000"     ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS40_ctauS1"        ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS40_ctauS10"       ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS40_ctauS100"      ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS40_ctauS1000"     ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS55_ctauS1"        ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS55_ctauS10"       ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS55_ctauS100"      ${xcggZH_HToSSTobbbb}
 countalist "ggZH_HToSSTobbbb_MS55_ctauS1000"     ${xcggZH_HToSSTobbbb}
 countalist "SingleElectron"                      ${xcData}
 countalist "SingleMuon"                          ${xcData}
 countalist "DoubleEG"                            ${xcData}
 countalist "DoubleMuon"                          ${xcData}
 countalist "MuonEG"                              ${xcData}
 
