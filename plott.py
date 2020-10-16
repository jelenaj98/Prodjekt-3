import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(6,6))
x,y,z = np.loadtxt("positions_1sun.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,"o", label ="Sola")
x,y,z = np.loadtxt("positions_1earth.txt", usecols=(1,2,3), unpack =True)
plt.plot(x,y,label="Jorda" )
plt.legend()
plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
plt.title("Sol-Jorda-systemet når \u03B2 = 2")
plt.show()
