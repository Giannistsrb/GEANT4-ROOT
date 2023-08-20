import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

# Input data for CU63
X_CU63 = np.array([1e-11, 0.001, 0.2, 0.5, 1, 2, 3, 4, 5, 6])
Y_CU63 = np.array([0, 1.2e-19, 1.2e-19, 4.218e-17, 4.47199e-9, 0.000177828, 0.00823285, 0.0714118, 0.221832, 0.300118])

# Input data for CU65
X_CU65 = np.array([1e-11, 0.001, 0.2, 0.5, 1, 2, 3, 4, 5, 6])
Y_CU65 = np.array([0, 1.2e-19, 1.2e-19, 3.5138e-17, 5.3683e-9, 0.000216501, 0.00891176, 0.0763174, 0.264039, 0.327509])

# Create interp1d functions for each isotope with linear interpolation
interp_func_CU63 = interp1d(X_CU63, Y_CU63, kind='cubic')
interp_func_CU65 = interp1d(X_CU65, Y_CU65, kind='cubic')

# Generate points for the smooth line using the interpolated functions
X_smooth = np.linspace(1e-11, 6, 100)
Y_smooth_CU63 = interp_func_CU63(X_smooth)
Y_smooth_CU65 = interp_func_CU65(X_smooth)

# Plotting the results

plt.plot(X_CU63, Y_CU63, 'o')
plt.plot(X_smooth, Y_smooth_CU63, label='$^{63}$Cu(d,n)$^{64}$Zn')

plt.plot(X_CU65, Y_CU65, 'o')
plt.plot(X_smooth, Y_smooth_CU65, label='$^{65}$Cu(d,n)$^{66}$Zn')

plt.xlabel('Ενέργεια [ΜeV]')
plt.ylabel('Ενεργός διατομή σ [barns]')
plt.title('Ισότοπα Χαλκού - TENDL 2019')
plt.grid(True)
plt.legend(fontsize=12)
plt.show()
