#include "analyzer_histograms.h"
#include <iostream>

//----------------------------analyzer_histograms
analyzer_histograms::analyzer_histograms() 
{
}

//----------------------------~analyzer_histograms
analyzer_histograms::~analyzer_histograms()
{
}


//----------------------------~analyzer_histograms
void analyzer_histograms::initSelectionCategories(){

  // Make sure that the numbers in here  match
  // static const int SELBINNAMESIZE  = 6;
  // static const int JETMULTNAMESIZE = 5; 
  // static const int LEPBINNAMESIZE  = 3;
  // initialize names
  jetmultnames.clear();
  jetmultnames.push_back("LeadingJet");
  jetmultnames.push_back("SubleadingJet");
  jetmultnames.push_back("ThirdJet");
  jetmultnames.push_back("FourthJet");
  jetmultnames.push_back("AllJets");

  tagmultnames.clear();
  tagmultnames.push_back("LeadingTag");
  tagmultnames.push_back("SubleadingTag");
  tagmultnames.push_back("ThirdTag");
  tagmultnames.push_back("FourthTag");
  tagmultnames.push_back("AllTags");

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
  selbinnames.push_back("CRHeavy");
  selbinnames.push_back("CRLight");

}



//----------------------------fillSelectedHistograms
Bool_t analyzer_histograms::fillSelectedHistograms(Double_t weight, int selbin, int lepbin)
{
 /// Decide here which histograms to get filled
 fillEleHistograms               ( weight, selbin, lepbin );
 fillMuHistograms                ( weight, selbin, lepbin );
 fillLepHistograms               ( weight, selbin, lepbin );
 fillPhoHistograms               ( weight, selbin, lepbin );
 fillMETHTHistograms             ( weight, selbin, lepbin );
 fillAODCaloJetMultHistograms    ( weight, selbin, lepbin );
 fillAODCaloJetTagMultHistograms ( weight, selbin, lepbin );
}

//----------------------------writeSelectedHistograms
Bool_t analyzer_histograms::writeSelectedHistograms(int selbin, int lepbin)
{
 /// Decide here which histograms to get written
 writeEleHistograms               ( selbin, lepbin );
 writeMuHistograms                ( selbin, lepbin );
 writeLepHistograms               ( selbin, lepbin );
 writePhoHistograms               ( selbin, lepbin );
 writeMETHTHistograms             ( selbin, lepbin );
 writeAODCaloJetMultHistograms    ( selbin, lepbin );
 writeAODCaloJetTagMultHistograms ( selbin, lepbin );
}

//----------------------------fillSelectedJetHistograms
Bool_t analyzer_histograms::fillSelectedJetHistograms(Double_t weight, int selbin, int lepbin, int jetbin )
{
 /// Decide here which jet histograms to get filled
 fillAODCaloJetBasicHistograms( weight, selbin, lepbin, jetbin );
 fillAODCaloJetExtraHistograms( weight, selbin, lepbin, jetbin );
}

//----------------------------writeSelectedJetHistograms
Bool_t analyzer_histograms::writeSelectedJetHistograms(int selbin, int lepbin, int jetbin)
{
 /// Decide here which jet histograms to get written
 writeAODCaloJetBasicHistograms( selbin, lepbin, jetbin );
 writeAODCaloJetExtraHistograms( selbin, lepbin, jetbin );
}

//----------------------------fillSelectedTagHistograms
Bool_t analyzer_histograms::fillSelectedTagHistograms(Double_t weight, int selbin, int lepbin, int tagbin )
{
 /// Decide here which tag histograms to get filled
 fillAODCaloJetTagHistograms( weight, selbin, lepbin, tagbin );
}

//----------------------------writeSelectedTagHistograms
Bool_t analyzer_histograms::writeSelectedTagHistograms(int selbin, int lepbin, int tagbin)
{
 /// Decide here which tag histograms to get written
 writeAODCaloJetTagHistograms( selbin, lepbin, tagbin );
}

//----------------------------initSingleHistogramTH1F
TH1F analyzer_histograms::initSingleHistogramTH1F(TString hname, TString htitle, Int_t nbins, Double_t xmin, Double_t xmax)
{

 histoTH1F.Clear();
 histoTH1F = TH1F( hname , htitle , nbins , xmin , xmax );
 histoTH1F.Sumw2();

 return histoTH1F;

}

//Overload for variable binning
TH1F analyzer_histograms::initSingleHistogramTH1F(TString hname, TString htitle, int nbins, Float_t xbins[])
{

  histoTH1F.Clear();
  histoTH1F = TH1F( hname , htitle , nbins , xbins );
  histoTH1F.Sumw2();

  return histoTH1F;

}



//----------------------------initSingleHistogramTH2F
TH2F analyzer_histograms::initSingleHistogramTH2F(TString hname, TString htitle,
                                   Int_t nbinsx, Double_t xmin, Double_t xmax,
                                   Int_t nbinsy, Double_t ymin, Double_t ymax)
{

 histoTH2F.Clear();
 histoTH2F = TH2F( hname , htitle , nbinsx , xmin , xmax  , nbinsy , ymin , ymax );
 histoTH2F.Sumw2();

 return histoTH2F;

}


TH2F analyzer_histograms::initSingleHistogramTH2F(TString hname, TString htitle,
						  int nbinsx, Float_t xbins[],
						  int nbinsy, Float_t ybins[])
{

 histoTH2F.Clear();
 histoTH2F = TH2F( hname , htitle , nbinsx , xbins , nbinsy , ybins );
 histoTH2F.Sumw2();

 return histoTH2F;

}

//----------------------------init2DHistograms
Bool_t analyzer_histograms::init2DHistograms()
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
Bool_t analyzer_histograms::fill2DHistograms(Double_t weight, int selbin)
{
  // //printf("fill2DHistograms\n");
  //
  //  if( NGOODVERTICES->size()>0 && JetNJets->size()>0 ) 
  //   { h_nvertnjets[selbin].Fill( NGOODVERTICES->at(0), JetNJets->at(0), weight ); }
  //
 return kTRUE;
}


//----------------------------write2DHistograms
Bool_t analyzer_histograms::write2DHistograms(int selbin)
{
 ////printf("write2DtHistograms\n");
 //h_nvertnjets[selbin].Write(); 
 //for(unsigned int j=0; j<jetmultnames.size(); ++j){
 //  // for histograms that are jet specific
 //}

 return kTRUE;
}


//----------------------------initEleHistograms
Bool_t analyzer_histograms::initEleHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){
   TString hname_AOD_nEle                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_nEle        "; 
   TString hname_AOD_nSelectedEle            = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_nSelectedEle";
   TString hname_AOD_elePt                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_elePt       "; 
   TString hname_AOD_eleEn                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_eleEn       "; 
   TString hname_AOD_eleEta                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_eleEta      "; 
   TString hname_AOD_elePhi                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_elePhi      "; 
   TString hname_AOD_eleCharge               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_eleCharge   "; 

   h_AOD_nEle                     [i][k] = initSingleHistogramTH1F( hname_AOD_nEle                    , "AOD_nEle                   ", 6,  0, 6) ;  
   h_AOD_nSelectedEle             [i][k] = initSingleHistogramTH1F( hname_AOD_nSelectedEle            , "AOD_nSelectedEle           ", 10,0,10);
   h_AOD_elePt                    [i][k] = initSingleHistogramTH1F( hname_AOD_elePt                   , "AOD_elePt                  ", 50, 0, 500) ;  
   h_AOD_eleEn                    [i][k] = initSingleHistogramTH1F( hname_AOD_eleEn                   , "AOD_eleEn                  ", 50, 0, 500) ;  
   h_AOD_eleEta                   [i][k] = initSingleHistogramTH1F( hname_AOD_eleEta                  , "AOD_eleEta                 ", 30, -5, 5); 
   h_AOD_elePhi                   [i][k] = initSingleHistogramTH1F( hname_AOD_elePhi                  , "AOD_elePhi                 ", 30, -5, 5); 
   h_AOD_eleCharge                [i][k] = initSingleHistogramTH1F( hname_AOD_eleCharge               , "AOD_eleCharge              ", 3, -1, 1); 
  }
 }
 return kTRUE;
}

//----------------------------fillEleHistograms
Bool_t analyzer_histograms::fillEleHistograms(Double_t weight, int selbin, int lepbin)
{
  h_AOD_nEle            [selbin][lepbin] .Fill( float(nAODEle), weight );
  h_AOD_nSelectedEle    [selbin][lepbin] .Fill( float(electron_list.size()), weight );
  // fill leading electron in vector
  if(electron_list.size() > 0){
   int eleindex = electron_list[0];
   h_AOD_elePt               [selbin][lepbin] .Fill( AOD_elePt               ->at(eleindex), weight );  
   h_AOD_eleEn               [selbin][lepbin] .Fill( AOD_eleEn               ->at(eleindex), weight );  
   h_AOD_eleEta              [selbin][lepbin] .Fill( AOD_eleEta              ->at(eleindex), weight );  
   h_AOD_elePhi              [selbin][lepbin] .Fill( AOD_elePhi              ->at(eleindex), weight );  
   h_AOD_eleCharge           [selbin][lepbin] .Fill( AOD_eleCharge           ->at(eleindex), weight );  
  }
 return kTRUE;
}

//----------------------------writeEleHistograms
Bool_t analyzer_histograms::writeEleHistograms(int selbin, int lepbin)
{
 h_AOD_nEle            [selbin][lepbin] .Write();
 h_AOD_nSelectedEle    [selbin][lepbin] .Write();
 h_AOD_elePt           [selbin][lepbin] .Write();
 h_AOD_eleEn           [selbin][lepbin] .Write();
 h_AOD_eleEta          [selbin][lepbin] .Write();
 h_AOD_elePhi          [selbin][lepbin] .Write();
 h_AOD_eleCharge       [selbin][lepbin] .Write();
 return kTRUE;
}


//----------------------------initMuHistograms
Bool_t analyzer_histograms::initMuHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){
   TString hname_AOD_nMu                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_nMu                "; 
   TString hname_AOD_nSelectedMu             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_nSelectedMu        ";
   TString hname_AOD_muPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muPt               "; 
   TString hname_AOD_muEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muEn               "; 
   TString hname_AOD_muEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muEta              "; 
   TString hname_AOD_muPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muPhi              "; 
   TString hname_AOD_muCharge                = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muCharge           "; 
   TString hname_AOD_muPFdBetaIsolation      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_muPFdBetaIsolation "; 

   h_AOD_nMu                      [i][k] = initSingleHistogramTH1F( hname_AOD_nMu                     , "AOD_nMu                    ", 6,  0, 6) ;  
   h_AOD_nSelectedMu              [i][k] = initSingleHistogramTH1F( hname_AOD_nSelectedMu             , "AOD_nSelectedMu            ", 10,0,10);
   h_AOD_muPt                     [i][k] = initSingleHistogramTH1F( hname_AOD_muPt                    , "AOD_muPt                   ", 50, 0, 500) ;  
   h_AOD_muEn                     [i][k] = initSingleHistogramTH1F( hname_AOD_muEn                    , "AOD_muEn                   ", 50, 0, 500) ;  
   h_AOD_muEta                    [i][k] = initSingleHistogramTH1F( hname_AOD_muEta                   , "AOD_muEta                  ", 30, -5, 5); 
   h_AOD_muPhi                    [i][k] = initSingleHistogramTH1F( hname_AOD_muPhi                   , "AOD_muPhi                  ", 30, -5, 5); 
   h_AOD_muCharge                 [i][k] = initSingleHistogramTH1F( hname_AOD_muCharge                , "AOD_muCharge               ", 3, -1, 1); 
   h_AOD_muPFdBetaIsolation       [i][k] = initSingleHistogramTH1F( hname_AOD_muPFdBetaIsolation      , "AOD_muPFdBetaIsolation     ", 30, -5, 5); 
  }
 }
 return kTRUE;
}


//----------------------------initLepHistograms
Bool_t analyzer_histograms::initLepHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){
   TString hname_AOD_dilepton_Mass = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_dilepton_Mass"; 
   TString hname_AOD_dilepton_Pt   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_dilepton_Pt  "; 

   h_AOD_dilepton_Mass[i][k] = initSingleHistogramTH1F( hname_AOD_dilepton_Mass, "AOD_dilepton_Mass", 30,  30, 150) ;  
   h_AOD_dilepton_Pt  [i][k] = initSingleHistogramTH1F( hname_AOD_dilepton_Pt  , "AOD_dilepton_Pt  ", 30,   0, 300) ;  
  }
 }
 return kTRUE;
}


//----------------------------fillMuHistograms
Bool_t analyzer_histograms::fillMuHistograms(Double_t weight, int selbin, int lepbin)
{
  h_AOD_nMu            [selbin][lepbin] .Fill( float(nAODMu), weight );
  h_AOD_nSelectedMu    [selbin][lepbin] .Fill( float(muon_list.size()), weight );
  // fill leading muon in vector
  if(muon_list.size() > 0){
   int muindex = muon_list[0];
   h_AOD_muPt               [selbin][lepbin] .Fill( AOD_muPt               ->at(muindex), weight );  
   h_AOD_muEn               [selbin][lepbin] .Fill( AOD_muEn               ->at(muindex), weight );  
   h_AOD_muEta              [selbin][lepbin] .Fill( AOD_muEta              ->at(muindex), weight );  
   h_AOD_muPhi              [selbin][lepbin] .Fill( AOD_muPhi              ->at(muindex), weight );  
   h_AOD_muCharge           [selbin][lepbin] .Fill( AOD_muCharge           ->at(muindex), weight );  
   h_AOD_muPFdBetaIsolation [selbin][lepbin] .Fill( AOD_muPFdBetaIsolation ->at(muindex), weight );  
  }
 return kTRUE;
}

//----------------------------writeMuHistograms
Bool_t analyzer_histograms::writeMuHistograms(int selbin, int lepbin)
{
 h_AOD_nMu                     [selbin][lepbin] .Write();
 h_AOD_nSelectedMu             [selbin][lepbin] .Write();
 h_AOD_muPt                    [selbin][lepbin] .Write();
 h_AOD_muEn                    [selbin][lepbin] .Write();
 h_AOD_muEta                   [selbin][lepbin] .Write();
 h_AOD_muPhi                   [selbin][lepbin] .Write(); 
 h_AOD_muCharge                [selbin][lepbin] .Write(); 
 h_AOD_muPFdBetaIsolation      [selbin][lepbin] .Write(); 
 return kTRUE;
}


//----------------------------fillLepHistograms
Bool_t analyzer_histograms::fillLepHistograms(Double_t weight, int selbin, int lepbin)
{
  h_AOD_dilepton_Mass  [selbin][lepbin] .Fill( dilep_mass, weight );
  h_AOD_dilepton_Pt    [selbin][lepbin] .Fill( dilep_pt, weight );
  return kTRUE;
}


//----------------------------writeLepHistograms
Bool_t analyzer_histograms::writeLepHistograms(int selbin, int lepbin)
{
 h_AOD_dilepton_Mass           [selbin][lepbin] .Write();
 h_AOD_dilepton_Pt             [selbin][lepbin] .Write();
 return kTRUE;
}


//----------------------------initPhoHistograms
Bool_t analyzer_histograms::initPhoHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){
   TString hname_AOD_nPho                     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_nPho        ";
   TString hname_AOD_nSelectedPho             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_nSelectedPho";
   TString hname_AOD_phoEn                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoEn       "; 
   TString hname_AOD_phoPt                    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoPt       "; 
   TString hname_AOD_phoEta                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoEta      "; 
   TString hname_AOD_phoPhi                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_phoPhi      "; 

   h_AOD_nPho                     [i][k] = initSingleHistogramTH1F( hname_AOD_nPho                    , "AOD_nPho        ", 6,  0, 6) ;  
   h_AOD_nSelectedPho             [i][k] = initSingleHistogramTH1F( hname_AOD_nSelectedPho            , "AOD_nSelectedPho", 10,0,10);
   h_AOD_phoEn                    [i][k] = initSingleHistogramTH1F( hname_AOD_phoEn                   , "AOD_phoEn       ", 50, 0, 500) ;  
   h_AOD_phoPt                    [i][k] = initSingleHistogramTH1F( hname_AOD_phoPt                   , "AOD_phoPt       ", 50, 0, 500) ;  
   h_AOD_phoEta                   [i][k] = initSingleHistogramTH1F( hname_AOD_phoEta                  , "AOD_phoEta      ", 30, -5, 5); 
   h_AOD_phoPhi                   [i][k] = initSingleHistogramTH1F( hname_AOD_phoPhi                  , "AOD_phoPhi      ", 30, -5, 5); 
  }
 }
 return kTRUE;
}

//----------------------------fillPhoHistograms
Bool_t analyzer_histograms::fillPhoHistograms(Double_t weight, int selbin, int lepbin)
{
 // fill leading photon in vector
  h_AOD_nPho              [selbin][lepbin] .Fill( float(nAODPho), weight );
  h_AOD_nSelectedPho      [selbin][lepbin] .Fill( float(photon_list.size()), weight );
  if(photon_list.size() > 0){
   int phoindex = photon_list[0];
   h_AOD_phoEn    [selbin][lepbin] .Fill( AOD_phoEn   ->at(phoindex), weight );  
   h_AOD_phoPt    [selbin][lepbin] .Fill( AOD_phoPt   ->at(phoindex), weight );  
   h_AOD_phoEta   [selbin][lepbin] .Fill( AOD_phoEta  ->at(phoindex), weight );  
   h_AOD_phoPhi   [selbin][lepbin] .Fill( AOD_phoPhi  ->at(phoindex), weight );  
  }
 return kTRUE;
}

//----------------------------writePhoHistograms
Bool_t analyzer_histograms::writePhoHistograms(int selbin, int lepbin)
{
 h_AOD_nPho              [selbin][lepbin] .Write();
 h_AOD_nSelectedPho      [selbin][lepbin] .Write();
 h_AOD_phoEn             [selbin][lepbin] .Write(); 
 h_AOD_phoPt             [selbin][lepbin] .Write(); 
 h_AOD_phoEta            [selbin][lepbin] .Write(); 
 h_AOD_phoPhi            [selbin][lepbin] .Write(); 
 return kTRUE;
}

//----------------------------initMETHTHistograms
Bool_t analyzer_histograms::initMETHTHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){
   TString hname_AOD_MET_phi                 = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_MET_phi    "; 
   TString hname_AOD_MET_pt                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_AOD_MET_pt    "; 
   TString hname_htall                       = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htall        " ;
   TString hname_htaodcalojets               = "h_"+lepnames[k]+"_"+selbinnames[i]+"_htaodcalojets" ;

   h_AOD_MET_phi                  [i][k] = initSingleHistogramTH1F( hname_AOD_MET_phi         , "AOD_MET_phi  " , 30, -5, 5); 
   h_AOD_MET_pt                   [i][k] = initSingleHistogramTH1F( hname_AOD_MET_pt          , "AOD_MET_pt   " , 50, 0, 500); 
   h_htall                        [i][k] = initSingleHistogramTH1F( hname_htall               , "htall        " , 50,0,1000) ; 
   h_htaodcalojets                [i][k] = initSingleHistogramTH1F( hname_htaodcalojets       , "htaodcalojets" , 50,0,1000) ; 
  }
 }

 return kTRUE;
}

//----------------------------fillMETHTHistograms
Bool_t analyzer_histograms::fillMETHTHistograms(Double_t weight, int selbin, int lepbin)
{
 h_AOD_MET_phi             [selbin][lepbin] .Fill( themephi       , weight);  
 h_AOD_MET_pt              [selbin][lepbin] .Fill( themet         , weight);  
 h_htall                   [selbin][lepbin] .Fill( htall          , weight); 
 h_htaodcalojets           [selbin][lepbin] .Fill( htaodcalojets  , weight); 
 return kTRUE;
}

//----------------------------writeMETHTHistograms
Bool_t analyzer_histograms::writeMETHTHistograms(int selbin, int lepbin)
{
 h_AOD_MET_phi             [selbin][lepbin] .Write(); 
 h_AOD_MET_pt              [selbin][lepbin] .Write(); 
 h_htall                   [selbin][lepbin] .Write(); 
 h_htaodcalojets           [selbin][lepbin] .Write(); 
 return kTRUE;
}

///// Jet Histograms
//----------------------------initAODCaloJetBasicHistograms
Bool_t analyzer_histograms::initAODCaloJetBasicHistograms()
{
  
  // loop through jets and selections to initialize histograms in parllel (series)
  for(unsigned int i=0; i<selbinnames.size(); ++i){
    for(unsigned int j=0; j<lepnames.size(); ++j){
      TString hname_nCaloJet                 = "h_"+lepnames[j]+"_"+selbinnames[i]+"_nCaloJet";
      TString hname_nPFJet                   = "h_"+lepnames[j]+"_"+selbinnames[i]+"_nPFJet";
      TString hname_nPFchsJet                = "h_"+lepnames[j]+"_"+selbinnames[i]+"_nPFchsJet";
      h_nCaloJet                 [i][j] = initSingleHistogramTH1F( hname_nCaloJet , "nCaloJet", 10,0,10);
      h_nPFJet                   [i][j] = initSingleHistogramTH1F( hname_nPFJet , "nPFJet", 10,0,10);
      h_nPFchsJet                [i][j] = initSingleHistogramTH1F( hname_nPFchsJet , "nPFchsJet", 10,0,10);

      for(unsigned int k=0; k<jetmultnames.size(); ++k){
        //std::cout<<" i "<<i<<" "<<selbinnames[i]<<" j "<<j<<" "<<lepnames[j]<<" k "<<k<<" "<<jetmultnames[k]<< std::endl;
	TString hname_AODCaloJetPt                            = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPt";                             
	TString hname_AODCaloJetPtVar                         = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPtVar";                             
	TString hname_AODCaloJetEta                           = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetEta";                            
	TString hname_AODCaloJetPhi                           = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPhi";                            
	TString hname_AODCaloJetAlphaMax                      = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMax";                       
	TString hname_AODCaloJetAlphaMax2                     = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMax2";                      
	TString hname_AODCaloJetAlphaMaxPrime                 = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMaxPrime";                  
	TString hname_AODCaloJetAlphaMaxPrime2                = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMaxPrime2";                 
	TString hname_AODCaloJetBeta                          = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetBeta";                           
	TString hname_AODCaloJetBeta2                         = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetBeta2";                          
	TString hname_AODCaloJetSumIP                         = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetSumIP";                          
	TString hname_AODCaloJetSumIPSig                      = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetSumIPSig";                       
	TString hname_AODCaloJetMedianIP                      = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMedianIP";                       
	TString hname_AODCaloJetMedianLog10IPSig              = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMedianLog10IPSig";               
	TString hname_AODCaloJetTrackAngle                    = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetTrackAngle";                     
	TString hname_AODCaloJetLogTrackAngle                 = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetLogTrackAngle";                  
	TString hname_AODCaloJetMedianLog10TrackAngle         = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMedianLog10TrackAngle";          
	TString hname_AODCaloJetTotalTrackAngle               = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetTotalTrackAngle";                
	TString hname_AODCaloJetMinDR                         = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMinDR";
        TString hname_AODCaloJetAbsEta                        = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAbsEta";
	TString hname_AODCaloJetPtVarAbsEtaVar                = "h_"+lepnames[j]+"_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPtVarAbsEtaVar";                             
	
	h_AODCaloJetPt                             [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetPt                             , "AODCaloJetPt                            ", 50,0,500  ); 
	h_AODCaloJetEta                            [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetEta                            , "AODCaloJetEta                           ", 30,-5,5   ); 
	h_AODCaloJetPhi                            [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetPhi                            , "AODCaloJetPhi                           ", 30,-5,5   ); 
	h_AODCaloJetAlphaMax                       [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax                       , "AODCaloJetAlphaMax                      ", 30, 0, 1  ); 
	h_AODCaloJetAlphaMax2                      [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax2                      , "AODCaloJetAlphaMax2                     ", 30, 0, 1  ); 
	h_AODCaloJetAlphaMaxPrime                  [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime                  , "AODCaloJetAlphaMaxPrime                 ", 30, 0, 1  ); 
	h_AODCaloJetAlphaMaxPrime2                 [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime2                 , "AODCaloJetAlphaMaxPrime2                ", 30, 0, 1  ); 
	h_AODCaloJetBeta                           [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetBeta                           , "AODCaloJetBeta                          ", 30, 0, 1  ); 
	h_AODCaloJetBeta2                          [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetBeta2                          , "AODCaloJetBeta2                         ", 30, 0, 1  ); 
	h_AODCaloJetSumIP                          [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetSumIP                          , "AODCaloJetSumIP                         ", 30, -3, 3 ); 
	h_AODCaloJetSumIPSig                       [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetSumIPSig                       , "AODCaloJetSumIPSig                      ", 30, -3, 3 ); 
	h_AODCaloJetMedianIP                       [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetMedianIP                       , "AODCaloJetMedianIP                      ", 30, -3, 3 ); 
	h_AODCaloJetMedianLog10IPSig               [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10IPSig               , "AODCaloJetMedianLog10IPSig              ", 30, -3, 3 ); 
	h_AODCaloJetTrackAngle                     [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetTrackAngle                     , "AODCaloJetTrackAngle                    ", 30, -3, 3 ); 
	h_AODCaloJetLogTrackAngle                  [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetLogTrackAngle                  , "AODCaloJetLogTrackAngle                 ", 30, -3, 3 ); 
	h_AODCaloJetMedianLog10TrackAngle          [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10TrackAngle          , "AODCaloJetMedianLog10TrackAngle         ", 30, -5, 1 ); 
	h_AODCaloJetTotalTrackAngle                [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetTotalTrackAngle                , "AODCaloJetTotalTrackAngle               ", 30, -3, 3 ); 
	h_AODCaloJetMinDR                          [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetMinDR                          , "AODCaloJetMinDR                         ", 30, 0, 5 ); 
        h_AODCaloJetAbsEta                         [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetAbsEta                         , "AODCaloJetAbsEta                        ", 4, 0, 3 );

	const int Pt_n_xbins = 10;
	float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
	h_AODCaloJetPtVar                             [i][k][j] = initSingleHistogramTH1F( hname_AODCaloJetPtVar                             , "AODCaloJetPtVar                            ",  Pt_n_xbins, Pt_xbins );

	
	const int AbsEta_n_bins = 2;
	float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
	h_AODCaloJetPtVarAbsEtaVar [i][k][j] = initSingleHistogramTH2F( hname_AODCaloJetPtVarAbsEtaVar, "AODCaloJetPtVarAbsEtaVar", Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins );

      }
    }
  }
  return kTRUE;
}

//----------------------------initAODCaloJetExtraHistograms
Bool_t analyzer_histograms::initAODCaloJetExtraHistograms()
{

 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int j=0; j<jetmultnames.size(); ++j){
   for(unsigned int k=0; k<lepnames.size(); ++k){

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
    h_AODCaloJetNCleanMatchedTracks            [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetNCleanMatchedTracks            , "AODCaloJetNCleanMatchedTracks           ", 20, 0, 20 ); 
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
 return kTRUE;
} //initAODCaloJetHistograms


//----------------------------initAODCaloJetTagHistograms
Bool_t analyzer_histograms::initAODCaloJetTagHistograms()
{

 // loop through jets and selections to initialize histograms in parallel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int j=0; j<tagmultnames.size(); ++j){
   for(unsigned int k=0; k<lepnames.size(); ++k){

    TString hname_AODCaloJetPt_Tag0                      = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPt_Tag0";
    TString hname_AODCaloJetPtVar_Tag0                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPtVar_Tag0";
    TString hname_AODCaloJetMinDR_Tag0                   = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetMinDR_Tag0";
    TString hname_AODCaloJetAbsEta_Tag0                  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetAbsEta_Tag0";
    TString hname_AODCaloJetNCleanMatchedTracks_Tag0     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetNCleanMatchedTracks_Tag0";
    TString hname_AODCaloJetPtVarAbsEtaVar_Tag0          = "h_"+lepnames[k]+"_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPtVarAbsEtaVar_Tag0";

    h_AODCaloJetPt_Tag0                       [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetPt_Tag0                       , "AODCaloJetPt_Tag0                      ", 50, 0, 500); 
    h_AODCaloJetMinDR_Tag0                    [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetMinDR_Tag0                    , "AODCaloJetMinDR_Tag0                   ", 30, 0, 5); 
    h_AODCaloJetAbsEta_Tag0                   [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetAbsEta_Tag0                   , "AODCaloJetAbsEta_Tag0                  ", 4, 0, 3);
    h_AODCaloJetNCleanMatchedTracks_Tag0      [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetNCleanMatchedTracks_Tag0      , "AODCaloJetNCleanMatchedTracks_Tag0     ", 20, 0, 20); 

    const int Pt_n_xbins = 10;
    float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
    h_AODCaloJetPtVar_Tag0                    [i][j][k] = initSingleHistogramTH1F( hname_AODCaloJetPtVar_Tag0                    , "AODCaloJetPtVar_Tag0                      ", Pt_n_xbins, Pt_xbins);

    const int AbsEta_n_bins = 2;
    float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
    h_AODCaloJetPtVarAbsEtaVar_Tag0           [i][j][k] = initSingleHistogramTH2F(hname_AODCaloJetPtVarAbsEtaVar_Tag0, "AODCaloJetPtVarAbsEtaVar_Tag0", Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins );



   } //   for(unsigned int i=0; i<selbinnames.size(); ++i){
  } //  for(unsigned int j=0; j<tagmultnames.size(); ++j){
 } // for(unsigned int k=0; k<lepnames.size(); ++k){
 return kTRUE;
} //initAODCaloJetTagHistograms


//----------------------------fillAODCaloJetBasicHistograms
Bool_t analyzer_histograms::fillAODCaloJetBasicHistograms(Double_t weight, int selbin, int lepbin, int jetbin)
{

  if(jetmultnames.at(jetbin) == "AllJets"){
    for(unsigned int i =0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i];
      h_AODCaloJetPt                             [selbin][jetbin][lepbin].Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPtVar                          [selbin][jetbin][lepbin].Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetEta                            [selbin][jetbin][lepbin].Fill( AODCaloJetEta                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPhi                            [selbin][jetbin][lepbin].Fill( AODCaloJetPhi                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax                       [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMax                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax2                      [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMax2                      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta                           [selbin][jetbin][lepbin].Fill( AODCaloJetBeta                           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta2                          [selbin][jetbin][lepbin].Fill( AODCaloJetBeta2                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIP                          [selbin][jetbin][lepbin].Fill( AODCaloJetSumIP                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIPSig                       [selbin][jetbin][lepbin].Fill( AODCaloJetSumIPSig                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianIP                       [selbin][jetbin][lepbin].Fill( AODCaloJetMedianIP                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10IPSig               [selbin][jetbin][lepbin].Fill( AODCaloJetMedianLog10IPSig               ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin][lepbin].Fill( AODCaloJetMedianLog10TrackAngle          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetTotalTrackAngle                [selbin][jetbin][lepbin].Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMinDR                          [selbin][jetbin][lepbin].Fill( aodcalojet_minDR_list                     .at( aodcalojetindex ), weight );  
      h_AODCaloJetAbsEta                         [selbin][jetbin][lepbin].Fill( fabs(AODCaloJetEta                       ->at( aodcalojetindex )), weight );
      h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin][lepbin].Fill( AODCaloJetPt->at(aodcalojetindex), fabs(AODCaloJetEta->at(aodcalojetindex)), weight );  
    }    
  }
  else{
    if( jetbin < (int)aodcalojet_list.size() ){
      int aodcalojetindex = aodcalojet_list[jetbin];
      h_AODCaloJetPt                             [selbin][jetbin][lepbin].Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPtVar                          [selbin][jetbin][lepbin].Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetEta                            [selbin][jetbin][lepbin].Fill( AODCaloJetEta                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPhi                            [selbin][jetbin][lepbin].Fill( AODCaloJetPhi                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax                       [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMax                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax2                      [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMax2                      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin][lepbin].Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta                           [selbin][jetbin][lepbin].Fill( AODCaloJetBeta                           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta2                          [selbin][jetbin][lepbin].Fill( AODCaloJetBeta2                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIP                          [selbin][jetbin][lepbin].Fill( AODCaloJetSumIP                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIPSig                       [selbin][jetbin][lepbin].Fill( AODCaloJetSumIPSig                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianIP                       [selbin][jetbin][lepbin].Fill( AODCaloJetMedianIP                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10IPSig               [selbin][jetbin][lepbin].Fill( AODCaloJetMedianLog10IPSig               ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin][lepbin].Fill( AODCaloJetMedianLog10TrackAngle          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetTotalTrackAngle                [selbin][jetbin][lepbin].Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMinDR                          [selbin][jetbin][lepbin].Fill( aodcalojet_minDR_list                     .at( aodcalojetindex ), weight );  
      h_AODCaloJetAbsEta                         [selbin][jetbin][lepbin].Fill( fabs(AODCaloJetEta                       ->at( aodcalojetindex )), weight );
      h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin][lepbin].Fill( AODCaloJetPt->at(aodcalojetindex), fabs(AODCaloJetEta->at(aodcalojetindex)), weight );  
    }
  }
  
  return kTRUE;
} //end fill histograms


//----------------------------writeAODCaloJetHistograms
Bool_t analyzer_histograms::writeAODCaloJetBasicHistograms(int selbin, int lepbin, int jetbin)
{
  //printf("writeAODCaloJetHistograms\n");
  h_AODCaloJetPt                             [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetPtVar                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetEta                            [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetPhi                            [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAlphaMax                       [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAlphaMax2                      [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetBeta                           [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetBeta2                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetSumIP                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetSumIPSig                       [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetMedianIP                       [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetMedianLog10IPSig               [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetTrackAngle                     [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetLogTrackAngle                  [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetTotalTrackAngle                [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetMinDR                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAbsEta                         [selbin][jetbin][lepbin].Write();
  h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin][lepbin].Write(); 
 return kTRUE;
}


//----------------------------fillAODCaloJetExtraHistograms
Bool_t analyzer_histograms::fillAODCaloJetExtraHistograms(Double_t weight, int selbin, int lepbin, int jetbin)
{

  if(jetmultnames.at(jetbin) == "AllJets"){
    for(unsigned int i =0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i];
      h_AODCaloJetAvfVx                          [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVx                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVy                          [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVy                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVz                          [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVz                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTotalChiSquared       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDegreesOfFreedom      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexChi2NDoF              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDistanceToBeam        ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTransverseError       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTransverseSig         ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaEta              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaPhi              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexRecoilPt              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTrackMass             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTrackEnergy           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotDeltaPhi            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotRecoilPt            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotMedianDeltaPhi      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotLog10MedianDeltaPhi ->at( aodcalojetindex ), weight );  
      h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin][lepbin].Fill( AODCaloJetNCleanMatchedTracks            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin][lepbin].Fill( AODCaloJetSumHitsInFrontOfVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin][lepbin].Fill( AODCaloJetSumMissHitsAfterVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin][lepbin].Fill( AODCaloJetHitsInFrontOfVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin][lepbin].Fill( AODCaloJetMissHitsAfterVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfDistToPV                    [selbin][jetbin][lepbin].Fill( AODCaloJetAvfDistToPV                    ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV2           ->at( aodcalojetindex ), weight );  
    }
  }
  else{
    if( jetbin < (int)aodcalojet_list.size() ){
      int aodcalojetindex = aodcalojet_list[jetbin];
      h_AODCaloJetAvfVx                          [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVx                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVy                          [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVy                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVz                          [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVz                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTotalChiSquared       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDegreesOfFreedom      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexChi2NDoF              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDistanceToBeam        ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTransverseError       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTransverseSig         ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaEta              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaPhi              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexRecoilPt              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTrackMass             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexTrackEnergy           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotDeltaPhi            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotRecoilPt            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotMedianDeltaPhi      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin][lepbin].Fill( AODCaloJetAvfBeamSpotLog10MedianDeltaPhi ->at( aodcalojetindex ), weight );  
      h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin][lepbin].Fill( AODCaloJetNCleanMatchedTracks            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin][lepbin].Fill( AODCaloJetSumHitsInFrontOfVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin][lepbin].Fill( AODCaloJetSumMissHitsAfterVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin][lepbin].Fill( AODCaloJetHitsInFrontOfVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin][lepbin].Fill( AODCaloJetMissHitsAfterVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfDistToPV                    [selbin][jetbin][lepbin].Fill( AODCaloJetAvfDistToPV                    ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][jetbin][lepbin].Fill( AODCaloJetAvfVertexDeltaZtoPV2           ->at( aodcalojetindex ), weight );  
    }
  }

 return kTRUE;
} //end fill histograms


//----------------------------writeAODCaloJetHistograms
Bool_t analyzer_histograms::writeAODCaloJetExtraHistograms(int selbin, int lepbin, int jetbin)
{
 //printf("writeAODCaloJetHistograms\n");
  h_AODCaloJetAvfVx                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVy                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVz                          [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfDistToPV                    [selbin][jetbin][lepbin].Write(); 
  h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin][lepbin].Write(); 
  
  return kTRUE;
}


//----------------------------fillAODCaloJetTagHistograms
Bool_t analyzer_histograms::fillAODCaloJetTagHistograms(Double_t weight, int selbin, int lepbin, int tagbin)
{
  
  if(tagmultnames.at(tagbin) == "AllTags"){
    for(unsigned int i =0; i<taggedjet_list.size(); i++){
      int tagindex = taggedjet_list[i];
      h_AODCaloJetPt_Tag0   [selbin][tagbin][lepbin].Fill( AODCaloJetPt->at( tagindex ), weight );  
      h_AODCaloJetPtVar_Tag0[selbin][tagbin][lepbin].Fill( AODCaloJetPt->at( tagindex ), weight );  
      h_AODCaloJetMinDR_Tag0[selbin][tagbin][lepbin].Fill( aodcalojet_minDR_list.at( tagindex ), weight );  
      h_AODCaloJetAbsEta_Tag0[selbin][tagbin][lepbin].Fill( fabs(AODCaloJetEta->at( tagindex )), weight );
      h_AODCaloJetNCleanMatchedTracks_Tag0[selbin][tagbin][lepbin].Fill( AODCaloJetNCleanMatchedTracks->at( tagindex ), weight );  
      h_AODCaloJetPtVarAbsEtaVar_Tag0[selbin][tagbin][lepbin].Fill( AODCaloJetPt->at(tagindex), fabs(AODCaloJetEta->at( tagindex )), weight );  
    }
  }
  else {
    if( tagbin < (int)taggedjet_list.size() ){
      int tagindex = taggedjet_list[tagbin];
      h_AODCaloJetPt_Tag0   [selbin][tagbin][lepbin].Fill( AODCaloJetPt->at( tagindex ), weight );  
      h_AODCaloJetPtVar_Tag0[selbin][tagbin][lepbin].Fill( AODCaloJetPt->at( tagindex ), weight );  
      h_AODCaloJetMinDR_Tag0[selbin][tagbin][lepbin].Fill( aodcalojet_minDR_list.at( tagindex ), weight );  
      h_AODCaloJetAbsEta_Tag0[selbin][tagbin][lepbin].Fill( fabs( AODCaloJetEta->at( tagindex ) ), weight );
      h_AODCaloJetNCleanMatchedTracks_Tag0[selbin][tagbin][lepbin].Fill( AODCaloJetNCleanMatchedTracks->at( tagindex ), weight );  
      h_AODCaloJetPtVarAbsEtaVar_Tag0[selbin][tagbin][lepbin].Fill( AODCaloJetPt->at(tagindex), fabs(AODCaloJetEta->at( tagindex )), weight );  
    }
  }
  
  return kTRUE;
} //end fill histograms


//----------------------------writeAODCaloJetTagHistograms
Bool_t analyzer_histograms::writeAODCaloJetTagHistograms(int selbin, int lepbin, int tagbin)
{
  //printf("writeAODCaloJetTagHistograms\n");
  h_AODCaloJetPt_Tag0                       [selbin][tagbin][lepbin].Write(); 
  h_AODCaloJetPtVar_Tag0                    [selbin][tagbin][lepbin].Write(); 
  h_AODCaloJetMinDR_Tag0                    [selbin][tagbin][lepbin].Write(); 
  h_AODCaloJetAbsEta_Tag0                   [selbin][tagbin][lepbin].Write(); 
  h_AODCaloJetNCleanMatchedTracks_Tag0      [selbin][tagbin][lepbin].Write(); 
  h_AODCaloJetPtVarAbsEtaVar_Tag0           [selbin][tagbin][lepbin].Write(); 

 return kTRUE;
}


// Cutflow section

//----------------------------initCutflowHistograms
Bool_t analyzer_histograms::initCutflowHistograms(){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  for(unsigned int k=0; k<lepnames.size(); ++k){
   TString hname_Cutflow    = "h_"+lepnames[k]+"_"+selbinnames[i]+"_Cutflow"; 
   TString hname_Onecut     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_Onecut"; 
   TString hname_NMinus     = "h_"+lepnames[k]+"_"+selbinnames[i]+"_NMinus"; 
   TString hname_RawCutflow = "h_"+lepnames[k]+"_"+selbinnames[i]+"_RawCutflow"; 
   TString hname_RawOnecut  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_RawOnecut"; 
   TString hname_RawNMinus  = "h_"+lepnames[k]+"_"+selbinnames[i]+"_RawNMinus"; 

   h_Cutflow    [i][k] = initSingleHistogramTH1F( hname_Cutflow , "Cutflow", 10,0,10);
   h_Onecut     [i][k] = initSingleHistogramTH1F( hname_Onecut  , "Onecut ", 10,0,10);
   h_NMinus     [i][k] = initSingleHistogramTH1F( hname_NMinus  , "NMinus ", 10,0,10); 
   h_RawCutflow [i][k] = initSingleHistogramTH1F( hname_RawCutflow , "RawCutflow", 10,0,10);
   h_RawOnecut  [i][k] = initSingleHistogramTH1F( hname_RawOnecut  , "RawOnecut ", 10,0,10);
   h_RawNMinus  [i][k] = initSingleHistogramTH1F( hname_RawNMinus  , "RawNMinus ", 10,0,10); 
  }
 }
}

//----------------------------fillCutflowHistograms
Bool_t analyzer_histograms::fillCutflowHistograms(Double_t weight, int selbin, int lepbin, Int_t selint)
{
 
 h_Cutflow[selbin][lepbin] .Fill( 1, weight );
 h_Onecut[selbin][lepbin]  .Fill( 1, weight );
 h_NMinus[selbin][lepbin]  .Fill( 1, weight );
 h_RawCutflow[selbin][lepbin] .Fill( 1 );
 h_RawOnecut[selbin][lepbin]  .Fill( 1 );
 h_RawNMinus[selbin][lepbin]  .Fill( 1 );

 Bool_t notdead = kTRUE;
 Int_t nmbits = 0;

 // for now all selections are 5 long
 // selection integers (bitset) start with 1/0 if pass all cuts
 // then 1/0 for each individual cut
 for( unsigned int i=1; i<6; ++i){
  // ignore the first bit, then keep checking if we ever get 0
  notdead = notdead && ( selint>>(i) & 1 ) ;

  // bit i and all preceding bits it pass
  if( notdead ){
   h_Cutflow[selbin][lepbin]    .Fill( 1+i, weight );
   h_RawCutflow[selbin][lepbin] .Fill( 1+i );
  }
  // just bit i passes
  if( selint>>(i) & 1 ){
   h_Onecut[selbin][lepbin]    .Fill( 1+i, weight );
   h_RawOnecut[selbin][lepbin] .Fill( 1+i );
  }
  // everything other than bit i passes
   // bit structure is (passAll)(sel1)(sel2)(sel3)(sel4)(sel5)000
   // nmbits is 011111000 except flip bit i to 0
   // then AND this with selection bitset to get comparison bitset
   // then if comp bitset == nmbits we know
   // selection bitset passed all cuts, ignoring cut i
  nmbits = 0;
  nmbits |= 0 << 0;
  nmbits |= 1 << 1;
  nmbits |= 1 << 2;
  nmbits |= 1 << 3;
  nmbits |= 1 << 4;
  nmbits |= 1 << 5;
  nmbits &= ~(1 << i);
  Int_t compbits = selint & nmbits;

  //std::cout<<"\n";
  //std::cout<<" nmbits: "<<nmbits<<" =    "; 
  //for(unsigned int i=0; i<8; ++i){
  // std::cout<< ( (nmbits>>i)&1 );
  //}
  //std::cout<<"\n";
  //std::cout<<" selint: "<<selint<<" =    "; 
  //for(unsigned int i=0; i<8; ++i){
  // std::cout<< ( (selint>>i)&1 );
  //}
  //std::cout<<"\n";
  //std::cout<<" cmpbit: "<<compbits<<" =    "; 
  //for(unsigned int i=0; i<8; ++i){
  // std::cout<< ( (compbits>>i)&1 );
  //}
  //std::cout<<"\n";

  if( nmbits==compbits ){
   h_NMinus[selbin][lepbin]    .Fill( 1+i, weight );
   h_RawNMinus[selbin][lepbin] .Fill( 1+i );
  }

 }

 return kTRUE;
}

//----------------------------writeCutflowHistograms
Bool_t analyzer_histograms::writeCutflowHistograms(int selbin, int lepbin)
{
 h_Cutflow    [selbin][lepbin] .Write();
 h_Onecut     [selbin][lepbin] .Write();
 h_RawCutflow [selbin][lepbin] .Write();
 h_RawOnecut  [selbin][lepbin] .Write();
 h_NMinus     [selbin][lepbin] .Write();
 h_RawNMinus  [selbin][lepbin] .Write();
 return kTRUE;
}



//---------------------------scaleVariableBinHistograms
Bool_t analyzer_histograms::scaleVariableBinHistograms(int selbin, int lepbin)
{

  for(unsigned int j=0; j<jetmultnames.size(); ++j){
    h_AODCaloJetPtVar                      [selbin][j][lepbin].Scale(1, "width");
  }
  for(unsigned int j=0; j<tagmultnames.size(); ++j){
    h_AODCaloJetPtVar_Tag0                 [selbin][j][lepbin].Scale(1, "width");
  }
  
  return kTRUE;
}


//----------------------------initAODCaloJetMultHistograms
Bool_t analyzer_histograms::initAODCaloJetMultHistograms()
{
  for(unsigned int i=0; i<selbinnames.size(); ++i){
    for(unsigned int k=0; k<lepnames.size(); ++k){

      TString hname_nSelectedAODCaloJet             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedAODCaloJet";
      h_nSelectedAODCaloJet                  [i][k] = initSingleHistogramTH1F( hname_nSelectedAODCaloJet         , "nSelectedAODCaloJet"      , 6, -0.5, 5.5);

    }//lep                                                                                                                                                                              
  }//sel                                                                                                                                                                                
}

//----------------------------fillAODCaloJetMultHistograms
Bool_t analyzer_histograms::fillAODCaloJetMultHistograms(Double_t weight, int selbin, int lepbin)
{
  h_nSelectedAODCaloJet    [selbin][lepbin] .Fill( float(aodcalojet_list.size()), weight );
}

//----------------------------writeAODCaloJetMultHistograms
Bool_t analyzer_histograms::writeAODCaloJetMultHistograms(int selbin, int lepbin)
{
  h_nSelectedAODCaloJet    [selbin][lepbin] .Write();
}


//----------------------------initAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::initAODCaloJetTagMultHistograms()
{
  for(unsigned int i=0; i<selbinnames.size(); ++i){
    for(unsigned int k=0; k<lepnames.size(); ++k){

      TString hname_nSelectedAODCaloJetTag             = "h_"+lepnames[k]+"_"+selbinnames[i]+"_nSelectedAODCaloJetTag";
      h_nSelectedAODCaloJetTag                  [i][k] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTag         , "nSelectedAODCaloJetTag"      , 6, -0.5, 5.5);

    }//lep                                                                                                                                                                              
  }//sel                                                                                                                                                                                
}

//----------------------------fillAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::fillAODCaloJetTagMultHistograms(Double_t weight, int selbin, int lepbin)
{
  h_nSelectedAODCaloJetTag    [selbin][lepbin] .Fill( float(taggedjet_list.size()), weight );
}

//----------------------------writeAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::writeAODCaloJetTagMultHistograms(int selbin, int lepbin)
{
  h_nSelectedAODCaloJetTag    [selbin][lepbin] .Write();
}







////////////////////////////
// Background estimate
////////////////////////////

int analyzer_histograms::getMistagRateBin(int j, TString mistag_name){
  
  int bin = 0;
  
  if(mistag_name == "PT"){
    bin = h_MistagRate_pt->FindBin( AODCaloJetPt->at( aodcalojet_list[j] ) );
  }
  if(mistag_name == "PT-ETA"){
    bin = h_MistagRate_pteta->FindBin( AODCaloJetPt ->at( aodcalojet_list[j] ),  fabs(AODCaloJetEta->at( aodcalojet_list[j] )));
  }
  
  //std::cout << "      getMistagRateBin: " << j << " " << bin << std::endl;
  return bin;
}


float analyzer_histograms::getMistagRateByBin(int j, TString mistag_name){
  
  float jetprob = 0;
  
  if(mistag_name == "PT"){
    jetprob = h_MistagRate_pt->GetBinContent( j );
  }
  if(mistag_name == "PT-ETA"){
    jetprob = h_MistagRate_pteta->GetBinContent( j );
  }
  
  //std::cout << "      getMistagRateByBin: " << j << " " << jetprob << std::endl;
  return jetprob;
}


float analyzer_histograms::getMistagRate(int j, TString mistag_name){
  
  float jetprob = 0;
  
  if(mistag_name == "PT"){
    jetprob = h_MistagRate_pt->GetBinContent( h_MistagRate_pt->FindBin( AODCaloJetPt->at( aodcalojet_list[j] ) ) );
  }
  if(mistag_name == "PT-ETA"){
    jetprob = h_MistagRate_pteta->GetBinContent( h_MistagRate_pteta->FindBin( AODCaloJetPt ->at( aodcalojet_list[j] ),  fabs(AODCaloJetEta->at( aodcalojet_list[j] ))) );
  }
  
  //std::cout << "      getMistagRate: " << j << " " << jetprob << std::endl;
  return jetprob;
}


float analyzer_histograms::computeTerm(int b, std::vector<int> mistagBins_tagged, std::vector<int> mistagBins_untagged, TString mistag_name){

  float full_probability=1;
  float partial_probability=1;
  int n_t=0, n_ut=0;
  for(int t=0; t<mistagBins_tagged.size(); t++){
    float jetprob = getMistagRateByBin( mistagBins_tagged.at(t), mistag_name);
    //std::cout << "JETPROB: " << mistagBins_tagged.at(t) << " " <<  jetprob << std::endl;
    full_probability *= jetprob;
    if(mistagBins_tagged.at(t)==b){
      n_t++;
    }
    else{
      partial_probability *= jetprob;
    }
  }
  for(int t=0; t<mistagBins_untagged.size(); t++){
    float jetprob = getMistagRateByBin( mistagBins_untagged.at(t), mistag_name);
    //std::cout << "JETPROB: " << mistagBins_untagged.at(t) << " " <<  jetprob << std::endl;
    full_probability *= (1-jetprob);
    if(mistagBins_untagged.at(t)==b){
      n_ut++;
    }
    else{
      partial_probability *= (1-jetprob);
    }
  }
  
  //Uncertainty term from this mistag rate bin
  float float_n_t = (float) n_t;
  float float_n_ut = (float) n_ut;
  float this_prob = getMistagRateByBin(b, mistag_name);
  
  float term  = partial_probability;
  if(n_t==0 && n_ut>0){
    term *= -float_n_ut*TMath::Power(1-this_prob, n_ut-1);
  }
  else if(n_t>0 && n_ut==0){
    term *= float_n_t*TMath::Power(this_prob, n_t-1);
  }
  else if (n_t==0 && n_ut==0){
    term = 0;
  }
  else{
    term *= (float_n_t*TMath::Power(this_prob, n_t-1) -float_n_ut*TMath::Power(1-this_prob, n_ut-1)) ;
  }
  
  return term;
}


//https://helloacm.com/cc-coding-exercise-recursive-combination-algorithm-implementation/
void analyzer_histograms::comb(int n, int r, int *arr, int sz, Double_t weight, TString mistag_name) {

  for (int i = n; i >= r; i --) {

    // choose the first elemente
    arr[r - 1] = i;
    if (r > 1) { // if still needs to choose
      // recursive into smaller problem
      comb(i - 1, r - 1, arr, sz, weight, mistag_name);
    }
    else {

      //*********************//
      // have one combo here 
      //*********************//
      bool debug=false;

      if(debug){
	std::cout << "    " << mistag_name << std::endl;
	std::cout << "    Combo: ";
        for (int b = 0; b < sz; b++) {
	  std::cout << arr[b] << " ";
        }
	std::cout << std::endl;
      }

      std::vector<int> mistagBins_tagged, mistagBins_untagged;
      
      double p=1;
      for(int j=1; j<=aodcalojet_list.size(); j++){
	
	//Get mistag rate
        //j-1 because index from 1
	int mistagBin = getMistagRateBin( j-1, mistag_name);
	float jetprob = getMistagRate   ( j-1, mistag_name);
        if(debug) std::cout << "      Prob: " << jetprob << std::endl;
	
	//Check if this is a "tagged" jet in this combo
        bool found = false;
        for(int t=0; t<sz; t++){
          if(j==arr[t]){
            p*=jetprob;
	    mistagBins_tagged.push_back(mistagBin);
            found = true;
            if(debug) std::cout << "      Tagged jet: " << j << std::endl;
            break;
          }
        }
	
	//If not tagged
        if(!found){
          p*=(1-jetprob);
	  mistagBins_untagged.push_back(mistagBin);
          if(debug) std::cout << "      Didn't tag jet: " << j << std::endl;
        }
        if(debug) std::cout << "      Updated prob: " << p << std::endl;
      }//loop over jets
      
      
      //Uncertainy
      if(mistag_name == "PT"){
	for(int b=0; b<=h_MistagRate_pt->GetNbinsX()+1; b++){//include underflow/overflow
	  
	  float term;
	  term = computeTerm(b, mistagBins_tagged, mistagBins_untagged, mistag_name);

	  //this is the derivative part.  leave multiplication by error in bin b for later.
	  h_MistagRate_pt_sys.at(sz)->Fill(h_MistagRate_pt_sys.at(sz)->GetBinCenter(b), weight*term);
	  
	  //std::cout << "b: " << b << ", term: " << term << std::endl;

	}//end bin
      }
      else if(mistag_name == "PT-ETA"){
	for(int b=0; b<h_MistagRate_pteta->GetSize(); b++){
	  
	  //if(h_MistagRate_pteta->IsBinUnderflow(b) || h_MistagRate_pteta->IsBinOverflow(b)) continue;
	  //include underflow and overflow

	  float term;
	  term = computeTerm(b, mistagBins_tagged, mistagBins_untagged, mistag_name);
	  //this is the derivative part.  leave multiplication by error in bin b for later.
	  
	  //Get bin location
	  int xbin, ybin, zbin;
	  h_MistagRate_pteta->GetBinXYZ(b, xbin, ybin, zbin);

	  float x, y;
	  x = h_MistagRate_pteta->GetXaxis()->GetBinCenter(xbin);
	  y = h_MistagRate_pteta->GetYaxis()->GetBinCenter(ybin);

	  std::cout << "b: " << b << ", xbin: " << xbin << ", ybin: " << ybin << ", term: " << term << std::endl;

	  h_MistagRate_pteta_sys.at(sz)->Fill(x, y, weight*term);
	  
	}//b
      }

      //Fill estimate from p already calculated 
      if(mistag_name == "PT"){
	h_bkgest_pt.Fill(sz,p*weight);
      }
      else if(mistag_name == "PT-ETA"){
	h_bkgest_pteta.Fill(sz,p*weight);
      }

    }//end of this combo
  }//outer for loop
}


Bool_t analyzer_histograms::initBackgroundEstimateHistograms()
{
  h_bkgest_pt.Clear();
  h_bkgest_pteta.Clear();

  h_bkgest_pt = initSingleHistogramTH1F("h_bkgest_pt", "h_bkgest_pt", 6, -.5, 5.5);
  h_bkgest_pteta = initSingleHistogramTH1F("h_bkgest_pteta", "h_bkgest_pteta", 6, -.5, 5.5);

  return kTRUE;
}


Bool_t analyzer_histograms::fillBackgroundEstimateHistograms(Double_t weight)
{
  bool debug=false;

  //number of jets
  const int N = aodcalojet_list.size();
  if(debug) std::cout << "NJets: " << aodcalojet_list.size() << std::endl;

  //loop over tag multiplicity
  for(int i=1; i<6; i++){
    if(N<i) continue; //code is safe anyway, but thist migh save time
    if(debug) std::cout << "  NTags: " << i << std::endl;
    const int M = i;
    int *arr = new int[M];
    comb(N, M, arr, M, weight, "PT");
    comb(N, M, arr, M, weight, "PT-ETA");
  }
  
  return kTRUE;
}


Bool_t analyzer_histograms::writeBackgroundEstimateHistograms(TFile* outfile)
{
  outfile->cd();

  h_bkgest_pt.Write();
  h_bkgest_pteta.Write();

  for(int i=0; i<6; i++){
    h_MistagRate_pt_sys.at(i)->Write();
    h_MistagRate_pteta_sys.at(i)->Write();
  }

  return kTRUE;
}


