#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TProfile.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <stdio.h>
#include <TProfile.h>
#include <map>
//#include <TMap.h>
#include <vector>
#include <iostream>
#include <fstream>

const int NBINSCentrality=6;
const double limit[10]={10,10,20,20,60,60,100,100,140,140};

//% of overlap for a given bin ie 1%of200 gives 2 
const int deltaC[10] = {0,0,0,0,0,2,2,2,2,2}; 

int isMC = 0;
