import numpy as np
import matplotlib.pyplot as plt

planets = ["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"]

for p in planets:
    fig, (ax1, ax2) = plt.subplots(1, 2, sharey='row',figsize=(10,5))
    method = "Euler"
    tid,kin, pos = np.loadtxt(p+"_Energy_" + method + ".txt", usecols=(0,1,2), unpack =True)
    ax1.plot(tid,kin, label ="Kinetic")
    ax1.plot(tid,pos, label ="Potential")
    tot = kin+pos
    ax1.plot(tid,tot, label ="Total")
    ax1.set_title("Energy for " + p + " - " + method)
    ax1.set(xlabel='Time (years)', ylabel='y label')
    
    method = "VelocityVerlet"
    tid,kin, pos = np.loadtxt(p+"_Energy_" + method + ".txt", usecols=(0,1,2), unpack =True)
    ax2.plot(tid,kin, label ="Kinetic")
    ax2.plot(tid,pos, label ="Potential")
    tot = kin+pos
    ax2.plot(tid,tot, label ="Total")
    ax2.set_title("Energy for " + p + " - " + method)
    plt.savefig("Energy"+p+".png")    
    fig_handle = plt.figure()  # Force a new figure instance to open(we will have two graphs)
    
    ax2.set(xlabel='Time (years)')
    plt.show()