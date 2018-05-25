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
 n_test  = 0;
 n_test2 = 0;

 n_passSig     = 0;
 n_passZH      = 0;
 n_passDY      = 0;
 n_passOffZ    = 0;
 n_passNoPair  = 0;
 n_passCRHeavy = 0;
 n_passCRLight = 0;

 n_ele_passSig     = 0;
 n_ele_passZH      = 0;
 n_ele_passDY      = 0;
 n_ele_passOffZ    = 0;
 n_ele_passNoPair  = 0;
 n_ele_passCRHeavy = 0;
 n_ele_passCRLight = 0;

 n_mu_passSig     = 0;
 n_mu_passZH      = 0;
 n_mu_passDY      = 0;
 n_mu_passOffZ    = 0;
 n_mu_passNoPair  = 0;
 n_mu_passCRHeavy = 0;
 n_mu_passCRLight = 0;

}


//----------------------------~cleareventcounters
void analyzer_globalvalues::cleareventcounters(){

  // clear counters for event variables
  nSelectedPho=0;
  nSelectedEle=0;
  nSelectedMuo=0;
  nSelectedAODCaloJet=0;


}

