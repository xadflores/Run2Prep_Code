from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'HI_Centrality_Study_GCTadd'
config.General.workArea = 'HI_Centrality_Study_GCTadd'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForest_PbPb_MIX_75X_DATA.py'

config.section_("Data")
config.Data.inputDataset = '/HIMinBiasUPC/dgulhan-HIMinBiasUPC_HIRun2011-v1_RECO_753_patch1-fd44351629dd155a25de2b4c109c824c/USER'
config.Data.inputDBS = 'phys03'
config.Data.useParent = True
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/HI/Prompt/Cert_181530-183126_HI7TeV_PromptReco_Collisions11_JSON.txt'
config.Data.publication = False
config.Data.outLFNDirBase = '/store/group/phys_heavyions/chflores/'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'


