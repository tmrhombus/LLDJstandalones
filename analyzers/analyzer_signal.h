#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"
// #include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TLorentzVector.h>

class analyzer_signal : public analyzer_base {

public :

 // basic functions
               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, 
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts);

 // make 1D,2D histograms (helper function)
 TH2F          initSingleHistogramTH2F(TString hnamex, TString htitley,
                                   Int_t nbinsx, Double_t xmin, Double_t xmax,
                                   Int_t nbinsy, Double_t ymin, Double_t ymax);
 TH1F          initSingleHistogramTH1F(TString hname, TString htitle,
                                   Int_t nbins, Double_t xmin,
                                   Double_t xmax);

 // make dilepton pair, pass by reference
 virtual void     makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2,
                            TLorentzVector *fv_ee, TLorentzVector *fv_mm, bool *passMM);
 // I like because I don't want to rely on CMSSW here
 double               dR(double eta1, double phi1, double eta2, double phi2);
 double               DeltaPhi(double phi1, double phi2);

 // event based weights
 void                  loadPUWeight();
 Double_t              makePUWeight();
 TH1F*                 PUWeights;
 void                  loadElectronWeight();
 Double_t              makeElectronWeight();
 TH2F*                 EleWeights;

 // object IDs and selections
 std::vector<int>     photon_passID     ( int bitnr, double phoPtCut, double phoEtaCut, TString sysbinname="");
 std::vector<int>     electron_passID   ( int bitnr, double elePtCut, double eleEtaCut, TString sysbinname="");
 std::vector<int>     muon_passID       ( int bitnr, double muPtCut , double muEtaCut , TString sysbinname="");
 std::vector<int>     slimmedjet_passID ( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname="");
 std::vector<int>     aodcalojet_passID ( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname="");

 // get (smeared) object pt
 Float_t          getPhotonPt(int idnr, TString sysbinname);
 Float_t          getElectronPt(int i, TString sysbinname);
 Float_t          getMuonPt(int i, TString sysbinname);

 // debug options, printouts
 virtual void debug_printobjects();
 virtual void debug_printmuons();
 virtual void debug_printelectrons();
 virtual void debug_printtriggers();

 // Histograms
 //  
 void          initSelectionCategories();
 // 2D Histograms 
 Bool_t        init2DHistograms();
 Bool_t        fill2DHistograms(Double_t weight, int selbin);
 Bool_t        write2DHistograms(int selbin);
 // Jet Variables
 Bool_t        initSlimmedJetHistograms();
 Bool_t        fillSlimmedJetHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeSlimmedJetHistograms(int selbin, int lepbin);
 // Event Variables
 Bool_t        initBasicHistograms();
 Bool_t        fillBasicHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeBasicHistograms(int selbin, int lepbin);

 // vectors of ints
 // each int is an entry in vector
 // associated with object passing
 // some selection
 std::vector<int> photon_list;
 std::vector<int> electron_list;
 std::vector<int> muon_list ;
 std::vector<int> slimmedjet_list;
 std::vector<int> aodcalojet_list;

 // ID bits for collections
 TString phoid;
 TString eleid;
 TString muoid;
 TString jetid;

 int phoidbit;
 int eleidbit;
 int muoidbit;
 int slimmedjetidbit;
 int aodcalojetidbit;
 float muoisoval;

 // Selection functions
 Bool_t        askPassSingleEle();
 Bool_t        askPassSingleMu();
 Bool_t        askPassDoubleEle();
 Bool_t        askPassDoubleMu();
 Bool_t        askPassSig();
 Bool_t        askPassZH();
 Bool_t        askPassDY();
 Bool_t        askPassOffZ();
 Bool_t        askPassNoPair();

 // selection booleans
 Bool_t passSingleEle ;
 Bool_t passSingleMu  ;
 Bool_t passDoubleEle ;
 Bool_t passDoubleMu  ;
 Bool_t passOSSF      ;
 Bool_t passZWindow   ; 
 Bool_t passGoodVtx   ;
 Bool_t passPTOSSFg50 ; 
 Bool_t passOneJet    ;

 // full cut booleans
 Bool_t doesPassSig;
 Bool_t doesPassZH;
 Bool_t doesPassDY;
 Bool_t doesPassOffZ;
 Bool_t doesPassNoPair;
 // personal variables
 Double_t themet;
 Double_t themephi;
 Double_t htall;
 Double_t htslimmedjets;
 Double_t htaodcalojets;

 // for dilepton
 TLorentzVector fourVec_ee, fourVec_mm, fourVec_ll;
 TLorentzVector fourVec_l1, fourVec_l2;
 TLorentzVector fourVec_met;
 TLorentzVector _leptomet;
 Double_t dilep_mass;
 Double_t dilep_pt;

 // selection counters (how many events pass)
 Int_t n_tot;
 Int_t n_test;
 Int_t n_test2;

 Int_t n_passSig;
 Int_t n_passZH;
 Int_t n_passDY;
 Int_t n_passOffZ;
 Int_t n_passNoPair;

 Int_t n_ele_passSig;
 Int_t n_ele_passZH;
 Int_t n_ele_passDY;
 Int_t n_ele_passOffZ;
 Int_t n_ele_passNoPair;

 Int_t n_mu_passSig;
 Int_t n_mu_passZH;
 Int_t n_mu_passDY;
 Int_t n_mu_passOffZ;
 Int_t n_mu_passNoPair;

 Int_t nSelectedPho;
 Int_t nSelectedEle;
 Int_t nSelectedMuo;
 Int_t nSelectedSlimmedJet;
 Int_t nSelectedAODCaloJet;

 // AOD
 int nmatched;
 int nunmatched;
 float drcut;

 // bin names
 std::vector<TString> selbinnames;
 std::vector<TString> jetmultnames;
 std::vector<TString> lepnames;
 // selbinnames  = NoSel, Sig, ZH, DY, OffZ, NoPair
 // jetmultnames = Leading, Subleading, Third, Fourth,allPFJets
 // lepbinname   = ele, mu, NoSel
 static const int SELBINNAMESIZE  = 6;
 static const int JETMULTNAMESIZE = 5; 
 static const int LEPBINNAMESIZE  = 3;

 // initialize histograms as global
 TH1F histoTH1F;
 TH2F histoTH2F;

 // // 2D
 TH2F h_IpVAlpha                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH2F h_IpVjetPt                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH2F h_AlphaVjetPt               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 // // 1D
 // General / leading
 TH1F  h_htall                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_htslimmedjets            [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_htaodcalojets            [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedPho             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedEle             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedMuo             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedSlimmedJet      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJet      [SELBINNAMESIZE][LEPBINNAMESIZE];

 TH1F  h_nVtx                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nGoodVtx                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nTrksPV                  [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_isPVGood                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_rho                      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_rhoCentral               [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nTruePU                  [SELBINNAMESIZE][LEPBINNAMESIZE];

 TH1F  h_pfMET                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_pfMETPhi                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_pfMETsumEt               [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nPho                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoSCEn                  [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoSCPhi                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoSCEta                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nEle                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_elePt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_eleEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_eleEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_elePhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_eleCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_eleSCEn                  [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_eleSCEta                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_eleSCPhi                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_elePFdBetaIsolationRhoEA [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_elePFdBetaIsolationCHS   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_elePFdBetaIsolationDiff  [SELBINNAMESIZE][LEPBINNAMESIZE];

 TH1F  h_nMu                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muPFdBetaIsolation      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSlimmedJets            [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODnCaloJet             [SELBINNAMESIZE][LEPBINNAMESIZE];

 // Jet
 TH1F  h_slimmedJetPt                             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetEn                             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetEta                            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetPhi                            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetRawPt                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetRawEn                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetMt                             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetArea                           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLeadTrackPID                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLeadTrackPt                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLeadTrackEta                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLeadTrackPhi                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLepTrackPID                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLepTrackPt                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLepTrackEta                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLepTrackPhi                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetNConstituents                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetVtxPt                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetVtxMass                        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetVtxNtrks                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetVtx3DVal                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetVtx3DSig                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetCSV2BJetTags                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetJetProbabilityBJetTags         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetpfCombinedMVAV2BJetTags        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetPartonID                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetHadFlvr                        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 TH1F  h_slimmedJetAlphaD                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlphaMaxD                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetSumIP                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetSumIPSig                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetMedianLog10IPSig               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetTrackAngle                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetLogTrackAngle                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetMedianLog10TrackAngle          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetTotalTrackAngle                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 TH1F  h_slimmedJetAlphaMax_PV3onPV2              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlphaMax_PV3onChg              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlphaMax_PV3onAll              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlphaMax_PV2onChg              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlphaMax_PV2onAll              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlpha2Max_PV3onPV2             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlpha2Max_PV3onChg             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlpha2Max_PV3onAll             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlpha2Max_PV2onChg             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetAlpha2Max_PV2onAll             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenJetEn                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenJetPt                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenJetEta                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenJetPhi                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenPartonID                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenEn                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenPt                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenEta                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenPhi                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_slimmedJetGenPartonMomID                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 // AOD jet histograms
 TH1F  h_AODCaloJetPt                             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetEta                            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetPhi                            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAlphaMax                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAlphaMax2                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAlphaMaxPrime                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAlphaMaxPrime2                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetBeta                           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetBeta2                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetSumIP                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetSumIPSig                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetMedianIP                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetMedianLog10IPSig               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetTrackAngle                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetLogTrackAngle                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetMedianLog10TrackAngle          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetTotalTrackAngle                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVx                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVy                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVz                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTotalChiSquared       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDegreesOfFreedom      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexChi2NDoF              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDistanceToBeam        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTransverseError       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTransverseSig         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaEta              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaPhi              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexRecoilPt              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTrackMass             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexTrackEnergy           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotDeltaPhi            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotRecoilPt            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotMedianDeltaPhi      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetNCleanMatchedTracks            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetSumHitsInFrontOfVert           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetSumMissHitsAfterVert           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetHitsInFrontOfVertPerTrack      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetMissHitsAfterVertPerTrack      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfDistToPV                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaZtoPV            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAvfVertexDeltaZtoPV2           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

};

#endif
