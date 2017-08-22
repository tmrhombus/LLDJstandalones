import FWCore.ParameterSet.Config as cms

##########################################################################################
# Setup

# this is the process run by cmsRun
process = cms.Process('LLDJ')
#process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

# log output
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )  ## number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 100  
#process.Tracer = cms.Service("Tracer")

# input files
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
 #'/store/mc/RunIISummer16MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/100000/00099D43-77ED-E611-8889-5065F381E1A1.root',

  #/ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM
   #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/08BA365D-40E5-E611-955F-00266CF89498.root'


  #'/store/mc/RunIISummer16MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/110000/08BA365D-40E5-E611-955F-00266CF89498.root'
  #'/store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/00000/004A0552-3929-E611-BD44-0025905A48F0.root'
  #'/store/mc/RunIISummer16MiniAODv2/WWTo2L2Nu_13TeV-powheg/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/08E155A9-FAB6-E611-92BF-00259073E45E.root'

   'file:/afs/hep.wisc.edu/cms/tperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_787B82F9-0ECB-E611-A5CD-1866DAEA7EA8.root',
   #'file:/afs/hep.wisc.edu/cms/tperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_EA59D0D0-5CCB-E611-B501-002590207C28.root',


#  # MS40-CT1,0p05
   #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0p05_52134309-19CF-E611-AD86-0CC47A4D7604.root',
#   'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_2CA15029-73CB-E611-8315-02163E019C53.root',
   #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/miniAOD/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_62211E56-2EC9-E611-95F3-02163E019C8F.root'

#  # MS40-CT100
  #'/store/mc/RunIISummer16MiniAODv2/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/54C6A127-05CA-E611-AAD2-0CC47A1DF1A4.root',
  #'/store/mc/RunIISummer16MiniAODv2/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/70576F21-CDC9-E611-BC72-001E675047A5.root',
  #'/store/mc/RunIISummer16MiniAODv2/ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/EA59D0D0-5CCB-E611-B501-002590207C28.root'
 )
)

# output name
process.TFileService = cms.Service("TFileService", fileName = cms.string('lldjntuple_mc.root'));

# cms geometry
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

# global tag
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'

##########################################################################################
# Jet Energy Corrections
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
# just take from global tag, no need to update collections

##########################################################################################
# Electron / Photon Corrections
# https://twiki.cern.ch/twiki/bin/view/CMS/EGMRegression

### EGM 80X regression
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

# Some proesses need random numbers, calculate using TRandom3 - Mersenne Twister
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
 calibratedPatElectrons  = cms.PSet( initialSeed = cms.untracked.uint32(8675389),
                                     engineName = cms.untracked.string('TRandom3'),
                                     ),
 calibratedPatPhotons    = cms.PSet( initialSeed = cms.untracked.uint32(8675389),
                                     engineName = cms.untracked.string('TRandom3'),
                                     ),
 lldjNtuple              = cms.PSet( initialSeed = cms.untracked.uint32(67890),
                                     engineName = cms.untracked.string('TRandom3')
                                     )
)
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')

# correct scale (data) or smear resolution (MC) 
process.calibratedPatElectrons.isMC = cms.bool(True)
process.calibratedPatPhotons.isMC = cms.bool(True)


##########################################################################################
# Electron / Photon Versioned ID

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
switchOnVIDPhotonIdProducer(process, dataFormat)

# define which IDs we want to produce
eleid_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
                 #'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_HZZ_V1_cff']
    
phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff',
                 'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff']

#add them to the VID producer
for idmod in eleid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

for idmod in phoid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

# hack recommended by https://twiki.cern.ch/twiki/bin/view/CMS/EGMRegression#VIDAnchor
process.selectedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("calibratedPatElectrons"),
    cut = cms.string("pt>5 && abs(superCluster.eta)<2.5")
)

process.selectedPhotons = cms.EDFilter("PATPhotonSelector",
    src = cms.InputTag("calibratedPatPhotons"),
    cut = cms.string("pt>5 && abs(superCluster.eta)<2.5")
)

# say which collections to run on 
process.load("RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi")
process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")
#process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
#process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
#process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')
#process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')


# 
process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('selectedElectrons')
process.egmPhotonIDs.physicsObjectSrc = cms.InputTag('selectedPhotons')

process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')
process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')
process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons')
process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons')

process.electronRegressionValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')
process.photonRegressionValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons')

process.egmPhotonIsolation.srcToIsolate = cms.InputTag('selectedPhotons')

##########################################################################################
# Now update MET
# 

from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=False
                           )


jecLevels = [
  'Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt',
  'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt'
]


#options
process.load("LLDJstandalones.ntuples.lldjNtuple_miniAOD_cfi")
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

#builds Ntuple
process.p = cms.Path(
    process.regressionApplication*  # e/gamma energy correction/resolution regression
    process.calibratedPatElectrons*
    process.calibratedPatPhotons*
    process.selectedElectrons*
    process.selectedPhotons*
    process.egmGsfElectronIDSequence*
    process.egmPhotonIDSequence*
    process.lldjMETFiltersSequence*
    process.lldjNtuple
    )

#print process.dumpPython()
#print process.egmGsfElectronIDSequence.dumpPython()

