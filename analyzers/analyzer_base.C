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

   // Set object pointers
   phoPt = 0;
   phoEn = 0;
   phoEta = 0;
   phoPhi = 0;
   phoSCEn = 0;
   phoSCEta = 0;
   phoSCPhi = 0;
   phoIDbit = 0;
   phoIDMVA = 0;
   phoObjPFChIso = 0;
   phoObjPFPhoIso = 0;
   phoObjPFNeuIso = 0;
   phoObjPFChWorstIso = 0;
   phoMapPFChIso = 0;
   phoMapPFPhoIso = 0;
   phoMapPFNeuIso = 0;
   phoMapPFChWorstIso = 0;
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
   slimmedJetPt = 0;
   slimmedJetEn = 0;
   slimmedJetEta = 0;
   slimmedJetPhi = 0;
   slimmedJetRawPt = 0;
   slimmedJetRawEn = 0;
   slimmedJetMt = 0;
   slimmedJetArea = 0;
   slimmedJetLeadTrackPID = 0;
   slimmedJetLeadTrackPt = 0;
   slimmedJetLeadTrackEta = 0;
   slimmedJetLeadTrackPhi = 0;
   slimmedJetLepTrackPID = 0;
   slimmedJetLepTrackPt = 0;
   slimmedJetLepTrackEta = 0;
   slimmedJetLepTrackPhi = 0;
   slimmedJetCHF = 0;
   slimmedJetNHF = 0;
   slimmedJetCEF = 0;
   slimmedJetNEF = 0;
   slimmedJetNCH = 0;
   slimmedJetNNP = 0;
   slimmedJetMUF = 0;
   slimmedJetHFHAE = 0;
   slimmedJetHFEME = 0;
   slimmedJetNConstituents = 0;
   slimmedJetVtxPt = 0;
   slimmedJetVtxMass = 0;
   slimmedJetVtxNtrks = 0;
   slimmedJetVtx3DVal = 0;
   slimmedJetVtx3DSig = 0;
   slimmedJetCSV2BJetTags = 0;
   slimmedJetJetProbabilityBJetTags = 0;
   slimmedJetpfCombinedMVAV2BJetTags = 0;
   slimmedJetPartonID = 0;
   slimmedJetHadFlvr = 0;
   slimmedJetPFLooseId = 0;
   slimmedJetID = 0;
   slimmedJetPUID = 0;
   slimmedJetPUFullID = 0;
   slimmedJetJECUnc = 0;
   slimmedJetP4Smear = 0;
   slimmedJetP4SmearUp = 0;
   slimmedJetP4SmearDo = 0;
   slimmedJetFiredTrgs = 0;
   slimmedJetAlphaD = 0;
   slimmedJetAlphaMaxD = 0;
   slimmedJetSumIP = 0;
   slimmedJetSumIPSig = 0;
   slimmedJetMedianLog10IPSig = 0;
   slimmedJetTrackAngle = 0;
   slimmedJetLogTrackAngle = 0;
   slimmedJetMedianLog10TrackAngle = 0;
   slimmedJetTotalTrackAngle = 0;
   slimmedJetDauVertex_x = 0;
   slimmedJetDauVertex_y = 0;
   slimmedJetDauVertex_z = 0;
   slimmedJetDauVertex_r = 0;
   slimmedJetAlphaMax_PV3onPV2 = 0;
   slimmedJetAlphaMax_PV3onChg = 0;
   slimmedJetAlphaMax_PV3onAll = 0;
   slimmedJetAlphaMax_PV2onChg = 0;
   slimmedJetAlphaMax_PV2onAll = 0;
   slimmedJetAlpha2Max_PV3onPV2 = 0;
   slimmedJetAlpha2Max_PV3onChg = 0;
   slimmedJetAlpha2Max_PV3onAll = 0;
   slimmedJetAlpha2Max_PV2onChg = 0;
   slimmedJetAlpha2Max_PV2onAll = 0;
   slimmedJetTrackPt = 0;
   slimmedJetTrackEta = 0;
   slimmedJetTrackPhi = 0;
   slimmedJetTrackPDGID = 0;
   slimmedJetTrackMomPDGID = 0;
   slimmedJetGenJetEn = 0;
   slimmedJetGenJetPt = 0;
   slimmedJetGenJetEta = 0;
   slimmedJetGenJetPhi = 0;
   slimmedJetGenPartonID = 0;
   slimmedJetGenEn = 0;
   slimmedJetGenPt = 0;
   slimmedJetGenEta = 0;
   slimmedJetGenPhi = 0;
   slimmedJetGenPartonMomID = 0;
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
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoPt", &phoPt, &b_phoPt);
   fChain->SetBranchAddress("phoEn", &phoEn, &b_phoEn);
   fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoSCEn", &phoSCEn, &b_phoSCEn);
   fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
   fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
   fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
   fChain->SetBranchAddress("phoIDMVA", &phoIDMVA, &b_phoIDMVA);
   fChain->SetBranchAddress("phoObjPFChIso", &phoObjPFChIso, &b_phoObjPFChIso);
   fChain->SetBranchAddress("phoObjPFPhoIso", &phoObjPFPhoIso, &b_phoObjPFPhoIso);
   fChain->SetBranchAddress("phoObjPFNeuIso", &phoObjPFNeuIso, &b_phoObjPFNeuIso);
   fChain->SetBranchAddress("phoObjPFChWorstIso", &phoObjPFChWorstIso, &b_phoObjPFChWorstIso);
   fChain->SetBranchAddress("phoMapPFChIso", &phoMapPFChIso, &b_phoMapPFChIso);
   fChain->SetBranchAddress("phoMapPFPhoIso", &phoMapPFPhoIso, &b_phoMapPFPhoIso);
   fChain->SetBranchAddress("phoMapPFNeuIso", &phoMapPFNeuIso, &b_phoMapPFNeuIso);
   fChain->SetBranchAddress("phoMapPFChWorstIso", &phoMapPFChWorstIso, &b_phoMapPFChWorstIso);
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
   fChain->SetBranchAddress("nSlimmedJets", &nSlimmedJets, &b_nSlimmedJets);
   fChain->SetBranchAddress("slimmedJetPt", &slimmedJetPt, &b_slimmedJetPt);
   fChain->SetBranchAddress("slimmedJetEn", &slimmedJetEn, &b_slimmedJetEn);
   fChain->SetBranchAddress("slimmedJetEta", &slimmedJetEta, &b_slimmedJetEta);
   fChain->SetBranchAddress("slimmedJetPhi", &slimmedJetPhi, &b_slimmedJetPhi);
   fChain->SetBranchAddress("slimmedJetRawPt", &slimmedJetRawPt, &b_slimmedJetRawPt);
   fChain->SetBranchAddress("slimmedJetRawEn", &slimmedJetRawEn, &b_slimmedJetRawEn);
   fChain->SetBranchAddress("slimmedJetMt", &slimmedJetMt, &b_slimmedJetMt);
   fChain->SetBranchAddress("slimmedJetArea", &slimmedJetArea, &b_slimmedJetArea);
   fChain->SetBranchAddress("slimmedJetLeadTrackPID", &slimmedJetLeadTrackPID, &b_slimmedJetLeadTrackPID);
   fChain->SetBranchAddress("slimmedJetLeadTrackPt", &slimmedJetLeadTrackPt, &b_slimmedJetLeadTrackPt);
   fChain->SetBranchAddress("slimmedJetLeadTrackEta", &slimmedJetLeadTrackEta, &b_slimmedJetLeadTrackEta);
   fChain->SetBranchAddress("slimmedJetLeadTrackPhi", &slimmedJetLeadTrackPhi, &b_slimmedJetLeadTrackPhi);
   fChain->SetBranchAddress("slimmedJetLepTrackPID", &slimmedJetLepTrackPID, &b_slimmedJetLepTrackPID);
   fChain->SetBranchAddress("slimmedJetLepTrackPt", &slimmedJetLepTrackPt, &b_slimmedJetLepTrackPt);
   fChain->SetBranchAddress("slimmedJetLepTrackEta", &slimmedJetLepTrackEta, &b_slimmedJetLepTrackEta);
   fChain->SetBranchAddress("slimmedJetLepTrackPhi", &slimmedJetLepTrackPhi, &b_slimmedJetLepTrackPhi);
   fChain->SetBranchAddress("slimmedJetCHF", &slimmedJetCHF, &b_slimmedJetCHF);
   fChain->SetBranchAddress("slimmedJetNHF", &slimmedJetNHF, &b_slimmedJetNHF);
   fChain->SetBranchAddress("slimmedJetCEF", &slimmedJetCEF, &b_slimmedJetCEF);
   fChain->SetBranchAddress("slimmedJetNEF", &slimmedJetNEF, &b_slimmedJetNEF);
   fChain->SetBranchAddress("slimmedJetNCH", &slimmedJetNCH, &b_slimmedJetNCH);
   fChain->SetBranchAddress("slimmedJetNNP", &slimmedJetNNP, &b_slimmedJetNNP);
   fChain->SetBranchAddress("slimmedJetMUF", &slimmedJetMUF, &b_slimmedJetMUF);
   fChain->SetBranchAddress("slimmedJetHFHAE", &slimmedJetHFHAE, &b_slimmedJetHFHAE);
   fChain->SetBranchAddress("slimmedJetHFEME", &slimmedJetHFEME, &b_slimmedJetHFEME);
   fChain->SetBranchAddress("slimmedJetNConstituents", &slimmedJetNConstituents, &b_slimmedJetNConstituents);
   fChain->SetBranchAddress("slimmedJetVtxPt", &slimmedJetVtxPt, &b_slimmedJetVtxPt);
   fChain->SetBranchAddress("slimmedJetVtxMass", &slimmedJetVtxMass, &b_slimmedJetVtxMass);
   fChain->SetBranchAddress("slimmedJetVtxNtrks", &slimmedJetVtxNtrks, &b_slimmedJetVtxNtrks);
   fChain->SetBranchAddress("slimmedJetVtx3DVal", &slimmedJetVtx3DVal, &b_slimmedJetVtx3DVal);
   fChain->SetBranchAddress("slimmedJetVtx3DSig", &slimmedJetVtx3DSig, &b_slimmedJetVtx3DSig);
   fChain->SetBranchAddress("slimmedJetCSV2BJetTags", &slimmedJetCSV2BJetTags, &b_slimmedJetCSV2BJetTags);
   fChain->SetBranchAddress("slimmedJetJetProbabilityBJetTags", &slimmedJetJetProbabilityBJetTags, &b_slimmedJetJetProbabilityBJetTags);
   fChain->SetBranchAddress("slimmedJetpfCombinedMVAV2BJetTags", &slimmedJetpfCombinedMVAV2BJetTags, &b_slimmedJetpfCombinedMVAV2BJetTags);
   fChain->SetBranchAddress("slimmedJetPartonID", &slimmedJetPartonID, &b_slimmedJetPartonID);
   fChain->SetBranchAddress("slimmedJetHadFlvr", &slimmedJetHadFlvr, &b_slimmedJetHadFlvr);
   fChain->SetBranchAddress("slimmedJetPFLooseId", &slimmedJetPFLooseId, &b_slimmedJetPFLooseId);
   fChain->SetBranchAddress("slimmedJetID", &slimmedJetID, &b_slimmedJetID);
   fChain->SetBranchAddress("slimmedJetPUID", &slimmedJetPUID, &b_slimmedJetPUID);
   fChain->SetBranchAddress("slimmedJetPUFullID", &slimmedJetPUFullID, &b_slimmedJetPUFullID);
   fChain->SetBranchAddress("slimmedJetJECUnc", &slimmedJetJECUnc, &b_slimmedJetJECUnc);
   fChain->SetBranchAddress("slimmedJetP4Smear", &slimmedJetP4Smear, &b_slimmedJetP4Smear);
   fChain->SetBranchAddress("slimmedJetP4SmearUp", &slimmedJetP4SmearUp, &b_slimmedJetP4SmearUp);
   fChain->SetBranchAddress("slimmedJetP4SmearDo", &slimmedJetP4SmearDo, &b_slimmedJetP4SmearDo);
   fChain->SetBranchAddress("slimmedJetFiredTrgs", &slimmedJetFiredTrgs, &b_slimmedJetFiredTrgs);
   fChain->SetBranchAddress("slimmedJetAlphaD", &slimmedJetAlphaD, &b_slimmedJetAlphaD);
   fChain->SetBranchAddress("slimmedJetAlphaMaxD", &slimmedJetAlphaMaxD, &b_slimmedJetAlphaMaxD);
   fChain->SetBranchAddress("slimmedJetSumIP", &slimmedJetSumIP, &b_slimmedJetSumIP);
   fChain->SetBranchAddress("slimmedJetSumIPSig", &slimmedJetSumIPSig, &b_slimmedJetSumIPSig);
   fChain->SetBranchAddress("slimmedJetMedianLog10IPSig", &slimmedJetMedianLog10IPSig, &b_slimmedJetMedianLog10IPSig);
   fChain->SetBranchAddress("slimmedJetTrackAngle", &slimmedJetTrackAngle, &b_slimmedJetTrackAngle);
   fChain->SetBranchAddress("slimmedJetLogTrackAngle", &slimmedJetLogTrackAngle, &b_slimmedJetLogTrackAngle);
   fChain->SetBranchAddress("slimmedJetMedianLog10TrackAngle", &slimmedJetMedianLog10TrackAngle, &b_slimmedJetMedianLog10TrackAngle);
   fChain->SetBranchAddress("slimmedJetTotalTrackAngle", &slimmedJetTotalTrackAngle, &b_slimmedJetTotalTrackAngle);
   fChain->SetBranchAddress("slimmedJetDauVertex_x", &slimmedJetDauVertex_x, &b_slimmedJetDauVertex_x);
   fChain->SetBranchAddress("slimmedJetDauVertex_y", &slimmedJetDauVertex_y, &b_slimmedJetDauVertex_y);
   fChain->SetBranchAddress("slimmedJetDauVertex_z", &slimmedJetDauVertex_z, &b_slimmedJetDauVertex_z);
   fChain->SetBranchAddress("slimmedJetDauVertex_r", &slimmedJetDauVertex_r, &b_slimmedJetDauVertex_r);
   fChain->SetBranchAddress("slimmedJetAlphaMax_PV3onPV2", &slimmedJetAlphaMax_PV3onPV2, &b_slimmedJetAlphaMax_PV3onPV2);
   fChain->SetBranchAddress("slimmedJetAlphaMax_PV3onChg", &slimmedJetAlphaMax_PV3onChg, &b_slimmedJetAlphaMax_PV3onChg);
   fChain->SetBranchAddress("slimmedJetAlphaMax_PV3onAll", &slimmedJetAlphaMax_PV3onAll, &b_slimmedJetAlphaMax_PV3onAll);
   fChain->SetBranchAddress("slimmedJetAlphaMax_PV2onChg", &slimmedJetAlphaMax_PV2onChg, &b_slimmedJetAlphaMax_PV2onChg);
   fChain->SetBranchAddress("slimmedJetAlphaMax_PV2onAll", &slimmedJetAlphaMax_PV2onAll, &b_slimmedJetAlphaMax_PV2onAll);
   fChain->SetBranchAddress("slimmedJetAlpha2Max_PV3onPV2", &slimmedJetAlpha2Max_PV3onPV2, &b_slimmedJetAlpha2Max_PV3onPV2);
   fChain->SetBranchAddress("slimmedJetAlpha2Max_PV3onChg", &slimmedJetAlpha2Max_PV3onChg, &b_slimmedJetAlpha2Max_PV3onChg);
   fChain->SetBranchAddress("slimmedJetAlpha2Max_PV3onAll", &slimmedJetAlpha2Max_PV3onAll, &b_slimmedJetAlpha2Max_PV3onAll);
   fChain->SetBranchAddress("slimmedJetAlpha2Max_PV2onChg", &slimmedJetAlpha2Max_PV2onChg, &b_slimmedJetAlpha2Max_PV2onChg);
   fChain->SetBranchAddress("slimmedJetAlpha2Max_PV2onAll", &slimmedJetAlpha2Max_PV2onAll, &b_slimmedJetAlpha2Max_PV2onAll);
   fChain->SetBranchAddress("slimmedJetTrackPt", &slimmedJetTrackPt, &b_slimmedJetTrackPt);
   fChain->SetBranchAddress("slimmedJetTrackEta", &slimmedJetTrackEta, &b_slimmedJetTrackEta);
   fChain->SetBranchAddress("slimmedJetTrackPhi", &slimmedJetTrackPhi, &b_slimmedJetTrackPhi);
   fChain->SetBranchAddress("slimmedJetTrackPDGID", &slimmedJetTrackPDGID, &b_slimmedJetTrackPDGID);
   fChain->SetBranchAddress("slimmedJetTrackMomPDGID", &slimmedJetTrackMomPDGID, &b_slimmedJetTrackMomPDGID);
   fChain->SetBranchAddress("slimmedJetGenJetEn", &slimmedJetGenJetEn, &b_slimmedJetGenJetEn);
   fChain->SetBranchAddress("slimmedJetGenJetPt", &slimmedJetGenJetPt, &b_slimmedJetGenJetPt);
   fChain->SetBranchAddress("slimmedJetGenJetEta", &slimmedJetGenJetEta, &b_slimmedJetGenJetEta);
   fChain->SetBranchAddress("slimmedJetGenJetPhi", &slimmedJetGenJetPhi, &b_slimmedJetGenJetPhi);
   fChain->SetBranchAddress("slimmedJetGenPartonID", &slimmedJetGenPartonID, &b_slimmedJetGenPartonID);
   fChain->SetBranchAddress("slimmedJetGenEn", &slimmedJetGenEn, &b_slimmedJetGenEn);
   fChain->SetBranchAddress("slimmedJetGenPt", &slimmedJetGenPt, &b_slimmedJetGenPt);
   fChain->SetBranchAddress("slimmedJetGenEta", &slimmedJetGenEta, &b_slimmedJetGenEta);
   fChain->SetBranchAddress("slimmedJetGenPhi", &slimmedJetGenPhi, &b_slimmedJetGenPhi);
   fChain->SetBranchAddress("slimmedJetGenPartonMomID", &slimmedJetGenPartonMomID, &b_slimmedJetGenPartonMomID);
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
