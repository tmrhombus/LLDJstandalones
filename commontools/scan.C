
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

