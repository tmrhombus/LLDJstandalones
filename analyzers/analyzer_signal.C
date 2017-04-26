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

  //  // variables used in cuts
  //  if(NGOODVERTICES    ->size()>0){ safeNGOODVERTICES      = NGOODVERTICES    ->at(0);}
  //  if(NDoubleElTriggers->size()>0){ safeNDoubleElTriggers  = NDoubleElTriggers->at(0);}
  //  if(NDoubleMuTriggers->size()>0){ safeNDoubleMuTriggers  = NDoubleMuTriggers->at(0);}
  //  if(NOSSF            ->size()>0){ safeNOSSF              = NOSSF            ->at(0);}
  //  if(MOSSF            ->size()>0){ safeMOSSF              = MOSSF            ->at(0);}
  //   if(safeMOSSF>100000.){ safeMOSSF = 0.;}
  //  if(PTOSSF           ->size()>0){ safePTOSSF             = PTOSSF           ->at(0);}
  //  if(JetNJets         ->size()>0){ safeJetNJets           = JetNJets         ->at(0);}
 
  //fprintf(logfile,"  safeNGOODVERTICES      %d\n" , safeNGOODVERTICES     );    
  //fprintf(logfile,"  safeNDoubleElTriggers  %d\n" , safeNDoubleElTriggers );
  //fprintf(logfile,"  safeNDoubleMuTriggers  %d\n" , safeNDoubleMuTriggers );
  //fprintf(logfile,"  safeMOSSF              %f\n" , safeMOSSF             );
  //fprintf(logfile,"  safeNOSSF              %d\n" , safeNOSSF             );
  //fprintf(logfile,"  safeJetNJets           %d\n" , safeJetNJets          ); 
  //fprintf(logfile,"  safePTOSSF             %f\n\n" , safePTOSSF            );    

  // get lists of "good" electrons, photons, jets

  // set our met

  // get photon, electron, muon vector lists
   // std::vector<int> elelist = electron_passLooseID(pho_index, 10.);  
   // std::vector<int> mulist = muon_passLooseID(pho_index, 10.);       

  // // make dilepton pair
  // fourVec_l1.SetPtEtaPhiE(0,0,0,0);
  // fourVec_l2.SetPtEtaPhiE(0,0,0,0);

  // //  // get electrons and muons and put into 4vectors
  // //  bool passMM = false;
  // //  makeDilep(candphotonindex, &fourVec_l1, &fourVec_l2, &fourVec_ee, &fourVec_mm, &passMM);
  // //  // make dilepton object and add to met
  // fourVec_ll = fourVec_l1 + fourVec_l2;
  // //printf("  pt: %.4f  eta: %.4f  phi: %.4f  mass: %.4f \n", fourVec_l1.Pt(), fourVec_l1.Eta(), fourVec_l1.Phi(), fourVec_l1.M() );
  // //printf("  pt: %.4f  eta: %.4f  phi: %.4f  mass: %.4f \n", fourVec_l2.Pt(), fourVec_l2.Eta(), fourVec_l2.Phi(), fourVec_l2.M() );
  // //printf("  pt: %.4f  eta: %.4f  phi: %.4f  mass: %.4f \n", fourVec_ll.Pt(), fourVec_ll.Eta(), fourVec_ll.Phi(), fourVec_ll.M() );
  // dilep_mass = fourVec_ll.M();
  // //printf(" dilep mass: %0.1f\n", dilep_mass );

  // // Dilepton Mass Window
  // Bool_t passZWindow = (dilep_mass>60. && dilep_mass<120.);
  // Bool_t passdimass20 = (dilep_mass>20.);



  // set booleans if pass various selections
  doesPassSig    = kTRUE;  // askPassSig   ();
  doesPassZH     = kTRUE;  // askPassZH    ();
  doesPassDY     = kTRUE;  // askPassDY    ();
  doesPassOffZ   = kTRUE;  // askPassOffZ  ();
  doesPassNoPair = kTRUE;  // askPassNoPair();

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

   // Jet
   TString hname_jetPt                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetPt                     " ;   
   TString hname_jetEn                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetEn                     " ;   
   TString hname_jetEta                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetEta                    " ;    
   TString hname_jetPhi                      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetPhi                    " ;    
   TString hname_jetRawPt                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetRawPt                  " ;      
   TString hname_jetRawEn                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetRawEn                  " ;      
   TString hname_jetMt                       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetMt                     " ;   
   TString hname_jetArea                     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetArea                   " ;     
   TString hname_jetLeadTrackPt              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLeadTrackPt            " ;            
   TString hname_jetLeadTrackEta             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLeadTrackEta           " ;             
   TString hname_jetLeadTrackPhi             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLeadTrackPhi           " ;             
   TString hname_jetLepTrackPID              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackPID            " ;            
   TString hname_jetLepTrackPt               = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackPt             " ;           
   TString hname_jetLepTrackEta              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackEta            " ;            
   TString hname_jetLepTrackPhi              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetLepTrackPhi            " ;            
   TString hname_jetCSV2BJetTags             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetCSV2BJetTags           " ;             
   TString hname_jetJetProbabilityBJetTags   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetJetProbabilityBJetTags " ;                       
   TString hname_jetpfCombinedMVAV2BJetTags  = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetpfCombinedMVAV2BJetTags" ;                        
   TString hname_jetPartonID                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetPartonID               " ;         
   TString hname_jetHadFlvr                  = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetHadFlvr                " ;        
   TString hname_jetGenJetEn                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetEn               " ;         
   TString hname_jetGenJetPt                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetPt               " ;         
   TString hname_jetGenJetEta                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetEta              " ;          
   TString hname_jetGenJetPhi                = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenJetPhi              " ;          
   TString hname_jetGenPartonID              = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPartonID            " ;            
   TString hname_jetGenEn                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenEn                  " ;      
   TString hname_jetGenPt                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPt                  " ;      
   TString hname_jetGenEta                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenEta                 " ;       
   TString hname_jetGenPhi                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPhi                 " ;       
   TString hname_jetGenPartonMomID           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"jetGenPartonMomID         " ;               
   TString hname_AK8JetPt                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetPt                  " ;      
   TString hname_AK8JetEn                    = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetEn                  " ;      
   TString hname_AK8JetRawPt                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetRawPt               " ;         
   TString hname_AK8JetRawEn                 = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetRawEn               " ;         
   TString hname_AK8JetEta                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetEta                 " ;       
   TString hname_AK8JetPhi                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetPhi                 " ;       
   TString hname_AK8JetMass                  = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"AK8JetMass                " ;        

   // initalize histograms
   h_jetPt                       [i][j] = initSingleHistogramTH1F(  hname_jetPt                      , "jetPt                     " , 50, 0, 500 );   
   h_jetEn                       [i][j] = initSingleHistogramTH1F(  hname_jetEn                      , "jetEn                     " , 50, 0, 500 );   
   h_jetEta                      [i][j] = initSingleHistogramTH1F(  hname_jetEta                     , "jetEta                    " , 10, -5, 5 );    
   h_jetPhi                      [i][j] = initSingleHistogramTH1F(  hname_jetPhi                     , "jetPhi                    " , 10, -5, 5 );    
   h_jetRawPt                    [i][j] = initSingleHistogramTH1F(  hname_jetRawPt                   , "jetRawPt                  " , 50, 0, 500 );      
   h_jetRawEn                    [i][j] = initSingleHistogramTH1F(  hname_jetRawEn                   , "jetRawEn                  " , 50, 0, 500 );      
   h_jetMt                       [i][j] = initSingleHistogramTH1F(  hname_jetMt                      , "jetMt                     " , 50, 0, 500 );   
   h_jetArea                     [i][j] = initSingleHistogramTH1F(  hname_jetArea                    , "jetArea                   " , 50, 0, 1 );     
   h_jetLeadTrackPt              [i][j] = initSingleHistogramTH1F(  hname_jetLeadTrackPt             , "jetLeadTrackPt            " , 50, 0, 100 );            
   h_jetLeadTrackEta             [i][j] = initSingleHistogramTH1F(  hname_jetLeadTrackEta            , "jetLeadTrackEta           " , 50, -5, 5 );             
   h_jetLeadTrackPhi             [i][j] = initSingleHistogramTH1F(  hname_jetLeadTrackPhi            , "jetLeadTrackPhi           " , 50, -5, 5 );             
   h_jetLepTrackPID              [i][j] = initSingleHistogramTH1F(  hname_jetLepTrackPID             , "jetLepTrackPID            " , 25, 0, 25 );            
   h_jetLepTrackPt               [i][j] = initSingleHistogramTH1F(  hname_jetLepTrackPt              , "jetLepTrackPt             " , 50, 0, 500 );           
   h_jetLepTrackEta              [i][j] = initSingleHistogramTH1F(  hname_jetLepTrackEta             , "jetLepTrackEta            " , 50, -5, 5 );            
   h_jetLepTrackPhi              [i][j] = initSingleHistogramTH1F(  hname_jetLepTrackPhi             , "jetLepTrackPhi            " , 50, -5, 5 );            
   h_jetCSV2BJetTags             [i][j] = initSingleHistogramTH1F(  hname_jetCSV2BJetTags            , "jetCSV2BJetTags           " , 50, 0, 1 );             
   h_jetJetProbabilityBJetTags   [i][j] = initSingleHistogramTH1F(  hname_jetJetProbabilityBJetTags  , "jetJetProbabilityBJetTags " , 50, 0, 1 );                       
   h_jetpfCombinedMVAV2BJetTags  [i][j] = initSingleHistogramTH1F(  hname_jetpfCombinedMVAV2BJetTags , "jetpfCombinedMVAV2BJetTags" , 50, 0, 1 );                        
   h_jetPartonID                 [i][j] = initSingleHistogramTH1F(  hname_jetPartonID                , "jetPartonID               " , 25, 0, 25 );         
   h_jetHadFlvr                  [i][j] = initSingleHistogramTH1F(  hname_jetHadFlvr                 , "jetHadFlvr                " , 25, 0, 25 );        
   h_jetGenJetEn                 [i][j] = initSingleHistogramTH1F(  hname_jetGenJetEn                , "jetGenJetEn               " , 50, 0, 500 );         
   h_jetGenJetPt                 [i][j] = initSingleHistogramTH1F(  hname_jetGenJetPt                , "jetGenJetPt               " , 50, 0, 500 );         
   h_jetGenJetEta                [i][j] = initSingleHistogramTH1F(  hname_jetGenJetEta               , "jetGenJetEta              " , 50, -5, 5 );          
   h_jetGenJetPhi                [i][j] = initSingleHistogramTH1F(  hname_jetGenJetPhi               , "jetGenJetPhi              " , 50, -5, 5 );          
   h_jetGenPartonID              [i][j] = initSingleHistogramTH1F(  hname_jetGenPartonID             , "jetGenPartonID            " , 25, 0, 25 );            
   h_jetGenEn                    [i][j] = initSingleHistogramTH1F(  hname_jetGenEn                   , "jetGenEn                  " , 50, 0, 500 );      
   h_jetGenPt                    [i][j] = initSingleHistogramTH1F(  hname_jetGenPt                   , "jetGenPt                  " , 50, 0, 500 );      
   h_jetGenEta                   [i][j] = initSingleHistogramTH1F(  hname_jetGenEta                  , "jetGenEta                 " , 50, -5, 5 );       
   h_jetGenPhi                   [i][j] = initSingleHistogramTH1F(  hname_jetGenPhi                  , "jetGenPhi                 " , 50, -5, 5 );       
   h_jetGenPartonMomID           [i][j] = initSingleHistogramTH1F(  hname_jetGenPartonMomID          , "jetGenPartonMomID         " , 25, 0, 25 );               
   h_AK8JetPt                    [i][j] = initSingleHistogramTH1F(  hname_AK8JetPt                   , "AK8JetPt                  " , 50, 0, 500 );      
   h_AK8JetEn                    [i][j] = initSingleHistogramTH1F(  hname_AK8JetEn                   , "AK8JetEn                  " , 50, 0, 500 );      
   h_AK8JetRawPt                 [i][j] = initSingleHistogramTH1F(  hname_AK8JetRawPt                , "AK8JetRawPt               " , 50, 0, 500 );         
   h_AK8JetRawEn                 [i][j] = initSingleHistogramTH1F(  hname_AK8JetRawEn                , "AK8JetRawEn               " , 50, 0, 500 );         
   h_AK8JetEta                   [i][j] = initSingleHistogramTH1F(  hname_AK8JetEta                  , "AK8JetEta                 " , 50, -5, 5 );       
   h_AK8JetPhi                   [i][j] = initSingleHistogramTH1F(  hname_AK8JetPhi                  , "AK8JetPhi                 " , 50, -5, 5 );       
   h_AK8JetMass                  [i][j] = initSingleHistogramTH1F(  hname_AK8JetMass                 , "AK8JetMass                " , 50, 0, 500 );        

  }
 }

 return kTRUE;
}

//----------------------------fillJetHistograms
Bool_t analyzer_signal::fillJetHistograms(Double_t weight, int selbin)
{

 //printf("fillJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){

  if(jetPt                      ->size()>j){h_jetPt                       [selbin][j].Fill( jetPt                      ->at(j), weight ); } 
  if(jetEn                      ->size()>j){h_jetEn                       [selbin][j].Fill( jetEn                      ->at(j), weight ); } 
  if(jetEta                     ->size()>j){h_jetEta                      [selbin][j].Fill( jetEta                     ->at(j), weight ); } 
  if(jetPhi                     ->size()>j){h_jetPhi                      [selbin][j].Fill( jetPhi                     ->at(j), weight ); } 
  if(jetRawPt                   ->size()>j){h_jetRawPt                    [selbin][j].Fill( jetRawPt                   ->at(j), weight ); } 
  if(jetRawEn                   ->size()>j){h_jetRawEn                    [selbin][j].Fill( jetRawEn                   ->at(j), weight ); } 
  if(jetMt                      ->size()>j){h_jetMt                       [selbin][j].Fill( jetMt                      ->at(j), weight ); } 
  if(jetArea                    ->size()>j){h_jetArea                     [selbin][j].Fill( jetArea                    ->at(j), weight ); } 
  if(jetLeadTrackPt             ->size()>j){h_jetLeadTrackPt              [selbin][j].Fill( jetLeadTrackPt             ->at(j), weight ); } 
  if(jetLeadTrackEta            ->size()>j){h_jetLeadTrackEta             [selbin][j].Fill( jetLeadTrackEta            ->at(j), weight ); } 
  if(jetLeadTrackPhi            ->size()>j){h_jetLeadTrackPhi             [selbin][j].Fill( jetLeadTrackPhi            ->at(j), weight ); } 
  if(jetLepTrackPID             ->size()>j){h_jetLepTrackPID              [selbin][j].Fill( jetLepTrackPID             ->at(j), weight ); } 
  if(jetLepTrackPt              ->size()>j){h_jetLepTrackPt               [selbin][j].Fill( jetLepTrackPt              ->at(j), weight ); } 
  if(jetLepTrackEta             ->size()>j){h_jetLepTrackEta              [selbin][j].Fill( jetLepTrackEta             ->at(j), weight ); } 
  if(jetLepTrackPhi             ->size()>j){h_jetLepTrackPhi              [selbin][j].Fill( jetLepTrackPhi             ->at(j), weight ); } 
  if(jetCSV2BJetTags            ->size()>j){h_jetCSV2BJetTags             [selbin][j].Fill( jetCSV2BJetTags            ->at(j), weight ); } 
  if(jetJetProbabilityBJetTags  ->size()>j){h_jetJetProbabilityBJetTags   [selbin][j].Fill( jetJetProbabilityBJetTags  ->at(j), weight ); } 
  if(jetpfCombinedMVAV2BJetTags ->size()>j){h_jetpfCombinedMVAV2BJetTags  [selbin][j].Fill( jetpfCombinedMVAV2BJetTags ->at(j), weight ); } 
  if(jetPartonID                ->size()>j){h_jetPartonID                 [selbin][j].Fill( jetPartonID                ->at(j), weight ); } 
  if(jetHadFlvr                 ->size()>j){h_jetHadFlvr                  [selbin][j].Fill( jetHadFlvr                 ->at(j), weight ); } 
  if(jetGenJetEn                ->size()>j){h_jetGenJetEn                 [selbin][j].Fill( jetGenJetEn                ->at(j), weight ); } 
  if(jetGenJetPt                ->size()>j){h_jetGenJetPt                 [selbin][j].Fill( jetGenJetPt                ->at(j), weight ); } 
  if(jetGenJetEta               ->size()>j){h_jetGenJetEta                [selbin][j].Fill( jetGenJetEta               ->at(j), weight ); } 
  if(jetGenJetPhi               ->size()>j){h_jetGenJetPhi                [selbin][j].Fill( jetGenJetPhi               ->at(j), weight ); } 
  if(jetGenPartonID             ->size()>j){h_jetGenPartonID              [selbin][j].Fill( jetGenPartonID             ->at(j), weight ); } 
  if(jetGenEn                   ->size()>j){h_jetGenEn                    [selbin][j].Fill( jetGenEn                   ->at(j), weight ); } 
  if(jetGenPt                   ->size()>j){h_jetGenPt                    [selbin][j].Fill( jetGenPt                   ->at(j), weight ); } 
  if(jetGenEta                  ->size()>j){h_jetGenEta                   [selbin][j].Fill( jetGenEta                  ->at(j), weight ); } 
  if(jetGenPhi                  ->size()>j){h_jetGenPhi                   [selbin][j].Fill( jetGenPhi                  ->at(j), weight ); } 
  if(jetGenPartonMomID          ->size()>j){h_jetGenPartonMomID           [selbin][j].Fill( jetGenPartonMomID          ->at(j), weight ); } 
  if(AK8JetPt                   ->size()>j){h_AK8JetPt                    [selbin][j].Fill( AK8JetPt                   ->at(j), weight ); } 
  if(AK8JetEn                   ->size()>j){h_AK8JetEn                    [selbin][j].Fill( AK8JetEn                   ->at(j), weight ); } 
  if(AK8JetRawPt                ->size()>j){h_AK8JetRawPt                 [selbin][j].Fill( AK8JetRawPt                ->at(j), weight ); } 
  if(AK8JetRawEn                ->size()>j){h_AK8JetRawEn                 [selbin][j].Fill( AK8JetRawEn                ->at(j), weight ); } 
  if(AK8JetEta                  ->size()>j){h_AK8JetEta                   [selbin][j].Fill( AK8JetEta                  ->at(j), weight ); } 
  if(AK8JetPhi                  ->size()>j){h_AK8JetPhi                   [selbin][j].Fill( AK8JetPhi                  ->at(j), weight ); } 
  if(AK8JetMass                 ->size()>j){h_AK8JetMass                  [selbin][j].Fill( AK8JetMass                 ->at(j), weight ); } 

 }

 return kTRUE;
}

//----------------------------writeJetHistograms
Bool_t analyzer_signal::writeJetHistograms(int selbin)
{
 //printf("writeJetHistograms\n");
 for(unsigned int j=0; j<jetmultnames.size(); ++j){

   h_jetPt                       [selbin][j].Write(); 
   h_jetEn                       [selbin][j].Write(); 
   h_jetEta                      [selbin][j].Write(); 
   h_jetPhi                      [selbin][j].Write(); 
   h_jetRawPt                    [selbin][j].Write(); 
   h_jetRawEn                    [selbin][j].Write(); 
   h_jetMt                       [selbin][j].Write(); 
   h_jetArea                     [selbin][j].Write(); 
   h_jetLeadTrackPt              [selbin][j].Write(); 
   h_jetLeadTrackEta             [selbin][j].Write(); 
   h_jetLeadTrackPhi             [selbin][j].Write(); 
   h_jetLepTrackPID              [selbin][j].Write(); 
   h_jetLepTrackPt               [selbin][j].Write(); 
   h_jetLepTrackEta              [selbin][j].Write(); 
   h_jetLepTrackPhi              [selbin][j].Write(); 
   h_jetCSV2BJetTags             [selbin][j].Write(); 
   h_jetJetProbabilityBJetTags   [selbin][j].Write(); 
   h_jetpfCombinedMVAV2BJetTags  [selbin][j].Write(); 
   h_jetPartonID                 [selbin][j].Write(); 
   h_jetHadFlvr                  [selbin][j].Write(); 
   h_jetGenJetEn                 [selbin][j].Write(); 
   h_jetGenJetPt                 [selbin][j].Write(); 
   h_jetGenJetEta                [selbin][j].Write(); 
   h_jetGenJetPhi                [selbin][j].Write(); 
   h_jetGenPartonID              [selbin][j].Write(); 
   h_jetGenEn                    [selbin][j].Write(); 
   h_jetGenPt                    [selbin][j].Write(); 
   h_jetGenEta                   [selbin][j].Write(); 
   h_jetGenPhi                   [selbin][j].Write(); 
   h_jetGenPartonMomID           [selbin][j].Write(); 
   h_AK8JetPt                    [selbin][j].Write(); 
   h_AK8JetEn                    [selbin][j].Write(); 
   h_AK8JetRawPt                 [selbin][j].Write(); 
   h_AK8JetRawEn                 [selbin][j].Write(); 
   h_AK8JetEta                   [selbin][j].Write(); 
   h_AK8JetPhi                   [selbin][j].Write(); 
   h_AK8JetMass                  [selbin][j].Write(); 

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
  TString hname_nVtx   = "h_"+selbinnames[i]+"_nVtx  "; 
  TString hname_nPU    = "h_"+selbinnames[i]+"_nPU   "; 
  TString hname_phoEt  = "h_"+selbinnames[i]+"_phoEt "; 
  TString hname_phoEta = "h_"+selbinnames[i]+"_phoEta"; 
  TString hname_phoPhi = "h_"+selbinnames[i]+"_phoPhi"; 
  TString hname_elePt  = "h_"+selbinnames[i]+"_elePt "; 
  TString hname_eleEta = "h_"+selbinnames[i]+"_eleEta"; 
  TString hname_elePhi = "h_"+selbinnames[i]+"_elePhi"; 
  TString hname_muPt   = "h_"+selbinnames[i]+"_muPt  "; 
  TString hname_muEta  = "h_"+selbinnames[i]+"_muEta "; 
  TString hname_muPhi  = "h_"+selbinnames[i]+"_muPhi "; 

  // initalize histograms
  h_nVtx  [i] = initSingleHistogramTH1F( hname_nVtx  , "nVtx  ", 60,0,60) ; 
  h_nPU   [i] = initSingleHistogramTH1F( hname_nPU   , "nPU   ", 60,0,60) ; 
  h_phoEt [i] = initSingleHistogramTH1F( hname_phoEt , "phoEt ", 50,0,300) ; 
  h_phoEta[i] = initSingleHistogramTH1F( hname_phoEta, "phoEta", 10,-5,5) ; 
  h_phoPhi[i] = initSingleHistogramTH1F( hname_phoPhi, "phoPhi", 10,5,5) ; 
  h_elePt [i] = initSingleHistogramTH1F( hname_elePt , "elePt ", 50,0,300) ; 
  h_eleEta[i] = initSingleHistogramTH1F( hname_eleEta, "eleEta", 10,-5,5) ; 
  h_elePhi[i] = initSingleHistogramTH1F( hname_elePhi, "elePhi", 10,-5,50) ; 
  h_muPt  [i] = initSingleHistogramTH1F( hname_muPt  , "muPt  ", 50,0,300) ; 
  h_muEta [i] = initSingleHistogramTH1F( hname_muEta , "muEta ", 10,-5,5) ; 
  h_muPhi [i] = initSingleHistogramTH1F( hname_muPhi , "muPhi ", 10,-5,5) ; 

 }

 return kTRUE;
}

//----------------------------fillSigHistograms
Bool_t analyzer_signal::fillSigHistograms(Double_t weight, int selbin)
{

 //printf("fillSigHistograms\n");
  h_nVtx  [selbin].Fill( nVtx  , weight); 

  if(nPU   ->size()>0){ h_nPU   [selbin].Fill( nPU   ->at(0), weight); } 
  if(phoEt ->size()>0){ h_phoEt [selbin].Fill( phoEt ->at(0), weight); } 
  if(phoEta->size()>0){ h_phoEta[selbin].Fill( phoEta->at(0), weight); } 
  if(phoPhi->size()>0){ h_phoPhi[selbin].Fill( phoPhi->at(0), weight); } 
  if(elePt ->size()>0){ h_elePt [selbin].Fill( elePt ->at(0), weight); } 
  if(eleEta->size()>0){ h_eleEta[selbin].Fill( eleEta->at(0), weight); } 
  if(elePhi->size()>0){ h_elePhi[selbin].Fill( elePhi->at(0), weight); } 
  if(muPt  ->size()>0){ h_muPt  [selbin].Fill( muPt  ->at(0), weight); } 
  if(muEta ->size()>0){ h_muEta [selbin].Fill( muEta ->at(0), weight); } 
  if(muPhi ->size()>0){ h_muPhi [selbin].Fill( muPhi ->at(0), weight); } 


 return kTRUE;
}

//----------------------------writeSigHistograms
//Bool_t analyzer_signal::writeSigHistograms(int ptbin, int sysbin)
Bool_t analyzer_signal::writeSigHistograms(int selbin)
{
 //printf("writeSigHistograms\n");
  h_nVtx  [selbin].Write(); 

  h_nPU   [selbin].Write(); 
  h_phoEt [selbin].Write(); 
  h_phoEta[selbin].Write(); 
  h_phoPhi[selbin].Write(); 
  h_elePt [selbin].Write(); 
  h_eleEta[selbin].Write(); 
  h_elePhi[selbin].Write(); 
  h_muPt  [selbin].Write(); 
  h_muEta [selbin].Write(); 
  h_muPhi [selbin].Write(); 

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

// if ( safeNGOODVERTICES > 0
//     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
//     && ( 70 < safeMOSSF && safeMOSSF < 110 ) 
//     && safePTOSSF > 50
//     && safeJetNJets > 0
//    )
// { doespass = kTRUE; npassZH++;}
 return doespass;
}

Bool_t analyzer_signal::askPassDY()
{
 Bool_t doespass = kFALSE;

// if ( safeNGOODVERTICES > 0
//     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
//     && ( 70 < safeMOSSF && safeMOSSF < 110 ) 
//     && safePTOSSF < 50
//     && safeJetNJets > 0
//    )
// { doespass = kTRUE; npassDY++; }
 return doespass;
}

Bool_t analyzer_signal::askPassOffZ()
{
 Bool_t doespass = kFALSE;

// if ( safeNGOODVERTICES > 0
//     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
//     && !( 70 < safeMOSSF && safeMOSSF < 110 ) 
//     && safeNOSSF == 1
//     && safeJetNJets > 0
//    )
// { doespass = kTRUE; npassOffZ++; }
 return doespass;
}

Bool_t analyzer_signal::askPassNoPair()
{
 Bool_t doespass = kFALSE;

// if ( safeNGOODVERTICES > 0
//     //&& ( safeNDoubleElTriggers > 0.5 || safeNDoubleMuTriggers > 0.5 )
//     && !( 70 < safeMOSSF && safeMOSSF < 110 ) 
//     && safeNOSSF == 0
//     && safeJetNJets > 0
//    )
// { doespass = kTRUE; npassNoPair++; }
 return doespass;
}

analyzer_signal::analyzer_signal()
{
}

analyzer_signal::~analyzer_signal()
{
}



// //-------------------------makeDilep
// void analyzeZllG::makeDilep(int pho_index, TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_ee, TLorentzVector *fv_mm, bool *passMM)
// {          
//                                                                     
//   TLorentzVector e1, e2, ee;                                        
//   TLorentzVector m1, m2, mm;                                        
//   e1.SetPtEtaPhiE( 0,0,0,0 );                                       
//   e2.SetPtEtaPhiE( 0,0,0,0 );                                       
//   m1.SetPtEtaPhiE( 0,0,0,0 );                                       
//   m2.SetPtEtaPhiE( 0,0,0,0 );                                       
//                                                                     
//   // // no pairs                                                    
//   // if( elelist.size()<2 && mulist.size()<2 ){return;}             
//                                                                     
//   //  // electrons                                                      
//   //  if( elelist.size()>1 ){                                           
//   //   for(int i=1; i<elelist.size(); ++i)                              
//   //   {                                                                
//   //    if( eleCharge->at(0)*eleCharge->at(i)==-1 )                     
//   //    {                                                               
//   //     //printf(" --we have electrons ");                             
//   //     e1.SetPtEtaPhiE( elePt->at(elelist[0]), eleEta->at(elelist[0]), elePhi->at(elelist[0]), eleEn->at(elelist[0]) );  
//   //     e2.SetPtEtaPhiE( elePt->at(elelist[i]), eleEta->at(elelist[i]), elePhi->at(elelist[i]), eleEn->at(elelist[i]) );  
//   //     break;   
//   //    }         
//   //   }          
//   //  }           
//   //  //printf(": diele mass = %f", ee.M());  
//   //  ee = e1 + e2;                           
//   //                                          
//   //  // muons                                
//   //  if( mulist.size()>1 ){                  
//   //   for(int i=1; i<mulist.size(); ++i)     
//   //   {                                                                                                                       
//   //     if( muCharge->at(0)*muCharge->at(i)==-1 )                                                                             
//   //     {                                                                                                                     
//   //      //printf(" --we have muons ");                                                                                       
//   //      m1.SetPtEtaPhiE( muPt->at(mulist[0]), muEta->at(mulist[0]), muPhi->at(mulist[0]), muEn->at(mulist[0]) );             
//   //      //printf(": charge pass ");                                                                                          
//   //      m2.SetPtEtaPhiE( muPt->at(mulist[i]), muEta->at(mulist[i]), muPhi->at(mulist[i]), muEn->at(mulist[i]) );             
//   //      break;                                                                                                               
//   //     }                                                                                                                     
//   //   }                                                                                                                       
//   //  }                                                                                                                        
//   //  //printf(": dimu mass = %f", mm.M());                                                                                    
//   //  mm = m1 + m2;                                                                                                            
//   //                                                                                                                           
//   //  *fv_ee = ee;                                                                                                             
//   //  *fv_mm = mm;                                                                                                             
//   //  // take highest mass dilepton pair                                                                                       
//   //  if( mm.M()>ee.M() ){ *fv_1 = m1; *fv_2 = m2; *passMM = true; }                                                           
//   //  else               { *fv_1 = e1; *fv_2 = e2; *passMM = false; }                                                          
//   return;                                                                                                                  
//                                                                                                                            
// } 
