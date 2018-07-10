#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"

#include <stdlib.h>     /* getenv */

//using namespace std;

void TriggerTurnOnTest( )
{
 // path to_"+region+"histograms.root files
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));
 TString sample = "DY50";
 TString region = "DY";
 TString lep = "mu";
 TString Nname = "Mu1Pt";
 TStrind Dname = "DMu1Pt";
 
 ////TString aversion = "addpuAOD" ;
 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/";
/*  
 TString outname = outpath+"TTOC23DEle1Pt";
 TString name = "DoubleEle:HLT_Ele23Ele12 Turn on vs Ele1Pt: DY Region ";
 //AOD_HLT_Mu17Mu8
 //AOD_HLT_Ele23Ele12
 //TString unit = "";
 TString unit = "  [GeV]";
 TFile *_file0 = TFile::Open(inpath+"DY50_DY_histograms.root");
 TH1F* TTOCNum    = (TH1F*)_file0->Get("h_ele_DY_TTOCEleTrigger23DEle1Pt")->Clone("TTOCNum");
 TH1F* TTOCDenom  = (TH1F*)_file0->Get("h_ele_DY_TTOCEle1Pt")->Clone("TTOCDenom");
*/
 
 TString outname = outpath+"TTOC"+Dname;
 TString name = "DoubleMu:HLT_Mu17Mu8 Turn on vs "+Nname+": "+region+" Region ";
 //AOD_HLT_Mu17Mu8
 //TString unit = "";
 TString unit = "  [GeV]";
 TFile *_file0 = TFile::Open(inpath+sample+"_"+region+"_histograms.root");
 TH1F* TTOCNum    = (TH1F*)_file0->Get("h_"+lep+"_"+region+"_TTOCMuTrigger"+Dname)->Clone("TTOCNum");
 TH1F* TTOCDenom  = (TH1F*)_file0->Get("h_"+lep+"_"+region+"_TTOC"+Nname)->Clone("TTOCDenom");

/* 
 TString outname = outpath+"TTOCDMu1Pt_OffZ";
 TString name = "DoubleMu:HLT_Mu17Mu8 Turn on vs Mu1Pt: OffZ Region ";
 //AOD_HLT_Mu17Mu8
 //TString unit = "";
 TString unit = "  [GeV]";
 TFile *_file0 = TFile::Open(inpath+"DY50_OffZ_histograms.root");
 TH1F* TTOCNum    = (TH1F*)_file0->Get("h_mu_OffZ_TTOCMuTriggerDMu1Pt")->Clone("TTOCNum");
 TH1F* TTOCDenom  = (TH1F*)_file0->Get("h_mu_OffZ_TTOCMu1Pt")->Clone("TTOCDenom");
*/
 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 canvas->Clear();
 canvas->cd();
 TPad *pad1  = new TPad("pad1", "pad1", 0, 0, 1, 1);
 pad1->SetTickx();
 pad1->SetTicky();
 pad1->SetGrid();
 pad1->Draw();
 pad1->cd();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kBird);

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.04);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.04);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 extra->SetTextFont(52);
 
 TText* extra2 = new TText(1,1,"") ;
 extra2->SetTextSize(0.04);
 extra2->SetTextColor(kBlack);
 extra2->SetTextAlign(11);
 extra2->SetTextFont(62);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 
 
  TGraphAsymmErrors* gr_TTOC = new TGraphAsymmErrors();
  gr_TTOC->Divide(TTOCNum, TTOCDenom, "cl=0.683 b(1,1) mode");
  gr_TTOC->Draw();
 
  for(int i = 1; i <=TTOCNum->GetXaxis()->GetNbins()+2; i++){
  
  cout<<"*********************** Position: "  << TTOCNum->GetXaxis()->GetBinCenter(i)  <<endl;
  cout<<"Numerator: "  << TTOCNum->GetBinContent(i)  <<endl;
  cout<<"Denominator: "<< TTOCDenom->GetBinContent(i)<<endl;
  cout<<"Ratio: "      << gr_TTOC->Eval(TTOCNum->GetXaxis()->GetBinCenter(i))<< ",  Numerator/Denominator: "<<TTOCNum->GetBinContent(i)/TTOCDenom->GetBinContent(i)  <<endl;
  //cout<<endl;

  }

  //--Style
  gPad->SetLeftMargin(0.15);
  gr_TTOC->SetLineWidth(2);
  gr_TTOC->SetMarkerSize(1);
  gr_TTOC->SetMarkerStyle(8);
  gr_TTOC->SetMarkerColor(kAzure-2);
  gr_TTOC->SetLineColor(kAzure-2);
  gr_TTOC->SetTitle(name);
  gr_TTOC->GetYaxis()->SetTitleOffset(1.55);
  gr_TTOC->GetXaxis()->SetTitle(TTOCDenom->GetTitle()+unit);
  gr_TTOC->GetYaxis()->SetTitle("Trigger Efficiency");
  //gStyle->SetOptStat(1101);
    gPad->Update();
    gPad->RedrawAxis();


    // save canvas
    //canvas->SaveAs(outname+".png");
    canvas->SaveAs(outname+".pdf");
}
