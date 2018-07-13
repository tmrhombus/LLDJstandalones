#ifndef analyzer_loop_h
#define analyzer_loop_h

#include "analyzer_tree.h"
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TMath.h>
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include <stdlib.h> 
class analyzer_loop : public analyzer_tree {

public :
 // basic functions
               analyzer_loop();
 virtual       ~analyzer_loop();
 virtual void  Loop(TString outfilename, 
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts,
                    TFile *optfile);
 static const int  width = 8;
 // debug options, printouts
 virtual void debug_printobjects();
 virtual void debug_printdilep();
 virtual void debug_printmuons();
 virtual void debug_printelectrons();
 virtual void debug_printphotons();
 virtual void debug_printjets();
 virtual void debug_printtriggers();
 virtual void debug_printbitset();
};

#endif
