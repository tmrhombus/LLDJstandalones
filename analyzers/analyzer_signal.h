
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

 // TH1F h_NELECTRONS[6];
 // TH1F h_NELECTRONS30[6];
 // TH1F h_NELECTRONSFROMBOSON[6];
 // TH1F h_NGOODELECTRONS[6];
 // TH1F h_NGOODLEPTONS[6];
 // TH1F h_NGOODMUONS[6];
 // TH1F h_NGOODVERTICES[6];
 // TH1F h_NKSHORTS[6];
 // TH1F h_NMUONS[6];
 // TH1F h_NMUONS30[6];
 // TH1F h_NMUONSFROMBOSON[6];
 // TH1F h_NOSSF[6];
 //
 // TH1F h_N_bJetsCSVL[6];
 // TH1F h_N_bJetsCSVM[6];
 // TH1F h_N_bosons[6];
 // TH1F h_PU_NumInteractions[6];
 //
 // TH1F h_fakeIncarnation[6];
 // TH1F h_ELECTRON_PT[6];
 // TH1F h_FLATWEIGHT[6];
 // TH1F h_HLTHT[6];
 // TH1F h_HSPH[6];
 // TH1F h_HT[6];
 // TH1F h_HTHLTID[6];
 // TH1F h_HT_All[6];
 // TH1F h_LEPTON_DANGLE[6];
 // TH1F h_LEPTON_DPHI[6];
 // TH1F h_LRM[6];
 //
 // TH1F h_MET[6];
 // TH1F h_MOSSF[6];
 // TH1F h_MUON_PT[6];
 // TH1F h_OSSFCLOSEMLL[6];
 // TH1F h_OSSFMAXMLL[6];
 // TH1F h_OSSFMINMLL[6];
 // TH1F h_PTOSSF[6];
 // TH1F h_SCALAR_PT[6];
 //
 // TH1F h_SIGNALQUARKS_GENDXY[6];
 // TH1F h_SIGNALQUARKS_P[6];
 // TH1F h_SIGNALQUARKS_PT[6];
 // TH1F h_SSPH[6];
 // TH1F h_TrueNumInteractions[6];
 // TH1F h_rhoAll[6];
 // TH1F h_rhoNeutral[6];
 // TH1F h_stupakR[6];
 // TH1F h_stupakR2[6];
 //
 // // JET
 // TH1F h_JetMISSINGINNER[6][4];
 // TH1F h_JetMISSINGOUTER[6][4];
 //
 // TH1F h_JetHSPH[6][4];
 // TH1F h_JetNJets[6][4];
 //
 // TH1F h_JetNCLEANMATCHEDTRACKS[6][4];
 // TH1F h_JetNMATCHEDTRACKS[6][4];
 // TH1F h_JetNTRACKSIPLT0P05[6][4];
 // TH1F h_JetNTRACKSIPSIGGT10[6][4];
 // TH1F h_JetNTRACKSIPSIGLT5[6][4];
 // TH1F h_JetALPHAMAX2[6][4];
 // TH1F h_JetALPHAMAXPRIME2[6][4];
 // TH1F h_JetALPHAMAXPRIME[6][4];
 // TH1F h_JetALPHAMAX[6][4];
 // TH1F h_JetASSOCAPLANARITY[6][4];
 // TH1F h_JetASSOCIATEDTRACKPT[6][4];
 // TH1F h_JetASSOCSPHERICITY[6][4];
 // TH1F h_JetASSOCTHRUSTMAJOR[6][4];
 // TH1F h_JetASSOCTHRUSTMINOR[6][4];
 // TH1F h_JetAVFASSOCAPLANARITY[6][4];
 // TH1F h_JetAVFASSOCSPHERICITY[6][4];
 // TH1F h_JetAVFASSOCTHRUSTMAJOR[6][4];
 // TH1F h_JetAVFASSOCTHRUSTMINOR[6][4];
 // TH1F h_JetAVFBEAMSPOTDELTAPHI[6][4];
 // TH1F h_JetAVFBEAMSPOTRECOILPT[6][4];
 // TH1F h_JetAVFDISTTOPV[6][4];
 // TH1F h_JetAVFVERTEXCHI2NDOF[6][4];
 // TH1F h_JetAVFVERTEXDEGREESOFFREEDOM[6][4];
 // TH1F h_JetAVFVERTEXDISTANCETOBEAM[6][4];
 // TH1F h_JetAVFVERTEXTOTALCHISQUARED[6][4];
 // TH1F h_JetAVFVERTEXTRACKENERGY[6][4];
 // TH1F h_JetAVFVERTEXTRACKMASS[6][4];
 // TH1F h_JetAVFVERTEXTRANSVERSESIG[6][4];
 // TH1F h_JetAVGMISSINGINNER[6][4];
 // TH1F h_JetAVGMISSINGOUTER[6][4];
 // TH1F h_JetBASICCALOJETS1ANGLE_DANGLE[6][4];
 // TH1F h_JetBASICCALOJETS1ANGLE_DPHI[6][4];
 // TH1F h_JetBASICCALOJETS1DELTAR[6][4];
 // TH1F h_JetBASICCALOJETS1PT20DELTAR[6][4];
 // TH1F h_JetBETA2[6][4];
 // TH1F h_JetBETA[6][4];
 // TH1F h_JetETA[6][4];
 // TH1F h_JetHITSINFRONTOFVERTPERTRACK[6][4];
 // TH1F h_JetIVFSCORE[6][4];
 // TH1F h_JetJETAREA[6][4];
 // TH1F h_JetLEPANGLE_DANGLE[6][4];
 // TH1F h_JetLEPANGLE_DPHI[6][4];
 // TH1F h_JetLEPDELTAR[6][4];
 //
 // TH1F h_JetLINEARRADIALMOMENT[6][4];
 // TH1F h_JetLRM[6][4];
 // TH1F h_JetMASSDISPLACED[6][4];
 // TH1F h_JetMEDIANIPLOG10SIG[6][4];
 // TH1F h_JetMEDIANIPLOGSIG[6][4];
 // TH1F h_JetMEDIANLOG10TRACKANGLE[6][4];
 //
 // TH1F h_JetMETANGLE_DANGLE[6][4];
 // TH1F h_JetMETANGLE_DPHI[6][4];
 // TH1F h_JetMETDELTAR[6][4];
 // TH1F h_JetMISSHITSAFTERVERTPERTRACK[6][4];
 // TH1F h_JetM[6][4];
 //
 // TH1F h_JetPHI[6][4];
 // TH1F h_JetPT[6][4];
 //
 // TH1F h_JetSELFDELTAR[6][4];
 // TH1F h_JetSSPH[6][4];
 // TH1F h_JetSTUPAKPT[6][4];
 // TH1F h_JetSTUPAKR[6][4];
 // TH1F h_JetSUMIPLOGSIG[6][4];
 // TH1F h_JetSUMIPSIG[6][4];
 // TH1F h_JetSUMIP[6][4];
 // TH1F h_JetTOTALTRACKANGLEPT[6][4];
 // TH1F h_JetTOTALTRACKANGLE[6][4];
 // TH1F h_JetTOTALTRACKPT[6][4];
 // TH1F h_JetTRACKENERGY[6][4];
 // TH1F h_JetTRACKMASS[6][4];

};

#endif
