#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>

void histneugen()
{    
    // Δημιουργία των TFile για να διαβάσουμε τα αρχεία r.root
    TFile *file1 = TFile::Open("3.45MeV_10^9_Mo_f=1_thin.root");
    TFile *file2 = TFile::Open("3.45MeV_10^7_Mo_f=100_thin.root");
    TFile *file3 = TFile::Open("3.45MeV_10^7_Mo_f=1000_thin.root");
    TFile *file4 = TFile::Open("3.45MeV_10^7_Mo_f=10000_thin.root");
    
    // Δημιουργία των TH1F ιστογραμμάτων και διάβασμά τους από τα αρχεία
    TH1F *hist1 = (TH1F*)file1->Get("Histo4;1");
    TH1F *hist2 = (TH1F*)file2->Get("Histo4;1");
    TH1F *hist3 = (TH1F*)file3->Get("Histo4;1");
    TH1F *hist4 = (TH1F*)file4->Get("Histo4;1");

    
    //-------------------------------------------------------------------------------
    int originalBins = 4096;
    double originalXmin = 0.0;
    double originalXmax = 10.0;
    int newBins = 16;
    double newXmin = 0.0;
    double newXmax = 10.0;

    int firstBin = hist1->GetXaxis()->FindBin(newXmin);
    int lastBin = hist1->GetXaxis()->FindBin(newXmax);

    // Calculate the rebin factor based on the desired new range and original range
    int rebinFactor = (lastBin - firstBin + 1) / newBins;

    // Rebin the histograms for the x-axis range [0, 25]
    hist1->Rebin(rebinFactor);
    hist2->Rebin(rebinFactor);
    hist3->Rebin(rebinFactor);
    hist4->Rebin(rebinFactor);

    // Set the x-axis range to [0, 25]
    hist1->GetXaxis()->SetRangeUser(newXmin, newXmax);
    hist2->GetXaxis()->SetRangeUser(newXmin, newXmax);
    hist3->GetXaxis()->SetRangeUser(newXmin, newXmax);
    hist4->GetXaxis()->SetRangeUser(newXmin, newXmax);

cout << "A" << " " << "B" << " " << "C" << " " << endl;
cout << hist1->Integral(0, 5) << " " << hist1->Integral(6,10) << " " << hist1->Integral(11,16) << endl;
cout << hist2->Integral(0, 5) << " " << hist2->Integral(6,10) << " " << hist2->Integral(11,16) << endl;
cout << hist3->Integral(0, 5) << " " << hist3->Integral(6,10) << " " << hist3->Integral(11,16) << endl;
cout << hist4->Integral(0, 5) << " " << hist4->Integral(6,10) << " " << hist4->Integral(11,16) << endl;

cout << "A/B" << " " << "A/C" << " " << endl;
cout << hist1->Integral(0, 5) / hist1->Integral(6,10) << " " << hist1->Integral(0,5) / hist1->Integral(11,16) <<endl;
cout << hist2->Integral(0, 5) / hist2->Integral(6,10) << " " << hist2->Integral(0,5) / hist2->Integral(11,16) <<endl;
cout << hist3->Integral(0, 5) / hist3->Integral(6,10) << " " << hist3->Integral(0,5) / hist3->Integral(11,16) <<endl;
cout << hist4->Integral(0, 5) / hist4->Integral(6,10) << " " << hist4->Integral(0,5) / hist4->Integral(11,16) <<endl;

cout << "(A/B)analog/(A/B)biased" << " " << "(A/C)analog/(A/C)biased" << " " << endl;

cout << (hist1->Integral(0, 5) / hist1->Integral(6,10))/(hist2->Integral(0, 5) / hist2->Integral(6,10)) << " " 
     << (hist1->Integral(0, 5) / hist1->Integral(11,16))/(hist2->Integral(0, 5) / hist2->Integral(11,16)) << endl;
cout << (hist1->Integral(0, 5) / hist1->Integral(6,10))/(hist3->Integral(0, 5) / hist3->Integral(6,10)) << " " 
     << (hist1->Integral(0, 5) / hist1->Integral(11,16))/(hist3->Integral(0, 5) / hist3->Integral(11,16)) << endl;
cout << (hist1->Integral(0, 5) / hist1->Integral(6,10))/(hist4->Integral(0, 5) / hist4->Integral(6,10)) << " " 
     << (hist1->Integral(0, 5) / hist1->Integral(11,16))/(hist4->Integral(0, 5) / hist4->Integral(11,16)) << endl;


    }
