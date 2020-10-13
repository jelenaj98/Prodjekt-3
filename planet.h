#ifndef PLANET_H
#define PLANET_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


class Planet
{
    FILE * posfile; //file for positions and velocities
    FILE * enefile; //file for kinetic and potencial energies


public:
    // Properties
    string name;
    double mass;
    double x,y,z;
    double vx,vy,vz;
    double potential;
    double kinetic;

    // Constructors
    Planet(string name, double M,double x,double y,double z,double vx, double vy,double vz);
    void PrintPosition(double time);
    void PrintEnergy(double time);


    // Functions
    double Distance(Planet other);
    void GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz,double G, double epsilon);
    void CalculateVelocity(double time_step, double ax,double axnew,double ay,double  aynew,double  az,double  aznew);
    void CalculateNewPosition(double time_step, double ax, double ay, double az);

    void KineticEnergy();
    double PotentialEnergy(Planet &other, double G, double epsilon);

};

#endif // PLANET_H