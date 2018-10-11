#include "analyzer_config.h"

//----------------------------analyzer_config
analyzer_config::analyzer_config() 
{
}

//----------------------------~analyzer_config
analyzer_config::~analyzer_config()
{
}


//----------------------------analyzer_config
void analyzer_config::setConfiguration() 
{

 pho_minPt  = 175.;
 pho_maxEta = 1.4442;
 ele_minPt1 = 25.;
 ele_minPt2 = 15.;
 ele_maxEta = 2.5;
 mu_minPt1  = 25.;
 mu_minPt2  = 12.;
 mu_maxEta  = 2.4;
 jet_minPt  = 25.;
 jet_maxEta = 2.4;

 // tagging variables
 tag_minIPsig = 1.15;
 tag_minTA    = -1.75;
 tag_maxAmax  = 0.75;
 // shifted tagging variables
 tag_shiftminIPsig = 1.2;
 tag_shiftminTA    = -1.4;
 tag_shiftmaxAmax  = 0.4;

 // set which collections
 phoid = "Medium"; // "Tight"; "Loose"; //Medium"; 
 eleid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 muoid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 jetid = "Loose"; // "Tight"; "Loose";

 jetmatchdRcut = 0.4;
 objcleandRcut = 0.4;

 if (phoid = "Loose")  phoidbit=0;
 if (phoid = "Medium") phoidbit=1;
 if (phoid = "Tight")  phoidbit=2;

 if (eleid = "Loose")  eleidbit=0;
 if (eleid = "Medium") eleidbit=1;
 if (eleid = "Tight")  eleidbit=2;

 if (muoid = "Loose")  muoidbit=0;
 if (muoid = "Medium") muoidbit=1;
 if (muoid = "Tight")  muoidbit=2;

 if (jetid = "Loose")  aodcalojetidbit=0;
 if (jetid = "Tight")  aodcalojetidbit=1;

 //printf("setting config\n");

}

void analyzer_config::initSelectionCategories( ){

  // Make sure that the numbers in here  match
  // static const int SELBINNAMESIZE  = 20;
  // static const int JETMULTNAMESIZE = 5; 
  // static const int LEPBINNAMESIZE  = 3;
  // initialize names
  jetmultnames.clear();
  jetmultnames.push_back("LeadingJet");
  jetmultnames.push_back("SubleadingJet");
  jetmultnames.push_back("ThirdJet");
  jetmultnames.push_back("FourthJet");
  jetmultnames.push_back("AllJets");

  tagmultnames.clear();
  tagmultnames.push_back("LeadingTag");
  tagmultnames.push_back("SubleadingTag");
  tagmultnames.push_back("ThirdTag");
  tagmultnames.push_back("FourthTag");
  tagmultnames.push_back("AllTags");

  selbinnames.clear();
  selbinnames.push_back("OneEleSig");
  selbinnames.push_back("TwoEleSig");
  selbinnames.push_back("OneMuSig");
  selbinnames.push_back("TwoMuSig");
  selbinnames.push_back("OneEleDY");
  selbinnames.push_back("TwoEleDY");
  selbinnames.push_back("OneMuDY");
  selbinnames.push_back("TwoMuDY");
  selbinnames.push_back("OneEleZH");
  selbinnames.push_back("TwoEleZH");
  selbinnames.push_back("OneMuZH");
  selbinnames.push_back("TwoMuZH");
  selbinnames.push_back("OneEleOffZ");
  selbinnames.push_back("TwoEleOffZ");
  selbinnames.push_back("OneMuOffZ");
  selbinnames.push_back("TwoMuOffZ");
  selbinnames.push_back("OneEleNoPair");
  selbinnames.push_back("OneMuNoPair");
  selbinnames.push_back("EleMuOSOF");
  selbinnames.push_back("OnePho");

  //std::cout<<" Selection category: "<<selcategory<<"\n";
  //if ( selcategory.EqualTo("Signal") ){
  // selbinnames.push_back("OneEleSig");
  // selbinnames.push_back("TwoEleSig");
  // selbinnames.push_back("OneMuSig");
  // selbinnames.push_back("TwoMuSig");
  //} else if ( selcategory.EqualTo("DY") ){
  // selbinnames.push_back("OneEleDY");
  // selbinnames.push_back("TwoEleDY");
  // selbinnames.push_back("OneMuDY");
  // selbinnames.push_back("TwoMuDY");
  //} else if ( selcategory.EqualTo("ZH") ){
  // selbinnames.push_back("OneEleZH");
  // selbinnames.push_back("TwoEleZH");
  // selbinnames.push_back("OneMuZH");
  // selbinnames.push_back("TwoMuZH");
  //} else if ( selcategory.EqualTo("OffZ") ){
  // selbinnames.push_back("OneEleOffZ");
  // selbinnames.push_back("TwoEleOffZ");
  // selbinnames.push_back("OneMuOffZ");
  // selbinnames.push_back("TwoMuOffZ");
  //} else if ( selcategory.EqualTo("MiscCR") ){
  // selbinnames.push_back("OneEleNoPair");
  // selbinnames.push_back("OneMuNoPair");
  // selbinnames.push_back("EleMuOSOF");
  // selbinnames.push_back("OnePho");
  //} 

}
