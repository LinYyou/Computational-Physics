#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<time.h>

typedef long long unsigned int MATTEO;


#define a 1181783497276652981
#define b 0
#define m pow(2, 64)
#define steps 1000
#define prove 100



typedef long long unsigned int MATTEO;
typedef struct position{
  int x;
  int y;
}position;


MATTEO Rand(MATTEO I);

void initial(MATTEO *I, position part[],position realpos[], position initPart[] , double density, int L, int *N); //Inizializzazione, quindi riempimento del reticolo
void PackmanEf(position *parc, int L, int N);//Stabilire un bordo per il reticolo
double realdistQuad(position realpos, position posIni);//calcola la distanza quadratica della posizione in tempo t del gas rispetto alla posizione iniziale
int verifica(position pos, position posGas[], int N);//Verifica che due molecole di gas non si collidono 
double meanDoub(double array[], int N);//Funzione per la media
void move(position participle[], position realpos[], position posIni[], double dist[], int N, MATTEO *I, int L);//Funzione per variare la posizione di ogni molecola di gas

int main(){
  MATTEO I;
  int i, j, k, t, L, N, file=1;
  position  *realpos, *participle, *posIni;
  double density, rand, *distQuad,  *coeff, invProve;
  FILE *f10, *f20,  *f40;

  I = time(NULL);
  
  
  //Inizializzazione degli array
  participle = (position *)calloc(3000, sizeof(position));
  if(participle == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
  
  realpos = (position *)calloc(3000, sizeof(position));
  if(realpos == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
  distQuad = (double *)calloc(3000, sizeof(double));
  if(realpos == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }

  posIni = (position *)calloc(3000, sizeof(position));
  if(participle == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
  
  coeff = (double *)calloc(3000, sizeof(double));
  if(realpos == NULL){
    printf("\n\nERRORE\n\n");
    exit(0);
  }
  
  
  //Fine inizializzazione
 
 

  invProve = 1./(double)prove/4.;
  density = 0.6;
  
  
  
  //File contenenti i dati per grafico per lo studio del coefficiente di diffusione in base alla densità
  while(file <= 3){

    for(t=1; t<=steps; t++){

      coeff[t]= 0;
    }

    
    if(file == 1){
      f10=fopen("taglia10.dat", "w");
	L=10;
      }
      
    if(file == 2){
      f20=fopen("taglia20.dat", "w");
	L=20;
    }
    
    if(file == 3){
      f40=fopen("taglia40.dat", "w");
	L=40;
      }
    
    for(k=0; k<prove; k++){
      N=0;
      initial(&I, participle ,realpos, posIni, density, L, &N);
      
      for(t=1; t<=steps; t++){
	move(participle, realpos, posIni, distQuad, N, &I, L);
	
	coeff[t] += meanDoub(distQuad, N)*invProve/(double)t;
      }
      
      
    }
    
    
    for(t=1; t<=steps; t++){
      if(file == 1)fprintf(f10,"\n%d    %g", t, coeff[t]);
      if(file == 2)fprintf(f20,"\n%d    %g", t, coeff[t]);
      if(file == 3)fprintf(f40,"\n%d    %g", t, coeff[t]);

    }
    
    
    if(file == 1)fclose(f10);
    if(file == 2)fclose(f20);  
    if(file == 3)fclose(f40);
 
    file++;
  }  
  
printf("\n\n");

return 0;
}



MATTEO Rand(MATTEO I){
  
  I = (a*I + b)%(MATTEO)m;
  
  return I;
}


void initial(MATTEO *I, position part[],position realpos[], position initPart[] , double density, int L, int *N){

  int i, j;
  double rand;
  
  for(i=0; i<L; i++){
    for(j=0; j<L; j++){
      (*I) = Rand(*I);
      rand = (double)(*I)/ULLONG_MAX;
      if(rand <= density){
	(*N)++;
	part[*N].x = i;
	initPart[*N].x = i;
	realpos[*N].x=i;
	part[*N].y = j;
	initPart[*N].y = j;
	realpos[*N].y=j;
      }
    }
  }
  printf("\n#Densità attesa: %g     Dimensione del reticolo : %d x %d  \n#Numero di particelle: %d   Densità reale: %g\n", density, L, L, (*N), (double)(*N)/(L*L) );

  
}

void PackmanEf(position *parc, int L, int N){
  
  
  if((*parc).x==(-1))(*parc).x=L-1;
  if((*parc).x==L)(*parc).x=0;
  if((*parc).y==(-1))(*parc).y=L-1;
  if((*parc).y==L)(*parc).y=0;    
}

double realdistQuad(position realpos, position posIni){

  return (double)(realpos.x - posIni.x)*(realpos.x - posIni.x) + (double)(realpos.y - posIni.y)*(realpos.y - posIni.y);

}

int verifica(position pos, position posGas[], int N){

  int collisione=0, i;	
  for(i=1; i<=N; i++){
    if(pos.x == posGas[i].x && pos.y==posGas[i].y){
      collisione++;
         }
    if(collisione == 2){
      return 1;
      
      i=N;
    }

  }
  


}


double meanDoub(double array[], int N){

  int i;
  double mean=0;
  for(i=1; i<=N; i++){
    mean+=array[i]/(double)N;
  }
  return mean;

}


void move(position participle[], position realpos[], position posIni[], double dist[], int N, MATTEO *I, int L){
  int i;
  double rand;
  for (i=1; i<=N; i++){
    (*I) = Rand(*I);
    rand = (double)(*I)/ULLONG_MAX;
    if(rand<0.25){
      participle[i].x++;
      realpos[i].x++;
      PackmanEf(&participle[i], L, N);
	    
      if(verifica(participle[i], participle, N)==1){
	participle[i].x--;
	PackmanEf(&participle[i], L, N);
	realpos[i].x--;
      }
    }else if(rand<0.50){
      participle[i].x--; 
      realpos[i].x--;
      PackmanEf(&participle[i], L, N);
	    
      if(verifica(participle[i], participle, N)==1){
	participle[i].x++;
	PackmanEf(&participle[i], L, N);
	realpos[i].x++;
      }
    }else if(rand<0.75){
      participle[i].y++; 
      realpos[i].y++;
      PackmanEf(&participle[i], L, N);
	    
      if(verifica(participle[i], participle, N)==1){
	participle[i].y--;
	PackmanEf(&participle[i], L, N);
	realpos[i].y--;
      }
    }else{
      participle[i].y--;
      PackmanEf(&participle[i], L, N);
      realpos[i].y--;
      
      if(verifica(participle[i], participle, N)==1) {
	participle[i].y++;
	PackmanEf(&participle[i], L, N);
	realpos[i].y++;
      }
    }
    //    printf("\n%d   %d  ", participle[i].x, participle[i].y);
    dist[i] = realdistQuad(realpos[i], posIni[i]);  
  }
}
