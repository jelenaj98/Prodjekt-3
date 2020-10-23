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
    FILE * positionFile; //file for positions and velocities
    FILE * energyFile; //file for kinetic and potencial energies

    Position  initialPosition;
    string positionFilename, energyFilename;

    double x,y,z;
    double vx,vy,vz;
    double revolution;
    string name;
    double mass;

    double kinetic, potential;
    double energyLoss;

public:

    // Constructors
    Planet(string name, double M, double revolution, Position initialP);

    // Public functions
    void PrintPosition(double time, string method);
    void PrintEnergy(double time, string method);
    double GetMass() { return mass; }
    double GetRevolution() { return revolution; }
    double GetKinetic() { return kinetic; }
    bool Bound() { return (kinetic+potential < 0.0 ); }
    void Init();
    void SetPotential(double potential) { this->potential = potential; }
    double GetPotential() { return potential; }
    void CalculateVelocity(double parameter, double time_step, double Fx,double Fxnew,double Fy,double  Fynew,double  Fz,double  Fznew);
    void CalculateNewPosition(double time_step, double Fx, double Fy, double Fz);
    void GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz,double G, double epsilon);
    double PotentialEnergy(Planet &other, double G, double epsilon);
    void KineticEnergy();
    void MassCorrection(double total_mass);

private:
    // Private functions
    double Distance(Planet other);
    double Angular_momentum(Planet &other);
};

#endif // PLANET_H
