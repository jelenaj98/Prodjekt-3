import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(6,6))
x,y,z = np.loadtxt("positions_1sun.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y, label ="Sola")
x,y,z = np.loadtxt("positions_1earth.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Jorda" )
x,y,z = np.loadtxt("positions_1Jupiter.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Jupiter" )

plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
#plt.title("Sol-Jorda-systemet når \u03B2 = 2")
plt.title("Solsystemet")

x,y,z = np.loadtxt("positions_1Mercury.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Mercury" )

x,y,z = np.loadtxt("positions_1Venus.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Venus" )

x,y,z = np.loadtxt("positions_1Mars.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Mars" )

x,y,z = np.loadtxt("positions_1Saturn.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Saturn" )

x,y,z = np.loadtxt("positions_1Uranus.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Uranus" )

x,y,z = np.loadtxt("positions_1Neptune.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Neptune" )

plt.legend()
plt.show()

"""
plt.figure(figsize=(6,6))
x,y,z = np.loadtxt("pherilion_positions_1sun.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,"o", label ="Sola")

x,y,z = np.loadtxt("pherilion_positions_1Mercury.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Mercury" )


#x,y,z = np.loadtxt("pherilion_positions_1earth.txt", usecols=(1,2,3), unpack =True)
#plt.plot(x,y,label="Jorda" )
#x,y,z = np.loadtxt("pherilion_positions_1Jupiter.txt", usecols=(1,2,3), unpack =True)
#plt.plot(x,y,label="Jupiter" )
plt.legend()
plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
#plt.title("Sol-Jorda-systemet når \u03B2 = 2")
plt.title("Sol-Jorda-Jupiter-systemet")
plt.show()
"""
