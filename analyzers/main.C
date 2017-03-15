#include <iostream>
#include <fstream>
#include <unistd.h>

#include "analyzer_signal.h"
#include "TROOT.h"
#include <TChain.h>
#include <TString.h>
#include <TStopwatch.h>
 
#include <vector>
#include <map>
 
int main(int argc, char **argv){

 // start stopwatch
 TStopwatch sw;
 sw.Start();

 // for getting command line options
 // s - sample name
 // l - lumi
 // x - extra name
 // e - nr events to run over
 char *sample = NULL;
 char *slumi = (char*)"12900";
 char *sxname = (char*)"";
 char *sevts = (char*)"-1";
 char *jettype = (char*)"ALLCALOJETS";
 char *inpath = (char*)"../lists";
 char *outpath = (char*)"../roots";
 int index;
 int s;
 int l;
 int x;
 int j;
 int i;
 int o;

 opterr = 0;

 while ((s = getopt (argc, argv, "s:l:x:e:j:i:o:")) != -1)
  switch (s)
   {
   case 'o':
    outpath = optarg;
    break;
   case 'i':
    inpath = optarg;
    break;
   case 'j':
    jettype = optarg;
    break;
   case 'e':
    sevts = optarg;
    break;
   case 'x':
    sxname = optarg;
    break;
   case 'l':
    slumi = optarg;
    break;
   case 's':
    sample = optarg;
    break;
   case '?':
    if (optopt == 's' || optopt == 'l')
     fprintf (stderr, "Option -%c requires an argument.\n", optopt);
    else if (isprint (optopt))
     fprintf (stderr, "Unknown option `-%c'.\n", optopt);
    else
     fprintf (stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
    return 1;
   default:
    abort ();
   }

 for (index = optind; index < argc; index++)
   printf ("Non-option argument %s\n", argv[index]);

 printf ("Running sample:   %s\n", sample);

 // easiest if we convert char to TString
 TString Tsample  = TString(sample);
 TString Txname   = TString(sxname);
 TString TSlumi   = TString(slumi);
 Double_t lumi    = TSlumi.Atof();
 TString TSevts   = TString(sevts);
 Int_t TIevts     = TSevts.Atoi();
 TString Tjettype = TString(jettype);
 TString Tinpath   = TString(inpath);  
 TString Toutpath  = TString(outpath); 

  printf("Tsample:  %s\n",Tsample.Data());
  printf("Txname:   %s\n",Txname.Data());
  printf("TSlumi:   %s\n",TSlumi.Data());
  printf("TSevts:   %s\n",TSevts.Data());
  printf("Tjettype: %s\n",Tjettype.Data());
 // MC vs Data
 Bool_t isMC=kTRUE;
 Bool_t makelog=kTRUE;

 TString outfilename=Toutpath +"/"+Tsample+"_"+Tjettype+Txname;
 TString inputListName=Tinpath+"/"+Tsample+".list";
 TString inputInfoName=Tinpath+"/"+Tsample+".info";

 TChain *theChain = new TChain("treeR");
 theChain->Reset();

 printf("Input List Name:  %s\n", inputListName.Data()) ; 
 printf("Output File Name: %s.root\n", outfilename.Data()  ) ; 

 // lines read from file variables
 std::string inputline = "";
 TString Tinputline = "";
 std::vector<TString> inputline_dump;

 // ---- Get list of files to run over and put in TChain
 // open <samplename>.list
 std::ifstream inputfile;
 inputfile.open(inputListName);
 if( !inputfile.good() ) {
   std::cerr << "Cannot open the file: \"" << inputListName+"\""<<std::endl;
   abort();
 }
 
 // we have the file open, start reading lines one by one
 while( std::getline(inputfile, inputline) ) {
  if( inputfile.fail() ) continue;

  // TChain needs a TString..
  Tinputline = inputline;
  //printf("Inputline: %s\n",Tinputline.Data());

  // read input file names
  if( Tinputline.Contains("/store/group") ){
   //if( dolocal ){
   // theChain->Add( "root://cmseos.fnal.gov/"+Tinputline );
   //}
   //else{
    theChain->Add( "root://cmsxrootd.fnal.gov/"+Tinputline );
   //}
   printf("Inputfile: %s\n",Tinputline.Data());
  }

  inputline_dump.push_back(inputline);
 } //while !inputfile.eof()
 inputfile.close();

 // sample-dependent input variables 
 Double_t nrevents     ;
 Double_t crosssection ;

 // ---- Get sample information 
 // open <samplename>.info
 inputfile.open(inputInfoName);
 if( !inputfile.good() ) {
   std::cerr << "Cannot open the file: \"" << inputInfoName+"\""<<std::endl;
   abort();
 }
 
 // we have the file open, start reading lines one by one
 while( std::getline(inputfile, inputline) ) {
  if( inputfile.fail() ) continue;

  Tinputline = inputline;
  //printf("Inputline: %s\n",Tinputline.Data());

  // read crosssection
  if( Tinputline.Contains("crosssection: ") ){  
   Tinputline.ReplaceAll("crosssection: ","");
   crosssection = Tinputline.Atof();
   printf("  crosssection: %f\n",crosssection);
  }

  // read nr events
  if( Tinputline.Contains("nrevents: ") ){  
   Tinputline.ReplaceAll("nrevents: ","");
   nrevents = Tinputline.Atof();
   printf("  nrevents: %f\n",nrevents);
  }
  inputline_dump.push_back(inputline);
 } //while !inputfile.eof()

 printf("  lumi: %f\n\n",lumi);

 analyzer_signal a;
 a.Init(theChain, makelog, Tjettype);
 a.initSigHistograms();
 a.initJetHistograms();

 a.Loop(outfilename, isMC, lumi, nrevents, crosssection, TIevts);

 // end stopwatch
 sw.Stop();
 printf("Real Time: %0.3f minutes\n",sw.RealTime()/60.0);
 printf("CPU Time: %0.3f minutes\n",sw.CpuTime()/60.0);
 printf("Done with %s\n\n\n",Tsample.Data());

 return 0;
}
