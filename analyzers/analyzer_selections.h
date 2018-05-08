
#ifndef analyzer_selections_h
#define analyzer_selections_h

#include "analyzer_createobjects.h"

class analyzer_selections : public analyzer_createobjects {


public :

                  analyzer_selections();
   virtual        ~analyzer_selections(); 

   virtual void  clearSelections();
   virtual void  setSelections();

   // Selection functions
   Bool_t        askPassSelvec( std::vector<Bool_t> selvec, Bool_t lepvec[3], int &counter, int &counterele, int &countermu );
   Int_t         setSelBits( std::vector<Bool_t> selvec );
   Bool_t        askPassSingleEle();
   Bool_t        askPassSingleMu();
   Bool_t        askPassDoubleEle();
   Bool_t        askPassDoubleMu();

   std::vector<Bool_t> selvecSignal ;
   std::vector<Bool_t> selvecZH     ;
   std::vector<Bool_t> selvecDY     ;
   std::vector<Bool_t> selvecOffZ   ;
   std::vector<Bool_t> selvecNoPair ;
   std::vector<Bool_t> selvec[6];

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
