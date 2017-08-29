
void singlevarplot_analyzed(){

 // path to root files
 TString outfilename = "ggZH_MS40_bbbb"  ;
 TString baseinname  = "ggZH_HToSSTobbbb_MS40"   ;
 //TString baseinname  = "lldjntuple_mc"   ;
 //TString infilename1 = "ctauS0_0"     ;
 //TString infilename2 = "ctauS0p05_0"  ;
 //TString infilename3 = "ctauS1_0"     ;
 //TString infilename4 = "ctauS10_0"    ;
 //TString infilename5 = "ctauS100_0"   ;  
 //TString infilename6 = "ctauS1000_0"  ;   
 //TString infilename7 = "ctauS10000_0" ;  

 TString infilename1 = "ctauS0"     ;
 TString infilename2 = "ctauS0p05"  ;
 TString infilename3 = "ctauS1"     ;
 TString infilename4 = "ctauS10"    ;
 TString infilename5 = "ctauS100"   ;  
 TString infilename6 = "ctauS1000"  ;   
 TString infilename7 = "ctauS10000" ;  

 TString inpath  = TString("../roots/coulou");
 TString outpath = TString("../plots/coulou");
 //TString inpath  = TString("../roots/coulou_tight_sigonly");
 //TString outpath = TString("../plots/coulou_tight_sigonly");

 // y axis plots as log
 //Bool_t dolog = kFALSE;
 Bool_t dolog = kTRUE;
 TString extraname = "";
 if(dolog){extraname+="_log";}

 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);

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
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 TString chainname="lldjNtuple/EventTree";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMax";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMax2";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMaxP";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMaxP2";
 //TString variable = "h_mu_OffZ_LeadingJet_alphaMax_jetDauVertex_r";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMax_PV3onPV2";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMax_PV3onNeu";
 //TString variable = "h_NoLepSel_DY_LeadingJet_jetAlphaMax_PV3onAll";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMax_PV2onNeu";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlphaMax_PV2onAll";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlpha2Max_PV3onPV2";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlpha2Max_PV3onNeu";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlpha2Max_PV3onAll";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlpha2Max_PV2onNeu";
 //TString variable = "h_mu_OffZ_LeadingJet_jetAlpha2Max_PV2onAll";
 //TString variable = "h_NoLepSel_NoSel_LeadingJet_jetAlphaMax_PV3onAll";
 TString variable = "h_NoLepSel_NoSel_LeadingJet_jetAlphaMax_PV3onAll";
 //TString variable = "h_NoLepSel_NoSel_LeadingJet_jetAlphaD";
 //TString variable = "h_NoLepSel_NoSel_LeadingJet_jetAlphaMaxD";

 // files and trees

 auto file1 = new TFile(inpath+"/"+baseinname+"_"+infilename1+".root");
 auto file2 = new TFile(inpath+"/"+baseinname+"_"+infilename2+".root");
 auto file3 = new TFile(inpath+"/"+baseinname+"_"+infilename3+".root");
 auto file4 = new TFile(inpath+"/"+baseinname+"_"+infilename4+".root");
 auto file5 = new TFile(inpath+"/"+baseinname+"_"+infilename5+".root");
 auto file6 = new TFile(inpath+"/"+baseinname+"_"+infilename6+".root");
 auto file7 = new TFile(inpath+"/"+baseinname+"_"+infilename7+".root");

 gStyle->SetPalette(71); //kBlueGreenYellow

 TH1F *h1 = (TH1F*)file1->Get(variable)->Clone("h1"); 
 TH1F *h2 = (TH1F*)file2->Get(variable)->Clone("h2"); 
 TH1F *h3 = (TH1F*)file3->Get(variable)->Clone("h3"); 
 TH1F *h4 = (TH1F*)file4->Get(variable)->Clone("h4"); 
 TH1F *h5 = (TH1F*)file5->Get(variable)->Clone("h5"); 
 TH1F *h6 = (TH1F*)file6->Get(variable)->Clone("h6"); 
 TH1F *h7 = (TH1F*)file7->Get(variable)->Clone("h7"); 

 ////TH1F *h1 = nullptr;
 //Tree1->Draw("jetPt[0]>>h1","");
 //TH1F *h1 = (TH1F*)gDirectory->Get("h1");

 //Tree2->Draw("jetPt[0]>>h2","");
 //TH1F *h2 = (TH1F*)gDirectory->Get("h2");

 //Tree3->Draw("jetPt[0]>>h3","");
 //TH1F *h3 = (TH1F*)gDirectory->Get("h3");

 //Tree4->Draw("jetPt[0]>>h4","");
 //TH1F *h4 = (TH1F*)gDirectory->Get("h4");

 //Tree5->Draw("jetPt[0]>>h5","");
 //TH1F *h5 = (TH1F*)gDirectory->Get("h5");

 //Tree6->Draw("jetPt[0]>>h6","");
 //TH1F *h6 = (TH1F*)gDirectory->Get("h6");

 //Tree7->Draw("jetPt[0]>>h7","");
 //TH1F *h7 = (TH1F*)gDirectory->Get("h7");

   h1->SetLineWidth(2);
   h2->SetLineWidth(2);
   h3->SetLineWidth(2);
   h4->SetLineWidth(2);
   h5->SetLineWidth(2);
   h6->SetLineWidth(2);
   h7->SetLineWidth(2);

   h1->SetLineColor(30);
   h2->SetLineColor(31);
   h3->SetLineColor(32);
   h4->SetLineColor(33);
   h5->SetLineColor(34);
   h6->SetLineColor(35);
   h7->SetLineColor(36);

   h1->Scale(1./h1->Integral(0,-1));
   h2->Scale(1./h2->Integral(0,-1));
   h3->Scale(1./h3->Integral(0,-1));
   h4->Scale(1./h4->Integral(0,-1));
   h5->Scale(1./h5->Integral(0,-1));
   h6->Scale(1./h6->Integral(0,-1));
   h7->Scale(1./h7->Integral(0,-1));

   h1->SetMaximum( h1->GetMaximum()*1.8 );

   canvas->Clear();
   h1->Draw("hist PLC PMC");
   h2->Draw("hist SAME PLC PMC");
   h3->Draw("hist SAME PLC PMC");
   h4->Draw("hist SAME PLC PMC");
   h5->Draw("hist SAME PLC PMC");
   h6->Draw("hist SAME PLC PMC");
   h7->Draw("hist SAME PLC PMC");

   // legend
   TLegend *leg = new TLegend(0.15,0.7,0.85,0.85);
   leg->SetNColumns(2);
   leg->SetBorderSize(0);
   leg->SetFillColor(kWhite);
   leg->AddEntry(h1,infilename1, "l"); 
   leg->AddEntry(h2,infilename2, "l"); 
   leg->AddEntry(h3,infilename3, "l"); 
   leg->AddEntry(h4,infilename4, "l"); 
   leg->AddEntry(h5,infilename5, "l"); 
   leg->AddEntry(h6,infilename6, "l"); 
   leg->AddEntry(h7,infilename7, "l"); 


   // add titles
   title->DrawTextNDC(0.13,0.91,"CMS");
   extra->DrawTextNDC(0.23,0.91,"Preliminary");
   lumi->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
   h1->GetXaxis()->SetTitle(h1->GetTitle());
   h1->GetYaxis()->SetTitle("Unit Normalized");
   h1->GetYaxis()->SetTitleOffset(1.5);
   h1->SetTitle("");
   leg->Draw();
   gPad->Update();
   gPad->RedrawAxis();

   // save canvas
   canvas->SaveAs(outpath+"/"+outfilename+"_"+variable+".pdf");
   //canvas->SaveAs(outpath+"/"+outfilename+"_"+variable+".png");

}

