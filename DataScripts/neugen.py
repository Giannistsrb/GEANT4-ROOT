import ROOT
import matplotlib.pyplot as plt
import numpy as np

# Αντικαταστήστε τα ακόλουθα μονοπάτια με τα δικά σας αρχεία
root_file_path1 = '0.913MeV_10^9_TiT_f=1_thin.root'
root_file_path2 = '0.913MeV_10^8_TiT_f=10_thin.root'
root_file_path3 = '0.913MeV_10^7_TiT_f=100_thin.root'
root_file_path4 = '0.913MeV_10^6_TiT_f=1000_thin.root'
root_file_path5 = '0.913MeV_10^5_TiT_f=10000_thin.root'

try:
    # Διάβασμα των 1D ιστογραμμάτων από τα αρχεία ROOT
    file1 = ROOT.TFile(root_file_path1)
    file2 = ROOT.TFile(root_file_path2)
    file3 = ROOT.TFile(root_file_path3)
    file4 = ROOT.TFile(root_file_path4)
    file5 = ROOT.TFile(root_file_path5)

    hist1 = file1.Get("Histo4")
    hist2 = file2.Get("Histo4")
    hist3 = file3.Get("Histo4")
    hist4 = file4.Get("Histo4")
    hist5 = file5.Get("Histo4")
    
    
    # Rebin:
    hist1.Rebin(128)
    hist2.Rebin(128)
    hist3.Rebin(128)
    hist4.Rebin(128)
    hist5.Rebin(128)

    energies1 = [hist1.GetBinCenter(i) for i in range(1, hist1.GetNbinsX() + 1)]
    energies2 = [hist2.GetBinCenter(i) for i in range(1, hist2.GetNbinsX() + 1)]
    energies3 = [hist3.GetBinCenter(i) for i in range(1, hist3.GetNbinsX() + 1)]
    energies4 = [hist4.GetBinCenter(i) for i in range(1, hist4.GetNbinsX() + 1)]
    energies5 = [hist5.GetBinCenter(i) for i in range(1, hist5.GetNbinsX() + 1)]

    counts1 = [hist1.GetBinContent(i) for i in range(1, hist1.GetNbinsX() + 1)]
    counts2 = [hist2.GetBinContent(i) for i in range(1, hist2.GetNbinsX() + 1)]
    counts3 = [hist3.GetBinContent(i) for i in range(1, hist3.GetNbinsX() + 1)]
    counts4 = [hist4.GetBinContent(i) for i in range(1, hist4.GetNbinsX() + 1)]
    counts5 = [hist5.GetBinContent(i) for i in range(1, hist5.GetNbinsX() + 1)]

    # Δημιουργία των κατάλληλων bins για τα ιστογράμματα
    bin_edges1 = np.linspace(min(energies1), max(energies1), len(energies1) + 1)
    bin_edges2 = np.linspace(min(energies2), max(energies2), len(energies2) + 1)
    bin_edges3 = np.linspace(min(energies3), max(energies3), len(energies3) + 1)
    bin_edges4 = np.linspace(min(energies4), max(energies4), len(energies4) + 1)
    bin_edges5 = np.linspace(min(energies5), max(energies5), len(energies5) + 1)

    # Δημιουργία του καμβά
    plt.figure(figsize=(15.2, 4.75))
    plt.subplot(1, 2, 1)
    plt.bar(energies1, counts1, width=np.diff(bin_edges1), align='edge',color="blue", edgecolor="black", alpha=0.40, label="Γεγονότα: 36264")
    plt.title(r"TiT, $E_{d}=0.91MeV$, $N_{d}=10^9$, $f_b=1$", fontsize=22)
    plt.xlabel("Βάθος στόχου [μm]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(fontsize=22, handlelength=0)
    plt.xlim(0, 5)
    plt.ylim(bottom=0)
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)

    plt.subplot(1, 2, 2)
    plt.bar(energies2, counts2, width=np.diff(bin_edges2), align='edge',color="blue", edgecolor="black", alpha=0.40, label="Γεγονότα: 36473")
    plt.title(r"TiT, $E_{d}=0.91MeV$, $N_{d}=10^8$, $f_b=10$", fontsize=22)
    plt.xlabel("Βάθος στόχου [μm]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(fontsize=22, handlelength=0)
    plt.xlim(0, 5)
    plt.ylim(bottom=0)
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)
    
    plt.tight_layout()
    plt.show()
    #--------------------------------------------------------------------------------
    
    plt.figure(figsize=(15.2, 4.75))
    plt.subplot(1, 2, 1)
    plt.bar(energies3, counts3, width=np.diff(bin_edges3), align='edge',color="blue", edgecolor="black", alpha=0.40, label="Γεγονότα: 36194")
    plt.title(r"TiT, $E_{d}=0.91MeV$, $N_{d}=10^7$, $f_b=100$", fontsize=22)
    plt.xlabel("Βάθος στόχου [μm]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(fontsize=22, handlelength=0)
    plt.xlim(0, 5)
    plt.ylim(bottom=0)
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)

    plt.subplot(1, 2, 2)
    plt.bar(energies4, counts4, width=np.diff(bin_edges4), align='edge',color="blue", edgecolor="black", alpha=0.40, label="Γεγονότα: 34318")
    plt.title(r"TiT, $E_{d}=0.91MeV$, $N_{d}=10^6$, $f_b=1000$", fontsize=22)
    plt.xlabel("Βάθος στόχου [μm]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(fontsize=22, handlelength=0)
    plt.xlim(0, 5)
    plt.ylim(bottom=0)
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)

    plt.tight_layout()
    plt.show()
    #----------------------------------------------------------------------------------
    
    # ΓΙΑ ΤΟΥΣ ΕΞΤΡΑ BIASING:
    # Δημιουργία του καμβά
    plt.figure(figsize=(15.2, 4.75))
    plt.subplot(1, 2, 1)
    plt.bar(energies5, counts5, width=np.diff(bin_edges5), align='edge',color="blue", edgecolor="black", alpha=0.40, label="Γεγονότα: 21536")
    plt.title(r"TiT, $E_{d}=0.91MeV$, $N_{d}=10^5$, $f_b=10000$", fontsize=22)
    plt.xlabel("Βάθος στόχου [μm]", fontsize=22)
    plt.ylabel("Γεγονότα", fontsize=22)
    plt.legend(fontsize=22, handlelength=0)
    plt.xlim(0, 5)
    plt.ylim(bottom=0)  # Ορίζουμε τον κατακόρυφο άξονα να ξεκινά από το 0.
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.grid(True)
    

   
    plt.tight_layout()
    plt.show()
    
    #RATIOS OF THE REGIONS A AND B:
    ratio_hist1 = hist1.Integral(0,7)   / hist1.Integral(8,15)
    ratio_hist2 = hist2.Integral(0,7)   / hist2.Integral(8,15)
    ratio_hist3 = hist3.Integral(0,14)  / hist3.Integral(15,22)
    ratio_hist4 = hist4.Integral(0,14)  / hist4.Integral(15,22)
    
    print(ratio_hist1)
    print(ratio_hist2)
    print(ratio_hist3)
    print(ratio_hist4)
    
except Exception as e:
    print(f'Προέκυψε σφάλμα: {e}')
