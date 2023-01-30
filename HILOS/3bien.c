#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    int i;
    int tipo;
    int *vector;
}cosa;

void * func(void * arg){
    cosa * e = (cosa *)arg;
    int suma, * resultado = (int *)malloc(sizeof(int)), its;
    if(e->tipo == 2)
        its = 5;
    else
        its = 2;
    printf("Se suman en una tanda\n");
    for(int i = e->i; i < (e->i + its); i++)
    {
        suma += e->vector[i];
        printf("| %d ", e->vector[i]);
    }
    printf("|\n Igual a [%d]\n", suma);
    e->i += its;
    *resultado = suma;
    pthread_exit((void *)resultado);
}
int main(int argc, char **argv){
    if(argc != 2){
        perror("ARGS\n");
        exit(EXIT_FAILURE);
    }
    if(atoi(argv[1]) != 5 && atoi(argv[1]) != 2){
        perror("ARGS value\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    int vec[10], *resultado, total, res;
    for(int i = 0; i < 10; i++){
        vec[i] = rand() % 10 + 1;
    }
    cosa e;
    e.tipo = atoi(argv[1]);
    e.i = 0;
    e.vector = vec;

    pthread_t hilos[e.tipo];

    for(int i = 0; i < e.tipo; i++){
        if(pthread_create(&hilos[i], NULL, (void *)func, &e) != 0){
            perror("CREATE\n");
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i = 0; i < e.tipo; i++){
        if(pthread_join(hilos[i], (void **)&resultado) != 0){
            perror("JOIN\n");
            exit(EXIT_FAILURE);
        }
        res = *resultado;
        total += res;
    }

    printf("El resultado total es %d\n", total);

    exit(EXIT_SUCCESS);

}