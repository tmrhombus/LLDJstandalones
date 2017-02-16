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
