import FWCore.ParameterSet.Config as cms

##########################################################################################
# Setup

# this is the process run by cmsRun
process = cms.Process('LLDJ')
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(4)
process.options.numberOfStreams=cms.untracked.uint32(0)

process.load("RecoTracker.TkNavigation.NavigationSchoolESProducer_cfi")

# log output
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(500) )  ## number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 100
#process.MessageLogger.cerr.FwkReport.reportEvery = 1
#process.Tracer = cms.Service('Tracer')

# input files
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring(
          #'file:MuEG.root'
        #'root://cms-xrd-global.cern.ch//store/data/Run2016G/SingleElectron/AOD/23Sep2016-v1/100000/62B0D6B4-D58A-E611-9F51-002590AC4B5C.root'
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/021C4224-7392-E711-8E7C-001F2908AEB6.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/0268C748-CD92-E711-8E1D-44A842CFCA0D.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/027D2611-AF92-E711-8905-0026B93F4B80.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/02956774-A792-E711-8D76-009C02AAB554.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/02A88193-3D92-E711-9082-3417EBE649DE.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/02C435C8-D392-E711-AEF6-3417EBE47EBC.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/043F1A1A-3092-E711-96D0-7845C4FC3998.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/04BC73E9-7F92-E711-ABAD-008CFAF72A28.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/04BF5EE7-7F92-E711-AD7D-0023AEEEB559.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/04D1A3B6-6C93-E711-A697-001E67A40514.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/04FDE4AA-0792-E711-9AFF-008CFAF71666.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/0643AA94-3D92-E711-96CB-7CD30AD0A7AA.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/06A01252-A192-E711-9ED7-008CFAF7485E.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/06D6F585-AE92-E711-87D5-001EC9ED948B.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/08202392-3D92-E711-B42F-3417EBE34B01.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/08972F55-7492-E711-B6F9-1CB72C1B6574.root',
        'root://cms-xrd-global.cern.ch///store/data/Run2016H/DoubleEG/AOD/07Aug17-v1/10000/08C6FAF6-B492-E711-8B3E-24BE05C6C7F1.root'
 ),
)

# output name
process.TFileService = cms.Service('TFileService', fileName = cms.string('lldjntuple_data_AOD.root'));

#process.out = cms.OutputModule(
#'PoolOutputModule',
#     fileName = cms.untracked.string('output6.root'),
#     outputCommands = cms.untracked.vstring( 
#      'keep *', )  
#)

# cms geometry
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

# global tag
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v7'
# Legacy Data Global Tag 
#process.GlobalTag.globaltag = '80X_dataRun2_2016LegacyRepro_v4'

# for AOD Photons
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.AOD
switchOnVIDPhotonIdProducer(process, dataFormat)
my_id_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection) 

# for AOD Electrons
switchOnVIDElectronIdProducer(process, dataFormat)
#my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff']
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff']
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


# pat for trigger
process.load( 'PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff' )

# pat for muons
process.load('PhysicsTools.PatAlgos.patSequences_cff')

from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process, names=['All'], outputModules = [])

# For AOD Track variables
process.MaterialPropagator = cms.ESProducer('PropagatorWithMaterialESProducer',
    ComponentName = cms.string('PropagatorWithMaterial'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)

process.TransientTrackBuilderESProducer = cms.ESProducer('TransientTrackBuilderESProducer',
    ComponentName = cms.string('TransientTrackBuilder')
)

#NTuplizer
process.lldjNtuple = cms.EDAnalyzer('lldjNtuple',

 doAOD                     = cms.bool(True),
 doMiniAOD                 = cms.bool(False),

 electronSrc               = cms.InputTag('selectedElectrons','','LLDJ'),
 rhoLabel                  = cms.InputTag('fixedGridRhoFastjetAll'),
 eleVetoIdMap              = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto'),
 eleLooseIdMap             = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose'),
 eleMediumIdMap            = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium'),
 eleTightIdMap             = cms.InputTag('egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight'),
 eleHLTIdMap               = cms.InputTag('egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1'),
 #eleMVAValuesMap           = cms.InputTag('electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values'),
 #eleMVAHZZValuesMap        = cms.InputTag('electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16HZZV1Values'),
 #elePFClusEcalIsoProducer  = cms.InputTag('electronEcalPFClusterIsolationProducer'),
 #elePFClusHcalIsoProducer  = cms.InputTag('electronHcalPFClusterIsolationProducer'),

 rhoCentralLabel           = cms.InputTag('fixedGridRhoFastjetCentralNeutral'),
 pileupCollection          = cms.InputTag('slimmedAddPileupInfo'),
 AODpileupCollection       = cms.InputTag('addPileupInfo', '', 'HLT'),
 VtxLabel                  = cms.InputTag('offlineSlimmedPrimaryVertices'),
 triggerResults            = cms.InputTag('TriggerResults', '', 'HLT'),

 AODTriggerInputTag           = cms.InputTag("TriggerResults","","HLT"),
 AODTriggerEventInputTag      = cms.InputTag("hltTriggerSummaryAOD","","HLT"),

 beamspotLabel_            = cms.InputTag('offlineBeamSpot'),

 ak4JetSrc                 = cms.InputTag('slimmedJets'),
 AODak4CaloJetsSrc         = cms.InputTag('ak4CaloJets' , '', 'RECO'),
 AODak4PFJetsSrc           = cms.InputTag('ak4PFJets'   , '', 'RECO'),
 AODak4PFJetsCHSSrc        = cms.InputTag('ak4PFJetsCHS', '', 'RECO'),
 selectedPatJetsSrc        = cms.InputTag('selectedPatJets'),                                   
 AODVertexSrc              = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
 AODTrackSrc               = cms.InputTag('generalTracks', '', 'RECO'),
 vertexFitterConfig = cms.PSet(
        finder = cms.string('avf'),
        sigmacut = cms.double(10.),
        Tini = cms.double(256.),
        ratio = cms.double(0.25),
        ),

 patTriggerResults         = cms.InputTag('TriggerResults', '', 'PAT'),
 BadChargedCandidateFilter = cms.InputTag('BadChargedCandidateFilter'),
 BadPFMuonFilter           = cms.InputTag('BadPFMuonFilter'),
 pfMETLabel                = cms.InputTag('slimmedMETsMuEGClean', '', 'LLDJ'),
 AODCaloMETlabel           = cms.InputTag('caloMet','','RECO'),    
 AODpfChMETlabel           = cms.InputTag('pfChMet','','RECO'),    
 AODpfMETlabel             = cms.InputTag('pfMet','','RECO'),  

 muonSrc                   = cms.InputTag('slimmedMuons'),
 muonAODSrc                = cms.InputTag('selectedPatMuons'),

 photonSrc                 = cms.InputTag('selectedPhotons','','LLDJ'),
 phoLooseIdMap             = cms.InputTag('egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-loose'),
 phoMediumIdMap            = cms.InputTag('egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-medium'),
 phoTightIdMap             = cms.InputTag('egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-tight'),
 phoChargedIsolation       = cms.InputTag('photonIDValueMapProducer:phoChargedIsolation'),
 phoNeutralHadronIsolation = cms.InputTag('photonIDValueMapProducer:phoNeutralHadronIsolation'),
 phoPhotonIsolation        = cms.InputTag('photonIDValueMapProducer:phoPhotonIsolation'),
 phoWorstChargedIsolation  = cms.InputTag('photonIDValueMapProducer:phoWorstChargedIsolation'),
 #photonAODSrc              = cms.InputTag('selectedPatPhotons'),
 photonAODSrc              = cms.InputTag('gedPhotons'),

 AOD_phoLooseIdMap  = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-loose"),
 AOD_phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium"),
 AOD_phoTightIdMap  = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-tight"),
 AOD_phoChargedIsolationMap       = cms.InputTag("photonIDValueMapProducer", "phoChargedIsolation"),
 AOD_phoNeutralHadronIsolationMap = cms.InputTag("photonIDValueMapProducer", "phoNeutralHadronIsolation"),
 AOD_phoPhotonIsolationMap        = cms.InputTag("photonIDValueMapProducer", "phoPhotonIsolation"),
 AOD_phoWorstChargedIsolationMap  = cms.InputTag("photonIDValueMapProducer", "phoWorstChargedIsolation"),

 electronAODSrc = cms.InputTag("gedGsfElectrons"),
 #AOD_eleIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1"),#doesn't work with AOD
 AOD_eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
 AOD_eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium"),
 AOD_eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight"),
 conversions  = cms.InputTag('allConversions'),

 genParticleSrc    = cms.InputTag("genParticles"),

 bits = cms.InputTag("TriggerResults","","HLT"),
 prescales = cms.InputTag("patTrigger"),
 objects = cms.InputTag("selectedPatTrigger"),

)


#builds Ntuple
process.p = cms.Path(
    process.egmPhotonIDSequence *
    process.lldjNtuple
    )

#process.ep = cms.EndPath(process.out)
#print process.dumpPython()
#print process.egmGsfElectronIDSequence.dumpPython()

