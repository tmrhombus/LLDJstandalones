import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

analysisConfigurator = CutSequenceProducer(initialCounter = 'initialEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace = locals())

analysisConfigurator.addSmearedAll('allMuons','goodMuons','vetoMuons','qcdMuons','allElectrons','goodElectrons','vetoElectrons','qcdElectrons','allJets','cleanJets','goodJets','fwdJets',mpost='')

selectionSequence = analysisConfigurator.returnSequence()
