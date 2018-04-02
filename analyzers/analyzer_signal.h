#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <vector>
#include "TTree.h"
#include "TBranch.h"
#include <stdlib.h> 
class analyzer_signal : public analyzer_base {

public :
 // basic functions
               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, 
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts, TFile *optfile);

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
 std::vector<int>     aodcalojet_passID ( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname="");

 void tagger();
 std::vector<int>   OPT_Event;
 std::vector<float> OPT_EventWeight;
 std::vector<int>   OPT_nJets;
 std::vector<float> OPT_AODCaloJetMedianLog10IPSig;
 std::vector<float> OPT_AODCaloJetMedianLog10TrackAngle;
 std::vector<float> OPT_AODCaloJetAlphaMax;
 TTree *OPTtree = new TTree("OPTtree","Optimization Variables");
 TBranch* b1 = OPTtree->Branch("OPT_Event"                              , &OPT_Event); 
 TBranch* b2 = OPTtree->Branch("OPT_EventWeight"                        , &OPT_EventWeight); 
 //TBranch* b3 = OPTtree->Branch("OPT_nJets"                              , &OPT_nJets); 
 TBranch* b4 = OPTtree->Branch("OPT_AODCaloJetMedianLog10IPSig"         , &OPT_AODCaloJetMedianLog10IPSig); 
 TBranch* b5 = OPTtree->Branch("OPT_AODCaloJetMedianLog10TrackAngle"    , &OPT_AODCaloJetMedianLog10TrackAngle); 
 TBranch* b6 = OPTtree->Branch("OPT_AODCaloJetAlphaMax"                 , &OPT_AODCaloJetAlphaMax); 
 
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
 // Event Variables
 Bool_t        initBasicHistograms();
 Bool_t        fillBasicHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeBasicHistograms(int selbin, int lepbin);
 // SlimmedJet Variables
 Bool_t        initSlimmedJetHistograms();
 Bool_t        fillSlimmedJetHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeSlimmedJetHistograms(int selbin, int lepbin);
 // AODCaloJet Variables
 Bool_t        initAODCaloJetHistograms();
 Bool_t        fillAODCaloJetHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeAODCaloJetHistograms(int selbin, int lepbin);

 // vectors of ints
 // each int is an entry in vector
 // associated with object passing
 // some selection
 std::vector<int> photon_list;
 std::vector<int> electron_list;
 std::vector<int> muon_list ;
 std::vector<int> aodcalojet_list;
 

 // ID bits for collections
 TString phoid;
 TString eleid;
 TString muoid;
 TString jetid;

 int phoidbit;
 int eleidbit;
 int muoidbit;
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
 float jetmatchdRcut ;
 float objcleandRcut ;

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
 TH1F  h_htaodcalojets            [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedPho             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedEle             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedMuo             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedSlimmedJet      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJet      [SELBINNAMESIZE][LEPBINNAMESIZE];

 //TH1F  h_nVtx                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_nGoodVtx                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_nTrksPV                  [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_isPVGood                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_rho                      [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_rhoCentral               [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_nTruePU                  [SELBINNAMESIZE][LEPBINNAMESIZE];

 //TH1F  h_AOD_pfMET                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_pfMET_phi                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_AOD_pfMETsumEt               [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nAODPho                      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoSCEn                  [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoSCPhi                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoSCEta                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_nEle                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_elePt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_eleEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_eleEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_elePhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_eleCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_eleSCEn                  [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_eleSCEta                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_eleSCPhi                 [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_elePFdBetaIsolationRhoEA [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_elePFdBetaIsolationCHS   [SELBINNAMESIZE][LEPBINNAMESIZE];
 //TH1F  h_elePFdBetaIsolationDiff  [SELBINNAMESIZE][LEPBINNAMESIZE];

 //TH1F  h_nMu                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muPFdBetaIsolation      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODnCaloJet             [SELBINNAMESIZE][LEPBINNAMESIZE];

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
