#include <iostream>
#include <stdio.h>
#include <cmath>
 
void countevents(TString listname){
 
 printf("listname %s\n",listname.Data());
 Double_t ntotal = 0;
 Double_t nevents = 0;

 char* CMSSW_BASE;
 submitbase = getenv ("CMSSW_BASE");
 TString Tsubmitbase = TString(submitbase);
 TString fulllistname = Tsubmitbase+"/src/LLDJstandalones/lists/"+listname;

 printf("listname : %s \n",fulllistname.Data());

 std::fstream inputfile;
 inputfile.open(fulllistname);
 if( !inputfile.good() ) { 
   std::cerr << "Cannot open the file: \"" << fulllistname+"\""<<std::endl;
   abort();
 }

 // lines read from file variables to count number of events
 std::string inputline = ""; 
 TString Tinputline = ""; 

 while( std::getline(inputfile, inputline) ) { 
  if( inputfile.fail() ) continue;

  Tinputline = inputline;

  if( Tinputline.Contains("/store/group") ){  // if filename

   TFile* theFile;
   theFile = TFile::Open("root://cmseos.fnal.gov/"+Tinputline);

   TH1F* h_nevents;
   h_nevents = (TH1F*)theFile->Get("noCutSignature_COUNT");

   nevents=h_nevents->GetBinContent(1);
   ntotal+=nevents;
   printf("file: %s \n events: %.1f \n",Tinputline.Data(),nevents);
  }
 } //while getline
 inputfile.close();

 FILE * outfile;
 outfile = fopen (fulllistname,"a");
 fprintf (outfile, "nrevents: %.1f \n",ntotal);
 fclose (outfile);

 printf("--total: %.1f\n",ntotal);
 
}
