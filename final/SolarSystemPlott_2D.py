import numpy as np
import matplotlib.pyplot as plt

methods = ["VelocityVerlet", "Euler"]
planets = ["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"]

for m in methods:
    plt.figure(figsize=(15,15))
    plt.xlabel("x [AU]")
    plt.ylabel("y [AU]")
    plt.title("Solar System - " + m)
        
    for p in planets:
        x,y,z = np.loadtxt(p+"_Position_" + m + ".txt", usecols=(1,2,3), unpack =True)
        plt.plot(x,y, label = p)
    
    plt.legend()
    plt.savefig("SolarSystem2D_" + m + ".png")
    
    fig_handle = plt.figure()  # Force a new figure instance to open(we will have two graphs)
    plt.show()
