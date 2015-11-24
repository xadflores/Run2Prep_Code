#include "centralityCommon.h"
#include "TLine.h"

using namespace std;

void plotCentrality(TString l1_input)
{

	TFile *lFile = TFile::Open(Form("%s_CentralityCalibration.root",l1_input.Data()));
	TH2D *hcorrOfflineEtsumVsL1Etsum = (TH2D*)lFile->Get("hcorrOfflineEtsumVsL1Etsum");
	TH1D *hl1Etsum = (TH1D*)lFile->Get("hl1Etsum");
	TProfile *profileofflineCentralityVsl1Etsum = (TProfile*)lFile->Get("profileofflineCentralityVsl1Etsum");
	TProfile *profilel1EtsumVsofflineCentrality = (TProfile*)lFile->Get("profilel1EtsumVsofflineCentrality");
	TProfile *profilel1CentralityVsofflineCentrality = (TProfile*)lFile->Get("profilel1CentralityVsofflineCentrality");
	TH2D *hcorrL1CentralityVsfflineCentrality= (TH2D*)lFile->Get("hcorrL1CentralityVsfflineCentrality");
	TF1* fprofileofflinel1EtsumVsCentrality_Calibration=(TF1*)lFile->Get("fprofileofflinel1EtsumVsCentrality_Calibration");
	fprofileofflinel1EtsumVsCentrality_Calibration->SetName("fprofileofflinel1EtsumVsCentrality_Calibration");
	TH1D *hofflineCentrality= (TH1D*)lFile->Get("hofflineCentrality");

	TH1D *hcorrl1EtsumPlusVscorrl1EtsumMinus= (TH1D*)lFile->Get("hcorrl1EtsumPlusVscorrl1EtsumMinus");
	TH1D *hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel= (TH1D*)lFile->Get("hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel");

	TH1D *hOffline[NBINSCentrality];
	ofstream out_data(Form("%s_output.txt",l1_input.Data()));


	for(int i = 0; i < NBINSCentrality; ++i){
		hOffline[i]=(TH1D*)lFile->Get(Form("hOffline_Bin%d",i)); 
	}  

	TF1 *f1 = new TF1("f1","pol9",0,6500);
	TF1 *f2 = new TF1("f2","pol9",0,200.);
	TF1 *f3 = new TF1("f3","pol1",0,200.);
	f3->SetLineColor(2);
	f1->SetLineColor(1);
	f2->SetLineColor(1);


	TCanvas *canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel=new TCanvas("canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel","canvas",600,600);
	canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->cd();
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->SetMinimum(0.);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitleOffset(1.3);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetLabelSize(0.03);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetTitle("L1 ETsum Plus");
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitle("L1 ETsum Minus");
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetTitleOffset(1.1);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitleOffset(1.1);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetTitleSize(0.04);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitleSize(0.04);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetRangeUser(0,2500.);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetRangeUser(0,2500.);
	hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->Draw();

	TCanvas *canvascorrl1EtsumPlusVscorrl1EtsumMinus=new TCanvas("canvascorrl1EtsumPlusVscorrl1EtsumMinus","canvas",600,600);
	canvascorrl1EtsumPlusVscorrl1EtsumMinus->cd();
	hcorrl1EtsumPlusVscorrl1EtsumMinus->SetMinimum(0.);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitleOffset(1.3);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetLabelSize(0.03);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetTitle("L1 ETsum Plus");
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitle("L1 ETsum Minus");
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetTitleOffset(1.1);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitleOffset(1.1);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetTitleSize(0.04);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitleSize(0.04);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetRangeUser(0,2500.);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetRangeUser(0,2500.);
	hcorrl1EtsumPlusVscorrl1EtsumMinus->Draw();

	hcorrl1EtsumPlusVscorrl1EtsumMinus->Draw();

	TCanvas *canvasOfflineCentrality=new TCanvas("canvasOfflineCentrality","canvas",1200,800);
	canvasOfflineCentrality->cd();
	hofflineCentrality->SetMinimum(0.);
	hofflineCentrality->GetYaxis()->SetTitleOffset(1.3);
	hofflineCentrality->GetYaxis()->SetLabelSize(0.03);
	hofflineCentrality->GetXaxis()->SetTitle("Offline Centrality");
	hofflineCentrality->GetYaxis()->SetTitle("Entries");
	hofflineCentrality->GetXaxis()->SetTitleOffset(1.1);
	hofflineCentrality->GetYaxis()->SetTitleOffset(1.1);
	hofflineCentrality->GetXaxis()->SetTitleSize(0.04);
	hofflineCentrality->GetYaxis()->SetTitleSize(0.04);
	hofflineCentrality->Draw();

	TCanvas *canvasOfflineEtsumVsL1Etsum=new TCanvas("canvasOfflineEtsumVsL1Etsum","canvas",1200,800);
	canvasOfflineEtsumVsL1Etsum->cd();
	hcorrOfflineEtsumVsL1Etsum->SetMinimum(0.);
	hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitleOffset(1.3);
	hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetLabelSize(0.03);
	hcorrOfflineEtsumVsL1Etsum->GetXaxis()->SetTitle("Offline HF E_{T} sum");
	hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitle("Emulator HF E_{T} sum");
	hcorrOfflineEtsumVsL1Etsum->GetXaxis()->SetTitleOffset(1.1);
	hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitleOffset(1.1);
	hcorrOfflineEtsumVsL1Etsum->GetXaxis()->SetTitleSize(0.04);
	hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitleSize(0.04);
	hcorrOfflineEtsumVsL1Etsum->Draw();


	TCanvas *canvasL1Etsum=new TCanvas("canvasL1Etsum","canvas",600,500);
	canvasL1Etsum->cd();
	hl1Etsum->SetMinimum(0.);
	hl1Etsum->GetYaxis()->SetTitleOffset(1.3);
	hl1Etsum->GetYaxis()->SetLabelSize(0.03);
	hl1Etsum->GetYaxis()->SetTitle("Entries");
	hl1Etsum->GetXaxis()->SetTitle("L1 E_{T} sum");
	hl1Etsum->GetXaxis()->SetTitleOffset(1.1);
	hl1Etsum->GetYaxis()->SetTitleOffset(1.1);
	hl1Etsum->GetXaxis()->SetTitleSize(0.04);
	hl1Etsum->GetYaxis()->SetTitleSize(0.04);
	hl1Etsum->Draw();


	TCanvas *canvasofflineCentralityVsl1Etsum=new TCanvas("canvasofflineCentralityVsl1Etsum","canvas",600,500);
	canvasofflineCentralityVsl1Etsum->cd();
	profileofflineCentralityVsl1Etsum->GetXaxis()->SetRangeUser(0,6500.);
	profileofflineCentralityVsl1Etsum->GetYaxis()->SetRangeUser(0,250.);
	profileofflineCentralityVsl1Etsum->GetYaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
	profileofflineCentralityVsl1Etsum->GetXaxis()->SetTitle("Emulator HF E_{T} sum");
	profileofflineCentralityVsl1Etsum->SetMarkerStyle(21);
	profileofflineCentralityVsl1Etsum->SetMarkerSize(0.6);
	profileofflineCentralityVsl1Etsum->GetXaxis()->SetTitleOffset(1.2);
	profileofflineCentralityVsl1Etsum->GetYaxis()->SetTitleOffset(1.2);
	profileofflineCentralityVsl1Etsum->Draw();
	profileofflineCentralityVsl1Etsum->Fit("f1");


	TCanvas *canvasl1EtsumVsofflineCentrality=new TCanvas("canvasl1EtsumVsofflineCentrality","canvas",600,500);
	canvasl1EtsumVsofflineCentrality->cd();
	profilel1EtsumVsofflineCentrality->GetYaxis()->SetRangeUser(0,6500.);
	profilel1EtsumVsofflineCentrality->GetXaxis()->SetRangeUser(0,250.);
	profilel1EtsumVsofflineCentrality->GetXaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
	profilel1EtsumVsofflineCentrality->GetYaxis()->SetTitle("Emulator HF E_{T} sum");
	profilel1EtsumVsofflineCentrality->SetMarkerStyle(21);
	profilel1EtsumVsofflineCentrality->SetMarkerSize(0.6);
	profilel1EtsumVsofflineCentrality->GetXaxis()->SetTitleOffset(1.2);
	profilel1EtsumVsofflineCentrality->GetYaxis()->SetTitleOffset(1.2);
	profilel1EtsumVsofflineCentrality->Draw();
	profilel1EtsumVsofflineCentrality->Fit("f2");

	TCanvas *canvasL1CentralityVsfflineCentrality=new TCanvas("canvasL1CentralityVsfflineCentrality","canvas",600,500);
	canvasL1CentralityVsfflineCentrality->cd();
	hcorrL1CentralityVsfflineCentrality->SetMinimum(0.);
	hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitleOffset(1.3);
	hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetLabelSize(0.03);
	hcorrL1CentralityVsfflineCentrality->GetXaxis()->SetTitle("Offline centrality");
	hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitle("L1 centrality");
	hcorrL1CentralityVsfflineCentrality->GetXaxis()->SetTitleOffset(1.1);
	hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitleOffset(1.1);
	hcorrL1CentralityVsfflineCentrality->GetXaxis()->SetTitleSize(0.04);
	hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitleSize(0.04);
	hcorrL1CentralityVsfflineCentrality->Draw();


	TCanvas *canvasl1CentralityVsofflineCentrality=new TCanvas("canvasl1CentralityVsofflineCentrality","canvas",600,500);
	canvasl1CentralityVsofflineCentrality->cd();
	profilel1CentralityVsofflineCentrality->GetYaxis()->SetRangeUser(0,250.);
	profilel1CentralityVsofflineCentrality->GetXaxis()->SetRangeUser(0,250.);
	profilel1CentralityVsofflineCentrality->GetXaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
	profilel1CentralityVsofflineCentrality->GetYaxis()->SetTitle("L1 Centrality (bins of 0.5%)");
	profilel1CentralityVsofflineCentrality->SetMarkerStyle(21);
	profilel1CentralityVsofflineCentrality->SetMarkerSize(0.6);
	profilel1CentralityVsofflineCentrality->GetXaxis()->SetTitleOffset(1.2);
	profilel1CentralityVsofflineCentrality->GetYaxis()->SetTitleOffset(1.2);
	profilel1CentralityVsofflineCentrality->Draw();
	profilel1CentralityVsofflineCentrality->Fit("f3");

	const Int_t COLORS[NBINSCentrality] = {kViolet+1,kRed+1,kBlue+1,kGreen+1,1,30};

	TCanvas *canvasranges=new TCanvas("canvasranges","canvasranges",600,500);
	canvasranges->cd();

	hOffline[0]->SetMaximum(500);
	hOffline[0]->GetXaxis()->SetRangeUser(-10,210.);
	//hOffline[0]->GetYaxis()->SetRangeUser(0,100.);
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
        TLine *line1 = new TLine(10,0,10,200);
        line1->SetLineStyle(2);
        line1->Draw("same");
        TLine *line2 = new TLine(20,0,20,200);
        line2->SetLineStyle(2);

        line2->Draw("same");
        TLine *line3 = new TLine(60,0,60,200);
        line3->SetLineStyle(2);

        line3->Draw("same");
        TLine *line4 = new TLine(100,0,100,200);
        line4->SetLineStyle(2);

        line4->Draw("same");
        TLine *line5 = new TLine(140,0,140,200);
        line5->SetLineStyle(2);

        line5->Draw("same");

	double newReslimit[10];
        for(int k=0; k<10;k++){
		if ( k==0 || (k%2)==0){
			newReslimit[k]=limit[k]+deltaC[k];}
		else {newReslimit[k]=limit[k]-deltaC[k];}
	}


	TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->SetTextSizePixels(20);
         

	leg->AddEntry(hOffline[0],Form("0  < L1cen < %f",newReslimit[0]),"lp");
	leg->AddEntry(hOffline[1],Form("%f < L1cen < %f",newReslimit[1],newReslimit[2]),"lp");
	leg->AddEntry(hOffline[2],Form("%f < L1cen < %f",newReslimit[3],newReslimit[4]),"lp");
	leg->AddEntry(hOffline[3],Form("%f < L1cen < %f",newReslimit[5],newReslimit[6]),"lp");
	leg->AddEntry(hOffline[4],Form("%f< L1cen < %f", newReslimit[7],newReslimit[8]),"lp");
	leg->AddEntry(hOffline[5],Form("%f< L1cen < 200",newReslimit[9]),"lp");
	leg->Draw();  

	double Etsum[10];
	double EtsumOrig[10];
	for (int m=0;m<10;m++){

		Etsum[m]=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(newReslimit[m]);
		EtsumOrig[m]=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit[m]);
	}

	out_data<<"***************************"<<endl;
	out_data<<"LUT for offline centrality ranges with OVERLAPS"<<endl;
	out_data<<"centrality 0-"<<(int)(newReslimit[0])<<" = E_{t} sum > "<<Etsum[0]<<endl;
	out_data<<"centrality "<<(int)(newReslimit[1])<<"-"<<(int)(newReslimit[2])<<" ="<<Etsum[2]<<"<E_{t} sum <"<<Etsum[1]<<endl;
	out_data<<"centrality "<<(int)(newReslimit[3])<<"-"<<(int)(newReslimit[4])<<" ="<<Etsum[4]<<"<E_{t} sum <"<<Etsum[3]<<endl;
	out_data<<"centrality "<<(int)(newReslimit[5])<<"-"<<(int)(newReslimit[6])<<" ="<<Etsum[6]<<"<E_{t} sum <"<<Etsum[5]<<endl;
	out_data<<"centrality "<<(int)(newReslimit[7])<<"-"<<(int)(newReslimit[8])<<" ="<<Etsum[8]<<"<E_{t} sum <"<<Etsum[7]<<endl;
	out_data<<"centrality "<<(int)(newReslimit[9])<<"-200 = E_{t} sum <"<<Etsum[9]<<endl;

	out_data<<"***************************"<<endl;
	out_data<<"LUT for offline centrality ranges with ORIGINAL"<<endl;
	out_data<<"centrality 0-"<<(int)(limit[0])<<" = E_{t} sum > "<<EtsumOrig[0]<<endl;
	out_data<<"centrality "<<(int)(limit[1])<<"-"<<(int)(limit[2])<<" ="<<EtsumOrig[2]<<"<E_{t} sum <"<<EtsumOrig[1]<<endl;
	out_data<<"centrality "<<(int)(limit[3])<<"-"<<(int)(limit[4])<<" ="<<EtsumOrig[4]<<"<E_{t} sum <"<<EtsumOrig[3]<<endl;
	out_data<<"centrality "<<(int)(limit[5])<<"-"<<(int)(limit[6])<<" ="<<EtsumOrig[6]<<"<E_{t} sum <"<<EtsumOrig[5]<<endl;
	out_data<<"centrality "<<(int)(limit[7])<<"-"<<(int)(limit[8])<<" ="<<EtsumOrig[8]<<"<E_{t} sum <"<<EtsumOrig[7]<<endl;
	out_data<<"centrality "<<(int)(limit[9])<<"-200 =  E_{t} sum <"<<EtsumOrig[9]<<endl;


    out_data<<"0"<<endl;
    out_data<<(int)(EtsumOrig[9])<<endl;
    out_data<<(int)(EtsumOrig[7])<<endl;
    out_data<<(int)(EtsumOrig[5])<<endl;
    out_data<<(int)(EtsumOrig[3])<<endl;
    out_data<<(int)(EtsumOrig[1])<<endl;
    out_data<<(int)6000<<endl;
    out_data<<(int)7000<<endl;
    out_data<<endl;

    out_data<<(int)(Etsum[8])<<endl;
    out_data<<(int)(Etsum[9])<<endl;
    out_data<<(int)(Etsum[6])<<endl;
    out_data<<(int)(Etsum[7])<<endl;
    out_data<<(int)(Etsum[4])<<endl;
    out_data<<(int)(Etsum[5])<<endl;
    out_data<<(int)(Etsum[2])<<endl;
    out_data<<(int)(Etsum[3])<<endl;
    out_data<<(int)(Etsum[0])<<endl;
    out_data<<(int)(Etsum[1])<<endl;
    out_data<<(int)5900<<endl;
    out_data<<(int)6100<<endl;
    out_data<<(int)6900<<endl;
    out_data<<(int)7100<<endl;

	//cout<<isMC<<endl;
	if(isMC){

		TH1D *hNcoll[NBINSCentrality];

		for(int i = 0; i < NBINSCentrality; ++i){
			hNcoll[i]=(TH1D*)lFile->Get(Form("hNcoll_Bin%d",i)); 
			hNcoll[i]->Rebin(5);
		}  

		TCanvas *canvasrangesNcoll=new TCanvas("canvasrangesNcoll","canvasrangesNcoll",600,500);
		canvasrangesNcoll->cd();

		hNcoll[0]->SetMaximum(300);
		hNcoll[0]->GetXaxis()->SetRangeUser(-0.5,1999.5);
		hNcoll[0]->GetYaxis()->SetTitleOffset(1.5);

		for(int j=0;j<NBINSCentrality;j++){

			hNcoll[j]->Sumw2();
			hNcoll[j]->SetMarkerStyle(0);
			hNcoll[j]->SetLineColor(COLORS[j]);
			hNcoll[j]->SetFillStyle(3325);
			hNcoll[j]->SetFillColor(COLORS[j]);
		}
		for(int j=0;j<NBINSCentrality;j++){
			hNcoll[j]->Draw("same hist e");

		}

		TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
		leg->SetFillColor(0);
		leg->SetTextFont(42);
		leg->SetTextSizePixels(20);

		leg->AddEntry(hNcoll[0],Form("0  < L1cen < %f",limit[0]),"lp");
		leg->AddEntry(hNcoll[1],Form("%f < L1cen < %f",limit[0],limit[1]),"lp");
		leg->AddEntry(hNcoll[2],Form("%f < L1cen < %f",limit[1],limit[2]),"lp");
		leg->AddEntry(hNcoll[3],Form("%f < L1cen < %f",limit[2],limit[3]),"lp");
		leg->AddEntry(hNcoll[4],Form("%f< L1cen < %f", limit[3],limit[4]),"lp");
		leg->AddEntry(hNcoll[5],Form("%f< L1cen < 200",limit[4]),"lp");
		leg->Draw();

			canvasrangesNcoll->SaveAs(Form("Plots/canvasrangesNcoll_%s.pdf",l1_input.Data()));

	}
	        canvasranges->SaveAs(Form("Plots/canvasranges_%s.pdf",l1_input.Data()));
		canvasl1CentralityVsofflineCentrality->SaveAs(Form("Plots/canvasl1CentralityVsofflineCentrality_%s.pdf",l1_input.Data()));
		canvasL1CentralityVsfflineCentrality->SaveAs(Form("Plots/canvasL1CentralityVsfflineCentrality_%s.pdf",l1_input.Data()));
		canvasl1EtsumVsofflineCentrality->SaveAs(Form("Plots/canvasl1EtsumVsofflineCentrality_%s.pdf",l1_input.Data()));
		canvasofflineCentralityVsl1Etsum->SaveAs(Form("Plots/canvasofflineCentralityVsl1Etsum_%s.pdf",l1_input.Data()));
		canvasL1Etsum->SaveAs(Form("Plots/canvasL1Etsum_%s.pdf",l1_input.Data()));
		canvasOfflineEtsumVsL1Etsum->SaveAs(Form("Plots/canvasOfflineEtsumVsL1Etsum_%s.pdf",l1_input.Data()));
		canvasOfflineCentrality->SaveAs(Form("Plots/canvasOfflineCentrality_%s.pdf",l1_input.Data()));
		canvascorrl1EtsumPlusVscorrl1EtsumMinus->SaveAs(Form("Plots/canvascorrl1EtsumPlusVscorrl1EtsumMinus_%s.pdf",l1_input.Data()));
		canvascorrl1EtsumPlusVscorrl1EtsumMinus->SaveAs(Form("Plots/canvascorrl1EtsumPlusVscorrl1EtsumMinusNo_%s.pdf",l1_input.Data()));
		canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->SaveAs(Form("Plots/canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel_%s.pdf",l1_input.Data()));

}


int main(int argc, char **argv)
{
	if(argc == 2)
	{
		plotCentrality(argv[1]);
		return 0;
	}
	else
	{
		std::cout << "Usage: \nmakeTurnOn_fromSameFile.exe <input_HiForest_file> <output_file>" << std::endl;
		return 1;
	}
}
