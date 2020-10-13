#include "planet.h"


Planet::Planet(string name,double M,double x,double y,double z,double vx, double vy,double vz){
    this->name = name;
    mass = M;
    this->x=x;
    this->y=y;
    this->z=z;
    this->vx=vx;
    this->vy=vy;
    this->vz=vz;
    potential = 0;
    kinetic = 0;

    string filename = "positions_1" + name + ".txt";
    posfile = fopen(filename.c_str(),"w");

    filename = "energy_" + name + ".txt";
    enefile = fopen(filename.c_str(),"w");
}

double Planet::Distance(Planet other)
{
    double xx = x-other.x;
    double yy = y-other.y;
    double zz = z-other.z;

    return sqrt(xx*xx + yy*yy + zz*zz);
}


void Planet::PrintPosition(double time)
{   // Writes time, position and velocity to a file "output"
    fprintf(posfile,"%15.8lf", time);
    fprintf(posfile,"%15.8f", x);
    fprintf(posfile,"%15.8f", y);
    fprintf(posfile,"%15.8f", z);
    fprintf(posfile,"%15.8f", vx);
    fprintf(posfile,"%15.8f", vy);
    fprintf(posfile,"%15.8f\n", vz);
}

void Planet::PrintEnergy(double time)
{   // Writes time, position and velocity to a file "output"
    fprintf(enefile,"%15.8lf", time);
    fprintf(enefile,"%15.8f", kinetic);
    fprintf(enefile,"%15.8f\n", potential);
}

void Planet::GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz,double G, double epsilon)
{   // Function that calculates the gravitational force between two objects, component by component.

    // Calculate relative distance between current planet and all other planets
    double rx = x - other.x;
    double ry = y - other.y;
    double rz = z - other.z;

    double r = Distance(other);
    double smoothing = epsilon*epsilon*epsilon;

    // Calculate the forces in each direction
    Fx -= G*mass*other.mass*rx/((r*r*r) + smoothing);
    Fy -= G*mass*other.mass*ry/((r*r*r) + smoothing);
    Fz -= G*mass*other.mass*rz/((r*r*r) + smoothing);
}

void Planet::CalculateNewPosition(double time_step, double ax, double ay, double az) {
    x += vx*time_step + 0.5*time_step*time_step*ax;
    y += vy*time_step + 0.5*time_step*time_step*ay;
    z += vz*time_step + 0.5*time_step*time_step*az;
}

void Planet::CalculateVelocity(double time_step, double ax,double axnew,double ay,double  aynew,double  az,double  aznew) {
    vx += 0.5*time_step*(ax + axnew);
    vy += 0.5*time_step*(ax + aynew);
    vz += 0.5*time_step*(ax + aznew);
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