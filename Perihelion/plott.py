import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

jord_og_sol = False
tre_legemer= False
solsystem = False
perihelion= True



if jord_og_sol:
    plt.figure(figsize=(6,6))
    x,y,z = np.loadtxt("positions_1sun.txt", usecols=(1,2,3), unpack =True)
    plt.plot(x,y, label ="Sola")
    x,y,z = np.loadtxt("positions_1earth.txt", usecols=(1,2,3), unpack =True)
    plt.plot(x,y,label="Jorda" )
    plt.xlabel("x [AU]")
    plt.ylabel("y [AU]")
    #plt.title("Sol-Jorda-systemet når \u03B2 = 2")
    plt.title("Jorda og Sola")
    plt.legend()
    plt.show()


if tre_legemer:
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
    plt.title("Jorda, Sola og Jupiter")
    plt.legend()
    plt.show()

if solsystem:
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

if perihelion:
    plt.figure(figsize=(6,6))
    tid, x,y,z = np.loadtxt("pherilion_position.txt", usecols=(0,1,2,3), unpack =True)
    tid1, x1,y1,z1 = np.loadtxt("uten_pherilion_position.txt", usecols=(0,1,2,3), unpack =True)

    theta = np.arctan(y/x)*3600 #arcsec
    theta1 = np.arctan(y1/x1)*3600 #arcsec
    print_theta = theta-theta1
    plt.plot(tid, print_theta)
    #plt.plot(tid, theta)
    #plt.plot(tid1, theta1)
    plt.title("Perihelionvinkel")
    plt.xlabel("Tid [år]")
    plt.ylabel("Theta")
    plt.show()


    #ax = plt.axes(projection="3d")



    plt.figure(figsize=(6,6))
    x,y,z = np.loadtxt("positions_1sun.txt", usecols=(1,2,3), unpack =True)
    plt.plot(x,y, label ="Sola")
    #ax.plot3D(x, y, z,label="Sun")

    x,y,z = np.loadtxt("positions_1Mercury.txt", usecols=(1,2,3), unpack =True)
    plt.plot(x,y,label="Mercury" )
    #ax.plot3D(x, y, z,label="Mercury")

    plt.legend()
    plt.xlabel("x [AU]")
    plt.ylabel("y [AU]")
    #plt.title("Sol-Jorda-systemet når \u03B2 = 2")
    plt.title("Sol og Merkur")
    #plt.show()
