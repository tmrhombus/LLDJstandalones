import FWCore.ParameterSet.Config as cms

##########################################################################################
# Setup

# this is the process run by cmsRun
process = cms.Process('LLDJ')
#process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

process.load("RecoTracker.TkNavigation.NavigationSchoolESProducer_cfi")

# log output
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )  ## number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 100
#process.Tracer = cms.Service('Tracer')

# input files
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring(
                # single mu
        #'/store/data/Run2016B/SingleMuon/MINIAOD/03Feb2017_ver1-v1/100000/08AD7B2D-34EE-E611-A7DA-001E674DA2E8.root',
        #'/store/data/Run2016B/SingleMuon/MINIAOD/03Feb2017_ver2-v2/100000/000C6E52-8BEC-E611-B3FF-0025905C42FE.root',
        #'/store/data/Run2016C/SingleMuon/MINIAOD/03Feb2017-v1/50000/001CF316-1AEB-E611-BBBD-0CC47A4C8EE2.root',
        #'/store/data/Run2016D/SingleMuon/MINIAOD/03Feb2017-v1/100000/00622F98-20EB-E611-A0A4-28924A33AFF6.root',
        #'/store/data/Run2016E/SingleMuon/MINIAOD/03Feb2017-v1/110000/001D567A-0CEB-E611-A438-D8D385AE8848.root',
        #'/store/data/Run2016F/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6AB6D-BCEC-E611-8F6E-0025905C3D98.root',
        #'/store/data/Run2016G/SingleMuon/MINIAOD/03Feb2017-v1/100000/00E6DF50-70EA-E611-ACC4-0CC47A1E089C.root',
        #'/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver2-v1/110000/00633FF0-85EA-E611-811C-001E674FB25C.root',
        #'/store/data/Run2016H/SingleMuon/MINIAOD/03Feb2017_ver3-v1/80000/0040ECBB-76EA-E611-8FE7-A0000420FE80.root',
        #
        #        # single ele
        '/store/data/Run2016B/SingleElectron/MINIAOD/03Feb2017_ver1-v1/100000/000E1D21-47ED-E611-85E0-0CC47A4D762A.root',
        #'/store/data/Run2016B/SingleElectron/MINIAOD/03Feb2017_ver2-v2/110000/003B2C1F-50EB-E611-A8F1-002590E2D9FE.root',
        #'/store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/02169BE7-81EB-E611-BB99-02163E0137CD.root',
        #'/store/data/Run2016D/SingleElectron/MINIAOD/03Feb2017-v1/110000/001A5DEC-77EB-E611-95CD-0CC47A4C8EE8.root',
        #'/store/data/Run2016E/SingleElectron/MINIAOD/03Feb2017-v1/110000/00022327-8BEA-E611-86CB-0025905B8566.root',
        #'/store/data/Run2016F/SingleElectron/MINIAOD/03Feb2017-v1/100000/00B336D6-6AEC-E611-8581-E0071B7AC7B0.root',
        #'/store/data/Run2016G/SingleElectron/MINIAOD/03Feb2017-v1/50000/004A75AB-B2EA-E611-B000-24BE05CEFDF1.root',
        #'/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver2-v1/100000/00553E5F-29EC-E611-ADB0-00259074AE8C.root',
        #'/store/data/Run2016H/SingleElectron/MINIAOD/03Feb2017_ver3-v1/110000/02973E99-69EC-E611-9913-5065F381A2F1.root',
        #'/store/data/Run2016G/SingleElectron/MINIAOD/03Feb2017-v1/50000/004A75AB-B2EA-E611-B000-24BE05CEFDF1.root'
        #
        #        # double mu
        #'/store/data/Run2016B/DoubleMuon/MINIAOD/03Feb2017_ver1-v1/110000/02B27BFE-1BEB-E611-8D50-001EC9B20ECB.root',
        #'/store/data/Run2016B/DoubleMuon/MINIAOD/03Feb2017_ver2-v2/100000/0005AD9F-64ED-E611-A952-0CC47A78A42C.root',
        #'/store/data/Run2016C/DoubleMuon/MINIAOD/03Feb2017-v1/110000/02292378-59ED-E611-BA0B-0CC47A4D768E.root',
        #'/store/data/Run2016C/DoubleMuon/MINIAOD/02Feb2017-v2/70000/00A7F0A8-C4E9-E611-A612-0CC47A7C357E.root',
        #'/store/data/Run2016D/DoubleMuon/MINIAOD/03Feb2017-v1/100000/00E0F123-F7ED-E611-9F34-0CC47A7FC736.root',
        #'/store/data/Run2016E/DoubleMuon/MINIAOD/03Feb2017-v1/100000/022FEC03-9AED-E611-9AE9-0025905A60B2.root',
        #'/store/data/Run2016F/DoubleMuon/MINIAOD/03Feb2017-v1/100000/0055F5B5-76EB-E611-B313-002590D9D9FC.root',
        #'/store/data/Run2016G/DoubleMuon/MINIAOD/03Feb2017-v1/100000/00182C13-EEEA-E611-8897-001E675A6C2A.root',
        #'/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver2-v1/110000/08ADA6AA-D3EC-E611-AF17-B083FED42488.root',
        #'/store/data/Run2016H/DoubleMuon/MINIAOD/03Feb2017_ver3-v1/50000/36C4C2FB-4AEB-E611-ADD7-008CFA580778.root',
        #
        #        # double ele
        #'/store/data/Run2016B/DoubleEG/MINIAOD/03Feb2017_ver1-v1/100000/02C07D99-20EB-E611-92B2-3417EBE700D2.root',
        #'/store/data/Run2016B/DoubleEG/MINIAOD/03Feb2017_ver2-v2/50000/00054938-CEEA-E611-889E-0CC47A4D7650.root',
        #'/store/data/Run2016C/DoubleEG/MINIAOD/03Feb2017-v1/80000/00371362-6AEC-E611-9845-842B2B758BAA.root',
        #'/store/data/Run2016D/DoubleEG/MINIAOD/03Feb2017-v1/100000/002CE21C-0BEB-E611-8597-001E67E6F8E6.root',
        #'/store/data/Run2016E/DoubleEG/MINIAOD/03Feb2017-v1/110000/003AF399-ABEA-E611-92CF-002590E2DA08.root',
        #'/store/data/Run2016F/DoubleEG/MINIAOD/03Feb2017-v1/80000/0006AFD8-F8EA-E611-9F9D-0CC47A13D09C.root',
        #'/store/data/Run2016G/DoubleEG/MINIAOD/03Feb2017-v1/100000/002F14FF-D0EA-E611-952E-008CFA197AF4.root',
        #'/store/data/Run2016H/DoubleEG/MINIAOD/03Feb2017_ver2-v1/100000/023E858B-F7EC-E611-889C-047D7BD6DDF2.root',
        #'/store/data/Run2016H/DoubleEG/MINIAOD/03Feb2017_ver3-v1/1030000/D41C6358-4DF0-E611-BBAC-002590DB927A.root',
 

 )
)

# output name
process.TFileService = cms.Service('TFileService', fileName = cms.string('lldjntuple_data_miniAOD.root'));

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

###########################################################################################
## Declare this is data (is this necessary?)
## 
process.load( 'PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff' )
process.load( 'PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff' )

from PhysicsTools.PatAlgos.tools.coreTools import *
runOnData( process,  names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )

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

# Some proesses need random numbers, calculate using TRandom3 - Mersenne Twister
process.RandomNumberGeneratorService = cms.Service('RandomNumberGeneratorService',
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
process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')

# correct scale (data) or smear resolution (MC) 
process.calibratedPatElectrons.isMC = cms.bool(False)
process.calibratedPatPhotons.isMC = cms.bool(False)


##########################################################################################
# Electron / Photon Versioned ID

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
switchOnVIDPhotonIdProducer(process, dataFormat)

# define which IDs we want to produce
eleid_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff']
                 #'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff',
                 #'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_HZZ_V1_cff']
    
phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']
                 #'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff']

#add them to the VID producer
for idmod in eleid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

for idmod in phoid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

# hack recommended by https://twiki.cern.ch/twiki/bin/view/CMS/EGMRegression#VIDAnchor
process.selectedElectrons = cms.EDFilter('PATElectronSelector',
    src = cms.InputTag('calibratedPatElectrons','','LLDJ'),
    cut = cms.string('pt>5 && abs(superCluster.eta)<2.5')
)

process.selectedPhotons = cms.EDFilter('PATPhotonSelector',
    src = cms.InputTag('calibratedPatPhotons','','LLDJ'),
    cut = cms.string('pt>5 && abs(superCluster.eta)<2.5')
)

# load electron/photon ID configurations
# we've modified this from the standard ID producer
# to manually specify AOD/miniAOD
process.load('RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi')
process.load('RecoEgamma.PhotonIdentification.PhotonIDValueMapProducer_cfi')

# Set up EGamma IDs
process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('selectedElectrons','','LLDJ')
process.egmPhotonIDs.physicsObjectSrc = cms.InputTag('selectedPhotons','','LLDJ')
process.egmGsfElectronIDs.isAOD=cms.bool(False)
process.egmPhotonIDs.isAOD=cms.bool(False)

# Electron ID 
process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons','','LLDJ')
process.electronIDValueMapProducer.src = cms.InputTag('') # make it give error if misconfigured
process.electronIDValueMapProducer.isAOD=cms.bool(False)

# Photon ID 
process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons','','LLDJ')
process.photonIDValueMapProducer.src = cms.InputTag('')
process.photonIDValueMapProducer.isAOD=cms.bool(False)

# we don't use MVA ID now, but maybe some time 
# process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons','','LLDJ')
# process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedPhotons','','LLDJ')
# process.electronMVAValueMapProducer.src = cms.InputTag('selectedElectrons','','LLDJ')
# process.photonMVAValueMapProducer.src = cms.InputTag('selectedPhotons','','LLDJ')

# Photon Isolation
process.egmPhotonIsolation.srcToIsolate = cms.InputTag('selectedPhotons','','LLDJ')

##########################################################################################
# Now update MET
# 

# MET correction and uncertainties
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
runMetCorAndUncFromMiniAOD(process,
                           isData=True
                           )

#######################  BadPFMuonFilter
process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag('slimmedMuons', '', 'PAT')
process.BadPFMuonFilter.PFCandidates = cms.InputTag('packedPFCandidates', '', 'PAT')

#######################  BadChargedCandidateFilter             
process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag('slimmedMuons', '', 'PAT')
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag('packedPFCandidates', '', 'PAT')

process.lldjMETFiltersSequence = cms.Sequence(
     process.BadPFMuonFilter *
     process.BadChargedCandidateFilter 
)


# creae e/g corrected MET on top of the bad muon corrected MET 
from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG
corMETFromMuonAndEG(process,
                    pfCandCollection='', #not needed                        
                    electronCollection='slimmedElectronsBeforeGSFix',
                    photonCollection='slimmedPhotonsBeforeGSFix',
                    corElectronCollection='selectedElectrons', 
                    corPhotonCollection='selectedPhotons',
                    allMETEGCorrected=True,
                    muCorrection=False,
                    eGCorrection=True,
                    runOnMiniAOD=True,
                    postfix='MuEGClean'
                    )

process.slimmedMETsMuEGClean = process.slimmedMETs.clone()
process.slimmedMETsMuEGClean.src = cms.InputTag('patPFMetT1MuEGClean')
process.slimmedMETsMuEGClean.rawVariation =  cms.InputTag('patPFMetRawMuEGClean')
process.slimmedMETsMuEGClean.t1Uncertainties = cms.InputTag('patPFMetT1%sMuEGClean')
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

##########################################################################################
# HLT Triggers
# 

process.singleEleHLTFilter = cms.EDFilter('HLTHighLevel',
                                          eventSetupPathsKey = cms.string(''),
                                          TriggerResultsTag = cms.InputTag('TriggerResults','','HLT'),
                                          HLTPaths = cms.vstring(
                                          #'HLT_Ele27_WPLoose_Gsf_v*',
                                          #'HLT_Ele27_WPTight_Gsf_v*', 
                                          #'HLT_Ele27_eta2p1_WPLoose_Gsf_v*', 
                                          #'HLT_Ele27_eta2p1_WPTight_Gsf_v*',
                                          #'HLT_Ele32_eta2p1_WPTight_Gsf_v*', 
                                          #'HLT_Ele35_WPLoose_Gsf_v*', 
                                          #'HLT_Ele45_WPLoose_Gsf_v*'

                                          'HLT_PFHT350_PFMET100_v1',
                                          'HLT_PFHT350_PFMET100_JetIdCleaned_v1',
                                          'HLT_PFHT350_PFMET100_JetIdCleaned_v2',

                                          'HLT_Ele23_WPLoose_Gsf_v1',
                                          'HLT_Ele23_WPLoose_Gsf_v2',
                                          'HLT_Ele23_WPLoose_Gsf_v3',
                                          'HLT_Ele23_WPLoose_Gsf_v4',
                                          'HLT_Ele23_WPLoose_Gsf_v5',
                                          'HLT_Ele23_WPLoose_Gsf_v6',
                                          'HLT_Ele23_WPLoose_Gsf_v7',
                                          'HLT_Ele23_WPLoose_Gsf_v8',
                                          'HLT_Ele23_WPLoose_Gsf_v9',
                                          'HLT_Ele23_WPLoose_Gsf_v10',
                                          'HLT_Ele23_WPLoose_Gsf_v11',
                                          'HLT_Ele23_WPLoose_Gsf_v12',
                                          'HLT_Ele27_WPTight_Gsf_v1',
                                          'HLT_Ele27_WPTight_Gsf_v2',
                                          'HLT_Ele27_WPTight_Gsf_v3',
                                          'HLT_Ele27_WPTight_Gsf_v4',
                                          'HLT_Ele27_WPTight_Gsf_v5',
                                          'HLT_Ele27_WPTight_Gsf_v6',
                                          'HLT_Ele27_WPTight_Gsf_v7',
                                          'HLT_Ele27_WPTight_Gsf_v8',
                                          'HLT_Ele27_WPTight_Gsf_v9',

                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9',
                                          'HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9',
                                          'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10',

                                          'HLT_IsoMu22_v1',
                                          'HLT_IsoMu22_v2',
                                          'HLT_IsoMu22_v3',
                                          'HLT_IsoMu22_v4',
                                          'HLT_IsoMu22_v5',
                                          'HLT_IsoMu22_v6',
                                          'HLT_IsoMu22_v7',
                                          'HLT_IsoTkMu22_v1',
                                          'HLT_IsoTkMu22_v2',
                                          'HLT_IsoTkMu22_v3',
                                          'HLT_IsoTkMu22_v4',
                                          'HLT_IsoTkMu22_v5',
                                          'HLT_IsoTkMu22_v6',
                                          'HLT_IsoTkMu22_v7',
                                          'HLT_IsoTkMu22_v8',
                                          'HLT_IsoTkMu22_v9',
                                          'HLT_IsoTkMu22_v10',

                                          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1',
                                          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2',
                                          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3',
                                          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4',
                                          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v5',
                                          'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v6',
                                          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2',
                                          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1',
                                          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3',
                                          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4',
                                          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v5',
                                          'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6',

                                          ),
                                          andOr = cms.bool(True), # True = OR, False = AND
                                          throw = cms.bool(False) # Tolerate if triggers not available
                                          )


# For AOD
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

 doAOD                     = cms.bool(False),
 doMiniAOD                 = cms.bool(True),

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
 pfMETLabel                = cms.InputTag('slimmedMETsMuEGClean', '', 'LLDJ'),

 muonSrc                   = cms.InputTag('slimmedMuons'),
 muonAODSrc                = cms.InputTag('selectedPatMuons'),

 photonSrc                 = cms.InputTag('selectedPhotons','','LLDJ'),
 phoLooseIdMap             = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-loose"),
 phoMediumIdMap            = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium"),
 phoTightIdMap             = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-tight"),
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
    process.singleEleHLTFilter*
    process.regressionApplication*  # e/gamma energy correction/resolution regression
    process.calibratedPatElectrons*
    process.calibratedPatPhotons*
    process.selectedElectrons*
    process.selectedPhotons*
    process.egmGsfElectronIDSequence*
    process.egmPhotonIDSequence*
    process.fullPatMetSequence* 
    process.egcorrMET*
    process.lldjMETFiltersSequence*
    process.lldjNtuple
    )

#process.ep = cms.EndPath(process.out)
#print process.dumpPython()
#print process.egmGsfElectronIDSequence.dumpPython()

