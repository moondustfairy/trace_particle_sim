//
// Created by sarah on 04.04.26.
//
void Analysis() {
    TFile f = TFile("histo_gcr.root");
    TCanvas* c1 = new TCanvas("c1", "  ");

    TDirectory* dir = f.Get("histo");

    TH1D* hist1 = (TH1D*)dir->Get("1");
    hist1->Draw("HIST");

    TH1D* hist2 = (TH1D*)dir->Get("2");
    hist2->Draw("HIST");

    TH1D* hist3 = (TH1D*)dir->Get("3");
    hist3->Draw("HIST");

    TH1D* hist4 = (TH1D*)dir->Get("4");
    hist4->Draw("HIST");
}