#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int enteros[3];
int pposi = 0;
int cposi = 0;
int p = 0;
int c = 0;
sem_t s;
sem_t pr;
sem_t cn;
void * prod(){    
    if(sem_wait(&pr) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    if(sem_wait(&s) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    pposi++;
    int nPRO = rand()%101;
    enteros[p] = nPRO;
    p = (p+1)%3;
    for(int j = 0; j < 3; j++){
        printf("|%d", enteros[j]);
    }
    printf("|");
    printf("---->Productor, Dato %d: %d\n", pposi, nPRO);
    if(sem_post(&s) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    } 
    if(sem_post(&cn) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }    
}
void * consum(){
    if(sem_wait(&cn) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    if(sem_wait(&s) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    cposi++;
    int nCON = enteros[c];
    enteros[c] = '\0';
    c = (c + 1)%3;
    for(int j = 0; j < 3; j++){
        printf("|%d", enteros[j]);
    }
    printf("|");
    printf("---->Consumidor, Dato %d: %d\n", cposi, nCON);
    printf("En la posicion %d del array se ha consumido %d\n", c, enteros[c]);
    if(sem_post(&s) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }
    if(sem_post(&pr) == -1){
        perror("ERROR DESEMAFORO\n");
        exit(EXIT_FAILURE);
    }  
}
int main(){
    srand(time(NULL));
    sem_init(&s, 0, 1);
    sem_init(&pr, 0, 3);
    sem_init(&cn, 0, 0);
    pthread_t hilo1[3];
    pthread_t hilo2[3];
    for(int i = 0; i < 3; i++){
        if(pthread_create(&hilo1[i], NULL, consum ,NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < 3; i++){
        if(pthread_create(&hilo2[i], NULL, prod, NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < 3; i++){
        if(pthread_join(hilo1[i], NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }
     for(int i = 0; i < 3; i++){
        if(pthread_join(hilo2[i], NULL)){
            perror("ERROR DE HILO\n");
            exit(EXIT_FAILURE);
        }
    }

}

/*
En concurrencia, el problema del productor-consumidor es un problema típico, y su enunciado
general es el siguiente:
-Hay un proceso generando algún tipo de datos (registros, caracteres, aumento de variables,
modificaciones en arrays, modificación de ficheros, etc) y poniéndolos en un buffer. Hay un
consumidor que está extrayendo datos de dicho buffer de uno en uno.
-El sistema está obligado a impedir la superposición de las operaciones sobre los datos, es decir, sólo
un agente (productor o consumidor) puede acceder al buffer en un momento dado (así el productor
no sobrescribe un elemento que esté leyendo el consumidor, y viceversa). Estaríamos hablando de
la sección crítica.
-Si suponemos que el buffer es limitado y está completo, el productor debe esperar hasta que el
consumidor lea al menos un elemento para así poder seguir almacenando datos. En el caso de que el
buffer esté vacío el consumidor debe esperar a que se escriba información nueva por parte del
productor

a) Implemente el problema para hilos, teniendo en cuenta que la sección crítica va a ser un
array de enteros con una capacidad de 5 elementos y donde habrá un productor y un
consumidor. Se podrán producir-consumir 10 elementos.

*/