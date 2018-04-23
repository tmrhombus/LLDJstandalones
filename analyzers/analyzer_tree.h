
#ifndef analyzer_tree_h
#define analyzer_tree_h

#include "analyzer_histograms.h"
#include <TLorentzVector.h>

class analyzer_tree : public analyzer_histograms {


public :

                  analyzer_tree();
   virtual        ~analyzer_tree(); 

   virtual void clearOPTtree();
   virtual void setOPTtree();

   // output TTree to be filled (slimmed vars/selections)
   TTree *OPTtree = new TTree("OPTtree","Optimization Variables");
  
   // vectors to be filled in optional tree
   std::vector<int>   OPT_Event;
   std::vector<float> OPT_EventWeight;
//   std::vector<int>   OPT_nJets;
   std::vector<float> OPT_AODCaloJetMedianLog10IPSig;
   std::vector<float> OPT_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> OPT_AODCaloJetAlphaMax;
  
   // link vectors to branches
   TBranch* b1 = OPTtree->Branch("OPT_Event"                              , &OPT_Event); 
   TBranch* b2 = OPTtree->Branch("OPT_EventWeight"                        , &OPT_EventWeight); 
//   //TBranch* b3 = OPTtree->Branch("OPT_nJets"                              , &OPT_nJets); 
   TBranch* b4 = OPTtree->Branch("OPT_AODCaloJetMedianLog10IPSig"         , &OPT_AODCaloJetMedianLog10IPSig); 
   TBranch* b5 = OPTtree->Branch("OPT_AODCaloJetMedianLog10TrackAngle"    , &OPT_AODCaloJetMedianLog10TrackAngle); 
   TBranch* b6 = OPTtree->Branch("OPT_AODCaloJetAlphaMax"                 , &OPT_AODCaloJetAlphaMax); 

};

#endif
