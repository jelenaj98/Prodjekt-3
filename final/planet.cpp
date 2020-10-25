#include "planet.h"
bool OPPGAVE_E = false;

Planet::Planet(string name,double mass,double revolution, Position initPosition)
{
    this->name = name;
    this->mass = mass;
    this->revolution = revolution;

   // remember initial positions and velocities
    initialPosition = initPosition;

    Init();

    positionFilename = name + "_Position_"; // example: Earth_position_Euler.txt
    energyFilename = name + "_Energy_";
}

void Planet::Init()
{
    x = initialPosition.x;
    y = initialPosition.y;
    z = initialPosition.z;
    vx = initialPosition.vx*365;
    vy = initialPosition.vy*365;
    vz = initialPosition.vz*365;
    potential = 0;
    kinetic = 0;

    positionFile = NULL;
    energyFile = NULL;
}

double Planet::Distance(Planet other)
{
    double xx = x-other.x;
    double yy = y-other.y;
    double zz = z-other.z;

    return sqrt(xx*xx + yy*yy + zz*zz);
}

void Planet::MassCorrection(double total_mass)
{
    x -= (x*mass/total_mass);
    y -= (y*mass/total_mass);
    z -= (z*mass/total_mass);
    vx -= (vx*mass/total_mass);
    vy -= (vy*mass/total_mass);
    vz -= (vz*mass/total_mass);
}

// Writes time, position and velocity to a file "output"
void Planet::PrintPosition(double time, string method)
{
    if(positionFile == NULL) {
        string filename = positionFilename + method + ".txt";
        positionFile = fopen(filename.c_str(),"w");
    }
    // It means that we do not need to print in a file more positions than one revolution - enough for plot
    // Example. Pluto revolution is 248.59 years, and without this condition, we will have 248.59 plots of Earth
    if(time <= revolution) {
        fprintf(positionFile,"%15.8lf", time);
        fprintf(positionFile,"%15.8f", x);
        fprintf(positionFile,"%15.8f", y);
        fprintf(positionFile,"%15.8f", z);
        fprintf(positionFile,"%15.8f", vx);
        fprintf(positionFile,"%15.8f", vy);
        fprintf(positionFile,"%15.8f\n", vz);
    }
}

void Planet::PrintEnergy(double time, string method)
{
    if(energyFile == NULL) {
        string filename = energyFilename + method + ".txt";
        energyFile = fopen(filename.c_str(),"w");
    }

    if(time <= revolution*5) {
        // Writes time, position and velocity to a file "output"
        fprintf(energyFile,"%15.8lf", time);
        fprintf(energyFile,"%15.8f", kinetic);
        fprintf(energyFile,"%15.8f\n", potential);
    }
}

void Planet::GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz, double G, double epsilon)
{   // Function that calculates the gravitational force between two objects, component by component.

    // Calculate relative distance between current planet and all other planets
    double rx = x - other.x;
    double ry = y - other.y;
    double rz = z - other.z;

    double r = Distance(other);

    double smoothing = epsilon*epsilon*epsilon;

    // Calculate the forces in each direction
    if (OPPGAVE_E){
      Fx -= G*mass*other.mass*rx/((pow(r,3.85)) + smoothing);
      Fy -= G*mass*other.mass*ry/((pow(r,3.85)) + smoothing);
      Fz -= G*mass*other.mass*rz/((pow(r,3.85)) + smoothing);

    }else{
      Fx -= G*mass*other.mass*rx/((r*r*r) + smoothing);
      Fy -= G*mass*other.mass*ry/((r*r*r) + smoothing);
      Fz -= G*mass*other.mass*rz/((r*r*r) + smoothing);
    }
}

void Planet::CalculateNewPosition(double time_step, double Fx, double Fy, double Fz) {
    x += vx*time_step + 0.5*time_step*time_step*Fx/mass;
    y += vy*time_step + 0.5*time_step*time_step*Fy/mass;
    z += vz*time_step + 0.5*time_step*time_step*Fz/mass;
}

// parameter = 0.5 VelocityVerlet
// parameter = 1 - Euler
void Planet::CalculateVelocity(double parameter, double time_step, double Fx,double Fxnew,double Fy,double  Fynew,double  Fz,double  Fznew) {
    vx += parameter*time_step*(Fx + Fxnew)/mass;
    vy += parameter*time_step*(Fy + Fynew)/mass;
    vz += parameter*time_step*(Fz + Fznew)/mass;
}

void Planet::KineticEnergy()
{
    kinetic = 0.5*mass*(vx*vx + vy*vy + vz*vz);
}

double Planet::PotentialEnergy(Planet &other, double G, double epsilon)
{
    if(epsilon==0.0)
        return -G*mass*other.mass/Distance(other);
    else
        return (G*mass*other.mass/epsilon)*(atan(Distance(other)/epsilon) - (0.5*M_PI));
}

//Regner ut angulærmonent
double Planet::Angular_momentum(Planet &other){

  return mass*(vx*vx + vy*vy + vz*vz)*Distance(other);

}
