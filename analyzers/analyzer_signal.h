#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"
 //#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <vector>
class analyzer_signal : public analyzer_base {

public :

               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, 
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts);
 TH2F          initSingleHistogramTH2F(TString hnamex, TString htitley,
                                   Int_t nbinsx, Double_t xmin, Double_t xmax,
                                   Int_t nbinsy, Double_t ymin, Double_t ymax);
 TH1F          initSingleHistogramTH1F(TString hname, TString htitle,
                                   Int_t nbins, Double_t xmin,
                                   Double_t xmax);
 virtual void     makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2,
                            TLorentzVector *fv_ee, TLorentzVector *fv_mm, bool *passMM);

 double               dR(double eta1, double phi1, double eta2, double phi2);
 double               DeltaPhi(double phi1, double phi2);

 void                  loadPUWeight();
 Double_t              makePUWeight();
 TH1F*                 PUWeights;
 void                  loadElectronWeight();
 Double_t              makeElectronWeight();
 TH2F*                 EleWeights;

 std::vector<int>     photon_passID  ( int bitnr, double phoPtCut, double phoEtaCut, TString sysbinname="");
 std::vector<int>     electron_passID( int bitnr, double elePtCut, double eleEtaCut, TString sysbinname="");
 std::vector<int>     muon_passID    ( int bitnr, double muPtCut , double muEtaCut , TString sysbinname="");
 std::vector<int>     jet_passID     ( int bitnr, double jetPtCut, double jetEtaCut, TString sysbinname="");
 void tagger(/*Double_t weight*/);
 //std::vector<int>     jet_matchToMiniAOD( TString jettype="" );

 Float_t          getPhotonPt(int idnr, TString sysbinname);
 Float_t          getElectronPt(int i, TString sysbinname);
 Float_t          getMuonPt(int i, TString sysbinname);

 virtual void debug_printobjects();
 virtual void debug_printmuons();
 virtual void debug_printelectrons();
 virtual void debug_printtriggers();

 // 2D Histograms 
 Bool_t        init2DHistograms();
 Bool_t        fill2DHistograms(Double_t weight, int selbin);
 Bool_t        write2DHistograms(int selbin);
 // Jet Variables
 Bool_t        initJetHistograms();
 Bool_t        fillJetHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeJetHistograms(int selbin, int lepbin);
 // Event Variables
 Bool_t        initSigHistograms();
 Bool_t        fillSigHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeSigHistograms(int selbin, int lepbin);

 // vectors of ints
 // each int is an entry in vector
 // associated with object passing
 // some selection
 std::vector<int> photon_list_l;
 std::vector<int> photon_list_m;
 std::vector<int> photon_list_t;
 std::vector<int> photon_list;
 std::vector<int> electron_list_l;
 std::vector<int> electron_list_m;
 std::vector<int> electron_list_t;
 std::vector<int> electron_list;
 std::vector<int> muon_list_l ;
 std::vector<int> muon_list_m ;
 std::vector<int> muon_list_t ;
 std::vector<int> muon_list ;
 std::vector<int> jet_list ;
 
 
 double IPmax = 1.0;
 double IPmin = 0.0;
 double IPrange = IPmax - IPmin;     //range to be covered
 double IPstep  = (IPrange/N); //step size
 static const int  N   = 1000;  //number of subdivisions for tagger function
 std::vector<double> tags;
 std::vector<double> Number;
 std::vector<double> CutValue;
 //std::vector<int> AODcalojet_list;
 //std::vector<int> AODPFjet_list;
 //std::vector<int> AODPFchsjet_list;

 TString phoid;
 TString eleid;
 TString muoid;
 TString jetid;

 int phoidbit;
 int eleidbit;
 int muoidbit;
 int jetidbit;
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
 Double_t htjets;

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
 Int_t ntag;
 Double_t number_sig;
 Double_t number_bkg;

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
 Int_t nSelectedJet;

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
 TH1F *h_ntags = new TH1F("h_ntags", "ntags", 10, 0, 10);
 TGraph* NumByCut = new TGraph(N);

 // // 2D
 TH2F h_IpVAlpha                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH2F h_IpVjetPt                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH2F h_AlphaVjetPt               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 // // 1D
 // General / leading
 TH1F  h_htall                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_htjets                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedPho             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedEle             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedMuo             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedJet             [SELBINNAMESIZE][LEPBINNAMESIZE];

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
// TH1F  h_phoEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
// TH1F  h_phoPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_phoPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
// TH1F  h_phoSCEn                  [SELBINNAMESIZE][LEPBINNAMESIZE];
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
// TH1F  h_elePFdBetaIsolationRhoEA [SELBINNAMESIZE][LEPBINNAMESIZE];
// TH1F  h_elePFdBetaIsolationCHS   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_elePFdBetaIsolationDiff  [SELBINNAMESIZE][LEPBINNAMESIZE];

 TH1F  h_nMu                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_muPFdBetaIsolation      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nJet                    [SELBINNAMESIZE][LEPBINNAMESIZE];

 // Jet
 TH1F  h_jetPt                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetEn                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetEta                        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetPhi                        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetRawPt                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetRawEn                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetArea                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetLeadTrackPt                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetLeadTrackEta               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetLeadTrackPhi               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetCSV2BJetTags               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetJetProbabilityBJetTags     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetpfCombinedMVAV2BJetTags    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax2                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMaxP                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMaxP2                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_alphaMax_jetDauVertex_r       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax_PV3onPV2          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax_PV3onNeu          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax_PV3onAll          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax_PV2onNeu          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMax_PV2onAll          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlpha2Max_PV3onPV2         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlpha2Max_PV3onNeu         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlpha2Max_PV3onAll         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlpha2Max_PV2onNeu         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlpha2Max_PV2onAll         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaD                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetAlphaMaxD                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetLog10IPSig                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetMedianLog10IPSig           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetSumIP                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetSumIPSig                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetTrackAngle                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetLogTrackAngle              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetMedianLogTrackAngle        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetTotalTrackAngle            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetNConstituents              [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetVtxPt                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetVtxMass                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetVtxNtrks                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetVtx3DVal                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_jetVtx3DSig                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
/*
 TH1F  h_AODCaloJetPt                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetEta                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetPhi                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetAlphaMax            [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetAlphaMax2           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetAlphaMaxPrime       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetAlphaMaxPrime2      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetBeta                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODCaloJetBeta2               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 

 TH1F  h_AODPFJetPt                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODPFJetEta                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODPFJetPhi                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 

 TH1F  h_AODPFchsJetPt                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODPFchsJetEta                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F  h_AODPFchsJetPhi                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
*/
};

#endif
