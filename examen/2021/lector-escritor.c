#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

int variable = -1;
int cuentalect = 0;
sem_t sc;
sem_t x;
void escribir(){
    variable = rand()%10+1;
}
void * lector(void * arg){
    int * n = (int *) arg;
    for(int i = 0; i < (*n); i++){
        if(sem_wait(&sc) != 0){
            perror("Wait\n");
            exit(EXIT_FAILURE);
        }
        cuentalect++;
        if(cuentalect == 1){
            if(sem_wait(&x) != 0){
                perror("Wait\n");
                exit(EXIT_FAILURE);
            }
        }
            
        if(sem_post(&sc) != 0){
            perror("POST\n");
            exit(EXIT_FAILURE);
        }
        printf("<---Lector %ld, lee el número %d\n", pthread_self(), variable);
        if(sem_wait(&sc) != 0){
            perror("Wait\n");
            exit(EXIT_FAILURE);
        }
        cuentalect--;
        if(cuentalect == 0){
            if(sem_post(&x) != 0){
                perror("POST\n");
                exit(EXIT_FAILURE);
            }
        }
        if(sem_post(&sc) != 0){
            perror("POST\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}
void * escritor(void * arg){
    int * n = (int *) arg;
    for(int i = 0; i < (*n); i++){
        if(sem_wait(&x) != 0){
            perror("WAIT\n");
            exit(EXIT_FAILURE);
        }
        escribir();
        printf("--->Escritor %ld, escribe el número %d\n", pthread_self(), variable);
        if(sem_post(&x) != 0){
            perror("POST\n");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    srand(time(NULL));
    if(argc != 2){
        perror("argumentos\n");
        exit(EXIT_FAILURE);
    }

    if(sem_init(&sc, 0, 1) != 0){
        perror("Sem INIT\n");
        exit(EXIT_FAILURE);
    }
    if(sem_init(&x, 0, 1) != 0){
        perror("Sem INIT\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    pthread_t e, l;
    
        if(pthread_create(&e, NULL, (void *)escritor, &n) != 0){
            perror("HILO\n");
            exit(EXIT_FAILURE);
        }
    
        if(pthread_create(&l, NULL, (void *)lector, &n) != 0){
            perror("HILO\n");
            exit(EXIT_FAILURE);
        }

    
        if(pthread_join(l, NULL) != 0){
            perror("Join 2\n");
            exit(EXIT_FAILURE);
        }
    
        if(pthread_join(e, NULL) != 0){
            perror("Join 1\n");
            exit(EXIT_FAILURE);
        }
    
    exit(EXIT_SUCCESS);

}
