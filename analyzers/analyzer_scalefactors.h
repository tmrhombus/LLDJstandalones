
#ifndef analyzer_scalefactors_h
#define analyzer_scalefactors_h

#include "analyzer_selections.h"

class analyzer_scalefactors : public analyzer_selections {


public :

                  analyzer_scalefactors();
   virtual        ~analyzer_scalefactors(); 

 // event based weights
 Float_t         makeEventWeight(Float_t crossSec, Float_t lumi,
                                  Float_t nrEvents);
 void            loadPUWeight();
 void 		 loadEleTriggerEffi();
 void 		 loadMuonTriggerEffi();
 Float_t         makePUWeight( TString dataset );
 Float_t         makeEleTriggerEffi( std::vector<int> &electron_list );
 Float_t         makeMuonTriggerEffi( std::vector<int> &muon_list );
 TH1F*           PUWeights_DoubleEG     ;
 TH1F*           PUWeights_DoubleMu     ;
 TH1F*           PUWeights_MuonEG       ;
 TH1F*           PUWeights_SinglePhoton ;
 void            loadElectronWeight( TString eleid );
 void            loadMuonWeight( TString muoid );
 void            loadMuonIso( TString muoid );
 Float_t         makeElectronWeight( std::vector<int> &electron_list );
 Float_t         makeMuonWeight( std::vector<int> &muon_list );
 Float_t         makeMuonIso( std::vector<int> &muon_list );
 TH2F*           EleWeights;
 TH2F*		 EleTrigEffi; 
 TH2F*		 EleTrigEffi1; 
 TH2F*		 EleTrigEffi2; 
 TH2F*           MuonWeights;
 TH2F*           MuonIso;
 TH2F*		 MuonTrigEffi; 
 TH2F*		 MuonTrigEffi17; 
 TH2F*		 MuonTrigEffi8; 
 Float_t         makeTTWeight( Float_t TTavgweight );

 void               loadMistagRate();
 TH1F*              h_MistagRate_pt;
 std::vector<TH1F*> h_MistagRate_pt_sys;
 TH2F*              h_MistagRate_pteta;
 std::vector<TH2F*> h_MistagRate_pteta_sys;

};

#endif
