#include <TH1D.h>
#include <TTree.h>
#include <TLegend.h>
#include <TCut.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include "TStyle.h"
#include "CMS_lumi.C"

const int NThresholds=3;
const Double_t L1_THRESHOLD[NThresholds] = {30.,50.,70};
const Int_t COLORS[NThresholds] = {1, kBlue,kRed};

TString baseline="L1_Centrality_ext0_100_HFplusANDminusTH0&&L1_Centrality_ext0_100_HFplusANDminusTH0_Prescl==1&&pcollisionEventSelection==1&&phfCoincFilter5==1&&pprimaryVertexFilter==1&&pclusterCompatibilityFilter==1";
TString cut[NThresholds]={"L1_Centrality_ext30_100_HFplusANDminusTH0",
                                           "L1_Centrality_ext50_100_HFplusANDminusTH0",
                                           "L1_Centrality_ext70_100_HFplusANDminusTH0"};
TString myprescale[NThresholds]={"L1_Centrality_ext30_100_HFplusANDminusTH0_Prescl",
                                           "L1_Centrality_ext50_100_HFplusANDminusTH0_Prescl",
                                           "L1_Centrality_ext70_100_HFplusANDminusTH0_Prescl"};
TLine*line[NThresholds];

// Take a tree, a variable and calculate the efficiency
TGraphAsymmErrors* getEfficiency(TTree *t, char *variable, TCut preselection, TCut cut, int nBin, Float_t *bins, double prescale)
{
   static int count = 0;
   count++;
   TH1D *hPass = new TH1D (Form("hPass%d",count),"",nBin,bins);
   TH1D *hAll = new TH1D (Form("hAll%d",count),"",nBin,bins);
   t->Draw(Form("%s>>hAll%d",variable,count),preselection);
   t->Draw(Form("%s>>hPass%d",variable,count),preselection&&cut);
   hPass->Scale(prescale);
   
   for (int ibin=1;ibin<=hPass->GetNbinsX();ibin++){
     if (hPass->GetBinContent(ibin)>hAll->GetBinContent(ibin)){
       hPass->SetBinContent(ibin,hAll->GetBinContent(ibin));
       hPass->SetBinError(ibin,hAll->GetBinError(ibin));
     }
   }
   

   TGraphAsymmErrors *g = new TGraphAsymmErrors;
   g->BayesDivide(hPass,hAll);
   return g;
}

void produceCentrality()
{

   // ============== Open file and basic settings ===============   
   // Open Dntuple file   /eos/cms/store/group/phys_heavyions/azsigmon/HiForestAODPbPb5TeV/HIMinimumBias1
   //TFile* file = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/velicanu/forest/HIRun2015/HIExpressPhysics/Merged/HIForestExpress_run262548-v6.root");
   TFile* file = TFile::Open("root://eoscms//eos/cms/store/group/phys_heavyions/azsigmon/HiForestAODPbPb5TeV/HIMinimumBias2/EventTree_PbPb_data_HIMinimumBias2_run262620_15Feb.root");
   TTree * tHlt = (TTree*)file->Get("hltanalysis/HltTree");
   TTree * tHi = (TTree*)file->Get("hiEvtAnalyzer/HiTree");
   TTree * tskim = (TTree*)file->Get("skimanalysis/HltTree");
    
   tHlt->AddFriend(tHi);
   tHlt->AddFriend(tskim);
   
   
   TH1D *hpresc[3];
   double meanprescale[3];
   for (int i=0; i<3;i++){
   hpresc[i]=new TH1D(Form("hpresc_%d",i),"h",100,0,1000);
   TString printer=Form("%s>>hpresc_%d",myprescale[i].Data(),i);
   tHlt->Draw(printer.Data(),baseline.Data()); 
   meanprescale[i]=hpresc[i]->GetMean();
   cout<<"meanprescale="<<meanprescale[i]<<endl;
   }
   
   const int nBin = 40;
   Float_t bins[nBin+1];
   for (int myindex=0; myindex<=nBin; myindex++) {
     bins[myindex]=(double)myindex*5;
     cout<<bins[myindex]<<endl;
   }
   // Templates for plotting  
   TH1D *hTmp = new TH1D ("hTmp","",100,0,100);
   TH1D *hTmp2 = new TH1D ("hTmp2","",100,0,100);
   
   TGraphAsymmErrors* gEfficiency[NThresholds];
   for (int i=0;i<NThresholds;i++){
     gEfficiency[i]=getEfficiency(tHlt,"hiBin/2",baseline.Data(),cut[i].Data(),nBin, bins,meanprescale[i]);
     line[i]=new TLine(L1_THRESHOLD[i],0.,L1_THRESHOLD[i],1.2);
	 line[i]->SetLineWidth(2);
	 line[i]->SetLineStyle(2);
	 line[i]->SetLineColor(COLORS[i]);
   }
       
  int W = 600;
  int H = 600;

  int H_ref = 600; 
  int W_ref = 600; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.14*W_ref;
  float R = 0.08*W_ref;

  TString canvName = "TRDFigure_Centrality";
  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  
  TH1* h = new TH1F("h","",100,0,100);
  h->GetXaxis()->SetNdivisions(11,5,0);
  h->GetXaxis()->SetTitle("Offline centrality (%)");  
  h->GetYaxis()->SetNdivisions(6,5,0);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetTitle("L1 trigger efficiency");  
  h->SetMaximum(2.);
  
  
  h->Draw();
  
  TLegend *leg=new TLegend(0.45,0.65,0.85,0.82,"");
  leg->SetBorderSize(0);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextFont(42);
  leg->SetTextSize(0.042);
  
	for(int i = 0; i < NThresholds; i++){
		leg->AddEntry(gEfficiency[i],Form("L1 centrality (%%) >%d ",(int)L1_THRESHOLD[i]),"lp");
		line[i]->Draw();
	}

  
  for (int i=0;i<NThresholds;i++){
  
    gEfficiency[i]->SetLineColor(COLORS[i]);
    gEfficiency[i]->SetLineWidth(2);
    gEfficiency[i]->SetMarkerStyle(20);
    gEfficiency[i]->SetMarkerColor(COLORS[i]);
    gEfficiency[i]->SetLineStyle(1);
    gEfficiency[i]->Draw("epsame");
  
  }
  leg->Draw();
  
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = ""; // default is "19.7 fb^{-1}"
  lumi_7TeV  = ""; // default is "19.7 fb^{-1}"
  lumi_sqrtS = ""; // default is "19.7 fb^{-1}"

  CMS_lumi( canv, 1, 11 );
  canv->SaveAs("TRDFigure_Centrality.pdf");
  canv->SaveAs("TRDFigure_Centrality.png");

}
