// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

// (local) variables associated with tree branches

ULong64_t   AOD_HLT_Ele23Loose_;
ULong64_t   AOD_HLT_Ele27Tight_;
ULong64_t   AOD_HLT_Ele17Ele12_;
ULong64_t   AOD_HLT_Ele23Ele12_;

ULong64_t   AOD_HLT_IsoMu22_;
ULong64_t   AOD_HLT_IsoTkMu22_;
ULong64_t   AOD_HLT_Mu17Mu8_;
ULong64_t   AOD_HLT_Mu17TkMu8_;

ULong64_t   AOD_HLT_PFHT350PFMET100_isPS_;

ULong64_t   AOD_HLT_Ele23Loose_isPS_;
ULong64_t   AOD_HLT_Ele27Tight_isPS_;
ULong64_t   AOD_HLT_Ele17Ele12_isPS_;
ULong64_t   AOD_HLT_Ele23Ele12_isPS_;

ULong64_t   AOD_HLT_IsoMu22_isPS_;
ULong64_t   AOD_HLT_IsoTkMu22_isPS_;
ULong64_t   AOD_HLT_Mu17Mu8_isPS_;
ULong64_t   AOD_HLT_Mu17TkMu8_isPS_;


const int bitsize=8;


void lldjNtuple::branchesAODTrigger(TTree* tree){
  tree->Branch("AOD_HLT_Ele23Loose",       &AOD_HLT_Ele23Loose_) ;
  tree->Branch("AOD_HLT_Ele27Tight",       &AOD_HLT_Ele27Tight_) ;
  tree->Branch("AOD_HLT_Ele17Ele12",       &AOD_HLT_Ele17Ele12_) ;
  tree->Branch("AOD_HLT_Ele23Ele12",       &AOD_HLT_Ele23Ele12_) ;
  
  tree->Branch("AOD_HLT_IsoMu22"  ,        &AOD_HLT_IsoMu22_)   ;
  tree->Branch("AOD_HLT_IsoTkMu22",        &AOD_HLT_IsoTkMu22_) ;
  tree->Branch("AOD_HLT_Mu17Mu8"  ,        &AOD_HLT_Mu17Mu8_)   ;
  tree->Branch("AOD_HLT_Mu17TkMu8",        &AOD_HLT_Mu17TkMu8_) ;
}


void lldjNtuple::fillAODTrigger(const edm::Event &e, const edm::EventSetup &es){
  
  AOD_HLT_Ele23Loose_       = 0;
  AOD_HLT_Ele27Tight_       = 0;
  AOD_HLT_Ele17Ele12_       = 0;
  AOD_HLT_Ele23Ele12_       = 0;
  
  AOD_HLT_IsoMu22_          = 0;
  AOD_HLT_IsoTkMu22_        = 0;
  AOD_HLT_Mu17Mu8_          = 0;
  AOD_HLT_Mu17TkMu8_        = 0;
  
  if( !( e.getByToken(AODTriggerToken_, AODTriggerHandle_) && e.getByToken(AODTriggerEventToken_, AODTriggerEventHandle_) ) ){ return; }
  
  for(int i = 0; i < (int)hltConfig_.size(); i++){
    string name = hltConfig_.triggerName(i);
    
    int bitEle23Loose = -1;
    if      (name.find("HLT_Ele23_WPLoose_Gsf_v1")  != string::npos) bitEle23Loose = 0  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v2")  != string::npos) bitEle23Loose = 1  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v3")  != string::npos) bitEle23Loose = 2  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v4")  != string::npos) bitEle23Loose = 3  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v5")  != string::npos) bitEle23Loose = 4  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v6")  != string::npos) bitEle23Loose = 5  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v7")  != string::npos) bitEle23Loose = 6  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v8")  != string::npos) bitEle23Loose = 7  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v9")  != string::npos) bitEle23Loose = 8  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v10") != string::npos) bitEle23Loose = 9  ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v11") != string::npos) bitEle23Loose = 10 ;
    else if (name.find("HLT_Ele23_WPLoose_Gsf_v12") != string::npos) bitEle23Loose = 11 ;
    
    int bitEle27Tight = -1;
    if      (name.find("HLT_Ele27_WPTight_Gsf_v1")  != string::npos) bitEle27Tight = 0 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v2")  != string::npos) bitEle27Tight = 1 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v3")  != string::npos) bitEle27Tight = 2 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v4")  != string::npos) bitEle27Tight = 3 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v5")  != string::npos) bitEle27Tight = 4 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v6")  != string::npos) bitEle27Tight = 5 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v7")  != string::npos) bitEle27Tight = 6 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v8")  != string::npos) bitEle27Tight = 7 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v9")  != string::npos) bitEle27Tight = 8 ;
    
    // Double Electron
    int bitEle17Ele12 = -1;
    if      (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")  != string::npos) bitEle17Ele12 = 0 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2")  != string::npos) bitEle17Ele12 = 1 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3")  != string::npos) bitEle17Ele12 = 2 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4")  != string::npos) bitEle17Ele12 = 3 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5")  != string::npos) bitEle17Ele12 = 4 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6")  != string::npos) bitEle17Ele12 = 5 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7")  != string::npos) bitEle17Ele12 = 6 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8")  != string::npos) bitEle17Ele12 = 7 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9")  != string::npos) bitEle17Ele12 = 8 ;
    else if (name.find("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10") != string::npos) bitEle17Ele12 = 9 ;
    
    int bitEle23Ele12 = -1;
    if      (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1")  != string::npos) bitEle23Ele12 = 0 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2")  != string::npos) bitEle23Ele12 = 1 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3")  != string::npos) bitEle23Ele12 = 2 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4")  != string::npos) bitEle23Ele12 = 3 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5")  != string::npos) bitEle23Ele12 = 4 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6")  != string::npos) bitEle23Ele12 = 5 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7")  != string::npos) bitEle23Ele12 = 6 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8")  != string::npos) bitEle23Ele12 = 7 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9")  != string::npos) bitEle23Ele12 = 8 ;
    else if (name.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10") != string::npos) bitEle23Ele12 = 9 ;
    
    // Single Iso Mu
    int bitIsoMu22   = -1;
    if      (name.find("HLT_IsoMu22_v1") != string::npos) bitIsoMu22 = 0 ;
    else if (name.find("HLT_IsoMu22_v2") != string::npos) bitIsoMu22 = 1 ;
    else if (name.find("HLT_IsoMu22_v3") != string::npos) bitIsoMu22 = 2 ;
    else if (name.find("HLT_IsoMu22_v4") != string::npos) bitIsoMu22 = 3 ;
    else if (name.find("HLT_IsoMu22_v5") != string::npos) bitIsoMu22 = 4 ;
    else if (name.find("HLT_IsoMu22_v6") != string::npos) bitIsoMu22 = 5 ;
    else if (name.find("HLT_IsoMu22_v7") != string::npos) bitIsoMu22 = 6 ;
    
    int bitIsoTkMu22 = -1;
    if      (name.find("HLT_IsoTkMu22_v1")  != string::npos) bitIsoTkMu22 = 0 ;
    else if (name.find("HLT_IsoTkMu22_v2")  != string::npos) bitIsoTkMu22 = 1 ;
    else if (name.find("HLT_IsoTkMu22_v3")  != string::npos) bitIsoTkMu22 = 2 ;
    else if (name.find("HLT_IsoTkMu22_v4")  != string::npos) bitIsoTkMu22 = 3 ;
    else if (name.find("HLT_IsoTkMu22_v5")  != string::npos) bitIsoTkMu22 = 4 ;
    else if (name.find("HLT_IsoTkMu22_v6")  != string::npos) bitIsoTkMu22 = 5 ;
    else if (name.find("HLT_IsoTkMu22_v7")  != string::npos) bitIsoTkMu22 = 6 ;
    else if (name.find("HLT_IsoTkMu22_v8")  != string::npos) bitIsoTkMu22 = 7 ;
    else if (name.find("HLT_IsoTkMu22_v9")  != string::npos) bitIsoTkMu22 = 8 ;
    else if (name.find("HLT_IsoTkMu22_v10") != string::npos) bitIsoTkMu22 = 9 ;
    
    // Double Iso Mu
    int bitMu17Mu8   = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17Mu8 = 0 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17Mu8 = 1 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17Mu8 = 2 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17Mu8 = 3 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17Mu8 = 4 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17Mu8 = 5 ;
    
    int bitMu17TkMu8 = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17TkMu8 = 0 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17TkMu8 = 1 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17TkMu8 = 2 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17TkMu8 = 3 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17TkMu8 = 4 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17TkMu8 = 5 ;                   
    
    //printf(" Reading trigger: %s\n" , name.c_str()  );
    //printf(" bitPFHT350PFMET100 %d \n", bitPFHT350PFMET100 ); 
    //printf(" bitEle23Loose      %d \n", bitEle23Loose      ); 
    //printf(" bitEle27Tight      %d \n", bitEle27Tight      ); 
    //printf(" bitEle17Ele12      %d \n", bitEle17Ele12      ); 
    //printf(" bitEle23Ele12      %d \n", bitEle23Ele12      ); 
    //printf(" bitIsoMu22         %d \n", bitIsoMu22         ); 
    //printf(" bitIsoTkMu22       %d \n", bitIsoTkMu22       ); 
    //printf(" bitMu17Mu8         %d \n", bitMu17Mu8         ); 
    //printf(" bitMu17TkMu8       %d \n", bitMu17TkMu8       ); 
    
    // indicates prescaling and whether trigger was fired or not
    unsigned int isPrescaled = hltPrescale_.prescaleValue(e,es,name);
    const unsigned int triggerIndex = hltConfig_.triggerIndex(name);
    unsigned int isFired     = AODTriggerHandle_->accept(triggerIndex);
    //cout << "was run " << AODTriggerHandle_->wasrun(triggerIndex) << endl;
    
    if ( bitEle23Loose      >= 0 ){
      AOD_HLT_Ele23Loose_            |= (isFired     << bitEle23Loose      );
      AOD_HLT_Ele23Loose_isPS_       |= (isPrescaled << bitEle23Loose      );
    }
    if ( bitEle27Tight      >= 0 ){     
      AOD_HLT_Ele27Tight_            |= (isFired     << bitEle27Tight      );
      AOD_HLT_Ele27Tight_isPS_       |= (isPrescaled << bitEle27Tight      );
    }
    if ( bitEle17Ele12      >= 0 ){     
      AOD_HLT_Ele17Ele12_            |= (isFired     << bitEle17Ele12      );
      AOD_HLT_Ele17Ele12_isPS_       |= (isPrescaled << bitEle17Ele12      );
    }
    if ( bitEle23Ele12      >= 0 ){     
      AOD_HLT_Ele23Ele12_            |= (isFired     << bitEle23Ele12      );
      AOD_HLT_Ele23Ele12_isPS_       |= (isPrescaled << bitEle23Ele12      );
    }
    
    if ( bitIsoMu22         >= 0 ){   
      AOD_HLT_IsoMu22_               |= (isFired     << bitIsoMu22         );
      AOD_HLT_IsoMu22_isPS_          |= (isPrescaled << bitIsoMu22         );
    }
    if ( bitIsoTkMu22       >= 0 ){     
      AOD_HLT_IsoTkMu22_             |= (isFired     << bitIsoTkMu22       );
      AOD_HLT_IsoTkMu22_isPS_        |= (isPrescaled << bitIsoTkMu22       );
    }
    if ( bitMu17Mu8         >= 0 ){   
      AOD_HLT_Mu17Mu8_               |= (isFired     << bitMu17Mu8         );
      AOD_HLT_Mu17Mu8_isPS_          |= (isPrescaled << bitMu17Mu8         );
    }
    if ( bitMu17TkMu8       >= 0 ){     
      AOD_HLT_Mu17TkMu8_             |= (isFired     << bitMu17TkMu8       );
      AOD_HLT_Mu17TkMu8_isPS_        |= (isPrescaled << bitMu17TkMu8       );
    }
    
    //std::bitset<bitsize> AOD_HLT_PFHT350PFMET100_b(bitPFHT350PFMET100);
    std::bitset<bitsize> AOD_HLT_Ele23Loose_b(bitEle23Loose);
    std::bitset<bitsize> AOD_HLT_Ele27Tight_b(bitEle27Tight);
    std::bitset<bitsize> AOD_HLT_Ele17Ele12_b(bitEle17Ele12);
    std::bitset<bitsize> AOD_HLT_Ele23Ele12_b(bitEle23Ele12);
    std::bitset<bitsize> AOD_HLT_IsoMu22_b(bitIsoMu22);
    std::bitset<bitsize> AOD_HLT_IsoTkMu22_b(bitIsoTkMu22);
    std::bitset<bitsize> AOD_HLT_Mu17Mu8_b(bitMu17Mu8);
    std::bitset<bitsize> AOD_HLT_Mu17TkMu8_b(bitMu17TkMu8);
    
  }//hltConfig loop
  
}//fillAODTrigger
