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

typedef struct position {
  int x;
  int y;
}position;


MATTEO Rand(MATTEO I);
void passo(double rand, int *x,int *y);

int main(int argc, char ** argv){
  int t,i,x,y,j=0, **bin, k;
  position Min,Max,*pos;
  MATTEO I;
  double rand;
  I = time(NULL);
  //libera l'array delle posizioni
  pos = (position *)calloc(prove, sizeof(position));
  if (pos == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
  
  
  //libera l'array dei bin(array bidimensionale)
  bin = (int **)calloc(prove, sizeof(int*));
  for(i=0;i<prove;i++){
    bin[i] = (int *)calloc(prove,sizeof(int));
  }    
  if (bin == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
  Min.x = 0;
  Min.y = 0;
  Max.x = 0;
  Max.y = 0;

  //ISTOGRAMMA
  for(i = 0; i < prove; i++){
    x = 0;
    y = 0;
    for(t=1; t < steps; t++){
      I = Rand(I);
      rand = (double)I/ULLONG_MAX;
      passo(rand,&x,&y);
      
    }
    pos[i].x = x;
    pos[i].y = y;
    //Seleziona il range dell'istrogramma, osservando quale è il valore minimo raggiunto di x (di y), e il valore massimo.
    if(x < Min.x) Min.x = x;
    if(y < Min.y) Min.y = y;
    if(x > Max.x) Max.x = x;
    if(y > Max.y) Max.y = y;
    //Riempimento dei bin[x][y], con x e y le coordinate, xrange=[Min.x; Max.x](idem for y).
    for(k=0;k<= - Min.x + Max.x;k++){
      if(pos[i].x - Min.x == k){
	for(j=0;j <= -Min.y + Max.y;j++){
	  
	  if(pos[i].y - Min.y == j){
	    bin[k][j]++;
	  }
	}
      }

    }
  }


  
  for(j=0;j<= -Min.y + Max.y;j++){
    for(k=0;k<= - Min.x + Max.x;k++){
      printf("\n %d    %d    %d", k+Min.x, j+Min.y, bin[k][j]);
    }
  }
  

  printf("\n\n");
  return 0;
}


MATTEO Rand(MATTEO I){
  
  I = (a*I + b)%(MATTEO)m;
  
  return I;
}

void passo(double rand, int *x, int *y ){
  
  if(rand < 0.25){
    (*x)++;
  }else if(rand >= 0.25 && rand<0.5){
    (*y)++;
  }else if(rand >= 0.5 && rand<0.75){
    (*x)--;
  }else{
    (*y)--;
  };
  
}
