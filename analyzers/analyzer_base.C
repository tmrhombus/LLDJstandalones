#include "analyzer_base.h"

//----------------------------analyzer_base
analyzer_base::analyzer_base() 
{
}

//----------------------------~analyzer_base
analyzer_base::~analyzer_base()
{
}

//----------------------------LoadTree
Long64_t analyzer_base::LoadTree(Long64_t entry)
{
 // Set the environment to read one entry
 if (!fChain) return -5;
 Long64_t centry = fChain->LoadTree(entry);
 if (centry < 0) return centry;
 if (fChain->GetTreeNumber() != fCurrent) {
  fCurrent = fChain->GetTreeNumber();
 }
 return centry;
}

//----------------------------makeEventWeight
Double_t analyzer_base::makeEventWeight(Double_t crossSec,
                                        Double_t lumi,
                                        Double_t nrEvents)
{
  // 1.0 for real data
  event_weight=1.0;
  Double_t crossSecScl = crossSec;
  if(isMC){ event_weight=lumi*crossSecScl/nrEvents; }
  //printf("isMC: %i lumi: %0.9f crossSec: %0.9f nrEvents: %0.9f",isMC,lumi,crossSecScl,nrEvents);
  //printf("  event_weight: %0.9f\n",event_weight);

  return event_weight;
}

//----------------------------Init
void analyzer_base::Init(TTree *tree, Bool_t isitMC, Bool_t domakelog)
{

   isMC = isitMC;
   makelog = domakelog;

   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // MC and Data
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // set object pointers
   phoE = 0;
   phoEt = 0;
   phoEta = 0;
   phoPhi = 0;
   phoCalibE = 0;
   phoCalibEt = 0;
   phoSCE = 0;
   phoSCRawE = 0;
   phoSCPhi = 0;
   phoSCEta = 0;
   phoIDbit = 0;
   phoPassLooseID = 0;
   phoPassMediumID = 0;
   phoPassTightID = 0;
   elePt = 0;
   eleEn = 0;
   eleEta = 0;
   elePhi = 0;
   eleCharge = 0;
   eleIDbit = 0;
   eleChargeConsistent = 0;
   eleSCEn = 0;
   eleSCEta = 0;
   eleSCPhi = 0;
   eleCalibPt = 0;
   eleCalibEn = 0;
   elePassVetoID = 0;
   elePassLooseID = 0;
   elePassMediumID = 0;
   elePassTightID = 0;
   elePassHEEPID = 0;
   elePassHLTID = 0;
   elePFdBetaIsolation = 0;
   elePFdBetaIsolationCorr = 0;
   elePFdBetaIsolationDiff = 0;
   muPt = 0;
   muEn = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muType = 0;
   muIDbit = 0;
   muPassLooseID = 0;
   muPassMediumID = 0;
   muPassTighID = 0;
   muNumberOfMissingInnerHits = 0;
   muNumberOfMissingMiddleHits = 0;
   muNumberOfMissingOuterHits = 0;
   muNumberOfMatchedStations = 0;
   muNumberOfValidPixelHits = 0;
   muTrackerLayersWithMeasurement = 0;
   muIsGlobalMuon = 0;
   muIsPFMuon = 0;
   muPFdBetaIsolation = 0;
   jetPt = 0;
   jetEn = 0;
   jetEta = 0;
   jetPhi = 0;
   jetRawPt = 0;
   jetRawEn = 0;
   jetMt = 0;
   jetArea = 0;
   jetLeadTrackPt = 0;
   jetLeadTrackEta = 0;
   jetLeadTrackPhi = 0;
   jetLepTrackPID = 0;
   jetLepTrackPt = 0;
   jetLepTrackEta = 0;
   jetLepTrackPhi = 0;
   jetCSV2BJetTags = 0;
   jetJetProbabilityBJetTags = 0;
   jetpfCombinedMVAV2BJetTags = 0;
   jetAlphaMax = 0;
   jetAlphaMax2 = 0;
   jetAlphaMaxP = 0;
   jetAlphaMaxP2 = 0;
   jetDauVertex_x = 0;
   jetDauVertex_y = 0;
   jetDauVertex_z = 0;
   jetDauVertex_r = 0;
   alphaMax_jetDauVertex_r = 0;
   jetAlphaMax_PV3onPV2 = 0;
   jetAlphaMax_PV3onNeu = 0;
   jetAlphaMax_PV3onAll = 0;
   jetAlphaMax_PV2onNeu = 0;
   jetAlphaMax_PV2onAll = 0;
   jetAlpha2Max_PV3onPV2 = 0;
   jetAlpha2Max_PV3onNeu = 0;
   jetAlpha2Max_PV3onAll = 0;
   jetAlpha2Max_PV2onNeu = 0;
   jetAlpha2Max_PV2onAll = 0;
   jetAlphaD = 0;
   jetAlphaMaxD = 0;
   jetLog10IPSig = 0;
   jetMedianLog10IPSig = 0;
   jetSumIP = 0;
   jetSumIPSig = 0;
   jetTrackAngle = 0;
   jetLogTrackAngle = 0;
   jetMedianLogTrackAngle = 0;
   jetTotalTrackAngle = 0;
   jetTrackPt = 0;
   jetTrackEta = 0;
   jetTrackPhi = 0;
   jetTrackPDGID = 0;
   jetTrackMomPDGID = 0;
   jetNConstituents = 0;
   jetPFLooseId = 0;
   jetID = 0;
   jetPUID = 0;
   jetPUFullID = 0;
   jetJECUnc = 0;
   jetFiredTrgs = 0;
   jetCHF = 0;
   jetNHF = 0;
   jetCEF = 0;
   jetNEF = 0;
   jetNCH = 0;
   jetNNP = 0;
   jetMUF = 0;
   jetVtxPt = 0;
   jetVtxMass = 0;
   jetVtxNtrks = 0;
   jetVtx3DVal = 0;
   jetVtx3DSig = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nGoodVtx", &nGoodVtx, &b_nGoodVtx);
   fChain->SetBranchAddress("nTrksPV", &nTrksPV, &b_nTrksPV);
   fChain->SetBranchAddress("isPVGood", &isPVGood, &b_isPVGood);
   fChain->SetBranchAddress("vtx", &vtx, &b_vtx);
   fChain->SetBranchAddress("vty", &vty, &b_vty);
   fChain->SetBranchAddress("vtz", &vtz, &b_vtz);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rhoCentral", &rhoCentral, &b_rhoCentral);
   fChain->SetBranchAddress("nTruePU", &nTruePU, &b_nTruePU);
   fChain->SetBranchAddress("HLT_Ele23Loose", &HLT_Ele23Loose, &b_HLT_Ele23Loose);
   fChain->SetBranchAddress("HLT_Ele27Tight", &HLT_Ele27Tight, &b_HLT_Ele27Tight);
   fChain->SetBranchAddress("HLT_Ele17Ele12", &HLT_Ele17Ele12, &b_HLT_Ele17Ele12);
   fChain->SetBranchAddress("HLT_Ele23Ele12", &HLT_Ele23Ele12, &b_HLT_Ele23Ele12);
   fChain->SetBranchAddress("HLT_IsoMu22", &HLT_IsoMu22, &b_HLT_IsoMu22);
   fChain->SetBranchAddress("HLT_IsoTkMu22", &HLT_IsoTkMu22, &b_HLT_IsoTkMu22);
   fChain->SetBranchAddress("HLT_Mu17Mu8", &HLT_Mu17Mu8, &b_HLT_Mu17Mu8);
   fChain->SetBranchAddress("HLT_Mu17TkMu8", &HLT_Mu17TkMu8, &b_HLT_Mu17TkMu8);
   fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
   fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);
   fChain->SetBranchAddress("pfMETPhi", &pfMETPhi, &b_pfMETPhi);
   fChain->SetBranchAddress("pfMETsumEt", &pfMETsumEt, &b_pfMETsumEt);
   fChain->SetBranchAddress("pfMETmEtSig", &pfMETmEtSig, &b_pfMETmEtSig);
   fChain->SetBranchAddress("pfMETSig", &pfMETSig, &b_pfMETSig);
   fChain->SetBranchAddress("pfMET_T1JERUp", &pfMET_T1JERUp, &b_pfMET_T1JERUp);
   fChain->SetBranchAddress("pfMET_T1JERDo", &pfMET_T1JERDo, &b_pfMET_T1JERDo);
   fChain->SetBranchAddress("pfMET_T1JESUp", &pfMET_T1JESUp, &b_pfMET_T1JESUp);
   fChain->SetBranchAddress("pfMET_T1JESDo", &pfMET_T1JESDo, &b_pfMET_T1JESDo);
   fChain->SetBranchAddress("pfMET_T1UESUp", &pfMET_T1UESUp, &b_pfMET_T1UESUp);
   fChain->SetBranchAddress("pfMET_T1UESDo", &pfMET_T1UESDo, &b_pfMET_T1UESDo);
   fChain->SetBranchAddress("pfMETPhi_T1JESUp", &pfMETPhi_T1JESUp, &b_pfMETPhi_T1JESUp);
   fChain->SetBranchAddress("pfMETPhi_T1JESDo", &pfMETPhi_T1JESDo, &b_pfMETPhi_T1JESDo);
   fChain->SetBranchAddress("pfMETPhi_T1UESUp", &pfMETPhi_T1UESUp, &b_pfMETPhi_T1UESUp);
   fChain->SetBranchAddress("pfMETPhi_T1UESDo", &pfMETPhi_T1UESDo, &b_pfMETPhi_T1UESDo);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
   fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
   fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoCalibE", &phoCalibE, &b_phoCalibE);
   fChain->SetBranchAddress("phoCalibEt", &phoCalibEt, &b_phoCalibEt);
   fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
   fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
   fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
   fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
   fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
   fChain->SetBranchAddress("phoPassLooseID", &phoPassLooseID, &b_phoPassLooseID);
   fChain->SetBranchAddress("phoPassMediumID", &phoPassMediumID, &b_phoPassMediumID);
   fChain->SetBranchAddress("phoPassTightID", &phoPassTightID, &b_phoPassTightID);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
   fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
   fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleCalibPt", &eleCalibPt, &b_eleCalibPt);
   fChain->SetBranchAddress("eleCalibEn", &eleCalibEn, &b_eleCalibEn);
   fChain->SetBranchAddress("elePassVetoID", &elePassVetoID, &b_elePassVetoID);
   fChain->SetBranchAddress("elePassLooseID", &elePassLooseID, &b_elePassLooseID);
   fChain->SetBranchAddress("elePassMediumID", &elePassMediumID, &b_elePassMediumID);
   fChain->SetBranchAddress("elePassTightID", &elePassTightID, &b_elePassTightID);
   fChain->SetBranchAddress("elePassHEEPID", &elePassHEEPID, &b_elePassHEEPID);
   fChain->SetBranchAddress("elePassHLTID", &elePassHLTID, &b_elePassHLTID);
   fChain->SetBranchAddress("elePFdBetaIsolation", &elePFdBetaIsolation, &b_elePFdBetaIsolation);
   fChain->SetBranchAddress("elePFdBetaIsolationCorr", &elePFdBetaIsolationCorr, &b_elePFdBetaIsolationCorr);
   fChain->SetBranchAddress("elePFdBetaIsolationDiff", &elePFdBetaIsolationDiff, &b_elePFdBetaIsolationDiff);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEn", &muEn, &b_muEn);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muType", &muType, &b_muType);
   fChain->SetBranchAddress("muIDbit", &muIDbit, &b_muIDbit);
   fChain->SetBranchAddress("muPassLooseID", &muPassLooseID, &b_muPassLooseID);
   fChain->SetBranchAddress("muPassMediumID", &muPassMediumID, &b_muPassMediumID);
   fChain->SetBranchAddress("muPassTighID", &muPassTighID, &b_muPassTighID);
   fChain->SetBranchAddress("muNumberOfMissingInnerHits", &muNumberOfMissingInnerHits, &b_muNumberOfMissingInnerHits);
   fChain->SetBranchAddress("muNumberOfMissingMiddleHits", &muNumberOfMissingMiddleHits, &b_muNumberOfMissingMiddleHits);
   fChain->SetBranchAddress("muNumberOfMissingOuterHits", &muNumberOfMissingOuterHits, &b_muNumberOfMissingOuterHits);
   fChain->SetBranchAddress("muNumberOfMatchedStations", &muNumberOfMatchedStations, &b_muNumberOfMatchedStations);
   fChain->SetBranchAddress("muNumberOfValidPixelHits", &muNumberOfValidPixelHits, &b_muNumberOfValidPixelHits);
   fChain->SetBranchAddress("muTrackerLayersWithMeasurement", &muTrackerLayersWithMeasurement, &b_muTrackerLayersWithMeasurement);
   fChain->SetBranchAddress("muIsGlobalMuon", &muIsGlobalMuon, &b_muIsGlobalMuon);
   fChain->SetBranchAddress("muIsPFMuon", &muIsPFMuon, &b_muIsPFMuon);
   fChain->SetBranchAddress("muPFdBetaIsolation", &muPFdBetaIsolation, &b_muPFdBetaIsolation);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEn", &jetEn, &b_jetEn);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
   fChain->SetBranchAddress("jetRawEn", &jetRawEn, &b_jetRawEn);
   fChain->SetBranchAddress("jetMt", &jetMt, &b_jetMt);
   fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
   fChain->SetBranchAddress("jetLeadTrackPt", &jetLeadTrackPt, &b_jetLeadTrackPt);
   fChain->SetBranchAddress("jetLeadTrackEta", &jetLeadTrackEta, &b_jetLeadTrackEta);
   fChain->SetBranchAddress("jetLeadTrackPhi", &jetLeadTrackPhi, &b_jetLeadTrackPhi);
   fChain->SetBranchAddress("jetLepTrackPID", &jetLepTrackPID, &b_jetLepTrackPID);
   fChain->SetBranchAddress("jetLepTrackPt", &jetLepTrackPt, &b_jetLepTrackPt);
   fChain->SetBranchAddress("jetLepTrackEta", &jetLepTrackEta, &b_jetLepTrackEta);
   fChain->SetBranchAddress("jetLepTrackPhi", &jetLepTrackPhi, &b_jetLepTrackPhi);
   fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
   fChain->SetBranchAddress("jetJetProbabilityBJetTags", &jetJetProbabilityBJetTags, &b_jetJetProbabilityBJetTags);
   fChain->SetBranchAddress("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags, &b_jetpfCombinedMVAV2BJetTags);
   fChain->SetBranchAddress("jetAlphaMax", &jetAlphaMax, &b_jetAlphaMax);
   fChain->SetBranchAddress("jetAlphaMax2", &jetAlphaMax2, &b_jetAlphaMax2);
   fChain->SetBranchAddress("jetAlphaMaxP", &jetAlphaMaxP, &b_jetAlphaMaxP);
   fChain->SetBranchAddress("jetAlphaMaxP2", &jetAlphaMaxP2, &b_jetAlphaMaxP2);
   fChain->SetBranchAddress("jetDauVertex_x", &jetDauVertex_x, &b_jetDauVertex_x);
   fChain->SetBranchAddress("jetDauVertex_y", &jetDauVertex_y, &b_jetDauVertex_y);
   fChain->SetBranchAddress("jetDauVertex_z", &jetDauVertex_z, &b_jetDauVertex_z);
   fChain->SetBranchAddress("jetDauVertex_r", &jetDauVertex_r, &b_jetDauVertex_r);
   fChain->SetBranchAddress("alphaMax_jetDauVertex_r", &alphaMax_jetDauVertex_r, &b_alphaMax_jetDauVertex_r);
   fChain->SetBranchAddress("jetAlphaMax_PV3onPV2", &jetAlphaMax_PV3onPV2, &b_jetAlphaMax_PV3onPV2);
   fChain->SetBranchAddress("jetAlphaMax_PV3onNeu", &jetAlphaMax_PV3onNeu, &b_jetAlphaMax_PV3onNeu);
   fChain->SetBranchAddress("jetAlphaMax_PV3onAll", &jetAlphaMax_PV3onAll, &b_jetAlphaMax_PV3onAll);
   fChain->SetBranchAddress("jetAlphaMax_PV2onNeu", &jetAlphaMax_PV2onNeu, &b_jetAlphaMax_PV2onNeu);
   fChain->SetBranchAddress("jetAlphaMax_PV2onAll", &jetAlphaMax_PV2onAll, &b_jetAlphaMax_PV2onAll);
   fChain->SetBranchAddress("jetAlpha2Max_PV3onPV2", &jetAlpha2Max_PV3onPV2, &b_jetAlpha2Max_PV3onPV2);
   fChain->SetBranchAddress("jetAlpha2Max_PV3onNeu", &jetAlpha2Max_PV3onNeu, &b_jetAlpha2Max_PV3onNeu);
   fChain->SetBranchAddress("jetAlpha2Max_PV3onAll", &jetAlpha2Max_PV3onAll, &b_jetAlpha2Max_PV3onAll);
   fChain->SetBranchAddress("jetAlpha2Max_PV2onNeu", &jetAlpha2Max_PV2onNeu, &b_jetAlpha2Max_PV2onNeu);
   fChain->SetBranchAddress("jetAlpha2Max_PV2onAll", &jetAlpha2Max_PV2onAll, &b_jetAlpha2Max_PV2onAll);
   fChain->SetBranchAddress("jetAlphaD", &jetAlphaD, &b_jetAlphaD);
   fChain->SetBranchAddress("jetAlphaMaxD", &jetAlphaMaxD, &b_jetAlphaMaxD);
   fChain->SetBranchAddress("jetLog10IPSig", &jetLog10IPSig, &b_jetLog10IPSig);
   fChain->SetBranchAddress("jetMedianLog10IPSig", &jetMedianLog10IPSig, &b_jetMedianLog10IPSig);
   fChain->SetBranchAddress("jetSumIP", &jetSumIP, &b_jetSumIP);
   fChain->SetBranchAddress("jetSumIPSig", &jetSumIPSig, &b_jetSumIPSig);
   fChain->SetBranchAddress("jetTrackAngle", &jetTrackAngle, &b_jetTrackAngle);
   fChain->SetBranchAddress("jetLogTrackAngle", &jetLogTrackAngle, &b_jetLogTrackAngle);
   fChain->SetBranchAddress("jetMedianLogTrackAngle", &jetMedianLogTrackAngle, &b_jetMedianLogTrackAngle);
   fChain->SetBranchAddress("jetTotalTrackAngle", &jetTotalTrackAngle, &b_jetTotalTrackAngle);
   fChain->SetBranchAddress("jetTrackPt", &jetTrackPt, &b_jetTrackPt);
   fChain->SetBranchAddress("jetTrackEta", &jetTrackEta, &b_jetTrackEta);
   fChain->SetBranchAddress("jetTrackPhi", &jetTrackPhi, &b_jetTrackPhi);
   fChain->SetBranchAddress("jetTrackPDGID", &jetTrackPDGID, &b_jetTrackPDGID);
   fChain->SetBranchAddress("jetTrackMomPDGID", &jetTrackMomPDGID, &b_jetTrackMomPDGID);
   fChain->SetBranchAddress("jetNConstituents", &jetNConstituents, &b_jetNConstituents);
   fChain->SetBranchAddress("jetPFLooseId", &jetPFLooseId, &b_jetPFLooseId);
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
   fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
   fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
   fChain->SetBranchAddress("jetFiredTrgs", &jetFiredTrgs, &b_jetFiredTrgs);
   fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
   fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
   fChain->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
   fChain->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
   fChain->SetBranchAddress("jetNCH", &jetNCH, &b_jetNCH);
   fChain->SetBranchAddress("jetNNP", &jetNNP, &b_jetNNP);
   fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
   fChain->SetBranchAddress("jetVtxPt", &jetVtxPt, &b_jetVtxPt);
   fChain->SetBranchAddress("jetVtxMass", &jetVtxMass, &b_jetVtxMass);
   fChain->SetBranchAddress("jetVtxNtrks", &jetVtxNtrks, &b_jetVtxNtrks);
   fChain->SetBranchAddress("jetVtx3DVal", &jetVtx3DVal, &b_jetVtx3DVal);
   fChain->SetBranchAddress("jetVtx3DSig", &jetVtx3DSig, &b_jetVtx3DSig);

   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   // MC Only (Hen)
   //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
   jetPartonID = 0;
   jetHadFlvr = 0;
   jetGenJetEn = 0;
   jetGenJetPt = 0;
   jetGenJetEta = 0;
   jetGenJetPhi = 0;
   jetGenPartonID = 0;
   jetGenEn = 0;
   jetGenPt = 0;
   jetGenEta = 0;
   jetGenPhi = 0;
   jetGenPartonMomID = 0;
   jetP4Smear = 0;
   jetP4SmearUp = 0;
   jetP4SmearDo = 0;
   if(isMC){
   fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
   fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetGenJetEn", &jetGenJetEn, &b_jetGenJetEn);
   fChain->SetBranchAddress("jetGenJetPt", &jetGenJetPt, &b_jetGenJetPt);
   fChain->SetBranchAddress("jetGenJetEta", &jetGenJetEta, &b_jetGenJetEta);
   fChain->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi, &b_jetGenJetPhi);
   fChain->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
   fChain->SetBranchAddress("jetGenEn", &jetGenEn, &b_jetGenEn);
   fChain->SetBranchAddress("jetGenPt", &jetGenPt, &b_jetGenPt);
   fChain->SetBranchAddress("jetGenEta", &jetGenEta, &b_jetGenEta);
   fChain->SetBranchAddress("jetGenPhi", &jetGenPhi, &b_jetGenPhi);
   fChain->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
   fChain->SetBranchAddress("jetP4Smear", &jetP4Smear, &b_jetP4Smear);
   fChain->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp, &b_jetP4SmearUp);
   fChain->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo, &b_jetP4SmearDo);
   }

}
