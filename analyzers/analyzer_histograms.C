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




//----------------------------fillSelectedHistograms
Bool_t analyzer_histograms::fillSelectedHistograms(Float_t weight, int selbin)
{
 /// Decide here which histograms to get filled
 fillEleHistograms               ( weight, selbin );
 fillMuHistograms                ( weight, selbin );
 fillLepHistograms               ( weight, selbin );
 fillPhoHistograms               ( weight, selbin );
 fillMETHTHistograms             ( weight, selbin );
 fillAODCaloJetMultHistograms    ( weight, selbin );
 fillAODCaloJetTagMultHistograms ( weight, selbin );
 if(TTOC) fillTTOCHistograms     ( weight, selbin );
 fillExtraHistograms             ( weight, selbin );
}

//----------------------------writeSelectedHistograms
Bool_t analyzer_histograms::writeSelectedHistograms(int selbin)
{
 /// Decide here which histograms to get written
 writeEleHistograms               ( selbin );
 writeMuHistograms                ( selbin );
 writeLepHistograms               ( selbin );
 writePhoHistograms               ( selbin );
 writeMETHTHistograms             ( selbin );
 writeAODCaloJetMultHistograms    ( selbin );
 writeAODCaloJetTagMultHistograms ( selbin );
 if(TTOC) writeTTOCHistograms     ( selbin );
 writeExtraHistograms             ( selbin );
}

//----------------------------fillSelectedJetHistograms
Bool_t analyzer_histograms::fillSelectedJetHistograms(Float_t weight, int selbin, int jetbin )
{
 /// Decide here which jet histograms to get filled
  fillAODCaloJetBasicHistograms( weight, selbin, jetbin );
  fillAODCaloJetStudyHistograms( weight, selbin, jetbin );
  fillAODCaloJet_L1PFHistograms( weight, selbin, jetbin );
  fillAODCaloJetExtraHistograms( weight, selbin, jetbin );
}

//----------------------------writeSelectedJetHistograms
Bool_t analyzer_histograms::writeSelectedJetHistograms(int selbin, int jetbin)
{
 /// Decide here which jet histograms to get written
  writeAODCaloJetBasicHistograms( selbin, jetbin );
  writeAODCaloJetStudyHistograms( selbin, jetbin );
  writeAODCaloJet_L1PFHistograms( selbin, jetbin );
  writeAODCaloJetExtraHistograms( selbin, jetbin );
}

//----------------------------fillSelectedTagHistograms
Bool_t analyzer_histograms::fillSelectedTagHistograms(Float_t weight, int selbin, int tagbin )
{
 /// Decide here which tag histograms to get filled
  fillAODCaloJetTagHistograms( weight, selbin, tagbin );
}

//----------------------------writeSelectedTagHistograms
Bool_t analyzer_histograms::writeSelectedTagHistograms(int selbin, int tagbin)
{
 /// Decide here which tag histograms to get written
  writeAODCaloJetTagHistograms( selbin, tagbin );
}


//----------------------------initSingleHistogramTH1F
TH1F* analyzer_histograms::initSingleHistogramTH1F(TString hname, TString htitle, Int_t nbins, Float_t xmin, Float_t xmax)
{

 TH1F* histoTH1F = new TH1F( hname , htitle , nbins , xmin , xmax );
 histoTH1F->Sumw2();

 return histoTH1F;

}

//Overload for variable binning
TH1F* analyzer_histograms::initSingleHistogramTH1F(TString hname, TString htitle, int nbins, Float_t xbins[])
{

  TH1F* histoTH1F = new TH1F( hname , htitle , nbins , xbins );
  histoTH1F->Sumw2();

  return histoTH1F;

}



//----------------------------initSingleHistogramTH2F
TH2F* analyzer_histograms::initSingleHistogramTH2F(TString hname, TString htitle,
                                   Int_t nbinsx, Float_t xmin, Float_t xmax,
                                   Int_t nbinsy, Float_t ymin, Float_t ymax)
{

 TH2F* histoTH2F = new TH2F( hname , htitle , nbinsx , xmin , xmax  , nbinsy , ymin , ymax );
 histoTH2F->Sumw2();

 return histoTH2F;

}


TH2F* analyzer_histograms::initSingleHistogramTH2F(TString hname, TString htitle,
						  int nbinsx, Float_t xbins[],
						  int nbinsy, Float_t ybins[])
{

 TH2F* histoTH2F = new TH2F( hname , htitle , nbinsx , xbins , nbinsy , ybins );
 histoTH2F->Sumw2();

 return histoTH2F;

}

//----------------------------init2DHistograms
Bool_t analyzer_histograms::init2DHistograms( TString uncbin )
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
Bool_t analyzer_histograms::fill2DHistograms(Float_t weight, int selbin)
{
  // //printf("fill2DHistograms\n");
  //
  //  if( NGOODVERTICES->size()>0 && JetNJets->size()>0 ) 
  //   { h_nvertnjets[selbin]->Fill( NGOODVERTICES->at(0), JetNJets->at(0), weight ); }
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
Bool_t analyzer_histograms::initEleHistograms( TString uncbin ){
 for(unsigned int i=0; i<selbinnames.size(); ++i){
   hist_file_out[i]->cd();
   //deleteEleHistograms(i);
   
   TString hname_AOD_nEle                    = "h_"+selbinnames[i]+"_AOD_nEle"        +uncbin; 
   TString hname_AOD_nSelectedEle            = "h_"+selbinnames[i]+"_AOD_nSelectedEle"+uncbin;
   TString hname_AOD_elePt                   = "h_"+selbinnames[i]+"_AOD_elePt"       +uncbin; 
   TString hname_AOD_eleEn                   = "h_"+selbinnames[i]+"_AOD_eleEn"       +uncbin; 
   TString hname_AOD_eleEta                  = "h_"+selbinnames[i]+"_AOD_eleEta"      +uncbin; 
   TString hname_AOD_elePhi                  = "h_"+selbinnames[i]+"_AOD_elePhi"      +uncbin; 
   TString hname_AOD_eleCharge               = "h_"+selbinnames[i]+"_AOD_eleCharge"   +uncbin; 
   
   h_AOD_nEle                     [i]= initSingleHistogramTH1F( hname_AOD_nEle                    , "AOD_nEle                   ", 6,  0, 6) ;  
   h_AOD_nSelectedEle             [i]= initSingleHistogramTH1F( hname_AOD_nSelectedEle            , "AOD_nSelectedEle           ", 10,0,10);
   h_AOD_elePt                    [i]= initSingleHistogramTH1F( hname_AOD_elePt                   , "AOD_elePt                  ", 50, 0, 500) ;  
   h_AOD_eleEn                    [i]= initSingleHistogramTH1F( hname_AOD_eleEn                   , "AOD_eleEn                  ", 50, 0, 500) ;  
   h_AOD_eleEta                   [i]= initSingleHistogramTH1F( hname_AOD_eleEta                  , "AOD_eleEta                 ", 30, -5, 5); 
   h_AOD_elePhi                   [i]= initSingleHistogramTH1F( hname_AOD_elePhi                  , "AOD_elePhi                 ", 30, -5, 5); 
   h_AOD_eleCharge                [i]= initSingleHistogramTH1F( hname_AOD_eleCharge               , "AOD_eleCharge              ", 3, -1, 1); 
 }

 return kTRUE;
}

//----------------------------fillEleHistograms
Bool_t analyzer_histograms::fillEleHistograms(Float_t weight, int selbin )
{
  hist_file_out[selbin]->cd();

  h_AOD_nEle            [selbin] ->Fill( float(nAODEle), weight );
  h_AOD_nSelectedEle    [selbin] ->Fill( float(electron_list.size()), weight );

  // fill leading electron in vector
  if(electron_list.size() > 0){
   int eleindex = electron_list[0];
   h_AOD_elePt               [selbin] ->Fill( Shifted_elePt            .at(eleindex), weight );  
   h_AOD_eleEn               [selbin] ->Fill( AOD_eleEn               ->at(eleindex), weight );  
   h_AOD_eleEta              [selbin] ->Fill( AOD_eleEta              ->at(eleindex), weight );  
   h_AOD_elePhi              [selbin] ->Fill( AOD_elePhi              ->at(eleindex), weight );  
   h_AOD_eleCharge           [selbin] ->Fill( AOD_eleCharge           ->at(eleindex), weight );  
  }
 return kTRUE;
}

//----------------------------writeEleHistograms
Bool_t analyzer_histograms::writeEleHistograms(int selbin)
{
  hist_file_out[selbin]->cd();
  
  h_AOD_nEle            [selbin] ->Write();
  h_AOD_nSelectedEle    [selbin] ->Write();
  h_AOD_elePt           [selbin] ->Write();
  h_AOD_eleEn           [selbin] ->Write();
  h_AOD_eleEta          [selbin] ->Write();
  h_AOD_elePhi          [selbin] ->Write();
  h_AOD_eleCharge       [selbin] ->Write();
  return kTRUE;
}

//----------------------------deleteEleHistograms
Bool_t analyzer_histograms::deleteEleHistograms(int selbin)
{
  //printf("deleteEleHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_AOD_nEle[selbin]!=NULL)            h_AOD_nEle            [selbin] ->Delete();
  if(h_AOD_nSelectedEle[selbin]!=NULL)    h_AOD_nSelectedEle    [selbin] ->Delete();
  if(h_AOD_elePt[selbin]!=NULL)           h_AOD_elePt           [selbin] ->Delete();
  if(h_AOD_eleEn[selbin]!=NULL)           h_AOD_eleEn           [selbin] ->Delete();
  if(h_AOD_eleEta[selbin]!=NULL)          h_AOD_eleEta          [selbin] ->Delete();
  if(h_AOD_elePhi[selbin]!=NULL)          h_AOD_elePhi          [selbin] ->Delete();
  if(h_AOD_eleCharge[selbin]!=NULL)       h_AOD_eleCharge       [selbin] ->Delete();
 return kTRUE;
}


//----------------------------initMuHistograms
Bool_t analyzer_histograms::initMuHistograms( TString uncbin ){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  hist_file_out[i]->cd();
  //deleteMuHistograms(i);
  TString hname_AOD_nMu                     = "h_"+selbinnames[i]+"_AOD_nMu"                +uncbin; 
  TString hname_AOD_nSelectedMu             = "h_"+selbinnames[i]+"_AOD_nSelectedMu"        +uncbin;
  TString hname_AOD_muPt                    = "h_"+selbinnames[i]+"_AOD_muPt"               +uncbin; 
  TString hname_AOD_muEn                    = "h_"+selbinnames[i]+"_AOD_muEn"               +uncbin; 
  TString hname_AOD_muEta                   = "h_"+selbinnames[i]+"_AOD_muEta"              +uncbin; 
  TString hname_AOD_muPhi                   = "h_"+selbinnames[i]+"_AOD_muPhi"              +uncbin; 
  TString hname_AOD_muCharge                = "h_"+selbinnames[i]+"_AOD_muCharge"           +uncbin; 
  TString hname_AOD_muPFdBetaIsolation      = "h_"+selbinnames[i]+"_AOD_muPFdBetaIsolation" +uncbin; 

  h_AOD_nMu                      [i] = initSingleHistogramTH1F( hname_AOD_nMu                     , "AOD_nMu                    ", 6,  0, 6) ;  
  h_AOD_nSelectedMu              [i] = initSingleHistogramTH1F( hname_AOD_nSelectedMu             , "AOD_nSelectedMu            ", 10,0,10);
  h_AOD_muPt                     [i] = initSingleHistogramTH1F( hname_AOD_muPt                    , "AOD_muPt                   ", 50, 0, 500) ;  
  h_AOD_muEn                     [i] = initSingleHistogramTH1F( hname_AOD_muEn                    , "AOD_muEn                   ", 50, 0, 500) ;  
  h_AOD_muEta                    [i] = initSingleHistogramTH1F( hname_AOD_muEta                   , "AOD_muEta                  ", 30, -5, 5); 
  h_AOD_muPhi                    [i] = initSingleHistogramTH1F( hname_AOD_muPhi                   , "AOD_muPhi                  ", 30, -5, 5); 
  h_AOD_muCharge                 [i] = initSingleHistogramTH1F( hname_AOD_muCharge                , "AOD_muCharge               ", 3, -1, 1); 
  h_AOD_muPFdBetaIsolation       [i] = initSingleHistogramTH1F( hname_AOD_muPFdBetaIsolation      , "AOD_muPFdBetaIsolation     ", 30, -5, 5); 
 }
 return kTRUE;
}

//----------------------------fillMuHistograms
Bool_t analyzer_histograms::fillMuHistograms(Float_t weight, int selbin)
{
  hist_file_out[selbin]->cd();
  h_AOD_nMu            [selbin] ->Fill( float(nAODMu), weight );
  h_AOD_nSelectedMu    [selbin] ->Fill( float(muon_list.size()), weight );
  // fill leading muon in vector
  if(muon_list.size() > 0){
   int muindex = muon_list[0];
   h_AOD_muPt               [selbin]->Fill( Shifted_muPt            .at(muindex), weight );  
   h_AOD_muEn               [selbin]->Fill( AOD_muEn               ->at(muindex), weight );  
   h_AOD_muEta              [selbin]->Fill( AOD_muEta              ->at(muindex), weight );  
   h_AOD_muPhi              [selbin]->Fill( AOD_muPhi              ->at(muindex), weight );  
   h_AOD_muCharge           [selbin]->Fill( AOD_muCharge           ->at(muindex), weight );  
   h_AOD_muPFdBetaIsolation [selbin]->Fill( AOD_muPFdBetaIsolation ->at(muindex), weight );  
  }
 return kTRUE;
}

//----------------------------writeMuHistograms
Bool_t analyzer_histograms::writeMuHistograms(int selbin)
{
  hist_file_out[selbin]->cd();
 h_AOD_nMu                     [selbin]->Write();
 h_AOD_nSelectedMu             [selbin]->Write();
 h_AOD_muPt                    [selbin]->Write();
 h_AOD_muEn                    [selbin]->Write();
 h_AOD_muEta                   [selbin]->Write();
 h_AOD_muPhi                   [selbin]->Write(); 
 h_AOD_muCharge                [selbin]->Write(); 
 h_AOD_muPFdBetaIsolation      [selbin]->Write(); 
 return kTRUE;
}

//----------------------------deleteMuHistograms
Bool_t analyzer_histograms::deleteMuHistograms(int selbin)
{
  //printf("deleteMuHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_AOD_nMu[selbin]!=NULL)                 h_AOD_nMu                     [selbin]->Delete();
  if(h_AOD_nSelectedMu[selbin]!=NULL)         h_AOD_nSelectedMu             [selbin]->Delete();
  if(h_AOD_muPt[selbin]!=NULL)                h_AOD_muPt                    [selbin]->Delete();
  if(h_AOD_muEn[selbin]!=NULL)                h_AOD_muEn                    [selbin]->Delete();
  if(h_AOD_muEta[selbin]!=NULL)               h_AOD_muEta                   [selbin]->Delete();
  if(h_AOD_muPhi[selbin]!=NULL)               h_AOD_muPhi                   [selbin]->Delete(); 
  if(h_AOD_muCharge[selbin]!=NULL)            h_AOD_muCharge                [selbin]->Delete(); 
  if(h_AOD_muPFdBetaIsolation[selbin]!=NULL)  h_AOD_muPFdBetaIsolation      [selbin]->Delete(); 
  return kTRUE;
}


//----------------------------initLepHistograms
Bool_t analyzer_histograms::initLepHistograms( TString uncbin ){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  hist_file_out[i]->cd();
  //deleteLepHistograms(i);
  TString hname_AOD_dilepton_Mass = "h_"+selbinnames[i]+"_AOD_dilepton_Mass"+uncbin; 
  TString hname_AOD_dilepton_Pt   = "h_"+selbinnames[i]+"_AOD_dilepton_Pt"  +uncbin; 
  TString hname_AOD_OSOFdilepton_Mass = "h_"+selbinnames[i]+"_AOD_OSOFdilepton_Mass"+uncbin; 
  TString hname_AOD_OSOFdilepton_Pt   = "h_"+selbinnames[i]+"_AOD_OSOFdilepton_Pt"  +uncbin; 

  h_AOD_dilepton_Mass[i] = initSingleHistogramTH1F( hname_AOD_dilepton_Mass, "AOD_dilepton_Mass", 30,  60, 120) ;  
  h_AOD_dilepton_Pt  [i] = initSingleHistogramTH1F( hname_AOD_dilepton_Pt  , "AOD_dilepton_Pt  ", 50,   0, 500) ;  
  h_AOD_OSOFdilepton_Mass[i] = initSingleHistogramTH1F( hname_AOD_OSOFdilepton_Mass, "AOD_OSOFdilepton_Mass", 30,  60, 120) ;  
  h_AOD_OSOFdilepton_Pt  [i] = initSingleHistogramTH1F( hname_AOD_OSOFdilepton_Pt  , "AOD_OSOFdilepton_Pt  ", 50,   0, 500) ;  
 }
 return kTRUE;
}

//----------------------------fillLepHistograms
Bool_t analyzer_histograms::fillLepHistograms(Float_t weight, int selbin )
{
  hist_file_out[selbin]->cd();
  h_AOD_dilepton_Mass  [selbin]->Fill( dilep_mass, weight );
  h_AOD_dilepton_Pt    [selbin]->Fill( dilep_pt, weight );
  h_AOD_OSOFdilepton_Mass  [selbin]->Fill( OSOF_mass, weight );
  h_AOD_OSOFdilepton_Pt    [selbin]->Fill( OSOF_pt, weight );
  return kTRUE;
}

//----------------------------writeLepHistograms
Bool_t analyzer_histograms::writeLepHistograms(int selbin)
{
  hist_file_out[selbin]->cd();
 h_AOD_dilepton_Mass           [selbin]->Write();
 h_AOD_dilepton_Pt             [selbin]->Write();
 h_AOD_OSOFdilepton_Mass       [selbin]->Write();
 h_AOD_OSOFdilepton_Pt         [selbin]->Write();
 return kTRUE;
}

//----------------------------deleteLepHistograms
Bool_t analyzer_histograms::deleteLepHistograms(int selbin)
{
  //printf("deleteLepHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_AOD_dilepton_Mass    [selbin]!=NULL)   h_AOD_dilepton_Mass           [selbin]->Delete();
  if(h_AOD_dilepton_Pt      [selbin]!=NULL)   h_AOD_dilepton_Pt             [selbin]->Delete();
  if(h_AOD_OSOFdilepton_Mass[selbin]!=NULL)   h_AOD_OSOFdilepton_Mass       [selbin]->Delete();
  if(h_AOD_OSOFdilepton_Pt  [selbin]!=NULL)   h_AOD_OSOFdilepton_Pt         [selbin]->Delete();  
  return kTRUE;
}


//----------------------------initPhoHistograms
Bool_t analyzer_histograms::initPhoHistograms( TString uncbin ){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
  hist_file_out[i]->cd();
  //deletePhoHistograms(i);
  TString hname_AOD_nPho                     = "h_"+selbinnames[i]+"_AOD_nPho"        +uncbin;
  TString hname_AOD_nSelectedPho             = "h_"+selbinnames[i]+"_AOD_nSelectedPho"+uncbin;
  TString hname_AOD_phoEn                    = "h_"+selbinnames[i]+"_AOD_phoEn"       +uncbin; 
  TString hname_AOD_phoPt                    = "h_"+selbinnames[i]+"_AOD_phoPt"       +uncbin; 
  TString hname_AOD_phoEta                   = "h_"+selbinnames[i]+"_AOD_phoEta"      +uncbin; 
  TString hname_AOD_phoPhi                   = "h_"+selbinnames[i]+"_AOD_phoPhi"      +uncbin; 

  h_AOD_nPho         [i] = initSingleHistogramTH1F( hname_AOD_nPho                    , "AOD_nPho        ", 6,  0, 6) ;  
  h_AOD_nSelectedPho [i] = initSingleHistogramTH1F( hname_AOD_nSelectedPho            , "AOD_nSelectedPho", 10,0,10);
  h_AOD_phoEn        [i] = initSingleHistogramTH1F( hname_AOD_phoEn                   , "AOD_phoEn       ", 50, 0, 500) ;  
  h_AOD_phoPt        [i] = initSingleHistogramTH1F( hname_AOD_phoPt                   , "AOD_phoPt       ", 50, 0, 500) ;  
  h_AOD_phoEta       [i] = initSingleHistogramTH1F( hname_AOD_phoEta                  , "AOD_phoEta      ", 30, -5, 5); 
  h_AOD_phoPhi       [i] = initSingleHistogramTH1F( hname_AOD_phoPhi                  , "AOD_phoPhi      ", 30, -5, 5); 
 }
 return kTRUE;
}

//----------------------------fillPhoHistograms
Bool_t analyzer_histograms::fillPhoHistograms(Float_t weight, int selbin)
{
  hist_file_out[selbin]->cd();
 // fill leading photon in vector
  h_AOD_nPho              [selbin]->Fill( float(nAODPho), weight );
  h_AOD_nSelectedPho      [selbin]->Fill( float(photon_list.size()), weight );
  if(photon_list.size() > 0){
   int phoindex = photon_list[0];
   h_AOD_phoEn    [selbin]->Fill( AOD_phoEn   ->at(phoindex), weight );  
   //h_AOD_phoPt    [selbin]->Fill( AOD_phoPt   ->at(phoindex), weight );  
   h_AOD_phoPt    [selbin]->Fill( Shifted_phoPt.at(phoindex), weight );  
   h_AOD_phoEta   [selbin]->Fill( AOD_phoEta  ->at(phoindex), weight );  
   h_AOD_phoPhi   [selbin]->Fill( AOD_phoPhi  ->at(phoindex), weight );  
  }
 return kTRUE;
}

//----------------------------writePhoHistograms
Bool_t analyzer_histograms::writePhoHistograms(int selbin)
{
  hist_file_out[selbin]->cd();
 h_AOD_nPho              [selbin]->Write();
 h_AOD_nSelectedPho      [selbin]->Write();
 h_AOD_phoEn             [selbin]->Write(); 
 h_AOD_phoPt             [selbin]->Write(); 
 h_AOD_phoEta            [selbin]->Write(); 
 h_AOD_phoPhi            [selbin]->Write(); 
 return kTRUE;
}

//----------------------------deletePhoHistograms
Bool_t analyzer_histograms::deletePhoHistograms(int selbin)
{
  //printf("deletePhoHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_AOD_nPho        [selbin]!=NULL)  h_AOD_nPho              [selbin]->Delete();
  if(h_AOD_nSelectedPho[selbin]!=NULL)  h_AOD_nSelectedPho      [selbin]->Delete();
  if(h_AOD_phoEn       [selbin]!=NULL)  h_AOD_phoEn             [selbin]->Delete(); 
  if(h_AOD_phoPt       [selbin]!=NULL)  h_AOD_phoPt             [selbin]->Delete(); 
  if(h_AOD_phoEta      [selbin]!=NULL)  h_AOD_phoEta            [selbin]->Delete(); 
  if(h_AOD_phoPhi      [selbin]!=NULL)  h_AOD_phoPhi            [selbin]->Delete(); 
  return kTRUE;
}

//----------------------------initMETHTHistograms
Bool_t analyzer_histograms::initMETHTHistograms( TString uncbin ){
  
  for(unsigned int i=0; i<selbinnames.size(); ++i){
    hist_file_out[i]->cd();
    //deleteMETHTHistograms(i);
    TString hname_AOD_MET_phi                 = "h_"+selbinnames[i]+"_AOD_MET_phi"  +uncbin ; 
    TString hname_AOD_MET_pt                  = "h_"+selbinnames[i]+"_AOD_MET_pt"   +uncbin ; 
    TString hname_htall                       = "h_"+selbinnames[i]+"_htall"        +uncbin ;
    TString hname_htaodcalojets               = "h_"+selbinnames[i]+"_htaodcalojets"+uncbin ;
    
    h_AOD_MET_phi    [i] = initSingleHistogramTH1F( hname_AOD_MET_phi   , "AOD_MET_phi  " , 30, -5, 5); 
    h_AOD_MET_pt     [i] = initSingleHistogramTH1F( hname_AOD_MET_pt    , "AOD_MET_pt   " , 50, 0, 100); 
    h_htall          [i] = initSingleHistogramTH1F( hname_htall         , "htall        " , 50,0,1000) ; 
    h_htaodcalojets  [i] = initSingleHistogramTH1F( hname_htaodcalojets , "htaodcalojets" , 50,0,1000) ; 
  }
  
  return kTRUE;
}

//----------------------------fillMETHTHistograms
Bool_t analyzer_histograms::fillMETHTHistograms(Float_t weight, int selbin)
{
  hist_file_out[selbin]->cd();
 h_AOD_MET_phi             [selbin]->Fill( themephi       , weight);  
 h_AOD_MET_pt              [selbin]->Fill( themet         , weight);  
 h_htall                   [selbin]->Fill( htall          , weight); 
 h_htaodcalojets           [selbin]->Fill( htaodcalojets  , weight); 
 return kTRUE;
}

//----------------------------writeMETHTHistograms
Bool_t analyzer_histograms::writeMETHTHistograms(int selbin)
{
  hist_file_out[selbin]->cd();
  h_AOD_MET_phi             [selbin]->Write(); 
  h_AOD_MET_pt              [selbin]->Write(); 
  h_htall                   [selbin]->Write(); 
  h_htaodcalojets           [selbin]->Write(); 
  return kTRUE;
}

//----------------------------deleteMETHTHistograms
Bool_t analyzer_histograms::deleteMETHTHistograms(int selbin)
{
  //printf("deleteMETHTHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_AOD_MET_phi  [selbin]!=NULL)   h_AOD_MET_phi             [selbin]->Delete(); 
  if(h_AOD_MET_pt   [selbin]!=NULL)   h_AOD_MET_pt              [selbin]->Delete(); 
  if(h_htall        [selbin]!=NULL)   h_htall                   [selbin]->Delete(); 
  if(h_htaodcalojets[selbin]!=NULL)   h_htaodcalojets           [selbin]->Delete(); 
  return kTRUE;
}



///// Jet Histograms
//----------------------------initAODCaloJetBasicHistograms
Bool_t analyzer_histograms::initAODCaloJetBasicHistograms( TString uncbin )
{

  // loop through jets and selections to initialize histograms in parllel (series)
  for(unsigned int i=0; i<selbinnames.size(); ++i){
  hist_file_out[i]->cd(); 
  //deleteAODCaloJetBasicHistograms(i);
      TString hname_nCaloJet                 = "h_"+selbinnames[i]+"_nCaloJet" +uncbin;
      TString hname_nPFJet                   = "h_"+selbinnames[i]+"_nPFJet"   +uncbin;
      TString hname_nPFchsJet                = "h_"+selbinnames[i]+"_nPFchsJet"+uncbin;
      h_nCaloJet                 [i] = initSingleHistogramTH1F( hname_nCaloJet  , "nCaloJet",  10,0,10);
      h_nPFJet                   [i] = initSingleHistogramTH1F( hname_nPFJet    , "nPFJet",    10,0,10);
      h_nPFchsJet                [i] = initSingleHistogramTH1F( hname_nPFchsJet , "nPFchsJet", 10,0,10);
      unsigned int k; if(jetMultOn) k=0; else k=jetmultnames.size()-1;
      for(k; k<jetmultnames.size(); ++k){
        //deleteAODCaloJetBasicHistograms(i,k);
	TString hname_AODCaloJetPt                            = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPt"                   +uncbin; 
	TString hname_AODCaloJetPtVar                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPtVar"                +uncbin; 
	TString hname_AODCaloJetEta                           = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetEta"                  +uncbin; 
	TString hname_AODCaloJetPhi                           = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPhi"                  +uncbin; 
	TString hname_AODCaloJetAlphaMax                      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMax"             +uncbin; 
	TString hname_AODCaloJetAlphaMax2                     = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMax2"            +uncbin; 
	TString hname_AODCaloJetAlphaMaxPrime                 = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMaxPrime"        +uncbin; 
	TString hname_AODCaloJetAlphaMaxPrime2                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAlphaMaxPrime2"       +uncbin; 
	TString hname_AODCaloJetBeta                          = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetBeta"                 +uncbin; 
	TString hname_AODCaloJetBeta2                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetBeta2"                +uncbin; 
	TString hname_AODCaloJetSumIP                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetSumIP"                +uncbin; 
	TString hname_AODCaloJetSumIPSig                      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetSumIPSig"             +uncbin; 
	TString hname_AODCaloJetMedianIP                      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMedianIP"             +uncbin; 
	TString hname_AODCaloJetMedianLog10IPSig              = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMedianLog10IPSig"     +uncbin; 
	TString hname_AODCaloJetTrackAngle                    = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetTrackAngle"           +uncbin; 
	TString hname_AODCaloJetLogTrackAngle                 = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetLogTrackAngle"        +uncbin; 
	TString hname_AODCaloJetMedianLog10TrackAngle         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMedianLog10TrackAngle"+uncbin; 
	TString hname_AODCaloJetTotalTrackAngle               = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetTotalTrackAngle"      +uncbin; 
	TString hname_AODCaloJetMinDR                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetMinDR"                +uncbin; 
	TString hname_AODCaloJetCSV                           = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetCSV"                  +uncbin; 
	TString hname_AODCaloJetPartonFlavour                 = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPartonFlavour"        +uncbin; 
        TString hname_AODCaloJetAbsEta                        = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetAbsEta"               +uncbin; 
	TString hname_AODCaloJetPtVarAbsEtaVar                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJetPtVarAbsEtaVar"       +uncbin; 
	h_AODCaloJetPt                             [i][k] = initSingleHistogramTH1F( hname_AODCaloJetPt                             , "AODCaloJetPt                            ", 50,0,500  ); 
	h_AODCaloJetEta                            [i][k] = initSingleHistogramTH1F( hname_AODCaloJetEta                            , "AODCaloJetEta                           ", 30,-5,5   ); 
	h_AODCaloJetPhi                            [i][k] = initSingleHistogramTH1F( hname_AODCaloJetPhi                            , "AODCaloJetPhi                           ", 30,-5,5   ); 
	h_AODCaloJetAlphaMax                       [i][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax                       , "AODCaloJetAlphaMax                      ", 50, 0, 1  ); 
	h_AODCaloJetAlphaMax2                      [i][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMax2                      , "AODCaloJetAlphaMax2                     ", 50, 0, 1  ); 
	h_AODCaloJetAlphaMaxPrime                  [i][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime                  , "AODCaloJetAlphaMaxPrime                 ", 50, 0, 1  ); 
	h_AODCaloJetAlphaMaxPrime2                 [i][k] = initSingleHistogramTH1F( hname_AODCaloJetAlphaMaxPrime2                 , "AODCaloJetAlphaMaxPrime2                ", 50, 0, 1  ); 
	h_AODCaloJetBeta                           [i][k] = initSingleHistogramTH1F( hname_AODCaloJetBeta                           , "AODCaloJetBeta                          ", 50, 0, 1  ); 
	h_AODCaloJetBeta2                          [i][k] = initSingleHistogramTH1F( hname_AODCaloJetBeta2                          , "AODCaloJetBeta2                         ", 50, 0, 1  ); 
	h_AODCaloJetSumIP                          [i][k] = initSingleHistogramTH1F( hname_AODCaloJetSumIP                          , "AODCaloJetSumIP                         ", 50, -3, 3 ); 
	h_AODCaloJetSumIPSig                       [i][k] = initSingleHistogramTH1F( hname_AODCaloJetSumIPSig                       , "AODCaloJetSumIPSig                      ", 50, -3, 3 ); 
	h_AODCaloJetMedianIP                       [i][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianIP                       , "AODCaloJetMedianIP                      ", 50, -3, 3 ); 
	h_AODCaloJetMedianLog10IPSig               [i][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10IPSig               , "AODCaloJetMedianLog10IPSig              ", 50, -3, 4 ); 
	h_AODCaloJetTrackAngle                     [i][k] = initSingleHistogramTH1F( hname_AODCaloJetTrackAngle                     , "AODCaloJetTrackAngle                    ", 50, -3, 3 ); 
	h_AODCaloJetLogTrackAngle                  [i][k] = initSingleHistogramTH1F( hname_AODCaloJetLogTrackAngle                  , "AODCaloJetLogTrackAngle                 ", 50, -3, 3 ); 
	h_AODCaloJetMedianLog10TrackAngle          [i][k] = initSingleHistogramTH1F( hname_AODCaloJetMedianLog10TrackAngle          , "AODCaloJetMedianLog10TrackAngle         ", 50, -5, 2 ); 
	h_AODCaloJetTotalTrackAngle                [i][k] = initSingleHistogramTH1F( hname_AODCaloJetTotalTrackAngle                , "AODCaloJetTotalTrackAngle               ", 50, -3, 3 ); 
	h_AODCaloJetMinDR                          [i][k] = initSingleHistogramTH1F( hname_AODCaloJetMinDR                          , "AODCaloJetMinDR                         ", 30, 0, 5 ); 
	h_AODCaloJetCSV                            [i][k] = initSingleHistogramTH1F( hname_AODCaloJetCSV                            , "AODCaloJetCSV                           ", 24, -.1, 1.1 ); 
	h_AODCaloJetPartonFlavour                  [i][k] = initSingleHistogramTH1F( hname_AODCaloJetPartonFlavour                  , "AODCaloJetPartonFlavour                 ", 35, -10, 25 ); 
        h_AODCaloJetAbsEta                         [i][k] = initSingleHistogramTH1F( hname_AODCaloJetAbsEta                         , "AODCaloJetAbsEta                        ", 4, 0, 3 );

	const int Pt_n_xbins = 10;
	float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
	h_AODCaloJetPtVar  [i][k] = initSingleHistogramTH1F( hname_AODCaloJetPtVar , "AODCaloJetPtVar",  Pt_n_xbins, Pt_xbins );

	const int AbsEta_n_bins = 2;
	float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
	h_AODCaloJetPtVarAbsEtaVar [i][k] = initSingleHistogramTH2F( hname_AODCaloJetPtVarAbsEtaVar, "AODCaloJetPtVarAbsEtaVar", Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins );

      }
  }
  return kTRUE;
}

//----------------------------fillAODCaloJetBasicHistograms
Bool_t analyzer_histograms::fillAODCaloJetBasicHistograms(Float_t weight, int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  if(jetmultnames.at(jetbin) == "AllJets"){
    // only fill these once (no jet multiplicity)
    h_nCaloJet                 [selbin]->Fill ( aodcalojet_list.size() , weight );
    h_nPFJet                   [selbin]->Fill ( 1 , weight ); // dummy values 
    h_nPFchsJet                [selbin]->Fill ( 1 , weight ); // dummy values 
    for(unsigned int i =0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i];
      h_AODCaloJetPt                             [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPtVar                          [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetEta                            [selbin][jetbin]->Fill( AODCaloJetEta                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPhi                            [selbin][jetbin]->Fill( AODCaloJetPhi                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax                       [selbin][jetbin]->Fill( Shifted_CaloJetAlphaMax                   .at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax2                      [selbin][jetbin]->Fill( AODCaloJetAlphaMax2                      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta                           [selbin][jetbin]->Fill( AODCaloJetBeta                           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta2                          [selbin][jetbin]->Fill( AODCaloJetBeta2                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIP                          [selbin][jetbin]->Fill( AODCaloJetSumIP                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIPSig                       [selbin][jetbin]->Fill( AODCaloJetSumIPSig                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianIP                       [selbin][jetbin]->Fill( AODCaloJetMedianIP                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10IPSig               [selbin][jetbin]->Fill( Shifted_CaloJetMedianLog10IPSig           .at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin]->Fill( Shifted_CaloJetMedianLog10TrackAngle      .at( aodcalojetindex ), weight );  
      h_AODCaloJetTotalTrackAngle                [selbin][jetbin]->Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMinDR                          [selbin][jetbin]->Fill( aodcalojet_minDR_list                     .at( aodcalojetindex ), weight );  
      h_AODCaloJetCSV                            [selbin][jetbin]->Fill( aodcalojet_matchedCSV_list                .at( aodcalojetindex ), weight );  
      h_AODCaloJetPartonFlavour                  [selbin][jetbin]->Fill( aodcalojet_matchedPartonFlavour_list      .at( aodcalojetindex ), weight );  
      h_AODCaloJetAbsEta                         [selbin][jetbin]->Fill( fabs(AODCaloJetEta                       ->at( aodcalojetindex )), weight );
      h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin]->Fill( AODCaloJetPt->at(aodcalojetindex), fabs(AODCaloJetEta->at(aodcalojetindex)), weight );  
    }    
  }
  else{
    if( jetbin < (int)aodcalojet_list.size() ){
      int aodcalojetindex = aodcalojet_list[jetbin];
      h_AODCaloJetPt                             [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPtVar                          [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetEta                            [selbin][jetbin]->Fill( AODCaloJetEta                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetPhi                            [selbin][jetbin]->Fill( AODCaloJetPhi                            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax                       [selbin][jetbin]->Fill( Shifted_CaloJetAlphaMax                   .at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMax2                      [selbin][jetbin]->Fill( AODCaloJetAlphaMax2                      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta                           [selbin][jetbin]->Fill( AODCaloJetBeta                           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetBeta2                          [selbin][jetbin]->Fill( AODCaloJetBeta2                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIP                          [selbin][jetbin]->Fill( AODCaloJetSumIP                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumIPSig                       [selbin][jetbin]->Fill( AODCaloJetSumIPSig                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianIP                       [selbin][jetbin]->Fill( AODCaloJetMedianIP                       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10IPSig               [selbin][jetbin]->Fill( Shifted_CaloJetMedianLog10IPSig           .at( aodcalojetindex ), weight );  
      h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin]->Fill( Shifted_CaloJetMedianLog10TrackAngle      .at( aodcalojetindex ), weight );  
      h_AODCaloJetTotalTrackAngle                [selbin][jetbin]->Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMinDR                          [selbin][jetbin]->Fill( aodcalojet_minDR_list                     .at( aodcalojetindex ), weight );  
      h_AODCaloJetCSV                            [selbin][jetbin]->Fill( aodcalojet_matchedCSV_list                .at( aodcalojetindex ), weight );  
      h_AODCaloJetPartonFlavour                  [selbin][jetbin]->Fill( aodcalojet_matchedPartonFlavour_list      .at( aodcalojetindex ), weight );  
      h_AODCaloJetAbsEta                         [selbin][jetbin]->Fill( fabs(AODCaloJetEta                       ->at( aodcalojetindex )), weight );
      h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin]->Fill( AODCaloJetPt->at(aodcalojetindex), fabs(AODCaloJetEta->at(aodcalojetindex)), weight );  
    }
  }
  
  return kTRUE;
} //end fill histograms

//----------------------------writeAODCaloJetHistograms
Bool_t analyzer_histograms::writeAODCaloJetBasicHistograms(int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  //printf("writeAODCaloJetHistograms\n");
  if(jetbin==0){
   h_nCaloJet                 [selbin]->Write();
   h_nPFJet                   [selbin]->Write();
   h_nPFchsJet                [selbin]->Write();
  }
  h_AODCaloJetPt                             [selbin][jetbin]->Write(); 
  h_AODCaloJetPtVar                          [selbin][jetbin]->Write(); 
  h_AODCaloJetEta                            [selbin][jetbin]->Write(); 
  h_AODCaloJetPhi                            [selbin][jetbin]->Write(); 
  h_AODCaloJetAlphaMax                       [selbin][jetbin]->Write(); 
  h_AODCaloJetAlphaMax2                      [selbin][jetbin]->Write(); 
  h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin]->Write(); 
  h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin]->Write(); 
  h_AODCaloJetBeta                           [selbin][jetbin]->Write(); 
  h_AODCaloJetBeta2                          [selbin][jetbin]->Write(); 
  h_AODCaloJetSumIP                          [selbin][jetbin]->Write(); 
  h_AODCaloJetSumIPSig                       [selbin][jetbin]->Write(); 
  h_AODCaloJetMedianIP                       [selbin][jetbin]->Write(); 
  h_AODCaloJetMedianLog10IPSig               [selbin][jetbin]->Write(); 
  h_AODCaloJetTrackAngle                     [selbin][jetbin]->Write(); 
  h_AODCaloJetLogTrackAngle                  [selbin][jetbin]->Write(); 
  h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin]->Write(); 
  h_AODCaloJetTotalTrackAngle                [selbin][jetbin]->Write(); 
  h_AODCaloJetMinDR                          [selbin][jetbin]->Write(); 
  h_AODCaloJetCSV                            [selbin][jetbin]->Write(); 
  h_AODCaloJetPartonFlavour                  [selbin][jetbin]->Write(); 
  h_AODCaloJetAbsEta                         [selbin][jetbin]->Write();
  h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin]->Write(); 
 return kTRUE;
}

Bool_t analyzer_histograms::deleteAODCaloJetBasicHistograms(int selbin)
{
  //printf("deleteAODCaloJetBasicHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_nCaloJet  [selbin]!=NULL)    h_nCaloJet                 [selbin]->Delete();
  if(h_nPFJet    [selbin]!=NULL)    h_nPFJet                   [selbin]->Delete();
  if(h_nPFchsJet [selbin]!=NULL)    h_nPFchsJet                [selbin]->Delete();
 return kTRUE;
}

//----------------------------deleteAODCaloJetHistograms
Bool_t analyzer_histograms::deleteAODCaloJetBasicHistograms(int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  //printf("deleteAODCaloJetHistograms\n");
  if(h_AODCaloJetPt                   [selbin][jetbin]!=NULL)    h_AODCaloJetPt                             [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetPtVar                [selbin][jetbin]!=NULL)    h_AODCaloJetPtVar                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetEta                  [selbin][jetbin]!=NULL)    h_AODCaloJetEta                            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetPhi                  [selbin][jetbin]!=NULL)    h_AODCaloJetPhi                            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAlphaMax             [selbin][jetbin]!=NULL)    h_AODCaloJetAlphaMax                       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAlphaMax2            [selbin][jetbin]!=NULL)    h_AODCaloJetAlphaMax2                      [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAlphaMaxPrime        [selbin][jetbin]!=NULL)    h_AODCaloJetAlphaMaxPrime                  [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAlphaMaxPrime2       [selbin][jetbin]!=NULL)    h_AODCaloJetAlphaMaxPrime2                 [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetBeta                 [selbin][jetbin]!=NULL)    h_AODCaloJetBeta                           [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetBeta2                [selbin][jetbin]!=NULL)    h_AODCaloJetBeta2                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetSumIP                [selbin][jetbin]!=NULL)    h_AODCaloJetSumIP                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetSumIPSig             [selbin][jetbin]!=NULL)    h_AODCaloJetSumIPSig                       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetMedianIP             [selbin][jetbin]!=NULL)    h_AODCaloJetMedianIP                       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetMedianLog10IPSig     [selbin][jetbin]!=NULL)    h_AODCaloJetMedianLog10IPSig               [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetTrackAngle           [selbin][jetbin]!=NULL)    h_AODCaloJetTrackAngle                     [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetLogTrackAngle        [selbin][jetbin]!=NULL)    h_AODCaloJetLogTrackAngle                  [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetMedianLog10TrackAngle[selbin][jetbin]!=NULL)    h_AODCaloJetMedianLog10TrackAngle          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetTotalTrackAngle      [selbin][jetbin]!=NULL)    h_AODCaloJetTotalTrackAngle                [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetMinDR                [selbin][jetbin]!=NULL)    h_AODCaloJetMinDR                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetCSV                  [selbin][jetbin]!=NULL)    h_AODCaloJetCSV                            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetPartonFlavour        [selbin][jetbin]!=NULL)    h_AODCaloJetPartonFlavour                  [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAbsEta               [selbin][jetbin]!=NULL)    h_AODCaloJetAbsEta                         [selbin][jetbin]->Delete();
  if(h_AODCaloJetPtVarAbsEtaVar       [selbin][jetbin]!=NULL)    h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin]->Delete(); 
 return kTRUE;
}


// Study for the reason behind necessity of the tagging variable shift
//----------------------------initAODCaloJetStudyHistograms
Bool_t analyzer_histograms::initAODCaloJetStudyHistograms( TString uncbin )
{

  // loop through jets and selections to initialize histograms in parllel (series)
  for(unsigned int i=0; i<selbinnames.size(); ++i){
  hist_file_out[i]->cd(); 
  //deleteAODCaloJetStudyHistograms(i);
      unsigned int k; if(jetMultOn) k=0; else k=jetmultnames.size()-1;
      for(k; k<jetmultnames.size(); ++k){
        //deleteAODCaloJetStudyHistograms(i,k);
        TString hname_AODCaloJet_Study_trk0_AlphaMax                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_trk0_AlphaMax"               +uncbin ;
        TString hname_AODCaloJet_Study_trk0_MedianLog10IPSig        = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_trk0_MedianLog10IPSig"       +uncbin ;
        TString hname_AODCaloJet_Study_trk0_MedianLog10TrackAngle   = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_trk0_MedianLog10TrackAngle"  +uncbin ;
        TString hname_AODCaloJet_Study_ptG0p5_AlphaMax              = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_ptG0p5_AlphaMax"             +uncbin ;
        TString hname_AODCaloJet_Study_ptG0p5_MedianLog10IPSig      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_ptG0p5_MedianLog10IPSig"     +uncbin ;
        TString hname_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle"+uncbin ;
        TString hname_AODCaloJet_Study_ptG10_AlphaMax              = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_ptG10_AlphaMax"             +uncbin ;
        TString hname_AODCaloJet_Study_ptG10_MedianLog10IPSig      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_ptG10_MedianLog10IPSig"     +uncbin ;
        TString hname_AODCaloJet_Study_ptG10_MedianLog10TrackAngle = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_ptG10_MedianLog10TrackAngle"+uncbin ;
                                                                                                      
        TString hname_AODCaloJet_Study_n_v_AlphaMax                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_n_v_AlphaMax"               +uncbin ;
        TString hname_AODCaloJet_Study_n_v_MedianLog10IPSig        = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_n_v_MedianLog10IPSig"       +uncbin ;
        TString hname_AODCaloJet_Study_n_v_MedianLog10TrackAngle   = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_n_v_MedianLog10TrackAngle"  +uncbin ;
        TString hname_AODCaloJet_Study_pt_v_AlphaMax                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_pt_v_AlphaMax"               +uncbin ;
        TString hname_AODCaloJet_Study_pt_v_MedianLog10IPSig        = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_pt_v_MedianLog10IPSig"       +uncbin ;
        TString hname_AODCaloJet_Study_pt_v_MedianLog10TrackAngle   = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_Study_pt_v_MedianLog10TrackAngle"  +uncbin ;

        h_AODCaloJet_Study_trk0_AlphaMax               [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_trk0_AlphaMax                , "Study_trk0_AlphaMax"               , 50, 0, 1 );
        h_AODCaloJet_Study_trk0_MedianLog10IPSig       [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_trk0_MedianLog10IPSig        , "Study_trk0_MedianLog10IPSig"       , 50, -3, 4);
        h_AODCaloJet_Study_trk0_MedianLog10TrackAngle  [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_trk0_MedianLog10TrackAngle   , "Study_trk0_MedianLog10TrackAngle"  , 50, -5, 2);
        h_AODCaloJet_Study_ptG0p5_AlphaMax             [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_ptG0p5_AlphaMax              , "Study_ptG0p5_AlphaMax"             , 50, 0, 1 );
        h_AODCaloJet_Study_ptG0p5_MedianLog10IPSig     [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_ptG0p5_MedianLog10IPSig      , "Study_ptG0p5_MedianLog10IPSig"     , 50, -3, 4);
        h_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle[i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle , "Study_ptG0p5_MedianLog10TrackAngle", 50, -5, 2);
        h_AODCaloJet_Study_ptG10_AlphaMax             [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_ptG10_AlphaMax              , "Study_ptG10_AlphaMax"             , 50, 0, 1 );
        h_AODCaloJet_Study_ptG10_MedianLog10IPSig     [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_ptG10_MedianLog10IPSig      , "Study_ptG10_MedianLog10IPSig"     , 50, -3, 4);
        h_AODCaloJet_Study_ptG10_MedianLog10TrackAngle[i][k] = initSingleHistogramTH1F( hname_AODCaloJet_Study_ptG10_MedianLog10TrackAngle , "Study_ptG10_MedianLog10TrackAngle", 50, -5, 2);

	const int Pt_n_xbins = 10;
	float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};

        //h_AODCaloJet_Study_pt_v_AlphaMax               [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_pt_v_AlphaMax                ,"Study_pt_v_AlphaMax"               , Pt_n_xbins, Pt_xbins, 50, 0, 1 );
        //h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_pt_v_MedianLog10IPSig        ,"Study_pt_v_MedianLog10IPSig"       , Pt_n_xbins, Pt_xbins, 50, -3, 4);
        //h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_pt_v_MedianLog10TrackAngle   ,"Study_pt_v_MedianLog10TrackAngle"  , Pt_n_xbins, Pt_xbins, 50, -5, 2);
        h_AODCaloJet_Study_pt_v_AlphaMax               [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_pt_v_AlphaMax               , "Study_pt_v_AlphaMax"               , 50, 0, 500, 50, 0, 1 );
        h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_pt_v_MedianLog10IPSig       , "Study_pt_v_MedianLog10IPSig"       , 50, 0, 500, 50, -3, 4);
        h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  , "Study_pt_v_MedianLog10TrackAngle"  , 50, 0, 500, 50, -5, 2);
        h_AODCaloJet_Study_n_v_AlphaMax               [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_n_v_AlphaMax               , "Study_n_v_AlphaMax"               , 15, 0, 15, 50, 0, 1 );
        h_AODCaloJet_Study_n_v_MedianLog10IPSig       [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_n_v_MedianLog10IPSig       , "Study_n_v_MedianLog10IPSig"       , 15, 0, 15, 50, -3, 4);
        h_AODCaloJet_Study_n_v_MedianLog10TrackAngle  [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_Study_n_v_MedianLog10TrackAngle  , "Study_n_v_MedianLog10TrackAngle"  , 15, 0, 15, 50, -5, 2);

      }
  }
  return kTRUE;
}

//----------------------------fillAODCaloJetStudyHistograms
Bool_t analyzer_histograms::fillAODCaloJetStudyHistograms(Float_t weight, int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  if(jetmultnames.at(jetbin) == "AllJets"){
    // only fill these once (no jet multiplicity)
    for(unsigned int i =0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i];
      // std::cout<<"AODCaloJetAvfVertexTrackEnergy"<<AODCaloJetAvfVertexTrackEnergy->at(0)<<" "<<aodcalojetindex<<std::endl;
      // std::cout<<" "<<AODCaloJetAvfVertexTrackEnergy->size()<<" "<<AODCaloJetNCleanMatchedTracks->at( aodcalojetindex )<<std::endl;
      if(aodcalojetindex==0){
       h_AODCaloJet_Study_trk0_AlphaMax               [selbin][jetbin]->Fill( AODCaloJetAlphaMax              ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_trk0_MedianLog10IPSig       [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_trk0_MedianLog10TrackAngle  [selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight); 
      }
      if(AODCaloJetAvfVertexTrackEnergy->at(0)>0.5){
       h_AODCaloJet_Study_ptG0p5_AlphaMax             [selbin][jetbin]->Fill( AODCaloJetAlphaMax              ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG0p5_MedianLog10IPSig     [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle[selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight); 
      }
      if(AODCaloJetAvfVertexTrackEnergy->at(0)>10.){
       h_AODCaloJet_Study_ptG10_AlphaMax              [selbin][jetbin]->Fill( AODCaloJetAlphaMax              ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG10_MedianLog10IPSig      [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG10_MedianLog10TrackAngle [selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight); 
      }
                                                                                                                         
      h_AODCaloJet_Study_n_v_AlphaMax               [selbin][jetbin]->Fill( AODCaloJetNCleanMatchedTracks->at(aodcalojetindex) , AODCaloJetAlphaMax              ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_n_v_MedianLog10IPSig       [selbin][jetbin]->Fill( AODCaloJetNCleanMatchedTracks->at(aodcalojetindex) , AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_n_v_MedianLog10TrackAngle  [selbin][jetbin]->Fill( AODCaloJetNCleanMatchedTracks->at(aodcalojetindex) , AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_pt_v_AlphaMax               [selbin][jetbin]->Fill(AODCaloJetAvfVertexTrackEnergy->at( 0 ) , AODCaloJetAlphaMax              ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [selbin][jetbin]->Fill(AODCaloJetAvfVertexTrackEnergy->at( 0 ) , AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [selbin][jetbin]->Fill(AODCaloJetAvfVertexTrackEnergy->at( 0 ) , AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight);

    }    
  }
  else{
    if( jetbin < (int)aodcalojet_list.size() ){
      int aodcalojetindex = aodcalojet_list[jetbin];
  
      if(aodcalojetindex==0){
       h_AODCaloJet_Study_trk0_AlphaMax               [selbin][jetbin]->Fill( AODCaloJetAlphaMax              ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_trk0_MedianLog10IPSig       [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_trk0_MedianLog10TrackAngle  [selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight); 
      }
      if(AODCaloJetAvfVertexTrackEnergy->at(0)>0.5){
       h_AODCaloJet_Study_ptG0p5_AlphaMax             [selbin][jetbin]->Fill( AODCaloJetAlphaMax              ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG0p5_MedianLog10IPSig     [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle[selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight); 
      }
      if(AODCaloJetAvfVertexTrackEnergy->at(0)>10.){
       h_AODCaloJet_Study_ptG10_AlphaMax              [selbin][jetbin]->Fill( AODCaloJetAlphaMax              ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG10_MedianLog10IPSig      [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight); 
       h_AODCaloJet_Study_ptG10_MedianLog10TrackAngle [selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight); 
      }
                                                                                                                         
      h_AODCaloJet_Study_n_v_AlphaMax               [selbin][jetbin]->Fill(AODCaloJetNCleanMatchedTracks->at( aodcalojetindex ) , AODCaloJetAlphaMax              ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_n_v_MedianLog10IPSig       [selbin][jetbin]->Fill(AODCaloJetNCleanMatchedTracks->at( aodcalojetindex ) , AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_n_v_MedianLog10TrackAngle  [selbin][jetbin]->Fill(AODCaloJetNCleanMatchedTracks->at( aodcalojetindex ) , AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_pt_v_AlphaMax               [selbin][jetbin]->Fill(AODCaloJetAvfVertexTrackEnergy->at( 0 ) , AODCaloJetAlphaMax              ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [selbin][jetbin]->Fill(AODCaloJetAvfVertexTrackEnergy->at( 0 ) , AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex), weight);
      h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [selbin][jetbin]->Fill(AODCaloJetAvfVertexTrackEnergy->at( 0 ) , AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex), weight);
    }
  }
  
  return kTRUE;
} //end fill histograms

//----------------------------writeAODCaloStudyJetHistograms
Bool_t analyzer_histograms::writeAODCaloJetStudyHistograms(int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  h_AODCaloJet_Study_trk0_AlphaMax               [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_trk0_MedianLog10IPSig       [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_trk0_MedianLog10TrackAngle  [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_ptG0p5_AlphaMax             [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_ptG0p5_MedianLog10IPSig     [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle[selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_ptG10_AlphaMax              [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_ptG10_MedianLog10IPSig      [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_ptG10_MedianLog10TrackAngle [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_n_v_AlphaMax               [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_n_v_MedianLog10IPSig       [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_n_v_MedianLog10TrackAngle  [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_pt_v_AlphaMax               [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [selbin][jetbin]->Write(); 
  h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [selbin][jetbin]->Write(); 
 return kTRUE;
}

//----------------------------deleteAODCaloJetStudyHistograms
Bool_t analyzer_histograms::deleteAODCaloJetStudyHistograms(int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  //printf("deleteAODCaloJetHistograms\n");
  if(h_AODCaloJet_Study_trk0_AlphaMax               [selbin][jetbin]!=NULL) h_AODCaloJet_Study_trk0_AlphaMax               [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_trk0_MedianLog10IPSig       [selbin][jetbin]!=NULL) h_AODCaloJet_Study_trk0_MedianLog10IPSig       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_trk0_MedianLog10TrackAngle  [selbin][jetbin]!=NULL) h_AODCaloJet_Study_trk0_MedianLog10TrackAngle  [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_ptG0p5_AlphaMax             [selbin][jetbin]!=NULL) h_AODCaloJet_Study_ptG0p5_AlphaMax             [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_ptG0p5_MedianLog10IPSig     [selbin][jetbin]!=NULL) h_AODCaloJet_Study_ptG0p5_MedianLog10IPSig     [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle[selbin][jetbin]!=NULL) h_AODCaloJet_Study_ptG0p5_MedianLog10TrackAngle[selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_ptG10_AlphaMax              [selbin][jetbin]!=NULL) h_AODCaloJet_Study_ptG10_AlphaMax             [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_ptG10_MedianLog10IPSig      [selbin][jetbin]!=NULL) h_AODCaloJet_Study_ptG10_MedianLog10IPSig     [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_ptG10_MedianLog10TrackAngle [selbin][jetbin]!=NULL) h_AODCaloJet_Study_ptG10_MedianLog10TrackAngle[selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_n_v_AlphaMax               [selbin][jetbin]!=NULL) h_AODCaloJet_Study_pt_v_AlphaMax               [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_n_v_MedianLog10IPSig       [selbin][jetbin]!=NULL) h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_n_v_MedianLog10TrackAngle  [selbin][jetbin]!=NULL) h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_pt_v_AlphaMax               [selbin][jetbin]!=NULL) h_AODCaloJet_Study_pt_v_AlphaMax               [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [selbin][jetbin]!=NULL) h_AODCaloJet_Study_pt_v_MedianLog10IPSig       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [selbin][jetbin]!=NULL) h_AODCaloJet_Study_pt_v_MedianLog10TrackAngle  [selbin][jetbin]->Delete(); 
 return kTRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///                         For L1 Pre-firing test                                                 ////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

///// Jet Histograms
//----------------------------initAODCaloJet_L1PFBasicHistograms
Bool_t analyzer_histograms::initAODCaloJet_L1PFHistograms( TString uncbin )
{
  // loop through jets and selections to initialize histograms in parllel (series)
  for(unsigned int i=0; i<selbinnames.size(); ++i){
      hist_file_out[i]->cd();
      //deleteAODCaloJet_L1PFHistograms(i);
      TString hname_nCaloJet_L1PF = "h_"+selbinnames[i]+"_nCaloJet_L1PF" +uncbin;
      h_nCaloJet_L1PF        [i] = initSingleHistogramTH1F( hname_nCaloJet_L1PF, "nCaloJet_L1PF",  10,0,10);
      
      TString hname_nSelectedAODCaloJet_L1PFTag  = "h_"+selbinnames[i]+"_nSelectedAODCaloJet_L1PFTag"+uncbin;
      h_nSelectedAODCaloJet_L1PFTag         [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJet_L1PFTag, "nSelectedAODCaloJet_L1PFTag", 6, -0.5, 5.5);
      unsigned int k; if(jetMultOn) k=0; else k=jetmultnames.size()-1;
      for(k; k<jetmultnames.size(); ++k){
        //deleteAODCaloJet_L1PFHistograms(i,k);
        TString hname_AODCaloJet_L1PFPt                            = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFPt"                   +uncbin;                                  
        //TString hname_AODCaloJet_L1PFPtVar                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFPtVar"                +uncbin;                                                            
        //TString hname_AODCaloJet_L1PFEta                           = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFEta"                  +uncbin;                                      
        //TString hname_AODCaloJet_L1PFPhi                           = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFPhi"                  +uncbin;                                      
        TString hname_AODCaloJet_L1PFAlphaMax                      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFAlphaMax"             +uncbin;                                      
        //TString hname_AODCaloJet_L1PFAlphaMax2                     = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFAlphaMax2"            +uncbin;                                      
        //TString hname_AODCaloJet_L1PFAlphaMaxPrime                 = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFAlphaMaxPrime"        +uncbin;                                      
        //TString hname_AODCaloJet_L1PFAlphaMaxPrime2                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFAlphaMaxPrime2"       +uncbin;                                      
        //TString hname_AODCaloJet_L1PFBeta                          = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFBeta"                 +uncbin;                                      
        //TString hname_AODCaloJet_L1PFBeta2                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFBeta2"                +uncbin;                                      
        //TString hname_AODCaloJet_L1PFSumIP                         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFSumIP"                +uncbin;                                      
        //TString hname_AODCaloJet_L1PFSumIPSig                      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFSumIPSig"             +uncbin;                                      
        //TString hname_AODCaloJet_L1PFMedianIP                      = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFMedianIP"             +uncbin;                                      
        TString hname_AODCaloJet_L1PFMedianLog10IPSig              = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFMedianLog10IPSig"     +uncbin;                                      
        //TString hname_AODCaloJet_L1PFTrackAngle                    = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFTrackAngle"           +uncbin;                                      
        //TString hname_AODCaloJet_L1PFLogTrackAngle                 = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFLogTrackAngle"        +uncbin;                                      
        TString hname_AODCaloJet_L1PFMedianLog10TrackAngle         = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFMedianLog10TrackAngle"+uncbin;                                      
        //TString hname_AODCaloJet_L1PFTotalTrackAngle               = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFTotalTrackAngle"      +uncbin;                                      
        //  TString hname_AODCaloJet_L1PFAbsEta                        = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFAbsEta"               +uncbin;             
        //TString hname_AODCaloJet_L1PFPtVarAbsEtaVar                = "h_"+selbinnames[i]+"_"+jetmultnames[k]+"_AODCaloJet_L1PFPtVarAbsEtaVar"       +uncbin;                                                  
        //
        h_AODCaloJet_L1PFPt                             [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFPt                             , "AODCaloJet_L1PFPt                            ", 50,0,500  ); 
        //h_AODCaloJet_L1PFEta                            [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFEta                            , "AODCaloJet_L1PFEta                           ", 30,-5,5   ); 
        //h_AODCaloJet_L1PFPhi                            [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFPhi                            , "AODCaloJet_L1PFPhi                           ", 30,-5,5   ); 
        h_AODCaloJet_L1PFAlphaMax                       [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFAlphaMax                       , "AODCaloJet_L1PFAlphaMax                      ", 30, 0, 1  ); 
        //h_AODCaloJet_L1PFAlphaMax2                      [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFAlphaMax2                      , "AODCaloJet_L1PFAlphaMax2                     ", 30, 0, 1  ); 
        //h_AODCaloJet_L1PFAlphaMaxPrime                  [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFAlphaMaxPrime                  , "AODCaloJet_L1PFAlphaMaxPrime                 ", 30, 0, 1  ); 
        //h_AODCaloJet_L1PFAlphaMaxPrime2                 [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFAlphaMaxPrime2                 , "AODCaloJet_L1PFAlphaMaxPrime2                ", 30, 0, 1  ); 
        //h_AODCaloJet_L1PFBeta                           [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFBeta                           , "AODCaloJet_L1PFBeta                          ", 30, 0, 1  ); 
        //h_AODCaloJet_L1PFBeta2                          [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFBeta2                          , "AODCaloJet_L1PFBeta2                         ", 30, 0, 1  ); 
        //h_AODCaloJet_L1PFSumIP                          [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFSumIP                          , "AODCaloJet_L1PFSumIP                         ", 30, -3, 3 ); 
        //h_AODCaloJet_L1PFSumIPSig                       [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFSumIPSig                       , "AODCaloJet_L1PFSumIPSig                      ", 30, -3, 3 ); 
        //h_AODCaloJet_L1PFMedianIP                       [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFMedianIP                       , "AODCaloJet_L1PFMedianIP                      ", 30, -3, 3 ); 
        h_AODCaloJet_L1PFMedianLog10IPSig               [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFMedianLog10IPSig               , "AODCaloJet_L1PFMedianLog10IPSig              ", 30, -3, 3 ); 
        //h_AODCaloJet_L1PFTrackAngle                     [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFTrackAngle                     , "AODCaloJet_L1PFTrackAngle                    ", 30, -3, 3 ); 
        //h_AODCaloJet_L1PFLogTrackAngle                  [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFLogTrackAngle                  , "AODCaloJet_L1PFLogTrackAngle                 ", 30, -3, 3 ); 
        h_AODCaloJet_L1PFMedianLog10TrackAngle          [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFMedianLog10TrackAngle          , "AODCaloJet_L1PFMedianLog10TrackAngle         ", 30, -5, 1 ); 
        //h_AODCaloJet_L1PFTotalTrackAngle                [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFTotalTrackAngle                , "AODCaloJet_L1PFTotalTrackAngle               ", 30, -3, 3 ); 
        //  h_AODCaloJet_L1PFAbsEta                         [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFAbsEta                         , "AODCaloJet_L1PFAbsEta                        ", 4, 0, 3 );

	//const int Pt_n_xbins = 10;
	//float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
	//h_AODCaloJet_L1PFPtVar  [i][k] = initSingleHistogramTH1F( hname_AODCaloJet_L1PFPtVar , "AODCaloJet_L1PFPtVar",  Pt_n_xbins, Pt_xbins );
	
	//const int AbsEta_n_bins = 2;
	//float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
	//h_AODCaloJet_L1PFPtVarAbsEtaVar [i][k] = initSingleHistogramTH2F( hname_AODCaloJet_L1PFPtVarAbsEtaVar, "AODCaloJet_L1PFPtVarAbsEtaVar", Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins );

      }
  }
  return kTRUE;
}

//----------------------------fillAODCaloJet_L1PFHistograms
Bool_t analyzer_histograms::fillAODCaloJet_L1PFHistograms(Float_t weight, int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  if(jetmultnames.at(jetbin) == "AllJets"){
    // only fill these once (no jet multiplicity)
    h_nCaloJet_L1PF                 [selbin]->Fill ( aodcalojet_L1PF_list.size() , weight );
    if(!L1PFremoved)  h_nSelectedAODCaloJet_L1PFTag       [selbin] ->Fill( float(taggedjet_list_L1PF.size()), weight );
    for(unsigned int i =0; i<aodcalojet_L1PF_list.size(); i++){
      int aodcalojet_L1PFindex = aodcalojet_L1PF_list[i];
      h_AODCaloJet_L1PFPt                             [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFPtVar                          [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFEta                            [selbin][jetbin]->Fill( AODCaloJetEta                            ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFPhi                            [selbin][jetbin]->Fill( AODCaloJetPhi                            ->at( aodcalojet_L1PFindex ), weight );  
      h_AODCaloJet_L1PFAlphaMax                       [selbin][jetbin]->Fill( AODCaloJetAlphaMax                       ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAlphaMax2                      [selbin][jetbin]->Fill( AODCaloJetAlphaMax2                      ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAlphaMaxPrime                  [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAlphaMaxPrime2                 [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFBeta                           [selbin][jetbin]->Fill( AODCaloJetBeta                           ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFBeta2                          [selbin][jetbin]->Fill( AODCaloJetBeta2                          ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFSumIP                          [selbin][jetbin]->Fill( AODCaloJetSumIP                          ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFSumIPSig                       [selbin][jetbin]->Fill( AODCaloJetSumIPSig                       ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFMedianIP                       [selbin][jetbin]->Fill( AODCaloJetMedianIP                       ->at( aodcalojet_L1PFindex ), weight );  
      h_AODCaloJet_L1PFMedianLog10IPSig               [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig               ->at( aodcalojet_L1PFindex ), weight );  
      h_AODCaloJet_L1PFMedianLog10TrackAngle          [selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle          ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFTotalTrackAngle                [selbin][jetbin]->Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFPtVarAbsEtaVar                 [selbin][jetbin]->Fill( AODCaloJetPt->at(aodcalojet_L1PFindex), fabs(AODCaloJetEta->at(aodcalojet_L1PFindex)), weight );  
    }    
  }
  else{
    if( jetbin < (int)aodcalojet_L1PF_list.size() ){
      int aodcalojet_L1PFindex = aodcalojet_L1PF_list[jetbin];
      h_AODCaloJet_L1PFPt                             [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFPtVar                          [selbin][jetbin]->Fill( AODCaloJetPt                             ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFEta                            [selbin][jetbin]->Fill( AODCaloJetEta                            ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFPhi                            [selbin][jetbin]->Fill( AODCaloJetPhi                            ->at( aodcalojet_L1PFindex ), weight );  
      h_AODCaloJet_L1PFAlphaMax                       [selbin][jetbin]->Fill( AODCaloJetAlphaMax                       ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAlphaMax2                      [selbin][jetbin]->Fill( AODCaloJetAlphaMax2                      ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAlphaMaxPrime                  [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime                  ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAlphaMaxPrime2                 [selbin][jetbin]->Fill( AODCaloJetAlphaMaxPrime2                 ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFBeta                           [selbin][jetbin]->Fill( AODCaloJetBeta                           ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFBeta2                          [selbin][jetbin]->Fill( AODCaloJetBeta2                          ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFSumIP                          [selbin][jetbin]->Fill( AODCaloJetSumIP                          ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFSumIPSig                       [selbin][jetbin]->Fill( AODCaloJetSumIPSig                       ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFMedianIP                       [selbin][jetbin]->Fill( AODCaloJetMedianIP                       ->at( aodcalojet_L1PFindex ), weight );  
      h_AODCaloJet_L1PFMedianLog10IPSig               [selbin][jetbin]->Fill( AODCaloJetMedianLog10IPSig               ->at( aodcalojet_L1PFindex ), weight );  
      h_AODCaloJet_L1PFMedianLog10TrackAngle          [selbin][jetbin]->Fill( AODCaloJetMedianLog10TrackAngle          ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFTotalTrackAngle                [selbin][jetbin]->Fill( AODCaloJetTotalTrackAngle                ->at( aodcalojet_L1PFindex ), weight );  
      //h_AODCaloJet_L1PFAbsEta                         [selbin][jetbin]->Fill( fabs(AODCaloJetEta                       ->at( aodcalojet_L1PFindex )), weight );
      //h_AODCaloJet_L1PFPtVarAbsEtaVar                 [selbin][jetbin]->Fill( AODCaloJetPt->at(aodcalojet_L1PFindex), fabs(AODCaloJetEta->at(aodcalojet_L1PFindex)), weight );  
    }
  }
  
  return kTRUE;
} //end fill histograms

//----------------------------writeAODCaloJet_L1PFHistograms
Bool_t analyzer_histograms::writeAODCaloJet_L1PFHistograms(int selbin, int jetbin)
{
  hist_file_out[selbin]->cd();
  //printf("writeAODCaloJet_L1PFHistograms\n");
  if(jetbin==0){
   h_nCaloJet_L1PF                 [selbin]->Write();
   h_nSelectedAODCaloJet_L1PFTag   [selbin]->Write();
  }
  h_AODCaloJet_L1PFPt                             [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFPtVar                          [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFEta                            [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFPhi                            [selbin][jetbin]->Write(); 
  h_AODCaloJet_L1PFAlphaMax                       [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFAlphaMax2                      [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFAlphaMaxPrime                  [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFAlphaMaxPrime2                 [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFBeta                           [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFBeta2                          [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFSumIP                          [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFSumIPSig                       [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFMedianIP                       [selbin][jetbin]->Write(); 
  h_AODCaloJet_L1PFMedianLog10IPSig               [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFTrackAngle                     [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFLogTrackAngle                  [selbin][jetbin]->Write(); 
  h_AODCaloJet_L1PFMedianLog10TrackAngle          [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFTotalTrackAngle                [selbin][jetbin]->Write(); 
  //h_AODCaloJet_L1PFAbsEta                         [selbin][jetbin]->Write();
  //h_AODCaloJet_L1PFPtVarAbsEtaVar                 [selbin][jetbin]->Write(); 
 return kTRUE;
}

//----------------------------deleteAODCaloJet_L1PFHistograms
Bool_t analyzer_histograms::deleteAODCaloJet_L1PFHistograms(int selbin)
{
  //printf("deleteAODCaloJet_L1PFHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_nCaloJet_L1PF              [selbin]!=NULL)   h_nCaloJet_L1PF              [selbin]->Delete();
  if(h_nSelectedAODCaloJet_L1PFTag[selbin]!=NULL)   h_nSelectedAODCaloJet_L1PFTag[selbin] ->Delete();
  return kTRUE;
}

//----------------------------deleteAODCaloJet_L1PFHistograms
Bool_t analyzer_histograms::deleteAODCaloJet_L1PFHistograms(int selbin, int jetbin)
{
  //printf("deleteAODCaloJet_L1PFHistograms\n");
  hist_file_out[selbin]->cd();

  if(h_AODCaloJet_L1PFPt                    [selbin][jetbin]!=NULL)   h_AODCaloJet_L1PFPt                             [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFPtVar               [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFPtVar                          [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFEta                 [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFEta                            [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFPhi                 [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFPhi                            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_L1PFAlphaMax              [selbin][jetbin]!=NULL)   h_AODCaloJet_L1PFAlphaMax                       [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFAlphaMax2           [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFAlphaMax2                      [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFAlphaMaxPrime       [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFAlphaMaxPrime                  [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFAlphaMaxPrime2      [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFAlphaMaxPrime2                 [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFBeta                [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFBeta                           [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFBeta2               [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFBeta2                          [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFSumIP               [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFSumIP                          [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFSumIPSig            [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFSumIPSig                       [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFMedianIP            [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFMedianIP                       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_L1PFMedianLog10IPSig      [selbin][jetbin]!=NULL)   h_AODCaloJet_L1PFMedianLog10IPSig               [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFTrackAngle          [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFTrackAngle                     [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFLogTrackAngle       [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFLogTrackAngle                  [selbin][jetbin]->Delete(); 
  if(h_AODCaloJet_L1PFMedianLog10TrackAngle [selbin][jetbin]!=NULL)   h_AODCaloJet_L1PFMedianLog10TrackAngle          [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJet_L1PFTotalTrackAngle     [selbin][jetbin]!=NULL)   //h_AODCaloJet_L1PFTotalTrackAngle                [selbin][jetbin]->Delete(); 
  ///if(h_AODCaloJetAbsEta                   [selbin][jetbin]!=NULL)   //h_AODCaloJetAbsEta                         [selbin][jetbin]->Delete();
  ///if(h_AODCaloJetPtVarAbsEtaVar           [selbin][jetbin]!=NULL)   //h_AODCaloJetPtVarAbsEtaVar                 [selbin][jetbin]->Delete(); 
  
  return kTRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///                         For L1 Pre-firing test    END                                          ////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////



//----------------------------initAODCaloJetExtraHistograms
Bool_t analyzer_histograms::initAODCaloJetExtraHistograms( TString uncbin )
{

 // loop through jets and selections to initialize histograms in parllel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
  hist_file_out[i]->cd();
  unsigned int j; if(jetMultOn) j=0; else j=jetmultnames.size()-1;
  for(j; j<jetmultnames.size(); ++j){
    //deleteAODCaloJetExtraHistograms(i,j);
    TString hname_AODCaloJetAvfVx                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVx"                          + uncbin ;                          
    TString hname_AODCaloJetAvfVy                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVy"                          + uncbin ;                          
    TString hname_AODCaloJetAvfVz                         = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVz"                          + uncbin ;                          
    TString hname_AODCaloJetAvfVertexTotalChiSquared      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTotalChiSquared"       + uncbin ;       
    TString hname_AODCaloJetAvfVertexDegreesOfFreedom     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDegreesOfFreedom"      + uncbin ;      
    TString hname_AODCaloJetAvfVertexChi2NDoF             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexChi2NDoF"              + uncbin ;              
    TString hname_AODCaloJetAvfVertexDistanceToBeam       = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDistanceToBeam"        + uncbin ;        
    TString hname_AODCaloJetAvfVertexTransverseError      = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTransverseError"       + uncbin ;       
    TString hname_AODCaloJetAvfVertexTransverseSig        = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTransverseSig"         + uncbin ;         
    TString hname_AODCaloJetAvfVertexDeltaEta             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaEta"              + uncbin ;              
    TString hname_AODCaloJetAvfVertexDeltaPhi             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaPhi"              + uncbin ;              
    TString hname_AODCaloJetAvfVertexRecoilPt             = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexRecoilPt"              + uncbin ;              
    TString hname_AODCaloJetAvfVertexTrackMass            = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTrackMass"             + uncbin ;             
    TString hname_AODCaloJetAvfVertexTrackEnergy          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexTrackEnergy"           + uncbin ;           
    TString hname_AODCaloJetAvfBeamSpotDeltaPhi           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotDeltaPhi"            + uncbin ;            
    TString hname_AODCaloJetAvfBeamSpotRecoilPt           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotRecoilPt"            + uncbin ;            
    TString hname_AODCaloJetAvfBeamSpotMedianDeltaPhi     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotMedianDeltaPhi"      + uncbin ;      
    TString hname_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi= "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi" + uncbin ; 
    TString hname_AODCaloJetNCleanMatchedTracks           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetNCleanMatchedTracks"            + uncbin ;            
    TString hname_AODCaloJetSumHitsInFrontOfVert          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetSumHitsInFrontOfVert"           + uncbin ;           
    TString hname_AODCaloJetSumMissHitsAfterVert          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetSumMissHitsAfterVert"           + uncbin ;           
    TString hname_AODCaloJetHitsInFrontOfVertPerTrack     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetHitsInFrontOfVertPerTrack"      + uncbin ;      
    TString hname_AODCaloJetMissHitsAfterVertPerTrack     = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetMissHitsAfterVertPerTrack"      + uncbin ;      
    TString hname_AODCaloJetAvfDistToPV                   = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfDistToPV"                    + uncbin ;                    
    TString hname_AODCaloJetAvfVertexDeltaZtoPV           = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaZtoPV"            + uncbin ;            
    TString hname_AODCaloJetAvfVertexDeltaZtoPV2          = "h_"+selbinnames[i]+"_"+jetmultnames[j]+"_AODCaloJetAvfVertexDeltaZtoPV2"           + uncbin ;           

    h_AODCaloJetAvfVx                          [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVx                          , "AODCaloJetAvfVx                         ", 30, -3, 3 ); 
    h_AODCaloJetAvfVy                          [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVy                          , "AODCaloJetAvfVy                         ", 30, -3, 3 ); 
    h_AODCaloJetAvfVz                          [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVz                          , "AODCaloJetAvfVz                         ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTotalChiSquared       [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTotalChiSquared       , "AODCaloJetAvfVertexTotalChiSquared      ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDegreesOfFreedom      [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDegreesOfFreedom      , "AODCaloJetAvfVertexDegreesOfFreedom     ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexChi2NDoF              [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexChi2NDoF              , "AODCaloJetAvfVertexChi2NDoF             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDistanceToBeam        [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDistanceToBeam        , "AODCaloJetAvfVertexDistanceToBeam       ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTransverseError       [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTransverseError       , "AODCaloJetAvfVertexTransverseError      ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTransverseSig         [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTransverseSig         , "AODCaloJetAvfVertexTransverseSig        ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaEta              [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaEta              , "AODCaloJetAvfVertexDeltaEta             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaPhi              [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaPhi              , "AODCaloJetAvfVertexDeltaPhi             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexRecoilPt              [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexRecoilPt              , "AODCaloJetAvfVertexRecoilPt             ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTrackMass             [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTrackMass             , "AODCaloJetAvfVertexTrackMass            ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexTrackEnergy           [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexTrackEnergy           , "AODCaloJetAvfVertexTrackEnergy          ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotDeltaPhi            [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotDeltaPhi            , "AODCaloJetAvfBeamSpotDeltaPhi           ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotRecoilPt            [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotRecoilPt            , "AODCaloJetAvfBeamSpotRecoilPt           ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotMedianDeltaPhi      , "AODCaloJetAvfBeamSpotMedianDeltaPhi     ", 30, -3, 3 ); 
    h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi , "AODCaloJetAvfBeamSpotLog10MedianDeltaPhi", 30, -3, 3 ); 
    h_AODCaloJetNCleanMatchedTracks            [i][j] = initSingleHistogramTH1F( hname_AODCaloJetNCleanMatchedTracks            , "AODCaloJetNCleanMatchedTracks           ", 20, 0, 20 ); 
    h_AODCaloJetSumHitsInFrontOfVert           [i][j] = initSingleHistogramTH1F( hname_AODCaloJetSumHitsInFrontOfVert           , "AODCaloJetSumHitsInFrontOfVert          ", 30, -3, 3 ); 
    h_AODCaloJetSumMissHitsAfterVert           [i][j] = initSingleHistogramTH1F( hname_AODCaloJetSumMissHitsAfterVert           , "AODCaloJetSumMissHitsAfterVert          ", 30, -3, 3 ); 
    h_AODCaloJetHitsInFrontOfVertPerTrack      [i][j] = initSingleHistogramTH1F( hname_AODCaloJetHitsInFrontOfVertPerTrack      , "AODCaloJetHitsInFrontOfVertPerTrack     ", 30, -3, 3 ); 
    h_AODCaloJetMissHitsAfterVertPerTrack      [i][j] = initSingleHistogramTH1F( hname_AODCaloJetMissHitsAfterVertPerTrack      , "AODCaloJetMissHitsAfterVertPerTrack     ", 30, -3, 3 ); 
    h_AODCaloJetAvfDistToPV                    [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfDistToPV                    , "AODCaloJetAvfDistToPV                   ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaZtoPV            [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaZtoPV            , "AODCaloJetAvfVertexDeltaZtoPV           ", 30, -3, 3 ); 
    h_AODCaloJetAvfVertexDeltaZtoPV2           [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAvfVertexDeltaZtoPV2           , "AODCaloJetAvfVertexDeltaZtoPV2          ", 30, -3, 3 ); 

   } //   for(unsigned int i=0; i<selbinnames.size(); ++i){
  } //  for(unsigned int j=0; j<jetmultnames.size(); ++j){
 return kTRUE;
} //initAODCaloJetHistograms

//----------------------------fillAODCaloJetExtraHistograms
Bool_t analyzer_histograms::fillAODCaloJetExtraHistograms(Float_t weight, int selbin, int jetbin)
{

  hist_file_out[selbin]->cd();

  if(jetmultnames.at(jetbin) == "AllJets"){
    for(unsigned int i =0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i];
      h_AODCaloJetAvfVx                          [selbin][jetbin]->Fill( AODCaloJetAvfVx                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVy                          [selbin][jetbin]->Fill( AODCaloJetAvfVy                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVz                          [selbin][jetbin]->Fill( AODCaloJetAvfVz                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin]->Fill( AODCaloJetAvfVertexTotalChiSquared       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin]->Fill( AODCaloJetAvfVertexDegreesOfFreedom      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin]->Fill( AODCaloJetAvfVertexChi2NDoF              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin]->Fill( AODCaloJetAvfVertexDistanceToBeam        ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin]->Fill( AODCaloJetAvfVertexTransverseError       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin]->Fill( AODCaloJetAvfVertexTransverseSig         ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaEta              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaPhi              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin]->Fill( AODCaloJetAvfVertexRecoilPt              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin]->Fill( AODCaloJetAvfVertexTrackMass             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin]->Fill( AODCaloJetAvfVertexTrackEnergy           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotDeltaPhi            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotRecoilPt            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotMedianDeltaPhi      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotLog10MedianDeltaPhi ->at( aodcalojetindex ), weight );  
      h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin]->Fill( AODCaloJetNCleanMatchedTracks            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin]->Fill( AODCaloJetSumHitsInFrontOfVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin]->Fill( AODCaloJetSumMissHitsAfterVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin]->Fill( AODCaloJetHitsInFrontOfVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin]->Fill( AODCaloJetMissHitsAfterVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfDistToPV                    [selbin][jetbin]->Fill( AODCaloJetAvfDistToPV                    ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaZtoPV            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaZtoPV2           ->at( aodcalojetindex ), weight );  
    }
  }
  else{
    if( jetbin < (int)aodcalojet_list.size() ){
      int aodcalojetindex = aodcalojet_list[jetbin];
      h_AODCaloJetAvfVx                          [selbin][jetbin]->Fill( AODCaloJetAvfVx                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVy                          [selbin][jetbin]->Fill( AODCaloJetAvfVy                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVz                          [selbin][jetbin]->Fill( AODCaloJetAvfVz                          ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin]->Fill( AODCaloJetAvfVertexTotalChiSquared       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin]->Fill( AODCaloJetAvfVertexDegreesOfFreedom      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin]->Fill( AODCaloJetAvfVertexChi2NDoF              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin]->Fill( AODCaloJetAvfVertexDistanceToBeam        ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin]->Fill( AODCaloJetAvfVertexTransverseError       ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin]->Fill( AODCaloJetAvfVertexTransverseSig         ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaEta              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaPhi              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin]->Fill( AODCaloJetAvfVertexRecoilPt              ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin]->Fill( AODCaloJetAvfVertexTrackMass             ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin]->Fill( AODCaloJetAvfVertexTrackEnergy           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotDeltaPhi            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotRecoilPt            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotMedianDeltaPhi      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin]->Fill( AODCaloJetAvfBeamSpotLog10MedianDeltaPhi ->at( aodcalojetindex ), weight );  
      h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin]->Fill( AODCaloJetNCleanMatchedTracks            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin]->Fill( AODCaloJetSumHitsInFrontOfVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin]->Fill( AODCaloJetSumMissHitsAfterVert           ->at( aodcalojetindex ), weight );  
      h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin]->Fill( AODCaloJetHitsInFrontOfVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin]->Fill( AODCaloJetMissHitsAfterVertPerTrack      ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfDistToPV                    [selbin][jetbin]->Fill( AODCaloJetAvfDistToPV                    ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaZtoPV            ->at( aodcalojetindex ), weight );  
      h_AODCaloJetAvfVertexDeltaZtoPV2           [selbin][jetbin]->Fill( AODCaloJetAvfVertexDeltaZtoPV2           ->at( aodcalojetindex ), weight );  
    }
  }

 return kTRUE;
} //end fill histograms


//----------------------------writeAODCaloJetHistograms
Bool_t analyzer_histograms::writeAODCaloJetExtraHistograms(int selbin, int jetbin)
{
 //printf("writeAODCaloJetHistograms\n");
  hist_file_out[selbin]->cd();
  h_AODCaloJetAvfVx                          [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVy                          [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVz                          [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin]->Write(); 
  h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin]->Write(); 
  h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin]->Write(); 
  h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin]->Write(); 
  h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin]->Write(); 
  h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfDistToPV                    [selbin][jetbin]->Write(); 
  h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin]->Write(); 
  return kTRUE;
}


//----------------------------deleteAODCaloJetExtraHistograms
Bool_t analyzer_histograms::deleteAODCaloJetExtraHistograms(int selbin, int jetbin)
{
  std::cout << "selbin " << selbin << " jetbin " << jetbin << std::endl;
  //printf("deleteAODCaloJetExtraHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_AODCaloJetAvfVx                         [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVx                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVy                         [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVy                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVz                         [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVz                          [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexTotalChiSquared      [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexTotalChiSquared       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexDegreesOfFreedom     [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexDegreesOfFreedom      [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexChi2NDoF             [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexChi2NDoF              [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexDistanceToBeam       [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexDistanceToBeam        [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexTransverseError      [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexTransverseError       [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexTransverseSig        [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexTransverseSig         [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexDeltaEta             [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexDeltaEta              [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexDeltaPhi             [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexDeltaPhi              [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexRecoilPt             [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexRecoilPt              [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexTrackMass            [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexTrackMass             [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexTrackEnergy          [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexTrackEnergy           [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfBeamSpotDeltaPhi           [selbin][jetbin]!=NULL)    h_AODCaloJetAvfBeamSpotDeltaPhi            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfBeamSpotRecoilPt           [selbin][jetbin]!=NULL)    h_AODCaloJetAvfBeamSpotRecoilPt            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfBeamSpotMedianDeltaPhi     [selbin][jetbin]!=NULL)    h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi[selbin][jetbin]!=NULL)    h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetNCleanMatchedTracks           [selbin][jetbin]!=NULL)    h_AODCaloJetNCleanMatchedTracks            [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetSumHitsInFrontOfVert          [selbin][jetbin]!=NULL)    h_AODCaloJetSumHitsInFrontOfVert           [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetSumMissHitsAfterVert          [selbin][jetbin]!=NULL)    h_AODCaloJetSumMissHitsAfterVert           [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetHitsInFrontOfVertPerTrack     [selbin][jetbin]!=NULL)    h_AODCaloJetHitsInFrontOfVertPerTrack      [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetMissHitsAfterVertPerTrack     [selbin][jetbin]!=NULL)    h_AODCaloJetMissHitsAfterVertPerTrack      [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfDistToPV                   [selbin][jetbin]!=NULL)    h_AODCaloJetAvfDistToPV                    [selbin][jetbin]->Delete(); 
  if(h_AODCaloJetAvfVertexDeltaZtoPV           [selbin][jetbin]!=NULL)    h_AODCaloJetAvfVertexDeltaZtoPV            [selbin][jetbin]->Delete(); 
  return kTRUE;
}



//----------------------------initAODCaloJetTagHistograms
Bool_t analyzer_histograms::initAODCaloJetTagHistograms( TString uncbin )
{

 // loop through jets and selections to initialize histograms in parallel (series)
 for(unsigned int i=0; i<selbinnames.size(); ++i){
   hist_file_out[i]->cd();

  for(unsigned int j=0; j<tagmultnames.size(); ++j){
   //deleteAODCaloJetTagHistograms(i,j);
   TString hname_AODCaloJetPt_Tag0                      = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPt_Tag0"                  + uncbin ;
   TString hname_AODCaloJetPtVar_Tag0                   = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPtVar_Tag0"               + uncbin ;
   TString hname_AODCaloJetMinDR_Tag0                   = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetMinDR_Tag0"               + uncbin ;
   TString hname_AODCaloJetCSV_Tag0                     = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetCSV_Tag0"                 + uncbin ;
   TString hname_AODCaloJetPartonFlavour_Tag0           = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPartonFlavour_Tag0"       + uncbin ;
   TString hname_AODCaloJetAbsEta_Tag0                  = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetAbsEta_Tag0"              + uncbin ;
   TString hname_AODCaloJetNCleanMatchedTracks_Tag0     = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetNCleanMatchedTracks_Tag0" + uncbin ;
   TString hname_AODCaloJetPtVarAbsEtaVar_Tag0          = "h_"+selbinnames[i]+"_"+tagmultnames[j]+"_AODCaloJetPtVarAbsEtaVar_Tag0"      + uncbin ;

   h_AODCaloJetPt_Tag0                       [i][j] = initSingleHistogramTH1F( hname_AODCaloJetPt_Tag0                       , "AODCaloJetPt_Tag0                      ", 50, 0, 500); 
   h_AODCaloJetMinDR_Tag0                    [i][j] = initSingleHistogramTH1F( hname_AODCaloJetMinDR_Tag0                    , "AODCaloJetMinDR_Tag0                   ", 30, 0, 5); 
   h_AODCaloJetCSV_Tag0                      [i][j] = initSingleHistogramTH1F( hname_AODCaloJetCSV_Tag0                      , "AODCaloJetCSV_Tag0                     ", 24, -.1, 1.1); 
   h_AODCaloJetPartonFlavour_Tag0            [i][j] = initSingleHistogramTH1F( hname_AODCaloJetPartonFlavour_Tag0            , "AODCaloJetPartonFlavour_Tag0           ", 35, -10, 25); 
   h_AODCaloJetAbsEta_Tag0                   [i][j] = initSingleHistogramTH1F( hname_AODCaloJetAbsEta_Tag0                   , "AODCaloJetAbsEta_Tag0                  ", 4, 0, 3);
   h_AODCaloJetNCleanMatchedTracks_Tag0      [i][j] = initSingleHistogramTH1F( hname_AODCaloJetNCleanMatchedTracks_Tag0      , "AODCaloJetNCleanMatchedTracks_Tag0     ", 20, 0, 20); 

   const int Pt_n_xbins = 10;
   float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
   h_AODCaloJetPtVar_Tag0                    [i][j] = initSingleHistogramTH1F( hname_AODCaloJetPtVar_Tag0 , "AODCaloJetPtVar_Tag0", Pt_n_xbins, Pt_xbins);

   const int AbsEta_n_bins = 2;
   float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
   h_AODCaloJetPtVarAbsEtaVar_Tag0           [i][j] = initSingleHistogramTH2F(hname_AODCaloJetPtVarAbsEtaVar_Tag0, "AODCaloJetPtVarAbsEtaVar_Tag0", Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins );

  } //   for(unsigned int i=0; i<selbinnames.size(); ++i){
 } //  for(unsigned int j=0; j<tagmultnames.size(); ++j){
 return kTRUE;
} //initAODCaloJetTagHistograms



//----------------------------fillAODCaloJetTagHistograms
Bool_t analyzer_histograms::fillAODCaloJetTagHistograms(Float_t weight, int selbin, int tagbin)
{
  hist_file_out[selbin]->cd();

  if(tagmultnames.at(tagbin) == "AllTags"){
    for(unsigned int i =0; i<taggedjet_list.size(); i++){
      int tagindex = taggedjet_list[i];
      h_AODCaloJetPt_Tag0                            [selbin][tagbin]->Fill( AODCaloJetPt->at(                        tagindex ), weight );  
      h_AODCaloJetPtVar_Tag0                         [selbin][tagbin]->Fill( AODCaloJetPt->at(                        tagindex ), weight );  
      h_AODCaloJetMinDR_Tag0                         [selbin][tagbin]->Fill( aodcalojet_minDR_list.at(                tagindex ), weight );  
      h_AODCaloJetCSV_Tag0                           [selbin][tagbin]->Fill( aodcalojet_matchedCSV_list.at(           tagindex ), weight );  
      h_AODCaloJetPartonFlavour_Tag0                 [selbin][tagbin]->Fill( aodcalojet_matchedPartonFlavour_list.at( tagindex ), weight );  
      h_AODCaloJetAbsEta_Tag0                        [selbin][tagbin]->Fill( fabs(AODCaloJetEta->at(                  tagindex )), weight );
      h_AODCaloJetNCleanMatchedTracks_Tag0           [selbin][tagbin]->Fill( AODCaloJetNCleanMatchedTracks->at(       tagindex ), weight );  
      h_AODCaloJetPtVarAbsEtaVar_Tag0                [selbin][tagbin]->Fill( AODCaloJetPt->at(tagindex), fabs(AODCaloJetEta->at( tagindex )), weight );  
    }
  }
  else {
    if( tagbin < (int)taggedjet_list.size() ){
      int tagindex = taggedjet_list[tagbin];
      h_AODCaloJetPt_Tag0                            [selbin][tagbin]->Fill( AODCaloJetPt->at(                        tagindex ), weight );  
      h_AODCaloJetPtVar_Tag0                         [selbin][tagbin]->Fill( AODCaloJetPt->at(                        tagindex ), weight );  
      h_AODCaloJetMinDR_Tag0                         [selbin][tagbin]->Fill( aodcalojet_minDR_list.at(                tagindex ), weight );  
      h_AODCaloJetCSV_Tag0                           [selbin][tagbin]->Fill( aodcalojet_matchedCSV_list.at(           tagindex ), weight );  
      h_AODCaloJetPartonFlavour_Tag0                 [selbin][tagbin]->Fill( aodcalojet_matchedPartonFlavour_list.at( tagindex ), weight );  
      h_AODCaloJetAbsEta_Tag0                        [selbin][tagbin]->Fill( fabs( AODCaloJetEta->at(                 tagindex ) ), weight );
      h_AODCaloJetNCleanMatchedTracks_Tag0           [selbin][tagbin]->Fill( AODCaloJetNCleanMatchedTracks->at(       tagindex ), weight );  
      h_AODCaloJetPtVarAbsEtaVar_Tag0                [selbin][tagbin]->Fill( AODCaloJetPt->at(tagindex), fabs(AODCaloJetEta->at( tagindex )), weight );  
    }
  }
  
  return kTRUE;
} //end fill histograms


//----------------------------writeAODCaloJetTagHistograms
Bool_t analyzer_histograms::writeAODCaloJetTagHistograms(int selbin, int tagbin)
{
  hist_file_out[selbin]->cd();

  //printf("writeAODCaloJetTagHistograms\n");
  h_AODCaloJetPt_Tag0                       [selbin][tagbin]->Write(); 
  h_AODCaloJetPtVar_Tag0                    [selbin][tagbin]->Write(); 
  h_AODCaloJetMinDR_Tag0                    [selbin][tagbin]->Write(); 
  h_AODCaloJetCSV_Tag0                      [selbin][tagbin]->Write(); 
  h_AODCaloJetPartonFlavour_Tag0            [selbin][tagbin]->Write(); 
  h_AODCaloJetAbsEta_Tag0                   [selbin][tagbin]->Write(); 
  h_AODCaloJetNCleanMatchedTracks_Tag0      [selbin][tagbin]->Write(); 
  h_AODCaloJetPtVarAbsEtaVar_Tag0           [selbin][tagbin]->Write(); 

 return kTRUE;
}


//----------------------------deleteAODCaloJetTagHistograms
Bool_t analyzer_histograms::deleteAODCaloJetTagHistograms(int selbin, int tagbin)
{
  std::cout << "selbin " << selbin << " tagbin " << tagbin << std::endl;
  hist_file_out[selbin]->cd();
  //printf("deleteAODCaloJetTagHistograms\n");
  if(h_AODCaloJetPt_Tag0                  [selbin][tagbin]!=NULL)    h_AODCaloJetPt_Tag0                       [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetPtVar_Tag0               [selbin][tagbin]!=NULL)    h_AODCaloJetPtVar_Tag0                    [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetMinDR_Tag0               [selbin][tagbin]!=NULL)    h_AODCaloJetMinDR_Tag0                    [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetCSV_Tag0                 [selbin][tagbin]!=NULL)    h_AODCaloJetCSV_Tag0                      [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetPartonFlavour_Tag0       [selbin][tagbin]!=NULL)    h_AODCaloJetPartonFlavour_Tag0            [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetAbsEta_Tag0              [selbin][tagbin]!=NULL)    h_AODCaloJetAbsEta_Tag0                   [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetNCleanMatchedTracks_Tag0 [selbin][tagbin]!=NULL)    h_AODCaloJetNCleanMatchedTracks_Tag0      [selbin][tagbin]->Delete(); 
  if(h_AODCaloJetPtVarAbsEtaVar_Tag0      [selbin][tagbin]!=NULL)    h_AODCaloJetPtVarAbsEtaVar_Tag0           [selbin][tagbin]->Delete(); 
  return kTRUE;
}


// Cutflow section

//----------------------------initCutflowHistograms
Bool_t analyzer_histograms::initCutflowHistograms( TString uncbin ){

 for(unsigned int i=0; i<selbinnames.size(); ++i){

  //deleteCutflowHistograms(i);
  TString hname_Cutflow    = "h_"+selbinnames[i]+"_Cutflow"   +uncbin; 
  TString hname_Onecut     = "h_"+selbinnames[i]+"_Onecut"    +uncbin; 
  TString hname_NMinus     = "h_"+selbinnames[i]+"_NMinus"    +uncbin; 
  TString hname_RawCutflow = "h_"+selbinnames[i]+"_RawCutflow"+uncbin; 
  TString hname_RawOnecut  = "h_"+selbinnames[i]+"_RawOnecut" +uncbin; 
  TString hname_RawNMinus  = "h_"+selbinnames[i]+"_RawNMinus" +uncbin; 

  h_Cutflow    [i] = initSingleHistogramTH1F( hname_Cutflow , "Cutflow", 10,0,10);
  h_Onecut     [i] = initSingleHistogramTH1F( hname_Onecut  , "Onecut ", 10,0,10);
  h_NMinus     [i] = initSingleHistogramTH1F( hname_NMinus  , "NMinus ", 10,0,10); 
  h_RawCutflow [i] = initSingleHistogramTH1F( hname_RawCutflow , "RawCutflow", 10,0,10);
  h_RawOnecut  [i] = initSingleHistogramTH1F( hname_RawOnecut  , "RawOnecut ", 10,0,10);
  h_RawNMinus  [i] = initSingleHistogramTH1F( hname_RawNMinus  , "RawNMinus ", 10,0,10); 
 }
 return kTRUE;
}

//----------------------------fillCutflowHistograms
Bool_t analyzer_histograms::fillCutflowHistograms(Float_t weight, int selbin, Int_t localselint, Int_t localselkey)
{

 h_Cutflow[selbin] ->Fill( 1, weight );
 h_Onecut[selbin]  ->Fill( 1, weight );
 h_NMinus[selbin]  ->Fill( 1, weight );
 h_RawCutflow[selbin] ->Fill( 1 );
 h_RawOnecut[selbin]  ->Fill( 1 );
 h_RawNMinus[selbin]  ->Fill( 1 );

 Bool_t notdead = kTRUE;
 Int_t nmbits = 0;

 // for now all selections are less than 8 long
 // selection integers (bitset) start with 1/0 if pass all cuts
 // then 1/0 for each individual cut
 for( unsigned int i=1; i<8; ++i){
  // ignore the first bit, then keep checking if we ever get 0
  notdead = notdead && ( localselint>>(i) & 1 ) ;

  // bit i and all preceding bits it pass
  if( notdead ){
   h_Cutflow[selbin]    ->Fill( 1+i, weight );
   h_RawCutflow[selbin] ->Fill( 1+i );
  }
  // just bit i passes
  if( localselint>>(i) & 1 ){
   h_Onecut[selbin]    ->Fill( 1+i, weight );
   h_RawOnecut[selbin] ->Fill( 1+i );
  }
  // everything other than bit i passes
   // bit structure is (passAll)(sel1)(sel2)(sel3)(sel4)(sel5)000
   // nmbits is 011111000 ( localselkey ) except flip bit i to 0
   // then AND this with selection bitset to get comparison bitset
   // then if comp bitset == nmbits we know
   // selection bitset passed all cuts, ignoring cut i
  nmbits = localselkey;
  nmbits &= ~(1 << i);
  Int_t compbits = localselint & nmbits;

  //std::cout<<"\n";
  //std::cout<<" nmbits: "<<nmbits<<" =    "; 
  //for(unsigned int i=0; i<8; ++i){
  // std::cout<< ( (nmbits>>i)&1 );
  //}
  //std::cout<<"\n";
  //std::cout<<" localselint: "<<localselint<<" =    "; 
  //for(unsigned int i=0; i<8; ++i){
  // std::cout<< ( (localselint>>i)&1 );
  //}
  //std::cout<<"\n";
  //std::cout<<" cmpbit: "<<compbits<<" =    "; 
  //for(unsigned int i=0; i<8; ++i){
  // std::cout<< ( (compbits>>i)&1 );
  //}
  //std::cout<<"\n";

  if( nmbits==compbits ){
   h_NMinus[selbin]    ->Fill( 1+i, weight );
   h_RawNMinus[selbin] ->Fill( 1+i );
  }

 }

 return kTRUE;
}

//----------------------------writeCutflowHistograms
Bool_t analyzer_histograms::writeCutflowHistograms(int selbin)
{
 h_Cutflow    [selbin]->Write();
 h_Onecut     [selbin]->Write();
 h_RawCutflow [selbin]->Write();
 h_RawOnecut  [selbin]->Write();
 h_NMinus     [selbin]->Write();
 h_RawNMinus  [selbin]->Write();
 return kTRUE;
}

//----------------------------deleteCutflowHistograms
Bool_t analyzer_histograms::deleteCutflowHistograms(int selbin)
{
  //printf("deleteCutflowHistograms\n");
  if(h_Cutflow   [selbin]!=NULL)  h_Cutflow    [selbin]->Delete();
  if(h_Onecut    [selbin]!=NULL)  h_Onecut     [selbin]->Delete();
  if(h_RawCutflow[selbin]!=NULL)  h_RawCutflow [selbin]->Delete();
  if(h_RawOnecut [selbin]!=NULL)  h_RawOnecut  [selbin]->Delete();
  if(h_NMinus    [selbin]!=NULL)  h_NMinus     [selbin]->Delete();
  if(h_RawNMinus [selbin]!=NULL)  h_RawNMinus  [selbin]->Delete();
  return kTRUE;
}


////////////////////////////
// Trigger Efficiencies
////////////////////////////

//----------------------------initTTOCHistograms
Bool_t analyzer_histograms::initTTOCHistograms( TString uncbin ){

 for(unsigned int i=0; i<selbinnames.size(); ++i){
   //deleteTTOCHistograms(i);
   //Basic histograms
   TString hname_TTOCMu1Pt           = "h_"+selbinnames[i]+"_TTOCMu1Pt"      +uncbin; 
   TString hname_TTOCMu2Pt           = "h_"+selbinnames[i]+"_TTOCMu2Pt"      +uncbin; 
   TString hname_TTOCMuPt            = "h_"+selbinnames[i]+"_TTOCMuPt"       +uncbin; 
   TString hname_TTOCMu1Eta          = "h_"+selbinnames[i]+"_TTOCMu1Eta"     +uncbin; 
   TString hname_TTOCMu2Eta          = "h_"+selbinnames[i]+"_TTOCMu2Eta"     +uncbin; 
   TString hname_TTOCMuEta           = "h_"+selbinnames[i]+"_TTOCMuEta"      +uncbin; 
   TString hname_TTOCEle1Pt          = "h_"+selbinnames[i]+"_TTOCEle1Pt"     +uncbin; 
   TString hname_TTOCEle2Pt          = "h_"+selbinnames[i]+"_TTOCEle2Pt"     +uncbin; 
   TString hname_TTOCElePt           = "h_"+selbinnames[i]+"_TTOCElePt"      +uncbin; 
   TString hname_TTOCEle1Eta         = "h_"+selbinnames[i]+"_TTOCEle1Eta"    +uncbin; 
   TString hname_TTOCEle2Eta         = "h_"+selbinnames[i]+"_TTOCEle2Eta"    +uncbin; 
   TString hname_TTOCEleEta          = "h_"+selbinnames[i]+"_TTOCEleEta"     +uncbin; 
   TString hname_TTOCEMu_ElePt       = "h_"+selbinnames[i]+"_TTOCEMu_ElePt"  +uncbin;
   TString hname_TTOCEMu_MuPt        = "h_"+selbinnames[i]+"_TTOCEMu_MuPt"   +uncbin;
   TString hname_TTOCEMuPt           = "h_"+selbinnames[i]+"_TTOCEMuPt"      +uncbin;
   TString hname_TTOCEMu_EleEta      = "h_"+selbinnames[i]+"_TTOCEMu_EleEta" +uncbin;
   TString hname_TTOCEMu_MuEta       = "h_"+selbinnames[i]+"_TTOCEMu_MuEta"  +uncbin;
   TString hname_TTOCEMuEta          = "h_"+selbinnames[i]+"_TTOCEMuEta"     +uncbin;
   TString hname_TTOCMuE_ElePt       = "h_"+selbinnames[i]+"_TTOCMuE_ElePt"  +uncbin;
   TString hname_TTOCMuE_MuPt        = "h_"+selbinnames[i]+"_TTOCMuE_MuPt"   +uncbin;
   TString hname_TTOCMuEPt           = "h_"+selbinnames[i]+"_TTOCMuEPt"      +uncbin;
   TString hname_TTOCMuE_EleEta      = "h_"+selbinnames[i]+"_TTOCMuE_EleEta" +uncbin;
   TString hname_TTOCMuE_MuEta       = "h_"+selbinnames[i]+"_TTOCMuE_MuEta"  +uncbin;
   TString hname_TTOCMuEEta          = "h_"+selbinnames[i]+"_TTOCMuEEta"     +uncbin;
   TString hname_TTOCPhoPt           = "h_"+selbinnames[i]+"_TTOCPhoPt"      +uncbin;
   TString hname_TTOCPhoEta          = "h_"+selbinnames[i]+"_TTOCPhoEta"     +uncbin;
   //-------trigger specific
   //Double muon
   TString hname_TTOCTriggerDMu1Pt        = "h_"+selbinnames[i]+"_TTOCMuTriggerDMu1Pt"        +uncbin; 
   TString hname_TTOCTriggerDMu2Pt        = "h_"+selbinnames[i]+"_TTOCMuTriggerDMu2Pt"        +uncbin; 
   TString hname_TTOCTriggerDMuPt         = "h_"+selbinnames[i]+"_TTOCMuTriggerDMuPt"         +uncbin; 
   TString hname_TTOCTriggerDMu1Eta       = "h_"+selbinnames[i]+"_TTOCMuTriggerDMu1Eta"       +uncbin; 
   TString hname_TTOCTriggerDMu2Eta       = "h_"+selbinnames[i]+"_TTOCMuTriggerDMu2Eta"       +uncbin; 
   TString hname_TTOCTriggerDMuEta        = "h_"+selbinnames[i]+"_TTOCMuTriggerDMuEta"        +uncbin; 
   TString hname_TTOCTriggerDTkMu1Pt      = "h_"+selbinnames[i]+"_TTOCMuTriggerDTkMu1Pt"      +uncbin; 
   TString hname_TTOCTriggerDTkMu2Pt      = "h_"+selbinnames[i]+"_TTOCMuTriggerDTkMu2Pt"      +uncbin; 
   TString hname_TTOCTriggerDTkMu1Eta     = "h_"+selbinnames[i]+"_TTOCMuTriggerDTkMu1Eta"     +uncbin; 
   TString hname_TTOCTriggerDTkMu2Eta     = "h_"+selbinnames[i]+"_TTOCMuTriggerDTkMu2Eta"     +uncbin; 
   TString hname_TTOCTriggerNoDZMu1Pt     = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZMu1Pt"     +uncbin; 
   TString hname_TTOCTriggerNoDZMu2Pt     = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZMu2Pt"     +uncbin; 
   TString hname_TTOCTriggerNoDZMu1Eta    = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZMu1Eta"    +uncbin; 
   TString hname_TTOCTriggerNoDZMu2Eta    = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZMu2Eta"    +uncbin; 
   TString hname_TTOCTriggerNoDZTkMu1Pt   = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZTkMu1Pt"   +uncbin; 
   TString hname_TTOCTriggerNoDZTkMu2Pt   = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZTkMu2Pt"   +uncbin; 
   TString hname_TTOCTriggerNoDZTkMu1Eta  = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZTkMu1Eta"  +uncbin; 
   TString hname_TTOCTriggerNoDZTkMu2Eta  = "h_"+selbinnames[i]+"_TTOCMuTriggerNoDZTkMu2Eta"  +uncbin; 
   //--Single Mu
   TString hname_TTOCTrigger22MuPt        = "h_"+selbinnames[i]+"_TTOCMuTrigger22MuPt"        +uncbin; 
   TString hname_TTOCTrigger22MuEta       = "h_"+selbinnames[i]+"_TTOCMuTrigger22MuEta"       +uncbin; 
   TString hname_TTOCTrigger22TkMuPt      = "h_"+selbinnames[i]+"_TTOCMuTrigger22TkMuPt"      +uncbin; 
   TString hname_TTOCTrigger22TkMuEta     = "h_"+selbinnames[i]+"_TTOCMuTrigger22TkMuEta"     +uncbin; 
   TString hname_TTOCTrigger24MuPt        = "h_"+selbinnames[i]+"_TTOCMuTrigger24MuPt"        +uncbin; 
   TString hname_TTOCTrigger24MuEta       = "h_"+selbinnames[i]+"_TTOCMuTrigger24MuEta"       +uncbin; 
   TString hname_TTOCTrigger24TkMuPt      = "h_"+selbinnames[i]+"_TTOCMuTrigger24TkMuPt"      +uncbin; 
   TString hname_TTOCTrigger24TkMuEta     = "h_"+selbinnames[i]+"_TTOCMuTrigger24TkMuEta"     +uncbin; 
   //Double Electron
   TString hname_TTOCTrigger23DEle1Pt     = "h_"+selbinnames[i]+"_TTOCEleTrigger23DEle1Pt"    +uncbin; 
   TString hname_TTOCTrigger23DEle2Pt     = "h_"+selbinnames[i]+"_TTOCEleTrigger23DEle2Pt"    +uncbin; 
   TString hname_TTOCTrigger23DElePt      = "h_"+selbinnames[i]+"_TTOCEleTrigger23DElePt"     +uncbin; 
   TString hname_TTOCTrigger23DEle1Eta    = "h_"+selbinnames[i]+"_TTOCEleTrigger23DEle1Eta"   +uncbin; 
   TString hname_TTOCTrigger23DEle2Eta    = "h_"+selbinnames[i]+"_TTOCEleTrigger23DEle2Eta"   +uncbin; 
   TString hname_TTOCTrigger23DEleEta     = "h_"+selbinnames[i]+"_TTOCEleTrigger23DEleEta"    +uncbin; 
   TString hname_TTOCTrigger17DEle1Pt     = "h_"+selbinnames[i]+"_TTOCEleTrigger17DEle1Pt"    +uncbin; 
   TString hname_TTOCTrigger17DEle2Pt     = "h_"+selbinnames[i]+"_TTOCEleTrigger17DEle2Pt"    +uncbin; 
   TString hname_TTOCTrigger17DEle1Eta    = "h_"+selbinnames[i]+"_TTOCEleTrigger17DEle1Eta"   +uncbin; 
   TString hname_TTOCTrigger17DEle2Eta    = "h_"+selbinnames[i]+"_TTOCEleTrigger17DEle2Eta"   +uncbin; 
   //-------------Single Electron
   TString hname_TTOCTrigger23ElePt       = "h_"+selbinnames[i]+"_TTOCEleTrigger23ElePt"      +uncbin; 
   TString hname_TTOCTrigger23EleEta      = "h_"+selbinnames[i]+"_TTOCEleTrigger23EleEta"     +uncbin; 
   TString hname_TTOCTrigger27ElePt       = "h_"+selbinnames[i]+"_TTOCEleTrigger27ElePt"      +uncbin; 
   TString hname_TTOCTrigger27EleEta      = "h_"+selbinnames[i]+"_TTOCEleTrigger27EleEta"     +uncbin; 
   
   TString hname_TTOCTriggerEMu_ElePt     = "h_"+selbinnames[i]+"_TTOCTriggerEMu_ElePt"       +uncbin;
   TString hname_TTOCTriggerEMu_MuPt      = "h_"+selbinnames[i]+"_TTOCTriggerEMu_MuPt"        +uncbin;
   TString hname_TTOCTriggerEMuPt         = "h_"+selbinnames[i]+"_TTOCTriggerEMuPt"           +uncbin;
   TString hname_TTOCTriggerEMu_EleEta    = "h_"+selbinnames[i]+"_TTOCTriggerEMu_EleEta"      +uncbin;
   TString hname_TTOCTriggerEMu_MuEta     = "h_"+selbinnames[i]+"_TTOCTriggerEMu_MuEta"       +uncbin;
   TString hname_TTOCTriggerEMuEta        = "h_"+selbinnames[i]+"_TTOCTriggerEMuEta"          +uncbin;
   TString hname_TTOCTriggerMuE_ElePt     = "h_"+selbinnames[i]+"_TTOCTriggerMuE_ElePt"       +uncbin;
   TString hname_TTOCTriggerMuE_MuPt      = "h_"+selbinnames[i]+"_TTOCTriggerMuE_MuPt"        +uncbin;
   TString hname_TTOCTriggerMuEPt         = "h_"+selbinnames[i]+"_TTOCTriggerMuEPt"           +uncbin;
   TString hname_TTOCTriggerMuE_EleEta    = "h_"+selbinnames[i]+"_TTOCTriggerMuE_EleEta"      +uncbin;
   TString hname_TTOCTriggerMuE_MuEta     = "h_"+selbinnames[i]+"_TTOCTriggerMuE_MuEta"       +uncbin;
   TString hname_TTOCTriggerMuEEta        = "h_"+selbinnames[i]+"_TTOCTriggerMuEEta"          +uncbin;
   TString hname_TTOCTriggerPhoPt         = "h_"+selbinnames[i]+"_TTOCTriggerPhoPt"           +uncbin;
   TString hname_TTOCTriggerPhoEta        = "h_"+selbinnames[i]+"_TTOCTriggerPhoEta"          +uncbin;

   h_TTOCMu1Pt                [i] = initSingleHistogramTH1F( hname_TTOCMu1Pt     , "TTOCMu1Pt",       MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCMu2Pt                [i] = initSingleHistogramTH1F( hname_TTOCMu2Pt     , "TTOCMu2Pt",       MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCMuPt                 [i] = initSingleHistogramTH2F( hname_TTOCMuPt      , "TTOCMuPt" ,       MuPtBin ,MuPtBinMin ,MuPtBinMax, MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCMu1Eta               [i] = initSingleHistogramTH1F( hname_TTOCMu1Eta    , "TTOCMu1Eta",      MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCMu2Eta               [i] = initSingleHistogramTH1F( hname_TTOCMu2Eta    , "TTOCMu2Eta",      MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCMuEta                [i] = initSingleHistogramTH2F( hname_TTOCMuEta     , "TTOCMuEta" ,      MuEtaBin,MuEtaBinMin,MuEtaBinMax,MuEtaBin ,MuEtaBinMin ,MuEtaBinMax);
   h_TTOCEle1Pt               [i] = initSingleHistogramTH1F( hname_TTOCEle1Pt    , "TTOCEle1Pt",      ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCEle2Pt               [i] = initSingleHistogramTH1F( hname_TTOCEle2Pt    , "TTOCEle2Pt",      ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCElePt                [i] = initSingleHistogramTH2F( hname_TTOCElePt     , "TTOCElePt" ,      ElePtBin,ElePtBinMin,ElePtBinMax, ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCEle1Eta              [i] = initSingleHistogramTH1F( hname_TTOCEle1Eta   , "TTOCEle1Eta",     EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCEle2Eta              [i] = initSingleHistogramTH1F( hname_TTOCEle2Eta   , "TTOCEle2Eta",     EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCEleEta               [i] = initSingleHistogramTH2F( hname_TTOCEleEta    , "TTOCEleEta" ,     EleEtaBin,EleEtaBinMin,EleEtaBinMax, EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCEMu_ElePt            [i] = initSingleHistogramTH1F( hname_TTOCEMu_ElePt , "_TTOCEMu_ElePt",  ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCEMu_MuPt             [i] = initSingleHistogramTH1F( hname_TTOCEMu_MuPt  , "_TTOCEMu_MuPt",   MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCEMuPt                [i] = initSingleHistogramTH2F( hname_TTOCEMuPt     , "_TTOCEMuPt",      ElePtBin,ElePtBinMin,ElePtBinMax, MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCEMu_EleEta           [i] = initSingleHistogramTH1F( hname_TTOCEMu_EleEta, "_TTOCEMu_EleEta", EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCEMu_MuEta            [i] = initSingleHistogramTH1F( hname_TTOCEMu_MuEta , "_TTOCEMu_MuEta",  MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCEMuEta               [i] = initSingleHistogramTH2F( hname_TTOCEMuEta    , "_TTOCEMuEta",     EleEtaBin,EleEtaBinMin,EleEtaBinMax, MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCMuE_ElePt            [i] = initSingleHistogramTH1F( hname_TTOCMuE_ElePt , "_TTOCMuE_ElePt",  ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCMuE_MuPt             [i] = initSingleHistogramTH1F( hname_TTOCMuE_MuPt  , "_TTOCMuE_MuPt",   MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCMuEPt                [i] = initSingleHistogramTH2F( hname_TTOCMuEPt     , "_TTOCMuEPt",      MuPtBin ,MuPtBinMin ,MuPtBinMax, ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCMuE_EleEta           [i] = initSingleHistogramTH1F( hname_TTOCMuE_EleEta, "_TTOCMuE_EleEta", EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCMuE_MuEta            [i] = initSingleHistogramTH1F( hname_TTOCMuE_MuEta , "_TTOCMuE_MuEta",  MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCMuEEta               [i] = initSingleHistogramTH2F( hname_TTOCMuEEta    , "_TTOCMuEEta",     MuEtaBin,MuEtaBinMin,MuEtaBinMax, EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCPhoPt                [i] = initSingleHistogramTH1F( hname_TTOCPhoPt     , "_TTOCPhoPt",      PhoPtBin,PhoPtBinMin,PhoPtBinMax);
   h_TTOCPhoEta               [i] = initSingleHistogramTH1F( hname_TTOCPhoEta    , "_TTOCPhoEta",     PhoEtaBin,PhoEtaBinMin,PhoEtaBinMax);    
   //--------------Double Mu
   h_TTOCTriggerDMu1Pt        [i] = initSingleHistogramTH1F( hname_TTOCTriggerDMu1Pt       ,  "TTOCTriggerDMu1Pt",       MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerDMu2Pt        [i] = initSingleHistogramTH1F( hname_TTOCTriggerDMu2Pt       ,  "TTOCTriggerDMu2Pt",       MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerDMuPt         [i] = initSingleHistogramTH2F( hname_TTOCTriggerDMuPt        ,  "TTOCTriggerDMuPt" ,       MuPtBin ,MuPtBinMin ,MuPtBinMax, MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerDMu1Eta       [i] = initSingleHistogramTH1F( hname_TTOCTriggerDMu1Eta      ,  "TTOCTriggerDMu1Eta",      MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerDMu2Eta       [i] = initSingleHistogramTH1F( hname_TTOCTriggerDMu2Eta      ,  "TTOCTriggerDMu2Eta",      MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerDMuEta        [i] = initSingleHistogramTH2F( hname_TTOCTriggerDMuEta       ,  "TTOCTriggerDMuEta" ,      MuEtaBin,MuEtaBinMin,MuEtaBinMax,MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerDTkMu1Pt      [i] = initSingleHistogramTH1F( hname_TTOCTriggerDTkMu1Pt     ,  "TTOCTriggerDTkMu1Pt",     MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerDTkMu2Pt      [i] = initSingleHistogramTH1F( hname_TTOCTriggerDTkMu2Pt     ,  "TTOCTriggerDTkMu2Pt",     MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerDTkMu1Eta     [i] = initSingleHistogramTH1F( hname_TTOCTriggerDTkMu1Eta    ,  "TTOCTriggerDTkMu1Eta",    MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerDTkMu2Eta     [i] = initSingleHistogramTH1F( hname_TTOCTriggerDTkMu2Eta    ,  "TTOCTriggerDTkMu2Eta",    MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerNoDZMu1Pt     [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZMu1Pt    ,  "TTOCTriggerNoDZMu1Pt",    MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerNoDZMu2Pt     [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZMu2Pt    ,  "TTOCTriggerNoDZMu2Pt",    MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerNoDZMu1Eta    [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZMu1Eta   ,  "TTOCTriggerNoDZMu1Eta",   MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerNoDZMu2Eta    [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZMu2Eta   ,  "TTOCTriggerNoDZMu2Eta",   MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerNoDZTkMu1Pt   [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZTkMu1Pt  ,  "TTOCTriggerNoDZTkMu1Pt",  MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerNoDZTkMu2Pt   [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZTkMu2Pt  ,  "TTOCTriggerNoDZTkMu2Pt",  MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerNoDZTkMu1Eta  [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZTkMu1Eta ,  "TTOCTriggerNoDZTkMu1Eta", MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerNoDZTkMu2Eta  [i] = initSingleHistogramTH1F( hname_TTOCTriggerNoDZTkMu2Eta ,  "TTOCTriggerNoDZTkMu2Eta", MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   //--Single Mu
   h_TTOCTrigger22MuPt       [i] = initSingleHistogramTH1F( hname_TTOCTrigger22MuPt        ,  "TTOCTrigger22MuPt",    MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTrigger22MuEta      [i] = initSingleHistogramTH1F( hname_TTOCTrigger22MuEta       ,  "TTOCTrigger22MuEta",   MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTrigger22TkMuPt     [i] = initSingleHistogramTH1F( hname_TTOCTrigger22TkMuPt      ,  "TTOCTrigger22TkMuPt",  MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTrigger22TkMuEta    [i] = initSingleHistogramTH1F( hname_TTOCTrigger22TkMuEta     ,  "TTOCTrigger22TkMuEta", MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTrigger24MuPt       [i] = initSingleHistogramTH1F( hname_TTOCTrigger24MuPt        ,  "TTOCTrigger24MuPt",    MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTrigger24MuEta      [i] = initSingleHistogramTH1F( hname_TTOCTrigger24MuEta       ,  "TTOCTrigger24MuEta",   MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTrigger24TkMuPt     [i] = initSingleHistogramTH1F( hname_TTOCTrigger24TkMuPt      ,  "TTOCTrigger24TkMuPt",  MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTrigger24TkMuEta    [i] = initSingleHistogramTH1F( hname_TTOCTrigger24TkMuEta     ,  "TTOCTrigger24TkMuEta", MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   //--------------Double Electron
   h_TTOCTrigger23DEle1Pt     [i] = initSingleHistogramTH1F( hname_TTOCTrigger23DEle1Pt    ,  "TTOCTrigger23DEle1Pt",   ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger23DEle2Pt     [i] = initSingleHistogramTH1F( hname_TTOCTrigger23DEle2Pt    ,  "TTOCTrigger23DEle2Pt",   ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger23DElePt      [i] = initSingleHistogramTH2F( hname_TTOCTrigger23DElePt     ,  "TTOCTrigger23DElePt" ,   ElePtBin ,ElePtBinMin ,ElePtBinMax, ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger23DEle1Eta    [i] = initSingleHistogramTH1F( hname_TTOCTrigger23DEle1Eta   ,  "TTOCTrigger23DEle1Eta",  EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTrigger23DEle2Eta    [i] = initSingleHistogramTH1F( hname_TTOCTrigger23DEle2Eta   ,  "TTOCTrigger23DEle2Eta",  EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTrigger23DEleEta     [i] = initSingleHistogramTH2F( hname_TTOCTrigger23DEleEta    ,  "TTOCTrigger23DEleEta" ,  EleEtaBin,EleEtaBinMin,EleEtaBinMax,EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTrigger17DEle1Pt     [i] = initSingleHistogramTH1F( hname_TTOCTrigger17DEle1Pt    ,  "TTOCTrigger17DEle1Pt",   ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger17DEle2Pt     [i] = initSingleHistogramTH1F( hname_TTOCTrigger17DEle2Pt    ,  "TTOCTrigger17DEle2Pt",   ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger17DEle1Eta    [i] = initSingleHistogramTH1F( hname_TTOCTrigger17DEle1Eta   ,  "TTOCTrigger17DEle1Eta",  EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTrigger17DEle2Eta    [i] = initSingleHistogramTH1F( hname_TTOCTrigger17DEle2Eta   ,  "TTOCTrigger17Dele2Eta",  EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   //--Single Electron
   h_TTOCTrigger23ElePt      [i] = initSingleHistogramTH1F( hname_TTOCTrigger23ElePt       ,  "TTOCTrigger23ElePt",      ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger23EleEta     [i] = initSingleHistogramTH1F( hname_TTOCTrigger23EleEta      ,  "TTOCTrigger23EleEta",     EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTrigger27ElePt      [i] = initSingleHistogramTH1F( hname_TTOCTrigger27ElePt       ,  "TTOCTrigger27ElePt",      ElePtBin ,ElePtBinMin ,ElePtBinMax);
   h_TTOCTrigger27EleEta     [i] = initSingleHistogramTH1F( hname_TTOCTrigger27EleEta      ,  "TTOCTrigger27EleEta",     EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   
   h_TTOCTriggerEMu_ElePt    [i] = initSingleHistogramTH1F( hname_TTOCTriggerEMu_ElePt     , "_TTOCTriggerEMu_ElePt",  ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCTriggerEMu_MuPt     [i] = initSingleHistogramTH1F( hname_TTOCTriggerEMu_MuPt      , "_TTOCTriggerEMu_MuPt",   MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerEMuPt        [i] = initSingleHistogramTH2F( hname_TTOCTriggerEMuPt         , "_TTOCTriggerEMuPt",      ElePtBin,ElePtBinMin,ElePtBinMax, MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerEMu_EleEta   [i] = initSingleHistogramTH1F( hname_TTOCTriggerEMu_EleEta    , "_TTOCTriggerEMu_EleEta", EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTriggerEMu_MuEta    [i] = initSingleHistogramTH1F( hname_TTOCTriggerEMu_MuEta     , "_TTOCTriggerEMu_MuEta",  MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerEMuEta       [i] = initSingleHistogramTH2F( hname_TTOCTriggerEMuEta        , "_TTOCTriggerEMuEta",     EleEtaBin,EleEtaBinMin,EleEtaBinMax, MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerMuE_ElePt    [i] = initSingleHistogramTH1F( hname_TTOCTriggerMuE_ElePt     , "_TTOCTriggerMuE_ElePt",  ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCTriggerMuE_MuPt     [i] = initSingleHistogramTH1F( hname_TTOCTriggerMuE_MuPt      , "_TTOCTriggerMuE_MuPt",   MuPtBin ,MuPtBinMin ,MuPtBinMax);
   h_TTOCTriggerMuEPt        [i] = initSingleHistogramTH2F( hname_TTOCTriggerMuEPt         , "_TTOCTriggerMuEPt",      MuPtBin ,MuPtBinMin ,MuPtBinMax, ElePtBin,ElePtBinMin,ElePtBinMax);
   h_TTOCTriggerMuE_EleEta   [i] = initSingleHistogramTH1F( hname_TTOCTriggerMuE_EleEta    , "_TTOCTriggerMuE_EleEta", EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTriggerMuE_MuEta    [i] = initSingleHistogramTH1F( hname_TTOCTriggerMuE_MuEta     , "_TTOCTriggerMuE_MuEta",  MuEtaBin,MuEtaBinMin,MuEtaBinMax);
   h_TTOCTriggerMuEEta       [i] = initSingleHistogramTH2F( hname_TTOCTriggerMuEEta        , "_TTOCTriggerMuEEta",     MuEtaBin,MuEtaBinMin,MuEtaBinMax, EleEtaBin,EleEtaBinMin,EleEtaBinMax);
   h_TTOCTriggerPhoPt        [i] = initSingleHistogramTH1F( hname_TTOCTriggerPhoPt         , "_TTOCTriggerPhoPt",      PhoPtBin,PhoPtBinMin,PhoPtBinMax);
   h_TTOCTriggerPhoEta       [i] = initSingleHistogramTH1F( hname_TTOCTriggerPhoEta        , "_TTOCTriggerPhoEta",     PhoEtaBin,PhoEtaBinMin,PhoEtaBinMax);    
 }

 return kTRUE;
}

//----------------------------fillTTOCHistograms
Bool_t analyzer_histograms::fillTTOCHistograms(Float_t weight, int selbin)
{
   //setup
   int leadPho;
   if(photon_list.size()>0)  {leadPho    = photon_list[0]; }
   int leadMu;
   int subLeadMu;
   if(muon_list.size()>0)    {leadMu    = muon_list[0]; }
   if(muon_list.size()>1)    {subLeadMu = muon_list[1]; }
   int leadEle;
   int subLeadEle;
   if(electron_list.size()>0) {leadEle    = electron_list[0];} 
   if(electron_list.size()>1) {subLeadEle = electron_list[1];} 
 
   //define trigger passing bools
   //Bool_t doesPassDMu = (Bool_t)( (AOD_HLT_IsoMu22 > 0) || (AOD_HLT_IsoTkMu22 > 0) || (AOD_HLT_IsoMu24 > 0) || (AOD_HLT_IsoTkMu24 > 0) );
   Bool_t doesPassDMu = (Bool_t)( (AOD_HLT_Mu17Mu8 > 0) || (AOD_HLT_Mu17TkMu8 > 0) || (AOD_HLT_Mu17Mu8_noDZ > 0) || (AOD_HLT_Mu17TkMu8_noDZ > 0)) ; 
   Bool_t doesPassDEle = (Bool_t)( (AOD_HLT_Ele23Ele12 > 0) ); 
   Bool_t doesPassEMu = kFALSE;
   Bool_t doesPassMuE = kFALSE;
   //EMu
   doesPassEMu =  (Bool_t)( (AOD_HLT_Mu12Ele23_DZ > 0) );
   if(run>=273158 && run<=278272){
    doesPassEMu =  (Bool_t)( (AOD_HLT_Mu8Ele23 > 0) );
   }
   else if(run>=278273 && run<=284044){
    doesPassEMu = (Bool_t)( (AOD_HLT_Mu12Ele23_DZ > 0));
   }
   //MuE
   doesPassMuE =  (Bool_t)( (AOD_HLT_Mu23Ele12_DZ > 0) );
   if(run>=273158 && run<=278272){
    doesPassMuE = (Bool_t)( (AOD_HLT_Mu23Ele12 > 0) );
   }
   else if(run>=278273 && run<=284044){
    doesPassMuE = (Bool_t)( (AOD_HLT_Mu23Ele12_DZ > 0) );
   }
   //-------------------------Fill Passing basic selections
   //Single Photon 
   if(photon_list.size() >0){
    h_TTOCPhoPt               [selbin] ->Fill( AOD_phoPt               ->at(leadPho), weight );  
    h_TTOCPhoEta              [selbin] ->Fill( AOD_phoEta              ->at(leadPho), weight ); 
   }
   //MuonEG
   if(muon_list.size() > 0 && electron_list.size() > 0){
    //MuE
    if( AOD_muPt->at(leadMu) > AOD_elePt->at(leadEle) ){
      // fill for muon 
      h_TTOCMuE_MuPt             [selbin] ->Fill( AOD_muPt               ->at(leadMu), weight );  
      h_TTOCMuE_MuEta            [selbin] ->Fill( AOD_muEta              ->at(leadMu), weight ); 
      // fill for electron
      h_TTOCMuE_ElePt            [selbin] ->Fill( AOD_elePt               ->at(leadEle), weight );  
      h_TTOCMuE_EleEta           [selbin] ->Fill( AOD_eleEta              ->at(leadEle), weight );
      //2D Hists  
      h_TTOCMuEPt                [selbin] ->Fill( AOD_muPt ->at(leadMu), AOD_elePt->at(leadEle), weight );  
      h_TTOCMuEEta               [selbin] ->Fill( AOD_muEta->at(leadMu), AOD_eleEta->at(leadEle), weight );  
    }
    //EMu
    if( AOD_muPt->at(leadMu) < AOD_elePt->at(leadEle) ){
      // fill for muon 
      h_TTOCEMu_MuPt             [selbin] ->Fill( AOD_muPt               ->at(leadMu), weight );  
      h_TTOCEMu_MuEta            [selbin] ->Fill( AOD_muEta              ->at(leadMu), weight ); 
      // fill for electron
      h_TTOCEMu_ElePt            [selbin] ->Fill( AOD_elePt               ->at(leadEle), weight );  
      h_TTOCEMu_EleEta           [selbin] ->Fill( AOD_eleEta              ->at(leadEle), weight );
      //2D Hists  
      h_TTOCEMuPt                [selbin] ->Fill( AOD_elePt ->at(leadEle), AOD_muPt->at(leadMu), weight );  
      h_TTOCEMuEta               [selbin] ->Fill( AOD_eleEta->at(leadEle), AOD_muEta->at(leadMu), weight );  
    }
   }
   //DoubleMu
   if(muon_list.size() > 1){
    // fill leading muon in vector
    h_TTOCMu1Pt               [selbin] ->Fill( AOD_muPt               ->at(leadMu), weight );  
    h_TTOCMu1Eta              [selbin] ->Fill( AOD_muEta              ->at(leadMu), weight ); 
    // fill for sub-leading muon in vector
    h_TTOCMu2Pt               [selbin] ->Fill( AOD_muPt               ->at(subLeadMu), weight );  
    h_TTOCMu2Eta              [selbin] ->Fill( AOD_muEta              ->at(subLeadMu), weight );
    //2D Hists  
    h_TTOCMuPt                [selbin] ->Fill( AOD_muPt ->at(leadMu), AOD_muPt->at(subLeadMu), weight );  
    h_TTOCMuEta               [selbin] ->Fill( AOD_muEta->at(leadMu), AOD_muEta->at(subLeadMu), weight );  
   }
   //DoubleEle
   if(electron_list.size() > 1){
   // fill leading electron in vector
    h_TTOCEle1Pt               [selbin] ->Fill( AOD_elePt               ->at(leadEle), weight );  
    h_TTOCEle1Eta              [selbin] ->Fill( AOD_eleEta              ->at(leadEle), weight ); 
   // fill for sub-leading muon in vector
    h_TTOCEle2Pt               [selbin] ->Fill( AOD_elePt               ->at(subLeadEle), weight );  
    h_TTOCEle2Eta              [selbin] ->Fill( AOD_eleEta              ->at(subLeadEle), weight );  
    //2D Hists
    h_TTOCElePt                [selbin] ->Fill( AOD_elePt ->at(leadEle), AOD_elePt->at(subLeadEle), weight );  
    h_TTOCEleEta               [selbin] ->Fill( AOD_eleEta->at(leadEle), AOD_eleEta->at(subLeadEle), weight );  
   }

   //--------------------Fill For Passing Equivalent Triggers
   // fill for passing all Double Muon triggers used in analyzer_selections.C def of double muon
   if(doesPassDMu && muon_list.size() > 1){
    h_TTOCTriggerDMu1Pt               [selbin] ->Fill( AOD_muPt               ->at(leadMu), weight );  
    h_TTOCTriggerDMu2Pt               [selbin] ->Fill( AOD_muPt               ->at(subLeadMu), weight );  
    h_TTOCTriggerDMu1Eta              [selbin] ->Fill( AOD_muEta              ->at(leadMu), weight );  
    h_TTOCTriggerDMu2Eta              [selbin] ->Fill( AOD_muEta              ->at(subLeadMu), weight ); 
    
    h_TTOCTriggerDMuPt                [selbin] ->Fill( AOD_muPt ->at(leadMu), AOD_muPt->at(subLeadMu), weight );  
    h_TTOCTriggerDMuEta               [selbin] ->Fill( AOD_muEta->at(leadMu), AOD_muEta->at(subLeadMu), weight );  
   } 
   // fill for passing all Double electron triggers used in analyzer_selections.C def of double electron
   if( doesPassDEle && electron_list.size() > 1){
    h_TTOCTrigger23DEle1Pt               [selbin] ->Fill( AOD_elePt               ->at(leadEle), weight );  
    h_TTOCTrigger23DEle2Pt               [selbin] ->Fill( AOD_elePt               ->at(subLeadEle), weight );  
    h_TTOCTrigger23DEle1Eta              [selbin] ->Fill( AOD_eleEta              ->at(leadEle), weight );  
    h_TTOCTrigger23DEle2Eta              [selbin] ->Fill( AOD_eleEta              ->at(subLeadEle), weight );  

    h_TTOCTrigger23DElePt                [selbin] ->Fill( AOD_elePt ->at(leadEle), AOD_elePt ->at(subLeadEle), weight );  
    h_TTOCTrigger23DEleEta               [selbin] ->Fill( AOD_eleEta->at(leadEle), AOD_eleEta->at(subLeadEle), weight );  
   } 
   // fill for passing all Single photon triggers used in analyzer_selections.C def of OnePho
   //if (photon_list.size()>0)std::cout<<"***************NoPassPhotonPt: "<<AOD_phoPt->at(leadPho)<<std::endl;
   if( (Bool_t)AOD_HLT_Photon165_HE10 && photon_list.size() > 0){
    h_TTOCTriggerPhoPt             [selbin] ->Fill( AOD_phoPt               ->at(leadPho), weight );  
    h_TTOCTriggerPhoEta            [selbin] ->Fill( AOD_phoEta              ->at(leadPho), weight );  
    //std::cout<<"PhotonPt: "<<AOD_phoPt->at(leadPho)<<std::endl;
   }
   // fill for passing all MuonEG triggers used in analyzer_selections.C def of EleMuOSOF
   if(doesPassMuE && muon_list.size() > 0 && electron_list.size() > 0){
    //MuE
    if( AOD_muPt->at(leadMu) > AOD_elePt->at(leadEle) ){
      // fill for muon 
      h_TTOCTriggerMuE_MuPt             [selbin] ->Fill( AOD_muPt               ->at(leadMu), weight );  
      h_TTOCTriggerMuE_MuEta            [selbin] ->Fill( AOD_muEta              ->at(leadMu), weight ); 
      // fill for electron
      h_TTOCTriggerMuE_ElePt            [selbin] ->Fill( AOD_elePt               ->at(leadEle), weight );  
      h_TTOCTriggerMuE_EleEta           [selbin] ->Fill( AOD_eleEta              ->at(leadEle), weight );
      //2D Hists  
      h_TTOCTriggerMuEPt                [selbin] ->Fill( AOD_muPt ->at(leadMu), AOD_elePt->at(leadEle), weight );  
      h_TTOCTriggerMuEEta               [selbin] ->Fill( AOD_muEta->at(leadMu), AOD_eleEta->at(leadEle), weight );  
   }}
   if(doesPassEMu && muon_list.size() > 0 && electron_list.size() > 0){
    //EMu
    if( AOD_elePt->at(leadEle) > AOD_muPt->at(leadMu) ){
      // fill for muon 
      h_TTOCTriggerEMu_MuPt             [selbin] ->Fill( AOD_muPt               ->at(leadMu), weight );  
      h_TTOCTriggerEMu_MuEta            [selbin] ->Fill( AOD_muEta              ->at(leadMu), weight ); 
      // fill for electron
      h_TTOCTriggerEMu_ElePt            [selbin] ->Fill( AOD_elePt               ->at(leadEle), weight );  
      h_TTOCTriggerEMu_EleEta           [selbin] ->Fill( AOD_eleEta              ->at(leadEle), weight );
      //2D Hists  
      h_TTOCTriggerEMuPt                [selbin] ->Fill( AOD_elePt ->at(leadEle), AOD_muPt->at(leadMu), weight );  
      h_TTOCTriggerEMuEta               [selbin] ->Fill( AOD_eleEta->at(leadEle), AOD_muEta->at(leadMu), weight );  
   }}
 return kTRUE;
}

//----------------------------writeTTOCHistograms
Bool_t analyzer_histograms::writeTTOCHistograms(int selbin)
{
  h_TTOCMu1Pt           [selbin] ->Write();
  h_TTOCMu2Pt           [selbin] ->Write();
  h_TTOCMuPt            [selbin] ->Write();
  h_TTOCMu1Eta          [selbin] ->Write();
  h_TTOCMu2Eta          [selbin] ->Write();
  h_TTOCMuEta           [selbin] ->Write();
  h_TTOCEle1Pt          [selbin] ->Write();
  h_TTOCEle2Pt          [selbin] ->Write();
  h_TTOCElePt           [selbin] ->Write();
  h_TTOCEle1Eta         [selbin] ->Write();
  h_TTOCEle2Eta         [selbin] ->Write();
  h_TTOCEleEta          [selbin] ->Write();
  h_TTOCEMu_ElePt       [selbin] ->Write(); 
  h_TTOCEMu_MuPt        [selbin] ->Write(); 
  h_TTOCEMuPt           [selbin] ->Write(); 
  h_TTOCEMu_EleEta      [selbin] ->Write(); 
  h_TTOCEMu_MuEta       [selbin] ->Write(); 
  h_TTOCEMuEta          [selbin] ->Write(); 
  h_TTOCMuE_ElePt       [selbin] ->Write(); 
  h_TTOCMuE_MuPt        [selbin] ->Write(); 
  h_TTOCMuEPt           [selbin] ->Write(); 
  h_TTOCMuE_EleEta      [selbin] ->Write(); 
  h_TTOCMuE_MuEta       [selbin] ->Write(); 
  h_TTOCMuEEta          [selbin] ->Write();  
  h_TTOCPhoPt           [selbin] ->Write();  
  h_TTOCPhoEta          [selbin] ->Write();  
  //Double Mu
  h_TTOCTriggerDMu1Pt        [selbin] ->Write();
  h_TTOCTriggerDMu2Pt        [selbin] ->Write();
  h_TTOCTriggerDMuPt         [selbin] ->Write();
  h_TTOCTriggerDMu1Eta       [selbin] ->Write();
  h_TTOCTriggerDMu2Eta       [selbin] ->Write();
  h_TTOCTriggerDMuEta        [selbin] ->Write();
  h_TTOCTriggerDTkMu1Pt      [selbin] ->Write();
  h_TTOCTriggerDTkMu2Pt      [selbin] ->Write();
  h_TTOCTriggerDTkMu1Eta     [selbin] ->Write();
  h_TTOCTriggerDTkMu2Eta     [selbin] ->Write();
  h_TTOCTriggerNoDZMu1Pt     [selbin] ->Write();
  h_TTOCTriggerNoDZMu2Pt     [selbin] ->Write();
  h_TTOCTriggerNoDZMu1Eta    [selbin] ->Write();
  h_TTOCTriggerNoDZMu2Eta    [selbin] ->Write();
  h_TTOCTriggerNoDZTkMu1Pt   [selbin] ->Write();
  h_TTOCTriggerNoDZTkMu2Pt   [selbin] ->Write();
  h_TTOCTriggerNoDZTkMu1Eta  [selbin] ->Write();
  h_TTOCTriggerNoDZTkMu2Eta  [selbin] ->Write();
  //--Single Mu
  h_TTOCTrigger22MuPt          [selbin] ->Write();
  h_TTOCTrigger22MuEta         [selbin] ->Write();
  h_TTOCTrigger22TkMuPt        [selbin] ->Write();
  h_TTOCTrigger22TkMuEta       [selbin] ->Write();
  h_TTOCTrigger24MuPt          [selbin] ->Write();
  h_TTOCTrigger24MuEta         [selbin] ->Write();
  h_TTOCTrigger24TkMuPt        [selbin] ->Write();
  h_TTOCTrigger24TkMuEta       [selbin] ->Write();
  //Double Electron
  h_TTOCTrigger23DEle1Pt       [selbin] ->Write();
  h_TTOCTrigger23DEle2Pt       [selbin] ->Write();
  h_TTOCTrigger23DElePt        [selbin] ->Write();
  h_TTOCTrigger23DEle1Eta      [selbin] ->Write();
  h_TTOCTrigger23DEle2Eta      [selbin] ->Write();
  h_TTOCTrigger23DEleEta       [selbin] ->Write();
  h_TTOCTrigger17DEle1Pt     [selbin] ->Write();
  h_TTOCTrigger17DEle2Pt     [selbin] ->Write();
  h_TTOCTrigger17DEle1Eta    [selbin] ->Write();
  h_TTOCTrigger17DEle2Eta    [selbin] ->Write();
  //--Single Electron
  h_TTOCTrigger23ElePt         [selbin] ->Write();
  h_TTOCTrigger23EleEta        [selbin] ->Write();
  h_TTOCTrigger27ElePt         [selbin] ->Write();
  h_TTOCTrigger27EleEta        [selbin] ->Write();
  
  h_TTOCTriggerEMu_ElePt     [selbin] ->Write(); 
  h_TTOCTriggerEMu_MuPt      [selbin] ->Write(); 
  h_TTOCTriggerEMuPt         [selbin] ->Write(); 
  h_TTOCTriggerEMu_EleEta    [selbin] ->Write(); 
  h_TTOCTriggerEMu_MuEta     [selbin] ->Write(); 
  h_TTOCTriggerEMuEta        [selbin] ->Write(); 
  h_TTOCTriggerMuE_ElePt     [selbin] ->Write(); 
  h_TTOCTriggerMuE_MuPt      [selbin] ->Write(); 
  h_TTOCTriggerMuEPt         [selbin] ->Write(); 
  h_TTOCTriggerMuE_EleEta    [selbin] ->Write(); 
  h_TTOCTriggerMuE_MuEta     [selbin] ->Write(); 
  h_TTOCTriggerMuEEta        [selbin] ->Write();  
  h_TTOCTriggerPhoPt         [selbin] ->Write();  
  h_TTOCTriggerPhoEta        [selbin] ->Write();  
 return kTRUE;
}

//----------------------------deleteTTOCHistograms
Bool_t analyzer_histograms::deleteTTOCHistograms(int selbin)
{
  //printf("deleteTTOCHistograms\n");
  if(h_TTOCMu1Pt     [selbin]!=NULL)    h_TTOCMu1Pt           [selbin] ->Delete();
  if(h_TTOCMu2Pt     [selbin]!=NULL)    h_TTOCMu2Pt           [selbin] ->Delete();
  if(h_TTOCMuPt      [selbin]!=NULL)    h_TTOCMuPt            [selbin] ->Delete();
  if(h_TTOCMu1Eta    [selbin]!=NULL)    h_TTOCMu1Eta          [selbin] ->Delete();
  if(h_TTOCMu2Eta    [selbin]!=NULL)    h_TTOCMu2Eta          [selbin] ->Delete();
  if(h_TTOCMuEta     [selbin]!=NULL)    h_TTOCMuEta           [selbin] ->Delete();
  if(h_TTOCEle1Pt    [selbin]!=NULL)    h_TTOCEle1Pt          [selbin] ->Delete();
  if(h_TTOCEle2Pt    [selbin]!=NULL)    h_TTOCEle2Pt          [selbin] ->Delete();
  if(h_TTOCElePt     [selbin]!=NULL)    h_TTOCElePt           [selbin] ->Delete();
  if(h_TTOCEle1Eta   [selbin]!=NULL)    h_TTOCEle1Eta         [selbin] ->Delete();
  if(h_TTOCEle2Eta   [selbin]!=NULL)    h_TTOCEle2Eta         [selbin] ->Delete();
  if(h_TTOCEleEta    [selbin]!=NULL)    h_TTOCEleEta          [selbin] ->Delete();
  if(h_TTOCEMu_ElePt [selbin]!=NULL)    h_TTOCEMu_ElePt       [selbin] ->Delete(); 
  if(h_TTOCEMu_MuPt  [selbin]!=NULL)    h_TTOCEMu_MuPt        [selbin] ->Delete(); 
  if(h_TTOCEMuPt     [selbin]!=NULL)    h_TTOCEMuPt           [selbin] ->Delete(); 
  if(h_TTOCEMu_EleEta[selbin]!=NULL)    h_TTOCEMu_EleEta      [selbin] ->Delete(); 
  if(h_TTOCEMu_MuEta [selbin]!=NULL)    h_TTOCEMu_MuEta       [selbin] ->Delete(); 
  if(h_TTOCEMuEta    [selbin]!=NULL)    h_TTOCEMuEta          [selbin] ->Delete(); 
  if(h_TTOCMuE_ElePt [selbin]!=NULL)    h_TTOCMuE_ElePt       [selbin] ->Delete(); 
  if(h_TTOCMuE_MuPt  [selbin]!=NULL)    h_TTOCMuE_MuPt        [selbin] ->Delete(); 
  if(h_TTOCMuEPt     [selbin]!=NULL)    h_TTOCMuEPt           [selbin] ->Delete(); 
  if(h_TTOCMuE_EleEta[selbin]!=NULL)    h_TTOCMuE_EleEta      [selbin] ->Delete(); 
  if(h_TTOCMuE_MuEta [selbin]!=NULL)    h_TTOCMuE_MuEta       [selbin] ->Delete(); 
  if(h_TTOCMuEEta    [selbin]!=NULL)    h_TTOCMuEEta          [selbin] ->Delete();  
  if(h_TTOCPhoPt     [selbin]!=NULL)    h_TTOCPhoPt           [selbin] ->Delete();  
  if(h_TTOCPhoEta    [selbin]!=NULL)    h_TTOCPhoEta          [selbin] ->Delete(); 
  //Double Mu
  //if(h_TTOCTriggerDMu1Pt      [selbin]!=NULL)    h_TTOCTriggerDMu1Pt        [selbin] ->Delete();
  //if(h_TTOCTriggerDMu2Pt      [selbin]!=NULL)    h_TTOCTriggerDMu2Pt        [selbin] ->Delete();
  //if(h_TTOCTriggerDMuPt       [selbin]!=NULL)    h_TTOCTriggerDMuPt         [selbin] ->Delete();
  //if(h_TTOCTriggerDMu1Eta     [selbin]!=NULL)    h_TTOCTriggerDMu1Eta       [selbin] ->Delete();
  //if(h_TTOCTriggerDMu2Eta     [selbin]!=NULL)    h_TTOCTriggerDMu2Eta       [selbin] ->Delete();
  //if(h_TTOCTriggerDMuEta      [selbin]!=NULL)    h_TTOCTriggerDMuEta        [selbin] ->Delete();
  //if(h_TTOCTriggerDTkMu1Pt    [selbin]!=NULL)    h_TTOCTriggerDTkMu1Pt      [selbin] ->Delete();
  //if(h_TTOCTriggerDTkMu2Pt    [selbin]!=NULL)    h_TTOCTriggerDTkMu2Pt      [selbin] ->Delete();
  //if(h_TTOCTriggerDTkMu1Eta   [selbin]!=NULL)    h_TTOCTriggerDTkMu1Eta     [selbin] ->Delete();
  //if(h_TTOCTriggerDTkMu2Eta   [selbin]!=NULL)    h_TTOCTriggerDTkMu2Eta     [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZMu1Pt   [selbin]!=NULL)    h_TTOCTriggerNoDZMu1Pt     [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZMu2Pt   [selbin]!=NULL)    h_TTOCTriggerNoDZMu2Pt     [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZMu1Eta  [selbin]!=NULL)    h_TTOCTriggerNoDZMu1Eta    [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZMu2Eta  [selbin]!=NULL)    h_TTOCTriggerNoDZMu2Eta    [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZTkMu1Pt [selbin]!=NULL)    h_TTOCTriggerNoDZTkMu1Pt   [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZTkMu2Pt [selbin]!=NULL)    h_TTOCTriggerNoDZTkMu2Pt   [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZTkMu1Eta[selbin]!=NULL)    h_TTOCTriggerNoDZTkMu1Eta  [selbin] ->Delete();
  //if(h_TTOCTriggerNoDZTkMu2Eta[selbin]!=NULL)    h_TTOCTriggerNoDZTkMu2Eta  [selbin] ->Delete();
  //--Single Mu
  if(h_TTOCTrigger22MuPt    [selbin]!=NULL)   h_TTOCTrigger22MuPt          [selbin] ->Delete();
  if(h_TTOCTrigger22MuEta   [selbin]!=NULL)   h_TTOCTrigger22MuEta         [selbin] ->Delete();
  if(h_TTOCTrigger22TkMuPt  [selbin]!=NULL)   h_TTOCTrigger22TkMuPt        [selbin] ->Delete();
  if(h_TTOCTrigger22TkMuEta [selbin]!=NULL)   h_TTOCTrigger22TkMuEta       [selbin] ->Delete();
  if(h_TTOCTrigger24MuPt    [selbin]!=NULL)   h_TTOCTrigger24MuPt          [selbin] ->Delete();
  if(h_TTOCTrigger24MuEta   [selbin]!=NULL)   h_TTOCTrigger24MuEta         [selbin] ->Delete();
  if(h_TTOCTrigger24TkMuPt  [selbin]!=NULL)   h_TTOCTrigger24TkMuPt        [selbin] ->Delete();
  if(h_TTOCTrigger24TkMuEta [selbin]!=NULL)   h_TTOCTrigger24TkMuEta       [selbin] ->Delete();
  //Double Electron
  if(h_TTOCTrigger23DEle1Pt  [selbin]!=NULL)  h_TTOCTrigger23DEle1Pt       [selbin] ->Delete();
  if(h_TTOCTrigger23DEle2Pt  [selbin]!=NULL)  h_TTOCTrigger23DEle2Pt       [selbin] ->Delete();
  if(h_TTOCTrigger23DElePt   [selbin]!=NULL)  h_TTOCTrigger23DElePt        [selbin] ->Delete();
  if(h_TTOCTrigger23DEle1Eta [selbin]!=NULL)  h_TTOCTrigger23DEle1Eta      [selbin] ->Delete();
  if(h_TTOCTrigger23DEle2Eta [selbin]!=NULL)  h_TTOCTrigger23DEle2Eta      [selbin] ->Delete();
  if(h_TTOCTrigger23DEleEta  [selbin]!=NULL)  h_TTOCTrigger23DEleEta       [selbin] ->Delete();
  //if(h_TTOCTrigger17DEle1Pt  [selbin]!=NULL)  h_TTOCTrigger17DEle1Pt     [selbin] ->Delete()
  //if(h_TTOCTrigger17DEle2Pt  [selbin]!=NULL)  h_TTOCTrigger17DEle2Pt     [selbin] ->Delete();
  //if(h_TTOCTrigger17DEle1Eta [selbin]!=NULL)  h_TTOCTrigger17DEle1Eta    [selbin] ->Delete();
  //if(h_TTOCTrigger17DEle2Eta [selbin]!=NULL)  h_TTOCTrigger17DEle2Eta    [selbin] ->Delete();
  //--Single Electron
  if(h_TTOCTrigger23ElePt   [selbin]!=NULL)   h_TTOCTrigger23ElePt         [selbin] ->Delete();
  if(h_TTOCTrigger23EleEta  [selbin]!=NULL)   h_TTOCTrigger23EleEta        [selbin] ->Delete();
  if(h_TTOCTrigger27ElePt   [selbin]!=NULL)   h_TTOCTrigger27ElePt         [selbin] ->Delete();
  if(h_TTOCTrigger27EleEta  [selbin]!=NULL)   h_TTOCTrigger27EleEta        [selbin] ->Delete(); 
  if(h_TTOCTriggerEMu_ElePt [selbin]!=NULL)   h_TTOCTriggerEMu_ElePt       [selbin] ->Delete(); 
  if(h_TTOCTriggerEMu_MuPt  [selbin]!=NULL)   h_TTOCTriggerEMu_MuPt        [selbin] ->Delete(); 
  if(h_TTOCTriggerEMuPt     [selbin]!=NULL)   h_TTOCTriggerEMuPt           [selbin] ->Delete(); 
  if(h_TTOCTriggerEMu_EleEta[selbin]!=NULL)   h_TTOCTriggerEMu_EleEta      [selbin] ->Delete(); 
  if(h_TTOCTriggerEMu_MuEta [selbin]!=NULL)   h_TTOCTriggerEMu_MuEta       [selbin] ->Delete(); 
  if(h_TTOCTriggerEMuEta    [selbin]!=NULL)   h_TTOCTriggerEMuEta          [selbin] ->Delete(); 
  if(h_TTOCTriggerMuE_ElePt [selbin]!=NULL)   h_TTOCTriggerMuE_ElePt       [selbin] ->Delete(); 
  if(h_TTOCTriggerMuE_MuPt  [selbin]!=NULL)   h_TTOCTriggerMuE_MuPt        [selbin] ->Delete(); 
  if(h_TTOCTriggerMuEPt     [selbin]!=NULL)   h_TTOCTriggerMuEPt           [selbin] ->Delete(); 
  if(h_TTOCTriggerMuE_EleEta[selbin]!=NULL)   h_TTOCTriggerMuE_EleEta      [selbin] ->Delete(); 
  if(h_TTOCTriggerMuE_MuEta [selbin]!=NULL)   h_TTOCTriggerMuE_MuEta       [selbin] ->Delete(); 
  if(h_TTOCTriggerMuEEta    [selbin]!=NULL)   h_TTOCTriggerMuEEta          [selbin] ->Delete();  
  if(h_TTOCTriggerPhoPt     [selbin]!=NULL)   h_TTOCTriggerPhoPt           [selbin] ->Delete();  
  if(h_TTOCTriggerPhoEta    [selbin]!=NULL)   h_TTOCTriggerPhoEta          [selbin] ->Delete();  
  return kTRUE;
}


//----------------------------initExtraHistograms
Bool_t analyzer_histograms::initExtraHistograms( TString uncbin ){

  //for(unsigned int i=0; i<selbinnames.size(); ++i){
  //deleteExtraHistograms(i);
  //}
 return kTRUE;
}

//----------------------------fillExtraHistograms
Bool_t analyzer_histograms::fillExtraHistograms(Float_t weight, int selbin)
{ 
  return kTRUE;
}

//----------------------------writeExtraHistograms
Bool_t analyzer_histograms::writeExtraHistograms(int selbin)
{
 return kTRUE;
}


//----------------------------deleteExtraHistograms
Bool_t analyzer_histograms::deleteExtraHistograms(int selbin)
{
 return kTRUE;
}

//---------------------------scaleVariableBinHistograms
Bool_t analyzer_histograms::scaleVariableBinHistograms(int selbin)
{

  hist_file_out[selbin]->cd();

  unsigned int j; if(jetMultOn) j=0; else j=jetmultnames.size()-1;
  for(j; j<jetmultnames.size(); ++j){
    h_AODCaloJetPtVar                      [selbin][j]->Scale(1, "width");
  }
  for(unsigned int j=0; j<tagmultnames.size(); ++j){
    h_AODCaloJetPtVar_Tag0                 [selbin][j]->Scale(1, "width");
  }
  
  return kTRUE;
}


//----------------------------initAODCaloJetMultHistograms
Bool_t analyzer_histograms::initAODCaloJetMultHistograms( TString uncbin )
{
  for(unsigned int i=0; i<selbinnames.size(); ++i){
    hist_file_out[i]->cd();

    //deleteAODCaloJetMultHistograms(i);
    TString hname_nSelectedAODCaloJet          = "h_"+selbinnames[i]+"_nSelectedAODCaloJet"+uncbin;
    h_nSelectedAODCaloJet                  [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJet         , "nSelectedAODCaloJet"      , 10, -0.5, 9.5);
  }//sel                                                                                                                                                                                
}

//----------------------------fillAODCaloJetMultHistograms
Bool_t analyzer_histograms::fillAODCaloJetMultHistograms(Float_t weight, int selbin)
{
  hist_file_out[selbin]->cd();

  h_nSelectedAODCaloJet    [selbin] ->Fill( float(aodcalojet_list.size()), weight );
}

//----------------------------writeAODCaloJetMultHistograms
Bool_t analyzer_histograms::writeAODCaloJetMultHistograms(int selbin)
{
  hist_file_out[selbin]->cd();
  h_nSelectedAODCaloJet    [selbin] ->Write();
}

//----------------------------deleteAODCaloJetMultHistograms
Bool_t analyzer_histograms::deleteAODCaloJetMultHistograms(int selbin)
{
  //printf("deleteAODCaloJetMultHistograms\n");
  hist_file_out[selbin]->cd();
  if(h_nSelectedAODCaloJet[selbin]!=NULL) h_nSelectedAODCaloJet    [selbin] ->Delete();
}


//----------------------------initAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::initAODCaloJetTagMultHistograms( TString uncbin )
{
  for(unsigned int i=0; i<selbinnames.size(); ++i){
    hist_file_out[i]->cd();

      //deleteAODCaloJetTagMultHistograms(i);
      TString hname_nSelectedAODCaloJetTag        = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTag"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB1     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB1"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB3     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB3"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB4     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB4"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB5     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB5"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB6     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB6"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB7     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB7"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL1     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL1"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL2     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL2"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL3     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL3"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL4     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL4"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL5     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL5"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL6     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL6"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBL7     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBL7"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2a     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2a"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2c     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2c"+uncbin;
      TString hname_nSelectedAODCaloJetTagIP       = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagIP"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBIPa     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBIPa"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBIPb     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBIPb"+uncbin;
      TString hname_nSelectedAODCaloJetTagSBIPc     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSBIPc"+uncbin;

      TString hname_nSelectedAODCaloJetTag_0b        = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTag_0b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB1_0b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB1_0b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2_0b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2_0b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB3_0b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB3_0b"+uncbin;
      TString hname_nSelectedAODCaloJetTag_1b        = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTag_1b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB1_1b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB1_1b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2_1b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2_1b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB3_1b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB3_1b"+uncbin;
      TString hname_nSelectedAODCaloJetTag_2b        = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTag_2b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB1_2b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB1_2b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB2_2b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB2_2b"+uncbin;
      TString hname_nSelectedAODCaloJetTagSB3_2b     = "h_"+selbinnames[i]+"_nSelectedAODCaloJetTagSB3_2b"+uncbin;

      h_nSelectedAODCaloJetTag                [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTag            , "nSelectedAODCaloJetTag"         , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB1             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB1         , "nSelectedAODCaloJetTagSB1"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB2             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2         , "nSelectedAODCaloJetTagSB2"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB3             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB3         , "nSelectedAODCaloJetTagSB3"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB4             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB4         , "nSelectedAODCaloJetTagSB4"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB5             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB5         , "nSelectedAODCaloJetTagSB5"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB6             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB6         , "nSelectedAODCaloJetTagSB6"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB7             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB7         , "nSelectedAODCaloJetTagSB7"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL1             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL1         , "nSelectedAODCaloJetTagSBL1"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL2             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL2         , "nSelectedAODCaloJetTagSBL2"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL3             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL3         , "nSelectedAODCaloJetTagSBL3"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL4             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL4         , "nSelectedAODCaloJetTagSBL4"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL5             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL5         , "nSelectedAODCaloJetTagSBL5"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL6             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL6         , "nSelectedAODCaloJetTagSBL6"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBL7             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBL7         , "nSelectedAODCaloJetTagSBL7"      , 6, -0.5, 5.5);

      h_nSelectedAODCaloJetTagSB2a             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2a         , "nSelectedAODCaloJetTagSB2a"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB2b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2b         , "nSelectedAODCaloJetTagSB2b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB2c             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2c         , "nSelectedAODCaloJetTagSB2c"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagIP               [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagIP           , "nSelectedAODCaloJetTagIP"        , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBIPa            [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBIPa        , "nSelectedAODCaloJetTagSBIPa"     , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBIPb            [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBIPb        , "nSelectedAODCaloJetTagSBIPb"     , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSBIPc            [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSBIPc        , "nSelectedAODCaloJetTagSBIPc"     , 6, -0.5, 5.5);


      h_nSelectedAODCaloJetTag_0b                [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTag_0b            , "nSelectedAODCaloJetTag_0b"         , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB1_0b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB1_0b         , "nSelectedAODCaloJetTagSB1_0b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB2_0b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2_0b         , "nSelectedAODCaloJetTagSB2_0b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB3_0b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB3_0b         , "nSelectedAODCaloJetTagSB3_0b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTag_1b                [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTag_1b            , "nSelectedAODCaloJetTag_1b"         , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB1_1b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB1_1b         , "nSelectedAODCaloJetTagSB1_1b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB2_1b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2_1b         , "nSelectedAODCaloJetTagSB2_1b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB3_1b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB3_1b         , "nSelectedAODCaloJetTagSB3_1b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTag_2b                [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTag_2b            , "nSelectedAODCaloJetTag_2b"         , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB1_2b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB1_2b         , "nSelectedAODCaloJetTagSB1_2b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB2_2b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB2_2b         , "nSelectedAODCaloJetTagSB2_2b"      , 6, -0.5, 5.5);
      h_nSelectedAODCaloJetTagSB3_2b             [i] = initSingleHistogramTH1F( hname_nSelectedAODCaloJetTagSB3_2b         , "nSelectedAODCaloJetTagSB3_2b"      , 6, -0.5, 5.5);
  }//sel                                                                                                                                                                                
}

//----------------------------fillAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::fillAODCaloJetTagMultHistograms(Float_t weight, int selbin)
{
  hist_file_out[selbin]->cd();
  h_nSelectedAODCaloJetTag       [selbin] ->Fill( float(taggedjet_list.size()), weight );
  h_nSelectedAODCaloJetTagSB1    [selbin] ->Fill( float(taggedjetSB1_list.size()), weight );
  h_nSelectedAODCaloJetTagSB2    [selbin] ->Fill( float(taggedjetSB2_list.size()), weight );
  h_nSelectedAODCaloJetTagSB3    [selbin] ->Fill( float(taggedjetSB3_list.size()), weight );
  h_nSelectedAODCaloJetTagSB4    [selbin] ->Fill( float(taggedjetSB4_list.size()), weight );
  h_nSelectedAODCaloJetTagSB5    [selbin] ->Fill( float(taggedjetSB5_list.size()), weight );
  h_nSelectedAODCaloJetTagSB6    [selbin] ->Fill( float(taggedjetSB6_list.size()), weight );
  h_nSelectedAODCaloJetTagSB7    [selbin] ->Fill( float(taggedjetSB7_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL1    [selbin] ->Fill( float(taggedjetSBL1_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL2    [selbin] ->Fill( float(taggedjetSBL2_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL3    [selbin] ->Fill( float(taggedjetSBL3_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL4    [selbin] ->Fill( float(taggedjetSBL4_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL5    [selbin] ->Fill( float(taggedjetSBL5_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL6    [selbin] ->Fill( float(taggedjetSBL6_list.size()), weight );
  h_nSelectedAODCaloJetTagSBL7    [selbin] ->Fill( float(taggedjetSBL7_list.size()), weight );

  h_nSelectedAODCaloJetTagSB2a    [selbin] ->Fill( float(taggedjetSB2a_list.size()), weight );
  h_nSelectedAODCaloJetTagSB2b    [selbin] ->Fill( float(taggedjetSB2b_list.size()), weight );
  h_nSelectedAODCaloJetTagSB2c    [selbin] ->Fill( float(taggedjetSB2c_list.size()), weight );
  h_nSelectedAODCaloJetTagIP      [selbin] ->Fill( float(taggedjetIP_list.size()), weight );
  h_nSelectedAODCaloJetTagSBIPa    [selbin] ->Fill( float(taggedjetSBIPa_list.size()), weight );
  h_nSelectedAODCaloJetTagSBIPb    [selbin] ->Fill( float(taggedjetSBIPb_list.size()), weight );
  h_nSelectedAODCaloJetTagSBIPc    [selbin] ->Fill( float(taggedjetSBIPc_list.size()), weight );

  if(nBPartonFlavour==0){
    h_nSelectedAODCaloJetTag_0b       [selbin] ->Fill( float(taggedjet_list.size()), weight );
    h_nSelectedAODCaloJetTagSB1_0b    [selbin] ->Fill( float(taggedjetSB1_list.size()), weight );
    h_nSelectedAODCaloJetTagSB2_0b    [selbin] ->Fill( float(taggedjetSB2_list.size()), weight );
    h_nSelectedAODCaloJetTagSB3_0b    [selbin] ->Fill( float(taggedjetSB3_list.size()), weight );
  }
  else if(nBPartonFlavour==1){
    h_nSelectedAODCaloJetTag_1b       [selbin] ->Fill( float(taggedjet_list.size()), weight );
    h_nSelectedAODCaloJetTagSB1_1b    [selbin] ->Fill( float(taggedjetSB1_list.size()), weight );
    h_nSelectedAODCaloJetTagSB2_1b    [selbin] ->Fill( float(taggedjetSB2_list.size()), weight );
    h_nSelectedAODCaloJetTagSB3_1b    [selbin] ->Fill( float(taggedjetSB3_list.size()), weight );
  }
  else if(nBPartonFlavour>=2){
    h_nSelectedAODCaloJetTag_2b       [selbin] ->Fill( float(taggedjet_list.size()), weight );
    h_nSelectedAODCaloJetTagSB1_2b    [selbin] ->Fill( float(taggedjetSB1_list.size()), weight );
    h_nSelectedAODCaloJetTagSB2_2b    [selbin] ->Fill( float(taggedjetSB2_list.size()), weight );
    h_nSelectedAODCaloJetTagSB3_2b    [selbin] ->Fill( float(taggedjetSB3_list.size()), weight );
  }

}

//----------------------------writeAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::writeAODCaloJetTagMultHistograms(int selbin)
{
  hist_file_out[selbin]->cd();

  h_nSelectedAODCaloJetTag       [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB1    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB2    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB3    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB4    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB5    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB6    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB7    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL1    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL2    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL3    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL4    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL5    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL6    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBL7    [selbin] ->Write();

  h_nSelectedAODCaloJetTagSB2a    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB2b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB2c    [selbin] ->Write();
  h_nSelectedAODCaloJetTagIP      [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBIPa    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBIPb    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSBIPc    [selbin] ->Write();

  h_nSelectedAODCaloJetTag_0b       [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB1_0b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB2_0b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB3_0b    [selbin] ->Write();
  h_nSelectedAODCaloJetTag_1b       [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB1_1b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB2_1b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB3_1b    [selbin] ->Write();
  h_nSelectedAODCaloJetTag_2b       [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB1_2b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB2_2b    [selbin] ->Write();
  h_nSelectedAODCaloJetTagSB3_2b    [selbin] ->Write();
}

//----------------------------deleteAODCaloJetTagMultHistograms
Bool_t analyzer_histograms::deleteAODCaloJetTagMultHistograms(int selbin)
{
  //printf("deleteAODCaloJetTagMultHistograms\n");
  hist_file_out[selbin]->cd();

  if(h_nSelectedAODCaloJetTag      [selbin]!=NULL)    h_nSelectedAODCaloJetTag       [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB1   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB1    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB2   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB3   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB3    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB4   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB4    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB5   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB5    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB6   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB6    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB7   [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB7    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL1  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL1    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL2  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL2    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL3  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL3    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL4  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL4    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL5  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL5    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL6  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL6    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBL7  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBL7    [selbin] ->Delete();
  
  if(h_nSelectedAODCaloJetTagSB2a  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2a    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB2b  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB2c  [selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2c    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagIP    [selbin]!=NULL)    h_nSelectedAODCaloJetTagIP      [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBIPa [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBIPa    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBIPb [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBIPb    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSBIPc [selbin]!=NULL)    h_nSelectedAODCaloJetTagSBIPc    [selbin] ->Delete();
  
  if(h_nSelectedAODCaloJetTag_0b   [selbin]!=NULL)    h_nSelectedAODCaloJetTag_0b       [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB1_0b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB1_0b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB2_0b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2_0b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB3_0b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB3_0b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTag_1b   [selbin]!=NULL)    h_nSelectedAODCaloJetTag_1b       [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB1_1b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB1_1b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB2_1b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2_1b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB3_1b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB3_1b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTag_2b   [selbin]!=NULL)    h_nSelectedAODCaloJetTag_2b       [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB1_2b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB1_2b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB2_2b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB2_2b    [selbin] ->Delete();
  if(h_nSelectedAODCaloJetTagSB3_2b[selbin]!=NULL)    h_nSelectedAODCaloJetTagSB3_2b    [selbin] ->Delete();
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
void analyzer_histograms::comb(int n, int r, int *arr, int sz, Float_t weight, TString mistag_name) {

  for (int i = n; i >= r; i --) {

    // choose the first elemente
    arr[r - 1] = i;
    if (r > 1) { // if still needs to choose
      // recursive into smaller problem
      comb(i - 1, r - 1, arr, sz, weight, mistag_name);
    }
    else {

      //x *********************x//
      // have one combo here 
      //x*********************x//
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
	  
	  if(debug) std::cout << "b: " << b << ", term: " << term << std::endl;

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

	  //std::cout << "b: " << b << ", xbin: " << xbin << ", ybin: " << ybin << ", term: " << term << std::endl;

	  h_MistagRate_pteta_sys.at(sz)->Fill(x, y, weight*term);
	  
	}//b
      }

      //Fill estimate from p already calculated 
      if(mistag_name == "PT"){
	h_bkgest_pt->Fill(sz,p*weight);
      }
      else if(mistag_name == "PT-ETA"){
	h_bkgest_pteta->Fill(sz,p*weight);
      }

    }//end of this combo
  }//outer for loop
}


Bool_t analyzer_histograms::initBackgroundEstimateHistograms()
{
  /*
  if(h_bkgest_pt!=NULL) h_bkgest_pt->Clear();
  if(h_bkgest_pteta!=NULL) h_bkgest_pteta->Clear();
  */  

  h_bkgest_pt = initSingleHistogramTH1F("h_bkgest_pt", "h_bkgest_pt", 6, -.5, 5.5);
  h_bkgest_pteta = initSingleHistogramTH1F("h_bkgest_pteta", "h_bkgest_pteta", 6, -.5, 5.5);

  return kTRUE;
}


Bool_t analyzer_histograms::fillBackgroundEstimateHistograms(Float_t weight)
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

  h_bkgest_pt->Write();
  h_bkgest_pteta->Write();

  for(int i=0; i<6; i++){
    h_MistagRate_pt_sys.at(i)->Write();
    h_MistagRate_pteta_sys.at(i)->Write();
  }

  return kTRUE;
}



