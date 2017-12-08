//can do variable cuts or specified cuts
//for specified edit lns 195-197, 161-163
//for vairable define cut 31-33, specify var 70-72,105-107
void tagger(){

bool variable_cut = false;
bool prnt         = false;
bool prnt2        = false;
vector<TString> SigFileList;
vector<TString> BkgFileList;

//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS1000_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS1000_OPT.root");
SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS100_OPT.root");
SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS100_OPT.root");
//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS10_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS10_OPT.root");
//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS1_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS1_OPT.root");

BkgFileList.push_back("../roots/tagroots/DY50_OPT.root");
BkgFileList.push_back("../roots/tagroots/TTtoLfromT_OPT.root");
BkgFileList.push_back("../roots/tagroots/TTtoLfromTbar_OPT.root");
BkgFileList.push_back("../roots/tagroots/WJetsToLNu_OPT.root");

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if(variable_cut){
const int NC = 100;
const float MIN = -3.0;
const float MAX = 3.0;
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
    for (int j=0; j<TA->size(); j++){
      if(prnt)cout<<TA->at(j)<<",   ";
      if(TA->at(j)>=cut_val_[hh]){
      tags_s[hh] = tags_s[hh] + 1;
      }
    }
    if(tags_s[hh] >=2){num_sig_[hh] = num_sig_[hh] + EventWeight->at(i);}
    if(prnt)cout<<endl;
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_sig: "             <<num_sig_[hh]<<"        tags: "             <<tags_s[hh]<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
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
    if(prnt)cout<<"IP: ";
    for (int j=0; j<TA->size(); j++){
      if(prnt)cout<<TA->at(j)<<",   ";
      if(TA->at(j)>=cut_val_[hh]){
      tags_b[hh] = tags_b[hh] + 1;
      }
    }
    if(tags_b[hh] >=2){num_bkg_[hh] = num_bkg_[hh] + EventWeight->at(i);}
    if(prnt)cout<<endl;
  }
if(prnt)cout<<"Event Size: "          <<Event->size()<<endl;
if(prnt)cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
if(prnt)cout<<"Num_bkg: "             <<num_bkg_[hh]<<"        tags: "             <<tags_b[hh]<<endl;
if(prnt)cout<<"IP Size: "             <<IP->size()<<endl;
if(prnt)cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files
if(prnt2)cout<<"cut_val: "<<cut_val_[hh]<<"   N_sig: "<<num_sig_[hh] <<"   N_bkg: "<<num_bkg_[hh]<<endl;
cv[hh] = cut_val_[hh];
if((num_sig_[hh] + num_bkg_[hh]) >0) ss = (num_sig_[hh]/( sqrt(num_sig_[hh] + num_bkg_[hh])) );
else ss=0.0;
if(ss> max_ss){ max_ss = ss; max_pos = cut_val_[hh];}
significance_[hh] = ss;
}//loop cuts
TGraph *eff = new TGraph(NC,cv, significance_);
eff->Draw();
cout<<"MaxSignificance: "<<max_ss<<"    CutValue: "<<max_pos<<endl;
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

