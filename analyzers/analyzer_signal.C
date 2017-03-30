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

 ntot=0;
 npassSig=0;
 npassZH=0;
 npassDY=0;
 npassOffZ=0;
 npassNoPair=0;

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ printf(" entry %lli\n",jentry); }

  // make event weight
  event_weight = makeEventWeight(crossSec,lumi,nrEvents,isMC);
  ntot++;

  // variables used in cuts
  if(NGOODVERTICES    ->size()>0){ safeNGOODVERTICES      = NGOODVERTICES    ->at(0);}
  if(NDoubleElTriggers->size()>0){ safeNDoubleElTriggers  = NDoubleElTriggers->at(0);}
  if(NDoubleMuTriggers->size()>0){ safeNDoubleMuTriggers  = NDoubleMuTriggers->at(0);}
  if(NOSSF            ->size()>0){ safeNOSSF              = NOSSF            ->at(0);}
  if(MOSSF            ->size()>0){ safeMOSSF              = MOSSF            ->at(0);}
   if(safeMOSSF>100000.){ safeMOSSF = 0.;}
  if(PTOSSF           ->size()>0){ safePTOSSF             = PTOSSF           ->at(0);}
  if(JetNJets         ->size()>0){ safeJetNJets           = JetNJets         ->at(0);}
 
  printf("  safeNGOODVERTICES      %d\n" , safeNGOODVERTICES     );    
  printf("  safeNDoubleElTriggers  %d\n" , safeNDoubleElTriggers );
  printf("  safeNDoubleMuTriggers  %d\n" , safeNDoubleMuTriggers );
  printf("  safeMOSSF              %f\n" , safeMOSSF             );
  printf("  safeNOSSF              %d\n" , safeNOSSF             );
  printf("  safeJetNJets           %d\n" , safeJetNJets          ); 
  printf("  safePTOSSF             %f\n\n" , safePTOSSF            );    

  // set booleans if pass various selections
  doesPassSig    = askPassSig   ();
  doesPassZH     = askPassZH    ();
  doesPassDY     = askPassDY    ();
  doesPassOffZ   = askPassOffZ  ();
  doesPassNoPair = askPassNoPair();

  // fill histogram
                       fillSigHistograms(event_weight,0); fillJetHistograms(event_weight,0); fill2DHistograms(event_weight,0);  
  if( doesPassSig   ){ fillSigHistograms(event_weight,1); fillJetHistograms(event_weight,1); fill2DHistograms(event_weight,1); }
  if( doesPassZH    ){ fillSigHistograms(event_weight,2); fillJetHistograms(event_weight,2); fill2DHistograms(event_weight,2); }
  if( doesPassDY    ){ fillSigHistograms(event_weight,3); fillJetHistograms(event_weight,3); fill2DHistograms(event_weight,3); }
  if( doesPassOffZ  ){ fillSigHistograms(event_weight,4); fillJetHistograms(event_weight,4); fill2DHistograms(event_weight,4); }
  if( doesPassNoPair){ fillSigHistograms(event_weight,5); fillJetHistograms(event_weight,5); fill2DHistograms(event_weight,5); }

  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);

 } // end loop over entries

 printf(" ntot        %i \n",ntot        ); 
 printf(" npassSig    %i \n",npassSig    ); 
 printf(" npassZH     %i \n",npassZH     ); 
 printf(" npassDY     %i \n",npassDY     ); 
 printf(" npassOffZ   %i \n",npassOffZ   ); 
 printf(" npassNoPair %i \n",npassNoPair ); 

 // make outfile and save histograms
 TFile *outfile = new TFile(outfilename+".root","RECREATE");
 outfile->cd();
 for(int i=0; i<selbinnames.size(); ++i){  // i = selbin
  writeSigHistograms(i);
  writeJetHistograms(i);
  write2DHistograms(i);
 }
 outfile->Close();

} // end analyzer_signal::Loop()

//----------------------------initSingleHistogramTH1F
TH1F analyzer_signal::initSingleHistogramTH1F(TString hname, TString htitle, Int_t nbins, Double_t xmin, Double_t xmax)
{

 histoTH1F.Clear();
 histoTH1F = TH1F( hname , htitle , nbins , xmin , xmax );
 histoTH1F.Sumw2();

 return histoTH1F;

}



//----------------------------initSingleHistogramTH2F
TH2F analyzer_signal::initSingleHistogramTH2F(TString hname, TString htitle,
                                   Int_t nbinsx, Double_t xmin, Double_t xmax,
                                   Int_t nbinsy, Double_t ymin, Double_t ymax)
{

 histoTH2F.Clear();
 histoTH2F = TH2F( hname , htitle , nbinsx , xmin , xmax  , nbinsy , ymin , ymax );
 histoTH2F.Sumw2();

 return histoTH2F;

}

//----------------------------init2DHistograms
Bool_t analyzer_signal::init2DHistograms()
{

 // assumes that selbins and jetmultnames have already been filled (initJetHistograms, initSigHistograms)
 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){

   TString hname_nvertnjets = "h_"+selbinnames[i]+"_NGOODVERTICES_v_NJets";
   TString htitle_nvertnjets = "Nr. Good Vertices (x) vs. Nr. Jets (y)" ;
   h_nvertnjets[i] = initSingleHistogramTH2F( hname_nvertnjets, htitle_nvertnjets, 50, 0, 50, 50, 0, 50 ); 

  for(unsigned int j=0; j<jetmultnames.size(); ++j){
   // for histograms that are jet specific
  }
 }

 return kTRUE;
}


//----------------------------fill2DHistograms
Bool_t analyzer_signal::fill2DHistograms(Double_t weight, int selbin)
{
 //printf("fill2DHistograms\n");

  if( NGOODVERTICES->size()>0 && JetNJets->size()>0 ) 
   { h_nvertnjets[selbin].Fill( NGOODVERTICES->at(0), JetNJets->at(0), weight ); }

 return kTRUE;
}


//----------------------------write2DHistograms
Bool_t analyzer_signal::write2DHistograms(int selbin)
{
 //printf("write2DtHistograms\n");
 h_nvertnjets[selbin].Write(); 
 for(unsigned int j=0; j<jetmultnames.size(); ++j){
   // for histograms that are jet specific
 }

 return kTRUE;
}


//----------------------------initJetHistograms
Bool_t analyzer_signal::initJetHistograms()
{

 // initialize names
 jetmultnames.clear();
 jetmultnames.push_back("LeadingJet");
 jetmultnames.push_back("SubleadingJet");
 jetmultnames.push_back("ThirdJet");
 jetmultnames.push_back("FourthJet");

 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int j=0; j<jetmultnames.size(); ++j){

 // JET
  TString hname_MISSINGINNER                            = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MISSINGINNER"                                       ; 
  TString hname_MISSINGOUTER                            = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MISSINGOUTER"                                       ; 
  TString hname_HSPH                                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_HSPH"                                               ; 
  TString hname_NJets                                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_NJets"                                              ; 
  TString hname_NCLEANMATCHEDTRACKS                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_NCLEANMATCHEDTRACKS"                                ; 
  TString hname_NMATCHEDTRACKS                          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_NMATCHEDTRACKS"                                     ; 
  TString hname_NTRACKSIPLT0P05                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_NTRACKSIPLT0P05"                                    ; 
  TString hname_NTRACKSIPSIGGT10                        = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_NTRACKSIPSIGGT10"                                   ; 
  TString hname_NTRACKSIPSIGLT5                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_NTRACKSIPSIGLT5"                                    ; 
  TString hname_ALPHAMAX2                               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ALPHAMAX2"                                          ; 
  TString hname_ALPHAMAXPRIME2                          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ALPHAMAXPRIME2"                                     ; 
  TString hname_ALPHAMAXPRIME                           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ALPHAMAXPRIME"                                      ; 
  TString hname_ALPHAMAX                                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ALPHAMAX"                                           ; 
  TString hname_ASSOCAPLANARITY                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ASSOCAPLANARITY"                                    ; 
  TString hname_ASSOCIATEDTRACKPT                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ASSOCIATEDTRACKPT"                                  ; 
  TString hname_ASSOCSPHERICITY                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ASSOCSPHERICITY"                                    ; 
  TString hname_ASSOCTHRUSTMAJOR                        = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ASSOCTHRUSTMAJOR"                                   ; 
  TString hname_ASSOCTHRUSTMINOR                        = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ASSOCTHRUSTMINOR"                                   ; 
  TString hname_AVFASSOCAPLANARITY                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFASSOCAPLANARITY"                                 ; 
  TString hname_AVFASSOCSPHERICITY                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFASSOCSPHERICITY"                                 ; 
  TString hname_AVFASSOCTHRUSTMAJOR                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFASSOCTHRUSTMAJOR"                                ; 
  TString hname_AVFASSOCTHRUSTMINOR                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFASSOCTHRUSTMINOR"                                ; 
  TString hname_AVFBEAMSPOTDELTAPHI                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFBEAMSPOTDELTAPHI"                                ; 
  TString hname_AVFBEAMSPOTRECOILPT                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFBEAMSPOTRECOILPT"                                ; 
  TString hname_AVFDISTTOPV                             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFDISTTOPV"                                        ; 
  TString hname_AVFVERTEXCHI2NDOF                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXCHI2NDOF"                                  ; 
  TString hname_AVFVERTEXDEGREESOFFREEDOM               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXDEGREESOFFREEDOM"                          ; 
  TString hname_AVFVERTEXDISTANCETOBEAM                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXDISTANCETOBEAM"                            ; 
  TString hname_AVFVERTEXTOTALCHISQUARED                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXTOTALCHISQUARED"                           ; 
  TString hname_AVFVERTEXTRACKENERGY                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXTRACKENERGY"                               ; 
  TString hname_AVFVERTEXTRACKMASS                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXTRACKMASS"                                 ; 
  TString hname_AVFVERTEXTRANSVERSESIG                  = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVFVERTEXTRANSVERSESIG"                             ; 
  TString hname_AVGMISSINGINNER                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVGMISSINGINNER"                                    ; 
  TString hname_AVGMISSINGOUTER                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AVGMISSINGOUTER"                                    ; 
  TString hname_BASICCALOJETS1ANGLE_DANGLE              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_BASICCALOJETS1ANGLE_DANGLE"                         ; 
  TString hname_BASICCALOJETS1ANGLE_DPHI                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_BASICCALOJETS1ANGLE_DPHI"                           ; 
  TString hname_BASICCALOJETS1DELTAR                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_BASICCALOJETS1DELTAR"                               ; 
  TString hname_BASICCALOJETS1PT20DELTAR                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_BASICCALOJETS1PT20DELTAR"                           ; 
  TString hname_BETA2                                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_BETA2"                                              ; 
  TString hname_BETA                                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_BETA"                                               ; 
  TString hname_ETA                                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_ETA"                                                ; 
  TString hname_HITSINFRONTOFVERTPERTRACK               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_HITSINFRONTOFVERTPERTRACK"                          ; 
  TString hname_IVFSCORE                                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_IVFSCORE"                                           ; 
  TString hname_JETAREA                                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_JETAREA"                                            ; 
  TString hname_LEPANGLE_DANGLE                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_LEPANGLE_DANGLE"                                    ; 
  TString hname_LEPANGLE_DPHI                           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_LEPANGLE_DPHI"                                      ; 
  TString hname_LEPDELTAR                               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_LEPDELTAR"                                          ; 
  TString hname_LINEARRADIALMOMENT                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_LINEARRADIALMOMENT"                                 ; 
  TString hname_LRM                                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_LRM"                                                ; 
  TString hname_MASSDISPLACED                           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MASSDISPLACED"                                      ; 
  TString hname_MEDIANIPLOG10SIG                        = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MEDIANIPLOG10SIG"                                   ; 
  TString hname_MEDIANIPLOGSIG                          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MEDIANIPLOGSIG"                                     ; 
  TString hname_MEDIANLOG10TRACKANGLE                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MEDIANLOG10TRACKANGLE"                              ; 
  TString hname_METANGLE_DANGLE                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_METANGLE_DANGLE"                                    ; 
  TString hname_METANGLE_DPHI                           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_METANGLE_DPHI"                                      ; 
  TString hname_METDELTAR                               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_METDELTAR"                                          ; 
  TString hname_MISSHITSAFTERVERTPERTRACK               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_MISSHITSAFTERVERTPERTRACK"                          ; 
  TString hname_M                                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_M"                                                  ; 
  TString hname_PHI                                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_PHI"                                                ; 
  TString hname_PT                                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_PT"                                                 ; 
  TString hname_SELFDELTAR                              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_SELFDELTAR"                                         ; 
  TString hname_SSPH                                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_SSPH"                                               ; 
  TString hname_STUPAKPT                                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_STUPAKPT"                                           ; 
  TString hname_STUPAKR                                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_STUPAKR"                                            ; 
  TString hname_SUMIPLOGSIG                             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_SUMIPLOGSIG"                                        ; 
  TString hname_SUMIPSIG                                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_SUMIPSIG"                                           ; 
  TString hname_SUMIP                                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_SUMIP"                                              ; 
  TString hname_TOTALTRACKANGLEPT                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_TOTALTRACKANGLEPT"                                  ; 
  TString hname_TOTALTRACKANGLE                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_TOTALTRACKANGLE"                                    ; 
  TString hname_TOTALTRACKPT                            = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_TOTALTRACKPT"                                       ; 
  TString hname_TRACKENERGY                             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_TRACKENERGY"                                        ; 
  TString hname_TRACKMASS                               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_TRACKMASS"                                          ; 

  // initalize histograms
  h_JetMISSINGINNER                            [i][j] = initSingleHistogramTH1F( hname_MISSINGINNER                             , "MISSINGINNER                           " , 50, 0, 50 ); 
  h_JetMISSINGOUTER                            [i][j] = initSingleHistogramTH1F( hname_MISSINGOUTER                             , "MISSINGOUTER                           " , 50, 0, 50 ); 
  h_JetHSPH                                    [i][j] = initSingleHistogramTH1F( hname_HSPH                                     , "HSPH                                   " , 50, 0, 50 ); 
  h_JetNJets                                   [i][j] = initSingleHistogramTH1F( hname_NJets                                    , "NJets                                  " , 50, 0, 50 ); 
  h_JetNCLEANMATCHEDTRACKS                     [i][j] = initSingleHistogramTH1F( hname_NCLEANMATCHEDTRACKS                      , "NCLEANMATCHEDTRACKS                    " , 50, 0, 50 ); 
  h_JetNMATCHEDTRACKS                          [i][j] = initSingleHistogramTH1F( hname_NMATCHEDTRACKS                           , "NMATCHEDTRACKS                         " , 50, 0, 50 ); 
  h_JetNTRACKSIPLT0P05                         [i][j] = initSingleHistogramTH1F( hname_NTRACKSIPLT0P05                          , "NTRACKSIPLT0P05                        " , 50, 0, 50 ); 
  h_JetNTRACKSIPSIGGT10                        [i][j] = initSingleHistogramTH1F( hname_NTRACKSIPSIGGT10                         , "NTRACKSIPSIGGT10                       " , 50, 0, 50 ); 
  h_JetNTRACKSIPSIGLT5                         [i][j] = initSingleHistogramTH1F( hname_NTRACKSIPSIGLT5                          , "NTRACKSIPSIGLT5                        " , 50, 0, 50 ); 
  h_JetALPHAMAX2                               [i][j] = initSingleHistogramTH1F( hname_ALPHAMAX2                                , "ALPHAMAX2                              " , 20, 0, 1 ); 
  h_JetALPHAMAXPRIME2                          [i][j] = initSingleHistogramTH1F( hname_ALPHAMAXPRIME2                           , "ALPHAMAXPRIME2                         " , 20, 0, 1 ); 
  h_JetALPHAMAXPRIME                           [i][j] = initSingleHistogramTH1F( hname_ALPHAMAXPRIME                            , "ALPHAMAXPRIME                          " , 20, 0, 1 ); 
  h_JetALPHAMAX                                [i][j] = initSingleHistogramTH1F( hname_ALPHAMAX                                 , "ALPHAMAX                               " , 20, 0, 1 ); 
  h_JetASSOCAPLANARITY                         [i][j] = initSingleHistogramTH1F( hname_ASSOCAPLANARITY                          , "ASSOCAPLANARITY                        " , 20, 0, 1 ); 
  h_JetASSOCIATEDTRACKPT                       [i][j] = initSingleHistogramTH1F( hname_ASSOCIATEDTRACKPT                        , "ASSOCIATEDTRACKPT                      " , 200, 0, 100 ); 
  h_JetASSOCSPHERICITY                         [i][j] = initSingleHistogramTH1F( hname_ASSOCSPHERICITY                          , "ASSOCSPHERICITY                        " , 20, 0, 1 ); 
  h_JetASSOCTHRUSTMAJOR                        [i][j] = initSingleHistogramTH1F( hname_ASSOCTHRUSTMAJOR                         , "ASSOCTHRUSTMAJOR                       " , 20, 0, 1 ); 
  h_JetASSOCTHRUSTMINOR                        [i][j] = initSingleHistogramTH1F( hname_ASSOCTHRUSTMINOR                         , "ASSOCTHRUSTMINOR                       " , 20, 0, 1 ); 
  h_JetAVFASSOCAPLANARITY                      [i][j] = initSingleHistogramTH1F( hname_AVFASSOCAPLANARITY                       , "AVFASSOCAPLANARITY                     " , 20, 0, 1 ); 
  h_JetAVFASSOCSPHERICITY                      [i][j] = initSingleHistogramTH1F( hname_AVFASSOCSPHERICITY                       , "AVFASSOCSPHERICITY                     " , 20, 0, 1 ); 
  h_JetAVFASSOCTHRUSTMAJOR                     [i][j] = initSingleHistogramTH1F( hname_AVFASSOCTHRUSTMAJOR                      , "AVFASSOCTHRUSTMAJOR                    " , 20, 0, 1 ); 
  h_JetAVFASSOCTHRUSTMINOR                     [i][j] = initSingleHistogramTH1F( hname_AVFASSOCTHRUSTMINOR                      , "AVFASSOCTHRUSTMINOR                    " , 20, 0, 1 ); 
  h_JetAVFBEAMSPOTDELTAPHI                     [i][j] = initSingleHistogramTH1F( hname_AVFBEAMSPOTDELTAPHI                      , "AVFBEAMSPOTDELTAPHI                    " , 100, -5, 5 ); 
  h_JetAVFBEAMSPOTRECOILPT                     [i][j] = initSingleHistogramTH1F( hname_AVFBEAMSPOTRECOILPT                      , "AVFBEAMSPOTRECOILPT                    " , 100, 0, 100 ); 
  h_JetAVFDISTTOPV                             [i][j] = initSingleHistogramTH1F( hname_AVFDISTTOPV                              , "AVFDISTTOPV                            " , 100, 0, 100 ); 
  h_JetAVFVERTEXCHI2NDOF                       [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXCHI2NDOF                        , "AVFVERTEXCHI2NDOF                      " , 100, 0, 100 ); 
  h_JetAVFVERTEXDEGREESOFFREEDOM               [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXDEGREESOFFREEDOM                , "AVFVERTEXDEGREESOFFREEDOM              " , 40, 0, 40 ); 
  h_JetAVFVERTEXDISTANCETOBEAM                 [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXDISTANCETOBEAM                  , "AVFVERTEXDISTANCETOBEAM                " , 100, 0, 100 ); 
  h_JetAVFVERTEXTOTALCHISQUARED                [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXTOTALCHISQUARED                 , "AVFVERTEXTOTALCHISQUARED               " , 100, 0, 100 ); 
  h_JetAVFVERTEXTRACKENERGY                    [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXTRACKENERGY                     , "AVFVERTEXTRACKENERGY                   " , 200, 0, 200 ); 
  h_JetAVFVERTEXTRACKMASS                      [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXTRACKMASS                       , "AVFVERTEXTRACKMASS                     " , 200, 0, 200 ); 
  h_JetAVFVERTEXTRANSVERSESIG                  [i][j] = initSingleHistogramTH1F( hname_AVFVERTEXTRANSVERSESIG                   , "AVFVERTEXTRANSVERSESIG                 " , 200, 0, 200 ); 
  h_JetAVGMISSINGINNER                         [i][j] = initSingleHistogramTH1F( hname_AVGMISSINGINNER                          , "AVGMISSINGINNER                        " , 50, 0, 5 ); 
  h_JetAVGMISSINGOUTER                         [i][j] = initSingleHistogramTH1F( hname_AVGMISSINGOUTER                          , "AVGMISSINGOUTER                        " , 40, 0, 20 ); 
  h_JetBASICCALOJETS1ANGLE_DANGLE              [i][j] = initSingleHistogramTH1F( hname_BASICCALOJETS1ANGLE_DANGLE               , "BASICCALOJETS1ANGLE_DANGLE             " , 100, 0, 100 ); 
  h_JetBASICCALOJETS1ANGLE_DPHI                [i][j] = initSingleHistogramTH1F( hname_BASICCALOJETS1ANGLE_DPHI                 , "BASICCALOJETS1ANGLE_DPHI               " , 100, 0, 100 ); 
  h_JetBASICCALOJETS1DELTAR                    [i][j] = initSingleHistogramTH1F( hname_BASICCALOJETS1DELTAR                     , "BASICCALOJETS1DELTAR                   " , 20, 0, 10 ); 
  h_JetBASICCALOJETS1PT20DELTAR                [i][j] = initSingleHistogramTH1F( hname_BASICCALOJETS1PT20DELTAR                 , "BASICCALOJETS1PT20DELTAR               " , 20, 0, 10 ); 
  h_JetBETA2                                   [i][j] = initSingleHistogramTH1F( hname_BETA2                                    , "BETA2                                  " , 40, 0, 2 ); 
  h_JetBETA                                    [i][j] = initSingleHistogramTH1F( hname_BETA                                     , "BETA                                   " , 40, 0, 2 ); 
  h_JetETA                                     [i][j] = initSingleHistogramTH1F( hname_ETA                                      , "ETA                                    " , 100, -6, 6 ); 
  h_JetHITSINFRONTOFVERTPERTRACK               [i][j] = initSingleHistogramTH1F( hname_HITSINFRONTOFVERTPERTRACK                , "HITSINFRONTOFVERTPERTRACK              " , 100, 0, 100 ); 
  h_JetIVFSCORE                                [i][j] = initSingleHistogramTH1F( hname_IVFSCORE                                 , "IVFSCORE                               " , 100, 0, 100 ); 
  h_JetJETAREA                                 [i][j] = initSingleHistogramTH1F( hname_JETAREA                                  , "JETAREA                                " , 20, 0, 1 ); 
  h_JetLEPANGLE_DANGLE                         [i][j] = initSingleHistogramTH1F( hname_LEPANGLE_DANGLE                          , "LEPANGLE_DANGLE                        " , 40, 0, 4 ); 
  h_JetLEPANGLE_DPHI                           [i][j] = initSingleHistogramTH1F( hname_LEPANGLE_DPHI                            , "LEPANGLE_DPHI                          " , 100, -4, 4 ); 
  h_JetLEPDELTAR                               [i][j] = initSingleHistogramTH1F( hname_LEPDELTAR                                , "LEPDELTAR                              " , 50, 0, 10 ); 
  h_JetLINEARRADIALMOMENT                      [i][j] = initSingleHistogramTH1F( hname_LINEARRADIALMOMENT                       , "LINEARRADIALMOMENT                     " , 20, 0, 5 ); 
  h_JetLRM                                     [i][j] = initSingleHistogramTH1F( hname_LRM                                      , "LRM                                    " , 100, 0, 100 ); 
  h_JetMASSDISPLACED                           [i][j] = initSingleHistogramTH1F( hname_MASSDISPLACED                            , "MASSDISPLACED                          " , 100, 0, 100 ); 
  h_JetMEDIANIPLOG10SIG                        [i][j] = initSingleHistogramTH1F( hname_MEDIANIPLOG10SIG                         , "MEDIANIPLOG10SIG                       " , 100, -10, 10 ); 
  h_JetMEDIANIPLOGSIG                          [i][j] = initSingleHistogramTH1F( hname_MEDIANIPLOGSIG                           , "MEDIANIPLOGSIG                         " , 100,-10, 10 ); 
  h_JetMEDIANLOG10TRACKANGLE                   [i][j] = initSingleHistogramTH1F( hname_MEDIANLOG10TRACKANGLE                    , "MEDIANLOG10TRACKANGLE                  " , 100, -10, 10 ); 
  h_JetMETANGLE_DANGLE                         [i][j] = initSingleHistogramTH1F( hname_METANGLE_DANGLE                          , "METANGLE_DANGLE                        " , 50, 0, 5 ); 
  h_JetMETANGLE_DPHI                           [i][j] = initSingleHistogramTH1F( hname_METANGLE_DPHI                            , "METANGLE_DPHI                          " , 40, -10, 10 ); 
  h_JetMETDELTAR                               [i][j] = initSingleHistogramTH1F( hname_METDELTAR                                , "METDELTAR                              " , 100, 0, 10 ); 
  h_JetMISSHITSAFTERVERTPERTRACK               [i][j] = initSingleHistogramTH1F( hname_MISSHITSAFTERVERTPERTRACK                , "MISSHITSAFTERVERTPERTRACK              " , 100, 0, 10 ); 
  h_JetM                                       [i][j] = initSingleHistogramTH1F( hname_M                                        , "M                                      " , 200, 0, 200 ); 
  h_JetPHI                                     [i][j] = initSingleHistogramTH1F( hname_PHI                                      , "PHI                                    " , 40, -4, 4 ); 
  h_JetPT                                      [i][j] = initSingleHistogramTH1F( hname_PT                                       , "PT                                     " , 200, 0, 200 ); 
  h_JetSELFDELTAR                              [i][j] = initSingleHistogramTH1F( hname_SELFDELTAR                               , "SELFDELTAR                             " , 100, 0, 10 ); 
  h_JetSSPH                                    [i][j] = initSingleHistogramTH1F( hname_SSPH                                     , "SSPH                                   " , 20, -1, 1 ); 
  h_JetSTUPAKPT                                [i][j] = initSingleHistogramTH1F( hname_STUPAKPT                                 , "STUPAKPT                               " , 100, 0, 100 ); 
  h_JetSTUPAKR                                 [i][j] = initSingleHistogramTH1F( hname_STUPAKR                                  , "STUPAKR                                " , 3, 0, 10000 ); 
  h_JetSUMIPLOGSIG                             [i][j] = initSingleHistogramTH1F( hname_SUMIPLOGSIG                              , "SUMIPLOGSIG                            " , 100, -20, 40 ); 
  h_JetSUMIPSIG                                [i][j] = initSingleHistogramTH1F( hname_SUMIPSIG                                 , "SUMIPSIG                               " , 100, 0, 100 ); 
  h_JetSUMIP                                   [i][j] = initSingleHistogramTH1F( hname_SUMIP                                    , "SUMIP                                  " , 100, 0, 100 ); 
  h_JetTOTALTRACKANGLEPT                       [i][j] = initSingleHistogramTH1F( hname_TOTALTRACKANGLEPT                        , "TOTALTRACKANGLEPT                      " , 100, 0, 10 ); 
  h_JetTOTALTRACKANGLE                         [i][j] = initSingleHistogramTH1F( hname_TOTALTRACKANGLE                          , "TOTALTRACKANGLE                        " , 100, 0, 10 ); 
  h_JetTOTALTRACKPT                            [i][j] = initSingleHistogramTH1F( hname_TOTALTRACKPT                             , "TOTALTRACKPT                           " , 100, 0, 100 ); 
  h_JetTRACKENERGY                             [i][j] = initSingleHistogramTH1F( hname_TRACKENERGY                              , "TRACKENERGY                            " , 100, 0, 100 ); 
  h_JetTRACKMASS                               [i][j] = initSingleHistogramTH1F( hname_TRACKMASS                                , "TRACKMASS                              " , 40, -2, 2 ); 

  }
 }

 return kTRUE;
}

//----------------------------fillJetHistograms
Bool_t analyzer_signal::fillJetHistograms(Double_t weight, int selbin)
{

 //printf("fillJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){

  if(JetMISSINGINNER                            ->size()>j){h_JetMISSINGINNER                            [selbin][j].Fill( JetMISSINGINNER                            ->at(j), weight ); } 
  if(JetMISSINGOUTER                            ->size()>j){h_JetMISSINGOUTER                            [selbin][j].Fill( JetMISSINGOUTER                            ->at(j), weight ); } 
  if(JetHSPH                                    ->size()>j){h_JetHSPH                                    [selbin][j].Fill( JetHSPH                                    ->at(j), weight ); } 
  if(JetNJets                                   ->size()>j){h_JetNJets                                   [selbin][j].Fill( JetNJets                                   ->at(j), weight ); } 
  if(JetNCLEANMATCHEDTRACKS                     ->size()>j){h_JetNCLEANMATCHEDTRACKS                     [selbin][j].Fill( JetNCLEANMATCHEDTRACKS                     ->at(j), weight ); } 
  if(JetNMATCHEDTRACKS                          ->size()>j){h_JetNMATCHEDTRACKS                          [selbin][j].Fill( JetNMATCHEDTRACKS                          ->at(j), weight ); } 
  if(JetNTRACKSIPLT0P05                         ->size()>j){h_JetNTRACKSIPLT0P05                         [selbin][j].Fill( JetNTRACKSIPLT0P05                         ->at(j), weight ); } 
  if(JetNTRACKSIPSIGGT10                        ->size()>j){h_JetNTRACKSIPSIGGT10                        [selbin][j].Fill( JetNTRACKSIPSIGGT10                        ->at(j), weight ); } 
  if(JetNTRACKSIPSIGLT5                         ->size()>j){h_JetNTRACKSIPSIGLT5                         [selbin][j].Fill( JetNTRACKSIPSIGLT5                         ->at(j), weight ); } 
  if(JetALPHAMAX2                               ->size()>j){h_JetALPHAMAX2                               [selbin][j].Fill( JetALPHAMAX2                               ->at(j), weight ); } 
  if(JetALPHAMAXPRIME2                          ->size()>j){h_JetALPHAMAXPRIME2                          [selbin][j].Fill( JetALPHAMAXPRIME2                          ->at(j), weight ); } 
  if(JetALPHAMAXPRIME                           ->size()>j){h_JetALPHAMAXPRIME                           [selbin][j].Fill( JetALPHAMAXPRIME                           ->at(j), weight ); } 
  if(JetALPHAMAX                                ->size()>j){h_JetALPHAMAX                                [selbin][j].Fill( JetALPHAMAX                                ->at(j), weight ); } 
  if(JetASSOCAPLANARITY                         ->size()>j){h_JetASSOCAPLANARITY                         [selbin][j].Fill( JetASSOCAPLANARITY                         ->at(j), weight ); } 
  if(JetASSOCIATEDTRACKPT                       ->size()>j){h_JetASSOCIATEDTRACKPT                       [selbin][j].Fill( JetASSOCIATEDTRACKPT                       ->at(j), weight ); } 
  if(JetASSOCSPHERICITY                         ->size()>j){h_JetASSOCSPHERICITY                         [selbin][j].Fill( JetASSOCSPHERICITY                         ->at(j), weight ); } 
  if(JetASSOCTHRUSTMAJOR                        ->size()>j){h_JetASSOCTHRUSTMAJOR                        [selbin][j].Fill( JetASSOCTHRUSTMAJOR                        ->at(j), weight ); } 
  if(JetASSOCTHRUSTMINOR                        ->size()>j){h_JetASSOCTHRUSTMINOR                        [selbin][j].Fill( JetASSOCTHRUSTMINOR                        ->at(j), weight ); } 
  if(JetAVFASSOCAPLANARITY                      ->size()>j){h_JetAVFASSOCAPLANARITY                      [selbin][j].Fill( JetAVFASSOCAPLANARITY                      ->at(j), weight ); } 
  if(JetAVFASSOCSPHERICITY                      ->size()>j){h_JetAVFASSOCSPHERICITY                      [selbin][j].Fill( JetAVFASSOCSPHERICITY                      ->at(j), weight ); } 
  if(JetAVFASSOCTHRUSTMAJOR                     ->size()>j){h_JetAVFASSOCTHRUSTMAJOR                     [selbin][j].Fill( JetAVFASSOCTHRUSTMAJOR                     ->at(j), weight ); } 
  if(JetAVFASSOCTHRUSTMINOR                     ->size()>j){h_JetAVFASSOCTHRUSTMINOR                     [selbin][j].Fill( JetAVFASSOCTHRUSTMINOR                     ->at(j), weight ); } 
  if(JetAVFBEAMSPOTDELTAPHI                     ->size()>j){h_JetAVFBEAMSPOTDELTAPHI                     [selbin][j].Fill( JetAVFBEAMSPOTDELTAPHI                     ->at(j), weight ); } 
  if(JetAVFBEAMSPOTRECOILPT                     ->size()>j){h_JetAVFBEAMSPOTRECOILPT                     [selbin][j].Fill( JetAVFBEAMSPOTRECOILPT                     ->at(j), weight ); } 
  if(JetAVFDISTTOPV                             ->size()>j){h_JetAVFDISTTOPV                             [selbin][j].Fill( JetAVFDISTTOPV                             ->at(j), weight ); } 
  if(JetAVFVERTEXCHI2NDOF                       ->size()>j){h_JetAVFVERTEXCHI2NDOF                       [selbin][j].Fill( JetAVFVERTEXCHI2NDOF                       ->at(j), weight ); } 
  if(JetAVFVERTEXDEGREESOFFREEDOM               ->size()>j){h_JetAVFVERTEXDEGREESOFFREEDOM               [selbin][j].Fill( JetAVFVERTEXDEGREESOFFREEDOM               ->at(j), weight ); } 
  if(JetAVFVERTEXDISTANCETOBEAM                 ->size()>j){h_JetAVFVERTEXDISTANCETOBEAM                 [selbin][j].Fill( JetAVFVERTEXDISTANCETOBEAM                 ->at(j), weight ); } 
  if(JetAVFVERTEXTOTALCHISQUARED                ->size()>j){h_JetAVFVERTEXTOTALCHISQUARED                [selbin][j].Fill( JetAVFVERTEXTOTALCHISQUARED                ->at(j), weight ); } 
  if(JetAVFVERTEXTRACKENERGY                    ->size()>j){h_JetAVFVERTEXTRACKENERGY                    [selbin][j].Fill( JetAVFVERTEXTRACKENERGY                    ->at(j), weight ); } 
  if(JetAVFVERTEXTRACKMASS                      ->size()>j){h_JetAVFVERTEXTRACKMASS                      [selbin][j].Fill( JetAVFVERTEXTRACKMASS                      ->at(j), weight ); } 
  if(JetAVFVERTEXTRANSVERSESIG                  ->size()>j){h_JetAVFVERTEXTRANSVERSESIG                  [selbin][j].Fill( JetAVFVERTEXTRANSVERSESIG                  ->at(j), weight ); } 
  if(JetAVGMISSINGINNER                         ->size()>j){h_JetAVGMISSINGINNER                         [selbin][j].Fill( JetAVGMISSINGINNER                         ->at(j), weight ); } 
  if(JetAVGMISSINGOUTER                         ->size()>j){h_JetAVGMISSINGOUTER                         [selbin][j].Fill( JetAVGMISSINGOUTER                         ->at(j), weight ); } 
  if(JetBASICCALOJETS1ANGLE_DANGLE              ->size()>j){h_JetBASICCALOJETS1ANGLE_DANGLE              [selbin][j].Fill( JetBASICCALOJETS1ANGLE_DANGLE              ->at(j), weight ); } 
  if(JetBASICCALOJETS1ANGLE_DPHI                ->size()>j){h_JetBASICCALOJETS1ANGLE_DPHI                [selbin][j].Fill( JetBASICCALOJETS1ANGLE_DPHI                ->at(j), weight ); } 
  if(JetBASICCALOJETS1DELTAR                    ->size()>j){h_JetBASICCALOJETS1DELTAR                    [selbin][j].Fill( JetBASICCALOJETS1DELTAR                    ->at(j), weight ); } 
  if(JetBASICCALOJETS1PT20DELTAR                ->size()>j){h_JetBASICCALOJETS1PT20DELTAR                [selbin][j].Fill( JetBASICCALOJETS1PT20DELTAR                ->at(j), weight ); } 
  if(JetBETA2                                   ->size()>j){h_JetBETA2                                   [selbin][j].Fill( JetBETA2                                   ->at(j), weight ); } 
  if(JetBETA                                    ->size()>j){h_JetBETA                                    [selbin][j].Fill( JetBETA                                    ->at(j), weight ); } 
  if(JetETA                                     ->size()>j){h_JetETA                                     [selbin][j].Fill( JetETA                                     ->at(j), weight ); } 
  if(JetHITSINFRONTOFVERTPERTRACK               ->size()>j){h_JetHITSINFRONTOFVERTPERTRACK               [selbin][j].Fill( JetHITSINFRONTOFVERTPERTRACK               ->at(j), weight ); } 
  if(JetIVFSCORE                                ->size()>j){h_JetIVFSCORE                                [selbin][j].Fill( JetIVFSCORE                                ->at(j), weight ); } 
  if(JetJETAREA                                 ->size()>j){h_JetJETAREA                                 [selbin][j].Fill( JetJETAREA                                 ->at(j), weight ); } 
  if(JetLEPANGLE_DANGLE                         ->size()>j){h_JetLEPANGLE_DANGLE                         [selbin][j].Fill( JetLEPANGLE_DANGLE                         ->at(j), weight ); } 
  if(JetLEPANGLE_DPHI                           ->size()>j){h_JetLEPANGLE_DPHI                           [selbin][j].Fill( JetLEPANGLE_DPHI                           ->at(j), weight ); } 
  if(JetLEPDELTAR                               ->size()>j){h_JetLEPDELTAR                               [selbin][j].Fill( JetLEPDELTAR                               ->at(j), weight ); } 
  if(JetLINEARRADIALMOMENT                      ->size()>j){h_JetLINEARRADIALMOMENT                      [selbin][j].Fill( JetLINEARRADIALMOMENT                      ->at(j), weight ); } 
  if(JetLRM                                     ->size()>j){h_JetLRM                                     [selbin][j].Fill( JetLRM                                     ->at(j), weight ); } 
  if(JetMASSDISPLACED                           ->size()>j){h_JetMASSDISPLACED                           [selbin][j].Fill( JetMASSDISPLACED                           ->at(j), weight ); } 
  if(JetMEDIANIPLOG10SIG                        ->size()>j){h_JetMEDIANIPLOG10SIG                        [selbin][j].Fill( JetMEDIANIPLOG10SIG                        ->at(j), weight ); } 
  if(JetMEDIANIPLOGSIG                          ->size()>j){h_JetMEDIANIPLOGSIG                          [selbin][j].Fill( JetMEDIANIPLOGSIG                          ->at(j), weight ); } 
  if(JetMEDIANLOG10TRACKANGLE                   ->size()>j){h_JetMEDIANLOG10TRACKANGLE                   [selbin][j].Fill( JetMEDIANLOG10TRACKANGLE                   ->at(j), weight ); } 
  if(JetMETANGLE_DANGLE                         ->size()>j){h_JetMETANGLE_DANGLE                         [selbin][j].Fill( JetMETANGLE_DANGLE                         ->at(j), weight ); } 
  if(JetMETANGLE_DPHI                           ->size()>j){h_JetMETANGLE_DPHI                           [selbin][j].Fill( JetMETANGLE_DPHI                           ->at(j), weight ); } 
  if(JetMETDELTAR                               ->size()>j){h_JetMETDELTAR                               [selbin][j].Fill( JetMETDELTAR                               ->at(j), weight ); } 
  if(JetMISSHITSAFTERVERTPERTRACK               ->size()>j){h_JetMISSHITSAFTERVERTPERTRACK               [selbin][j].Fill( JetMISSHITSAFTERVERTPERTRACK               ->at(j), weight ); } 
  if(JetM                                       ->size()>j){h_JetM                                       [selbin][j].Fill( JetM                                       ->at(j), weight ); } 
  if(JetPHI                                     ->size()>j){h_JetPHI                                     [selbin][j].Fill( JetPHI                                     ->at(j), weight ); } 
  if(JetPT                                      ->size()>j){h_JetPT                                      [selbin][j].Fill( JetPT                                      ->at(j), weight ); } 
  if(JetSELFDELTAR                              ->size()>j){h_JetSELFDELTAR                              [selbin][j].Fill( JetSELFDELTAR                              ->at(j), weight ); } 
  if(JetSSPH                                    ->size()>j){h_JetSSPH                                    [selbin][j].Fill( JetSSPH                                    ->at(j), weight ); } 
  if(JetSTUPAKPT                                ->size()>j){h_JetSTUPAKPT                                [selbin][j].Fill( JetSTUPAKPT                                ->at(j), weight ); } 
  if(JetSTUPAKR                                 ->size()>j){h_JetSTUPAKR                                 [selbin][j].Fill( JetSTUPAKR                                 ->at(j), weight ); } 
  if(JetSUMIPLOGSIG                             ->size()>j){h_JetSUMIPLOGSIG                             [selbin][j].Fill( JetSUMIPLOGSIG                             ->at(j), weight ); } 
  if(JetSUMIPSIG                                ->size()>j){h_JetSUMIPSIG                                [selbin][j].Fill( JetSUMIPSIG                                ->at(j), weight ); } 
  if(JetSUMIP                                   ->size()>j){h_JetSUMIP                                   [selbin][j].Fill( JetSUMIP                                   ->at(j), weight ); } 
  if(JetTOTALTRACKANGLEPT                       ->size()>j){h_JetTOTALTRACKANGLEPT                       [selbin][j].Fill( JetTOTALTRACKANGLEPT                       ->at(j), weight ); } 
  if(JetTOTALTRACKANGLE                         ->size()>j){h_JetTOTALTRACKANGLE                         [selbin][j].Fill( JetTOTALTRACKANGLE                         ->at(j), weight ); } 
  if(JetTOTALTRACKPT                            ->size()>j){h_JetTOTALTRACKPT                            [selbin][j].Fill( JetTOTALTRACKPT                            ->at(j), weight ); } 
  if(JetTRACKENERGY                             ->size()>j){h_JetTRACKENERGY                             [selbin][j].Fill( JetTRACKENERGY                             ->at(j), weight ); } 
  if(JetTRACKMASS                               ->size()>j){h_JetTRACKMASS                               [selbin][j].Fill( JetTRACKMASS                               ->at(j), weight ); } 
 }

 return kTRUE;
}

//----------------------------writeJetHistograms
Bool_t analyzer_signal::writeJetHistograms(int selbin)
{
 //printf("writeJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){

  h_JetMISSINGINNER                            [selbin][j].Write(); 
  h_JetMISSINGOUTER                            [selbin][j].Write(); 
  h_JetHSPH                                    [selbin][j].Write(); 
  h_JetNJets                                   [selbin][j].Write(); 
  h_JetNCLEANMATCHEDTRACKS                     [selbin][j].Write(); 
  h_JetNMATCHEDTRACKS                          [selbin][j].Write(); 
  h_JetNTRACKSIPLT0P05                         [selbin][j].Write(); 
  h_JetNTRACKSIPSIGGT10                        [selbin][j].Write(); 
  h_JetNTRACKSIPSIGLT5                         [selbin][j].Write(); 
  h_JetALPHAMAX2                               [selbin][j].Write(); 
  h_JetALPHAMAXPRIME2                          [selbin][j].Write(); 
  h_JetALPHAMAXPRIME                           [selbin][j].Write(); 
  h_JetALPHAMAX                                [selbin][j].Write(); 
  h_JetASSOCAPLANARITY                         [selbin][j].Write(); 
  h_JetASSOCIATEDTRACKPT                       [selbin][j].Write(); 
  h_JetASSOCSPHERICITY                         [selbin][j].Write(); 
  h_JetASSOCTHRUSTMAJOR                        [selbin][j].Write(); 
  h_JetASSOCTHRUSTMINOR                        [selbin][j].Write(); 
  h_JetAVFASSOCAPLANARITY                      [selbin][j].Write(); 
  h_JetAVFASSOCSPHERICITY                      [selbin][j].Write(); 
  h_JetAVFASSOCTHRUSTMAJOR                     [selbin][j].Write(); 
  h_JetAVFASSOCTHRUSTMINOR                     [selbin][j].Write(); 
  h_JetAVFBEAMSPOTDELTAPHI                     [selbin][j].Write(); 
  h_JetAVFBEAMSPOTRECOILPT                     [selbin][j].Write(); 
  h_JetAVFDISTTOPV                             [selbin][j].Write(); 
  h_JetAVFVERTEXCHI2NDOF                       [selbin][j].Write(); 
  h_JetAVFVERTEXDEGREESOFFREEDOM               [selbin][j].Write(); 
  h_JetAVFVERTEXDISTANCETOBEAM                 [selbin][j].Write(); 
  h_JetAVFVERTEXTOTALCHISQUARED                [selbin][j].Write(); 
  h_JetAVFVERTEXTRACKENERGY                    [selbin][j].Write(); 
  h_JetAVFVERTEXTRACKMASS                      [selbin][j].Write(); 
  h_JetAVFVERTEXTRANSVERSESIG                  [selbin][j].Write(); 
  h_JetAVGMISSINGINNER                         [selbin][j].Write(); 
  h_JetAVGMISSINGOUTER                         [selbin][j].Write(); 
  h_JetBASICCALOJETS1ANGLE_DANGLE              [selbin][j].Write(); 
  h_JetBASICCALOJETS1ANGLE_DPHI                [selbin][j].Write(); 
  h_JetBASICCALOJETS1DELTAR                    [selbin][j].Write(); 
  h_JetBASICCALOJETS1PT20DELTAR                [selbin][j].Write(); 
  h_JetBETA2                                   [selbin][j].Write(); 
  h_JetBETA                                    [selbin][j].Write(); 
  h_JetETA                                     [selbin][j].Write(); 
  h_JetHITSINFRONTOFVERTPERTRACK               [selbin][j].Write(); 
  h_JetIVFSCORE                                [selbin][j].Write(); 
  h_JetJETAREA                                 [selbin][j].Write(); 
  h_JetLEPANGLE_DANGLE                         [selbin][j].Write(); 
  h_JetLEPANGLE_DPHI                           [selbin][j].Write(); 
  h_JetLEPDELTAR                               [selbin][j].Write(); 
  h_JetLINEARRADIALMOMENT                      [selbin][j].Write(); 
  h_JetLRM                                     [selbin][j].Write(); 
  h_JetMASSDISPLACED                           [selbin][j].Write(); 
  h_JetMEDIANIPLOG10SIG                        [selbin][j].Write(); 
  h_JetMEDIANIPLOGSIG                          [selbin][j].Write(); 
  h_JetMEDIANLOG10TRACKANGLE                   [selbin][j].Write(); 
  h_JetMETANGLE_DANGLE                         [selbin][j].Write(); 
  h_JetMETANGLE_DPHI                           [selbin][j].Write(); 
  h_JetMETDELTAR                               [selbin][j].Write(); 
  h_JetMISSHITSAFTERVERTPERTRACK               [selbin][j].Write(); 
  h_JetM                                       [selbin][j].Write(); 
  h_JetPHI                                     [selbin][j].Write(); 
  h_JetPT                                      [selbin][j].Write(); 
  h_JetSELFDELTAR                              [selbin][j].Write(); 
  h_JetSSPH                                    [selbin][j].Write(); 
  h_JetSTUPAKPT                                [selbin][j].Write(); 
  h_JetSTUPAKR                                 [selbin][j].Write(); 
  h_JetSUMIPLOGSIG                             [selbin][j].Write(); 
  h_JetSUMIPSIG                                [selbin][j].Write(); 
  h_JetSUMIP                                   [selbin][j].Write(); 
  h_JetTOTALTRACKANGLEPT                       [selbin][j].Write(); 
  h_JetTOTALTRACKANGLE                         [selbin][j].Write(); 
  h_JetTOTALTRACKPT                            [selbin][j].Write(); 
  h_JetTRACKENERGY                             [selbin][j].Write(); 
  h_JetTRACKMASS                               [selbin][j].Write(); 
 }

 return kTRUE;
}


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

 for(unsigned int i=0; i<selbinnames.size(); ++i){

  // initialize names
  TString hname_NELECTRONS           = "h_"+selbinnames[i]+"_NELECTRONS";             
  TString hname_NELECTRONS30         = "h_"+selbinnames[i]+"_NELECTRONS30";           
  TString hname_NELECTRONSFROMBOSON  = "h_"+selbinnames[i]+"_NELECTRONSFROMBOSON";    
  TString hname_NGOODELECTRONS       = "h_"+selbinnames[i]+"_NGOODELECTRONS";         
  TString hname_NGOODLEPTONS         = "h_"+selbinnames[i]+"_NGOODLEPTONS";           
  TString hname_NGOODMUONS           = "h_"+selbinnames[i]+"_NGOODMUONS";             
  TString hname_NGOODVERTICES        = "h_"+selbinnames[i]+"_NGOODVERTICES";          
  TString hname_NKSHORTS             = "h_"+selbinnames[i]+"_NKSHORTS";               
  TString hname_NMUONS               = "h_"+selbinnames[i]+"_NMUONS";                 
  TString hname_NMUONS30             = "h_"+selbinnames[i]+"_NMUONS30";               
  TString hname_NMUONSFROMBOSON      = "h_"+selbinnames[i]+"_NMUONSFROMBOSON";        
  TString hname_NOSSF                = "h_"+selbinnames[i]+"_NOSSF";                  
  TString hname_N_bJetsCSVL          = "h_"+selbinnames[i]+"_N_bJetsCSVL";            
  TString hname_N_bJetsCSVM          = "h_"+selbinnames[i]+"_N_bJetsCSVM";            
  TString hname_N_bosons             = "h_"+selbinnames[i]+"_N_bosons";               
  TString hname_PU_NumInteractions   = "h_"+selbinnames[i]+"_PU_NumInteractions";     
  TString hname_fakeIncarnation      = "h_"+selbinnames[i]+"_fakeIncarnation";        
  TString hname_ELECTRON_PT          = "h_"+selbinnames[i]+"_ELECTRON_PT";            
  TString hname_FLATWEIGHT           = "h_"+selbinnames[i]+"_FLATWEIGHT";             
  TString hname_HLTHT                = "h_"+selbinnames[i]+"_HLTHT";                  
  TString hname_HSPH                 = "h_"+selbinnames[i]+"_HSPH";                   
  TString hname_HT                   = "h_"+selbinnames[i]+"_HT";                     
  TString hname_HTHLTID              = "h_"+selbinnames[i]+"_HTHLTID";                
  TString hname_HT_All               = "h_"+selbinnames[i]+"_HT_All";                 
  TString hname_LEPTON_DANGLE        = "h_"+selbinnames[i]+"_LEPTON_DANGLE";          
  TString hname_LEPTON_DPHI          = "h_"+selbinnames[i]+"_LEPTON_DPHI";            
  TString hname_LRM                  = "h_"+selbinnames[i]+"_LRM";                    
  TString hname_MET                  = "h_"+selbinnames[i]+"_MET";                    
  TString hname_MOSSF                = "h_"+selbinnames[i]+"_MOSSF";                  
  TString hname_MUON_PT              = "h_"+selbinnames[i]+"_MUON_PT";                
  TString hname_OSSFCLOSEMLL         = "h_"+selbinnames[i]+"_OSSFCLOSEMLL";           
  TString hname_OSSFMAXMLL           = "h_"+selbinnames[i]+"_OSSFMAXMLL";             
  TString hname_OSSFMINMLL           = "h_"+selbinnames[i]+"_OSSFMINMLL";             
  TString hname_PTOSSF               = "h_"+selbinnames[i]+"_PTOSSF";                 
  TString hname_SCALAR_PT            = "h_"+selbinnames[i]+"_SCALAR_PT";              
  TString hname_SIGNALQUARKS_GENDXY  = "h_"+selbinnames[i]+"_SIGNALQUARKS_GENDXY";    
  TString hname_SIGNALQUARKS_P       = "h_"+selbinnames[i]+"_SIGNALQUARKS_P";         
  TString hname_SIGNALQUARKS_PT      = "h_"+selbinnames[i]+"_SIGNALQUARKS_PT";        
  TString hname_SSPH                 = "h_"+selbinnames[i]+"_SSPH";                   
  TString hname_TrueNumInteractions  = "h_"+selbinnames[i]+"_TrueNumInteractions";    
  TString hname_rhoAll               = "h_"+selbinnames[i]+"_rhoAll";                 
  TString hname_rhoNeutral           = "h_"+selbinnames[i]+"_rhoNeutral";             
  TString hname_stupakR              = "h_"+selbinnames[i]+"_stupakR";                
  TString hname_stupakR2             = "h_"+selbinnames[i]+"_stupakR2";               

  // initalize histograms
  h_NELECTRONS         [i] = initSingleHistogramTH1F( hname_NELECTRONS         , "NELECTRONS         " , 10, 0, 10); 
  h_NELECTRONS30       [i] = initSingleHistogramTH1F( hname_NELECTRONS30       , "NELECTRONS30       " , 10, 0, 10); 
  h_NELECTRONSFROMBOSON[i] = initSingleHistogramTH1F( hname_NELECTRONSFROMBOSON, "NELECTRONSFROMBOSON" , 10, 0, 10); 
  h_NGOODELECTRONS     [i] = initSingleHistogramTH1F( hname_NGOODELECTRONS     , "NGOODELECTRONS     " , 10, 0, 10); 
  h_NGOODLEPTONS       [i] = initSingleHistogramTH1F( hname_NGOODLEPTONS       , "NGOODLEPTONS       " , 10, 0, 10); 
  h_NGOODMUONS         [i] = initSingleHistogramTH1F( hname_NGOODMUONS         , "NGOODMUONS         " , 10, 0, 10); 
  h_NGOODVERTICES      [i] = initSingleHistogramTH1F( hname_NGOODVERTICES      , "NGOODVERTICES      " , 50, 0, 50); 
  h_NKSHORTS           [i] = initSingleHistogramTH1F( hname_NKSHORTS           , "NKSHORTS           " , 10, 0, 10); 
  h_NMUONS             [i] = initSingleHistogramTH1F( hname_NMUONS             , "NMUONS             " , 40, 0, 40); 
  h_NMUONS30           [i] = initSingleHistogramTH1F( hname_NMUONS30           , "NMUONS30           " , 10, 0, 10); 
  h_NMUONSFROMBOSON    [i] = initSingleHistogramTH1F( hname_NMUONSFROMBOSON    , "NMUONSFROMBOSON    " , 10, 0, 10); 
  h_NOSSF              [i] = initSingleHistogramTH1F( hname_NOSSF              , "NOSSF              " , 50, 0, 5); 
  h_N_bJetsCSVL        [i] = initSingleHistogramTH1F( hname_N_bJetsCSVL        , "N_bJetsCSVL        " , 50, 0, 5); 
  h_N_bJetsCSVM        [i] = initSingleHistogramTH1F( hname_N_bJetsCSVM        , "N_bJetsCSVM        " , 50, 0, 5); 
  h_N_bosons           [i] = initSingleHistogramTH1F( hname_N_bosons           , "N_bosons           " , 20, 0, 20); 

  h_PU_NumInteractions [i] = initSingleHistogramTH1F( hname_PU_NumInteractions , "PU_NumInteractions " , 100, 0, 60); 
  h_fakeIncarnation    [i] = initSingleHistogramTH1F( hname_fakeIncarnation    , "fakeIncarnation    " , 100, 0, 100); 
  h_ELECTRON_PT        [i] = initSingleHistogramTH1F( hname_ELECTRON_PT        , "ELECTRON_PT        " , 100, 0, 100); 
  h_FLATWEIGHT         [i] = initSingleHistogramTH1F( hname_FLATWEIGHT         , "FLATWEIGHT         " , 100, 0, 10); 
  h_HLTHT              [i] = initSingleHistogramTH1F( hname_HLTHT              , "HLTHT              " , 400, 0, 400); 
  h_HSPH               [i] = initSingleHistogramTH1F( hname_HSPH               , "HSPH               " , 10, 0, 1); 
  h_HT                 [i] = initSingleHistogramTH1F( hname_HT                 , "HT                 " , 500, 0, 500); 
  h_HTHLTID            [i] = initSingleHistogramTH1F( hname_HTHLTID            , "HTHLTID            " , 500, 0, 500); 
  h_HT_All             [i] = initSingleHistogramTH1F( hname_HT_All             , "HT_All             " , 1000, 0, 1000); 
  h_LEPTON_DANGLE      [i] = initSingleHistogramTH1F( hname_LEPTON_DANGLE      , "LEPTON_DANGLE      " , 40, 0, 4); 
  h_LEPTON_DPHI        [i] = initSingleHistogramTH1F( hname_LEPTON_DPHI        , "LEPTON_DPHI        " , 80, -4, 4); 
  h_LRM                [i] = initSingleHistogramTH1F( hname_LRM                , "LRM                " , 100, 0, 100); 
  h_MET                [i] = initSingleHistogramTH1F( hname_MET                , "MET                " , 200, 0, 200); 
  h_MOSSF              [i] = initSingleHistogramTH1F( hname_MOSSF              , "MOSSF              " , 200, 0, 200); 
  h_MUON_PT            [i] = initSingleHistogramTH1F( hname_MUON_PT            , "MUON_PT            " , 200, 0, 100); 
  h_OSSFCLOSEMLL       [i] = initSingleHistogramTH1F( hname_OSSFCLOSEMLL       , "OSSFCLOSEMLL       " , 200, 0, 100); 
  h_OSSFMAXMLL         [i] = initSingleHistogramTH1F( hname_OSSFMAXMLL         , "OSSFMAXMLL         " , 200, 0, 100); 
  h_OSSFMINMLL         [i] = initSingleHistogramTH1F( hname_OSSFMINMLL         , "OSSFMINMLL         " , 200, 0, 100); 
  h_PTOSSF             [i] = initSingleHistogramTH1F( hname_PTOSSF             , "PTOSSF             " , 200, 0, 100); 
  h_SCALAR_PT          [i] = initSingleHistogramTH1F( hname_SCALAR_PT          , "SCALAR_PT          " , 200, 0, 100); 
  h_SIGNALQUARKS_GENDXY[i] = initSingleHistogramTH1F( hname_SIGNALQUARKS_GENDXY, "SIGNALQUARKS_GENDXY" , 200, 0, 100); 
  h_SIGNALQUARKS_P     [i] = initSingleHistogramTH1F( hname_SIGNALQUARKS_P     , "SIGNALQUARKS_P     " , 200, 0, 200); 
  h_SIGNALQUARKS_PT    [i] = initSingleHistogramTH1F( hname_SIGNALQUARKS_PT    , "SIGNALQUARKS_PT    " , 200, 0, 200); 
  h_SSPH               [i] = initSingleHistogramTH1F( hname_SSPH               , "SSPH               " , 10, 0, 1); 
  h_TrueNumInteractions[i] = initSingleHistogramTH1F( hname_TrueNumInteractions, "TrueNumInteractions" , 100, 0, 50); 
  h_rhoAll             [i] = initSingleHistogramTH1F( hname_rhoAll             , "rhoAll             " , 100, 0, 50); 
  h_rhoNeutral         [i] = initSingleHistogramTH1F( hname_rhoNeutral         , "rhoNeutral         " , 100, 0, 10); 
  h_stupakR            [i] = initSingleHistogramTH1F( hname_stupakR            , "stupakR            " , 10, 0, 1); 
  h_stupakR2           [i] = initSingleHistogramTH1F( hname_stupakR2           , "stupakR2           " , 10, 0, 1); 

 }

 return kTRUE;
}

//----------------------------fillSigHistograms
Bool_t analyzer_signal::fillSigHistograms(Double_t weight, int selbin)
{

 //printf("fillSigHistograms\n");
 if(NELECTRONS         ->size()>0){h_NELECTRONS         [selbin] .Fill( NELECTRONS         ->at(0), weight); } 
 if(NELECTRONS30       ->size()>0){h_NELECTRONS30       [selbin] .Fill( NELECTRONS30       ->at(0), weight); } 

 if(NELECTRONSFROMBOSON->size()>0){h_NELECTRONSFROMBOSON[selbin] .Fill( NELECTRONSFROMBOSON->at(0), weight); } 
 if(NGOODELECTRONS     ->size()>0){h_NGOODELECTRONS     [selbin] .Fill( NGOODELECTRONS     ->at(0), weight); } 
 if(NGOODLEPTONS       ->size()>0){h_NGOODLEPTONS       [selbin] .Fill( NGOODLEPTONS       ->at(0), weight); } 
 if(NGOODMUONS         ->size()>0){h_NGOODMUONS         [selbin] .Fill( NGOODMUONS         ->at(0), weight); } 
 if(NGOODVERTICES      ->size()>0){h_NGOODVERTICES      [selbin] .Fill( NGOODVERTICES      ->at(0), weight); } 
 if(NKSHORTS           ->size()>0){h_NKSHORTS           [selbin] .Fill( NKSHORTS           ->at(0), weight); } 
 if(NMUONS             ->size()>0){h_NMUONS             [selbin] .Fill( NMUONS             ->at(0), weight); } 
 if(NMUONS30           ->size()>0){h_NMUONS30           [selbin] .Fill( NMUONS30           ->at(0), weight); } 
 if(NMUONSFROMBOSON    ->size()>0){h_NMUONSFROMBOSON    [selbin] .Fill( NMUONSFROMBOSON    ->at(0), weight); } 
 if(NOSSF              ->size()>0){h_NOSSF              [selbin] .Fill( NOSSF              ->at(0), weight); } 
 if(N_bJetsCSVL        ->size()>0){h_N_bJetsCSVL        [selbin] .Fill( N_bJetsCSVL        ->at(0), weight); } 
 if(N_bJetsCSVM        ->size()>0){h_N_bJetsCSVM        [selbin] .Fill( N_bJetsCSVM        ->at(0), weight); } 
 if(N_bosons           ->size()>0){h_N_bosons           [selbin] .Fill( N_bosons           ->at(0), weight); } 
 if(PU_NumInteractions ->size()>0){h_PU_NumInteractions [selbin] .Fill( PU_NumInteractions ->at(0), weight); } 
 if(fakeIncarnation    ->size()>0){h_fakeIncarnation    [selbin] .Fill( fakeIncarnation    ->at(0), weight); } 
 if(ELECTRON_PT        ->size()>0){h_ELECTRON_PT        [selbin] .Fill( ELECTRON_PT        ->at(0), weight); }
 if(FLATWEIGHT         ->size()>0){h_FLATWEIGHT         [selbin] .Fill( FLATWEIGHT         ->at(0), weight); } 
 if(HLTHT              ->size()>0){h_HLTHT              [selbin] .Fill( HLTHT              ->at(0), weight); } 
 if(HSPH               ->size()>0){h_HSPH               [selbin] .Fill( HSPH               ->at(0), weight); } 
 if(HT                 ->size()>0){h_HT                 [selbin] .Fill( HT                 ->at(0), weight); } 
 if(HTHLTID            ->size()>0){h_HTHLTID            [selbin] .Fill( HTHLTID            ->at(0), weight); } 
 if(HT_All             ->size()>0){h_HT_All             [selbin] .Fill( HT_All             ->at(0), weight); } 
 if(LEPTON_DANGLE      ->size()>0){h_LEPTON_DANGLE      [selbin] .Fill( LEPTON_DANGLE      ->at(0), weight); } 
 if(LEPTON_DPHI        ->size()>0){h_LEPTON_DPHI        [selbin] .Fill( LEPTON_DPHI        ->at(0), weight); } 
 if(LRM                ->size()>0){h_LRM                [selbin] .Fill( LRM                ->at(0), weight); } 
 if(MET                ->size()>0){h_MET                [selbin] .Fill( MET                ->at(0), weight); } 
 if(MOSSF              ->size()>0){h_MOSSF              [selbin] .Fill( MOSSF              ->at(0), weight); } 
 if(MUON_PT            ->size()>0){h_MUON_PT            [selbin] .Fill( MUON_PT            ->at(0), weight); } 
 if(OSSFCLOSEMLL       ->size()>0){h_OSSFCLOSEMLL       [selbin] .Fill( OSSFCLOSEMLL       ->at(0), weight); } 
 if(OSSFMAXMLL         ->size()>0){h_OSSFMAXMLL         [selbin] .Fill( OSSFMAXMLL         ->at(0), weight); } 
 if(OSSFMINMLL         ->size()>0){h_OSSFMINMLL         [selbin] .Fill( OSSFMINMLL         ->at(0), weight); } 
 if(PTOSSF             ->size()>0){h_PTOSSF             [selbin] .Fill( PTOSSF             ->at(0), weight); } 
 if(SCALAR_PT          ->size()>0){h_SCALAR_PT          [selbin] .Fill( SCALAR_PT          ->at(0), weight); } 
 if(SIGNALQUARKS_GENDXY->size()>0){h_SIGNALQUARKS_GENDXY[selbin] .Fill( SIGNALQUARKS_GENDXY->at(0), weight); } 
 if(SIGNALQUARKS_P     ->size()>0){h_SIGNALQUARKS_P     [selbin] .Fill( SIGNALQUARKS_P     ->at(0), weight); } 
 if(SIGNALQUARKS_PT    ->size()>0){h_SIGNALQUARKS_PT    [selbin] .Fill( SIGNALQUARKS_PT    ->at(0), weight); } 
 if(SSPH               ->size()>0){h_SSPH               [selbin] .Fill( SSPH               ->at(0), weight); } 
 if(TrueNumInteractions->size()>0){h_TrueNumInteractions[selbin] .Fill( TrueNumInteractions->at(0), weight); } 
 if(rhoAll             ->size()>0){h_rhoAll             [selbin] .Fill( rhoAll             ->at(0), weight); } 
 if(rhoNeutral         ->size()>0){h_rhoNeutral         [selbin] .Fill( rhoNeutral         ->at(0), weight); } 
 if(stupakR            ->size()>0){h_stupakR            [selbin] .Fill( stupakR            ->at(0), weight); } 
 if(stupakR2           ->size()>0){h_stupakR2           [selbin] .Fill( stupakR2           ->at(0), weight); } 

 return kTRUE;
}

//----------------------------writeSigHistograms
//Bool_t analyzer_signal::writeSigHistograms(int ptbin, int sysbin)
Bool_t analyzer_signal::writeSigHistograms(int selbin)
{
 //printf("writeSigHistograms\n");
 h_NELECTRONS         [selbin] .Write(); 
 h_NELECTRONS30       [selbin] .Write(); 
 h_NELECTRONSFROMBOSON[selbin] .Write(); 
 h_NGOODELECTRONS     [selbin] .Write(); 
 h_NGOODLEPTONS       [selbin] .Write(); 
 h_NGOODMUONS         [selbin] .Write(); 
 h_NGOODVERTICES      [selbin] .Write(); 
 h_NKSHORTS           [selbin] .Write(); 
 h_NMUONS             [selbin] .Write(); 
 h_NMUONS30           [selbin] .Write(); 
 h_NMUONSFROMBOSON    [selbin] .Write(); 
 h_NOSSF              [selbin] .Write(); 
 h_N_bJetsCSVL        [selbin] .Write(); 
 h_N_bJetsCSVM        [selbin] .Write(); 
 h_N_bosons           [selbin] .Write(); 
 h_PU_NumInteractions [selbin] .Write(); 
 h_fakeIncarnation    [selbin] .Write(); 
 h_ELECTRON_PT        [selbin] .Write(); 
 h_FLATWEIGHT         [selbin] .Write(); 
 h_HLTHT              [selbin] .Write(); 
 h_HSPH               [selbin] .Write(); 
 h_HT                 [selbin] .Write(); 
 h_HTHLTID            [selbin] .Write(); 
 h_HT_All             [selbin] .Write(); 
 h_LEPTON_DANGLE      [selbin] .Write(); 
 h_LEPTON_DPHI        [selbin] .Write(); 
 h_LRM                [selbin] .Write(); 
 h_MET                [selbin] .Write(); 
 h_MOSSF              [selbin] .Write(); 
 h_MUON_PT            [selbin] .Write(); 
 h_OSSFCLOSEMLL       [selbin] .Write(); 
 h_OSSFMAXMLL         [selbin] .Write(); 
 h_OSSFMINMLL         [selbin] .Write(); 
 h_PTOSSF             [selbin] .Write(); 
 h_SCALAR_PT          [selbin] .Write(); 
 h_SIGNALQUARKS_GENDXY[selbin] .Write(); 
 h_SIGNALQUARKS_P     [selbin] .Write(); 
 h_SIGNALQUARKS_PT    [selbin] .Write(); 
 h_SSPH               [selbin] .Write(); 
 h_TrueNumInteractions[selbin] .Write(); 
 h_rhoAll             [selbin] .Write(); 
 h_rhoNeutral         [selbin] .Write(); 
 h_stupakR            [selbin] .Write(); 
 h_stupakR2           [selbin] .Write(); 

 return kTRUE;
}

// cuts -------------------------------------------------------------
Bool_t analyzer_signal::askPassSig()
{
 Bool_t doespass = kTRUE;
 npassSig++;
 return doespass;
}

Bool_t analyzer_signal::askPassZH()
{
 Bool_t doespass = kFALSE;

 if ( safeNGOODVERTICES > 0
     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
     && ( 70 < safeMOSSF && safeMOSSF < 110 ) 
     && safePTOSSF > 50
     && safeJetNJets > 0
    )
 { doespass = kTRUE; npassZH++;}
 return doespass;
}

Bool_t analyzer_signal::askPassDY()
{
 Bool_t doespass = kFALSE;

 if ( safeNGOODVERTICES > 0
     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
     && ( 70 < safeMOSSF && safeMOSSF < 110 ) 
     && safePTOSSF < 50
     && safeJetNJets > 0
    )
 { doespass = kTRUE; npassDY++; }
 return doespass;
}

Bool_t analyzer_signal::askPassOffZ()
{
 Bool_t doespass = kFALSE;

 if ( safeNGOODVERTICES > 0
     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
     && !( 70 < safeMOSSF && safeMOSSF < 110 ) 
     && safeNOSSF == 1
     && safeJetNJets > 0
    )
 { doespass = kTRUE; npassOffZ++; }
 return doespass;
}

Bool_t analyzer_signal::askPassNoPair()
{
 Bool_t doespass = kFALSE;

 if ( safeNGOODVERTICES > 0
     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
     && !( 70 < safeMOSSF && safeMOSSF < 110 ) 
     && safeNOSSF == 0
     && safeJetNJets > 0
    )
 { doespass = kTRUE; npassNoPair++; }
 return doespass;
}

analyzer_signal::analyzer_signal()
{
}

analyzer_signal::~analyzer_signal()
{
}
