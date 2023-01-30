#include <semaphore.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef struct{
    int *v;
    int tam;
}params;

pthread_mutex_t mutex;

void * consumir(void * arg){
    params * aux = (params *)arg;  
    int modelo = rand()%(aux->tam), cantidad = rand()%10+1;
    int * coches = aux->v;
    

    if(pthread_mutex_lock(&mutex) != 0){
        perror("LOCK\n");
        exit(EXIT_FAILURE);
    }

    if(coches[modelo] < cantidad){
        printf("MODELO [%d] -->EXITENCIAS [%d]. PEDIDO [%d],Nos queda --> 0\n", modelo, coches[modelo], cantidad);
        coches[modelo] = 0;
    }
    else{
        printf("MODELO [%d] -->EXITENCIAS [%d]. PEDIDO [%d],Nos queda --> %d\n", modelo, coches[modelo],cantidad, (coches[modelo] - cantidad));
        coches[modelo] -= cantidad;
    }
    for(int i = 0; i < aux->tam; i++){
        if(i == modelo)
            printf("| [%d] ", coches[i]);  
        
        else
            printf("| %d ", coches[i]);
    }
    if(pthread_mutex_unlock(&mutex) != 0){
        perror("UNLOCK\n");
        exit(EXIT_FAILURE);
    }
    printf("|\n");
    pthread_exit((void *)coches);

}
void * producir(void * arg){
    params * aux = (params *)arg;
    int modelo = rand()%(aux->tam), cantidad = rand()%10+1;
    int * coches = aux->v;

    if(pthread_mutex_lock(&mutex) != 0){
        perror("LOCK\n");
        exit(EXIT_FAILURE);
    }

    printf("MODELO [%d] -->EXITENCIAS [%d]. SUMINISTRO [%d],Tenemos --> %d\n", modelo, coches[modelo], cantidad, (coches[modelo] + cantidad));
    coches[modelo] += cantidad;
    
    for(int i = 0; i < aux->tam; i++){
        if(i == modelo)
            printf("| [%d] ", coches[i]);  
        
        else
            printf("| %d ", coches[i]);
    }
    if(pthread_mutex_unlock(&mutex) != 0){
        perror("UNLOCK\n");
        exit(EXIT_FAILURE);
    }
    printf("|\n");
    pthread_exit((void *)coches);
    
}
int main(){
    int N, M;
    printf("Introduce N clientes\n-->");
    scanf("%d", &N);
    printf("Introduce M proovedores y modelos\n-->");
    scanf("%d", &M);

    srand(time(NULL));

    if(pthread_mutex_init(&mutex, NULL) != 0){
        perror("INIT MUTEX\n");
        exit(EXIT_FAILURE);
    }

    int coches[M], *resultado;
    params aux;
    aux.v = coches;
    aux.tam = M;

    for(int i = 0; i < M; i++){
        coches[i] = 10;
    }

    pthread_t con[N], pro[M];
    for(int i = 0; i < N; i++){
        if(pthread_create(&con[i], NULL, (void *) consumir, &aux) != 0){
            perror("CREATE\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < M; i++){
        if(pthread_create(&pro[i], NULL, (void *) producir, &aux) != 0){
            perror("CREATE\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < N; i++){
        if(pthread_join(con[i], (void **)&resultado) != 0){
            perror("JOIN\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < M; i++){
        if(pthread_join(pro[i], (void **)&resultado) != 0){
            perror("JOIN\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("RESULTADO\n");
    for(int i = 0; i < M; i++){
        printf("| %d ", resultado[i]);
    }
    printf("|\n");


    if(pthread_mutex_destroy(&mutex) != 0){
        perror("DESTROY MUTEX\n");
        exit(EXIT_FAILURE);
    }

}
