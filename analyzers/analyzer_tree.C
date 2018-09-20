#include "analyzer_tree.h"

//----------------------------analyzer_tree
analyzer_tree::analyzer_tree() 
{
}

//----------------------------~analyzer_tree
analyzer_tree::~analyzer_tree()
{
}


//----------------------------setOPTtree
void analyzer_tree::setOPTtree(){

  OPT_Event.push_back(event);
  OPT_EventWeight.push_back(event_weight);
  OPT_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    //n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      OPT_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      OPT_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      OPT_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      OPT_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      OPT_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    OPT_AODCaloJetMedianLog10IPSig      .push_back(-5);
    OPT_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    OPT_AODCaloJetAlphaMax              .push_back(-5);
    OPT_AODCaloJetEta                   .push_back(-99);
    OPT_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearOPTtree
void analyzer_tree::clearOPTtree(){

  //clear optimization arrays each new event
  OPT_Event                           .clear();
  OPT_EventWeight                     .clear();
  OPT_nJets                           .clear();
  OPT_AODCaloJetMedianLog10IPSig      .clear();
  OPT_AODCaloJetMedianLog10TrackAngle .clear();
  OPT_AODCaloJetAlphaMax              .clear();
  OPT_AODCaloJetEta                   .clear();
  OPT_AODCaloJetPt                    .clear();

}

//-----------------------------NM1 Tree stiff
void analyzer_tree::setNM1tree(){

  NM1_Event.push_back(event);
  NM1_EventWeight.push_back(event_weight);
  NM1_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    //n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1_AODCaloJetAlphaMax              .push_back(-5);
    NM1_AODCaloJetEta                   .push_back(-99);
    NM1_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearNM1tree
void analyzer_tree::clearNM1tree(){

  //clear arrays each new event
  NM1_Event                           .clear();
  NM1_EventWeight                     .clear();
  NM1_nJets                           .clear();
  NM1_AODCaloJetMedianLog10IPSig      .clear();
  NM1_AODCaloJetMedianLog10TrackAngle .clear();
  NM1_AODCaloJetAlphaMax              .clear();
  NM1_AODCaloJetEta                   .clear();
  NM1_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1CRHeavytree(){

  NM1CRHeavy_Event.push_back(event);
  NM1CRHeavy_EventWeight.push_back(event_weight);
  NM1CRHeavy_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    //n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1CRHeavy_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1CRHeavy_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1CRHeavy_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1CRHeavy_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1CRHeavy_AODCaloJetAlphaMax              .push_back(-5);
    NM1CRHeavy_AODCaloJetEta                   .push_back(-99);
    NM1CRHeavy_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearOPTtree
void analyzer_tree::clearNM1CRHeavytree(){

  //clear optimization arrays each new event
  NM1CRHeavy_Event                           .clear();
  NM1CRHeavy_EventWeight                     .clear();
  NM1CRHeavy_nJets                           .clear();
  NM1CRHeavy_AODCaloJetMedianLog10IPSig      .clear();
  NM1CRHeavy_AODCaloJetMedianLog10TrackAngle .clear();
  NM1CRHeavy_AODCaloJetAlphaMax              .clear();
  NM1CRHeavy_AODCaloJetEta                   .clear();
  NM1CRHeavy_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1CRLighttree(){

  NM1CRLight_Event.push_back(event);
  NM1CRLight_EventWeight.push_back(event_weight);
  NM1CRLight_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    //n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1CRLight_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1CRLight_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1CRLight_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1CRLight_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1CRLight_AODCaloJetAlphaMax              .push_back(-5);
    NM1CRLight_AODCaloJetEta                   .push_back(-99);
    NM1CRLight_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearOPTtree
void analyzer_tree::clearNM1CRLighttree(){

  //clear optimization arrays each new event
  NM1CRLight_Event                           .clear();
  NM1CRLight_EventWeight                     .clear();
  NM1CRLight_nJets                           .clear();
  NM1CRLight_AODCaloJetMedianLog10IPSig      .clear();
  NM1CRLight_AODCaloJetMedianLog10TrackAngle .clear();
  NM1CRLight_AODCaloJetAlphaMax              .clear();
  NM1CRLight_AODCaloJetEta                   .clear();
  NM1CRLight_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1MuZHtree(){

  NM1MuZH_Event.push_back(event);
  NM1MuZH_EventWeight.push_back(event_weight);
  NM1MuZH_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    //n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1MuZH_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1MuZH_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1MuZH_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1MuZH_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1MuZH_AODCaloJetAlphaMax              .push_back(-5);
    NM1MuZH_AODCaloJetEta                   .push_back(-99);
    NM1MuZH_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearOPTtree
void analyzer_tree::clearNM1MuZHtree(){

  //clear optimization arrays each new event
  NM1MuZH_Event                           .clear();
  NM1MuZH_EventWeight                     .clear();
  NM1MuZH_nJets                           .clear();
  NM1MuZH_AODCaloJetMedianLog10IPSig      .clear();
  NM1MuZH_AODCaloJetMedianLog10TrackAngle .clear();
  NM1MuZH_AODCaloJetAlphaMax              .clear();
  NM1MuZH_AODCaloJetEta                   .clear();
  NM1MuZH_AODCaloJetPt                    .clear();

}

void analyzer_tree::setNM1EleZHtree(){

  NM1EleZH_Event.push_back(event);
  NM1EleZH_EventWeight.push_back(event_weight);
  NM1EleZH_nJets.push_back(aodcalojet_list.size());
  if(aodcalojet_list.size()>0){
    //n_test = n_test + 1;
    for(int i = 0; i<aodcalojet_list.size(); i++){
      int aodcalojetindex = aodcalojet_list[i]; 
      NM1EleZH_AODCaloJetMedianLog10IPSig      .push_back(AODCaloJetMedianLog10IPSig      ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetMedianLog10TrackAngle .push_back(AODCaloJetMedianLog10TrackAngle ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetAlphaMax              .push_back(AODCaloJetAlphaMax              ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetEta                   .push_back(AODCaloJetEta                   ->at(aodcalojetindex));
      NM1EleZH_AODCaloJetPt                    .push_back(AODCaloJetPt                    ->at(aodcalojetindex));
      }
  }
  else{
    NM1EleZH_AODCaloJetMedianLog10IPSig      .push_back(-5);
    NM1EleZH_AODCaloJetMedianLog10TrackAngle .push_back(-5);
    NM1EleZH_AODCaloJetAlphaMax              .push_back(-5);
    NM1EleZH_AODCaloJetEta                   .push_back(-99);
    NM1EleZH_AODCaloJetPt                    .push_back(-99);
  }

}

//----------------------------clearOPTtree
void analyzer_tree::clearNM1EleZHtree(){

  //clear optimization arrays each new event
  NM1EleZH_Event                           .clear();
  NM1EleZH_EventWeight                     .clear();
  NM1EleZH_nJets                           .clear();
  NM1EleZH_AODCaloJetMedianLog10IPSig      .clear();
  NM1EleZH_AODCaloJetMedianLog10TrackAngle .clear();
  NM1EleZH_AODCaloJetAlphaMax              .clear();
  NM1EleZH_AODCaloJetEta                   .clear();
  NM1EleZH_AODCaloJetPt                    .clear();

}

