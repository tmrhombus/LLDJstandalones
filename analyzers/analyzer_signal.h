
#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"

class analyzer_signal : public analyzer_base {

public :

 analyzer_signal();
 virtual ~analyzer_signal();
 virtual void     Loop(TString outfilename, Bool_t isMC,
                       Double_t lumi, Double_t nrEvents,
                       Double_t crossSec);


};

#endif
