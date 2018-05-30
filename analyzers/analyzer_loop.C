#define analyzer_loop_cxx
#include "analyzer_loop.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>

using namespace std;

analyzer_loop::analyzer_loop()
{
}

analyzer_loop::~analyzer_loop()
{
}

void analyzer_loop::Loop(TString outfilename, 
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
 
 clearglobalcounters();

 if(isMC) loadPUWeight();
 if(isMC) loadElectronWeight( eleid );

 bool doBkgEst = true;
 if( doBkgEst ) loadMistagRate();

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {

  cleareventcounters();
  clearOPTtree(); 

  //printf(" Event %lld\n", event);
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ std::cout << " entry " << jentry << std::endl; }

  n_tot++;

  // get lists of "good" electrons, photons, jets
  // idbit, pt, eta, sysbinname
  photon_list     = photon_passID    ( phoidbit,        pho_minPt, pho_maxEta, ""); 
  electron_list   = electron_passID  ( eleidbit,        ele_minPt1, ele_minPt2, ele_maxEta, "");
  muon_list       = muon_passID      ( muoidbit,        mu_minPt1,  mu_minPt2,  mu_maxEta,  ""); 
  aodcalojet_list = aodcalojet_passID( aodcalojetidbit, jet_minPt, jet_maxEta, ""); 
  taggedjet_list  = jet_passTagger   ();

  aodcalojet_minDR_list = jet_minDR();

  // colisions happen @LHC at a given rate, use event_weight
  // to make the simulation match the rate seen in data
  // = lum * cross-section / nrEvents generated
  event_weight = makeEventWeight(crossSec,lumi,nrEvents);
  // for MC, simulated pileup is different from observed
  // in commontools/pileup we make a ratio for scaling MC
  if(isMC) event_weight *= makePUWeight(); //<-----need nTruePU
  // electrons also have an associated scale factor for MC 
  if(isMC) event_weight *= makeElectronWeight( electron_list );

  getMET();

  calculateHT();

  makeDiLepton();

  // set booleans if pass selections 
  passOSSF = (dilep_mass>20.);
  passOSOF = (OSOF_mass>0.);
  passZWindow = (dilep_mass>70. && dilep_mass<110.);
  passZWinOSOF= (OSOF_mass>70. && OSOF_mass<110.);
  passPTOSSF  = (dilep_pt>100.);
  passGoodVtx = true; // = nVtx>0; FIXME put in ntuples
  passOneJet  = false; if (aodcalojet_list.size()>0) passOneJet=true;  
  passOneTag  = false; if (taggedjet_list.size()>0) passOneTag=true;  
  passTwoTag  = false; if (taggedjet_list.size()>1) passTwoTag=true;  
  
  passSingleEle = askPassSingleEle();
  passSingleMu  = askPassSingleMu();
  passDoubleEle = askPassDoubleEle();
  passDoubleMu  = askPassDoubleMu();
  passSinglePho = askPassSinglePho();

  // clear then reset selection vectors
  clearSelections();
  setSelections();

  // set booleans if fall into lepton bin
  dofilllepbin[0] = ( passSingleEle || passDoubleEle ) ;
  dofilllepbin[1] = ( passSingleMu || passDoubleMu ) ;
  dofilllepbin[2] = kTRUE ;

  // set bits if pass various selections, increment counters
  bitsPassSig     = setSelBits( selvecSignal , dofilllepbin, n_passSig    , n_ele_passSig    , n_mu_passSig      ) ;
  bitsPassZH      = setSelBits( selvecZH     , dofilllepbin, n_passZH     , n_ele_passZH     , n_mu_passZH       ) ; 
  bitsPassDY      = setSelBits( selvecDY     , dofilllepbin, n_passDY     , n_ele_passDY     , n_mu_passDY       ) ; 
  bitsPassOffZ    = setSelBits( selvecOffZ   , dofilllepbin, n_passOffZ   , n_ele_passOffZ   , n_mu_passOffZ     ) ; 
  bitsPassNoPair  = setSelBits( selvecNoPair , dofilllepbin, n_passNoPair , n_ele_passNoPair , n_mu_passNoPair   ) ; 
  bitsPassCRHeavy = setSelBits( selvecCRHeavy, dofilllepbin, n_passCRHeavy, n_ele_passCRHeavy, n_mu_passCRHeavy  ) ; 
  bitsPassCRLight = setSelBits( selvecCRLight, dofilllepbin, n_passCRLight, n_ele_passCRLight, n_mu_passCRLight  ) ; 

  // put into array for looping in Cutflow histograms
  selvec[0] = 1;
  selvec[1] = bitsPassSig     ;
  selvec[2] = bitsPassZH      ;
  selvec[3] = bitsPassDY      ;
  selvec[4] = bitsPassOffZ    ;
  selvec[5] = bitsPassNoPair  ;
  selvec[6] = bitsPassCRHeavy ;
  selvec[7] = bitsPassCRLight ;

  dofillselbin[0] = kTRUE         ;
  dofillselbin[1] = ( (bitsPassSig    >> 0) & 1) ; 
  dofillselbin[2] = ( (bitsPassZH     >> 0) & 1) ; 
  dofillselbin[3] = ( (bitsPassDY     >> 0) & 1) ; 
  dofillselbin[4] = ( (bitsPassOffZ   >> 0) & 1) ; 
  dofillselbin[5] = ( (bitsPassNoPair >> 0) & 1) ; 
  dofillselbin[6] = ( (bitsPassCRHeavy>> 0) & 1) ; 
  dofillselbin[7] = ( (bitsPassCRLight>> 0) & 1) ; 

  
  if(doBkgEst){
    //Can choose more regions here
    if( dofilllepbin[1] && dofillselbin[2] ){//mu ZH
      fillBackgroundEstimateHistograms(event_weight);
    }
    //continue;//don't do rest loop
  }
  

  // fill the histograms
  for(unsigned int i=0; i<selbinnames.size(); ++i){
   for(unsigned int j=0; j<lepnames.size(); ++j){
    if (dofilllepbin[j]){
     fillCutflowHistograms( event_weight, i, j, selvec[i] );
     if( dofillselbin[i] ){
      fillSelectedHistograms( event_weight, i, j );

      //jets
      for( unsigned int k=0; k<jetmultnames.size(); ++k){
       fillSelectedJetHistograms( event_weight, i, j, k );
      }  

      //tagged jets
      for( unsigned int k=0; k<tagmultnames.size(); ++k){
       fillSelectedTagHistograms( event_weight, i, j, k );
      }  

     } // if( dofillselbin[i] ){
    } // if (dofilllepbin[j]){
   } // for(unsigned int j=0; j<lepnames.size(); ++j){
  } // for(unsigned int i=0; i<selbinnames.size(); ++i){

  //debug_printobjects();   // helpful printout (turn off when submitting!!!)

  //printf("make log: %0.i\n",makelog);
  
  if( ( (bitsPassCRHeavy >> 0) & 1) ){
   setOPTtree(); 
   OPTtree->Fill();
  }
 } // end loop over entries
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << " Summary     cleaning dR=" << objcleandRcut << std::endl;

 std::cout << " ntot         " << n_tot << std::endl;
 std::cout << " npassSig     " << setw(width) << left << n_passSig     << setw(width) << left << n_ele_passSig     << setw(width) << left << n_mu_passSig     << std::endl;
 std::cout << " npassZH      " << setw(width) << left << n_passZH      << setw(width) << left << n_ele_passZH      << setw(width) << left << n_mu_passZH      << std::endl;
 std::cout << " npassDY      " << setw(width) << left << n_passDY      << setw(width) << left << n_ele_passDY      << setw(width) << left << n_mu_passDY      << std::endl;
 std::cout << " npassOffZ    " << setw(width) << left << n_passOffZ    << setw(width) << left << n_ele_passOffZ    << setw(width) << left << n_mu_passOffZ    << std::endl;
 std::cout << " npassNoPair  " << setw(width) << left << n_passNoPair  << setw(width) << left << n_ele_passNoPair  << setw(width) << left << n_mu_passNoPair  << std::endl;
 std::cout << " npassCRHeavy " << setw(width) << left << n_passCRHeavy << setw(width) << left << n_ele_passCRHeavy << setw(width) << left << n_mu_passCRHeavy << std::endl;
 std::cout << " npassCRLight " << setw(width) << left << n_passCRLight << setw(width) << left << n_ele_passCRLight << setw(width) << left << n_mu_passCRLight << std::endl;
 std::cout << std::endl;
 
 if(doBkgEst){
   //Can choose more regions here
   TFile *outfile = new TFile(outfilename+"_BkgEst.root","RECREATE");
   outfile->cd();
   writeBackgroundEstimateHistograms();
   outfile->Close();
   //return;//don't do more of this function
 }

 // make outfile and save histograms
 // write the histograms
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  TFile *outfile = new TFile(outfilename+"_"+selbinnames[i]+"_histograms.root","RECREATE");
  outfile->cd();
  for(unsigned int j=0; j<lepnames.size(); ++j){

    //Normalize variable binned histograms by bin width
    //Could put this in its own loop for clarity
    scaleVariableBinHistograms( i, j );
    
    writeSelectedHistograms( i, j );
    writeCutflowHistograms( i, j );

    //jet
    for( unsigned int k=0; k<jetmultnames.size(); ++k){
      writeSelectedJetHistograms( i, j, k );
    }

    //tag
    for( unsigned int k=0; k<tagmultnames.size(); ++k){
      writeSelectedTagHistograms( i, j, k );
    }

  }
  outfile->Close();
 }

 optfile->cd();
 OPTtree->CloneTree()->Write();
 optfile->Close();

} // end analyzer_loop::Loop()


void analyzer_loop::debug_printobjects(){

  printf("\n Event %lld\n", event);
  printf(" Pass ossf %d zwind %d ptg50 %d 1jet %d vtx %d \n", passOSSF, passZWindow, passPTOSSF, passOneJet, passGoodVtx);

  debug_printbitset();
  debug_printphotons();
  debug_printmuons();
  debug_printelectrons();

  printf(" Pass SingleEle: %d SingleMu: %d\n", passSingleEle, passSingleMu);

  debug_printdilep();
  debug_printjets();

  return;

 }

void analyzer_loop::debug_printmuons()
{

 // muon debug
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
 return;
}

void analyzer_loop::debug_printelectrons()
{
  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   printf( " electron %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_elePt->at(eleindex), AOD_eleEta->at(eleindex), AOD_elePhi->at(eleindex));
  }
 return;
}


void analyzer_loop::debug_printdilep()
{
  if(dilep_mass>0.){
   printf(" DILEP FOUND\n");
   printf("  l1 pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
     fourVec_l1.Pt(), fourVec_l1.Eta(), fourVec_l1.Phi(), fourVec_l1.M() );
   printf("  l2 pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
     fourVec_l2.Pt(), fourVec_l2.Eta(), fourVec_l2.Phi(), fourVec_l2.M() );
   printf("  ll pt %.1f  eta %.1f  phi %.1f  mass %.1f \n",
      fourVec_ll.Pt(), fourVec_ll.Eta(), fourVec_ll.Phi(), fourVec_ll.M() );
  }
 return;
}

void analyzer_loop::debug_printphotons()
{
  for(int i=0; i<photon_list.size(); ++i){
   int phoindex = photon_list[i];
   printf( " photon %d : pt %.1f eta %.1f phi %.1f\n", i, AOD_phoPt->at(phoindex), AOD_phoEta->at(phoindex), AOD_phoPhi->at(phoindex));
  }
 return;
}

void analyzer_loop::debug_printjets()
{
  for(int i=0; i<aodcalojet_list.size(); ++i){
   int jetindex = aodcalojet_list[i];
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, AODCaloJetPt->at(jetindex), AODCaloJetEta->at(jetindex), AODCaloJetPhi->at(jetindex));
   printf( "  tagvars amax %.1f TA %.1f IP %.1f\n", i, AODCaloJetAlphaMax->at(jetindex), AODCaloJetMedianLog10TrackAngle->at(jetindex), AODCaloJetMedianLog10IPSig->at(jetindex));
  }

  for(int i=0; i<taggedjet_list.size(); ++i){
   int jetindex = taggedjet_list[i];
   printf( " TAGGED JET\n");
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, AODCaloJetPt->at(jetindex), AODCaloJetEta->at(jetindex), AODCaloJetPhi->at(jetindex));
   printf( "  tagvars amax %.1f TA %.1f IP %.1f\n", i, AODCaloJetAlphaMax->at(jetindex), AODCaloJetMedianLog10TrackAngle->at(jetindex), AODCaloJetMedianLog10IPSig->at(jetindex));
  }
 return;
}


void analyzer_loop::debug_printtriggers()
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

void analyzer_loop::debug_printbitset()
{

  std::cout<<" bitsPassSig    "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassSig>>i)&1 );
  }
  std::cout<<"\n";  
  std::cout<<" bitsPassZH     "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassZH    >>i) & 1); 
  }
  std::cout<<"\n";  
  std::cout<<" bitsPassDY     "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassDY    >>i) & 1); 
  }
  std::cout<<"\n";  
  std::cout<<" bitsPassOffZ   "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassOffZ  >>i) & 1); 
  }
  std::cout<<"\n";  
  std::cout<<" bitsPassNoPair "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassNoPair>>i) & 1); 
  }
  std::cout<<"\n";  
  std::cout<<" bitsPassCRHeavy "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassCRHeavy>>i) & 1); 
  }
  std::cout<<"\n";  
  std::cout<<" bitsPassCRLight "; 
  for(unsigned int i=0; i<8; ++i){
   std::cout<< ( (bitsPassCRLight>>i) & 1); 
  }
  std::cout<<"\n";  
 return;

}

