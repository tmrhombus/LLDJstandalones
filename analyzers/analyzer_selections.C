#include "analyzer_selections.h"

//----------------------------analyzer_selections
analyzer_selections::analyzer_selections() 
{
}

//----------------------------~analyzer_selections
analyzer_selections::~analyzer_selections()
{
}

// trigger ------------------------
Bool_t analyzer_selections::askPassSingleEle()
{
 Bool_t doespass = kFALSE;
 if(electron_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_Ele23Loose > 0) || (AOD_HLT_Ele27Tight > 0) );
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassDoubleEle()
{
 Bool_t doespass = kFALSE;
 if(electron_list.size()>1){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_Ele17Ele12 > 0) || (AOD_HLT_Ele23Ele12 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassSingleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>0){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_IsoMu22 > 0) || (AOD_HLT_IsoTkMu22 > 0) );
 } 
 return doespass;
}

Bool_t analyzer_selections::askPassDoubleMu()
{
 Bool_t doespass = kFALSE;
 if(muon_list.size()>1){ 
  if(isMC) doespass = kTRUE;
  else doespass = (Bool_t)( (AOD_HLT_Mu17Mu8 > 0) || (AOD_HLT_Mu17TkMu8 > 0) ) ; 
 } 
 return doespass;
}



//----------------------------analyzer_selections
// signal/control region selections ------------------------
Bool_t analyzer_selections::askPassSig()
{
 Bool_t doespass = kFALSE;
 if( passGoodVtx
    && passZWindow
    && passPTOSSFg50
    && passOneTag
    && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
   )
 {
  doespass = kTRUE; n_passSig++;
  if( passSingleEle || passDoubleEle ) { n_ele_passSig++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passSig++; }
 }
 return doespass;
}


Bool_t analyzer_selections::askPassZH()
{
 Bool_t doespass = kFALSE;
 if( passGoodVtx
    && passZWindow
    && passPTOSSFg50
    && passOneJet
    && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
   )
 {
  doespass = kTRUE;
  n_passZH++;
  if( passSingleEle || passDoubleEle ) { n_ele_passZH++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passZH++; }
 }
 return doespass;
}


Bool_t analyzer_selections::askPassDY()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
      && passZWindow
      && !passPTOSSFg50
      && passOneJet
      && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) 
     )
  { doespass = kTRUE; n_passDY++; 
   if( passSingleEle || passDoubleEle ) { n_ele_passDY++; } // printf("\n PASS SingleEle Event %lld\n", event); }
   else if( passSingleMu  || passDoubleMu  ) { n_mu_passDY++;  }//  printf("\n PASS SingleMu Event %lld\n", event); }
  }
  return doespass;
}


Bool_t analyzer_selections::askPassOffZ()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && !passZWindow
     && passOSSF
     && passOneJet
     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu)
    )
 { doespass = kTRUE; n_passOffZ++;
  if( passSingleEle || passDoubleEle ) { n_ele_passOffZ++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passOffZ++; }
 }
 return doespass;
}

Bool_t analyzer_selections::askPassNoPair()
{
 Bool_t doespass = kFALSE;

 if ( passGoodVtx
     && !passZWindow
     && !passOSSF
     && passOneJet
     && (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu)
    )
 { doespass = kTRUE; n_passNoPair++;
  if( passSingleEle || passDoubleEle ) { n_ele_passNoPair++; }
  else if( passSingleMu  || passDoubleMu  ) { n_mu_passNoPair++; }
 }
 return doespass;
}
