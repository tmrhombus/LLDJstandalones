
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
 //regions.push_back("Sig");
 //regions.push_back("ZH");
 regions.push_back("DY");
 regions.push_back("OffZ");
 //regions.push_back("NoPair"); 

 // lepton flavor
 std::vector<TString> leptons;
 leptons.clear();
 leptons.push_back("ele"); 
 leptons.push_back("mu");  
 leptons.push_back("NoLepSel");

 // variables to plot
 std::vector<TString> variables;
 variables.clear();
 variables.push_back("nVtx");                                  
 variables.push_back("phoEt");                                 
 //variables.push_back("phoEta");                                
 //variables.push_back("phoPhi");                                
 variables.push_back("elePt");                                 
 //variables.push_back("eleEta");                                
 //variables.push_back("elePhi");                                
 variables.push_back("muPt");                                  
 //variables.push_back("muEta");                                 
 //variables.push_back("muPhi");                                 
 variables.push_back("LeadingJetjetPt");                       
 //variables.push_back("LeadingJetjetEta");                      


 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kCMYK);

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

 TFile* file_DY10to50                            ;
 TFile* file_DY50                                ;
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
 TFile* file_TTtoLfromTbar                       ;
 TFile* file_TTtoLfromT                          ;
 TFile* file_WG                                  ;
 TFile* file_WJetsToLNu                          ;
 TFile* file_WWToLNuLNu                          ;
 TFile* file_WWToLNuQQ                           ;
 TFile* file_WZToL3Nu                            ;
 TFile* file_WZTo3LNu                            ;
 TFile* file_WZToLNu2QorQQ2L                     ;
 TFile* file_ZG                                  ;
 TFile* file_ZH_HToBB_ZToLL                      ;
 TFile* file_ZZToLLNuNu                          ;
 TFile* file_ZZToLLQQ                            ;
 TFile* file_ZZToNuNuQQ                          ;
 TFile* file_ZZToLLLL                            ;
 TFile* file_SingleElectron                      ;
 TFile* file_SingleMuon                          ;
 TFile* file_DoubleEG                            ;
 TFile* file_DoubleMuon                          ;
 TFile* file_MuonEG                              ;

 // initialize histos
 TH1F* h_DY10to50                            ;
 TH1F* h_DY50                                ;
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
 TH1F* h_TTtoLfromTbar                       ;
 TH1F* h_TTtoLfromT                          ;
 TH1F* h_WG                                  ;
 TH1F* h_WJetsToLNu                          ;
 TH1F* h_WWToLNuLNu                          ;
 TH1F* h_WWToLNuQQ                           ;
 TH1F* h_WZToL3Nu                            ;
 TH1F* h_WZTo3LNu                            ;
 TH1F* h_WZToLNu2QorQQ2L                     ;
 TH1F* h_ZG                                  ;
 TH1F* h_ZH_HToBB_ZToLL                      ;
 TH1F* h_ZZToLLNuNu                          ;
 TH1F* h_ZZToLLQQ                            ;
 TH1F* h_ZZToNuNuQQ                          ;
 TH1F* h_ZZToLLLL                            ;
 TH1F* h_SingleElectron                      ;
 TH1F* h_SingleMuon                          ;
 TH1F* h_DoubleEG                            ;
 TH1F* h_DoubleMuon                          ;
 TH1F* h_MuonEG                              ;

 // (combined) histos to be made
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_VG     ;
 TH1F* h_TT     ;
 TH1F* h_totbkg ;

 TH1F* h_Data   ;

 // load histogram files
 file_DY10to50                          = new TFile( inpath + "DY10to50.root"                         ) ;
 file_DY50                              = new TFile( inpath + "DY50.root"                             ) ;
 file_ggZH_HToBB_ZToLL                  = new TFile( inpath + "ggZH_HToBB_ZToLL.root"                 ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS0      = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS0.root"     ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS0p05   = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS0p05.root"  ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS1      = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS1.root"     ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS10     = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS10.root"    ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS100    = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS100.root"   ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS1000   = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS1000.root"  ) ;
 file_ggZH_HToSSTobbbb_MS40_ctauS10000  = new TFile( inpath + "ggZH_HToSSTobbbb_MS40_ctauS10000.root" ) ;
 file_GJets_HT40To100                   = new TFile( inpath + "GJets_HT40To100.root"                  ) ;
 file_GJets_HT100To200                  = new TFile( inpath + "GJets_HT100To200.root"                 ) ;
 file_GJets_HT200To400                  = new TFile( inpath + "GJets_HT200To400.root"                 ) ;
 file_GJets_HT400To600                  = new TFile( inpath + "GJets_HT400To600.root"                 ) ;
 file_GJets_HT600ToInf                  = new TFile( inpath + "GJets_HT600ToInf.root"                 ) ;
 file_ST_s                              = new TFile( inpath + "ST_s.root"                             ) ;
 file_STbar_t                           = new TFile( inpath + "STbar_t.root"                          ) ;
 file_ST_t                              = new TFile( inpath + "ST_t.root"                             ) ;
 file_STbar_tW                          = new TFile( inpath + "STbar_tW.root"                         ) ;
 file_ST_tW                             = new TFile( inpath + "ST_tW.root"                            ) ;
 file_TTtoLL                            = new TFile( inpath + "TTtoLL.root"                           ) ;
 file_TTtoLfromTbar                     = new TFile( inpath + "TTtoLfromTbar.root"                    ) ;
 file_TTtoLfromT                        = new TFile( inpath + "TTtoLfromT.root"                       ) ;
 file_WG                                = new TFile( inpath + "WG.root"                               ) ;
 file_WJetsToLNu                        = new TFile( inpath + "WJetsToLNu.root"                       ) ;
 file_WWToLNuLNu                        = new TFile( inpath + "WWToLNuLNu.root"                       ) ;
 file_WWToLNuQQ                         = new TFile( inpath + "WWToLNuQQ.root"                        ) ;
 file_WZToL3Nu                          = new TFile( inpath + "WZToL3Nu.root"                         ) ;
 file_WZTo3LNu                          = new TFile( inpath + "WZTo3LNu.root"                         ) ;
 file_WZToLNu2QorQQ2L                   = new TFile( inpath + "WZToLNu2QorQQ2L.root"                  ) ;
 file_ZG                                = new TFile( inpath + "ZG.root"                               ) ;
 file_ZH_HToBB_ZToLL                    = new TFile( inpath + "ZH_HToBB_ZToLL.root"                   ) ;
 file_ZZToLLNuNu                        = new TFile( inpath + "ZZToLLNuNu.root"                       ) ;
 file_ZZToLLQQ                          = new TFile( inpath + "ZZToLLQQ.root"                         ) ;
 file_ZZToNuNuQQ                        = new TFile( inpath + "ZZToNuNuQQ.root"                       ) ;
 file_ZZToLLLL                          = new TFile( inpath + "ZZToLLLL.root"                         ) ;
 file_SingleElectron                    = new TFile( inpath + "SingleElectron.root"                   ) ;
 file_SingleMuon                        = new TFile( inpath + "SingleMuon.root"                       ) ;
 file_DoubleEG                          = new TFile( inpath + "DoubleEG.root"                         ) ;
 file_DoubleMuon                        = new TFile( inpath + "DoubleMuon.root"                       ) ;
 file_MuonEG                            = new TFile( inpath + "MuonEG.root"                           ) ;

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
    h_DY10to50                          = (TH1F*)file_DY10to50                         ->Get("h_"+varname)->Clone( "DY10to50"                         ) ;
    h_DY50                              = (TH1F*)file_DY50                             ->Get("h_"+varname)->Clone( "DY50"                             ) ;
    h_ggZH_HToBB_ZToLL                  = (TH1F*)file_ggZH_HToBB_ZToLL                 ->Get("h_"+varname)->Clone( "ggZH_HToBB_ZToLL"                 ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS0      = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS0     ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS0"     ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS0p05   = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS0p05"  ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS1      = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS1     ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS1"     ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS10     = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS10    ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS10"    ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS100    = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS100   ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS100"   ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS1000   = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS1000"  ) ;
    h_ggZH_HToSSTobbbb_MS40_ctauS10000  = (TH1F*)file_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Get("h_"+varname)->Clone( "ggZH_HToSSTobbbb_MS40_ctauS10000" ) ;
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
    h_TTtoLL                            = (TH1F*)file_TTtoLL                           ->Get("h_"+varname)->Clone( "TTtoLL"                           ) ;
    h_TTtoLfromTbar                     = (TH1F*)file_TTtoLfromTbar                    ->Get("h_"+varname)->Clone( "TTtoLfromTbar"                    ) ;
    h_TTtoLfromT                        = (TH1F*)file_TTtoLfromT                       ->Get("h_"+varname)->Clone( "TTtoLfromT"                       ) ;
    h_WG                                = (TH1F*)file_WG                               ->Get("h_"+varname)->Clone( "WG"                               ) ;
    h_WJetsToLNu                        = (TH1F*)file_WJetsToLNu                       ->Get("h_"+varname)->Clone( "WJetsToLNu"                       ) ;
    h_WWToLNuLNu                        = (TH1F*)file_WWToLNuLNu                       ->Get("h_"+varname)->Clone( "WWToLNuLNu"                       ) ;
    h_WWToLNuQQ                         = (TH1F*)file_WWToLNuQQ                        ->Get("h_"+varname)->Clone( "WWToLNuQQ"                        ) ;
    h_WZToL3Nu                          = (TH1F*)file_WZToL3Nu                         ->Get("h_"+varname)->Clone( "WZToL3Nu"                         ) ;
    h_WZTo3LNu                          = (TH1F*)file_WZTo3LNu                         ->Get("h_"+varname)->Clone( "WZTo3LNu"                         ) ;
    h_WZToLNu2QorQQ2L                   = (TH1F*)file_WZToLNu2QorQQ2L                  ->Get("h_"+varname)->Clone( "WZToLNu2QorQQ2L"                  ) ;
    h_ZG                                = (TH1F*)file_ZG                               ->Get("h_"+varname)->Clone( "ZG"                               ) ;
    h_ZH_HToBB_ZToLL                    = (TH1F*)file_ZH_HToBB_ZToLL                   ->Get("h_"+varname)->Clone( "ZH_HToBB_ZToLL"                   ) ;
    h_ZZToLLNuNu                        = (TH1F*)file_ZZToLLNuNu                       ->Get("h_"+varname)->Clone( "ZZToLLNuNu"                       ) ;
    h_ZZToLLQQ                          = (TH1F*)file_ZZToLLQQ                         ->Get("h_"+varname)->Clone( "ZZToLLQQ"                         ) ;
    h_ZZToNuNuQQ                        = (TH1F*)file_ZZToNuNuQQ                       ->Get("h_"+varname)->Clone( "ZZToNuNuQQ"                       ) ;
    h_ZZToLLLL                          = (TH1F*)file_ZZToLLLL                         ->Get("h_"+varname)->Clone( "ZZToLLLL"                         ) ;
    h_SingleElectron                    = (TH1F*)file_SingleElectron                   ->Get("h_"+varname)->Clone( "SingleElectron"                   ) ;
    h_SingleMuon                        = (TH1F*)file_SingleMuon                       ->Get("h_"+varname)->Clone( "SingleMuon"                       ) ;
    h_DoubleEG                          = (TH1F*)file_DoubleEG                         ->Get("h_"+varname)->Clone( "DoubleEG"                         ) ;
    h_DoubleMuon                        = (TH1F*)file_DoubleMuon                       ->Get("h_"+varname)->Clone( "DoubleMuon"                       ) ;
    h_MuonEG                            = (TH1F*)file_MuonEG                           ->Get("h_"+varname)->Clone( "MuonEG"                           ) ;

    // integrals of histograms
    Double_t int_DY10to50                          = h_DY10to50                         ->Integral(0,-1) ;
    Double_t int_DY50                              = h_DY50                             ->Integral(0,-1) ;
    Double_t int_ggZH_HToBB_ZToLL                  = h_ggZH_HToBB_ZToLL                 ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0      = h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0p05   = h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1      = h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10     = h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS100    = h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1000   = h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) ;
    Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10000  = h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ;
    Double_t int_GJets_HT40To100                   = h_GJets_HT40To100                  ->Integral(0,-1) ;
    Double_t int_GJets_HT100To200                  = h_GJets_HT100To200                 ->Integral(0,-1) ;
    Double_t int_GJets_HT200To400                  = h_GJets_HT200To400                 ->Integral(0,-1) ;
    Double_t int_GJets_HT400To600                  = h_GJets_HT400To600                 ->Integral(0,-1) ;
    Double_t int_GJets_HT600ToInf                  = h_GJets_HT600ToInf                 ->Integral(0,-1) ;
    Double_t int_ST_s                              = h_ST_s                             ->Integral(0,-1) ;
    Double_t int_STbar_t                           = h_STbar_t                          ->Integral(0,-1) ;
    Double_t int_ST_t                              = h_ST_t                             ->Integral(0,-1) ;
    Double_t int_STbar_tW                          = h_STbar_tW                         ->Integral(0,-1) ;
    Double_t int_ST_tW                             = h_ST_tW                            ->Integral(0,-1) ;
    Double_t int_TTtoLL                            = h_TTtoLL                           ->Integral(0,-1) ;
    Double_t int_TTtoLfromTbar                     = h_TTtoLfromTbar                    ->Integral(0,-1) ;
    Double_t int_TTtoLfromT                        = h_TTtoLfromT                       ->Integral(0,-1) ;
    Double_t int_WG                                = h_WG                               ->Integral(0,-1) ;
    Double_t int_WJetsToLNu                        = h_WJetsToLNu                       ->Integral(0,-1) ;
    Double_t int_WWToLNuLNu                        = h_WWToLNuLNu                       ->Integral(0,-1) ;
    Double_t int_WWToLNuQQ                         = h_WWToLNuQQ                        ->Integral(0,-1) ;
    Double_t int_WZToL3Nu                          = h_WZToL3Nu                         ->Integral(0,-1) ;
    Double_t int_WZTo3LNu                          = h_WZTo3LNu                         ->Integral(0,-1) ;
    Double_t int_WZToLNu2QorQQ2L                   = h_WZToLNu2QorQQ2L                  ->Integral(0,-1) ;
    Double_t int_ZG                                = h_ZG                               ->Integral(0,-1) ;
    Double_t int_ZH_HToBB_ZToLL                    = h_ZH_HToBB_ZToLL                   ->Integral(0,-1) ;
    Double_t int_ZZToLLNuNu                        = h_ZZToLLNuNu                       ->Integral(0,-1) ;
    Double_t int_ZZToLLQQ                          = h_ZZToLLQQ                         ->Integral(0,-1) ;
    Double_t int_ZZToNuNuQQ                        = h_ZZToNuNuQQ                       ->Integral(0,-1) ;
    Double_t int_ZZToLLLL                          = h_ZZToLLLL                         ->Integral(0,-1) ;
    Double_t int_SingleElectron                    = h_SingleElectron                   ->Integral(0,-1) ;
    Double_t int_SingleMuon                        = h_SingleMuon                       ->Integral(0,-1) ;
    Double_t int_DoubleEG                          = h_DoubleEG                         ->Integral(0,-1) ;
    Double_t int_DoubleMuon                        = h_DoubleMuon                       ->Integral(0,-1) ;
    Double_t int_MuonEG                            = h_MuonEG                           ->Integral(0,-1) ;

    FILE * outtable;
 
    outtable = fopen (outname+".txt","w");
     fprintf (outtable, "           & %s \n", region.Data()); 
     fprintf (outtable, "DY10to50                          &%3.1f\n", int_DY10to50                         ) ;
     fprintf (outtable, "DY50                              &%3.1f\n", int_DY50                             ) ;
     fprintf (outtable, "ggZH_HToBB_ZToLL                  &%3.1f\n", int_ggZH_HToBB_ZToLL                 ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS0      &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS0     ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS0p05   &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS0p05  ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS1      &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS1     ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS10     &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS10    ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS100    &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS100   ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS1000   &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS1000  ) ;
     fprintf (outtable, "ggZH_HToSSTobbbb_MS40_ctauS10000  &%3.1f\n", int_ggZH_HToSSTobbbb_MS40_ctauS10000 ) ;
     fprintf (outtable, "GJets_HT40To100                   &%3.1f\n", int_GJets_HT40To100                  ) ;
     fprintf (outtable, "GJets_HT100To200                  &%3.1f\n", int_GJets_HT100To200                 ) ;
     fprintf (outtable, "GJets_HT200To400                  &%3.1f\n", int_GJets_HT200To400                 ) ;
     fprintf (outtable, "GJets_HT400To600                  &%3.1f\n", int_GJets_HT400To600                 ) ;
     fprintf (outtable, "GJets_HT600ToInf                  &%3.1f\n", int_GJets_HT600ToInf                 ) ;
     fprintf (outtable, "ST_s                              &%3.1f\n", int_ST_s                             ) ;
     fprintf (outtable, "STbar_t                           &%3.1f\n", int_STbar_t                          ) ;
     fprintf (outtable, "ST_t                              &%3.1f\n", int_ST_t                             ) ;
     fprintf (outtable, "STbar_tW                          &%3.1f\n", int_STbar_tW                         ) ;
     fprintf (outtable, "ST_tW                             &%3.1f\n", int_ST_tW                            ) ;
     fprintf (outtable, "TTtoLL                            &%3.1f\n", int_TTtoLL                           ) ;
     fprintf (outtable, "TTtoLfromTbar                     &%3.1f\n", int_TTtoLfromTbar                    ) ;
     fprintf (outtable, "TTtoLfromT                        &%3.1f\n", int_TTtoLfromT                       ) ;
     fprintf (outtable, "WG                                &%3.1f\n", int_WG                               ) ;
     fprintf (outtable, "WJetsToLNu                        &%3.1f\n", int_WJetsToLNu                       ) ;
     fprintf (outtable, "WWToLNuLNu                        &%3.1f\n", int_WWToLNuLNu                       ) ;
     fprintf (outtable, "WWToLNuQQ                         &%3.1f\n", int_WWToLNuQQ                        ) ;
     fprintf (outtable, "WZToL3Nu                          &%3.1f\n", int_WZToL3Nu                         ) ;
     fprintf (outtable, "WZTo3LNu                          &%3.1f\n", int_WZTo3LNu                         ) ;
     fprintf (outtable, "WZToLNu2QorQQ2L                   &%3.1f\n", int_WZToLNu2QorQQ2L                  ) ;
     fprintf (outtable, "ZG                                &%3.1f\n", int_ZG                               ) ;
     fprintf (outtable, "ZH_HToBB_ZToLL                    &%3.1f\n", int_ZH_HToBB_ZToLL                   ) ;
     fprintf (outtable, "ZZToLLNuNu                        &%3.1f\n", int_ZZToLLNuNu                       ) ;
     fprintf (outtable, "ZZToLLQQ                          &%3.1f\n", int_ZZToLLQQ                         ) ;
     fprintf (outtable, "ZZToNuNuQQ                        &%3.1f\n", int_ZZToNuNuQQ                       ) ;
     fprintf (outtable, "ZZToLLLL                          &%3.1f\n", int_ZZToLLLL                         ) ;
     fprintf (outtable, "SingleElectron                    &%3.1f\n", int_SingleElectron                   ) ;
     fprintf (outtable, "SingleMuon                        &%3.1f\n", int_SingleMuon                       ) ;
     fprintf (outtable, "DoubleEG                          &%3.1f\n", int_DoubleEG                         ) ;
     fprintf (outtable, "DoubleMuon                        &%3.1f\n", int_DoubleMuon                       ) ;
     fprintf (outtable, "MuonEG                            &%3.1f\n", int_MuonEG                           ) ;
    fclose (outtable);

    // merge some histograms
    h_DY = (TH1F*)h_DY10to50->Clone("h_DY");
     h_DY->Add(h_DY50);

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

    h_VG = (TH1F*)h_ZH_HToBB_ZToLL->Clone("h_ZH");
     h_VG->Add(h_ggZH_HToBB_ZToLL);

    h_VV = (TH1F*)h_WWToLNuLNu->Clone("h_VV");
     h_VV->Add(h_WWToLNuQQ      ) ;
     h_VV->Add(h_WZToL3Nu       ) ;
     h_VV->Add(h_WZTo3LNu       ) ;
     h_VV->Add(h_WZToLNu2QorQQ2L) ;
     h_VV->Add(h_ZZToLLNuNu     ) ;
     h_VV->Add(h_ZZToLLQQ       ) ;
     h_VV->Add(h_ZZToNuNuQQ     ) ;
     h_VV->Add(h_ZZToLLLL       ) ;

    h_TT = (TH1F*)h_TTtoLL->Clone("h_TT");
     h_TT->Add(h_TTtoLfromTbar );
     h_TT->Add(h_TTtoLfromT    );

    h_VG = (TH1F*)h_WG->Clone("h_VG");
     h_VG->Add(h_ZG);

    h_totbkg= (TH1F*)h_DY10to50->Clone("h_totbkg");
     h_totbkg->Add(h_DY50            ) ;
     h_totbkg->Add(h_ggZH_HToBB_ZToLL) ;
     h_totbkg->Add(h_GJets_HT40To100 ) ;
     h_totbkg->Add(h_GJets_HT100To200) ;
     h_totbkg->Add(h_GJets_HT200To400) ;
     h_totbkg->Add(h_GJets_HT400To600) ;
     h_totbkg->Add(h_GJets_HT600ToInf) ;
     h_totbkg->Add(h_ST_s            ) ;
     h_totbkg->Add(h_STbar_t         ) ;
     h_totbkg->Add(h_ST_t            ) ;
     h_totbkg->Add(h_STbar_tW        ) ;
     h_totbkg->Add(h_ST_tW           ) ;
     h_totbkg->Add(h_TTtoLL          ) ;
     h_totbkg->Add(h_TTtoLfromTbar   ) ;
     h_totbkg->Add(h_TTtoLfromT      ) ;
     h_totbkg->Add(h_WG              ) ;
     h_totbkg->Add(h_WJetsToLNu      ) ;
     h_totbkg->Add(h_WWToLNuLNu      ) ;
     h_totbkg->Add(h_WWToLNuQQ       ) ;
     h_totbkg->Add(h_WZToL3Nu        ) ;
     h_totbkg->Add(h_WZTo3LNu        ) ;
     h_totbkg->Add(h_WZToLNu2QorQQ2L ) ;
     h_totbkg->Add(h_ZG              ) ;
     h_totbkg->Add(h_ZH_HToBB_ZToLL  ) ;
     h_totbkg->Add(h_ZZToLLNuNu      ) ;
     h_totbkg->Add(h_ZZToLLQQ        ) ;
     h_totbkg->Add(h_ZZToNuNuQQ      ) ;
     h_totbkg->Add(h_ZZToLLLL        ) ;
    Double_t intbkg = h_totbkg->Integral(0,-1);

    // set data set(s) to use
    if( lepton=="ele"){
     h_Data = (TH1F*)h_SingleElectron->Clone("h_Data");
    }
    else if( lepton=="mu"){
     h_Data = (TH1F*)h_SingleMuon->Clone("h_Data");
    }
    else{
     h_Data = (TH1F*)h_SingleElectron->Clone("h_Data");
      h_Data->Add(h_SingleMuon);
    }
    Double_t intdata = h_Data->Integral(0,-1);

    // set attributes
    //h_DY          -> SetFillColor(kRed); 
    //h_GJets       -> SetFillColor(kOrange-3);
    //h_VV          -> SetFillColor(kYellow+1); 
    //h_ST          -> SetFillColor(kGreen+1); 
    //h_TT          -> SetFillColor(kGreen-9); 
    //h_WJetsToLNu  -> SetFillColor(kAzure+10); 
    //h_VG          -> SetFillColor(kBlue); 
    //h_VG          -> SetFillColor(kGreen);

    //h_DY         -> SetLineColor(kBlack); 
    //h_GJets      -> SetLineColor(kBlack);
    //h_ST         -> SetLineColor(kBlack); 
    //h_TT         -> SetLineColor(kBlack); 
    //h_WJetsToLNu -> SetLineColor(kBlack); 
    //h_VV         -> SetLineColor(kBlack); 
    //h_VG         -> SetLineColor(kBlack); 
    //h_VG         -> SetLineColor(kBlack);

    // h_DY         -> SetFillStyle(3001); 
    // h_GJets      -> SetFillStyle(3001);
    // h_ST         -> SetFillStyle(3001); 
    // h_TT         -> SetFillStyle(3001); 
    // h_WJetsToLNu -> SetFillStyle(3001); 
    // h_VV         -> SetFillStyle(3001); 
    // h_VG         -> SetFillStyle(3001); 
    // h_VG         -> SetFillStyle(3001);

    h_Data  -> SetLineColor(kBlack);
    h_Data  -> SetLineWidth(3);

    //h_SignalWm   ->SetFillStyle(3001); 
    //h_SignalWm   ->SetFillStyle(3001); 
    //h_SignalWp   ->SetFillStyle(3001); 
    //h_SignalVG   ->SetFillStyle(3001); 
    //h_SignalggZH ->SetFillStyle(3001); 
    //h_SignalWm   ->SetLineColor(1); 
    //h_SignalWp   ->SetLineColor(2); 
    //h_SignalVG   ->SetLineColor(3); 
    //h_SignalggZH ->SetLineColor(4); 
    //h_SignalWm   ->SetLineWidth(2); 
    //h_SignalWp   ->SetLineWidth(2); 
    //h_SignalVG   ->SetLineWidth(2); 
    //h_SignalggZH ->SetLineWidth(2); 

    // make stack
    THStack *bgstack = new THStack("bgstack","");
    bgstack->Add(h_DY         ); 
    bgstack->Add(h_VV         ); 
    bgstack->Add(h_ST         ); 
    bgstack->Add(h_TT         ); 
    bgstack->Add(h_WJetsToLNu ); 
    bgstack->Add(h_VG         );
    bgstack->Add(h_VG         );

    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS0      ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1));
    //  }                                     
    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS0p05   ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1));  
    //  }                                     
    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS1      ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1)); 
    //  }                                     
    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS10     ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1)); 
    //  }                                     
    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS100    ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1));   
    //  }                                     
    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS1000   ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1));  
    //  }                                     
    //  if( h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) > 0.1){ ;
    //     h_ggZH_HToSSTobbbb_MS40_ctauS10000  ->Scale( intbkg / h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ); 
    //  }

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
    leg->AddEntry(h_DY           , "Drell-Yan", "f"); 
    leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
    leg->AddEntry(h_VV           , "Diboson", "f"); 
    leg->AddEntry(h_ST           , "Single Top", "f"); 
    leg->AddEntry(h_TT           , "t#bar{t}+Jets", "f"); 
    leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
    leg->AddEntry(h_VG           , "ZH#rightarrowLLbb", "f");
    leg->AddEntry(h_VG           , "V#gamma", "f");
    //if(drawSignal){
    // leg->AddEntry(h_SignalWm, "Signal W-H","l");
    // leg->AddEntry(h_SignalWp, "Signal W+H","l");
    // leg->AddEntry(h_SignalVG, "Signal ZH","l");
    // leg->AddEntry(h_SignalggZH, "Signal ggZH","l");
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0     , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}0     )", "l" ) ;
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0p05  , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}0p05  )", "l" ) ;
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1     , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}1     )", "l" ) ;
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10    , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}10    )", "l" ) ;
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS100   , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}100   )", "l" ) ;
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1000  , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}1000  )", "l" ) ;
       //  leg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10000 , "ZH#rightarrow SS#rightarrow bbbb (M_{S}40 c#tau_{S}10000 )", "l" ) ;
    //}
    
    // and draw
    //bgstack->Draw("hist PFC ");

    //h_DY          -> Draw("hist SAMES PFC");
    h_DY          -> Draw("hist SAMES PFC");
    h_GJets       -> Draw("hist PFC");
    h_VV          -> Draw("hist SAMES PFC"); 
    h_ST          -> Draw("hist SAMES PFC");
    h_TT          -> Draw("hist SAMES PFC");
    h_WJetsToLNu  -> Draw("hist SAMES PFC"); 
    h_VG          -> Draw("hist SAMES PFC");
    h_VG          -> Draw("hist SAMES PFC");
    if(drawData){
     h_Data->Draw("sames, E");
    }
    //if(drawSignal){
    // h_SignalWm->Draw("hist sames");
    // h_SignalWp->Draw("hist sames");
    // h_SignalVG->Draw("hist sames");
    // h_SignalggZH->Draw("hist sames");
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0      = h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Integral(0,-1) ;
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS0p05   = h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Integral(0,-1) ;
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1      = h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Integral(0,-1) ;
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10     = h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Integral(0,-1) ;
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS100    = h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Integral(0,-1) ;
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS1000   = h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Integral(0,-1) ;
       //  Double_t int_ggZH_HToSSTobbbb_MS40_ctauS10000  = h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Integral(0,-1) ;
    //}
    leg->Draw();

    // add titles
    title->DrawTextNDC(0.13,0.91,"CMS");
    extra->DrawTextNDC(0.23,0.91,"Preliminary");
    lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
    bgstack->GetXaxis()->SetTitle(h_TT->GetTitle());
    bgstack->GetYaxis()->SetTitle("Events / bin");

    gPad->Update();
    gPad->RedrawAxis();

    // save canvas
    canvas->SaveAs(outname+".pdf");
    canvas->SaveAs(outname+".png");
    //canvas->SaveAs(outpath+jettype+"_"+varname+extraname+".pdf");

   } 
  }
 }
}

