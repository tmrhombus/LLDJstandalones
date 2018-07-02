#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"
#include <stdio.h>
#include <cstdlib> /* mkdir */

#include <stdlib.h>     /* getenv */

//using namespace std;

void plotter_stackedRegion(TString region, Bool_t dolog, Bool_t HIP )
{

 // Draw signal as lines
 Bool_t drawSignal = kFALSE; //kTRUE;
 Bool_t drawRatio = kTRUE;

 // path to_"+region+"histograms.root files
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));

 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/"+region+"/";

 TString extraname = "";
 if(HIP){
  extraname+="_HIP";
  outpath = outpath+"HIP/";
 }
 if(!HIP){
  outpath = outpath+"Good/";
  extraname+="_Good";
 }

 // lumi scaling for some eras
 Float_t MCSF = 1.;
 Float_t lumiBCDEF = 19691. ;
 Float_t lumiGH = 16226.5 ;
 if(HIP){ MCSF=lumiBCDEF/10000.; }
 else{ MCSF=lumiGH/10000.; }
 
 //TString extraname = "";
 if(dolog){
  extraname+="_log";
  outpath = outpath+"log/";
 }

 TString mdcommand = (TString)"mkdir -p "+outpath.Data();
 const int dir_err = system(mdcommand);

 if(drawSignal){extraname+="_wsig";}
 // lepton flavor
 std::vector<TString> leptons;
 leptons.clear();
 leptons.push_back("ele"); 
 leptons.push_back("mu");  
 //leptons.push_back("NoLepSel");

 // variables to plot
 std::vector<TString> variables;
 variables.clear();

  //variables.push_back("nVtx");                   
  //variables.push_back("nGoodVtx");               
  //variables.push_back("nTrksPV");                
  //variables.push_back("rho");                    
  //variables.push_back("pfMET");                  
  //variables.push_back("pfMETPhi");               
  //variables.push_back("pfMETsumEt");             
  //variables.push_back("nPho");                   
  //variables.push_back("phoE");                   
  //variables.push_back("phoEt");                  
  //variables.push_back("phoEta");                 
  //variables.push_back("phoPhi");                 
  //variables.push_back("nEle");                   
//  variables.push_back("AOD_elePt");                  
//  variables.push_back("AOD_eleEta");                 
//  variables.push_back("AOD_elePhi");                 
//  //variables.push_back("nMu");                    
//  variables.push_back("AOD_muPt");                   
//  //variables.push_back("muEn");                   
//  variables.push_back("AOD_muEta");                  
//  variables.push_back("AOD_muPhi");                  
//  //variables.push_back("nJet");                   
//  variables.push_back("htall"); 
//  variables.push_back("htaodcalojets");
//  //variables.push_back("nSelectedPho");
//  variables.push_back("AOD_nSelectedEle");
//  variables.push_back("AOD_nSelectedMu");
//  variables.push_back("nSelectedAODCaloJet");
//  variables.push_back("nSelectedAODCaloJetTag");
//  variables.push_back("LeadingJet_AODCaloJetPt");                      
//  //variables.push_back("LeadingJet_jetEn");                      
//  variables.push_back("LeadingJet_AODCaloJetEta");                     
//  variables.push_back("LeadingJet_AODCaloJetPhi");                     
//  //variables.push_back("LeadingJet_jetArea");                    
//  //variables.push_back("LeadingJet_jetLeadTrackPt");             
//  //variables.push_back("LeadingJet_jetLeadTrackEta");            
//  //variables.push_back("LeadingJet_jetLeadTrackPhi");            
//  //variables.push_back("LeadingJet_jetCSV2BJetTags");            
//  //variables.push_back("LeadingJet_jetJetProbabilityBJetTags");  
//  //variables.push_back("LeadingJet_jetpfCombinedMVAV2BJetTags"); 
//  //variables.push_back("LeadingJet_jetAlphaMax");                
//  //variables.push_back("LeadingJet_jetAlphaMax2");               
//  //variables.push_back("LeadingJet_jetAlphaMaxP");               
//  //variables.push_back("LeadingJet_jetAlphaMaxP2");              
//  //variables.push_back("LeadingJet_alphaMax_jetDauVertex_r");    
//  //variables.push_back("LeadingJet_jetAlphaMax_PV3onPV2");       
//  //variables.push_back("LeadingJet_jetAlphaMax_PV3onNeu");       
//  //variables.push_back("LeadingJet_jetAlphaMax_PV3onAll");       
//  //variables.push_back("LeadingJet_jetAlphaMax_PV2onNeu");       
//  //variables.push_back("LeadingJet_jetAlphaMax_PV2onAll");       
//  //variables.push_back("LeadingJet_jetAlpha2Max_PV3onPV2");      
//  //variables.push_back("LeadingJet_jetAlpha2Max_PV3onNeu");      
//  //variables.push_back("LeadingJet_jetAlpha2Max_PV3onAll");      
//  //variables.push_back("LeadingJet_jetAlpha2Max_PV2onNeu");      
//  //variables.push_back("LeadingJet_jetAlpha2Max_PV2onAll");      
//  //variables.push_back("LeadingJet_jetAlphaD");                  
//  //variables.push_back("LeadingJet_jetAlphaMaxD");               
//  //variables.push_back("LeadingJet_jetLog10IPSig");              
//  //variables.push_back("LeadingJet_jetMedianLog10IPSig");        
//  //variables.push_back("LeadingJet_jetSumIP");                   
//  //variables.push_back("LeadingJet_jetSumIPSig");                
//  //variables.push_back("LeadingJet_jetTrackAngle");              
//  //variables.push_back("LeadingJet_jetLogTrackAngle");           
//  //variables.push_back("LeadingJet_jetMedianLogTrackAngle");     
//  //variables.push_back("LeadingJet_jetTotalTrackAngle");         
//  //variables.push_back("LeadingJet_jetNConstituents");           
//  //variables.push_back("AllJets_AODCaloJetPtVar");
//  //variables.push_back("AllJets_AODCaloJetPtVar_Tag0");
//  //variables.push_back("AllJets_AODCaloJetdR");
//  //variables.push_back("AllJets_AODCaloJetdR_Tag0");
//  //variables.push_back("AllJets_AODCaloJetNCleanMatchedTracks");
//  //variables.push_back("AllJets_AODCaloJetNCleanMatchedTracks_Tag0");
//  variables.push_back("AllJets_AODCaloJetMedianLog10IPSig");
//  variables.push_back("AllJets_AODCaloJetMedianLog10TrackAngle");
//  variables.push_back("AllJets_AODCaloJetAlphaMax");
  variables.push_back("AllJets_AODCaloJetPt");                      
//  //variables.push_back("AllJets_AODCaloJetEn");                      
//  variables.push_back("AllJets_AODCaloJetEta");                     
//  variables.push_back("AllJets_AODCaloJetPhi");                     

 // make canvas and text
 int canx = 1100;
 int cany = 1200;
 float lmarg = 0.12;
 float rmarg = 0.05;
 
 TCanvas* canvas = new TCanvas("canvas","canvas",canx,cany); 

 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kBird);

 canvas->Clear();
 canvas->cd();

 TPad *pad1  = new TPad("pad1", "pad1", 0, 0.25, 1, 1);
 pad1->SetBottomMargin(0.04);
 pad1->SetLeftMargin(lmarg);
 pad1->SetRightMargin(rmarg);
 pad1->SetFrameLineWidth(3);
 pad1->SetLogy(dolog);
 pad1->Draw();

 canvas->cd();
 TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.25);
 pad2->SetTopMargin(0.04);
 pad2->SetBottomMargin(0.4);
 pad2->SetFrameLineWidth(3);
 pad2->SetLeftMargin(lmarg);
 pad2->SetRightMargin(rmarg);
 pad2->SetLogy(0);
 pad2->SetGrid();
 pad2->Draw();
 canvas->cd();

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.06);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.05);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* extra2 = new TText(1,1,"") ;
 extra2->SetTextSize(0.03);
 extra2->SetTextColor(kBlack);
 extra2->SetTextAlign(11);
 //extra2->SetTextAlign(13);
 extra2->SetTextFont(62);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.05);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // initialize histogram files 
 TFile* file_Data_SingleMu_H_3       ; 
 TFile* file_Data_SingleMu_H_2       ; 
 TFile* file_Data_SingleMu_G         ; 
 TFile* file_Data_SingleMu_F         ; 
 TFile* file_Data_SingleMu_E         ; 
 TFile* file_Data_SingleMu_D         ; 
 TFile* file_Data_SingleMu_C         ; 
 TFile* file_Data_SingleMu_B_2       ; 
 TFile* file_Data_SingleEle_H_3      ; 
 TFile* file_Data_SingleEle_H_2      ; 
 TFile* file_Data_SingleEle_G        ; 
 TFile* file_Data_SingleEle_F        ; 
 TFile* file_Data_SingleEle_E        ; 
 TFile* file_Data_SingleEle_D        ; 
 TFile* file_Data_SingleEle_C        ; 
 TFile* file_Data_SingleEle_B_2      ; 
 TFile* file_Data_SinglePhoton_H_3   ; 
 TFile* file_Data_SinglePhoton_H_2   ; 
 TFile* file_Data_SinglePhoton_G     ; 
 TFile* file_Data_SinglePhoton_F     ; 
 TFile* file_Data_SinglePhoton_E     ; 
 TFile* file_Data_SinglePhoton_D     ; 
 TFile* file_Data_SinglePhoton_C     ; 
 TFile* file_Data_SinglePhoton_B_2   ; 
 TFile* file_Data_DoubleMu_H_3       ; 
 TFile* file_Data_DoubleMu_H_2       ; 
 TFile* file_Data_DoubleMu_G         ; 
 TFile* file_Data_DoubleMu_F         ; 
 TFile* file_Data_DoubleMu_E         ; 
 TFile* file_Data_DoubleMu_D         ; 
 TFile* file_Data_DoubleMu_C         ; 
 TFile* file_Data_DoubleMu_B_2       ; 
 TFile* file_Data_DoubleEG_H_3       ; 
 TFile* file_Data_DoubleEG_H_2       ; 
 TFile* file_Data_DoubleEG_G         ; 
 TFile* file_Data_DoubleEG_F         ; 
 TFile* file_Data_DoubleEG_E         ; 
 TFile* file_Data_DoubleEG_D         ; 
 TFile* file_Data_DoubleEG_C         ; 
 TFile* file_Data_DoubleEG_B_2       ; 
 TFile* file_DY50                                ;
 TFile* file_DY5to50_HT100To200                  ; 
 TFile* file_DY5to50_HT200To400                  ; 
 TFile* file_DY5to50_HT400To600                  ; 
 TFile* file_DY5to50_HT600ToInf                  ; 
 TFile* file_DY10to50                            ; 
 TFile* file_ggZH_HToBB_ZToLL                    ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS0        ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS0p05     ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS1        ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS10       ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS100      ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS1000     ;
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS10000    ;
 TFile* file_GJets_HT40To100                     ;
 TFile* file_GJets_HT100To200                    ;
 TFile* file_GJets_HT200To400                    ;
 TFile* file_GJets_HT400To600                    ;
 TFile* file_GJets_HT600ToInf                    ;
 TFile* file_ST_s                                ;
 TFile* file_STbar_t                             ;
 TFile* file_ST_t                                ;
 TFile* file_STbar_tW                            ;
 TFile* file_ST_tW                               ;
 TFile* file_TTtoLL                              ;
 TFile* file_TTJets                              ;
 TFile* file_TTtoLfromTbar                       ;
 TFile* file_TTtoLfromT                          ;
 TFile* file_WG                                  ;
 TFile* file_WJetsToLNu                          ;
 TFile* file_WW                                  ;
 TFile* file_WZ                                  ;
 TFile* file_WWToLNuLNu                          ;
 TFile* file_WWToLNuQQ                           ;
 TFile* file_WZToL3Nu                            ;
 TFile* file_WZTo3LNu                            ;
 TFile* file_WZToLNu2QorQQ2L                     ;
 TFile* file_ZGTo2LG                             ;
 TFile* file_ZH_HToBB_ZToLL                      ;
 TFile* file_ZZ                                  ;
 TFile* file_ZZToLLNuNu                          ;
 TFile* file_ZZToLLQQ                            ;
 TFile* file_ZZToNuNuQQ                          ;
 TFile* file_ZZToLLLL                            ;

 // initialize histos
 TH1F* h_DY50                                ;
 TH1F* h_DY5to50_HT100To200                  ; 
 TH1F* h_DY5to50_HT200To400                  ; 
 TH1F* h_DY5to50_HT400To600                  ; 
 TH1F* h_DY5to50_HT600ToInf                  ; 
 TH1F* h_DY10to50                            ; 
 TH1F* h_ggZH_HToBB_ZToLL                    ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS0        ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS0p05     ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS1        ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS10       ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS100      ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS1000     ;
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS10000    ;
 TH1F* h_GJets_HT40To100                     ;
 TH1F* h_GJets_HT100To200                    ;
 TH1F* h_GJets_HT200To400                    ;
 TH1F* h_GJets_HT400To600                    ;
 TH1F* h_GJets_HT600ToInf                    ;
 TH1F* h_ST_s                                ;
 TH1F* h_STbar_t                             ;
 TH1F* h_ST_t                                ;
 TH1F* h_STbar_tW                            ;
 TH1F* h_ST_tW                               ;
 TH1F* h_TTtoLL                              ;
 TH1F* h_TTJets                              ;
 TH1F* h_TTtoLfromTbar                       ;
 TH1F* h_TTtoLfromT                          ;
 TH1F* h_WG                                  ;
 TH1F* h_WJetsToLNu                          ;
 TH1F* h_WW                                  ;
 TH1F* h_WZ                                  ;
 TH1F* h_WWToLNuLNu                          ;
 TH1F* h_WWToLNuQQ                           ;
 TH1F* h_WZToL3Nu                            ;
 TH1F* h_WZTo3LNu                            ;
 TH1F* h_WZToLNu2QorQQ2L                     ;
 TH1F* h_ZG                                  ;
 TH1F* h_ZH_HToBB_ZToLL                      ;
 TH1F* h_ZZ                                  ;
 TH1F* h_ZZToLLNuNu                          ;
 TH1F* h_ZZToLLQQ                            ;
 TH1F* h_ZZToNuNuQQ                          ;
 TH1F* h_ZZToLLLL                            ;
 TH1F* h_SingleElectronHIP                   ;
 TH1F* h_SingleMuonHIP                       ;
 TH1F* h_SingleElectronGood                  ;
 TH1F* h_SingleMuonGood                      ;
 TH1F* h_Data_SingleMu_H_3     ;
 TH1F* h_Data_SingleMu_H_2     ;
 TH1F* h_Data_SingleMu_G       ;
 TH1F* h_Data_SingleMu_F       ;
 TH1F* h_Data_SingleMu_E       ;
 TH1F* h_Data_SingleMu_D       ;
 TH1F* h_Data_SingleMu_C       ;
 TH1F* h_Data_SingleMu_B_2     ;
 TH1F* h_Data_SingleEle_H_3    ;
 TH1F* h_Data_SingleEle_H_2    ;
 TH1F* h_Data_SingleEle_G      ;
 TH1F* h_Data_SingleEle_F      ;
 TH1F* h_Data_SingleEle_E      ;
 TH1F* h_Data_SingleEle_D      ;
 TH1F* h_Data_SingleEle_C      ;
 TH1F* h_Data_SingleEle_B_2    ;
 TH1F* h_Data_SinglePhoton_H_3 ;
 TH1F* h_Data_SinglePhoton_H_2 ;
 TH1F* h_Data_SinglePhoton_G   ;
 TH1F* h_Data_SinglePhoton_F   ;
 TH1F* h_Data_SinglePhoton_E   ;
 TH1F* h_Data_SinglePhoton_D   ;
 TH1F* h_Data_SinglePhoton_C   ;
 TH1F* h_Data_SinglePhoton_B_2 ;
 TH1F* h_Data_DoubleMu_H_3     ;
 TH1F* h_Data_DoubleMu_H_2     ;
 TH1F* h_Data_DoubleMu_G       ;
 TH1F* h_Data_DoubleMu_F       ;
 TH1F* h_Data_DoubleMu_E       ;
 TH1F* h_Data_DoubleMu_D       ;
 TH1F* h_Data_DoubleMu_C       ;
 TH1F* h_Data_DoubleMu_B_2     ;
 TH1F* h_Data_DoubleEG_H_3     ;
 TH1F* h_Data_DoubleEG_H_2     ;
 TH1F* h_Data_DoubleEG_G       ;
 TH1F* h_Data_DoubleEG_F       ;
 TH1F* h_Data_DoubleEG_E       ;
 TH1F* h_Data_DoubleEG_D       ;
 TH1F* h_Data_DoubleEG_C       ;
 TH1F* h_Data_DoubleEG_B_2     ;
 TH1F* h_ratio ;
 TH1F* h_ratiostaterr ;

 // (combined) histos to be made
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_VG     ;
 TH1F* h_ZH     ;
 TH1F* h_TT     ;
 TH1F* h_bkgtotal ;

 TH1F* h_Data   ;
 //cout << "IN path: "<< inpath<<endl;
 // load histogram files
// file_DY5to50_HT100To200                = new TFile( inpath + "DY5to50_HT100To200_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT200To400                = new TFile( inpath + "DY5to50_HT200To400_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT400To600                = new TFile( inpath + "DY5to50_HT400To600_"+region+"_histograms.root"               ) ; 
// file_DY5to50_HT600ToInf                = new TFile( inpath + "DY5to50_HT600ToInf_"+region+"_histograms.root"               ) ; 
// file_DY10to50                          = new TFile( inpath + "DY10to50_"+region+"_histograms.root"                          ) ; 
 file_DY50                              = new TFile( inpath + "DYJetsToLL_M-50_"+region+"_histograms.root"                             ) ;
 ///file_DY50                              = new TFile( inpath + "DY50_"+region+"_histograms.root"                             ) ;

// file_ggZH_HToSSTobbbb_MS40_ctauS0      = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS0_"+region+"_histograms.root"     ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS0p05   = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS0p05_"+region+"_histograms.root"  ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS1      = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS1_"+region+"_histograms.root"     ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS10     = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS10_"+region+"_histograms.root"    ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS100    = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS100_"+region+"_histograms.root"   ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS1000   = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS1000_"+region+"_histograms.root"  ) ;
// file_ggZH_HToSSTobbbb_MS40_ctauS10000  = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS10000_"+region+"_histograms.root" ) ;
 file_GJets_HT40To100                   = new TFile( inpath + "GJets_HT-40To100_"+region+"_histograms.root"                  ) ;
 file_GJets_HT100To200                  = new TFile( inpath + "GJets_HT-100To200_"+region+"_histograms.root"                 ) ;
 file_GJets_HT200To400                  = new TFile( inpath + "GJets_HT-200To400_"+region+"_histograms.root"                 ) ;
 file_GJets_HT400To600                  = new TFile( inpath + "GJets_HT-400To600_"+region+"_histograms.root"                 ) ;
 file_GJets_HT600ToInf                  = new TFile( inpath + "GJets_HT-600ToInf_"+region+"_histograms.root"                 ) ;
 file_ST_s                              = new TFile( inpath + "ST_s-channel_4f_leptonDecays_"+region+"_histograms.root"                             ) ;
 file_STbar_t                           = new TFile( inpath + "ST_t-channel_antitop_4f_inclusiveDecays_"+region+"_histograms.root"                          ) ;
 file_ST_t                              = new TFile( inpath + "ST_t-channel_top_4f_inclusiveDecays_"+region+"_histograms.root"                             ) ;
 file_STbar_tW                          = new TFile( inpath + "ST_tW_antitop_5f_NoFullyHadronicDecays_"+region+"_histograms.root"                         ) ;
 file_ST_tW                             = new TFile( inpath + "ST_tW_top_5f_NoFullyHadronicDecays_"+region+"_histograms.root"                            ) ;
 //file_TTtoLL                            = new TFile( inpath + "TTtoLL_"+region+"_histograms.root"                           ) ;
 file_TTJets                            = new TFile( inpath + "TTJets_"+region+"_histograms.root"                           ) ;
 //file_TTtoLfromTbar                     = new TFile( inpath + "TTtoLfromTbar_"+region+"_histograms.root"                    ) ;
 //file_TTtoLfromT                        = new TFile( inpath + "TTtoLfromT_"+region+"_histograms.root"                       ) ;
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000_DY_histograms.root 
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10_DY_histograms.root
//ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10_DY_histograms.root
//ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1_DY_histograms.root
 file_WJetsToLNu                        = new TFile( inpath + "WJetsToLNu_"+region+"_histograms.root"                       ) ;
 file_WG                                = new TFile( inpath + "WGToLNuG_"+region+"_histograms.root"                         ) ;
 file_ZGTo2LG                           = new TFile( inpath + "ZGTo2LG_"+region+"_histograms.root"                               ) ;
 file_WW                                = new TFile( inpath + "WW_"+region+"_histograms.root"                               ) ;
 file_WZ                                = new TFile( inpath + "WZ_"+region+"_histograms.root"                               ) ;
 file_ZZ                                = new TFile( inpath + "ZZ_"+region+"_histograms.root"                               ) ;
 //file_WWToLNuLNu                        = new TFile( inpath + "WWToLNuLNu_"+region+"_histograms.root"                       ) ;
 //file_WWToLNuQQ                         = new TFile( inpath + "WWToLNuQQ_"+region+"_histograms.root"                        ) ;
 //file_WZToL3Nu                          = new TFile( inpath + "WZToL3Nu_"+region+"_histograms.root"                         ) ;
 //file_WZTo3LNu                          = new TFile( inpath + "WZTo3LNu_"+region+"_histograms.root"                         ) ;
 //file_WZToLNu2QorQQ2L                   = new TFile( inpath + "WZToLNu2QorQQ2L_"+region+"_histograms.root"                  ) ;
 file_ZH_HToBB_ZToLL                    = new TFile( inpath + "ZH_HToBB_ZToLL_"+region+"_histograms.root"                   ) ;
 file_ggZH_HToBB_ZToLL                  = new TFile( inpath + "ggZH_HToBB_ZToLL_"+region+"_histograms.root"                 ) ;
 //file_ZZToLLNuNu                        = new TFile( inpath + "ZZToLLNuNu_"+region+"_histograms.root"                       ) ;
 //file_ZZToLLQQ                          = new TFile( inpath + "ZZToLLQQ_"+region+"_histograms.root"                         ) ;
 //file_ZZToNuNuQQ                        = new TFile( inpath + "ZZToNuNuQQ_"+region+"_histograms.root"                       ) ;
 //file_ZZToLLLL                          = new TFile( inpath + "ZZToLLLL_"+region+"_histograms.root"                         ) ;

// file_Data_SingleMu_H_3             =  new TFile( inpath + "Data_SingleMu_H_3_"+region+"_histograms.root"     ) ; 
// file_Data_SingleMu_H_2             =  new TFile( inpath + "Data_SingleMu_H_2_"+region+"_histograms.root"     ) ; 
// file_Data_SingleMu_G               =  new TFile( inpath + "Data_SingleMu_G_"+region+"_histograms.root"       ) ; 
// file_Data_SingleMu_F               =  new TFile( inpath + "Data_SingleMu_F_"+region+"_histograms.root"       ) ; 
// file_Data_SingleMu_E               =  new TFile( inpath + "Data_SingleMu_E_"+region+"_histograms.root"       ) ; 
// file_Data_SingleMu_D               =  new TFile( inpath + "Data_SingleMu_D_"+region+"_histograms.root"       ) ; 
// file_Data_SingleMu_C               =  new TFile( inpath + "Data_SingleMu_C_"+region+"_histograms.root"       ) ; 
// file_Data_SingleMu_B_2             =  new TFile( inpath + "Data_SingleMu_B_2_"+region+"_histograms.root"     ) ; 
// file_Data_SingleEle_H_3            =  new TFile( inpath + "Data_SingleEle_H_3_"+region+"_histograms.root"    ) ; 
// file_Data_SingleEle_H_2            =  new TFile( inpath + "Data_SingleEle_H_2_"+region+"_histograms.root"    ) ; 
// file_Data_SingleEle_G            =  new TFile( inpath + "Data_SingleEle_G_"+region+"_histograms.root"    ) ; 
// file_Data_SingleEle_F              =  new TFile( inpath + "Data_SingleEle_F_"+region+"_histograms.root"      ) ; 
// file_Data_SingleEle_E              =  new TFile( inpath + "Data_SingleEle_E_"+region+"_histograms.root"      ) ; 
// file_Data_SingleEle_D              =  new TFile( inpath + "Data_SingleEle_D_"+region+"_histograms.root"      ) ; 
// file_Data_SingleEle_C              =  new TFile( inpath + "Data_SingleEle_C_"+region+"_histograms.root"      ) ; 
// file_Data_SingleEle_B_2            =  new TFile( inpath + "Data_SingleEle_B_2_"+region+"_histograms.root"    ) ; 
// file_Data_SinglePhoton_H_3         =  new TFile( inpath + "Data_SinglePhoton_H_3_"+region+"_histograms.root" ) ; 
// file_Data_SinglePhoton_H_2         =  new TFile( inpath + "Data_SinglePhoton_H_2_"+region+"_histograms.root" ) ; 
// file_Data_SinglePhoton_G           =  new TFile( inpath + "Data_SinglePhoton_G_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_F           =  new TFile( inpath + "Data_SinglePhoton_F_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_E           =  new TFile( inpath + "Data_SinglePhoton_E_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_D           =  new TFile( inpath + "Data_SinglePhoton_D_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_C           =  new TFile( inpath + "Data_SinglePhoton_C_"+region+"_histograms.root"   ) ; 
// file_Data_SinglePhoton_B_2         =  new TFile( inpath + "Data_SinglePhoton_B_2_"+region+"_histograms.root" ) ; 
 file_Data_DoubleMu_H_3             =  new TFile( inpath + "Data_DoubleMu_H_3_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleMu_H_2             =  new TFile( inpath + "Data_DoubleMu_H_2_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleMu_G               =  new TFile( inpath + "Data_DoubleMu_G_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_F               =  new TFile( inpath + "Data_DoubleMu_F_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_E               =  new TFile( inpath + "Data_DoubleMu_E_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_D               =  new TFile( inpath + "Data_DoubleMu_D_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_C               =  new TFile( inpath + "Data_DoubleMu_C_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleMu_B_2             =  new TFile( inpath + "Data_DoubleMu_B_2_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleEG_H_3             =  new TFile( inpath + "Data_DoubleEG_H_3_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleEG_H_2             =  new TFile( inpath + "Data_DoubleEG_H_2_"+region+"_histograms.root"     ) ; 
 file_Data_DoubleEG_G               =  new TFile( inpath + "Data_DoubleEG_G_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_F               =  new TFile( inpath + "Data_DoubleEG_F_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_E               =  new TFile( inpath + "Data_DoubleEG_E_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_D               =  new TFile( inpath + "Data_DoubleEG_D_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_C               =  new TFile( inpath + "Data_DoubleEG_C_"+region+"_histograms.root"       ) ; 
// file_Data_DoubleEG_B_2             =  new TFile( inpath + "Data_DoubleEG_B_2_"+region+"_histograms.root"     ) ; 

/// file_SingleElectronGood                = new TFile( inpath + "Data_SingleEle_Good_"+region+"_histograms.root"              ) ;
/// file_SingleMuonGood                    = new TFile( inpath + "Data_SingleMu_Good_"+region+"_histograms.root"               ) ;
/// file_SingleElectronHIP                 = new TFile( inpath + "Data_SingleEle_HIP_"+region+"_histograms.root"               ) ;
/// file_SingleMuonHIP                     = new TFile( inpath + "Data_SingleMu_HIP_"+region+"_histograms.root"                ) ;
// file_DoubleEG                          = new TFile( inpath + "DoubleEG_"+region+"_histograms.root"                         ) ;
// file_DoubleMuon                        = new TFile( inpath + "DoubleMuon_"+region+"_histograms.root"                       ) ;
// file_MuonEG                            = new TFile( inpath + "MuonEG_"+region+"_histograms.root"                           ) ;

  for(unsigned int j=0; j<variables.size(); ++j){
   TString variable = variables[j];
   for(unsigned int k=0; k<leptons.size(); ++k){
    TString lepton = leptons[k];

    TString varname = lepton+"_"+region+"_"+variable;

    printf("plotting  h_%s \n",varname.Data());
    TString outname = outpath+varname+extraname; 
    TString logname = outpath+"logs/"+varname+extraname; 
    //cout << "logname: " << logname << endl;

    // get histograms from files
//    h_DY10to50                          = (TH1F*)file_DY10to50                         ->Get("h_"+varname)->Clone( "DY10to50"                         ) ;
//    h_DY5to50_HT100To200                = (TH1F*)file_DY5to50_HT100To200               ->Get("h_"+varname)->Clone( "DY5to50_HT100To200"               ) ; 
//    h_DY5to50_HT200To400                = (TH1F*)file_DY5to50_HT200To400               ->Get("h_"+varname)->Clone( "DY5to50_HT200To400"               ) ; 
//    h_DY5to50_HT400To600                = (TH1F*)file_DY5to50_HT400To600               ->Get("h_"+varname)->Clone( "DY5to50_HT400To600"               ) ; 
//    h_DY5to50_HT600ToInf                = (TH1F*)file_DY5to50_HT600ToInf               ->Get("h_"+varname)->Clone( "DY5to50_HT600ToInf"               ) ; 
    //h_DY5to50_HT70To100                 = (TH1F*)file_DY5to50_HT70To100                ->Get("h_"+varname)->Clone( "DY5to50_HT70To100"                ) ; 
    h_DY50                              = (TH1F*)file_DY50                             ->Get("h_"+varname)->Clone( "DY50"                             ) ;
    //h_DY50->Scale(35900.0/20000.0); 
    h_ggZH_HToBB_ZToLL                  = (TH1F*)file_ggZH_HToBB_ZToLL                 ->Get("h_"+varname)->Clone( "ggZH_HToBB_ZToLL"                 ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS0      = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS0     ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS0"     ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS0p05   = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS0p05"  ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1      = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS1     ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS1"     ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10     = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS10    ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS10"    ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS100    = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS100   ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS100"   ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1000   = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS1000"  ) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10000  = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS10000" ) ;
    h_GJets_HT40To100                   = (TH1F*)file_GJets_HT40To100                  ->Get("h_"+varname)->Clone( "GJets_HT40To100"                  ) ;
    h_GJets_HT100To200                  = (TH1F*)file_GJets_HT100To200                 ->Get("h_"+varname)->Clone( "GJets_HT100To200"                 ) ;
    h_GJets_HT200To400                  = (TH1F*)file_GJets_HT200To400                 ->Get("h_"+varname)->Clone( "GJets_HT200To400"                 ) ;
    h_GJets_HT400To600                  = (TH1F*)file_GJets_HT400To600                 ->Get("h_"+varname)->Clone( "GJets_HT400To600"                 ) ;
    h_GJets_HT600ToInf                  = (TH1F*)file_GJets_HT600ToInf                 ->Get("h_"+varname)->Clone( "GJets_HT600ToInf"                 ) ;
    h_ST_s                              = (TH1F*)file_ST_s                             ->Get("h_"+varname)->Clone( "ST_s"                             ) ;
    h_STbar_t                           = (TH1F*)file_STbar_t                          ->Get("h_"+varname)->Clone( "STbar_t"                          ) ;
    h_ST_t                              = (TH1F*)file_ST_t                             ->Get("h_"+varname)->Clone( "ST_t"                             ) ;
    h_STbar_tW                          = (TH1F*)file_STbar_tW                         ->Get("h_"+varname)->Clone( "STbar_tW"                         ) ;
    h_ST_tW                             = (TH1F*)file_ST_tW                            ->Get("h_"+varname)->Clone( "ST_tW"                            ) ;
    //h_TTtoLL                            = (TH1F*)file_TTtoLL                           ->Get("h_"+varname)->Clone( "TTtoLL"                           ) ;
    h_TTJets                            = (TH1F*)file_TTJets                           ->Get("h_"+varname)->Clone( "TTJets"                           ) ;
    //h_TTtoLfromTbar                     = (TH1F*)file_TTtoLfromTbar                    ->Get("h_"+varname)->Clone( "TTtoLfromTbar"                    ) ;
    //h_TTtoLfromT                        = (TH1F*)file_TTtoLfromT                       ->Get("h_"+varname)->Clone( "TTtoLfromT"                       ) ;
    h_WG                                = (TH1F*)file_WG                               ->Get("h_"+varname)->Clone( "WG"                               ) ;
    h_WJetsToLNu                        = (TH1F*)file_WJetsToLNu                       ->Get("h_"+varname)->Clone( "WJetsToLNu"                       ) ;
    h_WW                                = (TH1F*)file_WW                               ->Get("h_"+varname)->Clone( "WW"                               ) ;
    h_WZ                                = (TH1F*)file_WZ                               ->Get("h_"+varname)->Clone( "WZ"                               ) ;
    //h_WWToLNuLNu                        = (TH1F*)file_WWToLNuLNu                       ->Get("h_"+varname)->Clone( "WWToLNuLNu"                       ) ;
    //h_WWToLNuQQ                         = (TH1F*)file_WWToLNuQQ                        ->Get("h_"+varname)->Clone( "WWToLNuQQ"                        ) ;
    //h_WZToL3Nu                          = (TH1F*)file_WZToL3Nu                         ->Get("h_"+varname)->Clone( "WZToL3Nu"                         ) ;
    //h_WZTo3LNu                          = (TH1F*)file_WZTo3LNu                         ->Get("h_"+varname)->Clone( "WZTo3LNu"                         ) ;
    //h_WZToLNu2QorQQ2L                   = (TH1F*)file_WZToLNu2QorQQ2L                  ->Get("h_"+varname)->Clone( "WZToLNu2QorQQ2L"                  ) ;
    h_ZG                                = (TH1F*)file_ZGTo2LG                          ->Get("h_"+varname)->Clone( "ZG"                               ) ;
    h_ZH_HToBB_ZToLL                    = (TH1F*)file_ZH_HToBB_ZToLL                   ->Get("h_"+varname)->Clone( "ZH_HToBB_ZToLL"                   ) ;
    h_ZZ                                = (TH1F*)file_ZZ                               ->Get("h_"+varname)->Clone( "ZZ"                               ) ;
    //h_ZZToLLNuNu                        = (TH1F*)file_ZZToLLNuNu                       ->Get("h_"+varname)->Clone( "ZZToLLNuNu"                       ) ;
    //h_ZZToLLQQ                          = (TH1F*)file_ZZToLLQQ                         ->Get("h_"+varname)->Clone( "ZZToLLQQ"                         ) ;
    //h_ZZToNuNuQQ                        = (TH1F*)file_ZZToNuNuQQ                       ->Get("h_"+varname)->Clone( "ZZToNuNuQQ"                       ) ;
    //h_ZZToLLLL                          = (TH1F*)file_ZZToLLLL                         ->Get("h_"+varname)->Clone( "ZZToLLLL"                         ) ;
    //h_ZZToLLLL->Scale(35900.0/20000.0); 
//    h_SingleElectronGood                = (TH1F*)file_SingleElectronGood               ->Get("h_"+varname)->Clone( "SingleElectronGood"               ) ;
//    h_SingleElectronGood->Scale(35917.4/16203.725);
//    h_SingleMuonGood                    = (TH1F*)file_SingleMuonGood                   ->Get("h_"+varname)->Clone( "SingleMuonGood"                   ) ;
//    h_SingleMuonGood->Scale(35917.4/16226.445);
//    h_SingleElectronHIP                 = (TH1F*)file_SingleElectronHIP                ->Get("h_"+varname)->Clone( "SingleElectronHIP"                ) ;
//    h_SingleElectronHIP->Scale(35917.4/19695.05);
//    h_SingleMuonHIP                     = (TH1F*)file_SingleMuonHIP                    ->Get("h_"+varname)->Clone( "SingleMuonHIP"                    ) ;
//    h_SingleMuonHIP->Scale(35917.4/19690.94);

// h_Data_SingleMu_H_3     = (TH1F*) file_Data_SingleMu_H_3     -> Get("h_"+varname)->Clone( "Data_SingleMu_H_3"      ) ; 
// h_Data_SingleMu_H_2     = (TH1F*) file_Data_SingleMu_H_2     -> Get("h_"+varname)->Clone( "Data_SingleMu_H_2"      ) ; 
// h_Data_SingleMu_G       = (TH1F*) file_Data_SingleMu_G       -> Get("h_"+varname)->Clone( "Data_SingleMu_G"        ) ; 
// h_Data_SingleMu_F       = (TH1F*) file_Data_SingleMu_F       -> Get("h_"+varname)->Clone( "Data_SingleMu_F"        ) ; 
// h_Data_SingleMu_E       = (TH1F*) file_Data_SingleMu_E       -> Get("h_"+varname)->Clone( "Data_SingleMu_E"        ) ; 
// h_Data_SingleMu_D       = (TH1F*) file_Data_SingleMu_D       -> Get("h_"+varname)->Clone( "Data_SingleMu_D"        ) ; 
// h_Data_SingleMu_C       = (TH1F*) file_Data_SingleMu_C       -> Get("h_"+varname)->Clone( "Data_SingleMu_C"        ) ; 
// h_Data_SingleMu_B_2     = (TH1F*) file_Data_SingleMu_B_2     -> Get("h_"+varname)->Clone( "Data_SingleMu_B_2"      ) ; 
// h_Data_SingleEle_H_3    = (TH1F*) file_Data_SingleEle_H_3    -> Get("h_"+varname)->Clone( "Data_SingleEle_H_3"     ) ; 
// h_Data_SingleEle_H_2    = (TH1F*) file_Data_SingleEle_H_2    -> Get("h_"+varname)->Clone( "Data_SingleEle_H_2"     ) ; 
// h_Data_SingleEle_G      = (TH1F*) file_Data_SingleEle_G    -> Get("h_"+varname)->Clone( "Data_SingleEle_G"     ) ; 
// h_Data_SingleEle_F      = (TH1F*) file_Data_SingleEle_F      -> Get("h_"+varname)->Clone( "Data_SingleEle_F"       ) ; 
// h_Data_SingleEle_E      = (TH1F*) file_Data_SingleEle_E      -> Get("h_"+varname)->Clone( "Data_SingleEle_E"       ) ; 
// h_Data_SingleEle_D      = (TH1F*) file_Data_SingleEle_D      -> Get("h_"+varname)->Clone( "Data_SingleEle_D"       ) ; 
// h_Data_SingleEle_C      = (TH1F*) file_Data_SingleEle_C      -> Get("h_"+varname)->Clone( "Data_SingleEle_C"       ) ; 
// h_Data_SingleEle_B_2    = (TH1F*) file_Data_SingleEle_B_2    -> Get("h_"+varname)->Clone( "Data_SingleEle_B_2"     ) ; 
// h_Data_SinglePhoton_H_3 = (TH1F*) file_Data_SinglePhoton_H_3 -> Get("h_"+varname)->Clone( "Data_SinglePhoton_H_3"  ) ; 
// h_Data_SinglePhoton_H_2 = (TH1F*) file_Data_SinglePhoton_H_2 -> Get("h_"+varname)->Clone( "Data_SinglePhoton_H_2"  ) ; 
// h_Data_SinglePhoton_G   = (TH1F*) file_Data_SinglePhoton_G   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_G"    ) ; 
// h_Data_SinglePhoton_F   = (TH1F*) file_Data_SinglePhoton_F   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_F"    ) ; 
// h_Data_SinglePhoton_E   = (TH1F*) file_Data_SinglePhoton_E   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_E"    ) ; 
// h_Data_SinglePhoton_D   = (TH1F*) file_Data_SinglePhoton_D   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_D"    ) ; 
// h_Data_SinglePhoton_C   = (TH1F*) file_Data_SinglePhoton_C   -> Get("h_"+varname)->Clone( "Data_SinglePhoton_C"    ) ; 
// h_Data_SinglePhoton_B_2 = (TH1F*) file_Data_SinglePhoton_B_2 -> Get("h_"+varname)->Clone( "Data_SinglePhoton_B_2"  ) ; 
 h_Data_DoubleMu_H_3     = (TH1F*) file_Data_DoubleMu_H_3     -> Get("h_"+varname)->Clone( "Data_DoubleMu_H_3"      ) ; 
 h_Data_DoubleMu_H_2     = (TH1F*) file_Data_DoubleMu_H_2     -> Get("h_"+varname)->Clone( "Data_DoubleMu_H_2"      ) ; 
 h_Data_DoubleMu_G       = (TH1F*) file_Data_DoubleMu_G       -> Get("h_"+varname)->Clone( "Data_DoubleMu_G"        ) ; 
// h_Data_DoubleMu_F       = (TH1F*) file_Data_DoubleMu_F       -> Get("h_"+varname)->Clone( "Data_DoubleMu_F"        ) ; 
// h_Data_DoubleMu_E       = (TH1F*) file_Data_DoubleMu_E       -> Get("h_"+varname)->Clone( "Data_DoubleMu_E"        ) ; 
// h_Data_DoubleMu_D       = (TH1F*) file_Data_DoubleMu_D       -> Get("h_"+varname)->Clone( "Data_DoubleMu_D"        ) ; 
// h_Data_DoubleMu_C       = (TH1F*) file_Data_DoubleMu_C       -> Get("h_"+varname)->Clone( "Data_DoubleMu_C"        ) ; 
// h_Data_DoubleMu_B_2     = (TH1F*) file_Data_DoubleMu_B_2     -> Get("h_"+varname)->Clone( "Data_DoubleMu_B_2"      ) ; 
 h_Data_DoubleEG_H_3     = (TH1F*) file_Data_DoubleEG_H_3     -> Get("h_"+varname)->Clone( "Data_DoubleEG_H_3"      ) ; 
 h_Data_DoubleEG_H_2     = (TH1F*) file_Data_DoubleEG_H_2     -> Get("h_"+varname)->Clone( "Data_DoubleEG_H_2"      ) ; 
 h_Data_DoubleEG_G       = (TH1F*) file_Data_DoubleEG_G       -> Get("h_"+varname)->Clone( "Data_DoubleEG_G"        ) ; 
// h_Data_DoubleEG_F       = (TH1F*) file_Data_DoubleEG_F       -> Get("h_"+varname)->Clone( "Data_DoubleEG_F"        ) ; 
// h_Data_DoubleEG_E       = (TH1F*) file_Data_DoubleEG_E       -> Get("h_"+varname)->Clone( "Data_DoubleEG_E"        ) ; 
// h_Data_DoubleEG_D       = (TH1F*) file_Data_DoubleEG_D       -> Get("h_"+varname)->Clone( "Data_DoubleEG_D"        ) ; 
// h_Data_DoubleEG_C       = (TH1F*) file_Data_DoubleEG_C       -> Get("h_"+varname)->Clone( "Data_DoubleEG_C"        ) ; 
// h_Data_DoubleEG_B_2     = (TH1F*) file_Data_DoubleEG_B_2     -> Get("h_"+varname)->Clone( "Data_DoubleEG_B_2"      ) ; 
    
    //h_DoubleEG                          = (TH1F*)file_DoubleEG                         ->Get("h_"+varname)->Clone( "DoubleEG"                         ) ;
    //h_DoubleMuon                        = (TH1F*)file_DoubleMuon                       ->Get("h_"+varname)->Clone( "DoubleMuon"                       ) ;
    //h_MuonEG                            = (TH1F*)file_MuonEG                           ->Get("h_"+varname)->Clone( "MuonEG"                           ) ;
/// //
/// ////cout<<"test"<<endl;
/// //    // integrals of histograms
/// //    Double_t int_DY5to50_HT100To200                = h_DY5to50_HT100To200               ->Integral(0,-1) ; 
/// //    Double_t int_DY5to50_HT200To400                = h_DY5to50_HT200To400               ->Integral(0,-1) ; 
/// //    Double_t int_DY5to50_HT400To600                = h_DY5to50_HT400To600               ->Integral(0,-1) ; 
/// //    Double_t int_DY5to50_HT600ToInf                = h_DY5to50_HT600ToInf               ->Integral(0,-1) ; 
/// //    Double_t int_DY10to50                          = h_DY10to50                         ->Integral(0,-1) ; 
/// //    Double_t int_DY50                              = h_DY50                             ->Integral(0,-1) ;
/// //    Double_t int_ggZH_HToBB_ZToLL                  = h_ggZH_HToBB_ZToLL                 ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0      = h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0p05   = h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1      = h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10     = h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS100    = h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1000   = h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) ;
/// ////    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10000  = h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ;
/// //    Double_t int_GJets_HT40To100                   = h_GJets_HT40To100                  ->Integral(0,-1) ;
/// //    Double_t int_GJets_HT100To200                  = h_GJets_HT100To200                 ->Integral(0,-1) ;
/// //    Double_t int_GJets_HT200To400                  = h_GJets_HT200To400                 ->Integral(0,-1) ;
/// //    Double_t int_GJets_HT400To600                  = h_GJets_HT400To600                 ->Integral(0,-1) ;
/// //    Double_t int_GJets_HT600ToInf                  = h_GJets_HT600ToInf                 ->Integral(0,-1) ;
/// //    Double_t int_ST_s                              = h_ST_s                             ->Integral(0,-1) ;
/// //    Double_t int_STbar_t                           = h_STbar_t                          ->Integral(0,-1) ;
/// //    Double_t int_ST_t                              = h_ST_t                             ->Integral(0,-1) ;
/// //    Double_t int_STbar_tW                          = h_STbar_tW                         ->Integral(0,-1) ;
/// //    Double_t int_ST_tW                             = h_ST_tW                            ->Integral(0,-1) ;
/// //    Double_t int_TTtoLL                            = h_TTtoLL                           ->Integral(0,-1) ;
/// //    Double_t int_TTJets                            = h_TTJets                           ->Integral(0,-1) ;
/// //    Double_t int_TTtoLfromTbar                     = h_TTtoLfromTbar                    ->Integral(0,-1) ;
/// //    Double_t int_TTtoLfromT                        = h_TTtoLfromT                       ->Integral(0,-1) ;
/// //    Double_t int_WG                                = h_WG                               ->Integral(0,-1) ;
/// //    Double_t int_WJetsToLNu                        = h_WJetsToLNu                       ->Integral(0,-1) ;
/// //    Double_t int_WWToLNuLNu                        = h_WWToLNuLNu                       ->Integral(0,-1) ;
/// //    Double_t int_WW                                = h_WW                               ->Integral(0,-1) ;
/// //    Double_t int_WWToLNuQQ                         = h_WWToLNuQQ                        ->Integral(0,-1) ;
/// //    Double_t int_WZToL3Nu                          = h_WZToL3Nu                         ->Integral(0,-1) ;
/// //    Double_t int_WZTo3LNu                          = h_WZTo3LNu                         ->Integral(0,-1) ;
/// //    Double_t int_WZToLNu2QorQQ2L                   = h_WZToLNu2QorQQ2L                  ->Integral(0,-1) ;
/// //    Double_t int_ZG                                = h_ZG                               ->Integral(0,-1) ;
/// //    Double_t int_ZH_HToBB_ZToLL                    = h_ZH_HToBB_ZToLL                   ->Integral(0,-1) ;
/// //    Double_t int_ZZ                                = h_ZZ                               ->Integral(0,-1) ;
/// //    Double_t int_ZZToLLNuNu                        = h_ZZToLLNuNu                       ->Integral(0,-1) ;
/// //    Double_t int_ZZToLLQQ                          = h_ZZToLLQQ                         ->Integral(0,-1) ;
/// //    Double_t int_ZZToNuNuQQ                        = h_ZZToNuNuQQ                       ->Integral(0,-1) ;
/// //    Double_t int_ZZToLLLL                          = h_ZZToLLLL                         ->Integral(0,-1) ;
/// //    Double_t int_SingleElectronGood                = h_SingleElectronGood               ->Integral(0,-1) ;
/// //    Double_t int_SingleMuonGood                    = h_SingleMuonGood                   ->Integral(0,-1) ;
/// //    Double_t int_SingleElectronHIP                 = h_SingleElectronHIP                ->Integral(0,-1) ;
/// //    Double_t int_SingleMuonHIP                     = h_SingleMuonHIP                    ->Integral(0,-1) ;
/// //    //Double_t int_DoubleEG                          = h_DoubleEG                         ->Integral(0,-1) ;
/// //    //Double_t int_DoubleMuon                        = h_DoubleMuon                       ->Integral(0,-1) ;
/// //    //Double_t int_MuonEG                            = h_MuonEG                           ->Integral(0,-1) ;
/// //
/// //    cout <<"DataEg: "<<int_SingleElectronGood<<endl;
/// //    cout <<"DataEH: "<<int_SingleElectronHIP<<endl;
/// //    cout <<"DataMg: "<<int_SingleMuonGood<<endl;
/// //    cout <<"DataMh: "<<int_SingleMuonHIP<<endl;
/// //
/// //    FILE * outtable;
/// //    outtable = fopen (logname+".tex","w");
/// //     fprintf (outtable, "\\documentclass{standalone}\n\n");
/// //     fprintf (outtable, "\\begin{document}\n\n");
/// //     fprintf (outtable, "\\begin{tabular}{rl}\n\n");
/// //     fprintf (outtable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
/// //     fprintf (outtable, " \\hline \n");
/// //     fprintf (outtable, "\\Large  Backgrounds \\\\\n");
/// //     fprintf (outtable, " \\hline \n");
/// //     fprintf (outtable, "DY10to50                          & %3.1f  \\\\\n", int_DY10to50                         ) ;
/// //     fprintf (outtable, "DY5to50_HT100To200                & %3.1f  \\\\\n", int_DY5to50_HT100To200               ) ; 
/// //     fprintf (outtable, "DY5to50_HT200To400                & %3.1f  \\\\\n", int_DY5to50_HT200To400               ) ; 
/// //     fprintf (outtable, "DY5to50_HT400To600                & %3.1f  \\\\\n", int_DY5to50_HT400To600               ) ; 
/// //     fprintf (outtable, "DY5to50_HT600ToInf                & %3.1f  \\\\\n", int_DY5to50_HT600ToInf               ) ; 
/// ////     fprintf (outtable, "DY5to50_HT70To100                 & %3.1f  \\\\\n", int_DY5to50_HT70To100                ) ; 
/// //
/// //     fprintf (outtable, "DY50                              & %3.1f  \\\\\n", int_DY50                             ) ;
/// //
/// //     fprintf (outtable, "ggZH\\_HToBB\\_ZToLL              & %3.1f  \\\\\n", int_ggZH_HToBB_ZToLL                 ) ;
/// //     fprintf (outtable, "GJets\\_HT40To100                 & %3.1f  \\\\\n", int_GJets_HT40To100                  ) ;
/// //     fprintf (outtable, "GJets\\_HT100To200                & %3.1f  \\\\\n", int_GJets_HT100To200                 ) ;
/// //     fprintf (outtable, "GJets\\_HT200To400                & %3.1f  \\\\\n", int_GJets_HT200To400                 ) ;
/// //     fprintf (outtable, "GJets\\_HT400To600                & %3.1f  \\\\\n", int_GJets_HT400To600                 ) ;
/// //     fprintf (outtable, "GJets\\_HT600ToInf                & %3.1f  \\\\\n", int_GJets_HT600ToInf                 ) ;
/// //     fprintf (outtable, "ST\\_s                            & %3.1f  \\\\\n", int_ST_s                             ) ;
/// //     fprintf (outtable, "STbar\\_t                         & %3.1f  \\\\\n", int_STbar_t                          ) ;
/// //     fprintf (outtable, "ST\\_t                            & %3.1f  \\\\\n", int_ST_t                             ) ;
/// //     fprintf (outtable, "STbar\\_tW                        & %3.1f  \\\\\n", int_STbar_tW                         ) ;
/// //     fprintf (outtable, "ST\\_tW                           & %3.1f  \\\\\n", int_ST_tW                            ) ;
/// //     fprintf (outtable, "TTtoLL                            & %3.1f  \\\\\n", int_TTtoLL                           ) ;
/// //     fprintf (outtable, "TTJets                            & %3.1f  \\\\\n", int_TTJets                           ) ;
/// //     fprintf (outtable, "TTtoLfromTbar                     & %3.1f  \\\\\n", int_TTtoLfromTbar                    ) ;
/// //     fprintf (outtable, "TTtoLfromT                        & %3.1f  \\\\\n", int_TTtoLfromT                       ) ;
/// //     fprintf (outtable, "WG                                & %3.1f  \\\\\n", int_WG                               ) ;
/// //     fprintf (outtable, "WJetsToLNu                        & %3.1f  \\\\\n", int_WJetsToLNu                       ) ;
/// //     fprintf (outtable, "WW                                & %3.1f  \\\\\n", int_WW                               ) ;
/// //     fprintf (outtable, "WWToLNuLNu                        & %3.1f  \\\\\n", int_WWToLNuLNu                       ) ;
/// //     fprintf (outtable, "WWToLNuQQ                         & %3.1f  \\\\\n", int_WWToLNuQQ                        ) ;
/// //     fprintf (outtable, "WZToL3Nu                          & %3.1f  \\\\\n", int_WZToL3Nu                         ) ;
/// //     fprintf (outtable, "WZTo3LNu                          & %3.1f  \\\\\n", int_WZTo3LNu                         ) ;
/// //     fprintf (outtable, "WZToLNu2QorQQ2L                   & %3.1f  \\\\\n", int_WZToLNu2QorQQ2L                  ) ;
/// //     fprintf (outtable, "ZG                                & %3.1f  \\\\\n", int_ZG                               ) ;
/// //     fprintf (outtable, "ZH\\_HToBB\\_ZToLL                    & %3.1f  \\\\\n", int_ZH_HToBB_ZToLL                   ) ;
/// //     fprintf (outtable, "ZZ                                & %3.1f  \\\\\n", int_ZZ                               ) ;
/// //     fprintf (outtable, "ZZToLLNuNu                        & %3.1f  \\\\\n", int_ZZToLLNuNu                       ) ;
/// //     fprintf (outtable, "ZZToLLQQ                          & %3.1f  \\\\\n", int_ZZToLLQQ                         ) ;
/// //     fprintf (outtable, "ZZToNuNuQQ                        & %3.1f  \\\\\n", int_ZZToNuNuQQ                       ) ;
/// //     fprintf (outtable, "ZZToLLLL                          & %3.1f  \\\\\n", int_ZZToLLLL                         ) ;
/// //     fprintf (outtable, " \\hline \n");
/// //     fprintf (outtable, " \\Large Data \\\\\n");
/// //     fprintf (outtable, " \\hline \n");
/// //     //fprintf (outtable, "SingleElectron                    & %3.1f  \\\\\n", int_SingleElectron                   ) ;
/// //     //fprintf (outtable, "SingleMuon                        & %3.1f  \\\\\n", int_SingleMuon                       ) ;
/// //     //fprintf (outtable, "DoubleEG                          & %3.1f  \\\\\n", int_DoubleEG                         ) ;
/// //     //fprintf (outtable, "DoubleMuon                        & %3.1f  \\\\\n", int_DoubleMuon                       ) ;
/// //     //fprintf (outtable, "MuonEG                            & %3.1f  \\\\\n", int_MuonEG                           ) ;
/// //     fprintf (outtable, " \\hline \n");
/// //     //fprintf (outtable, "Signal (only relative matters (xc = 1 ) \\\\\n");
/// //     //fprintf (outtable, " \\hline \n");
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS0      & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS0     ) ;
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS0p05   & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS0p05  ) ;
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS1      & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS1     ) ;
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS10     & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS10    ) ;
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS100    & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS100   ) ;
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS1000   & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS1000  ) ;
/// //     //fprintf (outtable, "ggZH\\_HToSSTobbbb\\_MS40\\_ctauS10000  & %3.1f  \\\\\n", int_ggZH_HToSSTobbbb_MS40_ctauS10000 ) ;
/// //     fprintf (outtable, "\\end{tabular}\n\n");
/// //     fprintf (outtable, "\\end{document}\n\n");
/// //    fclose (outtable);
/// //
/// //
    // merge some histograms
    h_DY = (TH1F*)h_DY50->Clone("h_DY");
 //    h_DY->Add(h_DY5to50_HT100To200); 
 //    h_DY->Add(h_DY5to50_HT200To400); 
 //    h_DY->Add(h_DY5to50_HT400To600); 
 //    h_DY->Add(h_DY5to50_HT600ToInf); 
 //    h_DY->Add(h_DY10to50           ); 

    h_GJets = (TH1F*)h_GJets_HT40To100->Clone("h_GJets");
     h_GJets->Add(h_GJets_HT100To200);
     h_GJets->Add(h_GJets_HT200To400);
     h_GJets->Add(h_GJets_HT400To600);
     h_GJets->Add(h_GJets_HT600ToInf);

    h_ST = (TH1F*)h_ST_s->Clone("h_ST");
     h_ST->Add(h_STbar_t);
     h_ST->Add(h_ST_t);
     h_ST->Add(h_STbar_tW);
     h_ST->Add(h_ST_tW);

    h_ZH = (TH1F*)h_ZH_HToBB_ZToLL->Clone("h_ZH");
     h_ZH->Add(h_ggZH_HToBB_ZToLL);

    h_VV = (TH1F*)h_WW->Clone("h_VV");
     //h_VV->Add(h_WW             ) ;
     //h_VV->Add(h_WWToLNuLNu     ) ;
     //h_VV->Add(h_WWToLNuQQ      ) ;
     //h_VV->Add(h_WZToL3Nu       ) ;
     //h_VV->Add(h_WZTo3LNu       ) ;
     //h_VV->Add(h_WZToLNu2QorQQ2L) ;
     h_VV->Add(h_WZ             ) ;
     h_VV->Add(h_ZZ             ) ;
     //h_VV->Add(h_ZZToLLNuNu     ) ;
     //h_VV->Add(h_ZZToLLQQ       ) ;
     //h_VV->Add(h_ZZToNuNuQQ     ) ;
     //h_VV->Add(h_ZZToLLLL       ) ;

    h_TT = (TH1F*)h_TTJets->Clone("h_TT");
     //h_TT->Add(h_TTtoLfromTbar );
     //h_TT->Add(h_TTtoLfromT    );
     //h_TT->Add(h_TTtoLL        );
     //cout << "h_TT: " << h_TT->GetMaximum()<< endl;

     //cout << "h_TTtoLL: " << h_TTtoLL->Integral()<< endl;
     //cout << "h_TTtoLfromTbar: " << h_TTtoLfromTbar->Integral() << endl;
     //cout << "h_TTtoLfromT: " << h_TTtoLfromT->Integral() << endl;
   
    h_VG = (TH1F*)h_WG->Clone("h_VG");
    h_VG->Add(h_ZG);

    // rescale MC to match eras used
    h_DY         ->Scale(MCSF); 
    h_GJets      ->Scale(MCSF); 
    h_ST         ->Scale(MCSF); 
    h_ZH         ->Scale(MCSF); 
    h_VV         ->Scale(MCSF); 
    h_TT         ->Scale(MCSF); 
    h_VG         ->Scale(MCSF); 
    h_WJetsToLNu ->Scale(MCSF); 

    h_bkgtotal= (TH1F*)h_DY->Clone("h_bkgtotal");
     h_bkgtotal->Add(h_GJets ) ;
     h_bkgtotal->Add(h_ST    ) ;
     h_bkgtotal->Add(h_ZH    ) ;
     h_bkgtotal->Add(h_VV    ) ;
     h_bkgtotal->Add(h_TT    ) ;
     h_bkgtotal->Add(h_VG    ) ;
     h_bkgtotal->Add(h_WJetsToLNu      ) ;

    if( lepton=="ele"){
     // if(HIP){
     //  h_Data = (TH1F*)h_Data_SingleEle_B_2->Clone("h_Data");
     //  h_Data->Add( h_Data_SingleEle_F   )     ; 
     //  h_Data->Add( h_Data_SingleEle_E   )     ; 
     //  h_Data->Add( h_Data_SingleEle_D   )     ; 
     //  h_Data->Add( h_Data_SingleEle_C   )     ; 
     // }
     // else{
       h_Data = (TH1F*)h_Data_DoubleEG_G->Clone("h_Data");
       h_Data->Add( h_Data_DoubleEG_H_3 )     ; 
       h_Data->Add( h_Data_DoubleEG_H_2 )     ; 
      //}
    }
    else if( lepton=="mu"){
      //if(HIP){
      // h_Data = (TH1F*)h_Data_SingleMu_B_2->Clone("h_Data");
      // h_Data->Add( h_Data_SingleMu_F   )     ; 
      // h_Data->Add( h_Data_SingleMu_E   )     ; 
      // h_Data->Add( h_Data_SingleMu_D   )     ; 
      // h_Data->Add( h_Data_SingleMu_C   )     ; 
      //}
      //else{
       h_Data = (TH1F*)h_Data_DoubleMu_G->Clone("h_Data");
       h_Data->Add( h_Data_DoubleMu_H_3 )     ; 
       h_Data->Add( h_Data_DoubleMu_H_2 )     ; 
      //}
    }
    else{
      //h_Data = (TH1F*)h_SingleElectron->Clone("h_Data");
      //h_Data->Add(h_SingleMuon);

    // h_Data_SinglePhoton_H_3   ; 
    // h_Data_SinglePhoton_H_2   ; 
    // h_Data_SinglePhoton_G     ; 
    // h_Data_SinglePhoton_F     ; 
    // h_Data_SinglePhoton_E     ; 
    // h_Data_SinglePhoton_D     ; 
    // h_Data_SinglePhoton_C     ; 
    // h_Data_SinglePhoton_B_2   ; 
    // h_Data_DoubleMu_H_3       ; 
    // h_Data_DoubleMu_H_2       ; 
    // h_Data_DoubleMu_G         ; 
    // h_Data_DoubleMu_E         ; 
    // h_Data_DoubleMu_D         ; 
    // h_Data_DoubleMu_C         ; 
    // h_Data_DoubleMu_B_2       ; 
    // h_Data_DoubleEG_H_3       ; 
    // h_Data_DoubleEG_H_2       ; 
    // h_Data_DoubleEG_F         ; 
    // h_Data_DoubleEG_E         ; 
    // h_Data_DoubleEG_D         ; 
    // h_Data_DoubleEG_C         ; 
    // h_Data_DoubleEG_B_2       ; 
    }
/// //
/// //    // count + ratio
/// //    Double_t int_DY     = h_DY     ->Integral(0,-1) ; cout <<"DY: "<<int_DY<<endl; 
/// //    Double_t int_GJets  = h_GJets  ->Integral(0,-1) ; cout <<"GJets: "<<int_GJets<<endl;
/// //    Double_t int_ST     = h_ST     ->Integral(0,-1) ; cout <<"ST: "<<int_ST<<endl;
/// //    Double_t int_ZH     = h_ZH     ->Integral(0,-1) ; cout <<"ZH: "<<int_ZH<<endl; 
/// //    Double_t int_VV     = h_VV     ->Integral(0,-1) ; cout <<"VV: "<<int_VV<<endl;
/// //    Double_t int_TT     = h_TT     ->Integral(0,-1) ; cout <<"TT: "<<int_TT<<endl;
/// //    Double_t int_VG     = h_VG     ->Integral(0,-1) ; cout <<"VG: "<<int_VG<<endl;
/// //    Double_t int_bkgtotal = h_bkgtotal ->Integral(0,-1) ; cout <<"bkgtotal: "<<int_bkgtotal<<endl;
/// //    Double_t int_Data   = h_Data   ->Integral(0,-1);  cout <<"Data: "<<int_Data<<endl;
/// //    Double_t int_bkgOnData = int_bkgtotal/int_Data;
/// //
/// //    FILE * summarytable;
/// //    summarytable = fopen (logname+"_summary.tex","w");
/// //     fprintf (summarytable, "\\documentclass{standalone}\n\n");
/// //     fprintf (summarytable, "\\begin{document}\n\n");
/// //     fprintf (summarytable, "\\begin{tabular}{rl}\n\n");
/// //     fprintf (summarytable, " \\Huge %s & \\Huge %s   \\\\\n", lepton.Data(), region.Data()); 
/// //     fprintf (summarytable, " \\hline \n");
/// //     fprintf (summarytable, "\\Large  Backgrounds \\\\\n");
/// //     fprintf (summarytable, " \\hline \n");
/// //     fprintf (summarytable, "DY      & %3.1f \\\\\n", int_DY     ) ; 
/// //     fprintf (summarytable, "GJets   & %3.1f \\\\\n", int_GJets  ) ; 
/// //     fprintf (summarytable, "ST      & %3.1f \\\\\n", int_ST     ) ; 
/// //     fprintf (summarytable, "ZH      & %3.1f \\\\\n", int_ZH     ) ; 
/// //     fprintf (summarytable, "VV      & %3.1f \\\\\n", int_VV     ) ; 
/// //     fprintf (summarytable, "TT      & %3.1f \\\\\n", int_TT     ) ; 
/// //     fprintf (summarytable, "VG      & %3.1f \\\\\n", int_VG     ) ; 
/// //     fprintf (summarytable, "WJetsToLNu                        & %3.1f  \\\\\n", int_WJetsToLNu                       ) ;
/// //     fprintf (summarytable, " \\hline \n");
/// //     fprintf (summarytable, "Total Backgrouns     & %3.1f \\\\\n", int_bkgtotal ) ; 
/// //     fprintf (summarytable, " \\hline \n");
/// //     fprintf (summarytable, "Data                 & %3.1f  \\\\\n", int_Data   ) ;
/// //     fprintf (summarytable, " \\hline \n");
/// //     fprintf (summarytable, "Backgrounds / Data   & %3.1f  \\\\\n", int_bkgOnData   ) ;
/// //     fprintf (summarytable, "\\end{tabular}\n\n");
/// //     fprintf (summarytable, "\\end{document}\n\n");
/// //    fclose (summarytable);
/// //
    // set attributes
    h_DY         -> SetLineColor(kBlack); 
    h_GJets      -> SetLineColor(kBlack);
    h_ST         -> SetLineColor(kBlack); 
    h_TT         -> SetLineColor(kBlack); 
    h_WJetsToLNu -> SetLineColor(kBlack); 
    h_VV         -> SetLineColor(kBlack); 
    h_VG         -> SetLineColor(kBlack); 
    h_ZH         -> SetLineColor(kBlack);

    //h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineColor(632) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineColor(807) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineColor(798) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineColor(418) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineColor(601) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineColor(599) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineColor(618) ;

    //h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineWidth(2) ;

    h_Data  -> SetLineColor(kBlack);
    h_Data  -> SetMarkerStyle(8);
    h_Data  -> SetMarkerSize(1);
    h_Data  -> SetLineWidth(3);

    h_DY        ->SetFillStyle(1001);
    h_GJets     ->SetFillStyle(1001);
    h_ST        ->SetFillStyle(1001);
    h_TT        ->SetFillStyle(1001);
    h_WJetsToLNu->SetFillStyle(1001);
    h_VV        ->SetFillStyle(1001);
    h_VG        ->SetFillStyle(1001);
    h_ZH        ->SetFillStyle(1001);

    h_DY        ->SetFillColor(kAzure-3);
    h_GJets     ->SetFillColor(kViolet+3);
    h_ST        ->SetFillColor(kOrange+8);
    h_TT        ->SetFillColor(kGreen+1);
    h_WJetsToLNu->SetFillColor(kViolet-3);
    h_VV        ->SetFillColor(kRed);
    h_VG        ->SetFillColor(kPink+9);
    h_ZH        ->SetFillColor(kCyan);

    h_DY        ->SetLineColor(kBlack); 
    h_GJets     ->SetLineColor(kBlack); 
    h_ST        ->SetLineColor(kBlack); 
    h_TT        ->SetLineColor(kBlack); 
    h_WJetsToLNu->SetLineColor(kBlack); 
    h_VV        ->SetLineColor(kBlack); 
    h_VG        ->SetLineColor(kBlack); 
    h_ZH        ->SetLineColor(kBlack); 

    h_DY        ->SetLineWidth(2);
    h_GJets     ->SetLineWidth(2);
    h_ST        ->SetLineWidth(2);
    h_TT        ->SetLineWidth(2);
    h_WJetsToLNu->SetLineWidth(2);
    h_VV        ->SetLineWidth(2);
    h_VG        ->SetLineWidth(2);
    h_ZH        ->SetLineWidth(2);

    h_bkgtotal->SetFillColorAlpha(kYellow+1, 0.7);
    h_bkgtotal->SetFillStyle(1001);

    std::vector<TH1F *> v = {h_DY, h_GJets, h_ST, h_TT, h_WJetsToLNu, h_VV, h_VG, h_ZH};

    // make stack
    THStack *bgstack = new THStack("bgstack","");
    if(dolog){
     std::sort(v.begin(), v.end(),
               [](TH1F *a, TH1F *b) { return a->Integral() < b->Integral(); });
     for(int zz=0; zz<v.size(); zz++)
     {
      bgstack->Add(v[zz]);
      //cout <<v[zz]->Integral()<<std::endl;
     }
    }
    else{
     bgstack->Add(h_DY         ); 
     bgstack->Add(h_GJets      );
     bgstack->Add(h_ST         ); 
     bgstack->Add(h_TT         ); 
     bgstack->Add(h_WJetsToLNu ); 
     bgstack->Add(h_VV         ); 
     bgstack->Add(h_VG         );
     bgstack->Add(h_ZH         );
    }

//    if( h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS0      ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1));
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS0p05   ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1));  
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS1      ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1)); 
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS10     ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1)); 
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS100    ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1));   
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS1000   ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1));  
//    }                                     
//    if( h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) > 0.1){ ;
//       h_ggZH_HToSSTobbbb_MS40_ctauS10000  ->Scale( int_bkgtotal / h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ); 
//    }

    // make legend
    TLegend *leg;
    leg = new TLegend(0.2,0.7,0.88,0.88);
    leg->SetBorderSize(0);
    leg->SetNColumns(2);
    leg->SetFillColor(kWhite);
    leg->AddEntry(h_Data         , "Data", "lpe"); 
    leg->AddEntry(h_DY           , "Drell-Yan", "f"); 
    leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
    leg->AddEntry(h_ST           , "Single Top", "f"); 
    leg->AddEntry(h_TT           , "t#bar{t}+Jets", "f"); 
    leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
    leg->AddEntry(h_VV           , "Diboson", "f"); 
    leg->AddEntry(h_VG           , "V#gamma", "f");
    leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");
    leg->AddEntry(h_bkgtotal     , "MC bkg. stat. err.", "f");

     TLegend *sigleg = new TLegend(0.15,0.6,0.65,0.85);
   //if(drawSignal){
     //sigleg->SetBorderSize(0);
     //sigleg->SetFillColor(kWhite);
     //sigleg->SetHeader("Z(H#rightarrow SS#rightarrow bbbb)","C");
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0     , "M_{S}=40 c#tau_{S}=0    ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0p05  , "M_{S}=40 c#tau_{S}=0p05 ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1     , "M_{S}=40 c#tau_{S}=1    ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10    , "M_{S}=40 c#tau_{S}=10   ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS100   , "M_{S}=40 c#tau_{S}=100  ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1000  , "M_{S}=40 c#tau_{S}=1000 ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10000 , "M_{S}=40 c#tau_{S}=10000", "l" ) ;
    //}

    // set max and draw
    Double_t ymax;
    ymax = std::max(h_Data->GetMaximum(), h_bkgtotal->GetMaximum() );
    
    if(dolog){
     bgstack->SetMaximum(500*ymax); 
     bgstack->SetMinimum(1.0);
    } 
    else {
     bgstack->SetMaximum(ymax*1.4);
    }
     
    pad1->cd();
    bgstack->Draw("hist");
    //bgstack->Draw("hist e");
    bgstack->GetYaxis()->SetTitle("Events");
    bgstack->GetYaxis()->SetTitleSize(40);
    bgstack->GetYaxis()->SetTitleFont(43);
    bgstack->GetYaxis()->SetTitleOffset(1.55);
    h_bkgtotal->Draw("e2 sames");
    h_Data->Draw("sames E"); 

//    if(drawSignal){
//     h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Draw("hist sames") ;
//     sigleg->Draw();
//    }
    leg->Draw();

    char lumistring [50];
    int dummy; 

    // add titles
    title->DrawTextNDC(0.2,0.91,"CMS");
    extra->DrawTextNDC(0.3,0.91,"Preliminary");
    if(HIP){
     extra2->DrawTextNDC(0.51,0.91,"Eras B-F");
     dummy=sprintf (lumistring, "%0.1f", lumiBCDEF/1000.);
    }
    else{
     extra2->DrawTextNDC(0.51,0.91,"Eras GH");
     dummy=sprintf (lumistring, "%0.1f", lumiGH/1000.);
    }
    //lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
    lumi->DrawTextNDC(0.9,0.91,(TString)lumistring+" /fb (13 TeV)");


     pad2->cd();
     h_ratio = (TH1F*)h_Data->Clone("h_ratio");
     if(h_Data->Integral(-1,-1)>0){
      h_ratio->Divide(h_bkgtotal);
     }
     h_ratio->SetTitle(" ");
     // Y axis ratio plot settings
     h_ratio->GetYaxis()->SetTitleSize(40);
     h_ratio->GetYaxis()->SetTitleFont(43);
     h_ratio->GetYaxis()->SetTitleOffset(1.55);
     h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
     h_ratio->GetYaxis()->SetLabelSize(20);
     h_ratio->GetYaxis()->SetNdivisions(-105);
     h_ratio->GetYaxis()->SetTitle("Data/MC");
     // X axis ratio plot settings
     h_ratio->GetXaxis()->SetTitleSize(40);
     h_ratio->GetXaxis()->SetTitleFont(43);
     h_ratio->GetXaxis()->SetTitle(h_Data->GetTitle());
     h_ratio->GetXaxis()->SetTitleOffset(4.0);
     h_ratio->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
     h_ratio->GetXaxis()->SetLabelSize(20);//20
     h_ratio->SetMarkerStyle(20);
     h_ratio->SetMarkerColor(kRed);
     h_ratio->SetMarkerSize(1);
     h_ratio->GetYaxis()->SetRangeUser(0,2);
     h_ratio->Draw("ep");  // draw first to get ranges set internally inside root

     h_ratiostaterr = (TH1F*)h_bkgtotal->Clone("h_ratiostaterr");
     h_ratiostaterr->Divide(h_bkgtotal);

     pad2->Update();       // need to update pad to get X min/max
     TLine *line = new TLine(pad2->GetUxmin(),1,pad2->GetUxmax(),1);
     line->SetLineColor(kBlue);
     line->SetLineWidth(3);
     line->SetLineStyle(9);
     h_ratiostaterr->Draw("e2 same");
     line->Draw();
     h_ratio->Draw("ep same"); // draw points above line
 
     // save canvas
     //canvas->SaveAs(outname+".png");
     canvas->SaveAs(outname+".pdf");

     // save histograms into single root file
     TFile *outfile = TFile::Open(outname+".root","RECREATE");
     h_Data        ->Write();
     h_DY          ->Write();
     h_GJets       ->Write();
     h_ST          ->Write();
     h_TT          ->Write();
     h_WJetsToLNu  ->Write();
     h_VV          ->Write();
     h_VG          ->Write();
     h_ZH          ->Write();
     h_bkgtotal    ->Write();
     h_ratio       ->Write();
     h_ratiostaterr->Write();
     outfile->Close();
  
   } 
  }
}
