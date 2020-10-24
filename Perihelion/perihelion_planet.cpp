#include "perihelion_planet.h"


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
    double r_old2 =0;
    double r_old1 =0;
    double r_new = 0;
    double x_old2; double y_old2; double z_old2;
    double x_old1; double y_old1; double z_old1;
    double x_new; double y_new; double z_new;




    string filename = "positions_1" + name + ".txt";
    posfile = fopen(filename.c_str(),"w");

    filename = "energy_" + name + ".txt";
    enefile = fopen(filename.c_str(),"w");


    bool perihelion = false;
    if (perihelion){


    filename = "pherilion_position.txt";
    perifile = fopen(filename.c_str(),"w");
    }else{
    filename = "uten_pherilion_position.txt";
    perifile2 = fopen(filename.c_str(),"w");
    }
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

void Planet::PrintPerihelion(double time, double x, double y, double z)
{   // Writes time, position and velocity to a file "output"

    bool perihelion=false;

    if (perihelion){
    fprintf(perifile,"%15.8lf", time);
    fprintf(perifile,"%15.8f", x);
    fprintf(perifile,"%15.8f", y);
    fprintf(perifile,"%15.8f\n", z);
    //fprintf(posfile,"%15.8f", vx);
    //fprintf(posfile,"%15.8f", vy);
    //fprintf(posfile,"%15.8f\n", vz);
  }else{
    fprintf(perifile2,"%15.8lf", time);
    fprintf(perifile2,"%15.8f", x);
    fprintf(perifile2,"%15.8f", y);
    fprintf(perifile2,"%15.8f\n", z);



  }
}

void Planet::PrintEnergy(double time)
{   // Writes time, position and velocity to a file "output"
    fprintf(enefile,"%15.8lf", time);
    fprintf(enefile,"%15.8f", kinetic);
    fprintf(enefile,"%15.8f\n", potential);

}

void Planet::Setperihhelon(Planet &other, double time){
  double r = Distance(other);
  r_old2 =r;
  x_old2 = x; y_old2 = y; z_old2 =z;
  r_old1 =r;
  x_old1 = x; y_old1 = y; z_old1 =z;
  r_new = r;
  x_new = x; y_new = y; z_new =z;

  std::cout << name << '\n';
  std::cout << r_old2<<"   "<<r_old1<<"   "<<r_new << '\n';
}


void Planet::Perihelion(Planet &other, double time){
  double r = Distance(other);
  r_old2 =r_old1;
  x_old2 = x_old1; y_old2 = y_old1; z_old2 =z_old1;
  r_old1 =r_new;
  x_old1 = x_new; y_old1 = y_new; z_old1 =z_new;
  r_new = r;
  x_new = x; y_new = y; z_new =z;

  //std::cout << r_old2<<"   "<<r_old1<<"   "<<r_new << '\n';

  if ((r_old2 > r_old1) && (r_old1< r_new)){
    //std::cout << r_old2<<"   "<<r_old1<<"   "<<r_new << '\n';
    //std::cout << x_old2<<"   " <<x_old1<<"   "<< x_new<<'\n';
    PrintPerihelion(time, x_old1, y_old1, z_old1);

  }

}




void Planet::GravitationalForce(Planet &other,double &Fx,double &Fy,double &Fz, double G, double epsilon, double time)
{   // Function that calculates the gravitational force between two objects, component by component.

    // Calculate relative distance between current planet and all other planets
    double rx = x - other.x;
    double ry = y - other.y;
    double rz = z - other.z;

    double r = Distance(other);


    //std::cout << "r: " <<r<< '\n';
    //std::cout << "masse: " << mass<<'\n';
    //std::cout << "masse 2: " << other.mass<< '\n';
    double smoothing = epsilon*epsilon*epsilon;
    //double smoothing = 0;
    // Calculate the forces in each direction
      bool perihelion= false;
      if (perihelion){
      double c = 63241.1; // AU/yr
      double lx= ry*vz -rz*vy;
      double ly = ry*vx - rx*vz;
      double lz = rx*vy - ry*vx;
      Fx -= G*mass*other.mass*rx/((r*r*r) + smoothing)* (1+ (3*lx*lx)/(r*r*c*c));
      Fy -= G*mass*other.mass*ry/((r*r*r) + smoothing)* (1+ (3*ly*ly)/(r*r*c*c));
      Fz -= G*mass*other.mass*rz/((r*r*r) + smoothing)* (1+ (3*lz*lz)/(r*r*c*c));

    }else{

      Fx -= G*mass*other.mass*rx/((r*r*r) + smoothing);
      Fy -= G*mass*other.mass*ry/((r*r*r) + smoothing);
      Fz -= G*mass*other.mass*rz/((r*r*r) + smoothing);

    }



}

void Planet::CalculateNewPosition(double time_step, double ax, double ay, double az) {



    x += vx*time_step + 0.5*time_step*time_step*ax;
    y += vy*time_step + 0.5*time_step*time_step*ay;
    z += vz*time_step + 0.5*time_step*time_step*az;
    //std::cout << x<< "    " << time_step<<"   " << ax<< '\n';


}

void Planet::CalculateVelocity(double time_step, double ax,double axnew,double ay,double  aynew,double  az,double  aznew) {
    vx += 0.5*time_step*(ax + axnew);
    vy += 0.5*time_step*(ay + aynew);
    vz += 0.5*time_step*(az + aznew);
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
