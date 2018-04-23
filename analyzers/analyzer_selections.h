
#ifndef analyzer_selections_h
#define analyzer_selections_h

#include "analyzer_createobjects.h"

class analyzer_selections : public analyzer_createobjects {


public :

                  analyzer_selections();
   virtual        ~analyzer_selections(); 

   // Selection functions
   Bool_t        askPassSingleEle();
   Bool_t        askPassSingleMu();
   Bool_t        askPassDoubleEle();
   Bool_t        askPassDoubleMu();
   Bool_t        askPassSig();
   Bool_t        askPassZH();
   Bool_t        askPassDY();
   Bool_t        askPassOffZ();
   Bool_t        askPassNoPair();

   // selection booleans
   Bool_t passSingleEle ;
   Bool_t passSingleMu  ;
   Bool_t passDoubleEle ;
   Bool_t passDoubleMu  ;
   Bool_t passOSSF      ;   
   Bool_t passZWindow   ;   
   Bool_t passGoodVtx   ;   
   Bool_t passPTOSSFg50 ; 
   Bool_t passOneJet    ; 
   Bool_t passOneTag    ;
   Bool_t passTwoTag    ;

};

#endif
