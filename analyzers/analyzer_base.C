#include "analyzer_base.h"

analyzer_base::analyzer_base() 
{
printf("loading\n");
}

analyzer_base::~analyzer_base()
{
}


void analyzer_base::Init(TTree *tree)
 {
 printf(" Initting\n");
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).
 
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);
 
    fChain->SetBranchAddress("vars", &vars_ONZ, &b_vars);
 printf(" done Initting\n");
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
