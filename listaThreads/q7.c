#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

char flag = 0;

typedef struct Trio{
    char **matriz;
    int index, size;
} Trio;

//retorna 1 caso haja um elemento repetido
void *checkLine(void *args){
    
    int size = ((Trio*)args)->size;
    int index = ((Trio*)args)->index;
    char **matriz =  ((Trio*)args)->matriz;

    for(int j = 0; j < size-1; j++)          
        for(int k = j + 1; k < size; k++)   
            if(matriz[index][j] == matriz[index][k]){
                flag = 1;
                return 0;
            }
}

int main (){

    int size;
    scanf("%d", &size);

    //aloca a matriz do tamanho desejado
    char** matriz = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++)
        matriz[i] = (char*) malloc(size * sizeof(char));

    //le os valores da matriz
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            scanf(" %c", &matriz[i][j]);


    //cria o vetor de threads
    pthread_t threads[size];
    Trio argumentos[size];

    for(int i = 0;i < size; i++){
        argumentos[i].index = i;
        argumentos[i].size = size;
        argumentos[i].matriz = matriz;
        pthread_create(&threads[i], NULL, checkLine, &argumentos[i]);
    }

    for(int i = 0; i < size; i++){
       pthread_join(threads[i], NULL);
    }

    printf("%d\n", flag);

    return 0;
}