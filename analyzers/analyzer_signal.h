
#ifndef analyzer_signal_h
#define analyzer_signal_h

#include "analyzer_base.h"

class analyzer_signal : public analyzer_base {

public :

               analyzer_signal();
 virtual       ~analyzer_signal();
 virtual void  Loop(TString outfilename, Bool_t isMC,
                    Double_t lumi, Double_t nrEvents,
                    Double_t crossSec, Int_t nevts);
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
 TH1F h_PT[6]                                            ;
 TH1F h_NGOODVERTICES[6]                                 ;
 TH1F h_ALPHAMAX[6]                                      ;
 TH1F h_ASSOCAPLANARITY[6]                               ;
 TH1F h_ASSOCIATEDTRACKPT[6]                             ;
 TH1F h_ASSOCSPHERICITY[6]                               ;
 TH1F h_ASSOCTHRUSTMAJOR[6]                              ;
 TH1F h_ASSOCTHRUSTMINOR[6]                              ;
 TH1F h_AVFASSOCSPHERICITY[6]                            ;
 TH1F h_AVFASSOCTHRUSTMAJOR[6]                           ;
 TH1F h_AVFASSOCTHRUSTMINOR[6]                           ;
 TH1F h_BETA[6]                                          ;
 TH1F h_MEDIANIPLOG10SIG[6]                              ;
 TH1F h_MEDIANLOG10TRACKANGLE[6]                         ;
 TH1F h_MISSINGINNER[6]                                  ;
 TH1F h_SUMIP[6]                                         ;
 TH1F h_SUMIPSIG[6]                                      ;
 TH1F h_TOTALTRACKPT[6]                                  ;
 TH1F h_TOTALTRACKANGLE[6]                               ;
 TH1F h_HT[6]                                            ;
 TH1F h_Max_LEPTON_DPHI[6]                               ;
 TH1F h_Max_MEDIANIPLOG10SIG[6]                          ;
 TH1F h_Max_SUMIPSIG[6]                                  ;
 TH1F h_Max_TOTALTRACKANGLE[6]                           ;
 TH1F h_MET[6]                                           ;
 TH1F h_Min_LEPTON_DPHI[6]                               ;
 TH1F h_Alt_MT[6]                                        ;
 TH1F h_PTOSSF[6]                                        ;
 TH1F h_Alt_WPT[6]                                       ;

};

#endif
