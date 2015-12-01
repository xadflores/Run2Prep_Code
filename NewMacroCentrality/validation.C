#include "centralityCommon.h"
#include "TLine.h"

void validation(){
  const Int_t COLORS[NBINSCentrality] = {kViolet+1,kRed+1,kBlue+1,kGreen+1,1,30};
  TFile *inFile = new TFile("/data/velicanu/store/group/phys_heavyions/velicanu/forest/Run2015E/HIExpressPhysics/Merged/HIForestMinbiasUPC_run262548.root");
  TTree *hltTree = (TTree*)inFile->Get("hltanalysis/HltTree");
  TTree *fEvtTree = (TTree*)inFile->Get("hiEvtAnalyzer/HiTree");
  TTree *fSkimTree = (TTree*)inFile->Get("skimanalysis/HltTree");

  TH1D *hOffline[NBINSCentrality];
  for(int i = 0; i < NBINSCentrality; ++i){
    hOffline[i]=new TH1D("hOffline","hOffline",100,0,200);
  }  

  Int_t f_evt, f_run, f_lumi;
  Float_t vz;
  Int_t hiBin;
  float hiHF;

  Int_t L1_Centrality_ext0_100_HFplusANDminusTH0; 
  Int_t L1_Centrality_ext0_10_HFplusANDminusTH0; 
  Int_t L1_Centrality_ext30_100_HFplusANDminusTH0; 
  Int_t L1_Centrality_ext30_50_HFplusANDminusTH0;  
  Int_t L1_Centrality_ext50_100_HFplusANDminusTH0; 
  Int_t L1_Centrality_ext70_100_HFplusANDminusTH0; 
  Int_t HLT_HIL1MinimumBiasHF1AND_v1;
 
  L1_Centrality_ext0_100_HFplusANDminusTH0=0;
  L1_Centrality_ext0_10_HFplusANDminusTH0=0;
  L1_Centrality_ext30_100_HFplusANDminusTH0=0;
  L1_Centrality_ext30_50_HFplusANDminusTH0=0; 
  L1_Centrality_ext50_100_HFplusANDminusTH0=0;
  L1_Centrality_ext70_100_HFplusANDminusTH0=0;
  HLT_HIL1MinimumBiasHF1AND_v1=0;

  fEvtTree->SetBranchAddress("evt",&f_evt);
  fEvtTree->SetBranchAddress("run",&f_run);
  fEvtTree->SetBranchAddress("lumi",&f_lumi);
  fEvtTree->SetBranchAddress("vz",&vz);
  fEvtTree->SetBranchAddress("hiBin",&hiBin);
  fEvtTree->SetBranchAddress("hiHF",&hiHF);

  hltTree->SetBranchAddress("L1_Centrality_ext0_100_HFplusANDminusTH0",&L1_Centrality_ext0_100_HFplusANDminusTH0);
  hltTree->SetBranchAddress("L1_Centrality_ext0_10_HFplusANDminusTH0",&L1_Centrality_ext0_10_HFplusANDminusTH0);
  hltTree->SetBranchAddress("L1_Centrality_ext30_100_HFplusANDminusTH0",&L1_Centrality_ext30_100_HFplusANDminusTH0);
  hltTree->SetBranchAddress("L1_Centrality_ext30_50_HFplusANDminusTH0",&L1_Centrality_ext30_50_HFplusANDminusTH0);
  hltTree->SetBranchAddress("L1_Centrality_ext50_100_HFplusANDminusTH0",&L1_Centrality_ext50_100_HFplusANDminusTH0);
  hltTree->SetBranchAddress("L1_Centrality_ext70_100_HFplusANDminusTH0",&L1_Centrality_ext70_100_HFplusANDminusTH0);
  hltTree->SetBranchAddress("HLT_HIL1MinimumBiasHF1AND_v1",&HLT_HIL1MinimumBiasHF1AND_v1);

  int entries = 0;     
  entries = fEvtTree->GetEntries();

  for(Long64_t j = 0; j < 1e5; ++j)
  {
    // Only use good collision events ********
    fEvtTree->GetEntry(j);
    fSkimTree->GetEntry(j);
    hltTree->GetEntry(j);


    if(!HLT_HIL1MinimumBiasHF1AND_v1) continue;
    if(L1_Centrality_ext0_100_HFplusANDminusTH0) {hOffline[0]->Fill(hiBin);}
    if(L1_Centrality_ext0_10_HFplusANDminusTH0==1){hOffline[1]->Fill(hiBin);}
    if(L1_Centrality_ext30_50_HFplusANDminusTH0==1){hOffline[2]->Fill(hiBin);}
    if(L1_Centrality_ext30_100_HFplusANDminusTH0==1){hOffline[3]->Fill(hiBin);}
    if(L1_Centrality_ext50_100_HFplusANDminusTH0==1){hOffline[4]->Fill(hiBin);}
    if(L1_Centrality_ext70_100_HFplusANDminusTH0==1){hOffline[5]->Fill(hiBin);}

  }


  TCanvas *canvasranges=new TCanvas("canvasranges","canvasranges",600,500);
  canvasranges->cd();

  hOffline[0]->SetMaximum(100000);
  hOffline[0]->GetXaxis()->SetRangeUser(-10,210.);
  hOffline[0]->GetYaxis()->SetTitleOffset(1.5);

  for(int j=0;j<NBINSCentrality;j++){

    hOffline[j]->Sumw2();
    hOffline[j]->SetMarkerStyle(0);
    hOffline[j]->SetLineColor(COLORS[j]);
    hOffline[j]->SetFillStyle(3325);
    hOffline[j]->SetFillColor(COLORS[j]);
  }
  for(int j=0;j<NBINSCentrality;j++){
    hOffline[j]->Draw("same hist e");

  }


  TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSizePixels(20);


  leg->AddEntry(hOffline[0],"Centrality0-100","lp");
  leg->AddEntry(hOffline[1],"Centrality0-10","lp");
  leg->AddEntry(hOffline[2],"Centrality30-50","lp");
  leg->AddEntry(hOffline[3],"Centrality30-100","lp");
  leg->AddEntry(hOffline[4],"Centrality50-100","lp");
  leg->AddEntry(hOffline[5],"Centrality70-100","lp");
  leg->Draw();  
  
 TLine *line20=new TLine(20.,0,20.,300);
 line20->SetLineWidth(4);
 line20->SetLineStyle(2);

 TLine *line60=new TLine(60.,0,60.,300);
 line60->SetLineWidth(4);
 line60->SetLineStyle(2);

 TLine *line100=new TLine(100.,0,100.,300);
 line100->SetLineWidth(4);
 line100->SetLineStyle(2);

 TLine *line140=new TLine(140.,0,140.,300);
 line140->SetLineWidth(4);
 line140->SetLineStyle(2);

line20->Draw();
line60->Draw();
line100->Draw();
line140->Draw();

TFile *filevalidation=new TFile("filevalidation.root","recreate");
filevalidation->cd();
for(int j=0;j<NBINSCentrality;j++){
  hOffline[j]->Write();
}


}	
