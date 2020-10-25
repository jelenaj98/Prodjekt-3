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
    maxRevolution = 0;
    energyLoss = 0;
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
    total_mass += newPlanet.GetMass();
    if(newPlanet.GetRevolution() > maxRevolution) {
        maxRevolution = newPlanet.GetRevolution();
    }
    all_planets.push_back(newPlanet);
}

void SolarSystem::PrintPositions(double time, string method)
{   // Writes mass, position and velocity to a file "output"
    for(int i=0;i<total_planets;i++){
        all_planets[i].PrintPosition(time,method);
    }
}

//korigerer for massesenteret
void SolarSystem::baycentric()
{
 for(int i = 0; i<total_planets;i++){
    all_planets[i].MassCorrection(total_mass);
  }
}

// reset all Planet parameters to initial valus
void SolarSystem::ResetPlanetParameters() {
    for(int i=0; i<total_planets; i++){
        all_planets[i].Init();
    }

    energyLoss = 0;
}

// Writes energies to a file "output"
void  SolarSystem::PrintEnergy(double time,double epsilon, string method)
{
    for(int i=0;i<total_planets;i++){
        all_planets[i].SetPotential(0.0);
    }

    for(int i=0;i<total_planets;i++){
        Planet &current = all_planets[i];
        all_planets[i].KineticEnergy();

        for(int j=0;j<total_planets;j++){
          if(j!=i){
            Planet &other = all_planets[j];
            current.SetPotential(current.GetPotential() + current.PotentialEnergy(other,G,epsilon));
            other.SetPotential(other.GetPotential() + other.PotentialEnergy(current,G,epsilon));
          }
        }
    }

    for(int i=0;i<total_planets;i++){
        all_planets[i].PrintEnergy(time,method);
    }
}

// calculate Energy lost for condition (kinetic + potential > 0)
void SolarSystem::EnergyLoss() {
    for(int i;i < total_planets;i++) {
        if(!all_planets[i].Bound()) {
            energyLoss += all_planets[i].GetKinetic();
        }
    }
}


void SolarSystem::VelocityVerlet(int integration_points, double epsilon)
{   /*  Velocity-Verlet solver for two coupeled ODEs.
    The algorithm is, exemplified in 1D for position x(t), velocity v(t) and acceleration a(t):
    x(t+dt) = x(t) + v(t)*dt + 0.5*dt*dt*a(t);
    v(t+dt) = v(t) + 0.5*dt*[a(t) + a(t+dt)];*/

    // Reset planet parameters to initil values - in a case that Euler method is called first
    ResetPlanetParameters();

    // Define time step - automatic calculation for planet with max revolution
    double time_step = maxRevolution/((double) integration_points);
    double time = 0.0;
    double loss = 0.; // Possible energy loss
    string method = "VelocityVerlet";

    // Initialize forces
    double Fx,Fy,Fz,Fxnew,Fynew,Fznew;

    // Write initial values to file
    PrintPositions(time,method);

    // PLANET CALCULATIONS
    // Loop over time
    while(time < maxRevolution){
        // Loop over all planets
        for(int i=0; i<total_planets; i++){
            Planet &current = all_planets[i]; // Current planet we are looking at

            Fx = Fy = Fz = 0.0; // Reset forces before each run

            // Calculate forces in each dimension
            for(int j=0; j<total_planets; j++){
              if(j != i){
                Planet &other = all_planets[j];
                current.GravitationalForce(other,Fx,Fy,Fz,G,epsilon);
             }
           }

            // Calculate new position for current planet
            current.CalculateNewPosition(time_step,Fx,Fy,Fz);

            // Calculate forces for new positions
            Fxnew = Fynew = Fznew = 0;
            for(int j=0; j<total_planets; j++){
              if(j != i){
                Planet &other = all_planets[j];
                current.GravitationalForce(other,Fxnew,Fynew,Fznew,G,epsilon);

            }
          }

           // Calculate new velocity for current planet
           current.CalculateVelocity(0.5,time_step,Fx, Fxnew, Fy, Fynew, Fz, Fznew);
        }

        // print position and velocity for the given time
        PrintPositions(time,method);
        // print kinetic and potential energy for a given time
        PrintEnergy(time,epsilon,method);

        // calculate total energy loss
        EnergyLoss();

        time += time_step;
    }

    PrintEnergyLoss(method);
}


void SolarSystem::Euler(int integration_points, double epsilon)
{
    /*  Velocity-Verlet solver for two coupeled ODEs.
    The algorithm is, exemplified in 1D for position x(t), velocity v(t) and acceleration a(t):
    x(t+dt) = x(t) + v(t)*dt + 0.5*dt*dt*a(t);
    v(t+dt) = v(t) + 0.5*dt*[a(t) + a(t+dt)];*/

    // Reset planet parameters to initil values - in a case that VelocityVerlet method is called first
    ResetPlanetParameters();

    // Define time step - automatic calculation for planet with max revolution
    double time_step = maxRevolution/((double) integration_points);
    string method = "Euler";
    double time = 0.0;
    double loss = 0.; // Possible energy loss

    // Initialize forces
    double Fx,Fy,Fz,Fxnew,Fynew,Fznew;

    // Write initial values to file
    PrintPositions(time,method);
    while(time < maxRevolution){

        // Loop over all planets
        for(int i=0; i<total_planets; i++){
            Planet &current = all_planets[i]; // Current planet we are looking at

            double Fx =0.0, Fy = 0.0, Fz = 0.0; // Reset forces before each run

            // Calculate forces in each dimension
            for(int j=0; j<total_planets; j++){
                if(j != i){
                    Planet &other = all_planets[j];
                    current.GravitationalForce(other,Fx,Fy,Fz,G,epsilon);
                }
            }

            // Calculate new velocity for current planet
            current.CalculateVelocity(1, time_step,Fx, 0, Fy, 0, Fz, 0);


            // Calculate new position for current planet
            // For Euler method x(i+1) = xi + h*v(i+1)
            // v(i+1+) was calculated in a previous step
            current.CalculateNewPosition(time_step, 0, 0, 0);
        }

        // print position and velocity for the given time
        PrintPositions(time,method);

        // print kinetic and potential energy for a given time
         PrintEnergy(time,epsilon,method);

        // calculate total energy loss
        EnergyLoss();

        time += time_step;
    }

    PrintEnergyLoss(method);
}