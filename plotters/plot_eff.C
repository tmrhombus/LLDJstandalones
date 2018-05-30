#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TMath.h"


void plot_a_eff(TH1F* h_num, TH1F* h_den, float max, TString name, TFile* f_out){

  TGraphAsymmErrors* gr_eff = new TGraphAsymmErrors();
  gr_eff->SetName("gr_eff_"+name);
  gr_eff->Divide(h_num, h_den, "cl=0.683 b(1,1) mode");

  TH1F* h_eff = (TH1F*)h_num->Clone();
  h_eff->Divide(h_den);
  h_eff->SetName("h_eff_"+name);

  gr_eff->SetLineWidth(2);
  gr_eff->SetMarkerSize(1);
  gr_eff->SetMarkerStyle(8);
  gr_eff->SetMarkerColor(kGreen+1);
  gr_eff->SetLineColor(kGreen+1);

  gr_eff->SetTitle("Mistag rate " + name);
  gr_eff->GetXaxis()->SetTitle("");
  gr_eff->GetYaxis()->SetTitle("Mistag rate");

  TCanvas* c_eff = new TCanvas("c_eff_"+name, "c_eff_"+name, 640, 480);
  gr_eff->Draw("AP");
  gr_eff->GetYaxis()->SetRangeUser(0, max);
  gPad->Update();
  c_eff->Print("gr_eff_"+name+".pdf");

  f_out->cd();
  gr_eff->Write();
  h_num->Write();
  h_den->Write();
  h_eff->Write();
  
}


void plot_eff(TString region){

  //Note: this needs to be generalized to multidimensional histograms

  TFile* f_in  = TFile::Open("fout_"+region+".root", "READ");
  TFile* f_out = TFile::Open("feff_"+region+".root", "RECREATE");

  std::vector<TString> num_name;
  std::vector<TString> den_name;
  std::vector<TString> name;
  std::vector<float> max;

  //Pt
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetPtVar_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetPtVar");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetPtVar");
  max.push_back(0.006);

  /*
  //dR
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetMinDR_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetMinDR");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetMinDR");
  max.push_back(0.01);

  //Eta
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetAbsEta_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetAbsEta");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetAbsEta");
  max.push_back(0.01);

  //Nt
  num_name.push_back("h_Totbkg_mu_"+region+"_AllTags_AODCaloJetNCleanMatchedTracks_Tag0");
  den_name.push_back("h_Totbkg_mu_"+region+"_AllJets_AODCaloJetNCleanMatchedTracks");
  name.push_back("mu_"+region+"_AllJets_AODCaloJetNCleanMatchedTracks");
  max.push_back(0.04);
  */

  for(unsigned int i=0; i<num_name.size(); i++){
    
    TH1F* h_num = (TH1F*)f_in->Get(num_name.at(i));
    TH1F* h_den = (TH1F*)f_in->Get(den_name.at(i));
    
    plot_a_eff(h_num, h_den, max.at(i), name.at(i), f_out);

  }
  
  f_in->Close();
  f_out->Close();

}
