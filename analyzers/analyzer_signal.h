
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
 std::vector<int>     jet_passID( double jetPtCut, double jetEtaCut, TString sysbinname="");

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
 // jetmultnames = Leading, Subleading, Third, Fourth

 // initialize histograms as global
 TH1F histoTH1F;
 TH2F histoTH2F;

 // // 2D
 // TH2F h_nvertnjets[6];

 // General / leading


 TH1F h_nVtx[6][2];
 TH1F h_nPU[6][2];
 TH1F h_phoEt[6][2];
 TH1F h_phoEta[6][2];
 TH1F h_phoPhi[6][2];
 TH1F h_elePt[6][2];
 TH1F h_eleEta[6][2];
 TH1F h_elePhi[6][2];
 TH1F h_muPt[6][2];
 TH1F h_muEta[6][2];
 TH1F h_muPhi[6][2];

 TH1F h_htall[6][2];
 TH1F h_htjets[6][2];

 // Jet
 TH1F h_jetPt[6][4][2]; 

 TH1F h_jetTestVariable[6][4][2]; 

 TH1F h_jetEn[6][4][2]; 
 TH1F h_jetEta[6][4][2]; 
 TH1F h_jetPhi[6][4][2]; 
 TH1F h_jetRawPt[6][4][2]; 
 TH1F h_jetRawEn[6][4][2]; 
 TH1F h_jetMt[6][4][2]; 
 TH1F h_jetArea[6][4][2]; 
 TH1F h_jetLeadTrackPt[6][4][2]; 
 TH1F h_jetLeadTrackEta[6][4][2]; 
 TH1F h_jetLeadTrackPhi[6][4][2]; 
 TH1F h_jetLepTrackPID[6][4][2]; 
 TH1F h_jetLepTrackPt[6][4][2]; 
 TH1F h_jetLepTrackEta[6][4][2]; 
 TH1F h_jetLepTrackPhi[6][4][2]; 
 TH1F h_jetCSV2BJetTags[6][4][2]; 
 TH1F h_jetJetProbabilityBJetTags[6][4][2]; 
 TH1F h_jetpfCombinedMVAV2BJetTags[6][4][2]; 
 TH1F h_jetPartonID[6][4][2]; 
 TH1F h_jetHadFlvr[6][4][2]; 
 TH1F h_jetGenJetEn[6][4][2]; 
 TH1F h_jetGenJetPt[6][4][2]; 
 TH1F h_jetGenJetEta[6][4][2]; 
 TH1F h_jetGenJetPhi[6][4][2]; 
 TH1F h_jetGenPartonID[6][4][2]; 
 TH1F h_jetGenEn[6][4][2]; 
 TH1F h_jetGenPt[6][4][2]; 
 TH1F h_jetGenEta[6][4][2]; 
 TH1F h_jetGenPhi[6][4][2]; 
 TH1F h_jetGenPartonMomID[6][4][2]; 

 TH1F h_AK8JetPt[6][4][2]; 
 TH1F h_AK8JetEn[6][4][2]; 
 TH1F h_AK8JetRawPt[6][4][2]; 
 TH1F h_AK8JetRawEn[6][4][2]; 
 TH1F h_AK8JetEta[6][4][2]; 
 TH1F h_AK8JetPhi[6][4][2]; 
 TH1F h_AK8JetMass[6][4][2]; 


};

#endif
