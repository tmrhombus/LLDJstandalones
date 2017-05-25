
#include <stdlib.h>     /* getenv */

void plotter_stacked()
{

 // Draw signal as lines
 Bool_t drawSignal = kFALSE;
 Bool_t drawData = kTRUE;

 // path to root files
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));
 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/";

 // y axis plots as log
 Bool_t dolog = kTRUE;
 TString extraname = "";
 if(dolog){extraname+="_log";}
 if(drawSignal){extraname+="_wsig";}

 // phase space regions to plot
 std::vector<TString> regions;
 regions.clear();
 regions.push_back("NoSel");
 regions.push_back("Sig");
 regions.push_back("ZH");
 regions.push_back("DY");
 regions.push_back("OffZ");
 regions.push_back("NoPair"); 

 // lepton flavor
 std::vector<TString> leptons;
 leptons.clear();
 leptons.push_back("ele"); 
 leptons.push_back("mu");  

 // variables to plot
 std::vector<TString> variables;
 variables.clear();
 //variables.push_back("htall");                                

 //variables.push_back("nVtx");                                  
 // variables.push_back("htall");                                 
 // variables.push_back("htjets");                                
 // variables.push_back("nPU");                                   
 variables.push_back("phoEt");                                 
 variables.push_back("phoEta");                                
 variables.push_back("phoPhi");                                
 variables.push_back("elePt");                                 
 variables.push_back("eleEta");                                
 variables.push_back("elePhi");                                
 variables.push_back("muPt");                                  
 variables.push_back("muEta");                                 
 variables.push_back("muPhi");                                 
// variables.push_back("LeadingJetjetPt");                       
// variables.push_back("LeadingJetjetTestVariable");             
// variables.push_back("LeadingJetjetEn");                       
// variables.push_back("LeadingJetjetEta");                      
// variables.push_back("LeadingJetjetPhi");                      
// variables.push_back("LeadingJetjetRawPt");                    
// variables.push_back("LeadingJetjetRawEn");                    
// variables.push_back("LeadingJetjetMt");                       
// variables.push_back("LeadingJetjetArea");                     
// variables.push_back("LeadingJetjetLeadTrackPt");              
// variables.push_back("LeadingJetjetLeadTrackEta");             
// variables.push_back("LeadingJetjetLeadTrackPhi");             
// variables.push_back("LeadingJetjetLepTrackPID");              
// variables.push_back("LeadingJetjetLepTrackPt");               
// variables.push_back("LeadingJetjetLepTrackEta");              
// variables.push_back("LeadingJetjetLepTrackPhi");              
// variables.push_back("LeadingJetjetCSV2BJetTags");             
// variables.push_back("LeadingJetjetJetProbabilityBJetTags");   
// variables.push_back("LeadingJetjetpfCombinedMVAV2BJetTags");  
// variables.push_back("LeadingJetjetPartonID");                 
// variables.push_back("LeadingJetjetHadFlvr");                  
// variables.push_back("LeadingJetjetGenJetEn");                 
// variables.push_back("LeadingJetjetGenJetPt");                 
// variables.push_back("LeadingJetjetGenJetEta");                
// variables.push_back("LeadingJetjetGenJetPhi");                
// variables.push_back("LeadingJetjetGenPartonID");              
// variables.push_back("LeadingJetjetGenEn");                    
// variables.push_back("LeadingJetjetGenPt");                    
// variables.push_back("LeadingJetjetGenEta");                   
// variables.push_back("LeadingJetjetGenPhi");                   
// variables.push_back("LeadingJetjetGenPartonMomID");           
// variables.push_back("LeadingJetAK8JetPt");                    
// variables.push_back("LeadingJetAK8JetEn");                    
// variables.push_back("LeadingJetAK8JetRawPt");                 
// variables.push_back("LeadingJetAK8JetRawEn");                 
// variables.push_back("LeadingJetAK8JetEta");                   
// variables.push_back("LeadingJetAK8JetPhi");                   
// variables.push_back("LeadingJetAK8JetMass");                  
// variables.push_back("SubleadingJetjetPt");                    
// variables.push_back("SubleadingJetjetTestVariable");          
// variables.push_back("SubleadingJetjetEn");                    
// variables.push_back("SubleadingJetjetEta");                   
// variables.push_back("SubleadingJetjetPhi");                   
// variables.push_back("SubleadingJetjetRawPt");                 
// variables.push_back("SubleadingJetjetRawEn");                 
// variables.push_back("SubleadingJetjetMt");                    
// variables.push_back("SubleadingJetjetArea");                  
// variables.push_back("SubleadingJetjetLeadTrackPt");           
// variables.push_back("SubleadingJetjetLeadTrackEta");          
// variables.push_back("SubleadingJetjetLeadTrackPhi");          
// variables.push_back("SubleadingJetjetLepTrackPID");           
// variables.push_back("SubleadingJetjetLepTrackPt");            
// variables.push_back("SubleadingJetjetLepTrackEta");           
// variables.push_back("SubleadingJetjetLepTrackPhi");           
// variables.push_back("SubleadingJetjetCSV2BJetTags");          
// variables.push_back("SubleadingJetjetJetProbabilityBJetTags");
// variables.push_back("SubleadingJetjetpfCombinedMVAV2BJetTags")
// variables.push_back("SubleadingJetjetPartonID");              
// variables.push_back("SubleadingJetjetHadFlvr");               
// variables.push_back("SubleadingJetjetGenJetEn");              
// variables.push_back("SubleadingJetjetGenJetPt");              
// variables.push_back("SubleadingJetjetGenJetEta");             
// variables.push_back("SubleadingJetjetGenJetPhi");             
// variables.push_back("SubleadingJetjetGenPartonID");           
// variables.push_back("SubleadingJetjetGenEn");                 
// variables.push_back("SubleadingJetjetGenPt");                 
// variables.push_back("SubleadingJetjetGenEta");                
// variables.push_back("SubleadingJetjetGenPhi");                
// variables.push_back("SubleadingJetjetGenPartonMomID");        
// variables.push_back("SubleadingJetAK8JetPt");                 
// variables.push_back("SubleadingJetAK8JetEn");                 
// variables.push_back("SubleadingJetAK8JetRawPt");              
// variables.push_back("SubleadingJetAK8JetRawEn");              
// variables.push_back("SubleadingJetAK8JetEta");                
// variables.push_back("SubleadingJetAK8JetPhi");                
// variables.push_back("SubleadingJetAK8JetMass");               
// variables.push_back("ThirdJetjetPt");                         
// variables.push_back("ThirdJetjetTestVariable");               
// variables.push_back("ThirdJetjetEn");                         
// variables.push_back("ThirdJetjetEta");                        
// variables.push_back("ThirdJetjetPhi");                        
// variables.push_back("ThirdJetjetRawPt");                      
// variables.push_back("ThirdJetjetRawEn");                      
// variables.push_back("ThirdJetjetMt");                         
// variables.push_back("ThirdJetjetArea");                       
// variables.push_back("ThirdJetjetLeadTrackPt");                
// variables.push_back("ThirdJetjetLeadTrackEta");               
// variables.push_back("ThirdJetjetLeadTrackPhi");               
// variables.push_back("ThirdJetjetLepTrackPID");                
// variables.push_back("ThirdJetjetLepTrackPt");                 
// variables.push_back("ThirdJetjetLepTrackEta");                
// variables.push_back("ThirdJetjetLepTrackPhi");                
// variables.push_back("ThirdJetjetCSV2BJetTags");               
// variables.push_back("ThirdJetjetJetProbabilityBJetTags");     
// variables.push_back("ThirdJetjetpfCombinedMVAV2BJetTags");    
// variables.push_back("ThirdJetjetPartonID");                   
// variables.push_back("ThirdJetjetHadFlvr");                    
// variables.push_back("ThirdJetjetGenJetEn");                   
// variables.push_back("ThirdJetjetGenJetPt");                   
// variables.push_back("ThirdJetjetGenJetEta");                  
// variables.push_back("ThirdJetjetGenJetPhi");                  
// variables.push_back("ThirdJetjetGenPartonID");                
// variables.push_back("ThirdJetjetGenEn");                      
// variables.push_back("ThirdJetjetGenPt");                      
// variables.push_back("ThirdJetjetGenEta");                     
// variables.push_back("ThirdJetjetGenPhi");                     
// variables.push_back("ThirdJetjetGenPartonMomID");             
// variables.push_back("ThirdJetAK8JetPt");                      
// variables.push_back("ThirdJetAK8JetEn");                      
// variables.push_back("ThirdJetAK8JetRawPt");                   
// variables.push_back("ThirdJetAK8JetRawEn");                   
// variables.push_back("ThirdJetAK8JetEta");                     
// variables.push_back("ThirdJetAK8JetPhi");                     
// variables.push_back("ThirdJetAK8JetMass");                    
// variables.push_back("FourthJetjetPt");                        
// variables.push_back("FourthJetjetTestVariable");              
// variables.push_back("FourthJetjetEn");                        
// variables.push_back("FourthJetjetEta");                       
// variables.push_back("FourthJetjetPhi");                       
// variables.push_back("FourthJetjetRawPt");                     
// variables.push_back("FourthJetjetRawEn");                     
// variables.push_back("FourthJetjetMt");                        
// variables.push_back("FourthJetjetArea");                      
// variables.push_back("FourthJetjetLeadTrackPt");               
// variables.push_back("FourthJetjetLeadTrackEta");              
// variables.push_back("FourthJetjetLeadTrackPhi");              
// variables.push_back("FourthJetjetLepTrackPID");               
// variables.push_back("FourthJetjetLepTrackPt");                
// variables.push_back("FourthJetjetLepTrackEta");               
// variables.push_back("FourthJetjetLepTrackPhi");               
// variables.push_back("FourthJetjetCSV2BJetTags");              
// variables.push_back("FourthJetjetJetProbabilityBJetTags");    
// variables.push_back("FourthJetjetpfCombinedMVAV2BJetTags");   
// variables.push_back("FourthJetjetPartonID");                  
// variables.push_back("FourthJetjetHadFlvr");                   
// variables.push_back("FourthJetjetGenJetEn");                  
// variables.push_back("FourthJetjetGenJetPt");                  
// variables.push_back("FourthJetjetGenJetEta");                 
// variables.push_back("FourthJetjetGenJetPhi");                 
// variables.push_back("FourthJetjetGenPartonID");               
// variables.push_back("FourthJetjetGenEn");                     
// variables.push_back("FourthJetjetGenPt");                     
// variables.push_back("FourthJetjetGenEta");                    
// variables.push_back("FourthJetjetGenPhi");                    
// variables.push_back("FourthJetjetGenPartonMomID");            
// variables.push_back("FourthJetAK8JetPt");                     
// variables.push_back("FourthJetAK8JetEn");                     
// variables.push_back("FourthJetAK8JetRawPt");                  
// variables.push_back("FourthJetAK8JetRawEn");                  
// variables.push_back("FourthJetAK8JetEta");                    
// variables.push_back("FourthJetAK8JetPhi");                    
// variables.push_back("FourthJetAK8JetMass");                   


 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.04);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.04);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // initialize histogram files 

 TFile* file_DY50                            ;                            
 TFile* file_DY5to50_HT100to200              ;              
 TFile* file_DY5to50_HT200to400              ;              
 TFile* file_DY5to50_HT400to600              ;              
 TFile* file_DY5to50_HT600toInf              ;              
 TFile* file_DY5to50_HT70to100               ;               
 TFile* file_GJets_HT40To100                 ;                 
 TFile* file_GJets_HT100To200                ;                
 TFile* file_GJets_HT200To400                ;                
 TFile* file_GJets_HT400To600                ;                
 TFile* file_GJets_HT600ToInf                ;                
 TFile* file_ST_s                            ;                            
 TFile* file_STbar_t                         ;                         
 TFile* file_ST_t                            ;                            
 TFile* file_STbar_tW                        ;                        
 TFile* file_ST_tW                           ;                           
 TFile* file_TTJets                          ;                          
 TFile* file_WW                              ;                              
 TFile* file_WZ                              ;                              
 TFile* file_ZZ                              ;                              
 TFile* file_ZH_HToBB_ZToLL                  ;                  
 TFile* file_ggZH_HToBB_ZToLL                ;                
 TFile* file_ggZH_HToSSTobbbb_MS40_ctauS100  ;  
 TFile* file_ggZH_HToSSTodddd_MS40_ctauS100  ;  
 TFile* file_WJetsToLNu                      ;                      
 TFile* file_SingleElectron                  ;                  
 TFile* file_SingleMuon                      ;        

 // initialize histos
 TH1F* h_DY50                            ;                            
 TH1F* h_DY5to50_HT100to200              ;              
 TH1F* h_DY5to50_HT200to400              ;              
 TH1F* h_DY5to50_HT400to600              ;              
 TH1F* h_DY5to50_HT600toInf              ;              
 TH1F* h_DY5to50_HT70to100               ;               
 TH1F* h_GJets_HT40To100                 ;                 
 TH1F* h_GJets_HT100To200                ;                
 TH1F* h_GJets_HT200To400                ;                
 TH1F* h_GJets_HT400To600                ;                
 TH1F* h_GJets_HT600ToInf                ;                
 TH1F* h_ST_s                            ;                            
 TH1F* h_STbar_t                         ;                         
 TH1F* h_ST_t                            ;                            
 TH1F* h_STbar_tW                        ;                        
 TH1F* h_ST_tW                           ;                           
 TH1F* h_TTJets                          ;                          
 TH1F* h_WW                              ;                              
 TH1F* h_WZ                              ;                              
 TH1F* h_ZZ                              ;                              
 TH1F* h_ZH_HToBB_ZToLL                  ;                  
 TH1F* h_ggZH_HToBB_ZToLL                ;                
 TH1F* h_ggZH_HToSSTobbbb_MS40_ctauS100  ;  
 TH1F* h_ggZH_HToSSTodddd_MS40_ctauS100  ;  
 TH1F* h_WJets                           ;                      
 TH1F* h_SingleElectron                  ;                  
 TH1F* h_SingleMuon                      ;        

 // (combined) histos to be made
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_ZH     ;
 TH1F* h_totbkg ;

 TH1F* h_Data   ;

 // load histogram files
 file_DY50                            = new TFile( inpath + "DY50.root"                           ) ;                            
 file_DY5to50_HT100to200              = new TFile( inpath + "DY5to50_HT100to200.root"             ) ;              
 file_DY5to50_HT200to400              = new TFile( inpath + "DY5to50_HT200to400.root"             ) ;              
 file_DY5to50_HT400to600              = new TFile( inpath + "DY5to50_HT400to600.root"             ) ;              
 file_DY5to50_HT600toInf              = new TFile( inpath + "DY5to50_HT600toInf.root"             ) ;              
 file_DY5to50_HT70to100               = new TFile( inpath + "DY5to50_HT70to100.root"              ) ;               
 file_GJets_HT40To100                 = new TFile( inpath + "GJets_HT40To100.root"                ) ;                 
 file_GJets_HT100To200                = new TFile( inpath + "GJets_HT100To200.root"               ) ;                
 file_GJets_HT200To400                = new TFile( inpath + "GJets_HT200To400.root"               ) ;                
 file_GJets_HT400To600                = new TFile( inpath + "GJets_HT400To600.root"               ) ;                
 file_GJets_HT600ToInf                = new TFile( inpath + "GJets_HT600ToInf.root"               ) ;                
 file_ST_s                            = new TFile( inpath + "ST_s.root"                           ) ;                            
 file_STbar_t                         = new TFile( inpath + "STbar_t.root"                        ) ;                         
 file_ST_t                            = new TFile( inpath + "ST_t.root"                           ) ;                            
 file_STbar_tW                        = new TFile( inpath + "STbar_tW.root"                       ) ;                        
 file_ST_tW                           = new TFile( inpath + "ST_tW.root"                          ) ;                           
 file_TTJets                          = new TFile( inpath + "TTJets.root"                         ) ;                          
 file_WW                              = new TFile( inpath + "WW.root"                             ) ;                              
 file_WZ                              = new TFile( inpath + "WZ.root"                             ) ;                              
 file_ZZ                              = new TFile( inpath + "ZZ.root"                             ) ;                              
 file_ZH_HToBB_ZToLL                  = new TFile( inpath + "ZH_HToBB_ZToLL.root"                 ) ;                  
 file_ggZH_HToBB_ZToLL                = new TFile( inpath + "ggZH_HToBB_ZToLL.root"               ) ;                
 file_ggZH_HToSSTobbbb_MS40_ctauS100  = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS100.root" ) ;  
 file_ggZH_HToSSTodddd_MS40_ctauS100  = new TFile( inpath + "ggZH_HToSSTodddd_MS40_ctauS100.root" ) ;  
 file_WJets                           = new TFile( inpath + "WJetsToLNu.root"                     ) ;                      
 file_SingleElectron                  = new TFile( inpath + "SingleElectron.root"                 ) ;                  
 file_SingleMuon                      = new TFile( inpath + "SingleMuon.root"                     ) ;        

 for(unsigned int i=0; i<regions.size(); ++i){
  TString region = regions[i];
  for(unsigned int j=0; j<variables.size(); ++j){
   TString variable = variables[j];
   for(unsigned int k=0; k<leptons.size(); ++k){
    TString lepton = leptons[k];

    TString varname = lepton+"_"+region+"_"+variable;

    printf("plotting  h_%s \n",varname.Data());
    TString outname = outpath+varname+extraname; 

    // get histograms from files
    h_DY50                            =  (TH1F*)file_DY50                           ->Get("h_"+varname)->Clone("DY50"                           ) ;                            
    h_DY5to50_HT100to200              =  (TH1F*)file_DY5to50_HT100to200             ->Get("h_"+varname)->Clone("DY5to50_HT100to200"             ) ;              
    h_DY5to50_HT200to400              =  (TH1F*)file_DY5to50_HT200to400             ->Get("h_"+varname)->Clone("DY5to50_HT200to400"             ) ;              
    h_DY5to50_HT400to600              =  (TH1F*)file_DY5to50_HT400to600             ->Get("h_"+varname)->Clone("DY5to50_HT400to600"             ) ;              
    h_DY5to50_HT600toInf              =  (TH1F*)file_DY5to50_HT600toInf             ->Get("h_"+varname)->Clone("DY5to50_HT600toInf"             ) ;              
    h_DY5to50_HT70to100               =  (TH1F*)file_DY5to50_HT70to100              ->Get("h_"+varname)->Clone("DY5to50_HT70to100"              ) ;               
    h_GJets_HT40To100                 =  (TH1F*)file_GJets_HT40To100                ->Get("h_"+varname)->Clone("GJets_HT40To100"                ) ;                 
    h_GJets_HT100To200                =  (TH1F*)file_GJets_HT100To200               ->Get("h_"+varname)->Clone("GJets_HT100To200"               ) ;                
    h_GJets_HT200To400                =  (TH1F*)file_GJets_HT200To400               ->Get("h_"+varname)->Clone("GJets_HT200To400"               ) ;                
    h_GJets_HT400To600                =  (TH1F*)file_GJets_HT400To600               ->Get("h_"+varname)->Clone("GJets_HT400To600"               ) ;                
    h_GJets_HT600ToInf                =  (TH1F*)file_GJets_HT600ToInf               ->Get("h_"+varname)->Clone("GJets_HT600ToInf"               ) ;                
    h_ST_s                            =  (TH1F*)file_ST_s                           ->Get("h_"+varname)->Clone("ST_s"                           ) ;                            
    h_STbar_t                         =  (TH1F*)file_STbar_t                        ->Get("h_"+varname)->Clone("STbar_t"                        ) ;                         
    h_ST_t                            =  (TH1F*)file_ST_t                           ->Get("h_"+varname)->Clone("ST_t"                           ) ;                            
    h_STbar_tW                        =  (TH1F*)file_STbar_tW                       ->Get("h_"+varname)->Clone("STbar_tW"                       ) ;                        
    h_ST_tW                           =  (TH1F*)file_ST_tW                          ->Get("h_"+varname)->Clone("ST_tW"                          ) ;                           
    h_TTJets                          =  (TH1F*)file_TTJets                         ->Get("h_"+varname)->Clone("TTJets"                         ) ;                          
    h_WW                              =  (TH1F*)file_WW                             ->Get("h_"+varname)->Clone("WW"                             ) ;                              
    h_WZ                              =  (TH1F*)file_WZ                             ->Get("h_"+varname)->Clone("WZ"                             ) ;                              
    h_ZZ                              =  (TH1F*)file_ZZ                             ->Get("h_"+varname)->Clone("ZZ"                             ) ;                              
    h_ZH_HToBB_ZToLL                  =  (TH1F*)file_ZH_HToBB_ZToLL                 ->Get("h_"+varname)->Clone("ZH_HToBB_ZToLL"                 ) ;                  
    h_ggZH_HToBB_ZToLL                =  (TH1F*)file_ggZH_HToBB_ZToLL               ->Get("h_"+varname)->Clone("ggZH_HToBB_ZToLL"               ) ;                
    h_ggZH_HToSSTobbbb_MS40_ctauS100  =  (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS100 ->Get("h_"+varname)->Clone("ggZH_HToSSTobbbb_MS40_ctauS100" ) ;  
    h_ggZH_HToSSTodddd_MS40_ctauS100  =  (TH1F*)file_ggZH_HToSSTodddd_MS40_ctauS100 ->Get("h_"+varname)->Clone("ggZH_HToSSTodddd_MS40_ctauS100" ) ;  
    h_WJets                           =  (TH1F*)file_WJets                          ->Get("h_"+varname)->Clone("WJets"                          ) ;                      
    h_SingleElectron                  =  (TH1F*)file_SingleElectron                 ->Get("h_"+varname)->Clone("SingleElectron"                 ) ;                  
    h_SingleMuon                      =  (TH1F*)file_SingleMuon                     ->Get("h_"+varname)->Clone("SingleMuon"                     ) ;        

    // integrals of histograms
    Double_t int_DY50                           = h_DY50                           ->Integral(-1,-1);   
    Double_t int_DY5to50_HT100to200             = h_DY5to50_HT100to200             ->Integral(-1,-1);   
    Double_t int_DY5to50_HT200to400             = h_DY5to50_HT200to400             ->Integral(-1,-1);   
    Double_t int_DY5to50_HT400to600             = h_DY5to50_HT400to600             ->Integral(-1,-1);   
    Double_t int_DY5to50_HT600toInf             = h_DY5to50_HT600toInf             ->Integral(-1,-1);   
    Double_t int_DY5to50_HT70to100              = h_DY5to50_HT70to100              ->Integral(-1,-1);   
    Double_t int_GJets_HT40To100                = h_GJets_HT40To100                ->Integral(-1,-1);   
    Double_t int_GJets_HT100To200               = h_GJets_HT100To200               ->Integral(-1,-1);   
    Double_t int_GJets_HT200To400               = h_GJets_HT200To400               ->Integral(-1,-1);   
    Double_t int_GJets_HT400To600               = h_GJets_HT400To600               ->Integral(-1,-1);   
    Double_t int_GJets_HT600ToInf               = h_GJets_HT600ToInf               ->Integral(-1,-1);   
    Double_t int_ST_s                           = h_ST_s                           ->Integral(-1,-1);   
    Double_t int_STbar_t                        = h_STbar_t                        ->Integral(-1,-1);   
    Double_t int_ST_t                           = h_ST_t                           ->Integral(-1,-1);   
    Double_t int_STbar_tW                       = h_STbar_tW                       ->Integral(-1,-1);   
    Double_t int_ST_tW                          = h_ST_tW                          ->Integral(-1,-1);   
    Double_t int_TTJets                         = h_TTJets                         ->Integral(-1,-1);   
    Double_t int_WW                             = h_WW                             ->Integral(-1,-1);   
    Double_t int_WZ                             = h_WZ                             ->Integral(-1,-1);   
    Double_t int_ZZ                             = h_ZZ                             ->Integral(-1,-1);   
    Double_t int_ZH_HToBB_ZToLL                 = h_ZH_HToBB_ZToLL                 ->Integral(-1,-1);   
    Double_t int_ggZH_HToBB_ZToLL               = h_ggZH_HToBB_ZToLL               ->Integral(-1,-1);   
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS100 = h_ggZH_HToSSTobbbb_MS40_ctauS100 ->Integral(-1,-1);   
    Double_t int_ggZH_HToSSTodddd_MS40_ctauS100 = h_ggZH_HToSSTodddd_MS40_ctauS100 ->Integral(-1,-1);   
    Double_t int_WJetsToLNu                     = h_WJets                          ->Integral(-1,-1);   
    Double_t int_SingleElectron                 = h_SingleElectron                 ->Integral(-1,-1);   
    Double_t int_SingleMuon                     = h_SingleMuon                     ->Integral(-1,-1);   

    FILE * outtable;
 
    outtable = fopen (outname+".txt","w");
     fprintf (outtable, "           & %s \n", region.Data()); 
     fprintf (outtable, "DY50                           &%3.1f\n", int_DY50                           );   
     fprintf (outtable, "DY5to50_HT100to200             &%3.1f\n", int_DY5to50_HT100to200             );   
     fprintf (outtable, "DY5to50_HT200to400             &%3.1f\n", int_DY5to50_HT200to400             );   
     fprintf (outtable, "DY5to50_HT400to600             &%3.1f\n", int_DY5to50_HT400to600             );   
     fprintf (outtable, "DY5to50_HT600toInf             &%3.1f\n", int_DY5to50_HT600toInf             );   
     fprintf (outtable, "DY5to50_HT70to100              &%3.1f\n", int_DY5to50_HT70to100              );   
     fprintf (outtable, "GJets_HT40To100                &%3.1f\n", int_GJets_HT40To100                );   
     fprintf (outtable, "GJets_HT100To200               &%3.1f\n", int_GJets_HT100To200               );   
     fprintf (outtable, "GJets_HT200To400               &%3.1f\n", int_GJets_HT200To400               );   
     fprintf (outtable, "GJets_HT400To600               &%3.1f\n", int_GJets_HT400To600               );   
     fprintf (outtable, "GJets_HT600ToInf               &%3.1f\n", int_GJets_HT600ToInf               );   
     fprintf (outtable, "ST_s                           &%3.1f\n", int_ST_s                           );   
     fprintf (outtable, "STbar_t                        &%3.1f\n", int_STbar_t                        );   
     fprintf (outtable, "ST_t                           &%3.1f\n", int_ST_t                           );   
     fprintf (outtable, "STbar_tW                       &%3.1f\n", int_STbar_tW                       );   
     fprintf (outtable, "ST_tW                          &%3.1f\n", int_ST_tW                          );   
     fprintf (outtable, "TTJets                         &%3.1f\n", int_TTJets                         );   
     fprintf (outtable, "WW                             &%3.1f\n", int_WW                             );   
     fprintf (outtable, "WZ                             &%3.1f\n", int_WZ                             );   
     fprintf (outtable, "ZZ                             &%3.1f\n", int_ZZ                             );   
     fprintf (outtable, "ZH_HToBB_ZToLL                 &%3.1f\n", int_ZH_HToBB_ZToLL                 );   
     fprintf (outtable, "ggZH_HToBB_ZToLL               &%3.1f\n", int_ggZH_HToBB_ZToLL               );   
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS100 &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS100 );   
     fprintf (outtable, "ggZH_HToSSTodddd_MS40_ctauS100 &%3.1f\n", int_ggZH_HToSSTodddd_MS40_ctauS100 );   
     fprintf (outtable, "WJetsToLNu                     &%3.1f\n", int_WJetsToLNu                     );   
     fprintf (outtable, "SingleElectron                 &%3.1f\n", int_SingleElectron                 );   
     fprintf (outtable, "SingleMuon                     &%3.1f\n", int_SingleMuon                     );   
    fclose (outtable);

    // merge some histograms
    h_DY = (TH1F*)h_DY50->Clone("h_DY");
    h_DY->Add(h_DY5to50_HT70to100);
    h_DY->Add(h_DY5to50_HT100to200);
    h_DY->Add(h_DY5to50_HT200to400);
    h_DY->Add(h_DY5to50_HT400to600);
    h_DY->Add(h_DY5to50_HT600toInf);

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

    h_VV = (TH1F*)h_WW->Clone("h_WW");
    h_VV->Add(h_WZ);
    h_VV->Add(h_ZZ);

    h_ZH = (TH1F*)h_ZH_HToBB_ZToLL->Clone("h_ZH");
    h_ZH->Add(h_ggZH_HToBB_ZToLL);

    if( lepton=="ele"){
     h_Data = (TH1F*)h_SingleElectron->Clone("h_Data");
    }
    else if( lepton=="mu"){
     h_Data = (TH1F*)h_SingleMuon->Clone("h_Data");
    }

    // set attributes
    h_DY     -> SetFillColor(kRed); 
    h_GJets  -> SetFillColor(kOrange-3);
    h_VV     -> SetFillColor(kYellow+1); 
    h_ST     -> SetFillColor(kGreen+1); 
    h_TTJets -> SetFillColor(kGreen-9); 
    h_WJets  -> SetFillColor(kAzure+10); 
    h_ZH     -> SetFillColor(kBlue); 

    h_DY    -> SetLineColor(kBlack); 
    h_GJets -> SetLineColor(kBlack);
    h_ST    -> SetLineColor(kBlack); 
    h_TTJets -> SetLineColor(kBlack); 
    h_WJets -> SetLineColor(kBlack); 
    h_VV    -> SetLineColor(kBlack); 
    h_ZH    -> SetLineColor(kBlack); 

    h_Data  -> SetLineColor(kBlack);
    h_Data  -> SetLineWidth(3);

    //h_SignalWm   ->SetFillStyle(3001); 
    //h_SignalWm   ->SetFillStyle(3001); 
    //h_SignalWp   ->SetFillStyle(3001); 
    //h_SignalZH   ->SetFillStyle(3001); 
    //h_SignalggZH ->SetFillStyle(3001); 
    //h_SignalWm   ->SetLineColor(1); 
    //h_SignalWp   ->SetLineColor(2); 
    //h_SignalZH   ->SetLineColor(3); 
    //h_SignalggZH ->SetLineColor(4); 
    //h_SignalWm   ->SetLineWidth(2); 
    //h_SignalWp   ->SetLineWidth(2); 
    //h_SignalZH   ->SetLineWidth(2); 
    //h_SignalggZH ->SetLineWidth(2); 

    // make stack
    THStack *bgstack = new THStack("bgstack","");
    bgstack->Add(h_DY    ); 
    bgstack->Add(h_VV    ); 
    bgstack->Add(h_ST    ); 
    bgstack->Add(h_TTJets ); 
    bgstack->Add(h_WJets ); 
    bgstack->Add(h_ZH    );

    // make signal lines
    h_totbkg = (TH1F*)h_DY->Clone("h_totbkg");
    h_totbkg->Add(h_VV    ); 
    h_totbkg->Add(h_ST    ); 
    h_totbkg->Add(h_TTJets ); 
    h_totbkg->Add(h_WJets ); 
    h_totbkg->Add(h_ZH    );
    Double_t intbkg = h_totbkg->Integral();
    //if( h_SignalWm->Integral() > 0.1 ){
    // h_SignalWm   ->Scale( intbkg / h_SignalWm->Integral() ); 
    //}
    //if( h_SignalWp->Integral() > 0.1 ){
    // h_SignalWp   ->Scale( intbkg / h_SignalWp->Integral() ); 
    //}
    //if( h_SignalZH->Integral() > 0.1 ){
    // h_SignalZH   ->Scale( intbkg / h_SignalZH->Integral() ); 
    //}
    //if( h_SignalggZH->Integral() > 0.1 ){
    // h_SignalggZH   ->Scale( intbkg / h_SignalggZH->Integral() ); 
    //}

    // make legend
    TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
    leg->SetBorderSize(0);
    leg->SetFillColor(kWhite);
    if(drawData){
     if( lepton=="ele"){
      leg->AddEntry(h_Data      , "Data SingleEle", "lpe"); 
     }
     else if( lepton=="mu"){
      leg->AddEntry(h_Data      , "Data SingleMu", "lpe"); 
     }
    }
    leg->AddEntry(h_DY      , "Drell-Yan", "f"); 
    leg->AddEntry(h_GJets   , "#gamma+Jets", "f"); 
    leg->AddEntry(h_VV      , "Diboson", "f"); 
    leg->AddEntry(h_ST      , "Single Top", "f"); 
    leg->AddEntry(h_TTJets  , "t#bar{t}+Jets", "f"); 
    leg->AddEntry(h_WJets   , "W+Jets", "f"); 
    leg->AddEntry(h_ZH      , "ZH#rightarrowLLbb", "f");
    //if(drawSignal){
    // leg->AddEntry(h_SignalWm, "Signal W-H","l");
    // leg->AddEntry(h_SignalWp, "Signal W+H","l");
    // leg->AddEntry(h_SignalZH, "Signal ZH","l");
    // leg->AddEntry(h_SignalggZH, "Signal ggZH","l");
    //}
    
    // and draw
    bgstack->Draw("hist");
    if(drawData){
     h_Data->Draw("sames, E");
    }
    //if(drawSignal){
    // h_SignalWm->Draw("hist sames");
    // h_SignalWp->Draw("hist sames");
    // h_SignalZH->Draw("hist sames");
    // h_SignalggZH->Draw("hist sames");
    //}
    leg->Draw();

    // add titles
    title->DrawTextNDC(0.13,0.91,"CMS");
    extra->DrawTextNDC(0.23,0.91,"Preliminary");
    lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
    bgstack->GetXaxis()->SetTitle(h_TTJets->GetTitle());
    bgstack->GetYaxis()->SetTitle("Events / bin");

    gPad->Update();
    gPad->RedrawAxis();

    // save canvas
    canvas->SaveAs(outname+".pdf");
    //canvas->SaveAs(outpath+jettype+"_"+varname+extraname+".pdf");

   } 
  }
 }
}

