#include <iostream>
#include <stdio.h>
#include <cmath>
 
void countevents(TString listname, Bool_t doSingle=kFALSE){
 
 printf("listname %s\n",listname.Data());
 Double_t ntotal = 0;
 Double_t nevents = 0;

 // doSingle reads out events for every file individually
 printf("doSingle %i\n",doSingle);

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

   // open file
   TFile* theFile;
   theFile = TFile::Open("root://cmseos.fnal.gov/"+Tinputline);

   // get histogram
   TH1F* h_nevents;
   h_nevents = (TH1F*)theFile->Get("noCutSignature_COUNT");

   // add bin contents to total count
   nevents=h_nevents->GetBinContent(1);
   ntotal+=nevents;
   printf("file: %s \n events: %.1f \n",Tinputline.Data(),nevents);

   // write each line w/ nrevents to indivdual file
   if(doSingle){

    // manually get outname from inputname on list.. ug
    std::string outname = inputline;
    UInt_t erase_a = outname.find("allHistos");
    outname.erase(0,erase_a+10);
    UInt_t erase_b = outname.find("_TuneCUETP");
    outname.erase(erase_b,erase_b+40);
    printf(" outname %s\n",outname.c_str());
    TString Toutname = outname;

    TString fulloutname = Tsubmitbase+"/src/LLDJstandalones/lists/"+outname+".txt";

    FILE * outfile;
    outfile = fopen (fulloutname,"w");
    fprintf (outfile, "%s \n",Tinputline.Data());
    fprintf (outfile, "crosssection: 1.0 \n");
    fprintf (outfile, "nrevents: %.1f \n",nevents);
    fclose (outfile);
 
   } // if doSingle
  } // if line contains /store/group
 } //while getline
 inputfile.close();

 // append nrevents to list file
 FILE * outfile;
 outfile = fopen (fulllistname,"a");
 fprintf (outfile, "nrevents: %.1f \n",ntotal);
 fclose (outfile);

 printf("--total: %.1f\n",ntotal);
 
}
