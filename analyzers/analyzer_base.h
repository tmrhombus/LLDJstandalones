#ifndef analyzer_base_h
#define analyzer_base_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>

#include "vector"

class analyzer_base {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // global variables
   Bool_t makelog;
   FILE * logfile;
   Double_t event_weight;

   // Declaration of leaf types
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // MC
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
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
   ULong64_t       HLTEleMuX;
   ULong64_t       HLTPho;
   ULong64_t       HLTJet;
   ULong64_t       HLTEleMuXIsPrescaled;
   ULong64_t       HLTPhoIsPrescaled;
   ULong64_t       HLTJetIsPrescaled;
   std::vector<int>     *phoPrescale;
   std::vector<float>   *pdf;
   Float_t         pthat;
   Float_t         processID;
   Float_t         genWeight;
   Float_t         genHT;
   TString         *EventTag;
   Int_t           nPUInfo;
   std::vector<int>     *nPU;
   std::vector<int>     *puBX;
   std::vector<float>   *puTrue;
   Int_t           nMC;
   std::vector<int>     *mcPID;
   std::vector<float>   *mcVtx;
   std::vector<float>   *mcVty;
   std::vector<float>   *mcVtz;
   std::vector<float>   *mcPt;
   std::vector<float>   *mcMass;
   std::vector<float>   *mcEta;
   std::vector<float>   *mcPhi;
   std::vector<float>   *mcE;
   std::vector<float>   *mcEt;
   std::vector<int>     *mcGMomPID;
   std::vector<int>     *mcMomPID;
   std::vector<float>   *mcMomPt;
   std::vector<float>   *mcMomMass;
   std::vector<float>   *mcMomEta;
   std::vector<float>   *mcMomPhi;
   std::vector<unsigned short> *mcStatusFlag;
   std::vector<int>     *mcParentage;
   std::vector<int>     *mcStatus;
   std::vector<float>   *mcCalIsoDR03;
   std::vector<float>   *mcTrkIsoDR03;
   std::vector<float>   *mcCalIsoDR04;
   std::vector<float>   *mcTrkIsoDR04;
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
   Int_t           nPho;
   std::vector<float>   *phoE;
   std::vector<float>   *phoEt;
   std::vector<float>   *phoEta;
   std::vector<float>   *phoPhi;
   std::vector<float>   *phoCalibE;
   std::vector<float>   *phoCalibEt;
   std::vector<float>   *phoSCE;
   std::vector<float>   *phoSCRawE;
   std::vector<float>   *phoESEn;
   std::vector<float>   *phoESEnP1;
   std::vector<float>   *phoESEnP2;
   std::vector<float>   *phoSCEta;
   std::vector<float>   *phoSCPhi;
   std::vector<float>   *phoSCEtaWidth;
   std::vector<float>   *phoSCPhiWidth;
   std::vector<float>   *phoSCBrem;
   std::vector<int>     *phohasPixelSeed;
   std::vector<int>     *phoEleVeto;
   std::vector<float>   *phoR9;
   std::vector<float>   *phoHoverE;
   std::vector<float>   *phoE1x3;
   std::vector<float>   *phoE1x5;
   std::vector<float>   *phoE2x2;
   std::vector<float>   *phoE2x5Max;
   std::vector<float>   *phoE5x5;
   std::vector<float>   *phoESEffSigmaRR;
   std::vector<float>   *phoSigmaIEtaIEtaFull5x5;
   std::vector<float>   *phoSigmaIEtaIPhiFull5x5;
   std::vector<float>   *phoSigmaIPhiIPhiFull5x5;
   std::vector<float>   *phoE1x3Full5x5;
   std::vector<float>   *phoE1x5Full5x5;
   std::vector<float>   *phoE2x2Full5x5;
   std::vector<float>   *phoE2x5MaxFull5x5;
   std::vector<float>   *phoE5x5Full5x5;
   std::vector<float>   *phoR9Full5x5;
   std::vector<float>   *phoPFChIso;
   std::vector<float>   *phoPFPhoIso;
   std::vector<float>   *phoPFNeuIso;
   std::vector<float>   *phoPFChWorstIso;
   std::vector<float>   *phoIDMVA;
   std::vector<unsigned int> *phoFiredSingleTrgs;
   std::vector<unsigned int> *phoFiredDoubleTrgs;
   std::vector<unsigned int> *phoFiredL1Trgs;
   std::vector<float>   *phoSeedTime;
   std::vector<float>   *phoSeedEnergy;
   std::vector<unsigned short> *phoxtalBits;
   std::vector<unsigned short> *phoIDbit;
   Int_t           npfPho;
   std::vector<float>   *pfphoEt;
   std::vector<float>   *pfphoEta;
   std::vector<float>   *pfphoPhi;
   Int_t           nEle;
   std::vector<int>     *eleCharge;
   std::vector<int>     *eleChargeConsistent;
   std::vector<float>   *eleEn;
   std::vector<float>   *eleSCEn;
   std::vector<float>   *eleESEn;
   std::vector<float>   *eleESEnP1;
   std::vector<float>   *eleESEnP2;
   std::vector<float>   *eleD0;
   std::vector<float>   *eleDz;
   std::vector<float>   *eleSIP;
   std::vector<float>   *elePt;
   std::vector<float>   *eleEta;
   std::vector<float>   *elePhi;
   std::vector<float>   *eleR9;
   std::vector<float>   *eleCalibPt;
   std::vector<float>   *eleCalibEn;
   std::vector<float>   *eleSCEta;
   std::vector<float>   *eleSCPhi;
   std::vector<float>   *eleSCRawEn;
   std::vector<float>   *eleSCEtaWidth;
   std::vector<float>   *eleSCPhiWidth;
   std::vector<float>   *eleHoverE;
   std::vector<float>   *eleEoverP;
   std::vector<float>   *eleEoverPout;
   std::vector<float>   *eleEoverPInv;
   std::vector<float>   *eleBrem;
   std::vector<float>   *eledEtaAtVtx;
   std::vector<float>   *eledPhiAtVtx;
   std::vector<float>   *eledEtaAtCalo;
   std::vector<float>   *eleSigmaIEtaIEtaFull5x5;
   std::vector<float>   *eleSigmaIPhiIPhiFull5x5;
   std::vector<int>     *eleConvVeto;
   std::vector<int>     *eleMissHits;
   std::vector<float>   *eleESEffSigmaRR;
   std::vector<float>   *elePFChIso;
   std::vector<float>   *elePFPhoIso;
   std::vector<float>   *elePFNeuIso;
   std::vector<float>   *elePFPUIso;
   std::vector<float>   *elePFClusEcalIso;
   std::vector<float>   *elePFClusHcalIso;
   std::vector<float>   *elePFMiniIso;
   std::vector<float>   *eleIDMVA;
   std::vector<float>   *eleIDMVAHZZ;
   std::vector<float>   *eledEtaseedAtVtx;
   std::vector<float>   *eleE1x5;
   std::vector<float>   *eleE2x5;
   std::vector<float>   *eleE5x5;
   std::vector<float>   *eleE1x5Full5x5;
   std::vector<float>   *eleE2x5Full5x5;
   std::vector<float>   *eleE5x5Full5x5;
   std::vector<float>   *eleR9Full5x5;
   std::vector<int>     *eleEcalDrivenSeed;
   std::vector<float>   *eleDr03EcalRecHitSumEt;
   std::vector<float>   *eleDr03HcalDepth1TowerSumEt;
   std::vector<float>   *eleDr03HcalDepth2TowerSumEt;
   std::vector<float>   *eleDr03HcalTowerSumEt;
   std::vector<float>   *eleDr03TkSumPt;
   std::vector<float>   *elecaloEnergy;
   std::vector<float>   *eleTrkdxy;
   std::vector<float>   *eleKFHits;
   std::vector<float>   *eleKFChi2;
   std::vector<float>   *eleGSFChi2;
   std::vector<std::vector<float> > *eleGSFPt;
   std::vector<std::vector<float> > *eleGSFEta;
   std::vector<std::vector<float> > *eleGSFPhi;
   std::vector<std::vector<float> > *eleGSFCharge;
   std::vector<std::vector<int> > *eleGSFHits;
   std::vector<std::vector<int> > *eleGSFMissHits;
   std::vector<std::vector<int> > *eleGSFNHitsMax;
   std::vector<std::vector<float> > *eleGSFVtxProb;
   std::vector<std::vector<float> > *eleGSFlxyPV;
   std::vector<std::vector<float> > *eleGSFlxyBS;
   std::vector<std::vector<float> > *eleBCEn;
   std::vector<std::vector<float> > *eleBCEta;
   std::vector<std::vector<float> > *eleBCPhi;
   std::vector<std::vector<float> > *eleBCS25;
   std::vector<std::vector<float> > *eleBCS15;
   std::vector<std::vector<float> > *eleBCSieie;
   std::vector<std::vector<float> > *eleBCSieip;
   std::vector<std::vector<float> > *eleBCSipip;
   std::vector<unsigned int> *eleFiredSingleTrgs;
   std::vector<unsigned int> *eleFiredDoubleTrgs;
   std::vector<unsigned int> *eleFiredL1Trgs;
   std::vector<unsigned short> *eleIDbit;
   Int_t           npfHF;
   std::vector<float>   *pfHFEn;
   std::vector<float>   *pfHFECALEn;
   std::vector<float>   *pfHFHCALEn;
   std::vector<float>   *pfHFPt;
   std::vector<float>   *pfHFEta;
   std::vector<float>   *pfHFPhi;
   std::vector<float>   *pfHFIso;
   Int_t           nMu;
   std::vector<float>   *muPt;
   std::vector<float>   *muEn;
   std::vector<float>   *muEta;
   std::vector<float>   *muPhi;
   std::vector<int>     *muCharge;
   std::vector<int>     *muType;
   std::vector<unsigned short> *muIDbit;
   std::vector<float>   *muD0;
   std::vector<float>   *muDz;
   std::vector<float>   *muSIP;
   std::vector<float>   *muChi2NDF;
   std::vector<float>   *muInnerD0;
   std::vector<float>   *muInnerDz;
   std::vector<int>     *muTrkLayers;
   std::vector<int>     *muPixelLayers;
   std::vector<int>     *muPixelHits;
   std::vector<int>     *muMuonHits;
   std::vector<int>     *muStations;
   std::vector<int>     *muMatches;
   std::vector<int>     *muTrkQuality;
   std::vector<float>   *muIsoTrk;
   std::vector<float>   *muPFChIso;
   std::vector<float>   *muPFPhoIso;
   std::vector<float>   *muPFNeuIso;
   std::vector<float>   *muPFPUIso;
   std::vector<float>   *muPFMiniIso;
   std::vector<unsigned int> *muFiredTrgs;
   std::vector<unsigned int> *muFiredL1Trgs;
   std::vector<float>   *muInnervalidFraction;
   std::vector<float>   *musegmentCompatibility;
   std::vector<float>   *muchi2LocalPosition;
   std::vector<float>   *mutrkKink;
   std::vector<float>   *muBestTrkPtError;
   std::vector<float>   *muBestTrkPt;
   Int_t           nJet;
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
   std::vector<float>   *jetCSV2BJetTags;
   std::vector<float>   *jetJetProbabilityBJetTags;
   std::vector<float>   *jetpfCombinedMVAV2BJetTags;
   std::vector<int>     *jetPartonID;
   std::vector<int>     *jetHadFlvr;
   std::vector<float>   *jetGenJetEn;
   std::vector<float>   *jetGenJetPt;
   std::vector<float>   *jetGenJetEta;
   std::vector<float>   *jetGenJetPhi;
   std::vector<int>     *jetGenPartonID;
   std::vector<float>   *jetGenEn;
   std::vector<float>   *jetGenPt;
   std::vector<float>   *jetGenEta;
   std::vector<float>   *jetGenPhi;
   std::vector<int>     *jetGenPartonMomID;
   std::vector<float>   *jetP4Smear;
   std::vector<float>   *jetP4SmearUp;
   std::vector<float>   *jetP4SmearDo;
   std::vector<bool>    *jetPFLooseId;
   std::vector<int>     *jetID;
   std::vector<float>   *jetPUID;
   std::vector<int>     *jetPUFullID;
   std::vector<float>   *jetJECUnc;
   std::vector<unsigned int> *jetFiredTrgs;
   std::vector<float>   *jetCHF;
   std::vector<float>   *jetNHF;
   std::vector<float>   *jetCEF;
   std::vector<float>   *jetNEF;
   std::vector<int>     *jetNCH;
   std::vector<int>     *jetNNP;
   std::vector<float>   *jetMUF;
   std::vector<float>   *jetVtxPt;
   std::vector<float>   *jetVtxMass;
   std::vector<float>   *jetVtxNtrks;
   std::vector<float>   *jetVtx3DVal;
   std::vector<float>   *jetVtx3DSig;
   Int_t           nAK8Jet;
   std::vector<float>   *AK8JetPt;
   std::vector<float>   *AK8JetEn;
   std::vector<float>   *AK8JetRawPt;
   std::vector<float>   *AK8JetRawEn;
   std::vector<float>   *AK8JetEta;
   std::vector<float>   *AK8JetPhi;
   std::vector<float>   *AK8JetMass;
   std::vector<float>   *AK8Jet_tau1;
   std::vector<float>   *AK8Jet_tau2;
   std::vector<float>   *AK8Jet_tau3;
   std::vector<float>   *AK8JetCHF;
   std::vector<float>   *AK8JetNHF;
   std::vector<float>   *AK8JetCEF;
   std::vector<float>   *AK8JetNEF;
   std::vector<int>     *AK8JetNCH;
   std::vector<int>     *AK8JetNNP;
   std::vector<float>   *AK8JetMUF;
   std::vector<int>     *AK8Jetnconstituents;
   std::vector<bool>    *AK8JetPFLooseId;
   std::vector<bool>    *AK8JetPFTightLepVetoId;
   std::vector<float>   *AK8JetSoftDropMass;
   std::vector<float>   *AK8JetSoftDropMassCorr;
   std::vector<float>   *AK8JetPrunedMass;
   std::vector<float>   *AK8JetPrunedMassCorr;
   std::vector<float>   *AK8JetpfBoostedDSVBTag;
   std::vector<float>   *AK8JetDSVnewV4;
   std::vector<float>   *AK8JetCSV;
   std::vector<float>   *AK8JetJECUnc;
   std::vector<float>   *AK8JetL2L3corr;
   std::vector<float>   *AK8puppiPt;
   std::vector<float>   *AK8puppiMass;
   std::vector<float>   *AK8puppiEta;
   std::vector<float>   *AK8puppiPhi;
   std::vector<float>   *AK8puppiTau1;
   std::vector<float>   *AK8puppiTau2;
   std::vector<float>   *AK8puppiTau3;
   std::vector<float>   *AK8puppiSDL2L3corr;
   std::vector<float>   *AK8puppiSDMass;
   std::vector<float>   *AK8puppiSDMassL2L3Corr;
   std::vector<int>     *AK8JetPartonID;
   std::vector<int>     *AK8JetHadFlvr;
   std::vector<int>     *AK8JetGenJetIndex;
   std::vector<float>   *AK8JetGenJetEn;
   std::vector<float>   *AK8JetGenJetPt;
   std::vector<float>   *AK8JetGenJetEta;
   std::vector<float>   *AK8JetGenJetPhi;
   std::vector<int>     *AK8JetGenPartonID;
   std::vector<float>   *AK8JetGenEn;
   std::vector<float>   *AK8JetGenPt;
   std::vector<float>   *AK8JetGenEta;
   std::vector<float>   *AK8JetGenPhi;
   std::vector<int>     *AK8JetGenPartonMomID;
   std::vector<float>   *AK8JetP4Smear;
   std::vector<float>   *AK8JetP4SmearUp;
   std::vector<float>   *AK8JetP4SmearDo;
   std::vector<int>     *nAK8SDSJ;
   std::vector<std::vector<float> > *AK8SDSJPt;
   std::vector<std::vector<float> > *AK8SDSJEta;
   std::vector<std::vector<float> > *AK8SDSJPhi;
   std::vector<std::vector<float> > *AK8SDSJMass;
   std::vector<std::vector<float> > *AK8SDSJE;
   std::vector<std::vector<int> > *AK8SDSJCharge;
   std::vector<std::vector<int> > *AK8SDSJFlavour;
   std::vector<std::vector<float> > *AK8SDSJCSV;
   std::vector<int>     *nAK8puppiSDSJ;
   std::vector<std::vector<float> > *AK8puppiSDSJPt;
   std::vector<std::vector<float> > *AK8puppiSDSJEta;
   std::vector<std::vector<float> > *AK8puppiSDSJPhi;
   std::vector<std::vector<float> > *AK8puppiSDSJMass;
   std::vector<std::vector<float> > *AK8puppiSDSJE;
   std::vector<std::vector<int> > *AK8puppiSDSJCharge;
   std::vector<std::vector<int> > *AK8puppiSDSJFlavour;
   std::vector<std::vector<float> > *AK8puppiSDSJCSV;

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
   TBranch        *b_HLTEleMuX;   //!
   TBranch        *b_HLTPho;   //!
   TBranch        *b_HLTJet;   //!
   TBranch        *b_HLTEleMuXIsPrescaled;   //!
   TBranch        *b_HLTPhoIsPrescaled;   //!
   TBranch        *b_HLTJetIsPrescaled;   //!
   TBranch        *b_phoPrescale;   //!
   TBranch        *b_pdf;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_processID;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_genHT;   //!
   TBranch        *b_EventTag;   //!
   TBranch        *b_nPUInfo;   //!
   TBranch        *b_nPU;   //!
   TBranch        *b_puBX;   //!
   TBranch        *b_puTrue;   //!
   TBranch        *b_nMC;   //!
   TBranch        *b_mcPID;   //!
   TBranch        *b_mcVtx;   //!
   TBranch        *b_mcVty;   //!
   TBranch        *b_mcVtz;   //!
   TBranch        *b_mcPt;   //!
   TBranch        *b_mcMass;   //!
   TBranch        *b_mcEta;   //!
   TBranch        *b_mcPhi;   //!
   TBranch        *b_mcE;   //!
   TBranch        *b_mcEt;   //!
   TBranch        *b_mcGMomPID;   //!
   TBranch        *b_mcMomPID;   //!
   TBranch        *b_mcMomPt;   //!
   TBranch        *b_mcMomMass;   //!
   TBranch        *b_mcMomEta;   //!
   TBranch        *b_mcMomPhi;   //!
   TBranch        *b_mcStatusFlag;   //!
   TBranch        *b_mcParentage;   //!
   TBranch        *b_mcStatus;   //!
   TBranch        *b_mcCalIsoDR03;   //!
   TBranch        *b_mcTrkIsoDR03;   //!
   TBranch        *b_mcCalIsoDR04;   //!
   TBranch        *b_mcTrkIsoDR04;   //!
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
   TBranch        *b_nPho;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoCalibE;   //!
   TBranch        *b_phoCalibEt;   //!
   TBranch        *b_phoSCE;   //!
   TBranch        *b_phoSCRawE;   //!
   TBranch        *b_phoESEn;   //!
   TBranch        *b_phoESEnP1;   //!
   TBranch        *b_phoESEnP2;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoSCEtaWidth;   //!
   TBranch        *b_phoSCPhiWidth;   //!
   TBranch        *b_phoSCBrem;   //!
   TBranch        *b_phohasPixelSeed;   //!
   TBranch        *b_phoEleVeto;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_phoHoverE;   //!
   TBranch        *b_phoE1x3;   //!
   TBranch        *b_phoE1x5;   //!
   TBranch        *b_phoE2x2;   //!
   TBranch        *b_phoE2x5Max;   //!
   TBranch        *b_phoE5x5;   //!
   TBranch        *b_phoESEffSigmaRR;   //!
   TBranch        *b_phoSigmaIEtaIEtaFull5x5;   //!
   TBranch        *b_phoSigmaIEtaIPhiFull5x5;   //!
   TBranch        *b_phoSigmaIPhiIPhiFull5x5;   //!
   TBranch        *b_phoE1x3Full5x5;   //!
   TBranch        *b_phoE1x5Full5x5;   //!
   TBranch        *b_phoE2x2Full5x5;   //!
   TBranch        *b_phoE2x5MaxFull5x5;   //!
   TBranch        *b_phoE5x5Full5x5;   //!
   TBranch        *b_phoR9Full5x5;   //!
   TBranch        *b_phoPFChIso;   //!
   TBranch        *b_phoPFPhoIso;   //!
   TBranch        *b_phoPFNeuIso;   //!
   TBranch        *b_phoPFChWorstIso;   //!
   TBranch        *b_phoIDMVA;   //!
   TBranch        *b_phoFiredSingleTrgs;   //!
   TBranch        *b_phoFiredDoubleTrgs;   //!
   TBranch        *b_phoFiredL1Trgs;   //!
   TBranch        *b_phoSeedTime;   //!
   TBranch        *b_phoSeedEnergy;   //!
   TBranch        *b_phoxtalBits;   //!
   TBranch        *b_phoIDbit;   //!
   TBranch        *b_npfPho;   //!
   TBranch        *b_pfphoEt;   //!
   TBranch        *b_pfphoEta;   //!
   TBranch        *b_pfphoPhi;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleChargeConsistent;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleSCEn;   //!
   TBranch        *b_eleESEn;   //!
   TBranch        *b_eleESEnP1;   //!
   TBranch        *b_eleESEnP2;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleDz;   //!
   TBranch        *b_eleSIP;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleR9;   //!
   TBranch        *b_eleCalibPt;   //!
   TBranch        *b_eleCalibEn;   //!
   TBranch        *b_eleSCEta;   //!
   TBranch        *b_eleSCPhi;   //!
   TBranch        *b_eleSCRawEn;   //!
   TBranch        *b_eleSCEtaWidth;   //!
   TBranch        *b_eleSCPhiWidth;   //!
   TBranch        *b_eleHoverE;   //!
   TBranch        *b_eleEoverP;   //!
   TBranch        *b_eleEoverPout;   //!
   TBranch        *b_eleEoverPInv;   //!
   TBranch        *b_eleBrem;   //!
   TBranch        *b_eledEtaAtVtx;   //!
   TBranch        *b_eledPhiAtVtx;   //!
   TBranch        *b_eledEtaAtCalo;   //!
   TBranch        *b_eleSigmaIEtaIEtaFull5x5;   //!
   TBranch        *b_eleSigmaIPhiIPhiFull5x5;   //!
   TBranch        *b_eleConvVeto;   //!
   TBranch        *b_eleMissHits;   //!
   TBranch        *b_eleESEffSigmaRR;   //!
   TBranch        *b_elePFChIso;   //!
   TBranch        *b_elePFPhoIso;   //!
   TBranch        *b_elePFNeuIso;   //!
   TBranch        *b_elePFPUIso;   //!
   TBranch        *b_elePFClusEcalIso;   //!
   TBranch        *b_elePFClusHcalIso;   //!
   TBranch        *b_elePFMiniIso;   //!
   TBranch        *b_eleIDMVA;   //!
   TBranch        *b_eleIDMVAHZZ;   //!
   TBranch        *b_eledEtaseedAtVtx;   //!
   TBranch        *b_eleE1x5;   //!
   TBranch        *b_eleE2x5;   //!
   TBranch        *b_eleE5x5;   //!
   TBranch        *b_eleE1x5Full5x5;   //!
   TBranch        *b_eleE2x5Full5x5;   //!
   TBranch        *b_eleE5x5Full5x5;   //!
   TBranch        *b_eleR9Full5x5;   //!
   TBranch        *b_eleEcalDrivenSeed;   //!
   TBranch        *b_eleDr03EcalRecHitSumEt;   //!
   TBranch        *b_eleDr03HcalDepth1TowerSumEt;   //!
   TBranch        *b_eleDr03HcalDepth2TowerSumEt;   //!
   TBranch        *b_eleDr03HcalTowerSumEt;   //!
   TBranch        *b_eleDr03TkSumPt;   //!
   TBranch        *b_elecaloEnergy;   //!
   TBranch        *b_eleTrkdxy;   //!
   TBranch        *b_eleKFHits;   //!
   TBranch        *b_eleKFChi2;   //!
   TBranch        *b_eleGSFChi2;   //!
   TBranch        *b_eleGSFPt;   //!
   TBranch        *b_eleGSFEta;   //!
   TBranch        *b_eleGSFPhi;   //!
   TBranch        *b_eleGSFCharge;   //!
   TBranch        *b_eleGSFHits;   //!
   TBranch        *b_eleGSFMissHits;   //!
   TBranch        *b_eleGSFNHitsMax;   //!
   TBranch        *b_eleGSFVtxProb;   //!
   TBranch        *b_eleGSFlxyPV;   //!
   TBranch        *b_eleGSFlxyBS;   //!
   TBranch        *b_eleBCEn;   //!
   TBranch        *b_eleBCEta;   //!
   TBranch        *b_eleBCPhi;   //!
   TBranch        *b_eleBCS25;   //!
   TBranch        *b_eleBCS15;   //!
   TBranch        *b_eleBCSieie;   //!
   TBranch        *b_eleBCSieip;   //!
   TBranch        *b_eleBCSipip;   //!
   TBranch        *b_eleFiredSingleTrgs;   //!
   TBranch        *b_eleFiredDoubleTrgs;   //!
   TBranch        *b_eleFiredL1Trgs;   //!
   TBranch        *b_eleIDbit;   //!
   TBranch        *b_npfHF;   //!
   TBranch        *b_pfHFEn;   //!
   TBranch        *b_pfHFECALEn;   //!
   TBranch        *b_pfHFHCALEn;   //!
   TBranch        *b_pfHFPt;   //!
   TBranch        *b_pfHFEta;   //!
   TBranch        *b_pfHFPhi;   //!
   TBranch        *b_pfHFIso;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEn;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muIDbit;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muSIP;   //!
   TBranch        *b_muChi2NDF;   //!
   TBranch        *b_muInnerD0;   //!
   TBranch        *b_muInnerDz;   //!
   TBranch        *b_muTrkLayers;   //!
   TBranch        *b_muPixelLayers;   //!
   TBranch        *b_muPixelHits;   //!
   TBranch        *b_muMuonHits;   //!
   TBranch        *b_muStations;   //!
   TBranch        *b_muMatches;   //!
   TBranch        *b_muTrkQuality;   //!
   TBranch        *b_muIsoTrk;   //!
   TBranch        *b_muPFChIso;   //!
   TBranch        *b_muPFPhoIso;   //!
   TBranch        *b_muPFNeuIso;   //!
   TBranch        *b_muPFPUIso;   //!
   TBranch        *b_muPFMiniIso;   //!
   TBranch        *b_muFiredTrgs;   //!
   TBranch        *b_muFiredL1Trgs;   //!
   TBranch        *b_muInnervalidFraction;   //!
   TBranch        *b_musegmentCompatibility;   //!
   TBranch        *b_muchi2LocalPosition;   //!
   TBranch        *b_mutrkKink;   //!
   TBranch        *b_muBestTrkPtError;   //!
   TBranch        *b_muBestTrkPt;   //!
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
   TBranch        *b_jetCSV2BJetTags;   //!
   TBranch        *b_jetJetProbabilityBJetTags;   //!
   TBranch        *b_jetpfCombinedMVAV2BJetTags;   //!
   TBranch        *b_jetPartonID;   //!
   TBranch        *b_jetHadFlvr;   //!
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
   TBranch        *b_jetP4Smear;   //!
   TBranch        *b_jetP4SmearUp;   //!
   TBranch        *b_jetP4SmearDo;   //!
   TBranch        *b_jetPFLooseId;   //!
   TBranch        *b_jetID;   //!
   TBranch        *b_jetPUID;   //!
   TBranch        *b_jetPUFullID;   //!
   TBranch        *b_jetJECUnc;   //!
   TBranch        *b_jetFiredTrgs;   //!
   TBranch        *b_jetCHF;   //!
   TBranch        *b_jetNHF;   //!
   TBranch        *b_jetCEF;   //!
   TBranch        *b_jetNEF;   //!
   TBranch        *b_jetNCH;   //!
   TBranch        *b_jetNNP;   //!
   TBranch        *b_jetMUF;   //!
   TBranch        *b_jetVtxPt;   //!
   TBranch        *b_jetVtxMass;   //!
   TBranch        *b_jetVtxNtrks;   //!
   TBranch        *b_jetVtx3DVal;   //!
   TBranch        *b_jetVtx3DSig;   //!
   TBranch        *b_nAK8Jet;   //!
   TBranch        *b_AK8JetPt;   //!
   TBranch        *b_AK8JetEn;   //!
   TBranch        *b_AK8JetRawPt;   //!
   TBranch        *b_AK8JetRawEn;   //!
   TBranch        *b_AK8JetEta;   //!
   TBranch        *b_AK8JetPhi;   //!
   TBranch        *b_AK8JetMass;   //!
   TBranch        *b_AK8Jet_tau1;   //!
   TBranch        *b_AK8Jet_tau2;   //!
   TBranch        *b_AK8Jet_tau3;   //!
   TBranch        *b_AK8JetCHF;   //!
   TBranch        *b_AK8JetNHF;   //!
   TBranch        *b_AK8JetCEF;   //!
   TBranch        *b_AK8JetNEF;   //!
   TBranch        *b_AK8JetNCH;   //!
   TBranch        *b_AK8JetNNP;   //!
   TBranch        *b_AK8JetMUF;   //!
   TBranch        *b_AK8Jetnconstituents;   //!
   TBranch        *b_AK8JetPFLooseId;   //!
   TBranch        *b_AK8JetPFTightLepVetoId;   //!
   TBranch        *b_AK8JetSoftDropMass;   //!
   TBranch        *b_AK8JetSoftDropMassCorr;   //!
   TBranch        *b_AK8JetPrunedMass;   //!
   TBranch        *b_AK8JetPrunedMassCorr;   //!
   TBranch        *b_AK8JetpfBoostedDSVBTag;   //!
   TBranch        *b_AK8JetDSVnewV4;   //!
   TBranch        *b_AK8JetCSV;   //!
   TBranch        *b_AK8JetJECUnc;   //!
   TBranch        *b_AK8JetL2L3corr;   //!
   TBranch        *b_AK8puppiPt;   //!
   TBranch        *b_AK8puppiMass;   //!
   TBranch        *b_AK8puppiEta;   //!
   TBranch        *b_AK8puppiPhi;   //!
   TBranch        *b_AK8puppiTau1;   //!
   TBranch        *b_AK8puppiTau2;   //!
   TBranch        *b_AK8puppiTau3;   //!
   TBranch        *b_AK8puppiSDL2L3corr;   //!
   TBranch        *b_AK8puppiSDMass;   //!
   TBranch        *b_AK8puppiSDMassL2L3Corr;   //!
   TBranch        *b_AK8JetPartonID;   //!
   TBranch        *b_AK8JetHadFlvr;   //!
   TBranch        *b_AK8JetGenJetIndex;   //!
   TBranch        *b_AK8JetGenJetEn;   //!
   TBranch        *b_AK8JetGenJetPt;   //!
   TBranch        *b_AK8JetGenJetEta;   //!
   TBranch        *b_AK8JetGenJetPhi;   //!
   TBranch        *b_AK8JetGenPartonID;   //!
   TBranch        *b_AK8JetGenEn;   //!
   TBranch        *b_AK8JetGenPt;   //!
   TBranch        *b_AK8JetGenEta;   //!
   TBranch        *b_AK8JetGenPhi;   //!
   TBranch        *b_AK8JetGenPartonMomID;   //!
   TBranch        *b_AK8JetP4Smear;   //!
   TBranch        *b_AK8JetP4SmearUp;   //!
   TBranch        *b_AK8JetP4SmearDo;   //!
   TBranch        *b_nAK8SDSJ;   //!
   TBranch        *b_AK8SDSJPt;   //!
   TBranch        *b_AK8SDSJEta;   //!
   TBranch        *b_AK8SDSJPhi;   //!
   TBranch        *b_AK8SDSJMass;   //!
   TBranch        *b_AK8SDSJE;   //!
   TBranch        *b_AK8SDSJCharge;   //!
   TBranch        *b_AK8SDSJFlavour;   //!
   TBranch        *b_AK8SDSJCSV;   //!
   TBranch        *b_nAK8puppiSDSJ;   //!
   TBranch        *b_AK8puppiSDSJPt;   //!
   TBranch        *b_AK8puppiSDSJEta;   //!
   TBranch        *b_AK8puppiSDSJPhi;   //!
   TBranch        *b_AK8puppiSDSJMass;   //!
   TBranch        *b_AK8puppiSDSJE;   //!
   TBranch        *b_AK8puppiSDSJCharge;   //!
   TBranch        *b_AK8puppiSDSJFlavour;   //!
   TBranch        *b_AK8puppiSDSJCSV;   //!


   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // Data
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//



   // // general
   // std::std::vector<unsigned char> *bits;
   // std::std::vector<int>     *LUMI;
   // std::std::vector<int>     *NBASICELECTRONS;
   // std::std::vector<int>     *NBASICMUONS;
   // std::std::vector<int>     *NDoubleElTriggers;
   // std::std::vector<int>     *NDoubleMuTriggers;
   // std::std::vector<int>     *NELECTRONS;
   // std::std::vector<int>     *NELECTRONS30;
   // std::std::vector<int>     *NELECTRONSFROMBOSON;
   // std::std::vector<int>     *NGOODELECTRONS;
   // std::std::vector<int>     *NGOODISONOISEFILTER;
   // std::std::vector<int>     *NGOODLEPTONS;
   // std::std::vector<int>     *NGOODMUONS;
   // std::std::vector<int>     *NGOODNOISEFILTER;
   // std::std::vector<int>     *NGOODVERTICES;
   // std::std::vector<int>     *NHTMETTriggers;
   // std::std::vector<int>     *NKSHORTS;
   // std::std::vector<int>     *NMUONS;
   // std::std::vector<int>     *NMUONS30;
   // std::std::vector<int>     *NMUONSFROMBOSON;
   // std::std::vector<int>     *NOSSF;
   // std::std::vector<int>     *NSingleElTriggers;
   // std::std::vector<int>     *NSingleMuTriggers;
   // std::std::vector<int>     *N_bJetsCSVL;
   // std::std::vector<int>     *N_bJetsCSVM;
   // std::std::vector<int>     *N_bosons;
   // std::std::vector<int>     *PU_NumInteractions;
   // std::std::vector<int>     *RUN;
   // std::std::vector<int>     *fakeIncarnation;
   // std::std::vector<double>  *ALLKSHORT_KSIP3DSIG;
   // std::std::vector<double>  *ALLKSHORT_LXYZSIG;
   // std::std::vector<double>  *ALLKSHORT_VERTEXNORMALIZEDCHI2;
   // std::std::vector<double>  *ELECTRON_PT;
   // std::std::vector<double>  *FLATWEIGHT;
   // std::std::vector<double>  *HLTHT;
   // std::std::vector<double>  *HSPH;
   // std::std::vector<double>  *HT;
   // std::std::vector<double>  *HTHLTID;
   // std::std::vector<double>  *HT_All;
   // std::std::vector<double>  *KSHORT_CTAU;
   // std::std::vector<double>  *KSHORT_KSIP2D;
   // std::std::vector<double>  *KSHORT_KSIP3D;
   // std::std::vector<double>  *KSHORT_LXY;
   // std::std::vector<double>  *KSHORT_LXYZ;
   // std::std::vector<double>  *KSHORT_MASS;
   // std::std::vector<double>  *KSHORT_P;
   // std::std::vector<double>  *KSHORT_PT;
   // std::std::vector<double>  *LEPTON_DANGLE;
   // std::std::vector<double>  *LEPTON_DPHI;
   // std::std::vector<double>  *LRM;
   // std::std::vector<double>  *LSPH;
   // std::std::vector<double>  *MET;
   // std::std::vector<double>  *MOSSF;
   // std::std::vector<double>  *MUON_PT;
   // std::std::vector<double>  *OSSFCLOSEMLL;
   // std::std::vector<double>  *OSSFMAXMLL;
   // std::std::vector<double>  *OSSFMINMLL;
   // std::std::vector<double>  *PTOSSF;
   // std::std::vector<double>  *SCALAR_PT;
   // std::std::vector<double>  *SIGNALQUARKS_GENDXY;
   // std::std::vector<double>  *SIGNALQUARKS_P;
   // std::std::vector<double>  *SIGNALQUARKS_PT;
   // std::std::vector<double>  *SSPH;
   // std::std::vector<double>  *TrueNumInteractions;
   // std::std::vector<double>  *WEIGHT;
   // std::std::vector<double>  *rhoAll;
   // std::std::vector<double>  *rhoNeutral;
   // std::std::vector<double>  *stupakR;
   // std::std::vector<double>  *stupakR2;
   // std::std::vector<long>    *EVENT;

   // // jet
   // std::std::vector<int>     *JetMISSINGINNER;
   // std::std::vector<int>     *JetMISSINGOUTER;
   // std::std::vector<int>     *JetNJets;
   // std::std::vector<int>     *JetNCLEANMATCHEDTRACKS;
   // std::std::vector<int>     *JetNMATCHEDTRACKS;
   // std::std::vector<int>     *JetNTRACKSIPLT0P05;
   // std::std::vector<int>     *JetNTRACKSIPSIGGT10;
   // std::std::vector<int>     *JetNTRACKSIPSIGLT5;
   // std::std::vector<double>  *JetALPHAMAX2;
   // std::std::vector<double>  *JetALPHAMAXPRIME2;
   // std::std::vector<double>  *JetALPHAMAXPRIME;
   // std::std::vector<double>  *JetALPHAMAX;
   // std::std::vector<double>  *JetASSOCAPLANARITY;
   // std::std::vector<double>  *JetASSOCIATEDTRACKPT;
   // std::std::vector<double>  *JetASSOCSPHERICITY;
   // std::std::vector<double>  *JetASSOCTHRUSTMAJOR;
   // std::std::vector<double>  *JetASSOCTHRUSTMINOR;
   // std::std::vector<double>  *JetAVFASSOCAPLANARITY;
   // std::std::vector<double>  *JetAVFASSOCSPHERICITY;
   // std::std::vector<double>  *JetAVFASSOCTHRUSTMAJOR;
   // std::std::vector<double>  *JetAVFASSOCTHRUSTMINOR;
   // std::std::vector<double>  *JetAVFBEAMSPOTDELTAPHI;
   // std::std::vector<double>  *JetAVFBEAMSPOTRECOILPT;
   // std::std::vector<double>  *JetAVFDISTTOPV;
   // std::std::vector<double>  *JetAVFVERTEXCHI2NDOF;
   // std::std::vector<double>  *JetAVFVERTEXDEGREESOFFREEDOM;
   // std::std::vector<double>  *JetAVFVERTEXDISTANCETOBEAM;
   // std::std::vector<double>  *JetAVFVERTEXTOTALCHISQUARED;
   // std::std::vector<double>  *JetAVFVERTEXTRACKENERGY;
   // std::std::vector<double>  *JetAVFVERTEXTRACKMASS;
   // std::std::vector<double>  *JetAVFVERTEXTRANSVERSESIG;
   // std::std::vector<double>  *JetAVGMISSINGINNER;
   // std::std::vector<double>  *JetAVGMISSINGOUTER;
   // std::std::vector<double>  *JetBASICCALOJETS1ANGLE_DANGLE;
   // std::std::vector<double>  *JetBASICCALOJETS1ANGLE_DPHI;
   // std::std::vector<double>  *JetBASICCALOJETS1DELTAR;
   // std::std::vector<double>  *JetBASICCALOJETS1PT20ANGLE_DANGLE;
   // std::std::vector<double>  *JetBASICCALOJETS1PT20ANGLE_DPHI;
   // std::std::vector<double>  *JetBASICCALOJETS1PT20DELTAR;
   // std::std::vector<double>  *JetBETA2;
   // std::std::vector<double>  *JetBETA;
   // std::std::vector<double>  *JetETA;
   // std::std::vector<double>  *JetHITSINFRONTOFVERTPERTRACK;
   // std::std::vector<double>  *JetHSPH;
   // std::std::vector<double>  *JetIVFSCORE;
   // std::std::vector<double>  *JetJETAREA;
   // std::std::vector<double>  *JetLEPANGLE_DANGLE;
   // std::std::vector<double>  *JetLEPANGLE_DPHI;
   // std::std::vector<double>  *JetLEPDELTAR;
   // std::std::vector<double>  *JetLINEARRADIALMOMENT;
   // std::std::vector<double>  *JetLRM;
   // std::std::vector<double>  *JetLSPH;
   // std::std::vector<double>  *JetMASSDISPLACED;
   // std::std::vector<double>  *JetMEDIANIPLOG10SIG;
   // std::std::vector<double>  *JetMEDIANIPLOGSIG;
   // std::std::vector<double>  *JetMEDIANLOG10TRACKANGLE;
   // std::std::vector<double>  *JetMETANGLE_DANGLE;
   // std::std::vector<double>  *JetMETANGLE_DPHI;
   // std::std::vector<double>  *JetMETDELTAR;
   // std::std::vector<double>  *JetMISSHITSAFTERVERTPERTRACK;
   // std::std::vector<double>  *JetM;
   // std::std::vector<double>  *JetPHI;
   // std::std::vector<double>  *JetPT;
   // std::std::vector<double>  *JetSELFDELTAR;
   // std::std::vector<double>  *JetSSPH;
   // std::std::vector<double>  *JetSTUPAKPT;
   // std::std::vector<double>  *JetSTUPAKR;
   // std::std::vector<double>  *JetSUMIPLOGSIG;
   // std::std::vector<double>  *JetSUMIPSIG;
   // std::std::vector<double>  *JetSUMIP;
   // std::std::vector<double>  *JetTOTALTRACKANGLEPT;
   // std::std::vector<double>  *JetTOTALTRACKANGLE;
   // std::std::vector<double>  *JetTOTALTRACKPT;
   // std::std::vector<double>  *JetTRACKENERGY;
   // std::std::vector<double>  *JetTRACKMASS;

   // // Declaration of branches
   // // general
   // TBranch *b_bits;
   // TBranch *b_LUMI;
   // TBranch *b_NBASICELECTRONS;
   // TBranch *b_NBASICMUONS;
   // TBranch *b_NDoubleElTriggers;
   // TBranch *b_NDoubleMuTriggers;
   // TBranch *b_NELECTRONS;
   // TBranch *b_NELECTRONS30;
   // TBranch *b_NELECTRONSFROMBOSON;
   // TBranch *b_NGOODELECTRONS;
   // TBranch *b_NGOODISONOISEFILTER;
   // TBranch *b_NGOODLEPTONS;
   // TBranch *b_NGOODMUONS;
   // TBranch *b_NGOODNOISEFILTER;
   // TBranch *b_NGOODVERTICES;
   // TBranch *b_NHTMETTriggers;
   // TBranch *b_NKSHORTS;
   // TBranch *b_NMUONS;
   // TBranch *b_NMUONS30;
   // TBranch *b_NMUONSFROMBOSON;
   // TBranch *b_NOSSF;
   // TBranch *b_NSingleElTriggers;
   // TBranch *b_NSingleMuTriggers;
   // TBranch *b_N_bJetsCSVL;
   // TBranch *b_N_bJetsCSVM;
   // TBranch *b_N_bosons;
   // TBranch *b_PU_NumInteractions;
   // TBranch *b_RUN;
   // TBranch *b_fakeIncarnation;
   // TBranch *b_ALLKSHORT_KSIP3DSIG;
   // TBranch *b_ALLKSHORT_LXYZSIG;
   // TBranch *b_ALLKSHORT_VERTEXNORMALIZEDCHI2;
   // TBranch *b_ELECTRON_PT;
   // TBranch *b_FLATWEIGHT;
   // TBranch *b_HLTHT;
   // TBranch *b_HSPH;
   // TBranch *b_HT;
   // TBranch *b_HTHLTID;
   // TBranch *b_HT_All;
   // TBranch *b_KSHORT_CTAU;
   // TBranch *b_KSHORT_KSIP2D;
   // TBranch *b_KSHORT_KSIP3D;
   // TBranch *b_KSHORT_LXY;
   // TBranch *b_KSHORT_LXYZ;
   // TBranch *b_KSHORT_MASS;
   // TBranch *b_KSHORT_P;
   // TBranch *b_KSHORT_PT;
   // TBranch *b_LEPTON_DANGLE;
   // TBranch *b_LEPTON_DPHI;
   // TBranch *b_LRM;
   // TBranch *b_LSPH;
   // TBranch *b_MET;
   // TBranch *b_MOSSF;
   // TBranch *b_MUON_PT;
   // TBranch *b_OSSFCLOSEMLL;
   // TBranch *b_OSSFMAXMLL;
   // TBranch *b_OSSFMINMLL;
   // TBranch *b_PTOSSF;
   // TBranch *b_SCALAR_PT;
   // TBranch *b_SIGNALQUARKS_GENDXY;
   // TBranch *b_SIGNALQUARKS_P;
   // TBranch *b_SIGNALQUARKS_PT;
   // TBranch *b_SSPH;
   // TBranch *b_TrueNumInteractions;
   // TBranch *b_WEIGHT;
   // TBranch *b_rhoAll;
   // TBranch *b_rhoNeutral;
   // TBranch *b_stupakR;
   // TBranch *b_stupakR2;
   // TBranch *b_EVENT;

   // // jet
   // TBranch *b_JetMISSINGINNER;
   // TBranch *b_JetMISSINGOUTER;
   // TBranch *b_JetNJets;
   // TBranch *b_JetNCLEANMATCHEDTRACKS;
   // TBranch *b_JetNMATCHEDTRACKS;
   // TBranch *b_JetNTRACKSIPLT0P05;
   // TBranch *b_JetNTRACKSIPSIGGT10;
   // TBranch *b_JetNTRACKSIPSIGLT5;
   // TBranch *b_JetALPHAMAX2;
   // TBranch *b_JetALPHAMAXPRIME2;
   // TBranch *b_JetALPHAMAXPRIME;
   // TBranch *b_JetALPHAMAX;
   // TBranch *b_JetASSOCAPLANARITY;
   // TBranch *b_JetASSOCIATEDTRACKPT;
   // TBranch *b_JetASSOCSPHERICITY;
   // TBranch *b_JetASSOCTHRUSTMAJOR;
   // TBranch *b_JetASSOCTHRUSTMINOR;
   // TBranch *b_JetAVFASSOCAPLANARITY;
   // TBranch *b_JetAVFASSOCSPHERICITY;
   // TBranch *b_JetAVFASSOCTHRUSTMAJOR;
   // TBranch *b_JetAVFASSOCTHRUSTMINOR;
   // TBranch *b_JetAVFBEAMSPOTDELTAPHI;
   // TBranch *b_JetAVFBEAMSPOTRECOILPT;
   // TBranch *b_JetAVFDISTTOPV;
   // TBranch *b_JetAVFVERTEXCHI2NDOF;
   // TBranch *b_JetAVFVERTEXDEGREESOFFREEDOM;
   // TBranch *b_JetAVFVERTEXDISTANCETOBEAM;
   // TBranch *b_JetAVFVERTEXTOTALCHISQUARED;
   // TBranch *b_JetAVFVERTEXTRACKENERGY;
   // TBranch *b_JetAVFVERTEXTRACKMASS;
   // TBranch *b_JetAVFVERTEXTRANSVERSESIG;
   // TBranch *b_JetAVGMISSINGINNER;
   // TBranch *b_JetAVGMISSINGOUTER;
   // TBranch *b_JetBASICCALOJETS1ANGLE_DANGLE;
   // TBranch *b_JetBASICCALOJETS1ANGLE_DPHI;
   // TBranch *b_JetBASICCALOJETS1DELTAR;
   // TBranch *b_JetBASICCALOJETS1PT20ANGLE_DANGLE;
   // TBranch *b_JetBASICCALOJETS1PT20ANGLE_DPHI;
   // TBranch *b_JetBASICCALOJETS1PT20DELTAR;
   // TBranch *b_JetBETA2;
   // TBranch *b_JetBETA;
   // TBranch *b_JetETA;
   // TBranch *b_JetHITSINFRONTOFVERTPERTRACK;
   // TBranch *b_JetHSPH;
   // TBranch *b_JetIVFSCORE;
   // TBranch *b_JetJETAREA;
   // TBranch *b_JetLEPANGLE_DANGLE;
   // TBranch *b_JetLEPANGLE_DPHI;
   // TBranch *b_JetLEPDELTAR;
   // TBranch *b_JetLINEARRADIALMOMENT;
   // TBranch *b_JetLRM;
   // TBranch *b_JetLSPH;
   // TBranch *b_JetMASSDISPLACED;
   // TBranch *b_JetMEDIANIPLOG10SIG;
   // TBranch *b_JetMEDIANIPLOGSIG;
   // TBranch *b_JetMEDIANLOG10TRACKANGLE;
   // TBranch *b_JetMETANGLE_DANGLE;
   // TBranch *b_JetMETANGLE_DPHI;
   // TBranch *b_JetMETDELTAR;
   // TBranch *b_JetMISSHITSAFTERVERTPERTRACK;
   // TBranch *b_JetM;
   // TBranch *b_JetPHI;
   // TBranch *b_JetPT;
   // TBranch *b_JetSELFDELTAR;
   // TBranch *b_JetSSPH;
   // TBranch *b_JetSTUPAKPT;
   // TBranch *b_JetSTUPAKR;
   // TBranch *b_JetSUMIPLOGSIG;
   // TBranch *b_JetSUMIPSIG;
   // TBranch *b_JetSUMIP;
   // TBranch *b_JetTOTALTRACKANGLEPT;
   // TBranch *b_JetTOTALTRACKANGLE;
   // TBranch *b_JetTOTALTRACKPT;
   // TBranch *b_JetTRACKENERGY;
   // TBranch *b_JetTRACKMASS;


   //analyzer_base(TTree *tree=0);
   analyzer_base();
   virtual ~analyzer_base();
   virtual void     Init(TTree *tree, Bool_t domakelog, TString jettype);
   virtual Long64_t LoadTree(Long64_t entry);
   Double_t         makeEventWeight(Double_t crossSec, Double_t lumi,
                                    Double_t nrEvents, Bool_t isMC);
};

#endif

