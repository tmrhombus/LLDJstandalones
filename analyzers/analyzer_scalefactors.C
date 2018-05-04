#include "analyzer_scalefactors.h"
#include <iostream>

//----------------------------analyzer_scalefactors
analyzer_scalefactors::analyzer_scalefactors() 
{
}

//----------------------------~analyzer_scalefactors
analyzer_scalefactors::~analyzer_scalefactors()
{
}

//----------------------------makeEventWeight
Double_t analyzer_scalefactors::makeEventWeight(Double_t crossSec,
                                        Double_t lumi,
                                        Double_t nrEvents)
{
  // 1.0 for real data
  event_weight=1.0;
  Double_t crossSecScl = crossSec;
  if(isMC){ event_weight=lumi*crossSecScl/nrEvents; }
  //printf("isMC: %i lumi: %0.9f crossSec: %0.9f nrEvents: %0.9f",isMC,lumi,crossSecScl,nrEvents);
  //printf("  event_weight: %0.9f\n",event_weight);

  return event_weight;
}

//----------------------------makePUWeight
Double_t analyzer_scalefactors::makePUWeight(){
// Int_t tmpbin = PUWeights->GetBin(nTruePU);
// Double_t tmpweight = PUWeights->GetBinContent(tmpbin);
 //printf("making PU weight for %i , %i, %f \n", nTruePU,tmpbin,tmpweight);
 Double_t tmpweight=1.; /// FIXME
 return tmpweight;
}

//----------------------------makeElectronWeight
Double_t analyzer_scalefactors::makeElectronWeight( std::vector<int> &electron_list ){

 Double_t tmpsf;
 tmpsf = 1.;

 //check overlap with electrons
 if(electron_list.size()>0){
  //printf(" esize: %lu\n",electron_list.size());
  //printf(" esceta: %lu\n",eleSCEta->size());
  //printf(" ept: %lu\n",AOD_elePt->size());
  for(int d=0; d<electron_list.size(); ++d){
   //printf(" brgin looping over electrons\n");
   int eleindex = electron_list[d];
   //printf(" d: %i eleindex: %i\n",d,eleindex);
   //printf(" ele sceta %f pt %f \n",eleSCEta->at(eleindex),AOD_elePt->at(eleindex));
   Float_t eeta = AOD_eleEta->at(eleindex);//<------changed; don't have SCEta right now
   Float_t ept  = AOD_elePt->at(eleindex);
   Int_t tmpbinx       = EleWeights->GetXaxis()->FindBin( eeta );
   Int_t tmpbiny       = EleWeights->GetYaxis()->FindBin( ept  );
   //printf(" bins %i %i\n",tmpbinx,tmpbiny);
   Int_t tmpbin        = EleWeights->GetBin( tmpbinx, tmpbiny );
   Double_t tmpweight = EleWeights->GetBinContent(tmpbin);
   tmpsf *= tmpweight;
  }//end electrons
 } // if electrons

 //printf(" done making Electron weight\n");

 return tmpsf;
}


//----------------------------loadPUWeight
void analyzer_scalefactors::loadPUWeight(){
 std::cout << "loading PU weight" << std::endl;
 TString filename = "puWeights_69200_24jan2017.root" ;
 TFile* file_puweights = new TFile( filename ) ;
 std::cout <<" filename: " << filename << std::endl;
 PUWeights = (TH1F*)file_puweights->Get("h_PUweight")->Clone("PUWeights");
 return ;
}

//----------------------------loadElectronWeight
void analyzer_scalefactors::loadElectronWeight(TString eleid){
 std::cout << "loading Electron weight" << std::endl;
 TString filename = "egammaEffi_MoriondBH_ele"+eleid+".root" ;
 TFile* file_eleweights = new TFile( filename ) ;
 std::cout << " filename: " << filename << std::endl;
 EleWeights = (TH2F*)file_eleweights->Get("EGamma_SF2D")->Clone("EleWeights");
 return ;
}

