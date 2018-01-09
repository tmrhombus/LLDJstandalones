#include "FWCore/MessageLogger/interface/MessageLogger.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "FWCore/Common/interface/TriggerNames.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"
#include <iomanip>
#include <bitset>
using namespace std;

// (local) variables associated with tree branches
Int_t       AODrun_;
Long64_t    AODevent_;
Int_t       AODlumis_;
Bool_t      AODisData_;

void lldjNtuple::branchesAODEvent(TTree* tree) {

  tree->Branch("run",     	       &AODrun_);
  tree->Branch("event",    	       &AODevent_);
  tree->Branch("lumis",   	       &AODlumis_);
  tree->Branch("isData",  	       &AODisData_);

}

void lldjNtuple::fillAODEvent(const edm::Event& e, const edm::EventSetup& es) {

  AODrun_    = e.id().run();
  AODevent_  = e.id().event();
  AODlumis_  = e.luminosityBlock();
  AODisData_ = e.isRealData();

}
