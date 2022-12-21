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

void * cliente(void* arg){
    NOTAS * n; 
    n = (NOTAS*) arg;
    
    n->modelo_elegido = rand()%5;
    n->cantidad = rand()%10 + 1;
    
    if(pthread_mutex_lock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }

    //seccion crittica
    camisetas[n->modelo_elegido - 1] -= n->cantidad;
    //fin seccion critica
    if(pthread_mutex_unlock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);
}
void * proveedor(void * arg){
    NOTAS * n; 
    n = (NOTAS*) arg;
    
    n->modelo_elegido = rand()%5;
    n->cantidad = rand()%10 + 1;
    
    if(pthread_mutex_lock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }

    //seccion crittica
    camisetas[n->modelo_elegido - 1] += n->cantidad;
    //fin seccion critica
    if(pthread_mutex_unlock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);
}
int main(){
    NOTAS  * m = malloc(sizeof(NOTAS));
    int n;
    srand(time(NULL));

    printf("Introduzca el numero de clientes\n-->");
    scanf("%d", n);
    pthread_t clientes[n];
    printf("Introduzca el numero de proveedores\n-->");
    scanf("%d", m->modelos_disponibles);
    pthread_t proveedores[m->modelos_disponibles];

    rellenarVector(camisetas, n);
    for(int i = 0; i < n; i++){
        if(pthread_create(clientes+1, NULL, (void*) cliente, (void *)&m)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < m->modelos_disponibles; i++){
        if(pthread_create(proveedores+1, NULL, (void*) proveedor, (void *)&m)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < n; i++){
        if(pthread_join(clientes[i], NULL)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < m->modelos_disponibles; i++){
        if(pthread_join(proveedores[i], NULL)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
    
}
