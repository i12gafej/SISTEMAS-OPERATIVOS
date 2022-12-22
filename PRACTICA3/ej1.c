#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int camisetas[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  

void rellenarVector(int v[], int modelos){
    for(int i = 0 ; i < modelos; i++){
        v[i] = rand()%100 + 1;
    }
}
void * cliente(){
    int i = rand()%20 + 1;
    int cantidad = rand()%10 + 1;
    printf("El comprador %ld va a adquirir %d camisetas del tipo %d\n", pthread_self(), cantidad, i);
    if(pthread_mutex_lock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }

    //seccion crittica
    camisetas[i - 1] = camisetas[i - 1] - cantidad;
    //fin seccion critica
    if(pthread_mutex_unlock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);
}
void * proveedor(){
    int i = rand()%20 + 1;
    int cantidad = rand()%10 + 1;
    printf("El vendedor %ld va a suministrar %d camisetas del tipo %d\n", pthread_self(), cantidad, i);
    if(pthread_mutex_lock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }

    //seccion crittica
    camisetas[i - 1] = camisetas[i - 1] + cantidad;
    //fin seccion critica
    if(pthread_mutex_unlock(&mutex)){
        perror("Error de semaforo");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv){
    int n, provs;
    n = atoi(argv[1]);
    provs = atoi(argv[2]);

    srand(time(NULL));
   
    rellenarVector(camisetas, provs);
    printf("ABRIMOS LA TIENDA\n------------------------------------------------------------\n");
    for(int i = 0; i<provs; i++){
        printf("- Camisetas del tipo %d : %d\n", i+1, camisetas[i]);
    }
    pthread_t clientes[n];
    pthread_t proveedores[provs];
     for(int i = 0; i < n; i++){
        if(pthread_create(&clientes[i], NULL, cliente, NULL)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < provs; i++){
        if(pthread_create(&proveedores[i], NULL, proveedor, NULL)!=0){
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
    for(int i = 0; i < provs; i++){
        if(pthread_join(proveedores[i], NULL)!=0){
            perror("Hilo fallido");
            exit(EXIT_FAILURE);
        }
    }
    printf("CERRAMOS LA TIENDA\n------------------------------------------------------------\n");
    for(int i = 0; i<provs; i++){
        printf("- Camisetas del tipo %d : %d\n", i+1, camisetas[i]);
    }
}
