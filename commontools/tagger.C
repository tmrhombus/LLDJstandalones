///can do variable cuts or specified cuts
void tagger(Double_t c_ip, Double_t c_ta, Double_t c_al, int ntags, TString lifetime){

bool variable_cut = false;
bool plot         = false; //plots scanning result
TString outpath = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/plots/tagger/BarrelVEndcap/"+lifetime;
TString inpath  = "/uscms/home/ddiaz/nobackup/LLDJ_slc6_530_CMSSW_8_0_26_patch1/src/LLDJstandalones/roots/BarrelVEndcap/";
//1=IP, 2=TA, 3/default=Alpha
int  sel          = 3;
const float x     = 0.0; //for sys uncertainty

TString var;
if     (sel ==1){var = "MedianLog10IPSig";}
else if(sel ==2){var = "MedianLog10TrackAngle";}
else            {var = "AlphaMax";}

vector<TString> SigFileList;
vector<TString> BkgFileList;
//Big-hitters
//SigFileList.push_back( inpath+"ggZH_HToSSTobbbb_MS15_"+lifetime+"_OPTtree.root");
//SigFileList.push_back( inpath+"ZH_HToSSTobbbb_MS15_"  +lifetime+"_OPTtree.root");
SigFileList.push_back  ( inpath+"ggZH_HToSSTobbbb_MS40_"+lifetime+"_OPTtree.root");
SigFileList.push_back  ( inpath+"ZH_HToSSTobbbb_MS40_"  +lifetime+"_OPTtree.root");
//SigFileList.push_back( inpath+"ggZH_HToSSTobbbb_MS55_"+lifetime+"_OPTtree.root");
//SigFileList.push_back( inpath+"ZH_HToSSTobbbb_MS55_"  +lifetime+"_OPTtree.root");

BkgFileList.push_back( inpath+"DY50_OPTtree.root"         ); //kk=0
BkgFileList.push_back( inpath+"TTtoLfromT_OPTtree.root"   ); //kk=1
BkgFileList.push_back( inpath+"TTtoLfromTbar_OPTtree.root"); //kk=2
BkgFileList.push_back( inpath+"WJetsToLNu_OPTtree.root"   ); //kk=3
BkgFileList.push_back( inpath+"TTtoLL_OPTtree.root"       ); //kk=4

//little-guys
//single-top
BkgFileList.push_back( inpath+"ST_s_OPTtree.root"    ); //kk=5
BkgFileList.push_back( inpath+"ST_tW_OPTtree.root"   ); //kk=6
BkgFileList.push_back( inpath+"ST_t_OPTtree.root"    ); //kk=7
BkgFileList.push_back( inpath+"STbar_tW_OPTtree.root"); //kk=8
//BkgFileList.push_back( inpath+"STbar_t_OPTtree.root"); //kk=9
//diboson
BkgFileList.push_back( inpath+"WG_OPTtree.root"               ); //kk=10
BkgFileList.push_back( inpath+"WWToLNuLNu_OPTtree.root"      );//kk=11
BkgFileList.push_back( inpath+"WWToLNuQQ_OPTtree.root"        ); //kk=12
BkgFileList.push_back( inpath+"WZTo3LNu_OPTtree.root"         ); //kk=13
BkgFileList.push_back( inpath+"WZToL3Nu_OPTtree.root"         ); //kk=14
BkgFileList.push_back( inpath+"WZToLNu2QorQQ2L_OPTtree.root"  ); //kk=15
BkgFileList.push_back( inpath+"ZG_OPTtree.root"               ); //kk=16
//BkgFileList.push_back( inpath+"ZH_HToBB_ZToLL_OPTtree.root"  ); //kk=17
BkgFileList.push_back( inpath+"ZZToLLLL_OPTtree.root"         ); //kk=18
BkgFileList.push_back( inpath+"ZZToLLNuNu_OPTtree.root"       ); //kk=19
BkgFileList.push_back( inpath+"ZZToLLQQ_OPTtree.root"         ); //kk=20
BkgFileList.push_back( inpath+"ZZToNuNuQQ_OPTtree.root"       ); //kk=21
//BkgFileList.push_back( inpath+"ggZH_HToBB_ZToLL_OPTtree.root"); //kk=22
//control Region
///BkgFileList.push_back( inpath+"GJets_HT100To200_OPTtree.root");
///BkgFileList.push_back( inpath+"GJets_HT200To400_OPTtree.root");
///BkgFileList.push_back( inpath+"GJets_HT400To600_OPTtree.root");
///BkgFileList.push_back( inpath+"GJets_HT40To100_OPTtree.root");
///BkgFileList.push_back( inpath+"GJets_HT600ToInf_OPTtree.root");

TString nt, s_c_ip, s_c_ta, s_c_al, xx;
nt    .Form("%1d",ntags);
s_c_ip.Form("%1.2f",c_ip);
s_c_ta.Form("%1.2f",c_ta);
s_c_al.Form("%1.2f",c_al);
xx    .Form("%1.2f",x);

bool prnt         = false;
bool prnt2        = false;

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
const float STEP = (MAX-MIN)/((NC)*1.0);

vector<int>   tags_s(NC+1,0);
vector<int>   tags_b(NC+1,0);
vector<float> num_sig_(NC+1,0.0);// = 0.0;
vector<float> num_bkg_(NC+1,0.0);
vector<float> cut_val_(NC,0.0);
float cv[NC];

float ss=0.0;
float max_ss = 0.0;
float max_pos = 0.0;
float significance_[NC];

//loop cuts
for(int hh = 0; hh<=NC; hh++){
cut_val_[hh] = (MIN + (float)hh*STEP);
//loop over sig files
for(int ii = 0; ii <SigFileList.size(); ii++){
tags_s.clear();
TFile file(SigFileList[ii]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
///cout <<"Processing file: "<< SigFileList[i]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader, "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader, "OPT_AODCaloJetEta");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    //set initial #tags to 0
    tags_s[hh] =0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    			if(prnt)cout<<"IP: ";
    
    //apply cut increment #tags
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
        if(Alpha->at(j)<=cut_val_[hh] && Alpha->at(j)>=0.0 /*&& IP->at(j)>=1.00 && TA->at(j)>=-1.75*/){
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
for(int jj = 0; jj <BkgFileList.size(); jj++){
tags_b.clear();
TFile file(BkgFileList[jj]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
///cout <<"Processing file: "<< BkgFileList[j]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader, "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader, "OPT_AODCaloJetEta");

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
        if(Alpha->at(j)<=cut_val_[hh] && Alpha->at(j)>=0.0 /*&& IP->at(j)>=1.00 && TA->at(j)>=-1.75*/){
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
//for(int zzz=0; zzz<=NC+10; zzz++)
//{
//cout <<"iterator: "<<zzz<<"       alpha: "<<cv[zzz] <<"              significance: "<< significance_[zzz]<<endl;
//}
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

  canvas->SetGrid();
  //pad1->SetGrid();
  canvas->Update(); 
  eff->SetMaximum( max_ss + 0.1*max_ss ); 
  eff->GetXaxis()->SetLimits(cv[0],cv[NC-1]);
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
  gPad->Update();
  gPad->RedrawAxis();
  gPad->Update();
  gPad->RedrawAxis();
  canvas->SaveAs(outpath+"/"+nt+"_tags_"+var+"_"+lifetime+"_sys"+xx+".png");
  canvas->Clear();
}

}//end variable cut

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@










//non variable cut
else{

float tags, ntDY, ntTTL_T, ntTTL_Tbar, ntWJ, ntTTtoLL, ntDiboson, ntST;
//float nt
float num_sig = 0.0;
float num_bkg = 0.0;

TH1F* h_ntags      = new TH1F("h_ntags", "h_ntags", 7, -0.5, 6.5);
TH1F* h_ntDY       = new TH1F("h_ntDY", "h_ntDY", 7, -0.5, 6.5);
TH1F* h_ntTTL_T    = new TH1F("h_ntTTL_T", "h_ntTTL_T", 7, -0.5, 6.5);
TH1F* h_ntTTL_Tbar = new TH1F("h_ntTTL_Tbar", "h_ntTTL_Tbar", 7, -0.5, 6.5);
TH1F* h_ntWJ       = new TH1F("h_ntWJ", "h_ntWJ", 7, -0.5, 6.5);
TH1F* h_ntTTtoLL   = new TH1F("h_ntTTtoLL", "h_ntTTtoLL", 7, -0.5, 6.5);
TH1F* h_ntDiboson  = new TH1F("h_ntDiboson", "h_ntDiboson", 7, -0.5, 6.5);
TH1F* h_ntST       = new TH1F("h_ntSingleTop's", "h_ntSingleTop's", 7, -0.5, 6.5);

TH1F* h_Test       = new TH1F("h_Test", "h_Test", 50, 0, 500);
std::vector<TH1F *> v = {h_ntDY, h_ntTTL_T, h_ntTTL_Tbar, h_ntWJ, h_ntTTtoLL, h_ntDiboson, h_ntST};
//loop over sig files
for(int jj = 0; jj <SigFileList.size(); jj++){
TFile file(SigFileList[jj]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< SigFileList[jj]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader, "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader, "OPT_AODCaloJetEta");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags =0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    			if(prnt)cout<<"IP,TA,Alpha: "<<endl;
    for (int j=0; j<TA->size(); j++){
      			if(prnt)cout<<IP->at(j)<<"     "<<TA->at(j)<<"     "<<Alpha->at(j)<<endl;
      if(Alpha->at(j)<=c_al && IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0.0 && fabs(Eta->at(j))<=1.5){
      tags = tags + 1;
      }
    }
    if(tags >=ntags){num_sig = num_sig + EventWeight->at(i);}
    			if(prnt)cout<<endl;
    h_ntags->Fill(tags, EventWeight->at(i)); if(prnt){cout<<"File: " <<SigFileList[jj]<<" weight: " <<EventWeight->at(i)<<endl;}
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_sig: "             <<num_sig<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
//loop over bkg files
for(int kk = 0; kk <BkgFileList.size(); kk++){
TFile file(BkgFileList[kk]);
			if(prnt)cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< BkgFileList[kk]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  Pt(reader, "OPT_AODCaloJetPt");
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");
TTreeReaderValue<vector<float>>  TA(reader, "OPT_AODCaloJetMedianLog10TrackAngle");
TTreeReaderValue<vector<float>>  Alpha(reader, "OPT_AODCaloJetAlphaMax");
TTreeReaderValue<vector<float>>  Eta(reader, "OPT_AODCaloJetEta");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags       = 0;
    ntDY       = 0;
    ntTTL_T    = 0;
    ntTTL_Tbar = 0;
    ntWJ       = 0;
    ntTTtoLL   = 0;
    ntDiboson  = 0;
    ntST       = 0;
    			if(prnt)cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    			if(prnt)cout<<"IP,TA,Alpha: "<<endl;
    for (int j=0; j<TA->size(); j++){
      			if(prnt)cout<<IP->at(j)<<"     "<<TA->at(j)<<"     "<<Alpha->at(j)<<endl;
      h_Test->Fill(Pt->at(j));
      if(Alpha->at(j)<=c_al && IP->at(j)>=c_ip && TA->at(j)>=c_ta && Alpha->at(j)>=0.0 &&fabs(Eta->at(j))<=1.5 ){
      tags = tags + 1;
      if        (kk==0){ntDY = ntDY + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntDY<<endl;*/}
      else if   (kk==1){ntTTL_T = ntTTL_T + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntTTL_T<<endl;*/}
      else if   (kk==2){ntTTL_Tbar = ntTTL_Tbar + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: "<< ntTTL_Tbar<<endl;*/}
      else if   (kk==3){ntWJ = ntWJ + 1; /*cout <<"j: "<<j<<" "<<"   File: "<<BkgFileList[j]<<"  nt: " <<ntWJ<<endl;*/}
      else if   (kk==4){ntTTtoLL = ntTTtoLL +1;}
      else if   (kk>=10 && kk<=22){ntDiboson = ntDiboson + 1;}
      else if   (kk>=5  && kk<=9 ){ntST = ntST +1;}
      else      {i=i;}
      }
    }
    if(tags >=ntags){num_bkg = num_bkg + EventWeight->at(i);}
    			if(prnt)cout<<endl;
    if(kk==0)         {h_ntDY      ->Fill(ntDY, EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk==1)    {h_ntTTL_T   ->Fill(ntTTL_T, EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk==2)    {h_ntTTL_Tbar->Fill(ntTTL_Tbar, EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk==3)    {h_ntWJ      ->Fill(ntWJ, EventWeight->at(i)); if(prnt){cout <<"File: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
    else if(kk==4)    {h_ntTTtoLL  ->Fill(ntTTtoLL, EventWeight->at(i)); }
    else if(kk>=10 && kk<=22)    {h_ntDiboson  ->Fill(ntDiboson, EventWeight->at(i)); }
    else if(kk>=5  && kk<=9 )    {h_ntST       ->Fill(ntST,      EventWeight->at(i)); }
    else {h_ntDY->Fill(-3); h_ntTTL_T->Fill(-3); h_ntTTL_Tbar->Fill(-3); h_ntWJ->Fill(-3);if(prnt){cout <<"ErrorFile: "<<BkgFileList[kk]<< " weight(check): "<<EventWeight->at(i)<<", "<<EventWeight->at(i)<<endl;}}
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_bkg: "             <<num_bkg<<"        tags: "             <<tags<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//End Loop over bkg files
cout <<"Num_sig: "<<num_sig<<"         Num_bkg: " <<num_bkg<<endl;
if(plot){
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
  
  std::sort(v.begin(), v.end(),
              [](TH1F *a, TH1F *b) { return a->Integral() < b->Integral(); });
  //hs.Add(h_ntags);
  for(int zz=0; zz<v.size(); zz++)
  {
  hs->Add(v[zz]);
   }
  //h_ntDY      ->Draw   ("hist same");
  //h_ntTTL_T   ->Draw   ("hist same");
  //h_ntTTL_Tbar->Draw   ("hist same");
  //h_ntWJ      ->Draw   ("hist same");
  h_ntDY      ->SetFillColor(8);
  h_ntTTL_T   ->SetFillColor(9);
  h_ntTTL_Tbar->SetFillColor(41);
  h_ntWJ      ->SetFillColor(46);
  h_ntTTtoLL  ->SetFillColor(48);
  h_ntDiboson ->SetFillColor(42);
  h_ntST      ->SetFillColor(14);
  h_ntDY      ->SetLineColor(8);
  h_ntTTL_T   ->SetLineColor(9);
  h_ntTTL_Tbar->SetLineColor(41);
  h_ntWJ      ->SetLineColor(46);
  h_ntTTtoLL  ->SetLineColor(48);
  h_ntDiboson ->SetLineColor(42);
  h_ntST      ->SetLineColor(14);
  h_ntDY      ->SetLineWidth(3);
  h_ntTTL_T   ->SetLineWidth(3);
  h_ntTTL_Tbar->SetLineWidth(3);
  h_ntWJ      ->SetLineWidth(3);
  h_ntTTtoLL  ->SetLineWidth(3);
  h_ntDiboson ->SetLineWidth(3);
  h_ntST      ->SetLineWidth(3);
  
  h_Test->Draw("hist");
  //hs->Draw("hist");
  //hs->SetMinimum(0.001);
  //h_ntags     ->Draw   ("hist same");
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
  leg2->AddEntry(h_ntags,     "Signal", "l");
  leg2->AddEntry(h_ntDY,      "DY", "l");
  leg2->AddEntry(h_ntTTL_T,   "TTL_T", "l");
  leg2->AddEntry(h_ntTTL_Tbar,"TTL_Tbar", "l");
  leg2->AddEntry(h_ntWJ,      "WJ", "l");
  leg2->AddEntry(h_ntTTtoLL,  "TTtoLL", "l");
  leg2->AddEntry(h_ntDiboson, "Diboson", "l");
  leg2->AddEntry(h_ntST,      "ST", "l");
  leg2->Draw();
  //gStyle->SetOptStat(11);
  gPad->Update();
  gPad->RedrawAxis();
   canvas2->SaveAs(outpath+"h_Test.pdf"); 
 //canvas2->SaveAs(outpath+"/"+nt+"tags"+"_"+lifetime+"_cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+"_sys"+xx+".pdf");
  //canvas2->SaveAs(outpath+"/tags"+"_"+lifetime+"__cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+".png");
}// canvas2->SaveAs(outpath+"/"+nt+"tags"+"_"+lifetime+"_cip"+s_c_ip+"cta"+s_c_ta+"cal"+s_c_al+"_sys"+xx+".pdf");
}//bkg non-var

}

