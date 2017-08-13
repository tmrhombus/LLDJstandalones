import FWCore.ParameterSet.Config as cms

process = cms.Process('LLDJ')

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load("Configuration.Geometry.GeometryIdeal_cff" )
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016SeptRepro_v7')

#process.Tracer = cms.Service("Tracer")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#jec from sqlite
process.load("CondCore.DBCommon.CondDBCommon_cfi")
from CondCore.DBCommon.CondDBSetup_cfi import *
process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
 connect = cms.string('sqlite:Summer16_23Sep2016AllV4_DATA.db'),
 toGet = cms.VPSet(
 cms.PSet(
  record = cms.string('JetCorrectionsRecord'),
  tag = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK4PFchs'),
  label = cms.untracked.string('AK4PFchs')
 ),
 cms.PSet(
  record = cms.string('JetCorrectionsRecord'),
  tag = cms.string('JetCorrectorParametersCollection_Summer16_23Sep2016AllV4_DATA_AK8PFchs'),
  label = cms.untracked.string('AK8PFchs')
  )))
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
        #'/store/data/Run2016E/DoubleMuon/MINIAOD/03Feb2017-v1/100000/062FB971-1AED-E611-965F-0CC47A4C8F12.root'

 #'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_26_patch2/src/LLDJstandalones/roots/ggZH_HToSSTodddd_MS40_ctauS100.root'

        #'/store/data/Run2016H/DoubleMuon/MINIAOD/PromptReco-v3/000/284/036/00000/04DC0281-C89F-E611-81C6-02163E0141E6.root'
        #'/store/data/Run2016B/SingleElectron/MINIAOD/23Sep2016-v2/80000/5A4402F5-638C-E611-A471-0025905A60AA.root'
#DoubleMuon   
        #'/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver3-v1/50000/36C4C2FB-4AEB-E611-ADD7-008CFA580778.root'  #H3
        #'/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver2-v1/110000/08ADA6AA-D3EC-E611-AF17-B083FED42488.root' #H2
        #'/store/data/Run2016G/DoubleMuon/MINIAOD/03Feb2017-v1/100000/00182C13-EEEA-E611-8897-001E675A6C2A.root'      #G
        #'/store/data/Run2016F/DoubleMuon/MINIAOD/03Feb2017-v1/100000/0055F5B5-76EB-E611-B313-002590D9D9FC.root'      #F
        #'/store/data/Run2016E/DoubleMuon/MINIAOD/03Feb2017-v1/100000/022FEC03-9AED-E611-9AE9-0025905A60B2.root'      #E
        #'/store/data/Run2016D/DoubleMuon/MINIAOD/03Feb2017-v1/100000/00E0F123-F7ED-E611-9F34-0CC47A7FC736.root'      #D
        #'/store/data/Run2016C/DoubleMuon/MINIAOD/03Feb2017-v1/110000/02292378-59ED-E611-BA0B-0CC47A4D768E.root'      #C1
        #'/store/data/Run2016C/DoubleMuon/MINIAOD/02Feb2017-v2/70000/00A7F0A8-C4E9-E611-A612-0CC47A7C357E.root'       #C2
        #'/store/data/Run2016B/DoubleMuon/MINIAOD/03Feb2017_ver2-v2/100000/0005AD9F-64ED-E611-A952-0CC47A78A42C.root' #B2
        #'/store/data/Run2016B/DoubleMuon/MINIAOD/03Feb2017_ver1-v1/110000/02B27BFE-1BEB-E611-8D50-001EC9B20ECB.root' #B1
#LowMassDoubleMuon
        #'/store/data/Run2016H/DoubleMuonLowMass/MINIAOD/03Feb2017_ver3-v1/110000/0A414F65-86EB-E611-8D91-0025905A60AA.root' #H3
        #'/store/data/Run2016H/DoubleMuonLowMass/MINIAOD/03Feb2017_ver2-v1/110000/026089AB-88ED-E611-B6C0-0025905B856C.root' #H2
        '/store/data/Run2016G/DoubleMuonLowMass/MINIAOD/03Feb2017-v1/50000/00048884-B2EA-E611-A6C0-0090FAA57430.root'       #G
        #'/store/data/Run2016F/DoubleMuonLowMass/MINIAOD/03Feb2017-v1/100000/00F4545C-C3EA-E611-AF0C-A0000420FE80.root'      #F
        #'/store/data/Run2016E/DoubleMuonLowMass/MINIAOD/03Feb2017-v1/110000/0AF5A623-8BEA-E611-99EB-0090FAA58224.root'      #E
        #'/store/data/Run2016D/DoubleMuonLowMass/MINIAOD/03Feb2017-v1/110000/0282D7E6-B5EC-E611-8C53-24BE05CE2EE1.root'      #D
        #'/store/data/Run2016C/DoubleMuonLowMass/MINIAOD/03Feb2017-v1/100000/04793E09-E0EA-E611-B918-0CC47A706D70.root'      #C
        #'/store/data/Run2016B/DoubleMuonLowMass/MINIAOD/03Feb2017_ver2-v2/110000/0051D2EC-8AEA-E611-8117-10983627C3C1.root' #B2
        #'/store/data/Run2016B/DoubleMuonLowMass/MINIAOD/03Feb2017_ver1-v1/80000/88703E9B-C8EA-E611-A3DC-001E67443EB7.root'  #B1
#DoubleMuLMB_1
        #'/store/data/Run2016B/DoubleMuonLowMass/MINIAOD/03Feb2017_ver1-v1/80000/88703E9B-C8EA-E611-A3DC-001E67443EB7.root',
        #'/store/data/Run2016B/DoubleMuonLowMass/MINIAOD/03Feb2017_ver1-v1/80000/F6B43BBE-EBEA-E611-8735-0CC47A537688.root'
#SingleMuon
	#'/store/data/Run2016G/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6DF50-70EA-E611-ACC4-0CC47A1E089C.root'
        

        )
                            )

#process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )
process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

### EGM 80X regression
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')

### EGM scale and smearing correction
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')

#from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )
#runOnData( process, outputModules = [] )
#removeMCMatching(process, names=['All'], outputModules=[])

# this loads all available b-taggers
#process.load("RecoBTag.Configuration.RecoBTag_cff")
#process.load("RecoBTag.SecondaryVertex.pfBoostedDoubleSecondaryVertexAK8BJetTags_cfi")
#process.pfImpactParameterTagInfosAK8.primaryVertex = cms.InputTag("offlineSlimmedPrimaryVertices")
#process.pfImpactParameterTagInfosAK8.candidates = cms.InputTag("packedPFCandidates")
#process.pfImpactParameterTagInfosAK8.jets = cms.InputTag("slimmedJetsAK8")
#process.load("RecoBTag.SecondaryVertex.pfInclusiveSecondaryVertexFinderTagInfosAK8_cfi")
#process.pfInclusiveSecondaryVertexFinderTagInfosAK8.extSVCollection = cms.InputTag("slimmedSecondaryVertices")

process.TFileService = cms.Service("TFileService", fileName = cms.string('trigger_roots/LMDbleMu_G.root'))

jecLevels = [
  'Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt',
  'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt',
  'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt'
]

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJets'),
    labelName = 'UpdatedJEC',
    jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'None')
    )
updateJetCollection(
    process,
    jetSource = cms.InputTag('slimmedJetsAK8'),
    labelName = 'UpdatedJECAK8',
    jetCorrections = ('AK8PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'None'),
    btagDiscriminators = ['pfBoostedDoubleSecondaryVertexAK8BJetTags'],
    btagPrefix = 'newV4' # optional, in case interested in accessing both the old and new discriminator values
    )

# MET correction and uncertainties
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=True                           
                           )

# Now you are creating the e/g corrected MET on top of the bad muon corrected MET (on re-miniaod)
from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG
corMETFromMuonAndEG(process,
                    pfCandCollection="", #not needed                        
                    electronCollection="slimmedElectronsBeforeGSFix",
                    photonCollection="slimmedPhotonsBeforeGSFix",
                    corElectronCollection="slimmedElectrons",
                    corPhotonCollection="slimmedPhotons",
                    allMETEGCorrected=True,
                    muCorrection=False,
                    eGCorrection=True,
                    runOnMiniAOD=True,
                    postfix="MuEGClean"
                    )
process.slimmedMETsMuEGClean = process.slimmedMETs.clone()
process.slimmedMETsMuEGClean.src = cms.InputTag("patPFMetT1MuEGClean")
process.slimmedMETsMuEGClean.rawVariation =  cms.InputTag("patPFMetRawMuEGClean")
process.slimmedMETsMuEGClean.t1Uncertainties = cms.InputTag("patPFMetT1%sMuEGClean")
del process.slimmedMETsMuEGClean.caloMET

process.egcorrMET = cms.Sequence(
        process.cleanedPhotonsMuEGClean+process.cleanedCorPhotonsMuEGClean+
        process.matchedPhotonsMuEGClean + process.matchedElectronsMuEGClean +
        process.corMETPhotonMuEGClean+process.corMETElectronMuEGClean+
        process.patPFMetT1MuEGClean+process.patPFMetRawMuEGClean+
        process.patPFMetT1SmearMuEGClean+process.patPFMetT1TxyMuEGClean+
        process.patPFMetTxyMuEGClean+process.patPFMetT1JetEnUpMuEGClean+
        process.patPFMetT1JetResUpMuEGClean+process.patPFMetT1SmearJetResUpMuEGClean+
        process.patPFMetT1ElectronEnUpMuEGClean+process.patPFMetT1PhotonEnUpMuEGClean+
        process.patPFMetT1MuonEnUpMuEGClean+process.patPFMetT1TauEnUpMuEGClean+
        process.patPFMetT1UnclusteredEnUpMuEGClean+process.patPFMetT1JetEnDownMuEGClean+
        process.patPFMetT1JetResDownMuEGClean+process.patPFMetT1SmearJetResDownMuEGClean+
        process.patPFMetT1ElectronEnDownMuEGClean+process.patPFMetT1PhotonEnDownMuEGClean+
        process.patPFMetT1MuonEnDownMuEGClean+process.patPFMetT1TauEnDownMuEGClean+
        process.patPFMetT1UnclusteredEnDownMuEGClean+process.slimmedMETsMuEGClean)



process.load("LLDJstandalones.ntuples.lldjNtuple_miniAOD_cfi")
process.load("LLDJstandalones.ntuples.lldjPhotonIso_CITK_PUPPI_cff")
process.load("LLDJstandalones.ntuples.lldjMETFilters_cff")
process.lldjNtuple.dumpSoftDrop= cms.bool(True)
process.lldjNtuple.jecAK8PayloadNames=cms.vstring(jecLevels)
process.lldjNtuple.runHFElectrons=cms.bool(True)
process.lldjNtuple.isAOD=cms.bool(False)
process.lldjNtuple.doGenParticles=cms.bool(False)
process.lldjNtuple.dumpSubJets=cms.bool(True)
process.lldjNtuple.dumpJets=cms.bool(True)
process.lldjNtuple.dumpTaus=cms.bool(False)
process.lldjNtuple.pfMETLabel=cms.InputTag("slimmedMETsMuEGClean", "", "LLDJ")
## the following line is only needed when you run on Feb 2017 re-miniAOD
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
    
    process.p = cms.Path(
        ###process.reapplyJEC*
        ###process.pfImpactParameterTagInfosAK8 *
        ###process.pfInclusiveSecondaryVertexFinderTagInfosAK8 *
        ###process.pfBoostedDoubleSecondaryVertexAK8BJetTags *        
        process.fullPatMetSequence* 
        process.egcorrMET*
        process.lldjMETFiltersSequence* 
        process.regressionApplication*
        process.calibratedPatElectrons*
        process.calibratedPatPhotons*
        process.egmGsfElectronIDSequence*
        process.egmPhotonIDSequence*
        process.lldjNtuple
        )
    
#print process.dumpPython()
