
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
  
   //Keep for general purpose 
   virtual void clearNM1tree();
   virtual void setNM1tree();

   virtual void clearNM1CRHeavytree();
   virtual void setNM1CRHeavytree();
   virtual void clearNM1CRLighttree();
   virtual void setNM1CRLighttree();
   virtual void clearNM1MuZHtree();
   virtual void setNM1MuZHtree();
   virtual void clearNM1EleZHtree();
   virtual void setNM1EleZHtree();
   
//------------------------------OPT Tree
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

//---------------------------------NM1 Trees
   // NMinus1 plot gen. purpose
   TTree *NM1tree = new TTree("NM1tree","NMinus1Vars");
  
   // vectors to be filled in optional tree
   std::vector<int>   NM1_Event;
   std::vector<float> NM1_EventWeight;
   std::vector<int>   NM1_nJets;
   std::vector<float> NM1_AODCaloJetEta;
   std::vector<float> NM1_AODCaloJetPt;
   std::vector<float> NM1_AODCaloJetMedianLog10IPSig;
   std::vector<float> NM1_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> NM1_AODCaloJetAlphaMax;
  
   // link vectors to branches
   TBranch* bNM1Event       = NM1tree->Branch("NM1_Event"                              , &NM1_Event); 
   TBranch* bNM1EventWeight = NM1tree->Branch("NM1_EventWeight"                        , &NM1_EventWeight); 
   TBranch* bNM1nJets       = NM1tree->Branch("NM1_nJets"                              , &NM1_nJets); 
   TBranch* bNM1Eta         = NM1tree->Branch("NM1_AODCaloJetEta"                      , &NM1_AODCaloJetEta); 
   TBranch* bNM1Pt          = NM1tree->Branch("NM1_AODCaloJetPt"                       , &NM1_AODCaloJetPt); 
   TBranch* bNM1IP          = NM1tree->Branch("NM1_AODCaloJetMedianLog10IPSig"         , &NM1_AODCaloJetMedianLog10IPSig); 
   TBranch* bNM1TA          = NM1tree->Branch("NM1_AODCaloJetMedianLog10TrackAngle"    , &NM1_AODCaloJetMedianLog10TrackAngle); 
   TBranch* bNM1Alpha       = NM1tree->Branch("NM1_AODCaloJetAlphaMax"                 , &NM1_AODCaloJetAlphaMax); 
   
   // NMinus1 plot CRHeavy
   TTree *NM1CRHeavytree = new TTree("NM1CRHeavytree","NMinus1VarsCRHeavy");
  
   // vectors to be filled in optional tree
   std::vector<int>   NM1CRHeavy_Event;
   std::vector<float> NM1CRHeavy_EventWeight;
   std::vector<int>   NM1CRHeavy_nJets;
   std::vector<float> NM1CRHeavy_AODCaloJetEta;
   std::vector<float> NM1CRHeavy_AODCaloJetPt;
   std::vector<float> NM1CRHeavy_AODCaloJetMedianLog10IPSig;
   std::vector<float> NM1CRHeavy_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> NM1CRHeavy_AODCaloJetAlphaMax;
  
   // link vectors to branches
   TBranch* bNM1CRHeavyEvent       = NM1CRHeavytree->Branch("NM1CRHeavy_Event"                              , &NM1CRHeavy_Event); 
   TBranch* bNM1CRHeavyEventWeight = NM1CRHeavytree->Branch("NM1CRHeavy_EventWeight"                        , &NM1CRHeavy_EventWeight); 
   TBranch* bNM1CRHeavynJets       = NM1CRHeavytree->Branch("NM1CRHeavy_nJets"                              , &NM1CRHeavy_nJets); 
   TBranch* bNM1CRHeavyEta         = NM1CRHeavytree->Branch("NM1CRHeavy_AODCaloJetEta"                      , &NM1CRHeavy_AODCaloJetEta); 
   TBranch* bNM1CRHeavyPt          = NM1CRHeavytree->Branch("NM1CRHeavy_AODCaloJetPt"                       , &NM1CRHeavy_AODCaloJetPt); 
   TBranch* bNM1CRHeavyIP          = NM1CRHeavytree->Branch("NM1CRHeavy_AODCaloJetMedianLog10IPSig"         , &NM1CRHeavy_AODCaloJetMedianLog10IPSig); 
   TBranch* bNM1CRHeavyTA          = NM1CRHeavytree->Branch("NM1CRHeavy_AODCaloJetMedianLog10TrackAngle"    , &NM1CRHeavy_AODCaloJetMedianLog10TrackAngle); 
   TBranch* bNM1CRHeavyAlpha       = NM1CRHeavytree->Branch("NM1CRHeavy_AODCaloJetAlphaMax"                 , &NM1CRHeavy_AODCaloJetAlphaMax); 
   
   // NMinus1 plot CRLight
   TTree *NM1CRLighttree = new TTree("NM1CRLighttree","NMinus1VarsCRLight");
  
   // vectors to be filled in optional tree
   std::vector<int>   NM1CRLight_Event;
   std::vector<float> NM1CRLight_EventWeight;
   std::vector<int>   NM1CRLight_nJets;
   std::vector<float> NM1CRLight_AODCaloJetEta;
   std::vector<float> NM1CRLight_AODCaloJetPt;
   std::vector<float> NM1CRLight_AODCaloJetMedianLog10IPSig;
   std::vector<float> NM1CRLight_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> NM1CRLight_AODCaloJetAlphaMax;
  
   // link vectors to branches
   TBranch* bNM1CRLightEvent       = NM1CRLighttree->Branch("NM1CRLight_Event"                              , &NM1CRLight_Event); 
   TBranch* bNM1CRLightEventWeight = NM1CRLighttree->Branch("NM1CRLight_EventWeight"                        , &NM1CRLight_EventWeight); 
   TBranch* bNM1CRLightnJets       = NM1CRLighttree->Branch("NM1CRLight_nJets"                              , &NM1CRLight_nJets); 
   TBranch* bNM1CRLightEta         = NM1CRLighttree->Branch("NM1CRLight_AODCaloJetEta"                      , &NM1CRLight_AODCaloJetEta); 
   TBranch* bNM1CRLightPt          = NM1CRLighttree->Branch("NM1CRLight_AODCaloJetPt"                       , &NM1CRLight_AODCaloJetPt); 
   TBranch* bNM1CRLightIP          = NM1CRLighttree->Branch("NM1CRLight_AODCaloJetMedianLog10IPSig"         , &NM1CRLight_AODCaloJetMedianLog10IPSig); 
   TBranch* bNM1CRLightTA          = NM1CRLighttree->Branch("NM1CRLight_AODCaloJetMedianLog10TrackAngle"    , &NM1CRLight_AODCaloJetMedianLog10TrackAngle); 
   TBranch* bNM1CRLightAlpha       = NM1CRLighttree->Branch("NM1CRLight_AODCaloJetAlphaMax"                 , &NM1CRLight_AODCaloJetAlphaMax); 

   // NMinus1 plot MuZH
   TTree *NM1MuZHtree = new TTree("NM1MuZHtree","NMinus1VarsMuZH");
  
   // vectors to be filled in optional tree
   std::vector<int>   NM1MuZH_Event;
   std::vector<float> NM1MuZH_EventWeight;
   std::vector<int>   NM1MuZH_nJets;
   std::vector<float> NM1MuZH_AODCaloJetEta;
   std::vector<float> NM1MuZH_AODCaloJetPt;
   std::vector<float> NM1MuZH_AODCaloJetMedianLog10IPSig;
   std::vector<float> NM1MuZH_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> NM1MuZH_AODCaloJetAlphaMax;
  
   // link vectors to branches
   TBranch* bNM1MuZHEvent       = NM1MuZHtree->Branch("NM1MuZH_Event"                              , &NM1MuZH_Event); 
   TBranch* bNM1MuZHEventWeight = NM1MuZHtree->Branch("NM1MuZH_EventWeight"                        , &NM1MuZH_EventWeight); 
   TBranch* bNM1MuZHnJets       = NM1MuZHtree->Branch("NM1MuZH_nJets"                              , &NM1MuZH_nJets); 
   TBranch* bNM1MuZHEta         = NM1MuZHtree->Branch("NM1MuZH_AODCaloJetEta"                      , &NM1MuZH_AODCaloJetEta); 
   TBranch* bNM1MuZHPt          = NM1MuZHtree->Branch("NM1MuZH_AODCaloJetPt"                       , &NM1MuZH_AODCaloJetPt); 
   TBranch* bNM1MuZHIP          = NM1MuZHtree->Branch("NM1MuZH_AODCaloJetMedianLog10IPSig"         , &NM1MuZH_AODCaloJetMedianLog10IPSig); 
   TBranch* bNM1MuZHTA          = NM1MuZHtree->Branch("NM1MuZH_AODCaloJetMedianLog10TrackAngle"    , &NM1MuZH_AODCaloJetMedianLog10TrackAngle); 
   TBranch* bNM1MuZHAlpha       = NM1MuZHtree->Branch("NM1MuZH_AODCaloJetAlphaMax"                 , &NM1MuZH_AODCaloJetAlphaMax); 

   // NMinus1 plot EleZH
   TTree *NM1EleZHtree = new TTree("NM1EleZHtree","NMinus1VarsEleZH");
  
   // vectors to be filled in optional tree
   std::vector<int>   NM1EleZH_Event;
   std::vector<float> NM1EleZH_EventWeight;
   std::vector<int>   NM1EleZH_nJets;
   std::vector<float> NM1EleZH_AODCaloJetEta;
   std::vector<float> NM1EleZH_AODCaloJetPt;
   std::vector<float> NM1EleZH_AODCaloJetMedianLog10IPSig;
   std::vector<float> NM1EleZH_AODCaloJetMedianLog10TrackAngle;
   std::vector<float> NM1EleZH_AODCaloJetAlphaMax;
  
   // link vectors to branches
   TBranch* bNM1EleZHEvent       = NM1EleZHtree->Branch("NM1EleZH_Event"                              , &NM1EleZH_Event); 
   TBranch* bNM1EleZHEventWeight = NM1EleZHtree->Branch("NM1EleZH_EventWeight"                        , &NM1EleZH_EventWeight); 
   TBranch* bNM1EleZHnJets       = NM1EleZHtree->Branch("NM1EleZH_nJets"                              , &NM1EleZH_nJets); 
   TBranch* bNM1EleZHEta         = NM1EleZHtree->Branch("NM1EleZH_AODCaloJetEta"                      , &NM1EleZH_AODCaloJetEta); 
   TBranch* bNM1EleZHPt          = NM1EleZHtree->Branch("NM1EleZH_AODCaloJetPt"                       , &NM1EleZH_AODCaloJetPt); 
   TBranch* bNM1EleZHIP          = NM1EleZHtree->Branch("NM1EleZH_AODCaloJetMedianLog10IPSig"         , &NM1EleZH_AODCaloJetMedianLog10IPSig); 
   TBranch* bNM1EleZHTA          = NM1EleZHtree->Branch("NM1EleZH_AODCaloJetMedianLog10TrackAngle"    , &NM1EleZH_AODCaloJetMedianLog10TrackAngle); 
   TBranch* bNM1EleZHAlpha       = NM1EleZHtree->Branch("NM1EleZH_AODCaloJetAlphaMax"                 , &NM1EleZH_AODCaloJetAlphaMax); 
};

#endif
