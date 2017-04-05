import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(False))


process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
 fileNames = cms.untracked.vstring(
  'file:/uscms_data/d3/tmperry/LLDJ_slc6_530_CMSSW_8_0_18_patch1/src/LLDJstandalones/roots/TT_miniAOD_0AB045B5-BB0C-E511-81FD-0025905A60B8.root'
 ),
 inputCommands=cms.untracked.vstring(
  'keep *',
  'keep *_l1extraParticles_*_*',
 )
)

process.demo = cms.EDAnalyzer('ntuples'
     , tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo.root')
)

process.p = cms.Path(process.demo)
