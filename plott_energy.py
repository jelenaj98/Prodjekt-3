import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(6,6))
tid,kin, pos = np.loadtxt("energy_earth.txt", usecols=(0,1,2), unpack =True)
plt.plot(tid,kin, label ="Kinetisk energi for jorda")
plt.plot(tid,pos, label ="Potensiell energi for jorda")
tot = kin+pos
plt.plot(tid,tot, label ="Total energi for jorda")
plt.legend()
plt.xlabel("Tid")
plt.ylabel("Energi")
plt.title("Energien til jorda når \u03B2 = 2.85")
plt.show()












"""
tid,kin,pos = np.loadtxt("energy_sun.txt", usecols=(0,1,2), unpack =True)

plt.plot(tid,kin, label ="Kinetisk energi for Sola")
plt.plot(tid,pos, label ="Potensiell energi for Sola")
tot = kin+pos
plt.plot(tid,tot, label ="Total energi for Sola")
plt.legend()
plt.xlabel("Tid")
plt.ylabel("Energi")
plt.title("Energien til Sola når \u03B2 = 2")
plt.show()
"""
