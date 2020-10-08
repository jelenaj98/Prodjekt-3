/*    
    Euler's method for the Eart-Sun system, simplest possible code
*/ 
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace  std;

// output file as global variable
ofstream efile,vfile;

const double pi = acos(-1.0);
const double FourPi2 = 4*pi*pi;
const int NumberofSteps = 1000;
const  double FinalTime = 365.0;


// function declarations
void output(std::ostream&, double, double, double, double, double, double, double);


void Euler(double x, double y, double z, double vx, double vy, double vz, double Step){
    double r = sqrt(x*x+y*y+z*z);
    double time = 0.0;

    while (time <= FinalTime){
    x += Step*vx;
    y += Step*vy;
    z += Step*vz;

    
    vx -= Step*FourPi2*x/(r*r*r);
    vy -= Step*FourPi2*y/(r*r*r);
    vz -= Step*FourPi2*z/(r*r*r);

    r = sqrt(x*x+y*y+ z*z);
    time += Step;
    output(efile, time, x, y,z, vx, vy, vz);   // write to file 
  }
} 

void VelocityVerlet(double x, double y, double z, double vx, double vy, double vz, double Step){
    double r = sqrt(x*x+y*y+z*z);
    double time = 0.0;
    double axi, ayi, azi, axi_next,ayi_next, azi_next;

    while (time <= FinalTime){
        axi = FourPi2*x/(r*r*r);
        ayi = FourPi2*y/(r*r*r);
        azi = FourPi2*z/(r*r*r);
        x += Step*vx-(Step*Step)/2 * axi;
        y += Step*vy-(Step*Step)/2 * ayi;
        z += Step*vz-(Step*Step)/2 * azi;

        r = sqrt(x*x+y*y+z*z);
        axi_next = FourPi2*x/(r*r*r);
        ayi_next = FourPi2*y/(r*r*r);
        azi_next = FourPi2*z/(r*r*r);

        vx -= Step/2*(axi_next+axi);
        vy -= Step/2*(ayi_next+ayi);
        vz -= Step/2*(azi_next+azi);
   
    
        time += Step;
        output(vfile, time, x, y, z, vx, vy, vz);   // write to file 
  }
}

int main(int argc, char* argv[])
{
//  declarations of variables
  char *outfilename1,*outfilename2;
  // Read in output file, abort if there are too few command-line arguments
  if( argc <= 2 ){
    cout << "Bad Usage: " << argv[0] <<
      " read also 2 output files on same line" << endl;
    //    exit(1);
  }
  else{
    outfilename1=argv[1];
    outfilename2=argv[2];
  }
  efile.open(outfilename1);
  vfile.open(outfilename2);
  
  
  // Initial values  x = 1.0 AU and vy = 2*pi
    double Step = FinalTime/((double) NumberofSteps);  
    //double x =  1.0, y =  0.0, z =  0.0, vx = 0.0, vy = 2.0*pi, vz = 2.0*pi;
    double x = 9.641327723118710E-01, y = 2.465760952329768E-01, z = 7.355032830476560E-05, vx=-4.414756238829297E-03, vy= 1.662854248250772E-02, vz=-1.141917171095722E-06;


    Euler(x,y,z,vx,vy,vz,Step);
    VelocityVerlet(x,y, z, vx,vy, vz,Step);

    efile.close();  // close output file
    vfile.close();  // close output file
    
    return 0;
}   //  End of main function 

//    function to write out the final results
void output(std::ostream& file, double time, double x, double y, double z, double vx, double vy, double vz)
{
  file << setiosflags(ios::showpoint | ios::uppercase);
  file << setw(15) << setprecision(8) << time;
  file << setw(15) << setprecision(8) << x;
  file << setw(15) << setprecision(8) << y;
  file << setw(15) << setprecision(8) << z;
  file << setw(15) << setprecision(8) << vx;
  file << setw(15) << setprecision(8) << vy;
  file << setw(15) << setprecision(8) << vz << endl;
}  // end of function output