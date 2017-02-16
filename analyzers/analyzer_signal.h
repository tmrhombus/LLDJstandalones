
#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"

class analyzer_signal : public analyzer_base {

public :

  analyzer_signal();
  virtual void     Loop();
  virtual ~analyzer_signal();


};

#endif
