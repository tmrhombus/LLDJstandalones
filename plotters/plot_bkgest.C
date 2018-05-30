#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
//#include "TRatioPlot.h"
#include "TPad.h"

void print(TH1F* h){

  cout << h->GetName() << endl;
  for(int i=1; i<=h->GetNbinsX(); i++){
    cout << h->GetBinContent(i) << endl;
  }

}

void plot_bkgest(TString bkg_est_name = "h_bkgest_pteta"){
  
  //TString filename_bkg = "/uscms/home/kreis/workspace/LLDJ/analyzer/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/plotters/fout_ZH.root";
  TString filename_bkgest = "fout_ZH_bkgest.root";
  TString filename_bkg = "fout_ZH.root";

  TFile* file_bkg = TFile::Open(filename_bkg, "READ");
  TFile* file_bkgest = TFile::Open(filename_bkgest, "READ");

  TH1F* h_Totbkg = (TH1F*)file_bkg->Get("h_mu_ZH_nSelectedAODCaloJetTag");
  TH1F* h_Totbkg_bkgest = (TH1F*)file_bkgest->Get(bkg_est_name);

  //normalize
  //h_Totbkg->Scale(1/h_Totbkg->Integral(2,-1));
  //h_Totbkg_bkgest->Scale(1/h_Totbkg_bkgest->Integral(2,-1));

  print(h_Totbkg);
  print(h_Totbkg_bkgest);

  h_Totbkg->SetLineWidth(2);
  h_Totbkg_bkgest->SetLineWidth(2);

  h_Totbkg->SetLineColor(kBlack);
  h_Totbkg_bkgest->SetLineColor(kRed);
  
  //TRatioPlot* rp = new TRatioPlot(h_Totbkg_bkgest, h_Totbkg);

  TCanvas c("c", "c", 640, 480);
  gPad->SetLogy();
  h_Totbkg->GetYaxis()->SetRangeUser(1e-7,50000);
  

  h_Totbkg->Draw("HIST E");
  h_Totbkg_bkgest->Draw("HIST E SAME");
  //rp->Draw();
  c.SaveAs("rp.pdf");
  

}
