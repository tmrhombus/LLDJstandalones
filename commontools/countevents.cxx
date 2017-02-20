#include <iostream>
#include <cmath>
 
void countevents(TString listname){
 
 printf("listname %s\n",listname.Data());
 Double_t nevents = 0;

 char* CMSSW_BASE;
 submitbase = getenv ("CMSSW_BASE");
 TString Tsubmitbase = TString(submitbase);
 TString fulllistname = Tsubmitbase+"/src/LLDJstandalones/lists/"+listname;

 printf("listname : %s",fulllistname.Data());

 std::ifstream inputfile;
 inputfile.open(fulllistname);
 if( !inputfile.good() ) { 
   std::cerr << "Cannot open the file: \"" << fulllistname+"\""<<std::endl;
   abort();
 }

 // lines read from file variables
 std::string inputline = ""; 
 TString Tinputline = ""; 

 while( std::getline(inputfile, inputline) ) { 
  if( inputfile.fail() ) continue;

  // TChain needs a TString..
  Tinputline = inputline;

  if( Tinputline.Contains("/store/group") ){  // if filename

   //filename = TString("/store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHistos/allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_1.root") ;

   TFile* theFile;
   theFile = TFile::Open("root://cmseos.fnal.gov/"+Tinputline);
   //theFile = TFile::Open("root://cmseos.fnal.gov//store/group/lpchbb/noreplica/stata/AnalysisTrees/addedHistos/allHistos_TT_TuneCUETP8M1_13TeV-powheg-pythia8_1.root");

   TH1F* h_nevents;
   h_nevents = (TH1F*)theFile->Get("noCutSignature_COUNT");

   nevents+=h_nevents->GetBinContent(1);
   printf("prart: %f\n",nevents);
  }
 } //while !inputfile.eof()

 printf("nrevents: %f\n",nevents);
 printf("tot %f\n",nevents);
 
}
