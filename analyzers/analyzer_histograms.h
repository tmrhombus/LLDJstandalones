
#ifndef analyzer_histograms_h
#define analyzer_histograms_h

#include "analyzer_scalefactors.h"

class analyzer_histograms : public analyzer_scalefactors {


public :

                  analyzer_histograms();
   virtual        ~analyzer_histograms(); 

 // bin names
 std::vector<TString> selbinnames;
 std::vector<TString> jetmultnames;
 std::vector<TString> tagmultnames;
 std::vector<TString> lepnames;
 // selbinnames  = NoSel, Sig, ZH, DY, OffZ, NoPair
 // jetmultnames = Leading, Subleading, Third, Fourth, All
 // lepbinname   = ele, mu, NoSel
 static const int SELBINNAMESIZE  = 6;
 static const int JETMULTNAMESIZE = 5; 
 static const int TAGMULTNAMESIZE = 5; 
 static const int LEPBINNAMESIZE  = 3;

 void          initSelectionCategories();

 // Histograms

 // make 1D,2D histograms (helper function)
 TH2F          initSingleHistogramTH2F(TString hnamex, TString htitley,
                                   Int_t nbinsx, Double_t xmin, Double_t xmax,
                                   Int_t nbinsy, Double_t ymin, Double_t ymax);
 TH1F          initSingleHistogramTH1F(TString hname, TString htitle,
                                   Int_t nbins, Double_t xmin,
                                   Double_t xmax);
 TH1F         initSingleHistogramTH1F(TString hname, TString htitle, 
				      int nbins, Float_t xbins[]);

 // Cutflow histograms
 Bool_t        initCutflowHistograms();
 Bool_t        fillCutflowHistograms(Double_t weight, int selbin, int lepbin, Int_t selint);
 Bool_t        writeCutflowHistograms(int selbin, int lepbin);

 // 2D Histograms 
 Bool_t        init2DHistograms();
 Bool_t        fill2DHistograms(Double_t weight, int selbin);
 Bool_t        write2DHistograms(int selbin);
 // Electron Variables
 Bool_t        initEleHistograms();
 Bool_t        fillEleHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeEleHistograms(int selbin, int lepbin);
 // Muon Variables
 Bool_t        initMuHistograms();
 Bool_t        fillMuHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeMuHistograms(int selbin, int lepbin);
 // Lepton Variables
 Bool_t        initLepHistograms();
 Bool_t        fillLepHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeLepHistograms(int selbin, int lepbin);
 // Photon Variables
 Bool_t        initPhoHistograms();
 Bool_t        fillPhoHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writePhoHistograms(int selbin, int lepbin);
 // MET/HT Variables
 Bool_t        initMETHTHistograms();
 Bool_t        fillMETHTHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeMETHTHistograms(int selbin, int lepbin);

 // AODCaloJet Basic Variables
 Bool_t        initAODCaloJetBasicHistograms();
 Bool_t        fillAODCaloJetBasicHistograms(Double_t weight, int selbin, int lepbin, int jetbin);
 Bool_t        writeAODCaloJetBasicHistograms(int selbin, int lepbin, int jetbin);
 // AODCaloJet Extra Variables
 Bool_t        initAODCaloJetExtraHistograms();
 Bool_t        fillAODCaloJetExtraHistograms(Double_t weight, int selbin, int lepbin, int jetbin);
 Bool_t        writeAODCaloJetExtraHistograms(int selbin, int lepbin, int jetbin);
 // AODCaloJetTag Basic Variables
 Bool_t        initAODCaloJetTagHistograms();
 Bool_t        fillAODCaloJetTagHistograms(Double_t weight, int selbin, int lepbin, int tagbin);
 Bool_t        writeAODCaloJetTagHistograms(int selbin, int lepbin, int tagbin);
 // Jet Multiplicity
 Bool_t        initAODCaloJetMultHistograms();
 Bool_t        fillAODCaloJetMultHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeAODCaloJetMultHistograms(int selbin, int lepbin);
 Bool_t        initAODCaloJetTagMultHistograms();
 Bool_t        fillAODCaloJetTagMultHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        writeAODCaloJetTagMultHistograms(int selbin, int lepbin);

 //For variable binning
 Bool_t        scaleVariableBinHistograms(int selbin, int lepbin);

 // Set up which histograms to fill 
 Bool_t        fillSelectedHistograms(Double_t weight, int selbin, int lepbin);
 Bool_t        fillSelectedJetHistograms(Double_t weight, int selbin, int lepbin, int jetbin);
 Bool_t        fillSelectedTagHistograms(Double_t weight, int selbin, int lepbin, int tagbin);
 Bool_t        writeSelectedHistograms(int selbin, int lepbin);
 Bool_t        writeSelectedJetHistograms(int selbin, int lepbin, int jetbin);
 Bool_t        writeSelectedTagHistograms(int selbin, int lepbin, int tagbin);

 Bool_t dofillselbin    [SELBINNAMESIZE];
 Bool_t dofilllepbin    [LEPBINNAMESIZE];

 // initialize histograms as global
 TH1F histoTH1F;
 TH2F histoTH2F;

 // Cutflow histograms
 TH1F h_Cutflow                       [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_Onecut                        [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_NMinus                        [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_RawCutflow                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_RawOnecut                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F h_RawNMinus                     [SELBINNAMESIZE][LEPBINNAMESIZE];

 // Electron
 TH1F  h_AOD_nEle                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_nSelectedEle             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_elePt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_eleEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_eleEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_elePhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_eleCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];

 // Muon
 TH1F  h_AOD_nMu                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_nSelectedMu             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muCharge                [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_muPFdBetaIsolation      [SELBINNAMESIZE][LEPBINNAMESIZE];
 
 // Generic Lepton
 TH1F  h_AOD_dilepton_Mass           [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_dilepton_Pt             [SELBINNAMESIZE][LEPBINNAMESIZE];

 // Photon
 TH1F  h_AOD_nPho                     [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_nSelectedPho             [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoEn                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoPt                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoEta                   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_phoPhi                   [SELBINNAMESIZE][LEPBINNAMESIZE];

 // MET / HT
 TH1F  h_AOD_MET_phi              [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AOD_MET_pt               [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_htall                    [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_htaodcalojets            [SELBINNAMESIZE][LEPBINNAMESIZE];

 // nJets
 TH1F  h_nSelectedAODCaloJet      [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nSelectedAODCaloJetTag   [SELBINNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_nCaloJet                 [SELBINNAMESIZE][LEPBINNAMESIZE]; // AODnCaloJet; 
 TH1F  h_nPFJet                   [SELBINNAMESIZE][LEPBINNAMESIZE]; // AODnPFJet; 
 TH1F  h_nPFchsJet                [SELBINNAMESIZE][LEPBINNAMESIZE]; // AODnPFchsJet; 

 // AODCaloJetBasicHistograms
 TH1F  h_AODCaloJetPt                             [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetPtVar                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
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
 TH1F  h_AODCaloJetMinDR                          [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAbsEta                         [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 // AODCaloJetExtraHistograms
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

 // AODCaloJetTagHistograms
 TH1F  h_AODCaloJetPt_Tag0                       [SELBINNAMESIZE][TAGMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetPtVar_Tag0                    [SELBINNAMESIZE][TAGMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetMinDR_Tag0                    [SELBINNAMESIZE][TAGMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetAbsEta_Tag0                   [SELBINNAMESIZE][TAGMULTNAMESIZE][LEPBINNAMESIZE];
 TH1F  h_AODCaloJetNCleanMatchedTracks_Tag0      [SELBINNAMESIZE][TAGMULTNAMESIZE][LEPBINNAMESIZE];


 // // 2D
 TH2F h_IpVAlpha                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH2F h_IpVjetPt                  [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];
 TH2F h_AlphaVjetPt               [SELBINNAMESIZE][JETMULTNAMESIZE][LEPBINNAMESIZE];

 // Background Estimate
 void comb(int n, int r, int *arr, int sz, Double_t weight);
 TH1F h_bkgest;//for now only one
 Bool_t initBackgroundEstimateHistograms();
 Bool_t fillBackgroundEstimateHistograms(Double_t weight);
 Bool_t writeBackgroundEstimateHistograms();

};

#endif
