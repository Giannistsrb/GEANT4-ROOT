import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

    # Input data
X = np.array([1.00e-11, 0.001, 0.05, 0.1, 0.2, 0.5, 1, 2, 3, 4])
Y = np.array([0, 1.20e-19, 1.20e-19, 1.57e-19, 1.96e-12, 2.17e-06, 0.00157483, 0.0823068, 0.23765, 0.287446])

    # Create an interpolation function
interp_func = interp1d(X, Y, kind='cubic')

    # Generate points for the smooth line
X_smooth = np.linspace(X.min(), X.max(), 100)
Y_smooth = interp_func(X_smooth)

    # Plot the original data and the smooth line
plt.figure()
plt.plot(X, Y, 'ro')
plt.plot(X_smooth, Y_smooth, 'b-', label='$^{27}$Al(d,n)$^{28}$Si')

    # Add labels and title
plt.xlabel('Ενέργεια [ΜeV]')
plt.ylabel('Ενεργός διατομή σ [barns]')
plt.title('Ισότοπο $^{27}Al$ - TENDL 2019')

    # Add a legend
plt.legend(fontsize=12)

    # Show the plot
plt.grid(True)
plt.show()
