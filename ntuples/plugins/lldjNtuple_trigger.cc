
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

ULong64_t   HLT_Ele23Loose_;
ULong64_t   HLT_Ele27Tight_;
ULong64_t   HLT_Ele17Ele12_;
ULong64_t   HLT_Ele23Ele12_;

ULong64_t   HLT_IsoMu22_;
ULong64_t   HLT_IsoTkMu22_;
ULong64_t   HLT_Mu17Mu8_;
ULong64_t   HLT_Mu17TkMu8_;

ULong64_t   HLT_PFHT350PFMET100_isPS_;

ULong64_t   HLT_Ele23Loose_isPS_;
ULong64_t   HLT_Ele27Tight_isPS_;
ULong64_t   HLT_Ele17Ele12_isPS_;
ULong64_t   HLT_Ele23Ele12_isPS_;

ULong64_t   HLT_IsoMu22_isPS_;
ULong64_t   HLT_IsoTkMu22_isPS_;
ULong64_t   HLT_Mu17Mu8_isPS_;
ULong64_t   HLT_Mu17TkMu8_isPS_;

const int bitsize=8;


void lldjNtuple::branchesTrigger(TTree* tree){

  tree->Branch("HLT_Ele23Loose",       &HLT_Ele23Loose_) ;
  tree->Branch("HLT_Ele27Tight",       &HLT_Ele27Tight_) ;
  tree->Branch("HLT_Ele17Ele12",       &HLT_Ele17Ele12_) ;
  tree->Branch("HLT_Ele23Ele12",       &HLT_Ele23Ele12_) ;

  tree->Branch("HLT_IsoMu22"  ,        &HLT_IsoMu22_)   ;
  tree->Branch("HLT_IsoTkMu22",        &HLT_IsoTkMu22_) ;
  tree->Branch("HLT_Mu17Mu8"  ,        &HLT_Mu17Mu8_)   ;
  tree->Branch("HLT_Mu17TkMu8",        &HLT_Mu17TkMu8_) ;

}

void lldjNtuple::fillTrigger(const edm::Event &e, const edm::EventSetup &es){

  edm::Handle<edm::TriggerResults>                     triggerBits;
  edm::Handle<edm::View<pat::TriggerObjectStandAlone>> triggerObjects;
  edm::Handle<pat::PackedTriggerPrescales>             triggerPrescales;

  e.getByToken(triggerBits_, triggerBits);
  e.getByToken(triggerObjects_, triggerObjects);
  e.getByToken(triggerPrescales_, triggerPrescales);

  HLT_Ele23Loose_       = 0;
  HLT_Ele27Tight_       = 0;
  HLT_Ele17Ele12_       = 0;
  HLT_Ele23Ele12_       = 0;

  HLT_IsoMu22_          = 0;
  HLT_IsoTkMu22_        = 0;
  HLT_Mu17Mu8_          = 0;
  HLT_Mu17TkMu8_        = 0;

  const edm::TriggerNames &trgnames = e.triggerNames(*triggerBits);

  for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
    //  std::cout << "Trigger " << trgnames.triggerName(i) <<
    //          ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
    //          ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)")
    //          << std::endl;

    const string name = trgnames.triggerName(i);
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
    if      (name.find("HLT_IsoTkMu22_v1")  != string::npos) bitIsoMu22 = 0 ;
    else if (name.find("HLT_IsoTkMu22_v2")  != string::npos) bitIsoMu22 = 1 ;
    else if (name.find("HLT_IsoTkMu22_v3")  != string::npos) bitIsoMu22 = 2 ;
    else if (name.find("HLT_IsoTkMu22_v4")  != string::npos) bitIsoMu22 = 3 ;
    else if (name.find("HLT_IsoTkMu22_v5")  != string::npos) bitIsoMu22 = 4 ;
    else if (name.find("HLT_IsoTkMu22_v6")  != string::npos) bitIsoMu22 = 5 ;
    else if (name.find("HLT_IsoTkMu22_v7")  != string::npos) bitIsoMu22 = 6 ;
    else if (name.find("HLT_IsoTkMu22_v8")  != string::npos) bitIsoMu22 = 7 ;
    else if (name.find("HLT_IsoTkMu22_v9")  != string::npos) bitIsoMu22 = 8 ;
    else if (name.find("HLT_IsoTkMu22_v10") != string::npos) bitIsoMu22 = 9 ;

    // Double Iso Mu
    int bitMu17Mu8   = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17Mu8 = 0 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17Mu8 = 1 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17Mu8 = 2 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17Mu8 = 3 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17Mu8 = 4 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17Mu8 = 5 ;

    int bitMu17TkMu8 = -1;
    if      (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1") != string::npos) bitMu17Mu8 = 0 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2") != string::npos) bitMu17Mu8 = 1 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3") != string::npos) bitMu17Mu8 = 2 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4") != string::npos) bitMu17Mu8 = 3 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v5") != string::npos) bitMu17Mu8 = 4 ;                   
    else if (name.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6") != string::npos) bitMu17Mu8 = 5 ;                   

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
    unsigned int isPrescaled = triggerPrescales->getPrescaleForIndex(i);
    unsigned int isFired     = triggerBits->accept(i) ;

    if ( bitEle23Loose      >= 0 ){
     HLT_Ele23Loose_            |= (isFired     << bitEle23Loose      );
     HLT_Ele23Loose_isPS_       |= (isPrescaled << bitEle23Loose      );
    }
    if ( bitEle27Tight      >= 0 ){     
     HLT_Ele27Tight_            |= (isFired     << bitEle27Tight      );
     HLT_Ele27Tight_isPS_       |= (isPrescaled << bitEle27Tight      );
    }
    if ( bitEle17Ele12      >= 0 ){     
     HLT_Ele17Ele12_            |= (isFired     << bitEle17Ele12      );
     HLT_Ele17Ele12_isPS_       |= (isPrescaled << bitEle17Ele12      );
    }
    if ( bitEle23Ele12      >= 0 ){     
     HLT_Ele23Ele12_            |= (isFired     << bitEle23Ele12      );
     HLT_Ele23Ele12_isPS_       |= (isPrescaled << bitEle23Ele12      );
    }

    if ( bitIsoMu22         >= 0 ){   
     HLT_IsoMu22_               |= (isFired     << bitIsoMu22         );
     HLT_IsoMu22_isPS_          |= (isPrescaled << bitIsoMu22         );
    }
    if ( bitIsoTkMu22       >= 0 ){     
     HLT_IsoTkMu22_             |= (isFired     << bitIsoTkMu22       );
     HLT_IsoTkMu22_isPS_        |= (isPrescaled << bitIsoTkMu22       );
    }
    if ( bitMu17Mu8         >= 0 ){   
     HLT_Mu17Mu8_               |= (isFired     << bitMu17Mu8         );
     HLT_Mu17Mu8_isPS_          |= (isPrescaled << bitMu17Mu8         );
    }
    if ( bitMu17TkMu8       >= 0 ){     
     HLT_Mu17TkMu8_             |= (isFired     << bitMu17TkMu8       );
     HLT_Mu17TkMu8_isPS_        |= (isPrescaled << bitMu17TkMu8       );
    }


    //std::bitset<bitsize> HLT_PFHT350PFMET100_b(bitPFHT350PFMET100);
    std::bitset<bitsize> HLT_Ele23Loose_b(bitEle23Loose);
    std::bitset<bitsize> HLT_Ele27Tight_b(bitEle27Tight);
    std::bitset<bitsize> HLT_Ele17Ele12_b(bitEle17Ele12);
    std::bitset<bitsize> HLT_Ele23Ele12_b(bitEle23Ele12);
    std::bitset<bitsize> HLT_IsoMu22_b(bitIsoMu22);
    std::bitset<bitsize> HLT_IsoTkMu22_b(bitIsoTkMu22);
    std::bitset<bitsize> HLT_Mu17Mu8_b(bitMu17Mu8);
    std::bitset<bitsize> HLT_Mu17TkMu8_b(HLT_Mu17TkMu8_b);

  }

//  IF YOU WANT TO UNPACK TRIGGER OBJECT / MATCHING 
////////////////////////////////////////////////////
//    const edm::TriggerNames &names = e.triggerNames(*triggerBits);
//    std::cout << "\n == TRIGGER PATHS= " << std::endl;
//    for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
//        std::cout << "Trigger " << names.triggerName(i) <<
//                ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
//                ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)")
//                << std::endl;
//    }
//    std::cout << "\n TRIGGER OBJECTS " << std::endl;
//    for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
//        obj.unpackPathNames(names);
//        std::cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
//        // Print trigger object collection and type
//        std::cout << "\t   Collection: " << obj.collection() << std::endl;
//        std::cout << "\t   Type IDs:   ";
//        for (unsigned h = 0; h < obj.filterIds().size(); ++h) std::cout << " " << obj.filterIds()[h] ;
//        std::cout << std::endl;
//        // Print associated trigger filters
//        std::cout << "\t   Filters:    ";
//        for (unsigned h = 0; h < obj.filterLabels().size(); ++h) std::cout << " " << obj.filterLabels()[h];
//        std::cout << std::endl;
//        std::vector<std::basic_string<char>> pathNamesAll  = obj.pathNames(false);
//        std::vector<std::basic_string<char>> pathNamesLast = obj.pathNames(true);
//        // Print all trigger paths, for each one record also if the object is associated to a 'l3' filter (always true for the
//        // definition used in the PAT trigger producer) and if it's associated to the last filter of a successfull path (which
//        // means that this object did cause this trigger to succeed; however, it doesn't work on some multi-object triggers)
//        std::cout << "\t   Paths (" << pathNamesAll.size()<<"/"<<pathNamesLast.size()<<"):    ";
//        for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
//            bool isBoth = obj.hasPathName( pathNamesAll[h], true, true );
//            bool isL3   = obj.hasPathName( pathNamesAll[h], false, true );
//            bool isLF   = obj.hasPathName( pathNamesAll[h], true, false );
//            bool isNone = obj.hasPathName( pathNamesAll[h], false, false );
//            std::cout << "   " << pathNamesAll[h];
//            if (isBoth) std::cout << "(L,3)";
//            if (isL3 && !isBoth) std::cout << "(*,3)";
//            if (isLF && !isBoth) std::cout << "(L,*)";
//            if (isNone && !isBoth && !isL3 && !isLF) std::cout << "(*,*)";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;


}

