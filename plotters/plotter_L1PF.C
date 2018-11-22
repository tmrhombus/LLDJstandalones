
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
#include <stdio.h>
#include <cstdlib> /* mkdir */

#include <stdlib.h>     /* getenv */

//using namespace std;

void plotter_L1PF(TString region, TString varname, TString varname2, Bool_t dolog)
{

 TString inpath  = TString("../plots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));

 inpath = inpath+aversion+"/"+region+"/GH/";
 outpath = outpath+aversion+"/"+region+"/GH/";

 TString infilename = region+"_"+varname;
 TString outname = "L1PF_"+region+"_"+varname;
 outname = outpath + outname;

 TString lifetime = "40";
 // canvas and text attributes
 int canx = 1100;
 int cany = 1200;
 float lmarg = 0.12;
 float rmarg = 0.05;
 
 TCanvas* canvas = new TCanvas("canvas","canvas",canx,cany); 

 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(kBird);

 canvas->Clear();
 canvas->cd();

 TPad *plotpad  = new TPad("plotpad", "plotpad", 0, 0.25, 1, 1);
 plotpad->SetBottomMargin(0.04);
 plotpad->SetLeftMargin(lmarg);
 plotpad->SetRightMargin(rmarg);
 plotpad->SetFrameLineWidth(3);
 plotpad->SetLogy(dolog);
 plotpad->Draw();

 canvas->cd();
 TPad *ratiopad = new TPad("ratiopad", "ratiopad", 0, 0, 1, 0.25);
 ratiopad->SetTopMargin(0.04);
 ratiopad->SetBottomMargin(0.4);
 ratiopad->SetFrameLineWidth(3);
 ratiopad->SetLeftMargin(lmarg);
 ratiopad->SetRightMargin(rmarg);
 ratiopad->SetLogy(0);
 ratiopad->SetGrid();
 ratiopad->Draw();
 canvas->cd();

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.06);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.05);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* extra2 = new TText(1,1,"") ;
 extra2->SetTextSize(0.03);
 extra2->SetTextColor(kBlack);
 extra2->SetTextAlign(11);
 //extra2->SetTextAlign(13);
 extra2->SetTextFont(62);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.05);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);



 TFile* file_nominal       ; 
 TFile* file_L1PF          ; 
 
 TH1F* h_nominal           ;
 TH1F* h_L1PF              ;
 TH1F* h_rat               ;
 //cout<<inpath + region + "_AllJets_AODCaloJet"+varname+"_GH.root" <<endl;
 
 //if(dolog){
 //   file_nominal   = TFile::Open( inpath+region+"_"+varname+"_GH_log.root"  ) ; 
 //   h_nominal      = (TH1F*)file_nominal->Get("bkgtotal")->Clone( "Original" ) ;
 //  
 //   file_L1PF      = TFile::Open( inpath+region+"_"+varname+"_GH_log.root"  ) ; 
 //   h_L1PF         = (TH1F*)file_L1PF->Get("bkgtotal")->Clone( "ForTest" ) ;
 //}
 //else{
    file_nominal     = TFile::Open( inpath+region+"_"+varname+"_GH.root"  ) ; 
    h_nominal        = (TH1F*)file_nominal->Get("bkgtotal")->Clone( "Original" ) ;
    h_nominalSig1000 = (TH1F*)file_nominal->Get("Sig_MS"+lifetime+"ct1000")->Clone( "Orig. Sig c#tau 1000" ) ;
   
    file_L1PF      = TFile::Open( inpath+region+"_"+varname2+"_GH.root"  ) ; 
    h_L1PF         = (TH1F*)file_L1PF->Get("bkgtotal")->Clone( "ForTest" ) ;
    h_L1PFSig1000 = (TH1F*)file_L1PF->Get("Sig_MS"+lifetime+"ct1000")->Clone( "L1PF Sig c#tau 1000" ) ;
 //}
 h_rat = (TH1F*)h_nominal->Clone("ratio");
 h_rat->Add(h_L1PF,-1);
 h_rat->Divide(h_nominal);

 plotpad->cd();
 
 h_nominal       ->SetFillStyle(1001);
// h_nominalSig1000->SetFillStyle(1001);
 h_L1PF          ->SetFillStyle(1001);
 h_L1PFSig1000   ->SetMarkerStyle(3);
 h_L1PFSig1000   ->SetMarkerSize(4);
 
 h_nominal       ->SetLineColor(kBlack); 
 h_nominalSig1000->SetLineColor(kGreen+0); 
 h_L1PF          ->SetLineColor(kBlack); 
 h_L1PFSig1000   ->SetLineColor(kGreen+3); 

 h_nominal       ->SetLineWidth(2);
 h_nominalSig1000->SetLineWidth(4);
 h_L1PF          ->SetLineWidth(4);
 h_L1PFSig1000   ->SetLineWidth(4);

 h_nominal       ->SetFillColor(kBlue);
 //h_L1PF        ->SetFillColor(kRed);

 h_nominal->GetYaxis()->SetTitle("Entries");
 h_nominal->GetYaxis()->SetTitleOffset(1.75);
 h_L1PF->SetFillColorAlpha(kRed, 0.5);
 h_L1PF->SetFillStyle(3444);
 if(dolog) h_nominal->SetMaximum(h_nominal->GetMaximum()*1000); 
 else      h_nominal->SetMaximum(h_nominal->GetMaximum()*1.50); 
 TLegend *leg;
   leg = new TLegend(0.2,0.7,0.88,0.88);
   leg->SetBorderSize(0);
   leg->SetNColumns(2);
   leg->SetFillColor(kWhite);
   leg->AddEntry(h_nominal         , "Original", "f"); 
 //  leg->AddEntry(h_nominalSig1000  , "Orig. Sig c#tau 1000", "l"); 
   leg->AddEntry(h_L1PF            , "ForTest" , "f"); 
//   leg->AddEntry(h_L1PFSig1000     , "L1PF. Sig c#tau 1000" , "lp"); 

 h_nominal       ->Draw("hist");
 //h_nominalSig1000->Draw("hist sames");
 h_L1PF          ->Draw("hist sames");
 //h_L1PFSig1000   ->Draw("p sames");
 leg->Draw();

 ratiopad->cd();
       h_rat->SetTitle(" ");
       // Y axis ratio plot settings
       h_rat->GetYaxis()->SetTitleSize(36);
       h_rat->GetYaxis()->SetTitleFont(43);
       h_rat->GetYaxis()->SetTitleOffset(1.55);
       h_rat->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
       h_rat->GetYaxis()->SetLabelSize(20);
       h_rat->GetYaxis()->SetNdivisions(-105);
       h_rat->GetYaxis()->SetTitle("#frac{Orig-Test}{Orig}");
       //h_rat->SetTitle("Orig-Test/Orig");
       // X axis ratio plot settings
       h_rat->GetXaxis()->SetTitleSize(40);
       h_rat->GetXaxis()->SetTitleFont(43);
       h_rat->GetXaxis()->SetTitle((TString)h_nominal->GetTitle());
       h_rat->GetXaxis()->SetTitleOffset(4.0);
       h_rat->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
       h_rat->GetXaxis()->SetLabelSize(20);//20
       h_rat->SetMarkerStyle(20);
       h_rat->SetMarkerColor(kRed);
       h_rat->SetMarkerSize(1);
       h_rat->GetYaxis()->SetRangeUser(-0.15,0.15);
       h_rat->Draw("hist p");  // draw first to get ranges set internally inside root
       //h_rat->SetTitle("Orig-Test/Orig");
              
       ratiopad->Update();       // need to update pad to get X min/max
       TLine *line = new TLine(ratiopad->GetUxmin(),0,ratiopad->GetUxmax(),0);
       line->SetLineColor(kBlue);
       line->SetLineWidth(3);
       line->SetLineStyle(9);
       line->Draw();
       h_rat->Draw("hist p same"); // draw points above line

 canvas->SaveAs(outname+".pdf");

















}
