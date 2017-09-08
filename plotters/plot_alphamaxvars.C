
void plot_alphamaxvars(){

 // path to root files
 TString outfilename = "amaxplots"  ;
 TString infilename1 = "testmc" ;

 TString inpath  = TString("../roots/amaxtime");
 TString outpath = TString("../plots/amaxtime");

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

 //TString selection = "h_NoLepSel_NoSel_SubleadingJet";
 TString selection = "h_NoLepSel_NoSel_LeadingJet";

 TString variable0 = "jetAlphaMaxD";
 TString variable1 = "jetAlphaMax_PV3onAll";
 TString variable2 = "jetAlphaMax_PV3onPV2";
 TString variable3 = "jetAlphaMax_PV3onNeu";
 TString variable4 = "AODCaloJetAlphaMax";       
 TString variable5 = "AODCaloJetAlphaMax2";      
 TString variable6 = "AODCaloJetAlphaMaxPrime";  
 TString variable7 = "AODCaloJetAlphaMaxPrime2"; 
 TString variable8 = "AODCaloJetBeta";           
 TString variable9 = "AODCaloJetBeta2";          

 // files and trees

 auto file1 = new TFile(inpath+"/"+infilename1+".root");

 gStyle->SetPalette(71); //kBlueGreenYellow

 TH1F *h0 = (TH1F*)file1->Get(selection+"_"+variable0)->Clone("h0"); 
 TH1F *h1 = (TH1F*)file1->Get(selection+"_"+variable1)->Clone("h1"); 
 TH1F *h2 = (TH1F*)file1->Get(selection+"_"+variable2)->Clone("h2"); 
 TH1F *h3 = (TH1F*)file1->Get(selection+"_"+variable3)->Clone("h3"); 
 TH1F *h4 = (TH1F*)file1->Get(selection+"_"+variable4)->Clone("h4"); 
 TH1F *h5 = (TH1F*)file1->Get(selection+"_"+variable5)->Clone("h5"); 
 TH1F *h6 = (TH1F*)file1->Get(selection+"_"+variable6)->Clone("h6"); 
 TH1F *h7 = (TH1F*)file1->Get(selection+"_"+variable7)->Clone("h7"); 
 TH1F *h8 = (TH1F*)file1->Get(selection+"_"+variable8)->Clone("h8"); 
 TH1F *h9 = (TH1F*)file1->Get(selection+"_"+variable9)->Clone("h9"); 

 h0->SetLineWidth(2);
 h1->SetLineWidth(2);
 h2->SetLineWidth(2);
 h3->SetLineWidth(2);
 h4->SetLineWidth(2);
 h5->SetLineWidth(2);
 h6->SetLineWidth(2);
 h7->SetLineWidth(2);
 h8->SetLineWidth(2);
 h9->SetLineWidth(2);

 //h0->SetLineColor(30);
 //h1->SetLineColor(30);
 //h2->SetLineColor(31);
 //h3->SetLineColor(32);
 //h4->SetLineColor(33);
 //h5->SetLineColor(34);
 //h6->SetLineColor(35);
 //h7->SetLineColor(36);

 h0->Scale(1./h0->Integral(0,-1));
 h1->Scale(1./h1->Integral(0,-1));
 h2->Scale(1./h2->Integral(0,-1));
 h3->Scale(1./h3->Integral(0,-1));
 h4->Scale(1./h4->Integral(0,-1));
 h5->Scale(1./h5->Integral(0,-1));
 h6->Scale(1./h6->Integral(0,-1));
 h7->Scale(1./h7->Integral(0,-1));
 h8->Scale(1./h8->Integral(0,-1));
 h9->Scale(1./h9->Integral(0,-1));

 h0->SetMaximum( 0.3 );
 //h0->SetMaximum( h0->GetMaximum()*1.8 );

 canvas->Clear();
 h0->Draw("hist PLC PMC");
 h1->Draw("hist SAME PLC PMC");
 //h2->Draw("hist SAME PLC PMC");
 //h3->Draw("hist SAME PLC PMC");
 h4->Draw("hist SAME PLC PMC");
// h5->Draw("hist SAME PLC PMC");
// h6->Draw("hist SAME PLC PMC");
// h7->Draw("hist SAME PLC PMC");
// h8->Draw("hist SAME PLC PMC");
// h9->Draw("hist SAME PLC PMC");

 // legend
 TLegend *leg = new TLegend(0.15,0.7,0.85,0.85);
 leg->SetNColumns(2);
 leg->SetBorderSize(0);
 leg->SetFillColor(kWhite);
 leg->AddEntry(h0, variable0, "l"); 
 leg->AddEntry(h1, variable1, "l"); 
 //leg->AddEntry(h2, variable2, "l"); 
 //leg->AddEntry(h3, variable3, "l"); 
 leg->AddEntry(h4, variable4, "l"); 
// leg->AddEntry(h5, variable5, "l"); 
// leg->AddEntry(h6, variable6, "l"); 
// leg->AddEntry(h7, variable7, "l"); 
// leg->AddEntry(h8, variable8, "l"); 
// leg->AddEntry(h9, variable9, "l"); 


 // add titles
 title->DrawTextNDC(0.13,0.91,"CMS");
 extra->DrawTextNDC(0.23,0.91,"Preliminary");
 lumi->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
 //h0->GetXaxis()->SetTitle("AlphaMax variations J2");
 h0->GetXaxis()->SetTitle("AlphaMax variations J1");
 h0->GetYaxis()->SetTitle("Unit Normalized");
 h0->GetYaxis()->SetTitleOffset(1.5);
 h0->SetTitle("");
 leg->Draw();
 gPad->Update();
 gPad->RedrawAxis();

 // save canvas
 //canvas->SaveAs(outpath+"/"+outfilename+"J2some.pdf");
 canvas->SaveAs(outpath+"/"+outfilename+"J1some.pdf");
 //canvas->SaveAs(outpath+"/"+outfilename+"_"+variable+".png");

}

