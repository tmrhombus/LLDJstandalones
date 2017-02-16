#define analyzer_signal_cxx
#include "analyzer_signal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void analyzer_signal::Loop(TString outfilename, Bool_t isMC,
                       Double_t lumi, Double_t nrEvents,
                       Double_t crossSec)
{

 if (fChain == 0) return;

 Long64_t nentries = fChain->GetEntriesFast();
 nentries = 5000; // for testing purposes

 // start looping over entries
 Long64_t nbytes = 0, nb = 0;
 for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;

  // make event weight
  event_weight = makeEventWeight(crossSec,lumi,nrEvents,isMC);

  printf("Event: %0.f  %0.llu weight: %0.4f \n",vars_EVENT,jentry,event_weight);

 } // end loop over entries

 // make outfile and save histograms
 TFile *outfile = new TFile(outfilename,"RECREATE");
 outfile->cd();
 //for(unsigned int i=0; i<ptbinnames.size(); ++i){
 // for(unsigned int j=0; j<sysbinnames.size(); ++j){
 //  WriteHistograms(i,j);
 // }
 //}
 //WriteHistograms();
 outfile->Close();

} // end analyzer_signal::Loop()

analyzer_signal::analyzer_signal()
{
}

analyzer_signal::~analyzer_signal()
{
}
