
cmsrel CMSSW_7_5_3_patch1
cd CMSSW_7_5_3_patch1/src
cmsenv
git cms-merge-topic -u CmsHI:forest_$CMSSW_VERSION
mkdir Analyzer
cd Analyzer
git clone -b AnalyzerForGCTunpacking git@github.com:richard-cms/L1UpgradeAnalyzer.git
scram b -j8

