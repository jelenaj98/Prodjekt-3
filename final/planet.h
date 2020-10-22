#ifndef PLANET_H
#define PLANET_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

typedef struct Position{
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
} Position;


class Planet
{
// Properties
    FILE * posfile; //file for positions and velocities
    FILE * enefile; //file for kinetic and potencial energies
    double x,y,z;
    double vx,vy,vz;
    double revolution;
    string name;
    double mass;

    Position initialPosition;

    double kinetic;

public:
     double potential;
    // Constructors
    Planet(string name, double M, double revolution, Position initialP);
    void PrintPosition(double time);
    void PrintEnergy(double time);
    double GetMass() { return mass; }
    double GetRevolution() { return revolution; }


    // Functions
    double Distance(Planet other);
    void GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz,double G, double epsilon);
    void CalculateVelocity(double time_step, double Fx,double Fxnew,double Fy,double  Fynew,double  Fz,double  Fznew);
    void CalculateNewPosition(double time_step, double Fx, double Fy, double Fz);

    void KineticEnergy();
    double PotentialEnergy(Planet &other, double G, double epsilon);
    double Angular_momentum(Planet &other);
    void MassCorrection(double total_mass);

  private:
    void Init();

};

#endif // PLANET_H
