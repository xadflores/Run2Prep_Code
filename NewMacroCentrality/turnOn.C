#include <iostream>
#include <vector>
#include <algorithm>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom1.h"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TF1.h"
 
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TComplex.h"
#include "TString.h"  
#include "TCut.h"
#include "TNtuple.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h" 



void drawText(const char *text, float xp, float yp, int size=24){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw("same");
}

void turnOn(){
 TH1F::SetDefaultSumw2();
 
 TFile * file = new TFile("/data/velicanu/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIMinimumBias2/Merged/HIMinimumBias_run262816.root");
 //TFile * file = new TFile("/data/velicanu/store/group/phys_heavyions/velicanu/forest/Run2015E/HIExpressPhysics/Merged/HIForestMinbiasUPC_run262548.root");

 TTree * tHlt = (TTree*)file->Get("hltanalysis/HltTree");
 TTree * tHi = (TTree*)file->Get("hiEvtAnalyzer/HiTree");
 TTree * skim = (TTree*)file->Get("skimanalysis/HltTree");
 
 tHlt->AddFriend(tHi);
 tHlt->AddFriend(skim);
 
 
  int nTrig = 8;
  TString trigNames[]={ "L1_MinimumBiasHF1_AND","L1_MinimumBiasHF2_AND","L1_HFplusANDminusTH0","L1_Centrality_ext0_100_MinimumumBiasHF1_AND", "L1_Centrality_ext0_5_MinimumumBiasHF1_AND", "L1_Centrality_ext0_10_MinimumumBiasHF1_AND", "L1_Centrality_ext30_50_MinimumumBiasHF1_AND", "L1_Centrality_ext50_100_MinimumumBiasHF1_AND"};
  //int nTrig = 7;
 //TString trigNames[]={ "L1_HFplusANDminusTH0","L1_Centrality_ext0_100_HFplusANDminusTH0", "L1_Centrality_ext0_5_HFplusANDminusTH0", "L1_Centrality_ext0_10_HFplusANDminusTH0", "L1_Centrality_ext30_50_HFplusANDminusTH0", "L1_Centrality_ext30_100_HFplusANDminusTH0", "L1_Centrality_ext50_100_HFplusANDminusTH0"};
 const int nthresholds=4;
 const int threshold[nthresholds]={10,20,60,100};
 const int color[nthresholds]={1,2,4,7};

 TH1F * hHi[nTrig];
 TGraphAsymmErrors *hTurnOn[nTrig-1];
 for(int iTrig = 0; iTrig < nTrig; iTrig++){
  hHi[iTrig] = new TH1F(Form("hHi%d",iTrig),";hiBin;Trig turn on",201,-0.5,200.5);
  //tHlt->Draw(Form("hiBin>>hHi%d",iTrig),Form("%s && L1_MinimumBiasHF1_AND && HLT_HIL1MinimumBiasHF1AND_v1 && pcollisionEventSelection",trigNames[iTrig].Data()));
  tHlt->Draw(Form("hiBin>>hHi%d",iTrig),Form("%s && L1_MinimumBiasHF1_AND && HLT_HIL1MinimumBiasHF1AND_v1 && pcollisionEventSelection",trigNames[iTrig].Data()));
 }
 
 for(int iTrig = 0; iTrig < nTrig; iTrig++){
  cout<<trigNames[iTrig].Data() << " number of events = "<<hHi[iTrig]->Integral()<<endl;
 }
 
 cout<<1<<endl;
 for(int iTrig = 1; iTrig < nTrig; iTrig++){
  // hHi[iTrig]->Divide(hHi[0]);
  hTurnOn[iTrig-1] = new TGraphAsymmErrors(hHi[iTrig]);
  hTurnOn[iTrig-1]->BayesDivide(hHi[iTrig],hHi[0]);
 }
 
  TLine * line[nthresholds];
   for(int counter = 0; counter < nthresholds; counter++){
    line[counter]=new TLine(threshold[counter],0,threshold[counter],1.1);
    line[counter]->SetLineWidth(4);
    line[counter]->SetLineColor(color[counter]);
    line[counter]->SetLineStyle(2);
  }
   

 TCanvas * c1[nTrig-1];
 for(int iTrig = 1; iTrig<nTrig; iTrig++){
  c1[iTrig-1] = new TCanvas(Form("c1%d",iTrig-1),"",600,600);
   hTurnOn[iTrig-1]->GetXaxis()->SetTitle("hiBin");
   hTurnOn[iTrig-1]->GetYaxis()->SetTitle("Trig turn on");
   hTurnOn[iTrig-1]->SetMaximum(1.5);
   hTurnOn[iTrig-1]->SetMinimum(0);
  // hHi[iTrig]->Draw();
  hTurnOn[iTrig-1]->Draw("A p");
  drawText(Form("%s",trigNames[iTrig].Data()),0.25,0.9);
  c1[iTrig-1]->SaveAs(Form("plots/turnon_%s_%s.png",trigNames[iTrig].Data(),trigNames[0].Data()));
  line[0]->Draw();
  line[1]->Draw();
  line[2]->Draw();
  line[3]->Draw();
  c1[iTrig-1] ->SaveAs(Form("TurnOn/canvas_%d.pdf",iTrig));
 }
}