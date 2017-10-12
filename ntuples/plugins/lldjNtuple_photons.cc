#include <TString.h>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

Int_t            nPho_;
vector<float>    phoPt_;
vector<float>    phoEn_;
vector<float>    phoEta_;
vector<float>    phoPhi_;

vector<float>    phoSCEn_;
vector<float>    phoSCEta_;
vector<float>    phoSCPhi_;

vector<UShort_t> phoIDbit_;
vector<Float_t>  phoIDMVA_;

vector<float>    phoObjPFChIso_;
vector<float>    phoObjPFPhoIso_;
vector<float>    phoObjPFNeuIso_;
vector<float>    phoObjPFChWorstIso_;

vector<float>    phoMapPFChIso_;
vector<float>    phoMapPFPhoIso_;
vector<float>    phoMapPFNeuIso_;
vector<float>    phoMapPFChWorstIso_;


void lldjNtuple::branchesPhotons(TTree* tree) {

 tree->Branch("nPho",               &nPho_               );             
 tree->Branch("phoPt",              &phoPt_              );             
 tree->Branch("phoEn",              &phoEn_              );             
 tree->Branch("phoEta",             &phoEta_             );             
 tree->Branch("phoPhi",             &phoPhi_             );             
                                                   
 tree->Branch("phoSCEn",            &phoSCEn_            );             
 tree->Branch("phoSCEta",           &phoSCEta_           );             
 tree->Branch("phoSCPhi",           &phoSCPhi_           );             

 tree->Branch("phoIDbit",           &phoIDbit_           );             
 tree->Branch("phoIDMVA",           &phoIDMVA_           );             
  
 tree->Branch("phoObjPFChIso",      &phoObjPFChIso_      );
 tree->Branch("phoObjPFPhoIso",     &phoObjPFPhoIso_     );
 tree->Branch("phoObjPFNeuIso",     &phoObjPFNeuIso_     );
 tree->Branch("phoObjPFChWorstIso", &phoObjPFChWorstIso_ );
  
 tree->Branch("phoMapPFChIso",      &phoMapPFChIso_      );
 tree->Branch("phoMapPFPhoIso",     &phoMapPFPhoIso_     );
 tree->Branch("phoMapPFNeuIso",     &phoMapPFNeuIso_     );
 tree->Branch("phoMapPFChWorstIso", &phoMapPFChWorstIso_ );

}

void lldjNtuple::fillPhotons(const edm::Event& e, const edm::EventSetup& es) {
 
 // cleanup from previous execution
 nPho_               = 0;
 phoPt_              .clear();    
 phoEn_              .clear();    
 phoEta_             .clear();     
 phoPhi_             .clear();     

 phoSCEn_            .clear();      
 phoSCEta_           .clear();       
 phoSCPhi_           .clear();       

 phoIDbit_           .clear();       
 phoIDMVA_           .clear();       

 phoObjPFChIso_      .clear();
 phoObjPFPhoIso_     .clear();
 phoObjPFNeuIso_     .clear();
 phoObjPFChWorstIso_ .clear();

 phoMapPFChIso_      .clear();
 phoMapPFPhoIso_     .clear();
 phoMapPFNeuIso_     .clear();
 phoMapPFChWorstIso_ .clear();

 edm::Handle<edm::View<pat::Photon> > photonHandle;
 e.getByToken(photonCollection_, photonHandle);

 if (!photonHandle.isValid()) {
   edm::LogWarning("lldjNtuple") << "no pat::Photons in event";
   return;
 }

 ///Photon ID/Isolation Value maps (already run upstream)
 edm::Handle<edm::ValueMap<bool> >  loose_id_decisions;
 edm::Handle<edm::ValueMap<bool> >  medium_id_decisions;
 edm::Handle<edm::ValueMap<bool> >  tight_id_decisions;

 edm::Handle<edm::ValueMap<float> > mvaValues;

 edm::Handle<edm::ValueMap<float> > phoChargedIsolationMap;
 edm::Handle<edm::ValueMap<float> > phoNeutralHadronIsolationMap;
 edm::Handle<edm::ValueMap<float> > phoPhotonIsolationMap;
 edm::Handle<edm::ValueMap<float> > phoWorstChargedIsolationMap;

// # brokenphotons
// e.getByToken(phoLooseIdMapToken_ ,  loose_id_decisions);
// e.getByToken(phoMediumIdMapToken_,  medium_id_decisions);
// e.getByToken(phoTightIdMapToken_ ,  tight_id_decisions);
//
// //e.getByToken(phoMVAValuesMapToken_, mvaValues);
// 
// e.getByToken(phoChargedIsolationToken_,       phoChargedIsolationMap);
// e.getByToken(phoNeutralHadronIsolationToken_, phoNeutralHadronIsolationMap);
// e.getByToken(phoPhotonIsolationToken_,        phoPhotonIsolationMap);
// e.getByToken(phoWorstChargedIsolationToken_,  phoWorstChargedIsolationMap);

 int tmpcounter = 0;

 for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho) {

  Float_t phoPt  = iPho->et();
  Float_t phoEta = iPho->eta();
  const auto pho = photonHandle->ptrAt( tmpcounter );
  tmpcounter++;

  UShort_t tmpphoIDbit = 0;
  
  //bool isPassLoose  = (*loose_id_decisions)[pho];
  //if(isPassLoose) setbit(tmpphoIDbit, 0);
  //
  //bool isPassMedium = (*medium_id_decisions)[pho];
  //if(isPassMedium) setbit(tmpphoIDbit, 1);
  //
  //bool isPassTight  = (*tight_id_decisions)[pho];
  //if(isPassTight) setbit(tmpphoIDbit, 2);

  //printf(" PhoID: %hu \n", tmpphoIDbit);
  //// selections for electron collection
  //if (phoPt < 20 || fabs(phoEta) > 2.1 || tmpphoIDbit==0) continue;
  if (phoPt < 20 || fabs(phoEta) > 2.1) continue;
  
  phoPt_     .push_back(phoPt);
  phoEn_     .push_back(iPho->energy());
  phoEta_    .push_back(phoEta);
  phoPhi_    .push_back(iPho->phi());

  phoSCEn_   .push_back( (*iPho).superCluster()->energy());      
  phoSCEta_  .push_back( (*iPho).superCluster()->eta());       
  phoSCPhi_  .push_back( (*iPho).superCluster()->phi());       

  //phoObjPFChIso_       .push_back(iPho->chargedHadronIso());
  //phoObjPFPhoIso_      .push_back(iPho->photonIso());
  //phoObjPFNeuIso_      .push_back(iPho->neutralHadronIso());

  ////phoMapPFChIso_     .push_back((*phoChargedIsolationMap)[pho]);
  ////phoMapPFPhoIso_    .push_back((*phoPhotonIsolationMap)[pho]);
  ////phoMapPFNeuIso_    .push_back((*phoNeutralHadronIsolationMap)[pho]);
  ////phoMapPFChWorstIso_.push_back((*phoWorstChargedIsolationMap)[pho]);
  ////
  ////phoIDMVA_.push_back((*mvaValues)[pho]);  
  ////phoIDbit_.push_back(tmpphoIDbit);      

  nPho_++;
 }
}

