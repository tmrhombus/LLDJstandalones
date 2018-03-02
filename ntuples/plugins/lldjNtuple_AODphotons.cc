#include <TString.h>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

Int_t            nAODPho_;
vector<float>    AOD_phoPt_;
vector<float>    AOD_phoEn_;
vector<float>    AOD_phoEta_;
vector<float>    AOD_phoPhi_;

vector<float>    AOD_phoSCEn_;
vector<float>    AOD_phoSCEta_;
vector<float>    AOD_phoSCPhi_;

vector<UShort_t> AOD_phoIDbit_;
vector<Float_t>  AOD_phoIDMVA_;

vector<float>    AOD_phoObjPFChIso_;
vector<float>    AOD_phoObjPFPhoIso_;
vector<float>    AOD_phoObjPFNeuIso_;
vector<float>    AOD_phoObjPFChWorstIso_;

vector<float>    AOD_phoMapPFChIso_;
vector<float>    AOD_phoMapPFPhoIso_;
vector<float>    AOD_phoMapPFNeuIso_;
vector<float>    AOD_phoMapPFChWorstIso_;


void lldjNtuple::branchesAODPhotons(TTree* tree) {

 tree->Branch("nAODPho",                &nAODPho_               );             
 tree->Branch("AOD_phoPt",              &AOD_phoPt_              );             
 tree->Branch("AOD_phoEn",              &AOD_phoEn_              );             
 tree->Branch("AOD_phoEta",             &AOD_phoEta_             );             
 tree->Branch("AOD_phoPhi",             &AOD_phoPhi_             );             
                                                   
 tree->Branch("AOD_phoSCEn",            &AOD_phoSCEn_            );             
 tree->Branch("AOD_phoSCEta",           &AOD_phoSCEta_           );             
 tree->Branch("AOD_phoSCPhi",           &AOD_phoSCPhi_           );             

 tree->Branch("AOD_phoIDbit",           &AOD_phoIDbit_           );             
 tree->Branch("AOD_phoIDMVA",           &AOD_phoIDMVA_           );             
  
 tree->Branch("AOD_phoObjPFChIso",      &AOD_phoObjPFChIso_      );
 tree->Branch("AOD_phoObjPFPhoIso",     &AOD_phoObjPFPhoIso_     );
 tree->Branch("AOD_phoObjPFNeuIso",     &AOD_phoObjPFNeuIso_     );
 tree->Branch("AOD_phoObjPFChWorstIso", &AOD_phoObjPFChWorstIso_ );
  
 tree->Branch("AOD_phoMapPFChIso",      &AOD_phoMapPFChIso_      );
 tree->Branch("AOD_phoMapPFPhoIso",     &AOD_phoMapPFPhoIso_     );
 tree->Branch("AOD_phoMapPFNeuIso",     &AOD_phoMapPFNeuIso_     );
 tree->Branch("AOD_phoMapPFChWorstIso", &AOD_phoMapPFChWorstIso_ );

}

void lldjNtuple::fillAODPhotons(const edm::Event& e, const edm::EventSetup& es) {
 
 // cleanup from previous execution
 nAODPho_                 = 0;
 AOD_phoPt_              .clear();    
 AOD_phoEn_              .clear();    
 AOD_phoEta_             .clear();     
 AOD_phoPhi_             .clear();     

 AOD_phoSCEn_            .clear();      
 AOD_phoSCEta_           .clear();       
 AOD_phoSCPhi_           .clear();       

 AOD_phoIDbit_           .clear();       
 AOD_phoIDMVA_           .clear();       

 AOD_phoObjPFChIso_      .clear();
 AOD_phoObjPFPhoIso_     .clear();
 AOD_phoObjPFNeuIso_     .clear();
 AOD_phoObjPFChWorstIso_ .clear();

 AOD_phoMapPFChIso_      .clear();
 AOD_phoMapPFPhoIso_     .clear();
 AOD_phoMapPFNeuIso_     .clear();
 AOD_phoMapPFChWorstIso_ .clear();

 //edm::Handle<edm::View<pat::Photon> > photonHandle;
 edm::Handle<edm::View<reco::Photon> > photonHandle;
 e.getByToken(photonAODCollection_, photonHandle);

 if (!photonHandle.isValid()) {
   std::cout << "Invalid photon handle" << std::endl;
   edm::LogWarning("lldjNtuple") << "no pat::Photons in event";
   return;
 } 
 
 /*
 if(!(e.getByToken(AOD_phoLooseIdMapToken_ ,loose_id_decisions) 
    || e.getByToken(AOD_phoMediumIdMapToken_ ,medium_id_decisions) 
    || e.getByToken(AOD_phoTightIdMapToken_ ,tight_id_decisions) 
    || e.getByToken(AOD_phoChargedIsolationMapToken_ ,AOD_phoChargedIsolationHandle_) 
    || e.getByToken(AOD_phoNeutralHadronIsolationMapToken_ ,AOD_phoNeutralHadronIsolationHandle_) 
    || e.getByToken(AOD_phoPhotonIsolationMapToken_ ,AOD_phoPhotonIsolationHandle_) 
    || e.getByToken(AOD_phoWorstChargedIsolationMapToken_ ,AOD_phoWorstChargedIsolationHandle_)
      )){
   edm::LogWarning("lldjNtuple") << "Failure in ID tokens";
   return;
 } 
 */

 e.getByToken(AOD_phoLooseIdMapToken_,  loose_id_decisions);
 e.getByToken(AOD_phoMediumIdMapToken_, medium_id_decisions);
 e.getByToken(AOD_phoTightIdMapToken_,  tight_id_decisions);
 e.getByToken(AOD_phoChargedIsolationMapToken_,       AOD_phoChargedIsolationHandle_);
 e.getByToken(AOD_phoNeutralHadronIsolationMapToken_, AOD_phoNeutralHadronIsolationHandle_);
 e.getByToken(AOD_phoPhotonIsolationMapToken_,        AOD_phoPhotonIsolationHandle_);
 e.getByToken(AOD_phoWorstChargedIsolationMapToken_,  AOD_phoWorstChargedIsolationHandle_);
 
 //int tmpcounter = 0;

 // for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho) {

for (size_t i = 0; i < photonHandle->size(); ++i){
  const auto pho = photonHandle->ptrAt(i);

  std::cout << "photon loop" << std::endl;
 
  Float_t AOD_phoPt  = pho->et();
  std::cout << "photon got pt" << std::endl;
  Float_t AOD_phoEta = pho->eta();
  //const auto pho = photonHandle->ptrAt( tmpcounter );
  //tmpcounter++;

  UShort_t tmpphoIDbit = 0;
  std::cout << "photon try loose" << std::endl;
  //bool isPassLoose  = (*loose_id_decisions)[pho];
  bool isPassLoose  = (*loose_id_decisions)[pho];
  std::cout << "photon got loose" << std::endl;
  if(isPassLoose) setbit(tmpphoIDbit, 0);
  
  bool isPassMedium = (*medium_id_decisions)[pho];
  if(isPassMedium) setbit(tmpphoIDbit, 1);
  
  bool isPassTight  = (*tight_id_decisions)[pho];
  if(isPassTight) setbit(tmpphoIDbit, 2);

  //printf(" PhoID: %hu \n", tmpphoIDbit);
  //// selections for electron collection
  //if (phoPt < 20 || fabs(phoEta) > 2.1 || tmpphoIDbit==0) continue;
  if (AOD_phoPt < 20 || fabs(AOD_phoEta) > 2.1) continue;

  AOD_phoPt_     .push_back(AOD_phoPt);

  AOD_phoEn_     .push_back(pho->energy());
  AOD_phoEta_    .push_back(AOD_phoEta);
  AOD_phoPhi_    .push_back(pho->phi());

  AOD_phoSCEn_   .push_back( (*pho).superCluster()->energy());      
  AOD_phoSCEta_  .push_back( (*pho).superCluster()->eta());       
  AOD_phoSCPhi_  .push_back( (*pho).superCluster()->phi());       

  AOD_phoObjPFChIso_       .push_back(pho->chargedHadronIso());
  AOD_phoObjPFPhoIso_      .push_back(pho->photonIso());
  AOD_phoObjPFNeuIso_      .push_back(pho->neutralHadronIso());

  //AOD_phoMapPFChIso_     .push_back((*AOD_phoChargedIsolationHandle_)[pho]);
  //AOD_phoMapPFPhoIso_    .push_back((*AOD_phoPhotonIsolationHandle_)[pho]);
  //AOD_phoMapPFNeuIso_    .push_back((*AOD_phoNeutralHadronIsolationHandle_)[pho]);
  //AOD_phoMapPFChWorstIso_.push_back((*AOD_phoWorstChargedIsolationHandle_)[pho]);
  
  ////phoIDMVA_.push_back((*mvaValues)[pho]);  
  ////phoIDbit_.push_back(tmpphoIDbit);      

  nAODPho_++;

 }
}

