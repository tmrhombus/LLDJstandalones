// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

// (local) variables associated with tree branches

ULong64_t   AOD_HLT_Ele23Loose_;
ULong64_t   AOD_HLT_Ele27Tight_;
ULong64_t   AOD_HLT_Ele17Ele12_;
ULong64_t   AOD_HLT_Ele23Ele12_;

ULong64_t   AOD_HLT_IsoMu22_;
ULong64_t   AOD_HLT_IsoTkMu22_;
ULong64_t   AOD_HLT_Mu17Mu8_;
ULong64_t   AOD_HLT_Mu17TkMu8_;

ULong64_t   AOD_HLT_Mu17Mu8_noDZ_;
ULong64_t   AOD_HLT_Mu17TkMu8_noDZ_;
ULong64_t   AOD_HLT_IsoMu24_;
ULong64_t   AOD_HLT_IsoTkMu24_;


// // triggers used in VHbb
//  // https://indico.cern.ch/event/655639/contributions/2670493/attachments/1497203/2337123/VHbb_Approval_28_07_17_v10.pdf#page=8

// - HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9 (Era H)
// - Already implemented through v10
 
// new
// - HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v6 (Era H) 
// AOD_HLT_Mu17Mu8_noDZ_

// new
// ULong64_t   AOD_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*  
// - HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v5 (Era H) 
// AOD_HLT_Mu17TkMu8_noDZ_

// ULong64_t   AOD_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v* 
// - HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7 (Era H) 
// - Implemented through v7

// ULong64_t   AOD_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v* 
// - HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6 (Era H) 
// - Already implemented

// ULong64_t   AOD_HLT_Ele27_WPTight_Gsf
// - HLT_Ele27_WPTight_Gsf_v7 (Era H) 
// - Already implemented

// new
// - HLT_IsoMu24_v4 (Era H) 
// ULong64_t   AOD_HLT_IsoMu24

// new 
// - HLT_IsoTkMu24_v4 (Era H) 
// ULong64_t   AOD_HLT_IsoTkMu24



// Full trigger list 
// from https://cmsweb.cern.ch/das/download?lfn=/store/data/Run2016H/SingleMuon/AOD/PromptReco-v3/000/284/036/00000/2C315372-649F-E611-AEBF-FA163E028533.root
//HLTriggerFirstPath
//HLT_AK8PFJet360_TrimMass30_v7
//HLT_AK8PFJet400_TrimMass30_v1
//HLT_AK8PFHT750_TrimMass50_v1
//HLT_AK8PFHT800_TrimMass50_v1
//HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_v1
//HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_v1
//HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_v1
//HLT_AK8DiPFJet300_200_TrimMass30_v1
//HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v8
//HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_v7
//HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_v6
//HLT_AK8DiPFJet280_200_TrimMass30_v5
//HLT_AK8DiPFJet250_200_TrimMass30_v5
//HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_v5
//HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_v5
//HLT_CaloJet500_NoJetID_v5
//HLT_Dimuon13_PsiPrime_v6
//HLT_Dimuon13_Upsilon_v6
//HLT_Dimuon20_Jpsi_v6
//HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v8
//HLT_DoubleEle33_CaloIdL_v7
//HLT_DoubleEle33_CaloIdL_MW_v8
//HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v10
//HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v3
//HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg_v3
//HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg_v2
//HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg_v2
//HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_v2
//HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_v2
//HLT_DoubleEle37_Ele27_CaloIdL_GsfTrkIdVL_v7
//HLT_DoubleMu33NoFiltersNoVtx_v5
//HLT_DoubleMu38NoFiltersNoVtx_v5
//HLT_DoubleMu23NoFiltersNoVtxDisplaced_v5
//HLT_DoubleMu28NoFiltersNoVtxDisplaced_v5
//HLT_DoubleMu0_v2
//HLT_DoubleMu4_3_Bs_v7
//HLT_DoubleMu4_3_Jpsi_Displaced_v7
//HLT_DoubleMu4_JpsiTrk_Displaced_v7
//HLT_DoubleMu4_LowMassNonResonantTrk_Displaced_v7
//HLT_DoubleMu3_Trk_Tau3mu_v4
//HLT_DoubleMu4_PsiPrimeTrk_Displaced_v7
//HLT_Mu7p5_L2Mu2_Jpsi_v4
//HLT_Mu7p5_L2Mu2_Upsilon_v4
//HLT_Mu7p5_Track2_Jpsi_v4
//HLT_Mu7p5_Track3p5_Jpsi_v4
//HLT_Mu7p5_Track7_Jpsi_v4
//HLT_Mu7p5_Track2_Upsilon_v4
//HLT_Mu7p5_Track3p5_Upsilon_v4
//HLT_Mu7p5_Track7_Upsilon_v4
//HLT_Dimuon0er16_Jpsi_NoOS_NoVertexing_v4
//HLT_Dimuon6_Jpsi_NoVertexing_v4
//HLT_DoublePhoton60_v7
//HLT_DoublePhoton85_v8
//HLT_Ele20_eta2p1_WPLoose_Gsf_LooseIsoPFTau28_v3
//HLT_Ele22_eta2p1_WPLoose_Gsf_LooseIsoPFTau29_v3
//HLT_Ele22_eta2p1_WPLoose_Gsf_v9
//HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30_v4
//HLT_Ele25_WPTight_Gsf_v7
//HLT_Ele25_eta2p1_WPTight_Gsf_v7
//HLT_Ele27_WPLoose_Gsf_WHbbBoost_v9
//HLT_Ele27_WPTight_Gsf_v7
//HLT_Ele27_WPTight_Gsf_L1JetTauSeeded_v4
//HLT_Ele27_eta2p1_WPLoose_Gsf_v8
//HLT_Ele27_eta2p1_WPTight_Gsf_v8
//HLT_Ele30_WPTight_Gsf_v1
//HLT_Ele30_eta2p1_WPTight_Gsf_v1
//HLT_Ele32_WPTight_Gsf_v1
//HLT_Ele32_eta2p1_WPTight_Gsf_v8
//HLT_Ele36_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1_v3
//HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v9
//HLT_Ele105_CaloIdVT_GsfTrkIdT_v8
//HLT_HT200_v4
//HLT_HT275_v4
//HLT_HT325_v4
//HLT_HT425_v4
//HLT_HT575_v4
//HLT_HT430to450_v4
//HLT_HT450to470_v4
//HLT_HT470to500_v4
//HLT_HT500to550_v4
//HLT_HT550to650_v4
//HLT_HT650_v5
//HLT_IsoMu16_eta2p1_MET30_v4
//HLT_IsoMu16_eta2p1_MET30_LooseIsoPFTau50_Trk30_eta2p1_v5
//HLT_DoubleIsoMu17_eta2p1_noDzCut_v5
//HLT_IsoMu19_eta2p1_LooseIsoPFTau20_v5
//HLT_IsoMu19_eta2p1_LooseIsoPFTau20_SingleL1_v5
//HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v5
//HLT_IsoMu19_eta2p1_LooseCombinedIsoPFTau20_v1
//HLT_IsoMu19_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_v1
//HLT_IsoMu19_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_v1
//HLT_IsoMu21_eta2p1_MediumCombinedIsoPFTau32_Trk1_eta2p1_Reg_v1
//HLT_IsoMu21_eta2p1_TightCombinedIsoPFTau32_Trk1_eta2p1_Reg_v1
//HLT_IsoMu20_v6
//HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v5
//HLT_IsoMu21_eta2p1_LooseIsoPFTau50_Trk30_eta2p1_SingleL1_v4
//HLT_IsoMu21_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v5
//HLT_IsoMu22_v5
//HLT_IsoMu22_eta2p1_v4
//HLT_IsoMu24_v4
//HLT_IsoMu24_eta2p1_v3
//HLT_IsoMu27_v7
//HLT_IsoTkMu20_v7
//HLT_IsoTkMu22_v5
//HLT_IsoTkMu22_eta2p1_v4
//HLT_IsoTkMu24_v4
//HLT_IsoTkMu24_eta2p1_v3
//HLT_IsoTkMu27_v7
//HLT_JetE30_NoBPTX3BX_v4
//HLT_JetE30_NoBPTX_v4
//HLT_JetE50_NoBPTX3BX_v4
//HLT_JetE70_NoBPTX3BX_v4
//HLT_L1SingleMu18_v1
//HLT_L2Mu10_v3
//HLT_L2DoubleMu23_NoVertex_v6
//HLT_L2DoubleMu28_NoVertex_2Cha_Angle2p5_Mass10_v6
//HLT_L2DoubleMu38_NoVertex_2Cha_Angle2p5_Mass10_v6
//HLT_L2Mu10_NoVertex_NoBPTX3BX_v2
//HLT_L2Mu10_NoVertex_NoBPTX_v3
//HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX_v1
//HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX_v2
//HLT_LooseIsoPFTau50_Trk30_eta2p1_v7
//HLT_LooseIsoPFTau50_Trk30_eta2p1_MET90_v6
//HLT_LooseIsoPFTau50_Trk30_eta2p1_MET110_v6
//HLT_LooseIsoPFTau50_Trk30_eta2p1_MET120_v6
//HLT_PFTau120_eta2p1_v5
//HLT_PFTau140_eta2p1_v5
//HLT_VLooseIsoPFTau120_Trk50_eta2p1_v5
//HLT_VLooseIsoPFTau140_Trk50_eta2p1_v5
//HLT_Mu17_Mu8_v5
//HLT_Mu17_Mu8_DZ_v7
//HLT_Mu17_Mu8_SameSign_v5
//HLT_Mu17_Mu8_SameSign_DZ_v6
//HLT_Mu20_Mu10_v5
//HLT_Mu20_Mu10_DZ_v6
//HLT_Mu20_Mu10_SameSign_v4
//HLT_Mu20_Mu10_SameSign_DZ_v6
//HLT_Mu17_TkMu8_DZ_v6
//HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v6
//HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7
//HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v5
//HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6
//HLT_Mu25_TkMu0_dEta18_Onia_v6
//HLT_Mu27_TkMu8_v5
//HLT_Mu30_TkMu11_v5
//HLT_Mu30_eta2p1_PFJet150_PFJet50_v5
//HLT_Mu40_TkMu11_v5
//HLT_Mu40_eta2p1_PFJet200_PFJet50_rsNoVtx_Photon38_CaloIdL_v7
//HLT_Mu42NoFiltersNoVtx_Photon42_CaloIdL_v7
//HLT_Mu28NoFiltersNoVtxDisplaced_Photon28_CaloIdL_v7
//HLT_Mu33NoFiltersNoVtxDisplaced_Photon33_CaloIdL_v7
//HLT_Mu23NoFiltersNoVtx_PhFJet200_v4
//HLT_AK8PFJet260_v5
//HLT_AK8PFJet320_v5
//HLT_AK8PFJet400_v5
//HLT_AK8PFJet450_v5
//HLT_AK8PFJet500_v5
//HLT_PFJet40_v9
//HLT_PFJet60_v9
//HLT_PFJet80_v8
//HLT_PFJet140_v8
//HFHT600_v8
//HLT_PFHT650_v8
//HLT_PFHT900_v6
//HLT_PFHT200_PFAlphaT0p51_v8
//HLT_PFHT200_DiPFJetAve90_PFAlphaT0p63_v8
//HLT_PFHT250_DiPFJetAve90_PFAlphaT0p58_v8
//HLT_PFHT300_DoubleJet90_Double30_DoubleBTagCSV_p087_v5
//HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160_v5
//HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6_v5
//HLT_Douton75_R9Id90_HE10_Iso40_EBOnly_PFMET40_v9
//HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_VBF_v7
//HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40_v9
//HLT_v3
//HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v4
//HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v9
//HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v3
//HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v9
//HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4
//HLThoton30_v7
//HLT_Photon36_v7
//HLT_Photon50_v7
//HLT_Photon75_v7
//HLT_Photon90_v7
//HLT_Photon120_v7
//HLT_Photon175_v8
//HLT_Photon165_HE10_v8
//HLT_Photon22_R9Id90_HE10_IsoM_v7
//HLT_Photon30_R9Id90_HE10_IsoM_v8
//HLT_Photon36_R9Id90_HE10_IsoM_v8
//HLT_Photon50_R9Id90_HE10_IsoM_v8
//HLT_Photonbb60_200_v3
//HLT_Rsq0p02_MR450_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_v3
//HLT_Rsq0p02_MR500_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_v2
//HLT_Rsq0p02_MR550_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_v2
//HLT_HT250_DisplacedDijet40_DisplacedTrack_v5T_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight_v8
//HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight_v8
//HLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v10
//HLT_DoubleMu8_Mass8_PFHT300_v9
//HLT_Mu8_Ele8_CaloIdM_TMu17_DoubleTrkMu8NoFiltersNoVtx_v6
//HLT_Mu8_v5
//HLT_Mu17_v4
//HLT_Mu3_PFJet40_v6
//HLT_Ele8_CaloIdM_TrackIdM_PFJet30_v9
//HLT_Ele12_CaloIdM_TrackIdM_PFJet30_v9
//HLT_Ele17_CaloIdM_TrackIdM_PFJet30_v7
//40_BTagScouting_v7
//DST_CaloJet40_CaloScouting_PFScouting_v7
//DST_CaloJet40_CaloBTagScouting_v6
//DST_L1HTT_BTagScouting_v7
//DST_L1HTT_CaloScouting_PFScouting_v7
//DST_L1HTT_CaloBTagScouting_HLT_HISinglePhoton40_v4
//HLT_HISinglePhoton60_v4
//HLT_EcalCalibration_v3
//HLT_HcalCalibration_v4
//AlCa_EcalPhiSym_v6
//AlCa_SingleEle_WPVeryLoose_Gsf_v7
//AlCa_DoubleEle_CaloIdL_TrackIdL
//AlCa_LumiPixels_ZeroBias_v5
//HLT_Photon500_v6
//HLT_Photon600_v6
//HLT_Mu300_v3
//HLT_Mu350_v3
//HLT_MET250_v5
//HLT_MET300_v5
//HLT_MET600_v5
//HLT_MET700_v5
//HLT_PFMET300_v7
//HLT_PFMET400_v7
//HLT_PFMET500_v7



ULong64_t   AOD_HLT_PFHT350PFMET100_isPS_;

ULong64_t   AOD_HLT_Ele23Loose_isPS_;
ULong64_t   AOD_HLT_Ele27Tight_isPS_;
ULong64_t   AOD_HLT_Ele17Ele12_isPS_;
ULong64_t   AOD_HLT_Ele23Ele12_isPS_;

ULong64_t   AOD_HLT_IsoMu22_isPS_;
ULong64_t   AOD_HLT_IsoTkMu22_isPS_;
ULong64_t   AOD_HLT_Mu17Mu8_isPS_;
ULong64_t   AOD_HLT_Mu17TkMu8_isPS_;

ULong64_t   AOD_HLT_Mu17Mu8_noDZ_isPS_;
ULong64_t   AOD_HLT_Mu17TkMu8_noDZ_isPS_;
ULong64_t   AOD_HLT_IsoMu24_isPS_;
ULong64_t   AOD_HLT_IsoTkMu24_isPS_;

const int bitsize=8;


void lldjNtuple::branchesAODTrigger(TTree* tree){
  tree->Branch("AOD_HLT_Ele23Loose",       &AOD_HLT_Ele23Loose_) ;
  tree->Branch("AOD_HLT_Ele27Tight",       &AOD_HLT_Ele27Tight_) ;
  tree->Branch("AOD_HLT_Ele17Ele12",       &AOD_HLT_Ele17Ele12_) ;
  tree->Branch("AOD_HLT_Ele23Ele12",       &AOD_HLT_Ele23Ele12_) ;
  
  tree->Branch("AOD_HLT_IsoMu22"  ,        &AOD_HLT_IsoMu22_)   ;
  tree->Branch("AOD_HLT_IsoTkMu22",        &AOD_HLT_IsoTkMu22_) ;
  tree->Branch("AOD_HLT_Mu17Mu8"  ,        &AOD_HLT_Mu17Mu8_)   ;
  tree->Branch("AOD_HLT_Mu17TkMu8",        &AOD_HLT_Mu17TkMu8_) ;

  tree->Branch("AOD_HLT_Mu17Mu8_noDZ"  ,   &AOD_HLT_Mu17Mu8_noDZ_)   ;
  tree->Branch("AOD_HLT_Mu17TkMu8_noDZ",   &AOD_HLT_Mu17TkMu8_noDZ_) ;
  tree->Branch("AOD_HLT_IsoMu24"  ,        &AOD_HLT_IsoMu24_)   ;
  tree->Branch("AOD_HLT_IsoTkMu24",        &AOD_HLT_IsoTkMu24_) ;

}


void lldjNtuple::fillAODTrigger(const edm::Event &e, const edm::EventSetup &es){
  
  AOD_HLT_Ele23Loose_       = 0;
  AOD_HLT_Ele27Tight_       = 0;
  AOD_HLT_Ele17Ele12_       = 0;
  AOD_HLT_Ele23Ele12_       = 0;
  
  AOD_HLT_IsoMu22_          = 0;
  AOD_HLT_IsoTkMu22_        = 0;
  AOD_HLT_Mu17Mu8_          = 0;
  AOD_HLT_Mu17TkMu8_        = 0;

  AOD_HLT_Mu17Mu8_noDZ_     = 0;
  AOD_HLT_Mu17TkMu8_noDZ_   = 0;
  AOD_HLT_IsoMu24_          = 0;
  AOD_HLT_IsoTkMu24_        = 0;

  
  if( !( e.getByToken(AODTriggerToken_, AODTriggerHandle_) && e.getByToken(AODTriggerEventToken_, AODTriggerEventHandle_) ) ){ return; }
  
  for(int i = 0; i < (int)hltConfig_.size(); i++){
    string name = hltConfig_.triggerName(i);
    //std::cout<<name<<"\n";
    
    int bitEle23Loose = -1;
    if      (name.find("HLT_Ele23_WPLoose_Gsf_v1")  != string::npos) bitEle23Loose = 0  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v2")  != string::npos) bitEle23Loose = 1  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v3")  != string::npos) bitEle23Loose = 2  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v4")  != string::npos) bitEle23Loose = 3  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v5")  != string::npos) bitEle23Loose = 4  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v6")  != string::npos) bitEle23Loose = 5  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v7")  != string::npos) bitEle23Loose = 6  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v8")  != string::npos) bitEle23Loose = 7  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v9")  != string::npos) bitEle23Loose = 8  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v10") != string::npos) bitEle23Loose = 9  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v11") != string::npos) bitEle23Loose = 10 ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v12") != string::npos) bitEle23Loose = 11 ;
    
    int bitEle27Tight = -1;
    if      (name.find("HLT_Ele27_WPTight_Gsf_v1")  != string::npos) bitEle27Tight = 0 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v2")  != string::npos) bitEle27Tight = 1 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v3")  != string::npos) bitEle27Tight = 2 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v4")  != string::npos) bitEle27Tight = 3 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v5")  != string::npos) bitEle27Tight = 4 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v6")  != string::npos) bitEle27Tight = 5 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v7")  != string::npos) bitEle27Tight = 6 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v8")  != string::npos) bitEle27Tight = 7 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v9")  != string::npos) bitEle27Tight = 8 ;
    
    // Double Electron
    int bitEle17Ele12 = -1;
    if      (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")  != string::npos) bitEle17Ele12 = 0 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2")  != string::npos) bitEle17Ele12 = 1 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3")  != string::npos) bitEle17Ele12 = 2 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4")  != string::npos) bitEle17Ele12 = 3 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5")  != string::npos) bitEle17Ele12 = 4 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6")  != string::npos) bitEle17Ele12 = 5 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7")  != string::npos) bitEle17Ele12 = 6 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8")  != string::npos) bitEle17Ele12 = 7 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9")  != string::npos) bitEle17Ele12 = 8 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10") != string::npos) bitEle17Ele12 = 9 ;
    
    int bitEle23Ele12 = -1;
    if      (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")  != string::npos) bitEle23Ele12 = 0 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2")  != string::npos) bitEle23Ele12 = 1 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3")  != string::npos) bitEle23Ele12 = 2 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4")  != string::npos) bitEle23Ele12 = 3 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5")  != string::npos) bitEle23Ele12 = 4 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6")  != string::npos) bitEle23Ele12 = 5 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7")  != string::npos) bitEle23Ele12 = 6 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8")  != string::npos) bitEle23Ele12 = 7 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9")  != string::npos) bitEle23Ele12 = 8 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10") != string::npos) bitEle23Ele12 = 9 ;
    
    // Single Iso Mu
    int bitIsoMu22   = -1;
    if      (name.find("HLT_IsoMu22_v1") != string::npos) bitIsoMu22 = 0 ;
    else if (name.find("HLT_IsoMu22_v2") != string::npos) bitIsoMu22 = 1 ;
    else if (name.find("HLT_IsoMu22_v3") != string::npos) bitIsoMu22 = 2 ;
    else if (name.find("HLT_IsoMu22_v4") != string::npos) bitIsoMu22 = 3 ;
    else if (name.find("HLT_IsoMu22_v5") != string::npos) bitIsoMu22 = 4 ;
    else if (name.find("HLT_IsoMu22_v6") != string::npos) bitIsoMu22 = 5 ;
    else if (name.find("HLT_IsoMu22_v7") != string::npos) bitIsoMu22 = 6 ;
    
    int bitIsoTkMu22 = -1;
    if      (name.find("HLT_IsoTkMu22_v1")  != string::npos) bitIsoTkMu22 = 0 ;
    else if (name.find("HLT_IsoTkMu22_v2")  != string::npos) bitIsoTkMu22 = 1 ;
    else if (name.find("HLT_IsoTkMu22_v3")  != string::npos) bitIsoTkMu22 = 2 ;
    else if (name.find("HLT_IsoTkMu22_v4")  != string::npos) bitIsoTkMu22 = 3 ;
    else if (name.find("HLT_IsoTkMu22_v5")  != string::npos) bitIsoTkMu22 = 4 ;
    else if (name.find("HLT_IsoTkMu22_v6")  != string::npos) bitIsoTkMu22 = 5 ;
    else if (name.find("HLT_IsoTkMu22_v7")  != string::npos) bitIsoTkMu22 = 6 ;
    else if (name.find("HLT_IsoTkMu22_v8")  != string::npos) bitIsoTkMu22 = 7 ;
    else if (name.find("HLT_IsoTkMu22_v9")  != string::npos) bitIsoTkMu22 = 8 ;
    else if (name.find("HLT_IsoTkMu22_v10") != string::npos) bitIsoTkMu22 = 9 ;

    int bitIsoMu24   = -1;
    if      (name.find("HLT_IsoMu24_v1") != string::npos) bitIsoMu24 = 0 ;
    else if (name.find("HLT_IsoMu24_v2") != string::npos) bitIsoMu24 = 1 ;
    else if (name.find("HLT_IsoMu24_v3") != string::npos) bitIsoMu24 = 2 ;
    else if (name.find("HLT_IsoMu24_v4") != string::npos) bitIsoMu24 = 3 ;
    
    int bitIsoTkMu24 = -1;
    if      (name.find("HLT_IsoTkMu24_v1")  != string::npos) bitIsoTkMu24 = 0 ;
    else if (name.find("HLT_IsoTkMu24_v2")  != string::npos) bitIsoTkMu24 = 1 ;
    else if (name.find("HLT_IsoTkMu24_v3")  != string::npos) bitIsoTkMu24 = 2 ;
    else if (name.find("HLT_IsoTkMu24_v4")  != string::npos) bitIsoTkMu24 = 3 ;
    
    // Double Iso Mu
    int bitMu17Mu8   = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17Mu8 = 0 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17Mu8 = 1 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17Mu8 = 2 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17Mu8 = 3 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17Mu8 = 4 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17Mu8 = 5 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7") != string::npos) bitMu17Mu8 = 6 ;
    
    int bitMu17TkMu8 = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17TkMu8 = 0 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17TkMu8 = 1 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17TkMu8 = 2 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17TkMu8 = 3 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17TkMu8 = 4 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17TkMu8 = 5 ;                   

    int bitMu17Mu8_noDZ   = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1") != string::npos) bitMu17Mu8_noDZ = 0 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v2") != string::npos) bitMu17Mu8_noDZ = 1 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v3") != string::npos) bitMu17Mu8_noDZ = 2 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v4") != string::npos) bitMu17Mu8_noDZ = 3 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v5") != string::npos) bitMu17Mu8_noDZ = 4 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v6") != string::npos) bitMu17Mu8_noDZ = 5 ;
    
    int bitMu17TkMu8_noDZ = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1") != string::npos) bitMu17TkMu8_noDZ = 0 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v2") != string::npos) bitMu17TkMu8_noDZ = 1 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v3") != string::npos) bitMu17TkMu8_noDZ = 2 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v4") != string::npos) bitMu17TkMu8_noDZ = 3 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v5") != string::npos) bitMu17TkMu8_noDZ = 4 ;                   
    
    //printf(" Reading trigger: %s\n" , name.c_str()  );
    //printf(" bitPFHT350PFMET100 %d \n", bitPFHT350PFMET100 ); 
    //printf(" bitEle23Loose      %d \n", bitEle23Loose      ); 
    //printf(" bitEle27Tight      %d \n", bitEle27Tight      ); 
    //printf(" bitEle17Ele12      %d \n", bitEle17Ele12      ); 
    //printf(" bitEle23Ele12      %d \n", bitEle23Ele12      ); 
    //printf(" bitIsoMu22         %d \n", bitIsoMu22         ); 
    //printf(" bitIsoTkMu22       %d \n", bitIsoTkMu22       ); 
    //printf(" bitMu17Mu8         %d \n", bitMu17Mu8         ); 
    //printf(" bitMu17TkMu8       %d \n", bitMu17TkMu8       ); 
    
    // indicates prescaling and whether trigger was fired or not
    unsigned int isPrescaled = hltPrescale_.prescaleValue(e,es,name);
    const unsigned int triggerIndex = hltConfig_.triggerIndex(name);
    unsigned int isFired     = AODTriggerHandle_->accept(triggerIndex);
    //cout << "was run " << AODTriggerHandle_->wasrun(triggerIndex) << endl;
    
    if ( bitEle23Loose      >= 0 ){
      AOD_HLT_Ele23Loose_            |= (isFired     << bitEle23Loose      );
      AOD_HLT_Ele23Loose_isPS_       |= (isPrescaled << bitEle23Loose      );
    }
    if ( bitEle27Tight      >= 0 ){     
      AOD_HLT_Ele27Tight_            |= (isFired     << bitEle27Tight      );
      AOD_HLT_Ele27Tight_isPS_       |= (isPrescaled << bitEle27Tight      );
    }
    if ( bitEle17Ele12      >= 0 ){     
      AOD_HLT_Ele17Ele12_            |= (isFired     << bitEle17Ele12      );
      AOD_HLT_Ele17Ele12_isPS_       |= (isPrescaled << bitEle17Ele12      );
    }
    if ( bitEle23Ele12      >= 0 ){     
      AOD_HLT_Ele23Ele12_            |= (isFired     << bitEle23Ele12      );
      AOD_HLT_Ele23Ele12_isPS_       |= (isPrescaled << bitEle23Ele12      );
    }
    if ( bitIsoMu22         >= 0 ){   
      AOD_HLT_IsoMu22_               |= (isFired     << bitIsoMu22         );
      AOD_HLT_IsoMu22_isPS_          |= (isPrescaled << bitIsoMu22         );
    }
    if ( bitIsoTkMu22       >= 0 ){     
      AOD_HLT_IsoTkMu22_             |= (isFired     << bitIsoTkMu22       );
      AOD_HLT_IsoTkMu22_isPS_        |= (isPrescaled << bitIsoTkMu22       );
    }
    if ( bitIsoMu24         >= 0 ){   
      AOD_HLT_IsoMu24_               |= (isFired     << bitIsoMu24         );
      AOD_HLT_IsoMu24_isPS_          |= (isPrescaled << bitIsoMu24         );
    }
    if ( bitIsoTkMu24       >= 0 ){     
      AOD_HLT_IsoTkMu24_             |= (isFired     << bitIsoTkMu24       );
      AOD_HLT_IsoTkMu24_isPS_        |= (isPrescaled << bitIsoTkMu24       );
    }
    if ( bitMu17Mu8         >= 0 ){   
      AOD_HLT_Mu17Mu8_               |= (isFired     << bitMu17Mu8         );
      AOD_HLT_Mu17Mu8_isPS_          |= (isPrescaled << bitMu17Mu8         );
    }
    if ( bitMu17TkMu8       >= 0 ){     
      AOD_HLT_Mu17TkMu8_             |= (isFired     << bitMu17TkMu8       );
      AOD_HLT_Mu17TkMu8_isPS_        |= (isPrescaled << bitMu17TkMu8       );
    }
    if ( bitMu17Mu8_noDZ         >= 0 ){   
      AOD_HLT_Mu17Mu8_noDZ_               |= (isFired     << bitMu17Mu8_noDZ         );
      AOD_HLT_Mu17Mu8_noDZ_isPS_          |= (isPrescaled << bitMu17Mu8_noDZ         );
    }
    if ( bitMu17TkMu8_noDZ       >= 0 ){     
      AOD_HLT_Mu17TkMu8_noDZ_             |= (isFired     << bitMu17TkMu8_noDZ       );
      AOD_HLT_Mu17TkMu8_noDZ_isPS_        |= (isPrescaled << bitMu17TkMu8_noDZ       );
    }
    
    //std::bitset<bitsize> AOD_HLT_PFHT350PFMET100_b(bitPFHT350PFMET100);
    std::bitset<bitsize> AOD_HLT_Ele23Loose_b(bitEle23Loose);
    std::bitset<bitsize> AOD_HLT_Ele27Tight_b(bitEle27Tight);
    std::bitset<bitsize> AOD_HLT_Ele17Ele12_b(bitEle17Ele12);
    std::bitset<bitsize> AOD_HLT_Ele23Ele12_b(bitEle23Ele12);
    std::bitset<bitsize> AOD_HLT_IsoMu22_b(bitIsoMu22);
    std::bitset<bitsize> AOD_HLT_IsoTkMu22_b(bitIsoTkMu22);
    std::bitset<bitsize> AOD_HLT_IsoMu24_b(bitIsoMu24);
    std::bitset<bitsize> AOD_HLT_IsoTkMu24_b(bitIsoTkMu24);
    std::bitset<bitsize> AOD_HLT_Mu17Mu8_b(bitMu17Mu8);
    std::bitset<bitsize> AOD_HLT_Mu17TkMu8_b(bitMu17TkMu8);
    std::bitset<bitsize> AOD_HLT_Mu17Mu8_noDZ_b(bitMu17Mu8_noDZ);
    std::bitset<bitsize> AOD_HLT_Mu17TkMu8_noDZ_b(bitMu17TkMu8_noDZ);
    
  }//hltConfig loop
  
}//fillAODTrigger
