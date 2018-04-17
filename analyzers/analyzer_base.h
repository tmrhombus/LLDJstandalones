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
   //Int_t           nVtx;
   //Int_t           nGoodVtx;
   //Int_t           nTrksPV;
   //Bool_t          isPVGood;
   //Float_t         vtx;
   //Float_t         vty;
   //Float_t         vtz;
   //Float_t         rho;
   //Float_t         rhoCentral;
   //Int_t           nTruePU;
   ULong64_t       AOD_HLT_Ele23Loose;
   ULong64_t       AOD_HLT_Ele27Tight;
   ULong64_t       AOD_HLT_Ele17Ele12;
   ULong64_t       AOD_HLT_Ele23Ele12;
   ULong64_t       AOD_HLT_IsoMu22;
   ULong64_t       AOD_HLT_IsoTkMu22;
   ULong64_t       AOD_HLT_Mu17Mu8;
   ULong64_t       AOD_HLT_Mu17TkMu8;
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
   Int_t           nAODPho;
   std::vector<float>   *AOD_phoPt;
   std::vector<float>   *AOD_phoEn;
   std::vector<float>   *AOD_phoEta;
   std::vector<float>   *AOD_phoPhi;
   std::vector<float>   *AOD_phoSCEn;
   std::vector<float>   *AOD_phoSCEta;
   std::vector<float>   *AOD_phoSCPhi;
   std::vector<unsigned short> *AOD_phoIDbit;
   //std::vector<float>   *AOD_phoIDMVA;
   std::vector<float>   *AOD_phoObjPFChIso;
   std::vector<float>   *AOD_phoObjPFPhoIso;
   std::vector<float>   *AOD_phoObjPFNeuIso;
   std::vector<float>   *AOD_phoObjPFChWorstIso;
   std::vector<float>   *AOD_phoMapPFChIso;
   std::vector<float>   *AOD_phoMapPFPhoIso;
   std::vector<float>   *AOD_phoMapPFNeuIso;
   std::vector<float>   *AOD_phoMapPFChWorstIso;
   Int_t           nAODEle;
   std::vector<float>   *AOD_elePt;
   std::vector<float>   *AOD_eleEn;
   std::vector<float>   *AOD_eleEta;
   std::vector<float>   *AOD_elePhi;
   //std::vector<float>   *AOD_eleSCEn;
   //std::vector<float>   *AOD_eleSCEta;
   //std::vector<float>   *AOD_eleSCPhi;
   std::vector<int>     *AOD_eleCharge;
   std::vector<int>     *AOD_eleChargeConsistent;
   std::vector<int>     *AOD_elePassConversionVeto;
   std::vector<unsigned short> *AOD_eleIDbit;
   //std::vector<float>   *AOD_elePFdBetaIsolationRhoEA;
   //std::vector<float>   *AOD_elePFdBetaIsolationCHS;
   //std::vector<float>   *AOD_elePFdBetaIsolationDiff;
   Int_t           nAODMu;
   std::vector<float>   *AOD_muPt;
   std::vector<float>   *AOD_muEn;
   std::vector<float>   *AOD_muEta;
   std::vector<float>   *AOD_muPhi;
   std::vector<int>     *AOD_muCharge;
   std::vector<int>     *AOD_muType;
   //std::vector<unsigned short> *AOD_muIDbit;
   std::vector<bool>    *AOD_muPassLooseID;
   //std::vector<bool>    *AOD_muPassHipID;
   std::vector<bool>    *AOD_muPassTightID;
   //std::vector<int>     *AOD_muNumberOfMissingInnerHits;
   //std::vector<int>     *AOD_muNumberOfMissingMiddleHits;
   //std::vector<int>     *AOD_muNumberOfMissingOuterHits;
   //std::vector<int>     *AOD_muNumberOfMatchedStations;
   //std::vector<int>     *AOD_muNumberOfValidPixelHits;
   //std::vector<int>     *AOD_muTrackerLayersWithMeasurement;
   std::vector<int>     *AOD_muIsGlobalMuon;
   std::vector<int>     *AOD_muIsPFMuon;
   std::vector<float>   *AOD_muPFdBetaIsolation;
   std::vector<float>   *AOD_muDxy;
   std::vector<float>   *AOD_muDxyErr;
   Int_t           AODnCaloJet;
   std::vector<float>   *AODCaloJetPt;
   std::vector<float>   *AODCaloJetEta;
   std::vector<float>   *AODCaloJetPhi;
   std::vector<float>   *AODCaloJetAlphaMax;
   std::vector<float>   *AODCaloJetAlphaMax2;
   std::vector<float>   *AODCaloJetAlphaMaxPrime;
   std::vector<float>   *AODCaloJetAlphaMaxPrime2;
   std::vector<float>   *AODCaloJetBeta;
   std::vector<float>   *AODCaloJetBeta2;
   std::vector<float>   *AODCaloJetSumIP;
   std::vector<float>   *AODCaloJetSumIPSig;
   std::vector<float>   *AODCaloJetMedianIP;
   std::vector<float>   *AODCaloJetMedianLog10IPSig;
   std::vector<float>   *AODCaloJetTrackAngle;
   std::vector<float>   *AODCaloJetLogTrackAngle;
   std::vector<float>   *AODCaloJetMedianLog10TrackAngle;
   std::vector<float>   *AODCaloJetTotalTrackAngle;
   std::vector<float>   *AODCaloJetAvfVx;
   std::vector<float>   *AODCaloJetAvfVy;
   std::vector<float>   *AODCaloJetAvfVz;
   std::vector<float>   *AODCaloJetAvfVertexTotalChiSquared;
   std::vector<float>   *AODCaloJetAvfVertexDegreesOfFreedom;
   std::vector<float>   *AODCaloJetAvfVertexChi2NDoF;
   std::vector<float>   *AODCaloJetAvfVertexDistanceToBeam;
   std::vector<float>   *AODCaloJetAvfVertexTransverseError;
   std::vector<float>   *AODCaloJetAvfVertexTransverseSig;
   std::vector<float>   *AODCaloJetAvfVertexDeltaEta;
   std::vector<float>   *AODCaloJetAvfVertexDeltaPhi;
   std::vector<float>   *AODCaloJetAvfVertexRecoilPt;
   std::vector<float>   *AODCaloJetAvfVertexTrackMass;
   std::vector<float>   *AODCaloJetAvfVertexTrackEnergy;
   std::vector<float>   *AODCaloJetAvfBeamSpotDeltaPhi;
   std::vector<float>   *AODCaloJetAvfBeamSpotRecoilPt;
   std::vector<float>   *AODCaloJetAvfBeamSpotMedianDeltaPhi;
   std::vector<float>   *AODCaloJetAvfBeamSpotLog10MedianDeltaPhi;
   std::vector<int>     *AODCaloJetNCleanMatchedTracks;
   std::vector<int>     *AODCaloJetSumHitsInFrontOfVert;
   std::vector<int>     *AODCaloJetSumMissHitsAfterVert;
   std::vector<int>     *AODCaloJetHitsInFrontOfVertPerTrack;
   std::vector<int>     *AODCaloJetMissHitsAfterVertPerTrack;
   std::vector<float>   *AODCaloJetAvfDistToPV;
   std::vector<float>   *AODCaloJetAvfVertexDeltaZtoPV;
   std::vector<float>   *AODCaloJetAvfVertexDeltaZtoPV2;
   Int_t           AODnPFJet;
   std::vector<float>   *AODPFJetPt;
   std::vector<float>   *AODPFJetEta;
   std::vector<float>   *AODPFJetPhi;
   std::vector<float>   *AODPFJetAlphaMax;
   std::vector<float>   *AODPFJetAlphaMax2;
   std::vector<float>   *AODPFJetAlphaMaxPrime;
   std::vector<float>   *AODPFJetAlphaMaxPrime2;
   std::vector<float>   *AODPFJetBeta;
   std::vector<float>   *AODPFJetBeta2;
   std::vector<float>   *AODPFJetSumIP;
   std::vector<float>   *AODPFJetSumIPSig;
   std::vector<float>   *AODPFJetMedianLog10IPSig;
   std::vector<float>   *AODPFJetTrackAngle;
   std::vector<float>   *AODPFJetLogTrackAngle;
   std::vector<float>   *AODPFJetMedianLog10TrackAngle;
   std::vector<float>   *AODPFJetTotalTrackAngle;
   Int_t           AODnPFchsJet;
   std::vector<float>   *AODPFchsJetPt;
   std::vector<float>   *AODPFchsJetEta;
   std::vector<float>   *AODPFchsJetPhi;
   std::vector<float>   *AODPFchsJetAlphaMax;
   std::vector<float>   *AODPFchsJetAlphaMax2;
   std::vector<float>   *AODPFchsJetAlphaMaxPrime;
   std::vector<float>   *AODPFchsJetAlphaMaxPrime2;
   std::vector<float>   *AODPFchsJetBeta;
   std::vector<float>   *AODPFchsJetBeta2;
   std::vector<float>   *AODPFchsJetSumIP;
   std::vector<float>   *AODPFchsJetSumIPSig;
   std::vector<float>   *AODPFchsJetMedianLog10IPSig;
   std::vector<float>   *AODPFchsJetTrackAngle;
   std::vector<float>   *AODPFchsJetLogTrackAngle;
   std::vector<float>   *AODPFchsJetMedianLog10TrackAngle;
   std::vector<float>   *AODPFchsJetTotalTrackAngle;
   //Float_t         genMET;
   //Float_t         genMETPhi;
   //Int_t           metFilters;
   //Float_t         pfMET;
   Float_t         AOD_pfMET_phi;
   Float_t         AOD_pfMET_pt;
   //Float_t         pfMETsumEt;
   //Float_t         pfMETmEtSig;
   //Float_t         pfMETSig;
   //Float_t         pfMET_T1JERUp;
   //Float_t         pfMET_T1JERDo;
   //Float_t         pfMET_T1JESUp;
   //Float_t         pfMET_T1JESDo;
   //Float_t         pfMET_T1UESUp;
   //Float_t         pfMET_T1UESDo;
   //Float_t         pfMETPhi_T1JESUp;
   //Float_t         pfMETPhi_T1JESDo;
   //Float_t         pfMETPhi_T1UESUp;
   //Float_t         pfMETPhi_T1UESDo;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   //TBranch        *b_nVtx;   //!
   //TBranch        *b_nGoodVtx;   //!
   //TBranch        *b_nTrksPV;   //!
   //TBranch        *b_isPVGood;   //!
   //TBranch        *b_vtx;   //!
   //TBranch        *b_vty;   //!
   //TBranch        *b_vtz;   //!
   //TBranch        *b_rho;   //!
   //TBranch        *b_rhoCentral;   //!
   //TBranch        *b_nTruePU;   //!
   TBranch        *b_AOD_HLT_Ele23Loose;   //!
   TBranch        *b_AOD_HLT_Ele27Tight;   //!
   TBranch        *b_AOD_HLT_Ele17Ele12;   //!
   TBranch        *b_AOD_HLT_Ele23Ele12;   //!
   TBranch        *b_AOD_HLT_IsoMu22;   //!
   TBranch        *b_AOD_HLT_IsoTkMu22;   //!
   TBranch        *b_AOD_HLT_Mu17Mu8;   //!
   TBranch        *b_AOD_HLT_Mu17TkMu8;   //!
   TBranch        *b_llpId;   //!
   TBranch        *b_llpStatus;   //!
   TBranch        *b_llpPt;   //!
   TBranch        *b_llpEta;   //!
   TBranch        *b_llpPhi;   //!
   TBranch        *b_llpMass;   //!
   TBranch        *b_llpDaughterId;   //!
   TBranch        *b_llpDaughterStatus;   //!
   TBranch        *b_llpDaughterPt;   //!
   TBranch        *b_llpDaughterEta;   //!
   TBranch        *b_llpDaughterPhi;   //!
   TBranch        *b_llpDaughterMass;   //!
   TBranch        *b_nAODPho;   //!
   TBranch        *b_AOD_phoPt;   //!
   TBranch        *b_AOD_phoEn;   //!
   TBranch        *b_AOD_phoEta;   //!
   TBranch        *b_AOD_phoPhi;   //!
   TBranch        *b_AOD_phoSCEn;   //!
   TBranch        *b_AOD_phoSCEta;   //!
   TBranch        *b_AOD_phoSCPhi;   //!
   TBranch        *b_AOD_phoIDbit;   //!
//   TBranch        *b_AOD_phoIDMVA;   //!
   TBranch        *b_AOD_phoObjPFChIso;   //!
   TBranch        *b_AOD_phoObjPFPhoIso;   //!
   TBranch        *b_AOD_phoObjPFNeuIso;   //!
   TBranch        *b_AOD_phoObjPFChWorstIso;   //!
   TBranch        *b_AOD_phoMapPFChIso;   //!
   TBranch        *b_AOD_phoMapPFPhoIso;   //!
   TBranch        *b_AOD_phoMapPFNeuIso;   //!
   TBranch        *b_AOD_phoMapPFChWorstIso;   //!
   TBranch        *b_nAODEle;   //!
   TBranch        *b_AOD_elePt;   //!
   TBranch        *b_AOD_eleEn;   //!
   TBranch        *b_AOD_eleEta;   //!
   TBranch        *b_AOD_elePhi;   //!
   //TBranch        *b_AOD_eleSCEn;   //!
   //TBranch        *b_AOD_eleSCEta;   //!
   //TBranch        *b_AOD_eleSCPhi;   //!
   TBranch        *b_AOD_eleCharge;   //!
   TBranch        *b_AOD_eleChargeConsistent;   //!
   TBranch        *b_AOD_elePassConversionVeto;   //!
   TBranch        *b_AOD_eleIDbit;   //!
   //TBranch        *b_AOD_elePFdBetaIsolationRhoEA;   //!
   //TBranch        *b_AOD_elePFdBetaIsolationCHS;   //!
   TBranch        *b_AOD_elePFdBetaIsolationDiff;   //!
   TBranch        *b_nAODMu;   //!
   TBranch        *b_AOD_muPt;   //!
   TBranch        *b_AOD_muEn;   //!
   TBranch        *b_AOD_muEta;   //!
   TBranch        *b_AOD_muPhi;   //!
   TBranch        *b_AOD_muCharge;   //!
   TBranch        *b_AOD_muType;   //!
   //TBranch        *b_AOD_muIDbit;   //!
   TBranch        *b_AOD_muPassLooseID;   //!
   //TBranch        *b_AOD_muPassHipID;   //!
   TBranch        *b_AOD_muPassTightID;   //!
   //TBranch        *b_AOD_muNumberOfMissingInnerHits;   //!
   //TBranch        *b_AOD_muNumberOfMissingMiddleHits;   //!
   //TBranch        *b_AOD_muNumberOfMissingOuterHits;   //!
   //TBranch        *b_AOD_muNumberOfMatchedStations;   //!
   //TBranch        *b_AOD_muNumberOfValidPixelHits;   //!
   //TBranch        *b_AOD_muTrackerLayersWithMeasurement;   //!
   TBranch        *b_AOD_muIsGlobalMuon;   //!
   TBranch        *b_AOD_muIsPFMuon;   //!
   TBranch        *b_AOD_muPFdBetaIsolation;   //!
   TBranch        *b_AOD_muDxy;   //!
   TBranch        *b_AOD_muDxyErr;   //!
   TBranch        *b_AODnCaloJet;   //!
   TBranch        *b_AODCaloJetPt;   //!
   TBranch        *b_AODCaloJetEta;   //!
   TBranch        *b_AODCaloJetPhi;   //!
   TBranch        *b_AODCaloJetAlphaMax;   //!
   TBranch        *b_AODCaloJetAlphaMax2;   //!
   TBranch        *b_AODCaloJetAlphaMaxPrime;   //!
   TBranch        *b_AODCaloJetAlphaMaxPrime2;   //!
   TBranch        *b_AODCaloJetBeta;   //!
   TBranch        *b_AODCaloJetBeta2;   //!
   TBranch        *b_AODCaloJetSumIP;   //!
   TBranch        *b_AODCaloJetSumIPSig;   //!
   TBranch        *b_AODCaloJetMedianIP;   //!
   TBranch        *b_AODCaloJetMedianLog10IPSig;   //!
   TBranch        *b_AODCaloJetTrackAngle;   //!
   TBranch        *b_AODCaloJetLogTrackAngle;   //!
   TBranch        *b_AODCaloJetMedianLog10TrackAngle;   //!
   TBranch        *b_AODCaloJetTotalTrackAngle;   //!
   TBranch        *b_AODCaloJetAvfVx;   //!
   TBranch        *b_AODCaloJetAvfVy;   //!
   TBranch        *b_AODCaloJetAvfVz;   //!
   TBranch        *b_AODCaloJetAvfVertexTotalChiSquared;   //!
   TBranch        *b_AODCaloJetAvfVertexDegreesOfFreedom;   //!
   TBranch        *b_AODCaloJetAvfVertexChi2NDoF;   //!
   TBranch        *b_AODCaloJetAvfVertexDistanceToBeam;   //!
   TBranch        *b_AODCaloJetAvfVertexTransverseError;   //!
   TBranch        *b_AODCaloJetAvfVertexTransverseSig;   //!
   TBranch        *b_AODCaloJetAvfVertexDeltaEta;   //!
   TBranch        *b_AODCaloJetAvfVertexDeltaPhi;   //!
   TBranch        *b_AODCaloJetAvfVertexRecoilPt;   //!
   TBranch        *b_AODCaloJetAvfVertexTrackMass;   //!
   TBranch        *b_AODCaloJetAvfVertexTrackEnergy;   //!
   TBranch        *b_AODCaloJetAvfBeamSpotDeltaPhi;   //!
   TBranch        *b_AODCaloJetAvfBeamSpotRecoilPt;   //!
   TBranch        *b_AODCaloJetAvfBeamSpotMedianDeltaPhi;   //!
   TBranch        *b_AODCaloJetAvfBeamSpotLog10MedianDeltaPhi;   //!
   TBranch        *b_AODCaloJetNCleanMatchedTracks;   //!
   TBranch        *b_AODCaloJetSumHitsInFrontOfVert;   //!
   TBranch        *b_AODCaloJetSumMissHitsAfterVert;   //!
   TBranch        *b_AODCaloJetHitsInFrontOfVertPerTrack;   //!
   TBranch        *b_AODCaloJetMissHitsAfterVertPerTrack;   //!
   TBranch        *b_AODCaloJetAvfDistToPV;   //!
   TBranch        *b_AODCaloJetAvfVertexDeltaZtoPV;   //!
   TBranch        *b_AODCaloJetAvfVertexDeltaZtoPV2;   //!
   TBranch        *b_AODnPFJet;   //!
   TBranch        *b_AODPFJetPt;   //!
   TBranch        *b_AODPFJetEta;   //!
   TBranch        *b_AODPFJetPhi;   //!
   TBranch        *b_AODPFJetAlphaMax;   //!
   TBranch        *b_AODPFJetAlphaMax2;   //!
   TBranch        *b_AODPFJetAlphaMaxPrime;   //!
   TBranch        *b_AODPFJetAlphaMaxPrime2;   //!
   TBranch        *b_AODPFJetBeta;   //!
   TBranch        *b_AODPFJetBeta2;   //!
   TBranch        *b_AODPFJetSumIP;   //!
   TBranch        *b_AODPFJetSumIPSig;   //!
   TBranch        *b_AODPFJetMedianLog10IPSig;   //!
   TBranch        *b_AODPFJetTrackAngle;   //!
   TBranch        *b_AODPFJetLogTrackAngle;   //!
   TBranch        *b_AODPFJetMedianLog10TrackAngle;   //!
   TBranch        *b_AODPFJetTotalTrackAngle;   //!
   TBranch        *b_AODnPFchsJet;   //!
   TBranch        *b_AODPFchsJetPt;   //!
   TBranch        *b_AODPFchsJetEta;   //!
   TBranch        *b_AODPFchsJetPhi;   //!
   TBranch        *b_AODPFchsJetAlphaMax;   //!
   TBranch        *b_AODPFchsJetAlphaMax2;   //!
   TBranch        *b_AODPFchsJetAlphaMaxPrime;   //!
   TBranch        *b_AODPFchsJetAlphaMaxPrime2;   //!
   TBranch        *b_AODPFchsJetBeta;   //!
   TBranch        *b_AODPFchsJetBeta2;   //!
   TBranch        *b_AODPFchsJetSumIP;   //!
   TBranch        *b_AODPFchsJetSumIPSig;   //!
   TBranch        *b_AODPFchsJetMedianLog10IPSig;   //!
   TBranch        *b_AODPFchsJetTrackAngle;   //!
   TBranch        *b_AODPFchsJetLogTrackAngle;   //!
   TBranch        *b_AODPFchsJetMedianLog10TrackAngle;   //!
   TBranch        *b_AODPFchsJetTotalTrackAngle;   //!
   //TBranch        *b_genMET;   //!
   //TBranch        *b_genMETPhi;   //!
   //TBranch        *b_metFilters;   //!
   //TBranch        *b_pfMET;   //!
   TBranch        *b_AOD_pfMET_phi;   //!
   TBranch        *b_AOD_pfMET_pt;   //!
   //TBranch        *b_pfMETsumEt;   //!
   //TBranch        *b_pfMETmEtSig;   //!
   //TBranch        *b_pfMETSig;   //!
   //TBranch        *b_pfMET_T1JERUp;   //!
   //TBranch        *b_pfMET_T1JERDo;   //!
   //TBranch        *b_pfMET_T1JESUp;   //!
   //TBranch        *b_pfMET_T1JESDo;   //!
   //TBranch        *b_pfMET_T1UESUp;   //!
   //TBranch        *b_pfMET_T1UESDo;   //!
   //TBranch        *b_pfMETPhi_T1JESUp;   //!
   //TBranch        *b_pfMETPhi_T1JESDo;   //!
   //TBranch        *b_pfMETPhi_T1UESUp;   //!
   //TBranch        *b_pfMETPhi_T1UESDo;   //!

   //analyzer_base(TTree *tree=0);
   analyzer_base();
   virtual ~analyzer_base();
   virtual void     Init(TTree *tree, Bool_t isitMC, Bool_t domakelog);
   virtual Long64_t LoadTree(Long64_t entry);
   Double_t         makeEventWeight(Double_t crossSec, Double_t lumi,
                                    Double_t nrEvents);
   
};

#endif
