#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
sem_t sA;
sem_t sB;

void * escribirA (void * p){
    int i;
    for (i= 0; i< 5; i++){
        if(sem_wait(&sA)){ //si el semaforo aun no se ha abierto, no se abre, 
                           //o si se acaba de abrir se cierra
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
        printf ("A");
        fflush(NULL);
        if(sem_post(&sB)){ // si el B ya se a escrito, se le vuelve a permitir que escriba
                            //
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }        
    }
    pthread_exit(NULL);
}

void * escribirB (void * p){
    int i;
    for (i= 0; i< 5; i++){
        if(sem_wait(&sB)){ //Decrementa la unidad del semaforo, con lo que ya no se puede volver escribir hasta que
                            // A no se haya escrito
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }        
        printf ("B");
        fflush(NULL);
        if(sem_post(&sA)){ //Cuando B se haya escrito se pone a 1 A, B esta en 0 
                            //con lo que B no se escribe
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}

int main(){
    if(sem_init(&sA, 0, 0) != 0){
        perror("ERROR DE INICIO DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sB, 0, 1) != 0){
        perror("ERROR DE INICIO DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    pthread_t A, B;
    if(pthread_create(&A, NULL, escribirA, NULL)){
        perror("ERROR DE HILO\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&B, NULL, escribirB, NULL)){
        perror("ERROR DE HILO\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(A, NULL)){
        perror("ERROR DE HILO\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(B, NULL)){
        perror("ERROR DE HILO\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");
}