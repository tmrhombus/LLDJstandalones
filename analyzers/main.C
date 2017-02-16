//#include "plotshapesr.C"
//#include "plottf.C"
//#include "plotuncs.C"
//#include "plotsr.C"

#include <iostream>
#include <fstream>

//#include "analyzer_base.h"
#include "analyzer_signal.h"
#include "TROOT.h"
#include <TChain.h>
#include <TString.h>
//#include <Bool_t.h>
 
int main(){
 
    gROOT->ProcessLine("#include <vector>");
    gROOT->ProcessLine("#include <map>");

    //gSystem->Load("libDCache.so");
    //plotshapesr m;
    //plottf m;
    //plotuncs m;
    //plotsr m;


    TChain *theChain = new TChain("tree_BASICCALOJETS1PT20MATCHED"); ;
    theChain->Reset();

   // Double_t lumi=12900.;
   // Double_t nrEvents=12900.;
   // Double_t crossSec=1.;

    TString path = "../test";

     Bool_t isMC=kTRUE;

     TString outfilename=path+"/test.root";
     TString inputListName=path+"/list_TT.txt";
     


    printf("Input List Name:  %s\n", inputListName.Data()) ;  // << std::endl;
    printf("Output File Name: %s\n", outfilename.Data()  ) ;  // << std::endl;

    //std::cout << "Input List Name:  " << inputListName << std::endl;
    //std::cout << "Output File Name: " << outfilename << std::endl;

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

     theChain->Add( "root://cmsxrootd.fnal.gov//"+infilename );

     infilename_dump.push_back(infilename);
    } //while !inputList.eof()

     analyzer_signal a;
     a.Init(theChain);
     //a.Init();

     a.Loop();
     return 0;
}
