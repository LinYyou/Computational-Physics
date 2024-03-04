#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>

typedef long long unsigned int MATTEO;
typedef long unsigned int LIN;

#define a 1181783497276652981
#define b 0
#define m pow(2, 64)
#define steps 1000
#define prove 100000

MATTEO Rand(MATTEO I);
int passo(double rand, int walk);

int main(int argc, char ** argv){
  int walk, Dimensione, t, i,j, Min= 0, Max=0, *PosF, *Bin;
  //double XQuad[steps];
  double *XQuad;
  MATTEO I;
  double rand;
  I = time(NULL);



  
  XQuad = (double *) calloc(steps,  sizeof(double));
  if (XQuad == NULL){
    printf("\n\n ERRORE \n\n");
    exit(0);

  }

  PosF = (int *) calloc(prove,  sizeof(int));
  if (PosF == NULL){
    printf("\n\n ERRORE \n\n");
    exit(0);

  }


  Bin = (int *) calloc(steps,  sizeof(int));
  if (PosF == NULL){
    printf("\n\n ERRORE \n\n");
    exit(0);

  }
  
  /*
    if(argc != 2){
  printf("\nNon ti scordare di scegliere la dimensione, o 1 o 2?");
    
    return 1;
    }
  
  Dimensione = atoi(argv[1]);
  */
  for(t=0; t< steps; t++){
  XQuad[t] = 0;
  }
  
  
  
  for(i=0; i < prove;i++){
    walk = 0;
    for(t=1; t< steps; t++){
      I  = Rand(I);
      rand = (double)I/ULLONG_MAX;
      walk = passo(rand , walk);
      XQuad[t] += walk*walk;
     
    }
    PosF[i] = walk;
    
    if(walk<Min) Min = walk;
    if(walk>Max) Max = walk;

    
    for(j=0; j <= -Min + Max ;j++){
      if(PosF[i]- Min == j) Bin[j]++;
       
    }
  }   

  for(j=0; j <= -Min + Max ;j++){
    printf("\n%d    %d", Bin[j], j+Min);
  }
  // for(t=1; t<steps; t++){
  //   printf("\n%d    %lf", t, (double)XQuad[t]/prove);
  //}



  
  
  printf("\n\n");

  return 0;
}

MATTEO Rand(MATTEO I){
    
  I = (a*I + b)%(MATTEO)m;
  
  return I;
  }
 
int passo(double rand, int walk){

  if(rand < 0.5){
    walk++;
  }else{
    walk--;
  }

  return walk;
}
