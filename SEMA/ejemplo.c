#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int c = 10;
void * incremento(){
    for(int i = 0; i < 10000; i++){
        if(pthread_mutex_lock(&mutex)){
            perror("FALLO SSEM");
            exit(EXIT_FAILURE);
        }
        c++;
        if(pthread_mutex_unlock(&mutex)){
            perror("FALLO SSEM");
            exit(EXIT_FAILURE);
        }
    }
    //printf("FINAL INCREMENTO: %d\n",c);    
}
void * decremento(){
    for(int i = 0; i < 10000; i++){
        if(pthread_mutex_lock(&mutex)){
            perror("FALLO SSEM");
            exit(EXIT_FAILURE);
        }
        c--;
        if(pthread_mutex_unlock(&mutex)){
            perror("FALLO SSEM");
            exit(EXIT_FAILURE);
        }
    }
    //printf("FINAL DECREMENTO: %d\n",c);    
}
int main(){
    pthread_t uno, dos;
    if(pthread_create(&uno, NULL, incremento, NULL)){
        perror("MAAAAAL 1");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&dos, NULL, decremento, NULL)){
        perror("MAAAAAL 2");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(uno, NULL)){
        perror("MAAAAAL 1");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(dos, NULL)){
        perror("MAAAAAL 1");
        exit(EXIT_FAILURE);
    }
    printf("FINAL DECREMENTO: %d\n",c);    
    
}