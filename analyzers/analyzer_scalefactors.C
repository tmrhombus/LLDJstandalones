#include "analyzer_scalefactors.h"
#include <iostream>

//----------------------------analyzer_scalefactors
analyzer_scalefactors::analyzer_scalefactors() 
{
}

//----------------------------~analyzer_scalefactors
analyzer_scalefactors::~analyzer_scalefactors()
{
}

//----------------------------makeEventWeight
Float_t analyzer_scalefactors::makeEventWeight(Float_t crossSec,
                                        Float_t lumi,
                                        Float_t nrEvents)
{
  // 1.0 for real data
  event_weight=1.0;
  Float_t crossSecScl = crossSec;
  if(isMC){ event_weight=lumi*crossSecScl/nrEvents; }
  //printf("isMC: %i lumi: %0.9f crossSec: %0.9f nrEvents: %0.9f",isMC,lumi,crossSecScl,nrEvents);
  //printf("  event_weight: %0.9f\n",event_weight);

  return event_weight;
}

//----------------------------makePUWeight
Float_t analyzer_scalefactors::makePUWeight( TString dataset ){
 Int_t tmpbin;
 Float_t tmpweight;
 if( dataset.EqualTo("DoubleEG") ){
  tmpbin    = PUWeights_DoubleEG->GetBin(AODnTruePU);
  tmpweight = PUWeights_DoubleEG->GetBinContent(tmpbin);
 }
 else if( dataset.EqualTo("DoubleMu") ){
  tmpbin    = PUWeights_DoubleMu->GetBin(AODnTruePU);
  tmpweight = PUWeights_DoubleMu->GetBinContent(tmpbin);
 }
 else if( dataset.EqualTo("MuonEG") ){
  tmpbin    = PUWeights_MuonEG->GetBin(AODnTruePU);
  tmpweight = PUWeights_MuonEG->GetBinContent(tmpbin);
 }
 else if( dataset.EqualTo("SinglePhoton") ){
  tmpbin    = PUWeights_SinglePhoton->GetBin(AODnTruePU);
  tmpweight = PUWeights_SinglePhoton->GetBinContent(tmpbin);
 }
 //printf("making PU weight for %i , %i, %f \n", AODnTruePU,tmpbin,tmpweight);
 return tmpweight;
}

//----------------------------makeElectronWeight
Float_t analyzer_scalefactors::makeElectronWeight( std::vector<int> &electron_list ){

 Float_t tmpsf;
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
   Float_t tmpweight = EleWeights->GetBinContent(tmpbin);
   tmpsf *= tmpweight;
  }//end electrons
 } // if electrons

 //printf(" done making Electron weight\n");

 return tmpsf;
}

//----------------------------makeMuonWeight ----MuonID weight
Float_t analyzer_scalefactors::makeMuonWeight( std::vector<int> &muon_list ){

 Float_t tmpsf;
 tmpsf = 1.;

 //check overlap with electrons
 if(muon_list.size()>0){
  for(int d=0; d<muon_list.size(); ++d){
   int muindex = muon_list[d];
   Float_t mueta = AOD_muEta->at(muindex);//<------changed; don't have SCEta right now
   Float_t mupt  = AOD_muPt->at(muindex);
   Int_t tmpbinx       = MuonWeights->GetXaxis()->FindBin( mueta );
   Int_t tmpbiny       = MuonWeights->GetYaxis()->FindBin( mupt  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = MuonWeights->GetBin( tmpbinx, tmpbiny );
   Float_t tmpweight = MuonWeights->GetBinContent(tmpbin);
   tmpsf *= tmpweight;
  }//end Muons
 } // if Muons
 return tmpsf;
}

//----------------------------makeMuonIso ----MuonISO weight
Float_t analyzer_scalefactors::makeMuonIso( std::vector<int> &muon_list ){

 Float_t tmpsf;
 tmpsf = 1.;

 //check overlap with electrons
 if(muon_list.size()>0){
  for(int d=0; d<muon_list.size(); ++d){
   int muindex = muon_list[d];
   Float_t mueta = AOD_muEta->at(muindex);//<------changed; don't have SCEta right now
   Float_t mupt  = AOD_muPt->at(muindex);
   Int_t tmpbinx       = MuonIso->GetXaxis()->FindBin( mueta );
   Int_t tmpbiny       = MuonIso->GetYaxis()->FindBin( mupt  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = MuonIso->GetBin( tmpbinx, tmpbiny );
   Float_t tmpweight = MuonIso->GetBinContent(tmpbin);
   tmpsf *= tmpweight;
  }//end Muons
 } // if Muons


 return tmpsf;
}
//----------------------------makeEleTriggerEffi
Float_t analyzer_scalefactors::makeEleTriggerEffi( std::vector<int> &electron_list ){

 Float_t tmpsf, tmpweight;
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
   //if(AOD_elePt->at(eleindex)>23) {EleTrigEffi->Clone("EleTrigEffi1");} //pt>23GeV leading leg's Trig SF
   //else {EleTrigEffi->Clone("EleTrigEffi2");} //pt<23GeV lagging leg's Trig SF
   if(AOD_elePt->at(eleindex)>23){Int_t tmpbinx       = EleTrigEffi1->GetXaxis()->FindBin( eeta );
   Int_t tmpbiny       = EleTrigEffi1->GetYaxis()->FindBin( ept  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = EleTrigEffi1->GetBin( tmpbinx, tmpbiny );
   tmpweight = EleTrigEffi1->GetBinContent(tmpbin);}
   else{Int_t tmpbinx       = EleTrigEffi2->GetXaxis()->FindBin( eeta );
   Int_t tmpbiny       = EleTrigEffi2->GetYaxis()->FindBin( ept  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = EleTrigEffi2->GetBin( tmpbinx, tmpbiny );
   tmpweight = EleTrigEffi2->GetBinContent(tmpbin);}
   tmpsf *= tmpweight; 
  }//end electrons
 } // if electrons

 //printf(" done making Electron weight\n");

 return tmpsf;
}


//----------------------------makeMuonTriggerEffi
Float_t analyzer_scalefactors::makeMuonTriggerEffi( std::vector<int> &muon_list ){

 Float_t tmpsf,tmpweight;
 tmpsf = 1.;

 if(muon_list.size()>0){
  for(int d=0; d<muon_list.size(); ++d){
   int muindex = muon_list[d];
   Float_t mueta = AOD_muEta->at(muindex);//<------changed; don't have SCEta right now
   Float_t mupt  = AOD_muPt->at(muindex);
   if(AOD_muPt->at(muindex)>17) { //pt>17GeV leading leg's Muon Trig SF
   Int_t tmpbinx       = MuonTrigEffi17->GetXaxis()->FindBin( mueta );
   Int_t tmpbiny       = MuonTrigEffi17->GetYaxis()->FindBin( mupt  );
   Int_t tmpbin        = MuonTrigEffi17->GetBin( tmpbinx, tmpbiny );
   tmpweight = MuonTrigEffi17->GetBinContent(tmpbin);}
   else { //pt<17GeV lagging leg's Muon Trig SF
   Int_t tmpbinx       = MuonTrigEffi8->GetXaxis()->FindBin( mueta );
   Int_t tmpbiny       = MuonTrigEffi8->GetYaxis()->FindBin( mupt  );
   Int_t tmpbin        = MuonTrigEffi8->GetBin( tmpbinx, tmpbiny );
   tmpweight = MuonTrigEffi8->GetBinContent(tmpbin);}
   tmpsf *= tmpweight; 
  }//end Muons
 } // if Muons


 return tmpsf;
}
//----------------------------makeTTWeight
Float_t analyzer_scalefactors::makeTTWeight( Float_t TTavgweight){
  Float_t TTSF = 1.; 
  if(toppts->size() == 2){ 
   TTSF =  ( exp( 0.0615 - 0.0005*toppts->at(0)) * exp( 0.0615 - 0.0005*toppts->at(1)) ) / TTavgweight ;
  }
 return TTSF;
}


//----------------------------loadPUWeight
void analyzer_scalefactors::loadPUWeight(){
 std::cout << "loading PU weight" << std::endl;
 TString filename_DoubleEG     = "puWeights_DoubleEG_69200.root" ;
 TString filename_DoubleMu     = "puWeights_DoubleMu_69200.root" ;
 TString filename_MuonEG       = "puWeights_MuonEG_69200.root" ;
 TString filename_SinglePhoton = "puWeights_SinglePhoton_69200.root" ;
 TFile* file_puweights_DoubleEG     = new TFile( filename_DoubleEG     ) ;
 TFile* file_puweights_DoubleMu     = new TFile( filename_DoubleMu     ) ;
 TFile* file_puweights_MuonEG       = new TFile( filename_MuonEG       ) ;
 TFile* file_puweights_SinglePhoton = new TFile( filename_SinglePhoton ) ;
 //std::cout <<" filename: " << filename << std::endl;
 PUWeights_DoubleEG     = (TH1F*)file_puweights_DoubleEG    ->Get("h_PUweight")->Clone("PUWeights_DoubleEG"    );
 PUWeights_DoubleMu     = (TH1F*)file_puweights_DoubleMu    ->Get("h_PUweight")->Clone("PUWeights_DoubleMu"    );
 PUWeights_MuonEG       = (TH1F*)file_puweights_MuonEG      ->Get("h_PUweight")->Clone("PUWeights_MuonEG"      );
 PUWeights_SinglePhoton = (TH1F*)file_puweights_SinglePhoton->Get("h_PUweight")->Clone("PUWeights_SinglePhoton");
 return ;
}
/*
//----------------------------loadTrigEffi
void analyzer_scalefactors::loadTriggerEfficiency(){
 std::cout << "loading Trigger Efficiency" << std::endl;
 TString filename_muon23     = "egammaEffi_MoriondBH_eleTight" ;
 TString filename_muon17     = "egammaEffi_MoriondBH_eleLoose" ;
 TString filename_muon08       = "egammaEffi_MoriondBH_eleMedium" ;
 TString filename_muontk08 = "egammaEffi_MoriondBH_eleTight" ;
 TFile* file_filename_muon23    = new TFile( filename_muon23    ) ;
 TFile* file_filename_muon17    = new TFile( filename_muon17    ) ;
 TFile* file_filename_muon08    = new TFile( filename_muon08    ) ;
 TFile* file_filename_muontk08  = new TFile( filename_muontk08  ) ;
 //std::cout <<" filename: " << filename << std::endl;
 TrigEffi_muon23    = (TH1F*)file_filename_muon23   ->Get("EGamma_SF2D")->Clone("TrigEffi_muon23"   );
 TrigEffi_muon17    = (TH1F*)file_filename_muon17   ->Get("EGamma_SF2D")->Clone("TrigEffi_muon17"   );
 TrigEffi_muon08    = (TH1F*)file_filename_muon08   ->Get("EGamma_SF2D")->Clone("TrigEffi_muon08"   );
 TrigEffi_muontk08  = (TH1F*)file_filename_muontk08 ->Get("EGamma_SF2D")->Clone("TrigEffi_muontk08" );
 return ;
}*/

//----------------------------loadElectronWeight
void analyzer_scalefactors::loadElectronWeight(TString eleid){
 std::cout << "loading Electron weight" << std::endl;
 TString filename = "egammaEffi_MoriondBH_ele"+eleid+".root" ;
 TFile* file_eleweights = new TFile( filename ) ;
 std::cout << " filename: " << filename << std::endl;
 EleWeights = (TH2F*)file_eleweights->Get("EGamma_SF2D")->Clone("EleWeights");
 return ;
}
//----------------------------loadMuonWeight
void analyzer_scalefactors::loadMuonWeight(TString muoid){
 std::cout << "loading Muon weight" << std::endl;
 TString filename = "Run_SF_ID.root" ;
 TFile* file_muonweights = new TFile( filename ) ;
 std::cout << " filename: " << filename << std::endl;
 TString histname = "NUM_"+muoid+"ID_DEN_genTracks_eta_pt" ;
 MuonWeights = (TH2F*)file_muonweights->Get(histname)->Clone("MuonWeights");
 return ;
}

//----------------------------loadMuonIso
void analyzer_scalefactors::loadMuonIso(TString muoid){
 std::cout << "loading Muon Iso" << std::endl;
 TString filename = "Run_SF_ISO.root" ;
 TFile* file_muoniso = new TFile( filename ) ;
 std::cout << " filename: " << filename << std::endl;
 TString histname;
 if (muoid.EqualTo("Loose")) histname = "NUM_LooseRelIso_DEN_LooseID_eta_pt" ; //ISO criteria always given as Loose
 if (muoid.EqualTo("Medium")) histname = "NUM_LooseRelIso_DEN_MediumID_eta_pt" ;
 if (muoid.EqualTo("Tight")) histname = "NUM_LooseRelIso_DEN_TightIDandIPCut_eta_pt" ;
 MuonIso = (TH2F*)file_muoniso->Get(histname)->Clone("MuonIso");
 return ;
}


//----------------------------loadEleTrigEffi
void analyzer_scalefactors::loadEleTriggerEffi(){
 std::cout << "loading Electron Trigger Efficiency" << std::endl;
 TString filename_EleLeg1     = "EleLeg1.root" ;
 TString filename_EleLeg2     = "EleLeg2.root" ;
 TFile* file_EleLeg1     = new TFile( filename_EleLeg1    ) ;
 TFile* file_EleLeg2     = new TFile( filename_EleLeg2    ) ;
 EleTrigEffi1     = (TH2F*)file_EleLeg1    ->Get("TrigEffi")->Clone("EleTrigEffi1"    );
 EleTrigEffi2     = (TH2F*)file_EleLeg2    ->Get("TrigEffi")->Clone("EleTrigEffi2"    );
 //TString filename = "eleleg1.root" ;
 //TFile* file_eletrig = new TFile( filename ) ;
 //EleTrigEffi = (TH2F*)file_eletrig->Get("TrigEffi")->Clone("EleTrigEffi");
 return ;
}

//----------------------------loadMuonTrigEffi
void analyzer_scalefactors::loadMuonTriggerEffi(){
 std::cout << "loading Muon Trigger Efficiency" << std::endl;
 TString filename_Muon17     = "Muon17.root" ;
 TString filename_Muon8     = "Muon8.root" ;
 TFile* file_Muon17     = new TFile( filename_Muon17    ) ;
 TFile* file_Muon8     = new TFile(  filename_Muon8  ) ;
 MuonTrigEffi17     = (TH2F*)file_Muon17    ->Get("TrigEffi")->Clone("MuonTrigEffi17"    );
 MuonTrigEffi8     = (TH2F*)file_Muon8    ->Get("TrigEffi")->Clone("MuonTrigEffi8"    );
 //TString filename = "Muon17.root" ;
 //TFile* file_muontrig = new TFile( filename ) ;
 //MuonTrigEffi = (TH2F*)file_muontrig->Get("TrigEffi")->Clone("MuonTrigEffi");
 return ;
}

//----------------------------loadMistagRate
void analyzer_scalefactors::loadMistagRate(){

  TFile* fMistagRate = TFile::Open("feff_ZH.root", "READ");

  h_MistagRate_pt = (TH1F*)fMistagRate->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVar");
  //Systematics
  for(int i=0; i<6; i++){
    TString num = ""; num+= i;
    TString name = h_MistagRate_pt->GetName(); name+= "_sys_"; name += num;
    TH1F* temp = (TH1F*)h_MistagRate_pt->Clone();
    temp->SetName( name );
    temp->Reset();
    h_MistagRate_pt_sys.push_back( temp );
  }

  h_MistagRate_pteta = (TH2F*)fMistagRate->Get("h_eff_mu_ZH_AllJets_AODCaloJetPtVarAbsEtaVar");
  //Systematics
  for(int i=0; i<6; i++){
    TString num = ""; num+= i;
    TString name = h_MistagRate_pteta->GetName(); name+= "_sys_"; name += num;

    //TH2F* temp = (TH2F*)h_MistagRate_pteta->Clone();
    //temp->SetName( name );
    //temp->Reset();

    //For some reason the normal way leads to bizarre seg faults.  
    //Recreate from scratch:
    const int Pt_n_xbins = 10;
    float Pt_xbins[Pt_n_xbins+1] = {0, 10, 20, 30, 40, 50, 75, 100, 150, 250, 500};
    const int AbsEta_n_bins = 2;
    float AbsEta_bins[AbsEta_n_bins+1] = {0, 1.5, 2.4};
    TH2F* temp = new TH2F(name, name, Pt_n_xbins, Pt_xbins, AbsEta_n_bins, AbsEta_bins);

    h_MistagRate_pteta_sys.push_back( temp );
  }
  return;
}


