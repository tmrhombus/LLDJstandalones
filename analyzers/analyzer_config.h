
#ifndef analyzer_config_h
#define analyzer_config_h

#include "analyzer_globalvalues.h"

class analyzer_config : public analyzer_globalvalues {


public :

                  analyzer_config();
   virtual        ~analyzer_config(); 
   virtual void   setconfiguration();

   Float_t pho_minPt;
   Float_t pho_maxEta;
   Float_t ele_minPt1;
   Float_t ele_minPt2;
   Float_t ele_maxEta;
   Float_t mu_minPt1;
   Float_t mu_minPt2;
   Float_t mu_maxEta;
   Float_t jet_minPt;
   Float_t jet_maxEta;

};

#endif
