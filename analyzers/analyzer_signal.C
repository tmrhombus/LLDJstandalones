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
 number_sig =0.0;
 number_bkg = 0.0;
 nmatched = 0;
 nunmatched = 0;

 drcut = 0.4;

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

 if (jetid = "Loose")  jetidbit=0;
 if (jetid = "Tight")  jetidbit=1;

 if(isMC) loadPUWeight();
 if(isMC) loadElectronWeight();

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {

  // clear counters for event variables
  nSelectedPho=0;
  nSelectedEle=0;
  nSelectedMuo=0;
  nSelectedJet=0;

  //printf(" Event %lld\n", event);
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ printf(" entry %lli\n",jentry); }

  n_tot++;

//  // get lists of "good" electrons, photons, jets
//  photon_list = photon_passID( phoidbit, 30, 1.4442, ""); // pt, eta, sysbinname
  electron_list = electron_passID( eleidbit, 30, 2.1, "");
  muon_list = muon_passID( muoidbit, 30, 2.1, ""); 
  jet_list = jet_passID( jetidbit, 25, 2.4, ""); 
  //AODcalojet_list   = jet_matchToMiniAOD("calo");          
  //AODPFjet_list     = jet_matchToMiniAOD("pf");          
  //AODPFchsjet_list  = jet_matchToMiniAOD("pfchs");          

  // make event weight in analyzerBase.C
  // colisions happen @LHC at a given rate, use event_weight
  // to make the simulation match the rate seen in data
  // = lum * cross-section / nrEvents generated
  //if( event==472257123 ){ printf("making eventweight\n"); }
  event_weight = makeEventWeight(crossSec,lumi,nrEvents);
  // for MC, simulated pileup is different from observed
  // in commontools/pileup we make a ratio for scaling MC
  if(isMC) event_weight *= makePUWeight();
  // electrons also have an associated scale factor for MC 
  if(isMC) event_weight *= makeElectronWeight();

  
  //std::cout<<"ntags: "<<ntag<<std::endl; 
  h_ntags->Fill(ntag);
  //h_ntags->Write();
  if(ntag>=2){
  number_sig = number_sig + event_weight;
  //number_bkg = number_bkg + event_weight;
  //std::cout <<"****** event_weight: "<<event_weight<<" lumi "<<lumi<<std::endl;
  std::cout <<"ntag = "<<ntag<< " numb_sig: "<< number_sig<< " numb_bkg: "<< number_bkg/*<< " event_weight*numb_sig: "<< event_weight*number_sig<< " event_weight*numb_bkg: "<< event_weight*number_bkg*/<<std::endl;
   }
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

  for(int i=0; i<jet_list.size(); ++i){
   int jetindex = jet_list[i];
   htall  += jetPt->at(jetindex);
   htjets += jetPt->at(jetindex);
  } 

  
  // check compatibility between AOD/miniAOD jets
 // printf("miniAOD: %i    AOD: %i \n", (int)jet_list.size(), (int)AODcalojet_list.size() );
 /* if( jet_list.size()!=AODcalojet_list.size()){nunmatched ++; continue;}
  nmatched ++;
  for(int i=0; i<jet_list.size(); ++i){
   int miniAODjetindex = jet_list.at(i);
   int AODjetindex     = AODcalojet_list.at(i);
   printf(" miniAOD: %f %f %f\n",
    jetPt ->at(miniAODjetindex), 
    jetEta->at(miniAODjetindex), 
    jetPhi->at(miniAODjetindex) );*/
/*
   printf(" AOD:     %f %f %f\n\n",
    AODCaloJetPt  ->at(AODjetindex), 
    AODCaloJetEta ->at(AODjetindex), 
    AODCaloJetPhi ->at(AODjetindex)  
   );*/
 // } 

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
  passOneJet =  jet_list.size()>0; 

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

   
  //}
  //if( event==472257123 ){ printf("EVENT in question\n"); 
  //}

  // set booleans if pass various selections
  //if( event==472257123 ){ printf("askPassSig\n"); }
  doesPassSig    = askPassSig   ();
  //if( event==472257123 ){ printf("askPassZH\n");  }
  doesPassZH     = askPassZH    ();
  //if( event==472257123 ){ printf("askPassDY\n");  }
  doesPassDY     = askPassDY    ();
  //if( event==472257123 ){ printf("askPassOffZ\n");  }
  doesPassOffZ   = askPassOffZ  ();
  //if( event==472257123 ){ printf("askPassSig\n");  }
  doesPassNoPair = askPassNoPair();

  // fill histogram

  //if( event==472257123 ){ printf("fillEle\n");  }
  //if( passSingleEle ){
  if( passSingleEle || passDoubleEle ){
                        fillSigHistograms(event_weight,0,0); fillJetHistograms(event_weight,0,0);  //fill2DHistograms(event_weight,0);  
   if( doesPassSig   ){ fillSigHistograms(event_weight,1,0); fillJetHistograms(event_weight,1,0); }//fill2DHistograms(event_weight,1); }
   if( doesPassZH    ){ fillSigHistograms(event_weight,2,0); fillJetHistograms(event_weight,2,0); }//fill2DHistograms(event_weight,2); }
   if( doesPassDY    ){ fillSigHistograms(event_weight,3,0); fillJetHistograms(event_weight,3,0); }//fill2DHistograms(event_weight,3); }
   if( doesPassOffZ  ){ fillSigHistograms(event_weight,4,0); fillJetHistograms(event_weight,4,0); }//fill2DHistograms(event_weight,4); }
   if( doesPassNoPair){ fillSigHistograms(event_weight,5,0); fillJetHistograms(event_weight,5,0); }//fill2DHistograms(event_weight,5); }
  }

  //if( event==472257123 ){ printf("fillMu\n");  }
  //if( passSingleMu ){
  if( passSingleMu || passDoubleMu ){
                        fillSigHistograms(event_weight,0,1); fillJetHistograms(event_weight,0,1);  //fill2DHistograms(event_weight,0);  
   if( doesPassSig   ){ fillSigHistograms(event_weight,1,1); fillJetHistograms(event_weight,1,1); }//fill2DHistograms(event_weight,1); }
   if( doesPassZH    ){ fillSigHistograms(event_weight,2,1); fillJetHistograms(event_weight,2,1); }//fill2DHistograms(event_weight,2); }
   if( doesPassDY    ){ fillSigHistograms(event_weight,3,1); fillJetHistograms(event_weight,3,1); }//fill2DHistograms(event_weight,3); }
   if( doesPassOffZ  ){ fillSigHistograms(event_weight,4,1); fillJetHistograms(event_weight,4,1); }//fill2DHistograms(event_weight,4); }
   if( doesPassNoPair){ fillSigHistograms(event_weight,5,1); fillJetHistograms(event_weight,5,1); }//fill2DHistograms(event_weight,5); }
  }
   
  //if( event==472257123 ){ printf("Done Looping\n");  }
  //No Lep selection
                          fillSigHistograms(event_weight,0,2); fillJetHistograms(event_weight,0,2);  //fill2DHistograms(event_weight,0);  
     if( doesPassSig   ){ fillSigHistograms(event_weight,1,2); fillJetHistograms(event_weight,1,2); }//fill2DHistograms(event_weight,1); }
     if( doesPassZH    ){ fillSigHistograms(event_weight,2,2); fillJetHistograms(event_weight,2,2); }//fill2DHistograms(event_weight,2); }
     if( doesPassDY    ){ fillSigHistograms(event_weight,3,2); fillJetHistograms(event_weight,3,2); }//fill2DHistograms(event_weight,3); }
     if( doesPassOffZ  ){ fillSigHistograms(event_weight,4,2); fillJetHistograms(event_weight,4,2); }//fill2DHistograms(event_weight,4); }
     if( doesPassNoPair){ fillSigHistograms(event_weight,5,2); fillJetHistograms(event_weight,5,2); }//fill2DHistograms(event_weight,5); }
  
  //printf("make log: %0.i\n",makelog);
  //printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);

 } // end loop over entries

 printf("\n\n Summary   dR=%0.1f\n",drcut);
 printf("  ntot        %i \n",n_tot        ); 
 //printf(" npassSig    %i %i %i \n",n_passSig    ,n_ele_passSig    ,n_mu_passSig    ); 
 //printf(" npassZH     %i %i %i \n",n_passZH     ,n_ele_passZH     ,n_mu_passZH     ); 
 //printf(" npassDY     %i %i %i \n",n_passDY     ,n_ele_passDY     ,n_mu_passDY     ); 
 //printf(" npassOffZ   %i %i %i \n",n_passOffZ   ,n_ele_passOffZ   ,n_mu_passOffZ   ); 
 //printf(" npassNoPair %i %i %i \n",n_passNoPair ,n_ele_passNoPair ,n_mu_passNoPair ); 
 
 std::cout <<"  numb_sig:   "<< number_sig<<std::endl;
 printf("  nmatched    %i\n",nmatched);
 printf("  nunmatched  %i\n",nunmatched);

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
 h_ntags->Write();
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
 
 // initialize names
 //jetmultnames.clear();
 //jetmultnames.push_back("LeadingJet");
 //jetmultnames.push_back("SubleadingJet");
 //jetmultnames.push_back("ThirdJet");
 //jetmultnames.push_back("FourthJet");
 //jetmultnames.push_back("AllPFJets");

 // loop through jets and selections to initialize histograms in parllel (series)
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
 jetmultnames.push_back("AllPFJets");

 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int j=0; j<jetmultnames.size(); ++j){
   for(unsigned int k=0; k<lepnames.size(); ++k){

    // Jet
    TString  hname_jetPt                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetPt                     "; 
    TString  hname_jetEn                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetEn                     "; 
    TString  hname_jetEta                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetEta                    "; 
    TString  hname_jetPhi                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetPhi                    "; 
    TString  hname_jetRawPt                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetRawPt                  "; 
    TString  hname_jetRawEn                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetRawEn                  "; 
    TString  hname_jetArea                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetArea                   "; 
    TString  hname_jetLeadTrackPt             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetLeadTrackPt            "; 
    TString  hname_jetLeadTrackEta            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetLeadTrackEta           "; 
    TString  hname_jetLeadTrackPhi            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetLeadTrackPhi           "; 
    TString  hname_jetCSV2BJetTags            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetCSV2BJetTags           "; 
    TString  hname_jetJetProbabilityBJetTags  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetJetProbabilityBJetTags "; 
    TString  hname_jetpfCombinedMVAV2BJetTags = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetpfCombinedMVAV2BJetTags"; 
    TString  hname_jetAlphaMax                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax               "; 
    TString  hname_jetAlphaMax2               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax2              "; 
    TString  hname_jetAlphaMaxP               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMaxP              "; 
    TString  hname_jetAlphaMaxP2              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMaxP2             "; 
    TString  hname_alphaMax_jetDauVertex_r    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_alphaMax_jetDauVertex_r   "; 
    TString  hname_jetAlphaMax_PV3onPV2       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax_PV3onPV2      "; 
    TString  hname_jetAlphaMax_PV3onNeu       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax_PV3onNeu      "; 
    TString  hname_jetAlphaMax_PV3onAll       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax_PV3onAll      "; 
    TString  hname_jetAlphaMax_PV2onNeu       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax_PV2onNeu      "; 
    TString  hname_jetAlphaMax_PV2onAll       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMax_PV2onAll      "; 
    TString  hname_jetAlpha2Max_PV3onPV2      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlpha2Max_PV3onPV2     "; 
    TString  hname_jetAlpha2Max_PV3onNeu      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlpha2Max_PV3onNeu     "; 
    TString  hname_jetAlpha2Max_PV3onAll      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlpha2Max_PV3onAll     "; 
    TString  hname_jetAlpha2Max_PV2onNeu      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlpha2Max_PV2onNeu     "; 
    TString  hname_jetAlpha2Max_PV2onAll      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlpha2Max_PV2onAll     "; 
    TString  hname_jetAlphaD                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaD                 "; 
    TString  hname_jetAlphaMaxD               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetAlphaMaxD              "; 
    TString  hname_jetLog10IPSig              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetLog10IPSig             "; 
    TString  hname_jetMedianLog10IPSig        = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetMedianLog10IPSig       "; 
    TString  hname_jetSumIP                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetSumIP                  "; 
    TString  hname_jetSumIPSig                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetSumIPSig               "; 
    TString  hname_jetTrackAngle              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetTrackAngle             "; 
    TString  hname_jetLogTrackAngle           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetLogTrackAngle          "; 
    TString  hname_jetMedianLogTrackAngle     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetMedianLogTrackAngle    "; 
    TString  hname_jetTotalTrackAngle         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetTotalTrackAngle        "; 
    TString  hname_jetNConstituents           = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetNConstituents          "; 
    TString  hname_jetVtxPt                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetVtxPt                  "; 
    TString  hname_jetVtxMass                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetVtxMass                "; 
    TString  hname_jetVtxNtrks                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetVtxNtrks               "; 
    TString  hname_jetVtx3DVal                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetVtx3DVal               "; 
    TString  hname_jetVtx3DSig                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_jetVtx3DSig               "; 
    TString  hname_IpVAlpha                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_IpVAlpha                  "; 
    TString  hname_IpVjetPt                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_IpVjetPt                  "; 
    TString  hname_AlphaVjetPt                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AlphaVjetPt               "; 
/*
    TString hname_AODCaloJetPt                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetPt            "; 
    TString hname_AODCaloJetEta               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetEta           "; 
    TString hname_AODCaloJetPhi               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetPhi           "; 
    TString hname_AODCaloJetAlphaMax          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMax      "; 
    TString hname_AODCaloJetAlphaMax2         = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMax2     "; 
    TString hname_AODCaloJetAlphaMaxPrime     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMaxPrime "; 
    TString hname_AODCaloJetAlphaMaxPrime2    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAlphaMaxPrime2"; 
    TString hname_AODCaloJetBeta              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetBeta          "; 
    TString hname_AODCaloJetBeta2             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetBeta2         "; 
*/
    // initialize the histograms
    h_jetPt                      [i][j][k] = initSingleHistogramTH1F( hname_jetPt                     , "jetPt                     " , 50, 0, 500 ); 
    h_jetEn                      [i][j][k] = initSingleHistogramTH1F( hname_jetEn                     , "jetEn                     " , 50, 0, 500 ); 
    h_jetEta                     [i][j][k] = initSingleHistogramTH1F( hname_jetEta                    , "jetEta                    " , 10, -5, 5 );  
    h_jetPhi                     [i][j][k] = initSingleHistogramTH1F( hname_jetPhi                    , "jetPhi                    " , 10, -5, 5 );
    h_jetRawPt                   [i][j][k] = initSingleHistogramTH1F( hname_jetRawPt                  , "jetRawPt                  " , 50, 0, 500 ); 
    h_jetRawEn                   [i][j][k] = initSingleHistogramTH1F( hname_jetRawEn                  , "jetRawEn                  " , 50, 0, 500) ; 
    h_jetArea                    [i][j][k] = initSingleHistogramTH1F( hname_jetArea                   , "jetArea                   " , 30, 0, 1) ; 
    h_jetLeadTrackPt             [i][j][k] = initSingleHistogramTH1F( hname_jetLeadTrackPt            , "jetLeadTrackPt            " , 50, 0, 100 ); 
    h_jetLeadTrackEta            [i][j][k] = initSingleHistogramTH1F( hname_jetLeadTrackEta           , "jetLeadTrackEta           " , 10, -5, 5 );  
    h_jetLeadTrackPhi            [i][j][k] = initSingleHistogramTH1F( hname_jetLeadTrackPhi           , "jetLeadTrackPhi           " , 10, -5, 5 );  
    h_jetCSV2BJetTags            [i][j][k] = initSingleHistogramTH1F( hname_jetCSV2BJetTags           , "jetCSV2BJetTags           " , 30, 0, 1) ; 
    h_jetJetProbabilityBJetTags  [i][j][k] = initSingleHistogramTH1F( hname_jetJetProbabilityBJetTags , "jetJetProbabilityBJetTags " , 30, 0, 1) ; 
    h_jetpfCombinedMVAV2BJetTags [i][j][k] = initSingleHistogramTH1F( hname_jetpfCombinedMVAV2BJetTags, "jetpfCombinedMVAV2BJetTags" , 30, 0, 1) ; 
    h_jetAlphaMax                [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax               , "jetAlphaMax               " , 30, 0, 1) ; 
    h_jetAlphaMax2               [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax2              , "jetAlphaMax2              " , 30, 0, 1) ; 
    h_jetAlphaMaxP               [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMaxP              , "jetAlphaMaxP              " , 30, 0, 1) ; 
    h_jetAlphaMaxP2              [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMaxP2             , "jetAlphaMaxP2             " , 30, 0, 1) ; 
    h_alphaMax_jetDauVertex_r    [i][j][k] = initSingleHistogramTH1F( hname_alphaMax_jetDauVertex_r   , "alphaMax_jetDauVertex_r   " , 30, 0, 1) ; 
    h_jetAlphaMax_PV3onPV2       [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax_PV3onPV2      , "jetAlphaMax_PV3onPV2      " , 30, 0, 1) ; 
    h_jetAlphaMax_PV3onNeu       [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax_PV3onNeu      , "jetAlphaMax_PV3onNeu      " , 30, 0, 1) ; 
    h_jetAlphaMax_PV3onAll       [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax_PV3onAll      , "jetAlphaMax_PV3onAll      " , 30, 0, 1) ; 
    h_jetAlphaMax_PV2onNeu       [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax_PV2onNeu      , "jetAlphaMax_PV2onNeu      " , 30, 0, 1) ; 
    h_jetAlphaMax_PV2onAll       [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMax_PV2onAll      , "jetAlphaMax_PV2onAll      " , 30, 0, 1) ; 
    h_jetAlpha2Max_PV3onPV2      [i][j][k] = initSingleHistogramTH1F( hname_jetAlpha2Max_PV3onPV2     , "jetAlpha2Max_PV3onPV2     " , 30, 0, 1) ; 
    h_jetAlpha2Max_PV3onNeu      [i][j][k] = initSingleHistogramTH1F( hname_jetAlpha2Max_PV3onNeu     , "jetAlpha2Max_PV3onNeu     " , 30, 0, 1) ; 
    h_jetAlpha2Max_PV3onAll      [i][j][k] = initSingleHistogramTH1F( hname_jetAlpha2Max_PV3onAll     , "jetAlpha2Max_PV3onAll     " , 30, 0, 1) ; 
    h_jetAlpha2Max_PV2onNeu      [i][j][k] = initSingleHistogramTH1F( hname_jetAlpha2Max_PV2onNeu     , "jetAlpha2Max_PV2onNeu     " , 30, 0, 1) ; 
    h_jetAlpha2Max_PV2onAll      [i][j][k] = initSingleHistogramTH1F( hname_jetAlpha2Max_PV2onAll     , "jetAlpha2Max_PV2onAll     " , 30, 0, 1) ; 
    h_jetAlphaD                  [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaD                 , "jetAlphaD                 " , 30, 0, 1) ; 
    h_jetAlphaMaxD               [i][j][k] = initSingleHistogramTH1F( hname_jetAlphaMaxD              , "jetAlphaMaxD              " , 30, 0, 1) ; 
    h_jetLog10IPSig              [i][j][k] = initSingleHistogramTH1F( hname_jetLog10IPSig             , "jetLog10IPSig             " , 30, -2, 3 ); 
    h_jetMedianLog10IPSig        [i][j][k] = initSingleHistogramTH1F( hname_jetMedianLog10IPSig       , "jetMedianLog10IPSig       " , 30, -2, 3 ); 
    h_jetSumIP                   [i][j][k] = initSingleHistogramTH1F( hname_jetSumIP                  , "jetSumIP                  " , 30, -2, 3 ); 
    h_jetSumIPSig                [i][j][k] = initSingleHistogramTH1F( hname_jetSumIPSig               , "jetSumIPSig               " , 30, -2, 3 ); 
    h_jetTrackAngle              [i][j][k] = initSingleHistogramTH1F( hname_jetTrackAngle             , "jetTrackAngle             " , 30, 0, 1) ; 
    h_jetLogTrackAngle           [i][j][k] = initSingleHistogramTH1F( hname_jetLogTrackAngle          , "jetLogTrackAngle          " , 30, 0, 1) ; 
    h_jetMedianLogTrackAngle     [i][j][k] = initSingleHistogramTH1F( hname_jetMedianLogTrackAngle    , "jetMedianLogTrackAngle    " , 30, 0, 1) ; 
    h_jetTotalTrackAngle         [i][j][k] = initSingleHistogramTH1F( hname_jetTotalTrackAngle        , "jetTotalTrackAngle        " , 30, 0, 1) ; 
    h_jetNConstituents           [i][j][k] = initSingleHistogramTH1F( hname_jetNConstituents          , "jetNConstituents          " , 30, 0, 30 ); 
    h_jetVtxPt                   [i][j][k] = initSingleHistogramTH1F( hname_jetVtxPt                  , "jetVtxPt                  " , 50, 0, 100 ); 
    h_jetVtxMass                 [i][j][k] = initSingleHistogramTH1F( hname_jetVtxMass                , "jetVtxMass                " , 50, 0, 100 ); 
    h_jetVtxNtrks                [i][j][k] = initSingleHistogramTH1F( hname_jetVtxNtrks               , "jetVtxNtrks               " , 30, 0, 30) ; 
    h_jetVtx3DVal                [i][j][k] = initSingleHistogramTH1F( hname_jetVtx3DVal               , "jetVtx3DVal               " , 30, 0, 1) ; 
    h_jetVtx3DSig                [i][j][k] = initSingleHistogramTH1F( hname_jetVtx3DSig               , "jetVtx3DSig               " , 30, 0, 1) ;
/*
    h_AODCaloJetPt               [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetPt              , "AODCaloJetPt            ", 50,0,500); 
    h_AODCaloJetEta              [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetEta             , "AODCaloJetEta           ", 30,-5,5); 
    h_AODCaloJetPhi              [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetPhi             , "AODCaloJetPhi           ", 30,-5,5); 
    h_AODCaloJetAlphaMax         [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax        , "AODCaloJetAlphaMax      ", 30, 0, 1); 
    h_AODCaloJetAlphaMax2        [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax2       , "AODCaloJetAlphaMax2     ", 30, 0, 1); 
    h_AODCaloJetAlphaMaxPrime    [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime   , "AODCaloJetAlphaMaxPrime ", 30, 0, 1); 
    h_AODCaloJetAlphaMaxPrime2   [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime2  , "AODCaloJetAlphaMaxPrime2", 30, 0, 1); 
    h_AODCaloJetBeta             [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetBeta            , "AODCaloJetBeta          ", 30, 0, 1); 
    h_AODCaloJetBeta2            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetBeta2           , "AODCaloJetBeta2         ", 30, 0, 1); 
*/
    h_IpVAlpha                   [i][j][k] = initSingleHistogramTH2F( hname_IpVAlpha                  , "jetIpVAlpha               " , 30, -2, 3, 30, 0, 1) ;
    h_IpVjetPt                   [i][j][k] = initSingleHistogramTH2F( hname_IpVjetPt                  , "jetIpVjetPt               " , 30, -2, 3, 50, 0, 500) ;
    h_AlphaVjetPt                [i][j][k] = initSingleHistogramTH2F( hname_AlphaVjetPt               , "jetAlphaVjetPt            " , 30,  0, 1, 50, 0, 500) ;

   }  //    for(unsigned int i=0; i<selbinnames.size(); ++i){
  }   //      for(unsigned int j=0; j<jet_list.size(); ++j){
 }    //         for(unsigned int k=0; k<lepnames.size(); ++k){

 return kTRUE;
}

//----------------------------fillJetHistograms
Bool_t analyzer_signal::fillJetHistograms(Double_t weight, int selbin, int lepbin)
{

 //printf("fillJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){
  if(j<(jetmultnames.size()-1)){
   if(jetPt                     ->size()>j){ h_jetPt                      [selbin][j][lepbin].Fill( jetPt                     ->at(j), weight); }
   if(jetEn                     ->size()>j){ h_jetEn                      [selbin][j][lepbin].Fill( jetEn                     ->at(j), weight); }
   if(jetEta                    ->size()>j){ h_jetEta                     [selbin][j][lepbin].Fill( jetEta                    ->at(j), weight); }
   if(jetPhi                    ->size()>j){ h_jetPhi                     [selbin][j][lepbin].Fill( jetPhi                    ->at(j), weight); }
   if(jetRawPt                  ->size()>j){ h_jetRawPt                   [selbin][j][lepbin].Fill( jetRawPt                  ->at(j), weight); }
   if(jetRawEn                  ->size()>j){ h_jetRawEn                   [selbin][j][lepbin].Fill( jetRawEn                  ->at(j), weight); }
   if(jetArea                   ->size()>j){ h_jetArea                    [selbin][j][lepbin].Fill( jetArea                   ->at(j), weight); }
   if(jetLeadTrackPt            ->size()>j){ h_jetLeadTrackPt             [selbin][j][lepbin].Fill( jetLeadTrackPt            ->at(j), weight); }
   if(jetLeadTrackEta           ->size()>j){ h_jetLeadTrackEta            [selbin][j][lepbin].Fill( jetLeadTrackEta           ->at(j), weight); }
   if(jetLeadTrackPhi           ->size()>j){ h_jetLeadTrackPhi            [selbin][j][lepbin].Fill( jetLeadTrackPhi           ->at(j), weight); }
   if(jetCSV2BJetTags           ->size()>j){ h_jetCSV2BJetTags            [selbin][j][lepbin].Fill( jetCSV2BJetTags           ->at(j), weight); }
   if(jetJetProbabilityBJetTags ->size()>j){ h_jetJetProbabilityBJetTags  [selbin][j][lepbin].Fill( jetJetProbabilityBJetTags ->at(j), weight); }
   if(jetpfCombinedMVAV2BJetTags->size()>j){ h_jetpfCombinedMVAV2BJetTags [selbin][j][lepbin].Fill( jetpfCombinedMVAV2BJetTags->at(j), weight); }
   if(jetAlphaMax               ->size()>j){ h_jetAlphaMax                [selbin][j][lepbin].Fill( jetAlphaMax               ->at(j), weight); }
   if(jetAlphaMax2              ->size()>j){ h_jetAlphaMax2               [selbin][j][lepbin].Fill( jetAlphaMax2              ->at(j), weight); }
   if(jetAlphaMaxP              ->size()>j){ h_jetAlphaMaxP               [selbin][j][lepbin].Fill( jetAlphaMaxP              ->at(j), weight); }
   if(jetAlphaMaxP2             ->size()>j){ h_jetAlphaMaxP2              [selbin][j][lepbin].Fill( jetAlphaMaxP2             ->at(j), weight); }
   if(alphaMax_jetDauVertex_r   ->size()>j){ h_alphaMax_jetDauVertex_r    [selbin][j][lepbin].Fill( alphaMax_jetDauVertex_r   ->at(j), weight); }
   if(jetAlphaMax_PV3onPV2      ->size()>j){ h_jetAlphaMax_PV3onPV2       [selbin][j][lepbin].Fill( jetAlphaMax_PV3onPV2      ->at(j), weight); }
   if(jetAlphaMax_PV3onNeu      ->size()>j){ h_jetAlphaMax_PV3onNeu       [selbin][j][lepbin].Fill( jetAlphaMax_PV3onNeu      ->at(j), weight); }
   if(jetAlphaMax_PV3onAll      ->size()>j){ h_jetAlphaMax_PV3onAll       [selbin][j][lepbin].Fill( jetAlphaMax_PV3onAll      ->at(j), weight); }
   if(jetAlphaMax_PV2onNeu      ->size()>j){ h_jetAlphaMax_PV2onNeu       [selbin][j][lepbin].Fill( jetAlphaMax_PV2onNeu      ->at(j), weight); }
   if(jetAlphaMax_PV2onAll      ->size()>j){ h_jetAlphaMax_PV2onAll       [selbin][j][lepbin].Fill( jetAlphaMax_PV2onAll      ->at(j), weight); }
   if(jetAlpha2Max_PV3onPV2     ->size()>j){ h_jetAlpha2Max_PV3onPV2      [selbin][j][lepbin].Fill( jetAlpha2Max_PV3onPV2     ->at(j), weight); }
   if(jetAlpha2Max_PV3onNeu     ->size()>j){ h_jetAlpha2Max_PV3onNeu      [selbin][j][lepbin].Fill( jetAlpha2Max_PV3onNeu     ->at(j), weight); }
   if(jetAlpha2Max_PV3onAll     ->size()>j){ h_jetAlpha2Max_PV3onAll      [selbin][j][lepbin].Fill( jetAlpha2Max_PV3onAll     ->at(j), weight); }
   if(jetAlpha2Max_PV2onNeu     ->size()>j){ h_jetAlpha2Max_PV2onNeu      [selbin][j][lepbin].Fill( jetAlpha2Max_PV2onNeu     ->at(j), weight); }
   if(jetAlpha2Max_PV2onAll     ->size()>j){ h_jetAlpha2Max_PV2onAll      [selbin][j][lepbin].Fill( jetAlpha2Max_PV2onAll     ->at(j), weight); }
   if(jetAlphaD                 ->size()>j){ h_jetAlphaD                  [selbin][j][lepbin].Fill( jetAlphaD                 ->at(j), weight); }
   if(jetAlphaMaxD              ->size()>j){ h_jetAlphaMaxD               [selbin][j][lepbin].Fill( jetAlphaMaxD              ->at(j), weight); }
   if(jetLog10IPSig             ->size()>j){ h_jetLog10IPSig              [selbin][j][lepbin].Fill( jetLog10IPSig             ->at(j), weight); }
   if(jetMedianLog10IPSig       ->size()>j){ h_jetMedianLog10IPSig        [selbin][j][lepbin].Fill( jetMedianLog10IPSig       ->at(j), weight); }
   if(jetSumIP                  ->size()>j){ h_jetSumIP                   [selbin][j][lepbin].Fill( jetSumIP                  ->at(j), weight); }
   if(jetSumIPSig               ->size()>j){ h_jetSumIPSig                [selbin][j][lepbin].Fill( jetSumIPSig               ->at(j), weight); }
   if(jetTrackAngle             ->size()>j){ h_jetTrackAngle              [selbin][j][lepbin].Fill( jetTrackAngle             ->at(j), weight); }
   if(jetLogTrackAngle          ->size()>j){ h_jetLogTrackAngle           [selbin][j][lepbin].Fill( jetLogTrackAngle          ->at(j), weight); }
   if(jetMedianLogTrackAngle    ->size()>j){ h_jetMedianLogTrackAngle     [selbin][j][lepbin].Fill( jetMedianLogTrackAngle    ->at(j), weight); }
   if(jetTotalTrackAngle        ->size()>j){ h_jetTotalTrackAngle         [selbin][j][lepbin].Fill( jetTotalTrackAngle        ->at(j), weight); }
   if(jetNConstituents          ->size()>j){ h_jetNConstituents           [selbin][j][lepbin].Fill( jetNConstituents          ->at(j), weight); }
   if(jetVtxPt                  ->size()>j){ h_jetVtxPt                   [selbin][j][lepbin].Fill( jetVtxPt                  ->at(j), weight); }
   if(jetVtxMass                ->size()>j){ h_jetVtxMass                 [selbin][j][lepbin].Fill( jetVtxMass                ->at(j), weight); }
   if(jetVtxNtrks               ->size()>j){ h_jetVtxNtrks                [selbin][j][lepbin].Fill( jetVtxNtrks               ->at(j), weight); }
   if(jetVtx3DVal               ->size()>j){ h_jetVtx3DVal                [selbin][j][lepbin].Fill( jetVtx3DVal               ->at(j), weight); }
   if(jetVtx3DSig               ->size()>j){ h_jetVtx3DSig                [selbin][j][lepbin].Fill( jetVtx3DSig               ->at(j), weight); }
/*
   if(AODCaloJetPt              ->size()>j){ h_AODCaloJetPt                [selbin][j][lepbin].Fill( AODCaloJetPt             ->at(j), weight); }
   if(AODCaloJetEta             ->size()>j){ h_AODCaloJetEta               [selbin][j][lepbin].Fill( AODCaloJetEta            ->at(j), weight); }
   if(AODCaloJetPhi             ->size()>j){ h_AODCaloJetPhi               [selbin][j][lepbin].Fill( AODCaloJetPhi            ->at(j), weight); }
   if(AODCaloJetAlphaMax        ->size()>j){ h_AODCaloJetAlphaMax          [selbin][j][lepbin].Fill( AODCaloJetAlphaMax       ->at(j), weight); }
   if(AODCaloJetAlphaMax2       ->size()>j){ h_AODCaloJetAlphaMax2         [selbin][j][lepbin].Fill( AODCaloJetAlphaMax2      ->at(j), weight); }
   if(AODCaloJetAlphaMaxPrime   ->size()>j){ h_AODCaloJetAlphaMaxPrime     [selbin][j][lepbin].Fill( AODCaloJetAlphaMaxPrime  ->at(j), weight); }
   if(AODCaloJetAlphaMaxPrime2  ->size()>j){ h_AODCaloJetAlphaMaxPrime2    [selbin][j][lepbin].Fill( AODCaloJetAlphaMaxPrime2 ->at(j), weight); }
   if(AODCaloJetBeta            ->size()>j){ h_AODCaloJetBeta              [selbin][j][lepbin].Fill( AODCaloJetBeta           ->at(j), weight); }
   if(AODCaloJetBeta2           ->size()>j){ h_AODCaloJetBeta2             [selbin][j][lepbin].Fill( AODCaloJetBeta2          ->at(j), weight); }
*/
   if(jetMedianLog10IPSig->size()>j&&jetAlphaMaxD->size()>j){ h_IpVAlpha  [selbin][j][lepbin].Fill(jetMedianLog10IPSig->at(j),jetAlphaMax->at(j), weight); }
   if(jetMedianLog10IPSig->size()>j&&jetPt->size()>j){ h_IpVjetPt    [selbin][j][lepbin].Fill( jetMedianLog10IPSig->at(j), jetPt->at(j), weight); }
   if(jetPt->size()>j&&jetAlphaMaxD->size()>j)       { h_AlphaVjetPt [selbin][j][lepbin].Fill( jetAlphaMax        ->at(j), jetPt->at(j), weight); }

   //if(isMC){
   // if(jetPartonID                ->size()>j){h_jetPartonID                 [selbin][j][lepbin].Fill( jetPartonID                ->at(j), weight ); } 
   // if(jetHadFlvr                 ->size()>j){h_jetHadFlvr                  [selbin][j][lepbin].Fill( jetHadFlvr                 ->at(j), weight ); } 
   // if(jetGenJetEn                ->size()>j){h_jetGenJetEn                 [selbin][j][lepbin].Fill( jetGenJetEn                ->at(j), weight ); } 
   // if(jetGenJetPt                ->size()>j){h_jetGenJetPt                 [selbin][j][lepbin].Fill( jetGenJetPt                ->at(j), weight ); } 
   // if(jetGenJetEta               ->size()>j){h_jetGenJetEta                [selbin][j][lepbin].Fill( jetGenJetEta               ->at(j), weight ); } 
   // if(jetGenJetPhi               ->size()>j){h_jetGenJetPhi                [selbin][j][lepbin].Fill( jetGenJetPhi               ->at(j), weight ); } 
   // if(jetGenPartonID             ->size()>j){h_jetGenPartonID              [selbin][j][lepbin].Fill( jetGenPartonID             ->at(j), weight ); } 
   // if(jetGenEn                   ->size()>j){h_jetGenEn                    [selbin][j][lepbin].Fill( jetGenEn                   ->at(j), weight ); } 
   // if(jetGenPt                   ->size()>j){h_jetGenPt                    [selbin][j][lepbin].Fill( jetGenPt                   ->at(j), weight ); } 
   // if(jetGenEta                  ->size()>j){h_jetGenEta                   [selbin][j][lepbin].Fill( jetGenEta                  ->at(j), weight ); } 
   // if(jetGenPhi                  ->size()>j){h_jetGenPhi                   [selbin][j][lepbin].Fill( jetGenPhi                  ->at(j), weight ); } 
   // if(jetGenPartonMomID          ->size()>j){h_jetGenPartonMomID           [selbin][j][lepbin].Fill( jetGenPartonMomID          ->at(j), weight ); } 
   //}

  } // if( j<(jetmultnames.size()-1 ) ){
    else // if not ( j<(jetmultnames.size()-1 ) ){
    {//n_entries += jet_list.size(); std::cout<<jet_list.size()<<" "<<n_entries<<std::endl;
     for(unsigned int i =0; i<jet_list.size(); i++)
     { 
      // daniel - this isn't doing what you think it is
       // let's say we have initial jet list with 5 jets, and we find nrs 1,2,4 are good
      // jet_list.size()==3 but we don't want to fill with jetPt->at(3) 
       // look at the loops where we do lepton/jet cleaning or the ht sums
       // i'll just leave this commented out for now
      int jindex = jet_list[i];  
      if(jetPt                     ->size()>jindex){ h_jetPt                      [selbin][j][lepbin].Fill( jetPt                     ->at(jindex), weight); }
      if(jetEn                     ->size()>jindex){ h_jetEn                      [selbin][j][lepbin].Fill( jetEn                     ->at(jindex), weight); }
      if(jetEta                    ->size()>jindex){ h_jetEta                     [selbin][j][lepbin].Fill( jetEta                    ->at(jindex), weight); }
      if(jetPhi                    ->size()>jindex){ h_jetPhi                     [selbin][j][lepbin].Fill( jetPhi                    ->at(jindex), weight); }
      if(jetRawPt                  ->size()>jindex){ h_jetRawPt                   [selbin][j][lepbin].Fill( jetRawPt                  ->at(jindex), weight); }
      if(jetRawEn                  ->size()>jindex){ h_jetRawEn                   [selbin][j][lepbin].Fill( jetRawEn                  ->at(jindex), weight); }
      if(jetArea                   ->size()>jindex){ h_jetArea                    [selbin][j][lepbin].Fill( jetArea                   ->at(jindex), weight); }
      if(jetLeadTrackPt            ->size()>jindex){ h_jetLeadTrackPt             [selbin][j][lepbin].Fill( jetLeadTrackPt            ->at(jindex), weight); }
      if(jetLeadTrackEta           ->size()>jindex){ h_jetLeadTrackEta            [selbin][j][lepbin].Fill( jetLeadTrackEta           ->at(jindex), weight); }
      if(jetLeadTrackPhi           ->size()>jindex){ h_jetLeadTrackPhi            [selbin][j][lepbin].Fill( jetLeadTrackPhi           ->at(jindex), weight); }
      if(jetCSV2BJetTags           ->size()>jindex){ h_jetCSV2BJetTags            [selbin][j][lepbin].Fill( jetCSV2BJetTags           ->at(jindex), weight); }
      if(jetJetProbabilityBJetTags ->size()>jindex){ h_jetJetProbabilityBJetTags  [selbin][j][lepbin].Fill( jetJetProbabilityBJetTags ->at(jindex), weight); }
      if(jetpfCombinedMVAV2BJetTags->size()>jindex){ h_jetpfCombinedMVAV2BJetTags [selbin][j][lepbin].Fill( jetpfCombinedMVAV2BJetTags->at(jindex), weight); }
      if(jetAlphaMax               ->size()>jindex){ h_jetAlphaMax                [selbin][j][lepbin].Fill( jetAlphaMax               ->at(jindex), weight); }
      if(jetAlphaMax2              ->size()>jindex){ h_jetAlphaMax2               [selbin][j][lepbin].Fill( jetAlphaMax2              ->at(jindex), weight); }
      if(jetAlphaMaxP              ->size()>jindex){ h_jetAlphaMaxP               [selbin][j][lepbin].Fill( jetAlphaMaxP              ->at(jindex), weight); }
      if(jetAlphaMaxP2             ->size()>jindex){ h_jetAlphaMaxP2              [selbin][j][lepbin].Fill( jetAlphaMaxP2             ->at(jindex), weight); }
      if(alphaMax_jetDauVertex_r   ->size()>jindex){ h_alphaMax_jetDauVertex_r    [selbin][j][lepbin].Fill( alphaMax_jetDauVertex_r   ->at(jindex), weight); }
      if(jetAlphaMax_PV3onPV2      ->size()>jindex){ h_jetAlphaMax_PV3onPV2       [selbin][j][lepbin].Fill( jetAlphaMax_PV3onPV2      ->at(jindex), weight); }
      if(jetAlphaMax_PV3onNeu      ->size()>jindex){ h_jetAlphaMax_PV3onNeu       [selbin][j][lepbin].Fill( jetAlphaMax_PV3onNeu      ->at(jindex), weight); }
      if(jetAlphaMax_PV3onAll      ->size()>jindex){ h_jetAlphaMax_PV3onAll       [selbin][j][lepbin].Fill( jetAlphaMax_PV3onAll      ->at(jindex), weight); }
      if(jetAlphaMax_PV2onNeu      ->size()>jindex){ h_jetAlphaMax_PV2onNeu       [selbin][j][lepbin].Fill( jetAlphaMax_PV2onNeu      ->at(jindex), weight); }
      if(jetAlphaMax_PV2onAll      ->size()>jindex){ h_jetAlphaMax_PV2onAll       [selbin][j][lepbin].Fill( jetAlphaMax_PV2onAll      ->at(jindex), weight); }
      if(jetAlpha2Max_PV3onPV2     ->size()>jindex){ h_jetAlpha2Max_PV3onPV2      [selbin][j][lepbin].Fill( jetAlpha2Max_PV3onPV2     ->at(jindex), weight); }
      if(jetAlpha2Max_PV3onNeu     ->size()>jindex){ h_jetAlpha2Max_PV3onNeu      [selbin][j][lepbin].Fill( jetAlpha2Max_PV3onNeu     ->at(jindex), weight); }
      if(jetAlpha2Max_PV3onAll     ->size()>jindex){ h_jetAlpha2Max_PV3onAll      [selbin][j][lepbin].Fill( jetAlpha2Max_PV3onAll     ->at(jindex), weight); }
      if(jetAlpha2Max_PV2onNeu     ->size()>jindex){ h_jetAlpha2Max_PV2onNeu      [selbin][j][lepbin].Fill( jetAlpha2Max_PV2onNeu     ->at(jindex), weight); }
      if(jetAlpha2Max_PV2onAll     ->size()>jindex){ h_jetAlpha2Max_PV2onAll      [selbin][j][lepbin].Fill( jetAlpha2Max_PV2onAll     ->at(jindex), weight); }
      if(jetAlphaD                 ->size()>jindex){ h_jetAlphaD                  [selbin][j][lepbin].Fill( jetAlphaD                 ->at(jindex), weight); }
      if(jetAlphaMaxD              ->size()>jindex){ h_jetAlphaMaxD               [selbin][j][lepbin].Fill( jetAlphaMaxD              ->at(jindex), weight); }
      if(jetLog10IPSig             ->size()>jindex){ h_jetLog10IPSig              [selbin][j][lepbin].Fill( jetLog10IPSig             ->at(jindex), weight); }
      if(jetMedianLog10IPSig       ->size()>jindex){ h_jetMedianLog10IPSig        [selbin][j][lepbin].Fill( jetMedianLog10IPSig       ->at(jindex), weight); }
      if(jetSumIP                  ->size()>jindex){ h_jetSumIP                   [selbin][j][lepbin].Fill( jetSumIP                  ->at(jindex), weight); }
      if(jetSumIPSig               ->size()>jindex){ h_jetSumIPSig                [selbin][j][lepbin].Fill( jetSumIPSig               ->at(jindex), weight); }
      if(jetTrackAngle             ->size()>jindex){ h_jetTrackAngle              [selbin][j][lepbin].Fill( jetTrackAngle             ->at(jindex), weight); }
      if(jetLogTrackAngle          ->size()>jindex){ h_jetLogTrackAngle           [selbin][j][lepbin].Fill( jetLogTrackAngle          ->at(jindex), weight); }
      if(jetMedianLogTrackAngle    ->size()>jindex){ h_jetMedianLogTrackAngle     [selbin][j][lepbin].Fill( jetMedianLogTrackAngle    ->at(jindex), weight); }
      if(jetTotalTrackAngle        ->size()>jindex){ h_jetTotalTrackAngle         [selbin][j][lepbin].Fill( jetTotalTrackAngle        ->at(jindex), weight); }
      if(jetNConstituents          ->size()>jindex){ h_jetNConstituents           [selbin][j][lepbin].Fill( jetNConstituents          ->at(jindex), weight); }
      if(jetVtxPt                  ->size()>jindex){ h_jetVtxPt                   [selbin][j][lepbin].Fill( jetVtxPt                  ->at(jindex), weight); }
      if(jetVtxMass                ->size()>jindex){ h_jetVtxMass                 [selbin][j][lepbin].Fill( jetVtxMass                ->at(jindex), weight); }
      if(jetVtxNtrks               ->size()>jindex){ h_jetVtxNtrks                [selbin][j][lepbin].Fill( jetVtxNtrks               ->at(jindex), weight); }
      if(jetVtx3DVal               ->size()>jindex){ h_jetVtx3DVal                [selbin][j][lepbin].Fill( jetVtx3DVal               ->at(jindex), weight); }
      if(jetVtx3DSig               ->size()>jindex){ h_jetVtx3DSig                [selbin][j][lepbin].Fill( jetVtx3DSig               ->at(jindex), weight); }
      //std::cout<<"fill 2D"<<std::endl;
      if(jetMedianLog10IPSig->size()>jindex&&jetAlphaMaxD->size()>jindex){ h_IpVAlpha [selbin][j][lepbin].Fill(jetMedianLog10IPSig->at(jindex),jetAlphaMax->at(jindex), weight); }
      if(jetMedianLog10IPSig->size()>jindex&&jetPt->size()>jindex){ h_IpVjetPt    [selbin][j][lepbin].Fill( jetMedianLog10IPSig->at(jindex), jetPt->at(jindex), weight); }
      if(jetPt->size()>jindex&&jetAlphaMaxD->size()>jindex)       { h_AlphaVjetPt [selbin][j][lepbin].Fill( jetAlphaMax        ->at(jindex), jetPt->at(jindex), weight); }
      //std::cout<<"fill 2D end"<<std::endl;
     } //  for(unsigned int i =0; i<jet_list.size(); i++)
    } // if not ( j<(jetmultnames.size()-1 ) ){
 } //for(unsigned int j=0; j<jetmultnames.size(); ++j){

 return kTRUE;
} //end fill histograms

//----------------------------writeJetHistograms
Bool_t analyzer_signal::writeJetHistograms(int selbin, int lepbin)
{
 //printf("writeJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){
  h_jetPt                      [selbin][j][lepbin].Write(); 
  h_jetEn                      [selbin][j][lepbin].Write(); 
  h_jetEta                     [selbin][j][lepbin].Write(); 
  h_jetPhi                     [selbin][j][lepbin].Write(); 
  h_jetRawPt                   [selbin][j][lepbin].Write(); 
  h_jetRawEn                   [selbin][j][lepbin].Write(); 
  h_jetArea                    [selbin][j][lepbin].Write(); 
  h_jetLeadTrackPt             [selbin][j][lepbin].Write(); 
  h_jetLeadTrackEta            [selbin][j][lepbin].Write(); 
  h_jetLeadTrackPhi            [selbin][j][lepbin].Write(); 
  h_jetCSV2BJetTags            [selbin][j][lepbin].Write(); 
  h_jetJetProbabilityBJetTags  [selbin][j][lepbin].Write(); 
  h_jetpfCombinedMVAV2BJetTags [selbin][j][lepbin].Write(); 
  h_jetAlphaMax                [selbin][j][lepbin].Write(); 
  h_jetAlphaMax2               [selbin][j][lepbin].Write(); 
  h_jetAlphaMaxP               [selbin][j][lepbin].Write(); 
  h_jetAlphaMaxP2              [selbin][j][lepbin].Write(); 
  h_alphaMax_jetDauVertex_r    [selbin][j][lepbin].Write(); 
  h_jetAlphaMax_PV3onPV2       [selbin][j][lepbin].Write(); 
  h_jetAlphaMax_PV3onNeu       [selbin][j][lepbin].Write(); 
  h_jetAlphaMax_PV3onAll       [selbin][j][lepbin].Write(); 
  h_jetAlphaMax_PV2onNeu       [selbin][j][lepbin].Write(); 
  h_jetAlphaMax_PV2onAll       [selbin][j][lepbin].Write(); 
  h_jetAlpha2Max_PV3onPV2      [selbin][j][lepbin].Write(); 
  h_jetAlpha2Max_PV3onNeu      [selbin][j][lepbin].Write(); 
  h_jetAlpha2Max_PV3onAll      [selbin][j][lepbin].Write(); 
  h_jetAlpha2Max_PV2onNeu      [selbin][j][lepbin].Write(); 
  h_jetAlpha2Max_PV2onAll      [selbin][j][lepbin].Write(); 
  h_jetAlphaD                  [selbin][j][lepbin].Write(); 
  h_jetAlphaMaxD               [selbin][j][lepbin].Write(); 
  h_jetLog10IPSig              [selbin][j][lepbin].Write(); 
  h_jetMedianLog10IPSig        [selbin][j][lepbin].Write(); 
  h_jetSumIP                   [selbin][j][lepbin].Write(); 
  h_jetSumIPSig                [selbin][j][lepbin].Write(); 
  h_jetTrackAngle              [selbin][j][lepbin].Write(); 
  h_jetLogTrackAngle           [selbin][j][lepbin].Write(); 
  h_jetMedianLogTrackAngle     [selbin][j][lepbin].Write(); 
  h_jetTotalTrackAngle         [selbin][j][lepbin].Write(); 
  h_jetNConstituents           [selbin][j][lepbin].Write(); 
  h_jetVtxPt                   [selbin][j][lepbin].Write(); 
  h_jetVtxMass                 [selbin][j][lepbin].Write(); 
  h_jetVtxNtrks                [selbin][j][lepbin].Write(); 
  h_jetVtx3DVal                [selbin][j][lepbin].Write(); 
  h_jetVtx3DSig                [selbin][j][lepbin].Write(); 
/*
  h_AODCaloJetPt               [selbin][j][lepbin].Write(); 
  h_AODCaloJetEta              [selbin][j][lepbin].Write(); 
  h_AODCaloJetPhi              [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMax         [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMax2        [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMaxPrime    [selbin][j][lepbin].Write(); 
  h_AODCaloJetAlphaMaxPrime2   [selbin][j][lepbin].Write(); 
  h_AODCaloJetBeta             [selbin][j][lepbin].Write(); 
  h_AODCaloJetBeta2            [selbin][j][lepbin].Write(); 
*/
  h_IpVAlpha                   [selbin][j][lepbin].Write(); 
  h_IpVjetPt                   [selbin][j][lepbin].Write(); 
  h_AlphaVjetPt                [selbin][j][lepbin].Write(); 

 }

 return kTRUE;
}


//----------------------------initSigHistograms
Bool_t analyzer_signal::initSigHistograms()
{

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

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){

   // initialize names
   TString hname_nVtx                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nVtx                   "; 
   TString hname_nGoodVtx                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nGoodVtx               "; 
   TString hname_nTrksPV                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nTrksPV                "; 
   TString hname_isPVGood                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_isPVGood               "; 
   TString hname_rho                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_rho                    "; 
   TString hname_rhoCentral              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_rhoCentral             "; 
   TString hname_nTruePU                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nTruePU                "; 
   TString hname_pfMET                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_pfMET                  "; 
   TString hname_pfMETPhi                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_pfMETPhi               "; 
   TString hname_pfMETsumEt              = "h_"+lepnames[k]+"_"+selbinnames[i]+"_pfMETsumEt             "; 

   //TString hname_nPho                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nPho                   "; 
   //TString hname_phoEn                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoEn                  "; 
   //TString hname_phoPt                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoPt                  "; 
   //TString hname_phoEta                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoEta                 "; 
   //TString hname_phoPhi                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoPhi                 "; 
   //TString hname_phoSCEn                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoSCEn                "; 
   //TString hname_phoSCPhi                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoSCPhi               "; 
   //TString hname_phoSCEta                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_phoSCEta               "; 

   TString hname_nEle                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nEle                   "; 
   TString hname_elePt                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePt                  "; 
   TString hname_eleEn                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleEn                  "; 
   TString hname_eleEta                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleEta                 "; 
   TString hname_elePhi                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePhi                 "; 
   TString hname_eleCharge               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleCharge              "; 
   TString hname_eleSCEn                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCEn                "; 
   TString hname_eleSCEta                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCEta               "; 
   TString hname_eleSCPhi                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_eleSCPhi               "; 
   //TString hname_elePFdBetaIsolationRhoEA = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationRhoEA"; 
   //TString hname_elePFdBetaIsolationCHS   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationCHS  "; 
   TString hname_elePFdBetaIsolationDiff  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_elePFdBetaIsolationDiff "; 
   TString hname_nMu                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nMu                    "; 
   TString hname_muPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPt                   "; 
   TString hname_muEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muEn                   "; 
   TString hname_muEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muEta                  "; 
   TString hname_muPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPhi                  "; 
   TString hname_muCharge                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muCharge               "; 
   TString hname_muPFdBetaIsolation      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_muPFdBetaIsolation     "; 
   TString hname_nJet                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nJet                   "; 

   TString hname_htall                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htall "; 
   TString hname_htjets                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htjets"; 
   TString hname_nSelectedPho            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedPho";
   TString hname_nSelectedEle            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedEle";
   TString hname_nSelectedMuo            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedMuo";
   TString hname_nSelectedJet            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedJet";

   // initalize histograms
   h_nVtx                    [i][k] = initSingleHistogramTH1F( hname_nVtx                    , "nVtx                   ", 60,0,60) ; 
   h_nGoodVtx                [i][k] = initSingleHistogramTH1F( hname_nGoodVtx                , "nGoodVtx               ", 60,0,60) ;  
   h_nTrksPV                 [i][k] = initSingleHistogramTH1F( hname_nTrksPV                 , "nTrksPV                ", 60,0,60) ;  
   h_isPVGood                [i][k] = initSingleHistogramTH1F( hname_isPVGood                , "isPVGood               ", 2,0,1) ;  
   h_rho                     [i][k] = initSingleHistogramTH1F( hname_rho                     , "rho                    ", 30, -3, 3); 
   h_rhoCentral              [i][k] = initSingleHistogramTH1F( hname_rhoCentral              , "rhoCentral             ", 30, -3, 3); 
   h_nTruePU                 [i][k] = initSingleHistogramTH1F( hname_nTruePU                 , "nTruePU                ", 60,0,60) ;  
   h_pfMET                   [i][k] = initSingleHistogramTH1F( hname_pfMET                   , "pfMET                  ", 50, 0, 500) ;  
   h_pfMETPhi                [i][k] = initSingleHistogramTH1F( hname_pfMETPhi                , "pfMETPhi               ", 30, -5, 5); 
   h_pfMETsumEt              [i][k] = initSingleHistogramTH1F( hname_pfMETsumEt              , "pfMETsumEt             ", 50, 0, 500)  ;

   //h_nPho                    [i][k] = initSingleHistogramTH1F( hname_nPho                    , "nPho                   ", 10,0,10) ;  
   //h_phoEn                   [i][k] = initSingleHistogramTH1F( hname_phoEn                   , "phoEn                  ", 50, 0, 500) ;  
   //h_phoPt                   [i][k] = initSingleHistogramTH1F( hname_phoPt                   , "phoPt                  ", 50, 0, 500) ;  
   //h_phoEta                  [i][k] = initSingleHistogramTH1F( hname_phoEta                  , "phoEta                 ", 30, -5, 5); 
   //h_phoPhi                  [i][k] = initSingleHistogramTH1F( hname_phoPhi                  , "phoPhi                 ", 30, -5, 5); 
   //h_phoSCEn                 [i][k] = initSingleHistogramTH1F( hname_phoSCEn                 , "phoSCEn                ", 50, 0, 500) ;  
   //h_phoSCPhi                [i][k] = initSingleHistogramTH1F( hname_phoSCPhi                , "phoSCPhi               ", 30, -5, 5); 
   //h_phoSCEta                [i][k] = initSingleHistogramTH1F( hname_phoSCEta                , "phoSCEta               ", 30, -5, 5); 

   h_nEle                    [i][k] = initSingleHistogramTH1F( hname_nEle                    , "nEle                   ", 10,0,10) ; 
   h_elePt                   [i][k] = initSingleHistogramTH1F( hname_elePt                   , "elePt                  ", 50, 0, 500) ;  
   h_eleEn                   [i][k] = initSingleHistogramTH1F( hname_eleEn                   , "eleEn                  ", 50, 0, 500) ;  
   h_eleEta                  [i][k] = initSingleHistogramTH1F( hname_eleEta                  , "eleEta                 ", 30, -5, 5); 
   h_elePhi                  [i][k] = initSingleHistogramTH1F( hname_elePhi                  , "elePhi                 ", 30, -5, 5); 
   h_eleCharge               [i][k] = initSingleHistogramTH1F( hname_eleCharge               , "eleCharge              ", 3, -1, 1); 
   h_eleSCEn                 [i][k] = initSingleHistogramTH1F( hname_eleSCEn                 , "eleSCEn                ", 50, 0, 500) ;  
   h_eleSCEta                [i][k] = initSingleHistogramTH1F( hname_eleSCEta                , "eleSCEta               ", 30, -5, 5); 
   h_eleSCPhi                [i][k] = initSingleHistogramTH1F( hname_eleSCPhi                , "eleSCPhi               ", 30, -5, 5); 
   //h_elePFdBetaIsolationRhoEA [i][k] = initSingleHistogramTH1F( hname_elePFdBetaIsolationRhoEA, "elePFdBetaIsolationRhoEA", 30, 0, 1); 
   //h_elePFdBetaIsolationCHS   [i][k] = initSingleHistogramTH1F( hname_elePFdBetaIsolationCHS  , "elePFdBetaIsolationCHS  ", 30, 0, 1); 
   h_elePFdBetaIsolationDiff  [i][k] = initSingleHistogramTH1F( hname_elePFdBetaIsolationDiff , "elePFdBetaIsolationDiff ", 30, 0, 1); 
   h_nMu                     [i][k] = initSingleHistogramTH1F( hname_nMu                     , "nMu                    ", 10,0,10) ; 
   h_muPt                    [i][k] = initSingleHistogramTH1F( hname_muPt                    , "muPt                   ", 50, 0, 500) ;  
   h_muEn                    [i][k] = initSingleHistogramTH1F( hname_muEn                    , "muEn                   ", 50, 0, 500) ;  
   h_muEta                   [i][k] = initSingleHistogramTH1F( hname_muEta                   , "muEta                  ", 30, -5, 5); 
   h_muPhi                   [i][k] = initSingleHistogramTH1F( hname_muPhi                   , "muPhi                  ", 30, -5, 5); 
   h_muCharge                [i][k] = initSingleHistogramTH1F( hname_muCharge                , "muCharge               ", 3, -1, 1); 
   h_muPFdBetaIsolation      [i][k] = initSingleHistogramTH1F( hname_muPFdBetaIsolation      , "muPFdBetaIsolation     ", 30, -5, 5); 
   h_nJet                    [i][k] = initSingleHistogramTH1F( hname_nJet                    , "nJet                   ", 10,0,10) ; 

   h_htall  [i][k] = initSingleHistogramTH1F( hname_htall  , "htall ", 50,0,1000) ; 
   h_htjets [i][k] = initSingleHistogramTH1F( hname_htjets , "htjets", 50,0,1000) ; 
   h_nSelectedPho [i][k] = initSingleHistogramTH1F( hname_nSelectedPho , "nSelectedPho", 10,0,10);
   h_nSelectedEle [i][k] = initSingleHistogramTH1F( hname_nSelectedEle , "nSelectedEle", 10,0,10);
   h_nSelectedMuo [i][k] = initSingleHistogramTH1F( hname_nSelectedMuo , "nSelectedMuo", 10,0,10);
   h_nSelectedJet [i][k] = initSingleHistogramTH1F( hname_nSelectedJet , "nSelectedJet", 10,0,10);

  }
 }

 return kTRUE;
}

//----------------------------fillSigHistograms
Bool_t analyzer_signal::fillSigHistograms(Double_t weight, int selbin, int lepbin)
{

 //printf("fillSigHistograms\n");
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
 //h_nPho                    [selbin][lepbin] .Fill( nPho       , weight);  
 h_nEle                    [selbin][lepbin] .Fill( nEle       , weight);  
 h_nMu                     [selbin][lepbin] .Fill( nMu        , weight);  
 h_nJet                    [selbin][lepbin] .Fill( nJet       , weight);  

 h_htall                   [selbin][lepbin] .Fill( htall      , weight); 
 h_htjets                  [selbin][lepbin] .Fill( htjets     , weight); 
 h_nSelectedPho            [selbin][lepbin] .Fill( nSelectedPho, weight);
 h_nSelectedEle            [selbin][lepbin] .Fill( nSelectedEle, weight);
 h_nSelectedMuo            [selbin][lepbin] .Fill( nSelectedMuo, weight);
 h_nSelectedJet            [selbin][lepbin] .Fill( nSelectedJet, weight);

 //if(phoEn                  ->size()>0){ h_phoEn                   [selbin][lepbin] .Fill( phoEn                  ->at(0), weight ); } 
 //if(phoPt                  ->size()>0){ h_phoPt                   [selbin][lepbin] .Fill( phoPt                  ->at(0), weight ); } 
 //if(phoEta                 ->size()>0){ h_phoEta                  [selbin][lepbin] .Fill( phoEta                 ->at(0), weight ); } 
 //if(phoPhi                 ->size()>0){ h_phoPhi                  [selbin][lepbin] .Fill( phoPhi                 ->at(0), weight ); } 
 //if(phoSCEn                ->size()>0){ h_phoSCEn                 [selbin][lepbin] .Fill( phoSCEn                ->at(0), weight ); } 
 //if(phoSCPhi               ->size()>0){ h_phoSCPhi                [selbin][lepbin] .Fill( phoSCPhi               ->at(0), weight ); } 
 //if(phoSCEta               ->size()>0){ h_phoSCEta                [selbin][lepbin] .Fill( phoSCEta               ->at(0), weight ); } 

 if(elePt                  ->size()>0){ h_elePt                   [selbin][lepbin] .Fill( elePt                  ->at(0), weight ); } 
 if(eleEn                  ->size()>0){ h_eleEn                   [selbin][lepbin] .Fill( eleEn                  ->at(0), weight ); } 
 if(eleEta                 ->size()>0){ h_eleEta                  [selbin][lepbin] .Fill( eleEta                 ->at(0), weight ); } 
 if(elePhi                 ->size()>0){ h_elePhi                  [selbin][lepbin] .Fill( elePhi                 ->at(0), weight ); } 
 if(eleCharge              ->size()>0){ h_eleCharge               [selbin][lepbin] .Fill( eleCharge              ->at(0), weight ); } 
 if(eleSCEn                ->size()>0){ h_eleSCEn                 [selbin][lepbin] .Fill( eleSCEn                ->at(0), weight ); } 
 if(eleSCEta               ->size()>0){ h_eleSCEta                [selbin][lepbin] .Fill( eleSCEta               ->at(0), weight ); } 
 if(eleSCPhi               ->size()>0){ h_eleSCPhi                [selbin][lepbin] .Fill( eleSCPhi               ->at(0), weight ); } 
 //if(elePFdBetaIsolationRhoEA->size()>0){ h_elePFdBetaIsolationRhoEA[selbin][lepbin].Fill( elePFdBetaIsolationRhoEA->at(0), weight); }
 //if(elePFdBetaIsolationCHS  ->size()>0){ h_elePFdBetaIsolationCHS  [selbin][lepbin].Fill( elePFdBetaIsolationCHS  ->at(0), weight); }
 if(elePFdBetaIsolationDiff ->size()>0){ h_elePFdBetaIsolationDiff [selbin][lepbin].Fill( elePFdBetaIsolationDiff ->at(0), weight); }
 if(muPt                   ->size()>0){ h_muPt                    [selbin][lepbin] .Fill( muPt                   ->at(0), weight ); } 
 if(muEn                   ->size()>0){ h_muEn                    [selbin][lepbin] .Fill( muEn                   ->at(0), weight ); } 
 if(muEta                  ->size()>0){ h_muEta                   [selbin][lepbin] .Fill( muEta                  ->at(0), weight ); } 
 if(muPhi                  ->size()>0){ h_muPhi                   [selbin][lepbin] .Fill( muPhi                  ->at(0), weight ); } 
 if(muCharge               ->size()>0){ h_muCharge                [selbin][lepbin] .Fill( muCharge               ->at(0), weight ); } 
 if(muPFdBetaIsolation     ->size()>0){ h_muPFdBetaIsolation      [selbin][lepbin] .Fill( muPFdBetaIsolation     ->at(0), weight ); } 

 return kTRUE;
}

//----------------------------writeSigHistograms
//Bool_t analyzer_signal::writeSigHistograms(int ptbin, int sysbin)
Bool_t analyzer_signal::writeSigHistograms(int selbin, int lepbin)
{
 //printf("writeSigHistograms\n");

  h_nVtx                    [selbin][lepbin].Write(); 
  h_nGoodVtx                [selbin][lepbin].Write(); 
  h_nTrksPV                 [selbin][lepbin].Write(); 
  h_isPVGood                [selbin][lepbin].Write(); 
  h_rho                     [selbin][lepbin].Write(); 
  h_rhoCentral              [selbin][lepbin].Write(); 
  h_nTruePU                 [selbin][lepbin].Write(); 
  h_pfMET                   [selbin][lepbin].Write(); 
  h_pfMETPhi                [selbin][lepbin].Write(); 
  h_pfMETsumEt              [selbin][lepbin].Write(); 
  h_nPho                    [selbin][lepbin].Write(); 
  //h_phoEn                   [selbin][lepbin].Write(); 
  //h_phoPt                   [selbin][lepbin].Write(); 
  h_phoEta                  [selbin][lepbin].Write(); 
  h_phoPhi                  [selbin][lepbin].Write(); 
  //h_phoSCEn                 [selbin][lepbin].Write(); 
  h_phoSCPhi                [selbin][lepbin].Write(); 
  h_phoSCEta                [selbin][lepbin].Write(); 
  h_nEle                    [selbin][lepbin].Write(); 
  h_elePt                   [selbin][lepbin].Write(); 
  h_eleEn                   [selbin][lepbin].Write(); 
  h_eleEta                  [selbin][lepbin].Write(); 
  h_elePhi                  [selbin][lepbin].Write(); 
  h_eleCharge               [selbin][lepbin].Write(); 
  h_eleSCEn                 [selbin][lepbin].Write(); 
  h_eleSCEta                [selbin][lepbin].Write(); 
  h_eleSCPhi                [selbin][lepbin].Write(); 
  //h_elePFdBetaIsolationRhoEA[selbin][lepbin].Write();
  //h_elePFdBetaIsolationCHS  [selbin][lepbin].Write();
  h_elePFdBetaIsolationDiff [selbin][lepbin].Write();
  h_nMu                     [selbin][lepbin].Write(); 
  h_muPt                    [selbin][lepbin].Write(); 
  h_muEn                    [selbin][lepbin].Write(); 
  h_muEta                   [selbin][lepbin].Write(); 
  h_muPhi                   [selbin][lepbin].Write(); 
  h_muCharge                [selbin][lepbin].Write(); 
  h_muPFdBetaIsolation      [selbin][lepbin].Write(); 
  h_nJet                    [selbin][lepbin].Write(); 

  h_htall  [selbin][lepbin].Write(); 
  h_htjets [selbin][lepbin].Write(); 
  h_nSelectedPho [selbin][lepbin] .Write();
  h_nSelectedEle [selbin][lepbin] .Write();
  h_nSelectedMuo [selbin][lepbin] .Write();
  h_nSelectedJet [selbin][lepbin] .Write();

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
//  // check overlap with photons
//  if(photon_list.size()>0){
//   for(int d=0; d<photon_list.size(); ++d){
//    int phoindex = photon_list[d];
//    if(phoindex<= (phoEta->size()-1) && phoindex<= (phoPhi->size()-1)){
//     if( dR( phoEta->at(phoindex),phoPhi->at(phoindex), eleEta->at(i),elePhi->at(i) ) < 0.4 )  pass_overlap=false;
//    }
//   }//end photons
//  } // if photons

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

//-------------------------jet_passID
std::vector<int> analyzer_signal::jet_passID( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname) {

  std::vector<int> jetlist;
  ntag = 0;

  for(int i = 0; i < nJet; i++)
  {

   bool pass_overlap = true;
//   // check overlap with photons
//   if(photon_list.size()>0){
//    for(int d=0; d<photon_list.size(); ++d){
//     int phoindex = photon_list[d];
//     if(phoindex<= (phoEta->size()-1)&&phoindex<= (phoPhi->size()-1)){
//      if( dR( phoEta->at(phoindex),phoPhi->at(phoindex), jetEta->at(i),jetPhi->at(i) ) < 0.4 ){
//       ////printf(" Jet   ");
//       //printf("  pt: %4.3f eta: %4.3f phi: %4.3f\n", jetPt->at(i), jetEta->at(i), jetPhi->at(i) );
//       //printf(" Photon");
//       //printf("  pt: %4.3f eta: %4.3f phi: %4.3f\n", phoPt->at(phoindex), phoPta->at(phoindex), phoPhi->at(phoindex) );
//       pass_overlap=false;
//      }
//     }
//    }//end photons
//   } // if photons
   //check overlap with electrons
   if(electron_list.size()>0){
    for(int d=0; d<electron_list.size(); ++d){
     //printf(" brgin looping over electrons\n");
     int eleindex = electron_list[d];
     if( dR( eleEta->at(eleindex),elePhi->at(eleindex), jetEta->at(i),jetPhi->at(i) ) < 0.4 ) pass_overlap=false; // printf(" OL w electron\n");
    }//end electrons
   } // if electrons
   //check overlap with muons
   if(muon_list.size()>0){
    for(int d=0; d<muon_list.size(); ++d){
     int muindex = muon_list[d];
     if(muindex<= (muEta->size()-1)&&muindex<= (muPhi->size()-1)){
      if( dR( muEta->at(muindex),muPhi->at(muindex), jetEta->at(i),jetPhi->at(i) ) < 0.4 )  pass_overlap=false; //printf(" OL w muon\n");
     }
    }//end muons
   } // if muons

   bool pass_id  ;
   pass_id  = jetID->at(i) >> bitnr & 0x1 == 1;      
              
   bool pass_kin = jetPt->at(i) > jetPtCut && ( fabs(jetEta->at(i)) < jetEtaCut ) ;

   bool pass_signal = abs(jetGenPartonMomID->at(i)) > 9000000 ;//9000006
              
   //if( pass_id && pass_kin && pass_overlap )
   if( pass_id && pass_kin && pass_overlap && pass_signal && jetAlphaMax_PV3onAll->at(i) !=0 )

   {
    //printf(" a selected jet\n");
    if(jetMedianLog10IPSig->at(i) >=0.6 /*&& jetAlphaMaxD->at(i) >=0.0 && jetMedianLog10IPSig->at(i) <=2.0*/ && jetAlphaMaxD->at(i) <=0.1)
    {ntag= ntag + 1;}
    nSelectedJet++;
    jetlist.push_back(i);
   } // if pass_bit && pass_kin
  }// for(int i = 0; i < nJet; i++)

  return jetlist;

}


//-------------------------photon_passLooseID
std::vector<int> analyzer_signal::photon_passID( int bitnr, double phoPtCut, double phoEtaCut, TString sysbinname){

// std::vector<int> pholist;
// pholist.clear();
//
// //Loop over photons                   
// for(int p=0;p<nPho;p++)
// {    
//  Float_t thephoPt = getPhotonPt(p,sysbinname);
//  //Float_t thephoPt =  phoSCRawE->at(p) / TMath::CosH( (*phoSCEta)[p] ); //  phoPt->at(p); 
//  Float_t thephoEta = phoSCEta->at(p);                                  //  phoEta->at(p);
//
//  //bool kinematic = phoPt > phoPtCut && fabs((*phoSCEta)[p])<phoEtaCut;
//  bool kinematic = thephoPt > phoPtCut && fabs(thephoEta)<phoEtaCut;
//
//  bool pass_bit = phoIDbit->at(p) >> bitnr & 0x1 == 1; 
//  //printf(" photon %i %i %i\n",p,bitnr,pass_bit);
//
//  if( kinematic && pass_bit){
//   nSelectedPho++;
//   //printf("selected aphoton\n");
//   pholist.push_back(p);
//  }    
// }    
//
// return pholist;

}
/*
//-------------------------jet_matchToMiniAOD
std::vector<int> analyzer_signal::jet_matchToMiniAOD( TString jettype ){

  std::vector<int> tmpAODjetlist;

  // loop over miniAOD jet list (already passed selections)
  int lengthjets = (int)jet_list.size();
  for(int i = 0; i < lengthjets; i++)
  {

   // find index corresponding to miniAOD jet
   int jetindex = jet_list[i];
   // miniAOD jet parameters
   float miniAODjetPt  = jetPt->at(jetindex); 
   float miniAODjetEta = jetEta->at(jetindex); 
   float miniAODjetPhi = jetPhi->at(jetindex); 

   // initialize AOD jet parameters
   float AODjetPt;
   float AODjetEta;
   float AODjetPhi;

   // loop over AOD jets and look for match via deltaR
   int nAODjets;
   if( jettype=="calo" ){nAODjets = (int)AODCaloJetPt->size();}
   //if( jettype=="calo" ){nAODjets = (int)AODPFJetPt->size();} // do other jets
   //if( jettype=="calo" ){nAODjets = (int)AODPFchsJetPt->size();}
   for( int j = 0; j<nAODjets; j++ ) {

    if( jettype=="calo" ){
     AODjetPt  = AODCaloJetPt ->at(j) ;
     AODjetEta = AODCaloJetEta->at(j) ;
     AODjetPhi = AODCaloJetPhi->at(j) ;
    }

//    printf(" miniAOD: %f %f %f\n",
//     miniAODjetPt , 
//     miniAODjetEta, 
//     miniAODjetPhi );
//
//    printf(" AOD:     %f %f %f\n\n",
//     AODjetPt , 
//     AODjetEta, 
//     AODjetPhi );

    //AODPFJetPt     
    //AODPFJetEta    
    //AODPFJetPhi    

    //AODPFchsJetPt  
    //AODPFchsJetEta 
    //AODPFchsJetPhi 

    // if find match (AOD,miniAOD), add AODjet to list, break loop over AOD jets 
    // still have loop over miniAOD jets, so keep going and find next one
    if( dR( miniAODjetEta, miniAODjetPhi, AODjetEta, AODjetPhi) < drcut ) {  
       tmpAODjetlist.push_back(j); break;
    }

   }
  }

  return tmpAODjetlist;

}*/

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

  for(int i=0; i<jet_list.size(); ++i){
   int jetindex = jet_list[i];
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, jetPt->at(jetindex), jetEta->at(jetindex), jetPhi->at(jetindex));
  } 

  printf( " met %.1f mephi %.1f\n", themet, themephi);
  printf( " nvtx %d \n", nVtx);
  printf( " htall %.1f htjets %.1f\n", htall, htjets);

 }

void analyzer_signal::debug_printmuons()
{

 printf( " Loose Mu\n" );
 for(int i=0; i<muon_list_l.size(); ++i){
  int muindex = muon_list_l[i];
  printf( "  muon %d : pt %.1f eta %.1f phi %.1f\n", i, muPt->at(muindex), muEta->at(muindex), muPhi->at(muindex));
 }

 printf( " Med Mu\n" );
 for(int i=0; i<muon_list_m.size(); ++i){
  int muindex = muon_list_m[i];
  printf( "  muon %d : pt %.1f eta %.1f phi %.1f\n", i, muPt->at(muindex), muEta->at(muindex), muPhi->at(muindex));
 }

 printf( " Tight Mu\n" );
 for(int i=0; i<muon_list_t.size(); ++i){
  int muindex = muon_list_t[i];
  printf( "  muon %d : pt %.1f eta %.1f phi %.1f\n", i, muPt->at(muindex), muEta->at(muindex), muPhi->at(muindex));
 }

}


void analyzer_signal::debug_printelectrons()
{

 printf( " Loose Ele\n" );
 for(int i=0; i<electron_list_l.size(); ++i){
  int eleindex = electron_list_l[i];
  printf( "  electron %d : pt %.1f eta %.1f phi %.1f\n", i, elePt->at(eleindex), eleEta->at(eleindex), elePhi->at(eleindex));
 }

 printf( " Med Ele\n" );
 for(int i=0; i<electron_list_m.size(); ++i){
  int eleindex = electron_list_m[i];
  printf( "  electron %d : pt %.1f eta %.1f phi %.1f\n", i, elePt->at(eleindex), eleEta->at(eleindex), elePhi->at(eleindex));
 }

 printf( " Tight Ele\n" );
 for(int i=0; i<electron_list_t.size(); ++i){
  int eleindex = electron_list_t[i];
  printf( "  electron %d : pt %.1f eta %.1f phi %.1f\n", i, elePt->at(eleindex), eleEta->at(eleindex), elePhi->at(eleindex));
 }

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

}

