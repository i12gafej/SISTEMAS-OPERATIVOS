#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

int par = 0;
int impar = 0;
pthread_mutex_t mutex;

void * p(void * arg){
    int *indice = (int *)arg, valor, *retorno = (int*)malloc(sizeof(int)), suma = 0;
    for(int i = 0; i < 100; i++){
        valor = rand()%11;
        if(pthread_mutex_lock(&mutex) != 0){
            perror("LOCK\n");
            exit(EXIT_FAILURE);
        }
            if((*indice)%2 == 0){
                par += valor;
            }
            else{
                impar += valor;
            }
            suma += valor;
        if(pthread_mutex_unlock(&mutex) != 0){
            perror("UNLOCK\n");
            exit(EXIT_FAILURE);
        }
    }
    *retorno = suma;
    printf("Se le ha sumado a la variable %d\n", *retorno);
    pthread_exit((void *)retorno);
}

int main(int argc, char **argv){
    srand(time(NULL));
    if(argc != 2){
        perror("ARGS\n");
        exit(EXIT_FAILURE);
    }
    int N = atoi(argv[1]), *retorno, resultado;
    pthread_t hilo[N];

    if(pthread_mutex_init(&mutex, NULL) != 0){
        perror("Init\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < N; i++){
        int j = i + 1; 
        if(pthread_create(&hilo[i], NULL, (void *) p, &j) != 0){
            perror("Create\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < N; i++){
        if(pthread_join(hilo[i], (void **)&retorno) != 0){
            perror("Join\n");
            exit(EXIT_FAILURE);
        }
        resultado += *retorno;
    }
    if(resultado == (par + impar)){
        printf("Correspondecia\n");
    }
    else{
        printf("No correspondencia\n");
    }
    exit(EXIT_SUCCESS);
}