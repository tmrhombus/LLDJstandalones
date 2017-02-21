
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
 Bool_t        fillSigHistograms(Double_t weight,int selbin);
 Bool_t        writeSigHistograms(int selbin);
 Bool_t        askPassSig();
 Bool_t        askPassZH();
 Bool_t        askPassDY();
 Bool_t        askPassOffZ();
 Bool_t        askPassNoPair();

 // selection variables
 Bool_t doesPassSig;
 Bool_t doesPassZH;
 Bool_t doesPassDY;
 Bool_t doesPassOffZ;
 Bool_t doesPassNoPair;

 // bin names
 std::vector<TString> selbinnames;

 // initialize histograms as global
 //  selbins = NoSel, Sig, ZH, DY, OffZ, NoPair
 TH1F h_sig_PT[6]                                            ;
 TH1F h_sig_NGOODVERTICES[6]                                 ;
 TH1F h_sig_ALPHAMAX[6]                                      ;
 TH1F h_sig_ASSOCAPLANARITY[6]                               ;
 TH1F h_sig_ASSOCIATEDTRACKPT[6]                             ;
 TH1F h_sig_ASSOCSPHERICITY[6]                               ;
 TH1F h_sig_ASSOCTHRUSTMAJOR[6]                              ;
 TH1F h_sig_ASSOCTHRUSTMINOR[6]                              ;
 TH1F h_sig_AVFASSOCSPHERICITY[6]                            ;
 TH1F h_sig_AVFASSOCTHRUSTMAJOR[6]                           ;
 TH1F h_sig_AVFASSOCTHRUSTMINOR[6]                           ;
 TH1F h_sig_BETA[6]                                          ;
 TH1F h_sig_MEDIANIPLOG10SIG[6]                              ;
 TH1F h_sig_MEDIANLOG10TRACKANGLE[6]                         ;
 TH1F h_sig_MISSINGINNER[6]                                  ;
 TH1F h_sig_SUMIP[6]                                         ;
 TH1F h_sig_SUMIPSIG[6]                                      ;
 TH1F h_sig_TOTALTRACKPT[6]                                  ;
 TH1F h_sig_TOTALTRACKANGLE[6]                               ;
 TH1F h_sig_HT[6]                                            ;
 TH1F h_sig_Max_LEPTON_DPHI[6]                               ;
 TH1F h_sig_Max_MEDIANIPLOG10SIG[6]                          ;
 TH1F h_sig_Max_SUMIPSIG[6]                                  ;
 TH1F h_sig_Max_TOTALTRACKANGLE[6]                           ;
 TH1F h_sig_MET[6]                                           ;
 TH1F h_sig_Min_LEPTON_DPHI[6]                               ;
 TH1F h_sig_Alt_MT[6]                                        ;
 TH1F h_sig_PTOSSF[6]                                        ;
 TH1F h_sig_Alt_WPT[6]                                       ;

};

#endif
