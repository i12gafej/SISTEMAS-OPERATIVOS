#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
typedef struct {
    int modelos_disponibles;
    int modelo_elegido;
    int cantidad;
}NOTAS;

int camisetas[] = {0,0,0,0,0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  

void rellenarVector(int v[], int modelos){
    for(int i = 0 ; i < modelos; i++){
        v[i] = rand()%100 + 1;
    }
}

void * algo(void* arg){
    NOTAS * n; 
    n = (NOTAS*) arg;
    
    n->modelo_elegido = rand()%n->modelos_disponibles;
    n->cantidad = rand()%11;
    pthread_exit((void**)n);
}
int main(){
    NOTAS  * m = malloc(sizeof(NOTAS));
    int n;
    srand(time(NULL));

    printf("Introduzca el numero de clientes\n-->");
    scanf("%d", n);
    pthread_t hilos[n];
    printf("Introduzca el numero de proveedores\n-->");
    scanf("%d", m->modelos_disponibles);

    
    rellenarVector(camisetas, m->modelos_disponibles);
    for(int i = 0; i < n; i++){
        if(pthread_create(hilos+1, NULL, (void*) algo, (void *)&m)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
}
