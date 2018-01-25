//can do variable cuts or specified cuts
void tagger(Double_t c_ip, Double_t c_ta, Double_t c_al, int ntags){

bool variable_cut = false;
bool plot         = false;
//const int ntags   = 2;
TString lifetime = "ctauS1";
TString outpath = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/plots/tagger/18_1_2018_tagger/"+lifetime;

//1=IP, 2=TA, 3/default=Alpha
int  sel          = 1;
const float x     = 0.0; //for sys uncertainty

TString var;
if     (sel ==1){var = "MedianLog10IPSig";}
else if(sel ==2){var = "MedianLog10TrackAngle";}
else            {var = "AlphaMax";}

vector<TString> SigFileList;
vector<TString> BkgFileList;

SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_"+lifetime+"_OPT.root");
SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_"+lifetime+"_OPT.root");

BkgFileList.push_back("../roots/tagroots/DY50_OPT.root");
BkgFileList.push_back("../roots/tagroots/TTtoLfromT_OPT.root");
BkgFileList.push_back("../roots/tagroots/TTtoLfromTbar_OPT.root");
BkgFileList.push_back("../roots/tagroots/WJetsToLNu_OPT.root");
TString nt, s_c_ip, s_c_ta, s_c_al, xx;
nt    .Form("%1d",ntags);
s_c_ip.Form("%1.2f",c_ip);
s_c_ta.Form("%1.2f",c_ta);
s_c_al.Form("%1.2f",c_al);
xx    .Form("%1.2f",x);
bool prnt         = false;
bool prnt2        = false;
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if(variable_cut){
const int NC = 100;
float MAX;
float MIN;
if(sel==1){
 MIN = -3.0;
 MAX = 3.0;
}
else if(sel==2){
 MIN = -3.0;
 MAX = 3.0;
}
else{
 MIN = 0.0;
 MAX = 1.0;
}
const float STEP = (MAX-MIN)/(NC*1.0);

vector<int>   tags_s(NC+1,0);
vector<int>   tags_b(NC+1,0);
vector<float> num_sig_(NC+1,0.0);// = 0.0;
vector<float> num_bkg_(NC+1,0.0);
vector<float> cut_val_(NC+1,0.0);
float cv[NC+1];

float ss=0.0;
float max_ss = 0.0;
float max_pos = 0.0;
float significance_[NC+1];

//loop cuts
for(int hh = 0; hh<=NC; hh++){
cut_val_[hh] = (MIN + (float)hh*STEP);
//loop over sig files
for(int i = 0; i <SigFileList.size(); i++){
tags_s.clear();
TFile file(SigFileList[i]);
if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
///cout <<"Processing file: "<< SigFileList[i]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags_s[hh] =0;
    if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    if(prnt)cout<<"IP: ";
    if(sel ==1){
    if(prnt)cout<<"IP: ";
      for (int j=0; j<IP->size(); j++){
        if(prnt)cout<<IP->at(j)<<",   ";
        if(IP->at(j)>=cut_val_[hh]){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    else if(sel ==2){
    if(prnt)cout<<"TA: ";
      for (int j=0; j<TA->size(); j++){
        if(prnt)cout<<TA->at(j)<<",   ";
        if(TA->at(j)>=cut_val_[hh]){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    else{
    if(prnt)cout<<"Alpha: ";
      for (int j=0; j<Alpha->size(); j++){
        if(prnt)cout<<Alpha->at(j)<<",   ";
        if(Alpha->at(j)<=cut_val_[hh]){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    if(tags_s[hh] >=ntags){num_sig_[hh] = num_sig_[hh] + EventWeight->at(i);}
    if(prnt)cout<<endl;
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_sig: "             <<num_sig_[hh]<<"        tags: "             <<tags_s[hh]<<endl;
if(sel ==1){
  if(prnt)cout<<"IP Size: "                <<IP->size()<<endl;
}
else if(sel ==2){
  if(prnt)cout<<"TA Size: "                <<TA->size()<<endl;
}
else{
  if(prnt)cout<<"Alpha Size: "             <<Alpha->size()<<endl;
}
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
//loop over bkg files
for(int j = 0; j <BkgFileList.size(); j++){
tags_b.clear();
TFile file(BkgFileList[j]);
if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
///cout <<"Processing file: "<< BkgFileList[j]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags_b[hh] =0;
    if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    if(sel ==1){
    if(prnt)cout<<"IP: ";
      for (int j=0; j<IP->size(); j++){
        if(prnt)cout<<IP->at(j)<<",   ";
        if(IP->at(j)>=cut_val_[hh]){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    else if(sel ==2){
    if(prnt)cout<<"TA: ";
      for (int j=0; j<TA->size(); j++){
        if(prnt)cout<<TA->at(j)<<",   ";
        if(TA->at(j)>=cut_val_[hh]){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    else{
    if(prnt)cout<<"Alpha: ";
      for (int j=0; j<Alpha->size(); j++){
        if(prnt)cout<<Alpha->at(j)<<",   ";
        if(Alpha->at(j)<=cut_val_[hh]){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    if(tags_b[hh] >=ntags){num_bkg_[hh] = num_bkg_[hh] + EventWeight->at(i);}
    if(prnt)cout<<endl;
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_bkg: "             <<num_bkg_[hh]<<"        tags: "             <<tags_b[hh]<<endl;
if(sel ==1){
  if(prnt)cout<<"IP Size: "                <<IP->size()<<endl;
}
else if(sel ==2){
  if(prnt)cout<<"TA Size: "                <<TA->size()<<endl;
}
else{
  if(prnt)cout<<"Alpha Size: "             <<Alpha->size()<<endl;
}
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files
if(prnt2)cout<<"cut_val: "<<cut_val_[hh]<<"   N_sig: "<<num_sig_[hh] <<"   N_bkg: "<<num_bkg_[hh]<<endl;
cv[hh] = cut_val_[hh];
if((num_sig_[hh] + num_bkg_[hh]) >0) ss = (num_sig_[hh]/( sqrt(num_sig_[hh] + num_bkg_[hh]+ x*num_bkg_[hh])  ) );
else ss=0.0;
if(ss> max_ss){ max_ss = ss; max_pos = cut_val_[hh];}
significance_[hh] = ss;
}//loop cuts
TGraph *eff = new TGraph(NC,cv, significance_);
eff->Draw();
cout<<"MaxSignificance: "<<max_ss<<"    CutValue: "<<max_pos<<endl;
// ######## Print out #######
if(plot){
  TCanvas* canvas = new TCanvas("canvas","canvas",1280,1024);
  canvas->Clear();
  canvas->cd();
  canvas->SetGrid();
  TPad *pad1  = new TPad("pad1", "pad1", 0, 0.0, 1, 1);
  gStyle->SetOptStat(0);
  //pad1->SetLogy(dolog);
  pad1->SetTickx();
  pad1->SetTicky(); 
  pad1->Draw();
  pad1->SetGrid();
  pad1->SetFillStyle(4000);
  pad1->cd();
  gStyle->SetLineWidth(2);
  gStyle->SetPalette(71);

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

  //->GetXaxis()->SetTitle("E_{#gamma} (GeV)"); 
  //gPad->Update();
  //gPad->RedrawAxis();
  canvas->SetGrid();
  //pad1->SetGrid();
  canvas->Update(); 
  eff->SetMaximum( max_ss + 0.1*max_ss ); 
  //eff->GetXaxis()->SetLimits(sg1xa[0],0);//sg1xa[sig_g1->GetMaxSize()-1]);
  eff->GetXaxis()->SetLimits(cv[0],cv[NC]);
  eff->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B+"+xx+"*B}}");
  eff->GetXaxis()->SetTitle("Cut Value");
  gPad->SetLeftMargin(0.15);
  eff->GetYaxis()->SetTitleOffset(2.0);
  eff->GetXaxis()->CenterTitle();
  eff->GetYaxis()->CenterTitle();
  eff->SetLineWidth(2);
  eff->Draw   ("AL"/*"*"*/);
  eff->SetTitle("gte"+nt+"_tags;"+var+"_"+lifetime);
  title->DrawTextNDC(0.06,0.91,"CMS");
  extra->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
  //leg->Draw();
  gPad->Update();
  gPad->RedrawAxis();
  gPad->Update();
  gPad->RedrawAxis();
  canvas->SaveAs(outpath+"/"+nt+"_tags_"+var+"_"+lifetime+"_sys"+xx+".png");
  canvas->Clear();
}

}//end variable cut

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//non variable cut
else{
//const float CUT_VAL = 0.5;
float tags, ntDY, ntTTL_T, ntTTL_Tbar, ntWJ;
float num_sig = 0.0;
float num_bkg = 0.0;
//loop over sig files
TH1F* h_ntags      = new TH1F("h_ntags", "h_ntags", 7, -0.5, 6.5);
TH1F* h_ntDY       = new TH1F("h_ntDY", "h_ntDY", 7, -0.5, 6.5);
TH1F* h_ntTTL_T    = new TH1F("h_ntTTL_T", "h_ntTTL_T", 7, -0.5, 6.5);
TH1F* h_ntTTL_Tbar = new TH1F("h_ntTTL_Tbar", "h_ntTTL_Tbar", 7, -0.5, 6.5);
TH1F* h_ntWJ       = new TH1F("h_ntWJ", "h_ntWJ", 7, -0.5, 6.5);
for(int i = 0; i <SigFileList.size(); i++){
TFile file(SigFileList[i]);
if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< SigFileList[i]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags =0;
    if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    if(prnt)cout<<"IP: ";
    for (int j=0; j<TA->size(); j++){///////////////////////////////////////////////////////////////////////////////
      if(prnt)cout<<TA->at(j)<<",   ";
      if(Alpha->at(j)<=c_al && IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0 ){
      tags = tags + 1;
      }
    }
    if(tags >=ntags){num_sig = num_sig + EventWeight->at(i);}
    if(prnt)cout<<endl;
    h_ntags->Fill(tags, EventWeight->at(i));
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_sig: "             <<num_sig<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
//loop over bkg files
for(int j = 0; j <BkgFileList.size(); j++){
TFile file(BkgFileList[j]);
if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< BkgFileList[j]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    float weight = EventWeight->at(i);
    tags       = 0;
    ntDY       = 0;
    ntTTL_T    = 0;
    ntTTL_Tbar = 0;
    ntWJ       = 0;
    if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    if(prnt)cout<<"IP: ";
    for (int j=0; j<TA->size(); j++){/////////////////////////////////////////////////////////////////////////////////
      if(prnt)cout<<TA->at(j)<<",   ";
      if(Alpha->at(j)<=c_al && IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0 ){
      tags = tags + 1;
      if(j==0){ntDY = ntDY +1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntDY<<endl;*/}
      else if(j==1){ntTTL_T = ntTTL_T +1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntTTL_T<<endl;*/}
      else if(j==2){ntTTL_Tbar = ntTTL_Tbar +1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntTTL_Tbar<<endl;*/}
      else {ntWJ = ntWJ +1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: " <<ntWJ<<endl;*/}
      }
    }
    if(tags >=ntags){num_bkg = num_bkg + EventWeight->at(i);}
    if(prnt)cout<<endl;
    if(j==0)         h_ntDY      ->Fill(ntDY, weight);
    else if(j==1)    h_ntTTL_T   ->Fill(ntTTL_T, weight);
    else if(j==2)    h_ntTTL_Tbar->Fill(ntTTL_Tbar, weight);
    else if(j==3)    h_ntWJ      ->Fill(ntWJ, weight);
    else {h_ntDY->Fill(-3); h_ntTTL_T->Fill(-3); h_ntTTL_Tbar->Fill(-3); h_ntWJ->Fill(-3);}
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_bkg: "             <<num_bkg<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//End Loop over bkg files
cout <<"Num_sig: "<<num_sig<<"         Num_bkg: " <<num_bkg<<endl;

  //canvas stuff
  //Bool_t dolog = kFALSE;
  Bool_t dolog = kTRUE;
  //TString extraname = "";
  //if(dolog){extraname+="_log";}
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",1280,1024);
  canvas2->Clear();
  canvas2->cd();
  canvas2->SetGrid();
  TPad *pad2  = new TPad("pad2", "pad2", 0, 0.0, 1, 1);
  gStyle->SetOptStat(0);
  pad2->SetLogy(dolog);
  pad2->SetTickx();
  pad2->SetTicky(); 
  pad2->Draw();
  pad2->SetGrid();
  pad2->SetFillStyle(4000);
  pad2->cd();
  gStyle->SetLineWidth(2);
  gStyle->SetPalette(71);

  TText* title2 = new TText(1,1,"") ; 
  title2->SetTextSize(0.04);
  title2->SetTextColor(kBlack);
  title2->SetTextAlign(11);
  title2->SetTextFont(62);

  TText* extra2 = new TText(1,1,"") ;
  extra2->SetTextSize(0.04);
  extra2->SetTextColor(kBlack);
  extra2->SetTextAlign(11);
  extra2->SetTextFont(52);

  TText* lumi2 = new TText(1,1,"") ;
  lumi2->SetTextSize(0.03);
  lumi2->SetTextColor(kBlack);
  lumi2->SetTextAlign(31);
  lumi2->SetTextFont(42);

  canvas2->Update(); 
  h_ntags->GetXaxis()->SetTitle("Number of tags");
  gPad->SetLeftMargin(0.15);
  h_ntags->GetYaxis()->SetTitleOffset(2.0);
  h_ntags->GetXaxis()->CenterTitle();
  h_ntags->GetYaxis()->CenterTitle();
  h_ntags->SetLineWidth(3);
  h_ntags      ->SetLineColor(1);
  THStack *hs = new THStack("hs","Number of tags");
  //hs.Add(h_ntags);
  hs->Add(h_ntDY);
  hs->Add(h_ntTTL_T);
  hs->Add(h_ntTTL_Tbar);
  hs->Add(h_ntWJ);
  //h_ntDY      ->Draw   ("hist same");
  //h_ntTTL_T   ->Draw   ("hist same");
  //h_ntTTL_Tbar->Draw   ("hist same");
  //h_ntWJ      ->Draw   ("hist same");
  h_ntDY      ->SetFillColor(8);
  h_ntTTL_T   ->SetFillColor(9);
  h_ntTTL_Tbar->SetFillColor(41);
  h_ntWJ      ->SetFillColor(46);
  h_ntDY      ->SetLineColor(8);
  h_ntTTL_T   ->SetLineColor(9);
  h_ntTTL_Tbar->SetLineColor(41);
  h_ntWJ      ->SetLineColor(46);
  h_ntDY      ->SetLineWidth(3);
  h_ntTTL_T   ->SetLineWidth(3);
  h_ntTTL_Tbar->SetLineWidth(3);
  h_ntWJ      ->SetLineWidth(3);
  hs->Draw("hist");
  hs->SetMinimum(1.0);
  h_ntags     ->Draw   ("hist same");
  hs->SetTitle("cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+":N tags,"+lifetime);
  title2->DrawTextNDC(0.06,0.91,"CMS");
  extra2->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi2->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
  TLegend *leg2 = new TLegend(0.6,0.6,0.9,0.85);
  leg2->SetNColumns(2);
  leg2->SetBorderSize(1);
  leg2->SetTextSize(.03);
  TString entries;
  entries.Form("%1.0f",h_ntags->GetEntries());
  //leg2->AddEntry(h_ntags,   entries+" entries", "l");
  leg2->AddEntry(h_ntags,   "Signal", "l");
  leg2->AddEntry(h_ntDY,   "DY", "l");
  leg2->AddEntry(h_ntTTL_T,   "TTL_T", "l");
  leg2->AddEntry(h_ntTTL_Tbar,   "TTL_Tbar", "l");
  leg2->AddEntry(h_ntWJ,   "WJ", "l");
  leg2->Draw();
  //gStyle->SetOptStat(11);
  gPad->Update();
  gPad->RedrawAxis();
  
  canvas2->SaveAs(outpath+"/tags"+"_"+lifetime+"__cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+".png");
  //canvas2->SaveAs(outpath+"/"+nt+"tags"+"_"+lifetime+"_cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+"_sys"+xx+".pdf");

}//bkg non-var

}

