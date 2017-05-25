#!/bin/bash

# Makes a list of files in eos
# then greps through to separate into samples
# 
# output files are xxx/lists/<sample>.list
# formatted as one file per line: /store/group/xxx.root

# don't forget to source setup.sh (from xxx/LLDJstandalones)
mkdir -p "${listdir}"

# only works from login.hep.wisc.edu
# ls  /hdfs/store/user/tmperry/rainday/*/*/*/*/*root > ${listdir}/allfiles.list

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
doSingleElectron=true                 
doSingleMuon=true                     
 
makealist () {
 if [ $1 = true ]
 then
  printf "Making %s\n" $2
  fullsamplename=$(grep -i "$3" ${listdir}/allfiles.masterlist)
  printf "%s\n"  ${fullsamplename} > ${listdir}/$2.list
  sed -i -e "s@/hdfs@@" ${listdir}/$2.list
 fi
}

makealist ${doDY50}                            "DY50"                            "/DYJetsToLL_M-50"                                                
makealist ${doDY5to50_HT100to200}              "DY5to50_HT100to200"              "/DYJetsToLL_M-5to50_HT-100to200"                                 
makealist ${doDY5to50_HT200to400}              "DY5to50_HT200to400"              "/DYJetsToLL_M-5to50_HT-200to400"                                 
makealist ${doDY5to50_HT400to600}              "DY5to50_HT400to600"              "/DYJetsToLL_M-5to50_HT-400to600"                                 
makealist ${doDY5to50_HT600toInf}              "DY5to50_HT600toInf"              "/DYJetsToLL_M-5to50_HT-600toInf"                                 
makealist ${doDY5to50_HT70to100}               "DY5to50_HT70to100"               "/DYJetsToLL_M-5to50_HT-70to100"                                  
makealist ${doGJets_HT40To100}                 "GJets_HT40To100"                 "/GJets_HT-40To100"                                       
makealist ${doGJets_HT100To200}                "GJets_HT100To200"                "/GJets_HT-100To200"                                      
makealist ${doGJets_HT200To400}                "GJets_HT200To400"                "/GJets_HT-200To400"                                      
makealist ${doGJets_HT400To600}                "GJets_HT400To600"                "/GJets_HT-400To600"                                      
makealist ${doGJets_HT600ToInf}                "GJets_HT600ToInf"                "/GJets_HT-600ToInf"                                      
makealist ${doST_s}                            "ST_s"                            "/ST_s-channel_4f_leptonDecays"                           
makealist ${doSTbar_t}                         "STbar_t"                         "/ST_t-channel_antitop_4f_inclusiveDecays"                
makealist ${doST_t}                            "ST_t"                            "/ST_t-channel_top_4f_inclusiveDecays"                    
makealist ${doSTbar_tW}                        "STbar_tW"                        "/ST_tW_antitop_5f_inclusiveDecays"                       
makealist ${doST_tW}                           "ST_tW"                           "/ST_tW_top_5f_inclusiveDecays"                           
makealist ${doTTJets}                          "TTJets"                          "/TTJets"                                                 
makealist ${doWW}                              "WW"                              "/WW"                                                     
makealist ${doWZ}                              "WZ"                              "/WZ"                                                     
makealist ${doZZ}                              "ZZ"                              "/ZZ"                                                     
makealist ${doZH_HToBB_ZToLL}                  "ZH_HToBB_ZToLL"                  "/ZH_HToBB_ZToLL"                                         
makealist ${doggZH_HToBB_ZToLL}                "ggZH_HToBB_ZToLL"                "/ggZH_HToBB_ZToLL"                                       
makealist ${doggZH_HToSSTobbbb_MS40_ctauS100}  "ggZH_HToSSTobbbb_MS40_ctauS100"  "/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100"          
makealist ${doggZH_HToSSTodddd_MS40_ctauS100}  "ggZH_HToSSTodddd_MS40_ctauS100"  "/ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100"          
makealist ${doWJetsToLNu}                      "WJetsToLNu"                      "/WJetsToLNu"                                             
makealist ${doSingleElectron}                  "SingleElectron"                  "/SingleElectron"                                         
makealist ${doSingleMuon}                      "SingleMuon"                      "/SingleMuon"                                             

