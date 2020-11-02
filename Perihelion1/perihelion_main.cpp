#include "perihelion_solarsystem.h"
#include <iostream>

using namespace std;

int main(){


     int IntegrationPoints = 156250000; // No. of integration points
     double FinalTime = 100;    // End time of calculation
     double TimeStep = FinalTime/((double) IntegrationPoints);

     // initial position x = 1AU, y = z = 0, vx = 2pi, vy=0, vz=0
     //Planet Earth("earth",0.000003,1.,0.0,0.0,0.0,6.3,0.); // Earth: (mass,x,y,z,vx,vy,vz)
     //Planet Earth("earth",0.000003,1.,0.0,0.0,0.0,6.3,0.); // Earth: (mass,x,y,z,vx,vy,vz)
     //Planet Jupiter("Jupiter", 0.0009543,2.498448739730900E+00,-4.465376195677621E+00,-3.737360937699062E-02,6.492384890941658E-03*365, 4.042682241018491E-03*365,-1.620109807189240E-04*356);
     Planet Mercury("Mercury",0.0000001651,  0.3075,0,0, 0, 12.44,0);
     Planet Sun("sun",1.,0.,0.,0.,0.,0.,0.);           // Sun: (mass,x,y,z,vx,vy,vz)




     SolarSystem sol(5.0);
     //sol.add(Earth);
    // sol.add(Jupiter);
     sol.add(Mercury);
     sol.add(Sun);
     sol.baycentric();

     sol.VelocityVerlet(IntegrationPoints,FinalTime,0.);

    return 0;
}
