
void dumpplots(){

 TString histotype="TH1";
 //TString histotype="TH2";

 // path to root files
 inpath  = TString("../roots");
 outpath = TString("../plots");
 //TString infilename = "DY5to50"; // no .root
 TString infilename = "DY50"; // no .root

 // y axis plots as log
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

 TFile* thefile = new TFile(inpath+"/"+infilename+".root"); 

 // set up iterator to loop
 TIter next(thefile->GetListOfKeys());
 TKey *key;
 while ((key = (TKey*)next())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom(histotype)) continue;
    TH1 *h = (TH1*)key->ReadObj();
    TString hname = key->GetName();
    if(histotype=="TH2"){h->Draw("colz");}
    else{h->Draw();}

   // add titles
   title->DrawTextNDC(0.13,0.91,"CMS");
   extra->DrawTextNDC(0.23,0.91,"Preliminary");
   lumi->DrawTextNDC(0.9,0.91,"20 /fb (13 TeV)");
   h->GetXaxis()->SetTitle(h->GetTitle());
   h->GetYaxis()->SetTitle("");
   h->SetTitle("");
   //h->GetYaxis()->SetTitle("Events / bin");

   gPad->Update();
   gPad->RedrawAxis();

   // save canvas
   canvas->SaveAs(outpath+"/"+infilename+"_"+hname+".png");
 }

}

