#define analyzer_signal_cxx
#include "analyzer_signal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void analyzer_signal::Loop(TString outfilename, Bool_t isMC,
                       Double_t lumi, Double_t nrEvents,
                       Double_t crossSec)
{

 if(makelog){
  logfile = fopen( outfilename+".txt", "w"); 
 }

 if (fChain == 0) return;

 Long64_t nentries = fChain->GetEntriesFast();
 nentries = 5000; // for testing purposes

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;

  // make event weight
  event_weight = makeEventWeight(crossSec,lumi,nrEvents,isMC);

  // fill histogram
  fillSigHistograms(event_weight);

  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);

 } // end loop over entries

 // make outfile and save histograms
 TFile *outfile = new TFile(outfilename+".root","RECREATE");
 outfile->cd();
 //for(unsigned int i=0; i<ptbinnames.size(); ++i){
 // for(unsigned int j=0; j<sysbinnames.size(); ++j){
 //  WriteHistograms(i,j);
 // }
 //}
 writeSigHistograms();
 outfile->Close();

} // end analyzer_signal::Loop()

//----------------------------initSigHistograms
Bool_t analyzer_signal::initSigHistograms()
{

 printf("initSigHistograms\n");
  //   TString h_sig_PT_BASICCALOJETS1PT20MATCHED            
  //   TString h_sig_NGOODVERTICES 
  //   TString h_sig_ALPHAMAX                                        
  //   TString h_sig_ASSOCAPLANARITY                                 
  //   TString h_sig_ASSOCIATEDTRACKPT                               
  //   TString h_sig_ASSOCSPHERICITY                                 
  //   TString h_sig_ASSOCTHRUSTMAJOR                                
  //   TString h_sig_ASSOCTHRUSTMINOR                                
  //   TString h_sig_AVFASSOCSPHERICITY                              
  //   TString h_sig_AVFASSOCTHRUSTMAJOR                             
  //   TString h_sig_AVFASSOCTHRUSTMINOR                             
  //   TString h_sig_BETA                                            
  //   TString h_sig_MEDIANIPLOG10SIG                                
  //   TString h_sig_MEDIANLOG10TRACKANGLE                           
  //   TString h_sig_MISSINGINNER                                    
  //   TString h_sig_SUMIP                                           
  //   TString h_sig_SUMIPSIG                                        
  //   TString h_sig_TOTALTRACKPT                                    
  //   TString h_sig_TOTALTRACKANGLE                                 
  //  
  //   TString h_sig_HT                                              
  //   TString h_sig_Max_LEPTON_DPHI                                 
  //   TString h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED  
  //   TString h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED          
  //   TString h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED   
  //   TString h_sig_MET                                             
  //   TString h_sig_Min_LEPTON_DPHI                                 
  //   TString h_sig_Alt_MT                                          
  //   TString h_sig_PTOSSF                                          
  //   TString h_sig_Alt_WPT                                         

 // initialize names (more general - easier for when we incorporate systematics)
 TString hname_sig_PT            = "h_sig_PT"           ;
 TString hname_sig_NGOODVERTICES = "h_sig_NGOODVERTICES";

 TString hname_sig_ALPHAMAX              = "h_sig_ALPHAMAX";                                        
 TString hname_sig_ASSOCAPLANARITY       = "h_sig_ASSOCAPLANARITY";                                 
 TString hname_sig_ASSOCIATEDTRACKPT     = "h_sig_ASSOCIATEDTRACKPT";                               
 TString hname_sig_ASSOCSPHERICITY       = "h_sig_ASSOCSPHERICITY";                                 
 TString hname_sig_ASSOCTHRUSTMAJOR      = "h_sig_ASSOCTHRUSTMAJOR";                                
 TString hname_sig_ASSOCTHRUSTMINOR      = "h_sig_ASSOCTHRUSTMINOR ";                               
 TString hname_sig_AVFASSOCSPHERICITY    = "h_sig_AVFASSOCSPHERICITY";                              
 TString hname_sig_AVFASSOCTHRUSTMAJOR   = "h_sig_AVFASSOCTHRUSTMAJOR";                             
 TString hname_sig_AVFASSOCTHRUSTMINOR   = "h_sig_AVFASSOCTHRUSTMINOR";                             
 TString hname_sig_BETA                  = "h_sig_BETA";                                            
 TString hname_sig_MEDIANIPLOG10SIG      = "h_sig_MEDIANIPLOG10SIG";                                
 TString hname_sig_MEDIANLOG10TRACKANGLE = "h_sig_MEDIANLOG10TRACKANGLE";                           
 TString hname_sig_MISSINGINNER          = "h_sig_MISSINGINNER";                                    
 TString hname_sig_SUMIP                 = "h_sig_SUMIP";                                           
 TString hname_sig_SUMIPSIG              = "h_sig_SUMIPSIG";                                        
 TString hname_sig_TOTALTRACKPT          = "h_sig_TOTALTRACKPT";                                    
 TString hname_sig_TOTALTRACKANGLE       = "h_sig_TOTALTRACKANGLE";                                 

 TString hname_sig_HT                                              = "h_sig_HT";                                              
 TString hname_sig_Max_LEPTON_DPHI                                 = "h_sig_Max_LEPTON_DPHI";                                 
 TString hname_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED  = "h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED";  
 TString hname_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED          = "h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED";          
 TString hname_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED   = "h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED";   
 TString hname_sig_MET                                             = "h_sig_MET";                                             
 TString hname_sig_Min_LEPTON_DPHI                                 = "h_sig_Min_LEPTON_DPHI";                                 
 TString hname_sig_Alt_MT                                          = "h_sig_Alt_MT";                                          
 TString hname_sig_PTOSSF                                          = "h_sig_PTOSSF";                                          
 TString hname_sig_Alt_WPT                                         = "h_sig_Alt_WPT";                                         
 

 // initalize histograms

 // clear
 h_sig_PT[0]                                            .Clear();
 h_sig_NGOODVERTICES[0]                                 .Clear();
 h_sig_ALPHAMAX[0]                                      .Clear();
 h_sig_ASSOCAPLANARITY[0]                               .Clear();
 h_sig_ASSOCIATEDTRACKPT[0]                             .Clear();
 h_sig_ASSOCSPHERICITY[0]                               .Clear();
 h_sig_ASSOCTHRUSTMAJOR[0]                              .Clear();
 h_sig_ASSOCTHRUSTMINOR[0]                              .Clear();
 h_sig_AVFASSOCSPHERICITY[0]                            .Clear();
 h_sig_AVFASSOCTHRUSTMAJOR[0]                           .Clear();
 h_sig_AVFASSOCTHRUSTMINOR[0]                           .Clear();
 h_sig_BETA[0]                                          .Clear();
 h_sig_MEDIANIPLOG10SIG[0]                              .Clear();
 h_sig_MEDIANLOG10TRACKANGLE[0]                         .Clear();
 h_sig_MISSINGINNER[0]                                  .Clear();
 h_sig_SUMIP[0]                                         .Clear();
 h_sig_SUMIPSIG[0]                                      .Clear();
 h_sig_TOTALTRACKPT[0]                                  .Clear();
 h_sig_TOTALTRACKANGLE[0]                               .Clear();
 h_sig_HT[0]                                            .Clear();
 h_sig_Max_LEPTON_DPHI[0]                               .Clear();
 h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED[0].Clear();
 h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED[0]        .Clear();
 h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED[0] .Clear();
 h_sig_MET[0]                                           .Clear();
 h_sig_Min_LEPTON_DPHI[0]                               .Clear();
 h_sig_Alt_MT[0]                                        .Clear();
 h_sig_PTOSSF[0]                                        .Clear();
 h_sig_Alt_WPT[0]                                       .Clear();

 // initialize
 h_sig_PT[0]                                             = TH1F( hname_sig_PT                   ,"PT"                   , 500,0,500);
 h_sig_NGOODVERTICES[0]                                  = TH1F( hname_sig_NGOODVERTICES        ,"NGOODVERTICES"        , 60,0,60);
 h_sig_ALPHAMAX[0]                                       = TH1F( hname_sig_ALPHAMAX             ,"ALPHAMAX"             , 100, 0, 1);
 h_sig_ASSOCAPLANARITY[0]                                = TH1F( hname_sig_ASSOCAPLANARITY      ,"ASSOCAPLANARITY"      , 100, 0, 1);
 h_sig_ASSOCIATEDTRACKPT[0]                              = TH1F( hname_sig_ASSOCIATEDTRACKPT    ,"ASSOCIATEDTRACKPT"    , 200, 0, 200);
 h_sig_ASSOCSPHERICITY[0]                                = TH1F( hname_sig_ASSOCSPHERICITY      ,"ASSOCSPHERICITY"      , 100, 0, 1);
 h_sig_ASSOCTHRUSTMAJOR[0]                               = TH1F( hname_sig_ASSOCTHRUSTMAJOR     ,"ASSOCTHRUSTMAJOR"     , 100, 0, 1);
 h_sig_ASSOCTHRUSTMINOR[0]                               = TH1F( hname_sig_ASSOCTHRUSTMINOR     ,"ASSOCTHRUSTMINOR"     , 100, 0, 1);
 h_sig_AVFASSOCSPHERICITY[0]                             = TH1F( hname_sig_AVFASSOCSPHERICITY   ,"AVFASSOCSPHERICITY"   , 100, 0, 1);
 h_sig_AVFASSOCTHRUSTMAJOR[0]                            = TH1F( hname_sig_AVFASSOCTHRUSTMAJOR  ,"AVFASSOCTHRUSTMAJOR"  , 100, 0, 1);
 h_sig_AVFASSOCTHRUSTMINOR[0]                            = TH1F( hname_sig_AVFASSOCTHRUSTMINOR  ,"AVFASSOCTHRUSTMINOR"  , 100, 0, 1);
 h_sig_BETA[0]                                           = TH1F( hname_sig_BETA                 ,"BETA"                 , 100, 0, 1);
 h_sig_MEDIANIPLOG10SIG[0]                               = TH1F( hname_sig_MEDIANIPLOG10SIG     ,"MEDIANIPLOG10SIG"     , 100, -1, 4);
 h_sig_MEDIANLOG10TRACKANGLE[0]                          = TH1F( hname_sig_MEDIANLOG10TRACKANGLE,"MEDIANLOG10TRACKANGLE", 100, -4, 1);
 h_sig_MISSINGINNER[0]                                   = TH1F( hname_sig_MISSINGINNER         ,"MISSINGINNER"         , 100, 0, 10);
 h_sig_SUMIP[0]                                          = TH1F( hname_sig_SUMIP                ,"SUMIP"                , 100, 0, 750);
 h_sig_SUMIPSIG[0]                                       = TH1F( hname_sig_SUMIPSIG             ,"SUMIPSIG"             , 100, 0, 750);
 h_sig_TOTALTRACKPT[0]                                   = TH1F( hname_sig_TOTALTRACKPT         ,"TOTALTRACKPT"         , 100, 0, 200);
 h_sig_TOTALTRACKANGLE[0]                                = TH1F( hname_sig_TOTALTRACKANGLE      ,"TOTALTRACKANGLE"      , 100, 0, 3.15);
 h_sig_HT[0]                                             = TH1F( hname_sig_HT                                             , "HT"                                             , 100, 0, 1000);
 h_sig_Max_LEPTON_DPHI[0]                                = TH1F( hname_sig_Max_LEPTON_DPHI                                , "Max_LEPTON_DPHI"                                , 100, 0, 3.15);
 h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED[0] = TH1F( hname_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED , "Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED" , 100, -1, 4);
 h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED[0]         = TH1F( hname_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED         , "Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED"         , 100, 0, 750);
 h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED[0]  = TH1F( hname_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED  , "Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED"  , 100, 0, 3.15);
 h_sig_MET[0]                                            = TH1F( hname_sig_MET                                            , "MET"                                            , 100, 0, 300);
 h_sig_Min_LEPTON_DPHI[0]                                = TH1F( hname_sig_Min_LEPTON_DPHI                                , "Min_LEPTON_DPHI"                                , 100, 0, 3.15);
 h_sig_Alt_MT[0]                                         = TH1F( hname_sig_Alt_MT                                         , "Alt_MT"                                         , 100, 0, 500);
 h_sig_PTOSSF[0]                                         = TH1F( hname_sig_PTOSSF                                         , "PTOSSF"                                         , 100, 0, 400);
 h_sig_Alt_WPT[0]                                        = TH1F( hname_sig_Alt_WPT                                        , "Alt_WPT"                                        , 100, 0, 1000);

 // initialze weights
 h_sig_PT[0]                                            .Sumw2();
 h_sig_NGOODVERTICES[0]                                 .Sumw2();
 h_sig_ALPHAMAX[0]                                      .Sumw2();
 h_sig_ASSOCAPLANARITY[0]                               .Sumw2();
 h_sig_ASSOCIATEDTRACKPT[0]                             .Sumw2();
 h_sig_ASSOCSPHERICITY[0]                               .Sumw2();
 h_sig_ASSOCTHRUSTMAJOR[0]                              .Sumw2();
 h_sig_ASSOCTHRUSTMINOR[0]                              .Sumw2();
 h_sig_AVFASSOCSPHERICITY[0]                            .Sumw2();
 h_sig_AVFASSOCTHRUSTMAJOR[0]                           .Sumw2();
 h_sig_AVFASSOCTHRUSTMINOR[0]                           .Sumw2();
 h_sig_BETA[0]                                          .Sumw2();
 h_sig_MEDIANIPLOG10SIG[0]                              .Sumw2();
 h_sig_MEDIANLOG10TRACKANGLE[0]                         .Sumw2();
 h_sig_MISSINGINNER[0]                                  .Sumw2();
 h_sig_SUMIP[0]                                         .Sumw2();
 h_sig_SUMIPSIG[0]                                      .Sumw2();
 h_sig_TOTALTRACKPT[0]                                  .Sumw2();
 h_sig_TOTALTRACKANGLE[0]                               .Sumw2();
 h_sig_HT[0]                                            .Sumw2();
 h_sig_Max_LEPTON_DPHI[0]                               .Sumw2();
 h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED[0].Sumw2();
 h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED[0]        .Sumw2();
 h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED[0] .Sumw2();
 h_sig_MET[0]                                           .Sumw2();
 h_sig_Min_LEPTON_DPHI[0]                               .Sumw2();
 h_sig_Alt_MT[0]                                        .Sumw2();
 h_sig_PTOSSF[0]                                        .Sumw2();
 h_sig_Alt_WPT[0]                                       .Sumw2();

 return kTRUE;
}

//----------------------------fillSigHistograms
Bool_t analyzer_signal::fillSigHistograms(Double_t weight)
{

 printf("fillSigHistograms\n");
 h_sig_PT[0]                                            .Fill(vars_PT_BASICCALOJETS1PT20MATCHED,weight);                                              
 h_sig_NGOODVERTICES[0]                                 .Fill(vars_NGOODVERTICES,weight);                                   
 h_sig_ALPHAMAX[0]                                      .Fill(vars_ALPHAMAX_BASICCALOJETS1PT20MATCHED,weight);                                        
 h_sig_ASSOCAPLANARITY[0]                               .Fill(vars_ASSOCAPLANARITY_BASICCALOJETS1PT20MATCHED,weight);                                 
 h_sig_ASSOCIATEDTRACKPT[0]                             .Fill(vars_ASSOCIATEDTRACKPT_BASICCALOJETS1PT20MATCHED,weight);                               
 h_sig_ASSOCSPHERICITY[0]                               .Fill(vars_ASSOCSPHERICITY_BASICCALOJETS1PT20MATCHED,weight);                                 
 h_sig_ASSOCTHRUSTMAJOR[0]                              .Fill(vars_ASSOCTHRUSTMAJOR_BASICCALOJETS1PT20MATCHED,weight);                                
 h_sig_ASSOCTHRUSTMINOR[0]                              .Fill(vars_ASSOCTHRUSTMINOR_BASICCALOJETS1PT20MATCHED,weight);                                
 h_sig_AVFASSOCSPHERICITY[0]                            .Fill(vars_AVFASSOCSPHERICITY_BASICCALOJETS1PT20MATCHED,weight);                              
 h_sig_AVFASSOCTHRUSTMAJOR[0]                           .Fill(vars_AVFASSOCTHRUSTMAJOR_BASICCALOJETS1PT20MATCHED,weight);                             
 h_sig_AVFASSOCTHRUSTMINOR[0]                           .Fill(vars_AVFASSOCTHRUSTMINOR_BASICCALOJETS1PT20MATCHED,weight);                             
 h_sig_BETA[0]                                          .Fill(vars_BETA_BASICCALOJETS1PT20MATCHED,weight);                                            
 h_sig_MEDIANIPLOG10SIG[0]                              .Fill(vars_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED,weight);                                
 h_sig_MEDIANLOG10TRACKANGLE[0]                         .Fill(vars_MEDIANLOG10TRACKANGLE_BASICCALOJETS1PT20MATCHED,weight);                           
 h_sig_MISSINGINNER[0]                                  .Fill(vars_MISSINGINNER_BASICCALOJETS1PT20MATCHED,weight);                                    
 h_sig_SUMIP[0]                                         .Fill(vars_SUMIP_BASICCALOJETS1PT20MATCHED,weight);                                           
 h_sig_SUMIPSIG[0]                                      .Fill(vars_SUMIPSIG_BASICCALOJETS1PT20MATCHED,weight);                                        
 h_sig_TOTALTRACKPT[0]                                  .Fill(vars_TOTALTRACKPT_BASICCALOJETS1PT20MATCHED,weight);                                    
 h_sig_TOTALTRACKANGLE[0]                               .Fill(vars_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED,weight);                                 
 h_sig_HT[0]                                            .Fill(vars_HT,weight);                                              
 h_sig_Max_LEPTON_DPHI[0]                               .Fill(vars_Max_LEPTON_DPHI,weight);                                 
 h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED[0].Fill(vars_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED,weight);  
 h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED[0]        .Fill(vars_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED,weight);          
 h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED[0] .Fill(vars_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED,weight);   
 h_sig_MET[0]                                           .Fill(vars_MET,weight);                                             
 h_sig_Min_LEPTON_DPHI[0]                               .Fill(vars_Min_LEPTON_DPHI,weight);                                 
 h_sig_Alt_MT[0]                                        .Fill(vars_Alt_MT,weight);                                          
 h_sig_PTOSSF[0]                                        .Fill(vars_PTOSSF,weight);                                          
 h_sig_Alt_WPT[0]                                       .Fill(vars_Alt_WPT,weight);                                         

 return kTRUE;
}

//----------------------------writeSigHistograms
//Bool_t analyzer_signal::writeSigHistograms(int ptbin, int sysbin)
Bool_t analyzer_signal::writeSigHistograms()
{
 printf("writeSigHistograms\n");
 //h_sig_MET[ptbin][sysbin].Write();
 h_sig_PT[0].Write();
 h_sig_NGOODVERTICES[0].Write();

 h_sig_ALPHAMAX[0].Write();  // 0 1
 h_sig_ASSOCAPLANARITY[0].Write();  // 0 1
 h_sig_ASSOCIATEDTRACKPT[0].Write();  // 0 200
 h_sig_ASSOCSPHERICITY[0].Write();  // 0 1
 h_sig_ASSOCTHRUSTMAJOR[0].Write();  // 0 1
 h_sig_ASSOCTHRUSTMINOR[0].Write();  //0 1
 h_sig_AVFASSOCSPHERICITY[0].Write();  // 0 1
 h_sig_AVFASSOCTHRUSTMAJOR[0].Write();  // 0 1
 h_sig_AVFASSOCTHRUSTMINOR[0].Write();  // 0 1
 h_sig_BETA[0].Write();  // 0 1
 h_sig_MEDIANIPLOG10SIG[0].Write();  // -1 4
 h_sig_MEDIANLOG10TRACKANGLE[0].Write();  // -4 1
 h_sig_MISSINGINNER[0].Write();  // 0 10
 h_sig_SUMIP[0].Write();  // 0 750
 h_sig_SUMIPSIG[0].Write();  // 0 750
 h_sig_TOTALTRACKPT[0].Write();  // 0 200
 h_sig_TOTALTRACKANGLE[0].Write();  // 0 3.15

 h_sig_HT[0].Write();  // 0 1000
 h_sig_Max_LEPTON_DPHI[0].Write();  // 0 3.15
 h_sig_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED[0].Write();  // -1 4
 h_sig_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED[0].Write();  // 0 750
 h_sig_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED[0].Write();  // 0 3.15
 h_sig_MET[0].Write();  // 0 300
 h_sig_Min_LEPTON_DPHI[0].Write();  // 0 3.15
 h_sig_Alt_MT[0].Write();  // 0 500
 h_sig_PTOSSF[0].Write();  // 0 400
 h_sig_Alt_WPT[0].Write();  // 0 1000
 
 return kTRUE;
}

analyzer_signal::analyzer_signal()
{
}

analyzer_signal::~analyzer_signal()
{
}
