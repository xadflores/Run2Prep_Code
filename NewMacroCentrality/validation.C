#include "centralityCommon.h"


void validation()
{
	TFile *inFile = TFile::Open("root://cms-xrd-global.cern.ch///store/group/phys_heavyions/velicanu/forest/Run2015E/HIExpressPhysics/Merged/HiForestStreamer_Run262314-262315.root");
	TTree *hltTree = (TTree*)inFile->Get("hltanalysis/HltTree");
	TTree *fEvtTree = (TTree*)inFile->Get("hiEvtAnalyzer/HiTree");
	TTree *fSkimTree = (TTree*)inFile->Get("skimanalysis/HltTree");


	Int_t f_evt, f_run, f_lumi;
	Float_t vz;
	Int_t hiBin;
	float hiHF;

	Int_t L1_Centrality_ext0_100_HFplusANDminusTH0; 
	Int_t L1_Centrality_ext0_100_HFplusORminusTH0;  
	Int_t L1_Centrality_ext0_10_HFplusANDminusTH0;  
	Int_t L1_Centrality_ext0_5_HFplusANDminusTH0;   
	Int_t L1_Centrality_ext30_100_HFplusANDminusTH0;
	Int_t L1_Centrality_ext30_50_HFplusANDminusTH0; 
	Int_t L1_Centrality_ext50_100_HFplusANDminusTH0;
	Int_t L1_Centrality_ext70_100_HFplusANDminusTH0;

	fEvtTree->SetBranchAddress("evt",&f_evt);
	fEvtTree->SetBranchAddress("run",&f_run);
	fEvtTree->SetBranchAddress("lumi",&f_lumi);
	fEvtTree->SetBranchAddress("vz",&vz);
	fEvtTree->SetBranchAddress("hiBin",&hiBin);
	fEvtTree->SetBranchAddress("hiHF",&hiHF);

        hltTree->SetBranchAddress("L1_Centrality_ext0_100_HFplusANDminusTH0",&L1_Centrality_ext0_100_HFplusORminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext0_100_HFplusORminusTH0",&L1_Centrality_ext0_100_HFplusORminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext0_10_HFplusANDminusTH0",&L1_Centrality_ext0_10_HFplusANDminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext0_5_HFplusANDminusTH0",&L1_Centrality_ext0_5_HFplusANDminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext30_100_HFplusANDminusTH0",&L1_Centrality_ext30_100_HFplusANDminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext30_50_HFplusANDminusTH0",&L1_Centrality_ext30_50_HFplusANDminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext50_100_HFplusANDminusTH0",&L1_Centrality_ext50_100_HFplusANDminusTH0);
        hltTree->SetBranchAddress("L1_Centrality_ext70_100_HFplusANDminusTH0",&L1_Centrality_ext70_100_HFplusANDminusTH0);

	TH1D *hofflineCentrality = new TH1D("hofflineCentrality","Offline cent; Offline centrality; Entries",40,0.,200.);


        int entries = 0;     
        entries = fEvtTree->GetEntries();
	for(Long64_t j = 0; j < entries; ++j)
	{
		// Only use good collision events ********
		fEvtTree->GetEntry(j);
		fSkimTree->GetEntry(j);
		hltTree->GetEntry(j);

		if(L1_Centrality_ext0_10_HFplusANDminusTH0==1){hofflineCentrality->Fill(hiBin);}

	}
  hofflineCentrality->Draw();
}	
