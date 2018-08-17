#include "analyzer_createobjects.h"

//----------------------------analyzer_createobjects
analyzer_createobjects::analyzer_createobjects() 
{
}

//----------------------------~analyzer_createobjects
analyzer_createobjects::~analyzer_createobjects()
{
}


//----------------------------analyzer_createobjects

//-------------------------muon_passID
std::vector<int> analyzer_createobjects::muon_passID( int bitnr, Float_t muPtCut1, Float_t muPtCut2, Float_t muEtaCut, TString sysbinname)
{
 std::vector<int> mulist;

 // bool pass_loose  ;
 // bool pass_medium ;
 // bool pass_tight  ;
 // bool pass_soft   ;
 // bool pass_hipt   ;
 //
 // pass_loose  = muIDbit->at(i) >> 0 & 0x1 == 1;      
 // pass_medium = muIDbit->at(i) >> 1 & 0x1 == 1;      
 // pass_tight  = muIDbit->at(i) >> 2 & 0x1 == 1;     
 // pass_soft   = muIDbit->at(i) >> 3 & 0x1 == 1;    
 // pass_hipt   = muIDbit->at(i) >> 4 & 0x1 == 1;    
 //
 //  printf(" Muon %i    %i %i %i %i %i \n\n",i
 //        , pass_loose  
 //        , pass_medium  
 //        , pass_tight
 //        , pass_soft
 //        , pass_hipt
 //        );       

 for(int i = 0; i < Shifted_muPt.size(); i++) 
 {    
  //  printf(" Muon %i    %i %i %i %i %i \n",i
  //        ,muIDbit->at(i) >> 0 & 0x1 
  //        ,muIDbit->at(i) >> 1 & 0x1 
  //        ,muIDbit->at(i) >> 2 & 0x1 
  //        ,muIDbit->at(i) >> 3 & 0x1 
  //        ,muIDbit->at(i) >> 4 & 0x1 
  //        );       

  Float_t muonPt = getMuonPt(i,sysbinname);
  bool pass_kin = false;
  if( i==0 ) pass_kin = (muonPt > muPtCut1) && ( fabs(AOD_muEta->at(i)) < muEtaCut ) ;
  else       pass_kin = (muonPt > muPtCut2) && ( fabs(AOD_muEta->at(i)) < muEtaCut ) ;

  bool pass_bit = AOD_muPassLooseID->at(i);//muIDbit->at(i) >> bitnr & 0x1 == 1;<------need to add      

  if (muoid = "Loose")  muoisoval = 0.25 ;
  if (muoid = "Medium") muoisoval = 0.25 ;
  if (muoid = "Tight")  muoisoval = 0.15 ;
  bool pass_iso = AOD_muPFdBetaIsolation->at(i) < muoisoval ;

  if( pass_bit && pass_kin && pass_iso )
  {
   //printf(" a selected muon\n");
   nSelectedMuo++;
   mulist.push_back(i);
  } // if pass_bit && pass_kin
 } // loop over muons
 return mulist;
}

//-------------------------electron_passID
std::vector<int> analyzer_createobjects::electron_passID( int bitnr, Float_t elePtCut1, Float_t elePtCut2, Float_t eleEtaCut, TString sysbinname)
{

 std::vector<int> elelist;
 // veto loose medium tight heep hlt

 for(int i = 0; i < nAODEle; i++) 
 {    

  Float_t electronPt = getElectronPt(i,sysbinname);

  bool pass_kin = false;
  if( i==0 ) pass_kin =  (electronPt > elePtCut1) && ( fabs(AOD_eleEta->at(i)) < eleEtaCut ) ;
  else       pass_kin =  (electronPt > elePtCut2) && ( fabs(AOD_eleEta->at(i)) < eleEtaCut ) ;
  
  

  bool pass_convsersion_veto = (AOD_elePassConversionVeto->at(i) > 0); //could have been bool

  bool pass_bit = AOD_eleIDbit->at(i) >> bitnr & 0x1 == 1;      

  bool pass_overlap = true;
/*
  if(photon_list.size()>0){
   for(int d=0; d<photon_list.size(); ++d){
    int phoindex = photon_list[d];
    if(phoindex<= (AOD_phoEta->size()-1) && phoindex<= (AOD_phoPhi->size()-1)){
     if( dR( AOD_phoEta->at(phoindex),AOD_phoPhi->at(phoindex), AOD_eleEta->at(i),AOD_elePhi->at(i) ) < objcleandRcut )  pass_overlap=false;
    }
   }//end photons
  } // if photons
*/
  //// isolation already in VID
  //bool pass_iso = AOD_elePFdBetaIsolationRhoEA ->at(i) <  [SELBINNAMESIZE][LEPBINNAMESIZE];
  //bool pass_iso = AOD_elePFdBetaIsolationCHS   ->at(i) <  [SELBINNAMESIZE][LEPBINNAMESIZE];
  //bool pass_iso = AOD_elePFdBetaIsolationDiff  ->at(i) <  [SELBINNAMESIZE][LEPBINNAMESIZE];

  bool pass_crack = (fabs(AOD_eleEta->at(i))<1.442) ||  (fabs(AOD_eleEta->at(i))>1.566);

  if( pass_bit && pass_kin && pass_overlap && pass_convsersion_veto && pass_crack )
  {
   nSelectedEle++;
   //printf(" a selected electron\n");
   elelist.push_back(i);
  } // if pass_bit && pass_kin
 } // loop over electrons

 //if(elelist.size()>1)std::cout<<"*********************************************************************************" <<std::endl;
 //if(elelist.size()>1){for(int ii=0; ii<elelist.size(); ii++){std::cout<<"Before sort: index: "<<ii<<", Pt: "<<getElectronPt(elelist[ii], sysbinname)<<"  Eta: "<<AOD_eleEta->at(elelist[ii])<<std::endl;}}
 //if(elelist.size()>1)std::cout<<"*********************************************************************************"<<std::endl;
 
  std::sort(elelist.begin(),elelist.end(), 
           [&]( int a, int b ) { return AOD_elePt->at(a) > AOD_elePt->at(b); });
   
  /* for (int ii = (elelist.size() - 1); ii >= 0; ii--)
   {
     for (int jj = 1; jj <=ii; jj++)
     {
       if( getElectronPt(elelist[jj-1], sysbinname) < getElectronPt(elelist[jj],sysbinname) )
       {
        int temp = elelist[jj-1];
        elelist[jj-1] = elelist[jj];
        elelist[jj] = temp;
    } } } 
  */
   
   //if(elelist.size()>1)std::cout<<"*********************************************************************************" <<std::endl;
   //if(elelist.size()>1){for(int ii=0; ii<elelist.size(); ii++){std::cout<<"After sort: index: "<<ii<<", Pt:  "<<getElectronPt(elelist[ii], sysbinname)<<"  Eta: "<<AOD_eleEta->at(elelist[ii])<<std::endl;}}
   //if(elelist.size()>1)std::cout<<"*********************************************************************************"<<std::endl;
 return elelist;
}
 

//-------------------------jet_passTagger
std::vector<int> analyzer_createobjects::jet_passTagger( ) {

  std::vector<int> taglist;

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int aodcalojetindex = aodcalojet_list[i];
   if( Shifted_CaloJetMedianLog10IPSig.at(aodcalojetindex)      >  tag_minIPsig  &&
       Shifted_CaloJetMedianLog10TrackAngle.at(aodcalojetindex) >  tag_minTA     &&
       Shifted_CaloJetAlphaMax.at(aodcalojetindex)              <  tag_maxAmax  )
    {
     taglist.push_back(aodcalojetindex);
    }
  }
  return taglist;
}


//-------------------------jet_minDR
// Finds Delta R of closest "good" jet
std::vector<float> analyzer_createobjects::jet_minDR( ) {

  std::vector<float> minDR_list;
  
  for(int i = 0; i < AODnCaloJet; i++){//all jets

    float min_dR = -1;
    
    for(int j=0; j<aodcalojet_list.size(); ++j){//good jets
      
      if(i == aodcalojet_list[j]) continue;//don't allow check with itself
      
      float my_dR = dR(AODCaloJetEta->at(i), AODCaloJetPhi->at(i), AODCaloJetEta->at(aodcalojet_list[j]), AODCaloJetPhi->at(aodcalojet_list[j]));
      if(my_dR < min_dR || min_dR<0){
	min_dR = my_dR;
      }

    }//j   
    minDR_list.push_back(min_dR);
  }//i
  
  return minDR_list;
}


//-------------------------jet_passID
std::vector<int> analyzer_createobjects::jet_passID( int bitnr, TString jettype, Float_t jetPtCut, Float_t jetEtaCut, TString sysbinname ) {

  std::vector<int> jetlist;

  // set parameters based on jet collection
  int njets;
  if(jettype.EqualTo("calo")){
   njets = AODnCaloJet;
  }
  if(jettype.EqualTo("pf")){
   njets = AODnPFJet;
  }
  if(jettype.EqualTo("pfchs")){
   njets = AODnPFchsJet;
  }

  for(int i = 0; i < njets; i++)
  {

   float jetpt;
   float jeteta;
   float jetphi;
   if(jettype.EqualTo("calo")){
    jetpt  = AODCaloJetPt->at(i) ;       
    jeteta = AODCaloJetEta->at(i);       
    jetphi = AODCaloJetPhi->at(i);              
   }
   if(jettype.EqualTo("pf")){
    jetpt  = AODPFJetPt->at(i) ;       
    jeteta = AODPFJetEta->at(i);       
    jetphi = AODPFJetPhi->at(i);              
   }
   if(jettype.EqualTo("pfchs")){
    jetpt  = AODPFchsJetPt->at(i) ;       
    jeteta = AODPFchsJetEta->at(i);       
    jetphi = AODPFchsJetPhi->at(i);              
   }
   bool pass_overlap = true;
/*
   // check overlap with photons
   if(photon_list.size()>0){
    for(int d=0; d<photon_list.size(); ++d){
     int phoindex = photon_list[d];
     if(phoindex<= (AOD_phoEta->size()-1)&&phoindex<= (AOD_phoPhi->size()-1)){  //  <---- shouldn't be needed?
      if( dR( AOD_phoEta->at(phoindex),AOD_phoPhi->at(phoindex), AODCaloJetEta->at(i),AODCaloJetPhi->at(i) ) < objcleandRcut ){
       pass_overlap=false;
      } // if overlap
     }
    }//end photons
   } // if photons
*/
   //check overlap with electrons
   if(electron_list.size()>0){
    for(int d=0; d<electron_list.size(); ++d){
     //printf(" brgin looping over electrons\n");
     int eleindex = electron_list[d];
     if( dR( AOD_eleEta->at(eleindex), AOD_elePhi->at(eleindex), jeteta, jetphi ) < objcleandRcut )
     {
      pass_overlap=false; // printf(" OL w electron\n");
     } // if overlap
    }//end electrons
   } // if electrons
   //check overlap with muons
   if(muon_list.size()>0){
    for(int d=0; d<muon_list.size(); ++d){
     int muindex = muon_list[d];
     if(muindex<= (AOD_muEta->size()-1)&&muindex<= (AOD_muPhi->size()-1)){
      if( dR( AOD_muEta->at(muindex),AOD_muPhi->at(muindex), jeteta, jetphi ) < objcleandRcut )
      {
       pass_overlap=false; //printf(" OL w muon\n");
      } // if overlap     }
     }
    }//end muons
   } // if muons

   // WHAT ABOUT JET ID?
   bool pass_kin = jetpt > jetPtCut && ( fabs(jeteta) < jetEtaCut ) ;
              
   if( pass_kin && pass_overlap )
   {
    jetlist.push_back(i);
   } // if pass_bit && pass_kin
  }// for(int i = 0; i < nJet; i++)

  return jetlist;

}


//-------------------------photon_passLooseID
std::vector<int> analyzer_createobjects::photon_passID( int bitnr, Float_t AOD_phoPtCut, Float_t phoEtaCut, TString sysbinname){

 std::vector<int> pholist;
 pholist.clear();

 bool pass_overlap = true;
 ////Loop over photons                   
 for(int p=0;p<Shifted_phoPt.size();p++)//<-----change from nPho until we get it
 {    
  Float_t theAOD_phoPt = getPhotonPt(p,sysbinname);
  //Float_t thephoEta = AOD_phoEta->at(p); //AOD_phoSCEta->at(p); doesn't seem to be used unless someone objects, will delete after next PR 5/6/2018

  bool kinematic = theAOD_phoPt > AOD_phoPtCut && fabs((*AOD_phoEta)[p])<phoEtaCut;
  //bool kinematic = theAOD_phoPt > AOD_phoPtCut && fabs(thephoSCEta)<phoEtaCut;
  
   //check overlap with electrons
   if(electron_list.size()>0){
    for(int d=0; d<electron_list.size(); ++d){
     //printf(" brgin looping over electrons\n");
     int eleindex = electron_list[d];
     //std::cout << eleindex <<"      size: "<<electron_list.size()<<"     Eta:  "<<AOD_eleEta->size()<<std::endl;
     if( dR( AOD_eleEta->at(eleindex),AOD_elePhi->at(eleindex), AOD_eleEta->at(eleindex),AOD_elePhi->at(eleindex) ) < objcleandRcut )
     {
      pass_overlap=false; // printf(" OL w electron\n");
     } // if overlap
    }//end electrons
   } // if electrons



  bool pass_bit = AOD_phoIDbit->at(p) >> bitnr & 0x1 == 1; //phoIDbit->at(p) >> bitnr & 0x1 == 1; 
  //printf(" photon %i %i %i\n",p,bitnr,pass_bit);

  if( kinematic && pass_bit && pass_overlap ){
   nSelectedPho++;
   //printf("selected aphoton\n");
   pholist.push_back(p);
  }    
 }    

 return pholist;

}


//-------------------------dR
double analyzer_createobjects::dR(double eta1, double phi1, double eta2, double phi2)
{
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//-------------------------DeltaPhi
double analyzer_createobjects::DeltaPhi(double phi1, double phi2)
//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
{
  double pi = TMath::Pi();
  double dphi = fabs(phi1-phi2);
  if(dphi>pi) 
    dphi = 2.0*pi - dphi;
  return dphi;
}

//-------------------------getMuonPt
Float_t analyzer_createobjects::getMuonPt(int i, TString sysbinname){

      //Muon passes pt cut 
      Float_t muonPt = Shifted_muPt.at(i);
      Float_t muonEnergy = muonPt*TMath::CosH( AOD_muEta->at(i) );
      if(sysbinname=="_MESUp"  ){ muonEnergy*=(1.0 + 0.020); }
      if(sysbinname=="_MESDown"){ muonEnergy*=(1.0 - 0.020); }

      muonPt = muonEnergy/TMath::CosH( AOD_muEta->at(i) );
  return muonPt;

}

//-------------------------getElectronPt
Float_t analyzer_createobjects::getElectronPt(int i, TString sysbinname){

      //Electron passes pt cut 
      Float_t electronPt = Shifted_elePt.at(i);
      Float_t electronEnergy = electronPt*TMath::CosH( AOD_eleEta->at(i) );
      if(sysbinname=="_EGSUp"  ){ electronEnergy*=(1.0 + 0.020); }
      if(sysbinname=="_EGSDown"){ electronEnergy*=(1.0 - 0.020); }

      electronPt = electronEnergy/TMath::CosH( AOD_eleEta->at(i) );

  return electronPt;

}

//-------------------------getPhotonPt
Float_t analyzer_createobjects::getPhotonPt(int idnr, TString sysbinname){

      Float_t photonenergy = AOD_phoSCEn->at(idnr);
      if(sysbinname=="_EGSUp"  ){ photonenergy*=(1. + 0.020); }
      if(sysbinname=="_EGSDown"){ photonenergy*=(1. - 0.020); }

      Float_t AOD_phoPt = photonenergy/TMath::CosH( (*AOD_phoSCEta)[idnr] );

  return AOD_phoPt;

}


//-------------------------getMET
Float_t analyzer_createobjects::getMET(){
 themet   = AOD_pfMET_pt; //AOD_pfChMET_pt;
 themephi = AOD_pfMET_phi; // AOD_pfChMET_phi;
}



//-------------------------calculateHT
void analyzer_createobjects::calculateHT(){
  // calculate ht
  htall  = 0.;
  htaodcalojets = 0.;

  for(int i=0; i<photon_list.size(); ++i){
   int phoindex = photon_list[i];
   htall += Shifted_phoPt.at(phoindex);
  }

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   htall += Shifted_elePt.at(eleindex);
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   htall += Shifted_muPt.at(muindex);
  }

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int aodcalojetindex = aodcalojet_list[i];
   htall  += AODCaloJetPt->at(aodcalojetindex);
   htaodcalojets += AODCaloJetPt->at(aodcalojetindex);
  }

  return;
}


//-------------------------makeDiLepton
void analyzer_createobjects::makeDiLepton(){

  // make dilepton pair
  fourVec_l1.SetPtEtaPhiE(0,0,0,0);
  fourVec_l2.SetPtEtaPhiE(0,0,0,0);

  // get electrons and muons and put into 4vectors
  makeDilep(&fourVec_l1, &fourVec_l2, &fourVec_ee, &fourVec_mm);
  // make dilepton object
  fourVec_ll = fourVec_l1 + fourVec_l2;
  dilep_mass = fourVec_ll.M();
  dilep_pt   = fourVec_ll.Pt();
 
  // So it looks like these are only used for this calculation, so I will recycle for OSOF
  fourVec_l1.SetPtEtaPhiE(0,0,0,0);
  fourVec_l2.SetPtEtaPhiE(0,0,0,0);
  
  makeDilep(&fourVec_l1, &fourVec_l2, &fourVec_em);
  OSOF_mass = fourVec_em.M();
  OSOF_pt   = fourVec_em.Pt();
  
}

void analyzer_createobjects::makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_em)
{
  TLorentzVector e, m;
  e.SetPtEtaPhiE( 0,0,0,0 );
  m.SetPtEtaPhiE( 0,0,0,0 ); 
  
  // Require exactly 1 electron and 1 muon
  if ( !( (electron_list.size()==1 && muon_list.size()==1) ) ) return;

  //Set the electron and muon fourvectors if they have opposite sign otherwise we will use the dummy vectors.
  if(AOD_eleCharge->at(electron_list[0])*AOD_muCharge->at(muon_list[0])==-1)
  {
    e.SetPtEtaPhiE( Shifted_elePt.at(electron_list[0]), AOD_eleEta->at(electron_list[0]), AOD_elePhi->at(electron_list[0]), AOD_eleEn->at(electron_list[0]) );
    m.SetPtEtaPhiE( Shifted_muPt.at(    muon_list[0]), AOD_muEta ->at(    muon_list[0]), AOD_muPhi ->at(    muon_list[0]), AOD_muEn ->at(    muon_list[0]) );
  }
 
  *fv_1  = e;
  *fv_2  = m;
  *fv_em = e+m; 
  return; 
}

//-------------------------makeDilep
void analyzer_createobjects::makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_ee, TLorentzVector *fv_mm)
{          
                                                                    
  TLorentzVector e1, e2, ee;                                        
  TLorentzVector m1, m2, mm;                                        
  e1.SetPtEtaPhiE( 0,0,0,0 );                                       
  e2.SetPtEtaPhiE( 0,0,0,0 );                                       
  m1.SetPtEtaPhiE( 0,0,0,0 );                                       
  m2.SetPtEtaPhiE( 0,0,0,0 );                                       

  // Require exactly 2 electrons and no muons xor exactly 2 muons and no electrons
  if ( !( (electron_list.size()==2 && muon_list.size()==0) || (electron_list.size()==0 && muon_list.size()==2) ) ) return;

  //The following code selects the OSSF pair with mass closest to Z mass.  
  //Previous cut on electron_list and muon_list sizes means there is at max one pair, so no real choice
  //But we leave this code as is in case we want to use this feature at some point.  It works for the simple case, too.

   // electrons    
   double best_ee_mass = 9e9;
   if( electron_list.size()>1 ){                                           
     for(int i=0; i<electron_list.size(); ++i)                              
       {                                                                
         for(int j=i+1; j<electron_list.size(); ++j)
           {
             if( AOD_eleCharge->at(electron_list[i])*AOD_eleCharge->at(electron_list[j])==-1 )                     
       	{                                                               
       	  TLorentzVector temp1, temp2, temp12;
       	  temp1.SetPtEtaPhiE( Shifted_elePt.at(electron_list[i]), AOD_eleEta->at(electron_list[i]), AOD_elePhi->at(electron_list[i]), AOD_eleEn->at(electron_list[i]) );
       	  temp2.SetPtEtaPhiE( Shifted_elePt.at(electron_list[j]), AOD_eleEta->at(electron_list[j]), AOD_elePhi->at(electron_list[j]), AOD_eleEn->at(electron_list[j]) );  
       	  temp12 = temp1+temp2;
       	  if( fabs(91.1876-temp12.M()) < fabs(91.1876 - best_ee_mass) ){
       	    best_ee_mass = temp12.M();
            e1.SetPtEtaPhiE( Shifted_elePt.at(electron_list[i]), AOD_eleEta->at(electron_list[i]), AOD_elePhi->at(electron_list[i]), AOD_eleEn->at(electron_list[i]) );
            e2.SetPtEtaPhiE( Shifted_elePt.at(electron_list[j]), AOD_eleEta->at(electron_list[j]), AOD_elePhi->at(electron_list[j]), AOD_eleEn->at(electron_list[j]) );  
       	  }
       	}         
           }          
       }           
     ee = e1 + e2;
   }//electron size > 1

   // muons                                
   double best_mm_mass = 9e9;
   int best_mm_i=-1, best_mm_j=-1;
   if( muon_list.size()>1 ){                  
     for(int i=0; i<muon_list.size(); ++i)     
       {                                           
         for(int j=i+1; j<muon_list.size(); ++j)
           {
             if( AOD_muCharge->at(muon_list[i])*AOD_muCharge->at(muon_list[j])==-1 ) 
       	{            
       	  TLorentzVector temp1, temp2, temp12;
       	  temp1.SetPtEtaPhiE( Shifted_muPt.at(muon_list[i]), AOD_muEta->at(muon_list[i]), AOD_muPhi->at(muon_list[i]), AOD_muEn->at(muon_list[i]) );
       	  temp2.SetPtEtaPhiE( Shifted_muPt.at(muon_list[j]), AOD_muEta->at(muon_list[j]), AOD_muPhi->at(muon_list[j]), AOD_muEn->at(muon_list[j]) );  
       	  temp12 = temp1+temp2;
       	  if( fabs(91.1876-temp12.M()) < fabs(91.1876 - best_mm_mass) ){
       	    best_mm_mass = temp12.M();
            m1.SetPtEtaPhiE( Shifted_muPt.at(muon_list[i]), AOD_muEta->at(muon_list[i]), AOD_muPhi->at(muon_list[i]), AOD_muEn->at(muon_list[i]) );
            m2.SetPtEtaPhiE( Shifted_muPt.at(muon_list[j]), AOD_muEta->at(muon_list[j]), AOD_muPhi->at(muon_list[j]), AOD_muEn->at(muon_list[j]) );  
       	  } 
       	}   
           }    
       }
     mm = m1 + m2;      
   }//muon size > 1

   *fv_ee = ee;  
   *fv_mm = mm;  

   // take pair closest to Z mass
   if( fabs(91.1876-ee.M()) < fabs(91.1876-mm.M()) ){
     *fv_1 = e1; 
     *fv_2 = e2;
   } 
   else{
     *fv_1 = m1; 
     *fv_2 = m2;
   }

   return;                                                          
                                                                   
}

void analyzer_createobjects::shiftCollections( TString uncbin )
{

  Shifted_elePt                       .clear();  
  Shifted_phoPt                       .clear();  
  Shifted_muPt                        .clear();  
  Shifted_CaloJetPt                   .clear();  
  Shifted_CaloJetAlphaMax             .clear();  
  Shifted_CaloJetMedianLog10IPSig     .clear();  
  Shifted_CaloJetMedianLog10TrackAngle.clear();  

 for(unsigned int i=0; i<AOD_elePt->size(); ++i){
  Shifted_elePt.push_back( AOD_elePt->at(i));
 }
 for(unsigned int i=0; i<AOD_phoPt->size(); ++i){
  Shifted_phoPt.push_back( AOD_phoPt->at(i));
 }
 for(unsigned int i=0; i<AOD_muPt->size(); ++i){
  Shifted_muPt.push_back( AOD_muPt->at(i));
 }
 for(unsigned int i=0; i<AODCaloJetPt->size(); ++i){
  Shifted_CaloJetPt.push_back( AODCaloJetPt->at(i));
 }
 for(unsigned int i=0; i<AODCaloJetAlphaMax->size(); ++i){
  Shifted_CaloJetAlphaMax.push_back( AODCaloJetAlphaMax->at(i));
 }
 for(unsigned int i=0; i<AODCaloJetMedianLog10IPSig->size(); ++i){
  Shifted_CaloJetMedianLog10IPSig.push_back( AODCaloJetMedianLog10IPSig->at(i));
 }
 for(unsigned int i=0; i<AODCaloJetMedianLog10TrackAngle->size(); ++i){
  Shifted_CaloJetMedianLog10TrackAngle.push_back( AODCaloJetMedianLog10TrackAngle->at(i));
 }

// for(unsigned int i=0; i<AOD_elePt->size(); ++i){
//  std::cout<<" AOD_elePt->at(i) "<< AOD_elePt->at(i)<<" Shifted_elePt.at(i) "<< Shifted_elePt.at(i) <<std::endl;
// }

 for(unsigned int i=0; i<Shifted_elePt.size(); ++i){
  Shifted_elePt.at(i) = getElectronPt(i,uncbin);
 }
 for(unsigned int i=0; i<Shifted_phoPt.size(); ++i){
  Shifted_phoPt.at(i) = getPhotonPt(i,uncbin);
 }
 for(unsigned int i=0; i<Shifted_muPt.size(); ++i){
  Shifted_muPt.at(i) = getMuonPt(i,uncbin);
 }

 float deltaAmax  = (tag_shiftmaxAmax/tag_maxAmax) - 1.    ;
 float deltaIPsig = (tag_shiftminIPsig/tag_minIPsig) - 1.  ;
 float deltaTA    = (tag_shiftminTA/tag_minTA) - 1.        ;
 if(uncbin.EqualTo( "_AMaxUp") || uncbin.EqualTo( "_TagVarsUp") ){ 
  for(unsigned int i=0; i<Shifted_CaloJetAlphaMax.size(); ++i){
   Shifted_CaloJetAlphaMax.at(i) = Shifted_CaloJetAlphaMax.at(i) * (1+deltaAmax) ;
  }
 }
 if(uncbin.EqualTo( "_AMaxDown") || uncbin.EqualTo( "_TagVarsDown") ){ 
  for(unsigned int i=0; i<Shifted_CaloJetAlphaMax.size(); ++i){
   Shifted_CaloJetAlphaMax.at(i) = Shifted_CaloJetAlphaMax.at(i) * (1-deltaAmax) ;
  }
 }
 if(uncbin.EqualTo( "_IPSigUp")   || uncbin.EqualTo( "_TagVarsUp")    ){ 
  for(unsigned int i=0; i<Shifted_CaloJetMedianLog10IPSig.size(); ++i){
   Shifted_CaloJetMedianLog10IPSig.at(i) = Shifted_CaloJetMedianLog10IPSig.at(i) * (1+deltaIPsig) ;
  }
 }
 if(uncbin.EqualTo( "_IPSigDown") || uncbin.EqualTo( "_TagVarsDown")  ){ 
  for(unsigned int i=0; i<Shifted_CaloJetMedianLog10IPSig.size(); ++i){
   Shifted_CaloJetMedianLog10IPSig.at(i) = Shifted_CaloJetMedianLog10IPSig.at(i) * (1-deltaIPsig) ;
  }
 }
 if(uncbin.EqualTo( "_TAUp")      || uncbin.EqualTo( "_TagVarsUp")    ){ 
  for(unsigned int i=0; i<Shifted_CaloJetMedianLog10TrackAngle.size(); ++i){
   Shifted_CaloJetMedianLog10TrackAngle.at(i) = Shifted_CaloJetMedianLog10TrackAngle.at(i) * (1+deltaTA) ;
  }
 }
 if(uncbin.EqualTo( "_TADown")    || uncbin.EqualTo( "_TagVarsDown")  ){ 
  for(unsigned int i=0; i<Shifted_CaloJetMedianLog10TrackAngle.size(); ++i){
   Shifted_CaloJetMedianLog10TrackAngle.at(i) = Shifted_CaloJetMedianLog10TrackAngle.at(i) * (1-deltaTA) ;
  }
 }

 return;

}

