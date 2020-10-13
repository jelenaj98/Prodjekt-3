#include "solarsystem.h"
#include "planet.h"
#include <iostream>
#include <cmath>
#include "time.h"

void SolarSystem::Init() {
    total_planets = 0;
    radius = 100;
    total_mass = 0;
    G = 4*M_PI*M_PI;
    totalKinetic = 0;
    totalPotential = 0;
}

SolarSystem::SolarSystem()
{
    Init();
}

SolarSystem::SolarSystem(double r)
{
    Init();
    radius = r;
}

void SolarSystem::add(Planet newPlanet)
{
    total_planets += 1;
    total_mass += newPlanet.mass;
    all_planets.push_back(newPlanet);
}

void SolarSystem::PrintPositions(double time)
{   // Writes mass, position and velocity to a file "output"
    for(int i=0;i<total_planets;i++){
        all_planets[i].PrintPosition(time);
    }
}

void  SolarSystem::PrintEnergy(double time,double epsilon)
{   // Writes energies to a file "output"

    for(int i=0;i<total_planets;i++){
        all_planets[i].potential = 0;
    }

    for(int i=0;i<total_planets;i++){
        Planet &current = all_planets[i];
        all_planets[i].KineticEnergy();

        for(int j=i+1;j<total_planets;j++){
            Planet &other = all_planets[j];
            current.potential += current.PotentialEnergy(other,G,epsilon);
            other.potential += other.PotentialEnergy(current,G,epsilon);
        }
    }

    for(int i=0;i<total_planets;i++){
        all_planets[i].PrintEnergy(time);
    }
}

void SolarSystem::VelocityVerlet(int integration_points, double final_time, double epsilon)
{   /*  Velocity-Verlet solver for two coupeled ODEs.
    The algorithm is, exemplified in 1D for position x(t), velocity v(t) and acceleration a(t):
    x(t+dt) = x(t) + v(t)*dt + 0.5*dt*dt*a(t);
    v(t+dt) = v(t) + 0.5*dt*[a(t) + a(t+dt)];*/

    // Define time step
    double time_step = final_time/((double) integration_points);
    double time = 0.0;
    double loss = 0.; // Possible energy loss

    //initialize accelerations
    double ax,ay,az,axnew,aynew,aznew;

    // Initialize forces
    double Fx,Fy,Fz,Fxnew,Fynew,Fznew;

    // Write initial values to file
    PrintPositions(time);

    // Set up clock to measure the time usage
    clock_t planet_VV,finish_VV;
    planet_VV = clock();

    // PLANET CALCULATIONS
    // Loop over time
    time += time_step;
    while(time < final_time){

        // Loop over all planets
        for(int i=0; i<total_planets; i++){
            Planet &current = all_planets[i]; // Current planet we are looking at

            Fx = Fy = Fz = Fxnew = Fynew = Fznew = 0.0; // Reset forces before each run

            // Calculate forces in each dimension
            for(int j=i+1; j<total_planets; j++){
                Planet &other = all_planets[j];
                current.GravitationalForce(other,Fx,Fy,Fz,G,epsilon);
             }

            // Acceleration in each dimension for current planet
            ax = Fx/current.mass;
            ay = Fy/current.mass;
            az = Fz/current.mass;

            // Calculate new position for current planet
            current.CalculateNewPosition(time_step,ax,ay,az);

            // Calculate forces for new positions
            Fx = Fy = Fz = 0;
            for(int j=i+1; j<total_planets; j++){
                Planet &other = all_planets[j];
                current.GravitationalForce(other,Fx,Fy,Fz,G,epsilon);
            }

            // Acceleration each dimension exerted for current planet
            axnew = Fx/current.mass;
            aynew = Fy/current.mass;
            aznew = Fz/current.mass;

            // Calculate new velocity for current planet
            current.CalculateVelocity(time_step, ax,axnew,ay,aynew,az,aznew);
        }

        // print position and velocity for the given time
        PrintPositions(time);
        // print kinetic and potential energy for a given time
        PrintEnergy(time,epsilon);

        time += time_step;
    }
}


