#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_tree.h"
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TMath.h>
#include "TTree.h"
#include "TBranch.h"
#include <stdlib.h> 
class analyzer_signal : public analyzer_tree {

public :
 // basic functions
               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, 
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts);
 
 // debug options, printouts
 virtual void debug_printobjects();
 virtual void debug_printmuons();
 virtual void debug_printelectrons();
 virtual void debug_printphotons();
 virtual void debug_printjets();
 virtual void debug_printtriggers();

};

#endif
