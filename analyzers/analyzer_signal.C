#define analyzer_signal_cxx
#include "analyzer_signal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void analyzer_signal::Loop()
{

 if (fChain == 0) return;

 Long64_t nentries = fChain->GetEntriesFast();
 nentries = 5000; // for testing purposes

 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;

  printf("Event: %f\n",vars_EVENT);

 } // loop over entries


}

analyzer_signal::analyzer_signal(){
}

analyzer_signal::~analyzer_signal()
{
}
