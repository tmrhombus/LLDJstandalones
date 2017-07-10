
#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"
// #include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TLorentzVector.h>

class analyzer_signal : public analyzer_base {
//private:
//constexpr int JETMULTNAMESIZE = 5;
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

 std::vector<int>     photon_passLooseID(double phoPtCut=15., double phoEtaCut=1.4442, TString sysbinname="");
  Double_t            EAchargedworst(Double_t eta);
  Double_t            EAcharged(Double_t eta);
  Double_t            EAneutral(Double_t eta);
  Double_t            EAphoton(Double_t eta);

 std::vector<int>     electron_passLooseID( double elePtCut, double eleEtaCut, TString sysbinname="");
 std::vector<int>     electron_passTightID( double elePtCut, double eleEtaCut, TString sysbinname="");
 std::vector<int>     muon_passLooseID( double muPtCut, double muEtaCut, TString sysbinname="");
 std::vector<int>     muon_passTightID( double muPtCut, double muEtaCut, TString sysbinname="");
 std::vector<int>     jet_passID( double jetPtCut, double jetEtaCut, TString PFJetID, TString sysbinname="");

 Float_t          getPhotonPt(int idnr, TString sysbinname);
 Float_t          getElectronPt(int i, TString sysbinname);
 Float_t          getMuonPt(int i, TString sysbinname);

 virtual void debug_printobjects();

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
 std::vector<int> photon_list;
 std::vector<int> electron_list;
 std::vector<int> muon_list ;
 std::vector<int> jet_list ;

 // Selection functions
 Bool_t        askPassSingleEle();
 Bool_t        askPassSingleMu();
 Bool_t        askPassSig();
 Bool_t        askPassZH();
 Bool_t        askPassDY();
 Bool_t        askPassOffZ();
 Bool_t        askPassNoPair();

 // selection booleans
 Bool_t passSingleEle ;
 Bool_t passSingleMu  ;
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
 // TH2F h_nvertnjets[SELBINNAMESIZE];

 // General / leading


 TH1F h_nVtx                          [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_nPU                           [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_phoEt                         [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_phoEta                        [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_phoPhi                        [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_elePt                         [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_eleEta                        [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_elePhi                        [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_muPt                          [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_muEta                         [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_muPhi                         [SELBINNAMESIZE][LEPBINNAMESIZE];

 TH1F h_htall                         [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_htjets                        [SELBINNAMESIZE][LEPBINNAMESIZE];

// TH1F h_jetTestVariable[SELBINNAMESIZE][4];
 


// Jet
 TH1F h_jetPt                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 

 TH1F h_jetSumIP                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetSumIPSig                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetLog10IPSig                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetMedianLog10IPSig           [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetTrackPhi2                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetTrackPDGID		      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetTrackMom		      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetNConstituents	      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 TH1F h_jetTestVariable               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 

 TH1F h_jetAlphaMax                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetAlphaMax2                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetAlphaMaxP                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F h_jetAlphaMaxP2                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 // TH1F h_CA2_x [SELBINNAMESIZE][4][LEPBINNAMESIZE];
 // TH1F h_CA2_y [SELBINNAMESIZE][4][LEPBINNAMESIZE];
 // TH1F h_CA2_z [SELBINNAMESIZE][4][LEPBINNAMESIZE];
 TH1F h_jetEn                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetEta                        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetPhi                        [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetRawPt                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetRawEn                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetMt                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetArea                       [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLeadTrackPt                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLeadTrackEta               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLeadTrackPhi               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLepTrackPID                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLepTrackPt                 [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLepTrackEta                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetLepTrackPhi                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetCSV2BJetTags               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetJetProbabilityBJetTags     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetpfCombinedMVAV2BJetTags    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetPartonID                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetHadFlvr                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenJetEn                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenJetPt                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenJetEta                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenJetPhi                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenPartonID                [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenEn                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenPt                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenEta                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenPhi                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_jetGenPartonMomID             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 

 TH1F h_AK8JetPt                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_AK8JetEn                      [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_AK8JetRawPt                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_AK8JetRawEn                   [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_AK8JetEta                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_AK8JetPhi                     [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 
 TH1F h_AK8JetMass                    [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE]; 


};

#endif
