#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

//THIS IS FOR PLOTTING WITH MCNP FLUX (RUNS WITH Helium-3 in the Foil):

void plot1DHist()
 {
  //THIS IS FOR PLOTTING WITH MCNP FLUX (RUNS WITH Helium-3 in the Foil):
  
  // Open the ROOT files:
  TFile* file1 = TFile::Open("2.9MeV_10^9_biasTarget=HeTiT_f=100_fnInteractions>4.root");
  TFile* file2 = TFile::Open("2.9MeV_10^9_biasTarget=HeTiT_f=200_fnInteractions>4.root");
  TFile* file3 = TFile::Open("2.9MeV_10^9_biasTarget=HeTiT_f=1000_fnInteractions>4.root");
  TFile* file4 = TFile::Open("al7.root");
  
  // Retrieve the histograms from root files:
  TH1F *hist1 = (TH1F*)file1->Get("Al7_1stFoil_NeutronsAll;1");
  TH1F *hist2 = (TH1F*)file2->Get("Al7_1stFoil_NeutronsAll;1");
  TH1F *hist3 = (TH1F*)file3->Get("Al7_1stFoil_NeutronsAll;1");
  TH1F *hist4 = (TH1F*)file4->Get("MCNP_Flux;1");
  
  // Create a canvas and set the style:
  TCanvas* canvas1 = new TCanvas("Canvas1", "Fluxes", 800, 600);
  gStyle->SetOptStat(0); // Turn off the statistics box: type 0.

  // Draw the histogram:
  hist1->Draw("hist");
  hist2->Draw("hist SAME");
  hist3->Draw("hist SAME");
  hist4->Draw("hist SAME");
  
  
  // Axies names:
  hist1->GetXaxis()->SetTitle("Energy [MeV]");
  hist1->GetYaxis()->SetTitle("Neutron Counts");
  hist1->SetTitle("2.9MeV deuteron beam. BiasTarget:He-TiT. Al7 (1st foil): Neutron Flux.");

  // Customize the histogram appearance
  hist1->SetLineColor(kBlack);
  hist1->SetLineWidth(1);
  
  hist2->SetLineColor(kBlue);
  hist2->SetLineWidth(1);
  hist2->Scale(1.0 / 2.0);
  
  hist3->SetLineColor(kRed);
  hist3->SetLineWidth(1);
  hist3->Scale(1.0 / 10.0);

  hist4->SetLineColor(kGreen);
  hist4->SetLineWidth(2);
 
  //Logarithmic scale in y-axis:
  gPad->SetLogy();
  
  // Create a legend:
  TLegend* legend1 = new TLegend(0.7, 0.7, 0.9, 0.9);

  legend1->AddEntry(hist1, "N=10e+9. f=100.  Entries: 87068  ",  "l");
  legend1->AddEntry(hist2, "N=10e+9. f=200.  Entries: 87329  ",  "l");
  legend1->AddEntry(hist3, "N=10e+9, f=1000. Entries: 886453 ",  "l");
  legend1->AddEntry(hist4, "MCNP Flux", "l");

  legend1->SetTextSize(0.034);

  // Draw the legend
  legend1->Draw();
  
  //Integral under every histogram:
  Double_t hist1Integral = hist1->Integral();  //Geant with f=100
  Double_t hist2Integral = hist2->Integral();  //Geant with f=200
  Double_t hist3Integral = hist3->Integral();  //Geant with f=1000
  Double_t hist4Integral = hist4->Integral();  //MCNP Flux
  
  //Normalization of the MCNP flux to the Geant with f=100 histogram:
  hist4->Scale(hist1Integral/hist4Integral);
  
   //Integrals calculator: 
   std::cout << "Integrals for the first plots (Geant for vs MCNP): " << " " << std::endl;
   std::cout << "Integral of hist with f=100:  " << hist1Integral     << " " << std::endl;
   std::cout << "Integral of hist with f=200:  " << hist2Integral     << " " << std::endl;
   std::cout << "Integral of hist with f=1000: " << hist3Integral     << " " << std::endl;
   std::cout << "Integral of the MCNP Flux:    " << hist4Integral     << " " << std::endl;
   
   
   //Integrals from 1350s to 1690s bin (part1) and from 1690s to 2000 bin (part2):
   
   //Geant with f=100:
   Double_t Integral_Part1_Hist1 = hist1->Integral(1350,1690);
   Double_t Integral_Part2_Hist1 = hist1->Integral(1690,2000);
   
   //Geant with f=200:
   Double_t Integral_Part1_Hist2 = hist2->Integral(1350,1690);
   Double_t Integral_Part2_Hist2 = hist2->Integral(1690,2000);
   
   //Geant with f=1000:
   Double_t Integral_Part1_Hist3 = hist3->Integral(1350,1690);
   Double_t Integral_Part2_Hist3 = hist3->Integral(1690,2000);
   
   //MCNP Flux:
   Double_t Integral_Part1_Hist4 = hist4->Integral(1350,1690);
   Double_t Integral_Part2_Hist4 = hist4->Integral(1690,2000);
   
   //Ratios for the areas for every histogram:
   Double_t RatioHist1 = Integral_Part2_Hist1 / Integral_Part1_Hist1; 
   Double_t RatioHist2 = Integral_Part2_Hist2 / Integral_Part1_Hist2;
   Double_t RatioHist3 = Integral_Part2_Hist3 / Integral_Part1_Hist3;
   Double_t RatioHist4 = Integral_Part2_Hist4 / Integral_Part1_Hist4;
   
   //Print the results for the ratios: 
   std::cout << "Ratios for the first plots (Geant for vs MCNP):   "               << " " << std::endl;
   std::cout << "Ratio B/A, Geant with f=100:  " << RatioHist1 << " " << std::endl; 
   std::cout << "Ratio B/A, Geant with f=200:  " << RatioHist2 << " " << std::endl; 
   std::cout << "Ratio B/A, Geant with f=1000: " << RatioHist3 << " " << std::endl; 
   std::cout << "Ratio B/A, MCNP Flux:         " << RatioHist4 << " " << std::endl; 
   
   //-----------------------------------------------------------------------------------------------
   //THIS IS FOR COMPARING THE Run with Helium with the Run without Helium in 2.9MeV with f=1000:
   
   //Open the root files:
   TFile* withHelium3    = TFile::Open("2.9MeV_10^9_biasTarget=HeTiT_f=1000_fnInteractions>4.root");
   TFile* withoutHelium3 = TFile::Open("2.9MeV_10^9_biasTarget=TiT_f=1000_fnInteractions>4.root");
   
   //Retrieve the histograms from ROOT files:
   TH1F *histHeTiT = (TH1F*)withHelium3->Get("Al7_1stFoil_NeutronsAll;1");
   TH1F *histTiT   = (TH1F*)withoutHelium3->Get("Al7_1stFoil_NeutronsAll;1");
   
  // Create a canvas and set the style:
  TCanvas* canvas2 = new TCanvas("Canvas2", "Fluxes", 800, 600);
  gStyle->SetOptStat(0); // Turn off the statistics box: type 0.
  
  // Draw the histogram:
  histHeTiT->Draw("hist");
  histTiT->Draw("hist SAME");
  
  // Axies names:
  histHeTiT->GetXaxis()->SetTitle("Energy [MeV]");
  histHeTiT->GetYaxis()->SetTitle("Neutron Counts");
  histHeTiT->SetTitle("2.9MeV deuteron beam. Comparison with and without He3. Biasing f=1000. Al7 (1st foil). Neutron Flux.");

  // Customize the histogram appearance
  histHeTiT->SetLineColor(kRed);
  histHeTiT->SetLineWidth(1);
  
  histTiT->SetLineColor(kBlack);
  histTiT->SetLineWidth(1);
  
  //Logarithmic scale in y-axis:
  gPad->SetLogy();
  
  // Create a legend:
  TLegend* legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);

  legend2->AddEntry(histHeTiT, "HeTiT: N=10e+9. f=1000. Entries: 886453",  "l");
  legend2->AddEntry(histTiT,   "TiT:   N=10e+9. f=1000. Entries: 886453",  "l");
  legend2->SetTextSize(0.034);

  // Draw the legend
  legend2->Draw();
  
  //Integral under every histogram:
  Double_t histHeTiTIntegral = histHeTiT->Integral();  //   Helium-3 Run f=1000
  Double_t histTiTIntegral   = histTiT->Integral();    //No Helium-3 Run f=1000
  
  //Integrals calculator: 
  std::cout << "Integrals for the second plots (HeTiT vs TiT with f=1000):  "    << " " << std::endl;
  std::cout << "Integral of hist with HeTiT:  " << histHeTiTIntegral             << " " << std::endl;
  std::cout << "Integral of hist with TiT:    " << histTiTIntegral               << " " << std::endl;
  
  //Integrals from 1350s to 1690s bin (part1) and from 1690s to 2000 bin (part2):
   
   //With He3:
   Double_t Integral_Part1_HeTiT = histHeTiT->Integral(1350,1690);
   Double_t Integral_Part2_HeTiT = histHeTiT->Integral(1690,2000);
   
   //Without He3:
   Double_t Integral_Part1_TiT = histTiT->Integral(1350,1690);
   Double_t Integral_Part2_TiT = histTiT->Integral(1690,2000);
   
   //Ratios for the areas for every histogram:
   Double_t RatioHeTiT = Integral_Part2_HeTiT / Integral_Part1_HeTiT; 
   Double_t RatioTiT   = Integral_Part2_TiT / Integral_Part1_TiT;
   
   //Print the results for the ratios: 
   std::cout << "Ratios for the second plots (HeTiT vs TiT with f=1000): "   << " " << std::endl;
   std::cout << "Ratio B/A, HeTiT:  " << RatioHeTiT                          << " " << std::endl; 
   std::cout << "Ratio B/A, TiT:    " << RatioTiT                            << " " << std::endl; 
    
}

