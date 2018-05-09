#include "analyzer_selections.h"

//----------------------------analyzer_selections
analyzer_selections::analyzer_selections() 
{
}

//----------------------------~analyzer_selections
analyzer_selections::~analyzer_selections()
{
}

void analyzer_selections::clearSelections()
{
 selvecSignal .clear(); 
 selvecZH     .clear(); 
 selvecDY     .clear(); 
 selvecOffZ   .clear(); 
 selvecNoPair .clear(); 
}

void analyzer_selections::setSelections()
{
 selvecSignal .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) ) ;
 selvecSignal .push_back( passGoodVtx   );
 selvecSignal .push_back( passZWindow   );
 selvecSignal .push_back( passPTOSSFg50 );
 selvecSignal .push_back( passOneTag    );

 selvecZH     .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) ) ;
 selvecZH     .push_back( passGoodVtx   );
 selvecZH     .push_back( passZWindow   );
 selvecZH     .push_back( passPTOSSFg50 );
 selvecZH     .push_back( passOneJet    );

 selvecDY     .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) );
 selvecDY     .push_back( passGoodVtx    );
 selvecDY     .push_back( passZWindow    );
 selvecDY     .push_back( !passPTOSSFg50 );
 selvecDY     .push_back( passOneJet     );

 selvecOffZ   .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu) );
 selvecOffZ   .push_back( passGoodVtx  );
 selvecOffZ   .push_back( !passZWindow );
 selvecOffZ   .push_back( passOSSF     );
 selvecOffZ   .push_back( passOneJet   );

 selvecNoPair .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu) );
 selvecNoPair .push_back( passGoodVtx  );
 selvecNoPair .push_back( !passZWindow );
 selvecNoPair .push_back( !passOSSF    );
 selvecNoPair .push_back( passOneJet   );
}

Bool_t analyzer_selections::askPassSelvec( std::vector<Bool_t> selvec, Bool_t lepvec[3], int &counter, int &counterele, int &countermu)
{
 Bool_t doespass = kTRUE;
 for(unsigned int i=0; i<selvec.size(); ++i){
  if( !selvec[i] ) doespass = kFALSE;
 }

 if( doespass && lepvec[0] ) counterele++;
 if( doespass && lepvec[1] ) countermu++;
 if( doespass ) counter++;

 return doespass;
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
