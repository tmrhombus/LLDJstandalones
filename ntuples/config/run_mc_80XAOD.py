import FWCore.ParameterSet.Config as cms

##########################################################################################
# Setup

# this is the process run by cmsRun
process = cms.Process('LLDJ')
#process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load("RecoTracker.TkNavigation.NavigationSchoolESProducer_cfi")

# log output
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )  ## number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 1

# input files
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring(
'file:D420E413-FDC8-E611-869C-00259021A342.root' 
 #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/AOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_D6822833-FEC8-E611-8CD1-002590E7D7DE.root'
#'/store/mc/RunIISummer16DR80Premix/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/4A859964-FEC8-E611-B0B8-20CF3027A561.root',
#'/store/mc/RunIISummer16DR80Premix/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/D420E413-FDC8-E611-869C-00259021A342.root',
#'/store/mc/RunIISummer16DR80Premix/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/AODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/D6822833-FEC8-E611-8CD1-002590E7D7DE.root'

 ),
)

# output name
process.TFileService = cms.Service('TFileService', fileName = cms.string('lldjntuple_mc_AOD.root'));

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
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'

# pat for muons
process.load('PhysicsTools.PatAlgos.patSequences_cff')



##########################################################################################
# For AOD Track variables
# 
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
 VtxLabel                  = cms.InputTag('offlineSlimmedPrimaryVertices'),
 triggerResults            = cms.InputTag('TriggerResults', '', 'HLT'),

 beamspotLabel_            = cms.InputTag('offlineBeamSpot'),

 ak4JetSrc                 = cms.InputTag('slimmedJets'),
 AODak4CaloJetsSrc         = cms.InputTag('ak4CaloJets' , '', 'RECO'),
 AODak4PFJetsSrc           = cms.InputTag('ak4PFJets'   , '', 'RECO'),
 AODak4PFJetsCHSSrc        = cms.InputTag('ak4PFJetsCHS', '', 'RECO'),
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
 pfMETLabel                = cms.InputTag('slimmedMETs'),

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

 genParticleSrc    = cms.InputTag("genParticles"),

 bits = cms.InputTag("TriggerResults","","HLT"),
 prescales = cms.InputTag("patTrigger"),
 objects = cms.InputTag("selectedPatTrigger"),

)

#builds Ntuple
process.p = cms.Path(
    process.particleFlowPtrs *
    process.patCandidates *
    process.selectedPatCandidates *
    process.lldjNtuple
    )

#process.ep = cms.EndPath(process.out)
#print process.dumpPython()
#print process.egmGsfElectronIDSequence.dumpPython()

