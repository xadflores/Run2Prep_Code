//---Skimmer---//
//-------------//
//---To Run ---//
//>root
//>.L skim.C+
//>skim("inFile","outFile");
//--

#include "TTree.h"
#include "TFile.h"

//--how many events do you want to keep?
#define EVENTS 100000

TTree* makeSmall(TTree* told) {
   TTree *tnew = told->CloneTree(0);
   int nentries = told->GetEntries();
   for (int i=0; i<EVENTS; i++) {
      told->GetEntry(i);
      tnew->Fill();
   }
   return tnew;
}

//-------
//this is used to skim the file located at MIT
// /cms/store/user/velicanu/HydjetMB5020_750_75X_mcRun2_HeavyIon_v1_RealisticHICollisions2011_STARTHI50_mc_L1_HLT_HIFOREST_merged/0.root 
//
//-------

void skim(const char *filein, const char *fileout) {
   TFile *fin = TFile::Open(filein);
   TFile *fout = new TFile(fileout,"RECREATE");

//--Define the tree's that you want to keep--
   fout->cd();
   TDirectory *akPu3 = fout->mkdir("akPu3CaloJetAnalyzer");
   akPu3->cd();
   TTree *tr_akPu3 = makeSmall((TTree*) fin->Get("akPu3CaloJetAnalyzer/t"));

   TDirectory *hiEvtAna = fout->mkdir("hiEvtAnalyzer");
   hiEvtAna->cd();
   TTree *tr_hiEvtAna = makeSmall((TTree*) fin->Get("hiEvtAnalyzer/HiTree"));

   TDirectory *skimAna = fout->mkdir("skimanalysis");
   skimAna->cd();
   TTree *tr_skimAna = makeSmall((TTree*) fin->Get("skimanalysis/HltTree"));

   TDirectory *L1UpgradeAna = fout->mkdir("L1UpgradeAnalyzer");
   L1UpgradeAna->cd();
   TTree *tr_L1UpgradeAna = makeSmall((TTree*) fin->Get("L1UpgradeAnalyzer/L1UpgradeTree"));

   TDirectory *HiGenPAna = fout->mkdir("HiGenParticleAna");
   HiGenPAna->cd();
   TTree *tr_HiGenPAna = makeSmall((TTree*) fin->Get("HiGenParticleAna/hi"));
//---

   fout->Write();
   fout->Close();
}


