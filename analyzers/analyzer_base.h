#ifndef analyzer_base_h
#define analyzer_base_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

#include <stdlib.h>     /* getenv */

#include "vector"

class analyzer_base {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // global variables
   Bool_t makelog;
   Bool_t isMC;
   FILE * logfile;
   Double_t event_weight;

   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // MC and Data
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // Declaration of leaf types
   Int_t                 run;
   Long64_t              event;
   Int_t                 lumis;
   Bool_t                isData;
   Int_t                 nVtx;
   Int_t                 nGoodVtx;
   Int_t                 nTrksPV;
   Bool_t                isPVGood;
   Float_t               vtx;
   Float_t               vty;
   Float_t               vtz;
   Float_t               rho;
   Float_t               rhoCentral;
   Int_t                 nTruePU;
   ULong64_t             HLT_Ele23Loose;
   ULong64_t             HLT_Ele27Tight;
   ULong64_t             HLT_Ele17Ele12;
   ULong64_t             HLT_Ele23Ele12;
   ULong64_t             HLT_IsoMu22;
   ULong64_t             HLT_IsoTkMu22;
   ULong64_t             HLT_Mu17Mu8;
   ULong64_t             HLT_Mu17TkMu8;
   Int_t                 nPho;
   std::vector<float>   *phoPt;
   std::vector<float>   *phoEn;
   std::vector<float>   *phoEta;
   std::vector<float>   *phoPhi;
   std::vector<float>   *phoSCEn;
   std::vector<float>   *phoSCEta;
   std::vector<float>   *phoSCPhi;
   std::vector<unsigned short> *phoIDbit;
   std::vector<float>   *phoIDMVA;
   std::vector<float>   *phoObjPFChIso;
   std::vector<float>   *phoObjPFPhoIso;
   std::vector<float>   *phoObjPFNeuIso;
   std::vector<float>   *phoObjPFChWorstIso;
   std::vector<float>   *phoMapPFChIso;
   std::vector<float>   *phoMapPFPhoIso;
   std::vector<float>   *phoMapPFNeuIso;
   std::vector<float>   *phoMapPFChWorstIso;
   Int_t                 nEle;
   std::vector<float>   *elePt;
   std::vector<float>   *eleEn;
   std::vector<float>   *eleEta;
   std::vector<float>   *elePhi;
   std::vector<float>   *eleSCEn;
   std::vector<float>   *eleSCEta;
   std::vector<float>   *eleSCPhi;
   std::vector<int>     *eleCharge;
   std::vector<int>     *eleChargeConsistent;
   std::vector<unsigned short> *eleIDbit;
   std::vector<float>   *elePFdBetaIsolationRhoEA;
   std::vector<float>   *elePFdBetaIsolationCHS;
   std::vector<float>   *elePFdBetaIsolationDiff;
   Int_t           nMu;
   std::vector<float>   *muPt;
   std::vector<float>   *muEn;
   std::vector<float>   *muEta;
   std::vector<float>   *muPhi;
   std::vector<int>     *muCharge;
   std::vector<int>     *muType;
   std::vector<unsigned short> *muIDbit;
   std::vector<bool>    *muPassLooseID;
   std::vector<bool>    *muPassHipID;
   std::vector<bool>    *muPassTighID;
   std::vector<int>     *muNumberOfMissingInnerHits;
   std::vector<int>     *muNumberOfMissingMiddleHits;
   std::vector<int>     *muNumberOfMissingOuterHits;
   std::vector<int>     *muNumberOfMatchedStations;
   std::vector<int>     *muNumberOfValidPixelHits;
   std::vector<int>     *muTrackerLayersWithMeasurement;
   std::vector<int>     *muIsGlobalMuon;
   std::vector<int>     *muIsPFMuon;
   std::vector<float>   *muPFdBetaIsolation;
   Int_t                 nJet;
   std::vector<float>   *jetPt;
   std::vector<float>   *jetEn;
   std::vector<float>   *jetEta;
   std::vector<float>   *jetPhi;
   std::vector<float>   *jetRawPt;
   std::vector<float>   *jetRawEn;
   std::vector<float>   *jetMt;
   std::vector<float>   *jetArea;
   std::vector<float>   *jetLeadTrackPt;
   std::vector<float>   *jetLeadTrackEta;
   std::vector<float>   *jetLeadTrackPhi;
   std::vector<int>     *jetLepTrackPID;
   std::vector<float>   *jetLepTrackPt;
   std::vector<float>   *jetLepTrackEta;
   std::vector<float>   *jetLepTrackPhi;
   std::vector<float>   *jetCHF;
   std::vector<float>   *jetNHF;
   std::vector<float>   *jetCEF;
   std::vector<float>   *jetNEF;
   std::vector<int>     *jetNCH;
   std::vector<int>     *jetNNP;
   std::vector<float>   *jetMUF;
   std::vector<float>   *jetHFHAE;
   std::vector<float>   *jetHFEME;
   std::vector<int>     *jetNConstituents;
   std::vector<float>   *jetVtxPt;
   std::vector<float>   *jetVtxMass;
   std::vector<float>   *jetVtxNtrks;
   std::vector<float>   *jetVtx3DVal;
   std::vector<float>   *jetVtx3DSig;
   std::vector<float>   *jetCSV2BJetTags;
   std::vector<float>   *jetJetProbabilityBJetTags;
   std::vector<float>   *jetpfCombinedMVAV2BJetTags;
   std::vector<int>     *jetPartonID;
   std::vector<int>     *jetHadFlvr;
   std::vector<bool>    *jetPFLooseId;
   std::vector<int>     *jetID;
   std::vector<float>   *jetPUID;
   std::vector<int>     *jetPUFullID;
   std::vector<float>   *jetJECUnc;
   std::vector<float>   *jetP4Smear;
   std::vector<float>   *jetP4SmearUp;
   std::vector<float>   *jetP4SmearDo;
   std::vector<unsigned int> *jetFiredTrgs;
   std::vector<float>        *jetAlphaD;
   std::vector<float>        *jetAlphaMaxD;
   std::vector<float>        *jetSumIP;
   std::vector<float>        *jetSumIPSig;
   std::vector<float>        *jetLog10IPSig;
   std::vector<float>        *jetMedianLog10IPSig;
   std::vector<float>        *jetTrackAngle;
   std::vector<float>        *jetLogTrackAngle;
   std::vector<float>        *jetMedianLogTrackAngle;
   std::vector<float>        *jetTotalTrackAngle;
   std::vector<float>        *jetAlphaMax;
   std::vector<float>        *jetAlphaMax2;
   std::vector<float>        *jetAlphaMaxP;
   std::vector<float>        *jetAlphaMaxP2;
   std::vector<float>        *jetDauVertex_x;
   std::vector<float>        *jetDauVertex_y;
   std::vector<float>        *jetDauVertex_z;
   std::vector<float>        *jetDauVertex_r;
   std::vector<float>        *alphaMax_jetDauVertex_r;
   std::vector<float>        *jetAlphaMax_PV3onPV2;
   std::vector<float>        *jetAlphaMax_PV3onNeu;
   std::vector<float>        *jetAlphaMax_PV3onAll;
   std::vector<float>        *jetAlphaMax_PV2onNeu;
   std::vector<float>        *jetAlphaMax_PV2onAll;
   std::vector<float>        *jetAlpha2Max_PV3onPV2;
   std::vector<float>        *jetAlpha2Max_PV3onNeu;
   std::vector<float>        *jetAlpha2Max_PV3onAll;
   std::vector<float>        *jetAlpha2Max_PV2onNeu;
   std::vector<float>        *jetAlpha2Max_PV2onAll;
   std::vector<std::vector<float> > *jetTrackPt;
   std::vector<std::vector<float> > *jetTrackEta;
   std::vector<std::vector<float> > *jetTrackPhi;
   std::vector<std::vector<int> >   *jetTrackPDGID;
   std::vector<std::vector<int> >   *jetTrackMomPDGID;
   std::vector<float>               *jetGenJetEn;
   std::vector<float>               *jetGenJetPt;
   std::vector<float>               *jetGenJetEta;
   std::vector<float>               *jetGenJetPhi;
   std::vector<int>                 *jetGenPartonID;
   std::vector<float>               *jetGenEn;
   std::vector<float>               *jetGenPt;
   std::vector<float>               *jetGenEta;
   std::vector<float>               *jetGenPhi;
   std::vector<int>                 *jetGenPartonMomID;
   Int_t                             metFilters;
   Float_t                           pfMET;
   Float_t                           pfMETPhi;
   Float_t                           pfMETsumEt;
   Float_t                           pfMETmEtSig;
   Float_t                           pfMETSig;
   Float_t                           pfMET_T1JERUp;
   Float_t                           pfMET_T1JERDo;
   Float_t                           pfMET_T1JESUp;
   Float_t                           pfMET_T1JESDo;
   Float_t                           pfMET_T1UESUp;
   Float_t                           pfMET_T1UESDo;
   Float_t                           pfMETPhi_T1JESUp;
   Float_t                           pfMETPhi_T1JESDo;
   Float_t                           pfMETPhi_T1UESUp;
   Float_t                           pfMETPhi_T1UESDo;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nGoodVtx;   //!
   TBranch        *b_nTrksPV;   //!
   TBranch        *b_isPVGood;   //!
   TBranch        *b_vtx;   //!
   TBranch        *b_vty;   //!
   TBranch        *b_vtz;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rhoCentral;   //!
   TBranch        *b_nTruePU;   //!
   TBranch        *b_HLT_Ele23Loose;   //!
   TBranch        *b_HLT_Ele27Tight;   //!
   TBranch        *b_HLT_Ele17Ele12;   //!
   TBranch        *b_HLT_Ele23Ele12;   //!
   TBranch        *b_HLT_IsoMu22;   //!
   TBranch        *b_HLT_IsoTkMu22;   //!
   TBranch        *b_HLT_Mu17Mu8;   //!
   TBranch        *b_HLT_Mu17TkMu8;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoPt;   //!
   TBranch        *b_phoEn;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoSCEn;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoIDbit;   //!
   TBranch        *b_phoIDMVA;   //!
   TBranch        *b_phoObjPFChIso;   //!
   TBranch        *b_phoObjPFPhoIso;   //!
   TBranch        *b_phoObjPFNeuIso;   //!
   TBranch        *b_phoObjPFChWorstIso;   //!
   TBranch        *b_phoMapPFChIso;   //!
   TBranch        *b_phoMapPFPhoIso;   //!
   TBranch        *b_phoMapPFNeuIso;   //!
   TBranch        *b_phoMapPFChWorstIso;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleSCEn;   //!
   TBranch        *b_eleSCEta;   //!
   TBranch        *b_eleSCPhi;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleChargeConsistent;   //!
   TBranch        *b_eleIDbit;   //!
   TBranch        *b_elePFdBetaIsolationRhoEA;   //!
   TBranch        *b_elePFdBetaIsolationCHS;   //!
   TBranch        *b_elePFdBetaIsolationDiff;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEn;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muIDbit;   //!
   TBranch        *b_muPassLooseID;   //!
   TBranch        *b_muPassHipID;   //!
   TBranch        *b_muPassTighID;   //!
   TBranch        *b_muNumberOfMissingInnerHits;   //!
   TBranch        *b_muNumberOfMissingMiddleHits;   //!
   TBranch        *b_muNumberOfMissingOuterHits;   //!
   TBranch        *b_muNumberOfMatchedStations;   //!
   TBranch        *b_muNumberOfValidPixelHits;   //!
   TBranch        *b_muTrackerLayersWithMeasurement;   //!
   TBranch        *b_muIsGlobalMuon;   //!
   TBranch        *b_muIsPFMuon;   //!
   TBranch        *b_muPFdBetaIsolation;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEn;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetRawPt;   //!
   TBranch        *b_jetRawEn;   //!
   TBranch        *b_jetMt;   //!
   TBranch        *b_jetArea;   //!
   TBranch        *b_jetLeadTrackPt;   //!
   TBranch        *b_jetLeadTrackEta;   //!
   TBranch        *b_jetLeadTrackPhi;   //!
   TBranch        *b_jetLepTrackPID;   //!
   TBranch        *b_jetLepTrackPt;   //!
   TBranch        *b_jetLepTrackEta;   //!
   TBranch        *b_jetLepTrackPhi;   //!
   TBranch        *b_jetCHF;   //!
   TBranch        *b_jetNHF;   //!
   TBranch        *b_jetCEF;   //!
   TBranch        *b_jetNEF;   //!
   TBranch        *b_jetNCH;   //!
   TBranch        *b_jetNNP;   //!
   TBranch        *b_jetMUF;   //!
   TBranch        *b_jetHFHAE;   //!
   TBranch        *b_jetHFEME;   //!
   TBranch        *b_jetNConstituents;   //!
   TBranch        *b_jetVtxPt;   //!
   TBranch        *b_jetVtxMass;   //!
   TBranch        *b_jetVtxNtrks;   //!
   TBranch        *b_jetVtx3DVal;   //!
   TBranch        *b_jetVtx3DSig;   //!
   TBranch        *b_jetCSV2BJetTags;   //!
   TBranch        *b_jetJetProbabilityBJetTags;   //!
   TBranch        *b_jetpfCombinedMVAV2BJetTags;   //!
   TBranch        *b_jetPartonID;   //!
   TBranch        *b_jetHadFlvr;   //!
   TBranch        *b_jetPFLooseId;   //!
   TBranch        *b_jetID;   //!
   TBranch        *b_jetPUID;   //!
   TBranch        *b_jetPUFullID;   //!
   TBranch        *b_jetJECUnc;   //!
   TBranch        *b_jetP4Smear;   //!
   TBranch        *b_jetP4SmearUp;   //!
   TBranch        *b_jetP4SmearDo;   //!
   TBranch        *b_jetFiredTrgs;   //!
   TBranch        *b_jetAlphaD;   //!
   TBranch        *b_jetAlphaMaxD;   //!
   TBranch        *b_jetSumIP;   //!
   TBranch        *b_jetSumIPSig;   //!
   TBranch        *b_jetLog10IPSig;   //!
   TBranch        *b_jetMedianLog10IPSig;   //!
   TBranch        *b_jetTrackAngle;   //!
   TBranch        *b_jetLogTrackAngle;   //!
   TBranch        *b_jetMedianLogTrackAngle;   //!
   TBranch        *b_jetTotalTrackAngle;   //!
   TBranch        *b_jetAlphaMax;   //!
   TBranch        *b_jetAlphaMax2;   //!
   TBranch        *b_jetAlphaMaxP;   //!
   TBranch        *b_jetAlphaMaxP2;   //!
   TBranch        *b_jetDauVertex_x;   //!
   TBranch        *b_jetDauVertex_y;   //!
   TBranch        *b_jetDauVertex_z;   //!
   TBranch        *b_jetDauVertex_r;   //!
   TBranch        *b_alphaMax_jetDauVertex_r;   //!
   TBranch        *b_jetAlphaMax_PV3onPV2;   //!
   TBranch        *b_jetAlphaMax_PV3onNeu;   //!
   TBranch        *b_jetAlphaMax_PV3onAll;   //!
   TBranch        *b_jetAlphaMax_PV2onNeu;   //!
   TBranch        *b_jetAlphaMax_PV2onAll;   //!
   TBranch        *b_jetAlpha2Max_PV3onPV2;   //!
   TBranch        *b_jetAlpha2Max_PV3onNeu;   //!
   TBranch        *b_jetAlpha2Max_PV3onAll;   //!
   TBranch        *b_jetAlpha2Max_PV2onNeu;   //!
   TBranch        *b_jetAlpha2Max_PV2onAll;   //!
   TBranch        *b_jetTrackPt;   //!
   TBranch        *b_jetTrackEta;   //!
   TBranch        *b_jetTrackPhi;   //!
   TBranch        *b_jetTrackPDGID;   //!
   TBranch        *b_jetTrackMomPDGID;   //!
   TBranch        *b_jetGenJetEn;   //!
   TBranch        *b_jetGenJetPt;   //!
   TBranch        *b_jetGenJetEta;   //!
   TBranch        *b_jetGenJetPhi;   //!
   TBranch        *b_jetGenPartonID;   //!
   TBranch        *b_jetGenEn;   //!
   TBranch        *b_jetGenPt;   //!
   TBranch        *b_jetGenEta;   //!
   TBranch        *b_jetGenPhi;   //!
   TBranch        *b_jetGenPartonMomID;   //!
   TBranch        *b_metFilters;   //!
   TBranch        *b_pfMET;   //!
   TBranch        *b_pfMETPhi;   //!
   TBranch        *b_pfMETsumEt;   //!
   TBranch        *b_pfMETmEtSig;   //!
   TBranch        *b_pfMETSig;   //!
   TBranch        *b_pfMET_T1JERUp;   //!
   TBranch        *b_pfMET_T1JERDo;   //!
   TBranch        *b_pfMET_T1JESUp;   //!
   TBranch        *b_pfMET_T1JESDo;   //!
   TBranch        *b_pfMET_T1UESUp;   //!
   TBranch        *b_pfMET_T1UESDo;   //!
   TBranch        *b_pfMETPhi_T1JESUp;   //!
   TBranch        *b_pfMETPhi_T1JESDo;   //!
   TBranch        *b_pfMETPhi_T1UESUp;   //!
   TBranch        *b_pfMETPhi_T1UESDo;   //!


   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // MC  (Hen)
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // Declaration of leaf types
   Float_t         genMET;
   Float_t         genMETPhi;
   TBranch        *b_genMET;   //!
   TBranch        *b_genMETPhi;   //!

   //analyzer_base(TTree *tree=0);
   analyzer_base();
   virtual ~analyzer_base();
   virtual void     Init(TTree *tree, Bool_t isitMC, Bool_t domakelog);
   virtual Long64_t LoadTree(Long64_t entry);
   Double_t         makeEventWeight(Double_t crossSec, Double_t lumi,
                                    Double_t nrEvents);
};

#endif

