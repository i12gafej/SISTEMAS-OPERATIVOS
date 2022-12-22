#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

static int impar = 0;
static int par = 0;
pthread_mutex_t mutex = PTHREAD_MUTEZ_INITIALIZER;
void * Opar(void * arg){
    int *numero = malloc(sizeof(int));
    numero = (int*) arg;
    
    if(pthread_mutex_lock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    par = par + *numero;
    if(pthread_mutex_unlock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);
}
void * Oimpar(void * arg){
    int *numero = malloc(sizeof(int));
    numero = (int*) arg;
    
    if(pthread_mutex_lock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    impar = impar + *numero;
    if(pthread_mutex_unlock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv){
    int n;
    n = atoi(argv[1]);
    pthread_t hilos[n];
    for(int i = 0; i < n ; i++){
        if(i%2 == 0){
            if(pthread_create(&hilos[i], NULL, Opar,(void*) &i)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            if(pthread_create(&hilos[i], NULL, Oimpar,(void*) &i)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    for(int i = 0; i < n ; i++){
        if(i%2 == 0){
            if(pthread_join(hilos[i], NULL)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            if(pthread_join(hilos[i], NULL)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
