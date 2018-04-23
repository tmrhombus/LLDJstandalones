
#ifndef analyzer_config_h
#define analyzer_config_h

#include "analyzer_globalvalues.h"

class analyzer_config : public analyzer_globalvalues {


public :

                  analyzer_config();
   virtual        ~analyzer_config(); 
   virtual void   setconfiguration();

};

#endif
