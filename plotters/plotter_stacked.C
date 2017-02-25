
void plotter_stacked()
{

 // path to root files
 inpath  = TString("../roots/");
 outpath = TString("../plots/");

 // y axis plots as log
 Bool_t dolog = kTRUE;
 TString extraname = "";
 if(dolog){extraname+="_log";}

 // phase space regions to plot
 std::vector<TString> regions;
 regions.clear();
 regions.push_back("NoSel");
 regions.push_back("Sig");
 regions.push_back("ZH");
 regions.push_back("DY");
 regions.push_back("OffZ");
 regions.push_back("NoPair");

 // variables to plot
 std::vector<TString> variables;
 variables.clear();
 variables.push_back("PT");                   
 variables.push_back("NGOODVERTICES");        
 variables.push_back("ALPHAMAX");             
 variables.push_back("ASSOCAPLANARITY");      
 variables.push_back("ASSOCIATEDTRACKPT");    
 variables.push_back("ASSOCSPHERICITY");      
 variables.push_back("ASSOCTHRUSTMAJOR");     
 variables.push_back("ASSOCTHRUSTMINOR");     
 variables.push_back("AVFASSOCSPHERICITY");   
 variables.push_back("AVFASSOCTHRUSTMAJOR");  
 variables.push_back("AVFASSOCTHRUSTMINOR");  
 variables.push_back("BETA");                 
 variables.push_back("MEDIANIPLOG10SIG");     
 variables.push_back("MEDIANLOG10TRACKANGLE");
 variables.push_back("MISSINGINNER");         
 variables.push_back("SUMIP");                
 variables.push_back("SUMIPSIG");             
 variables.push_back("TOTALTRACKPT");         
 variables.push_back("TOTALTRACKANGLE");      
 variables.push_back("HT");                   
 variables.push_back("Max_LEPTON_DPHI");      
 variables.push_back("Max_MEDIANIPLOG10SIG"); 
 variables.push_back("Max_SUMIPSIG");         
 variables.push_back("Max_TOTALTRACKANGLE");  
 variables.push_back("MET");                  
 variables.push_back("Min_LEPTON_DPHI");      
 variables.push_back("Alt_MT");               
 variables.push_back("PTOSSF");               
 variables.push_back("Alt_WPT");              

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
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // load histogram files
 TFile* file_DY50     = new TFile(inpath+"DY50.root"); 
 TFile* file_DY5to50  = new TFile(inpath+"DY5to50.root");   
 TFile* file_STs      = new TFile(inpath+"STs.root");       
 TFile* file_STtbar   = new TFile(inpath+"STtbar.root");    
 TFile* file_STtbarW  = new TFile(inpath+"STtbarW.root");   
 TFile* file_STt      = new TFile(inpath+"STt.root");       
 TFile* file_STtW     = new TFile(inpath+"STtW.root");      
 TFile* file_TTbar    = new TFile(inpath+"TTbar.root");     
 TFile* file_WJets    = new TFile(inpath+"WJets.root");     
 TFile* file_WW       = new TFile(inpath+"WW.root");        
 TFile* file_WZ       = new TFile(inpath+"WZ.root");        
 TFile* file_ZZ       = new TFile(inpath+"ZZ.root");        
 TFile* file_ZHtoLLbb = new TFile(inpath+"ZHtoLLbb.root");  

 // initialize histos
 TH1F* h_DY50     ; 
 TH1F* h_DY5to50  ; 
 TH1F* h_STs      ; 
 TH1F* h_STtbar   ; 
 TH1F* h_STtbarW  ; 
 TH1F* h_STt      ; 
 TH1F* h_STtW     ; 
 TH1F* h_TTbar    ; 
 TH1F* h_WJets    ; 
 TH1F* h_WW       ; 
 TH1F* h_WZ       ; 
 TH1F* h_ZZ       ; 
 TH1F* h_ZHtoLLbb ; 

 // (combined) histos to be made
 TH1F* h_DY ;
 TH1F* h_ST ;
 TH1F* h_VV ;

 for(unsigned int i=0; i<regions.size(); ++i){
  TString region = regions[i];

  for(unsigned int j=0; j<variables.size(); ++j){
   TString variable = variables[j];

   TString varname = region+"_"+variable;

   printf("plotting  h_%s \n",varname.Data());

   // get histograms from files
   h_DY50     = (TH1F*)file_DY50    ->Get("h_"+varname)->Clone("h_DY50"); 
   h_DY5to50  = (TH1F*)file_DY5to50 ->Get("h_"+varname)->Clone("h_DY5to50"); 
   h_STs      = (TH1F*)file_STs     ->Get("h_"+varname)->Clone("h_STs"); 
   h_STtbar   = (TH1F*)file_STtbar  ->Get("h_"+varname)->Clone("h_STtbar"); 
   h_STtbarW  = (TH1F*)file_STtbarW ->Get("h_"+varname)->Clone("h_STtbarW"); 
   h_STt      = (TH1F*)file_STt     ->Get("h_"+varname)->Clone("h_STt"); 
   h_STtW     = (TH1F*)file_STtW    ->Get("h_"+varname)->Clone("h_STtW"); 
   h_TTbar    = (TH1F*)file_TTbar   ->Get("h_"+varname)->Clone("h_TTbar"); 
   h_WJets    = (TH1F*)file_WJets   ->Get("h_"+varname)->Clone("h_WJets"); 
   h_WW       = (TH1F*)file_WW      ->Get("h_"+varname)->Clone("h_WW"); 
   h_WZ       = (TH1F*)file_WZ      ->Get("h_"+varname)->Clone("h_WZ"); 
   h_ZZ       = (TH1F*)file_ZZ      ->Get("h_"+varname)->Clone("h_ZZ"); 
   h_ZHtoLLbb = (TH1F*)file_ZHtoLLbb->Get("h_"+varname)->Clone("h_ZHtoLLbb"); 

   // merge some histograms
   h_DY = (TH1F*)h_DY50->Clone("h_DY");
   h_DY->Add(h_DY5to50);

   h_ST = (TH1F*)h_STs->Clone("h_ST");
   h_ST->Add(h_STtbar);
   h_ST->Add(h_STtbarW);
   h_ST->Add(h_STt);
   h_ST->Add(h_STtW);

   h_VV = (TH1F*)h_WW->Clone("h_WW");
   h_VV->Add(h_WZ);
   h_VV->Add(h_ZZ);

   // set attributes
   h_DY       -> SetFillColor(kRed); 
   h_ST       -> SetFillColor(kGreen+1); 
   h_TTbar    -> SetFillColor(kGreen-9); 
   h_WJets    -> SetFillColor(kAzure+10); 
   h_VV       -> SetFillColor(kOrange-3); 
   h_ZHtoLLbb -> SetFillColor(kBlue); 

   h_DY       -> SetLineColor(kBlack); 
   h_ST       -> SetLineColor(kBlack); 
   h_TTbar    -> SetLineColor(kBlack); 
   h_WJets    -> SetLineColor(kBlack); 
   h_VV       -> SetLineColor(kBlack); 
   h_ZHtoLLbb -> SetLineColor(kBlack); 

   // make stack
   THStack *bgstack = new THStack("bgstack","");
   bgstack->Add(h_DY      ); 
   bgstack->Add(h_VV      ); 
   bgstack->Add(h_ST      ); 
   bgstack->Add(h_TTbar   ); 
   bgstack->Add(h_WJets   ); 
   bgstack->Add(h_ZHtoLLbb);

   // make legend
   TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
   leg->SetBorderSize(0);
   leg->SetFillColor(kWhite);
   leg->AddEntry(h_DY      , "Drell-Yan", "f"); 
   leg->AddEntry(h_VV      , "Diboson", "f"); 
   leg->AddEntry(h_ST      , "Single Top", "f"); 
   leg->AddEntry(h_TTbar   , "TTbar", "f"); 
   leg->AddEntry(h_WJets   , "W+Jets", "f"); 
   leg->AddEntry(h_ZHtoLLbb, "ZH#rightarrowLLbb", "f");
   
   // and draw
   bgstack->Draw("hist");
   leg->Draw();

   // add titles
   title->DrawTextNDC(0.13,0.91,"CMS");
   extra->DrawTextNDC(0.23,0.91,"Preliminary");
   lumi->DrawTextNDC(0.9,0.91,"20 /fb (13 TeV)");
   bgstack->GetXaxis()->SetTitle(h_TTbar->GetTitle());

   gPad->Update();
   gPad->RedrawAxis();

   // save canvas
   canvas->SaveAs(outpath+varname+extraname+".pdf");
 
  }
 }

}

