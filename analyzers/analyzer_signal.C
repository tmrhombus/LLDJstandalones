#define analyzer_signal_cxx
#include "analyzer_signal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void analyzer_signal::Loop(TString outfilename, 
                       Double_t lumi, Double_t nrEvents,
                       Double_t crossSec, Int_t nevts, TFile *optfile)
{

 if(makelog){
  logfile = fopen( outfilename+".txt", "w"); 
 }

 if (fChain == 0) return;

 Long64_t nentries = fChain->GetEntriesFast();
 if(nevts>0){ 
  nentries = Long64_t(nevts);
 }
 
 nmatched   = 0;
 nunmatched = 0;

 jetmatchdRcut = 0.4;
 objcleandRcut = 0.4;

 n_tot   = 0;
 n_test  = 0;
 n_test2 = 0; 

 n_passSig    = 0;
 n_passZH     = 0;
 n_passDY     = 0;
 n_passOffZ   = 0;
 n_passNoPair = 0;

 n_ele_passSig    = 0;
 n_ele_passZH     = 0;
 n_ele_passDY     = 0;
 n_ele_passOffZ   = 0;
 n_ele_passNoPair = 0;

 n_mu_passSig    = 0;
 n_mu_passZH     = 0;
 n_mu_passDY     = 0;
 n_mu_passOffZ   = 0;
 n_mu_passNoPair = 0;

 // set which collections
 phoid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 eleid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 muoid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 jetid = "Loose"; // "Tight"; "Loose";

 if (phoid = "Loose")  phoidbit=0;
 if (phoid = "Medium") phoidbit=1;
 if (phoid = "Tight")  phoidbit=2;

 if (eleid = "Loose")  eleidbit=1;
 if (eleid = "Medium") eleidbit=2;
 if (eleid = "Tight")  eleidbit=3;

 if (muoid = "Loose")  muoidbit=0;
 if (muoid = "Medium") muoidbit=1;
 if (muoid = "Tight")  muoidbit=2;

 if (jetid = "Loose")  aodcalojetidbit=0;
 if (jetid = "Tight")  aodcalojetidbit=1;

 if(isMC) loadPUWeight();
 if(isMC) loadElectronWeight();

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {

  // clear counters for event variables
  nSelectedPho=0;
  nSelectedEle=0;
  nSelectedMuo=0;
  //nSelectedSlimmedJet=0;
  nSelectedAODCaloJet=0;
 
  //clear optimization arrays each new event
  OPT_Event                           .clear();
  OPT_EventWeight                     .clear();
  OPT_AODCaloJetMedianLog10IPSig      .clear();
  OPT_AODCaloJetMedianLog10TrackAngle .clear();
  OPT_AODCaloJetAlphaMax              .clear();

  //printf(" Event %lld\n", event);
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ printf(" entry %lli\n",jentry); }

  n_tot++;

  // get lists of "good" electrons, photons, jets
  // idbit, pt, eta, sysbinname
  photon_list     = photon_passID    ( phoidbit,        30, 1.4442, ""); 
  electron_list   = electron_passID  ( eleidbit,        30, 2.1,    "");
  muon_list       = muon_passID      ( muoidbit,        30, 2.1,    ""); 
  aodcalojet_list = aodcalojet_passID( aodcalojetidbit, 25, 2.4,    ""); 

  // make event weight in analyzerBase.C
  // colisions happen @LHC at a given rate, use event_weight
  // to make the simulation match the rate seen in data
  // = lum * cross-section / nrEvents generated
  event_weight = makeEventWeight(crossSec,lumi,nrEvents);
  //std::cout<<event_weight<<std::endl;
  // for MC, simulated pileup is different from observed
  // in commontools/pileup we make a ratio for scaling MC
  //if(isMC) event_weight *= makePUWeight();<-----need nTruePU
  // electrons also have an associated scale factor for MC 
  if(isMC) event_weight *= makeElectronWeight();

  tagger();
  
  // set our met
  //themet = AOD_pfMET;
  themephi = AOD_pfMET_phi;
  // AOD_pfMET_T1JERUp;   //!
  // AOD_pfMET_T1JERDo;   //!
  // AOD_pfMET_T1JESUp;   //!
  // AOD_pfMET_T1JESDo;   //!
  // AOD_pfMET_T1MESUp;   //!
  // AOD_pfMET_T1MESDo;   //!
  // AOD_pfMET_T1EESUp;   //!
  // AOD_pfMET_T1EESDo;   //!
  // AOD_pfMET_T1PESUp;   //!
  // AOD_pfMET_T1PESDo;   //!
  // AOD_pfMET_T1TESUp;   //!
  // AOD_pfMET_T1TESDo;   //!
  // AOD_pfMET_T1UESUp;   //!
  // AOD_pfMET_T1UESDo;   //!

  // calculate ht
  htall  = 0.;
  htaodcalojets = 0.;

  for(int i=0; i<photon_list.size(); ++i){
   int phoindex = photon_list[i];
   htall += AOD_phoPt->at(phoindex);
  }

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   htall += AOD_elePt->at(eleindex);
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   htall += AOD_muPt->at(muindex);
  }

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int aodcalojetindex = aodcalojet_list[i];
   htall  += AODCaloJetPt->at(aodcalojetindex);
   htaodcalojets += AODCaloJetPt->at(aodcalojetindex);
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

  //passGoodVtx = nVtx>0;
  
  passSingleEle = askPassSingleEle();
  passSingleMu  = askPassSingleMu();
  passDoubleEle = askPassDoubleEle();
  passDoubleMu  = askPassDoubleMu();


  //if( passZWindow && !(passDoubleEle||passDoubleMu||passSingleEle||passSingleMu) ){
  // debug_printobjects();   // helpful printout (turn off when submitting!!!)
  // debug_printmuons();     // helpful printout (turn off when submitting!!!)
  // debug_printelectrons(); // helpful printout (turn off when submitting!!!)
  // debug_printtriggers();
  //}

   
  // set booleans if pass various selections
  doesPassSig    = askPassSig   ();
  doesPassZH     = askPassZH    ();
  doesPassDY     = askPassDY    ();
  doesPassOffZ   = askPassOffZ  ();
  doesPassNoPair = askPassNoPair();

  // fill histogram

  //if( passSingleEle ){
  if( passSingleEle || passDoubleEle ){
                        fillBasicHistograms(event_weight,0,0);  /* fillSlimmedJetHistograms(event_weight,0,0);*/ fillAODCaloJetHistograms(event_weight,0,0);  
   if( doesPassSig   ){ fillBasicHistograms(event_weight,1,0); /* fillSlimmedJetHistograms(event_weight,1,0);*/ fillAODCaloJetHistograms(event_weight,1,0); }
   if( doesPassZH    ){ fillBasicHistograms(event_weight,2,0); /* fillSlimmedJetHistograms(event_weight,2,0);*/ fillAODCaloJetHistograms(event_weight,2,0); }
   if( doesPassDY    ){ fillBasicHistograms(event_weight,3,0); /* fillSlimmedJetHistograms(event_weight,3,0);*/ fillAODCaloJetHistograms(event_weight,3,0); }
   if( doesPassOffZ  ){ fillBasicHistograms(event_weight,4,0); /* fillSlimmedJetHistograms(event_weight,4,0);*/ fillAODCaloJetHistograms(event_weight,4,0); }
   if( doesPassNoPair){ fillBasicHistograms(event_weight,5,0); /* fillSlimmedJetHistograms(event_weight,5,0);*/ fillAODCaloJetHistograms(event_weight,5,0); }
  }

  //if( passSingleMu ){
  if( passSingleMu || passDoubleMu ){
                        fillBasicHistograms(event_weight,0,1);  /* fillSlimmedJetHistograms(event_weight,0,1);*/ fillAODCaloJetHistograms(event_weight,0,1);  
   if( doesPassSig   ){ fillBasicHistograms(event_weight,1,1); /* fillSlimmedJetHistograms(event_weight,1,1);*/ fillAODCaloJetHistograms(event_weight,1,1); }
   if( doesPassZH    ){ fillBasicHistograms(event_weight,2,1); /* fillSlimmedJetHistograms(event_weight,2,1);*/ fillAODCaloJetHistograms(event_weight,2,1); }
   if( doesPassDY    ){ fillBasicHistograms(event_weight,3,1); /* fillSlimmedJetHistograms(event_weight,3,1);*/ fillAODCaloJetHistograms(event_weight,3,1); }
   if( doesPassOffZ  ){ fillBasicHistograms(event_weight,4,1); /* fillSlimmedJetHistograms(event_weight,4,1);*/ fillAODCaloJetHistograms(event_weight,4,1); }
   if( doesPassNoPair){ fillBasicHistograms(event_weight,5,1); /* fillSlimmedJetHistograms(event_weight,5,1);*/ fillAODCaloJetHistograms(event_weight,5,1); }
  }
   
  //No Lep selection
                        fillBasicHistograms(event_weight,0,2);  /* fillSlimmedJetHistograms(event_weight,0,2);*/ fillAODCaloJetHistograms(event_weight,0,2);  
   if( doesPassSig   ){ fillBasicHistograms(event_weight,1,2); /* fillSlimmedJetHistograms(event_weight,1,2);*/ fillAODCaloJetHistograms(event_weight,1,2); }
   if( doesPassZH    ){ fillBasicHistograms(event_weight,2,2); /* fillSlimmedJetHistograms(event_weight,2,2);*/ fillAODCaloJetHistograms(event_weight,2,2); }
   if( doesPassDY    ){ fillBasicHistograms(event_weight,3,2); /* fillSlimmedJetHistograms(event_weight,3,2);*/ fillAODCaloJetHistograms(event_weight,3,2); }
   if( doesPassOffZ  ){ fillBasicHistograms(event_weight,4,2); /* fillSlimmedJetHistograms(event_weight,4,2);*/ fillAODCaloJetHistograms(event_weight,4,2); }
   if( doesPassNoPair){ fillBasicHistograms(event_weight,5,2); /* fillSlimmedJetHistograms(event_weight,5,2);*/ fillAODCaloJetHistograms(event_weight,5,2); }
  
  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);
  OPTtree->Fill();
 } // end loop over entries

 printf("\n\n Summary   dR=%0.1f\n",jetmatchdRcut);
 printf("  nmatched    %i\n",nmatched);
 printf("  nunmatched  %i\n",nunmatched);

 printf("  ntot        %i \n",n_tot        ); 
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
   writeBasicHistograms(i,k);
   //writeSlimmedJetHistograms(i,k);
   writeAODCaloJetHistograms(i,k);
   //write2DHistograms(i,k);
  }
 }
 outfile->Close();
 optfile->cd();
 OPTtree->Write();
 optfile->Close();

//std::cout<<"Total!=0: "<<n_test <<" Total ==0 "<<n_test2<<std::endl;
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
 
 // loop through jets and selections to initialize histograms in parllel (series)
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


// this should probably go somewhere better
void analyzer_signal::initSelectionCategories(){

  // initialize names
  jetmultnames.clear();
  jetmultnames.push_back("LeadingJet");
  jetmultnames.push_back("SubleadingJet");
  jetmultnames.push_back("ThirdJet");
  jetmultnames.push_back("FourthJet");
  jetmultnames.push_back("AllJets");

  lepnames.clear();
  lepnames.push_back("ele");
  lepnames.push_back("mu");
  lepnames.push_back("NoLepSel");

  selbinnames.clear();
  selbinnames.push_back("NoSel");
  selbinnames.push_back("Sig");
  selbinnames.push_back("ZH");
  selbinnames.push_back("DY");
  selbinnames.push_back("OffZ");
  selbinnames.push_back("NoPair");

}

//----------------------------initBasicHistograms
Bool_t analyzer_signal::initBasicHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){

   // initialize names
   //TString hname_nVtx                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nVtx        "; 
   //TString hname_nGoodVtx                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nGoodVtx    "; 
   //TString hname_nTrksPV                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nTrksPV     "; 
   //TString hname_isPVGood                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_isPVGood    "; 
   //TString hname_rho                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_rho         "; 
   //TString hname_rhoCentral               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_rhoCentral  "; 
   //TString hname_nTruePU                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nTruePU     "; 
   //TString hname_AOD_pfMET                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_pfMET       "; 
   TString hname_AOD_pfMET_phi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_pfMET_phi    "; 
   TString hname_AOD_pfMET_pt                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_pfMET_pt    "; 
   //TString hname_AOD_pfMETsumEt              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_pfMETsumEt  "; 

   TString hname_nAODPho                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nAODPho        "; 
   TString hname_AOD_phoEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoEn       "; 
   TString hname_AOD_phoPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoPt       "; 
   TString hname_AOD_phoEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoEta      "; 
   TString hname_AOD_phoPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoPhi      "; 
   TString hname_AOD_phoSCEn                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoSCEn     "; 
   TString hname_AOD_phoSCPhi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoSCPhi    "; 
   TString hname_AOD_phoSCEta                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoSCEta    ";
   TString hname_AOD_phoIDbit                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoIDbit    ";

   TString hname_nAODEle                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nAODEle        "; 
   TString hname_AOD_elePt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_elePt       "; 
   TString hname_AOD_eleEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_eleEn       "; 
   TString hname_AOD_eleEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_eleEta      "; 
   TString hname_AOD_elePhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_elePhi      "; 
   TString hname_AOD_eleCharge                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_eleCharge   "; 
   //TString hname_AOD_eleSCEn                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCEn     "; 
   //TString hname_AOD_eleSCEta                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCEta    "; 
   //TString hname_AOD_eleSCPhi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCPhi    "; 
   //TString hname_AOD_elePFdBetaIsolationRhoEA = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationRhoEA"; 
   //TString hname_AOD_elePFdBetaIsolationCHS   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationCHS  "; 
   //TString hname_AOD_elePFdBetaIsolationDiff  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationDiff "; 
   TString hname_nAODMu                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nAODMu                "; 
   TString hname_AOD_muPt                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muPt               "; 
   TString hname_AOD_muEn                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muEn               "; 
   TString hname_AOD_muEta                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muEta              "; 
   TString hname_AOD_muPhi                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muPhi              "; 
   TString hname_AOD_muCharge                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muCharge           "; 
   TString hname_AOD_muPFdBetaIsolation       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muPFdBetaIsolation "; 
   TString hname_AOD_muDxy                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muDxy              "; 
   TString hname_AOD_muDxyErr                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muDxyErr           "; 

   TString hname_htall                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htall        " ;
   TString hname_htaodcalojets            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htaodcalojets" ;

   TString hname_nSelectedPho             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedPho";
   TString hname_nSelectedEle             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedEle";
   TString hname_nSelectedMuo             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedMuo";
   TString hname_nSelectedSlimmedJet      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedSlimmedJet";
   TString hname_nSelectedAODCaloJet      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedAODCaloJet";

   // initalize histograms
   //h_nVtx                     [i][k] = initSingleHistogramTH1F( hname_nVtx                    , "nVtx                   ", 60,0,60) ; 
   //h_nGoodVtx                 [i][k] = initSingleHistogramTH1F( hname_nGoodVtx                , "nGoodVtx               ", 60,0,60) ;  
   //h_nTrksPV                  [i][k] = initSingleHistogramTH1F( hname_nTrksPV                 , "nTrksPV                ", 60,0,60) ;  
   //h_isPVGood                 [i][k] = initSingleHistogramTH1F( hname_isPVGood                , "isPVGood               ", 2,0,1) ;  
   //h_rho                      [i][k] = initSingleHistogramTH1F( hname_rho                     , "rho                    ", 30, -3, 3); 
   //h_rhoCentral               [i][k] = initSingleHistogramTH1F( hname_rhoCentral              , "rhoCentral             ", 30, -3, 3); 
   //h_nTruePU                  [i][k] = initSingleHistogramTH1F( hname_nTruePU                 , "nTruePU                ", 60,0,60) ;  
   //h_AOD_pfMET                    [i][k] = initSingleHistogramTH1F( hname_AOD_pfMET                   , "AOD_pfMET                  ", 50, 0, 500) ;  
   h_AOD_pfMET_phi                  [i][k] = initSingleHistogramTH1F( hname_AOD_pfMET_phi               , "AOD_pfMET_phi              ", 30, -5, 5); 
   h_AOD_pfMET_pt                   [i][k] = initSingleHistogramTH1F( hname_AOD_pfMET_pt                , "AOD_pfMET_pt               ", 50, 0, 500); 
   //h_AOD_pfMETsumEt               [i][k] = initSingleHistogramTH1F( hname_AOD_pfMETsumEt              , "AOD_pfMETsumEt             ", 50, 0, 500)  ;

   h_AOD_phoEn                    [i][k] = initSingleHistogramTH1F( hname_AOD_phoEn                   , "AOD_phoEn                  ", 50, 0, 500) ;  
   h_AOD_phoPt                    [i][k] = initSingleHistogramTH1F( hname_AOD_phoPt                   , "AOD_phoPt                  ", 50, 0, 500) ;  
   h_AOD_phoEta                   [i][k] = initSingleHistogramTH1F( hname_AOD_phoEta                  , "AOD_phoEta                 ", 30, -5, 5); 
   h_AOD_phoPhi                   [i][k] = initSingleHistogramTH1F( hname_AOD_phoPhi                  , "AOD_phoPhi                 ", 30, -5, 5); 
   h_AOD_phoSCEn                  [i][k] = initSingleHistogramTH1F( hname_AOD_phoSCEn                 , "AOD_phoSCEn                ", 50, 0, 500) ;  
   h_AOD_phoSCPhi                 [i][k] = initSingleHistogramTH1F( hname_AOD_phoSCPhi                , "AOD_phoSCPhi               ", 30, -5, 5); 
   h_AOD_phoSCEta                 [i][k] = initSingleHistogramTH1F( hname_AOD_phoSCEta                , "AOD_phoSCEta               ", 30, -5, 5); 

   h_AOD_elePt                    [i][k] = initSingleHistogramTH1F( hname_AOD_elePt                   , "AOD_elePt                  ", 50, 0, 500) ;  
   h_AOD_eleEn                    [i][k] = initSingleHistogramTH1F( hname_AOD_eleEn                   , "AOD_eleEn                  ", 50, 0, 500) ;  
   h_AOD_eleEta                   [i][k] = initSingleHistogramTH1F( hname_AOD_eleEta                  , "AOD_eleEta                 ", 30, -5, 5); 
   h_AOD_elePhi                   [i][k] = initSingleHistogramTH1F( hname_AOD_elePhi                  , "AOD_elePhi                 ", 30, -5, 5); 
   h_AOD_eleCharge                [i][k] = initSingleHistogramTH1F( hname_AOD_eleCharge               , "AOD_eleCharge              ", 3, -1, 1); 
   //h_eleSCEn                  [i][k] = initSingleHistogramTH1F( hname_AOD_eleSCEn                 , "eleSCEn                ", 50, 0, 500) ;  
   //h_eleSCEta                 [i][k] = initSingleHistogramTH1F( hname_AOD_eleSCEta                , "eleSCEta               ", 30, -5, 5); 
   //h_eleSCPhi                 [i][k] = initSingleHistogramTH1F( hname_AOD_eleSCPhi                , "eleSCPhi               ", 30, -5, 5); 
   //h_elePFdBetaIsolationRhoEA [i][k] = initSingleHistogramTH1F( hname_AOD_elePFdBetaIsolationRhoEA, "elePFdBetaIsolationRhoEA", 30, 0, 1); 
   //h_elePFdBetaIsolationCHS   [i][k] = initSingleHistogramTH1F( hname_AOD_elePFdBetaIsolationCHS  , "elePFdBetaIsolationCHS  ", 30, 0, 1); 
   //h_elePFdBetaIsolationDiff  [i][k] = initSingleHistogramTH1F( hname_AOD_elePFdBetaIsolationDiff , "elePFdBetaIsolationDiff ", 30, 0, 1); 

   h_AOD_muPt                     [i][k] = initSingleHistogramTH1F( hname_AOD_muPt                    , "AOD_muPt                   ", 50, 0, 500) ;  
   h_AOD_muEn                     [i][k] = initSingleHistogramTH1F( hname_AOD_muEn                    , "AOD_muEn                   ", 50, 0, 500) ;  
   h_AOD_muEta                    [i][k] = initSingleHistogramTH1F( hname_AOD_muEta                   , "AOD_muEta                  ", 30, -5, 5); 
   h_AOD_muPhi                    [i][k] = initSingleHistogramTH1F( hname_AOD_muPhi                   , "AOD_muPhi                  ", 30, -5, 5); 
   h_AOD_muCharge                 [i][k] = initSingleHistogramTH1F( hname_AOD_muCharge                , "AOD_muCharge               ", 3, -1, 1); 
   h_AOD_muPFdBetaIsolation       [i][k] = initSingleHistogramTH1F( hname_AOD_muPFdBetaIsolation      , "AOD_muPFdBetaIsolation     ", 30, -5, 5); 
   h_AOD_muDxy                    [i][k] = initSingleHistogramTH1F( hname_AOD_muDxy                   , "AOD_muDxy                  ", 30, 0, 10); 
   h_AOD_muDxyErr                 [i][k] = initSingleHistogramTH1F( hname_AOD_muDxyErr                , "AOD_muDxyErr               ", 30, 0, 0.5); 

   h_htall                    [i][k] = initSingleHistogramTH1F( hname_htall               , "htall "             , 50,0,1000) ; 
   h_htaodcalojets            [i][k] = initSingleHistogramTH1F( hname_htaodcalojets       , "htaodcalojets"      , 50,0,1000) ; 
   h_nSelectedPho             [i][k] = initSingleHistogramTH1F( hname_nSelectedPho        , "nSelectedPho"       , 10,0,10);
   h_nSelectedEle             [i][k] = initSingleHistogramTH1F( hname_nSelectedEle        , "nSelectedEle"       , 10,0,10);
   h_nSelectedMuo             [i][k] = initSingleHistogramTH1F( hname_nSelectedMuo        , "nSelectedMuo"       , 10,0,10);
   h_nSelectedSlimmedJet      [i][k] = initSingleHistogramTH1F( hname_nSelectedSlimmedJet , "nSelectedSlimmedJet", 10,0,10);
   h_nSelectedAODCaloJet      [i][k] = initSingleHistogramTH1F( hname_nSelectedAODCaloJet , "nSelectedAODCaloJet", 10,0,10);

  }
 }

 return kTRUE;
}

//----------------------------fillBasicHistograms
Bool_t analyzer_signal::fillBasicHistograms(Double_t weight, int selbin, int lepbin)
{

 // fill single values
 //h_nVtx                    [selbin][lepbin] .Fill( nVtx       , weight);  
 //h_nGoodVtx                [selbin][lepbin] .Fill( nGoodVtx   , weight);  
 //h_nTrksPV                 [selbin][lepbin] .Fill( nTrksPV    , weight);  
 //h_isPVGood                [selbin][lepbin] .Fill( isPVGood   , weight);  
 //h_rho                     [selbin][lepbin] .Fill( rho        , weight);  
 //h_rhoCentral              [selbin][lepbin] .Fill( rhoCentral , weight);  
 //h_nTruePU                 [selbin][lepbin] .Fill( nTruePU    , weight);  
 //h_AOD_pfMET                   [selbin][lepbin] .Fill( AOD_pfMET      , weight);  
 h_AOD_pfMET_phi                 [selbin][lepbin] .Fill( AOD_pfMET_phi   , weight);  
 h_AOD_pfMET_pt                  [selbin][lepbin] .Fill( AOD_pfMET_pt   , weight);  
 //h_AOD_pfMETsumEt              [selbin][lepbin] .Fill( AOD_pfMETsumEt , weight);  

 h_htall                   [selbin][lepbin] .Fill( htall              , weight); 
 h_htaodcalojets           [selbin][lepbin] .Fill( htaodcalojets      , weight); 
 h_nSelectedPho            [selbin][lepbin] .Fill( nSelectedPho       , weight);
 h_nSelectedEle            [selbin][lepbin] .Fill( nSelectedEle       , weight);
 h_nSelectedMuo            [selbin][lepbin] .Fill( nSelectedMuo       , weight);
 h_nSelectedSlimmedJet     [selbin][lepbin] .Fill( nSelectedSlimmedJet, weight);
 h_nSelectedAODCaloJet     [selbin][lepbin] .Fill( nSelectedAODCaloJet, weight);

 // fill leading photon in vector
 if(photon_list.size() > 0){
  int phoindex = photon_list[0];
  h_AOD_phoEn    [selbin][lepbin] .Fill( AOD_phoEn   ->at(phoindex), weight );  
  h_AOD_phoPt    [selbin][lepbin] .Fill( AOD_phoPt   ->at(phoindex), weight );  
  h_AOD_phoEta   [selbin][lepbin] .Fill( AOD_phoEta  ->at(phoindex), weight );  
  h_AOD_phoPhi   [selbin][lepbin] .Fill( AOD_phoPhi  ->at(phoindex), weight );  
  h_AOD_phoSCEn  [selbin][lepbin] .Fill( AOD_phoSCEn ->at(phoindex), weight );  
  h_AOD_phoSCPhi [selbin][lepbin] .Fill( AOD_phoSCPhi->at(phoindex), weight );  
  h_AOD_phoSCEta [selbin][lepbin] .Fill( AOD_phoSCEta->at(phoindex), weight );  
 }

 // fill leading electron in vector
 if(electron_list.size() > 0){
  int eleindex = electron_list[0];
  h_AOD_elePt                   [selbin][lepbin] .Fill( AOD_elePt                    ->at(eleindex), weight );
  h_AOD_eleEn                   [selbin][lepbin] .Fill( AOD_eleEn                    ->at(eleindex), weight );
  h_AOD_eleEta                  [selbin][lepbin] .Fill( AOD_eleEta                   ->at(eleindex), weight );
  h_AOD_elePhi                  [selbin][lepbin] .Fill( AOD_elePhi                   ->at(eleindex), weight );
  h_AOD_eleCharge               [selbin][lepbin] .Fill( AOD_eleCharge                ->at(eleindex), weight );
  //h_eleSCEn                 [selbin][lepbin] .Fill( eleSCEn                  ->at(eleindex), weight );
  //h_eleSCEta                [selbin][lepbin] .Fill( eleSCEta                 ->at(eleindex), weight );
  //h_eleSCPhi                [selbin][lepbin] .Fill( eleSCPhi                 ->at(eleindex), weight );
  //h_elePFdBetaIsolationRhoEA[selbin][lepbin] .Fill( elePFdBetaIsolationRhoEA ->at(eleindex), weight ); 
  //h_elePFdBetaIsolationCHS  [selbin][lepbin] .Fill( elePFdBetaIsolationCHS   ->at(eleindex), weight ); 
  //h_elePFdBetaIsolationDiff [selbin][lepbin] .Fill( elePFdBetaIsolationDiff  ->at(eleindex), weight ); 
 }

 // fill leading muon in vector
 if(muon_list.size() > 0){
  int muindex = muon_list[0];
  h_AOD_muPt               [selbin][lepbin] .Fill( AOD_muPt               ->at(muindex), weight );  
  h_AOD_muEn               [selbin][lepbin] .Fill( AOD_muEn               ->at(muindex), weight );  
  h_AOD_muEta              [selbin][lepbin] .Fill( AOD_muEta              ->at(muindex), weight );  
  h_AOD_muPhi              [selbin][lepbin] .Fill( AOD_muPhi              ->at(muindex), weight );  
  h_AOD_muCharge           [selbin][lepbin] .Fill( AOD_muCharge           ->at(muindex), weight );  
  h_AOD_muPFdBetaIsolation [selbin][lepbin] .Fill( AOD_muPFdBetaIsolation ->at(muindex), weight );  
  h_AOD_muDxy              [selbin][lepbin] .Fill( AOD_muDxy              ->at(muindex), weight );  
  h_AOD_muDxyErr           [selbin][lepbin] .Fill( AOD_muDxyErr           ->at(muindex), weight );  
 }

 return kTRUE;
}

//----------------------------writeBasicHistograms
Bool_t analyzer_signal::writeBasicHistograms(int selbin, int lepbin)
{
 //h_nVtx                    [selbin][lepbin] .Write(); 
 //h_nGoodVtx                [selbin][lepbin] .Write(); 
 //h_nTrksPV                 [selbin][lepbin] .Write(); 
 //h_isPVGood                [selbin][lepbin] .Write(); 
 //h_rho                     [selbin][lepbin] .Write(); 
 //h_rhoCentral              [selbin][lepbin] .Write(); 
 //h_nTruePU                 [selbin][lepbin] .Write(); 
 //h_AOD_pfMET                   [selbin][lepbin] .Write(); 
 h_AOD_pfMET_phi                 [selbin][lepbin] .Write(); 
 h_AOD_pfMET_pt                  [selbin][lepbin] .Write(); 
 //h_AOD_pfMETsumEt              [selbin][lepbin] .Write(); 

 h_htall                   [selbin][lepbin] .Write(); 
 h_htaodcalojets           [selbin][lepbin] .Write(); 
 h_nSelectedPho            [selbin][lepbin] .Write(); 
 h_nSelectedEle            [selbin][lepbin] .Write(); 
 h_nSelectedMuo            [selbin][lepbin] .Write(); 
 h_nSelectedSlimmedJet     [selbin][lepbin] .Write(); 
 h_nSelectedAODCaloJet     [selbin][lepbin] .Write(); 

 h_AOD_phoEn                   [selbin][lepbin] .Write(); 
 h_AOD_phoPt                   [selbin][lepbin] .Write(); 
 h_AOD_phoEta                  [selbin][lepbin] .Write(); 
 h_AOD_phoPhi                  [selbin][lepbin] .Write(); 
 h_AOD_phoSCEn                 [selbin][lepbin] .Write(); 
 h_AOD_phoSCPhi                [selbin][lepbin] .Write(); 
 h_AOD_phoSCEta                [selbin][lepbin] .Write(); 

 h_AOD_elePt                   [selbin][lepbin] .Write(); 
 h_AOD_eleEn                   [selbin][lepbin] .Write(); 
 h_AOD_eleEta                  [selbin][lepbin] .Write(); 
 h_AOD_elePhi                  [selbin][lepbin] .Write(); 
 h_AOD_eleCharge               [selbin][lepbin] .Write(); 
 //h_eleSCEn                 [selbin][lepbin] .Write(); 
 //h_eleSCEta                [selbin][lepbin] .Write(); 
 //h_eleSCPhi                [selbin][lepbin] .Write(); 
 //h_elePFdBetaIsolationRhoEA[selbin][lepbin] .Write(); 
 //h_elePFdBetaIsolationCHS  [selbin][lepbin] .Write(); 
 //h_elePFdBetaIsolationDiff [selbin][lepbin] .Write(); 

 h_AOD_muPt                    [selbin][lepbin] .Write(); 
 h_AOD_muEn                    [selbin][lepbin] .Write(); 
 h_AOD_muEta                   [selbin][lepbin] .Write(); 
 h_AOD_muPhi                   [selbin][lepbin] .Write(); 
 h_AOD_muCharge                [selbin][lepbin] .Write(); 
 h_AOD_muPFdBetaIsolation      [selbin][lepbin] .Write(); 
 h_AOD_muDxy                   [selbin][lepbin] .Write(); 
 h_AOD_muDxyErr                [selbin][lepbin] .Write(); 

 return kTRUE;
}

//----------------------------initAODCaloJetHistograms
Bool_t analyzer_signal::initAODCaloJetHistograms()
{

 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int j=0; j<jetmultnames.size(); ++j){
   for(unsigned int k=0; k<lepnames.size(); ++k){

    TString hname_AODCaloJetPt                            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetPt";                             
    TString hname_AODCaloJetEta                           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetEta";                            
    TString hname_AODCaloJetPhi                           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetPhi";                            
    TString hname_AODCaloJetAlphaMax                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMax";                       
    TString hname_AODCaloJetAlphaMax2                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMax2";                      
    TString hname_AODCaloJetAlphaMaxPrime                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMaxPrime";                  
    TString hname_AODCaloJetAlphaMaxPrime2                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMaxPrime2";                 
    TString hname_AODCaloJetBeta                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetBeta";                           
    TString hname_AODCaloJetBeta2                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetBeta2";                          
    TString hname_AODCaloJetSumIP                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetSumIP";                          
    TString hname_AODCaloJetSumIPSig                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetSumIPSig";                       
    TString hname_AODCaloJetMedianIP                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetMedianIP";                       
    TString hname_AODCaloJetMedianLog10IPSig              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetMedianLog10IPSig";               
    TString hname_AODCaloJetTrackAngle                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetTrackAngle";                     
    TString hname_AODCaloJetLogTrackAngle                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetLogTrackAngle";                  
    TString hname_AODCaloJetMedianLog10TrackAngle         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetMedianLog10TrackAngle";          
    TString hname_AODCaloJetTotalTrackAngle               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetTotalTrackAngle";                
    TString hname_AODCaloJetAvfVx                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVx";                          
    TString hname_AODCaloJetAvfVy                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVy";                          
    TString hname_AODCaloJetAvfVz                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVz";                          
    TString hname_AODCaloJetAvfVertexTotalChiSquared      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTotalChiSquared";       
    TString hname_AODCaloJetAvfVertexDegreesOfFreedom     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDegreesOfFreedom";      
    TString hname_AODCaloJetAvfVertexChi2NDoF             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexChi2NDoF";              
    TString hname_AODCaloJetAvfVertexDistanceToBeam       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDistanceToBeam";        
    TString hname_AODCaloJetAvfVertexTransverseError      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTransverseError";       
    TString hname_AODCaloJetAvfVertexTransverseSig        = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTransverseSig";         
    TString hname_AODCaloJetAvfVertexDeltaEta             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaEta";              
    TString hname_AODCaloJetAvfVertexDeltaPhi             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaPhi";              
    TString hname_AODCaloJetAvfVertexRecoilPt             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexRecoilPt";              
    TString hname_AODCaloJetAvfVertexTrackMass            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTrackMass";             
    TString hname_AODCaloJetAvfVertexTrackEnergy          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTrackEnergy";           
    TString hname_AODCaloJetAvfBeamSpotDeltaPhi           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotDeltaPhi";            
    TString hname_AODCaloJetAvfBeamSpotRecoilPt           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotRecoilPt";            
    TString hname_AODCaloJetAvfBeamSpotMedianDeltaPhi     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotMedianDeltaPhi";      
    TString hname_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi= "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi"; 
    TString hname_AODCaloJetNCleanMatchedTracks           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetNCleanMatchedTracks";            
    TString hname_AODCaloJetSumHitsInFrontOfVert          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetSumHitsInFrontOfVert";           
    TString hname_AODCaloJetSumMissHitsAfterVert          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetSumMissHitsAfterVert";           
    TString hname_AODCaloJetHitsInFrontOfVertPerTrack     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetHitsInFrontOfVertPerTrack";      
    TString hname_AODCaloJetMissHitsAfterVertPerTrack     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetMissHitsAfterVertPerTrack";      
    TString hname_AODCaloJetAvfDistToPV                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfDistToPV";                    
    TString hname_AODCaloJetAvfVertexDeltaZtoPV           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaZtoPV";            
    TString hname_AODCaloJetAvfVertexDeltaZtoPV2          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaZtoPV2";           

    h_AODCaloJetPt                             [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetPt                             , "AODCaloJetPt                            ", 50,0,500  ); 
    h_AODCaloJetEta                            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetEta                            , "AODCaloJetEta                           ", 30,-5,5   ); 
    h_AODCaloJetPhi                            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetPhi                            , "AODCaloJetPhi                           ", 30,-5,5   ); 
    h_AODCaloJetAlphaMax                       [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax                       , "AODCaloJetAlphaMax                      ", 30, 0, 1  ); 
    h_AODCaloJetAlphaMax2                      [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax2                      , "AODCaloJetAlphaMax2                     ", 30, 0, 1  ); 
    h_AODCaloJetAlphaMaxPrime                  [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime                  , "AODCaloJetAlphaMaxPrime                 ", 30, 0, 1  ); 
    h_AODCaloJetAlphaMaxPrime2                 [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime2                 , "AODCaloJetAlphaMaxPrime2                ", 30, 0, 1  ); 
    h_AODCaloJetBeta                           [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetBeta                           , "AODCaloJetBeta                          ", 30, 0, 1  ); 
    h_AODCaloJetBeta2                          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetBeta2                          , "AODCaloJetBeta2                         ", 30, 0, 1  ); 
    h_AODCaloJetSumIP                          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetSumIP                          , "AODCaloJetSumIP                         ", 30, -3, 3 ); 
    h_AODCaloJetSumIPSig                       [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetSumIPSig                       , "AODCaloJetSumIPSig                      ", 30, -3, 3 ); 
    h_AODCaloJetMedianIP                       [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianIP                       , "AODCaloJetMedianIP                      ", 30, -3, 3 ); 
    h_AODCaloJetMedianLog10IPSig               [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10IPSig               , "AODCaloJetMedianLog10IPSig              ", 30, -3, 3 ); 
    h_AODCaloJetTrackAngle                     [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetTrackAngle                     , "AODCaloJetTrackAngle                    ", 30, -3, 3 ); 
    h_AODCaloJetLogTrackAngle                  [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetLogTrackAngle                  , "AODCaloJetLogTrackAngle                 ", 30, -3, 3 ); 
    h_AODCaloJetMedianLog10TrackAngle          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10TrackAngle          , "AODCaloJetMedianLog10TrackAngle         ", 30, -5, 1 ); 
    h_AODCaloJetTotalTrackAngle                [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetTotalTrackAngle                , "AODCaloJetTotalTrackAngle               ", 30, -3, 3 ); 
    h_AODCaloJetAvfVx                          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVx                          , "AODCaloJetAvfVx                         ", 30, -3, 3 ); 
    h_AODCaloJetAvfVy                          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVy                          , "AODCaloJetAvfVy                         ", 30, -3, 3 ); 
    h_AODCaloJetAvfVz                          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVz                          , "AODCaloJetAvfVz                         ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTotalChiSquared       [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTotalChiSquared       , "AODCaloJetAvfVertexTotalChiSquared      ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDegreesOfFreedom      [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDegreesOfFreedom      , "AODCaloJetAvfVertexDegreesOfFreedom     ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexChi2NDoF              [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexChi2NDoF              , "AODCaloJetAvfVertexChi2NDoF             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDistanceToBeam        [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDistanceToBeam        , "AODCaloJetAvfVertexDistanceToBeam       ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTransverseError       [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTransverseError       , "AODCaloJetAvfVertexTransverseError      ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTransverseSig         [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTransverseSig         , "AODCaloJetAvfVertexTransverseSig        ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaEta              [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaEta              , "AODCaloJetAvfVertexDeltaEta             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaPhi              [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaPhi              , "AODCaloJetAvfVertexDeltaPhi             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexRecoilPt              [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexRecoilPt              , "AODCaloJetAvfVertexRecoilPt             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTrackMass             [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTrackMass             , "AODCaloJetAvfVertexTrackMass            ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTrackEnergy           [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTrackEnergy           , "AODCaloJetAvfVertexTrackEnergy          ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotDeltaPhi            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotDeltaPhi            , "AODCaloJetAvfBeamSpotDeltaPhi           ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotRecoilPt            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotRecoilPt            , "AODCaloJetAvfBeamSpotRecoilPt           ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotMedianDeltaPhi      , "AODCaloJetAvfBeamSpotMedianDeltaPhi     ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi , "AODCaloJetAvfBeamSpotLog10MedianDeltaPhi", 30, -3, 3 ); 
    h_AODCaloJetNCleanMatchedTracks            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetNCleanMatchedTracks            , "AODCaloJetNCleanMatchedTracks           ", 30, -3, 3 ); 
    h_AODCaloJetSumHitsInFrontOfVert           [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetSumHitsInFrontOfVert           , "AODCaloJetSumHitsInFrontOfVert          ", 30, -3, 3 ); 
    h_AODCaloJetSumMissHitsAfterVert           [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetSumMissHitsAfterVert           , "AODCaloJetSumMissHitsAfterVert          ", 30, -3, 3 ); 
    h_AODCaloJetHitsInFrontOfVertPerTrack      [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetHitsInFrontOfVertPerTrack      , "AODCaloJetHitsInFrontOfVertPerTrack     ", 30, -3, 3 ); 
    h_AODCaloJetMissHitsAfterVertPerTrack      [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetMissHitsAfterVertPerTrack      , "AODCaloJetMissHitsAfterVertPerTrack     ", 30, -3, 3 ); 
    h_AODCaloJetAvfDistToPV                    [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfDistToPV                    , "AODCaloJetAvfDistToPV                   ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaZtoPV            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaZtoPV            , "AODCaloJetAvfVertexDeltaZtoPV           ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaZtoPV2           [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaZtoPV2           , "AODCaloJetAvfVertexDeltaZtoPV2          ", 30, -3, 3 ); 

   } //   for(unsigned int i=0; i<selbinnames.size(); ++i){
  } //  for(unsigned int j=0; j<jetmultnames.size(); ++j){
 } // for(unsigned int k=0; k<lepnames.size(); ++k){

} //initAODCaloJetHistograms


//----------------------------fillAODCaloJetHistograms
Bool_t analyzer_signal::fillAODCaloJetHistograms(Double_t weight, int selbin, int lepbin)
{

// printf(" AODCaloJetPt                            %u\n",  AODCaloJetPt                            ->size() ); 
// printf(" AODCaloJetEta                           %u\n",  AODCaloJetEta                           ->size() ); 
// printf(" AODCaloJetPhi                           %u\n",  AODCaloJetPhi                           ->size() ); 
// printf(" AODCaloJetAlphaMax                      %u\n",  AODCaloJetAlphaMax                      ->size() ); 
// printf(" AODCaloJetAlphaMax2                     %u\n",  AODCaloJetAlphaMax2                     ->size() ); 
// printf(" AODCaloJetAlphaMaxPrime                 %u\n",  AODCaloJetAlphaMaxPrime                 ->size() ); 
// printf(" AODCaloJetAlphaMaxPrime2                %u\n",  AODCaloJetAlphaMaxPrime2                ->size() ); 
// printf(" AODCaloJetBeta                          %u\n",  AODCaloJetBeta                          ->size() ); 
// printf(" AODCaloJetBeta2                         %u\n",  AODCaloJetBeta2                         ->size() ); 
// printf(" AODCaloJetSumIP                         %u\n",  AODCaloJetSumIP                         ->size() ); 
// printf(" AODCaloJetSumIPSig                      %u\n",  AODCaloJetSumIPSig                      ->size() ); 
// printf(" AODCaloJetMedianIP                      %u\n",  AODCaloJetMedianIP                      ->size() ); 
// printf(" AODCaloJetMedianLog10IPSig              %u\n",  AODCaloJetMedianLog10IPSig              ->size() ); 
// printf(" AODCaloJetTrackAngle                    %u\n",  AODCaloJetTrackAngle                    ->size() ); 
// printf(" AODCaloJetLogTrackAngle                 %u\n",  AODCaloJetLogTrackAngle                 ->size() ); 
// printf(" AODCaloJetMedianLog10TrackAngle         %u\n",  AODCaloJetMedianLog10TrackAngle         ->size() ); 
// printf(" AODCaloJetTotalTrackAngle               %u\n",  AODCaloJetTotalTrackAngle               ->size() ); 
// printf(" AODCaloJetAvfVx                         %u\n",  AODCaloJetAvfVx                         ->size() ); 
// printf(" AODCaloJetAvfVy                         %u\n",  AODCaloJetAvfVy                         ->size() ); 
// printf(" AODCaloJetAvfVz                         %u\n",  AODCaloJetAvfVz                         ->size() ); 
// printf(" AODCaloJetAvfVertexTotalChiSquared      %u\n",  AODCaloJetAvfVertexTotalChiSquared      ->size() ); 
// printf(" AODCaloJetAvfVertexDegreesOfFreedom     %u\n",  AODCaloJetAvfVertexDegreesOfFreedom     ->size() ); 
// printf(" AODCaloJetAvfVertexChi2NDoF             %u\n",  AODCaloJetAvfVertexChi2NDoF             ->size() ); 
// printf(" AODCaloJetAvfVertexDistanceToBeam       %u\n",  AODCaloJetAvfVertexDistanceToBeam       ->size() ); 
// printf(" AODCaloJetAvfVertexTransverseError      %u\n",  AODCaloJetAvfVertexTransverseError      ->size() ); 
// printf(" AODCaloJetAvfVertexTransverseSig        %u\n",  AODCaloJetAvfVertexTransverseSig        ->size() ); 
// printf(" AODCaloJetAvfVertexDeltaEta             %u\n",  AODCaloJetAvfVertexDeltaEta             ->size() ); 
// printf(" AODCaloJetAvfVertexDeltaPhi             %u\n",  AODCaloJetAvfVertexDeltaPhi             ->size() ); 
// printf(" AODCaloJetAvfVertexRecoilPt             %u\n",  AODCaloJetAvfVertexRecoilPt             ->size() ); 
// printf(" AODCaloJetAvfVertexTrackMass            %u\n",  AODCaloJetAvfVertexTrackMass            ->size() ); 
// printf(" AODCaloJetAvfVertexTrackEnergy          %u\n",  AODCaloJetAvfVertexTrackEnergy          ->size() ); 
// printf(" AODCaloJetAvfBeamSpotDeltaPhi           %u\n",  AODCaloJetAvfBeamSpotDeltaPhi           ->size() ); 
// printf(" AODCaloJetAvfBeamSpotRecoilPt           %u\n",  AODCaloJetAvfBeamSpotRecoilPt           ->size() ); 
// printf(" AODCaloJetAvfBeamSpotMedianDeltaPhi     %u\n",  AODCaloJetAvfBeamSpotMedianDeltaPhi     ->size() ); 
// printf(" AODCaloJetAvfBeamSpotLog10MedianDeltaPhi%u\n",  AODCaloJetAvfBeamSpotLog10MedianDeltaPhi->size() ); 
// printf(" AODCaloJetNCleanMatchedTracks           %u\n",  AODCaloJetNCleanMatchedTracks           ->size() ); 
// printf(" AODCaloJetSumHitsInFrontOfVert          %u\n",  AODCaloJetSumHitsInFrontOfVert          ->size() ); 
// printf(" AODCaloJetSumMissHitsAfterVert          %u\n",  AODCaloJetSumMissHitsAfterVert          ->size() ); 
// printf(" AODCaloJetHitsInFrontOfVertPerTrack     %u\n",  AODCaloJetHitsInFrontOfVertPerTrack     ->size() ); 
// printf(" AODCaloJetMissHitsAfterVertPerTrack     %u\n",  AODCaloJetMissHitsAfterVertPerTrack     ->size() ); 
// printf(" AODCaloJetAvfDistToPV                   %u\n",  AODCaloJetAvfDistToPV                   ->size() ); 
// printf(" AODCaloJetAvfVertexDeltaZtoPV           %u\n",  AODCaloJetAvfVertexDeltaZtoPV           ->size() ); 
// printf(" AODCaloJetAvfVertexDeltaZtoPV2          %u\n",  AODCaloJetAvfVertexDeltaZtoPV2          ->size() ); 


 // i don't really like this hacky loop
 // idea is to have jets: 1,2,3,4,all
 // first fill individual jets
 for(unsigned int j=0; j<jetmultnames.size()-1; ++j){
  if( (int)aodcalojet_list.size()>j ){
   int aodcalojetindex = aodcalojet_list[j];
    h_AODCaloJetPt                             [selbin][j][lepbin].Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
    h_AODCaloJetEta                            [selbin][j][lepbin].Fill( AODCaloJetEta                            ->at( aodcalojetindex ), weight );  
    h_AODCaloJetPhi                            [selbin][j][lepbin].Fill( AODCaloJetPhi                            ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAlphaMax                       [selbin][j][lepbin].Fill( AODCaloJetAlphaMax                       ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAlphaMax2                      [selbin][j][lepbin].Fill( AODCaloJetAlphaMax2                      ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAlphaMaxPrime                  [selbin][j][lepbin].Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAlphaMaxPrime2                 [selbin][j][lepbin].Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojetindex ), weight );  
    h_AODCaloJetBeta                           [selbin][j][lepbin].Fill( AODCaloJetBeta                           ->at( aodcalojetindex ), weight );  
    h_AODCaloJetBeta2                          [selbin][j][lepbin].Fill( AODCaloJetBeta2                          ->at( aodcalojetindex ), weight );  
    h_AODCaloJetSumIP                          [selbin][j][lepbin].Fill( AODCaloJetSumIP                          ->at( aodcalojetindex ), weight );  
    h_AODCaloJetSumIPSig                       [selbin][j][lepbin].Fill( AODCaloJetSumIPSig                       ->at( aodcalojetindex ), weight );  
    h_AODCaloJetMedianIP                       [selbin][j][lepbin].Fill( AODCaloJetMedianIP                       ->at( aodcalojetindex ), weight );  
    h_AODCaloJetMedianLog10IPSig               [selbin][j][lepbin].Fill( AODCaloJetMedianLog10IPSig               ->at( aodcalojetindex ), weight );  
//    h_AODCaloJetTrackAngle                   [selbin][j][lepbin].Fill( AODCaloJetTrackAngle                     ->at( aodcalojetindex ), weight );  
//    h_AODCaloJetLogTrackAngle                [selbin][j][lepbin].Fill( AODCaloJetLogTrackAngle                  ->at( aodcalojetindex ), weight );  
    h_AODCaloJetMedianLog10TrackAngle          [selbin][j][lepbin].Fill( AODCaloJetMedianLog10TrackAngle          ->at( aodcalojetindex ), weight );  
    h_AODCaloJetTotalTrackAngle                [selbin][j][lepbin].Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVx                          [selbin][j][lepbin].Fill( AODCaloJetAvfVx                          ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVy                          [selbin][j][lepbin].Fill( AODCaloJetAvfVy                          ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVz                          [selbin][j][lepbin].Fill( AODCaloJetAvfVz                          ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexTotalChiSquared       [selbin][j][lepbin].Fill( AODCaloJetAvfVertexTotalChiSquared       ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][j][lepbin].Fill( AODCaloJetAvfVertexDegreesOfFreedom      ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexChi2NDoF              [selbin][j][lepbin].Fill( AODCaloJetAvfVertexChi2NDoF              ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexDistanceToBeam        [selbin][j][lepbin].Fill( AODCaloJetAvfVertexDistanceToBeam        ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexTransverseError       [selbin][j][lepbin].Fill( AODCaloJetAvfVertexTransverseError       ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexTransverseSig         [selbin][j][lepbin].Fill( AODCaloJetAvfVertexTransverseSig         ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexDeltaEta              [selbin][j][lepbin].Fill( AODCaloJetAvfVertexDeltaEta              ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexDeltaPhi              [selbin][j][lepbin].Fill( AODCaloJetAvfVertexDeltaPhi              ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexRecoilPt              [selbin][j][lepbin].Fill( AODCaloJetAvfVertexRecoilPt              ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexTrackMass             [selbin][j][lepbin].Fill( AODCaloJetAvfVertexTrackMass             ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexTrackEnergy           [selbin][j][lepbin].Fill( AODCaloJetAvfVertexTrackEnergy           ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][j][lepbin].Fill( AODCaloJetAvfBeamSpotDeltaPhi            ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][j][lepbin].Fill( AODCaloJetAvfBeamSpotRecoilPt            ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][j][lepbin].Fill( AODCaloJetAvfBeamSpotMedianDeltaPhi      ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][j][lepbin].Fill( AODCaloJetAvfBeamSpotLog10MedianDeltaPhi ->at( aodcalojetindex ), weight );  
    h_AODCaloJetNCleanMatchedTracks            [selbin][j][lepbin].Fill( AODCaloJetNCleanMatchedTracks            ->at( aodcalojetindex ), weight );  
    h_AODCaloJetSumHitsInFrontOfVert           [selbin][j][lepbin].Fill( AODCaloJetSumHitsInFrontOfVert           ->at( aodcalojetindex ), weight );  
    h_AODCaloJetSumMissHitsAfterVert           [selbin][j][lepbin].Fill( AODCaloJetSumMissHitsAfterVert           ->at( aodcalojetindex ), weight );  
    h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][j][lepbin].Fill( AODCaloJetHitsInFrontOfVertPerTrack      ->at( aodcalojetindex ), weight );  
    h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][j][lepbin].Fill( AODCaloJetMissHitsAfterVertPerTrack      ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfDistToPV                    [selbin][j][lepbin].Fill( AODCaloJetAvfDistToPV                    ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][j][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV            ->at( aodcalojetindex ), weight );  
    h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][j][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV2           ->at( aodcalojetindex ), weight );  

  } // if( aodcalojet_list.size()>j )
 } // for(unsigned int j=0; j<jetmultnames.size()-1; ++j){

 // now fill inclusive
 // this should work, and if it doesn't that's a clue we screwed up somewhere earlier
  int incjetbin = (int) jetmultnames.size();
 for(int i =0; i<(int)aodcalojet_list.size(); i++)
 { 
  int aodcalojetindex = aodcalojet_list[i];
  h_AODCaloJetPt                             [selbin][incjetbin][lepbin].Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
  h_AODCaloJetEta                            [selbin][incjetbin][lepbin].Fill( AODCaloJetEta                            ->at( aodcalojetindex ), weight );  
  h_AODCaloJetPhi                            [selbin][incjetbin][lepbin].Fill( AODCaloJetPhi                            ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAlphaMax                       [selbin][incjetbin][lepbin].Fill( AODCaloJetAlphaMax                       ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAlphaMax2                      [selbin][incjetbin][lepbin].Fill( AODCaloJetAlphaMax2                      ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAlphaMaxPrime                  [selbin][incjetbin][lepbin].Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAlphaMaxPrime2                 [selbin][incjetbin][lepbin].Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojetindex ), weight );  
  h_AODCaloJetBeta                           [selbin][incjetbin][lepbin].Fill( AODCaloJetBeta                           ->at( aodcalojetindex ), weight );  
  h_AODCaloJetBeta2                          [selbin][incjetbin][lepbin].Fill( AODCaloJetBeta2                          ->at( aodcalojetindex ), weight );  
  h_AODCaloJetSumIP                          [selbin][incjetbin][lepbin].Fill( AODCaloJetSumIP                          ->at( aodcalojetindex ), weight );  
  h_AODCaloJetSumIPSig                       [selbin][incjetbin][lepbin].Fill( AODCaloJetSumIPSig                       ->at( aodcalojetindex ), weight );  
  h_AODCaloJetMedianIP                       [selbin][incjetbin][lepbin].Fill( AODCaloJetMedianIP                       ->at( aodcalojetindex ), weight );  
  h_AODCaloJetMedianLog10IPSig               [selbin][incjetbin][lepbin].Fill( AODCaloJetMedianLog10IPSig               ->at( aodcalojetindex ), weight );  
//  h_AODCaloJetTrackAngle                     [selbin][incjetbin][lepbin].Fill( AODCaloJetTrackAngle                     ->at( aodcalojetindex ), weight );  
//  h_AODCaloJetLogTrackAngle                  [selbin][incjetbin][lepbin].Fill( AODCaloJetLogTrackAngle                  ->at( aodcalojetindex ), weight );  
  h_AODCaloJetMedianLog10TrackAngle          [selbin][incjetbin][lepbin].Fill( AODCaloJetMedianLog10TrackAngle          ->at( aodcalojetindex ), weight );  
  h_AODCaloJetTotalTrackAngle                [selbin][incjetbin][lepbin].Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVx                          [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVx                          ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVy                          [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVy                          ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVz                          [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVz                          ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexTotalChiSquared       [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexTotalChiSquared       ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexDegreesOfFreedom      ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexChi2NDoF              [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexChi2NDoF              ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexDistanceToBeam        [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexDistanceToBeam        ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexTransverseError       [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexTransverseError       ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexTransverseSig         [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexTransverseSig         ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexDeltaEta              [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaEta              ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexDeltaPhi              [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaPhi              ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexRecoilPt              [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexRecoilPt              ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexTrackMass             [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexTrackMass             ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexTrackEnergy           [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexTrackEnergy           ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfBeamSpotDeltaPhi            ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfBeamSpotRecoilPt            ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfBeamSpotMedianDeltaPhi      ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfBeamSpotLog10MedianDeltaPhi ->at( aodcalojetindex ), weight );  
  h_AODCaloJetNCleanMatchedTracks            [selbin][incjetbin][lepbin].Fill( AODCaloJetNCleanMatchedTracks            ->at( aodcalojetindex ), weight );  
  h_AODCaloJetSumHitsInFrontOfVert           [selbin][incjetbin][lepbin].Fill( AODCaloJetSumHitsInFrontOfVert           ->at( aodcalojetindex ), weight );  
  h_AODCaloJetSumMissHitsAfterVert           [selbin][incjetbin][lepbin].Fill( AODCaloJetSumMissHitsAfterVert           ->at( aodcalojetindex ), weight );  
  h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][incjetbin][lepbin].Fill( AODCaloJetHitsInFrontOfVertPerTrack      ->at( aodcalojetindex ), weight );  
  h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][incjetbin][lepbin].Fill( AODCaloJetMissHitsAfterVertPerTrack      ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfDistToPV                    [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfDistToPV                    ->at( aodcalojetindex ), weight );  
  h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV            ->at( aodcalojetindex ), weight );  
//h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][incjetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV2           ->at( aodcalojetindex ), weight );   // this vector isn't the same length I guess

 } //  for(unsigned int i =0; i<jet_list.size(); i++)

 return kTRUE;
} //end fill histograms


//----------------------------writeAODCaloJetHistograms
Bool_t analyzer_signal::writeAODCaloJetHistograms(int selbin, int lepbin)
{
 //printf("writeAODCaloJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){
  h_AODCaloJetPt                             [selbin][j][lepbin].Write(); 
  h_AODCaloJetEta                            [selbin][j][lepbin].Write(); 
  h_AODCaloJetPhi                            [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMax                       [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMax2                      [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMaxPrime                  [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMaxPrime2                 [selbin][j][lepbin].Write(); 
  h_AODCaloJetBeta                           [selbin][j][lepbin].Write(); 
  h_AODCaloJetBeta2                          [selbin][j][lepbin].Write(); 
  h_AODCaloJetSumIP                          [selbin][j][lepbin].Write(); 
  h_AODCaloJetSumIPSig                       [selbin][j][lepbin].Write(); 
  h_AODCaloJetMedianIP                       [selbin][j][lepbin].Write(); 
  h_AODCaloJetMedianLog10IPSig               [selbin][j][lepbin].Write(); 
  h_AODCaloJetTrackAngle                     [selbin][j][lepbin].Write(); 
  h_AODCaloJetLogTrackAngle                  [selbin][j][lepbin].Write(); 
  h_AODCaloJetMedianLog10TrackAngle          [selbin][j][lepbin].Write(); 
  h_AODCaloJetTotalTrackAngle                [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVx                          [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVy                          [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVz                          [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexTotalChiSquared       [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexChi2NDoF              [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexDistanceToBeam        [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexTransverseError       [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexTransverseSig         [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexDeltaEta              [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexDeltaPhi              [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexRecoilPt              [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexTrackMass             [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexTrackEnergy           [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][j][lepbin].Write(); 
  h_AODCaloJetNCleanMatchedTracks            [selbin][j][lepbin].Write(); 
  h_AODCaloJetSumHitsInFrontOfVert           [selbin][j][lepbin].Write(); 
  h_AODCaloJetSumMissHitsAfterVert           [selbin][j][lepbin].Write(); 
  h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][j][lepbin].Write(); 
  h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfDistToPV                    [selbin][j][lepbin].Write(); 
  h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][j][lepbin].Write(); 
 // h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][j][lepbin].Write(); 

 }

 return kTRUE;
}

// trigger ------------------------
Bool_t analyzer_signal::askPassSingleEle()
{
 //printf("AOD_HLT_Ele23Loose %llu \n", AOD_HLT_Ele23Loose) ;
 //printf("AOD_HLT_Ele27Tight %llu \n", AOD_HLT_Ele27Tight) ;
 //printf("AOD_HLT_Ele17Ele12 %llu \n", AOD_HLT_Ele17Ele12) ;
 //printf("AOD_HLT_Ele23Ele12 %llu \n", AOD_HLT_Ele23Ele12) ;
 //printf("AOD_HLT_IsoMu22    %llu \n", AOD_HLT_IsoMu22   ) ;
 //printf("AOD_HLT_IsoTkMu22  %llu \n", AOD_HLT_IsoTkMu22 ) ;
 //printf("AOD_HLT_Mu17Mu8    %llu \n", AOD_HLT_Mu17Mu8   ) ;
 //printf("AOD_HLT_Mu17TkMu8  %llu \n", AOD_HLT_Mu17TkMu8 ) ;

 Bool_t doespass = kFALSE;
 if(electron_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_Ele23Loose > 0) || (AOD_HLT_Ele27Tight > 0) );
 } 
 return doespass;
}

Bool_t analyzer_signal::askPassDoubleEle()
{
 Bool_t doespass = kFALSE;
 if(electron_list.size()>1){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_Ele17Ele12 > 0) || (AOD_HLT_Ele23Ele12 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_signal::askPassSingleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_IsoMu22 > 0) || (AOD_HLT_IsoTkMu22 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_signal::askPassDoubleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>1){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_Mu17Mu8 > 0) || (AOD_HLT_Mu17TkMu8 > 0) ) ;
 } 
 return doespass;
}

// signal/control region selections ------------------------
Bool_t analyzer_signal::askPassSig()
{
 Bool_t doespass = kTRUE;
 if( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) ){
  n_passSig++;
  if( passSingleEle || passDoubleEle ) { n_ele_passSig++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passSig++; }
 }
 return doespass;
}
//different than what I was using previously
Bool_t analyzer_signal::askPassZH()
{
 Bool_t doespass = kFALSE;

 if( passGoodVtx
    && passZWindow
    && passPTOSSFg50
    //&& passOneJet
    && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
   )
 { doespass = kTRUE; n_passZH++;
  if( passSingleEle || passDoubleEle ) { n_ele_passZH++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passZH++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassDY()
{
 Bool_t doespass = kFALSE;

if ( passGoodVtx
     && passZWindow
     && !passPTOSSFg50
     //&& passOneJet
     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
    )
 { doespass = kTRUE; n_passDY++; 
  if( passSingleEle || passDoubleEle ) { n_ele_passDY++; } // printf("\n PASS SingleEle Event %lld\n", event); }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passDY++;  } // printf("\n PASS SingleMu Event %lld\n", event); }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassOffZ()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && !passZWindow
     && passOSSF
     //&& passOneJet
     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu)
    )
 { doespass = kTRUE; n_passOffZ++;
  if( passSingleEle || passDoubleEle ) { n_ele_passOffZ++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passOffZ++; }
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
     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu)
    )
 { doespass = kTRUE; n_passNoPair++;
  if( passSingleEle || passDoubleEle ) { n_ele_passNoPair++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passNoPair++; }
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
      Float_t muonPt = AOD_muPt->at(i);
      Float_t muonEnergy = muonPt*TMath::CosH( AOD_muEta->at(i) );
      if(sysbinname=="_MESUp"  ){ muonEnergy*=(1.0 + 0.015); }
      if(sysbinname=="_MESDown"){ muonEnergy*=(1.0 - 0.015); }

      muonPt = muonEnergy/TMath::CosH( AOD_muEta->at(i) );
  return muonPt;

}

//-------------------------getElectronPt
Float_t analyzer_signal::getElectronPt(int i, TString sysbinname){

      //Electron passes pt cut 
      Float_t electronPt = AOD_elePt->at(i);
      Float_t electronEnergy = electronPt*TMath::CosH( AOD_eleEta->at(i) );
      if(sysbinname=="_EESUp"  ){ electronEnergy*=(1.0 + 0.015); }
      if(sysbinname=="_EESDown"){ electronEnergy*=(1.0 - 0.015); }

      electronPt = electronEnergy/TMath::CosH( AOD_eleEta->at(i) );

  return electronPt;

}

// #brokenphotons
//-------------------------getPhotonPt
Float_t analyzer_signal::getPhotonPt(int idnr, TString sysbinname){

      Float_t photonenergy = AOD_phoSCEn->at(idnr);
      if(sysbinname=="_PESUp"  ){ photonenergy*=(1. + 0.015); }
      if(sysbinname=="_PESDown"){ photonenergy*=(1. - 0.015); }

      Float_t AOD_phoPt = photonenergy/TMath::CosH( (*AOD_phoSCEta)[idnr] );

  return AOD_phoPt;

}

//-------------------------muon_passID
std::vector<int> analyzer_signal::muon_passID( int bitnr, double muPtCut, double muEtaCut, TString sysbinname)
{
 std::vector<int> mulist;

 // bool pass_loose  ;
 // bool pass_medium ;
 // bool pass_tight  ;
 // bool pass_soft   ;
 // bool pass_hipt   ;
 //
 // pass_loose  = muIDbit->at(i) >> 0 & 0x1 == 1;      
 // pass_medium = muIDbit->at(i) >> 1 & 0x1 == 1;      
 // pass_tight  = muIDbit->at(i) >> 2 & 0x1 == 1;     
 // pass_soft   = muIDbit->at(i) >> 3 & 0x1 == 1;    
 // pass_hipt   = muIDbit->at(i) >> 4 & 0x1 == 1;    
 //
 //  printf(" Muon %i    %i %i %i %i %i \n\n",i
 //        , pass_loose  
 //        , pass_medium  
 //        , pass_tight
 //        , pass_soft
 //        , pass_hipt
 //        );       

 for(int i = 0; i < AOD_muPt->size(); i++) 
 {    
  //  printf(" Muon %i    %i %i %i %i %i \n",i
  //        ,muIDbit->at(i) >> 0 & 0x1 
  //        ,muIDbit->at(i) >> 1 & 0x1 
  //        ,muIDbit->at(i) >> 2 & 0x1 
  //        ,muIDbit->at(i) >> 3 & 0x1 
  //        ,muIDbit->at(i) >> 4 & 0x1 
  //        );       

  Float_t muonPt = getMuonPt(i,sysbinname);
  bool pass_kin = muonPt > muPtCut && ( fabs(AOD_muEta->at(i)) < muEtaCut ) ;

  bool pass_bit = AOD_muPassLooseID->at(i);//muIDbit->at(i) >> bitnr & 0x1 == 1;<------need to add      

  if (muoid = "Loose")  muoisoval = 0.25 ;
  if (muoid = "Medium") muoisoval = 0.25 ;
  if (muoid = "Tight")  muoisoval = 0.15 ;
  bool pass_iso = AOD_muPFdBetaIsolation->at(i) > muoisoval ;

  if( pass_bit && pass_kin && pass_iso )
  {
   //printf(" a selected muon\n");
   nSelectedMuo++;
   mulist.push_back(i);
  } // if pass_bit && pass_kin
 } // loop over muons
 return mulist;
}

//-------------------------electron_passID
std::vector<int> analyzer_signal::electron_passID( int bitnr, double elePtCut, double eleEtaCut, TString sysbinname)
{

 std::vector<int> elelist;
 // veto loose medium tight heep hlt

 for(int i = 0; i < nAODEle; i++) 
 {    

  Float_t electronPt = getElectronPt(i,sysbinname);
  bool pass_kin = electronPt > elePtCut && ( fabs(AOD_eleEta->at(i)) < eleEtaCut ) ;

  bool pass_bit = AOD_eleIDbit->at(i) >> bitnr & 0x1 == 1;      

  bool pass_overlap = true;
  //// #brokenphotons
  //// check overlap with photons
  //if(photon_list.size()>0){
  // for(int d=0; d<photon_list.size(); ++d){
  //  int phoindex = photon_list[d];
  //  if(phoindex<= (phoEta->size()-1) && phoindex<= (phoPhi->size()-1)){
  //   if( dR( phoEta->at(phoindex),phoPhi->at(phoindex), eleEta->at(i),elePhi->at(i) ) < objcleandRcut )  pass_overlap=false;
  //  }
  // }//end photons
  //} // if photons

  //// isolation already in VID
  //bool pass_iso = elePFdBetaIsolationRhoEA ->at(i) <  [SELBINNAMESIZE][LEPBINNAMESIZE];
  //bool pass_iso = elePFdBetaIsolationCHS   ->at(i) <  [SELBINNAMESIZE][LEPBINNAMESIZE];
  //bool pass_iso = elePFdBetaIsolationDiff  ->at(i) <  [SELBINNAMESIZE][LEPBINNAMESIZE];

  if( pass_bit && pass_kin && pass_overlap)
  {
   nSelectedEle++;
   //printf(" a selected electron\n");
   elelist.push_back(i);
  } // if pass_bit && pass_kin
 } // loop over electrons
 return elelist;
}
 
void analyzer_signal::tagger(){
  OPT_Event.push_back(event);
  OPT_EventWeight.push_back(event_weight);
  //OPT_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      //if(aodcalojet_list.size()>=1){
      OPT_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojet_list[i]));
      OPT_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojet_list[i]));
      OPT_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojet_list[i]));
      //std::cout<<">0 " << aodcalojet_list.size()<<",  "<<n_test<<std::endl;
      }
  }
  else{
    OPT_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPT_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPT_AODCaloJetAlphaMax              .push_back(-5);
    n_test2 = n_test2 + 1;
    //std::cout<<"<0 " <<aodcalojet_list.size()<<",  "<<n_test2<<std::endl;
  }
}

//-------------------------aodcalojet_passID
std::vector<int> analyzer_signal::aodcalojet_passID( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname) {

  std::vector<int> jetlist;

  for(int i = 0; i < AODnCaloJet; i++)
  {

   bool pass_overlap = true;
   //// #brokenphotons
   //// check overlap with photons
   //if(photon_list.size()>0){
   // for(int d=0; d<photon_list.size(); ++d){
   //  int phoindex = photon_list[d];
   //  if(phoindex<= (phoEta->size()-1)&&phoindex<= (phoPhi->size()-1)){  //  <---- shouldn't be needed?
   //   if( dR( phoEta->at(phoindex),phoPhi->at(phoindex), AODCaloJetEta->at(i),AODCaloJetPhi->at(i) ) < objcleandRcut ){
   //    pass_overlap=false;
   //   } // if overlap
   //  }
   // }//end photons
   //} // if photons
   //check overlap with electrons
   if(electron_list.size()>0){
    for(int d=0; d<electron_list.size(); ++d){
     //printf(" brgin looping over electrons\n");
     int eleindex = electron_list[d];
     if( dR( AOD_eleEta->at(eleindex),AOD_elePhi->at(eleindex), AODCaloJetEta->at(i),AODCaloJetPhi->at(i) ) < objcleandRcut )
     {
      pass_overlap=false; // printf(" OL w electron\n");
     } // if overlap
    }//end electrons
   } // if electrons
   //check overlap with muons
   if(muon_list.size()>0){
    for(int d=0; d<muon_list.size(); ++d){
     int muindex = muon_list[d];
     if(muindex<= (AOD_muEta->size()-1)&&muindex<= (AOD_muPhi->size()-1)){
      if( dR( AOD_muEta->at(muindex),AOD_muPhi->at(muindex), AODCaloJetEta->at(i),AODCaloJetPhi->at(i) ) < objcleandRcut )
      {
       pass_overlap=false; //printf(" OL w muon\n");
      } // if overlap     }
     }
    }//end muons
   } // if muons

   bool pass_kin = AODCaloJetPt->at(i) > jetPtCut && ( fabs(AODCaloJetEta->at(i)) < jetEtaCut ) ;
              
   if( pass_kin && pass_overlap )
   {
    nSelectedAODCaloJet++;
    jetlist.push_back(i);
   } // if pass_bit && pass_kin
  }// for(int i = 0; i < nJet; i++)

  return jetlist;

}


//-------------------------photon_passLooseID
std::vector<int> analyzer_signal::photon_passID( int bitnr, double AOD_phoPtCut, double phoEtaCut, TString sysbinname){

 std::vector<int> pholist;
 pholist.clear();

 ////Loop over photons                   
 for(int p=0;p<AOD_phoPt->size();p++)//<-----change from nPho until we get it
 {    
  Float_t theAOD_phoPt = getPhotonPt(p,sysbinname);
  //Float_t theAOD_phoPt =  phoSCRawE->at(p) / TMath::CosH( (*phoSCEta)[p] ); //  AOD_phoPt->at(p); 
  Float_t thephoEta = AOD_phoSCEta->at(p);                                  //  phoEta->at(p);

  bool kinematic = theAOD_phoPt > AOD_phoPtCut && fabs((*AOD_phoSCEta)[p])<phoEtaCut;
  //bool kinematic = theAOD_phoPt > AOD_phoPtCut && fabs(thephoEta)<phoEtaCut;

  bool pass_bit = true; //phoIDbit->at(p) >> bitnr & 0x1 == 1; 
  //printf(" photon %i %i %i\n",p,bitnr,pass_bit);

  if( kinematic && pass_bit){
   nSelectedPho++;
   //printf("selected aphoton\n");
   pholist.push_back(p);
  }    
 }    

 return pholist;

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
       if( AOD_eleCharge->at(0)*AOD_eleCharge->at(i)==-1 )                     
       {                                                               
        //printf(" --we have electrons ");                             
        e1.SetPtEtaPhiE( AOD_elePt->at(electron_list[0]), AOD_eleEta->at(electron_list[0]), AOD_elePhi->at(electron_list[0]), AOD_eleEn->at(electron_list[0]) );  
        e2.SetPtEtaPhiE( AOD_elePt->at(electron_list[i]), AOD_eleEta->at(electron_list[i]), AOD_elePhi->at(electron_list[i]), AOD_eleEn->at(electron_list[i]) );  
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
        if( AOD_muCharge->at(0)*AOD_muCharge->at(i)==-1 ) 
        {                                         
         //printf(" --we have muons ");           
         m1.SetPtEtaPhiE( AOD_muPt->at(muon_list[0]), AOD_muEta->at(muon_list[0]), AOD_muPhi->at(muon_list[0]), AOD_muEn->at(muon_list[0]) );             
         //printf(": charge pass ");    
         m2.SetPtEtaPhiE( AOD_muPt->at(muon_list[i]), AOD_muEta->at(muon_list[i]), AOD_muPhi->at(muon_list[i]), AOD_muEn->at(muon_list[i]) );             
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


void analyzer_signal::loadPUWeight(){
 printf("loading PU weight \n");
 char* cCMSSW_BASE = std::getenv("CMSSW_BASE");
 TString CMSSW_BASE = (TString)cCMSSW_BASE;
 TString filename = CMSSW_BASE+"/src/LLDJstandalones/data/puWeights_69200_24jan2017.root" ;
 TFile* file_puweights = new TFile( filename ) ;
 printf(" filename: %s\n",filename.Data());
 PUWeights = (TH1F*)file_puweights->Get("h_PUweight")->Clone("PUWeights");
 return ;
}

void analyzer_signal::loadElectronWeight(){
 printf("loading Electron weight \n");
 char* cCMSSW_BASE = std::getenv("CMSSW_BASE");
 TString CMSSW_BASE = (TString)cCMSSW_BASE;
 TString filename = CMSSW_BASE+"/src/LLDJstandalones/data/egammaEffi_MoriondBH_ele"+eleid+".root" ;
 TFile* file_eleweights = new TFile( filename ) ;
 printf(" filename: %s\n",filename.Data());
 EleWeights = (TH2F*)file_eleweights->Get("EGamma_SF2D")->Clone("EleWeights");
 return ;
}

//Double_t analyzer_signal::makePUWeight(){
// Int_t tmpbin = PUWeights->GetBin(nTruePU);
// Double_t tmpweight = PUWeights->GetBinContent(tmpbin);
// //printf("making PU weight for %i , %i, %f \n", nTruePU,tmpbin,tmpweight);
// return tmpweight;
//}

Double_t analyzer_signal::makeElectronWeight(){

 Double_t tmpsf;
 tmpsf = 1.;

 //check overlap with electrons
 if(electron_list.size()>0){
  //printf(" esize: %lu\n",electron_list.size());
  //printf(" esceta: %lu\n",eleSCEta->size());
  //printf(" ept: %lu\n",AOD_elePt->size());
  for(int d=0; d<electron_list.size(); ++d){
   //printf(" brgin looping over electrons\n");
   int eleindex = electron_list[d];
   //printf(" d: %i eleindex: %i\n",d,eleindex);
   //printf(" ele sceta %f pt %f \n",eleSCEta->at(eleindex),AOD_elePt->at(eleindex));
   Float_t eeta = AOD_eleEta->at(eleindex);//<------changed; don't have SCEta right now
   Float_t ept  = AOD_elePt->at(eleindex);
   Int_t tmpbinx       = EleWeights->GetXaxis()->FindBin( eeta );
   Int_t tmpbiny       = EleWeights->GetYaxis()->FindBin( ept  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = EleWeights->GetBin( tmpbinx, tmpbiny );
   Double_t tmpweight = EleWeights->GetBinContent(tmpbin);
   tmpsf *= tmpweight;
  }//end electrons
 } // if electrons

 //printf(" done making Electron weight\n");

 return tmpsf;
}

void analyzer_signal::debug_printobjects(){

  printf("\n Event %lld\n", event);
  printf(" Pass ossf %d zwind %d ptg50 %d 1jet %d vtx %d \n", passOSSF, passZWindow, passPTOSSFg50, passOneJet, passGoodVtx);
  if(dilep_mass>0.){printf(" Dilep Found\n");}

//  for(int i=0; i<photon_list.size(); ++i){
//   int phoindex = photon_list[i];
//   printf( " photon %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_phoPt->at(phoindex), phoEta->at(phoindex), phoPhi->at(phoindex));
//  }

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   printf( " electron %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_elePt->at(eleindex), AOD_eleEta->at(eleindex), AOD_elePhi->at(eleindex));
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   printf( " muon %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_muPt->at(muindex), AOD_muEta->at(muindex), AOD_muPhi->at(muindex));

   //printf(" muonid %d    %d %d %d %d %d \n",i
   //      ,muIDbit->at(i) >> 0 & 0x1 
   //      ,muIDbit->at(i) >> 1 & 0x1 
   //      ,muIDbit->at(i) >> 2 & 0x1 
   //      ,muIDbit->at(i) >> 3 & 0x1 
   //      ,muIDbit->at(i) >> 4 & 0x1 
   //      );       
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

  return;

 }

void analyzer_signal::debug_printmuons()
{

 // muon debug
 return;

}


void analyzer_signal::debug_printelectrons()
{

 // elecgron debug
 return;

}



void analyzer_signal::debug_printtriggers()
{

 printf("AOD_HLT_Ele23Loose %llu \n", AOD_HLT_Ele23Loose) ;
 printf("AOD_HLT_Ele27Tight %llu \n", AOD_HLT_Ele27Tight) ;
 printf("AOD_HLT_Ele17Ele12 %llu \n", AOD_HLT_Ele17Ele12) ;
 printf("AOD_HLT_Ele23Ele12 %llu \n", AOD_HLT_Ele23Ele12) ;
 printf("AOD_HLT_IsoMu22    %llu \n", AOD_HLT_IsoMu22   ) ;
 printf("AOD_HLT_IsoTkMu22  %llu \n", AOD_HLT_IsoTkMu22 ) ;
 printf("AOD_HLT_Mu17Mu8    %llu \n", AOD_HLT_Mu17Mu8   ) ;
 printf("AOD_HLT_Mu17TkMu8  %llu \n", AOD_HLT_Mu17TkMu8 ) ;
 return;

}

