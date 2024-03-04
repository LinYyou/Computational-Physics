#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define pi 3.14159265354

struct phaseSpace{
  double x;
  double v;
};


//prototipi

struct phaseSpace EulerMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ);
struct phaseSpace EulerCromerMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ);

struct phaseSpace VerletMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ);
struct phaseSpace VerletAutoMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ);

double Energy(struct phaseSpace pendolo, double OmegaQ);
double Accelerazione(double OmegaQ,double X);


int main(int argc, char* argv[]){
  
  double x0, V0, dt, tTot, Acc,OmegaQ; 
  struct phaseSpace pendolo;
  int Option;
  if(argc != 7){
    printf("Errore!I valori devono essere x0, v0, tTot, dt, OmegaQ!!!!\n");
    return 1;
  }
  
  x0 = atof(argv[1]);
  V0 = atof(argv[2]);
  tTot = atof(argv[3]);
  dt =atof( argv[4]);
  OmegaQ =atof( argv[5]);
  Option = atoi(argv[6]);


  if(Option == 1) EulerMethod(pendolo,dt,tTot,x0,V0,OmegaQ);
  if(Option == 2) EulerCromerMethod(pendolo,dt,tTot,x0,V0,OmegaQ);
  if(Option == 3) VerletMethod(pendolo,dt,tTot,x0,V0,OmegaQ);
  //  if(Option == 4) VerletAutoMethod(pendolo,dt,tTot,x0,V0,OmegaQ);

  

  
  return 0;
}


double Accelerazione(double OmegaQ, double X){

  return -OmegaQ*sin(X); 

  }

double Energy(struct phaseSpace pendolo, double OmegaQ){

  return pendolo.v*pendolo.v + OmegaQ*pendolo.x*pendolo.x;

}




struct phaseSpace EulerMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ){

  double t,Amp,phi, xAnal, vAnal, Energia, E0;


  pendolo.x = x0;
  pendolo.v = V0;
  phi = atan(-V0/(x0*sqrt(OmegaQ)));
  Amp = x0/cos(phi);
  E0 = x0*x0*OmegaQ + V0*V0;
  
  for(t=0;t<tTot;t+=dt){
  
  pendolo.x = pendolo.x + pendolo.v*dt;
  pendolo.v = pendolo.v + Accelerazione(OmegaQ, pendolo.x)*dt;

  xAnal = x0 + Amp*cos(sqrt(OmegaQ)*t + phi); 
  vAnal=V0 -Amp*sqrt(OmegaQ)*sin(sqrt(OmegaQ)*t + phi);
  Energia = Energy(pendolo, OmegaQ);
  
  printf("%g     %g     %g     %g     %g     %g\n", t, pendolo.x, pendolo.v, xAnal, vAnal,(Energia-E0)/E0);
  
  }

}


struct phaseSpace EulerCromerMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ){

  double t,Amp,phi, xAnal, vAnal, Energia, E0;


  pendolo.x = x0;
  pendolo.v = V0;
  phi = atan(-V0/(x0*sqrt(OmegaQ)));
  Amp = x0/cos(phi);
  E0 = x0*x0*OmegaQ + V0*V0;
  
  for(t=0;t<tTot;t+=dt){

    pendolo.v = pendolo.v + Accelerazione(OmegaQ, pendolo.x)*dt;
    pendolo.x = pendolo.x + pendolo.v*dt;
  

    xAnal = x0 + Amp*cos(sqrt(OmegaQ)*t + phi); 
    vAnal=V0 -Amp*sqrt(OmegaQ)*sin(sqrt(OmegaQ)*t + phi);
    Energia = Energy(pendolo, OmegaQ);
  
    printf("%g     %g     %g     %g     %g     %g\n", t, pendolo.x, pendolo.v, xAnal, vAnal,(Energia-E0)/E0);
  
  }

}

struct phaseSpace VerletMethod(struct phaseSpace pendolo, double dt, double tTot, double x0, double V0, double OmegaQ){
  
  double x1, t,Amp,phi, xAnal, vAnal, Energia, E0, vn, xn, xnMenoUno;

  xnMenoUno = x0;
  xn = x0+pendolo.v*dt;
  phi = atan(-V0/(x0*sqrt(OmegaQ)));
  Amp = x0/cos(phi);  
  E0 = x0*x0*OmegaQ + V0*V0;

  for(t=dt;t<tTot;t+=dt){
      
    pendolo.x = 2*xn - xnMenoUno + Accelerazione(OmegaQ, xn)*dt*dt;
    vn= (pendolo.x - xnMenoUno)/(2*dt);
    xnMenoUno = xn;
    xn = pendolo.x;

    xAnal = x0 + Amp*cos(sqrt(OmegaQ)*t + phi); 
    vAnal=V0 -Amp*sqrt(OmegaQ)*sin(sqrt(OmegaQ)*t + phi);
    Energia = xn*xn*OmegaQ + vn*vn;
    printf("%g     %g     %g      %g      %g      %g\n", t, xn, vn, xAnal, vAnal, (Energia-E0)/E0 );
    
  }
  

}
