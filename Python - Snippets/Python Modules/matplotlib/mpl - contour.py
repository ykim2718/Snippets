"""
y, 2025.1.19
mpl - contour.py
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import scipy.interpolate as si

# Sample data creation
data = {
    'x': [1, 2, 3, 1, 2, 3, 1, 2, 3],
    'y': [1, 1, 1, 2, 2, 2, 3, 3, 3],
    'z': [5, 3, 2, 6, 5, 4, 7, 6, 5]
}

# Create DataFrame
df = pd.DataFrame(data)

if False:
    # Pivot the DataFrame to create a grid of z values
    Z = df.pivot(index='y', columns='x', values='z').values

    # Get unique x and y values
    x_unique = df['x'].unique()
    y_unique = df['y'].unique()

    # Create a meshgrid for x and y values
    X, Y = np.meshgrid(x_unique, y_unique)

else:
    xlim = df.x.min(), df.x.max()
    ylim = df.y.min(), df.y.max()
    grid_count = 20
    x = df.x.values
    y = df.y.values
    z = df.z.values
    X = np.linspace(xlim[0], xlim[1], grid_count)
    Y = np.linspace(ylim[0], ylim[1], grid_count)
    Z = si.griddata((x, y), z, (X[None, :], Y[:, None]), method='cubic')

# Create the contour plot
fig, ax1 = plt.subplots()
contour = ax1.contour(X, Y, Z)

# Add labels and color bar
ax1.set_xlabel("X-axis")
ax1.set_ylabel("Y-axis")
ax1.set_title("Contour Plot")
plt.colorbar(contour)
plt.show()

