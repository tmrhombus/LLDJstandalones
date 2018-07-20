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
void analyzer_config::setconfiguration() 
{

 pho_minPt  = 15.;
 pho_maxEta = 1.4442;
 ele_minPt1 = 25.;
 ele_minPt2 = 15.;
 ele_maxEta = 2.5;
 mu_minPt1  = 25.;
 mu_minPt2  = 12.;
 mu_maxEta  = 2.4;
 jet_minPt  = 25.;
 jet_maxEta = 2.4;

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
