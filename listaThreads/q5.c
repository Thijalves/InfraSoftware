#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <unistd.h>

#define N 5
#define LEFT ((id+N-1)%N) /* numero do vizinho a esquerda de i */
#define RIGHT ((id+1)%N) /* numero do vizinho a direita de i */

#define TAKEN 'T'
#define AVAILABLE 'A'

void think(int id);    
void get_forks(int id);
void put_forks(int id);
void* filosofo(void* args);

//mutex para o array todo
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//variaveis de condicao
pthread_cond_t cond[N] = {PTHREAD_COND_INITIALIZER};

//array com o estado de cada garfo
char estadoGarfos[N];
//array com o estado de cada filosofos
char estadoFilos[N];

int main (){

    //ilustra a mesa dos filosofos onde H eh hungry e E eh eating
    for(int i = 0; i < 5; i++)
        estadoFilos[i] = 'H';
        
    printf("---------\n");
    printf("  %c   %c  \n", estadoFilos[0], estadoFilos[1]);
    printf(" %c     %c  \n", estadoFilos[4], estadoFilos[2]);
    printf("    %c  \n", estadoFilos[3]);
    printf("---------\n");

    //cria as threads
    pthread_t threads[5];
    int* philosoherID[5];
    for(int i = 0; i < 5; i++){
        philosoherID[i] = (int *) malloc(sizeof(int)); 
        *philosoherID[i] = i;
        pthread_create(&threads[i], NULL, filosofo, (void*) philosoherID[i]);
    }

    for(int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    return 0;
}

//funcoes chamadas pelo filosofo

void* filosofo(void* args){
    int id = *((int*) args);
    while (1){
        sleep(1); //think
        get_forks(id);
        sleep(1); //eat
        put_forks(id);
    }
}

void get_forks(int id){

    //trava o mutex
    pthread_mutex_lock(&mutex);

    //enquanto nao puder pegar os garfos fica dormindo
    while (estadoGarfos[id] == TAKEN || estadoGarfos[RIGHT] == TAKEN) {
        pthread_cond_wait(&cond[id], &mutex);
    }

    //aqui ele pode comer
    estadoGarfos[id] = TAKEN;
    estadoGarfos[RIGHT] = TAKEN;
    printf("%d pegou os grafos %d e %d\n", id, id, RIGHT);
    estadoFilos[id] = 'E';
    //ilustra a mesa dos filosofos onde H eh hungry e E eh eating
    printf("---------\n");
    printf("  %c   %c  \n", estadoFilos[0], estadoFilos[1]);
    printf(" %c     %c  \n", estadoFilos[4], estadoFilos[2]);
    printf("    %c  \n", estadoFilos[3]);
    printf("---------\n");

    //destrava o mutex
    pthread_mutex_unlock(&mutex);
    
}

void put_forks(int id){

    //trava o mutex
    pthread_mutex_lock(&mutex);

    //Solta os grafos
    estadoGarfos[id] = AVAILABLE;
    estadoGarfos[RIGHT] = AVAILABLE;
    printf("%d soltou os garfos %d e %d\n", id, id, RIGHT);
    estadoFilos[id] = 'H';
    //ilustra a mesa dos filosofos onde H eh hungry e E eh eating
    printf("---------\n");
    printf("  %c   %c  \n", estadoFilos[0], estadoFilos[1]);
    printf(" %c     %c  \n", estadoFilos[4], estadoFilos[2]);
    printf("    %c  \n", estadoFilos[3]);
    printf("---------\n");

    //avisa aos vizinhos que soltou
    pthread_cond_signal(&cond[LEFT]);
    pthread_cond_signal(&cond[RIGHT]);
   
    //destrava o mutex
    pthread_mutex_unlock(&mutex);


}