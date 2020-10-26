#include "solarsystem.h"
#include <iostream>
#include "time.h"
extern bool OPPGAVE_E;

using namespace std;

int main(){
	std::clock_t c_start = std::clock();

     int IntegrationPoints = 30000; // No. of integration points

     Position earthPosition = {
        9.641327723118710E-01,2.465760952329768E-01,7.355032830476560E-05,
        -4.414756238829297E-03,1.662854248250772E-02,-1.141917171095722E-06
     };
     Position sunPosition = {
        -6.042129225281306E-03,6.466147207407354E-03 ,8.697025391574593E-05,
        -7.340949389436893E-06,-5.013274120148366E-06,2.189694604890483E-07
     };
     Position mercuryPosition = {
        2.643154303593134E-01,-3.157121726001744E-01,-5.104028200574216E-02,
        1.594913945525348E-02,1.943209256008390E-02, 1.248175570907458E-04
     };
     Position venusPosition = {
        4.150243727322463E-02,7.249838052804233E-01,1.199344556569153E-02,
        -2.027816182702826E-02,-1.110945668283595E-03, 1.154794297386271E-03
     };
     Position marsPosition = {
        1.345378062254299E+00,4.084608038233191E-01,-2.464109560220932E-02,
        -3.461024232126337E-03,1.460286918855168E-02, 3.910679989453692E-04
     };
     Position jupiterPosition = {
        2.498448739730900E+00,-4.465376195677621E+00,-3.737360937699062E-02,
        6.492384890941658E-03, 4.042682241018491E-03,-1.620109807189240E-04
     };
     Position saturnPosition = {
        5.103722722985534E+00,-8.589325573332745E+00,-5.383728342461085E-02,
        4.485417789473280E-03, 2.835373677499000E-03,-2.279140494199569E-04
     };
     Position uranusPosition = {
        1.555699241302860E+01,1.221910149177578E+01,-1.561607122345573E-01,
        -2.458330565291503E-03,2.909818903772846E-03,4.265513850741358E-05
     };
     Position neptunePosition = {
        2.940729514413145E+01,-5.493019203455270E+00 ,-5.646020096991961E-01,
        5.555764171920431E-04,3.104406750096129E-03,-7.673262993881012E-05
     };

     Planet Sun("Sun",1.,0.1, sunPosition);
     Planet Earth("Earth",0.000003, 1., earthPosition); // Earth: (mass,x,y,z,vx,vy,vz)
     Planet Mercury("Mercury",1.651E-7, 0.25, mercuryPosition);
     Planet Venus("Venus",0.000002447,0.62, venusPosition);
     Planet Mars("Mars",3.213E-7,1.88, marsPosition);
     Planet Jupiter("Jupiter", 0.0009543,11.86, jupiterPosition);
     Planet Saturn("Saturn",0.0002857,29.46, saturnPosition);
     Planet Uranus("Uranus",0.00004365 ,84.01, uranusPosition);
     Planet Neptune("Neptune",0.00005149, 164.79, neptunePosition);

     SolarSystem sol(5.0);
     sol.add(Earth);
     sol.add(Sun);
     sol.add(Mercury);
     sol.add(Venus);
     sol.add(Mars);
     sol.add(Jupiter);
     sol.add(Saturn);
     sol.add(Uranus);
     sol.add(Neptune);


     OPPGAVE_E = false;

     sol.baycentric();
     // inside this method, first is called method for resset Planet parameters (position, velocities, energy) to initiala values
     sol.Euler(IntegrationPoints, 0.0);


     sol.baycentric();
     // inside this method, first is called method for resset Planet parameters (position, velocities, energy) to initiala values
     sol.VelocityVerlet(IntegrationPoints, 0.0);
	std::clock_t c_end = std::clock();

    double time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms /1000.0 << " s\n";
    return 0;
}
