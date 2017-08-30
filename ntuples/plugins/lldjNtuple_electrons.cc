#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"

#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;
//using namespace reco;

// (local) variables associated with tree branches
Int_t            nEle_;
vector<float>    elePt_;
vector<float>    eleEn_;
vector<float>    eleEta_;
vector<float>    elePhi_;

vector<float>    eleSCEn_;
vector<float>    eleSCEta_;
vector<float>    eleSCPhi_;

vector<int>      eleCharge_;
vector<int>      eleChargeConsistent_;

vector<UShort_t> eleIDbit_;

vector<float>    elePFdBetaIsolationRhoEA_ ;
vector<float>    elePFdBetaIsolationCHS_   ;
vector<float>    elePFdBetaIsolationDiff_  ;

float rho;

void lldjNtuple::branchesElectrons(TTree* tree) {

 tree->Branch("nEle",                     &nEle_                     );                           
 tree->Branch("elePt",                    &elePt_                    );     
 tree->Branch("eleEn",                    &eleEn_                    );     
 tree->Branch("eleEta",                   &eleEta_                   );     
 tree->Branch("elePhi",                   &elePhi_                   );     

 tree->Branch("eleSCEn",                  &eleSCEn_                  );     
 tree->Branch("eleSCEta",                 &eleSCEta_                 );     
 tree->Branch("eleSCPhi",                 &eleSCPhi_                 );     

 tree->Branch("eleCharge",                &eleCharge_                );     
 tree->Branch("eleChargeConsistent",      &eleChargeConsistent_      );     

 tree->Branch("eleIDbit",                 &eleIDbit_                 );     

 tree->Branch("elePFdBetaIsolationRhoEA", &elePFdBetaIsolationRhoEA_ );     
 tree->Branch("elePFdBetaIsolationCHS",   &elePFdBetaIsolationCHS_   );     
 tree->Branch("elePFdBetaIsolationDiff",  &elePFdBetaIsolationDiff_  );     

}

void lldjNtuple::fillElectrons(const edm::Event &e, const edm::EventSetup &es) {
    
 // cleanup from previous execution
 nEle_                     = 0;

 elePt_                    .clear();     
 eleEn_                    .clear();     
 eleEta_                   .clear();     
 elePhi_                   .clear();     

 eleSCEn_                  .clear();     
 eleSCEta_                 .clear();     
 eleSCPhi_                 .clear();     

 eleCharge_                .clear();     
 eleChargeConsistent_      .clear();     

 eleIDbit_                 .clear();     

 elePFdBetaIsolationRhoEA_ .clear();     
 elePFdBetaIsolationCHS_   .clear();     
 elePFdBetaIsolationDiff_  .clear();     

 // get handles
 edm::Handle<edm::View<pat::Electron> > electronHandle;
 e.getByToken(electronCollection_, electronHandle);

 edm::Handle<double> rhoHandle;
 e.getByToken(rhoLabel_, rhoHandle);

 if (!electronHandle.isValid()) {
   edm::LogWarning("lldjNtuple") << "no pat::Electrons in event";
   return;
 }

 edm::Handle<edm::ValueMap<bool> >  veto_id_decisions;
 edm::Handle<edm::ValueMap<bool> >  loose_id_decisions;
 edm::Handle<edm::ValueMap<bool> >  medium_id_decisions;
 edm::Handle<edm::ValueMap<bool> >  tight_id_decisions;
 edm::Handle<edm::ValueMap<bool> >  hlt_id_decisions; 
 edm::Handle<edm::ValueMap<bool> >  heep_id_decisions;
 //edm::Handle<edm::ValueMap<float> > eleMVAValues;
 //edm::Handle<edm::ValueMap<float> > eleMVAHZZValues;
 //edm::Handle<edm::ValueMap<float> > elePFClusEcalIsoValues;
 //edm::Handle<edm::ValueMap<float> > elePFClusHcalIsoValues;

 e.getByToken(eleVetoIdMapToken_ ,         veto_id_decisions);
 e.getByToken(eleLooseIdMapToken_ ,        loose_id_decisions);
 e.getByToken(eleMediumIdMapToken_,        medium_id_decisions);
 e.getByToken(eleTightIdMapToken_,         tight_id_decisions);
 e.getByToken(eleHLTIdMapToken_,           hlt_id_decisions);
 //e.getByToken(eleHEEPIdMapToken_ ,         heep_id_decisions);
 //e.getByToken(eleMVAValuesMapToken_,       eleMVAValues);
 //e.getByToken(eleMVAHZZValuesMapToken_,    eleMVAHZZValues);
 //e.getByToken(elePFClusEcalIsoToken_,      elePFClusEcalIsoValues);
 //e.getByToken(elePFClusHcalIsoToken_,      elePFClusHcalIsoValues);

 for (edm::View<pat::Electron>::const_iterator iEle = electronHandle->begin(); iEle != electronHandle->end(); ++iEle) {

  Float_t elePt  = iEle->pt();
  Float_t eleEta = iEle->eta();
  //printf(" Electron %u pt %f\n", nEle_, elePt );

  const auto el = electronHandle->ptrAt(nEle_);
  UShort_t tmpeleIDbit = 0;
  ///el->electronID("cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto") also works
  bool isPassVeto  = (*veto_id_decisions)[el];
  if (isPassVeto) setbit(tmpeleIDbit, 0);
  bool isPassLoose  = (*loose_id_decisions)[el];
  if (isPassLoose) setbit(tmpeleIDbit, 1);
  bool isPassMedium = (*medium_id_decisions)[el];
  if (isPassMedium) setbit(tmpeleIDbit, 2);
  bool isPassTight  = (*tight_id_decisions)[el];
  if (isPassTight) setbit(tmpeleIDbit, 3);
  //bool isPassHEEP = (*heep_id_decisions)[el];
  //if (isPassHEEP) setbit(tmpeleIDbit, 4);
  bool isPassHLT = (*hlt_id_decisions)[el];
  if (isPassHLT) setbit(tmpeleIDbit, 5);

  // twiki https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPFBasedIsolationRun2
  float effectiveArea = 0;
  rho = *(rhoHandle.product());

  // electron effective areas from https://indico.cern.ch/event/369239/contribution/4/attachments/1134761/1623262/talk_effective_areas_25ns.pdf
  // (see slide 12)
  if(abs(iEle->superCluster()->eta()) >= 0.0000 && abs(iEle->superCluster()->eta()) < 1.0000)
    effectiveArea = 0.1752;
  if(abs(iEle->superCluster()->eta()) >= 1.0000 && abs(iEle->superCluster()->eta()) < 1.4790)
    effectiveArea = 0.1862;
  if(abs(iEle->superCluster()->eta()) >= 1.4790 && abs(iEle->superCluster()->eta()) < 2.0000)
    effectiveArea = 0.1411;
  if(abs(iEle->superCluster()->eta()) >= 2.0000 && abs(iEle->superCluster()->eta()) < 2.2000)
    effectiveArea = 0.1534;
  if(abs(iEle->superCluster()->eta()) >= 2.2000 && abs(iEle->superCluster()->eta()) < 2.3000)
    effectiveArea = 0.1903;
  if(abs(iEle->superCluster()->eta()) >= 2.3000 && abs(iEle->superCluster()->eta()) < 2.4000)
    effectiveArea = 0.2243;
  if(abs(iEle->superCluster()->eta()) >= 2.4000 && abs(iEle->superCluster()->eta()) < 5.0000)
    effectiveArea = 0.2687;

  Float_t elePFChIso      = iEle->pfIsolationVariables().sumChargedHadronPt ;
  Float_t elePFPhoIso     = iEle->pfIsolationVariables().sumPhotonEt        ;
  Float_t elePFNeuIso     = iEle->pfIsolationVariables().sumNeutralHadronEt ;
  Float_t elePFPUIso      = iEle->pfIsolationVariables().sumPUPt            ;

  Float_t PUea  = effectiveArea*rho ;
  Float_t PUchs = 0.5*elePFPUIso    ;

  Float_t elePFdBetaIsolationRhoEA =  ( elePFChIso + max( (Float_t)0.0, elePFNeuIso + elePFPhoIso - PUea  ) ) / elePt ;
  Float_t elePFdBetaIsolationCHS   =  ( elePFChIso + max( (Float_t)0.0, elePFNeuIso + elePFPhoIso - PUchs ) ) / elePt ;

  // selections for electron collection
  if (elePt < 20 || fabs(eleEta) > 2.1 || tmpeleIDbit==0) continue;

  // and fill variables linked to tree
  elePt_              .push_back(elePt);
  eleEn_              .push_back(iEle->energy());
  eleEta_             .push_back(eleEta);
  elePhi_             .push_back(iEle->phi());
  eleCharge_          .push_back(iEle->charge());
  eleChargeConsistent_.push_back((Int_t)iEle->isGsfCtfScPixChargeConsistent());
  eleSCEn_            .push_back(iEle->superCluster()->energy());
  eleSCEta_           .push_back(iEle->superCluster()->eta());
  eleSCPhi_           .push_back(iEle->superCluster()->phi());
  ///   eleSCRawEn_         .push_back(iEle->superCluster()->rawEnergy());
  ///   eleSCEtaWidth_      .push_back(iEle->superCluster()->etaWidth());
  ///   eleSCPhiWidth_      .push_back(iEle->superCluster()->phiWidth());
  eleIDbit_.push_back(tmpeleIDbit);

  elePFdBetaIsolationRhoEA_ .push_back( elePFdBetaIsolationRhoEA ) ;
  elePFdBetaIsolationCHS_   .push_back( elePFdBetaIsolationCHS   ) ;
  elePFdBetaIsolationDiff_  .push_back( elePFdBetaIsolationRhoEA - elePFdBetaIsolationCHS ) ;

  nEle_++;

 }
}
