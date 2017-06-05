
TFile *thefile = TFile::Open("lldjntuple_mc_310.root");

TFile *thefile = TFile::Open("lldjntuple_mc_MS40_cTauS0p05.root");

TTree* thetree = (TTree*)thefile->Get("lldjNtuple/EventTree");

//TString cuts="event==472257123";
TString cuts="";

TString columns="event:phoEt: phoEta: phoPhi";
TString columns="event:elePt: eleEta: elePhi";
TString columns="event:muPt: muEta: muPhi   ";
TString columns="event:jetPt: jetEta: jetPhi";

TString columns="event:phoEt: phoEta: phoPhi : event:elePt: eleEta: elePhi : event:muPt: muEta: muPhi : event: jetPt: jetEta: jetPhi";

((TTreePlayer*)(thetree->GetPlayer()))->SetScanRedirect(true);

((TTreePlayer*)(thetree->GetPlayer()))->SetScanFileName("scanoutput.txt");

//thetree->Scan(columns,cuts)
thetree->Scan(columns,cuts,"colsize=10");

 
***********************************************************************************************************************************************************************************************************************
*    Row   * Instance *     event *     phoEt *    phoEta *   phoPhi  *     event *     elePt *    eleEta *   elePhi  *     event *      muPt *     muEta *    muPhi  *     event *     jetPt *    jetEta *    jetPhi *
***********************************************************************************************************************************************************************************************************************
*    22593 *        0 * 472257123 * 48.207160 * -2.254289 * -2.607473 * 472257123 * 48.289077 * -2.266778 * -2.611328 * 472257123 *           *           *           * 472257123 * 55.258148 * -2.266778 * -2.611328 *
*    22593 *        1 * 472257123 * 32.692096 * -1.249681 * 0.3297082 * 472257123 * 33.224926 * -1.249957 * 0.3126917 * 472257123 *           *           *           * 472257123 * 38.951274 * -1.251235 * 0.3094213 *
*    22593 *        2 * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 * 25.614477 * -3.249002 * -1.522386 *
*    22593 *        3 * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 * 22.357919 * 3.0829284 * -2.672019 *
*    22593 *        4 * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 * 19.386655 * 3.9279768 * 2.4071373 *
*    22593 *        5 * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 *           *           *           * 472257123 * 18.603103 * -2.624485 * 2.0727469 *
***********************************************************************************************************************************************************************************************************************
==> 6 selected entries
IncrementalExecutor::executeFunction: symbol '_ZN5cling10printValueEPKx' unresolved while linking [cling interface function]!
You are probably missing the definition of cling::printValue(long long const*)
Maybe you need to load the corresponding shared library?
(Long64_t) Error in ValuePrinter: missing output string.

 
 




// Mu
TString columns = "HLT_IsoMu24_eta2p1_v_fired:nrGoodMu:nrVetoMu:nrVetoEle:nrGoodJets:nrFwdJets:mt_goodMuon:goodJ1_CSV:goodJ2_CSV"; 
// Ele
//TString columns = "EVENT:goodEle_pt_vec:goodEle_eta_vec:goodEle_phi_vec";
TString columns = "HLT_Ele27_WP80_fired:nrGoodEle:goodEle_Iso03_vec[0]:nrVetoEle:nrVetoMu:nrGoodJets:nrFwdJets:mt_goodElectron:goodJ1_CSV:goodJ2_CSV";


// Wbb Mu
TString cuts = "(HLT_IsoMu24_eta2p1_v_fired && nrGoodMu==1 && nrVetoMu<=1 && nrVetoEle==0 && nrGoodJets==2 && nrFwdJets==0)"; 
// Wbb Ele
TString cuts = "(HLT_Ele27_WP80_fired && nrGoodEle==1 && goodEle_Iso03_vec[0]<0.10 && nrVetoEle<=1 && nrVetoMu==0 && nrGoodJets==2 && nrFwdJets==0)"; 
// no cut
TString cuts = ""; 

TTree* tree0 = _file0.Get("muEleEventTree/eventTree");

((TTreePlayer*)(tree0->GetPlayer()))->SetScanRedirect(true);
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("Wbb4F_skimmed_wjj_mu.txt");
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("Wbb4F_skimmed_wjj_ele.txt");
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("Wbb4F_isItFull_wjj_mu.txt");
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("Wbb4F_isItFull_wjj_ele.txt");

((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("New_Mu.txt");
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("New_Ele.txt");
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("Old_Mu.txt");
((TTreePlayer*)(tree0->GetPlayer()))->SetScanFileName("Old_Ele.txt");

tree0->Scan(columns,cuts,"colsize=10");




