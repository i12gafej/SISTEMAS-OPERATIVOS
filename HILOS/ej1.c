#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
void * generar(){
    float * resul = malloc(sizeof(float)), * resul2 = malloc(sizeof(float));
    *resul = 0.0;
    *resul2 = 0.0;
    
    *resul = (float)(rand()% 10000)/100;
    *resul2 = (float)(rand()% 10000)/100;
    printf("Numero 1 : %f // Numero 2 : %f \n",*resul, *resul2);
    *resul += *resul2;
    pthread_exit((void *) resul);
}
int main(int argc, char **argv){
      srand((unsigned) time(NULL));

    if(argc < 2 || argc > 2){
        printf("No hay argumentos suficientes, introduce las N hebras creadas\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);
    float * numeroSumao = malloc(sizeof(float)), total;
    pthread_t hilo[n];

    for(int i = 0; i < n; i++){
        if(pthread_create(&hilo[i], NULL, generar, NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < n; i++){
        if(pthread_join(hilo[i], (void**)&numeroSumao)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
        total += *numeroSumao;
    }
    printf("El numero es %f\n", total);
}