HEEP checkout

cmsrel CMSSW_8_0_25
cd CMSSW_8_0_25/src
cmsenv 
git cms-merge-topic Sam-Harper:HEEPV70VID_8010_ReducedCheckout  #brings in HEEP V70 into VID
git cms-merge-topic ikrav:egm_id_80X_v3 #for other E/gamma IDs in VID if you wish to have them
git cms-merge-topic Sam-Harper:PackedCandNoPuppi #only necessary to run HEEP V70 on AOD (it will crash if this is not present looking for puppi candidates
mkdir -p ../external/slc6_amd64_gcc530/data/RecoEgamma/ElectronIdentification/ #we need this for the mva weights which runs in VID regardless if you need it or not
git clone git@github.com:cms-data/RecoEgamma-ElectronIdentification ../external/slc6_amd64_gcc530/data/RecoEgamma/ElectronIdentification/data #we need this for the mva weights which runs in VID regardless if you need it or not
scramv1 b -j 16 #more cores the better


from PhysicsTools.SelectorUtils.tools.vid_id_tools import switchOnVIDElectronIdProducer
from PhysicsTools.SelectorUtils.tools.vid_id_tools import setupVIDElectronSelection
from PhysicsTools.SelectorUtils.tools.vid_id_tools import setupAllVIDIdsInModule
from PhysicsTools.SelectorUtils.tools.vid_id_tools import DataFormat
    
# turn on VID producer, indicate data format  to be
# DataFormat.AOD or DataFormat.MiniAOD, as appropriate
dataFormat = DataFormat.MiniAOD if useMiniAOD else DataFormat.AOD
switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff']

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

This produces the sequence

process.egmGsfElectronIDSequence

which is common to all E/gamma IDs which run VID and must be added to cms.Path before the module in which you wish to access the HEEPV70 ID results. 



access as  https://github.com/Sam-Harper/HEEP/blob/HEEPV70/VID/plugins/HEEPV70Example.cc
 edm::EDGetTokenT<edm::ValueMap<bool> > vidPassToken_;
vidPassToken_=consumes<edm::ValueMap<bool> >(iPara.getParameter<edm::InputTag>("vid"));
 edm::Handle<edm::ValueMap<bool> > vidPass;
 iEvent.getByToken(vidPassToken_,vidPass);

  for(size_t eleNr=0;eleNr<eleHandle->size();eleNr++){  
    edm::Ptr<reco::GsfElectron> elePtr(eleHandle,eleNr); //note we use an edm::Ptr rather than an edm::Ref
                                                         //as we do not know if its a pat::Electron 
                                                         //or a reco::GsfElectron
   
    //this allows to tell if the electron passed HEEPV70, true = passed
bool passHEEPV70=(*vidPass)[elePtr]; 
}

------------------------------


    egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto
    egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose
    egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium
    egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight
    egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1
    egmGsfElectronIDs:heepElectronID-HEEPV70


# define which IDs we want to produce
my_id_modules = [
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff'
    ]

#add them to the VID producer
for idmod in my_id_modules:
setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


process.p = cms.Path(process.egmGsfElectronIDSequence * process.ntupler)






https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2

 EGamma POG approved scale factors are provided as a TH2F histogram and can be in links below. The 2 dimensions are:

    x-axis: SuperCluster Eta
    y-axis: pT 

The value can be access with usual GetBinContent and the recommended systematic is the error (GetBinError). The pT range is limited to 150GeV. For pT > 150 GeV the highest pT bin scale factor should to be used. 
