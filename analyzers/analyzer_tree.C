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

