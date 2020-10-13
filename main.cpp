#include "solarsystem.h"
#include <iostream>

using namespace std;

int main(){


     int IntegrationPoints = 10000; // No. of integration points
     double FinalTime = 50.0;    // End time of calculation
     double TimeStep = FinalTime/((double) IntegrationPoints);

     // initial position x = 1AU, y = z = 0, vx = 2pi, vy=0, vz=0
     Planet Earth("earth",0.000003,1.,0.0,0.0,0.0,6.3,0.); // Earth: (mass,x,y,z,vx,vy,vz)
     Planet Sun("sun",1.,0.,0.,0.,0.,0.,0.);           // Sun: (mass,x,y,z,vx,vy,vz)

     SolarSystem sol(5.0);
     sol.add(Earth);
     sol.add(Sun);

     sol.VelocityVerlet(IntegrationPoints,FinalTime,0.);

    return 0;
}