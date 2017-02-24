#define analyzer_signal_cxx
#include "analyzer_signal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void analyzer_signal::Loop(TString outfilename, Bool_t isMC,
                       Double_t lumi, Double_t nrEvents,
                       Double_t crossSec, Int_t nevts)
{

 if(makelog){
  logfile = fopen( outfilename+".txt", "w"); 
 }

 if (fChain == 0) return;

 Long64_t nentries = fChain->GetEntriesFast();
 if(nevts>0){ 
  nentries = Long64_t(nevts);
 }

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ printf(" entry %lli\n",jentry); }

  // make event weight
  event_weight = makeEventWeight(crossSec,lumi,nrEvents,isMC);

  // printf(" vars_hasGoodVertex %f \n vars_hasDoubleElTriggers %f \n vars_hasDoubleMuTriggers %f \n vars_ONZ %f \n vars_NBASICCALOJETS %f \n",
  //     vars_hasGoodVertex,
  //     vars_hasDoubleElTriggers,
  //     vars_hasDoubleMuTriggers,
  //     vars_ONZ,
  //     vars_NBASICCALOJETS);
  doesPassSig    = askPassSig   ();
  doesPassZH     = askPassZH    ();
  doesPassDY     = askPassDY    ();
  doesPassOffZ   = askPassOffZ  ();
  doesPassNoPair = askPassNoPair();

  // fill histogram
                       fillSigHistograms(event_weight,0);  
  if( doesPassSig   ){ fillSigHistograms(event_weight,1); }
  if( doesPassZH    ){ fillSigHistograms(event_weight,2); }
  if( doesPassDY    ){ fillSigHistograms(event_weight,3); }
  if( doesPassOffZ  ){ fillSigHistograms(event_weight,4); }
  if( doesPassNoPair){ fillSigHistograms(event_weight,5); }

  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);

 } // end loop over entries

 // make outfile and save histograms
 TFile *outfile = new TFile(outfilename+".root","RECREATE");
 outfile->cd();
 for(int i=0; i<selbinnames.size(); ++i){  // i = selbin
  writeSigHistograms(i);
 }
 outfile->Close();

} // end analyzer_signal::Loop()

//----------------------------initSigHistograms
Bool_t analyzer_signal::initSigHistograms()
{

 selbinnames.clear();
 selbinnames.push_back("NoSel");
 selbinnames.push_back("Sig");
 selbinnames.push_back("ZH");
 selbinnames.push_back("DY");
 selbinnames.push_back("OffZ");
 selbinnames.push_back("NoPair");
 

 // initialize names
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  TString hname_sig_PT                    = "h_"+selbinnames[i]+"_PT"           ;
  TString hname_sig_NGOODVERTICES         = "h_"+selbinnames[i]+"_NGOODVERTICES";

  TString hname_sig_ALPHAMAX              = "h_"+selbinnames[i]+"_ALPHAMAX";                                        
  TString hname_sig_ASSOCAPLANARITY       = "h_"+selbinnames[i]+"_ASSOCAPLANARITY";                                 
  TString hname_sig_ASSOCIATEDTRACKPT     = "h_"+selbinnames[i]+"_ASSOCIATEDTRACKPT";                               
  TString hname_sig_ASSOCSPHERICITY       = "h_"+selbinnames[i]+"_ASSOCSPHERICITY";                                 
  TString hname_sig_ASSOCTHRUSTMAJOR      = "h_"+selbinnames[i]+"_ASSOCTHRUSTMAJOR";                                
  TString hname_sig_ASSOCTHRUSTMINOR      = "h_"+selbinnames[i]+"_ASSOCTHRUSTMINOR ";                               
  TString hname_sig_AVFASSOCSPHERICITY    = "h_"+selbinnames[i]+"_AVFASSOCSPHERICITY";                              
  TString hname_sig_AVFASSOCTHRUSTMAJOR   = "h_"+selbinnames[i]+"_AVFASSOCTHRUSTMAJOR";                             
  TString hname_sig_AVFASSOCTHRUSTMINOR   = "h_"+selbinnames[i]+"_AVFASSOCTHRUSTMINOR";                             
  TString hname_sig_BETA                  = "h_"+selbinnames[i]+"_BETA";                                            
  TString hname_sig_MEDIANIPLOG10SIG      = "h_"+selbinnames[i]+"_MEDIANIPLOG10SIG";                                
  TString hname_sig_MEDIANLOG10TRACKANGLE = "h_"+selbinnames[i]+"_MEDIANLOG10TRACKANGLE";                           
  TString hname_sig_MISSINGINNER          = "h_"+selbinnames[i]+"_MISSINGINNER";                                    
  TString hname_sig_SUMIP                 = "h_"+selbinnames[i]+"_SUMIP";                                           
  TString hname_sig_SUMIPSIG              = "h_"+selbinnames[i]+"_SUMIPSIG";                                        
  TString hname_sig_TOTALTRACKPT          = "h_"+selbinnames[i]+"_TOTALTRACKPT";                                    
  TString hname_sig_TOTALTRACKANGLE       = "h_"+selbinnames[i]+"_TOTALTRACKANGLE";                                 

  TString hname_sig_HT                    = "h_"+selbinnames[i]+"_HT";                                              
  TString hname_sig_Max_LEPTON_DPHI       = "h_"+selbinnames[i]+"_Max_LEPTON_DPHI";                                 
  TString hname_sig_Max_MEDIANIPLOG10SIG  = "h_"+selbinnames[i]+"_Max_MEDIANIPLOG10SIG";  
  TString hname_sig_Max_SUMIPSIG          = "h_"+selbinnames[i]+"_Max_SUMIPSIG";          
  TString hname_sig_Max_TOTALTRACKANGLE   = "h_"+selbinnames[i]+"_Max_TOTALTRACKANGLE";   
  TString hname_sig_MET                   = "h_"+selbinnames[i]+"_MET";                                             
  TString hname_sig_Min_LEPTON_DPHI       = "h_"+selbinnames[i]+"_Min_LEPTON_DPHI";                                 
  TString hname_sig_Alt_MT                = "h_"+selbinnames[i]+"_Alt_MT";                                          
  TString hname_sig_PTOSSF                = "h_"+selbinnames[i]+"_PTOSSF";                                          
  TString hname_sig_Alt_WPT               = "h_"+selbinnames[i]+"_Alt_WPT";                                         

  // initalize histograms

  // clear
  h_PT[i]                   .Clear();
  h_NGOODVERTICES[i]        .Clear();
  h_ALPHAMAX[i]             .Clear();
  h_ASSOCAPLANARITY[i]      .Clear();
  h_ASSOCIATEDTRACKPT[i]    .Clear();
  h_ASSOCSPHERICITY[i]      .Clear();
  h_ASSOCTHRUSTMAJOR[i]     .Clear();
  h_ASSOCTHRUSTMINOR[i]     .Clear();
  h_AVFASSOCSPHERICITY[i]   .Clear();
  h_AVFASSOCTHRUSTMAJOR[i]  .Clear();
  h_AVFASSOCTHRUSTMINOR[i]  .Clear();
  h_BETA[i]                 .Clear();
  h_MEDIANIPLOG10SIG[i]     .Clear();
  h_MEDIANLOG10TRACKANGLE[i].Clear();
  h_MISSINGINNER[i]         .Clear();
  h_SUMIP[i]                .Clear();
  h_SUMIPSIG[i]             .Clear();
  h_TOTALTRACKPT[i]         .Clear();
  h_TOTALTRACKANGLE[i]      .Clear();
  h_HT[i]                   .Clear();
  h_Max_LEPTON_DPHI[i]      .Clear();
  h_Max_MEDIANIPLOG10SIG[i] .Clear();
  h_Max_SUMIPSIG[i]         .Clear();
  h_Max_TOTALTRACKANGLE[i]  .Clear();
  h_MET[i]                  .Clear();
  h_Min_LEPTON_DPHI[i]      .Clear();
  h_Alt_MT[i]               .Clear();
  h_PTOSSF[i]               .Clear();
  h_Alt_WPT[i]              .Clear();

  // initialize
  h_PT[i]                    = TH1F( hname_sig_PT                   ,"PT"                   , 500,0,500);
  h_NGOODVERTICES[i]         = TH1F( hname_sig_NGOODVERTICES        ,"NGOODVERTICES"        , 60,0,60);
  h_ALPHAMAX[i]              = TH1F( hname_sig_ALPHAMAX             ,"ALPHAMAX"             , 100, 0, 1);
  h_ASSOCAPLANARITY[i]       = TH1F( hname_sig_ASSOCAPLANARITY      ,"ASSOCAPLANARITY"      , 100, 0, 1);
  h_ASSOCIATEDTRACKPT[i]     = TH1F( hname_sig_ASSOCIATEDTRACKPT    ,"ASSOCIATEDTRACKPT"    , 200, 0, 200);
  h_ASSOCSPHERICITY[i]       = TH1F( hname_sig_ASSOCSPHERICITY      ,"ASSOCSPHERICITY"      , 100, 0, 1);
  h_ASSOCTHRUSTMAJOR[i]      = TH1F( hname_sig_ASSOCTHRUSTMAJOR     ,"ASSOCTHRUSTMAJOR"     , 100, 0, 1);
  h_ASSOCTHRUSTMINOR[i]      = TH1F( hname_sig_ASSOCTHRUSTMINOR     ,"ASSOCTHRUSTMINOR"     , 100, 0, 1);
  h_AVFASSOCSPHERICITY[i]    = TH1F( hname_sig_AVFASSOCSPHERICITY   ,"AVFASSOCSPHERICITY"   , 100, 0, 1);
  h_AVFASSOCTHRUSTMAJOR[i]   = TH1F( hname_sig_AVFASSOCTHRUSTMAJOR  ,"AVFASSOCTHRUSTMAJOR"  , 100, 0, 1);
  h_AVFASSOCTHRUSTMINOR[i]   = TH1F( hname_sig_AVFASSOCTHRUSTMINOR  ,"AVFASSOCTHRUSTMINOR"  , 100, 0, 1);
  h_BETA[i]                  = TH1F( hname_sig_BETA                 ,"BETA"                 , 100, 0, 1);
  h_MEDIANIPLOG10SIG[i]      = TH1F( hname_sig_MEDIANIPLOG10SIG     ,"MEDIANIPLOG10SIG"     , 100, -1, 4);
  h_MEDIANLOG10TRACKANGLE[i] = TH1F( hname_sig_MEDIANLOG10TRACKANGLE,"MEDIANLOG10TRACKANGLE", 100, -4, 1);
  h_MISSINGINNER[i]          = TH1F( hname_sig_MISSINGINNER         ,"MISSINGINNER"         , 100, 0, 10);
  h_SUMIP[i]                 = TH1F( hname_sig_SUMIP                ,"SUMIP"                , 100, 0, 750);
  h_SUMIPSIG[i]              = TH1F( hname_sig_SUMIPSIG             ,"SUMIPSIG"             , 100, 0, 750);
  h_TOTALTRACKPT[i]          = TH1F( hname_sig_TOTALTRACKPT         ,"TOTALTRACKPT"         , 100, 0, 200);
  h_TOTALTRACKANGLE[i]       = TH1F( hname_sig_TOTALTRACKANGLE      ,"TOTALTRACKANGLE"      , 100, 0, 3.15);
  h_HT[i]                    = TH1F( hname_sig_HT                   , "HT"                  , 100, 0, 1000);
  h_Max_LEPTON_DPHI[i]       = TH1F( hname_sig_Max_LEPTON_DPHI      , "Max_LEPTON_DPHI"     , 100, 0, 3.15);
  h_Max_MEDIANIPLOG10SIG[i]  = TH1F( hname_sig_Max_MEDIANIPLOG10SIG , "Max_MEDIANIPLOG10SIG", 100, -1, 4);
  h_Max_SUMIPSIG[i]          = TH1F( hname_sig_Max_SUMIPSIG         , "Max_SUMIPSIG"        , 100, 0, 750);
  h_Max_TOTALTRACKANGLE[i]   = TH1F( hname_sig_Max_TOTALTRACKANGLE  , "Max_TOTALTRACKANGLE" , 100, 0, 3.15);
  h_MET[i]                   = TH1F( hname_sig_MET                  , "MET"                 , 100, 0, 300);
  h_Min_LEPTON_DPHI[i]       = TH1F( hname_sig_Min_LEPTON_DPHI      , "Min_LEPTON_DPHI"     , 100, 0, 3.15);
  h_Alt_MT[i]                = TH1F( hname_sig_Alt_MT               , "Alt_MT"              , 100, 0, 500);
  h_PTOSSF[i]                = TH1F( hname_sig_PTOSSF               , "PTOSSF"              , 100, 0, 400);
  h_Alt_WPT[i]               = TH1F( hname_sig_Alt_WPT              , "Alt_WPT"             , 100, 0, 1000);

  // initialze weights
  h_PT[i]                   .Sumw2();
  h_NGOODVERTICES[i]        .Sumw2();
  h_ALPHAMAX[i]             .Sumw2();
  h_ASSOCAPLANARITY[i]      .Sumw2();
  h_ASSOCIATEDTRACKPT[i]    .Sumw2();
  h_ASSOCSPHERICITY[i]      .Sumw2();
  h_ASSOCTHRUSTMAJOR[i]     .Sumw2();
  h_ASSOCTHRUSTMINOR[i]     .Sumw2();
  h_AVFASSOCSPHERICITY[i]   .Sumw2();
  h_AVFASSOCTHRUSTMAJOR[i]  .Sumw2();
  h_AVFASSOCTHRUSTMINOR[i]  .Sumw2();
  h_BETA[i]                 .Sumw2();
  h_MEDIANIPLOG10SIG[i]     .Sumw2();
  h_MEDIANLOG10TRACKANGLE[i].Sumw2();
  h_MISSINGINNER[i]         .Sumw2();
  h_SUMIP[i]                .Sumw2();
  h_SUMIPSIG[i]             .Sumw2();
  h_TOTALTRACKPT[i]         .Sumw2();
  h_TOTALTRACKANGLE[i]      .Sumw2();
  h_HT[i]                   .Sumw2();
  h_Max_LEPTON_DPHI[i]      .Sumw2();
  h_Max_MEDIANIPLOG10SIG[i] .Sumw2();
  h_Max_SUMIPSIG[i]         .Sumw2();
  h_Max_TOTALTRACKANGLE[i]  .Sumw2();
  h_MET[i]                  .Sumw2();
  h_Min_LEPTON_DPHI[i]      .Sumw2();
  h_Alt_MT[i]               .Sumw2();
  h_PTOSSF[i]               .Sumw2();
  h_Alt_WPT[i]              .Sumw2();
 }

 return kTRUE;
}

//----------------------------fillSigHistograms
Bool_t analyzer_signal::fillSigHistograms(Double_t weight, int selbin)
{

 //printf("fillSigHistograms\n");
 h_PT[selbin]                   .Fill(vars_PT_BASICCALOJETS1PT20MATCHED,weight);                                              
 h_NGOODVERTICES[selbin]        .Fill(vars_NGOODVERTICES,weight);                                   
 h_ALPHAMAX[selbin]             .Fill(vars_ALPHAMAX_BASICCALOJETS1PT20MATCHED,weight);                                        
 h_ASSOCAPLANARITY[selbin]      .Fill(vars_ASSOCAPLANARITY_BASICCALOJETS1PT20MATCHED,weight);                                 
 h_ASSOCIATEDTRACKPT[selbin]    .Fill(vars_ASSOCIATEDTRACKPT_BASICCALOJETS1PT20MATCHED,weight);                               
 h_ASSOCSPHERICITY[selbin]      .Fill(vars_ASSOCSPHERICITY_BASICCALOJETS1PT20MATCHED,weight);                                 
 h_ASSOCTHRUSTMAJOR[selbin]     .Fill(vars_ASSOCTHRUSTMAJOR_BASICCALOJETS1PT20MATCHED,weight);                                
 h_ASSOCTHRUSTMINOR[selbin]     .Fill(vars_ASSOCTHRUSTMINOR_BASICCALOJETS1PT20MATCHED,weight);                                
 h_AVFASSOCSPHERICITY[selbin]   .Fill(vars_AVFASSOCSPHERICITY_BASICCALOJETS1PT20MATCHED,weight);                              
 h_AVFASSOCTHRUSTMAJOR[selbin]  .Fill(vars_AVFASSOCTHRUSTMAJOR_BASICCALOJETS1PT20MATCHED,weight);                             
 h_AVFASSOCTHRUSTMINOR[selbin]  .Fill(vars_AVFASSOCTHRUSTMINOR_BASICCALOJETS1PT20MATCHED,weight);                             
 h_BETA[selbin]                 .Fill(vars_BETA_BASICCALOJETS1PT20MATCHED,weight);                                            
 h_MEDIANIPLOG10SIG[selbin]     .Fill(vars_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED,weight);                                
 h_MEDIANLOG10TRACKANGLE[selbin].Fill(vars_MEDIANLOG10TRACKANGLE_BASICCALOJETS1PT20MATCHED,weight);                           
 h_MISSINGINNER[selbin]         .Fill(vars_MISSINGINNER_BASICCALOJETS1PT20MATCHED,weight);                                    
 h_SUMIP[selbin]                .Fill(vars_SUMIP_BASICCALOJETS1PT20MATCHED,weight);                                           
 h_SUMIPSIG[selbin]             .Fill(vars_SUMIPSIG_BASICCALOJETS1PT20MATCHED,weight);                                        
 h_TOTALTRACKPT[selbin]         .Fill(vars_TOTALTRACKPT_BASICCALOJETS1PT20MATCHED,weight);                                    
 h_TOTALTRACKANGLE[selbin]      .Fill(vars_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED,weight);                                 
 h_HT[selbin]                   .Fill(vars_HT,weight);                                              
 h_Max_LEPTON_DPHI[selbin]      .Fill(vars_Max_LEPTON_DPHI,weight);                                 
 h_Max_MEDIANIPLOG10SIG[selbin] .Fill(vars_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED,weight);  
 h_Max_SUMIPSIG[selbin]         .Fill(vars_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED,weight);          
 h_Max_TOTALTRACKANGLE[selbin]  .Fill(vars_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED,weight);   
 h_MET[selbin]                  .Fill(vars_MET,weight);                                             
 h_Min_LEPTON_DPHI[selbin]      .Fill(vars_Min_LEPTON_DPHI,weight);                                 
 h_Alt_MT[selbin]               .Fill(vars_Alt_MT,weight);                                          
 h_PTOSSF[selbin]               .Fill(vars_PTOSSF,weight);                                          
 h_Alt_WPT[selbin]              .Fill(vars_Alt_WPT,weight);                                         

 return kTRUE;
}

//----------------------------writeSigHistograms
//Bool_t analyzer_signal::writeSigHistograms(int ptbin, int sysbin)
Bool_t analyzer_signal::writeSigHistograms(int selbin)
{
 //printf("writeSigHistograms\n");
 //h_MET[ptbin][sysbin].Write();
 h_PT[selbin].Write();
 h_NGOODVERTICES[selbin].Write();

 h_ALPHAMAX[selbin].Write();  // 0 1
 h_ASSOCAPLANARITY[selbin].Write();  // 0 1
 h_ASSOCIATEDTRACKPT[selbin].Write();  // 0 200
 h_ASSOCSPHERICITY[selbin].Write();  // 0 1
 h_ASSOCTHRUSTMAJOR[selbin].Write();  // 0 1
 h_ASSOCTHRUSTMINOR[selbin].Write();  //0 1
 h_AVFASSOCSPHERICITY[selbin].Write();  // 0 1
 h_AVFASSOCTHRUSTMAJOR[selbin].Write();  // 0 1
 h_AVFASSOCTHRUSTMINOR[selbin].Write();  // 0 1
 h_BETA[selbin].Write();  // 0 1
 h_MEDIANIPLOG10SIG[selbin].Write();  // -1 4
 h_MEDIANLOG10TRACKANGLE[selbin].Write();  // -4 1
 h_MISSINGINNER[selbin].Write();  // 0 10
 h_SUMIP[selbin].Write();  // 0 750
 h_SUMIPSIG[selbin].Write();  // 0 750
 h_TOTALTRACKPT[selbin].Write();  // 0 200
 h_TOTALTRACKANGLE[selbin].Write();  // 0 3.15

 h_HT[selbin].Write();  // 0 1000
 h_Max_LEPTON_DPHI[selbin].Write();  // 0 3.15
 h_Max_MEDIANIPLOG10SIG[selbin].Write();  // -1 4
 h_Max_SUMIPSIG[selbin].Write();  // 0 750
 h_Max_TOTALTRACKANGLE[selbin].Write();  // 0 3.15
 h_MET[selbin].Write();  // 0 300
 h_Min_LEPTON_DPHI[selbin].Write();  // 0 3.15
 h_Alt_MT[selbin].Write();  // 0 500
 h_PTOSSF[selbin].Write();  // 0 400
 h_Alt_WPT[selbin].Write();  // 0 1000
 
 return kTRUE;
}

// cuts
Bool_t analyzer_signal::askPassSig()
{
 Bool_t doespass = kTRUE;
 return doespass;
}

Bool_t analyzer_signal::askPassZH()
{
 Bool_t doespass = kFALSE;
 if(vars_hasGoodVertex > 0.5
    //&& (vars_hasDoubleElTriggers > 0.5 || vars_hasDoubleMuTriggers > 0.5)
    && vars_ONZ > 0.5 
    && vars_PTOSSF > 50
    && vars_NBASICCALOJETS > 0)
 { doespass = kTRUE; }
 return doespass;
}

Bool_t analyzer_signal::askPassDY()
{
 Bool_t doespass = kFALSE;
 if(vars_hasGoodVertex > 0.5
    //&& (vars_hasDoubleElTriggers > 0.5 || vars_hasDoubleMuTriggers > 0.5)
    && vars_ONZ > 0.5 
    && vars_PTOSSF < 50
    && vars_NBASICCALOJETS > 0)
 { doespass = kTRUE; }
 return doespass;
}

Bool_t analyzer_signal::askPassOffZ()
{
 Bool_t doespass = kFALSE;
 if(vars_hasGoodVertex > 0.5
    //&& (vars_hasDoubleElTriggers > 0.5 || vars_hasDoubleMuTriggers > 0.5)
    && vars_ONZ < 0.5 
    && vars_NOSSF == 1
    && vars_NBASICCALOJETS > 0)
 { doespass = kTRUE; }
 return doespass;
}

Bool_t analyzer_signal::askPassNoPair()
{
 Bool_t doespass = kFALSE;
 if(vars_hasGoodVertex > 0.5
    //&& (vars_hasDoubleElTriggers > 0.5 || vars_hasDoubleMuTriggers > 0.5)
    && vars_ONZ < 0.5 
    && vars_NOSSF == 0
    && vars_NBASICCALOJETS > 0)
 { doespass = kTRUE; }
 return doespass;
}

analyzer_signal::analyzer_signal()
{
}

analyzer_signal::~analyzer_signal()
{
}
