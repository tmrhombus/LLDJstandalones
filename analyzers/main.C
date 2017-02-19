#include <iostream>
#include <fstream>

#include "analyzer_signal.h"
#include "TROOT.h"
#include <TChain.h>
#include <TString.h>
#include <TStopwatch.h>
 
#include <vector>
#include <map>
 
int main(){

 // start stopwatch
 TStopwatch sw;
 sw.Start();

 Double_t lumi=12900.;
 TString path = "../test";

 // MC vs Data
 Bool_t isMC=kTRUE;
 Bool_t makelog=kTRUE;

 TString outfilename=path+"/test";
 TString inputListName=path+"/TTbar.txt";

 TChain *theChain = new TChain("tree_BASICCALOJETS1PT20MATCHED"); ;
 theChain->Reset();

 printf("Input List Name:  %s\n", inputListName.Data()) ; 
 printf("Output File Name: %s\n", outfilename.Data()  ) ; 

 std::vector<TString> inputline_dump;

  // sample-dependent input variables 
  Double_t nrEvents=22900.;
  Double_t crosssection=1.;

 // open file_name_list.txt
 std::ifstream inputfile;
 inputfile.open(inputListName);
 if( !inputfile.good() ) {
   std::cerr << "Cannot open the file: \"" << inputListName+"\""<<std::endl;
   abort();
 }

 // lines read from file variables
 std::string inputline = "";
 TString Tinputline = "";
 
 // we have the file open, start reading lines one by one
 //while( !inputfile.eof() ) {
 while( std::getline(inputfile, inputline) ) {
  if( inputfile.fail() ) continue;

  // TChain needs a TString..
  Tinputline = inputline;

  printf("Inputline: %s\n",Tinputline.Data());
  if( Tinputline.Contains("crosssection: ") ){  
   Tinputline.ReplaceAll("crosssection: ","");
   printf("Tinputline: %s %i\n",Tinputline.Data(),Tinputline.IsFloat());
   crosssection = Tinputline.Atof();
   //crosssection = TString::Atof(Tinputline);
   printf(" Cross Section Is:  %f\n",crosssection);
  }
  //if(line says nrevents){  }

  if( Tinputline.Contains("/store/group") ){
   std::cout << "Input File Name: "  << Tinputline <<  std::endl;

   theChain->Add( "root://cmsxrootd.fnal.gov/"+Tinputline );

   inputline_dump.push_back(inputline);
  }
 } //while !inputfile.eof()

  analyzer_signal a;
  a.Init(theChain, makelog);
  a.initSigHistograms();

  a.Loop(outfilename, isMC, lumi, nrEvents, crosssection);

 // end stopwatch
 sw.Stop();
 printf("Real Time: %0.3f minutes\n",sw.RealTime()/60.0);
 printf("CPU Time: %0.3f minutes\n",sw.CpuTime()/60.0);
 printf("Done\n");

 return 0;
}
