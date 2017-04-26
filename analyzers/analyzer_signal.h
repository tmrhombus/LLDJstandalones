
#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"
#include <TH1.h>
#include <TH2.h>

class analyzer_signal : public analyzer_base {

public :

               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, Bool_t isMC,
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts);
 TH2F          initSingleHistogramTH2F(TString hnamex, TString htitley,
                                   Int_t nbinsx, Double_t xmin, Double_t xmax,
                                   Int_t nbinsy, Double_t ymin, Double_t ymax);
 TH1F          initSingleHistogramTH1F(TString hname, TString htitle,
                                   Int_t nbins, Double_t xmin,
                                   Double_t xmax);
 // 2D Histograms 
 Bool_t        init2DHistograms();
 Bool_t        fill2DHistograms(Double_t weight, int selbin);
 Bool_t        write2DHistograms(int selbin);
 // Jet Variables
 Bool_t        initJetHistograms();
 Bool_t        fillJetHistograms(Double_t weight, int selbin);
 Bool_t        writeJetHistograms(int selbin);
 // Event Variables
 Bool_t        initSigHistograms();
 Bool_t        fillSigHistograms(Double_t weight, int selbin);
 Bool_t        writeSigHistograms(int selbin);
 // Selections
 Bool_t        askPassSig();
 Bool_t        askPassZH();
 Bool_t        askPassDY();
 Bool_t        askPassOffZ();
 Bool_t        askPassNoPair();

 // selection variables
 Bool_t doesPassSig;
 Bool_t doesPassZH;
 Bool_t doesPassDY;
 Bool_t doesPassOffZ;
 Bool_t doesPassNoPair;

// int    safeNGOODVERTICES      = 0;
//   Int_t           nVtx;
// int    safeNDoubleElTriggers  = 0;
//   vector<unsigned int> *eleFiredDoubleTrgs;
// int    safeNDoubleMuTriggers  = 0;
//   vector<unsigned int> *muFiredTrgs;
// int    safeNOSSF              = 0;
// double safeMOSSF              = 0.; 
// double safePTOSSF             = 0.; 
// int    safeJetNJets           = 0;
//   Int_t           nJet;

 Int_t ntot;
 Int_t npassSig;
 Int_t npassZH;
 Int_t npassDY;
 Int_t npassOffZ;
 Int_t npassNoPair;

 // bin names
 std::vector<TString> selbinnames;
 std::vector<TString> jetmultnames;

 // selbinnames  = NoSel, Sig, ZH, DY, OffZ, NoPair
 // jetmultnames = Leading, Subleading, Third, Fourth

 // initialize histograms as global
 TH1F histoTH1F;
 TH2F histoTH2F;

 // // 2D
 // TH2F h_nvertnjets[6];

 // General / leading
 TH1F h_nVtx[6];
 TH1F h_nPU[6];
 TH1F h_phoEt[6];
 TH1F h_phoEta[6];
 TH1F h_phoPhi[6];
 TH1F h_elePt[6];
 TH1F h_eleEta[6];
 TH1F h_elePhi[6];
 TH1F h_muPt[6];
 TH1F h_muEta[6];
 TH1F h_muPhi[6];

 // Jet
 TH1F h_jetPt[6][4]; 
 TH1F h_jetEn[6][4]; 
 TH1F h_jetEta[6][4]; 
 TH1F h_jetPhi[6][4]; 
 TH1F h_jetRawPt[6][4]; 
 TH1F h_jetRawEn[6][4]; 
 TH1F h_jetMt[6][4]; 
 TH1F h_jetArea[6][4]; 
 TH1F h_jetLeadTrackPt[6][4]; 
 TH1F h_jetLeadTrackEta[6][4]; 
 TH1F h_jetLeadTrackPhi[6][4]; 
 TH1F h_jetLepTrackPID[6][4]; 
 TH1F h_jetLepTrackPt[6][4]; 
 TH1F h_jetLepTrackEta[6][4]; 
 TH1F h_jetLepTrackPhi[6][4]; 
 TH1F h_jetCSV2BJetTags[6][4]; 
 TH1F h_jetJetProbabilityBJetTags[6][4]; 
 TH1F h_jetpfCombinedMVAV2BJetTags[6][4]; 
 TH1F h_jetPartonID[6][4]; 
 TH1F h_jetHadFlvr[6][4]; 
 TH1F h_jetGenJetEn[6][4]; 
 TH1F h_jetGenJetPt[6][4]; 
 TH1F h_jetGenJetEta[6][4]; 
 TH1F h_jetGenJetPhi[6][4]; 
 TH1F h_jetGenPartonID[6][4]; 
 TH1F h_jetGenEn[6][4]; 
 TH1F h_jetGenPt[6][4]; 
 TH1F h_jetGenEta[6][4]; 
 TH1F h_jetGenPhi[6][4]; 
 TH1F h_jetGenPartonMomID[6][4]; 

 TH1F h_AK8JetPt[6][4]; 
 TH1F h_AK8JetEn[6][4]; 
 TH1F h_AK8JetRawPt[6][4]; 
 TH1F h_AK8JetRawEn[6][4]; 
 TH1F h_AK8JetEta[6][4]; 
 TH1F h_AK8JetPhi[6][4]; 
 TH1F h_AK8JetMass[6][4]; 


};

#endif
