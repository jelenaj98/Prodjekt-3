import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt

methods = ["VelocityVerlet", "Euler"]
planets = ["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"]

for m in methods:
    plt.figure(figsize=(15,15))
    ax = plt.axes(projection="3d")
    ax.set_title("Solar system - " + m)
    ax.set_xlabel("x [AU]")
    ax.set_ylabel("y [AU]")
    ax.set_zlabel("z [AU]")

    for p in planets:
        x,y,z = np.loadtxt(p+"_Position_" + m + ".txt", usecols=(1,2,3), unpack =True)
        ax.plot3D(x, y, z,label=p)

    plt.legend()
    plt.savefig("SolarSystem3D_"+m+".png")

    fig_handle = plt.figure()  # Force a new figure instance to open(we will have two graphs)
    plt.show()