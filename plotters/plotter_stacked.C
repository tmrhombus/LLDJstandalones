
#include <stdlib.h>     /* getenv */

void plotter_stacked()
{

 // Draw signal as lines
 Bool_t drawSignal = kFALSE;

 // path to root files
 TString inpath  = TString("../roots/");
 TString outpath = TString("../plots/");
 //TString aversion = TString(getenv("aversion"));
 //inpath = inpath+aversion+"/";
 //outpath = outpath+aversion+"/";

 // y axis plots as log
 Bool_t dolog = kTRUE;
 TString extraname = "";
 if(dolog){extraname+="_log";}
 if(drawSignal){extraname+="_wsig";}

 // phase space regions to plot
 std::vector<TString> regions;
 regions.clear();
 regions.push_back("NoSel");
 //regions.push_back("Sig");
 regions.push_back("ZH");
 regions.push_back("DY");
 regions.push_back("OffZ");
 regions.push_back("NoPair");

 // jet types to plot
 std::vector<TString> jettypes;
 jettypes.clear();
 jettypes.push_back("ALLCALOJETS");                          
 //jettypes.push_back("ALLCALOJETSMATCHED");                   
 jettypes.push_back("BASICCALOJETS");                        
 //jettypes.push_back("BASICCALOJETS1");                       
 //jettypes.push_back("BASICCALOJETS1MATCHED");                
 jettypes.push_back("BASICCALOJETS1PT20");                   
 //jettypes.push_back("BASICCALOJETS1PT20MATCHED");            
 //jettypes.push_back("BASICCALOJETSMATCHED");                 
 jettypes.push_back("INCLUSIVETAGGEDCALOJETS");              
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETS20");            
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETS20MATCHED");     
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETS60");            
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETS60MATCHED");     
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSA");             
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSAMATCHED");      
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSB");             
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSBMATCHED");      
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSC");             
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSCMATCHED");      
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSD");             
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSDMATCHED");      
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSE");             
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSEMATCHED");      
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSF");             
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSFMATCHED");      
 //jettypes.push_back("INCLUSIVETAGGEDCALOJETSMATCHED");       

 // variables to plot
 std::vector<TString> variables;
 variables.clear();
// variables.push_back("NELECTRONS");                                
// variables.push_back("NELECTRONS30");                              
// variables.push_back("NELECTRONSFROMBOSON");                       
// variables.push_back("NGOODELECTRONS");                            
// variables.push_back("NGOODLEPTONS");                              
// variables.push_back("NGOODMUONS");                                
// variables.push_back("NGOODVERTICES");                             
// variables.push_back("NKSHORTS");                                  
// variables.push_back("NMUONS");                                    
// variables.push_back("NMUONS30");                                  
// variables.push_back("NMUONSFROMBOSON");                           
// variables.push_back("NOSSF");                                     
// variables.push_back("N_bJetsCSVL");                               
// variables.push_back("N_bJetsCSVM");                               
// variables.push_back("N_bosons");                                  
// variables.push_back("PU_NumInteractions");                        
// variables.push_back("fakeIncarnation");                           
// variables.push_back("ELECTRON_PT");                               
// variables.push_back("FLATWEIGHT");                                
// variables.push_back("HLTHT");                                     
// variables.push_back("HSPH");                                      
 variables.push_back("HT");                                        
// variables.push_back("HTHLTID");                                   
// variables.push_back("HT_All");                                    
// variables.push_back("LEPTON_DANGLE");                             
// variables.push_back("LEPTON_DPHI");                               
// variables.push_back("LRM");                                       
 variables.push_back("MET");                                       
//   variables.push_back("MOSSF");                                     
//   variables.push_back("MUON_PT");                                   
//  // variables.push_back("OSSFCLOSEMLL");                              
//  // variables.push_back("OSSFMAXMLL");                                
//  // variables.push_back("OSSFMINMLL");                                
//   variables.push_back("PTOSSF");                                    
//  // //variables.push_back("SCALAR_PT");                                 
//  // //variables.push_back("SIGNALQUARKS_GENDXY");                       
//  // //variables.push_back("SIGNALQUARKS_P");                            
//  // //variables.push_back("SIGNALQUARKS_PT");                           
//  // variables.push_back("SSPH");                                      
//  // variables.push_back("TrueNumInteractions");                       
//  // variables.push_back("rhoAll");                                    
//  // variables.push_back("rhoNeutral");                                
//  // variables.push_back("stupakR");                                   
//  // variables.push_back("stupakR2");                                  
//  // variables.push_back("LeadingJet_MISSINGINNER");                   
//  // variables.push_back("LeadingJet_MISSINGOUTER");                   
//  // variables.push_back("LeadingJet_HSPH");                           
//  // variables.push_back("LeadingJet_NJets");                          
//  // variables.push_back("LeadingJet_NCLEANMATCHEDTRACKS");            
//  // variables.push_back("LeadingJet_NMATCHEDTRACKS");                 
//  // variables.push_back("LeadingJet_NTRACKSIPLT0P05");                
//  // variables.push_back("LeadingJet_NTRACKSIPSIGGT10");               
//  // variables.push_back("LeadingJet_NTRACKSIPSIGLT5");                
//  // variables.push_back("LeadingJet_ALPHAMAX2");                      
//  // variables.push_back("LeadingJet_ALPHAMAXPRIME2");                 
//  // variables.push_back("LeadingJet_ALPHAMAXPRIME");                  
//  // variables.push_back("LeadingJet_ALPHAMAX");                       
//  // variables.push_back("LeadingJet_ASSOCAPLANARITY");                
//  // variables.push_back("LeadingJet_ASSOCIATEDTRACKPT");              
//  // variables.push_back("LeadingJet_ASSOCSPHERICITY");                
//  // variables.push_back("LeadingJet_ASSOCTHRUSTMAJOR");               
//  // variables.push_back("LeadingJet_ASSOCTHRUSTMINOR");               
//  // variables.push_back("LeadingJet_AVFASSOCAPLANARITY");             
//  // variables.push_back("LeadingJet_AVFASSOCSPHERICITY");             
//  // variables.push_back("LeadingJet_AVFASSOCTHRUSTMAJOR");            
//  // variables.push_back("LeadingJet_AVFASSOCTHRUSTMINOR");            
//  // variables.push_back("LeadingJet_AVFBEAMSPOTDELTAPHI");            
//  // variables.push_back("LeadingJet_AVFBEAMSPOTRECOILPT");            
//  // variables.push_back("LeadingJet_AVFDISTTOPV");                    
//  // variables.push_back("LeadingJet_AVFVERTEXCHI2NDOF");              
//  // variables.push_back("LeadingJet_AVFVERTEXDEGREESOFFREEDOM");      
//  // variables.push_back("LeadingJet_AVFVERTEXDISTANCETOBEAM");        
//  // variables.push_back("LeadingJet_AVFVERTEXTOTALCHISQUARED");       
//  // variables.push_back("LeadingJet_AVFVERTEXTRACKENERGY");           
//  // variables.push_back("LeadingJet_AVFVERTEXTRACKMASS");             
//  // variables.push_back("LeadingJet_AVFVERTEXTRANSVERSESIG");         
//  // variables.push_back("LeadingJet_AVGMISSINGINNER");                
//  // variables.push_back("LeadingJet_AVGMISSINGOUTER");                
//  // //variables.push_back("LeadingJet_BASICCALOJETS1ANGLE_DANGLE");     
//  // //variables.push_back("LeadingJet_BASICCALOJETS1ANGLE_DPHI");       
//  // //variables.push_back("LeadingJet_BASICCALOJETS1DELTAR");           
//  // //variables.push_back("LeadingJet_BASICCALOJETS1PT20DELTAR");       
//  // variables.push_back("LeadingJet_BETA2");                          
//   variables.push_back("LeadingJet_BETA");                           
//   variables.push_back("LeadingJet_ETA");                            
//  // variables.push_back("LeadingJet_HITSINFRONTOFVERTPERTRACK");      
//  // variables.push_back("LeadingJet_IVFSCORE");                       
//   variables.push_back("LeadingJet_JETAREA");                        
//  // variables.push_back("LeadingJet_LEPANGLE_DANGLE");                
//  // variables.push_back("LeadingJet_LEPANGLE_DPHI");                  
//  // variables.push_back("LeadingJet_LEPDELTAR");                      
//  // variables.push_back("LeadingJet_LINEARRADIALMOMENT");             
//  // variables.push_back("LeadingJet_LRM");                            
//  // variables.push_back("LeadingJet_MASSDISPLACED");                  
//  // variables.push_back("LeadingJet_MEDIANIPLOG10SIG");               
//  // variables.push_back("LeadingJet_MEDIANIPLOGSIG");                 
//  // variables.push_back("LeadingJet_MEDIANLOG10TRACKANGLE");          
//  // variables.push_back("LeadingJet_METANGLE_DANGLE");                
//  // variables.push_back("LeadingJet_METANGLE_DPHI");                  
//   variables.push_back("LeadingJet_METDELTAR");                      
//  // variables.push_back("LeadingJet_MISSHITSAFTERVERTPERTRACK");      
//   variables.push_back("LeadingJet_M");                              
//   variables.push_back("LeadingJet_PHI");                            
//   variables.push_back("LeadingJet_PT");                             
//  // variables.push_back("LeadingJet_SELFDELTAR");                     
//  // variables.push_back("LeadingJet_SSPH");                           
//  // variables.push_back("LeadingJet_STUPAKPT");                       
//  // //variables.push_back("LeadingJet_STUPAKR");                        
//  // variables.push_back("LeadingJet_SUMIPLOGSIG");                    
//  // variables.push_back("LeadingJet_SUMIPSIG");                       
//  // variables.push_back("LeadingJet_SUMIP");                          
//  // variables.push_back("LeadingJet_TOTALTRACKANGLEPT");              
//  // variables.push_back("LeadingJet_TOTALTRACKANGLE");                
//  // variables.push_back("LeadingJet_TOTALTRACKPT");                   
//  // variables.push_back("LeadingJet_TRACKENERGY");                    
//  // variables.push_back("LeadingJet_TRACKMASS");                      
//  // variables.push_back("SubleadingJet_MISSINGINNER");                
//  // variables.push_back("SubleadingJet_MISSINGOUTER");                
//  // variables.push_back("SubleadingJet_HSPH");                        
//  // variables.push_back("SubleadingJet_NJets");                       
//  // variables.push_back("SubleadingJet_NCLEANMATCHEDTRACKS");         
//  // variables.push_back("SubleadingJet_NMATCHEDTRACKS");              
//  // variables.push_back("SubleadingJet_NTRACKSIPLT0P05");             
//  // variables.push_back("SubleadingJet_NTRACKSIPSIGGT10");            
//  // variables.push_back("SubleadingJet_NTRACKSIPSIGLT5");             
//  // variables.push_back("SubleadingJet_ALPHAMAX2");                   
//  // variables.push_back("SubleadingJet_ALPHAMAXPRIME2");              
//  // variables.push_back("SubleadingJet_ALPHAMAXPRIME");               
//  // variables.push_back("SubleadingJet_ALPHAMAX");                    
//  // variables.push_back("SubleadingJet_ASSOCAPLANARITY");             
//  // variables.push_back("SubleadingJet_ASSOCIATEDTRACKPT");           
//  // variables.push_back("SubleadingJet_ASSOCSPHERICITY");             
//  // variables.push_back("SubleadingJet_ASSOCTHRUSTMAJOR");            
//  // variables.push_back("SubleadingJet_ASSOCTHRUSTMINOR");            
//  // variables.push_back("SubleadingJet_AVFASSOCAPLANARITY");          
//  // variables.push_back("SubleadingJet_AVFASSOCSPHERICITY");          
//  // variables.push_back("SubleadingJet_AVFASSOCTHRUSTMAJOR");         
//  // variables.push_back("SubleadingJet_AVFASSOCTHRUSTMINOR");         
//  // variables.push_back("SubleadingJet_AVFBEAMSPOTDELTAPHI");         
//  // variables.push_back("SubleadingJet_AVFBEAMSPOTRECOILPT");         
//  // variables.push_back("SubleadingJet_AVFDISTTOPV");                 
//  // variables.push_back("SubleadingJet_AVFVERTEXCHI2NDOF");           
//  // variables.push_back("SubleadingJet_AVFVERTEXDEGREESOFFREEDOM");   
//  // variables.push_back("SubleadingJet_AVFVERTEXDISTANCETOBEAM");     
//  // variables.push_back("SubleadingJet_AVFVERTEXTOTALCHISQUARED");    
//  // variables.push_back("SubleadingJet_AVFVERTEXTRACKENERGY");        
//  // variables.push_back("SubleadingJet_AVFVERTEXTRACKMASS");          
//  // variables.push_back("SubleadingJet_AVFVERTEXTRANSVERSESIG");      
//  // variables.push_back("SubleadingJet_AVGMISSINGINNER");             
//  // variables.push_back("SubleadingJet_AVGMISSINGOUTER");             
//  // variables.push_back("SubleadingJet_BASICCALOJETS1ANGLE_DANGLE");  
//  // variables.push_back("SubleadingJet_BASICCALOJETS1ANGLE_DPHI");    
//  // variables.push_back("SubleadingJet_BASICCALOJETS1DELTAR");        
//  // variables.push_back("SubleadingJet_BASICCALOJETS1PT20DELTAR");    
//  // variables.push_back("SubleadingJet_BETA2");                       
//  // variables.push_back("SubleadingJet_BETA");                        
//  // variables.push_back("SubleadingJet_ETA");                         
//  // variables.push_back("SubleadingJet_HITSINFRONTOFVERTPERTRACK");   
//  // variables.push_back("SubleadingJet_IVFSCORE");                    
//  // variables.push_back("SubleadingJet_JETAREA");                     
//  // variables.push_back("SubleadingJet_LEPANGLE_DANGLE");             
//  // variables.push_back("SubleadingJet_LEPANGLE_DPHI");               
//  // variables.push_back("SubleadingJet_LEPDELTAR");                   
//  // variables.push_back("SubleadingJet_LINEARRADIALMOMENT");          
//  // variables.push_back("SubleadingJet_LRM");                         
//  // variables.push_back("SubleadingJet_MASSDISPLACED");               
//  // variables.push_back("SubleadingJet_MEDIANIPLOG10SIG");            
//  // variables.push_back("SubleadingJet_MEDIANIPLOGSIG");              
//  // variables.push_back("SubleadingJet_MEDIANLOG10TRACKANGLE");       
//  // variables.push_back("SubleadingJet_METANGLE_DANGLE");             
//  // variables.push_back("SubleadingJet_METANGLE_DPHI");               
//  // variables.push_back("SubleadingJet_METDELTAR");                   
//  // variables.push_back("SubleadingJet_MISSHITSAFTERVERTPERTRACK");   
//  // variables.push_back("SubleadingJet_M");                           
//  // variables.push_back("SubleadingJet_PHI");                         
//  // variables.push_back("SubleadingJet_PT");                          
//  // variables.push_back("SubleadingJet_SELFDELTAR");                  
//  // variables.push_back("SubleadingJet_SSPH");                        
//  // variables.push_back("SubleadingJet_STUPAKPT");                    
//  // //variables.push_back("SubleadingJet_STUPAKR");                     
//  // variables.push_back("SubleadingJet_SUMIPLOGSIG");                 
//  // variables.push_back("SubleadingJet_SUMIPSIG");                    
//  // variables.push_back("SubleadingJet_SUMIP");                       
//  // variables.push_back("SubleadingJet_TOTALTRACKANGLEPT");           
//  // variables.push_back("SubleadingJet_TOTALTRACKANGLE");             
//  // variables.push_back("SubleadingJet_TOTALTRACKPT");                
//  // variables.push_back("SubleadingJet_TRACKENERGY");                 
//  // variables.push_back("SubleadingJet_TRACKMASS");                   
//  // variables.push_back("ThirdJet_MISSINGINNER");                     
//  // variables.push_back("ThirdJet_MISSINGOUTER");                     
//  // variables.push_back("ThirdJet_HSPH");                             
//  // variables.push_back("ThirdJet_NJets");                            
//  // variables.push_back("ThirdJet_NCLEANMATCHEDTRACKS");              
//  // variables.push_back("ThirdJet_NMATCHEDTRACKS");                   
//  // variables.push_back("ThirdJet_NTRACKSIPLT0P05");                  
//  // variables.push_back("ThirdJet_NTRACKSIPSIGGT10");                 
//  // variables.push_back("ThirdJet_NTRACKSIPSIGLT5");                  
//  // variables.push_back("ThirdJet_ALPHAMAX2");                        
//  // variables.push_back("ThirdJet_ALPHAMAXPRIME2");                   
//  // variables.push_back("ThirdJet_ALPHAMAXPRIME");                    
//  // variables.push_back("ThirdJet_ALPHAMAX");                         
//  // variables.push_back("ThirdJet_ASSOCAPLANARITY");                  
//  // variables.push_back("ThirdJet_ASSOCIATEDTRACKPT");                
//  // variables.push_back("ThirdJet_ASSOCSPHERICITY");                  
//  // variables.push_back("ThirdJet_ASSOCTHRUSTMAJOR");                 
//  // variables.push_back("ThirdJet_ASSOCTHRUSTMINOR");                 
//  // variables.push_back("ThirdJet_AVFASSOCAPLANARITY");               
//  // variables.push_back("ThirdJet_AVFASSOCSPHERICITY");               
//  // variables.push_back("ThirdJet_AVFASSOCTHRUSTMAJOR");              
//  // variables.push_back("ThirdJet_AVFASSOCTHRUSTMINOR");              
//  // variables.push_back("ThirdJet_AVFBEAMSPOTDELTAPHI");              
//  // variables.push_back("ThirdJet_AVFBEAMSPOTRECOILPT");              
//  // variables.push_back("ThirdJet_AVFDISTTOPV");                      
//  // variables.push_back("ThirdJet_AVFVERTEXCHI2NDOF");                
//  // variables.push_back("ThirdJet_AVFVERTEXDEGREESOFFREEDOM");        
//  // variables.push_back("ThirdJet_AVFVERTEXDISTANCETOBEAM");          
//  // variables.push_back("ThirdJet_AVFVERTEXTOTALCHISQUARED");         
//  // variables.push_back("ThirdJet_AVFVERTEXTRACKENERGY");             
//  // variables.push_back("ThirdJet_AVFVERTEXTRACKMASS");               
//  // variables.push_back("ThirdJet_AVFVERTEXTRANSVERSESIG");           
//  // variables.push_back("ThirdJet_AVGMISSINGINNER");                  
//  // variables.push_back("ThirdJet_AVGMISSINGOUTER");                  
//  // variables.push_back("ThirdJet_BASICCALOJETS1ANGLE_DANGLE");       
//  // variables.push_back("ThirdJet_BASICCALOJETS1ANGLE_DPHI");         
//  // variables.push_back("ThirdJet_BASICCALOJETS1DELTAR");             
//  // variables.push_back("ThirdJet_BASICCALOJETS1PT20DELTAR");         
//  // variables.push_back("ThirdJet_BETA2");                            
//  // variables.push_back("ThirdJet_BETA");                             
//  // variables.push_back("ThirdJet_ETA");                              
//  // variables.push_back("ThirdJet_HITSINFRONTOFVERTPERTRACK");        
//  // variables.push_back("ThirdJet_IVFSCORE");                         
//  // variables.push_back("ThirdJet_JETAREA");                          
//  // variables.push_back("ThirdJet_LEPANGLE_DANGLE");                  
//  // variables.push_back("ThirdJet_LEPANGLE_DPHI");                    
//  // variables.push_back("ThirdJet_LEPDELTAR");                        
//  // variables.push_back("ThirdJet_LINEARRADIALMOMENT");               
//  // variables.push_back("ThirdJet_LRM");                              
//  // variables.push_back("ThirdJet_MASSDISPLACED");                    
//  // variables.push_back("ThirdJet_MEDIANIPLOG10SIG");                 
//  // variables.push_back("ThirdJet_MEDIANIPLOGSIG");                   
//  // variables.push_back("ThirdJet_MEDIANLOG10TRACKANGLE");            
//  // variables.push_back("ThirdJet_METANGLE_DANGLE");                  
//  // variables.push_back("ThirdJet_METANGLE_DPHI");                    
//  // variables.push_back("ThirdJet_METDELTAR");                        
//  // variables.push_back("ThirdJet_MISSHITSAFTERVERTPERTRACK");        
//  // variables.push_back("ThirdJet_M");                                
//  // variables.push_back("ThirdJet_PHI");                              
//  // variables.push_back("ThirdJet_PT");                               
//  // variables.push_back("ThirdJet_SELFDELTAR");                       
//  // variables.push_back("ThirdJet_SSPH");                             
//  // variables.push_back("ThirdJet_STUPAKPT");                         
//  // variables.push_back("ThirdJet_STUPAKR");                          
//  // variables.push_back("ThirdJet_SUMIPLOGSIG");                      
//  // variables.push_back("ThirdJet_SUMIPSIG");                         
//  // variables.push_back("ThirdJet_SUMIP");                            
//  // variables.push_back("ThirdJet_TOTALTRACKANGLEPT");                
//  // variables.push_back("ThirdJet_TOTALTRACKANGLE");                  
//  // variables.push_back("ThirdJet_TOTALTRACKPT");                     
//  // variables.push_back("ThirdJet_TRACKENERGY");                      
//  // variables.push_back("ThirdJet_TRACKMASS");                        
//  // variables.push_back("FourthJet_MISSINGINNER");                    
//  // variables.push_back("FourthJet_MISSINGOUTER");                    
//  // variables.push_back("FourthJet_HSPH");                            
//  // variables.push_back("FourthJet_NJets");                           
//  // variables.push_back("FourthJet_NCLEANMATCHEDTRACKS");             
//  // variables.push_back("FourthJet_NMATCHEDTRACKS");                  
//  // variables.push_back("FourthJet_NTRACKSIPLT0P05");                 
//  // variables.push_back("FourthJet_NTRACKSIPSIGGT10");                
//  // variables.push_back("FourthJet_NTRACKSIPSIGLT5");                 
//  // variables.push_back("FourthJet_ALPHAMAX2");                       
//  // variables.push_back("FourthJet_ALPHAMAXPRIME2");                  
//  // variables.push_back("FourthJet_ALPHAMAXPRIME");                   
//  // variables.push_back("FourthJet_ALPHAMAX");                        
//  // variables.push_back("FourthJet_ASSOCAPLANARITY");                 
//  // variables.push_back("FourthJet_ASSOCIATEDTRACKPT");               
//  // variables.push_back("FourthJet_ASSOCSPHERICITY");                 
//  // variables.push_back("FourthJet_ASSOCTHRUSTMAJOR");                
//  // variables.push_back("FourthJet_ASSOCTHRUSTMINOR");                
//  // variables.push_back("FourthJet_AVFASSOCAPLANARITY");              
//  // variables.push_back("FourthJet_AVFASSOCSPHERICITY");              
//  // variables.push_back("FourthJet_AVFASSOCTHRUSTMAJOR");             
//  // variables.push_back("FourthJet_AVFASSOCTHRUSTMINOR");             
//  // variables.push_back("FourthJet_AVFBEAMSPOTDELTAPHI");             
//  // variables.push_back("FourthJet_AVFBEAMSPOTRECOILPT");             
//  // variables.push_back("FourthJet_AVFDISTTOPV");                     
//  // variables.push_back("FourthJet_AVFVERTEXCHI2NDOF");               
//  // variables.push_back("FourthJet_AVFVERTEXDEGREESOFFREEDOM");       
//  // variables.push_back("FourthJet_AVFVERTEXDISTANCETOBEAM");         
//  // variables.push_back("FourthJet_AVFVERTEXTOTALCHISQUARED");        
//  // variables.push_back("FourthJet_AVFVERTEXTRACKENERGY");            
//  // variables.push_back("FourthJet_AVFVERTEXTRACKMASS");              
//  // variables.push_back("FourthJet_AVFVERTEXTRANSVERSESIG");          
//  // variables.push_back("FourthJet_AVGMISSINGINNER");                 
//  // variables.push_back("FourthJet_AVGMISSINGOUTER");                 
//  // variables.push_back("FourthJet_BASICCALOJETS1ANGLE_DANGLE");      
//  // variables.push_back("FourthJet_BASICCALOJETS1ANGLE_DPHI");        
//  // variables.push_back("FourthJet_BASICCALOJETS1DELTAR");            
//  // variables.push_back("FourthJet_BASICCALOJETS1PT20DELTAR");        
//  // variables.push_back("FourthJet_BETA2");                           
//  // variables.push_back("FourthJet_BETA");                            
//  // variables.push_back("FourthJet_ETA");                             
//  // variables.push_back("FourthJet_HITSINFRONTOFVERTPERTRACK");       
//  // variables.push_back("FourthJet_IVFSCORE");                        
//  // variables.push_back("FourthJet_JETAREA");                         
//  // variables.push_back("FourthJet_LEPANGLE_DANGLE");                 
//  // variables.push_back("FourthJet_LEPANGLE_DPHI");                   
//  // variables.push_back("FourthJet_LEPDELTAR");                       
//  // variables.push_back("FourthJet_LINEARRADIALMOMENT");              
//  // variables.push_back("FourthJet_LRM");                             
//  // variables.push_back("FourthJet_MASSDISPLACED");                   
//  // variables.push_back("FourthJet_MEDIANIPLOG10SIG");                
//  // variables.push_back("FourthJet_MEDIANIPLOGSIG");                  
//  // variables.push_back("FourthJet_MEDIANLOG10TRACKANGLE");           
//  // variables.push_back("FourthJet_METANGLE_DANGLE");                 
//  // variables.push_back("FourthJet_METANGLE_DPHI");                   
//  // variables.push_back("FourthJet_METDELTAR");                       
//  // variables.push_back("FourthJet_MISSHITSAFTERVERTPERTRACK");       
//  // variables.push_back("FourthJet_M");                               
//  // variables.push_back("FourthJet_PHI");                             
//  // variables.push_back("FourthJet_PT");                              
//  // variables.push_back("FourthJet_SELFDELTAR");                      
//  // variables.push_back("FourthJet_SSPH");                            
//  // variables.push_back("FourthJet_STUPAKPT");                        
//  // variables.push_back("FourthJet_STUPAKR");                         
//  // variables.push_back("FourthJet_SUMIPLOGSIG");                     
//  // variables.push_back("FourthJet_SUMIPSIG");                        
//  // variables.push_back("FourthJet_SUMIP");                           
//  // variables.push_back("FourthJet_TOTALTRACKANGLEPT");               
//  // variables.push_back("FourthJet_TOTALTRACKANGLE");                 
//  // variables.push_back("FourthJet_TOTALTRACKPT");                    
//  // variables.push_back("FourthJet_TRACKENERGY");                     
//  // variables.push_back("FourthJet_TRACKMASS");                       

 // make canvas and text
 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500); 
 gStyle->SetOptStat(0);
 gPad->SetLogy(dolog);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);

 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.04);
 title->SetTextColor(kBlack);
 title->SetTextAlign(11);
 title->SetTextFont(62);
 
 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.04);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(11);
 //extra->SetTextAlign(13);
 extra->SetTextFont(52);
 
 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.03);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 // initialize histogram files 
 TFile* file_DY50       ; // = new TFile(inpath+"DY50.root"); 
 TFile* file_DY5to50    ; // = new TFile(inpath+"DY5to50.root");   
 TFile* file_STs        ; // = new TFile(inpath+"STs.root");       
 TFile* file_STtbar     ; // = new TFile(inpath+"STtbar.root");    
 TFile* file_STtbarW    ; // = new TFile(inpath+"STtbarW.root");   
 TFile* file_STt        ; // = new TFile(inpath+"STt.root");       
 TFile* file_STtW       ; // = new TFile(inpath+"STtW.root");      
 TFile* file_TTbar      ; // = new TFile(inpath+"TTbar.root");     
 TFile* file_WJets      ; // = new TFile(inpath+"WJets.root");     
 TFile* file_WW         ; // = new TFile(inpath+"WW.root");        
 TFile* file_WZ         ; // = new TFile(inpath+"WZ.root");        
 TFile* file_ZZ         ; // = new TFile(inpath+"ZZ.root");        
 TFile* file_ZHtoLLbb   ; // = new TFile(inpath+"ZHtoLLbb.root");  
 TFile* file_ggZHtoLLbb ; // = new TFile(inpath+"ZHtoLLbb.root");  
 TFile* file_SignalWm   ;
 TFile* file_SignalWp   ;
 TFile* file_SignalZH   ;
 TFile* file_SignalggZH ;

 // initialize histos
 TH1F* h_DY50     ; 
 TH1F* h_DY5to50  ; 
 TH1F* h_STs      ; 
 TH1F* h_STtbar   ; 
 TH1F* h_STtbarW  ; 
 TH1F* h_STt      ; 
 TH1F* h_STtW     ; 
 TH1F* h_TTbar    ; 
 TH1F* h_WJets    ; 
 TH1F* h_WW       ; 
 TH1F* h_WZ       ; 
 TH1F* h_ZZ       ; 
 TH1F* h_ZHtoLLbb   ; 
 TH1F* h_ggZHtoLLbb ; 
 TH1F* h_SignalWm   ;
 TH1F* h_SignalWp   ;
 TH1F* h_SignalZH   ;
 TH1F* h_SignalggZH ;

 // (combined) histos to be made
 TH1F* h_DY ;
 TH1F* h_ST ;
 TH1F* h_VV ;
 TH1F* h_ZH ;
 TH1F* h_totbkg;

 for(unsigned int k=0; k<jettypes.size(); ++k){
  TString jettype = jettypes[k];

  // load histogram files
  file_DY50     = new TFile(inpath+"DY50_"+jettype+".root"); 
  file_DY5to50  = new TFile(inpath+"DY5to50_"+jettype+".root");   
  file_STs      = new TFile(inpath+"STs_"+jettype+".root");       
  file_STtbar   = new TFile(inpath+"STtbar_"+jettype+".root");    
  file_STtbarW  = new TFile(inpath+"STtbarW_"+jettype+".root");   
  file_STt      = new TFile(inpath+"STt_"+jettype+".root");       
  file_STtW     = new TFile(inpath+"STtW_"+jettype+".root");      
  file_TTbar    = new TFile(inpath+"TTbar_"+jettype+".root");     
  file_WJets    = new TFile(inpath+"WJets_"+jettype+".root");     
  file_WW       = new TFile(inpath+"WW_"+jettype+".root");        
  file_WZ       = new TFile(inpath+"WZ_"+jettype+".root");        
  file_ZZ       = new TFile(inpath+"ZZ_"+jettype+".root");        
  file_ZHtoLLbb   = new TFile(inpath+"ZHtoLLbb_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_"+jettype+".root"); 
  file_ggZHtoLLbb = new TFile(inpath+"ZHtoLLbb_ggZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_"+jettype+".root");
  file_SignalWm   = new TFile(inpath+"Signal_WminusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8_"+jettype+".root");
  file_SignalWp   = new TFile(inpath+"Signal_WplusH_HToSSTobbbb_WToLNu_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8_"+jettype+".root");
  file_SignalZH   = new TFile(inpath+"Signal_ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8_"+jettype+".root");
  file_SignalggZH = new TFile(inpath+"Signal_ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8_"+jettype+".root");

  for(unsigned int i=0; i<regions.size(); ++i){
   TString region = regions[i];

   for(unsigned int j=0; j<variables.size(); ++j){
    TString variable = variables[j];

    TString varname = region+"_"+variable;

    printf("plotting  h_%s \n",varname.Data());
    TString outname = outpath+jettype+"_"+varname+extraname; 

    // get histograms from files
    h_DY50     = (TH1F*)file_DY50    ->Get("h_"+varname)->Clone("h_DY50"); 
    h_DY5to50  = (TH1F*)file_DY5to50 ->Get("h_"+varname)->Clone("h_DY5to50"); 
    h_STs      = (TH1F*)file_STs     ->Get("h_"+varname)->Clone("h_STs"); 
    h_STtbar   = (TH1F*)file_STtbar  ->Get("h_"+varname)->Clone("h_STtbar"); 
    h_STtbarW  = (TH1F*)file_STtbarW ->Get("h_"+varname)->Clone("h_STtbarW"); 
    h_STt      = (TH1F*)file_STt     ->Get("h_"+varname)->Clone("h_STt"); 
    h_STtW     = (TH1F*)file_STtW    ->Get("h_"+varname)->Clone("h_STtW"); 
    h_TTbar    = (TH1F*)file_TTbar   ->Get("h_"+varname)->Clone("h_TTbar"); 
    h_WJets    = (TH1F*)file_WJets   ->Get("h_"+varname)->Clone("h_WJets"); 
    h_WW       = (TH1F*)file_WW      ->Get("h_"+varname)->Clone("h_WW"); 
    h_WZ       = (TH1F*)file_WZ      ->Get("h_"+varname)->Clone("h_WZ"); 
    h_ZZ       = (TH1F*)file_ZZ      ->Get("h_"+varname)->Clone("h_ZZ"); 
    h_ZHtoLLbb   = (TH1F*)file_ZHtoLLbb   ->Get("h_"+varname)->Clone("h_ZHtoLLbb"); 
    h_ggZHtoLLbb = (TH1F*)file_ggZHtoLLbb ->Get("h_"+varname)->Clone("h_ggZHtoLLbb"); 
    h_SignalWm   = (TH1F*)file_SignalWm   ->Get("h_"+varname)->Clone("h_SignalWm"); 
    h_SignalWp   = (TH1F*)file_SignalWp   ->Get("h_"+varname)->Clone("h_SignalWp"); 
    h_SignalZH   = (TH1F*)file_SignalZH   ->Get("h_"+varname)->Clone("h_SignalZH"); 
    h_SignalggZH = (TH1F*)file_SignalggZH ->Get("h_"+varname)->Clone("h_SignalggZH"); 

    // integrals of histograms
    Double_t int_DY50       = h_DY50       ->Integral(-1,-1); 
    Double_t int_DY5to50    = h_DY5to50    ->Integral(-1,-1); 
    Double_t int_STs        = h_STs        ->Integral(-1,-1); 
    Double_t int_STtbar     = h_STtbar     ->Integral(-1,-1); 
    Double_t int_STtbarW    = h_STtbarW    ->Integral(-1,-1); 
    Double_t int_STt        = h_STt        ->Integral(-1,-1); 
    Double_t int_STtW       = h_STtW       ->Integral(-1,-1); 
    Double_t int_TTbar      = h_TTbar      ->Integral(-1,-1); 
    Double_t int_WJets      = h_WJets      ->Integral(-1,-1); 
    Double_t int_WW         = h_WW         ->Integral(-1,-1); 
    Double_t int_WZ         = h_WZ         ->Integral(-1,-1); 
    Double_t int_ZZ         = h_ZZ         ->Integral(-1,-1); 
    Double_t int_ZHtoLLbb   = h_ZHtoLLbb   ->Integral(-1,-1); 
    Double_t int_ggZHtoLLbb = h_ggZHtoLLbb ->Integral(-1,-1); 

    FILE * outtable;
 
    outtable = fopen (outname+".txt","w");
      fprintf (outtable, "           & %s \n", region.Data()); 
      fprintf (outtable, "DY50       & %3.1f\n", int_DY50       ); 
      fprintf (outtable, "DY5to50    & %3.1f\n", int_DY5to50    ); 
      fprintf (outtable, "STs        & %3.1f\n", int_STs        ); 
      fprintf (outtable, "STtbar     & %3.1f\n", int_STtbar     ); 
      fprintf (outtable, "STtbarW    & %3.1f\n", int_STtbarW    ); 
      fprintf (outtable, "STt        & %3.1f\n", int_STt        ); 
      fprintf (outtable, "STtW       & %3.1f\n", int_STtW       ); 
      fprintf (outtable, "TTbar      & %3.1f\n", int_TTbar      ); 
      fprintf (outtable, "WJets      & %3.1f\n", int_WJets      ); 
      fprintf (outtable, "WW         & %3.1f\n", int_WW         ); 
      fprintf (outtable, "WZ         & %3.1f\n", int_WZ         ); 
      fprintf (outtable, "ZZ         & %3.1f\n", int_ZZ         ); 
      fprintf (outtable, "ZHtoLLbb   & %3.1f\n", int_ZHtoLLbb   ); 
      fprintf (outtable, "ggZHtoLLbb & %3.1f\n", int_ggZHtoLLbb ); 
    fclose (outtable);

    // merge some histograms
    h_DY = (TH1F*)h_DY50->Clone("h_DY");
    h_DY->Add(h_DY5to50);

    h_ST = (TH1F*)h_STs->Clone("h_ST");
    h_ST->Add(h_STtbar);
    h_ST->Add(h_STtbarW);
    h_ST->Add(h_STt);
    h_ST->Add(h_STtW);

    h_VV = (TH1F*)h_WW->Clone("h_WW");
    h_VV->Add(h_WZ);
    h_VV->Add(h_ZZ);

    h_ZH = (TH1F*)h_ZHtoLLbb->Clone("h_ZH");
    h_ZH->Add(h_ggZHtoLLbb);

    // set attributes
    h_DY    -> SetFillColor(kRed); 
    h_ST    -> SetFillColor(kGreen+1); 
    h_TTbar -> SetFillColor(kGreen-9); 
    h_WJets -> SetFillColor(kAzure+10); 
    h_VV    -> SetFillColor(kOrange-3); 
    h_ZH    -> SetFillColor(kBlue); 

    h_DY    -> SetLineColor(kBlack); 
    h_ST    -> SetLineColor(kBlack); 
    h_TTbar -> SetLineColor(kBlack); 
    h_WJets -> SetLineColor(kBlack); 
    h_VV    -> SetLineColor(kBlack); 
    h_ZH    -> SetLineColor(kBlack); 

    h_SignalWm   ->SetFillStyle(3001); 
    h_SignalWp   ->SetFillStyle(3001); 
    h_SignalZH   ->SetFillStyle(3001); 
    h_SignalggZH ->SetFillStyle(3001); 
    h_SignalWm   ->SetLineColor(1); 
    h_SignalWp   ->SetLineColor(2); 
    h_SignalZH   ->SetLineColor(3); 
    h_SignalggZH ->SetLineColor(4); 
    h_SignalWm   ->SetLineWidth(2); 
    h_SignalWp   ->SetLineWidth(2); 
    h_SignalZH   ->SetLineWidth(2); 
    h_SignalggZH ->SetLineWidth(2); 

    // make stack
    THStack *bgstack = new THStack("bgstack","");
    bgstack->Add(h_DY    ); 
    bgstack->Add(h_VV    ); 
    bgstack->Add(h_ST    ); 
    bgstack->Add(h_TTbar ); 
    bgstack->Add(h_WJets ); 
    bgstack->Add(h_ZH    );

    // make signal lines
    h_totbkg = (TH1F*)h_DY->Clone("h_totbkg");
    h_totbkg->Add(h_VV    ); 
    h_totbkg->Add(h_ST    ); 
    h_totbkg->Add(h_TTbar ); 
    h_totbkg->Add(h_WJets ); 
    h_totbkg->Add(h_ZH    );
    Double_t intbkg = h_totbkg->Integral();
    if( h_SignalWm->Integral() > 0.1 ){
     h_SignalWm   ->Scale( intbkg / h_SignalWm->Integral() ); 
    }
    if( h_SignalWp->Integral() > 0.1 ){
     h_SignalWp   ->Scale( intbkg / h_SignalWp->Integral() ); 
    }
    if( h_SignalZH->Integral() > 0.1 ){
     h_SignalZH   ->Scale( intbkg / h_SignalZH->Integral() ); 
    }
    if( h_SignalggZH->Integral() > 0.1 ){
     h_SignalggZH   ->Scale( intbkg / h_SignalggZH->Integral() ); 
    }

    // make legend
    TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
    leg->SetBorderSize(0);
    leg->SetFillColor(kWhite);
    leg->AddEntry(h_DY      , "Drell-Yan", "f"); 
    leg->AddEntry(h_VV      , "Diboson", "f"); 
    leg->AddEntry(h_ST      , "Single Top", "f"); 
    leg->AddEntry(h_TTbar   , "TTbar", "f"); 
    leg->AddEntry(h_WJets   , "W+Jets", "f"); 
    leg->AddEntry(h_ZH      , "ZH#rightarrowLLbb", "f");
    if(drawSignal){
     leg->AddEntry(h_SignalWm, "Signal W-H","l");
     leg->AddEntry(h_SignalWp, "Signal W+H","l");
     leg->AddEntry(h_SignalZH, "Signal ZH","l");
     leg->AddEntry(h_SignalggZH, "Signal ggZH","l");
    }
    
    // and draw
    bgstack->Draw("hist");
    if(drawSignal){
     h_SignalWm->Draw("hist sames");
     h_SignalWp->Draw("hist sames");
     h_SignalZH->Draw("hist sames");
     h_SignalggZH->Draw("hist sames");
    }
    leg->Draw();

    // add titles
    title->DrawTextNDC(0.13,0.91,"CMS");
    extra->DrawTextNDC(0.23,0.91,"Preliminary");
    lumi->DrawTextNDC(0.9,0.91,"20 /fb (13 TeV)");
    bgstack->GetXaxis()->SetTitle(h_TTbar->GetTitle());
    bgstack->GetYaxis()->SetTitle("Events / bin");

    gPad->Update();
    gPad->RedrawAxis();

    // save canvas
    canvas->SaveAs(outname+".pdf");
    //canvas->SaveAs(outpath+jettype+"_"+varname+extraname+".pdf");
  
   }
  }
 }
}

