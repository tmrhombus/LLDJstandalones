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


void TriggerTurnOn( )
{
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 std::vector<TString> sample;
// sample.push_back("DYJetsToLL_M-50");//_TwoMuZH_histograms.root 
// sample.push_back("DYJetsToLL_M-5to50_HT-100to200");
// sample.push_back("DYJetsToLL_M-5to50_HT-200to400");
// sample.push_back("DYJetsToLL_M-5to50_HT-400to600");
// sample.push_back("DYJetsToLL_M-5to50_HT-600toInf");
 sample.push_back("GJets");
// sample.push_back("GJets_HT-100To200");
// sample.push_back("GJets_HT-200To400");
// sample.push_back("GJets_HT-400To600");
// sample.push_back("GJets_HT-600ToInf");
// sample.push_back("QCD_HT100to200");
// sample.push_back("QCD_HT200to300");
// sample.push_back("QCD_HT300to500");
// sample.push_back("QCD_HT500to700");
// sample.push_back("QCD_HT700to1000");
// sample.push_back("QCD_HT1000to1500");
// sample.push_back("QCD_HT1500to2000");
// sample.push_back("QCD_HT2000toInf");
// sample.push_back("ST_s-channel_4f_leptonDecays");
// sample.push_back("ST_t-channel_top_4f_inclusiveDecays");
// sample.push_back("ST_tW_top_5f_NoFullyHadronicDecays");
// sample.push_back("ST_t-channel_antitop_4f_inclusiveDecays");
// sample.push_back("ST_tW_antitop_5f_NoFullyHadronicDecays");
// sample.push_back("TTJets");
// sample.push_back("WGToLNuG");
// sample.push_back("WJetsToLNu");
// sample.push_back("ZGTo2LG");
// sample.push_back("ZZ");
// sample.push_back("ggZH_HToBB_ZToLL");
// sample.push_back("ZH_HToBB_ZToLL");


 

 //1D histograms to make
 std::vector<TString> Nname;
 std::vector<TString> Dname;
 //twoD histograms to make
 std::vector<TString> twoD_Nname;
 std::vector<TString> twoD_Dname;

 TString lep1 = "";
 TString lep2 = "";
 TString var  = "";
 TString trig = "";
 ///TString lepton;
 ///// lepton flavor
 ///std::vector<TString> lep;
 ///lep.clear();
 ///lep.push_back("ele"); 
 ///lep.push_back("mu");  
 
 TString aversion = TString(getenv("aversion"));
 inpath = inpath+aversion+"/";
 outpath = outpath+aversion+"/";
 
//TwoMuDY  <-Region
 //QCD_Ht...<-sampleName
 //SampleName+"_"+Region+"_histograms.root"
 //run one at a time or make a run....sh script
 TString region = "OnePho";
 //TString region = "EleMuOSOF"; 
 //TString region = "TwoMuDY";
 //TString region = "TwoEleDY"; 
 //TString region = "TwoMuZH";
 //TString region = "TwoEleZH"; 

 if (region == "TwoMuDY") outpath = outpath+"TwoMuDY/";
 if (region == "TwoEleDY") outpath = outpath+"TwoEleDY/";
 if (region == "OnePho") outpath = outpath+"OnePho/";
 if (region == "EleMuOSOF") outpath = outpath+"EleMu/";
 //if (region == "EleMuOSOF") outpath = outpath+"MuEle/";
 TGraphAsymmErrors* gr_TTOC = new TGraphAsymmErrors();
 TH1F* TTOCDenom;
 TH1F* TTOCNum;
 TH2F* twoD_TTOCDenom;
 TH2F* twoD_TTOCNum;
 TH2F* twoD_Divide;
 TString unit;
 TString name;
 TString twoD_name;
 
 for (int k = 0; k<sample.size(); k++){
 TFile *_file0 = TFile::Open(inpath+sample[k]+"_"+region+"_histograms.root");
  Nname.clear();
  Dname.clear();
  
  Nname.push_back("TTOCTriggerPhoPt");
  Dname.push_back("TTOCPhoPt");
  Nname.push_back("TTOCTriggerPhoEta");
  Dname.push_back("TTOCPhoEta");
  //Nname.push_back("TTOCTriggerMuE_ElePt");
  //Dname.push_back("TTOCMuE_ElePt");
   
  //Nname.push_back("TTOCMuTriggerDMu1Pt");
  //Dname.push_back("TTOCMu1Pt");
 ///// Nname.push_back("TTOCMuTriggerDMu2Pt");
 ///// Dname.push_back("TTOCMu2Pt");
 ///// Nname.push_back("TTOCMuTriggerDMu1Eta");
 ///// Dname.push_back("TTOCMu1Eta");
 ///// Nname.push_back("TTOCMuTriggerDMu2Eta");
 ///// Dname.push_back("TTOCMu2Eta");
 ///// Nname.push_back("TTOCEleTrigger23DEle1Pt");
 ///// Dname.push_back("TTOCEle1Pt");
 ///// Nname.push_back("TTOCEleTrigger23DEle2Pt");
 ///// Dname.push_back("TTOCEle2Pt");
 ///// Nname.push_back("TTOCEleTrigger23DEle1Eta");
 ///// Dname.push_back("TTOCEle1Eta");
 ///// Nname.push_back("TTOCEleTrigger23DEle2Eta");
 ///// Dname.push_back("TTOCEle2Eta");
 
 for (int j=0; j<Nname.size(); j++){
   if (Nname[j].Contains("Pt"))   var ="Pt";
   if (Nname[j].Contains("Eta"))  var ="Eta";
   if (Nname[j].Contains("Pho")) {lep1 ="Photon"; lep2=""     ; trig="OnePho";}
   if (Nname[j].Contains("Mu" )) {lep1 ="Mu1" ;   lep2 ="Mu2" ; trig="MuMu"; } 
   if (Nname[j].Contains("Ele")) {lep1 ="Ele1";   lep2 ="Ele2"; trig="EleEle";} 
   if (Nname[j].Contains("EMu")) {lep1 ="Ele" ;   lep2 ="Mu"  ; trig="EMu";}
   if (Nname[j].Contains("MuE")) {lep1 ="Mu"  ;   lep2 ="Ele" ; trig="MuE";}
   
   //name = sample[k]+":"+trig+" Trigger Turn on vs "+Dname[j]+": "+region+" Region ";
   name = sample[k]+":"+trig+" Trigger Turn on vs "+var+": "+region+" Region ";
   cout << "Plotting: "<<name<<endl;
   if( Dname[j].Contains("Eta") )  {unit = "";         }
   else                            {unit = "  [GeV]";  }
 cout<<inpath+sample[k]+"_"+region+"_histograms.root"<<endl;
 cout<<"h_"+region+"_"+Nname[j]<<endl;
 cout<<"h_"+region+"_"+Dname[j]<<endl;
   TString outname = outpath+region+"_"+sample[k]+"_TTOC"+Dname[j];
   TTOCNum    = (TH1F*)_file0->Get("h_"+region+"_"+Nname[j])->Clone("TTOCNum");
   TTOCDenom  = (TH1F*)_file0->Get("h_"+region+"_"+Dname[j])->Clone("TTOCDenom");

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
   
   //checking divide
   for(int i = 0; i <=TTOCNum->GetXaxis()->GetNbins()+1; i++){
   cout<<"*********************** Position: "  << TTOCNum->GetXaxis()->GetBinCenter(i)  <<endl;
   cout<<"Numerator: "  << (float)TTOCNum->GetBinContent(i)  <<endl;
   cout<<"Denominator: "<< (float)TTOCDenom->GetBinContent(i)<<endl;
   cout<<"Ratio: "      << gr_TTOC->Eval(TTOCNum->GetXaxis()->GetBinCenter(i))<< ",  Numerator/Denominator: "<<TTOCNum->GetBinContent(i)/TTOCDenom->GetBinContent(i)  <<endl;
   //cout<<endl;
   }
   
  
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
   gStyle->SetOptStat(0);
   gPad->Update();
   gPad->RedrawAxis();
 
   // save canvas
   canvas->SaveAs(outname+".png");
   canvas->SaveAs(outname+".pdf");
}//1D end

  twoD_Nname.clear();
  twoD_Dname.clear();
//  twoD_Nname.push_back("TTOCTriggerEMuPt");
//  twoD_Dname.push_back("TTOCEMuPt");
//  twoD_Nname.push_back("TTOCTriggerEMuEta");
//  twoD_Dname.push_back("TTOCEMuEta");
//  twoD_Nname.push_back("TTOCTriggerMuEPt");
//  twoD_Dname.push_back("TTOCMuEPt");
//  twoD_Nname.push_back("TTOCTriggerMuEEta");
//  twoD_Dname.push_back("TTOCMuEEta");
//
//  twoD_Nname.push_back("TTOCMuTriggerDMuPt");
//  twoD_Dname.push_back("TTOCMuPt");
//  twoD_Nname.push_back("TTOCMuTriggerDMuEta");
//  twoD_Dname.push_back("TTOCMuEta");
//  twoD_Nname.push_back("TTOCEleTrigger23DElePt");
//  twoD_Dname.push_back("TTOCElePt");
//  twoD_Nname.push_back("TTOCEleTrigger23DEleEta");
//  twoD_Dname.push_back("TTOCEleEta");
 for (int j=0; j<twoD_Nname.size(); j++){
   if (twoD_Nname[j].Contains("Pt"))   var ="Pt";
   if (twoD_Nname[j].Contains("Eta"))  var ="Eta";
   if (twoD_Nname[j].Contains("Pho")) {lep1 ="Photon"; lep2=""     ; trig="OnePho";}
   if (twoD_Nname[j].Contains("Mu" )) {lep1 ="Mu1" ;   lep2 ="Mu2" ; trig="MuMu"; } 
   if (twoD_Nname[j].Contains("Ele")) {lep1 ="Ele1";   lep2 ="Ele2"; trig="EleEle";} 
   if (twoD_Nname[j].Contains("EMu")) {lep1 ="Ele" ;   lep2 ="Mu"  ; trig="EMu";}
   if (twoD_Nname[j].Contains("MuE")) {lep1 ="Mu"  ;   lep2 ="Ele" ; trig="MuE";}
   twoD_name = sample[k]+": "+trig+" Trigger efficiency "+lep2+" vs. "+lep1+"  "+var+": "+region+" Region ";
   cout << "Plotting: "<<twoD_name<<endl;
   if( twoD_Dname[j].Contains("Eta") )  {unit = "";         }
   else                               {unit = "  [GeV]";  }
   TString outname2 = outpath+region+"_"+sample[k]+"_twoD_TTOC"+twoD_Dname[j];
   twoD_TTOCNum    = (TH2F*)_file0->Get("h_"+region+"_"+twoD_Nname[j])->Clone("twoD_TTOCNum");
   twoD_TTOCDenom  = (TH2F*)_file0->Get("h_"+region+"_"+twoD_Dname[j])->Clone("twoD_TTOCDenom");
   twoD_TTOCNum->Divide(twoD_TTOCDenom);
   // make canvas and text
   TCanvas* canvas2 = new TCanvas("canvas2","canvas2",900,100,500,500); 
   canvas2->Clear();
   canvas2->cd();
   TPad *pad2  = new TPad("pad2", "pad2", 0, 0, 1, 1);
   pad2->SetTickx();
   pad2->SetTicky();
   pad2->SetGrid();
   pad2->Draw();
   pad2->cd();
   gStyle->SetLineWidth(3);
   gStyle->SetPalette(kBird);
  
  //--twoD Style
  //h2_TTOC->SetLineWidth(2);
  //h2_TTOC->SetMarkerSize(1);
  //h2_TTOC->SetMarkerStyle(8);
  //h2_TTOC->SetMarkerColor(kAzure-2);
  //h2_TTOC->SetLineColor(kAzure-2);
   twoD_TTOCNum->SetTitle(twoD_name);
   twoD_TTOCNum->GetYaxis()->SetTitleOffset(1.25);
   twoD_TTOCNum->GetYaxis()->SetTitle(lep2+": "+var+unit);
   twoD_TTOCNum->GetXaxis()->SetTitle(lep1+": "+var+unit);
// }
  //h2_TTOC->GetZaxis()->SetTitle("Trigger Efficiency");
   twoD_TTOCNum->Draw("COLZ");
    gPad->Update();
    gPad->RedrawAxis();


    // save canvas
    canvas2->SaveAs(outname2+".png");
    canvas2->SaveAs(outname2+".pdf");
}//2D end
_file0->Close();
}//end sample loop
}
