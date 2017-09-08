#ifndef lldjNtuple_h
#define lldjNtuple_h

#include "TTree.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "HiggsAnalysis/HiggsTo2photons/interface/CiCPhotonID.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"

#include "RecoTracker/DebugTools/interface/GetTrackTrajInfo.h"
//#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
//#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "MagneticField/Engine/interface/MagneticField.h" 

#include "TrackingTools/GeomPropagators/interface/Propagator.h"

#include "TrackingTools/GeomPropagators/interface/StateOnTrackerBound.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"


using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class lldjNtuple : public edm::EDAnalyzer {
 public:

  explicit lldjNtuple(const edm::ParameterSet&);
  ~lldjNtuple();
  
  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  
  //   virtual void beginJob() {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  //   virtual void endJob() {};
  
  //   double TrackAngle(const edm::Event&, reco::TransientTrack track, TrajectoryStateOnSurface tSOSInnerHit);

  void branchesGlobalEvent(TTree*);
  void branchesMET        (TTree*);
  void branchesPhotons    (TTree*);
  void branchesElectrons  (TTree*);
  void branchesMuons      (TTree*);
  void branchesJets       (TTree*);

  void fillGlobalEvent(const edm::Event&, const edm::EventSetup&);
  void fillMET        (const edm::Event&, const edm::EventSetup&);
  void fillPhotons    (const edm::Event&, const edm::EventSetup&);
  void fillElectrons  (const edm::Event&, const edm::EventSetup&);
  void fillMuons      (const edm::Event&, const reco::Vertex);
  void fillJets       (const edm::Event&, const edm::EventSetup&);

  // collections
  // electrons
  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  edm::EDGetTokenT<double>                         rhoLabel_;
  // elecontr ID decisions objects
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleVetoIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleTightIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleHLTIdMapToken_;
  //edm::EDGetTokenT<edm::ValueMap<bool> >  eleHEEPIdMapToken_;
  //edm::EDGetTokenT<edm::ValueMap<float> > eleMVAValuesMapToken_;
  //edm::EDGetTokenT<edm::ValueMap<float> > eleMVAHZZValuesMapToken_;
  //edm::EDGetTokenT<edm::ValueMap<float> > elePFClusEcalIsoToken_;
  //edm::EDGetTokenT<edm::ValueMap<float> > elePFClusHcalIsoToken_;

  // global event
  edm::EDGetTokenT<double>                         rhoCentralLabel_;
  edm::EDGetTokenT<vector<PileupSummaryInfo> >     puCollection_;
  edm::EDGetTokenT<reco::VertexCollection>         vtxLabel_;
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  string                                           trgResultsProcess_;

  // jets
  edm::EDGetTokenT<edm::View<pat::Jet> >           jetsAK4Label_;
   // AOD Jets
  edm::EDGetTokenT<edm::View<reco::CaloJet> >      AODak4CaloJetsLabel_;   
  edm::EDGetTokenT<edm::View<reco::PFJet>   >      AODak4PFJetsLabel_;     
  edm::EDGetTokenT<edm::View<reco::PFJet>   >      AODak4PFJetsCHSLabel_;  

  edm::EDGetTokenT<edm::View<reco::Vertex>  >      AODVertexLabel_;
  edm::EDGetTokenT<edm::View<reco::Track>  >       AODTrackLabel_;
  const MagneticField*                             magneticField_;
  edm::ESHandle<Propagator>                        thePropagator_;
  edm::ESHandle<TransientTrackBuilder>             theBuilder_;

  void                                             matchTracksToJetToVertex(float jeteta, float jetphi); 
  void calculateAlphaMax(std::vector<reco::TransientTrack> tracks,std::vector<int>whichVertex, double& alphaMax, double& alphaMaxP, double& beta, double& alphaMax2, double& alphaMaxP2, double& beta2);

  // met
  edm::EDGetTokenT<edm::TriggerResults>            patTrgResultsLabel_;
  // for MET filters
  edm::EDGetTokenT<bool> BadChCandFilterToken_;
  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;
  edm::EDGetTokenT<edm::View<pat::MET> >           pfMETlabel_;

  // muons
  edm::EDGetTokenT<edm::View<pat::Muon> >          muonCollection_;

  // photons
  edm::EDGetTokenT<edm::View<pat::Photon> >        photonCollection_;

//  ///Photon ID in VID framework - 11th May, 2015
//  // photon ID decision objects and isolations
//  edm::EDGetTokenT<edm::ValueMap<bool> >  phoLooseIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  phoMediumIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  phoTightIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoMVAValuesMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_; 
//  edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_; 
//  edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_; 
//  edm::EDGetTokenT<edm::ValueMap<float> > phoWorstChargedIsolationToken_; 
//  //edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_CITK_;
//  //edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_CITK_;
//  //edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_CITK_;
//  //edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_PUPPI_;
//  //edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_PUPPI_;
//  //edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_PUPPI_;

  TTree   *tree_;
  TH1F    *hEvents_;

  JME::JetResolution            jetResolution_;
  JME::JetResolutionScaleFactor jetResolutionSF_;
};

#endif
