#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

static int impar = 0;
static int par = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void * Opar(void * arg){
    int *i = malloc(sizeof(int)), *suma = malloc(sizeof(int));
    i = (int*) arg;
    for(int j = 0; j < 5; j++){
        *suma = *suma + rand()%10;
        
        printf("%d. Numero = %d\n", j+1, *suma);
    }    
    if(pthread_mutex_lock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    //seccion critica
    par = par + *suma;   
    //fin seccion critica
    
    if(pthread_mutex_unlock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit((void*) suma);
}
void * Oimpar(void * arg){
    int *i = malloc(sizeof(int)), *suma = malloc(sizeof(int));
    i = (int*) arg;
    for(int j = 0; j < 5; j++){
        *suma = *suma + rand()%10;
        
        printf("%d. Numero = %d\n", j+1, *suma);
    }    
    if(pthread_mutex_lock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    //seccion critica
    impar = impar + *suma;    
    //fin seccion critica
    
    if(pthread_mutex_unlock(&mutex)){
        perror("ERROR DE SEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit((void*) suma);
}
int main(int argc, char **argv){
    int *numeropar = malloc(sizeof(int));
    int *numeroimp = malloc(sizeof(int));
    int n, count = 0, sum;
    n = atoi(argv[1]);
    pthread_t hilos[n];
    srand(time(NULL));
    for(int i = 0; i < n ; ++i){
        
        if(i%2 == 0){
            if(pthread_create(&hilos[i], NULL, Opar,(void *) &count)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
                
            }
           
        }
        else if(i % 2 == 1){
            if(pthread_create(&hilos[i], NULL, Oimpar, (void *) &count)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
                
            }
           
        }
        count++;
    }
    for(int i = 0; i < n ; i++){
        if((i + 1)%2 == 0){
            if(pthread_join(hilos[i], (void**) &numeroimp)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
            }
            sum = *numeroimp;
            printf("En el hilo %d se ha sumado a par %d, y la suma total es %d\n", i+1, sum, impar);
        }
        else if((i + 1)%2 == 1){
            if(pthread_join(hilos[i], (void**) &numeropar)){
                perror("ERROR DE HILO\n");
                exit(EXIT_FAILURE);
            }
            sum = *numeropar;
            printf("En el hilo %d se ha sumado a par %d, y la suma total es %d\n", i+1, sum, par);
        }
    }
    /*for(int i = 0; i < n ; i++){
        if(i%2 == 0){
            
        }
        else if(i%2 == 1){
            
        }
    }*/
    
    
    printf("EL IMPAR ES %d Y EL PAR ES %d\n", impar, par);
    
}