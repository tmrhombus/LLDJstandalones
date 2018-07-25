#include <iostream>
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TText.h"
#include "TFile.h"
#include <string>

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
 //TString Nname1 = "Mu1Pt";
 //TString Dname1 = "DMu1Pt";
 //TString Nname2 = "Mu2Pt";
 //TString Dname2 = "DMu2Pt";
 //histograms to make
 std::vector<TString> Nname;
 std::vector<TString> Dname;
 TString lepton;
 //for leptons
 int i = 1;
 if(i ==1){
 lepton = "Mu";
 Nname.push_back("DMu1Pt");
 Dname.push_back("Mu1Pt");
 Nname.push_back("DMu2Pt");
 Dname.push_back("Mu2Pt");
 Nname.push_back("DMu2Eta");
 Dname.push_back("Mu1Eta");
 Nname.push_back("DMu1Eta");
 Dname.push_back("Mu2Eta");
 }
 else{
 lepton = "Ele"; 
 Nname.push_back("23DEle1Pt");
 Dname.push_back("Ele1Pt");
 Nname.push_back("23DEle2Pt");
 Dname.push_back("Ele2Pt");
 Nname.push_back("23DEle1Eta");
 Dname.push_back("Ele1Eta");
 Nname.push_back("23DEle2Eta");
 Dname.push_back("Ele2Eta");
 }
 // lepton flavor
 std::vector<TString> lep;
 lep.clear();
 lep.push_back("ele"); 
 lep.push_back("mu");  
 
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
 
 TGraphAsymmErrors* gr_TTOC = new TGraphAsymmErrors();
 TH1F* TTOCDenom;
 TH1F* TTOCNum;
 TString unit;
 TString name;
 TFile *_file0 = TFile::Open(inpath+sample+"_"+region+"_histograms.root");
   TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 
 for (int j=0; j<Nname.size(); j++){
   if (i==1)name = "DoubleMu:HLT_Mu17Mu8 Turn on vs "    +Nname[j]+": "+region+" Region ";
   else     name = "DoubleEle:HLT_Ele23Ele12 Turn on vs "+Nname[j]+": "+region+" Region ";
   cout << "Plotting: "<<name<<endl;
   if( Dname[j].Contains("Eta") )  {unit = "";         }//cout <<"no Pt"<<endl;}
   else                            {unit = "  [GeV]";  }//cout <<"   Pt"<<endl;}
   TString outname = outpath+"TTOC"+Dname[j];
   TTOCNum    = (TH1F*)_file0->Get("h_"+lep[i]+"_"+region+"_TTOC"+lepton+"Trigger"+Nname[j])->Clone("TTOCNum");
   TTOCDenom  = (TH1F*)_file0->Get("h_"+lep[i]+"_"+region+"_TTOC"+Dname[j])->Clone("TTOCDenom");

   // make canvas and text
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

  gr_TTOC->Divide(TTOCNum, TTOCDenom, "cl=0.683 b(1,1) mode");
  gr_TTOC->Draw();

  /*
  float weight;
  TH2F* h2_TTOC = new TH2F("Mu1vsMu2", "Mu1vsMu2", 33,0,99, 33,0,99);
  for(  int i = 1; i <= TTOCNum1->GetXaxis()->GetNbins(); i++){
    for(int j = 1; j <= TTOCNum1->GetXaxis()->GetNbins(); j++){
      weight = gr_TTOC1->Eval(TTOCNum1->GetXaxis()->GetBinCenter(i)) + gr_TTOC2->Eval(TTOCNum2->GetXaxis()->GetBinCenter(j));
      if(TTOCNum1->GetBinContent(i) == 0 && TTOCDenom1->GetBinContent(i) == 0) weight = 0;
      if(TTOCNum2->GetBinContent(i) == 0 && TTOCDenom2->GetBinContent(i) == 0) weight = 0;
      cout <<"i: "<<i<<", j: "<<j<<",   x: "<<gr_TTOC1->Eval(TTOCNum1->GetXaxis()->GetBinCenter(i))<<",   y: "<<gr_TTOC2->Eval(TTOCNum2->GetXaxis()->GetBinCenter(j))<<",   weight: "<< weight<<endl;
      h2_TTOC->Fill(TTOCNum1->GetXaxis()->GetBinCenter(i),TTOCNum2->GetXaxis()->GetBinCenter(j), weight);
    }
  }
  h2_TTOC->Draw("COLZ");
  */ 
  /*
  //checking divide
  for(int i = 0; i <=TTOCNum->GetXaxis()->GetNbins()+1; i++){
  cout<<"*********************** Position: "  << TTOCNum->GetXaxis()->GetBinCenter(i)  <<endl;
  cout<<"Numerator: "  << TTOCNum->GetBinContent(i)  <<endl;
  cout<<"Denominator: "<< TTOCDenom->GetBinContent(i)<<endl;
  cout<<"Ratio: "      << gr_TTOC->Eval(TTOCNum->GetXaxis()->GetBinCenter(i))<< ",  Numerator/Denominator: "<<TTOCNum->GetBinContent(i)/TTOCDenom->GetBinContent(i)  <<endl;
  //cout<<endl;
  }
  */
  

  //--Style
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(1.2);
  gr_TTOC->SetLineWidth(2);
  gr_TTOC->SetMarkerSize(1);
  gr_TTOC->SetMarkerStyle(8);
  gr_TTOC->SetMarkerColor(kAzure-2);
  gr_TTOC->SetLineColor(kAzure-2);
  gr_TTOC->SetTitle(name);
  gr_TTOC->GetYaxis()->SetTitleOffset(1.95);
  gr_TTOC->GetXaxis()->SetTitle(TTOCDenom->GetTitle()+unit);
  gr_TTOC->GetYaxis()->SetTitle("Trigger Efficiency");
  //gStyle->SetOptStat(1101);
  gStyle->SetOptStat(0);
  //--2D Style
  //h2_TTOC->SetLineWidth(2);
  //h2_TTOC->SetMarkerSize(1);
  //h2_TTOC->SetMarkerStyle(8);
  //h2_TTOC->SetMarkerColor(kAzure-2);
  //h2_TTOC->SetLineColor(kAzure-2);
  //h2_TTOC->SetTitle(name2D);
  //h2_TTOC->GetYaxis()->SetTitleOffset(1.55);
  //h2_TTOC->GetYaxis()->SetTitle(TTOCDenom2->GetTitle()+unit);
  //h2_TTOC->GetXaxis()->SetTitle(TTOCDenom1->GetTitle()+unit);
  //h2_TTOC->GetZaxis()->SetTitle("Trigger Efficiency");
    gPad->Update();
    gPad->RedrawAxis();


    // save canvas
    canvas->SaveAs(outname+".png");
    canvas->SaveAs(outname+".pdf");
 }
}
