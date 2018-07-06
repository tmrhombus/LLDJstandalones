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

void plotter_singleMerged(TString region, TString lepname, TString varname, Bool_t dolog, Bool_t HIP )
{

// // Draw signal as lines
// Bool_t drawSignal = kFALSE; //kTRUE;
// Bool_t drawRatio = kTRUE;

 // Setup running configuration: IO, naming, SFs, ..
 /////////////////////////////////////////////////////

 TString inpath  = TString("../plots/");
 TString outpath = TString("../plots/");
 TString aversion = TString(getenv("aversion"));

 inpath = inpath+aversion+"/"+region+"/";
 outpath = outpath+aversion+"/"+region+"/";

 Float_t lumiBCDEF = 19691. ;
 Float_t lumiGH = 16226.5 ;

 TString eraname = "";
 if(HIP){
  eraname+="_BCDEF";
  outpath = outpath+"BCDEF/";
  inpath = inpath+"BCDEF/";
 }
 if(!HIP){
  outpath = outpath+"GH/";
  inpath = inpath+"GH/";
  eraname+="_GH";
 }

 TString infilename = lepname+"_"+region+"_"+varname+eraname;
 TString outname = "sp_"+lepname+"_"+region+"_"+varname+eraname;
  outname = outpath + outname;
 // std::cout<<"name: "<<inpath<<" "<<infilename<<std::endl;

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

 // initialize histogram file / histograms
 TFile* file_input       ; 
 TH1F* h_DY     ;
 TH1F* h_GJets  ;
 TH1F* h_ST     ;
 TH1F* h_VV     ;
 TH1F* h_VG     ;
 TH1F* h_ZH     ;
 TH1F* h_TT     ;
 TH1F* h_WJetsToLNu;
 TH1F* h_bkgtotal ;
 TH1F* h_ratio ;
 TH1F* h_ratiostaterr ;
 TH1F* h_altDY ;
 TH1F* h_altVV ;
 TH1F* h_altTT ;
 TH1F* h_Sig_MS15ct1000 ;
 TH1F* h_Sig_MS15ct100  ;
 TH1F* h_Sig_MS15ct10   ;
 TH1F* h_Sig_MS15ct1    ;
 TH1F* h_Sig_MS40ct1000 ;
 TH1F* h_Sig_MS40ct100  ;
 TH1F* h_Sig_MS40ct10   ;
 TH1F* h_Sig_MS40ct1    ;
 TH1F* h_Sig_MS55ct1000 ;
 TH1F* h_Sig_MS55ct100  ;
 TH1F* h_Sig_MS55ct10   ;
 TH1F* h_Sig_MS55ct1    ;
 TH1F* h_Data   ;
 THStack* bgstack;

 // load histogram file / histograms
 file_input = new TFile( inpath + infilename + ".root"               ) ; 
 h_DY             = (TH1F*)file_input->Get("DY"            )->Clone("DY"            )  ;
 h_GJets          = (TH1F*)file_input->Get("GJets"         )->Clone("GJets"         )  ;
 h_WJetsToLNu     = (TH1F*)file_input->Get("WJetsToLNu"    )->Clone("WJetsToLNu"    )  ;
 h_ST             = (TH1F*)file_input->Get("ST"            )->Clone("ST"            )  ;
 h_VV             = (TH1F*)file_input->Get("VV"            )->Clone("VV"            )  ;
 h_VG             = (TH1F*)file_input->Get("VG"            )->Clone("VG"            )  ;
 h_ZH             = (TH1F*)file_input->Get("ZH"            )->Clone("ZH"            )  ;
 h_TT             = (TH1F*)file_input->Get("TT"            )->Clone("TT"            )  ;
 h_bkgtotal       = (TH1F*)file_input->Get("bkgtotal"      )->Clone("bkgtotal"      )  ;
 bgstack       = (THStack*)file_input->Get("bgstack"      )->Clone("bgstack"      )  ;
 h_ratio          = (TH1F*)file_input->Get("ratio"         )->Clone("ratio"         )  ;
 h_ratiostaterr   = (TH1F*)file_input->Get("ratiostaterr"  )->Clone("ratiostaterr"  )  ;
 h_altDY          = (TH1F*)file_input->Get("altDY"         )->Clone("altDY"         )  ;
 h_altVV          = (TH1F*)file_input->Get("altVV"         )->Clone("altVV"         )  ;
 h_altTT          = (TH1F*)file_input->Get("altTT"         )->Clone("altTT"         )  ;
 h_Sig_MS15ct1000 = (TH1F*)file_input->Get("Sig_MS15ct1000")->Clone("Sig_MS15ct1000")  ;
 h_Sig_MS15ct100  = (TH1F*)file_input->Get("Sig_MS15ct100" )->Clone("Sig_MS15ct100" )  ;
 h_Sig_MS15ct10   = (TH1F*)file_input->Get("Sig_MS15ct10"  )->Clone("Sig_MS15ct10"  )  ;
 h_Sig_MS15ct1    = (TH1F*)file_input->Get("Sig_MS15ct1"   )->Clone("Sig_MS15ct1"   )  ;
 h_Sig_MS40ct1000 = (TH1F*)file_input->Get("Sig_MS40ct1000")->Clone("Sig_MS40ct1000")  ;
 h_Sig_MS40ct100  = (TH1F*)file_input->Get("Sig_MS40ct100" )->Clone("Sig_MS40ct100" )  ;
 h_Sig_MS40ct10   = (TH1F*)file_input->Get("Sig_MS40ct10"  )->Clone("Sig_MS40ct10"  )  ;
 h_Sig_MS40ct1    = (TH1F*)file_input->Get("Sig_MS40ct1"   )->Clone("Sig_MS40ct1"   )  ;
 h_Sig_MS55ct1000 = (TH1F*)file_input->Get("Sig_MS55ct1000")->Clone("Sig_MS55ct1000")  ;
 h_Sig_MS55ct100  = (TH1F*)file_input->Get("Sig_MS55ct100" )->Clone("Sig_MS55ct100" )  ;
 h_Sig_MS55ct10   = (TH1F*)file_input->Get("Sig_MS55ct10"  )->Clone("Sig_MS55ct10"  )  ;
 h_Sig_MS55ct1    = (TH1F*)file_input->Get("Sig_MS55ct1"   )->Clone("Sig_MS55ct1"   )  ;
 h_Data           = (TH1F*)file_input->Get("Data"          )->Clone("Data"          )  ;


    // set attributes
    h_DY         -> SetLineColor(kBlack); 
    h_GJets      -> SetLineColor(kBlack);
    h_ST         -> SetLineColor(kBlack); 
    h_TT         -> SetLineColor(kBlack); 
    h_WJetsToLNu -> SetLineColor(kBlack); 
    h_VV         -> SetLineColor(kBlack); 
    h_VG         -> SetLineColor(kBlack); 
    h_ZH         -> SetLineColor(kBlack);

    //h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineColor(632) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineColor(807) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineColor(798) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineColor(418) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineColor(601) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineColor(599) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineColor(618) ;

    //h_ggZH_HToSSTobbbb_MS40_ctauS0     -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS0p05  -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1     -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10    -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS100   -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS1000  -> SetLineWidth(2) ;
    //h_ggZH_HToSSTobbbb_MS40_ctauS10000 -> SetLineWidth(2) ;

    h_Data  -> SetLineColor(kBlack);
    h_Data  -> SetMarkerStyle(8);
    h_Data  -> SetMarkerSize(1);
    h_Data  -> SetLineWidth(3);

    h_DY        ->SetFillStyle(1001);
    h_GJets     ->SetFillStyle(1001);
    h_ST        ->SetFillStyle(1001);
    h_TT        ->SetFillStyle(1001);
    h_WJetsToLNu->SetFillStyle(1001);
    h_VV        ->SetFillStyle(1001);
    h_VG        ->SetFillStyle(1001);
    h_ZH        ->SetFillStyle(1001);

    h_DY        ->SetFillColor(kAzure-3);
    h_GJets     ->SetFillColor(kViolet+3);
    h_ST        ->SetFillColor(kOrange+8);
    h_TT        ->SetFillColor(kGreen+1);
    h_WJetsToLNu->SetFillColor(kViolet-3);
    h_VV        ->SetFillColor(kRed);
    h_VG        ->SetFillColor(kPink+9);
    h_ZH        ->SetFillColor(kCyan);

    h_DY        ->SetLineColor(kBlack); 
    h_GJets     ->SetLineColor(kBlack); 
    h_ST        ->SetLineColor(kBlack); 
    h_TT        ->SetLineColor(kBlack); 
    h_WJetsToLNu->SetLineColor(kBlack); 
    h_VV        ->SetLineColor(kBlack); 
    h_VG        ->SetLineColor(kBlack); 
    h_ZH        ->SetLineColor(kBlack); 

    h_DY        ->SetLineWidth(2);
    h_GJets     ->SetLineWidth(2);
    h_ST        ->SetLineWidth(2);
    h_TT        ->SetLineWidth(2);
    h_WJetsToLNu->SetLineWidth(2);
    h_VV        ->SetLineWidth(2);
    h_VG        ->SetLineWidth(2);
    h_ZH        ->SetLineWidth(2);
    h_bkgtotal  ->SetLineWidth(2);

    h_bkgtotal->SetFillColorAlpha(kYellow+1, 0.7);
    h_bkgtotal->SetFillStyle(1001);

    // make legend
    TLegend *leg;
    leg = new TLegend(0.2,0.7,0.88,0.88);
    leg->SetBorderSize(0);
    leg->SetNColumns(2);
    leg->SetFillColor(kWhite);
    leg->AddEntry(h_Data         , "Data", "lpe"); 
    leg->AddEntry(h_DY           , "Drell-Yan", "f"); 
    leg->AddEntry(h_GJets        , "#gamma+Jets", "f"); 
    leg->AddEntry(h_ST           , "Single Top", "f"); 
    leg->AddEntry(h_TT           , "t#bar{t}+Jets", "f"); 
    leg->AddEntry(h_WJetsToLNu   , "W+Jets", "f"); 
    leg->AddEntry(h_VV           , "Diboson", "f"); 
    leg->AddEntry(h_VG           , "V#gamma", "f");
    leg->AddEntry(h_ZH           , "ZH#rightarrowLLbb", "f");
    leg->AddEntry(h_bkgtotal     , "MC bkg. stat. err.", "f");

     TLegend *sigleg = new TLegend(0.15,0.6,0.65,0.85);
   //if(drawSignal){
     //sigleg->SetBorderSize(0);
     //sigleg->SetFillColor(kWhite);
     //sigleg->SetHeader("Z(H#rightarrow SS#rightarrow bbbb)","C");
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0     , "M_{S}=40 c#tau_{S}=0    ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS0p05  , "M_{S}=40 c#tau_{S}=0p05 ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1     , "M_{S}=40 c#tau_{S}=1    ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10    , "M_{S}=40 c#tau_{S}=10   ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS100   , "M_{S}=40 c#tau_{S}=100  ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS1000  , "M_{S}=40 c#tau_{S}=1000 ", "l" ) ;
     //sigleg->AddEntry(h_ggZH_HToSSTobbbb_MS40_ctauS10000 , "M_{S}=40 c#tau_{S}=10000", "l" ) ;
    //}

    // set max and draw
    Double_t ymax;
    ymax = std::max(h_Data->GetMaximum(), h_bkgtotal->GetMaximum() );
    
    if(dolog){
     bgstack->SetMaximum(500*ymax); 
     bgstack->SetMinimum(1.0);
    } 
    else {
     bgstack->SetMaximum(ymax*1.4);
    }
     
    plotpad->cd();
    bgstack->Draw("hist");
    //bgstack->Draw("hist e");
    bgstack->GetYaxis()->SetTitle("Events");
    bgstack->GetYaxis()->SetTitleSize(40);
    bgstack->GetYaxis()->SetTitleFont(43);
    bgstack->GetYaxis()->SetTitleOffset(1.55);
    h_bkgtotal->Draw("e2 sames");
    h_Data->Draw("sames E"); 

//    if(drawSignal){
//     h_ggZH_HToSSTobbbb_MS40_ctauS0     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS0p05  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1     ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10    ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS100   ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS1000  ->Draw("hist sames") ;
//     h_ggZH_HToSSTobbbb_MS40_ctauS10000 ->Draw("hist sames") ;
//     sigleg->Draw();
//    }
    leg->Draw();

    char lumistring [50];
    int dummy; 

    // add titles
    title->DrawTextNDC(0.2,0.91,"CMS");
    extra->DrawTextNDC(0.3,0.91,"Preliminary");
    if(HIP){
     extra2->DrawTextNDC(0.51,0.91,"Eras B-F");
     dummy=sprintf (lumistring, "%0.1f", lumiBCDEF/1000.);
    }
    else{
     extra2->DrawTextNDC(0.51,0.91,"Eras GH");
     dummy=sprintf (lumistring, "%0.1f", lumiGH/1000.);
    }
    //lumi->DrawTextNDC(0.9,0.91,"35.9 /fb (13 TeV)");
    lumi->DrawTextNDC(0.9,0.91,(TString)lumistring+" /fb (13 TeV)");


     ratiopad->cd();
     h_ratio = (TH1F*)h_Data->Clone("h_ratio");
     if(h_Data->Integral(-1,-1)>0){
      h_ratio->Divide(h_bkgtotal);
     }
     h_ratio->SetTitle(" ");
     // Y axis ratio plot settings
     h_ratio->GetYaxis()->SetTitleSize(40);
     h_ratio->GetYaxis()->SetTitleFont(43);
     h_ratio->GetYaxis()->SetTitleOffset(1.55);
     h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
     h_ratio->GetYaxis()->SetLabelSize(20);
     h_ratio->GetYaxis()->SetNdivisions(-105);
     h_ratio->GetYaxis()->SetTitle("Data/MC");
     // X axis ratio plot settings
     h_ratio->GetXaxis()->SetTitleSize(40);
     h_ratio->GetXaxis()->SetTitleFont(43);
     h_ratio->GetXaxis()->SetTitle(h_Data->GetTitle());
     h_ratio->GetXaxis()->SetTitleOffset(4.0);
     h_ratio->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
     h_ratio->GetXaxis()->SetLabelSize(20);//20
     h_ratio->SetMarkerStyle(20);
     h_ratio->SetMarkerColor(kRed);
     h_ratio->SetMarkerSize(1);
     h_ratio->GetYaxis()->SetRangeUser(0,2);
     h_ratio->Draw("ep");  // draw first to get ranges set internally inside root

     h_ratiostaterr = (TH1F*)h_bkgtotal->Clone("h_ratiostaterr");
     h_ratiostaterr->Divide(h_bkgtotal);

     ratiopad->Update();       // need to update pad to get X min/max
     TLine *line = new TLine(ratiopad->GetUxmin(),1,ratiopad->GetUxmax(),1);
     line->SetLineColor(kBlue);
     line->SetLineWidth(3);
     line->SetLineStyle(9);
     h_ratiostaterr->Draw("e2 same");
     line->Draw();
     h_ratio->Draw("ep same"); // draw points above line
 
     // save canvas
     //canvas->SaveAs(outname+".png");
     canvas->SaveAs(outname+".pdf");

     //// save histograms into single root file
     //TFile *outfile = TFile::Open(outname+".root","RECREATE");
     //h_Data        ->Write();
     //h_DY          ->Write();
     //h_GJets       ->Write();
     //h_ST          ->Write();
     //h_TT          ->Write();
     //h_WJetsToLNu  ->Write();
     //h_VV          ->Write();
     //h_VG          ->Write();
     //h_ZH          ->Write();
     //h_bkgtotal    ->Write();
     //h_ratio       ->Write();
     //h_ratiostaterr->Write();
     //bgstack       ->Write();
     //outfile->Close();
  
}
