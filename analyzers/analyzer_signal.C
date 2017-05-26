#define analyzer_signal_cxx
#include "analyzer_signal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void analyzer_signal::Loop(TString outfilename, 
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

 n_tot=0;

 n_passSig=0;
 n_passZH=0;
 n_passDY=0;
 n_passOffZ=0;
 n_passNoPair=0;

 n_ele_passSig=0;
 n_ele_passZH=0;
 n_ele_passDY=0;
 n_ele_passOffZ=0;
 n_ele_passNoPair=0;

 n_mu_passSig=0;
 n_mu_passZH=0;
 n_mu_passDY=0;
 n_mu_passOffZ=0;
 n_mu_passNoPair=0;

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ printf(" entry %lli\n",jentry); }

  // make event weight in analyzerBase.C
  // colisions happen @LHC at a given rate, use 
  // event_weight to make the simulation match what is seen in data
  // =lum/cross-section *nrEvents
  event_weight = makeEventWeight(crossSec,lumi,nrEvents);
  n_tot++;

  // get lists of "good" electrons, photons, jets
  photon_list = photon_passLooseID( 15, 2.5, ""); // pt, eta, sysbinname
  electron_list = electron_passLooseID( 30, 3, "");
  muon_list = muon_passTightID( 28, 2.4, ""); 
  //muon_list = muon_passLooseID( 15, 3, ""); 
  jet_list = jet_passID( 20, 2.4, "");

  // set our met
  themet = pfMET;
  themephi = pfMETPhi;
  // pfMET_T1JERUp;   //!
  // pfMET_T1JERDo;   //!
  // pfMET_T1JESUp;   //!
  // pfMET_T1JESDo;   //!
  // pfMET_T1MESUp;   //!
  // pfMET_T1MESDo;   //!
  // pfMET_T1EESUp;   //!
  // pfMET_T1EESDo;   //!
  // pfMET_T1PESUp;   //!
  // pfMET_T1PESDo;   //!
  // pfMET_T1TESUp;   //!
  // pfMET_T1TESDo;   //!
  // pfMET_T1UESUp;   //!
  // pfMET_T1UESDo;   //!

  // calculate ht
  htall  = 0.;
  htjets = 0.;
  //for(int i=0; i<photon_list.size(); ++i){
  // int phoindex = photon_list[i];
  // htall += phoEt->at(phoindex);
  //}

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   htall += elePt->at(eleindex);
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   htall += muPt->at(muindex);
  }

  for(int i=0; i<jet_list.size(); ++i){
   int jetindex = jet_list[i];
   htall  += jetPt->at(jetindex);
   htjets += jetPt->at(jetindex);
  } 

  // make dilepton pair
  fourVec_l1.SetPtEtaPhiE(0,0,0,0);
  fourVec_l2.SetPtEtaPhiE(0,0,0,0);

  // get electrons and muons and put into 4vectors
  bool passMM = false;
  makeDilep(&fourVec_l1, &fourVec_l2, &fourVec_ee, &fourVec_mm, &passMM);
  // make dilepton object
  fourVec_ll = fourVec_l1 + fourVec_l2;
  dilep_mass = fourVec_ll.M();
  dilep_pt   = fourVec_ll.Pt();

  // set booleans if pass selections 
  passOSSF = (dilep_mass>20.);
  passZWindow = (dilep_mass>70. && dilep_mass<110.);
  passPTOSSFg50 = (dilep_pt>50.);

  passGoodVtx = nVtx>0;
  passOneJet = jet_list.size()>0; 

  passSingleEle = askPassSingleEle();
  passSingleMu  = askPassSingleMu();

  //debug_printobjects(); // helpful printout (turn off when submitting!!!)

  // set booleans if pass various selections
  doesPassSig    = askPassSig   ();
  doesPassZH     = askPassZH    ();
  doesPassDY     = askPassDY    ();
  doesPassOffZ   = askPassOffZ  ();
  doesPassNoPair = askPassNoPair();

  // fill histogram

  if( passSingleEle ){
                        fillSigHistograms(event_weight,0,0); fillJetHistograms(event_weight,0,0);  //fill2DHistograms(event_weight,0);  
   if( doesPassSig   ){ fillSigHistograms(event_weight,1,0); fillJetHistograms(event_weight,1,0); }//fill2DHistograms(event_weight,1); }
   if( doesPassZH    ){ fillSigHistograms(event_weight,2,0); fillJetHistograms(event_weight,2,0); }//fill2DHistograms(event_weight,2); }
   if( doesPassDY    ){ fillSigHistograms(event_weight,3,0); fillJetHistograms(event_weight,3,0); }//fill2DHistograms(event_weight,3); }
   if( doesPassOffZ  ){ fillSigHistograms(event_weight,4,0); fillJetHistograms(event_weight,4,0); }//fill2DHistograms(event_weight,4); }
   if( doesPassNoPair){ fillSigHistograms(event_weight,5,0); fillJetHistograms(event_weight,5,0); }//fill2DHistograms(event_weight,5); }
  }

  if( passSingleMu ){
                        fillSigHistograms(event_weight,0,1); fillJetHistograms(event_weight,0,1);  //fill2DHistograms(event_weight,0);  
   if( doesPassSig   ){ fillSigHistograms(event_weight,1,1); fillJetHistograms(event_weight,1,1); }//fill2DHistograms(event_weight,1); }
   if( doesPassZH    ){ fillSigHistograms(event_weight,2,1); fillJetHistograms(event_weight,2,1); }//fill2DHistograms(event_weight,2); }
   if( doesPassDY    ){ fillSigHistograms(event_weight,3,1); fillJetHistograms(event_weight,3,1); }//fill2DHistograms(event_weight,3); }
   if( doesPassOffZ  ){ fillSigHistograms(event_weight,4,1); fillJetHistograms(event_weight,4,1); }//fill2DHistograms(event_weight,4); }
   if( doesPassNoPair){ fillSigHistograms(event_weight,5,1); fillJetHistograms(event_weight,5,1); }//fill2DHistograms(event_weight,5); }
  }
   
  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);

 } // end loop over entries

 printf("\n\nSummary\n");
 printf(" ntot        %i \n",n_tot        ); 
 printf(" npassSig    %i %i %i \n",n_passSig    ,n_ele_passSig    ,n_mu_passSig    ); 
 printf(" npassZH     %i %i %i \n",n_passZH     ,n_ele_passZH     ,n_mu_passZH     ); 
 printf(" npassDY     %i %i %i \n",n_passDY     ,n_ele_passDY     ,n_mu_passDY     ); 
 printf(" npassOffZ   %i %i %i \n",n_passOffZ   ,n_ele_passOffZ   ,n_mu_passOffZ   ); 
 printf(" npassNoPair %i %i %i \n",n_passNoPair ,n_ele_passNoPair ,n_mu_passNoPair ); 

 // make outfile and save histograms
 TFile *outfile = new TFile(outfilename+".root","RECREATE");
 outfile->cd();
 for(int i=0; i<selbinnames.size(); ++i){  // i = selbin
  for(unsigned int k=0; k<lepnames.size(); ++k){
   writeSigHistograms(i,k);
   writeJetHistograms(i,k);
   //write2DHistograms(i,k);
  }
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

 // // assumes that selbins and jetmultnames have already been filled (initJetHistograms, initSigHistograms)
 // // loop through jets and selections to initialize histograms in parllel (series)
 // for(unsigned int i=0; i<selbinnames.size(); ++i){

 //   TString hname_nvertnjets = "h_"+selbinnames[i]+"_NGOODVERTICES_v_NJets";
 //   TString htitle_nvertnjets = "Nr. Good Vertices (x) vs. Nr. Jets (y)" ;
 //   h_nvertnjets[i] = initSingleHistogramTH2F( hname_nvertnjets, htitle_nvertnjets, 50, 0, 50, 50, 0, 50 ); 

 //  for(unsigned int j=0; j<jetmultnames.size(); ++j){
 //   // for histograms that are jet specific
 //  }
 // }

 return kTRUE;
}


//----------------------------fill2DHistograms
Bool_t analyzer_signal::fill2DHistograms(Double_t weight, int selbin)
{
  // //printf("fill2DHistograms\n");
  //
  //  if( NGOODVERTICES->size()>0 && JetNJets->size()>0 ) 
  //   { h_nvertnjets[selbin].Fill( NGOODVERTICES->at(0), JetNJets->at(0), weight ); }
  //
 return kTRUE;
}


//----------------------------write2DHistograms
Bool_t analyzer_signal::write2DHistograms(int selbin)
{
 ////printf("write2DtHistograms\n");
 //h_nvertnjets[selbin].Write(); 
 //for(unsigned int j=0; j<jetmultnames.size(); ++j){
 //  // for histograms that are jet specific
 //}

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
   for(unsigned int k=0; k<lepnames.size(); ++k){

    // Jet
    TString hname_jetPt                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetPt                     " ;   

    TString hname_jetTestVariable             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetTestVariable           " ;   
    TString hname_jetSumIPSig                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetSumIPSig               " ;
    TString hname_jetMedianLog10IPSig         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetMedianLog10IPSig       " ;

    TString hname_jetEn                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetEn                     " ;   
    TString hname_jetEta                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetEta                    " ;    
    TString hname_jetPhi                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetPhi                    " ;    
    TString hname_jetRawPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetRawPt                  " ;      
    TString hname_jetRawEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetRawEn                  " ;      
    TString hname_jetMt                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetMt                     " ;   
    TString hname_jetArea                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetArea                   " ;     
    TString hname_jetLeadTrackPt              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLeadTrackPt            " ;            
    TString hname_jetLeadTrackEta             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLeadTrackEta           " ;             
    TString hname_jetLeadTrackPhi             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLeadTrackPhi           " ;             
    TString hname_jetLepTrackPID              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackPID            " ;            
    TString hname_jetLepTrackPt               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackPt             " ;           
    TString hname_jetLepTrackEta              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackEta            " ;            
    TString hname_jetLepTrackPhi              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackPhi            " ;            
    TString hname_jetCSV2BJetTags             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetCSV2BJetTags           " ;             
    TString hname_jetJetProbabilityBJetTags   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetJetProbabilityBJetTags " ;                       
    TString hname_jetpfCombinedMVAV2BJetTags  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetpfCombinedMVAV2BJetTags" ;                        
    TString hname_jetPartonID                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetPartonID               " ;         //
    TString hname_jetHadFlvr                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetHadFlvr                " ;         //
    TString hname_jetGenJetEn                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetEn               " ;         //
    TString hname_jetGenJetPt                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetPt               " ;         //
    TString hname_jetGenJetEta                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetEta              " ;         // 
    TString hname_jetGenJetPhi                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetPhi              " ;         // 
    TString hname_jetGenPartonID              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPartonID            " ;         //   
    TString hname_jetGenEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenEn                  " ;         //
    TString hname_jetGenPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPt                  " ;         //
    TString hname_jetGenEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenEta                 " ;         //
    TString hname_jetGenPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPhi                 " ;         //
    TString hname_jetGenPartonMomID           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPartonMomID         " ;         //      
    TString hname_AK8JetPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetPt                  " ;      
    TString hname_AK8JetEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetEn                  " ;      
    TString hname_AK8JetRawPt                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetRawPt               " ;         
    TString hname_AK8JetRawEn                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetRawEn               " ;         
    TString hname_AK8JetEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetEta                 " ;       
    TString hname_AK8JetPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetPhi                 " ;       
    TString hname_AK8JetMass                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetMass                " ;        

    // initalize histograms
    h_jetPt                       [i][j][k] = initSingleHistogramTH1F(  hname_jetPt                      , "jetPt                     " , 50, 0, 500 );   

    h_jetTestVariable             [i][j][k] = initSingleHistogramTH1F(  hname_jetTestVariable            , "jetTestVariable           " , 50, 0, 50 );   
    h_jetSumIPSig                 [i][j][k] = initSingleHistogramTH1F(  hname_jetSumIPSig                , "jetSumIPSig               " , 50, 0,1000);
    h_jetMedianLog10IPSig         [i][j][k] = initSingleHistogramTH1F(  hname_jetMedianLog10IPSig        , "jetMedianLog10IPSig       " , 50, -5, 5 );

    h_jetEn                       [i][j][k] = initSingleHistogramTH1F(  hname_jetEn                      , "jetEn                     " , 50, 0, 500 );   
    h_jetEta                      [i][j][k] = initSingleHistogramTH1F(  hname_jetEta                     , "jetEta                    " , 10, -5, 5 );    
    h_jetPhi                      [i][j][k] = initSingleHistogramTH1F(  hname_jetPhi                     , "jetPhi                    " , 10, -5, 5 );    
    h_jetRawPt                    [i][j][k] = initSingleHistogramTH1F(  hname_jetRawPt                   , "jetRawPt                  " , 50, 0, 500 );      
    h_jetRawEn                    [i][j][k] = initSingleHistogramTH1F(  hname_jetRawEn                   , "jetRawEn                  " , 50, 0, 500 );      
    h_jetMt                       [i][j][k] = initSingleHistogramTH1F(  hname_jetMt                      , "jetMt                     " , 50, 0, 500 );   
    h_jetArea                     [i][j][k] = initSingleHistogramTH1F(  hname_jetArea                    , "jetArea                   " , 50, 0, 1 );     
    h_jetLeadTrackPt              [i][j][k] = initSingleHistogramTH1F(  hname_jetLeadTrackPt             , "jetLeadTrackPt            " , 50, 0, 100 );            
    h_jetLeadTrackEta             [i][j][k] = initSingleHistogramTH1F(  hname_jetLeadTrackEta            , "jetLeadTrackEta           " , 50, -5, 5 );             
    h_jetLeadTrackPhi             [i][j][k] = initSingleHistogramTH1F(  hname_jetLeadTrackPhi            , "jetLeadTrackPhi           " , 50, -5, 5 );             
    h_jetLepTrackPID              [i][j][k] = initSingleHistogramTH1F(  hname_jetLepTrackPID             , "jetLepTrackPID            " , 25, 0, 25 );            
    h_jetLepTrackPt               [i][j][k] = initSingleHistogramTH1F(  hname_jetLepTrackPt              , "jetLepTrackPt             " , 50, 0, 500 );           
    h_jetLepTrackEta              [i][j][k] = initSingleHistogramTH1F(  hname_jetLepTrackEta             , "jetLepTrackEta            " , 50, -5, 5 );            
    h_jetLepTrackPhi              [i][j][k] = initSingleHistogramTH1F(  hname_jetLepTrackPhi             , "jetLepTrackPhi            " , 50, -5, 5 );            
    h_jetCSV2BJetTags             [i][j][k] = initSingleHistogramTH1F(  hname_jetCSV2BJetTags            , "jetCSV2BJetTags           " , 50, 0, 1 );             
    h_jetJetProbabilityBJetTags   [i][j][k] = initSingleHistogramTH1F(  hname_jetJetProbabilityBJetTags  , "jetJetProbabilityBJetTags " , 50, 0, 1 );                       
    h_jetpfCombinedMVAV2BJetTags  [i][j][k] = initSingleHistogramTH1F(  hname_jetpfCombinedMVAV2BJetTags , "jetpfCombinedMVAV2BJetTags" , 50, 0, 1 );                        
    h_jetPartonID                 [i][j][k] = initSingleHistogramTH1F(  hname_jetPartonID                , "jetPartonID               " , 25, 0, 25 );         //
    h_jetHadFlvr                  [i][j][k] = initSingleHistogramTH1F(  hname_jetHadFlvr                 , "jetHadFlvr                " , 25, 0, 25 );         //
    h_jetGenJetEn                 [i][j][k] = initSingleHistogramTH1F(  hname_jetGenJetEn                , "jetGenJetEn               " , 50, 0, 500 );        // 
    h_jetGenJetPt                 [i][j][k] = initSingleHistogramTH1F(  hname_jetGenJetPt                , "jetGenJetPt               " , 50, 0, 500 );        // 
    h_jetGenJetEta                [i][j][k] = initSingleHistogramTH1F(  hname_jetGenJetEta               , "jetGenJetEta              " , 50, -5, 5 );         // 
    h_jetGenJetPhi                [i][j][k] = initSingleHistogramTH1F(  hname_jetGenJetPhi               , "jetGenJetPhi              " , 50, -5, 5 );         // 
    h_jetGenPartonID              [i][j][k] = initSingleHistogramTH1F(  hname_jetGenPartonID             , "jetGenPartonID            " , 25, 0, 25 );         //   
    h_jetGenEn                    [i][j][k] = initSingleHistogramTH1F(  hname_jetGenEn                   , "jetGenEn                  " , 50, 0, 500 );        //
    h_jetGenPt                    [i][j][k] = initSingleHistogramTH1F(  hname_jetGenPt                   , "jetGenPt                  " , 50, 0, 500 );        //
    h_jetGenEta                   [i][j][k] = initSingleHistogramTH1F(  hname_jetGenEta                  , "jetGenEta                 " , 50, -5, 5 );         //
    h_jetGenPhi                   [i][j][k] = initSingleHistogramTH1F(  hname_jetGenPhi                  , "jetGenPhi                 " , 50, -5, 5 );         //
    h_jetGenPartonMomID           [i][j][k] = initSingleHistogramTH1F(  hname_jetGenPartonMomID          , "jetGenPartonMomID         " , 25, 0, 25 );         //      
    h_AK8JetPt                    [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetPt                   , "AK8JetPt                  " , 50, 0, 500 );      
    h_AK8JetEn                    [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetEn                   , "AK8JetEn                  " , 50, 0, 500 );      
    h_AK8JetRawPt                 [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetRawPt                , "AK8JetRawPt               " , 50, 0, 500 );         
    h_AK8JetRawEn                 [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetRawEn                , "AK8JetRawEn               " , 50, 0, 500 );         
    h_AK8JetEta                   [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetEta                  , "AK8JetEta                 " , 50, -5, 5 );       
    h_AK8JetPhi                   [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetPhi                  , "AK8JetPhi                 " , 50, -5, 5 );       
    h_AK8JetMass                  [i][j][k] = initSingleHistogramTH1F(  hname_AK8JetMass                 , "AK8JetMass                " , 50, 0, 500 );        

   }
  }
 }

 return kTRUE;
}

//----------------------------fillJetHistograms
Bool_t analyzer_signal::fillJetHistograms(Double_t weight, int selbin, int lepbin)
{

 //printf("fillJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){

  if(jetPt                      ->size()>j){h_jetPt                       [selbin][j][lepbin].Fill( jetPt                      ->at(j), weight ); } 

  if(jetTestVariable            ->size()>j){h_jetTestVariable             [selbin][j][lepbin].Fill( jetTestVariable            ->at(j), weight ); } 
  if(jetSumIPSig                ->size()>j){h_jetSumIPSig                 [selbin][j][lepbin].Fill( jetSumIPSig                ->at(j), weight ); }
  if(jetMedianLog10IPSig        ->size()>j){h_jetMedianLog10IPSig         [selbin][j][lepbin].Fill( jetMedianLog10IPSig        ->at(j), weight ); }

  if(jetEn                      ->size()>j){h_jetEn                       [selbin][j][lepbin].Fill( jetEn                      ->at(j), weight ); } 
  if(jetEta                     ->size()>j){h_jetEta                      [selbin][j][lepbin].Fill( jetEta                     ->at(j), weight ); } 
  if(jetPhi                     ->size()>j){h_jetPhi                      [selbin][j][lepbin].Fill( jetPhi                     ->at(j), weight ); } 
  if(jetRawPt                   ->size()>j){h_jetRawPt                    [selbin][j][lepbin].Fill( jetRawPt                   ->at(j), weight ); } 
  if(jetRawEn                   ->size()>j){h_jetRawEn                    [selbin][j][lepbin].Fill( jetRawEn                   ->at(j), weight ); } 
  if(jetMt                      ->size()>j){h_jetMt                       [selbin][j][lepbin].Fill( jetMt                      ->at(j), weight ); } 
  if(jetArea                    ->size()>j){h_jetArea                     [selbin][j][lepbin].Fill( jetArea                    ->at(j), weight ); } 
  if(jetLeadTrackPt             ->size()>j){h_jetLeadTrackPt              [selbin][j][lepbin].Fill( jetLeadTrackPt             ->at(j), weight ); } 
  if(jetLeadTrackEta            ->size()>j){h_jetLeadTrackEta             [selbin][j][lepbin].Fill( jetLeadTrackEta            ->at(j), weight ); } 
  if(jetLeadTrackPhi            ->size()>j){h_jetLeadTrackPhi             [selbin][j][lepbin].Fill( jetLeadTrackPhi            ->at(j), weight ); } 
  if(jetLepTrackPID             ->size()>j){h_jetLepTrackPID              [selbin][j][lepbin].Fill( jetLepTrackPID             ->at(j), weight ); } 
  if(jetLepTrackPt              ->size()>j){h_jetLepTrackPt               [selbin][j][lepbin].Fill( jetLepTrackPt              ->at(j), weight ); } 
  if(jetLepTrackEta             ->size()>j){h_jetLepTrackEta              [selbin][j][lepbin].Fill( jetLepTrackEta             ->at(j), weight ); } 
  if(jetLepTrackPhi             ->size()>j){h_jetLepTrackPhi              [selbin][j][lepbin].Fill( jetLepTrackPhi             ->at(j), weight ); } 
  if(jetCSV2BJetTags            ->size()>j){h_jetCSV2BJetTags             [selbin][j][lepbin].Fill( jetCSV2BJetTags            ->at(j), weight ); } 
  if(jetJetProbabilityBJetTags  ->size()>j){h_jetJetProbabilityBJetTags   [selbin][j][lepbin].Fill( jetJetProbabilityBJetTags  ->at(j), weight ); } 
  if(jetpfCombinedMVAV2BJetTags ->size()>j){h_jetpfCombinedMVAV2BJetTags  [selbin][j][lepbin].Fill( jetpfCombinedMVAV2BJetTags ->at(j), weight ); } 
  if(isMC){
   if(jetPartonID                ->size()>j){h_jetPartonID                 [selbin][j][lepbin].Fill( jetPartonID                ->at(j), weight ); } 
   if(jetHadFlvr                 ->size()>j){h_jetHadFlvr                  [selbin][j][lepbin].Fill( jetHadFlvr                 ->at(j), weight ); } 
   if(jetGenJetEn                ->size()>j){h_jetGenJetEn                 [selbin][j][lepbin].Fill( jetGenJetEn                ->at(j), weight ); } 
   if(jetGenJetPt                ->size()>j){h_jetGenJetPt                 [selbin][j][lepbin].Fill( jetGenJetPt                ->at(j), weight ); } 
   if(jetGenJetEta               ->size()>j){h_jetGenJetEta                [selbin][j][lepbin].Fill( jetGenJetEta               ->at(j), weight ); } 
   if(jetGenJetPhi               ->size()>j){h_jetGenJetPhi                [selbin][j][lepbin].Fill( jetGenJetPhi               ->at(j), weight ); } 
   if(jetGenPartonID             ->size()>j){h_jetGenPartonID              [selbin][j][lepbin].Fill( jetGenPartonID             ->at(j), weight ); } 
   if(jetGenEn                   ->size()>j){h_jetGenEn                    [selbin][j][lepbin].Fill( jetGenEn                   ->at(j), weight ); } 
   if(jetGenPt                   ->size()>j){h_jetGenPt                    [selbin][j][lepbin].Fill( jetGenPt                   ->at(j), weight ); } 
   if(jetGenEta                  ->size()>j){h_jetGenEta                   [selbin][j][lepbin].Fill( jetGenEta                  ->at(j), weight ); } 
   if(jetGenPhi                  ->size()>j){h_jetGenPhi                   [selbin][j][lepbin].Fill( jetGenPhi                  ->at(j), weight ); } 
   if(jetGenPartonMomID          ->size()>j){h_jetGenPartonMomID           [selbin][j][lepbin].Fill( jetGenPartonMomID          ->at(j), weight ); } 
  }

  if(AK8JetPt                   ->size()>j){h_AK8JetPt                    [selbin][j][lepbin].Fill( AK8JetPt                   ->at(j), weight ); } 
  if(AK8JetEn                   ->size()>j){h_AK8JetEn                    [selbin][j][lepbin].Fill( AK8JetEn                   ->at(j), weight ); } 
  if(AK8JetRawPt                ->size()>j){h_AK8JetRawPt                 [selbin][j][lepbin].Fill( AK8JetRawPt                ->at(j), weight ); } 
  if(AK8JetRawEn                ->size()>j){h_AK8JetRawEn                 [selbin][j][lepbin].Fill( AK8JetRawEn                ->at(j), weight ); } 
  if(AK8JetEta                  ->size()>j){h_AK8JetEta                   [selbin][j][lepbin].Fill( AK8JetEta                  ->at(j), weight ); } 
  if(AK8JetPhi                  ->size()>j){h_AK8JetPhi                   [selbin][j][lepbin].Fill( AK8JetPhi                  ->at(j), weight ); } 
  if(AK8JetMass                 ->size()>j){h_AK8JetMass                  [selbin][j][lepbin].Fill( AK8JetMass                 ->at(j), weight ); } 

 }

 return kTRUE;
}

//----------------------------writeJetHistograms
Bool_t analyzer_signal::writeJetHistograms(int selbin, int lepbin)
{
 //printf("writeJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){

   h_jetPt                       [selbin][j][lepbin].Write(); 

   h_jetTestVariable             [selbin][j][lepbin].Write(); 
   h_jetSumIPSig                 [selbin][j][lepbin].Write();
   h_jetMedianLog10IPSig         [selbin][j][lepbin].Write();

   h_jetEn                       [selbin][j][lepbin].Write(); 
   h_jetEta                      [selbin][j][lepbin].Write(); 
   h_jetPhi                      [selbin][j][lepbin].Write(); 
   h_jetRawPt                    [selbin][j][lepbin].Write(); 
   h_jetRawEn                    [selbin][j][lepbin].Write(); 
   h_jetMt                       [selbin][j][lepbin].Write(); 
   h_jetArea                     [selbin][j][lepbin].Write(); 
   h_jetLeadTrackPt              [selbin][j][lepbin].Write(); 
   h_jetLeadTrackEta             [selbin][j][lepbin].Write(); 
   h_jetLeadTrackPhi             [selbin][j][lepbin].Write(); 
   h_jetLepTrackPID              [selbin][j][lepbin].Write(); 
   h_jetLepTrackPt               [selbin][j][lepbin].Write(); 
   h_jetLepTrackEta              [selbin][j][lepbin].Write(); 
   h_jetLepTrackPhi              [selbin][j][lepbin].Write(); 
   h_jetCSV2BJetTags             [selbin][j][lepbin].Write(); 
   h_jetJetProbabilityBJetTags   [selbin][j][lepbin].Write(); 
   h_jetpfCombinedMVAV2BJetTags  [selbin][j][lepbin].Write(); 
   h_jetPartonID                 [selbin][j][lepbin].Write(); //
   h_jetHadFlvr                  [selbin][j][lepbin].Write(); //
   h_jetGenJetEn                 [selbin][j][lepbin].Write(); //
   h_jetGenJetPt                 [selbin][j][lepbin].Write(); //
   h_jetGenJetEta                [selbin][j][lepbin].Write(); //
   h_jetGenJetPhi                [selbin][j][lepbin].Write(); //
   h_jetGenPartonID              [selbin][j][lepbin].Write(); //
   h_jetGenEn                    [selbin][j][lepbin].Write(); //
   h_jetGenPt                    [selbin][j][lepbin].Write(); //
   h_jetGenEta                   [selbin][j][lepbin].Write(); //
   h_jetGenPhi                   [selbin][j][lepbin].Write(); //
   h_jetGenPartonMomID           [selbin][j][lepbin].Write(); //
   h_AK8JetPt                    [selbin][j][lepbin].Write(); 
   h_AK8JetEn                    [selbin][j][lepbin].Write(); 
   h_AK8JetRawPt                 [selbin][j][lepbin].Write(); 
   h_AK8JetRawEn                 [selbin][j][lepbin].Write(); 
   h_AK8JetEta                   [selbin][j][lepbin].Write(); 
   h_AK8JetPhi                   [selbin][j][lepbin].Write(); 
   h_AK8JetMass                  [selbin][j][lepbin].Write(); 
 }

 return kTRUE;
}


//----------------------------initSigHistograms
Bool_t analyzer_signal::initSigHistograms()
{

 lepnames.clear();
 lepnames.push_back("ele");
 lepnames.push_back("mu");

 selbinnames.clear();
 selbinnames.push_back("NoSel");
 selbinnames.push_back("Sig");
 selbinnames.push_back("ZH");
 selbinnames.push_back("DY");
 selbinnames.push_back("OffZ");
 selbinnames.push_back("NoPair");

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){

   // initialize names
   TString hname_nVtx   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nVtx  "; 
   TString hname_nPU    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nPU   "; 
   TString hname_phoEt  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoEt "; 
   TString hname_phoEta = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoEta"; 
   TString hname_phoPhi = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoPhi"; 
   TString hname_elePt  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePt "; 
   TString hname_eleEta = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleEta"; 
   TString hname_elePhi = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePhi"; 
   TString hname_muPt   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPt  "; 
   TString hname_muEta  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muEta "; 
   TString hname_muPhi  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPhi "; 

   TString hname_htall   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htall "; 
   TString hname_htjets  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htjets "; 

   // initalize histograms
   h_nVtx  [i][k] = initSingleHistogramTH1F( hname_nVtx  , "nVtx  ", 60,0,60) ; 
   h_nPU   [i][k] = initSingleHistogramTH1F( hname_nPU   , "nPU   ", 60,0,60) ; 
   h_phoEt [i][k] = initSingleHistogramTH1F( hname_phoEt , "phoEt ", 50,0,300) ; 
   h_phoEta[i][k] = initSingleHistogramTH1F( hname_phoEta, "phoEta", 10,-5,5) ; 
   h_phoPhi[i][k] = initSingleHistogramTH1F( hname_phoPhi, "phoPhi", 10,5,5) ; 
   h_elePt [i][k] = initSingleHistogramTH1F( hname_elePt , "elePt ", 50,0,300) ; 
   h_eleEta[i][k] = initSingleHistogramTH1F( hname_eleEta, "eleEta", 10,-5,5) ; 
   h_elePhi[i][k] = initSingleHistogramTH1F( hname_elePhi, "elePhi", 10,-5,50) ; 
   h_muPt  [i][k] = initSingleHistogramTH1F( hname_muPt  , "muPt  ", 50,0,300) ; 
   h_muEta [i][k] = initSingleHistogramTH1F( hname_muEta , "muEta ", 10,-5,5) ; 
   h_muPhi [i][k] = initSingleHistogramTH1F( hname_muPhi , "muPhi ", 10,-5,5) ; 

   h_htall  [i][k] = initSingleHistogramTH1F( hname_htall  , "htall ", 50,0,1000) ; 
   h_htjets [i][k] = initSingleHistogramTH1F( hname_htjets , "htjets", 50,0,1000) ; 
  }
 }

 return kTRUE;
}

//----------------------------fillSigHistograms
Bool_t analyzer_signal::fillSigHistograms(Double_t weight, int selbin, int lepbin)
{

 //printf("fillSigHistograms\n");
  h_nVtx  [selbin][lepbin].Fill( nVtx  , weight); 

  h_htall [selbin][lepbin].Fill( htall , weight);
  h_htjets[selbin][lepbin].Fill( htjets, weight);

  if(isMC){
   if(nPU   ->size()>0){ h_nPU   [selbin][lepbin].Fill( nPU   ->at(0), weight); } 
  }
  if(phoEt ->size()>0){ h_phoEt [selbin][lepbin].Fill( phoEt ->at(0), weight); } 
  if(phoEta->size()>0){ h_phoEta[selbin][lepbin].Fill( phoEta->at(0), weight); } 
  if(phoPhi->size()>0){ h_phoPhi[selbin][lepbin].Fill( phoPhi->at(0), weight); } 
  if(elePt ->size()>0){ h_elePt [selbin][lepbin].Fill( elePt ->at(0), weight); } 
  if(eleEta->size()>0){ h_eleEta[selbin][lepbin].Fill( eleEta->at(0), weight); } 
  if(elePhi->size()>0){ h_elePhi[selbin][lepbin].Fill( elePhi->at(0), weight); } 
  if(muPt  ->size()>0){ h_muPt  [selbin][lepbin].Fill( muPt  ->at(0), weight); } 
  if(muEta ->size()>0){ h_muEta [selbin][lepbin].Fill( muEta ->at(0), weight); } 
  if(muPhi ->size()>0){ h_muPhi [selbin][lepbin].Fill( muPhi ->at(0), weight); } 


 return kTRUE;
}

//----------------------------writeSigHistograms
//Bool_t analyzer_signal::writeSigHistograms(int ptbin, int sysbin)
Bool_t analyzer_signal::writeSigHistograms(int selbin, int lepbin)
{
 //printf("writeSigHistograms\n");
  h_nVtx  [selbin][lepbin].Write(); 
  h_htall [selbin][lepbin].Write(); 
  h_htjets[selbin][lepbin].Write(); 

  h_nPU   [selbin][lepbin].Write(); 
  h_phoEt [selbin][lepbin].Write(); 
  h_phoEta[selbin][lepbin].Write(); 
  h_phoPhi[selbin][lepbin].Write(); 
  h_elePt [selbin][lepbin].Write(); 
  h_eleEta[selbin][lepbin].Write(); 
  h_elePhi[selbin][lepbin].Write(); 
  h_muPt  [selbin][lepbin].Write(); 
  h_muEta [selbin][lepbin].Write(); 
  h_muPhi [selbin][lepbin].Write(); 

 return kTRUE;
}

// cuts -------------------------------------------------------------
Bool_t analyzer_signal::askPassSingleEle()
{
// eleFiredSingleTrgs = (vector<unsigned int>*)0x3961a70
// eleFiredDoubleTrgs = (vector<unsigned int>*)0x3961e80
 Bool_t doespass = kFALSE;
 if(electron_list.size()>0){ 
   doespass = elePt->at( electron_list.at(0) ) > 30 ;
 } 
 return doespass;
}


Bool_t analyzer_signal::askPassSingleMu()
{
// muFiredSingleTrgs = (vector<unsigned int>*)0x3961a70
// muFiredDoubleTrgs = (vector<unsigned int>*)0x3961e80
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0){ 
   doespass = muPt->at( muon_list.at(0) ) > 28 ;
 } 

 return doespass;
}


Bool_t analyzer_signal::askPassSig()
{
 Bool_t doespass = kTRUE;
 if( (passSingleEle || passSingleMu) ){
  n_passSig++;
  if( passSingleEle ){ n_ele_passSig++; }
  if( passSingleMu ) { n_mu_passSig++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassZH()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && passZWindow
     && passPTOSSFg50
     && passOneJet
     && (passSingleEle || passSingleMu)
     //&&  triggers..
    )
 { doespass = kTRUE; n_passZH++;
  if( passSingleEle ){ n_ele_passZH++; }
  if( passSingleMu ) { n_mu_passZH++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassDY()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && passZWindow
     && !passPTOSSFg50
     && passOneJet
     && (passSingleEle || passSingleMu)
     //&&  triggers..
    )
 { doespass = kTRUE; n_passDY++; 
  //printf("\n PASS DY Event %lld\n", event);
  if( passSingleEle ){ n_ele_passDY++; } // printf("\n PASS SingleEle Event %lld\n", event); }
  if( passSingleMu ) { n_mu_passDY++;  } // printf("\n PASS SingleMu Event %lld\n", event); }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassOffZ()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && !passZWindow
     && passOSSF
     && passOneJet
     && (passSingleEle || passSingleMu)
     //&&  triggers..
    )
 { doespass = kTRUE; n_passOffZ++;
  if( passSingleEle ){ n_ele_passOffZ++; }
  if( passSingleMu ) { n_mu_passOffZ++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassNoPair()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && !passZWindow
     && !passOSSF
     && passOneJet
     && (passSingleEle || passSingleMu)
     //&&  triggers..
    )
 { doespass = kTRUE; n_passNoPair++;
  if( passSingleEle ){ n_ele_passNoPair++; }
  if( passSingleMu ) { n_mu_passNoPair++; }
 }
 return doespass;
}

analyzer_signal::analyzer_signal()
{
}

analyzer_signal::~analyzer_signal()
{
}

//-------------------------dR
double analyzer_signal::dR(double eta1, double phi1, double eta2, double phi2)
{
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//-------------------------DeltaPhi
double analyzer_signal::DeltaPhi(double phi1, double phi2)
//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
{
  double pi = TMath::Pi();
  double dphi = fabs(phi1-phi2);
  if(dphi>pi) 
    dphi = 2.0*pi - dphi;
  return dphi;
}

//-------------------------getMuonPt
Float_t analyzer_signal::getMuonPt(int i, TString sysbinname){

      //Muon passes pt cut 
      Float_t muonPt = muPt->at(i);
      Float_t muonEnergy = muonPt*TMath::CosH( muEta->at(i) );
      if(sysbinname=="_MESUp"  ){ muonEnergy*=(1.0 + 0.015); }
      if(sysbinname=="_MESDown"){ muonEnergy*=(1.0 - 0.015); }

      muonPt = muonEnergy/TMath::CosH( muEta->at(i) );
  return muonPt;

}

//-------------------------getElectronPt
Float_t analyzer_signal::getElectronPt(int i, TString sysbinname){

      //Electron passes pt cut 
      Float_t electronPt = elePt->at(i);
      Float_t electronEnergy = electronPt*TMath::CosH( eleEta->at(i) );
      if(sysbinname=="_EESUp"  ){ electronEnergy*=(1.0 + 0.015); }
      if(sysbinname=="_EESDown"){ electronEnergy*=(1.0 - 0.015); }

      electronPt = electronEnergy/TMath::CosH( eleEta->at(i) );

  return electronPt;

}

//-------------------------getPhotonPt
Float_t analyzer_signal::getPhotonPt(int idnr, TString sysbinname){

      Float_t photonenergy = phoSCRawE->at(idnr);
      if(sysbinname=="_PESUp"  ){ photonenergy*=(1. + 0.015); }
      if(sysbinname=="_PESDown"){ photonenergy*=(1. - 0.015); }

      Float_t phoPt = photonenergy/TMath::CosH( (*phoSCEta)[idnr] );

  return phoPt;

}

//-------------------------muon_passLooseID
std::vector<int> analyzer_signal::muon_passLooseID( double muPtCut, double muEtaCut, TString sysbinname)
{
  std::vector<int> mulist;

  bool pass_PFMuon = false;
  bool pass_globalMuon = false;
  bool pass_trackerMuon = false;
  bool pass_iso = false;
  //Explicitly stating types to avoid a TMath::Max conversion issue 
  Float_t zero = 0.0; 
  Float_t muPhoPU = 999.9;
  Float_t tightIso_combinedRelative = 999.9;
  for(int i = 0; i < nMu; i++) 
    {    

      pass_PFMuon =            true;  // muIsPFMuon->at(i);
      pass_globalMuon =        true;  // muIsGlobalMuon->at(i);
      pass_trackerMuon =       true;  // muIsTrackerMuon->at(i);
      muPhoPU = muPFNeuIso->at(i) + muPFPhoIso->at(i) - 0.5*muPFPUIso->at(i);
      tightIso_combinedRelative = (muPFChIso->at(i) + TMath::Max(zero,muPhoPU))/(muPt->at(i));
      pass_iso = tightIso_combinedRelative < 0.25;
      //Muon passes Loose Muon ID and PF-based combined relative, dBeta-corrected Loose Muon Isolation cuts  

//if( event==767326116 ){
//      printf(" Event: %lli \n",event);
//      printf("  muPt              %f \n",  muPt->at(i)                        );
//      printf("  muIsPFMuon        %f \n",  muIsPFMuon->at(i)                  );
//      printf("  muIsGlobalMuon    %f \n",  muIsGlobalMuon->at(i)              );
//      printf("  muIsTrackerMuon   %f \n",  muIsTrackerMuon->at(i)             );
//      printf("  muPFNeuIso        %f \n",  muPFNeuIso->at(i)                  );
//      printf("  muPFPhoIso        %f \n",  muPFPhoIso->at(i)                  );
//      printf("  muPFPUIso         %f \n",  muPFPUIso->at(i)                   );
//      printf("  muPhoPU           %f \n",  muPhoPU                            );
//      printf("\n\n");
//                   std::cout<<muPt->at(i)<<std::endl;
//                   std::cout<<muEta->at(i)<<std::endl;
//                   std::cout<<"veto Passed!!!!"<<muEta->at(i)<<" "<<muPhi->at(i)<<" "<<phoSCEta->at(pho_index)<<" "<<phoSCPhi->at(pho_index)<<std::endl;
//}

      //if(pass_PFMuon && (pass_globalMuon || pass_trackerMuon) && pass_iso)
      if(pass_PFMuon && (pass_globalMuon || pass_trackerMuon) )
        {    
          //Muon passes pt cut 
          Float_t muonPt = getMuonPt(i,sysbinname);
          if(muonPt > muPtCut && ( fabs(muEta->at(i)) < muEtaCut ) )
            {    
              ////Muon does not overlap photon
              //if(dR(muEta->at(i),muPhi->at(i),phoSCEta->at(pho_index),phoSCPhi->at(pho_index)) > 0.5) 
              //  {    
                 mulist.push_back(i);
              //  }    
            }    
        }    
    }    
  return mulist;
}

//-------------------------muon_passTightID
std::vector<int> analyzer_signal::muon_passTightID(double muPtCut, double muEtaCut, TString sysbinname)
{
  std::vector<int> mu_cands;
  mu_cands.clear();

  bool pass_PFMuon = false;
  bool pass_globalMuon = false;
  // bool pass_trackerMuon = false;
  bool pass_chi2ndf = false;
  bool pass_chamberHit = false;
  bool pass_matchedStations = false;
  bool pass_dxy = false;
  bool pass_dz = false;
  bool pass_pixelHits = false;
  bool pass_trackLayers = false;
  bool pass_iso = false;
  //Explicitly stating types to avoid a TMath::Max conversion issue
  Float_t zero = 0.0; 
  Float_t muPhoPU = 999.9;
  Float_t tightIso_combinedRelative = 999.9;
  for(int i = 0; i < nMu; i++) 
  {
    pass_globalMuon = true;  //muIsGlobalMuon->at(i);
    pass_PFMuon =     true;  // muIsPFMuon->at(i);
    // pass_trackerMuon = muIsTrackerMuon->at(i);
    pass_chi2ndf = muChi2NDF->at(i) < 10.0;
    pass_chamberHit = muMuonHits->at(i) > 0; 
    pass_matchedStations = muStations->at(i) > 1; 
    pass_dxy = fabs(muInnerD0->at(i)) < 0.2; 
    pass_dz = fabs(muInnerDz->at(i)) < 0.5; 
    pass_pixelHits = muPixelHits->at(i) > 0; 
    pass_trackLayers = muTrkLayers->at(i) > 5; 

    muPhoPU = muPFNeuIso->at(i) + muPFPhoIso->at(i) - 0.5*muPFPUIso->at(i);
    tightIso_combinedRelative = (muPFChIso->at(i) + TMath::Max(zero,muPhoPU))/(muPt->at(i));
    pass_iso = tightIso_combinedRelative < 0.15;
    //Muon passes Tight Muon ID
    if(pass_globalMuon && pass_PFMuon && pass_chi2ndf && pass_chamberHit && pass_matchedStations && pass_dxy && pass_dz && pass_pixelHits && pass_trackLayers)
    {    
      //Muon passes pt cut 
      Float_t muonPt = getMuonPt(i,sysbinname);
      if(muonPt > muPtCut && ( fabs(muEta->at(i)) > muEtaCut ) )
      {    
        ////Muon does not overlap photon
        //if(dR(muEta->at(i),muPhi->at(i),phoSCEta->at(pho_index),phoSCPhi->at(pho_index)) > 0.5) 
        //{    
          mu_cands.push_back(i);
        //}    
      }    
    }    
  }
  return mu_cands;
}


//-------------------------electron_passLooseID
std::vector<int> analyzer_signal::electron_passLooseID( double elePtCut, double eleEtaCut, TString sysbinname)
{
  //bool veto_passed = true; //pass veto if no good electron found 
  std::vector<int> elelist;

  bool pass_SigmaIEtaIEtaFull5x5 = false;
  bool pass_dEtaIn = false;
  bool pass_dPhiIn = false;
  bool pass_HoverE = false;
  bool pass_iso = false;
  bool pass_ooEmooP = false;
  bool pass_d0 = false;
  bool pass_dz = false;
  bool pass_missingHits = false;
  bool pass_convVeto = false;
  //Explicitly stating types to avoid a TMath::Max conversion issue   
  Float_t EA = 0.0;
  Float_t zero = 0.0;
  Float_t EAcorrIso = 999.9;
  for(int i = 0; i < nEle; i++)
    {
      //Make sure these get reset for every electron  
      pass_SigmaIEtaIEtaFull5x5 = false;
      pass_dEtaIn = false;
      pass_dPhiIn = false;
      pass_HoverE = false;
      pass_iso = false;
      pass_ooEmooP = false;
      pass_d0 = false;
      pass_dz = false;
      pass_missingHits = false;
      pass_convVeto = false;
      //Find EA for corrected relative iso.  
      if(abs(eleSCEta->at(i)) <= 1.0)
        EA = 0.1752;
      else if(1.0 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 1.479)
        EA = 0.1862;
      else if(1.479 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.0)
        EA = 0.1411;
      else if(2.0 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.2)
        EA = 0.1534;
      else if(2.2 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.3)
        EA = 0.1903;
      else if(2.3 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.4)
        EA = 0.2243;
      else if(2.4 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) < 2.5)
        EA = 0.2687;
      EAcorrIso = (elePFChIso->at(i) + TMath::Max(zero,elePFNeuIso->at(i) + elePFPhoIso->at(i) - rho*EA))/(elePt->at(i));

      if(abs(eleSCEta->at(i)) <= 1.479)
        {    
          pass_SigmaIEtaIEtaFull5x5 = eleSigmaIEtaIEtaFull5x5->at(i) < 0.0103;
          pass_dEtaIn = abs(eledEtaAtVtx->at(i)) < 0.0105;
          pass_dPhiIn = abs(eledPhiAtVtx->at(i)) < 0.115;
          pass_HoverE = eleHoverE->at(i) < 0.104;
          pass_iso = EAcorrIso < 0.0893;
          pass_ooEmooP = eleEoverPInv->at(i) < 0.102;
          pass_d0 = abs(eleD0->at(i)) < 0.0261;
          pass_dz = abs(eleDz->at(i)) < 0.41;
          pass_missingHits = eleMissHits->at(i) <= 2;
          pass_convVeto = eleConvVeto->at(i) == 1;
        }     
      else if(1.479 < abs(eleSCEta->at(i)) < 2.5) 
        {    
          pass_SigmaIEtaIEtaFull5x5 = eleSigmaIEtaIEtaFull5x5->at(i) < 0.0301;
          pass_dEtaIn = abs(eledEtaAtVtx->at(i)) < 0.00814;
          pass_dPhiIn = abs(eledPhiAtVtx->at(i)) < 0.182;
          pass_HoverE = eleHoverE->at(i) < 0.0897;
          pass_iso = EAcorrIso < 0.121;
          pass_ooEmooP = eleEoverPInv->at(i) < 0.126;
          pass_d0 = abs(eleD0->at(i)) < 0.118;
          pass_dz = abs(eleDz->at(i)) < 0.822;
          pass_missingHits = eleMissHits->at(i) <= 1;
          pass_convVeto = eleConvVeto->at(i) == 1;
        }     

      //Electron passes Loose Electron ID cuts 
      if(pass_SigmaIEtaIEtaFull5x5 && pass_dEtaIn && pass_dPhiIn && pass_HoverE && pass_iso && pass_ooEmooP && pass_d0 && pass_dz && pass_missingHits && pass_convVeto)    
        {    
            //Electron passes pt cut 
            Float_t electronPt = getElectronPt(i,sysbinname);
            if(electronPt > elePtCut && ( fabs(eleEta->at(i)) < eleEtaCut ) )
            {    
              ////Electron does not overlap photon 
              //if(dR(eleSCEta->at(i),eleSCPhi->at(i),phoSCEta->at(pho_index),phoSCPhi->at(pho_index)) > 0.5) 
              //  {    
                  elelist.push_back(i);
              //  }     
            }     
        }     
    }     
  return elelist;
}

//-------------------------electron_passTightID
std::vector<int> analyzer_signal::electron_passTightID(double elePtCut, double eleEtaCut, TString sysbinname)
{

  std::vector<int> ele_cands;
  ele_cands.clear();

  bool pass_SigmaIEtaIEtaFull5x5 = false;
  bool pass_dEtaIn = false;
  bool pass_dPhiIn = false;
  bool pass_HoverE = false;
  bool pass_iso = false;
  bool pass_ooEmooP = false;
  bool pass_d0 = false;
  bool pass_dz = false;
  bool pass_missingHits = false;
  bool pass_convVeto = false;
  //Explicitly stating types to avoid a TMath::Max conversion issue
  Float_t EA = 0.0;
  Float_t zero = 0.0;
  Float_t EAcorrIso = 999.9;
  for(int i = 0; i < nEle; i++)
  {
    //Make sure these get reset for every electron
    pass_SigmaIEtaIEtaFull5x5 = false;
    pass_dEtaIn = false;
    pass_dPhiIn = false;
    pass_HoverE = false;
    pass_iso = false;
    pass_ooEmooP = false;
    pass_d0 = false;
    pass_dz = false;
    pass_missingHits = false;
    pass_convVeto = false;
    //Find EA for corrected relative iso.
    if(abs(eleSCEta->at(i)) <= 1.0)
      EA = 0.1752;
    else if(1.0 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 1.479)
      EA = 0.1862;
    else if(1.479 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.0)
      EA = 0.1411;
    else if(2.0 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.2)
      EA = 0.1534;
    else if(2.2 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.3)
      EA = 0.1903;
    else if(2.3 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) <= 2.4)
      EA = 0.2243;
    else if(2.4 < abs(eleSCEta->at(i)) && abs(eleSCEta->at(i)) < 2.5)
      EA = 0.2687;
    EAcorrIso = (elePFChIso->at(i) + TMath::Max(zero,elePFNeuIso->at(i) + elePFPhoIso->at(i) - rho*EA))/(elePt->at(i));

    if(abs(eleSCEta->at(i)) <= 1.479)
    {
      pass_SigmaIEtaIEtaFull5x5 = eleSigmaIEtaIEtaFull5x5->at(i) < 0.0101;
      pass_dEtaIn = abs(eledEtaAtVtx->at(i)) < 0.00926;
      pass_dPhiIn = abs(eledPhiAtVtx->at(i)) < 0.0336;
      pass_HoverE = eleHoverE->at(i) < 0.0597;
      pass_iso = EAcorrIso < 0.0354;
      pass_ooEmooP = eleEoverPInv->at(i) < 0.012;
      pass_d0 = abs(eleD0->at(i)) < 0.0111;
      pass_dz = abs(eleDz->at(i)) < 0.0466;
      pass_missingHits = eleMissHits->at(i) <= 2;
      pass_convVeto = eleConvVeto->at(i) == 1;
    }
    else if(1.479 < abs(eleSCEta->at(i)) < 2.5)
    {
      pass_SigmaIEtaIEtaFull5x5 = eleSigmaIEtaIEtaFull5x5->at(i) < 0.0279;
      pass_dEtaIn = abs(eledEtaAtVtx->at(i)) < 0.00724;
      pass_dPhiIn = abs(eledPhiAtVtx->at(i)) < 0.0918;
      pass_HoverE = eleHoverE->at(i) < 0.0615;
      pass_iso = EAcorrIso < 0.0646;
      pass_ooEmooP = eleEoverPInv->at(i) < 0.00999;
      pass_d0 = abs(eleD0->at(i)) < 0.0351;
      pass_dz = abs(eleDz->at(i)) < 0.417;
      pass_missingHits = eleMissHits->at(i) <= 1;
      pass_convVeto = eleConvVeto->at(i) == 1;
    }
      //Electron passes Loose Electron ID cuts
    if(pass_SigmaIEtaIEtaFull5x5 && pass_dEtaIn && pass_dPhiIn && pass_HoverE && pass_iso && pass_ooEmooP && pass_d0 && pass_dz && pass_missingHits && pass_convVeto)
    {
      //Electron passes pt cut 
      Float_t electronPt = getElectronPt(i,sysbinname);
      if(electronPt > elePtCut && ( fabs(elePt->at(i)) < eleEtaCut ) )
      {
        ////Electron does not overlap photon
        //if(dR(eleSCEta->at(i),eleSCPhi->at(i),phoSCEta->at(pho_index),phoSCPhi->at(pho_index)) > 0.5)
        //{
          ele_cands.push_back(i);
        //}
      }
    }
  }
  return ele_cands;
}

//-------------------------jet_passID
std::vector<int> analyzer_signal::jet_passID(double jetPtCut, double jetEtaCut, TString sysbinname) {

  bool jetVeto=true;
  std::vector<int> jetindex;
  float PUIDvalue = 0.0;

  for(int i = 0; i < nJet; i++)
   {
    if(0.0 < abs(jetEta->at(i)) && abs(jetEta->at(i)) <2.5)   {PUIDvalue =-0.8;}
    if(2.5 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <2.75) {PUIDvalue =-0.95;}
    if(2.75 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <3.0) {PUIDvalue =-0.97;}
    if(3.00 <= abs(jetEta->at(i)) && abs(jetEta->at(i)) <5.0) {PUIDvalue =-0.99;}

    bool passOverlap=true;
    // // check overlap with electrons
    // for(int i=0; i<electron_list.size(); ++i){
    //  int eleindex = electron_list[i];
    //  if( dR( eleSCEta->at(eleindex),eleSCPhi->at(eleindex), jetEta->at(i),jetPhi->at(i) ) < 0.5 ) 
    //   {
    //    passOverlap=false;
    //   }
    // }

    // check overlap with muons
    for(int i=0; i<muon_list.size(); ++i){
     int muindex = muon_list[i];
     if( dR( muEta->at(muindex),muPhi->at(muindex), jetEta->at(i),jetPhi->at(i) ) < 0.5 ) 
      {
       passOverlap=false;
      }
    }


    //double deltar = 0.0 ;
    //      std::cout<<"Jet size: "<<nJet<<std::endl;
    //      std::cout<<"Jet no:"<<i<<"coming here pujetid: "<<pfJet_pt[i]<<std::endl;
    //      if(OverlapWithMuon(jetEta->at(i),jetPhi->at(i)))     continue;
    //      std::cout<<"Jet no:"<<i<<"coming here OverlapWithMuon: "<<pfJet_pt[i]<<std::endl;
    //      if(OverlapWithElectron(jetEta->at(i),jetPhi->at(i)))   continue;
    //if(pho_index>=0){
    //  deltar= dR(jetEta->at(i),jetPhi->at(i),phoSCEta->at(pho_index),phoSCPhi->at(pho_index));
    //  //std::cout<<"Delta R between photon and jet="<<dR<< "jet pt"<<pfJet_pt[i]<<std::endl;
    //}
    //if(deltar>0.4 && jetPt->at(i) >jetPtCut && jetPFLooseId->at(i)==1) //  && jetPUidFullDiscriminant->at(i)>PUIDvalue)
    if( jetPt->at(i) >jetPtCut && abs(jetEta->at(i))<jetEtaCut && jetPFLooseId->at(i)==1 && passOverlap )
     //  && jetPUidFullDiscriminant->at(i)>PUIDvalue)
     {
       jetindex.push_back(i);
     }
   }

  //  std::cout<<"Jet size: "<< jetindex.size()<<std::endl;
  //if(jetindex.size()>1)jetVeto = false;
  return jetindex;

}


//-------------------------photon_passLooseID
std::vector<int> analyzer_signal::photon_passLooseID(double phoPtCut, double phoEtaCut, TString sysbinname){

  std::vector<int> pholist;
  pholist.clear();

  //Loop over photons                   
  for(int p=0;p<nPho;p++)
    {    

      Float_t thephoPt = getPhotonPt(p,sysbinname);
      //Float_t thephoPt =  phoSCRawE->at(p) / TMath::CosH( (*phoSCEta)[p] ); //  phoEt->at(p); 
      Float_t thephoEta = phoSCEta->at(p);                                  //  phoEta->at(p);

      //bool kinematic = phoPt > phoPtCut && fabs((*phoSCEta)[p])<phoEtaCut;
      bool kinematic = thephoPt > phoPtCut && fabs(thephoEta)<phoEtaCut;

      bool photonId = (
                       ((*phoHoverE)[p]                <  0.05   ) && 
                       ( TMath::Max( ( (*phoPFChIso)[p]       - rho*EAcharged((*phoSCEta)[p]) ), 0.0) < 1.37 )  &&
                       ( TMath::Max( ( (*phoPFNeuIso)[p] - rho*EAneutral((*phoSCEta)[p]) ), 0.0) <
                        (1.06 + (0.014 * thephoPt) + (0.000019 * pow(thephoPt, 2.0))) )  &&
                       ( TMath::Max( ( (*phoPFPhoIso)[p] - rho*EAphoton((*phoSCEta)[p])  ), 0.0) < 
                        (0.28 + (0.0053 * thephoPt)) ) 
                      );

      if(photonId && kinematic ){
        pholist.push_back(p);
      }    
    }    

  return pholist;

}

// https://indico.cern.ch/event/455258/contribution/0/attachments/1173322/1695132/SP15_253rd.pdf -- slide-5
// Worst Charged Hadron Isolation EA
Double_t analyzer_signal::EAchargedworst(Double_t eta){
  Float_t EffectiveArea = 0.0;
  if(fabs(eta) >= 0.0   && fabs(eta) < 1.0   ) EffectiveArea = 0.078;
  if(fabs(eta) >= 1.0   && fabs(eta) < 1.479 ) EffectiveArea = 0.089;
  return EffectiveArea;
}

// standard EA
Double_t analyzer_signal::EAcharged(Double_t eta){
  Float_t EffectiveArea = 0.0;
  if(fabs(eta) >= 0.0   && fabs(eta) < 1.0   ) EffectiveArea = 0.0;
  if(fabs(eta) >= 1.0   && fabs(eta) < 1.479 ) EffectiveArea = 0.0;
  if(fabs(eta) >= 1.479 && fabs(eta) < 2.0   ) EffectiveArea = 0.0;
  if(fabs(eta) >= 2.0   && fabs(eta) < 2.2   ) EffectiveArea = 0.0;
  if(fabs(eta) >= 2.2   && fabs(eta) < 2.3   ) EffectiveArea = 0.0;
  if(fabs(eta) >= 2.3   && fabs(eta) < 2.4   ) EffectiveArea = 0.0;
  if(fabs(eta) >= 2.4                        ) EffectiveArea = 0.0;

  return EffectiveArea;
}

Double_t analyzer_signal::EAneutral(Double_t eta){
  Float_t EffectiveArea = 0.;
  if(fabs(eta) >= 0.0   && fabs(eta) < 1.0   ) EffectiveArea = 0.0599;
  if(fabs(eta) >= 1.0   && fabs(eta) < 1.479 ) EffectiveArea = 0.0819;
  if(fabs(eta) >= 1.479 && fabs(eta) < 2.0   ) EffectiveArea = 0.0696;
  if(fabs(eta) >= 2.0   && fabs(eta) < 2.2   ) EffectiveArea = 0.0360;
  if(fabs(eta) >= 2.2   && fabs(eta) < 2.3   ) EffectiveArea = 0.0360;
  if(fabs(eta) >= 2.3   && fabs(eta) < 2.4   ) EffectiveArea = 0.0462;
  if(fabs(eta) >= 2.4                        ) EffectiveArea = 0.0656;

  return EffectiveArea;
}

Double_t analyzer_signal::EAphoton(Double_t eta){
  Float_t EffectiveArea = 0.;
  if(fabs(eta) >= 0.0   && fabs(eta) < 1.0   ) EffectiveArea = 0.1271;
  if(fabs(eta) >= 1.0   && fabs(eta) < 1.479 ) EffectiveArea = 0.1101;
  if(fabs(eta) >= 1.479 && fabs(eta) < 2.0   ) EffectiveArea = 0.0756;
  if(fabs(eta) >= 2.0   && fabs(eta) < 2.2   ) EffectiveArea = 0.1175;
  if(fabs(eta) >= 2.2   && fabs(eta) < 2.3   ) EffectiveArea = 0.1498;
  if(fabs(eta) >= 2.3   && fabs(eta) < 2.4   ) EffectiveArea = 0.1857;
  if(fabs(eta) >= 2.4                        ) EffectiveArea = 0.2183;

  return EffectiveArea;
}




 //-------------------------makeDilep
 void analyzer_signal::makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_ee, TLorentzVector *fv_mm, bool *passMM)
 {          
                                                                     
   TLorentzVector e1, e2, ee;                                        
   TLorentzVector m1, m2, mm;                                        
   e1.SetPtEtaPhiE( 0,0,0,0 );                                       
   e2.SetPtEtaPhiE( 0,0,0,0 );                                       
   m1.SetPtEtaPhiE( 0,0,0,0 );                                       
   m2.SetPtEtaPhiE( 0,0,0,0 );                                       
                                                                     
    // no pairs                                                    
    if( electron_list.size()<2 && muon_list.size()<2 ){return;}             
                                                                   
     // electrons                                                      
     if( electron_list.size()>1 ){                                           
      for(int i=1; i<electron_list.size(); ++i)                              
      {                                                                
       if( eleCharge->at(0)*eleCharge->at(i)==-1 )                     
       {                                                               
        //printf(" --we have electrons ");                             
        e1.SetPtEtaPhiE( elePt->at(electron_list[0]), eleEta->at(electron_list[0]), elePhi->at(electron_list[0]), eleEn->at(electron_list[0]) );  
        e2.SetPtEtaPhiE( elePt->at(electron_list[i]), eleEta->at(electron_list[i]), elePhi->at(electron_list[i]), eleEn->at(electron_list[i]) );  
        break;   
       }         
      }          
     }           
     //printf(": diele mass = %f", ee.M());  
     ee = e1 + e2;                           
                                             
     // muons                                
     if( muon_list.size()>1 ){                  
      for(int i=1; i<muon_list.size(); ++i)     
      {                                           
        if( muCharge->at(0)*muCharge->at(i)==-1 ) 
        {                                         
         //printf(" --we have muons ");           
         m1.SetPtEtaPhiE( muPt->at(muon_list[0]), muEta->at(muon_list[0]), muPhi->at(muon_list[0]), muEn->at(muon_list[0]) );             
         //printf(": charge pass ");    
         m2.SetPtEtaPhiE( muPt->at(muon_list[i]), muEta->at(muon_list[i]), muPhi->at(muon_list[i]), muEn->at(muon_list[i]) );             
         break;                                                                                           
        } 
      }   
     }    
     //printf(": dimu mass = %f", mm.M());  
     mm = m1 + m2; 
                   
     *fv_ee = ee;  
     *fv_mm = mm;  
     // take highest mass dilepton pair 
     if( mm.M()>ee.M() ){ *fv_1 = m1; *fv_2 = m2; *passMM = true; } 
     else               { *fv_1 = e1; *fv_2 = e2; *passMM = false; }
   return;                                                          
                                                                    
 } 


void analyzer_signal::debug_printobjects(){

  printf("\n Event %lld\n", event);
  printf(" Pass ossf %d zwind %d ptg50 %d 1jet %d vtx %d \n", passOSSF, passZWindow, passPTOSSFg50, passOneJet, passGoodVtx);
  if(dilep_mass>0.){printf(" Dilep Found\n");}
  for(int i=0; i<photon_list.size(); ++i){
   int phoindex = photon_list[i];
   printf( " photon %d : pt %.1f eta %.1f phi %.1f\n", i, phoEt->at(phoindex), phoEta->at(phoindex), phoPhi->at(phoindex));
  }

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   printf( " electron %d : pt %.1f eta %.1f phi %.1f\n", i, elePt->at(eleindex), eleEta->at(eleindex), elePhi->at(eleindex));
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   printf( " muon %d : pt %.1f eta %.1f phi %.1f\n", i, muPt->at(muindex), muEta->at(muindex), muPhi->at(muindex));
  }

  printf(" Pass SingleEle: %d SingleMu: %d\n", passSingleEle, passSingleMu);

  if(dilep_mass>0.){
   printf("  l1 pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
     fourVec_l1.Pt(), fourVec_l1.Eta(), fourVec_l1.Phi(), fourVec_l1.M() );
   printf("  l2 pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
     fourVec_l2.Pt(), fourVec_l2.Eta(), fourVec_l2.Phi(), fourVec_l2.M() );
   printf("  ll pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
      fourVec_ll.Pt(), fourVec_ll.Eta(), fourVec_ll.Phi(), fourVec_ll.M() );
  }

  for(int i=0; i<jet_list.size(); ++i){
   int jetindex = jet_list[i];
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, jetPt->at(jetindex), jetEta->at(jetindex), jetPhi->at(jetindex));
  } 

  printf( " met %.1f mephi %.1f\n", themet, themephi);
  printf( " nvtx %d \n", nVtx);
  printf( " htall %.1f htjets %.1f\n", htall, htjets);

 }
