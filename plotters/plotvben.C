/*
plot signal ID variables from lldj ntuples vs Ben's histograms
altering in/outpaths/names may be necessary

usage: root -l -b -q plotvben.C
*/

void plotvben(){

 // path for output
 TString outfilename = "plotvben_ggZH_MS40_bbbb"  ;
 TString outpath = "../plots"                     ;

 // path to root files
 lldjinpath  = TString("../roots/fromDaniel/ggZH");
 beninpath  = TString("../roots/fromBen");

 TString lldjbaseinname  = "lldjntuple_mc_MS40_cTauS"   ;
 TString lldjchainname="lldjNtuple/EventTree";

 // lifetimes being used
 // todo : make as vector, only make histos for
 //        lifetimes defined here
 //  .. I later found out Ben doesn't have 0 or 10000
 TString lifetime1   = "0" ;
 TString lifetime2   = "0p05" ;
 TString lifetime3   = "1" ;
 TString lifetime4   = "10" ;
 TString lifetime5   = "100" ;
 TString lifetime6   = "1000" ;
 TString lifetime7   = "10000" ;

 // variables to be plotted (titles get our names)
 // we assume that lldjvars and benvars match
 std::vector<TString> lldjvars;
 lldjvars.push_back("jetMedianLog10IPSig");
 lldjvars.push_back("jetMedianLogTrackAngle");

 std::vector<TString> benvars;
 //benvars.push_back("ALPHAMAX");
 benvars.push_back("MEDIANIPLOG10SIG");
 benvars.push_back("MEDIANLOG10TRACKANGLE");

 // took binnings to match Bens for plotting ease
 std::vector<TString> binnings;
 //binnings.push_back("(30,-1,1)");
 binnings.push_back("(20,-2,3)");
 binnings.push_back("(30,-5,1)");

 // set up canvas stuff once
 Bool_t dolog = kFALSE;
 //Bool_t dolog = kTRUE;
 TString extraname = "";
 if(dolog){extraname+="_log";}

 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);
 gStyle->SetPalette(71); //kBlueGreenYellow

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

 // start looping over variables
 for( int i=0; i<lldjvars.size(); ++i)
 {
  //printf("lldjvars %s benvars %s\n", lldjvars[i].Data(), benvars[i].Data() );
  // set local instances of variables from vector
  TString lldjvar = lldjvars[i].Data();
  TString benvar  = benvars[i].Data();
  TString binning = binnings[i].Data();

  // open files and access trees
  TFile* lldjfile1 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime1+".root");
  TTree* lldjtree1 = (TTree*)lldjfile1->Get(lldjchainname);

  TFile* lldjfile2 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime2+".root");
  TTree* lldjtree2 = (TTree*)lldjfile2->Get(lldjchainname);

  TFile* lldjfile3 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime3+".root");
  TTree* lldjtree3 = (TTree*)lldjfile3->Get(lldjchainname);

  TFile* lldjfile4 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime4+".root");
  TTree* lldjtree4 = (TTree*)lldjfile4->Get(lldjchainname);

  TFile* lldjfile5 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime5+".root");
  TTree* lldjtree5 = (TTree*)lldjfile5->Get(lldjchainname);

  TFile* lldjfile6 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime6+".root");
  TTree* lldjtree6 = (TTree*)lldjfile6->Get(lldjchainname);

  TFile* lldjfile7 = new TFile(lldjinpath+"/"+lldjbaseinname+lifetime7+".root");
  TTree* lldjtree7 = (TTree*)lldjfile7->Get(lldjchainname);

  // Ben's is easier since they're already stored as TH1D
  TString benbaseinname = "histos_ggZH_bbbb_MS-40_"+benvar+"_BASICCALOJETS1PT20";
  TFile* benfile = new TFile(beninpath+"/"+benbaseinname+".root");
  //printf(" %s/%s\n",beninpath.Data(),benbaseinname.Data());

  // get histograms
  lldjtree1->Draw(lldjvar+">>lldjh1"+binning,"");
  TH1F* lldjh1 = (TH1F*)gDirectory->Get("lldjh1");

  lldjtree2->Draw(lldjvar+">>lldjh2"+binning,"");
  TH1F* lldjh2 = (TH1F*)gDirectory->Get("lldjh2");

  lldjtree3->Draw(lldjvar+">>lldjh3"+binning,"");
  TH1F* lldjh3 = (TH1F*)gDirectory->Get("lldjh3");

  lldjtree4->Draw(lldjvar+">>lldjh4"+binning,"");
  TH1F* lldjh4 = (TH1F*)gDirectory->Get("lldjh4");

  lldjtree5->Draw(lldjvar+">>lldjh5"+binning,"");
  TH1F* lldjh5 = (TH1F*)gDirectory->Get("lldjh5");

  lldjtree6->Draw(lldjvar+">>lldjh6"+binning,"");
  TH1F* lldjh6 = (TH1F*)gDirectory->Get("lldjh6");

  lldjtree7->Draw(lldjvar+">>lldjh7"+binning,"");
  TH1F* lldjh7 = (TH1F*)gDirectory->Get("lldjh7");

  // I don't want to rewrite stuff in case he adds these samples later
  // so just comment out the lifetimes he doesn't have
  //TH1* benh1 = (TH1*)benfile->Get("h0")     ->Clone("benh1");
  TH1* benh2 = (TH1*)benfile->Get("h0p05")  ->Clone("benh2");
  TH1* benh3 = (TH1*)benfile->Get("h1")     ->Clone("benh3");
  TH1* benh4 = (TH1*)benfile->Get("h10")    ->Clone("benh4");
  TH1* benh5 = (TH1*)benfile->Get("h100")   ->Clone("benh5");
  TH1* benh6 = (TH1*)benfile->Get("h1000")  ->Clone("benh6");
  //TH1* benh7 = (TH1*)benfile->Get("h10000") ->Clone("benh7");

  // Set attributes for nice looking plots
  lldjh1->SetLineWidth(2);
  lldjh2->SetLineWidth(2);
  lldjh3->SetLineWidth(2);
  lldjh4->SetLineWidth(2);
  lldjh5->SetLineWidth(2);
  lldjh6->SetLineWidth(2);
  lldjh7->SetLineWidth(2);

  //benh1->SetLineWidth(3);
  benh2->SetLineWidth(3);
  benh3->SetLineWidth(3);
  benh4->SetLineWidth(3);
  benh5->SetLineWidth(3);
  benh6->SetLineWidth(3);
  //benh7->SetLineWidth(3);

  lldjh1->SetLineColor(30);
  lldjh2->SetLineColor(31);
  lldjh3->SetLineColor(32);
  lldjh4->SetLineColor(33);
  lldjh5->SetLineColor(34);
  lldjh6->SetLineColor(35);
  lldjh7->SetLineColor(36);

  //benh1->SetLineColor(40);
  benh2->SetLineColor(41);
  benh3->SetLineColor(42);
  benh4->SetLineColor(43);
  benh5->SetLineColor(44);
  benh6->SetLineColor(45);
  //benh7->SetLineColor(46);

  // normalize everything to unity
  lldjh1->Scale(1./lldjh1->Integral(0,-1));
  lldjh2->Scale(1./lldjh2->Integral(0,-1));
  lldjh3->Scale(1./lldjh3->Integral(0,-1));
  lldjh4->Scale(1./lldjh4->Integral(0,-1));
  lldjh5->Scale(1./lldjh5->Integral(0,-1));
  lldjh6->Scale(1./lldjh6->Integral(0,-1));
  lldjh7->Scale(1./lldjh7->Integral(0,-1));

  //benh1->Scale(1./benh1->Integral(0,-1));
  benh2->Scale(1./benh2->Integral(0,-1));
  benh3->Scale(1./benh3->Integral(0,-1));
  benh4->Scale(1./benh4->Integral(0,-1));
  benh5->Scale(1./benh5->Integral(0,-1));
  benh6->Scale(1./benh6->Integral(0,-1));
  //benh7->Scale(1./benh7->Integral(0,-1));

  // leave space at the top for the legend
  lldjh2->SetMaximum( lldjh2->GetMaximum()*2. );

  //// legend
  TLegend *leg = new TLegend(0.15,0.7,0.85,0.85);
  leg->SetNColumns(2);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  //leg->AddEntry(lldjh1,"lldj "+lifetime1, "l"); 
  leg->AddEntry(lldjh2,"lldj "+lifetime2, "l"); 
  leg->AddEntry(lldjh3,"lldj "+lifetime3, "l"); 
  leg->AddEntry(lldjh4,"lldj "+lifetime4, "l"); 
  leg->AddEntry(lldjh5,"lldj "+lifetime5, "l"); 
  leg->AddEntry(lldjh6,"lldj "+lifetime6, "l"); 
  //leg->AddEntry(lldjh7,"lldj "+lifetime7, "l"); 

  //leg->AddEntry(benh1,"ben "+lifetime1, "l"); 
  leg->AddEntry(benh2,"ben "+lifetime2, "l"); 
  leg->AddEntry(benh3,"ben "+lifetime3, "l"); 
  leg->AddEntry(benh4,"ben "+lifetime4, "l"); 
  leg->AddEntry(benh5,"ben "+lifetime5, "l"); 
  leg->AddEntry(benh6,"ben "+lifetime6, "l"); 
  //leg->AddEntry(benh7,"ben "+lifetime7, "l"); 

  // and draw
  canvas->Clear();
  //lldjh1->Draw("hist");
  lldjh2->Draw("hist");
  lldjh3->Draw("hist sames");
  lldjh4->Draw("hist sames");
  lldjh5->Draw("hist sames");
  lldjh6->Draw("hist sames");
  //lldjh7->Draw("hist sames");

  //benh1->Draw("hist sames");
  benh2->Draw("hist sames");
  benh3->Draw("hist sames");
  benh4->Draw("hist sames");
  benh5->Draw("hist sames");
  benh6->Draw("hist sames");
  //benh7->Draw("hist sames");

  // my version of root isn't new enough, but now
  // you nicely can auto choose colors from a palette
  //lldjh1->Draw("hist PLC PMC");
  //lldjh2->Draw("hist SAME PLC PMC");
  //lldjh3->Draw("hist SAME PLC PMC");
  //lldjh4->Draw("hist SAME PLC PMC");
  //lldjh5->Draw("hist SAME PLC PMC");
  //lldjh6->Draw("hist SAME PLC PMC");
  //lldjh7->Draw("hist SAME PLC PMC");

  // add titles
  title->DrawTextNDC(0.13,0.91,"CMS");
  extra->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
  lldjh2->GetXaxis()->SetTitle(lldjh2->GetTitle());
  lldjh2->GetYaxis()->SetTitle("Unit Normalized");
  lldjh2->GetYaxis()->SetTitleOffset(1.5);
  lldjh2->SetTitle("");
  leg->Draw();
  gPad->Update();
  gPad->RedrawAxis();

  // save canvas
  canvas->SaveAs(outpath+"/"+outfilename+"_"+lldjvar+".pdf");
  //canvas->SaveAs(outpath+"/"+outfilename+"_"+lldjvar+".png");
 }

}

