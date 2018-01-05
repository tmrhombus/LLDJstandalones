//can do variable cuts or specified cuts
void tagger(){

bool variable_cut = true;
bool prnt         = false;
bool prnt2        = false;
bool plot         = true;
int  sel          = 3; //1=IP, 2=TA, 3/default=Alpha
TString xx = "0";
const float x = 0.0;
TString lifetime = "ctauS100";

vector<TString> SigFileList;
vector<TString> BkgFileList;
TString var;
if     (sel ==1){var = "MedianLog10IPSig";}
else if(sel ==2){var = "MedianLog10TrackAngle";}
else            {var = "AlphaMax";}
TString outpath = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/plots/tagging";

//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS1000_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS1000_OPT.root");
//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS100_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS100_OPT.root");
SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS10_OPT.root");
SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS10_OPT.root");
//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS1_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS1_OPT.root");

BkgFileList.push_back("../roots/tagroots/DY50_OPT.root");
//BkgFileList.push_back("../roots/tagroots/TTtoLfromT_OPT.root");
//BkgFileList.push_back("../roots/tagroots/TTtoLfromTbar_OPT.root");
BkgFileList.push_back("../roots/tagroots/WJetsToLNu_OPT.root");

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
        if(Alpha->at(j)<=cut_val_[hh] && Alpha->at(j)>=0.0){
        tags_s[hh] = tags_s[hh] + 1;
        }
      }
    }
    if(tags_s[hh] >=2){num_sig_[hh] = num_sig_[hh] + EventWeight->at(i);}
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
        if(Alpha->at(j)<=cut_val_[hh] && Alpha->at(j)>=0.0){
        tags_b[hh] = tags_b[hh] + 1;
        }
      }
    }
    if(tags_b[hh] >=2){num_bkg_[hh] = num_bkg_[hh] + EventWeight->at(i);}
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
  gPad->Update();
  gPad->RedrawAxis();
  canvas->Update(); 
  eff->SetMaximum( max_ss + 0.1*max_ss ); 
  //eff->GetXaxis()->SetLimits(sg1xa[0],0);//sg1xa[sig_g1->GetMaxSize()-1]);
  eff->GetXaxis()->SetLimits(cv[0],cv[NC]);
  eff->GetYaxis()->SetTitle("#frac{S}{#sqrt{S+B+"+xx+"B}}");
  eff->GetXaxis()->SetTitle("Cut Value");
  gPad->SetLeftMargin(0.15);
  eff->GetYaxis()->SetTitleOffset(2.0);
  eff->GetXaxis()->CenterTitle();
  eff->GetYaxis()->CenterTitle();
  eff->SetLineWidth(2);
  eff->Draw   ("AL"/*"*"*/);
  eff->SetTitle(var+"_"+lifetime);
  title->DrawTextNDC(0.06,0.91,"CMS");
  extra->DrawTextNDC(0.23,0.91,"Preliminary");
  lumi->DrawTextNDC(0.9,0.91,"xx /fb (13 TeV)");
  //leg->Draw();
  gPad->Update();
  gPad->RedrawAxis();
  gPad->Update();
  gPad->RedrawAxis();
  canvas->SaveAs(outpath+"/tagger_"+var+"_"+lifetime+"_sys"+xx+".pdf");
}

}//variable cut

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//non variable vut
else{
const float CUT_VAL = 0.5;
float tags;
float num_sig = 0.0;
float num_bkg = 0.0;
//loop over sig files
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
      if(Alpha->at(j)<=0.2 && IP->at(j)>=1.5 && TA->at(j)>=-1.08 && Alpha->at(j)!=-5 ){
      tags = tags + 1;
      }
    }
    if(tags >=2){num_sig = num_sig + EventWeight->at(i);}
    if(prnt)cout<<endl;
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
    tags =0;
    if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    if(prnt)cout<<"IP: ";
    for (int j=0; j<TA->size(); j++){/////////////////////////////////////////////////////////////////////////////////
      if(prnt)cout<<TA->at(j)<<",   ";
      if(Alpha->at(j)<=0.2 && IP->at(j)>=1.5 && TA->at(j)>=-1.08 && Alpha->at(j)!=-5 ){
      tags = tags + 1;
      }
    }
    if(tags >=2){num_bkg = num_bkg + EventWeight->at(i);}
    if(prnt)cout<<endl;
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_bkg: "             <<num_bkg<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files
cout <<"Num_sig: "<<num_sig<<"         Num_bkg: " <<num_bkg<<endl;


}//bkg non-var

}

