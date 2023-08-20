import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import math

# Input data
X_MO95 = np.array([1e-11, 0.001, 0.5, 1, 2, 3, 4, 5, 6, 7])
Y_MO95 = np.array([0, 1.2e-19, 1.2e-19, 3.928e-14, 2.97986e-8, 7.90296e-5, 0.00390386, 0.033173, 0.0872612, 0.130208])

X_MO96 = np.array([1e-11, 0.001, 0.5, 1, 2, 3, 4, 5, 6, 7])
Y_MO96 = np.array([0, 1.2e-19, 1.2e-19, 4.0218e-14, 2.86456e-7, 7.95158e-5, 0.00396184, 0.036419, 0.141209, 0.26316])

X_MO97 = np.array([1e-11, 0.001, 0.5, 1, 2, 3, 4, 5, 6, 7])
Y_MO97 = np.array([0, 1.2e-19, 1.2e-19, 4.1049e-14, 4.04048e-8, 8.51258e-5, 0.00272287, 0.0147095, 0.0334668, 0.0461191])

X_MO98 = np.array([0.125, 0.25, 0.5, 1, 2, 3, 4, 5, 6, 7])
Y_MO98 = np.array([0, 1e-20, 1e-20, 4.7513e-14, 3.24791e-7, 6.01069e-5, 0.0031971, 0.0282156, 0.0692929, 0.0928391])

X_MO100 = np.array([0.125, 0.25, 0.5, 1, 2, 3, 4, 5, 6, 7])
Y_MO100 = np.array([0, 1e-20, 1e-20, 7.62e-14, 4.28859e-7, 0.000112396, 0.00319352, 0.0141385, 0.0333502, 0.0430998])

# Create interp1d functions for each isotope
interp_func_MO95 = interp1d(X_MO95, Y_MO95, kind='cubic')
interp_func_MO96 = interp1d(X_MO96, Y_MO96, kind='cubic')
interp_func_MO97 = interp1d(X_MO97, Y_MO97, kind='cubic')
interp_func_MO98 = interp1d(X_MO98, Y_MO98, kind='cubic')
interp_func_MO100 = interp1d(X_MO100, Y_MO100, kind='cubic')

# Generate points for the smooth line for each isotope
X_smooth = np.linspace(0.125, 7, 100)
Y_smooth_MO95 = interp_func_MO95(X_smooth)
Y_smooth_MO96 = interp_func_MO96(X_smooth)
Y_smooth_MO97 = interp_func_MO97(X_smooth)
Y_smooth_MO98 = interp_func_MO98(X_smooth)
Y_smooth_MO100 = interp_func_MO100(X_smooth)

# Plotting the results
plt.figure()

plt.plot(X_MO95, Y_MO95, 'o')
plt.plot(X_smooth, Y_smooth_MO95, label='$^{95}$Mo(d,n)$^{96}$Tc')

plt.plot(X_MO96, Y_MO96, 'o')
plt.plot(X_smooth, Y_smooth_MO96, label='$^{96}$Mo(d,n)$^{97}$Tc')

plt.plot(X_MO97, Y_MO97, 'o')
plt.plot(X_smooth, Y_smooth_MO97, label='$^{97}$Mo(d,n)$^{98}$Tc')

plt.plot(X_MO98, Y_MO98, 'o')
plt.plot(X_smooth, Y_smooth_MO98, label='$^{98}$Mo(d,n)$^{99}$Tc')

plt.plot(X_MO100, Y_MO100, 'o')
plt.plot(X_smooth, Y_smooth_MO100, label='$^{100}$Mo(d,n)$^{101}$Tc')

plt.xlabel('Ενέργεια [ΜeV]')
plt.ylabel('Ενεργός διατομή σ [barns]')
plt.legend(fontsize=12)
plt.title('Ισότοπα Μολυβδαινίου - TENDL 2019')
plt.grid(True)
plt.show()

