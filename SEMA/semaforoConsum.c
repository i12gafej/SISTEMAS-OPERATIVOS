#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int *buffer;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * consum(void * arg){
    int* m = (int*) arg; 
    int nmo = *m, modelo = rand()%(nmo);
    int cant = rand()%10 + 1;
    
    if(cant <= buffer[modelo]){
        if(pthread_mutex_lock(&mutex)){           
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
        printf("El comprandor %ld adquiere %d cantidad de %d modelo\n", pthread_self(), cant, modelo);
        buffer[modelo] -= cant;
        for(int i = 0; i < nmo; i++){
            printf("/ %d /", buffer[i]);
        }
        printf("\n");
        if(pthread_mutex_unlock(&mutex)){           
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        if(pthread_mutex_lock(&mutex)){           
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
        printf("El comprandor %ld adquiere %d cantidad de %d modelo\n", pthread_self(), cant, modelo);
        buffer[modelo] = 0;
        for(int i = 0; i < nmo; i++){
            printf("/ %d /", buffer[i]);
        }
        printf("\n");
        if(pthread_mutex_unlock(&mutex)){           
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
    }
    
    pthread_exit(NULL);
}
void * produ(void * arg){
    int* m = (int*) arg; 
    int nmo = *m, modelo = rand()%nmo, cant = rand()% 10 +1;
    
    if(pthread_mutex_lock(&mutex)){           
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
        printf("El productor %ld añade %d cantidad de %d modelo\n", pthread_self(), cant, modelo);
        buffer[modelo] += cant;
        for(int i = 0; i < nmo; i++){
            printf("/ %d /", buffer[i]);
        }
        printf("\n");
        if(pthread_mutex_unlock(&mutex)){           
            perror("ERROR DE SEMAFORO\n");
            exit(EXIT_FAILURE);
        }
        
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    if(argc < 3 || argc > 3){
        printf("Error de argumento\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]), m = atoi(argv[2]);
    pthread_t consumi[n], product[m];
    srand(time(NULL));
    buffer = (int *)malloc(m*sizeof(int));
    for(int i = 0; i < n; i++){
        buffer[i] = rand()%100 + 1;//0+1 a 99+1
    }
    for(int i = 0; i < n; i++){
        if(pthread_create(&consumi[i], NULL, (void*)consum, &m)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < m; i++){
        if(pthread_create(&product[i], NULL, produ, &m)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < n; i++){
        if(pthread_join(consumi[i], NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < m; i++){
        if(pthread_join(product[i], NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
}