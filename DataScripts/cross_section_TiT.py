import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

# Data for TENDL-2019: TI-48(D,N)V-49:
X_TI48 = np.array([1e-11, 0.001, 0.2, 0.5, 1, 2, 3, 4, 5, 6, 7, 8])
Y_TI48 = np.array([0, 1.2e-19, 1.2e-19, 1.6292e-11, 2.19533e-6, 0.0052322, 0.0984077, 0.327286, 0.451305, 0.473195, 0.411219, 0.320511])


# Input data for T:
# Data for ENDF/B-VI: H-3(D,N)HE-4-L0
X_H3_DN_HE4 = np.array([
    0.0000, 0.001, 0.002019, 0.00301352, 0.004, 0.00502857, 0.006, 0.00702927,
    0.0080295, 0.009, 0.0100597, 0.011, 0.0120579, 0.0131208, 0.014, 0.0150878,
    0.0153108, 0.0156516, 0.016, 0.0173281, 0.0176608, 0.018, 0.0192371, 0.02,
    0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.07, 0.075, 0.08, 0.085,
    0.09, 0.095, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2,
    1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7,
    2.8, 3, 3.2, 3.4, 3.6, 3.8, 4.8, 5.2, 5.8, 6.6, 7, 8])

Y_H3_DN_HE4 = np.array([
    0, 1.0268e-15, 2.64987e-10, 5.20681e-8, 1.1604e-6, 1.02897e-5, 4.6453e-5,
    0.000159317, 0.000414276, 0.00089074, 0.00179705, 0.003062, 0.00515644,
    0.00814677, 0.011399, 0.0165785, 0.0178076, 0.0198007, 0.021986, 0.0318598,
    0.0347161, 0.037791, 0.0505896, 0.059678, 0.28096, 0.47073, 0.71636, 1.0173,
    1.3702, 1.7686, 2.2021, 3.1134, 3.5535, 3.9571, 4.3068, 4.5902, 4.8005,
    4.937, 2.6051, 1.3448, 0.85074, 0.60485, 0.46249, 0.37157, 0.30944, 0.26483,
    0.23158, 0.20607, 0.18603, 0.16999, 0.15695, 0.1462, 0.13725, 0.12971,
    0.12333, 0.11788, 0.1132, 0.10916, 0.10567, 0.10263, 0.099995, 0.097697,
    0.095695, 0.093952, 0.092438, 0.089992, 0.088184, 0.086877, 0.085975,
    0.085262, 0.081523, 0.079509, 0.075695, 0.070442, 0.067979, 0.06000])
    
# Create interp1d functions for each isotope with linear interpolation
interp_func_CU63 = interp1d(X_TI48, Y_TI48, kind='cubic')
interp_func_CU65 = interp1d(X_H3_DN_HE4, Y_H3_DN_HE4, kind='cubic')

# Generate points for the smooth line using the interpolated functions
X_smooth = np.linspace(1e-11, 8, 100)
Y_smooth_CU63 = interp_func_CU63(X_smooth)
Y_smooth_CU65 = interp_func_CU65(X_smooth)

# Plotting the results

#plt.plot(X_TI48, Y_TI48, 'o', color='black')
plt.plot(X_smooth, Y_smooth_CU63, label='$^{48}$Ti(d,n)$^{49}$V')

#plt.plot(X_H3_DN_HE4, Y_H3_DN_HE4, 'o')
plt.plot(X_smooth, Y_smooth_CU65, label='$^{3}$H(d,n)$^{4}$He')

plt.xlabel('Ενέργεια [ΜeV]')
plt.ylabel('Ενεργός διατομή σ [barns]')
plt.title('Tιτάνιο & Τρίτιο')
plt.grid(True)
plt.yscale('log')
plt.legend(fontsize=12)
plt.show()

