
#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"

class analyzer_signal : public analyzer_base {

public :

               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, Bool_t isMC,
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec);
 Bool_t        initSigHistograms();
 Bool_t        fillSigHistograms(Double_t weight);
 Bool_t        writeSigHistograms();

 // initialize histograms as global
 TH1F h_sig_PT[1]                                            ;
 TH1F h_sig_NGOODVERTICES[1]                                 ;
 TH1F h_sig_ALPHAMAX[1]                                      ;
 TH1F h_sig_ASSOCAPLANARITY[1]                               ;
 TH1F h_sig_ASSOCIATEDTRACKPT[1]                             ;
 TH1F h_sig_ASSOCSPHERICITY[1]                               ;
 TH1F h_sig_ASSOCTHRUSTMAJOR[1]                              ;
 TH1F h_sig_ASSOCTHRUSTMINOR[1]                              ;
 TH1F h_sig_AVFASSOCSPHERICITY[1]                            ;
 TH1F h_sig_AVFASSOCTHRUSTMAJOR[1]                           ;
 TH1F h_sig_AVFASSOCTHRUSTMINOR[1]                           ;
 TH1F h_sig_BETA[1]                                          ;
 TH1F h_sig_MEDIANIPLOG10SIG[1]                              ;
 TH1F h_sig_MEDIANLOG10TRACKANGLE[1]                         ;
 TH1F h_sig_MISSINGINNER[1]                                  ;
 TH1F h_sig_SUMIP[1]                                         ;
 TH1F h_sig_SUMIPSIG[1]                                      ;
 TH1F h_sig_TOTALTRACKPT[1]                                  ;
 TH1F h_sig_TOTALTRACKANGLE[1]                               ;
 TH1F h_sig_HT[1]                                            ;
 TH1F h_sig_Max_LEPTON_DPHI[1]                               ;
 TH1F h_sig_Max_MEDIANIPLOG10SIG[1]                          ;
 TH1F h_sig_Max_SUMIPSIG[1]                                  ;
 TH1F h_sig_Max_TOTALTRACKANGLE[1]                           ;
 TH1F h_sig_MET[1]                                           ;
 TH1F h_sig_Min_LEPTON_DPHI[1]                               ;
 TH1F h_sig_Alt_MT[1]                                        ;
 TH1F h_sig_PTOSSF[1]                                        ;
 TH1F h_sig_Alt_WPT[1]                                       ;

};

#endif
