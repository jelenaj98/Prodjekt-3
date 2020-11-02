#include "perihelion_solarsystem.h"
#include "perihelion_planet.h"
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

void SolarSystem::PrintPositions1(double time)
{   // Writes mass, position and velocity to a file "output"
    for(int i=0;i<total_planets;i++){
        all_planets[i].PrintPosition(time);
    }
}
void SolarSystem::baycentric(){
//korigerer for massesenteret

  double x_verdi = 0;
  double y_verdi = 0;
  double z_verdi = 0;
  double vx_verdi = 0;
  double vy_verdi = 0;
  double vz_verdi = 0;
  //double M = 0;


for(int i = 0; i<total_planets;i++){
  Planet& current = all_planets[i];
  x_verdi += current.x * current.mass;
  y_verdi += current.y * current.mass;
  z_verdi += current.z * current.mass;
  vx_verdi += current.vx * current.mass;
  vy_verdi += current.vy * current.mass;
  vz_verdi += current.vz * current.mass;
  //M += m(i);

  }
  x_verdi /= total_mass;
  y_verdi /= total_mass;
  z_verdi /= total_mass;
  vx_verdi /= total_mass;
  vy_verdi /= total_mass;
  vz_verdi /= total_mass;

  for(int i = 0; i<total_planets;i++){
    Planet& current = all_planets[i];
    current.x -= x_verdi;
    current.y -= y_verdi;
    current.z -= z_verdi;
    current.vx -= vx_verdi;
    current.vy -= vy_verdi;
    current.vz -= vz_verdi;
}


}

void  SolarSystem::PrintEnergy1(double time,double epsilon)
{   // Writes energies to a file "output"

    for(int i=0;i<total_planets;i++){
        all_planets[i].potential = 0;
    }

    for(int i=0;i<total_planets;i++){
        Planet &current = all_planets[i];
        all_planets[i].KineticEnergy();

        for(int j=0;j<total_planets;j++){
          if(j!=i){
            Planet &other = all_planets[j];
            current.potential += current.PotentialEnergy(other,G,epsilon);
            other.potential += other.PotentialEnergy(current,G,epsilon);


        }}
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
    PrintPositions1(time);

    // Set up clock to measure the time usage
    clock_t planet_VV,finish_VV;
    planet_VV = clock();

    // PLANET CALCULATIONS
    // Loop over time
    //time += time_step;

  for(int i=0; i<total_planets; i++){
    Planet &current = all_planets[i];
    if (current.name =="Mercury"){
    for(int j=0; j<total_planets; j++){
      if(j != i){
        Planet &other = all_planets[j];
        current.Setperihhelon(other, time);
     }
   }}}


    while(time < final_time){

      //std::cout << "Time: " << time<< '\n';
        // Loop over all planets
        for(int i=0; i<total_planets; i++){
            Planet &current = all_planets[i]; // Current planet we are looking at
            //std::cout << "navn: "<< current.name << '\n';
            //std::cout << "pos: " <<current.x << "  "<< current.y << "  "<<current.z<< '\n';

            //std::cout << "fart: "<<current.vx << "  "<< current.vy << "  "<<current.vz<< '\n';
            //std::cout << " " << '\n';
            Fx = Fy = Fz = Fxnew = Fynew = Fznew = 0.0; // Reset forces before each run
            ax = ay = az = axnew = aynew = aznew = 0.0;
            //std::cout << "kraf: "<<Fx << "  "<< Fy << "  "<<Fz<< '\n';

            // Calculate forces in each dimension
            for(int j=0; j<total_planets; j++){
              if(j != i){
                Planet &other = all_planets[j];
                current.GravitationalForce(other,Fx,Fy,Fz,G,epsilon,time);
             }
           }
            // Acceleration in each dimension for current planet
            ax = Fx/current.mass;
            ay = Fy/current.mass;
            az = Fz/current.mass;
            

            // Calculate new position for current planet
            current.CalculateNewPosition(time_step,ax,ay,az);


            // Calculate forces for new positions
            Fx = Fy = Fz = 0;
            for(int j=0; j<total_planets; j++){
              if(j != i){
                Planet &other = all_planets[j];
                current.GravitationalForce(other,Fx,Fy,Fz,G,epsilon, time);
                if (current.name =="Mercury"){
                  current.Perihelion(other, time);

                }


            }
          }
            // Acceleration each dimension exerted for current planet
            axnew = Fx/current.mass;
            aynew = Fy/current.mass;
            aznew = Fz/current.mass;

            // Calculate new velocity for current planet
            current.CalculateVelocity(time_step, ax,axnew,ay,aynew,az,aznew);
            //std::cout << az << '\n';
            //std::cout << aznew << '\n';
            //std::cout << current.vz << '\n';
            //std::cout << "" << '\n';


            /*
            //Calculation the total energy for earth, and checing if its conserved.
            if (i == 0){
            for(int j=0; j<total_planets; j++){
              if(j != i){
                Planet &other = all_planets[j];
                double total_energy = current.kinetic + current.PotentialEnergy(other, G, epsilon);
                double angularmomentum =  current.Angular_momentum(other);
                std::cout << "Navn: " <<current.name<< '\n';
                std::cout << "Total energy: "<< total_energy << '\n';
                std::cout << "Angulærmoment: " <<angularmomentum << '\n';

              }
            }}
            */
        }

        // print position and velocity for the given time

        PrintPositions1(time);
        // print kinetic and potential energy for a given time
        //PrintEnergy1(time,epsilon);

        time += time_step;






    }


}
