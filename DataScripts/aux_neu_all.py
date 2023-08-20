import ROOT
import matplotlib.pyplot as plt
import numpy as np

# Αντικαταστήστε τα ακόλουθα μονοπάτια με τα δικά σας αρχεία
root_file_path1 = '3.45MeV_10^9_biasTarget=Mo_f=10000_fixed.root'  #Mo  biasing
root_file_path2 = '3.45MeV_10^9_biasTarget=TiT_f=1000_fixed.root' #TiT biasing
root_file_path3 = '3.45MeV_10^9_biasTarget=Cu_f=10000_fixed.root'   #Cu  biasing
root_file_path4 = 'au_X.root' #MCNP


try:
    # Διάβασμα των 1D ιστογραμμάτων από τα αρχεία ROOT
    file1 = ROOT.TFile(root_file_path1)
    file2 = ROOT.TFile(root_file_path2)
    file3 = ROOT.TFile(root_file_path3)
    file4 = ROOT.TFile(root_file_path4)
    
    hist1 = file1.Get("AuX_1stFoil_NeutronsAll;1")
    hist2 = file2.Get("AuX_1stFoil_NeutronsAll;1")
    hist3 = file3.Get("AuX_1stFoil_NeutronsAll;1")
    hist4 = file4.Get("MCNP_Flux;1")   
    
    #Clone hist1 and hist3:
    hist1_scaled = hist1.Clone()
    hist3_scaled = hist3.Clone()
    
    #Scale the hist1 and hist3:
    hist1_scaled.Scale(1/10)      # Scale hist1 bin contents by 1/10
    hist3_scaled.Scale(1/10)      # Scale hist3 bin contents by 10
    
    #Add them to hist2:
    hist2.Add(hist1_scaled)  # Add scaled hist1 to hist2
    hist2.Add(hist3_scaled)  # Add scaled hist3 to hist2
    
    #Clone the hist2:
    histAll = hist2.Clone()  
    
    #INTEGRALS:
    histAllIntegral = histAll.Integral()
    hist4Integral = hist4.Integral()
    
    print(histAllIntegral)
    print(hist4Integral)
    
        
    #SCALING THE MCNP:
    hist4.Scale(histAllIntegral/hist4Integral)
    
    energies4   = [hist4.GetBinCenter(i)        for i in range(1, hist4.GetNbinsX() + 1)]
    energiesAll = [histAll.GetBinCenter(i)      for i in range(1, histAll.GetNbinsX()  + 1)]
    
    counts4     = [hist4.GetBinContent(i)      for i in range(1, hist4.GetNbinsX() + 1)]
    countsAll   = [histAll.GetBinContent(i)    for i in range(1, histAll.GetNbinsX()  + 1)]
    
    # Add a small value (e.g., 1e-10) to each count to avoid zero or negative values
    small_value = 1e-6
    #counts2 = [count + small_value for count in counts2]
    counts4   = [count + small_value for count in counts4]
    countsAll = [count + small_value for count in countsAll]
 

    # Δημιουργία του καμβά
    plt.figure(figsize=(15,9))
    plt.step(energiesAll, countsAll, color="red")
    plt.step(energies4, counts4, color="blue")
    plt.title(r"Στόχος Al, $E_{d}=3.45MeV$", fontsize=22)
    plt.xlabel("Ενέργεια νετρονίων [MeV]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(["GEANT4", "MCNP"], loc = 0, frameon = True, fontsize=22)
    plt.xlim(0, 20)
    #plt.xscale('log')
    #plt.xlim(left=1, right=20)
    plt.yscale('log')
    plt.ylim(bottom=1e-1)  # Ορίζουμε τον κατακόρυφο άξονα να ξεκινά από το 0
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)
    
    plt.show()

except Exception as e:
    print(f'Προέκυψε σφάλμα: {e}')
