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
   elePt = 0;
   eleEn = 0;
   eleEta = 0;
   elePhi = 0;
   eleSCEn = 0;
   eleSCEta = 0;
   eleSCPhi = 0;
   eleCharge = 0;
   eleChargeConsistent = 0;
   eleIDbit = 0;
   elePFdBetaIsolationRhoEA = 0;
   elePFdBetaIsolationCHS = 0;
   elePFdBetaIsolationDiff = 0;
   muPt = 0;
   muEn = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muType = 0;
   muIDbit = 0;
   muPassLooseID = 0;
   muPassHipID = 0;
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
   jetCHF = 0;
   jetNHF = 0;
   jetCEF = 0;
   jetNEF = 0;
   jetNCH = 0;
   jetNNP = 0;
   jetMUF = 0;
   jetHFHAE = 0;
   jetHFEME = 0;
   jetNConstituents = 0;
   jetVtxPt = 0;
   jetVtxMass = 0;
   jetVtxNtrks = 0;
   jetVtx3DVal = 0;
   jetVtx3DSig = 0;
   jetCSV2BJetTags = 0;
   jetJetProbabilityBJetTags = 0;
   jetpfCombinedMVAV2BJetTags = 0;
   jetPartonID = 0;
   jetHadFlvr = 0;
   jetPFLooseId = 0;
   jetID = 0;
   jetPUID = 0;
   jetPUFullID = 0;
   jetJECUnc = 0;
   jetP4Smear = 0;
   jetP4SmearUp = 0;
   jetP4SmearDo = 0;
   jetFiredTrgs = 0;
   jetAlphaD = 0;
   jetAlphaMaxD = 0;
   jetSumIP = 0;
   jetSumIPSig = 0;
   jetLog10IPSig = 0;
   jetMedianLog10IPSig = 0;
   jetTrackAngle = 0;
   jetLogTrackAngle = 0;
   jetMedianLogTrackAngle = 0;
   jetTotalTrackAngle = 0;
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
   jetTrackPt = 0;
   jetTrackEta = 0;
   jetTrackPhi = 0;
   jetTrackPDGID = 0;
   jetTrackMomPDGID = 0;
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
   AODCaloJetPt = 0;
   AODCaloJetEta = 0;
   AODCaloJetPhi = 0;
   AODCaloJetAlphaMax = 0;
   AODCaloJetAlphaMax2 = 0;
   AODCaloJetAlphaMaxPrime = 0;
   AODCaloJetAlphaMaxPrime2 = 0;
   AODCaloJetBeta = 0;
   AODCaloJetBeta2 = 0;
   AODCaloJetSumIP = 0;
   AODCaloJetSumIPSig = 0;
   AODCaloJetLog10IPSig = 0;
   AODCaloJetMedianLog10IPSig = 0;
   AODCaloJetTrackAngle = 0;
   AODCaloJetLogTrackAngle = 0;
   AODCaloJetMedianLogTrackAngle = 0;
   AODCaloJetTotalTrackAngle = 0;
   AODPFJetPt = 0;
   AODPFJetEta = 0;
   AODPFJetPhi = 0;
   AODPFJetAlphaMax = 0;
   AODPFJetSumIP = 0;
   AODPFJetSumIPSig = 0;
   AODPFJetLog10IPSig = 0;
   AODPFJetMedianLog10IPSig = 0;
   AODPFJetTrackAngle = 0;
   AODPFJetLogTrackAngle = 0;
   AODPFJetMedianLogTrackAngle = 0;
   AODPFJetTotalTrackAngle = 0;
   AODPFchsJetPt = 0;
   AODPFchsJetEta = 0;
   AODPFchsJetPhi = 0;
   AODPFchsJetAlphaMax = 0;
   AODPFchsJetSumIP = 0;
   AODPFchsJetSumIPSig = 0;
   AODPFchsJetLog10IPSig = 0;
   AODPFchsJetMedianLog10IPSig = 0;
   AODPFchsJetTrackAngle = 0;
   AODPFchsJetLogTrackAngle = 0;
   AODPFchsJetMedianLogTrackAngle = 0;
   AODPFchsJetTotalTrackAngle = 0;
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
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
   fChain->SetBranchAddress("eleIDbit", &eleIDbit, &b_eleIDbit);
   fChain->SetBranchAddress("elePFdBetaIsolationRhoEA", &elePFdBetaIsolationRhoEA, &b_elePFdBetaIsolationRhoEA);
   fChain->SetBranchAddress("elePFdBetaIsolationCHS", &elePFdBetaIsolationCHS, &b_elePFdBetaIsolationCHS);
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
   fChain->SetBranchAddress("muPassHipID", &muPassHipID, &b_muPassHipID);
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
   fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
   fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
   fChain->SetBranchAddress("jetCEF", &jetCEF, &b_jetCEF);
   fChain->SetBranchAddress("jetNEF", &jetNEF, &b_jetNEF);
   fChain->SetBranchAddress("jetNCH", &jetNCH, &b_jetNCH);
   fChain->SetBranchAddress("jetNNP", &jetNNP, &b_jetNNP);
   fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
   fChain->SetBranchAddress("jetHFHAE", &jetHFHAE, &b_jetHFHAE);
   fChain->SetBranchAddress("jetHFEME", &jetHFEME, &b_jetHFEME);
   fChain->SetBranchAddress("jetNConstituents", &jetNConstituents, &b_jetNConstituents);
   fChain->SetBranchAddress("jetVtxPt", &jetVtxPt, &b_jetVtxPt);
   fChain->SetBranchAddress("jetVtxMass", &jetVtxMass, &b_jetVtxMass);
   fChain->SetBranchAddress("jetVtxNtrks", &jetVtxNtrks, &b_jetVtxNtrks);
   fChain->SetBranchAddress("jetVtx3DVal", &jetVtx3DVal, &b_jetVtx3DVal);
   fChain->SetBranchAddress("jetVtx3DSig", &jetVtx3DSig, &b_jetVtx3DSig);
   fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
   fChain->SetBranchAddress("jetJetProbabilityBJetTags", &jetJetProbabilityBJetTags, &b_jetJetProbabilityBJetTags);
   fChain->SetBranchAddress("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags, &b_jetpfCombinedMVAV2BJetTags);
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetPFLooseId", &jetPFLooseId, &b_jetPFLooseId);
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUID", &jetPUID, &b_jetPUID);
   fChain->SetBranchAddress("jetPUFullID", &jetPUFullID, &b_jetPUFullID);
   fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
   fChain->SetBranchAddress("jetP4Smear", &jetP4Smear, &b_jetP4Smear);
   fChain->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp, &b_jetP4SmearUp);
   fChain->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo, &b_jetP4SmearDo);
   fChain->SetBranchAddress("jetFiredTrgs", &jetFiredTrgs, &b_jetFiredTrgs);
   fChain->SetBranchAddress("jetAlphaD", &jetAlphaD, &b_jetAlphaD);
   fChain->SetBranchAddress("jetAlphaMaxD", &jetAlphaMaxD, &b_jetAlphaMaxD);
   fChain->SetBranchAddress("jetSumIP", &jetSumIP, &b_jetSumIP);
   fChain->SetBranchAddress("jetSumIPSig", &jetSumIPSig, &b_jetSumIPSig);
   fChain->SetBranchAddress("jetLog10IPSig", &jetLog10IPSig, &b_jetLog10IPSig);
   fChain->SetBranchAddress("jetMedianLog10IPSig", &jetMedianLog10IPSig, &b_jetMedianLog10IPSig);
   fChain->SetBranchAddress("jetTrackAngle", &jetTrackAngle, &b_jetTrackAngle);
   fChain->SetBranchAddress("jetLogTrackAngle", &jetLogTrackAngle, &b_jetLogTrackAngle);
   fChain->SetBranchAddress("jetMedianLogTrackAngle", &jetMedianLogTrackAngle, &b_jetMedianLogTrackAngle);
   fChain->SetBranchAddress("jetTotalTrackAngle", &jetTotalTrackAngle, &b_jetTotalTrackAngle);
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
   fChain->SetBranchAddress("jetTrackPt", &jetTrackPt, &b_jetTrackPt);
   fChain->SetBranchAddress("jetTrackEta", &jetTrackEta, &b_jetTrackEta);
   fChain->SetBranchAddress("jetTrackPhi", &jetTrackPhi, &b_jetTrackPhi);
   fChain->SetBranchAddress("jetTrackPDGID", &jetTrackPDGID, &b_jetTrackPDGID);
   fChain->SetBranchAddress("jetTrackMomPDGID", &jetTrackMomPDGID, &b_jetTrackMomPDGID);
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
   fChain->SetBranchAddress("AODnCaloJet", &AODnCaloJet, &b_AODnCaloJet);
   fChain->SetBranchAddress("AODCaloJetPt", &AODCaloJetPt, &b_AODCaloJetPt);
   fChain->SetBranchAddress("AODCaloJetEta", &AODCaloJetEta, &b_AODCaloJetEta);
   fChain->SetBranchAddress("AODCaloJetPhi", &AODCaloJetPhi, &b_AODCaloJetPhi);
   fChain->SetBranchAddress("AODCaloJetAlphaMax", &AODCaloJetAlphaMax, &b_AODCaloJetAlphaMax);
   fChain->SetBranchAddress("AODCaloJetAlphaMax2", &AODCaloJetAlphaMax2, &b_AODCaloJetAlphaMax2);
   fChain->SetBranchAddress("AODCaloJetAlphaMaxPrime", &AODCaloJetAlphaMaxPrime, &b_AODCaloJetAlphaMaxPrime);
   fChain->SetBranchAddress("AODCaloJetAlphaMaxPrime2", &AODCaloJetAlphaMaxPrime2, &b_AODCaloJetAlphaMaxPrime2);
   fChain->SetBranchAddress("AODCaloJetBeta", &AODCaloJetBeta, &b_AODCaloJetBeta);
   fChain->SetBranchAddress("AODCaloJetBeta2", &AODCaloJetBeta2, &b_AODCaloJetBeta2);
   fChain->SetBranchAddress("AODCaloJetSumIP", &AODCaloJetSumIP, &b_AODCaloJetSumIP);
   fChain->SetBranchAddress("AODCaloJetSumIPSig", &AODCaloJetSumIPSig, &b_AODCaloJetSumIPSig);
   fChain->SetBranchAddress("AODCaloJetLog10IPSig", &AODCaloJetLog10IPSig, &b_AODCaloJetLog10IPSig);
   fChain->SetBranchAddress("AODCaloJetMedianLog10IPSig", &AODCaloJetMedianLog10IPSig, &b_AODCaloJetMedianLog10IPSig);
   fChain->SetBranchAddress("AODCaloJetTrackAngle", &AODCaloJetTrackAngle, &b_AODCaloJetTrackAngle);
   fChain->SetBranchAddress("AODCaloJetLogTrackAngle", &AODCaloJetLogTrackAngle, &b_AODCaloJetLogTrackAngle);
   fChain->SetBranchAddress("AODCaloJetMedianLogTrackAngle", &AODCaloJetMedianLogTrackAngle, &b_AODCaloJetMedianLogTrackAngle);
   fChain->SetBranchAddress("AODCaloJetTotalTrackAngle", &AODCaloJetTotalTrackAngle, &b_AODCaloJetTotalTrackAngle);
   fChain->SetBranchAddress("AODnPFJet", &AODnPFJet, &b_AODnPFJet);
   fChain->SetBranchAddress("AODPFJetPt", &AODPFJetPt, &b_AODPFJetPt);
   fChain->SetBranchAddress("AODPFJetEta", &AODPFJetEta, &b_AODPFJetEta);
   fChain->SetBranchAddress("AODPFJetPhi", &AODPFJetPhi, &b_AODPFJetPhi);
   fChain->SetBranchAddress("AODPFJetAlphaMax", &AODPFJetAlphaMax, &b_AODPFJetAlphaMax);
   fChain->SetBranchAddress("AODPFJetSumIP", &AODPFJetSumIP, &b_AODPFJetSumIP);
   fChain->SetBranchAddress("AODPFJetSumIPSig", &AODPFJetSumIPSig, &b_AODPFJetSumIPSig);
   fChain->SetBranchAddress("AODPFJetLog10IPSig", &AODPFJetLog10IPSig, &b_AODPFJetLog10IPSig);
   fChain->SetBranchAddress("AODPFJetMedianLog10IPSig", &AODPFJetMedianLog10IPSig, &b_AODPFJetMedianLog10IPSig);
   fChain->SetBranchAddress("AODPFJetTrackAngle", &AODPFJetTrackAngle, &b_AODPFJetTrackAngle);
   fChain->SetBranchAddress("AODPFJetLogTrackAngle", &AODPFJetLogTrackAngle, &b_AODPFJetLogTrackAngle);
   fChain->SetBranchAddress("AODPFJetMedianLogTrackAngle", &AODPFJetMedianLogTrackAngle, &b_AODPFJetMedianLogTrackAngle);
   fChain->SetBranchAddress("AODPFJetTotalTrackAngle", &AODPFJetTotalTrackAngle, &b_AODPFJetTotalTrackAngle);
   fChain->SetBranchAddress("AODnPFchsJet", &AODnPFchsJet, &b_AODnPFchsJet);
   fChain->SetBranchAddress("AODPFchsJetPt", &AODPFchsJetPt, &b_AODPFchsJetPt);
   fChain->SetBranchAddress("AODPFchsJetEta", &AODPFchsJetEta, &b_AODPFchsJetEta);
   fChain->SetBranchAddress("AODPFchsJetPhi", &AODPFchsJetPhi, &b_AODPFchsJetPhi);
   fChain->SetBranchAddress("AODPFchsJetAlphaMax", &AODPFchsJetAlphaMax, &b_AODPFchsJetAlphaMax);
   fChain->SetBranchAddress("AODPFchsJetSumIP", &AODPFchsJetSumIP, &b_AODPFchsJetSumIP);
   fChain->SetBranchAddress("AODPFchsJetSumIPSig", &AODPFchsJetSumIPSig, &b_AODPFchsJetSumIPSig);
   fChain->SetBranchAddress("AODPFchsJetLog10IPSig", &AODPFchsJetLog10IPSig, &b_AODPFchsJetLog10IPSig);
   fChain->SetBranchAddress("AODPFchsJetMedianLog10IPSig", &AODPFchsJetMedianLog10IPSig, &b_AODPFchsJetMedianLog10IPSig);
   fChain->SetBranchAddress("AODPFchsJetTrackAngle", &AODPFchsJetTrackAngle, &b_AODPFchsJetTrackAngle);
   fChain->SetBranchAddress("AODPFchsJetLogTrackAngle", &AODPFchsJetLogTrackAngle, &b_AODPFchsJetLogTrackAngle);
   fChain->SetBranchAddress("AODPFchsJetMedianLogTrackAngle", &AODPFchsJetMedianLogTrackAngle, &b_AODPFchsJetMedianLogTrackAngle);
   fChain->SetBranchAddress("AODPFchsJetTotalTrackAngle", &AODPFchsJetTotalTrackAngle, &b_AODPFchsJetTotalTrackAngle);
   fChain->SetBranchAddress("genMET", &genMET, &b_genMET);
   fChain->SetBranchAddress("genMETPhi", &genMETPhi, &b_genMETPhi);
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


}
