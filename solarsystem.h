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

    
public:
    // initializers
    SolarSystem();
    SolarSystem(double r);

    // functions
    void add(Planet newplanet);
    void VelocityVerlet(int integration_points, double final_time, double epsilon);


private:
    void Init();
    void PrintPositions(double time);
    void PrintEnergy(double time, double epsilon);
};

#endif // SOLARSYSTEM_H