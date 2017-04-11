#!\bin\python
import FWCore.ParameterSet.Config as cms

# define the process 
process = cms.Process("ANALYSIS")

# no summary
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))

# global tag imports run specific calibrations
# ## process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8')
process.load("Configuration.StandardSequences.MagneticField_cff")

# load messanger service
process.load("FWCore.MessageService.MessageLogger_cfi")

# how many events to run over
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# input source for process
process.source = cms.Source("PoolSource",
 fileNames = cms.untracked.vstring(
  'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_18_patch1/src/LLDJstandalones/roots/TT_miniAOD_0AB045B5-BB0C-E511-81FD-0025905A60B8.root'
 ),
 inputCommands=cms.untracked.vstring(
  'keep *',
  'keep *_l1extraParticles_*_*',
 )
)

# this is where we define the collections and selections 
# from UWAnalysis.Configuration.tools.analysisToolsPT import *
# defaultReconstructionPT(process,
#  'HLT',
#  ['HLT_IsoMu24_eta2p1_v','HLT_Ele27_WP80'],
#  itsMC=True,itsData=False,lhep_="source")
# 
# createGeneratedParticles(process,
#  'genWs',
#  ["keep++ pdgId = {W+}","keep++ pdgId = {W-}"]
# )

# define selections for objects / events
process.load("UWAnalysis.Configuration.countSmearEvents_cff")
process.eventSelection = cms.Path(process.selectionSequence)


# createSystematics in analysisToolsPT
# define selections / systematics and add to process
process.selectionSequenceMuonUp        = createSystematics(process,process.selectionSequence,'MuonUp'      ,1.01, 1.0, 1.0, 0, 1.0)
process.selectionSequenceMuonDown      = createSystematics(process,process.selectionSequence,'MuonDown'    ,0.99, 1.0, 1.0, 0, 1.0)
process.selectionSequenceElectronUp    = createSystematics(process,process.selectionSequence,'ElectronUp'  ,1.0, 1.01, 1.0, 0, 1.0)
process.selectionSequenceElectronDown  = createSystematics(process,process.selectionSequence,'ElectronDown',1.0, 0.99, 1.0, 0, 1.0)
process.selectionSequenceJetUp         = createSystematics(process,process.selectionSequence,'JetUp'       ,1.00, 1.0, 1.0, 1, 1.0)
process.selectionSequenceJetDown       = createSystematics(process,process.selectionSequence,'JetDown'     ,1.00, 1.0, 1.0,-1, 1.0)

process.eventSelectionMuonUp        =  cms.Path(process.selectionSequenceMuonUp)
process.eventSelectionMuonDown      =  cms.Path(process.selectionSequenceMuonDown)
process.eventSelectionElectronUp    =  cms.Path(process.selectionSequenceElectronUp)
process.eventSelectionElectronDown  =  cms.Path(process.selectionSequenceElectronDown)
process.eventSelectionJetUp         =  cms.Path(process.selectionSequenceJetUp)
process.eventSelectionJetDown       =  cms.Path(process.selectionSequenceJetDown)

# add trees to the process to be written to
from UWAnalysis.Configuration.tools.ntupleToolsPTwbbClean import *
# calls producers

addEventTreeMC(process,'muEleEventTree',
      srcGMu='smearedGoodMuons',
      srcVMu='smearedVetoMuons',
      srcQMu='smearedQCDMuons',
      srcAMu='smearedAllMuons',
      srcGEle='smearedGoodElectrons',
      srcVEle='smearedVetoElectrons',
      srcQEle='smearedQCDElectrons',
      srcAEle='smearedAllElectrons',
      srcGJet='smearedGoodJets',
      srcFJet='smearedFwdJets',
      srcAJet='smearedAllJets',
      srcCJet='smearedCleanJets',
      lhep="source",
      srcGenParticles="genParticles",
      srcGenLep="dressedLeptons",
      srcTaggedGenJets="btaggedGenJets"
      )


# count events run over
addEventSummary(process,True)

## etc etc for different systematics - put them in their own copy tree
#addEventTreeMC(process,'muEleEventTreeElectronDown',
#      srcGMu='smearedGoodMuonsElectronDown',
#      srcVMu='smearedVetoMuonsElectronDown',
#      srcQMu='smearedQCDMuonsElectronDown',
#      srcAMu='smearedAllMuonsElectronDown',
#      srcGEle='smearedGoodElectronsElectronDown',
#      srcVEle='smearedVetoElectronsElectronDown',
#      srcQEle='smearedQCDElectronsElectronDown',
#      srcAEle='smearedAllElectronsElectronDown',
#      srcGJet='smearedGoodJetsElectronDown',
#      srcFJet='smearedFwdJetsElectronDown',
#      srcAJet='smearedAllJetsElectronDown',
#      srcCJet='smearedCleanJetsElectronDown',
#      lhep="source",
#      srcGenParticles="genParticles",
#      srcGenLep="dressedLeptons",
#      srcTaggedGenJets="btaggedGenJets"
#      )

# output file name
process.TFileService.fileName = cms.string('Bastille_Wbb4F_g.root') 

## makes EDM output of all collections
#process.out = cms.OutputModule("PoolOutputModule",
# fileName = cms.untracked.string('/scratch/tperry/analysis.root'),
# outputCommands = cms.untracked.vstring(
#                       'keep *'),
# )
#process.e = cms.EndPath(process.out)
#
#Pax = open("myConfig.py","w")
#Pax.write(process.dumpPython())

process.demo = cms.EDAnalyzer('ntuples'
     , tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)

# write the output to a file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo.root')
)


# run the process !
process.p = cms.Path(process.demo)
