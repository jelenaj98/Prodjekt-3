#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include "planet.h"
#include <vector>
#include <fstream>
using std::vector;

class SolarSystem
{
    // properties
    double radius;
    double G; //GravitationalConstant
    int total_planets;
    vector<Planet> all_planets;

    double total_mass; //Mass of all planets
    double totalKinetic;
    double totalPotential;

// max revolution of all planets in the system
    double maxRevolution;
    double energyLoss;


public:
    // initializers
    SolarSystem();
    SolarSystem(double r);

    // functions
    void add(Planet newplanet);
    void baycentric();
    void VelocityVerlet(int integration_points, double epsilon);
    void Euler(int integration_points, double epsilon);
    void PrintEnergyLoss(string method) { cout << "Total energyloss due to unbound planets (method " << method << "): " << energyLoss << endl; }


private:
    void Init();
    void PrintPositions(double time,string method);
    void PrintEnergy(double time, double epsilon, string method);
    void EnergyLoss();
    void ResetPlanetParameters();
};

#endif // SOLARSYSTEM_H
