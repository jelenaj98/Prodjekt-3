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
    double r_old2;
    double r_old1;
    double r_new;
    double x_old2; double y_old2; double z_old2;
    double x_old1; double y_old1; double z_old1;
    double x_new; double y_new; double z_new;



    // Constructors
    Planet(string name, double M,double x,double y,double z,double vx, double vy,double vz);
    void PrintPosition(double time, double x, double y, double z);
    void PrintEnergy(double time);


    // Functions
    double Distance(Planet other);
    void GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz,double G, double epsilon,double time);
    void CalculateVelocity(double time_step, double ax,double axnew,double ay,double  aynew,double  az,double  aznew);
    void CalculateNewPosition(double time_step, double ax, double ay, double az);
    void Setperihhelon(Planet &other, double time);
    void Perihelion(Planet &other, double time);

    void KineticEnergy();
    double PotentialEnergy(Planet &other, double G, double epsilon);
    double Angular_momentum(Planet &other);

};

#endif // PLANET_H
