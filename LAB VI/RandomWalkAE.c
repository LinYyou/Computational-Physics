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
#define steps 100
#define prove 1000

typedef struct position {
  int x;
  int y;
}position;


MATTEO Rand(MATTEO I);
void passo(MATTEO *I,int *x,int *y, position *prec, int *intra,int t);

int main(int argc, char ** argv){
  int t,i,x,y, intra = 0, control = 0;
  position *posFin, *pos;
  MATTEO I;
  I = time(NULL);

  pos = (position *)calloc(prove, sizeof(position));
  if (pos == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  posFin = (position *)calloc(prove, sizeof(position));
  if (pos == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
   

  
  for(i = 0; i < prove; i++){
    x = 0;
    y = 0;
    for(t=1; t <=steps; t++){
      control = intra;
      passo(&I,&x,&y, pos, &intra,t);
      pos[t].x = x;
      pos[t].y = y;
      if(intra > control) t=steps;
    }
    posFin[i].x = x;
    posFin[i].y = y;
   
     printf("\n  %d  %d",posFin[i].x,posFin[i].y);
  }

  printf("\nSu %d prove %d volte la particella è stata intrappolata",prove, intra);

  

  printf("\n\n");
  return 0;
}


MATTEO Rand(MATTEO I){
  
  I = (a*I + b)%(MATTEO)m;
  
  return I;
}

void passo(MATTEO *I,int *x, int *y, position *prec, int *intra,int t){
  double rand=0;
  int i, xL=0, xR=0, yU=0, yD=0, succ=0;
  for (i = 1; i< t; i++){

    if(prec[i].x +1 == *x && prec[i].y == *y)xL++;
    if(prec[i].x -1 == *x && prec[i].y == *y)xR++;
    if(prec[i].y +1 == *y && prec[i].x == *x)yD++;
    if(prec[i].y -1 == *y && prec[i].x == *x)yU++;
    
  }

  

  if(xL==1 && xR==1 && yU==1 && yD==1){
    (*intra)++;
  }
  else{

    while(succ == 0) {
  *I = Rand(*I);
  rand = (double)*I/ULLONG_MAX;
 
  if(rand < 0.25 && xR == 0){
    (*x)++;
    succ++;

  }else if(rand >= 0.25 && rand<0.5 && yU == 0){
    (*y)++;
    succ++;
  }else if(rand >= 0.5 && rand<0.75 && xL == 0){
    (*x)--;
    succ++;
    
  }else if(yD == 0){
    (*y)--;
    succ++;
  };

    }

    
  }
}