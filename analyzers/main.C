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
 Double_t nrEvents=22900.;
 Double_t crossSec=1.;

 TString path = "../test";

 // MC vs Data
 Bool_t isMC=kTRUE;
 Bool_t makelog=kTRUE;

 TString outfilename=path+"/test";
 TString inputListName=path+"/list_TT.txt";

 TChain *theChain = new TChain("tree_BASICCALOJETS1PT20MATCHED"); ;
 theChain->Reset();

 printf("Input List Name:  %s\n", inputListName.Data()) ; 
 printf("Output File Name: %s\n", outfilename.Data()  ) ; 

 std::vector<TString> infilename_dump;

 // open file_name_list.txt
 std::ifstream inputList;
 inputList.open(inputListName);
 if( !inputList.good() ) {
   std::cerr << "Cannot open the file: \"" << inputListName+"\""<<std::endl;
   abort();
 }
 // we have the file open, start reading lines one by one
 TString infilename = "";
 while( !inputList.eof() ) {
  infilename="";
  inputList >> infilename;
  if( inputList.fail() ) continue;

  std::cout << "Input File Name: "  << infilename <<  std::endl;

  theChain->Add( "root://cmsxrootd.fnal.gov/"+infilename );

  infilename_dump.push_back(infilename);
 } //while !inputList.eof()

  analyzer_signal a;
  a.Init(theChain, makelog);
  a.initSigHistograms();

  a.Loop(outfilename, isMC, lumi, nrEvents, crossSec);

 // end stopwatch
 sw.Stop();
 printf("Real Time: %0.3f minutes\n",sw.RealTime()/60.0);
 printf("CPU Time: %0.3f minutes\n",sw.CpuTime()/60.0);
 printf("Done\n");

 return 0;
}
