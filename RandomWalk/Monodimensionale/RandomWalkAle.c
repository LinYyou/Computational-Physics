#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>

typedef long long unsigned int MATTEO;


#define a 1181783497276652981
#define b 0
#define m pow(2, 64)
#define steps 1000
#define prove 100000

MATTEO Rand(MATTEO I);
int passo( MATTEO *I,int walk, double p[]);

int main(int argc, char ** argv){
  int walk=0, Dimensione, t, i,*XQuad;
  //double XQuad[steps];
  double rand, *p;
  MATTEO I, T;
  I = time(NULL);
  srand48(time(0));

  
  XQuad = (int *) calloc(10*steps,  sizeof(int));
  if (XQuad == NULL){
    printf("\n\n ERRORE \n\n");
    exit(0);
    
  }

  p = (double *) calloc(3*steps,  sizeof(double));
  if (XQuad == NULL){
    printf("\n\n ERRORE \n\n");
    exit(0);
    
  }
  
  for(i=0; i<2000; i++){
    p[i] = drand48();
  }
  
  
  
  
  for(i=0; i <= prove;i++){

    walk=0;
    for(t=1; t<= steps; t++){
      
      
      walk = passo(&I,walk, p);
      XQuad[t] += walk*walk;

    }   
  }   
  
  for(t=0; t<steps; t++){
    printf("\n%d    %lf", t, (double)XQuad[t]/prove );
  }
  
  
  
  
  
  
  printf("\n\n");
  
  return 0;
}

MATTEO Rand(MATTEO I){
  
  I = (a*I + b)%(MATTEO)m;
  
  return I;
}

int passo(MATTEO *I, int walk, double p[]){
  
  int i;
  double rand;
  
  
  (*I)  = Rand(*I);
  
  rand = (double)(*I)/ULLONG_MAX;
    
  if(rand < p[walk+1000]){
    walk++;
  }else{
    walk--;
  }
   
  
  return walk;
}
  
