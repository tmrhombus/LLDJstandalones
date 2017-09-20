import FWCore.ParameterSet.Config as cms

electronIDValueMapProducer = cms.EDProducer('ElectronIDValueMapProducer',
                                          # The module automatically detects AOD vs miniAOD, so we configure both
                                          # this messes with using parent so I prefer explicit AOD/miniAOD
                                          isAOD            = cms.bool(False),
                                          #
                                          # AOD case
                                          #
                                          ebReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
                                          eeReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
                                          esReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsES"),
                                          src = cms.InputTag('gedGsfElectrons'),
                                          #
                                          # miniAOD case
                                          #
                                          ebReducedRecHitCollectionMiniAOD = cms.InputTag("reducedEgamma:reducedEBRecHits"),
                                          eeReducedRecHitCollectionMiniAOD = cms.InputTag("reducedEgamma:reducedEERecHits"),
                                          esReducedRecHitCollectionMiniAOD = cms.InputTag("reducedEgamma:reducedESRecHits"),
                                          srcMiniAOD = cms.InputTag('slimmedElectrons',processName=cms.InputTag.skipCurrentProcess()),
)
