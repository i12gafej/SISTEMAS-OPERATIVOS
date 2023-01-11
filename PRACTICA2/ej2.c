#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void * contar(void * arg){
    
    int * n = malloc(sizeof(int)), nlineas = 0;
    char *fichero = (char *) arg;
    FILE *f = fopen(fichero, "rt");
    char ca[200];
    
    while(fgets(ca, 200, f) != NULL){
        
        ++(nlineas);
    }
    *n = nlineas;
    printf("Numero de lineas del fichero = %d\n", *n);
    fclose(f);
    pthread_exit((void *) n);
}
int main(int argc, char **argv){
    int * numero, total = 0;
    char * argu;
    
    if(argc < 2){
        printf("No hay argumentos suficientes, introduce los ficheros\n");
        exit(EXIT_FAILURE);
    }
    pthread_t hilo[argc - 1]; 
    
    for(int i = 0; i < (argc - 1); i++){
        
        argu = argv[i+1];
        
        if(pthread_create(&hilo[i], NULL,(void *) contar, (void*) argu)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i = 0; i < (argc - 1); i++){
        if(pthread_join(hilo[i], (void**)&numero)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
        total += *numero;
    }
    printf("Total es %d lineas\n ", total);
}
