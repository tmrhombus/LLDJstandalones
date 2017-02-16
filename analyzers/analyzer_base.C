#include "analyzer_base.h"

analyzer_base::analyzer_base() 
{
}

analyzer_base::~analyzer_base()
{
}


void analyzer_base::Init(TTree *tree)
 {
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
 
  fChain->SetBranchAddress("vars", &vars_ONZ, &b_vars);
 }

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
                                        Double_t nrEvents,
                                        Bool_t isMC)
{
  // 1.0 for real data
  event_weight=1.0;
  Double_t crossSecScl = crossSec;
  if(isMC){ event_weight=lumi*crossSecScl/nrEvents; }
  printf("isMC: %i lumi: %0.9f crossSec: %0.9f nrEvents: %0.9f",isMC,lumi,crossSecScl,nrEvents);
  printf("  event_weight: %0.9f\n",event_weight);

  return event_weight;
}
