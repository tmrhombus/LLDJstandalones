
#ifndef analyzer_globalvalues_h
#define analyzer_globalvalues_h

#include "analyzer_base.h"
#include <TLorentzVector.h>

class analyzer_globalvalues : public analyzer_base {

public :

                  analyzer_globalvalues();
   virtual        ~analyzer_globalvalues(); 
   virtual void   clearglobalcounters();
   virtual void   cleareventcounters();

   // vectors of ints
   // each int is an entry in vector
   // associated with object passing
   // some selection
   std::vector<int> photon_list;
   std::vector<int> electron_list;
   std::vector<int> muon_list ;
   std::vector<int> aodcalojet_list;
   std::vector<int> taggedjet_list;

   std::vector<float> aodcalojet_minDR_list;

   // for dilepton
   TLorentzVector fourVec_ee, fourVec_mm, fourVec_ll;
   TLorentzVector fourVec_l1, fourVec_l2;
   TLorentzVector fourVec_met;
   Double_t dilep_mass;
   Double_t dilep_pt;

   // personal variables
   Double_t themet;
   Double_t themephi;
   Double_t htall;
   Double_t htaodcalojets;
 
   // AOD
   float jetmatchdRcut ;
   float objcleandRcut ;

   // ID bits for collections
   TString phoid;
   TString eleid;
   TString muoid;
   TString jetid;

   int phoidbit;
   int eleidbit;
   int muoidbit;
   int aodcalojetidbit;
   float muoisoval;

   // full cut booleans
   Bool_t doesPassSig;
   Bool_t doesPassZH;
   Bool_t doesPassDY;
   Bool_t doesPassOffZ;
   Bool_t doesPassNoPair;

   // selection counters (how many events pass)
   Int_t n_tot;
   Int_t n_test;
   Int_t n_test2;

   Int_t n_passSig;
   Int_t n_passZH;
   Int_t n_passDY;
   Int_t n_passOffZ;
   Int_t n_passNoPair;

   Int_t n_ele_passSig;
   Int_t n_ele_passZH;
   Int_t n_ele_passDY;
   Int_t n_ele_passOffZ;
   Int_t n_ele_passNoPair;

   Int_t n_mu_passSig;
   Int_t n_mu_passZH;
   Int_t n_mu_passDY;
   Int_t n_mu_passOffZ;
   Int_t n_mu_passNoPair;

   Int_t nSelectedPho;
   Int_t nSelectedEle;
   Int_t nSelectedMuo;
   Int_t nSelectedSlimmedJet;
   Int_t nSelectedAODCaloJet;

};

#endif