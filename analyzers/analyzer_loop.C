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
                       Double_t crossSec, Int_t nevts, TFile *optfile, TString uncbin)
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

 std::cout<<"uncbin: "<<uncbin<<std::endl;
 TFile *outfile_bkgest = 0;
 bool doBkgEst = true;
 if( doBkgEst && uncbin.EqualTo("") ){
   std::cout<<"doBkgEst"<<std::endl;
   outfile_bkgest = TFile::Open(outfilename+"_BkgEst.root","RECREATE");
   loadMistagRate();
 }

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {

  cleareventcounters();
  if( uncbin.EqualTo("") ){
   optfile->cd();
   clearOPTtree(); 
  }

  //printf(" Event %lld\n", event);
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (jentry%10000 == 0){ std::cout << " entry " << jentry << std::endl; }

  shiftCollections(uncbin);
  n_tot++;

  // get lists of "good" electrons, photons, jets
  // idbit, pt, eta, sysbinname
  electron_list   = electron_passID  ( eleidbit,        ele_minPt1, ele_minPt2, ele_maxEta, "");
  photon_list     = photon_passID    ( phoidbit,        pho_minPt, pho_maxEta, ""); 
  muon_list       = muon_passID      ( muoidbit,        mu_minPt1,  mu_minPt2,  mu_maxEta,  ""); 
  aodcalojet_list = aodcalojet_passID( aodcalojetidbit, jet_minPt, jet_maxEta, ""); 
  //aodpfjet_list    = aodcalojet_passID( aodcalojetidbit, jet_minPt, jet_maxEta, ""); 
  //aodpfchsjet_list = aodcalojet_passID( aodcalojetidbit, jet_minPt, jet_maxEta, ""); 
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
  passGoodVtx = AODnGoodVtx>0; 
  passOneJet  = false; if (aodcalojet_list.size()>0) passOneJet=true;  
  passOneTag  = false; if (taggedjet_list.size()>0) passOneTag=true;  
  passTwoTag  = false; if (taggedjet_list.size()>1) passTwoTag=true;  
  
  passSingleEle = askPassSingleEle();
  passSingleMu  = askPassSingleMu();
  passDoubleEle = askPassDoubleEle();
  passDoubleMu  = askPassDoubleMu();
  passMuEG      = askPassMuEG();
  passSinglePho = askPassSinglePho();

  // clear then reset selection vectors
  clearSelections();
  setSelections();

  // set bits if pass various selections, increment counters
  bitsPassOneEleSig    = setSelBits( selvecOneEleSig    , n_passOneEleSig    );   
  bitsPassTwoEleSig    = setSelBits( selvecTwoEleSig    , n_passTwoEleSig    );   
  bitsPassOneMuSig     = setSelBits( selvecOneMuSig     , n_passOneMuSig     );   
  bitsPassTwoMuSig     = setSelBits( selvecTwoMuSig     , n_passTwoMuSig     );   
  bitsPassOneEleDY     = setSelBits( selvecOneEleDY     , n_passOneEleDY     );   
  bitsPassTwoEleDY     = setSelBits( selvecTwoEleDY     , n_passTwoEleDY     );   
  bitsPassOneMuDY      = setSelBits( selvecOneMuDY      , n_passOneMuDY      );   
  bitsPassTwoMuDY      = setSelBits( selvecTwoMuDY      , n_passTwoMuDY      );   
  bitsPassOneEleZH     = setSelBits( selvecOneEleZH     , n_passOneEleZH     );   
  bitsPassTwoEleZH     = setSelBits( selvecTwoEleZH     , n_passTwoEleZH     );   
  bitsPassOneMuZH      = setSelBits( selvecOneMuZH      , n_passOneMuZH      );   
  bitsPassTwoMuZH      = setSelBits( selvecTwoMuZH      , n_passTwoMuZH      );   
  bitsPassOneEleOffZ   = setSelBits( selvecOneEleOffZ   , n_passOneEleOffZ   );   
  bitsPassTwoEleOffZ   = setSelBits( selvecTwoEleOffZ   , n_passTwoEleOffZ   );   
  bitsPassOneMuOffZ    = setSelBits( selvecOneMuOffZ    , n_passOneMuOffZ    );   
  bitsPassTwoMuOffZ    = setSelBits( selvecTwoMuOffZ    , n_passTwoMuOffZ    );   
  bitsPassOneEleNoPair = setSelBits( selvecOneEleNoPair , n_passOneEleNoPair ); 
  bitsPassOneMuNoPair  = setSelBits( selvecOneMuNoPair  , n_passOneMuNoPair  );   
  bitsPassEleMuOSOF    = setSelBits( selvecEleMuOSOF    , n_passEleMuOSOF    );   
  bitsPassOnePho       = setSelBits( selvecOnePho       , n_passOnePho       );

  keyPassOneEleSig    = setSelKey( selvecOneEleSig    ); 
  keyPassTwoEleSig    = setSelKey( selvecTwoEleSig    ); 
  keyPassOneMuSig     = setSelKey( selvecOneMuSig     ); 
  keyPassTwoMuSig     = setSelKey( selvecTwoMuSig     ); 
  keyPassOneEleDY     = setSelKey( selvecOneEleDY     ); 
  keyPassTwoEleDY     = setSelKey( selvecTwoEleDY     ); 
  keyPassOneMuDY      = setSelKey( selvecOneMuDY      ); 
  keyPassTwoMuDY      = setSelKey( selvecTwoMuDY      ); 
  keyPassOneEleZH     = setSelKey( selvecOneEleZH     ); 
  keyPassTwoEleZH     = setSelKey( selvecTwoEleZH     ); 
  keyPassOneMuZH      = setSelKey( selvecOneMuZH      ); 
  keyPassTwoMuZH      = setSelKey( selvecTwoMuZH      ); 
  keyPassOneEleOffZ   = setSelKey( selvecOneEleOffZ   ); 
  keyPassTwoEleOffZ   = setSelKey( selvecTwoEleOffZ   ); 
  keyPassOneMuOffZ    = setSelKey( selvecOneMuOffZ    ); 
  keyPassTwoMuOffZ    = setSelKey( selvecTwoMuOffZ    ); 
  keyPassOneEleNoPair = setSelKey( selvecOneEleNoPair ); 
  keyPassOneMuNoPair  = setSelKey( selvecOneMuNoPair  ); 
  keyPassEleMuOSOF    = setSelKey( selvecEleMuOSOF    ); 
  keyPassOnePho       = setSelKey( selvecOnePho       ); 

  //debug_printbitset(); // this is a big printout
  //debug_printbitkeys(); // this is a big printout

  // put into array for looping in Cutflow histograms
  selvec[0]  = bitsPassOneEleSig    ; 
  selvec[1]  = bitsPassTwoEleSig    ; 
  selvec[2]  = bitsPassOneMuSig     ; 
  selvec[3]  = bitsPassTwoMuSig     ; 
  selvec[4]  = bitsPassOneEleDY     ; 
  selvec[5]  = bitsPassTwoEleDY     ; 
  selvec[6]  = bitsPassOneMuDY      ; 
  selvec[7]  = bitsPassTwoMuDY      ; 
  selvec[8]  = bitsPassOneEleZH     ; 
  selvec[9]  = bitsPassTwoEleZH     ; 
  selvec[10] = bitsPassOneMuZH      ; 
  selvec[11] = bitsPassTwoMuZH      ; 
  selvec[12] = bitsPassOneEleOffZ   ; 
  selvec[13] = bitsPassTwoEleOffZ   ; 
  selvec[14] = bitsPassOneMuOffZ    ; 
  selvec[15] = bitsPassTwoMuOffZ    ; 
  selvec[16] = bitsPassOneEleNoPair ; 
  selvec[17] = bitsPassOneMuNoPair  ; 
  selvec[18] = bitsPassEleMuOSOF    ; 
  selvec[19] = bitsPassOnePho       ; 

  selkey[0]  = keyPassOneEleSig    ; 
  selkey[1]  = keyPassTwoEleSig    ; 
  selkey[2]  = keyPassOneMuSig     ; 
  selkey[3]  = keyPassTwoMuSig     ; 
  selkey[4]  = keyPassOneEleDY     ; 
  selkey[5]  = keyPassTwoEleDY     ; 
  selkey[6]  = keyPassOneMuDY      ; 
  selkey[7]  = keyPassTwoMuDY      ; 
  selkey[8]  = keyPassOneEleZH     ; 
  selkey[9]  = keyPassTwoEleZH     ; 
  selkey[10] = keyPassOneMuZH      ; 
  selkey[11] = keyPassTwoMuZH      ; 
  selkey[12] = keyPassOneEleOffZ   ; 
  selkey[13] = keyPassTwoEleOffZ   ; 
  selkey[14] = keyPassOneMuOffZ    ; 
  selkey[15] = keyPassTwoMuOffZ    ; 
  selkey[16] = keyPassOneEleNoPair ; 
  selkey[17] = keyPassOneMuNoPair  ; 
  selkey[18] = keyPassEleMuOSOF    ; 
  selkey[19] = keyPassOnePho       ; 

  dofillselbin[0]  = ( ( bitsPassOneEleSig    >> 0) &1) ; 
  dofillselbin[1]  = ( ( bitsPassTwoEleSig    >> 0) &1) ; 
  dofillselbin[2]  = ( ( bitsPassOneMuSig     >> 0) &1) ; 
  dofillselbin[3]  = ( ( bitsPassTwoMuSig     >> 0) &1) ; 
  dofillselbin[4]  = ( ( bitsPassOneEleDY     >> 0) &1) ; 
  dofillselbin[5]  = ( ( bitsPassTwoEleDY     >> 0) &1) ; 
  dofillselbin[6]  = ( ( bitsPassOneMuDY      >> 0) &1) ; 
  dofillselbin[7]  = ( ( bitsPassTwoMuDY      >> 0) &1) ; 
  dofillselbin[8]  = ( ( bitsPassOneEleZH     >> 0) &1) ; 
  dofillselbin[9]  = ( ( bitsPassTwoEleZH     >> 0) &1) ; 
  dofillselbin[10] = ( ( bitsPassOneMuZH      >> 0) &1) ; 
  dofillselbin[11] = ( ( bitsPassTwoMuZH      >> 0) &1) ; 
  dofillselbin[12] = ( ( bitsPassOneEleOffZ   >> 0) &1) ; 
  dofillselbin[13] = ( ( bitsPassTwoEleOffZ   >> 0) &1) ; 
  dofillselbin[14] = ( ( bitsPassOneMuOffZ    >> 0) &1) ; 
  dofillselbin[15] = ( ( bitsPassTwoMuOffZ    >> 0) &1) ; 
  dofillselbin[16] = ( ( bitsPassOneEleNoPair >> 0) &1) ; 
  dofillselbin[17] = ( ( bitsPassOneMuNoPair  >> 0) &1) ; 
  dofillselbin[18] = ( ( bitsPassEleMuOSOF    >> 0) &1) ; 
  dofillselbin[19] = ( ( bitsPassOnePho       >> 0) &1) ; 

  // fake rate code
  if(doBkgEst && uncbin.EqualTo("")){
   if( dofillselbin[11] ){// TwoMuZH
    fillBackgroundEstimateHistograms(event_weight);
   }
  }
  // tagging variable optimization tree
  if( dofillselbin[11] && uncbin.EqualTo("") ){// TwoMuZH
   optfile->cd();
   setOPTtree(); 
   OPTtree->Fill();
  }
  

  // fill the histograms
  for(unsigned int i=0; i<selbinnames.size(); ++i){
   fillCutflowHistograms( event_weight, i, selvec[i], selkey[i] );
   if( dofillselbin[i] ){
    fillSelectedHistograms( event_weight, i );

    //jets
    for( unsigned int k=0; k<jetmultnames.size(); ++k){
     fillSelectedJetHistograms( event_weight, i, k );
    }  

    //tagged jets
    for( unsigned int k=0; k<tagmultnames.size(); ++k){
     fillSelectedTagHistograms( event_weight, i, k );
    }  
   } // if( dofillselbin[i] ){
  } // for(unsigned int i=0; i<selbinnames.size(); ++i){

  //  //debug_printobjects();   // helpful printout (turn off when submitting!!!)
  //
  //  //printf("make log: %0.i\n",makelog);

 } // end loop over entries
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << " Summary     cleaning dR=" << objcleandRcut << std::endl;

 std::cout << " Total events processed  " << n_tot << std::endl;
 //std::cout << "              " << setw(width) << left << "tot"         << setw(width) << left << "ele"             << setw(width) << left << "mu"             << std::endl;

 std::cout<<" n_passOneEleSig    " << setw(width) << left << n_passOneEleSig    << setw(width) << left << (float) n_passOneEleSig   / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleSig    " << setw(width) << left << n_passTwoEleSig    << setw(width) << left << (float) n_passTwoEleSig   / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuSig     " << setw(width) << left << n_passOneMuSig     << setw(width) << left << (float) n_passOneMuSig    / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuSig     " << setw(width) << left << n_passTwoMuSig     << setw(width) << left << (float) n_passTwoMuSig    / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleDY     " << setw(width) << left << n_passOneEleDY     << setw(width) << left << (float) n_passOneEleDY    / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleDY     " << setw(width) << left << n_passTwoEleDY     << setw(width) << left << (float) n_passTwoEleDY    / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuDY      " << setw(width) << left << n_passOneMuDY      << setw(width) << left << (float) n_passOneMuDY     / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuDY      " << setw(width) << left << n_passTwoMuDY      << setw(width) << left << (float) n_passTwoMuDY     / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleZH     " << setw(width) << left << n_passOneEleZH     << setw(width) << left << (float) n_passOneEleZH    / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleZH     " << setw(width) << left << n_passTwoEleZH     << setw(width) << left << (float) n_passTwoEleZH    / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuZH      " << setw(width) << left << n_passOneMuZH      << setw(width) << left << (float) n_passOneMuZH     / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuZH      " << setw(width) << left << n_passTwoMuZH      << setw(width) << left << (float) n_passTwoMuZH     / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleOffZ   " << setw(width) << left << n_passOneEleOffZ   << setw(width) << left << (float) n_passOneEleOffZ  / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoEleOffZ   " << setw(width) << left << n_passTwoEleOffZ   << setw(width) << left << (float) n_passTwoEleOffZ  / (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuOffZ    " << setw(width) << left << n_passOneMuOffZ    << setw(width) << left << (float) n_passOneMuOffZ   / (float) n_tot << std::endl;   
 std::cout<<" n_passTwoMuOffZ    " << setw(width) << left << n_passTwoMuOffZ    << setw(width) << left << (float) n_passTwoMuOffZ   / (float) n_tot << std::endl;   
 std::cout<<" n_passOneEleNoPair " << setw(width) << left << n_passOneEleNoPair << setw(width) << left << (float) n_passOneEleNoPair/ (float) n_tot << std::endl;   
 std::cout<<" n_passOneMuNoPair  " << setw(width) << left << n_passOneMuNoPair  << setw(width) << left << (float) n_passOneMuNoPair / (float) n_tot << std::endl;   
 std::cout<<" n_passEleMuOSOF    " << setw(width) << left << n_passEleMuOSOF    << setw(width) << left << (float) n_passEleMuOSOF   / (float) n_tot << std::endl;   
 std::cout<<" n_passOnePho       " << setw(width) << left << n_passOnePho       << setw(width) << left << (float) n_passOnePho      / (float) n_tot << std::endl;   
 std::cout<<std::endl<<std::endl;

 if(doBkgEst && uncbin.EqualTo("")){
   //Can choose more regions here
   outfile_bkgest->cd();
   writeBackgroundEstimateHistograms(outfile_bkgest);
   outfile_bkgest->Close();
 }
 if( uncbin.EqualTo("") ){
  optfile->cd();
  OPTtree->CloneTree()->Write();
  optfile->Close();
 }

 // make outfile and save histograms
 // write the histograms
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  TFile *outfile = new TFile(outfilename+"_"+selbinnames[i]+"_histograms.root","UPDATE");
  outfile->cd();

    //Normalize variable binned histograms by bin width
    //Could put this in its own loop for clarity
    scaleVariableBinHistograms( i );
    
    writeSelectedHistograms( i );
    writeCutflowHistograms( i );

    //jet
    for( unsigned int k=0; k<jetmultnames.size(); ++k){
      writeSelectedJetHistograms( i, k );
    }

    //tag
    for( unsigned int k=0; k<tagmultnames.size(); ++k){
      writeSelectedTagHistograms( i, k );
    }

  outfile->Close();
 }

} // end analyzer_loop::Loop()


void analyzer_loop::debug_printobjects(){

  printf("\n Event %lld\n", event);
  printf(" Pass ossf %d zwind %d ptg50 %d 1jet %d vtx %d \n", passOSSF, passZWindow, passPTOSSF, passOneJet, passGoodVtx);

  //debug_printbitset();
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
   printf( "  tagvars amax %.1f TA %.1f IP %.1f\n",  AODCaloJetAlphaMax->at(jetindex), AODCaloJetMedianLog10TrackAngle->at(jetindex), AODCaloJetMedianLog10IPSig->at(jetindex));
  }

  for(int i=0; i<taggedjet_list.size(); ++i){
   int jetindex = taggedjet_list[i];
   printf( " TAGGED JET\n");
   printf( " jet %d : pt %.1f eta %.1f phi %.1f\n", i, AODCaloJetPt->at(jetindex), AODCaloJetEta->at(jetindex), AODCaloJetPhi->at(jetindex));
   printf( "  tagvars amax %.1f TA %.1f IP %.1f\n", AODCaloJetAlphaMax->at(jetindex), AODCaloJetMedianLog10TrackAngle->at(jetindex), AODCaloJetMedianLog10IPSig->at(jetindex));
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

 std::cout<<" bitsPassOneEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassTwoMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassTwoMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneEleNoPair "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneEleNoPair >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOneMuNoPair  "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOneMuNoPair  >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassEleMuOSOF    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassEleMuOSOF    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" bitsPassOnePho       "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( bitsPassOnePho       >>i)&1 ); } 
 std::cout<<std::endl;

 return;

}


void analyzer_loop::debug_printbitkeys()
{

 std::cout<<" keyPassOneEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleSig    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleSig    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuSig     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuSig     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleDY     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleDY     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuDY      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuDY      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleZH     "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleZH     >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuZH      "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuZH      >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoEleOffZ   "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoEleOffZ   >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassTwoMuOffZ    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassTwoMuOffZ    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneEleNoPair "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneEleNoPair >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOneMuNoPair  "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOneMuNoPair  >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassEleMuOSOF    "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassEleMuOSOF    >>i)&1 ); } 
 std::cout<<std::endl;
 std::cout<<" keyPassOnePho       "; for(unsigned int i=0; i<8; ++i){ std::cout<<( ( keyPassOnePho       >>i)&1 ); } 
 std::cout<<std::endl;

 return;

}

