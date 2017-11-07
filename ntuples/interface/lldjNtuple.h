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
//#include "HiggsAnalysis/HiggsTo2photons/interface/CiCPhotonID.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "RecoTracker/Record/interface/NavigationSchoolRecord.h"

#include "RecoTracker/DebugTools/interface/GetTrackTrajInfo.h"
//#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
//#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "MagneticField/Engine/interface/MagneticField.h" 

#include "TrackingTools/GeomPropagators/interface/Propagator.h"

#include "TrackingTools/GeomPropagators/interface/StateOnTrackerBound.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"


using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class lldjNtuple : public edm::EDAnalyzer {
 public:

  explicit lldjNtuple(const edm::ParameterSet&);
  ~lldjNtuple();
  
  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  
  edm::ParameterSet lldj_pset_;

  //   virtual void beginJob() {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  //   virtual void endJob() {};
  
  void branchesGlobalEvent(TTree*);
  void branchesMET        (TTree*);
  void branchesPhotons    (TTree*);
  void branchesElectrons  (TTree*);
  void branchesMuons      (TTree*);
  void branchesJets       (TTree*);
  void branchesAODJets    (TTree*);
  void branchesTrigger    (TTree*);
  void branchesGenPart    (TTree*);

  void fillGlobalEvent(const edm::Event&, const edm::EventSetup&);
  void fillMET        (const edm::Event&, const edm::EventSetup&);
  void fillPhotons    (const edm::Event&, const edm::EventSetup&);
  void fillElectrons  (const edm::Event&, const edm::EventSetup&);
  void fillMuons      (const edm::Event&, const reco::Vertex);
  void fillJets       (const edm::Event&, const edm::EventSetup&);
  void fillAODJets    (const edm::Event&, const edm::EventSetup&);
  void fillTrigger    (const edm::Event&, const edm::EventSetup&);
  void fillGenPart    (const edm::Event&);

  bool doAOD_     ; 
  bool doMiniAOD_ ; 

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

  // beamspot
  edm::EDGetTokenT<reco::BeamSpot>                 beamspotLabel_;

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

  // jet functions
  vector<int> getJetTrackIndexs( float jeteta, float jetphi);
  void calculateAlphaMax( vector<int> jetTrackIDs,
   float& alphaMax, float& alphaMaxP, float& beta,
   float& alphaMax2, float& alphaMaxP2, float& beta2);
  void calculateTrackAngle( vector<int> jetTrackIDs,
   vector<float> &allTrackAngles,
   float &totalTrackAngle, float &totalTrackAnglePt);
  void calculateIP( vector<int> jetTrackIDs,
   vector<float> &jetIPs, vector<float> &jetIPSigs,
   float &sumIP, float &sumIPSig);

  float findMedian(vector<float> thevector);

  void calculateDisplacedVertices(const edm::EventSetup& es, vector<int> jetTrackIDs);

  void deltaVertex3D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dEta, double& dPhi, double& pt, double& m, double& energy);
  void deltaVertex2D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dPhi, double& pt, double& mediandPhi);
  vector<reco::TransientTrack> cleanTracks(vector<reco::TransientTrack> tracks, GlobalPoint vertPos);

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

  // photon ID decision objects and isolations
  edm::EDGetTokenT<edm::ValueMap<bool> >  phoLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  phoMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  phoTightIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > phoMVAValuesMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoWorstChargedIsolationToken_; 

  // trigger
  edm::EDGetTokenT<edm::TriggerResults>                     triggerBits_;
  edm::EDGetTokenT<edm::View<pat::TriggerObjectStandAlone>> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales>             triggerPrescales_;

  //gen
  edm::EDGetTokenT<vector<reco::GenParticle> >     genParticlesCollection_;

  

  TTree   *tree_;
  TH1F    *hEvents_;

  JME::JetResolution            slimmedJetResolution_;
  JME::JetResolutionScaleFactor slimmedJetResolutionSF_;

  // shared between miniAOD jets and AOD jets modules
  edm::Handle<double>                 rhoHandle;
  edm::Handle<reco::VertexCollection> vtxHandle;

};

#endif
