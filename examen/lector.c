#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int lect = 0;
sem_t l;
sem_t sl;
void leer(unsigned long int thr){
    printf("Se está leyendo %lu\n", thr);
}
void escribir(unsigned long int thr){
    printf("Se esta escribiendo %lu\n", thr);
}
void * lectura(){
    //wait int lect
    if(sem_wait(&sl) != 0){
        perror("wait\n");
        exit(EXIT_FAILURE);
    }
        lect++;
    
    if(lect == 1){
        //wait lector
        if(sem_wait(&l) != 0){
            perror("wait\n");
            exit(EXIT_FAILURE);   
        }
    }
    //post int lect
    if(sem_post(&sl) != 0){
        perror("post\n");
        exit(EXIT_FAILURE);
    }
    leer(pthread_self());
    //wait int lect
    if(sem_wait(&sl) != 0){
        perror("wait\n");
        exit(EXIT_FAILURE);
    }
        lect--;
    if(lect == 0){
        //post lector
        if(sem_post(&l) != 0){
            perror("post\n");
            exit(EXIT_FAILURE);
        }
    }
    //post int lect
    if(sem_post(&sl) != 0){
        perror("post\n");
        exit(EXIT_FAILURE);
    }
    
}
void * escritura(){
    if(sem_wait(&sl) != 0){
        perror("wait\n");
        exit(EXIT_FAILURE);
    }
    escribir(pthread_self());
    if(sem_post(&sl) != 0){
        perror("post\n");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char ** argv){
    if(sem_init(&l, 0, 1) != 0){
        perror("semaforo\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&sl, 0, 1) != 0){
        perror("semaforo\n");
        exit(EXIT_FAILURE);
    }
    pthread_t hilo1, hilo2;
    if(pthread_create(&hilo1, NULL, (void *)lectura, NULL)!= 0){
        perror("create thread\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&hilo1, NULL, (void *)lectura, NULL)!= 0){
        perror("create thread\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&hilo1, NULL, (void *)lectura, NULL)!= 0){
        perror("create thread\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&hilo2, NULL, (void *)escritura, NULL)!= 0){
        perror("create thread\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(hilo1, NULL) != 0){
        perror("join thread\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(hilo2, NULL) != 0){
        perror("join thread\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


//se invocan n lectores y m escritores
//se puede leer uno a la vez
//se puede escribir mientras no se lea