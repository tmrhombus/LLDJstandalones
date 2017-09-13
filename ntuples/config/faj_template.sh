#!/bin/bash

# submit using farmout 

farmoutAnalysisJobs $1 --input-dbs-path=DATASET \
 --use-osg \
 --input-files-per-job=UPERJOB \
 --extra-inputs=INPUTFILES \
 REQUESTNAME \
 $CMSSW_BASE \
 CMSRUNCONFIG


#farmoutAnalysisJobs $1 --input-files-per-job=1 --use-osg \
#  --input-dir=root://cmsxrootd.hep.wisc.edu//store/user/tuanqui/WJetsToLNu_scaledown_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/Fall2015PATTuples_v1 \
#${version}_WnJsclDown $CMSSW_BASE $CMSSW_BASE/src/UWAnalysis/Wbb8TeV/farmoutAJ_ntuples/MuEle-PATMCs.py
#
#
#
#
#if __name__ == '__main__':
#
## Usage : python crabConfig.py (to create jobs)
##         ./multicrab -c status -d WORKAREA (to check job status)
#
#    from CRABAPI.RawCommand import crabCommand
#    from httplib import HTTPException
#
#    from CRABClient.UserUtilities import config
#    config = config()
#    
#    from multiprocessing import Process
#
#    # Common configuration
#
#    config.General.workArea           = WORKAREA
#    config.General.transferLogs       = False
#    config.JobType.pluginName         = 'Analysis' # PrivateMC
#    config.JobType.psetName           = CMSRUNCONFIG
#    config.JobType.inputFiles         = [INPUTFILES]
#    config.JobType.sendExternalFolder = True
#    config.JobType.maxMemoryMB        = MAXMEM
#    config.Data.inputDBS              = 'global'    
#    config.Data.splitting             = SPLITTING # 'LumiBased' EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
#    config.Data.totalUnits            = NUNITS
#    config.Data.publication           = False
#    config.Site.storageSite           = STORESITE
#
#    def submit(config):
#        try:
#            crabCommand('submit', config = config)
#        except HTTPException, hte:
#            print hte.headers
#
#    # dataset dependent configuration
#
#    config.General.requestName = REQUESTNAME
#    config.Data.unitsPerJob    = UPERJOB
#    config.Data.inputDataset   = DATASET
#    config.Data.outLFNDirBase  = OUTLFNBASE
#    p = Process(target=submit, args=(config,))
#    p.start()
#    p.join()
#
#
#
#
