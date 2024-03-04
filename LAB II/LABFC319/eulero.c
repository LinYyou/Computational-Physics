#include <stdio.h>
#include <math.h>

#define N 10000
#define Ninput 1
#define pi 3.1415926

int main(){

  double X0,X, V0,V, t, tMax, DeltaT, OmegaQ, Acc, E,tau1, tau2;
  FILE *fp, *fp2; 
  int i= 0;
  
  //input dei dati iniziali
  printf("Inserisca il tempo: ");
  scanf("%lf", &tMax);

  printf("\nOra inserisca la posizione iniziale(m) :");
  scanf("%lf", &X0);

  printf("\nInserisca la velocita iniziale(m/s) :");
  scanf("%lf", &V0);

  do{
  printf("\nInserica la pulsazione :");
  scanf("%lf", &OmegaQ);
  }while(OmegaQ <= 0);
  


  /*for( i = 1; i < Ninput; i++){

    fscanf("%lf %lf %lf %lf %lf", &X, &V, &OmegaQ, &t, &tMax);
    }*/

  //Metodo di Eulero
  fp = fopen("eulero.dat", "w"); 
  
  DeltaT = tMax/N;

  X = X0;

  V = V0;

  
  for(t = 0; t < tMax; t += DeltaT){

    Acc= -OmegaQ*X;
    X = X + V*DeltaT; 
    V = V + Acc*DeltaT;
    E = V*V + OmegaQ*X*X;

    fprintf(fp,"\n%lf     %lf     %lf     %lf", X, V, Acc, E);
   
  }

  fclose(fp);
  printf("\n");



  
  //Metodo di Eulero-Cromer

  fp2 = fopen("euleroCromer.dat", "w"); 
  
  DeltaT = tMax/N;

  X = X0;

  V = V0;

  
for(t = 0; t < tMax; t += DeltaT){

    Acc= -OmegaQ*X;
    V = V + Acc*DeltaT;
    X = X + V*DeltaT; 
    E = V*V + OmegaQ*X*X;

      
      if(X == 0)      i++;
      if (i == 2){
	printf("\n%lf", t);
	i = 0;
      }
    
    

    
    fprintf(fp,"\n%lf     %lf     %lf     %lf", X, V, Acc, E);
   
 } 

 fclose(fp2); 


  
  return 0;
}
