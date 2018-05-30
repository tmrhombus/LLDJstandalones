
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
   std::vector<int>   OPT_nJets;
   std::vector<float> OPT_AODCaloJetMedianLog10IPSig;
   std::vector<float> OPT_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> OPT_AODCaloJetAlphaMax;
   std::vector<float> OPT_AODCaloJetEta;
   std::vector<float> OPT_AODCaloJetPt;
  
   // link vectors to branches
   TBranch* bEvent       = OPTtree->Branch("OPT_Event"                              , &OPT_Event); 
   TBranch* bEventWeight = OPTtree->Branch("OPT_EventWeight"                        , &OPT_EventWeight); 
   TBranch* bnJets       = OPTtree->Branch("OPT_nJets"                              , &OPT_nJets); 
   TBranch* bIP          = OPTtree->Branch("OPT_AODCaloJetMedianLog10IPSig"         , &OPT_AODCaloJetMedianLog10IPSig); 
   TBranch* bTA          = OPTtree->Branch("OPT_AODCaloJetMedianLog10TrackAngle"    , &OPT_AODCaloJetMedianLog10TrackAngle); 
   TBranch* bAlpha       = OPTtree->Branch("OPT_AODCaloJetAlphaMax"                 , &OPT_AODCaloJetAlphaMax); 
   TBranch* bEta         = OPTtree->Branch("OPT_AODCaloJetEta"                      , &OPT_AODCaloJetEta); 
   TBranch* bPt          = OPTtree->Branch("OPT_AODCaloJetPt"                       , &OPT_AODCaloJetPt); 

};

#endif
