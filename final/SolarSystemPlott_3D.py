import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt

plt.figure(figsize=(15,15))


x,y,z = np.loadtxt("positions_Sun.txt", usecols=(1,2,3), unpack =True)
x1,y1,z1 = np.loadtxt("positions_Earth.txt", usecols=(1,2,3), unpack =True)
x2,y2,z2 = np.loadtxt("positions_Mercury.txt", usecols=(1,2,3), unpack =True)
x3,y3,z3 = np.loadtxt("positions_Venus.txt", usecols=(1,2,3), unpack =True)
x4,y4,z4 = np.loadtxt("positions_Mars.txt", usecols=(1,2,3), unpack =True)
x5,y5,z5 = np.loadtxt("positions_Jupiter.txt", usecols=(1,2,3), unpack =True)
x6,y6,z6 = np.loadtxt("positions_Saturn.txt", usecols=(1,2,3), unpack =True)
x7,y7,z7 = np.loadtxt("positions_Uranus.txt", usecols=(1,2,3), unpack =True)
x8,y8,z8 = np.loadtxt("positions_Neptune.txt", usecols=(1,2,3), unpack =True)

plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
   
ax = plt.axes(projection="3d")

ax.plot3D(x, y, z,label="Sun")
ax.plot3D(x1, y1, z1,label="Earth")
ax.plot3D(x2, y2, z2,label="Mercury")
ax.plot3D(x3, y3, z3,label="Venus")
ax.plot3D(x4, y4, z4,label="Mars")
ax.plot3D(x5, y5, z5,label="Jupiter")
ax.plot3D(x6, y6, z6,label="Saturn")
ax.plot3D(x7, y7, z7,label="Uranus")
ax.plot3D(x8, y8, z8,label="SolarSystem3Dne")

plt.legend()
plt.savefig('SolarSystem3D.png')
plt.show()
