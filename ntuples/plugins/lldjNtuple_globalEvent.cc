#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"
#include <iomanip>
#include <bitset>
using namespace std;

// (local) variables associated with tree branches
const int bitsize=12;
Int_t       run_;
Long64_t    event_;
Int_t       lumis_;
Bool_t      isData_;
Int_t       nVtx_;
Int_t       nGoodVtx_;
Int_t       nTrksPV_;
Bool_t      isPVGood_;
float       vtx_;
float       vty_;
float       vtz_;
float       rho_;
float       rhoCentral_;
//can probably get rid of these? leftover from other code?
ULong64_t   HLTEleMuX_;
ULong64_t   HLTPho_;
ULong64_t   HLTJet_;
ULong64_t   HLTEleMuXIsPrescaled_;
ULong64_t   HLTPhoIsPrescaled_;
ULong64_t   HLTJetIsPrescaled_;
vector<int> phoPrescale_;

//ULong64_t   HLT_PFHT300PFMET110_;//everyone seemed to be against this at the meeting?
//ULong64_t   HLT_Ele23Loose_;

ULong64_t   HLT_Ele22eta2p1Loose_;
ULong64_t   HLT_Ele27Tight_;
ULong64_t   HLT_Ele17Ele12_;
ULong64_t   HLT_Ele23Ele12_;

ULong64_t   HLT_IsoMu24_;
ULong64_t   HLT_IsoTkMu24_;
ULong64_t   HLT_Mu17Mu8_;
ULong64_t   HLT_Mu17TkMu8_;

/* 
ULong64_t   HLT_Ele27_WPLoose_Gsf_WHbbBoost_;

ULong64_t   HLT_Ele27_WPLoose_Gsf_WHbbBoost_isPS_;
ULong64_t   HLT_PFHT300PFMET110_isPS_;
*/
//ULong64_t   HLT_Ele23Loose_isPS_;

ULong64_t   HLT_Ele22eta2p1Loose_isPS_;
ULong64_t   HLT_Ele27Tight_isPS_;
ULong64_t   HLT_Ele17Ele12_isPS_;
ULong64_t   HLT_Ele23Ele12_isPS_;

ULong64_t   HLT_IsoMu24_isPS_;
ULong64_t   HLT_IsoTkMu24_isPS_;
ULong64_t   HLT_Mu17Mu8_isPS_;
ULong64_t   HLT_Mu17TkMu8_isPS_;

void lldjNtuple::branchesGlobalEvent(TTree* tree) {

  tree->Branch("run",     	       &run_);
  tree->Branch("event",    	       &event_);
  tree->Branch("lumis",   	       &lumis_);
  tree->Branch("isData",  	       &isData_);
  tree->Branch("nVtx",                 &nVtx_);
  tree->Branch("nGoodVtx",             &nGoodVtx_);
  tree->Branch("nTrksPV",              &nTrksPV_);
  tree->Branch("isPVGood",             &isPVGood_);
  tree->Branch("vtx",                  &vtx_);
  tree->Branch("vty",                  &vty_);
  tree->Branch("vtz",                  &vtz_);
  tree->Branch("rho",                  &rho_);
  tree->Branch("rhoCentral",           &rhoCentral_);
  tree->Branch("HLTEleMuX",            &HLTEleMuX_);
  tree->Branch("HLTPho",               &HLTPho_);
  tree->Branch("HLTJet",               &HLTJet_);
  tree->Branch("HLTEleMuXIsPrescaled", &HLTEleMuXIsPrescaled_);
  tree->Branch("HLTPhoIsPrescaled",    &HLTPhoIsPrescaled_);
  tree->Branch("HLTJetIsPrescaled",    &HLTJetIsPrescaled_);
  tree->Branch("phoPrescale",          &phoPrescale_);
  
  /*
  tree->Branch("HLT_PFHT300PFMET110",  &HLT_PFHT300PFMET110_);
  tree->Branch("HLT_Ele27_WPLoose_Gsf_WHbbBoost", &HLT_Ele27_WPLoose_Gsf_WHbbBoost_);
  */  
  //tree->Branch("HLT_Ele23Loose",       &HLT_Ele23Loose_) ;
  
  tree->Branch("HLT_Ele22eta2p1Loose_", &HLT_Ele22eta2p1Loose_);
  tree->Branch("HLT_Ele27Tight",        &HLT_Ele27Tight_) ;
  tree->Branch("HLT_Ele17Ele12",        &HLT_Ele17Ele12_) ;
  tree->Branch("HLT_Ele23Ele12",        &HLT_Ele23Ele12_) ;

  tree->Branch("HLT_IsoMu24"  ,         &HLT_IsoMu24_)   ;
  tree->Branch("HLT_IsoTkMu24",         &HLT_IsoTkMu24_) ;
  tree->Branch("HLT_Mu17Mu8"  ,         &HLT_Mu17Mu8_)   ;
  tree->Branch("HLT_Mu17TkMu8",         &HLT_Mu17TkMu8_) ;

  tree->Branch("HLT_Ele22eta2p1Loose_isPS_", &HLT_Ele22eta2p1Loose_isPS_);
  tree->Branch("HLT_Ele27Tight_isPS_",        &HLT_Ele27Tight_isPS_) ;
  tree->Branch("HLT_Ele17Ele12_isPS_",        &HLT_Ele17Ele12_isPS_) ;
  tree->Branch("HLT_Ele23Ele12_isPS_",        &HLT_Ele23Ele12_isPS_) ;

  tree->Branch("HLT_IsoMu24_isPS_"  ,         &HLT_IsoMu24_isPS_)   ;
  tree->Branch("HLT_IsoTkMu24_isPS_",         &HLT_IsoTkMu24_isPS_) ;
  tree->Branch("HLT_Mu17Mu8_isPS_"  ,         &HLT_Mu17Mu8_isPS_)   ;
  tree->Branch("HLT_Mu17TkMu8_isPS_",         &HLT_Mu17TkMu8_isPS_) ;

}

void lldjNtuple::fillGlobalEvent(const edm::Event& e, const edm::EventSetup& es) {

  phoPrescale_.clear();

  edm::Handle<double> rhoHandle;
  e.getByToken(rhoLabel_, rhoHandle);

  edm::Handle<double> rhoCentralHandle;
  e.getByToken(rhoCentralLabel_, rhoCentralHandle);

  run_    = e.id().run();
  event_  = e.id().event();
  lumis_  = e.luminosityBlock();
  isData_ = e.isRealData();
  rho_    = *(rhoHandle.product());
  if (rhoCentralHandle.isValid()) rhoCentral_ = *(rhoCentralHandle.product());
  else rhoCentral_ = -99.;

  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);

  nVtx_     = -1;
  nGoodVtx_ = -1;
  if (vtxHandle.isValid())
  {
   nVtx_     = 0;
   nGoodVtx_ = 0;

   for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v)
   {
    if (nVtx_ == 0)
    {
     nTrksPV_ = v->nTracks();
     vtx_     = v->x();
     vty_     = v->y();
     vtz_     = v->z();

     isPVGood_ = false;
     if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) isPVGood_ = true;
    }

    if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) nGoodVtx_++;
    nVtx_++;
   }
  }
  else {edm::LogWarning("lldjNtuple") << "Primary vertices info not unavailable";}

  // HLT treatment
  HLTEleMuX_            = 0;
  HLTPho_               = 0;
  HLTJet_               = 0;
  HLTEleMuXIsPrescaled_ = 0;
  HLTPhoIsPrescaled_    = 0;
  HLTJetIsPrescaled_    = 0;
  
  /*
  HLT_PFHT300PFMET110_  = 0;
  HLT_Ele27_WPLoose_Gsf_WHbbBoost_ =0;
  */
  //HLT_Ele23Loose_       = 0;
  
  HLT_Ele22eta2p1Loose_ = 0;
  HLT_Ele27Tight_       = 0;
  HLT_Ele17Ele12_       = 0;
  HLT_Ele23Ele12_       = 0;

  HLT_IsoMu24_          = 0;
  HLT_IsoTkMu24_        = 0;
  HLT_Mu17Mu8_          = 0;
  HLT_Mu17TkMu8_        = 0;

  bool cfg_changed = true;
  HLTConfigProvider hltCfg;
  hltCfg.init(e.getRun(), es, trgResultsProcess_, cfg_changed);

  edm::Handle<edm::TriggerResults> trgResultsHandle;
  e.getByToken(trgResultsLabel_, trgResultsHandle);

  //edm::Handle<edm::TriggerResults> triggerBits;
  //edm::Handle<pat::TriggerObjectStandAlone> triggerObjects;
  //edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

  //e.getByToken(triggerBits_, triggerBits);
  //e.getByToken(triggerObjects_, triggerObjects);
  //e.getByToken(triggerPrescales_, triggerPrescales);
  
  const edm::TriggerNames &trgNames = e.triggerNames(*trgResultsHandle);
  //const edm::TriggerNames &names = e.triggerNames(*triggerBits);
  
  /*  To print out trigger names initially
  for (size_t i = 0; i < trgNames.size(); ++i) {
    const string &name = trgNames.triggerName(i);
    printf(" Reading trigger: %s\n" , name.c_str()  );
  }
  */
 
  /* wanted to try alternate method of getting these values
  std::cout << "\n == TRIGGER PATHS= " << std::endl;
  for (unsigned int i = 0, n = trgResultsHandle->size(); i < n; ++i) {
     std::cout << "Trigger " << trgNames.triggerName(i) <<
     ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
     ": " << (trgResultsHandle->accept(i) ? "PASS" : "fail (or not run)")
     << std::endl;
  }*/

  for (size_t i = 0; i < trgNames.size(); ++i) {
    const string &name = trgNames.triggerName(i);

    // HLT name => bit correspondence 
    /* This not in H runs, no alternative other than HLT_Ele22_eta2p1_WPLoose_Gsf or HLT_Ele27_WPLoose_Gsf_WHbbBoost 
    int bitEle23Loose = -1;
    if      (name.find("HLT_Ele23_WPLoose_Gsf_v1")  != string::npos) bitEle23Loose = 0  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v2")  != string::npos) bitEle23Loose = 1  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v3")  != string::npos) bitEle23Loose = 2  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v4")  != string::npos) bitEle23Loose = 3  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v5")  != string::npos) bitEle23Loose = 4  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v6")  != string::npos) bitEle23Loose = 5  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v7")  != string::npos) bitEle23Loose = 6  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v8")  != string::npos) bitEle23Loose = 7  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v9")  != string::npos) bitEle23Loose = 8  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v10") != string::npos) bitEle23Loose = 9  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v11") != string::npos) bitEle23Loose = 10 ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v12") != string::npos) bitEle23Loose = 11 ;
    */
    /*
    int bitEle27LooseWHbb = -1
    if      (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v1")  != string::npos) bitEle27LooseWHbb = 0 ;
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v2")  != string::npos) bitEle27LooseWHbb = 1 ;
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v3")  != string::npos) bitEle27LooseWHbb = 2 ; 
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v4")  != string::npos) bitEle27LooseWHbb = 3 ;
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v5")  != string::npos) bitEle27LooseWHbb = 4 ; 
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v6")  != string::npos) bitEle27LooseWHbb = 5 ;
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v7")  != string::npos) bitEle27LooseWHbb = 6 ;
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v8")  != string::npos) bitEle27LooseWHbb = 7 ;
    else if (name.find("HLT_Ele27_WPLoose_Gsf_WHbbBoost_v9")  != string::npos) bitEle27LooseWHbb = 8 ;
    */
    
    // Single Electron
    int bitEle22eta2p1Loose =-1; //runs v3-v9
    if      (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v1") != string::npos) bitEle22eta2p1Loose = 0;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v2") != string::npos) bitEle22eta2p1Loose = 1;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v3") != string::npos) bitEle22eta2p1Loose = 2;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v4") != string::npos) bitEle22eta2p1Loose = 3; 
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v5") != string::npos) bitEle22eta2p1Loose = 4;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v6") != string::npos) bitEle22eta2p1Loose = 5;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v7") != string::npos) bitEle22eta2p1Loose = 6;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v8") != string::npos) bitEle22eta2p1Loose = 7;
    else if (name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v9") != string::npos) bitEle22eta2p1Loose = 8;
        
    int bitEle27Tight = -1; //runs v1-v7
    if      (name.find("HLT_Ele27_WPTight_Gsf_v1")  != string::npos) bitEle27Tight = 0 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v2")  != string::npos) bitEle27Tight = 1 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v3")  != string::npos) bitEle27Tight = 2 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v4")  != string::npos) bitEle27Tight = 3 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v5")  != string::npos) bitEle27Tight = 4 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v6")  != string::npos) bitEle27Tight = 5 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v7")  != string::npos) bitEle27Tight = 6 ;
    
    // Double Electron
    int bitEle17Ele12 = -1; //runs v3-v9
    if      (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")  != string::npos) bitEle17Ele12 = 0 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2")  != string::npos) bitEle17Ele12 = 1 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3")  != string::npos) bitEle17Ele12 = 2 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4")  != string::npos) bitEle17Ele12 = 3 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5")  != string::npos) bitEle17Ele12 = 4 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6")  != string::npos) bitEle17Ele12 = 5 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7")  != string::npos) bitEle17Ele12 = 6 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8")  != string::npos) bitEle17Ele12 = 7 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9")  != string::npos) bitEle17Ele12 = 8 ;

    int bitEle23Ele12 = -1; //runs v3-v9
    if      (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")  != string::npos) bitEle23Ele12 = 0 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2")  != string::npos) bitEle23Ele12 = 1 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3")  != string::npos) bitEle23Ele12 = 2 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4")  != string::npos) bitEle23Ele12 = 3 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5")  != string::npos) bitEle23Ele12 = 4 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6")  != string::npos) bitEle23Ele12 = 5 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7")  != string::npos) bitEle23Ele12 = 6 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8")  != string::npos) bitEle23Ele12 = 7 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9")  != string::npos) bitEle23Ele12 = 8 ;

    // Single Iso Mu
    int bitIsoMu24   = -1; //runs v1-v4
    if      (name.find("HLT_IsoMu24_v1") != string::npos) bitIsoMu24 = 0 ;
    else if (name.find("HLT_IsoMu24_v2") != string::npos) bitIsoMu24 = 1 ;
    else if (name.find("HLT_IsoMu24_v3") != string::npos) bitIsoMu24 = 2 ;
    else if (name.find("HLT_IsoMu24_v4") != string::npos) bitIsoMu24 = 3 ;

    int bitIsoTkMu24 = -1; //runs v1-v4
    if      (name.find("HLT_IsoTkMu24_v1")  != string::npos) bitIsoTkMu24 = 0 ;
    else if (name.find("HLT_IsoTkMu24_v2")  != string::npos) bitIsoTkMu24 = 1 ;
    else if (name.find("HLT_IsoTkMu24_v3")  != string::npos) bitIsoTkMu24 = 2 ;
    else if (name.find("HLT_IsoTkMu24_v4")  != string::npos) bitIsoTkMu24 = 3 ;

    // Double Iso Mu
    int bitMu17Mu8   = -1; //runs v2,v3,v4,v7
    if      (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17Mu8 = 0 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17Mu8 = 1 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17Mu8 = 2 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17Mu8 = 3 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17Mu8 = 4 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17Mu8 = 5 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7") != string::npos) bitMu17Mu8 = 6 ;

    int bitMu17TkMu8 = -1; //runs v2,v3,v6
    if      (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17TkMu8 = 0 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17TkMu8 = 1 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17TkMu8 = 2 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17TkMu8 = 3 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17TkMu8 = 4 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17TkMu8 = 5 ;                   

    // Photon triggers
    int bitPho    = -1;
    if      (name.find("HLT_Photon22_v")                    != string::npos) bitPho =  0; //bit0(lowest)
    else if (name.find("HLT_Photon30_v")                    != string::npos) bitPho =  1;
    else if (name.find("HLT_Photon36_v")                    != string::npos) bitPho =  2;
    else if (name.find("HLT_Photon50_v")                    != string::npos) bitPho =  3;
    else if (name.find("HLT_Photon75_v")                    != string::npos) bitPho =  4;
    else if (name.find("HLT_Photon90_v")                    != string::npos) bitPho =  5;
    else if (name.find("HLT_Photon120_v")                   != string::npos) bitPho =  6;
    else if (name.find("HLT_Photon175_v")                   != string::npos) bitPho =  7;
    else if (name.find("HLT_Photon250_NoHE_v")              != string::npos) bitPho =  8;
    else if (name.find("HLT_Photon300_NoHE_v")              != string::npos) bitPho =  9;
    else if (name.find("HLT_Photon500_v")                   != string::npos) bitPho = 10;
    else if (name.find("HLT_Photon600_v")                   != string::npos) bitPho = 11;
    else if (name.find("HLT_Photon165_HE10_v")              != string::npos) bitPho = 12;
    else if (name.find("HLT_Photon135_PFMET100_v")                          != string::npos) bitPho = 18;
    else if (name.find("HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v")  != string::npos) bitPho = 19;
    else if (name.find("HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_VBF_v")       != string::npos) bitPho = 20;
    else if (name.find("HLT_Photon90_CaloIdL_PFHT600_v")                    != string::npos) bitPho = 21;
    else if (name.find("HLT_DoublePhoton60_v")                              != string::npos) bitPho = 22;
    else if (name.find("HLT_DoublePhoton85_v")                              != string::npos) bitPho = 23;
    else if (name.find("HLT_Photon22_R9Id90_HE10_IsoM_v")                   != string::npos) bitPho = 24;

    // Jet triggers
    // PF HT 350 MET 100
    /*
    int bitPFHT350PFMET100 = -1;
    if      (name.find("HLT_PFHT350_PFMET100_v1")              != string::npos) bitPFHT350PFMET100 = 0 ;
    else if (name.find("HLT_PFHT350_PFMET100_JetIdCleaned_v1") != string::npos) bitPFHT350PFMET100 = 1 ;
    else if (name.find("HLT_PFHT350_PFMET100_JetIdCleaned_v2") != string::npos) bitPFHT350PFMET100 = 2 ;
    
    int bitPFHT300PFMET110 = -1;
    if      (name.find("HLT_PFHT300_PFMET110_v1")              != string::npos) bitPFHT300PFMET110 = 0 ;
    else if (name.find("HLT_PFHT300_PFMET110_v2") 	       != string::npos) bitPFHT300PFMET110 = 1 ;	
    else if (name.find("HLT_PFHT300_PFMET110_v3")              != string::npos) bitPFHT300PFMET110 = 2 ;
    else if (name.find("HLT_PFHT300_PFMET110_v4")              != string::npos) bitPFHT300PFMET110 = 3 ;
    else if (name.find("HLT_PFHT300_PFMET110_v5")              != string::npos) bitPFHT300PFMET110 = 4 ;
    else if (name.find("HLT_PFHT300_PFMET110_v6")              != string::npos) bitPFHT300PFMET110 = 5 ;
    */
     int bitJet    = -1;//Can add these anytime if we need them, have readouts ready
    if      (name.find("HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v")                    != string::npos) bitJet =  0;
    else if (name.find("HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v")                    != string::npos) bitJet =  1; 
    else if (name.find("HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v")                != string::npos) bitJet =  2; 
    else if (name.find("HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v")                != string::npos) bitJet =  3; 
    else if (name.find("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v")                      != string::npos) bitJet =  4;
    else if (name.find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v")                    != string::npos) bitJet =  5;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")                    != string::npos) bitJet =  6;
    else if (name.find("HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != string::npos) bitJet =  7;
    else if (name.find("HLT_PFMET170_HBHECleaned_v")                                 != string::npos) bitJet =  8;
    else if (name.find("HLT_CaloJet500_NoJetID_v")                                   != string::npos) bitJet =  9;
    else if (name.find("HLT_PFJet40_v")                                              != string::npos) bitJet = 10; 
    else if (name.find("HLT_PFJet60_v")                                              != string::npos) bitJet = 11; 
    else if (name.find("HLT_PFJet80_v")                                              != string::npos) bitJet = 12; 
    else if (name.find("HLT_PFJet140_v")                                             != string::npos) bitJet = 13; 
    else if (name.find("HLT_PFJet200_v")                                             != string::npos) bitJet = 14; 
    else if (name.find("HLT_PFJet260_v")                                             != string::npos) bitJet = 15; 
    else if (name.find("HLT_PFJet320_v")                                             != string::npos) bitJet = 16; 
    else if (name.find("HLT_PFJet400_v")                                             != string::npos) bitJet = 17; 
    else if (name.find("HLT_PFJet450_v")                                             != string::npos) bitJet = 18;    
    else if (name.find("HLT_PFJet500_v")                                             != string::npos) bitJet = 19; 
    else if (name.find("HLT_AK8PFHT700_TrimR0p1PT0p3Mass50_v")                       != string::npos) bitJet = 20; 
    else if (name.find("HLT_AK8PFJet360_TrimMass30_v")                               != string::npos) bitJet = 21;
    else if (name.find("HLT_PFHT300_PFMET110_v")                                     != string::npos) bitJet = 22;
    else if (name.find("HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067_v")   != string::npos) bitJet = 23;
    else if (name.find("HLT_PFMET170_HBHE_BeamHaloCleaned_v")                        != string::npos) bitJet = 24;
    else if (name.find("HLT_PFMET300_v")                                             != string::npos) bitJet = 25;
    else if (name.find("HLT_PFMET110_PFMHT110_IDTight_v")                            != string::npos) bitJet = 26;
    else if (name.find("HLT_PFMET120_PFMHT120_IDTight_v")                            != string::npos) bitJet = 27;
    else if (name.find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v")                    != string::npos) bitJet = 28;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")                    != string::npos) bitJet = 29;
    else if (name.find("HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v") != string::npos) bitJet = 30;
    else if (name.find("HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_v") != string::npos) bitJet = 31;
    else if (name.find("HLT_PFHT800_v")                                              != string::npos) bitJet = 32;
    else if (name.find("HLT_PFHT900_v")                                              != string::npos) bitJet = 33;
    else if (name.find("HLT_PFHT750_4JetPt50_v")                                     != string::npos) bitJet = 34;
    else if (name.find("HLT_PFHT750_4JetPt70_v")                                     != string::npos) bitJet = 35;
    else if (name.find("HLT_PFHT800_4JetPt50_v")                                     != string::npos) bitJet = 36;

    // indicates prescaling and whether trigger was fired or not
    ULong64_t isPrescaled = (hltCfg.prescaleValue(0, name)!=1) ? 1 : 0;
    ULong64_t isFired     = (trgResultsHandle->accept(i)) ? 1 : 0;
    /*
    if ( bitPFHT300PFMET110 >= 0 ){
     HLT_PFHT300PFMET110_       |= (isFired     << bitPFHT300PFMET110 );
     HLT_PFHT300PFMET110_isPS_  |= (isPrescaled << bitPFHT300PFMET110 );
    }
    */

    if ( bitEle22eta2p1Loose    >= 0 ){
     HLT_Ele22eta2p1Loose_            |= (isFired     << bitEle22eta2p1Loose  );
     HLT_Ele22eta2p1Loose_isPS_       |= (isPrescaled << bitEle22eta2p1Loose  );
    }
    if ( bitEle27Tight          >= 0 ){     
     HLT_Ele27Tight_                  |= (isFired     << bitEle27Tight        );
     HLT_Ele27Tight_isPS_             |= (isPrescaled << bitEle27Tight        );
    }
    if ( bitEle17Ele12          >= 0 ){     
     HLT_Ele17Ele12_                  |= (isFired     << bitEle17Ele12        );
     HLT_Ele17Ele12_isPS_             |= (isPrescaled << bitEle17Ele12        );
    }
    if ( bitEle23Ele12          >= 0 ){     
     HLT_Ele23Ele12_                  |= (isFired     << bitEle23Ele12        );
     HLT_Ele23Ele12_isPS_             |= (isPrescaled << bitEle23Ele12        );
    }

    if ( bitIsoMu24              >= 0 ){   
     HLT_IsoMu24_                     |= (isFired     << bitIsoMu24           );
     HLT_IsoMu24_isPS_                |= (isPrescaled << bitIsoMu24           );
    }
    if ( bitIsoTkMu24            >= 0 ){     
     HLT_IsoTkMu24_                   |= (isFired     << bitIsoTkMu24         );
     HLT_IsoTkMu24_isPS_              |= (isPrescaled << bitIsoTkMu24         );
    }
    if ( bitMu17Mu8              >= 0 ){   
     HLT_Mu17Mu8_                     |= (isFired     << bitMu17Mu8           );
     HLT_Mu17Mu8_isPS_                |= (isPrescaled << bitMu17Mu8           );
    }
    if ( bitMu17TkMu8            >= 0 ){     
     HLT_Mu17TkMu8_                   |= (isFired     << bitMu17TkMu8         );
     HLT_Mu17TkMu8_isPS_              |= (isPrescaled << bitMu17TkMu8         );
    }


    // if (bitEleMuX >= 0) {
    //   HLTEleMuX_            |= (isFired << bitEleMuX);
    //   HLTEleMuXIsPrescaled_ |= (isPrescaled << bitEleMuX);
    // }
    
    if (bitPho >= 0) {
      HLTPho_            |= (isFired << bitPho);
      HLTPhoIsPrescaled_ |= (isPrescaled << bitPho);
    }
    
    if (bitJet >= 0) {
      HLTJet_            |= (isFired << bitJet);
      HLTJetIsPrescaled_ |= (isPrescaled << bitJet);
    }

    /*
    if (bitEle27LooseWHbb  >= 0) {
      HLT_Ele27_WPLoose_Gsf_WHbbBoost_ |= (isFired <<  bitEle27LooseWHbb);
      HLT_Ele27_WPLoose_Gsf_WHbbBoost_ |= (isPrescaled <<  bitEle27LooseWHbb);
     }
    if ( bitPFHT300PFMET110 >= 0 ){
      HLT_PFHT300PFMET110_       |= (isFired     << bitPFHT300PFMET110 );
      HLT_PFHT300PFMET110_isPS_  |= (isPrescaled << bitPFHT300PFMET110 );
    }
    */
//printouts to see if everything is ok
/*    
    //int prescaleSet(const edm::Event& e, const edm::EventSetup& es); //const;
    unsigned preScaleV = hltCfg.prescaleValue(0, name);
    //std::bitset<bitsize> HLT_PFHT300PFMET110_b(bitPFHT300PFMET110);
    // intb
    std::bitset<bitsize> HLT_Ele22eta2p1Loose_b(bitEle22eta2p1Loose);
    std::bitset<bitsize> HLT_Ele27Tight_b(bitEle27Tight);
    std::bitset<bitsize> HLT_Ele17Ele12_b(bitEle17Ele12);
    std::bitset<bitsize> HLT_Ele23Ele12_b(bitEle23Ele12);
    std::bitset<bitsize> HLT_IsoMu24_b(bitIsoMu24);
    std::bitset<bitsize> HLT_IsoTkMu24_b(bitIsoTkMu24);
    std::bitset<bitsize> HLT_Mu17Mu8_b(bitMu17Mu8);
    std::bitset<bitsize> HLT_Mu17TkMu8_b(bitMu17TkMu8);
    // Ub
    std::bitset<bitsize> HLT_Ele22eta2p1Loose_b2(HLT_Ele22eta2p1Loose_);
    std::bitset<bitsize> HLT_Ele27Tight_b2(HLT_Ele27Tight_);
    std::bitset<bitsize> HLT_Ele17Ele12_b2(HLT_Ele17Ele12_);
    std::bitset<bitsize> HLT_Ele23Ele12_b2(HLT_Ele23Ele12_);
    std::bitset<bitsize> HLT_IsoMu24_b2(HLT_IsoMu24_);
    std::bitset<bitsize> HLT_IsoTkMu24_b2(HLT_IsoTkMu24_);
    std::bitset<bitsize> HLT_Mu17Mu8_b2(HLT_Mu17Mu8_);
    std::bitset<bitsize> HLT_Mu17TkMu8_b2(HLT_Mu17TkMu8_);
    // PSb
    std::bitset<bitsize> HLT_Ele22eta2p1Loose_b3(HLT_Ele22eta2p1Loose_isPS_);
    std::bitset<bitsize> HLT_Ele27Tight_b3(HLT_Ele27Tight_isPS_);
    std::bitset<bitsize> HLT_Ele17Ele12_b3(HLT_Ele17Ele12_isPS_);
    std::bitset<bitsize> HLT_Ele23Ele12_b3(HLT_Ele23Ele12_isPS_);
    std::bitset<bitsize> HLT_IsoMu24_b3(HLT_IsoMu24_isPS_);
    std::bitset<bitsize> HLT_IsoTkMu24_b3(HLT_IsoTkMu24_isPS_);
    std::bitset<bitsize> HLT_Mu17Mu8_b3(HLT_Mu17Mu8_isPS_);
    std::bitset<bitsize> HLT_Mu17TkMu8_b3(HLT_Mu17TkMu8_isPS_);
 
    //if     (name.find("HLT_PFHT300_PFMET110_v")                     != string::npos){cout<<name<<" "<<HLT_PFHT300PFMET110_b<<" "
    //<<bitPFHT300PFMET110<<" "<<HLT_PFHT300PFMET110_<<" prescale: "<<(hltCfg.prescaleValue(0, name))<<endl;}
         if(name.find("HLT_Ele22_eta2p1_WPLoose_Gsf_v")             != string::npos){cout<<name<<" intb: "<<HLT_Ele22eta2p1Loose_b <<" int: " <<bitEle22eta2p1Loose 
    <<" U: "<<HLT_Ele22eta2p1Loose_<<" Ub: "<<HLT_Ele22eta2p1Loose_b2<<" prescale: "<<preScaleV <<" PSb: "<<HLT_Ele22eta2p1Loose_b3<<endl;}
    else if(name.find("HLT_Ele27_WPTight_Gsf_v")                    != string::npos){cout<<name<<" intb: "<<HLT_Ele27Tight_b       <<" int: " <<bitEle27Tight       
    <<" U: "<<HLT_Ele27Tight_      <<" Ub: "<<HLT_Ele27Tight_b2      <<" prescale: "<<preScaleV <<" PSb: "<<HLT_Ele27Tight_b3      <<endl;}
    else if(name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")!= string::npos){cout<<name<<" intb: "<<HLT_Ele17Ele12_b       <<" int: " <<bitEle17Ele12       
    <<" U: "<<HLT_Ele17Ele12_      <<" Ub: "<<HLT_Ele17Ele12_b2      <<" prescale: "<<preScaleV <<" PSb: "<<HLT_Ele17Ele12_b3      <<endl;}
    else if(name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")!= string::npos){cout<<name<<" intb: "<<HLT_Ele23Ele12_b       <<" int: " <<bitEle23Ele12       
    <<" U: "<<HLT_Ele23Ele12_      <<" Ub: "<<HLT_Ele23Ele12_b2      <<" prescale: "<<preScaleV <<" PSb: "<<HLT_Ele23Ele12_b3      <<endl;}
    else if(name.find("HLT_IsoMu24_v")                              != string::npos){cout<<name<<" intb: "<<HLT_IsoMu24_b          <<" int: " <<bitIsoMu24          
    <<" U: "<<HLT_IsoMu24_         <<" Ub: "<<HLT_IsoMu24_b2         <<" prescale: "<<preScaleV<<" PSb: "<<HLT_IsoMu24_b3          <<endl;}
    else if(name.find("HLT_IsoTkMu24_v")                            != string::npos){cout<<name<<" intb: "<<HLT_IsoTkMu24_b        <<" int: "<<bitIsoTkMu24        
    <<" U: "<<HLT_IsoTkMu24_       <<" Ub: "<<HLT_IsoTkMu24_b2       <<" prescale: "<<preScaleV<<" PSb: "<<HLT_IsoTkMu24_b3        <<endl;}
    else if(name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v")      != string::npos){cout<<name<<" intb: "<<HLT_Mu17Mu8_b          <<" int: "<<bitMu17Mu8          
    <<" U: "<<HLT_Mu17Mu8_         <<" Ub: "<<HLT_Mu17Mu8_b2         <<" prescale: "<<preScaleV<<" PSb: "<<HLT_Mu17Mu8_b3          <<endl;}
    else if(name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")    != string::npos){cout<<name<<" intb: "<<HLT_Mu17TkMu8_b        <<" int: "<<bitMu17TkMu8        
    <<" U:  "<<HLT_Mu17TkMu8_      <<" Ub: "<<HLT_Mu17TkMu8_b2       <<" prescale: "<<preScaleV<<" PSb: "<<HLT_Mu17TkMu8_b3        <<endl;}
 */   

    if      (name.find("HLT_Photon22_v")       != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon30_v")       != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon36_v")       != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon50_v")       != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon75_v")       != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon90_v")       != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon120_v")      != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon175_v")      != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));
    else if (name.find("HLT_Photon250_NoHE_v") != string::npos) phoPrescale_.push_back(hltCfg.prescaleValue(0, name));

  }

}
