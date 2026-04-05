
// source ${PATH TO ROOT INSTALL}/root/bin/thisroot.sh
// compile: g++ -o root_analysis root_analysis.cc `root-config --cflags --libs`
// execute: ./root_analysis

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TLegend.h"
#include "THStack.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    TFile f = TFile("histo_gcr.root");


    TDirectory* dirNTuple = (TFile*)f.Get("ntuple");
    TDirectory* dirHisto = (TFile*)f.Get("histo");

    Int_t EventID, PDGcode;
    Double_t ETube, ECylinder, LTube, LCylinder;

    TTree* tree = (TTree*)dirNTuple->Get("Ntuple1");
    tree->SetBranchAddress("EventID", &EventID);
    tree->SetBranchAddress("PDGcode", &PDGcode);
    tree->SetBranchAddress("ETube", &ETube);
    tree->SetBranchAddress("ECylinder", &ECylinder);
    tree->SetBranchAddress("LTube", &LTube);
    tree->SetBranchAddress("LCylinder", &LCylinder);

    Long64_t nEntries = tree->GetEntries();
    cout << "Reading tree with " << nEntries << " entries" << endl;

    //tree->Scan("LTube", "LTube>3.");
    //tree->Scan("LCylinder", "LCylinder>3.");

    auto hsProton = new THStack("hs", "Energy deposit for protons in tube (red) and cylinder (blue); Energy deposit (MeV); Counts");
    auto hsHe4 = new THStack("hs", "Energy deposit for He-4 in tube (red) and cylinder (blue); Energy deposit (MeV); Counts");
    auto hsElectron = new THStack("hs", "Energy deposit for electrons in tube (red) and cylinder (blue); Energy deposit (MeV); Counts");


    TH1D *histETube = new TH1D("ETube", "Energy deposit in tube", 150, 0., 3);
    TH1D *histECylinder = new TH1D("ECylinder", "Energy deposit in cylinder", 150, 0., 30);
    TH1D *histLTube = new TH1D("LTube", "Track length in tube", 150, 0., 5);
    TH1D *histLCylinder = new TH1D("LCylinder", "Track length in cylinder", 150, 0., 25);
    TH1D *histDepEProtonsTube = new TH1D("DepEProtonsTube", "Energy deposit for protons in Tube", 150, 0., 5);
    TH1D *histDepEProtonsCylinder = new TH1D("DepEProtonsCylinder", "Energy deposit for protons in Cylinder", 150, 0., 5);
    TH1D *histDepEHe4Tube = new TH1D("DepEHe4Tube", "Energy deposit for He-4 in Tube", 150, 0., 3);
    TH1D *histDepEHe4Cylinder = new TH1D("DepEHe4Cylinder", "Energy deposit for He-4 in Cylinder", 150, 0., 3);
    TH1D *histDepEElectronsTube = new TH1D("DepEElectronsTube", "Energy deposit for electrons in Tube", 150, 0., 3);
    TH1D *histDepEElectronsCylinder = new TH1D("DepEElectronsCylinder", "Energy deposit for electrons in Cylinder", 150, 0., 3);

    histETube->GetXaxis()->SetTitle("Energy deposit (MeV)");
    histETube->GetYaxis()->SetTitle("Counts");
    histECylinder->GetXaxis()->SetTitle("Energy deposit (MeV)");
    histECylinder->GetYaxis()->SetTitle("Counts");
    histLTube->GetXaxis()->SetTitle("Track length (mm)");
    histLTube->GetYaxis()->SetTitle("Counts");
    histLCylinder->GetXaxis()->SetTitle("Track length (mm)");
    histLCylinder->GetYaxis()->SetTitle("Counts");

    histDepEProtonsTube->SetFillColor(kRed);
    histDepEProtonsCylinder->SetFillColor(kBlue);
    histDepEHe4Tube->SetFillColor(kRed);
    histDepEHe4Cylinder->SetFillColor(kBlue);
    histDepEElectronsTube->SetFillColor(kRed);
    histDepEElectronsCylinder->SetFillColor(kBlue);

    // PDG codes: proton 2212, He-4 1000020040, electron 11

    for (int i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        histETube->Fill(ETube);
        histECylinder->Fill(ECylinder);
        histLTube->Fill(LTube);
        histLCylinder->Fill(LCylinder);
            if (PDGcode == 2212) {
                histDepEProtonsTube->Fill(ETube);
                histDepEProtonsCylinder->Fill(ECylinder);
            } else if (PDGcode == 1000020040) {
                histDepEHe4Tube->Fill(ETube);
                histDepEHe4Cylinder->Fill(ECylinder);
            } else if (PDGcode == 11) {
                histDepEElectronsTube->Fill(ETube);
                histDepEElectronsCylinder->Fill(ECylinder);
            }

    }

    hsProton->Add(histDepEProtonsTube);
    hsProton->Add(histDepEProtonsCylinder);

    hsHe4->Add(histDepEHe4Tube);
    hsHe4->Add(histDepEHe4Cylinder);

    hsElectron->Add(histDepEElectronsTube);
    hsElectron->Add(histDepEElectronsCylinder);

    TCanvas* canvas1 = new TCanvas("c1", "Canvas for each quantity", 0, 0, 800, 600);
    canvas1->Divide(2, 2);
    TCanvas* canvas2 = new TCanvas("c2", "Canvas for particle-specific energy deposits", 0, 0, 800, 600);
    canvas2->Divide(1, 3);

    canvas1->cd(1);
    histETube->Draw();
    canvas1->cd(2);
    histECylinder->Draw();
    canvas1->cd(3);
    histLTube->Draw();
    canvas1->cd(4);
    histLCylinder->Draw();
    canvas1->Print("histograms_gcr.pdf");

    canvas2->cd(1);
    hsProton->Draw();
    canvas2->cd(2);
    hsHe4->Draw();
    canvas2->cd(3);
    hsElectron->Draw();
    canvas2->Print("particle_specific_energy_deposits.pdf");

    return 0;
}