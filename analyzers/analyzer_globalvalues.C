#include "analyzer_globalvalues.h"

//----------------------------analyzer_globalvalues
analyzer_globalvalues::analyzer_globalvalues() 
{
}

//----------------------------~analyzer_globalvalues
analyzer_globalvalues::~analyzer_globalvalues()
{
}

//----------------------------~clearglobalcounters
void analyzer_globalvalues::clearglobalcounters()
{

 n_tot   = 0;

 n_passOneEleSig    = 0;
 n_passTwoEleSig    = 0;
 n_passOneMuSig     = 0;
 n_passTwoMuSig     = 0;
 n_passOneEleDY     = 0;
 n_passTwoEleDY     = 0;
 n_passOneMuDY      = 0;
 n_passTwoMuDY      = 0;
 n_passOneEleZH     = 0;
 n_passTwoEleZH     = 0;
 n_passOneMuZH      = 0;
 n_passTwoMuZH      = 0;
 n_passOneEleOffZ   = 0;
 n_passTwoEleOffZ   = 0;
 n_passOneMuOffZ    = 0;
 n_passTwoMuOffZ    = 0;
 n_passOneEleNoPair = 0;
 n_passOneMuNoPair  = 0;
 n_passEleMuOSOF    = 0;
 n_passOnePho       = 0;

}


//----------------------------~cleareventcounters
void analyzer_globalvalues::cleareventcounters(){

  // clear counters for event variables
  nSelectedPho=0;
  nSelectedEle=0;
  nSelectedMuo=0;
  nSelectedAODCaloJet=0;


}

