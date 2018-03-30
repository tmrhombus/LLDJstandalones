#ifndef analyzer_base_h
#define analyzer_base_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

#include <stdlib.h>     /* getenv */

#include "vector"

//#include "DataFormats/Math/interface/deltaR.h"

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
   Int_t           run;
   Long64_t        event;
   Int_t           lumis;
   Bool_t          isData;
   Int_t           nVtx;
   Int_t           nGoodVtx;
   Int_t           nTrksPV;
   Bool_t          isPVGood;
   Float_t         vtx;
   Float_t         vty;
   Float_t         vtz;
   Float_t         rho;
   Float_t         rhoCentral;
   Int_t           nTruePU;
   ULong64_t       HLT_Ele23Loose;
   ULong64_t       HLT_Ele27Tight;
   ULong64_t       HLT_Ele17Ele12;
   ULong64_t       HLT_Ele23Ele12;
   ULong64_t       HLT_IsoMu22;
   ULong64_t       HLT_IsoTkMu22;
   ULong64_t       HLT_Mu17Mu8;
   ULong64_t       HLT_Mu17TkMu8;
   std::vector<int>     *llpId;
   std::vector<int>     *llpStatus;
   std::vector<float>   *llpPt;
   std::vector<float>   *llpEta;
   std::vector<float>   *llpPhi;
   std::vector<float>   *llpMass;
   std::vector<int>     *llpDaughterId;
   std::vector<int>     *llpDaughterStatus;
   std::vector<float>   *llpDaughterPt;
   std::vector<float>   *llpDaughterEta;
   std::vector<float>   *llpDaughterPhi;
   std::vector<float>   *llpDaughterMass;
// #brokenphotons
   Int_t           nPho;
   std::vector<float>   *phoPt;
   std::vector<float>   *phoEn;
   std::vector<float>   *phoEta;
   std::vector<float>   *phoPhi;
   std::vector<float>   *phoSCEn;
   std::vector<float>   *phoSCEta;
   std::vector<float>   *phoSCPhi;
   std::vector<unsigned short> *phoIDbit;
   //std::vector<float>   *phoIDMVA;
   //std::vector<float>   *phoObjPFChIso;
   //std::vector<float>   *phoObjPFPhoIso;
   //std::vector<float>   *phoObjPFNeuIso;
   //std::vector<float>   *phoObjPFChWorstIso;
   //std::vector<float>   *phoMapPFChIso;
   //std::vector<float>   *phoMapPFPhoIso;
   //std::vector<float>   *phoMapPFNeuIso;
   //std::vector<float>   *phoMapPFChWorstIso;
   Int_t           nEle;
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
   Int_t           nSlimmedJets;
   std::vector<float>   *slimmedJetPt;
   std::vector<float>   *slimmedJetEn;
   std::vector<float>   *slimmedJetEta;
   std::vector<float>   *slimmedJetPhi;
   std::vector<float>   *slimmedJetRawPt;
   std::vector<float>   *slimmedJetRawEn;
   std::vector<float>   *slimmedJetMt;
   std::vector<float>   *slimmedJetArea;
   std::vector<float>   *slimmedJetLeadTrackPID;
   std::vector<float>   *slimmedJetLeadTrackPt;
   std::vector<float>   *slimmedJetLeadTrackEta;
   std::vector<float>   *slimmedJetLeadTrackPhi;
   std::vector<int>     *slimmedJetLepTrackPID;
   std::vector<float>   *slimmedJetLepTrackPt;
   std::vector<float>   *slimmedJetLepTrackEta;
   std::vector<float>   *slimmedJetLepTrackPhi;
   std::vector<float>   *slimmedJetCHF;
   std::vector<float>   *slimmedJetNHF;
   std::vector<float>   *slimmedJetCEF;
   std::vector<float>   *slimmedJetNEF;
   std::vector<int>     *slimmedJetNCH;
   std::vector<int>     *slimmedJetNNP;
   std::vector<float>   *slimmedJetMUF;
   std::vector<float>   *slimmedJetHFHAE;
   std::vector<float>   *slimmedJetHFEME;
   std::vector<int>     *slimmedJetNConstituents;
   std::vector<float>   *slimmedJetVtxPt;
   std::vector<float>   *slimmedJetVtxMass;
   std::vector<float>   *slimmedJetVtxNtrks;
   std::vector<float>   *slimmedJetVtx3DVal;
   std::vector<float>   *slimmedJetVtx3DSig;
   std::vector<float>   *slimmedJetCSV2BJetTags;
   std::vector<float>   *slimmedJetJetProbabilityBJetTags;
   std::vector<float>   *slimmedJetpfCombinedMVAV2BJetTags;
   std::vector<int>     *slimmedJetPartonID;
   std::vector<int>     *slimmedJetHadFlvr;
   std::vector<bool>    *slimmedJetPFLooseId;
   std::vector<int>     *slimmedJetID;
   std::vector<float>   *slimmedJetPUID;
   std::vector<int>     *slimmedJetPUFullID;
   std::vector<float>   *slimmedJetJECUnc;
   std::vector<float>   *slimmedJetP4Smear;
   std::vector<float>   *slimmedJetP4SmearUp;
   std::vector<float>   *slimmedJetP4SmearDo;
   std::vector<unsigned int> *slimmedJetFiredTrgs;
   std::vector<float>   *slimmedJetAlphaD;
   std::vector<float>   *slimmedJetAlphaMaxD;
   std::vector<float>   *slimmedJetSumIP;
   std::vector<float>   *slimmedJetSumIPSig;
   std::vector<float>   *slimmedJetMedianLog10IPSig;
   std::vector<float>   *slimmedJetTrackAngle;
   std::vector<float>   *slimmedJetLogTrackAngle;
   std::vector<float>   *slimmedJetMedianLog10TrackAngle;
   std::vector<float>   *slimmedJetTotalTrackAngle;
   std::vector<float>   *slimmedJetDauVertex_x;
   std::vector<float>   *slimmedJetDauVertex_y;
   std::vector<float>   *slimmedJetDauVertex_z;
   std::vector<float>   *slimmedJetDauVertex_r;
   std::vector<float>   *slimmedJetAlphaMax_PV3onPV2;
   std::vector<float>   *slimmedJetAlphaMax_PV3onChg;
   std::vector<float>   *slimmedJetAlphaMax_PV3onAll;
   std::vector<float>   *slimmedJetAlphaMax_PV2onChg;
   std::vector<float>   *slimmedJetAlphaMax_PV2onAll;
   std::vector<float>   *slimmedJetAlpha2Max_PV3onPV2;
   std::vector<float>   *slimmedJetAlpha2Max_PV3onChg;
   std::vector<float>   *slimmedJetAlpha2Max_PV3onAll;
   std::vector<float>   *slimmedJetAlpha2Max_PV2onChg;
   std::vector<float>   *slimmedJetAlpha2Max_PV2onAll;
   std::vector<std::vector<float> > *slimmedJetTrackPt;
   std::vector<std::vector<float> > *slimmedJetTrackEta;
   std::vector<std::vector<float> > *slimmedJetTrackPhi;
   std::vector<std::vector<int> > *slimmedJetTrackPDGID;
   std::vector<std::vector<int> > *slimmedJetTrackMomPDGID;
   std::vector<float>   *slimmedJetGenJetEn;
   std::vector<float>   *slimmedJetGenJetPt;
   std::vector<float>   *slimmedJetGenJetEta;
   std::vector<float>   *slimmedJetGenJetPhi;
   std::vector<int>     *slimmedJetGenPartonID;
   std::vector<float>   *slimmedJetGenEn;
   std::vector<float>   *slimmedJetGenPt;
   std::vector<float>   *slimmedJetGenEta;
   std::vector<float>   *slimmedJetGenPhi;
   std::vector<int>     *slimmedJetGenPartonMomID;
   Float_t         genMET;
   Float_t         genMETPhi;
   Int_t           metFilters;
   Float_t         pfMET;
   Float_t         pfMETPhi;
   Float_t         pfMETsumEt;
   Float_t         pfMETmEtSig;
   Float_t         pfMETSig;
   Float_t         pfMET_T1JERUp;
   Float_t         pfMET_T1JERDo;
   Float_t         pfMET_T1JESUp;
   Float_t         pfMET_T1JESDo;
   Float_t         pfMET_T1UESUp;
   Float_t         pfMET_T1UESDo;
   Float_t         pfMETPhi_T1JESUp;
   Float_t         pfMETPhi_T1JESDo;
   Float_t         pfMETPhi_T1UESUp;
   Float_t         pfMETPhi_T1UESDo;

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
   //TBranch        *b_llpId;   //!
   //TBranch        *b_llpStatus;   //!
   //TBranch        *b_llpPt;   //!
   //TBranch        *b_llpEta;   //!
   //TBranch        *b_llpPhi;   //!
   //TBranch        *b_llpMass;   //!
   //TBranch        *b_llpDaughterId;   //!
   //TBranch        *b_llpDaughterStatus;   //!
   //TBranch        *b_llpDaughterPt;   //!
   //TBranch        *b_llpDaughterEta;   //!
   //TBranch        *b_llpDaughterPhi;   //!
   //TBranch        *b_llpDaughterMass;   //!
// #brokenphotons
   TBranch        *b_nPho;   //!
   TBranch        *b_phoPt;   //!
   TBranch        *b_phoEn;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoSCEn;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoIDbit;   //!
//   TBranch        *b_phoIDMVA;   //!
//   TBranch        *b_phoObjPFChIso;   //!
//   TBranch        *b_phoObjPFPhoIso;   //!
//   TBranch        *b_phoObjPFNeuIso;   //!
//   TBranch        *b_phoObjPFChWorstIso;   //!
//   TBranch        *b_phoMapPFChIso;   //!
//   TBranch        *b_phoMapPFPhoIso;   //!
//   TBranch        *b_phoMapPFNeuIso;   //!
//   TBranch        *b_phoMapPFChWorstIso;   //!
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
   TBranch        *b_nSlimmedJets;   //!
   TBranch        *b_slimmedJetPt;   //!
   TBranch        *b_slimmedJetEn;   //!
   TBranch        *b_slimmedJetEta;   //!
   TBranch        *b_slimmedJetPhi;   //!
   TBranch        *b_slimmedJetRawPt;   //!
   TBranch        *b_slimmedJetRawEn;   //!
   TBranch        *b_slimmedJetMt;   //!
   TBranch        *b_slimmedJetArea;   //!
   TBranch        *b_slimmedJetLeadTrackPID;   //!
   TBranch        *b_slimmedJetLeadTrackPt;   //!
   TBranch        *b_slimmedJetLeadTrackEta;   //!
   TBranch        *b_slimmedJetLeadTrackPhi;   //!
   TBranch        *b_slimmedJetLepTrackPID;   //!
   TBranch        *b_slimmedJetLepTrackPt;   //!
   TBranch        *b_slimmedJetLepTrackEta;   //!
   TBranch        *b_slimmedJetLepTrackPhi;   //!
   TBranch        *b_slimmedJetCHF;   //!
   TBranch        *b_slimmedJetNHF;   //!
   TBranch        *b_slimmedJetCEF;   //!
   TBranch        *b_slimmedJetNEF;   //!
   TBranch        *b_slimmedJetNCH;   //!
   TBranch        *b_slimmedJetNNP;   //!
   TBranch        *b_slimmedJetMUF;   //!
   TBranch        *b_slimmedJetHFHAE;   //!
   TBranch        *b_slimmedJetHFEME;   //!
   TBranch        *b_slimmedJetNConstituents;   //!
   TBranch        *b_slimmedJetVtxPt;   //!
   TBranch        *b_slimmedJetVtxMass;   //!
   TBranch        *b_slimmedJetVtxNtrks;   //!
   TBranch        *b_slimmedJetVtx3DVal;   //!
   TBranch        *b_slimmedJetVtx3DSig;   //!
   TBranch        *b_slimmedJetCSV2BJetTags;   //!
   TBranch        *b_slimmedJetJetProbabilityBJetTags;   //!
   TBranch        *b_slimmedJetpfCombinedMVAV2BJetTags;   //!
   TBranch        *b_slimmedJetPartonID;   //!
   TBranch        *b_slimmedJetHadFlvr;   //!
   TBranch        *b_slimmedJetPFLooseId;   //!
   TBranch        *b_slimmedJetID;   //!
   TBranch        *b_slimmedJetPUID;   //!
   TBranch        *b_slimmedJetPUFullID;   //!
   TBranch        *b_slimmedJetJECUnc;   //!
   TBranch        *b_slimmedJetP4Smear;   //!
   TBranch        *b_slimmedJetP4SmearUp;   //!
   TBranch        *b_slimmedJetP4SmearDo;   //!
   TBranch        *b_slimmedJetFiredTrgs;   //!
   TBranch        *b_slimmedJetAlphaD;   //!
   TBranch        *b_slimmedJetAlphaMaxD;   //!
   TBranch        *b_slimmedJetSumIP;   //!
   TBranch        *b_slimmedJetSumIPSig;   //!
   TBranch        *b_slimmedJetMedianLog10IPSig;   //!
   TBranch        *b_slimmedJetTrackAngle;   //!
   TBranch        *b_slimmedJetLogTrackAngle;   //!
   TBranch        *b_slimmedJetMedianLog10TrackAngle;   //!
   TBranch        *b_slimmedJetTotalTrackAngle;   //!
   TBranch        *b_slimmedJetDauVertex_x;   //!
   TBranch        *b_slimmedJetDauVertex_y;   //!
   TBranch        *b_slimmedJetDauVertex_z;   //!
   TBranch        *b_slimmedJetDauVertex_r;   //!
   TBranch        *b_slimmedJetAlphaMax_PV3onPV2;   //!
   TBranch        *b_slimmedJetAlphaMax_PV3onChg;   //!
   TBranch        *b_slimmedJetAlphaMax_PV3onAll;   //!
   TBranch        *b_slimmedJetAlphaMax_PV2onChg;   //!
   TBranch        *b_slimmedJetAlphaMax_PV2onAll;   //!
   TBranch        *b_slimmedJetAlpha2Max_PV3onPV2;   //!
   TBranch        *b_slimmedJetAlpha2Max_PV3onChg;   //!
   TBranch        *b_slimmedJetAlpha2Max_PV3onAll;   //!
   TBranch        *b_slimmedJetAlpha2Max_PV2onChg;   //!
   TBranch        *b_slimmedJetAlpha2Max_PV2onAll;   //!
   TBranch        *b_slimmedJetTrackPt;   //!
   TBranch        *b_slimmedJetTrackEta;   //!
   TBranch        *b_slimmedJetTrackPhi;   //!
   TBranch        *b_slimmedJetTrackPDGID;   //!
   TBranch        *b_slimmedJetTrackMomPDGID;   //!
   TBranch        *b_slimmedJetGenJetEn;   //!
   TBranch        *b_slimmedJetGenJetPt;   //!
   TBranch        *b_slimmedJetGenJetEta;   //!
   TBranch        *b_slimmedJetGenJetPhi;   //!
   TBranch        *b_slimmedJetGenPartonID;   //!
   TBranch        *b_slimmedJetGenEn;   //!
   TBranch        *b_slimmedJetGenPt;   //!
   TBranch        *b_slimmedJetGenEta;   //!
   TBranch        *b_slimmedJetGenPhi;   //!
   TBranch        *b_slimmedJetGenPartonMomID;   //!
   TBranch        *b_genMET;   //!
   TBranch        *b_genMETPhi;   //!
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

   //analyzer_base(TTree *tree=0);
   analyzer_base();
   virtual ~analyzer_base();
   virtual void     Init(TTree *tree, Bool_t isitMC, Bool_t domakelog);
   virtual Long64_t LoadTree(Long64_t entry);
   Double_t         makeEventWeight(Double_t crossSec, Double_t lumi,
                                    Double_t nrEvents);
   
};

#endif
