//
//
//
void tagger(){

bool variable_cut = false;
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

//loop cuts
for(int hh = 0; hh<2; hh++){
cut_val_[hh] = (MIN + (float)hh*STEP);
//loop over sig files
for(int i = 0; i <SigFileList.size(); i++){
tags_s.clear();
TFile file(SigFileList[i]);
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< SigFileList[i]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags_s[hh] =0;
    std::cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    cout<<"IP: ";
    for (int j=0; j<IP->size(); j++){
      cout<<IP->at(j)<<",   ";
      if(IP->at(j)>cut_val_[hh]){
      tags_s[hh] = tags_s[hh] + 1;
      }
    }
    if(tags_s[hh] >=2){num_sig_[hh] = num_sig_[hh] + EventWeight->at(i);}
    cout<<endl;
  }
cout<<"Event Size: "          <<Event->size()<<endl;
cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
cout<<"Num_sig: "             <<num_sig_[hh]<<"        tags: "             <<tags_s[hh]<<endl;
cout<<"IP Size: "             <<IP->size()<<endl;
cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
//loop over bkg files
for(int j = 0; j <BkgFileList.size(); j++){
tags_b.clear();
TFile file(BkgFileList[j]);
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< BkgFileList[j]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags_b[hh] =0;
    std::cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    cout<<"IP: ";
    for (int j=0; j<IP->size(); j++){
      cout<<IP->at(j)<<",   ";
      if(IP->at(j)>cut_val_[hh]){
      tags_b[hh] = tags_b[hh] + 1;
      }
    }
    if(tags_b[hh] >=2){num_bkg_[hh] = num_bkg_[hh] + EventWeight->at(i);}
    cout<<endl;
  }
cout<<"Event Size: "          <<Event->size()<<endl;
cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
cout<<"Num_bkg: "             <<num_bkg_[hh]<<"        tags: "             <<tags_b[hh]<<endl;
cout<<"IP Size: "             <<IP->size()<<endl;
cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files
/////cout <<"Num_sig: "<<num_sig<<"         Num_bkg: " <<num_bkg<<endl;

}//loop cuts
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
/////for(int hh = 0; hh<2; hh++){
//loop over sig files
for(int i = 0; i <SigFileList.size(); i++){
TFile file(SigFileList[i]);
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< SigFileList[i]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags =0;
    std::cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    cout<<"IP: ";
    for (int j=0; j<IP->size(); j++){
      cout<<IP->at(j)<<",   ";
      if(IP->at(j)>CUT_VAL){
      tags = tags + 1;
      }
    }
    if(tags >=2){num_sig = num_sig + EventWeight->at(i);}
    cout<<endl;
  }
cout<<"Event Size: "          <<Event->size()<<endl;
cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
cout<<"Num_sig: "             <<num_sig<<"        tags: "             <<tags<<endl;
cout<<"IP Size: "             <<IP->size()<<endl;
cout<<"*********************************************************************************"<<endl;
}
}//Loop over sig files
////}//test
//loop over bkg files
for(int j = 0; j <BkgFileList.size(); j++){
TFile file(BkgFileList[j]);
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout <<"Processing file: "<< BkgFileList[j]<<endl;

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags =0;
    std::cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
    cout<<"IP: ";
    for (int j=0; j<IP->size(); j++){
      cout<<IP->at(j)<<",   ";
      if(IP->at(j)>CUT_VAL){
      tags = tags + 1;
      }
    }
    if(tags >=2){num_bkg = num_bkg + EventWeight->at(i);}
    cout<<endl;
  }
cout<<"Event Size: "          <<Event->size()<<endl;
cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
cout<<"Num_bkg: "             <<num_bkg<<"        tags: "             <<tags<<endl;
cout<<"IP Size: "             <<IP->size()<<endl;
cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files
cout <<"Num_sig: "<<num_sig<<"         Num_bkg: " <<num_bkg<<endl;


}

 //for(int g = 0; g<Number.size(); g++){
 // std::cout<<"Number["<<g<<"]: "<< Number[g]<<" IPCut: "<<CutValue[g]<<std::endl;
 // NumByCut->SetPoint(g,CutValue[g],Number[g]); 
 // }
 //cout <<"tagssize: "<<tags.size()<<"    cutsize: "<<cut_val.size()<<"    sigsize: "<<num_sig.size()<<endl;
}

