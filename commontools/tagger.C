
void tagger(){

bool variable_cut = false;
vector<TString> SigFileList;
vector<TString> BkgFileList;

//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS1000_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS1000_OPT.root");
SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS100_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS100_OPT.root");
//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS10_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS10_OPT.root");
//SigFileList.push_back("../roots/tagroots/ggZH_HToSSTobbbb_MS15_ctauS1_OPT.root");
//SigFileList.push_back("../roots/tagroots/ZH_HToSSTobbbb_MS15_ctauS1_OPT.root");

BkgFileList.push_back("../roots/tagroots/DY50_OPT.root");
//BkgFileList.push_back("../roots/tagroots/TTtoLfromT_OPT.root");
//BkgFileList.push_back("../roots/tagroots/TTtoLfromTbar_OPT.root");
//BkgFileList.push_back("../roots/tagroots/WJetsToLNu_OPT.root");

if(variable_cut){
const int NC = 100;
//vector<int> tags(NC+1,0);
//vector<float> num_sig(NC+1,0.0);// = 0.0;
float num_bkg = 0.0;
const float MIN = -3.0;
const float MAX = 3.0;
const float STEP = (MAX-MIN)/(NC*1.0);
//vector<float>  cut_val(NC+1,0.0);


//loop over signal files
for(int l = 0; l <SigFileList.size(); l++){
TFile file(SigFileList[l]);

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");

//num_sig.clear();
//tags.clear();


while (reader.Next()) {

for(int zz; zz<EventWeight->size(); zz++)
{
  for(int zx; zx<IP->size(); zx++){
  cout<<"IP: "<<IP->at(zx)<<endl;
  }
}
/*
 for(k = 0; k <=N; k++){
  cut_val[k] = MIN+ (float)k*STEP;
  for(int i = 0; i<EventWeight->size(); i++){
    //k is per cut value
    for (int j=0; j<IP->size(); j++){
      cout<<"IP: "<<IP->at(j)<<endl;
      if(IP->at(j)>=cut_val[k]){
      cout<<"true"<<endl;
      tags[k] = tags[k] + 1;
      }
    }
    if(tags[k] >=2){num_sig[k] = num_sig[k] + EventWeight->at(i);}
   }
  }
*/
}//while
}//Loop over sig files


/*
//loop over bkg files
for(int j = 0; j <BkgFileList.size(); j++){
TFile file(BkgFileList[j]);

TTreeReader reader("OPTtree", &file);
TTreeReaderValue<vector<int>>    Event(reader, "OPT_Event"); // template type must match datatype
TTreeReaderValue<vector<float>>  EventWeight(reader, "OPT_EventWeight"); // name must match branchname
TTreeReaderValue<vector<float>>  IP(reader, "OPT_AODCaloJetMedianLog10IPSig");

while (reader.Next()) {
  for(int i = 0; i<EventWeight->size(); i++){
    tags =0;
//    std::cout<<"Event: "<<Event->at(i)<< " EventWeight: " << EventWeight->at(i)<<std::endl;
//    cout<<"IP: ";
    for (int j=0; j<IP->size(); j++){
//      cout<<IP->at(j)<<",   ";
      if(IP->at(j)>CUT_VAL){
      tags = tags + 1;
      }
    }
    if(tags >=2){num_bkg = num_bkg + EventWeight->at(i);}
//    cout<<endl;
  }
//cout<<"Event Size: "          <<Event->size()<<endl;
//cout<<"EventWeight Size: "    <<EventWeight->size()<<endl;
//cout<<"Num_sig: "             <<num_sig<<"        tags: "             <<tags<<endl;
//cout<<"IP Size: "             <<IP->size()<<endl;
//cout<<"*********************************************************************************"<<endl;
}
}//Loop over bkg files

*/

 //for(int g = 0; g<Number.size(); g++){
 // std::cout<<"Number["<<g<<"]: "<< Number[g]<<" IPCut: "<<CutValue[g]<<std::endl;
 // NumByCut->SetPoint(g,CutValue[g],Number[g]); 
 // }
for(int a =0; a<=NC; a++){
//cout <<"Cut: " <<cut_val[a]<<"     Tag: "<<tags[a]<<"    Num_sig: "<<num_sig[a]<<endl;//"         Num_bkg: " <<num_bkg<<endl;
}
}//variable cut

else{
const float CUT_VAL = 0.5;
float tags;
float num_sig = 0.0;
float num_bkg = 0.0;
//loop over sig files
for(int i = 0; i <SigFileList.size(); i++){
TFile file(SigFileList[i]);

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
}//Loop over bkg files

//loop over bkg files
for(int j = 0; j <BkgFileList.size(); j++){
TFile file(BkgFileList[j]);

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
cout<<"Num_sig: "             <<num_sig<<"        tags: "             <<tags<<endl;
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

