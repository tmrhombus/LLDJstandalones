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
 
 nmatched = 0;
 nunmatched = 0;

 jetmatchdRcut = 0.4;
 objcleandRcut = 0.4;

 n_tot=0;
 n_test =0;
 n_test2 = 0; 

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

 if (jetid = "Loose")  slimmedjetidbit=0;
 if (jetid = "Tight")  slimmedjetidbit=1;

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
  nSelectedSlimmedJet=0;
  nSelectedAODCaloJet=0;
 
 OPT_Event                           .clear();
 OPT_EventWeight                     .clear();
 //OPT_nJets                           .clear();
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
  //photon_list     = photon_passID    ( phoidbit,        30, 1.4442, ""); 
  electron_list   = electron_passID  ( eleidbit,        30, 2.1,    "");
  muon_list       = muon_passID      ( muoidbit,        30, 2.1,    ""); 
  slimmedjet_list = slimmedjet_passID( slimmedjetidbit, 25, 2.4,    ""); 
  aodcalojet_list = aodcalojet_passID( aodcalojetidbit, 25, 2.4,    ""); 

  // make event weight in analyzerBase.C
  // colisions happen @LHC at a given rate, use event_weight
  // to make the simulation match the rate seen in data
  // = lum * cross-section / nrEvents generated
  event_weight = makeEventWeight(crossSec,lumi,nrEvents);
  // for MC, simulated pileup is different from observed
  // in commontools/pileup we make a ratio for scaling MC
  if(isMC) event_weight *= makePUWeight();
  // electrons also have an associated scale factor for MC 
  if(isMC) event_weight *= makeElectronWeight();

//  OPT_Event.push_back(event);
//  OPT_EventWeight.push_back(event_weight);
//  //OPT_nJets.push_back(aodcalojet_list.size());
  tagger();
  
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
  htslimmedjets = 0.;
  htaodcalojets = 0.;

  //// #brokenphotons
  //for(int i=0; i<photon_list.size(); ++i){
  // int phoindex = photon_list[i];
  // htall += phoPt->at(phoindex);
  //}

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   htall += elePt->at(eleindex);
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   htall += muPt->at(muindex);
  }

  for(int i=0; i<slimmedjet_list.size(); ++i){
   int slimmedjetindex = slimmedjet_list[i];
   //htall  += slimmedJetPt->at(slimmedjetindex);
   htslimmedjets += slimmedJetPt->at(slimmedjetindex);
  } 

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int aodcalojetindex = aodcalojet_list[i];
   htall  += AODCaloJetPt->at(aodcalojetindex);
   htaodcalojets += AODCaloJetPt->at(aodcalojetindex);
  } 

/*  
  // check compatibility between AOD/miniAOD jets
  printf("miniAOD: %i    AOD: %i \n", (int)slimmedjet_list.size(), (int)aodcalojet_list.size() );
  //if( jet_list.size()!=AODcalojet_list.size()){nunmatched ++; continue;}
  //nmatched ++;
  for(int i=0; i<slimmedjet_list.size(); ++i){
   int miniAODjetindex = slimmedjet_list.at(i);
   printf(" miniAOD: %f %f %f\n",
    slimmedJetPt ->at(miniAODjetindex), 
    slimmedJetEta->at(miniAODjetindex), 
    slimmedJetPhi->at(miniAODjetindex)
   );
  } 
  for(int i=0; i<aodcalojet_list.size(); ++i){
   int AODjetindex     = aodcalojet_list.at(i);
   printf(" AOD:     %f %f %f\n\n",
    AODCaloJetPt  ->at(AODjetindex), 
    AODCaloJetEta ->at(AODjetindex), 
    AODCaloJetPhi ->at(AODjetindex)  
   );
  } 
*/
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
  passOneJet =  slimmedjet_list.size()>0; 

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
                        fillBasicHistograms(event_weight,0,0); fillSlimmedJetHistograms(event_weight,0,0); fillAODCaloJetHistograms(event_weight,0,0);  
   if( doesPassSig   ){ fillBasicHistograms(event_weight,1,0); fillSlimmedJetHistograms(event_weight,1,0); fillAODCaloJetHistograms(event_weight,1,0); }
   if( doesPassZH    ){ fillBasicHistograms(event_weight,2,0); fillSlimmedJetHistograms(event_weight,2,0); fillAODCaloJetHistograms(event_weight,2,0); }
   if( doesPassDY    ){ fillBasicHistograms(event_weight,3,0); fillSlimmedJetHistograms(event_weight,3,0); fillAODCaloJetHistograms(event_weight,3,0); }
   if( doesPassOffZ  ){ fillBasicHistograms(event_weight,4,0); fillSlimmedJetHistograms(event_weight,4,0); fillAODCaloJetHistograms(event_weight,4,0); }
   if( doesPassNoPair){ fillBasicHistograms(event_weight,5,0); fillSlimmedJetHistograms(event_weight,5,0); fillAODCaloJetHistograms(event_weight,5,0); }
  }

  //if( passSingleMu ){
  if( passSingleMu || passDoubleMu ){
                        fillBasicHistograms(event_weight,0,1); fillSlimmedJetHistograms(event_weight,0,1); fillAODCaloJetHistograms(event_weight,0,1);  
   if( doesPassSig   ){ fillBasicHistograms(event_weight,1,1); fillSlimmedJetHistograms(event_weight,1,1); fillAODCaloJetHistograms(event_weight,1,1); }
   if( doesPassZH    ){ fillBasicHistograms(event_weight,2,1); fillSlimmedJetHistograms(event_weight,2,1); fillAODCaloJetHistograms(event_weight,2,1); }
   if( doesPassDY    ){ fillBasicHistograms(event_weight,3,1); fillSlimmedJetHistograms(event_weight,3,1); fillAODCaloJetHistograms(event_weight,3,1); }
   if( doesPassOffZ  ){ fillBasicHistograms(event_weight,4,1); fillSlimmedJetHistograms(event_weight,4,1); fillAODCaloJetHistograms(event_weight,4,1); }
   if( doesPassNoPair){ fillBasicHistograms(event_weight,5,1); fillSlimmedJetHistograms(event_weight,5,1); fillAODCaloJetHistograms(event_weight,5,1); }
  }
   
  //No Lep selection
                          fillBasicHistograms(event_weight,0,2); fillSlimmedJetHistograms(event_weight,0,2); fillAODCaloJetHistograms(event_weight,0,2);  
     if( doesPassSig   ){ fillBasicHistograms(event_weight,1,2); fillSlimmedJetHistograms(event_weight,1,2); fillAODCaloJetHistograms(event_weight,1,2); }
     if( doesPassZH    ){ fillBasicHistograms(event_weight,2,2); fillSlimmedJetHistograms(event_weight,2,2); fillAODCaloJetHistograms(event_weight,2,2); }
     if( doesPassDY    ){ fillBasicHistograms(event_weight,3,2); fillSlimmedJetHistograms(event_weight,3,2); fillAODCaloJetHistograms(event_weight,3,2); }
     if( doesPassOffZ  ){ fillBasicHistograms(event_weight,4,2); fillSlimmedJetHistograms(event_weight,4,2); fillAODCaloJetHistograms(event_weight,4,2); }
     if( doesPassNoPair){ fillBasicHistograms(event_weight,5,2); fillSlimmedJetHistograms(event_weight,5,2); fillAODCaloJetHistograms(event_weight,5,2); }
  
  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);
 //tagger();
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
 TFile *optfile = new TFile(outfilename+"_OPT"+".root","RECREATE");
 outfile->cd();
 for(int i=0; i<selbinnames.size(); ++i){  // i = selbin
  for(unsigned int k=0; k<lepnames.size(); ++k){
   writeBasicHistograms(i,k);
   writeSlimmedJetHistograms(i,k);
   writeAODCaloJetHistograms(i,k);
   //write2DHistograms(i,k);
  }
 }
 outfile->Close();
 optfile->cd();
 OPTtree->Write();
 optfile->Close();
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
   TString hname_nVtx                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nVtx        "; 
   TString hname_nGoodVtx                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nGoodVtx    "; 
   TString hname_nTrksPV                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nTrksPV     "; 
   TString hname_isPVGood                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_isPVGood    "; 
   TString hname_rho                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_rho         "; 
   TString hname_rhoCentral               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_rhoCentral  "; 
   TString hname_nTruePU                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nTruePU     "; 
   TString hname_pfMET                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_pfMET       "; 
   TString hname_pfMETPhi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_pfMETPhi    "; 
   TString hname_pfMETsumEt               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_pfMETsumEt  "; 

   TString hname_nPho                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nPho        "; 
   TString hname_phoEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoEn       "; 
   TString hname_phoPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoPt       "; 
   TString hname_phoEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoEta      "; 
   TString hname_phoPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoPhi      "; 
   TString hname_phoSCEn                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoSCEn     "; 
   TString hname_phoSCPhi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoSCPhi    "; 
   TString hname_phoSCEta                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoSCEta    "; 

   TString hname_nEle                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nEle        "; 
   TString hname_elePt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePt       "; 
   TString hname_eleEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleEn       "; 
   TString hname_eleEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleEta      "; 
   TString hname_elePhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePhi      "; 
   TString hname_eleCharge                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleCharge   "; 
   TString hname_eleSCEn                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCEn     "; 
   TString hname_eleSCEta                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCEta    "; 
   TString hname_eleSCPhi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCPhi    "; 
   TString hname_elePFdBetaIsolationRhoEA = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationRhoEA"; 
   TString hname_elePFdBetaIsolationCHS   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationCHS  "; 
   TString hname_elePFdBetaIsolationDiff  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationDiff "; 
   TString hname_nMu                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nMu                "; 
   TString hname_muPt                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPt               "; 
   TString hname_muEn                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muEn               "; 
   TString hname_muEta                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muEta              "; 
   TString hname_muPhi                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPhi              "; 
   TString hname_muCharge                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muCharge           "; 
   TString hname_muPFdBetaIsolation       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPFdBetaIsolation "; 

   TString hname_htall                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htall        " ;
   TString hname_htslimmedjets            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htslimmedjets" ;
   TString hname_htaodcalojets            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htaodcalojets" ;

   TString hname_nSelectedPho             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedPho";
   TString hname_nSelectedEle             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedEle";
   TString hname_nSelectedMuo             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedMuo";
   TString hname_nSelectedSlimmedJet      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedSlimmedJet";
   TString hname_nSelectedAODCaloJet      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedAODCaloJet";

   // initalize histograms
   h_nVtx                     [i][k] = initSingleHistogramTH1F( hname_nVtx                    , "nVtx                   ", 60,0,60) ; 
   h_nGoodVtx                 [i][k] = initSingleHistogramTH1F( hname_nGoodVtx                , "nGoodVtx               ", 60,0,60) ;  
   h_nTrksPV                  [i][k] = initSingleHistogramTH1F( hname_nTrksPV                 , "nTrksPV                ", 60,0,60) ;  
   h_isPVGood                 [i][k] = initSingleHistogramTH1F( hname_isPVGood                , "isPVGood               ", 2,0,1) ;  
   h_rho                      [i][k] = initSingleHistogramTH1F( hname_rho                     , "rho                    ", 30, -3, 3); 
   h_rhoCentral               [i][k] = initSingleHistogramTH1F( hname_rhoCentral              , "rhoCentral             ", 30, -3, 3); 
   h_nTruePU                  [i][k] = initSingleHistogramTH1F( hname_nTruePU                 , "nTruePU                ", 60,0,60) ;  
   h_pfMET                    [i][k] = initSingleHistogramTH1F( hname_pfMET                   , "pfMET                  ", 50, 0, 500) ;  
   h_pfMETPhi                 [i][k] = initSingleHistogramTH1F( hname_pfMETPhi                , "pfMETPhi               ", 30, -5, 5); 
   h_pfMETsumEt               [i][k] = initSingleHistogramTH1F( hname_pfMETsumEt              , "pfMETsumEt             ", 50, 0, 500)  ;

   h_phoEn                    [i][k] = initSingleHistogramTH1F( hname_phoEn                   , "phoEn                  ", 50, 0, 500) ;  
   h_phoPt                    [i][k] = initSingleHistogramTH1F( hname_phoPt                   , "phoPt                  ", 50, 0, 500) ;  
   h_phoEta                   [i][k] = initSingleHistogramTH1F( hname_phoEta                  , "phoEta                 ", 30, -5, 5); 
   h_phoPhi                   [i][k] = initSingleHistogramTH1F( hname_phoPhi                  , "phoPhi                 ", 30, -5, 5); 
   h_phoSCEn                  [i][k] = initSingleHistogramTH1F( hname_phoSCEn                 , "phoSCEn                ", 50, 0, 500) ;  
   h_phoSCPhi                 [i][k] = initSingleHistogramTH1F( hname_phoSCPhi                , "phoSCPhi               ", 30, -5, 5); 
   h_phoSCEta                 [i][k] = initSingleHistogramTH1F( hname_phoSCEta                , "phoSCEta               ", 30, -5, 5); 

   h_elePt                    [i][k] = initSingleHistogramTH1F( hname_elePt                   , "elePt                  ", 50, 0, 500) ;  
   h_eleEn                    [i][k] = initSingleHistogramTH1F( hname_eleEn                   , "eleEn                  ", 50, 0, 500) ;  
   h_eleEta                   [i][k] = initSingleHistogramTH1F( hname_eleEta                  , "eleEta                 ", 30, -5, 5); 
   h_elePhi                   [i][k] = initSingleHistogramTH1F( hname_elePhi                  , "elePhi                 ", 30, -5, 5); 
   h_eleCharge                [i][k] = initSingleHistogramTH1F( hname_eleCharge               , "eleCharge              ", 3, -1, 1); 
   h_eleSCEn                  [i][k] = initSingleHistogramTH1F( hname_eleSCEn                 , "eleSCEn                ", 50, 0, 500) ;  
   h_eleSCEta                 [i][k] = initSingleHistogramTH1F( hname_eleSCEta                , "eleSCEta               ", 30, -5, 5); 
   h_eleSCPhi                 [i][k] = initSingleHistogramTH1F( hname_eleSCPhi                , "eleSCPhi               ", 30, -5, 5); 
   h_elePFdBetaIsolationRhoEA [i][k] = initSingleHistogramTH1F( hname_elePFdBetaIsolationRhoEA, "elePFdBetaIsolationRhoEA", 30, 0, 1); 
   h_elePFdBetaIsolationCHS   [i][k] = initSingleHistogramTH1F( hname_elePFdBetaIsolationCHS  , "elePFdBetaIsolationCHS  ", 30, 0, 1); 
   h_elePFdBetaIsolationDiff  [i][k] = initSingleHistogramTH1F( hname_elePFdBetaIsolationDiff , "elePFdBetaIsolationDiff ", 30, 0, 1); 

   h_muPt                     [i][k] = initSingleHistogramTH1F( hname_muPt                    , "muPt                   ", 50, 0, 500) ;  
   h_muEn                     [i][k] = initSingleHistogramTH1F( hname_muEn                    , "muEn                   ", 50, 0, 500) ;  
   h_muEta                    [i][k] = initSingleHistogramTH1F( hname_muEta                   , "muEta                  ", 30, -5, 5); 
   h_muPhi                    [i][k] = initSingleHistogramTH1F( hname_muPhi                   , "muPhi                  ", 30, -5, 5); 
   h_muCharge                 [i][k] = initSingleHistogramTH1F( hname_muCharge                , "muCharge               ", 3, -1, 1); 
   h_muPFdBetaIsolation       [i][k] = initSingleHistogramTH1F( hname_muPFdBetaIsolation      , "muPFdBetaIsolation     ", 30, -5, 5); 

   h_htall                    [i][k] = initSingleHistogramTH1F( hname_htall               , "htall "             , 50,0,1000) ; 
   h_htslimmedjets            [i][k] = initSingleHistogramTH1F( hname_htslimmedjets       , "htslimmedjets"      , 50,0,1000) ; 
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
 h_nVtx                    [selbin][lepbin] .Fill( nVtx       , weight);  
 h_nGoodVtx                [selbin][lepbin] .Fill( nGoodVtx   , weight);  
 h_nTrksPV                 [selbin][lepbin] .Fill( nTrksPV    , weight);  
 h_isPVGood                [selbin][lepbin] .Fill( isPVGood   , weight);  
 h_rho                     [selbin][lepbin] .Fill( rho        , weight);  
 h_rhoCentral              [selbin][lepbin] .Fill( rhoCentral , weight);  
 h_nTruePU                 [selbin][lepbin] .Fill( nTruePU    , weight);  
 h_pfMET                   [selbin][lepbin] .Fill( pfMET      , weight);  
 h_pfMETPhi                [selbin][lepbin] .Fill( pfMETPhi   , weight);  
 h_pfMETsumEt              [selbin][lepbin] .Fill( pfMETsumEt , weight);  

 h_htall                   [selbin][lepbin] .Fill( htall              , weight); 
 h_htslimmedjets           [selbin][lepbin] .Fill( htslimmedjets      , weight); 
 h_htaodcalojets           [selbin][lepbin] .Fill( htaodcalojets      , weight); 
 h_nSelectedPho            [selbin][lepbin] .Fill( nSelectedPho       , weight);
 h_nSelectedEle            [selbin][lepbin] .Fill( nSelectedEle       , weight);
 h_nSelectedMuo            [selbin][lepbin] .Fill( nSelectedMuo       , weight);
 h_nSelectedSlimmedJet     [selbin][lepbin] .Fill( nSelectedSlimmedJet, weight);
 h_nSelectedAODCaloJet     [selbin][lepbin] .Fill( nSelectedAODCaloJet, weight);

 //// #brokenphotons
 //// fill leading photon in vector
 //if(photon_list.size() > 0){
 // int phoindex = photon_list[0];
 // h_phoEn    [selbin][lepbin] .Fill( phoEn   ->at(phoindex), weight );  
 // h_phoPt    [selbin][lepbin] .Fill( phoPt   ->at(phoindex), weight );  
 // h_phoEta   [selbin][lepbin] .Fill( phoEta  ->at(phoindex), weight );  
 // h_phoPhi   [selbin][lepbin] .Fill( phoPhi  ->at(phoindex), weight );  
 // h_phoSCEn  [selbin][lepbin] .Fill( phoSCEn ->at(phoindex), weight );  
 // h_phoSCPhi [selbin][lepbin] .Fill( phoSCPhi->at(phoindex), weight );  
 // h_phoSCEta [selbin][lepbin] .Fill( phoSCEta->at(phoindex), weight );  
 //}

 // fill leading electron in vector
 if(electron_list.size() > 0){
  int eleindex = electron_list[0];
  h_elePt                   [selbin][lepbin] .Fill( elePt                    ->at(eleindex), weight );
  h_eleEn                   [selbin][lepbin] .Fill( eleEn                    ->at(eleindex), weight );
  h_eleEta                  [selbin][lepbin] .Fill( eleEta                   ->at(eleindex), weight );
  h_elePhi                  [selbin][lepbin] .Fill( elePhi                   ->at(eleindex), weight );
  h_eleCharge               [selbin][lepbin] .Fill( eleCharge                ->at(eleindex), weight );
  h_eleSCEn                 [selbin][lepbin] .Fill( eleSCEn                  ->at(eleindex), weight );
  h_eleSCEta                [selbin][lepbin] .Fill( eleSCEta                 ->at(eleindex), weight );
  h_eleSCPhi                [selbin][lepbin] .Fill( eleSCPhi                 ->at(eleindex), weight );
  h_elePFdBetaIsolationRhoEA[selbin][lepbin] .Fill( elePFdBetaIsolationRhoEA ->at(eleindex), weight ); 
  h_elePFdBetaIsolationCHS  [selbin][lepbin] .Fill( elePFdBetaIsolationCHS   ->at(eleindex), weight ); 
  h_elePFdBetaIsolationDiff [selbin][lepbin] .Fill( elePFdBetaIsolationDiff  ->at(eleindex), weight ); 
 }

 // fill leading muon in vector
 if(muon_list.size() > 0){
  int muindex = muon_list[0];
  h_muPt               [selbin][lepbin] .Fill( muPt               ->at(muindex), weight );  
  h_muEn               [selbin][lepbin] .Fill( muEn               ->at(muindex), weight );  
  h_muEta              [selbin][lepbin] .Fill( muEta              ->at(muindex), weight );  
  h_muPhi              [selbin][lepbin] .Fill( muPhi              ->at(muindex), weight );  
  h_muCharge           [selbin][lepbin] .Fill( muCharge           ->at(muindex), weight );  
  h_muPFdBetaIsolation [selbin][lepbin] .Fill( muPFdBetaIsolation ->at(muindex), weight );  
 }

 return kTRUE;
}

//----------------------------writeBasicHistograms
Bool_t analyzer_signal::writeBasicHistograms(int selbin, int lepbin)
{
 h_nVtx                    [selbin][lepbin] .Write(); 
 h_nGoodVtx                [selbin][lepbin] .Write(); 
 h_nTrksPV                 [selbin][lepbin] .Write(); 
 h_isPVGood                [selbin][lepbin] .Write(); 
 h_rho                     [selbin][lepbin] .Write(); 
 h_rhoCentral              [selbin][lepbin] .Write(); 
 h_nTruePU                 [selbin][lepbin] .Write(); 
 h_pfMET                   [selbin][lepbin] .Write(); 
 h_pfMETPhi                [selbin][lepbin] .Write(); 
 h_pfMETsumEt              [selbin][lepbin] .Write(); 

 h_htall                   [selbin][lepbin] .Write(); 
 h_htslimmedjets           [selbin][lepbin] .Write(); 
 h_htaodcalojets           [selbin][lepbin] .Write(); 
 h_nSelectedPho            [selbin][lepbin] .Write(); 
 h_nSelectedEle            [selbin][lepbin] .Write(); 
 h_nSelectedMuo            [selbin][lepbin] .Write(); 
 h_nSelectedSlimmedJet     [selbin][lepbin] .Write(); 
 h_nSelectedAODCaloJet     [selbin][lepbin] .Write(); 

 h_phoEn                   [selbin][lepbin] .Write(); 
 h_phoPt                   [selbin][lepbin] .Write(); 
 h_phoEta                  [selbin][lepbin] .Write(); 
 h_phoPhi                  [selbin][lepbin] .Write(); 
 h_phoSCEn                 [selbin][lepbin] .Write(); 
 h_phoSCPhi                [selbin][lepbin] .Write(); 
 h_phoSCEta                [selbin][lepbin] .Write(); 

 h_elePt                   [selbin][lepbin] .Write(); 
 h_eleEn                   [selbin][lepbin] .Write(); 
 h_eleEta                  [selbin][lepbin] .Write(); 
 h_elePhi                  [selbin][lepbin] .Write(); 
 h_eleCharge               [selbin][lepbin] .Write(); 
 h_eleSCEn                 [selbin][lepbin] .Write(); 
 h_eleSCEta                [selbin][lepbin] .Write(); 
 h_eleSCPhi                [selbin][lepbin] .Write(); 
 h_elePFdBetaIsolationRhoEA[selbin][lepbin] .Write(); 
 h_elePFdBetaIsolationCHS  [selbin][lepbin] .Write(); 
 h_elePFdBetaIsolationDiff [selbin][lepbin] .Write(); 

 h_muPt                    [selbin][lepbin] .Write(); 
 h_muEn                    [selbin][lepbin] .Write(); 
 h_muEta                   [selbin][lepbin] .Write(); 
 h_muPhi                   [selbin][lepbin] .Write(); 
 h_muCharge                [selbin][lepbin] .Write(); 
 h_muPFdBetaIsolation      [selbin][lepbin] .Write(); 

 return kTRUE;
}

//----------------------------initSlimmedJetHistograms
Bool_t analyzer_signal::initSlimmedJetHistograms()
{

 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int j=0; j<jetmultnames.size(); ++j){
   for(unsigned int k=0; k<lepnames.size(); ++k){
    TString  hname_slimmedJetPt                             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetPt                      ";
    TString  hname_slimmedJetEn                             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetEn                      ";
    TString  hname_slimmedJetEta                            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetEta                     ";
    TString  hname_slimmedJetPhi                            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetPhi                     ";
    TString  hname_slimmedJetRawPt                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetRawPt                   ";
    TString  hname_slimmedJetRawEn                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetRawEn                   ";
    TString  hname_slimmedJetMt                             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetMt                      ";
    TString  hname_slimmedJetArea                           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetArea                    ";
    TString  hname_slimmedJetLeadTrackPID                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLeadTrackPID            ";
    TString  hname_slimmedJetLeadTrackPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLeadTrackPt             ";
    TString  hname_slimmedJetLeadTrackEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLeadTrackEta            ";
    TString  hname_slimmedJetLeadTrackPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLeadTrackPhi            ";
    TString  hname_slimmedJetLepTrackPID                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLepTrackPID             ";
    TString  hname_slimmedJetLepTrackPt                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLepTrackPt              ";
    TString  hname_slimmedJetLepTrackEta                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLepTrackEta             ";
    TString  hname_slimmedJetLepTrackPhi                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLepTrackPhi             ";
    TString  hname_slimmedJetNConstituents                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetNConstituents           ";
    TString  hname_slimmedJetVtxPt                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetVtxPt                   ";
    TString  hname_slimmedJetVtxMass                        = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetVtxMass                 ";
    TString  hname_slimmedJetVtxNtrks                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetVtxNtrks                ";
    TString  hname_slimmedJetVtx3DVal                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetVtx3DVal                ";
    TString  hname_slimmedJetVtx3DSig                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetVtx3DSig                ";
    TString  hname_slimmedJetCSV2BJetTags                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetCSV2BJetTags            ";
    TString  hname_slimmedJetJetProbabilityBJetTags         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetJetProbabilityBJetTags  ";
    TString  hname_slimmedJetpfCombinedMVAV2BJetTags        = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetpfCombinedMVAV2BJetTags ";
    TString  hname_slimmedJetPartonID                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetPartonID                ";
    TString  hname_slimmedJetHadFlvr                        = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetHadFlvr                 ";

    TString  hname_slimmedJetAlphaD                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaD                  ";
    TString  hname_slimmedJetAlphaMaxD                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaMaxD               ";
    TString  hname_slimmedJetSumIP                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetSumIP                   ";
    TString  hname_slimmedJetSumIPSig                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetSumIPSig                ";
    TString  hname_slimmedJetMedianLog10IPSig               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetMedianLog10IPSig        ";
    TString  hname_slimmedJetTrackAngle                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetTrackAngle              ";
    TString  hname_slimmedJetLogTrackAngle                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetLogTrackAngle           ";
    TString  hname_slimmedJetMedianLog10TrackAngle          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetMedianLog10TrackAngle   ";
    TString  hname_slimmedJetTotalTrackAngle                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetTotalTrackAngle         ";

    TString  hname_slimmedJetAlphaMax_PV3onPV2              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaMax_PV3onPV2       ";
    TString  hname_slimmedJetAlphaMax_PV3onChg              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaMax_PV3onChg       ";
    TString  hname_slimmedJetAlphaMax_PV3onAll              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaMax_PV3onAll       ";
    TString  hname_slimmedJetAlphaMax_PV2onChg              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaMax_PV2onChg       ";
    TString  hname_slimmedJetAlphaMax_PV2onAll              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlphaMax_PV2onAll       ";
    TString  hname_slimmedJetAlpha2Max_PV3onPV2             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlpha2Max_PV3onPV2      ";
    TString  hname_slimmedJetAlpha2Max_PV3onChg             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlpha2Max_PV3onChg      ";
    TString  hname_slimmedJetAlpha2Max_PV3onAll             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlpha2Max_PV3onAll      ";
    TString  hname_slimmedJetAlpha2Max_PV2onChg             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlpha2Max_PV2onChg      ";
    TString  hname_slimmedJetAlpha2Max_PV2onAll             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetAlpha2Max_PV2onAll      ";
    TString  hname_slimmedJetGenJetEn                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenJetEn                ";
    TString  hname_slimmedJetGenJetPt                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenJetPt                ";
    TString  hname_slimmedJetGenJetEta                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenJetEta               ";
    TString  hname_slimmedJetGenJetPhi                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenJetPhi               ";
    TString  hname_slimmedJetGenPartonID                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenPartonID             ";
    TString  hname_slimmedJetGenEn                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenEn                   ";
    TString  hname_slimmedJetGenPt                          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenPt                   ";
    TString  hname_slimmedJetGenEta                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenEta                  ";
    TString  hname_slimmedJetGenPhi                         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenPhi                  ";
    TString  hname_slimmedJetGenPartonMomID                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_slimmedJetGenPartonMomID          ";

    ////// 2D
    ////TString  hname_IpVAlpha                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_IpVAlpha                  "; 
    ////TString  hname_IpVslimmedJetPt            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_IpVjetPt                  "; 
    ////TString  hname_AlphaVjetPt                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AlphaVjetPt               "; 

    //TString hname_AODCaloJetPt                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetPt            "; 
    //TString hname_AODCaloJetEta               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetEta           "; 
    //TString hname_AODCaloJetPhi               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetPhi           "; 
    //TString hname_AODCaloJetAlphaMax          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMax      "; 
    //TString hname_AODCaloJetAlphaMax2         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMax2     "; 
    //TString hname_AODCaloJetAlphaMaxPrime     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMaxPrime "; 
    //TString hname_AODCaloJetAlphaMaxPrime2    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMaxPrime2"; 
    //TString hname_AODCaloJetBeta              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetBeta          "; 
    //TString hname_AODCaloJetBeta2             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetBeta2         "; 

    // initialize the histograms
    h_slimmedJetPt                      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetPt                     , "slimmedJetPt                     " , 50, 0, 500 ); 
    h_slimmedJetEn                      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetEn                     , "slimmedJetEn                     " , 50, 0, 500 ); 
    h_slimmedJetEta                     [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetEta                    , "slimmedJetEta                    " , 10, -5, 5 );  
    h_slimmedJetPhi                     [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetPhi                    , "slimmedJetPhi                    " , 10, -5, 5 );
    h_slimmedJetRawPt                   [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetRawPt                  , "slimmedJetRawPt                  " , 50, 0, 500 ); 
    h_slimmedJetRawEn                   [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetRawEn                  , "slimmedJetRawEn                  " , 50, 0, 500) ; 
    h_slimmedJetArea                    [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetArea                   , "slimmedJetArea                   " , 30, 0, 1) ; 
    h_slimmedJetLeadTrackPt             [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetLeadTrackPt            , "slimmedJetLeadTrackPt            " , 50, 0, 100 ); 
    h_slimmedJetLeadTrackPID            [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetLeadTrackPID           , "slimmedJetLeadTrackPID           " , 50, 0, 100 ); 
    h_slimmedJetLeadTrackEta            [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetLeadTrackEta           , "slimmedJetLeadTrackEta           " , 10, -5, 5 );  
    h_slimmedJetLeadTrackPhi            [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetLeadTrackPhi           , "slimmedJetLeadTrackPhi           " , 10, -5, 5 );  
    h_slimmedJetNConstituents           [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetNConstituents          , "slimmedJetNConstituents          " , 30, 0, 30 ); 
    h_slimmedJetVtxPt                   [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetVtxPt                  , "slimmedJetVtxPt                  " , 50, 0, 100 ); 
    h_slimmedJetVtxMass                 [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetVtxMass                , "slimmedJetVtxMass                " , 50, 0, 100 ); 
    h_slimmedJetVtxNtrks                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetVtxNtrks               , "slimmedJetVtxNtrks               " , 30, 0, 30) ; 
    h_slimmedJetVtx3DVal                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetVtx3DVal               , "slimmedJetVtx3DVal               " , 30, 0, 1) ; 
    h_slimmedJetVtx3DSig                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetVtx3DSig               , "slimmedJetVtx3DSig               " , 30, 0, 1) ;
    h_slimmedJetCSV2BJetTags            [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetCSV2BJetTags           , "slimmedJetCSV2BJetTags           " , 30, 0, 1) ; 
    h_slimmedJetJetProbabilityBJetTags  [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetJetProbabilityBJetTags , "slimmedJetJetProbabilityBJetTags " , 30, 0, 1) ; 
    h_slimmedJetpfCombinedMVAV2BJetTags [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetpfCombinedMVAV2BJetTags, "slimmedJetpfCombinedMVAV2BJetTags" , 30, 0, 1) ; 
    h_slimmedJetPartonID                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetPartonID               , "slimmedJetPartonID               " , 50, 0, 100 ); 
    h_slimmedJetHadFlvr                 [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetHadFlvr                , "slimmedJetHadFlvr                " , 50, 0, 100 ); 

    h_slimmedJetAlphaD                  [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaD                 , "slimmedJetAlphaD                 " , 30, 0, 1) ; 
    h_slimmedJetAlphaMaxD               [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaMaxD              , "slimmedJetAlphaMaxD              " , 30, 0, 1) ; 
    h_slimmedJetMedianLog10IPSig        [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetMedianLog10IPSig       , "slimmedJetMedianLog10IPSig       " , 30, -2, 3 ); 
    h_slimmedJetSumIP                   [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetSumIP                  , "slimmedJetSumIP                  " , 30, -2, 3 ); 
    h_slimmedJetSumIPSig                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetSumIPSig               , "slimmedJetSumIPSig               " , 30, -2, 3 ); 
    h_slimmedJetTrackAngle              [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetTrackAngle             , "slimmedJetTrackAngle             " , 30, 0, 1) ; 
    h_slimmedJetLogTrackAngle           [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetLogTrackAngle          , "slimmedJetLogTrackAngle          " , 30, 0, 1) ; 
    h_slimmedJetTotalTrackAngle         [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetTotalTrackAngle        , "slimmedJetTotalTrackAngle        " , 30, 0, 1) ; 

    h_slimmedJetAlphaMax_PV3onPV2       [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaMax_PV3onPV2      , "slimmedJetAlphaMax_PV3onPV2      " , 30, 0, 1) ; 
    h_slimmedJetAlphaMax_PV3onChg       [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaMax_PV3onChg      , "slimmedJetAlphaMax_PV3onChg      " , 30, 0, 1) ; 
    h_slimmedJetAlphaMax_PV3onAll       [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaMax_PV3onAll      , "slimmedJetAlphaMax_PV3onAll      " , 30, 0, 1) ; 
    h_slimmedJetAlphaMax_PV2onChg       [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaMax_PV2onChg      , "slimmedJetAlphaMax_PV2onChg      " , 30, 0, 1) ; 
    h_slimmedJetAlphaMax_PV2onAll       [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlphaMax_PV2onAll      , "slimmedJetAlphaMax_PV2onAll      " , 30, 0, 1) ; 
    h_slimmedJetAlpha2Max_PV3onPV2      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlpha2Max_PV3onPV2     , "slimmedJetAlpha2Max_PV3onPV2     " , 30, 0, 1) ; 
    h_slimmedJetAlpha2Max_PV3onChg      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlpha2Max_PV3onChg     , "slimmedJetAlpha2Max_PV3onChg     " , 30, 0, 1) ; 
    h_slimmedJetAlpha2Max_PV3onAll      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlpha2Max_PV3onAll     , "slimmedJetAlpha2Max_PV3onAll     " , 30, 0, 1) ; 
    h_slimmedJetAlpha2Max_PV2onChg      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlpha2Max_PV2onChg     , "slimmedJetAlpha2Max_PV2onChg     " , 30, 0, 1) ; 
    h_slimmedJetAlpha2Max_PV2onAll      [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetAlpha2Max_PV2onAll     , "slimmedJetAlpha2Max_PV2onAll     " , 30, 0, 1) ; 

    h_slimmedJetGenJetEn                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenJetEn       , "slimmedJetGenJetEn                ", 50, 0, 500) ;
    h_slimmedJetGenJetPt                [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenJetPt       , "slimmedJetGenJetPt                ", 50, 0, 500) ;
    h_slimmedJetGenJetEta               [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenJetEta      , "slimmedJetGenJetEta               ", 10, -5, 5) ;
    h_slimmedJetGenJetPhi               [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenJetPhi      , "slimmedJetGenJetPhi               ", 10, -5, 5) ;
    h_slimmedJetGenPartonID             [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenPartonID    , "slimmedJetGenPartonID             ", 50, 0, 500) ;
    h_slimmedJetGenEn                   [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenEn          , "slimmedJetGenEn                   ", 50, 0, 500) ;
    h_slimmedJetGenPt                   [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenPt          , "slimmedJetGenPt                   ", 50, 0, 500) ;
    h_slimmedJetGenEta                  [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenEta         , "slimmedJetGenEta                  ", 10, -5, 5) ;
    h_slimmedJetGenPhi                  [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenPhi         , "slimmedJetGenPhi                  ", 10, -5, 5) ;
    h_slimmedJetGenPartonMomID          [i][j][k] = initSingleHistogramTH1F( hname_slimmedJetGenPartonMomID , "slimmedJetGenPartonMomID          ", 50, 0, 500) ;

    ///h_IpVAlpha                   [i][j][k] = initSingleHistogramTH2F( hname_IpVAlpha                  , "jetIpVAlpha               " , 30, -2, 3, 30, 0, 1) ;
    ///h_IpVjetPt                   [i][j][k] = initSingleHistogramTH2F( hname_IpVjetPt                  , "jetIpVjetPt               " , 30, -2, 3, 50, 0, 500) ;
    ///h_AlphaVjetPt                [i][j][k] = initSingleHistogramTH2F( hname_AlphaVjetPt               , "jetAlphaVjetPt            " , 30,  0, 1, 50, 0, 500) ;

   }  //    for(unsigned int i=0; i<selbinnames.size(); ++i){
  }   //      for(unsigned int j=0; j<jet_list.size(); ++j){
 }    //         for(unsigned int k=0; k<lepnames.size(); ++k){

 return kTRUE;
}

//----------------------------fillSlimmedJetHistograms
Bool_t analyzer_signal::fillSlimmedJetHistograms(Double_t weight, int selbin, int lepbin)
{

 // i don't really like this hacky loop
 // idea is to have jets: 1,2,3,4,all
 // first fill individual jets
 for(unsigned int j=0; j<jetmultnames.size(); ++j){
  if( slimmedjet_list.size()>j ){
   int slimmedjetindex = slimmedjet_list[j];

   h_slimmedJetPt                      [selbin][j][lepbin].Fill( slimmedJetPt                     ->at( slimmedjetindex ), weight ); 
   h_slimmedJetEn                      [selbin][j][lepbin].Fill( slimmedJetEn                     ->at( slimmedjetindex ), weight ); 
   h_slimmedJetEta                     [selbin][j][lepbin].Fill( slimmedJetEta                    ->at( slimmedjetindex ), weight ); 
   h_slimmedJetPhi                     [selbin][j][lepbin].Fill( slimmedJetPhi                    ->at( slimmedjetindex ), weight ); 
   h_slimmedJetRawPt                   [selbin][j][lepbin].Fill( slimmedJetRawPt                  ->at( slimmedjetindex ), weight ); 
   h_slimmedJetRawEn                   [selbin][j][lepbin].Fill( slimmedJetRawEn                  ->at( slimmedjetindex ), weight ); 
   h_slimmedJetArea                    [selbin][j][lepbin].Fill( slimmedJetArea                   ->at( slimmedjetindex ), weight ); 
   h_slimmedJetLeadTrackPt             [selbin][j][lepbin].Fill( slimmedJetLeadTrackPt            ->at( slimmedjetindex ), weight ); 
   h_slimmedJetLeadTrackPID            [selbin][j][lepbin].Fill( slimmedJetLeadTrackPID           ->at( slimmedjetindex ), weight ); 
   h_slimmedJetLeadTrackEta            [selbin][j][lepbin].Fill( slimmedJetLeadTrackEta           ->at( slimmedjetindex ), weight ); 
   h_slimmedJetLeadTrackPhi            [selbin][j][lepbin].Fill( slimmedJetLeadTrackPhi           ->at( slimmedjetindex ), weight ); 
   h_slimmedJetNConstituents           [selbin][j][lepbin].Fill( slimmedJetNConstituents          ->at( slimmedjetindex ), weight ); 
   h_slimmedJetVtxPt                   [selbin][j][lepbin].Fill( slimmedJetVtxPt                  ->at( slimmedjetindex ), weight ); 
   h_slimmedJetVtxMass                 [selbin][j][lepbin].Fill( slimmedJetVtxMass                ->at( slimmedjetindex ), weight ); 
   h_slimmedJetVtxNtrks                [selbin][j][lepbin].Fill( slimmedJetVtxNtrks               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetVtx3DVal                [selbin][j][lepbin].Fill( slimmedJetVtx3DVal               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetVtx3DSig                [selbin][j][lepbin].Fill( slimmedJetVtx3DSig               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetCSV2BJetTags            [selbin][j][lepbin].Fill( slimmedJetCSV2BJetTags           ->at( slimmedjetindex ), weight ); 
   h_slimmedJetJetProbabilityBJetTags  [selbin][j][lepbin].Fill( slimmedJetJetProbabilityBJetTags ->at( slimmedjetindex ), weight ); 
   h_slimmedJetpfCombinedMVAV2BJetTags [selbin][j][lepbin].Fill( slimmedJetpfCombinedMVAV2BJetTags->at( slimmedjetindex ), weight ); 
   h_slimmedJetPartonID                [selbin][j][lepbin].Fill( slimmedJetPartonID               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetHadFlvr                 [selbin][j][lepbin].Fill( slimmedJetHadFlvr                ->at( slimmedjetindex ), weight ); 

   //h_slimmedJetAlphaD                  [selbin][j][lepbin].Fill( slimmedJetAlphaD                 ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlphaMaxD               [selbin][j][lepbin].Fill( slimmedJetAlphaMaxD              ->at( slimmedjetindex ), weight ); 
   h_slimmedJetMedianLog10IPSig        [selbin][j][lepbin].Fill( slimmedJetMedianLog10IPSig       ->at( slimmedjetindex ), weight ); 
   h_slimmedJetSumIP                   [selbin][j][lepbin].Fill( slimmedJetSumIP                  ->at( slimmedjetindex ), weight ); 
   h_slimmedJetSumIPSig                [selbin][j][lepbin].Fill( slimmedJetSumIPSig               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetTrackAngle              [selbin][j][lepbin].Fill( slimmedJetTrackAngle             ->at( slimmedjetindex ), weight ); 
   h_slimmedJetLogTrackAngle           [selbin][j][lepbin].Fill( slimmedJetLogTrackAngle          ->at( slimmedjetindex ), weight ); 
   h_slimmedJetTotalTrackAngle         [selbin][j][lepbin].Fill( slimmedJetTotalTrackAngle        ->at( slimmedjetindex ), weight ); 

   h_slimmedJetAlphaMax_PV3onPV2       [selbin][j][lepbin].Fill( slimmedJetAlphaMax_PV3onPV2      ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlphaMax_PV3onChg       [selbin][j][lepbin].Fill( slimmedJetAlphaMax_PV3onChg      ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlphaMax_PV3onAll       [selbin][j][lepbin].Fill( slimmedJetAlphaMax_PV3onAll      ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlphaMax_PV2onChg       [selbin][j][lepbin].Fill( slimmedJetAlphaMax_PV2onChg      ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlphaMax_PV2onAll       [selbin][j][lepbin].Fill( slimmedJetAlphaMax_PV2onAll      ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlpha2Max_PV3onPV2      [selbin][j][lepbin].Fill( slimmedJetAlpha2Max_PV3onPV2     ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlpha2Max_PV3onChg      [selbin][j][lepbin].Fill( slimmedJetAlpha2Max_PV3onChg     ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlpha2Max_PV3onAll      [selbin][j][lepbin].Fill( slimmedJetAlpha2Max_PV3onAll     ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlpha2Max_PV2onChg      [selbin][j][lepbin].Fill( slimmedJetAlpha2Max_PV2onChg     ->at( slimmedjetindex ), weight ); 
   h_slimmedJetAlpha2Max_PV2onAll      [selbin][j][lepbin].Fill( slimmedJetAlpha2Max_PV2onAll     ->at( slimmedjetindex ), weight ); 

   h_slimmedJetGenJetEn                [selbin][j][lepbin].Fill( slimmedJetGenJetEn               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenJetPt                [selbin][j][lepbin].Fill( slimmedJetGenJetPt               ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenJetEta               [selbin][j][lepbin].Fill( slimmedJetGenJetEta              ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenJetPhi               [selbin][j][lepbin].Fill( slimmedJetGenJetPhi              ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenPartonID             [selbin][j][lepbin].Fill( slimmedJetGenPartonID            ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenEn                   [selbin][j][lepbin].Fill( slimmedJetGenEn                  ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenPt                   [selbin][j][lepbin].Fill( slimmedJetGenPt                  ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenEta                  [selbin][j][lepbin].Fill( slimmedJetGenEta                 ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenPhi                  [selbin][j][lepbin].Fill( slimmedJetGenPhi                 ->at( slimmedjetindex ), weight ); 
   h_slimmedJetGenPartonMomID          [selbin][j][lepbin].Fill( slimmedJetGenPartonMomID         ->at( slimmedjetindex ), weight ); 

   ///if(jetMedianLog10IPSig->size()>j&&jetAlphaMaxD->size()>j){ h_IpVAlpha  [selbin][j][lepbin].Fill(jetMedianLog10IPSig->at(j),jetAlphaMax->at(j), weight); }
   ///if(jetMedianLog10IPSig->size()>j&&jetPt->size()>j){ h_IpVjetPt    [selbin][j][lepbin].Fill( jetMedianLog10IPSig->at(j), jetPt->at(j), weight); }
   ///if(jetPt->size()>j&&jetAlphaMaxD->size()>j)       { h_AlphaVjetPt [selbin][j][lepbin].Fill( jetAlphaMax        ->at(j), jetPt->at(j), weight); }

  } // if( slimmedjet_list.size()>j )
 } // for(unsigned int j=0; j<jetmultnames.size()-1; ++j){

 // now fill inclusive
 // this should work, and if it doesn't that's a clue we screwed up somewhere earlier
 int incjetbin = (int) jetmultnames.size();
 for(int i =0; i<(int)slimmedjet_list.size(); i++)
 { 
  int slimmedjetindex = slimmedjet_list[i];
  h_slimmedJetPt                      [selbin][incjetbin][lepbin].Fill( slimmedJetPt                     ->at( slimmedjetindex ), weight ); 
  h_slimmedJetEn                      [selbin][incjetbin][lepbin].Fill( slimmedJetEn                     ->at( slimmedjetindex ), weight ); 
  h_slimmedJetEta                     [selbin][incjetbin][lepbin].Fill( slimmedJetEta                    ->at( slimmedjetindex ), weight ); 
  h_slimmedJetPhi                     [selbin][incjetbin][lepbin].Fill( slimmedJetPhi                    ->at( slimmedjetindex ), weight ); 
  h_slimmedJetRawPt                   [selbin][incjetbin][lepbin].Fill( slimmedJetRawPt                  ->at( slimmedjetindex ), weight ); 
  h_slimmedJetRawEn                   [selbin][incjetbin][lepbin].Fill( slimmedJetRawEn                  ->at( slimmedjetindex ), weight ); 
  h_slimmedJetArea                    [selbin][incjetbin][lepbin].Fill( slimmedJetArea                   ->at( slimmedjetindex ), weight ); 
  h_slimmedJetLeadTrackPt             [selbin][incjetbin][lepbin].Fill( slimmedJetLeadTrackPt            ->at( slimmedjetindex ), weight ); 
  h_slimmedJetLeadTrackPID            [selbin][incjetbin][lepbin].Fill( slimmedJetLeadTrackPID           ->at( slimmedjetindex ), weight ); 
  h_slimmedJetLeadTrackEta            [selbin][incjetbin][lepbin].Fill( slimmedJetLeadTrackEta           ->at( slimmedjetindex ), weight ); 
  h_slimmedJetLeadTrackPhi            [selbin][incjetbin][lepbin].Fill( slimmedJetLeadTrackPhi           ->at( slimmedjetindex ), weight ); 
  h_slimmedJetNConstituents           [selbin][incjetbin][lepbin].Fill( slimmedJetNConstituents          ->at( slimmedjetindex ), weight ); 
  h_slimmedJetVtxPt                   [selbin][incjetbin][lepbin].Fill( slimmedJetVtxPt                  ->at( slimmedjetindex ), weight ); 
  h_slimmedJetVtxMass                 [selbin][incjetbin][lepbin].Fill( slimmedJetVtxMass                ->at( slimmedjetindex ), weight ); 
  h_slimmedJetVtxNtrks                [selbin][incjetbin][lepbin].Fill( slimmedJetVtxNtrks               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetVtx3DVal                [selbin][incjetbin][lepbin].Fill( slimmedJetVtx3DVal               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetVtx3DSig                [selbin][incjetbin][lepbin].Fill( slimmedJetVtx3DSig               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetCSV2BJetTags            [selbin][incjetbin][lepbin].Fill( slimmedJetCSV2BJetTags           ->at( slimmedjetindex ), weight ); 
  h_slimmedJetJetProbabilityBJetTags  [selbin][incjetbin][lepbin].Fill( slimmedJetJetProbabilityBJetTags ->at( slimmedjetindex ), weight ); 
  h_slimmedJetpfCombinedMVAV2BJetTags [selbin][incjetbin][lepbin].Fill( slimmedJetpfCombinedMVAV2BJetTags->at( slimmedjetindex ), weight ); 
  h_slimmedJetPartonID                [selbin][incjetbin][lepbin].Fill( slimmedJetPartonID               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetHadFlvr                 [selbin][incjetbin][lepbin].Fill( slimmedJetHadFlvr                ->at( slimmedjetindex ), weight ); 

  //h_slimmedJetAlphaD                  [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaD                 ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlphaMaxD               [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaMaxD              ->at( slimmedjetindex ), weight ); 
  h_slimmedJetMedianLog10IPSig        [selbin][incjetbin][lepbin].Fill( slimmedJetMedianLog10IPSig       ->at( slimmedjetindex ), weight ); 
  h_slimmedJetSumIP                   [selbin][incjetbin][lepbin].Fill( slimmedJetSumIP                  ->at( slimmedjetindex ), weight ); 
  h_slimmedJetSumIPSig                [selbin][incjetbin][lepbin].Fill( slimmedJetSumIPSig               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetTrackAngle              [selbin][incjetbin][lepbin].Fill( slimmedJetTrackAngle             ->at( slimmedjetindex ), weight ); 
  h_slimmedJetLogTrackAngle           [selbin][incjetbin][lepbin].Fill( slimmedJetLogTrackAngle          ->at( slimmedjetindex ), weight ); 
  h_slimmedJetTotalTrackAngle         [selbin][incjetbin][lepbin].Fill( slimmedJetTotalTrackAngle        ->at( slimmedjetindex ), weight ); 

  h_slimmedJetAlphaMax_PV3onPV2       [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaMax_PV3onPV2      ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlphaMax_PV3onChg       [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaMax_PV3onChg      ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlphaMax_PV3onAll       [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaMax_PV3onAll      ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlphaMax_PV2onChg       [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaMax_PV2onChg      ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlphaMax_PV2onAll       [selbin][incjetbin][lepbin].Fill( slimmedJetAlphaMax_PV2onAll      ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlpha2Max_PV3onPV2      [selbin][incjetbin][lepbin].Fill( slimmedJetAlpha2Max_PV3onPV2     ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlpha2Max_PV3onChg      [selbin][incjetbin][lepbin].Fill( slimmedJetAlpha2Max_PV3onChg     ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlpha2Max_PV3onAll      [selbin][incjetbin][lepbin].Fill( slimmedJetAlpha2Max_PV3onAll     ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlpha2Max_PV2onChg      [selbin][incjetbin][lepbin].Fill( slimmedJetAlpha2Max_PV2onChg     ->at( slimmedjetindex ), weight ); 
  h_slimmedJetAlpha2Max_PV2onAll      [selbin][incjetbin][lepbin].Fill( slimmedJetAlpha2Max_PV2onAll     ->at( slimmedjetindex ), weight ); 

  h_slimmedJetGenJetEn                [selbin][incjetbin][lepbin].Fill( slimmedJetGenJetEn               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenJetPt                [selbin][incjetbin][lepbin].Fill( slimmedJetGenJetPt               ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenJetEta               [selbin][incjetbin][lepbin].Fill( slimmedJetGenJetEta              ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenJetPhi               [selbin][incjetbin][lepbin].Fill( slimmedJetGenJetPhi              ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenPartonID             [selbin][incjetbin][lepbin].Fill( slimmedJetGenPartonID            ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenEn                   [selbin][incjetbin][lepbin].Fill( slimmedJetGenEn                  ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenPt                   [selbin][incjetbin][lepbin].Fill( slimmedJetGenPt                  ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenEta                  [selbin][incjetbin][lepbin].Fill( slimmedJetGenEta                 ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenPhi                  [selbin][incjetbin][lepbin].Fill( slimmedJetGenPhi                 ->at( slimmedjetindex ), weight ); 
  h_slimmedJetGenPartonMomID          [selbin][incjetbin][lepbin].Fill( slimmedJetGenPartonMomID         ->at( slimmedjetindex ), weight ); 

  /////std::cout<<"fill 2D"<<std::endl;
  ///if(jetMedianLog10IPSig->size()>jindex&&jetAlphaMaxD->size()>jindex){ h_IpVAlpha [selbin][j][lepbin].Fill(jetMedianLog10IPSig->at(jindex),jetAlphaMax->at(jindex), weight); }
  ///if(jetMedianLog10IPSig->size()>jindex&&jetPt->size()>jindex){ h_IpVjetPt    [selbin][j][lepbin].Fill( jetMedianLog10IPSig->at(jindex), jetPt->at(jindex), weight); }
  ///if(jetPt->size()>jindex&&jetAlphaMaxD->size()>jindex)       { h_AlphaVjetPt [selbin][j][lepbin].Fill( jetAlphaMax        ->at(jindex), jetPt->at(jindex), weight); }
  /////std::cout<<"fill 2D end"<<std::endl;

 } //  for(unsigned int i =0; i<jet_list.size(); i++)

 return kTRUE;
} //end fill histograms

//----------------------------writeSlimmedJetHistograms
Bool_t analyzer_signal::writeSlimmedJetHistograms(int selbin, int lepbin)
{
 //printf("writeSlimmedJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){
  h_slimmedJetPt                      [selbin][j][lepbin].Write(); 
  h_slimmedJetEn                      [selbin][j][lepbin].Write(); 
  h_slimmedJetEta                     [selbin][j][lepbin].Write(); 
  h_slimmedJetPhi                     [selbin][j][lepbin].Write(); 
  h_slimmedJetRawPt                   [selbin][j][lepbin].Write(); 
  h_slimmedJetRawEn                   [selbin][j][lepbin].Write(); 
  h_slimmedJetArea                    [selbin][j][lepbin].Write(); 
  h_slimmedJetLeadTrackPt             [selbin][j][lepbin].Write(); 
  h_slimmedJetLeadTrackPID            [selbin][j][lepbin].Write(); 
  h_slimmedJetLeadTrackEta            [selbin][j][lepbin].Write(); 
  h_slimmedJetLeadTrackPhi            [selbin][j][lepbin].Write(); 
  h_slimmedJetNConstituents           [selbin][j][lepbin].Write(); 
  h_slimmedJetVtxPt                   [selbin][j][lepbin].Write(); 
  h_slimmedJetVtxMass                 [selbin][j][lepbin].Write(); 
  h_slimmedJetVtxNtrks                [selbin][j][lepbin].Write(); 
  h_slimmedJetVtx3DVal                [selbin][j][lepbin].Write(); 
  h_slimmedJetVtx3DSig                [selbin][j][lepbin].Write(); 
  h_slimmedJetCSV2BJetTags            [selbin][j][lepbin].Write(); 
  h_slimmedJetJetProbabilityBJetTags  [selbin][j][lepbin].Write(); 
  h_slimmedJetpfCombinedMVAV2BJetTags [selbin][j][lepbin].Write(); 
  h_slimmedJetPartonID                [selbin][j][lepbin].Write(); 
  h_slimmedJetHadFlvr                 [selbin][j][lepbin].Write(); 

  //h_slimmedJetAlphaD                  [selbin][j][lepbin].Write(); 
  h_slimmedJetAlphaMaxD               [selbin][j][lepbin].Write(); 
  h_slimmedJetMedianLog10IPSig        [selbin][j][lepbin].Write(); 
  h_slimmedJetSumIP                   [selbin][j][lepbin].Write(); 
  h_slimmedJetSumIPSig                [selbin][j][lepbin].Write(); 
  h_slimmedJetTrackAngle              [selbin][j][lepbin].Write(); 
  h_slimmedJetLogTrackAngle           [selbin][j][lepbin].Write(); 
  h_slimmedJetTotalTrackAngle         [selbin][j][lepbin].Write(); 

  h_slimmedJetAlphaMax_PV3onPV2       [selbin][j][lepbin].Write(); 
  h_slimmedJetAlphaMax_PV3onChg       [selbin][j][lepbin].Write(); 
  h_slimmedJetAlphaMax_PV3onAll       [selbin][j][lepbin].Write(); 
  h_slimmedJetAlphaMax_PV2onChg       [selbin][j][lepbin].Write(); 
  h_slimmedJetAlphaMax_PV2onAll       [selbin][j][lepbin].Write(); 
  h_slimmedJetAlpha2Max_PV3onPV2      [selbin][j][lepbin].Write(); 
  h_slimmedJetAlpha2Max_PV3onChg      [selbin][j][lepbin].Write(); 
  h_slimmedJetAlpha2Max_PV3onAll      [selbin][j][lepbin].Write(); 
  h_slimmedJetAlpha2Max_PV2onChg      [selbin][j][lepbin].Write(); 
  h_slimmedJetAlpha2Max_PV2onAll      [selbin][j][lepbin].Write(); 

  h_slimmedJetGenJetEn                [selbin][j][lepbin].Write(); 
  h_slimmedJetGenJetPt                [selbin][j][lepbin].Write(); 
  h_slimmedJetGenJetEta               [selbin][j][lepbin].Write(); 
  h_slimmedJetGenJetPhi               [selbin][j][lepbin].Write(); 
  h_slimmedJetGenPartonID             [selbin][j][lepbin].Write(); 
  h_slimmedJetGenEn                   [selbin][j][lepbin].Write(); 
  h_slimmedJetGenPt                   [selbin][j][lepbin].Write(); 
  h_slimmedJetGenEta                  [selbin][j][lepbin].Write(); 
  h_slimmedJetGenPhi                  [selbin][j][lepbin].Write(); 
  h_slimmedJetGenPartonMomID          [selbin][j][lepbin].Write(); 

  // h_AODCaloJetPt               [selbin][j][lepbin].Write(); 
  // h_AODCaloJetEta              [selbin][j][lepbin].Write(); 
  // h_AODCaloJetPhi              [selbin][j][lepbin].Write(); 
  // h_AODCaloJetAlphaMax         [selbin][j][lepbin].Write(); 
  // h_AODCaloJetAlphaMax2        [selbin][j][lepbin].Write(); 
  // h_AODCaloJetAlphaMaxPrime    [selbin][j][lepbin].Write(); 
  // h_AODCaloJetAlphaMaxPrime2   [selbin][j][lepbin].Write(); 
  // h_AODCaloJetBeta             [selbin][j][lepbin].Write(); 
  // h_AODCaloJetBeta2            [selbin][j][lepbin].Write(); 

  // h_IpVAlpha                   [selbin][j][lepbin].Write(); 
  // h_IpVjetPt                   [selbin][j][lepbin].Write(); 
  // h_AlphaVjetPt                [selbin][j][lepbin].Write(); 
 }

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
    h_AODCaloJetMedianLog10TrackAngle          [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10TrackAngle          , "AODCaloJetMedianLog10TrackAngle         ", 30, -3, 3 ); 
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
/*
 printf(" AODCaloJetPt                            %u\n",  AODCaloJetPt                            ->size() ); 
 printf(" AODCaloJetEta                           %u\n",  AODCaloJetEta                           ->size() ); 
 printf(" AODCaloJetPhi                           %u\n",  AODCaloJetPhi                           ->size() ); 
 printf(" AODCaloJetAlphaMax                      %u\n",  AODCaloJetAlphaMax                      ->size() ); 
 printf(" AODCaloJetAlphaMax2                     %u\n",  AODCaloJetAlphaMax2                     ->size() ); 
 printf(" AODCaloJetAlphaMaxPrime                 %u\n",  AODCaloJetAlphaMaxPrime                 ->size() ); 
 printf(" AODCaloJetAlphaMaxPrime2                %u\n",  AODCaloJetAlphaMaxPrime2                ->size() ); 
 printf(" AODCaloJetBeta                          %u\n",  AODCaloJetBeta                          ->size() ); 
 printf(" AODCaloJetBeta2                         %u\n",  AODCaloJetBeta2                         ->size() ); 
 printf(" AODCaloJetSumIP                         %u\n",  AODCaloJetSumIP                         ->size() ); 
 printf(" AODCaloJetSumIPSig                      %u\n",  AODCaloJetSumIPSig                      ->size() ); 
 printf(" AODCaloJetMedianIP                      %u\n",  AODCaloJetMedianIP                      ->size() ); 
 printf(" AODCaloJetMedianLog10IPSig              %u\n",  AODCaloJetMedianLog10IPSig              ->size() ); 
 printf(" AODCaloJetTrackAngle                    %u\n",  AODCaloJetTrackAngle                    ->size() ); 
 printf(" AODCaloJetLogTrackAngle                 %u\n",  AODCaloJetLogTrackAngle                 ->size() ); 
 printf(" AODCaloJetMedianLog10TrackAngle         %u\n",  AODCaloJetMedianLog10TrackAngle         ->size() ); 
 printf(" AODCaloJetTotalTrackAngle               %u\n",  AODCaloJetTotalTrackAngle               ->size() ); 
 printf(" AODCaloJetAvfVx                         %u\n",  AODCaloJetAvfVx                         ->size() ); 
 printf(" AODCaloJetAvfVy                         %u\n",  AODCaloJetAvfVy                         ->size() ); 
 printf(" AODCaloJetAvfVz                         %u\n",  AODCaloJetAvfVz                         ->size() ); 
 printf(" AODCaloJetAvfVertexTotalChiSquared      %u\n",  AODCaloJetAvfVertexTotalChiSquared      ->size() ); 
 printf(" AODCaloJetAvfVertexDegreesOfFreedom     %u\n",  AODCaloJetAvfVertexDegreesOfFreedom     ->size() ); 
 printf(" AODCaloJetAvfVertexChi2NDoF             %u\n",  AODCaloJetAvfVertexChi2NDoF             ->size() ); 
 printf(" AODCaloJetAvfVertexDistanceToBeam       %u\n",  AODCaloJetAvfVertexDistanceToBeam       ->size() ); 
 printf(" AODCaloJetAvfVertexTransverseError      %u\n",  AODCaloJetAvfVertexTransverseError      ->size() ); 
 printf(" AODCaloJetAvfVertexTransverseSig        %u\n",  AODCaloJetAvfVertexTransverseSig        ->size() ); 
 printf(" AODCaloJetAvfVertexDeltaEta             %u\n",  AODCaloJetAvfVertexDeltaEta             ->size() ); 
 printf(" AODCaloJetAvfVertexDeltaPhi             %u\n",  AODCaloJetAvfVertexDeltaPhi             ->size() ); 
 printf(" AODCaloJetAvfVertexRecoilPt             %u\n",  AODCaloJetAvfVertexRecoilPt             ->size() ); 
 printf(" AODCaloJetAvfVertexTrackMass            %u\n",  AODCaloJetAvfVertexTrackMass            ->size() ); 
 printf(" AODCaloJetAvfVertexTrackEnergy          %u\n",  AODCaloJetAvfVertexTrackEnergy          ->size() ); 
 printf(" AODCaloJetAvfBeamSpotDeltaPhi           %u\n",  AODCaloJetAvfBeamSpotDeltaPhi           ->size() ); 
 printf(" AODCaloJetAvfBeamSpotRecoilPt           %u\n",  AODCaloJetAvfBeamSpotRecoilPt           ->size() ); 
 printf(" AODCaloJetAvfBeamSpotMedianDeltaPhi     %u\n",  AODCaloJetAvfBeamSpotMedianDeltaPhi     ->size() ); 
 printf(" AODCaloJetAvfBeamSpotLog10MedianDeltaPhi%u\n",  AODCaloJetAvfBeamSpotLog10MedianDeltaPhi->size() ); 
 printf(" AODCaloJetNCleanMatchedTracks           %u\n",  AODCaloJetNCleanMatchedTracks           ->size() ); 
 printf(" AODCaloJetSumHitsInFrontOfVert          %u\n",  AODCaloJetSumHitsInFrontOfVert          ->size() ); 
 printf(" AODCaloJetSumMissHitsAfterVert          %u\n",  AODCaloJetSumMissHitsAfterVert          ->size() ); 
 printf(" AODCaloJetHitsInFrontOfVertPerTrack     %u\n",  AODCaloJetHitsInFrontOfVertPerTrack     ->size() ); 
 printf(" AODCaloJetMissHitsAfterVertPerTrack     %u\n",  AODCaloJetMissHitsAfterVertPerTrack     ->size() ); 
 printf(" AODCaloJetAvfDistToPV                   %u\n",  AODCaloJetAvfDistToPV                   ->size() ); 
 printf(" AODCaloJetAvfVertexDeltaZtoPV           %u\n",  AODCaloJetAvfVertexDeltaZtoPV           ->size() ); 
 printf(" AODCaloJetAvfVertexDeltaZtoPV2          %u\n",  AODCaloJetAvfVertexDeltaZtoPV2          ->size() ); 
*/

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
////  h_AODCaloJetTrackAngle                     [selbin][incjetbin][lepbin].Fill( AODCaloJetTrackAngle                     ->at( aodcalojetindex ), weight );  
////  h_AODCaloJetLogTrackAngle                  [selbin][incjetbin][lepbin].Fill( AODCaloJetLogTrackAngle                  ->at( aodcalojetindex ), weight );  
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
  h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][j][lepbin].Write(); 

 }

 return kTRUE;
}

// trigger ------------------------
Bool_t analyzer_signal::askPassSingleEle()
{
 //printf("HLT_Ele23Loose %llu \n", HLT_Ele23Loose) ;
 //printf("HLT_Ele27Tight %llu \n", HLT_Ele27Tight) ;
 //printf("HLT_Ele17Ele12 %llu \n", HLT_Ele17Ele12) ;
 //printf("HLT_Ele23Ele12 %llu \n", HLT_Ele23Ele12) ;
 //printf("HLT_IsoMu22    %llu \n", HLT_IsoMu22   ) ;
 //printf("HLT_IsoTkMu22  %llu \n", HLT_IsoTkMu22 ) ;
 //printf("HLT_Mu17Mu8    %llu \n", HLT_Mu17Mu8   ) ;
 //printf("HLT_Mu17TkMu8  %llu \n", HLT_Mu17TkMu8 ) ;

 Bool_t doespass = kFALSE;
 if(electron_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (HLT_Ele23Loose > 0) || (HLT_Ele27Tight > 0) );
 } 
 return doespass;
}

Bool_t analyzer_signal::askPassDoubleEle()
{
 Bool_t doespass = kFALSE;
 if(electron_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (HLT_Ele17Ele12 > 0) || (HLT_Ele23Ele12 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_signal::askPassSingleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (HLT_IsoMu22 > 0) || (HLT_IsoTkMu22 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_signal::askPassDoubleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (HLT_Mu17Mu8 > 0) || (HLT_Mu17TkMu8 > 0) ) ;
 } 
 return doespass;
}

// signal/control region selections ------------------------
Bool_t analyzer_signal::askPassSig()
{
 Bool_t doespass = kTRUE;
 //if( (passSingleEle || passSingleMu ) ){
 if( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) ){
  n_passSig++;
  if( passSingleEle || passDoubleEle ) { n_ele_passSig++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passSig++; }
  //if( passSingleEle ) { n_ele_passSig++; }
  //else if( passSingleMu ) { n_mu_passSig++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassZH()
{
 Bool_t doespass = kFALSE;

//*// if ( passGoodVtx
//*//     && passZWindow
//*//     && passPTOSSFg50
//*//     && passOneJet
//*//     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
//*//     //&& (passSingleEle || passSingleMu ) 
//*//    )
 if ( passGoodVtx
    )
 { doespass = kTRUE; n_passZH++;
  if( passSingleEle || passDoubleEle ) { n_ele_passZH++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passZH++; }
  //if( passSingleEle ) { n_ele_passZH++; }
  //else if( passSingleMu ) { n_mu_passZH++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassDY()
{
 Bool_t doespass = kFALSE;

//*// if ( passGoodVtx
//*//     && passZWindow
//*//     && !passPTOSSFg50
//*//     && passOneJet
//*//     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
//*//     //&& (passSingleEle || passSingleMu) 
//*//    )
 if ( passGoodVtx
     && passOSSF
    )
 { doespass = kTRUE; n_passDY++; 
  //printf("\n PASS DY Event %lld\n", event);
  if( passSingleEle || passDoubleEle ) { n_ele_passDY++; } // printf("\n PASS SingleEle Event %lld\n", event); }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passDY++;  } // printf("\n PASS SingleMu Event %lld\n", event); }
  //if( passSingleEle ) { n_ele_passDY++; } // printf("\n PASS SingleEle Event %lld\n", event); }
  //else if( passSingleMu ) { n_mu_passDY++;  } // printf("\n PASS SingleMu Event %lld\n", event); }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassOffZ()
{
 Bool_t doespass = kFALSE;

//*// if ( passGoodVtx
//*//     && !passZWindow
//*//     && passOSSF
//*//     && passOneJet
//*//     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu)
//*//     //&& (passSingleEle || passSingleMu)
//*//    )
 if ( passGoodVtx
     && passOSSF
     && passZWindow
    )
 { doespass = kTRUE; n_passOffZ++;
  if( passSingleEle || passDoubleEle ) { n_ele_passOffZ++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passOffZ++; }
  //if( passSingleEle ) { n_ele_passOffZ++; }
  //else if( passSingleMu ) { n_mu_passOffZ++; }
 }
 return doespass;
}

Bool_t analyzer_signal::askPassNoPair()
{
 Bool_t doespass = kFALSE;

//*// if ( passGoodVtx
//*//     && !passZWindow
//*//     && !passOSSF
//*//     && passOneJet
//*//     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu)
//*//     //&& (passSingleEle || passSingleMu)
//*//    )
 if ( passGoodVtx
     && passOSSF
     && passZWindow
     && passOneJet
    )
 { doespass = kTRUE; n_passNoPair++;
  if( passSingleEle || passDoubleEle ) { n_ele_passNoPair++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passNoPair++; }
  //if( passSingleEle ) { n_ele_passNoPair++; }
  //else if( passSingleMu ) { n_mu_passNoPair++; }
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

//// #brokenphotons
////-------------------------getPhotonPt
//Float_t analyzer_signal::getPhotonPt(int idnr, TString sysbinname){
//
//      Float_t photonenergy = phoSCEn->at(idnr);
//      if(sysbinname=="_PESUp"  ){ photonenergy*=(1. + 0.015); }
//      if(sysbinname=="_PESDown"){ photonenergy*=(1. - 0.015); }
//
//      Float_t phoPt = photonenergy/TMath::CosH( (*phoSCEta)[idnr] );
//
//  return phoPt;
//
//}

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

 for(int i = 0; i < muPt->size(); i++) 
 {    
  //  printf(" Muon %i    %i %i %i %i %i \n",i
  //        ,muIDbit->at(i) >> 0 & 0x1 
  //        ,muIDbit->at(i) >> 1 & 0x1 
  //        ,muIDbit->at(i) >> 2 & 0x1 
  //        ,muIDbit->at(i) >> 3 & 0x1 
  //        ,muIDbit->at(i) >> 4 & 0x1 
  //        );       

  Float_t muonPt = getMuonPt(i,sysbinname);
  bool pass_kin = muonPt > muPtCut && ( fabs(muEta->at(i)) < muEtaCut ) ;

  bool pass_bit = muIDbit->at(i) >> bitnr & 0x1 == 1;      

  if (muoid = "Loose")  muoisoval = 0.25 ;
  if (muoid = "Medium") muoisoval = 0.25 ;
  if (muoid = "Tight")  muoisoval = 0.15 ;
  bool pass_iso = muPFdBetaIsolation->at(i) > muoisoval ;

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

 for(int i = 0; i < nEle; i++) 
 {    

  Float_t electronPt = getElectronPt(i,sysbinname);
  bool pass_kin = electronPt > elePtCut && ( fabs(eleEta->at(i)) < eleEtaCut ) ;

  bool pass_bit = eleIDbit->at(i) >> bitnr & 0x1 == 1;      

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

//-------------------------slimmedjet_passID
std::vector<int> analyzer_signal::slimmedjet_passID( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname) {

  std::vector<int> jetlist;

  //for(int i = 0; i < (int)slimmedJetPt->size() ; i++)
  for(int i = 0; i < nSlimmedJets; i++)
  {

   bool pass_overlap = true;
   //// #brokenphotons
   //// check overlap with photons
   //if(photon_list.size()>0){
   // for(int d=0; d<photon_list.size(); ++d){
   //  int phoindex = photon_list[d];
   //  if(phoindex<= (phoEta->size()-1)&&phoindex<= (phoPhi->size()-1)){  //  <---- shouldn't be needed?
   //   if( dR( phoEta->at(phoindex),phoPhi->at(phoindex), slimmedJetEta->at(i),slimmedJetPhi->at(i) ) < objcleandRcut ){
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
     if( dR( eleEta->at(eleindex),elePhi->at(eleindex), slimmedJetEta->at(i),slimmedJetPhi->at(i) ) < objcleandRcut )
     {
      pass_overlap=false; // printf(" OL w electron\n");
     } // if overlap
    }//end electrons
   } // if electrons
   //check overlap with muons
   if(muon_list.size()>0){
    for(int d=0; d<muon_list.size(); ++d){
     int muindex = muon_list[d];
     if(muindex<= (muEta->size()-1)&&muindex<= (muPhi->size()-1)){
      if( dR( muEta->at(muindex),muPhi->at(muindex), slimmedJetEta->at(i),slimmedJetPhi->at(i) ) < objcleandRcut )
      {
       pass_overlap=false; //printf(" OL w muon\n");
      } // if overlap
     }
    }//end muons
   } // if muons

   bool pass_id  ;
   pass_id  = slimmedJetID->at(i) >> bitnr & 0x1 == 1;      
              
   bool pass_kin = slimmedJetPt->at(i) > jetPtCut && ( fabs(slimmedJetEta->at(i)) < jetEtaCut ) ;

   bool pass_signal = slimmedJetGenPartonMomID->at(i) > 9000000 ;//9000006 i think?
              
   //if( pass_id && pass_kin && pass_overlap )
   if( pass_id && pass_kin && pass_overlap /*&& pass_signal*/)
   {
    nSelectedSlimmedJet++;
    jetlist.push_back(i);
   } // if pass_bit && pass_kin
  }// for(int i = 0; i < nJet; i++)

  return jetlist;

}
 

void analyzer_signal::tagger(){
  OPT_Event.push_back(event);
  OPT_EventWeight.push_back(event_weight);
  //OPT_nJets.push_back(aodcalojet_list.size());
    for(int i = 0; i<aodcalojet_list.size(); i++){
      if(aodcalojet_list.size()>0){
      OPT_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojet_list[i]));
      OPT_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojet_list[i]));
      OPT_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojet_list[i]));
      }
      else{
      OPT_AODCaloJetMedianLog10IPSig      .push_back(-5);
      OPT_AODCaloJetMedianLog10TrackAngle .push_back(-5);
      OPT_AODCaloJetAlphaMax              .push_back(-5);
      }
    }//looping through all the jets
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
     if( dR( eleEta->at(eleindex),elePhi->at(eleindex), AODCaloJetEta->at(i),AODCaloJetPhi->at(i) ) < objcleandRcut )
     {
      pass_overlap=false; // printf(" OL w electron\n");
     } // if overlap
    }//end electrons
   } // if electrons
   //check overlap with muons
   if(muon_list.size()>0){
    for(int d=0; d<muon_list.size(); ++d){
     int muindex = muon_list[d];
     if(muindex<= (muEta->size()-1)&&muindex<= (muPhi->size()-1)){
      if( dR( muEta->at(muindex),muPhi->at(muindex), AODCaloJetEta->at(i),AODCaloJetPhi->at(i) ) < objcleandRcut )
      {
       pass_overlap=false; //printf(" OL w muon\n");
      } // if overlap
     }
    }//end muons
   } // if muons

   bool pass_kin = AODCaloJetPt->at(i) > jetPtCut && ( fabs(AODCaloJetEta->at(i)) < jetEtaCut ) ;
              
   if( pass_kin && pass_overlap)
   {
    nSelectedAODCaloJet++;
    jetlist.push_back(i);
   } // if pass_bit && pass_kin
  }// for(int i = 0; i < nJet; i++)

  return jetlist;

}


//-------------------------photon_passLooseID
std::vector<int> analyzer_signal::photon_passID( int bitnr, double phoPtCut, double phoEtaCut, TString sysbinname){

 std::vector<int> pholist;
 pholist.clear();

 ////Loop over photons                   
 //for(int p=0;p<nPho;p++)
 //{    
 // Float_t thephoPt = getPhotonPt(p,sysbinname);
 // //Float_t thephoPt =  phoSCRawE->at(p) / TMath::CosH( (*phoSCEta)[p] ); //  phoPt->at(p); 
 // Float_t thephoEta = phoSCEta->at(p);                                  //  phoEta->at(p);

 // //bool kinematic = phoPt > phoPtCut && fabs((*phoSCEta)[p])<phoEtaCut;
 // bool kinematic = thephoPt > phoPtCut && fabs(thephoEta)<phoEtaCut;

 // bool pass_bit = phoIDbit->at(p) >> bitnr & 0x1 == 1; 
 // //printf(" photon %i %i %i\n",p,bitnr,pass_bit);

 // if( kinematic && pass_bit){
 //  nSelectedPho++;
 //  //printf("selected aphoton\n");
 //  pholist.push_back(p);
 // }    
 //}    

 return pholist;

}

////////-------------------------jet_matchToMiniAOD
//////std::vector<int> analyzer_signal::jet_matchToMiniAOD( TString jettype ){
//////
//////  std::vector<int> tmpAODjetlist;
//////
//////  // loop over miniAOD jet list (already passed selections)
//////  int lengthjets = (int)jet_list.size();
//////  for(int i = 0; i < lengthjets; i++)
//////  {
//////
//////   // find index corresponding to miniAOD jet
//////   int jetindex = jet_list[i];
//////   // miniAOD jet parameters
//////   float miniAODjetPt  = jetPt->at(jetindex); 
//////   float miniAODjetEta = jetEta->at(jetindex); 
//////   float miniAODjetPhi = jetPhi->at(jetindex); 
//////
//////   // initialize AOD jet parameters
//////   float AODjetPt;
//////   float AODjetEta;
//////   float AODjetPhi;
//////
//////   // loop over AOD jets and look for match via deltaR
//////   int nAODjets;
//////   if( jettype=="calo" ){nAODjets = (int)AODCaloJetPt->size();}
//////   //if( jettype=="calo" ){nAODjets = (int)AODPFJetPt->size();} // do other jets
//////   //if( jettype=="calo" ){nAODjets = (int)AODPFchsJetPt->size();}
//////   for( int j = 0; j<nAODjets; j++ ) {
//////
//////    if( jettype=="calo" ){
//////     AODjetPt  = AODCaloJetPt ->at(j) ;
//////     AODjetEta = AODCaloJetEta->at(j) ;
//////     AODjetPhi = AODCaloJetPhi->at(j) ;
//////    }
//////
////////    printf(" miniAOD: %f %f %f\n",
////////     miniAODjetPt , 
////////     miniAODjetEta, 
////////     miniAODjetPhi );
////////
////////    printf(" AOD:     %f %f %f\n\n",
////////     AODjetPt , 
////////     AODjetEta, 
////////     AODjetPhi );
//////
//////    //AODPFJetPt     
//////    //AODPFJetEta    
//////    //AODPFJetPhi    
//////
//////    //AODPFchsJetPt  
//////    //AODPFchsJetEta 
//////    //AODPFchsJetPhi 
//////
//////    // if find match (AOD,miniAOD), add AODjet to list, break loop over AOD jets 
//////    // still have loop over miniAOD jets, so keep going and find next one
//////    if( dR( miniAODjetEta, miniAODjetPhi, AODjetEta, AODjetPhi) < jetmatchdRcut ) {  
//////       tmpAODjetlist.push_back(j); break;
//////    }
//////
//////   }
//////  }
//////
//////  return tmpAODjetlist;
//////
//////}

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


void analyzer_signal::loadPUWeight(){
 printf("loading PU weight \n");
 //char* cCMSSW_BASE = std::getenv("CMSSW_BASE");
 //TString CMSSW_BASE = (TString)cCMSSW_BASE;

 //TString filename = CMSSW_BASE+"/src/LLDJstandalones/data/puWeights_69200_24jan2017.root" ;
 TString filename = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/data/puWeights_69200_24jan2017.root" ;
 TFile* file_puweights = new TFile( filename ) ;
 printf(" filename: %s\n",filename.Data());
 PUWeights = (TH1F*)file_puweights->Get("h_PUweight")->Clone("PUWeights");
 return ;
}

void analyzer_signal::loadElectronWeight(){
 printf("loading Electron weight \n");
 //char* cCMSSW_BASE = std::getenv("CMSSW_BASE");
 //TString CMSSW_BASE = (TString)cCMSSW_BASE;

 //TString filename = CMSSW_BASE+"/src/LLDJstandalones/data/egammaEffi_MoriondBH_ele"+eleid+".root" ;
 TString filename = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/data/egammaEffi_MoriondBH_ele"+eleid+".root" ;
 TFile* file_eleweights = new TFile( filename ) ;
 printf(" filename: %s\n",filename.Data());
 EleWeights = (TH2F*)file_eleweights->Get("EGamma_SF2D")->Clone("EleWeights");
 return ;
}

Double_t analyzer_signal::makePUWeight(){
 Int_t tmpbin = PUWeights->GetBin(nTruePU);
 Double_t tmpweight = PUWeights->GetBinContent(tmpbin);
 //printf("making PU weight for %i , %i, %f \n", nTruePU,tmpbin,tmpweight);
 return tmpweight;
}

Double_t analyzer_signal::makeElectronWeight(){

 Double_t tmpsf;
 tmpsf = 1.;

 //check overlap with electrons
 if(electron_list.size()>0){
  //printf(" esize: %lu\n",electron_list.size());
  //printf(" esceta: %lu\n",eleSCEta->size());
  //printf(" ept: %lu\n",elePt->size());
  for(int d=0; d<electron_list.size(); ++d){
   //printf(" brgin looping over electrons\n");
   int eleindex = electron_list[d];
   //printf(" d: %i eleindex: %i\n",d,eleindex);
   //printf(" ele sceta %f pt %f \n",eleSCEta->at(eleindex),elePt->at(eleindex));
   Float_t eeta = eleSCEta->at(eleindex);
   Float_t ept  = elePt->at(eleindex);
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
//   printf( " photon %d : pt %.1f eta %.1f phi %.1f\n", i, phoPt->at(phoindex), phoEta->at(phoindex), phoPhi->at(phoindex));
//  }

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   printf( " electron %d : pt %.1f eta %.1f phi %.1f\n", i, elePt->at(eleindex), eleEta->at(eleindex), elePhi->at(eleindex));
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   printf( " muon %d : pt %.1f eta %.1f phi %.1f\n", i, muPt->at(muindex), muEta->at(muindex), muPhi->at(muindex));

   printf(" muonid %d    %d %d %d %d %d \n",i
         ,muIDbit->at(i) >> 0 & 0x1 
         ,muIDbit->at(i) >> 1 & 0x1 
         ,muIDbit->at(i) >> 2 & 0x1 
         ,muIDbit->at(i) >> 3 & 0x1 
         ,muIDbit->at(i) >> 4 & 0x1 
         );       
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

  for(int i=0; i<slimmedjet_list.size(); ++i){
   int jetindex = slimmedjet_list[i];
   printf( " slimmed jet %d : pt %.1f eta %.1f phi %.1f\n", i, slimmedJetPt->at(jetindex), slimmedJetEta->at(jetindex), slimmedJetPhi->at(jetindex));
  } 

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int jetindex = aodcalojet_list[i];
   printf( " aodcalo jet %d : pt %.1f eta %.1f phi %.1f\n", i, AODCaloJetPt->at(jetindex), AODCaloJetEta->at(jetindex), AODCaloJetPhi->at(jetindex));
  } 

  printf( " met %.1f mephi %.1f\n", themet, themephi);
  printf( " nvtx %d \n", nVtx);
  printf( " htall %.1f htaodcalojets %.1f htslimmedjets %.1f \n", htall, htaodcalojets, htslimmedjets);

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

 printf("HLT_Ele23Loose %llu \n", HLT_Ele23Loose) ;
 printf("HLT_Ele27Tight %llu \n", HLT_Ele27Tight) ;
 printf("HLT_Ele17Ele12 %llu \n", HLT_Ele17Ele12) ;
 printf("HLT_Ele23Ele12 %llu \n", HLT_Ele23Ele12) ;
 printf("HLT_IsoMu22    %llu \n", HLT_IsoMu22   ) ;
 printf("HLT_IsoTkMu22  %llu \n", HLT_IsoTkMu22 ) ;
 printf("HLT_Mu17Mu8    %llu \n", HLT_Mu17Mu8   ) ;
 printf("HLT_Mu17TkMu8  %llu \n", HLT_Mu17TkMu8 ) ;
 return;

}

