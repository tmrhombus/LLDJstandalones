#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

// (local) variables associated with tree branches
Int_t            nMu_                             ; 
vector<float>    muPt_                            ; 
vector<float>    muEn_                            ; 
vector<float>    muEta_                           ; 
vector<float>    muPhi_                           ; 
vector<int>      muCharge_                        ; 
vector<int>      muType_                          ; 
vector<UShort_t> muIDbit_                         ; 
vector<bool>     muPassLooseID_                   ; 
vector<bool>     muPassMediumID_                  ; 
vector<bool>     muPassTighID_                    ; 
// vector<bool>     muPassSoftID_                 ; 
// vector<bool>     muPassHighPtID_               ; 
//vector<float>   muPVIndex_                        ; 
vector<int>     muNumberOfMissingInnerHits_       ; 
vector<int>     muNumberOfMissingMiddleHits_      ; 
vector<int>     muNumberOfMissingOuterHits_       ; 
//vector<int>     muNumberOfValidHits_              ; 
//vector<float>   muNormalizedChi2_                 ; 
vector<int>     muNumberOfMatchedStations_        ; 
vector<int>     muNumberOfValidPixelHits_         ; 
vector<int>     muTrackerLayersWithMeasurement_   ; 
vector<int>     muIsGlobalMuon_                   ; 
vector<int>     muIsPFMuon_                       ; 
//vector<int>     muIsTightMuonWRTVtx_              ; 
vector<float>   muPFdBetaIsolation_               ; 

void lldjNtuple::branchesMuons(TTree* tree) {
 tree->Branch("nMu",                            &nMu_                            ) ; 
 tree->Branch("muPt",                           &muPt_                           ) ; 
 tree->Branch("muEn",                           &muEn_                           ) ; 
 tree->Branch("muEta",                          &muEta_                          ) ; 
 tree->Branch("muPhi",                          &muPhi_                          ) ; 
 tree->Branch("muCharge",                       &muCharge_                       ) ; 
 tree->Branch("muType",                         &muType_                         ) ; 
 tree->Branch("muIDbit",                        &muIDbit_                        ) ; 
 tree->Branch("muPassLooseID",                  &muPassLooseID_                  ) ; 
 tree->Branch("muPassMediumID",                 &muPassMediumID_                 ) ; 
 tree->Branch("muPassTighID",                   &muPassTighID_                   ) ; 
 //tree->Branch("muPVIndex",                      &muPVIndex_                      ) ; 
 tree->Branch("muNumberOfMissingInnerHits",     &muNumberOfMissingInnerHits_     ) ; 
 tree->Branch("muNumberOfMissingMiddleHits",    &muNumberOfMissingMiddleHits_    ) ; 
 tree->Branch("muNumberOfMissingOuterHits",     &muNumberOfMissingOuterHits_     ) ; 
 //tree->Branch("muNumberOfValidHits",            &muNumberOfValidHits_            ) ; 
 //tree->Branch("muNormalizedChi2",               &muNormalizedChi2_               ) ; 
 tree->Branch("muNumberOfMatchedStations",      &muNumberOfMatchedStations_      ) ; 
 tree->Branch("muNumberOfValidPixelHits",       &muNumberOfValidPixelHits_       ) ; 
 tree->Branch("muTrackerLayersWithMeasurement", &muTrackerLayersWithMeasurement_ ) ; 
 tree->Branch("muIsGlobalMuon",                 &muIsGlobalMuon_                 ) ; 
 tree->Branch("muIsPFMuon",                     &muIsPFMuon_                     ) ; 
 //tree->Branch("muIsTightMuonWRTVtx",            &muIsTightMuonWRTVtx_            ) ; 
 tree->Branch("muPFdBetaIsolation",             &muPFdBetaIsolation_             ) ; 
}

void lldjNtuple::fillMuons(const edm::Event& e, math::XYZPoint& pv, reco::Vertex vtx) {

 // cleanup from previous execution
 nMu_ = 0;
 muPt_                          .clear() ; 
 muEn_                          .clear() ; 
 muEta_                         .clear() ; 
 muPhi_                         .clear() ; 
 muCharge_                      .clear() ; 
 muType_                        .clear() ; 
 muIDbit_                       .clear() ; 
 muPassLooseID_                 .clear() ; 
 muPassMediumID_                .clear() ; 
 muPassTighID_                  .clear() ; 
 //muPVIndex_                     .clear() ; 
 muNumberOfMissingInnerHits_    .clear() ; 
 muNumberOfMissingMiddleHits_   .clear() ; 
 muNumberOfMissingOuterHits_    .clear() ; 
 //muNumberOfValidHits_           .clear() ; 
 //muNormalizedChi2_              .clear() ; 
 muNumberOfMatchedStations_     .clear() ; 
 muNumberOfValidPixelHits_      .clear() ; 
 muTrackerLayersWithMeasurement_.clear() ; 
 muIsGlobalMuon_                .clear() ; 
 muIsPFMuon_                    .clear() ; 
 //muIsTightMuonWRTVtx_           .clear() ; 
 muPFdBetaIsolation_            .clear() ; 

 edm::Handle<edm::View<pat::Muon> > muonHandle;
 e.getByToken(muonCollection_, muonHandle);

 if (!muonHandle.isValid()) {
  edm::LogWarning("lldjNtuple") << "no pat::Muons in event";
  return;
 }

 for (edm::View<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {

  nMu_++;
  Float_t pt = iMu->pt();

  if (pt < 3) continue;
  if (! (iMu->isPFMuon() || iMu->isGlobalMuon() || iMu->isTrackerMuon())) continue;

  muPt_    .push_back(pt);
  muEn_    .push_back(iMu->energy());
  muEta_   .push_back(iMu->eta());
  muPhi_   .push_back(iMu->phi());
  muCharge_.push_back(iMu->charge());
  muType_  .push_back(iMu->type());
  // muD0_    .push_back(iMu->muonBestTrack()->dxy(pv));
  // muDz_    .push_back(iMu->muonBestTrack()->dz(pv));
  // muSIP_   .push_back(fabs(iMu->dB(pat::Muon::PV3D))/iMu->edB(pat::Muon::PV3D));

  UShort_t tmpmuIDbit = 0;

  if (iMu->isLooseMuon())     setbit(tmpmuIDbit, 0);
  if (iMu->isMediumMuon())    setbit(tmpmuIDbit, 1);
  if (iMu->isTightMuon(vtx))  setbit(tmpmuIDbit, 2);
  if (iMu->isSoftMuon(vtx))   setbit(tmpmuIDbit, 3);
  if (iMu->isHighPtMuon(vtx)) setbit(tmpmuIDbit, 4);
  muIDbit_.push_back(tmpmuIDbit);

  muPassLooseID_  .push_back(iMu->isLooseMuon())    ;
  muPassMediumID_ .push_back(iMu->isMediumMuon())   ;
  muPassTighID_   .push_back(iMu->isTightMuon(vtx)) ;
  //muPassSoftID_   .push_back(iMu->isSoftMuon(vtx))  ;
  //muPassHighPtID_ .push_back(iMu->isHighPtMuon(vtx));

  muIsGlobalMuon_                .push_back(iMu->  isGlobalMuon () ) ; 
  muIsPFMuon_                    .push_back(iMu->  isPFMuon     () ) ; 
  //muIsTightMuonWRTVtx_           .push_back(iMu->  isTightMuonWRTVtx ()  ) ; 

  Float_t muPFChIso      = iMu->pfIsolationR04().sumChargedHadronPt ;
  Float_t muPFPhoIso     = iMu->pfIsolationR04().sumPhotonEt        ;
  Float_t muPFNeuIso     = iMu->pfIsolationR04().sumNeutralHadronEt ;
  Float_t muPFPUIso      = iMu->pfIsolationR04().sumPUPt            ;
  Float_t pfdBetaIso     = ( muPFChIso + max(0.0,muPFNeuIso + muPFPhoIso - 0.5*muPFPUIso ) ) / pt ;

  muPFdBetaIsolation_     .push_back( pfdBetaIso     ) ; 

  const reco::Muon &recoMu = dynamic_cast<const reco::Muon &>(*iMu);

  if( !recoMu.innerTrack().isNull() ){
   muNumberOfMissingInnerHits_    .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::MISSING_INNER_HITS) ) ; 
   muNumberOfMissingMiddleHits_   .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::TRACK_HITS        ) ) ; 
   muNumberOfMissingOuterHits_    .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::MISSING_OUTER_HITS) ) ; 
   muNumberOfValidPixelHits_      .push_back( recoMu.innerTrack ()->hitPattern ().numberOfValidPixelHits       ()   ) ; 
   muTrackerLayersWithMeasurement_.push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithMeasurement ()   ) ; 
  }
  //muNumberOfValidHits_           .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::)              ) ; 
  //muNormalizedChi2_              .push_back( recoMu.globalTrack().normalizedChi2 ()   ) ; 

//  const pat::PackedCandidate &ppfMu = dynamic_cast<const pat::PackedCandidate &>(*iMu);
//
//  if (!ppfMu.vertexRef().isNull() && ppfMu.vertexRef().isAvailable()){
//   muPVIndex_ .push_back(ppfMu.vertexRef().index());
//  }

 }
}
