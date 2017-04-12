#include <TString.h>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "LLDJstandalones/ntuples/interface/GEDPhoIDTools.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

Int_t          npfPho_;
vector<float>  pfphoEt_;
vector<float>  pfphoEta_;
vector<float>  pfphoPhi_;

void lldjNtuple::branchesPFPhotons(TTree* tree) {
  
  tree->Branch("npfPho",                    &npfPho_);
  tree->Branch("pfphoEt",                   &pfphoEt_);
  tree->Branch("pfphoEta",                  &pfphoEta_);
  tree->Branch("pfphoPhi",                  &pfphoPhi_);

}

void lldjNtuple::fillPFPhotons(const edm::Event& e, const edm::EventSetup& es) {
  
  // cleanup from previous execution
  pfphoEt_                .clear();
  pfphoEta_               .clear();
  pfphoPhi_               .clear();

  npfPho_ = 0;

}

