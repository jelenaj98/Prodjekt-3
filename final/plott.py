import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(6,6))
x,y,z = np.loadtxt("positions_Sun.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y, label ="Sola")

x,y,z = np.loadtxt("positions_Earth.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Earth" )

x,y,z = np.loadtxt("positions_Mercury.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Mercury" )

x,y,z = np.loadtxt("positions_Venus.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Venus" )

x,y,z = np.loadtxt("positions_Mars.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Mars" )

x,y,z = np.loadtxt("positions_Jupiter.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Jupiter" )

x,y,z = np.loadtxt("positions_Saturn.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Saturn" )

x,y,z = np.loadtxt("positions_Uranus.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Uranus" )

x,y,z = np.loadtxt("positions_Neptune.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Neptune" )

plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
plt.title("Solsystemet")

plt.legend()
plt.show()
