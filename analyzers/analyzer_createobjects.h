
#ifndef analyzer_createobjects_h
#define analyzer_createobjects_h

#include "analyzer_config.h"

class analyzer_createobjects : public analyzer_config {


public :

                  analyzer_createobjects();
   virtual        ~analyzer_createobjects(); 

 // object IDs and selections
 std::vector<int>     photon_passID     ( int bitnr, Float_t phoPtCut, Float_t phoEtaCut, TString sysbinname="");
 std::vector<int>     electron_passID   ( int bitnr, Float_t elePtCut1, Float_t elePtCut2, Float_t eleEtaCut, TString sysbinname="");
 std::vector<int>     muon_passID       ( int bitnr, Float_t muPtCut1 , Float_t muPtCut2 , Float_t muEtaCut , TString sysbinname="");
 std::vector<int>     aodcalojet_passID ( int bitnr, Float_t jetPtCut, Float_t jetEtaCut, TString sysbinname="");
 std::vector<int>     jet_passTagger    ();

 std::vector<float>     jet_minDR    ();

 // make dilepton pair, pass by reference
 virtual void     makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2,
                            TLorentzVector *fv_ee, TLorentzVector *fv_mm);
 virtual void     makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_em);
 // I like because I don't want to rely on CMSSW here
 double               dR(double eta1, double phi1, double eta2, double phi2);
 double               DeltaPhi(double phi1, double phi2);

 // get (smeared) object pt
 Float_t          getPhotonPt(int idnr, TString sysbinname);
 Float_t          getElectronPt(int i, TString sysbinname);
 Float_t          getMuonPt(int i, TString sysbinname);

 Float_t          getMET();

 virtual void     calculateHT();
 virtual void     makeDiLepton();




};

#endif
