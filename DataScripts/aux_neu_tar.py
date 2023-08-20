import ROOT
import matplotlib.pyplot as plt
import numpy as np
import math as m

# Αντικαταστήστε τα ακόλουθα μονοπάτια με τα δικά σας αρχεία
root_file_path1 = '3.45MeV_10^9_biasTarget=Mo_f=10000_fixed.root'  #Mo  biasing
root_file_path2 = '3.45MeV_10^9_biasTarget=TiT_f=1000_fixed.root' #TiT biasing
root_file_path3 = '3.45MeV_10^9_biasTarget=Cu_f=10000_fixed.root'   #Cu  biasing


try:
    # Διάβασμα των 1D ιστογραμμάτων από τα αρχεία ROOT
    file1 = ROOT.TFile(root_file_path1)
    file2 = ROOT.TFile(root_file_path2)
    file3 = ROOT.TFile(root_file_path3)
    
    #Neutrons from every foil:
    #WHEN WE DO BIASING IN MO:
    histMo_biasMo              = file1.Get("AuX_1stFoil_TargetMoly;1")  #Moly neutrons with biasing in Mo
    histTiT_biasMo             = file1.Get("AuX_1stFoil_TargetTiT;1")   #TiT neutrons with biasing in Mo
    histCu_biasMo              = file1.Get("AuX_1stFoil_TargetCopper;1") #Cu neutrons with biasing in Mo
    histNotMoAndCu_biasMo      = file1.Get("AuX_1stFoil_TargetNotMoAndCu;1") #Flange and TiT neutrons with biasing in Mo
    
    #WHEN WE DO BIASING IN TIT:
    histMo_biasTiT               = file2.Get("AuX_1stFoil_TargetMoly;1") #Moly neutrons with biasing in TiT
    histTiT_biasTiT              = file2.Get("AuX_1stFoil_TargetTiT;1")  #TiT neutrons with biasing in TiT
    histCu_biasTiT               = file2.Get("AuX_1stFoil_TargetCopper;1") #Cu neutrons with biasing in TiT
    histNotMoAndCu_biasTiT       = file2.Get("AuX_1stFoil_TargetNotMoAndCu;1") #Flange and TiT neutrons with biasing in TiT
    
    #WHEN WE DO BIASING IN CU:
    histMo_biasCu              = file3.Get("AuX_1stFoil_TargetMoly;1") #Moly neutrons with biasing in Cu
    histTiT_biasCu             = file3.Get("AuX_1stFoil_TargetTiT;1")  #TiT neutrons with biasing in Cu
    histCu_biasCu              = file3.Get("AuX_1stFoil_TargetCopper;1") #Cu neutrons with biasing in Cu
    histNotMoAndCu_biasCu      = file3.Get("AuX_1stFoil_TargetNotMoAndCu;1") #Flange and TiT neutrons with biasing in Cu
   
    
    #Clone histograms which are about to be scaled:
    #Mo:
    histMo_biasMo_scaled  = histMo_biasMo.Clone()
    histMo_biasTiT_scaled = histMo_biasTiT.Clone()
    histMo_biasCu_scaled  = histMo_biasCu.Clone()
    
    #TiT:
    histTiT_biasMo_scaled = histTiT_biasMo.Clone()
    histTiT_biasTiT_scaled = histTiT_biasTiT.Clone()
    histTiT_biasCu_scaled = histTiT_biasCu.Clone()
    
    #Cu:
    histCu_biasMo_scaled  = histCu_biasMo.Clone()
    histCu_biasTiT_scaled = histCu_biasTiT.Clone()
    histCu_biasCu_scaled  = histCu_biasCu.Clone()
    
    #NotMoAndCu:
    histNotMoAndCu_biasMo_scaled  = histNotMoAndCu_biasMo.Clone()
    histNotMoAndCu_biasTiT_scaled = histNotMoAndCu_biasTiT.Clone()
    histNotMoAndCu_biasCu_scaled  = histNotMoAndCu_biasCu.Clone()
    
    
    #Scale Mo and Cu histograms:
    #Mo:
    histMo_biasMo_scaled.Scale(1/10)
    histMo_biasTiT_scaled.Scale(1)
    histMo_biasCu_scaled.Scale(1/10)
    
    #TiT:
    histTiT_biasMo_scaled.Scale(1/10)
    histTiT_biasTiT_scaled.Scale(1)
    histTiT_biasCu_scaled.Scale(1/10)
    
    #Cu:
    histCu_biasMo_scaled.Scale(1/10)
    histCu_biasTiT_scaled.Scale(1)
    histCu_biasCu_scaled.Scale(1/10)
    
    #Parasitic Neutrons:
    histNotMoAndCu_biasMo_scaled.Add(histTiT_biasMo_scaled,   -1)
    histNotMoAndCu_biasTiT_scaled.Add(histTiT_biasTiT_scaled, -1)
    histNotMoAndCu_biasCu_scaled.Add(histTiT_biasCu_scaled,   -1)
    histNotMoAndCu_biasMo_scaled.Scale(1/10)
    histNotMoAndCu_biasTiT_scaled.Scale(1)
    histNotMoAndCu_biasCu_scaled.Scale(1/10)
    
    
    #Group the Mo/TiT/Cu neutrons with different biasings:
    histMo_biasMo_scaled.Add(histMo_biasTiT_scaled)
    histMo_biasMo_scaled.Add(histMo_biasCu_scaled)
    
    histTiT_biasMo_scaled.Add(histTiT_biasTiT_scaled)
    histTiT_biasMo_scaled.Add(histTiT_biasCu_scaled)
    
    histCu_biasMo_scaled.Add(histCu_biasTiT_scaled)
    histCu_biasMo_scaled.Add(histCu_biasCu_scaled)
    
    histNotMoAndCu_biasMo_scaled.Add(histNotMoAndCu_biasTiT_scaled)
    histNotMoAndCu_biasMo_scaled.Add(histNotMoAndCu_biasCu_scaled)
    
    #Rebin:
    histMo_biasMo_scaled.Rebin(4)
    histTiT_biasMo_scaled.Rebin(4)
    histCu_biasMo_scaled.Rebin(4)
    histNotMoAndCu_biasMo_scaled.Rebin(4)
    
    
    #Clone the histMo_biasMo, histTiT_biasMo, histCu_biasMo. We get the final histograms:
    histMo       = histMo_biasMo_scaled.Clone()
    histTiT      = histTiT_biasMo_scaled.Clone()
    histCu       = histCu_biasMo_scaled.Clone()
    histOtherNeu = histNotMoAndCu_biasMo_scaled.Clone()
    
    #Integrals:
    histMoIntegral     = histMo.Integral()
    histTiTIntegral    = histTiT.Integral()
    histCuIntegral     = histCu.Integral()
    histOtherIntegral  = histOtherNeu.Integral()
    All                = histMoIntegral + histTiTIntegral + histCuIntegral + histOtherIntegral
    
    #Print the counts for verify:
    print("Molybdenum neutrons:", histMoIntegral)
    print("TiT neutrons:", histTiTIntegral)
    print("Cu neutrons:", histCuIntegral)
    print("Other:", histOtherIntegral)
    print("All neutrons:", All)
    
    
    #Add Mo, TiT, Cu neutrons with different biasings:
    energiesMo         = [histMo.GetBinCenter(i)           for i in range(1, histMo.GetNbinsX()         + 1)]
    energiesTiT        = [histTiT.GetBinCenter(i)          for i in range(1, histTiT.GetNbinsX()        + 1)]
    energiesCu         = [histCu.GetBinCenter(i)           for i in range(1, histCu.GetNbinsX()         + 1)]
    energiesOtherNeu   = [histOtherNeu.GetBinCenter(i)     for i in range(1, histOtherNeu.GetNbinsX()   + 1)]
    
    countsMo           = [histMo.GetBinContent(i)            for i in range(1, histMo.GetNbinsX()              + 1)]
    countsTiT          = [histTiT.GetBinContent(i)           for i in range(1, histTiT.GetNbinsX()             + 1)]
    countsCu           = [histCu.GetBinContent(i)            for i in range(1, histCu.GetNbinsX()              + 1)]
    countsOtherNeu     = [histOtherNeu.GetBinContent(i)      for i in range(1, histOtherNeu.GetNbinsX()        + 1)]
    
    # Add a small value (e.g., 1e-10) to each count to avoid zero or negative values
    small_value = 1e-6
    countsMo          = [count + small_value for count in countsMo]
    countsTiT         = [count + small_value for count in countsTiT]
    countsCu          = [count + small_value for count in countsCu]
    countsOtherNeu    = [count + small_value for count in countsOtherNeu]
    
    # Δημιουργία του καμβά
    plt.figure(figsize=(15,9))
    plt.step(energiesMo, countsMo, color="blue", alpha=1.0)
    plt.step(energiesTiT, countsTiT, color="red", alpha=1.0)
    plt.step(energiesCu, countsCu, color="green",  alpha=1.0)
    plt.step(energiesOtherNeu, countsOtherNeu, color="black", alpha=1.0)
    plt.title(r"Στόχος Al, $E_{d}=3.45MeV$", fontsize=22)
    plt.xlabel("Ενέργεια νετρονίων [MeV]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(["Στόχος Mo. Γεγονότα: 2436", "Στόχος TiT. Γεγονότα: 930998", "Στόχος Cu. Γεγονότα: 23316", "Παρασιτικά υπόλοιπης διάταξης. Γεγονότα: 23315 "], loc = 0, frameon = True, fontsize=22)
    plt.xlim(0, 20)
    plt.xscale('log')
    plt.xlim(left=1, right=20)
    plt.yscale('log')
    plt.ylim(bottom=m.sqrt(1/10))  
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)
    
    plt.show()

except Exception as e:
    print(f'Προέκυψε σφάλμα: {e}')
