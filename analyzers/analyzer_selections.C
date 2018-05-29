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
 selvecSignal  .clear(); 
 selvecZH      .clear(); 
 selvecDY      .clear(); 
 selvecOffZ    .clear(); 
 selvecNoPair  .clear(); 
 selvecCRHeavy .clear(); 
 selvecCRLight .clear(); 

 bitsPassSig=0;
 bitsPassZH=0;
 bitsPassDY=0;
 bitsPassOffZ=0;
 bitsPassNoPair=0;
 bitsPassCRHeavy=0;
 bitsPassCRLight=0;

}

void analyzer_selections::setSelections()
{
 selvecSignal  .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) ) ;
 selvecSignal  .push_back( passGoodVtx   );
 selvecSignal  .push_back( passZWindow   );
 selvecSignal  .push_back( passPTOSSF    );
 selvecSignal  .push_back( passOneTag    );

 selvecZH      .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) ) ;
 selvecZH      .push_back( passGoodVtx   );
 selvecZH      .push_back( passZWindow   );
 selvecZH      .push_back( passPTOSSF    );
 selvecZH      .push_back( passOneJet    );

 selvecDY      .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu ) );
 selvecDY      .push_back( passGoodVtx    );
 selvecDY      .push_back( passZWindow    );
 selvecDY      .push_back( !passPTOSSF    );
 selvecDY      .push_back( passOneJet     );

 selvecOffZ    .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu) );
 selvecOffZ    .push_back( passGoodVtx  );
 selvecOffZ    .push_back( !passZWindow );
 selvecOffZ    .push_back( passOSSF     );
 selvecOffZ    .push_back( passOneJet   );

 selvecNoPair  .push_back( (passSingleEle || passSingleMu || passDoubleEle || passDoubleMu) );
 selvecNoPair  .push_back( passGoodVtx  );
 selvecNoPair  .push_back( !passZWindow );
 selvecNoPair  .push_back( !passOSSF    );
 selvecNoPair  .push_back( passOneJet   );

 selvecCRHeavy .push_back( (passSingleEle && passSingleMu) );
 selvecCRHeavy .push_back( passGoodVtx  );
 selvecCRHeavy .push_back( passZWinOSOF );
 selvecCRHeavy .push_back( passOSOF     );
 selvecCRHeavy .push_back( passOneTag   );

 selvecCRLight .push_back( passSinglePho);
 selvecCRLight .push_back( passGoodVtx  );
 selvecCRLight .push_back( true         );
 selvecCRLight .push_back( passOneTag   );
 selvecCRLight .push_back( passOneJet   );
}

Int_t analyzer_selections::setSelBits( std::vector<Bool_t> selvec, Bool_t lepvec[3], int &counter, int &counterele, int &countermu )
{
 
 ULong64_t bitset = 0;
 Bool_t passall=kTRUE;
 // individual selections
 for(unsigned int i=0; i<selvec.size(); ++i){
  if(selvec[i]==0) passall=kFALSE;
  bitset |= (selvec[i] << i+1); 
 }
 // set first bit for pass all selections
 bitset |= passall << 0 ;

 // increment counters
 if( passall && lepvec[0] ) counterele++;
 if( passall && lepvec[1] ) countermu++;
 if( passall ) counter++;

 return bitset;
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

Bool_t analyzer_selections::askPassSinglePho()
{
 Bool_t doespass = kFALSE;
 if(photon_list.size()>0){ 
  //if(isMC) doespass = kTRUE;
  //else doespass = (Bool_t)( (AOD_HLT_Ele23Loose > 0) || (AOD_HLT_Ele27Tight > 0) );
  doespass = kTRUE;
 } 
 return doespass;
}

