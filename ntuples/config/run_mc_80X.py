import FWCore.ParameterSet.Config as cms
#NTUPLIZER
process = cms.Process('LLDJ')#what we are looking at

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8')
process.load("Configuration.StandardSequences.MagneticField_cff")

#process.Tracer = cms.Service("Tracer")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )##Number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 1000##how often to report use higher report number if using all events

#jec from sqlite
process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
 connect = cms.string('sqlite:Summer16_23Sep2016V4_MC.db'),
 toGet = cms.VPSet(
 cms.PSet(
  record = cms.string('JetCorrectionsRecord'),
  tag = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016V4_MC_AK4PFchs'),
  label = cms.untracked.string('AK4PFchs')
 ),
 cms.PSet(
  record = cms.string('JetCorrectionsRecord'),
  tag = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016V4_MC_AK8PFchs'),
  label = cms.untracked.string('AK8PFchs')
  )))
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')
#input files
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        #'/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/00000/004A0552-3929-E611-BD44-0025905A48F0.root'
        #'/store/mc/RunIISummer16MiniAODv2/WWTo2L2Nu_13TeV-powheg/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/08E155A9-FAB6-E611-92BF-00259073E45E.root'

       #/ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM
        'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/08BA365D-40E5-E611-955F-00266CF89498.root'
         #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_54C6A127-05CA-E611-AAD2-0CC47A1DF1A4.root',
        # 'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_2CA15029-73CB-E611-8315-02163E019C53.root',
        # 'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_0AD7D4F9-17C8-E611-9F65-008CFA1974D8.root'
#'/store/mc/RunIISummer16MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/08BA365D-40E5-E611-955F-00266CF89498.root'
        ))

#process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

### EGM 80X regression
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

### EGM scale and smearing correction         
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
                                                  calibratedPatElectrons = cms.PSet(
    initialSeed = cms.untracked.uint32(12345),
    engineName = cms.untracked.string('TRandom3')
    ),
                                                  calibratedPatPhotons = cms.PSet(
    initialSeed = cms.untracked.uint32(12345),
    engineName = cms.untracked.string('TRandom3')
    ),
                                                   lldjNtuple  = cms.PSet(
    initialSeed = cms.untracked.uint32(67890),
    engineName = cms.untracked.string('TRandom3')
    )
                                                   )

process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')
process.calibratedPatElectrons.isMC = cms.bool(True)
process.calibratedPatPhotons.isMC = cms.bool(True)

process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

process.TFileService = cms.Service("TFileService", fileName = cms.string('lldjntuple_mc2.root'))#'ZH_HToSSTobbbb_ZToLL_MH-125_MS-40/lldjntuple_mc_MS40_cTauS1.root'))

jecLevels = [
  'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt',
  'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt'
]

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'UpdatedJEC',
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')
    )
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJetsAK8'),
    labelName = 'UpdatedJECAK8',
    jetCorrections = ('AK8PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
    btagDiscriminators = ['pfBoostedDoubleSecondaryVertexAK8BJetTags'],
    btagPrefix = 'newV4' # optional, in case interested in accessing both the old and new discriminator values
    )

# MET correction and uncertainties
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=False
                           )
#options
process.load("LLDJstandalones.ntuples.lldjNtuple_miniAOD_cfi")
#process.load("LLDJstandalones.ntuples.lldjPhotonIso_CITK_PUPPI_cff")
process.load("LLDJstandalones.ntuples.lldjMETFilters_cff")
process.lldjNtuple.dumpSoftDrop= cms.bool(True)
process.lldjNtuple.jecAK8PayloadNames=cms.vstring(jecLevels)
process.lldjNtuple.runHFElectrons=cms.bool(True)
process.lldjNtuple.isAOD=cms.bool(False)
process.lldjNtuple.doGenParticles=cms.bool(True)
process.lldjNtuple.dumpSubJets=cms.bool(True)
process.lldjNtuple.dumpJets=cms.bool(True)
process.lldjNtuple.dumpTaus=cms.bool(False)
process.lldjNtuple.patTriggerResults=cms.InputTag("TriggerResults", "", "PAT")

#####VID framework####################
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
switchOnVIDPhotonIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_HZZ_V1_cff']

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
    
my_phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff',
                    'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff']

process.load("RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi")
process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')
process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')

#add them to the VID producer
for idmod in my_phoid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)
#builds Ntuple
process.p = cms.Path(
    process.regressionApplication*
    process.lldjMETFiltersSequence*
    process.calibratedPatElectrons*
    process.calibratedPatPhotons* 
    process.egmGsfElectronIDSequence*
    process.egmPhotonIDSequence*
    process.lldjNtuple
    )

#print process.dumpPython()
