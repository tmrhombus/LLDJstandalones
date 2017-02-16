
#ifndef analyzer_base_h
#define analyzer_base_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TBranch.h>
#include <TTree.h>

class analyzer_base {
public :
   analyzer_base();
   virtual ~analyzer_base();
   //virtual void     Init();

   //analyzer_base(TTree *tree=0);
   //virtual ~analyzer_base();
   //virtual Int_t    Cut(Long64_t entry);
   //virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   //virtual Bool_t   Notify();
   //virtual void     Show(Long64_t entry = -1);

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        vars_ONZ;
   Double_t        vars_hasGoodVertex;
   Double_t        vars_hasDoubleElTriggers;
   Double_t        vars_hasDoubleMuTriggers;
   Double_t        vars_hasSingleElTriggers;
   Double_t        vars_hasSingleMuTriggers;
   Double_t        vars_Max_LEPTON_DPHI;
   Double_t        vars_Min_LEPTON_DPHI;
   Double_t        vars_MET;
   Double_t        vars_PTOSSF;
   Double_t        vars_NOSSF;
   Double_t        vars_NGOODVERTICES;
   Double_t        vars_HT;
   Double_t        vars_NBASICCALOJETS1PT20MATCHED;
   Double_t        vars_Alt_MT;
   Double_t        vars_Alt_WPT;
   Double_t        vars_EVENT;
   Double_t        vars_NBASICCALOJETS;
   Double_t        vars_Min_ALPHAMAX_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_Max_SUMIPSIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_Max_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_Max_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_MISSINGINNER_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_MISSINGOUTER_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_NMATCHEDTRACKS_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_NTRACKSIPLT0P05_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_NTRACKSIPSIGGT10_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_NTRACKSIPSIGLT5_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ALPHAMAX2_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ALPHAMAXPRIME2_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ALPHAMAXPRIME_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ALPHAMAX_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ASSOCAPLANARITY_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ASSOCIATEDTRACKPT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ASSOCSPHERICITY_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ASSOCTHRUSTMAJOR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ASSOCTHRUSTMINOR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_BETA2_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_BETA_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_ETA_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_IVFSCORE_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_JETAREA_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_LEPDELTAR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_LINEARRADIALMOMENT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_MEDIANIPLOG10SIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_MEDIANIPLOGSIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_MEDIANLOG10TRACKANGLE_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_METANGLE_DANGLE_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_METANGLE_DPHI_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_METDELTAR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_MISSHITSAFTERVERTPERTRACK_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_PHI_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_PT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_STUPAKPT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_STUPAKR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_SUMIPLOGSIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_SUMIPSIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_SUMIP_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_TOTALTRACKANGLEPT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_TOTALTRACKANGLE_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_TOTALTRACKPT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_TRACKENERGY_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_TRACKMASS_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFASSOCAPLANARITY_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFASSOCSPHERICITY_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFASSOCTHRUSTMINOR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFASSOCTHRUSTMAJOR_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFVERTEXDISTANCETOBEAM_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFVERTEXTRACKENERGY_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFBEAMSPOTRECOILPT_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFVERTEXTRANSVERSESIG_BASICCALOJETS1PT20MATCHED;
   Double_t        vars_AVFVERTEXTRACKMASS_BASICCALOJETS1PT20MATCHED;

   // List of branches
   TBranch        *b_vars;   //!

};


#endif // #ifdef analyzer_base_cxx
