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

void plotter_tagvarUnc(TString region, TString lepname, TString varname, Bool_t dolog, Bool_t HIP )
{

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
 TH1F* h_altDY ;
 TH1F* h_altVV ;
 TH1F* h_altTT ;
 TH1F* h_Sig ;
 TH1F* h_Sig40 ;
 //TH1F* h_Sig_MS15ct1000 ;
 //TH1F* h_Sig_MS15ct100  ;
 //TH1F* h_Sig_MS15ct10   ;
 //TH1F* h_Sig_MS15ct1    ;
 //TH1F* h_Sig_MS40ct1000 ;
 //TH1F* h_Sig_MS40ct100  ;
 //TH1F* h_Sig_MS40ct10   ;
 //TH1F* h_Sig_MS40ct1    ;
 //TH1F* h_Sig_MS55ct1000 ;
 //TH1F* h_Sig_MS55ct100  ;
 //TH1F* h_Sig_MS55ct10   ;
 //TH1F* h_Sig_MS55ct1    ;
 TH1F* h_Data   ;
 THStack* bgstack;

 TH1F* h_DataNorm;
 TH1F* h_MCNorm;
 TH1F* h_DataInt;
 TH1F* h_MCInt;
 TH1F* h_DataInt2;
 TH1F* h_MCInt2;

 // load common histogram files / histograms
 file_input = new TFile( inpath + infilename + ".root"               ) ; 
 h_DY             = (TH1F*)file_input->Get("DY"            )->Clone("DY"            )  ;
 h_GJets          = (TH1F*)file_input->Get("GJets"         )->Clone("GJets"         )  ;
 h_WJetsToLNu     = (TH1F*)file_input->Get("WJetsToLNu"    )->Clone("WJetsToLNu"    )  ;
 h_ST             = (TH1F*)file_input->Get("ST"            )->Clone("ST"            )  ;
 h_VV             = (TH1F*)file_input->Get("VV"            )->Clone("VV"            )  ;
 h_VG             = (TH1F*)file_input->Get("VG"            )->Clone("VG"            )  ;
 h_ZH             = (TH1F*)file_input->Get("ZH"            )->Clone("ZH"            )  ;
 h_TT             = (TH1F*)file_input->Get("TT"            )->Clone("TT"            )  ;
 h_altDY          = (TH1F*)file_input->Get("altDY"         )->Clone("altDY"         )  ;
 h_altVV          = (TH1F*)file_input->Get("altVV"         )->Clone("altVV"         )  ;
 h_altTT          = (TH1F*)file_input->Get("altTT"         )->Clone("altTT"         )  ;
 h_Data           = (TH1F*)file_input->Get("Data"          )->Clone("Data"          )  ;

 std::vector<TString> MSs;
 std::vector<TString> cts;
 MSs.push_back("15");
 MSs.push_back("40");
 MSs.push_back("55");
 cts.push_back("1");
 cts.push_back("10");
 cts.push_back("100");
 cts.push_back("1000");

 for(unsigned int i=0; i<MSs.size(); ++i){
  TString MS = MSs.at(i);
  //std::cout<<MS<<std::endl;
  for(unsigned int i=0; i<cts.size(); ++i){
   TString ct = cts.at(i);
   //std::cout<<ct<<std::endl;

   TString outname = "tvuMS"+MS+"ct"+ct+"_"+lepname+"_"+region+"_"+varname+eraname;
   outname = outpath + outname;
   //std::cout<<outname<<std::endl;

   TString signame = "Sig_MS"+MS+"ct"+ct;
   //TString signame = (TString)"Sig_MS"+MS.Data()+(TString)"ct"+ct.Data();
   //std::cout<<signame<<std::endl;
   h_Sig = (TH1F*)file_input->Get(signame.Data())->Clone("h_Sig")  ;
   h_Sig->SetFillColor(kOrange+8);
   h_Sig->SetLineWidth(2);
   h_Sig->SetLineColor(kBlack);
   h_Sig40 = (TH1F*)h_Sig->Clone("h_Sig40"); 
   h_Sig40->Scale(40000);
   h_Sig40->SetFillStyle(0);
   h_Sig40->SetLineColor(kOrange+8);
   bgstack          = (THStack*)file_input->Get("bgstack"    )->Clone("bgstack"       )  ;
   bgstack->Add(h_Sig); 
   h_bkgtotal       = (TH1F*)file_input->Get("bkgtotal"      )->Clone("bkgtotal"      )  ;
   h_bkgtotal->Add(h_Sig);

   //h_bkgtotal->SetFillColorAlpha(kYellow+1, 0.7);
   //h_bkgtotal->SetFillStyle(1001);

//   printf(" size %10.10f %10.10f \n ", h_Sig->Integral(0,-1), h_bkgtotal->Integral(0,-1));


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
   //leg->AddEntry(h_bkgtotal     , "MC bkg. stat. err.", "f");
   leg->AddEntry(h_Sig, "Signal M_{S}"+MS+" c#tau"+ct,"f");
   leg->AddEntry(h_Sig40, "Signal x 40k","l");
  
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

   h_Data->Draw();
   TString xtitle = h_Data->GetTitle();
   TString xtstrp(xtitle.Strip(TString::kTrailing,' '));
   Float_t cutval=-999;
    // if we cut < or > doesn't actually matter
   if(xtstrp=="AODCaloJetAlphaMax"){
     cutval = 0.35; // Amax < 0.35
   }
   if(xtstrp=="AODCaloJetMedianLog10TrackAngle"){
     cutval = -1.5; // AODCaloJetMedianLog10TrackAngle > -1.5
   }
   if(xtstrp=="AODCaloJetMedianLog10IPSig"){
     cutval = 1.15; // AODCaloJetMedianLog10IPSig > 1.15
   }

   bgstack->Draw("hist");
   //bgstack->Draw("hist e");
   bgstack->GetYaxis()->SetTitle("Events");
   bgstack->GetYaxis()->SetTitleSize(40);
   bgstack->GetYaxis()->SetTitleFont(43);
   bgstack->GetYaxis()->SetTitleOffset(1.55);
   h_bkgtotal->Draw("e2 sames");
   // renormalize signal to show scale
//   printf( " scale: %10.10f \n", h_bkgtotal->Integral(0,-1) / h_Sig->Integral(0,-1) );
//   h_Sig->Scale( h_bkgtotal->Integral(0,-1) / h_Sig->Integral(0,-1) );
   h_Sig40->Draw("sames hist");
   h_Data->Draw("sames E"); 
   leg->Draw();
   if(cutval > -990){
    TLine *lcut = new TLine(cutval,0,cutval,h_bkgtotal->GetMaximum());
    lcut->SetLineColor(kRed);
    lcut ->Draw();
   }
  
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
  
   // second pad
   ratiopad->cd();

   h_DataInt  = (TH1F*)h_Data->Clone("DataInt"     );
   h_MCInt    = (TH1F*)h_bkgtotal->Clone("h_MCInt" );

   int nbins = h_DataInt->GetNbinsX();
   //std::cout<<" nbins data "<<nbins<<" mc"<<h_MCInt->GetNbinsX()<<std::endl;
   float datasum=0.;
   float mcsum=0.;
   for( int j=1; j<nbins+1; ++j){
    int databinint = h_Data->GetBinContent(j);
    int mcbinint = h_bkgtotal->GetBinContent(j);
    //std::cout<<"  datasum "<<datasum<<" binint "<<binint<<std::endl;
    datasum = datasum + databinint;
    mcsum = mcsum + mcbinint;
    h_DataInt->SetBinContent(j,datasum);
    h_MCInt->SetBinContent(j,mcsum);
   }

   h_DataInt->Scale( 1.0/h_Data->Integral());
   h_MCInt->Scale( 1.0/h_bkgtotal->Integral());

//   h_DataInt->Scale( 1.0/h_Data->Integral(0,-1));
//   h_MCInt->Scale( 1.0/h_bkgtotal->Integral(0,-1));

   h_DataInt->SetLineColor(kBlack);
   h_MCInt->SetLineColor(kOrange+8);
   h_DataInt->SetLineWidth(2);
   h_MCInt->SetLineWidth(2);
   h_DataInt->SetFillStyle(0);
   h_MCInt->SetFillStyle(0);

   // make legend
   TLegend *leg2;
   leg2 = new TLegend(0.2,0.6,0.4,0.88);
   leg2->SetBorderSize(2);
   leg2->SetFillColor(kWhite);
   leg2->AddEntry(h_DataInt , "Data", "l"); 
   leg2->AddEntry(h_MCInt   , "MC", "l"); 

   // Y axis ratio plot settings
   h_DataInt->GetYaxis()->SetTitleSize(40);
   h_DataInt->GetYaxis()->SetTitleFont(43);
   h_DataInt->GetYaxis()->SetTitleOffset(1.55);
   h_DataInt->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h_DataInt->GetYaxis()->SetLabelSize(20);
   //h_DataInt->GetYaxis()->SetNdivisions(-106);
   h_DataInt->GetYaxis()->SetTitle("Integral");
   // X axis ratio plot settings
   h_DataInt->GetXaxis()->SetTitleSize(40);
   h_DataInt->GetXaxis()->SetTitleFont(43);
//   TString xtitle = h_DataInt->GetTitle();
//   TString xtstrp(xtitle.Strip(TString::kTrailing,' '));
//   //xtitle.Strip(s=kTrailing,c=" ");
   h_DataInt->GetXaxis()->SetTitle(xtstrp);
   //h_DataInt->GetXaxis()->SetTitle(h_DataInt->GetTitle());
   h_DataInt->GetXaxis()->SetTitleOffset(4.0);
   h_DataInt->GetXaxis()->SetLabelFont(43); //43 Absolute font size in pixel (precision 3)
   h_DataInt->GetXaxis()->SetLabelSize(20);//20
   h_DataInt->GetYaxis()->SetRangeUser(0,1.1);
   h_DataInt->SetTitle(" ");
   h_DataInt->Draw("ep");  // draw first to get ranges set internally inside root

   ratiopad->Update();       // need to update pad to get X min/max
   TLine *line = new TLine(ratiopad->GetUxmin(),1,ratiopad->GetUxmax(),1);
   line->SetLineColor(kBlue);
   line->SetLineWidth(3);
   line->SetLineStyle(9);
   line->Draw();
   leg2->Draw();
   h_MCInt->Draw("hist same");
   h_DataInt->Draw("hist same"); // draw points above line
  
   // save canvas
   //canvas->SaveAs(outname+".png");
   canvas->SaveAs(outname+".pdf");
  

   // draw integral plots on large canvas
   //////////////////////////////////////////////

   TCanvas* can2 = new TCanvas("can2","can2",canx,cany); 
  
   can2->Clear();
   can2->cd();
  
   TPad *pp2  = new TPad("pp2", "pp2", 0, 0.25, 1, 1);
   //pp2->SetBottomMargin(0.04);
   pp2->SetBottomMargin(0.1);
   pp2->SetLeftMargin(lmarg);
   pp2->SetRightMargin(rmarg);
   pp2->SetFrameLineWidth(3);
   pp2->SetLogy(dolog);
   pp2->Draw();
  
   can2->cd();
   //TPad *rp2 = new TPad("rp2", "rp2", 0, 0, 1, 0.25);
   //rp2->SetTopMargin(0.04);
   //rp2->SetBottomMargin(0.4);
   //rp2->SetFrameLineWidth(3);
   //rp2->SetLeftMargin(lmarg);
   //rp2->SetRightMargin(rmarg);
   //rp2->SetLogy(0);
   //rp2->SetGrid();
   //rp2->Draw();

   pp2->cd();

   h_DataInt2  = (TH1F*)h_DataInt->Clone("DataInt2" );
   h_MCInt2    = (TH1F*)h_MCInt->Clone("MCInt2"    );
   
   // make legend
   TLegend *lg2;
   lg2 = new TLegend(0.2,0.5,0.4,0.7);
   lg2->SetBorderSize(2);
   lg2->SetFillColor(kWhite);
   lg2->AddEntry(h_DataInt2 , "Data", "l"); 
   lg2->AddEntry(h_MCInt2   , "MC", "l"); 
  
   h_DataInt2->GetYaxis()->SetTitle("Normalized Integral");
   h_DataInt2->GetXaxis()->SetTitle(xtstrp);
   h_DataInt2->GetXaxis()->SetTitleOffset(1.2);
   h_DataInt2->GetXaxis()->SetLabelSize(35);//20
   h_DataInt2->GetYaxis()->SetLabelSize(35);//20
   //std::cout<<" xtstrp: "<<xtstrp<<"----"<<std::endl;
   h_DataInt2->Draw("ep");  // draw first to get ranges set internally inside root
  
   pp2->Update();       // need to update pad to get X min/max
   TLine *l2 = new TLine(pp2->GetUxmin(),1,pp2->GetUxmax(),1);
   l2->SetLineColor(kBlue);
   l2->SetLineWidth(3);
   l2->SetLineStyle(9);
   l2->Draw();
   h_MCInt2->Draw("hist same");
   h_DataInt2->Draw("hist same"); // draw points above l2
   lg2->Draw();

   if(cutval > -990){
    // draw line at original cut value
    TLine *lcut2 = new TLine(cutval,0,cutval,1.05);
    lcut2->SetLineColor(kRed);
    lcut2 ->Draw();

    // only for tagging variables
    //std::cout<<" cutval: "<<cutval<<" var: "<<xtstrp<<std::endl;
    h_DataNorm  = (TH1F*)h_Data->Clone("DataNorm"     );
    h_MCNorm    = (TH1F*)h_bkgtotal->Clone("MCNorm" );
    h_DataNorm ->Scale( 1.0/h_DataNorm->Integral() ); 
    h_MCNorm   ->Scale( 1.0/h_MCNorm  ->Integral() ); 

    //std::cout<<" !!!!cutval: "<<cutval<<" var: "<<xtstrp<<std::endl;
    Int_t binAtCut;
    binAtCut = h_DataNorm->GetXaxis()->FindBin(cutval);
    Float_t dataIntToCut = h_DataNorm->Integral(0,binAtCut);
    Float_t mcIntToCut = h_MCNorm->Integral(0,binAtCut);

    //std::cout<<" bin "<<binAtCut<<" data: "<<dataIntToCut<<" mc: "<<mcIntToCut<<std::endl;
    Float_t datamcdiffToCut = dataIntToCut - mcIntToCut ;
    int mcbinup = -1;
    int mcbindown = -1;
    //std::cout<<" datamcdiffToCut "<<datamcdiffToCut<<std::endl;

    int bins = h_DataNorm->GetNbinsX();
    //std::cout<<" nbins data "<<nbins<<" mc"<<h_MCInt->GetNbinsX()<<std::endl;
    Int_t binMCequiv = 0;
    float tmpmcsum=0.;
    for( binMCequiv=1; binMCequiv<nbins+1; ++binMCequiv){
     tmpmcsum   += h_MCNorm->GetBinContent(binMCequiv); 

     if( tmpmcsum > dataIntToCut) break;

    }
    Float_t MCcutval = 0;
    MCcutval = h_MCNorm->GetXaxis()->GetBinLowEdge(binMCequiv+1); 
    // binMCequiv+1 because it should be GetBinHighEdge
      //MCcutval = h_MCNorm->GetXaxis()->GetBinCenter(binMCequiv);
    //printf(" CHECK: tmpmcsum %10.5f dataIntToCut %10.5f check(n) %10.5f check(n-1) %10.5f MCbin %i Databin %i \n",tmpmcsum,dataIntToCut,h_MCNorm->Integral(0,binMCequiv),h_MCNorm->Integral(0,binMCequiv-1),binMCequiv,binAtCut );
    printf(" old cut: %5.3f  new cut: %5.3f\n", cutval, MCcutval);

    // draw line at new cutvalue
    TLine *lnewcut2 = new TLine(MCcutval,0,MCcutval,1.05);
    lnewcut2->SetLineColor(kBlue);
    lnewcut2->SetLineWidth(1);
    lnewcut2 ->Draw();
   }


   title->DrawTextNDC(0.2,0.91,"CMS");
   extra->DrawTextNDC(0.3,0.91,"Preliminary");
   lumi->DrawTextNDC(0.9,0.91,(TString)lumistring+" /fb (13 TeV)");
   if(HIP){
    extra2->DrawTextNDC(0.51,0.91,"Eras B-F");
    dummy=sprintf (lumistring, "%0.1f", lumiBCDEF/1000.);
   }
   else{
    extra2->DrawTextNDC(0.51,0.91,"Eras GH");
    dummy=sprintf (lumistring, "%0.1f", lumiGH/1000.);
   }

   can2->SaveAs(outname+"_2.pdf");


  ////////////////////////////////




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
 }
}
