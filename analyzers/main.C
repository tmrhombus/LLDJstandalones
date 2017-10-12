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
 // j - jet type INCLUSIVETAGGEDCALOJETSAMATCHED
 // i - inpath
 // o - outpath
 // n - nfiles
 // a - start At file 
 // d - dolocal
 char *sample = NULL;
 char *slumi = (char*)"12900";
 char *sxname = (char*)"";
 char *sevts = (char*)"-1";
 char *inpath = (char*)"../lists";
 char *outpath = (char*)"../roots";
 char *nfiles = (char*)"-1";
 char *atfile = (char*)"0";
 bool dolocal = false;
 bool bisMC = false;
  
 int index;
 int s;
 double numberSignal;
 double numberBkg;
 opterr = 0;

 while ((s = getopt (argc, argv, "s:l:x:e:i:o:a:n:dm")) != -1)
  switch (s)
   {
   case 'm':
    bisMC = true;
   case 'd':
    dolocal = true;
    break;
   case 'a':
    atfile = optarg;
    break;
   case 'n':
    nfiles = optarg;
    break;
   case 'o':
    outpath = optarg;
    break;
   case 'i':
    inpath = optarg;
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
 TString Tinpath   = TString(inpath);  
 TString Toutpath  = TString(outpath); 
 TString TSatfile  = TString(atfile);  
 TString TSnfiles  = TString(nfiles);
 Int_t TIatfile = TSatfile.Atoi();
 Int_t TInfiles = TSnfiles.Atoi();
 // MC vs Data
 Bool_t isMC=bisMC;

 printf("Tsample:  %s\n",Tsample.Data());
 printf("Txname:   %s\n",Txname.Data());
 printf("TSlumi:   %s\n",TSlumi.Data());
 printf("TSevts:   %s\n",TSevts.Data());
 printf("TIatfile: %i\n",TIatfile);
 printf("TInfiles: %i\n",TInfiles);

 Bool_t makelog=kFALSE;

 TString outfilename=Toutpath +"/"+Tsample+Txname;
 TString inputListName=Tinpath+"/"+Tsample+".list";
 TString inputInfoName=Tinpath+"/"+Tsample+".info";

 TChain *theChain = new TChain("lldjNtuple/EventTree");
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
 
 // For dividing up input list
 Int_t nscanned = 0; // number of files scanned so far
 // we have the file open, start reading lines one by one
 while( std::getline(inputfile, inputline) ) {
  if( inputfile.fail() ) continue;

  nscanned++;
  if ( nscanned < TIatfile) continue;
  if ( nscanned >= (TIatfile+TInfiles) ) continue;

  // TChain needs a TString..
  Tinputline = inputline;
  //printf("Inputline: %s\n",Tinputline.Data());

  // read input file names
  if( Tinputline.Contains("/home/rhombus") ){
   theChain->Add( Tinputline );
   printf("Inputfile: %s\n",Tinputline.Data());
  }

  //if( Tinputline.Contains("/uscms/home") ){
  // theChain->Add( Tinputline );
  // printf("Inputfile: %s\n",Tinputline.Data());
  //}

  if( Tinputline.Contains("/uscms/home/ddiaz/") ){
   theChain->Add( Tinputline );
   printf("Inputfile: %s\n",Tinputline.Data());
  }

 /* if( Tinputline.Contains("/store/user") ){
    theChain->Add( "/hdfs"+Tinputline );
    //theChain->Add( "root://cmsxrootd.hep.wisc.edu/"+Tinputline );
  // //    theChain->Add( "root://cmsxrootd.fnal.gov/"+Tinputline );
  // }
   printf("Inputfile: %s\n",Tinputline.Data());
  }
*/
  // if( dolocal ){
  //  theChain->Add( "root://cmseos.fnal.gov/"+Tinputline );
  // }


  inputline_dump.push_back(inputline);
 } // while( std::getline(inputfile, inputline) )
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

 analyzer_signal analyzer;
 analyzer.Init(theChain, isMC, makelog);
 analyzer.initSigHistograms();
 analyzer.initJetHistograms();
 analyzer.init2DHistograms();

 analyzer.Loop(outfilename, lumi, nrevents, crosssection, TIevts);

 // end stopwatch
 sw.Stop();
 printf("Real Time: %0.3f minutes\n",sw.RealTime()/60.0);
 printf("CPU Time: %0.3f minutes\n",sw.CpuTime()/60.0);
 printf("Done with %s\n\n\n",Tsample.Data());

 return 0;
}
