#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
void * sumar5(void *arg){
    int * bif = (int*) arg, * suma = (int *)malloc(sizeof(int)), s = 0;
    printf("Sumamos : ");
    for(int i = 0; i < 5; i++){
        printf(" %i //", bif[i]);
        s += bif[i];
    }
    *suma = s;
    printf(" \nLa semisuma del vector es de %d\n", *suma);
    pthread_exit((void *) suma);
}
void * sumar2(void *arg){
    int * bif = (int*) arg, * suma = (int *)malloc(sizeof(int)), s = 0;
    printf("Sumamos : ");
    for(int i = 0; i < 2; i++){
        printf(" %d //", bif[i]);
        s += bif[i];
    }
    *suma = s;
    printf(" \nLa semisuma del vector es de %d\n", *suma);
    pthread_exit((void *) suma);
}
int main(int argc, char **argv){
    int n = atoi(argv[1]);
    if(argc < 2 || argc > 2 ){
        printf("Error de argumento"); 
        exit(EXIT_FAILURE);   
    }
    if(n != 5 && n != 2){
       printf("Error de numero"); 
       printf("%d", n);
        exit(EXIT_FAILURE);          
    }
    int v[10], *semiresul, total = 0;
    srand(time(NULL));
    for(int i = 0; i < 10; i++){
        v[i] = rand()%9 + 1;
        
    }
    if(atoi(argv[1]) == 2){
        pthread_t hilo[2];
        int * bif = (int*)malloc(5*sizeof(int));
        int * bif2 = (int*)malloc(5*sizeof(int));

        for(int j = 0; j < 2; j++){
            if(j == 0){
                for(int i = 0; i < 5; i++){
                    bif[i] = v[i];
                    printf("Bif[%i] = %i\n", i, bif[i]);
                }
                if(pthread_create(&hilo[j], NULL, sumar5, (void *) bif)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                for(int i = 0; i < 5; i++){
                    bif2[i] = v[i+5];
                    printf("Bif2[%i] = %i\n", i, bif2[i]);
                }
                if(pthread_create(&hilo[j], NULL, sumar5, (void *) bif2)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }
            }            
        }
        //printf("Total = %d\n", total);
        for(int i = 0; i < 2; i++){
            if(pthread_join(hilo[i], (void **)&semiresul)){
                perror("ERROR DE RECOGIDA\n");
                exit(EXIT_FAILURE);
            }
            total += *semiresul;
            
        }

        free(bif);
        free(bif2);
    }
    else if(atoi(argv[1]) == 5){
        pthread_t hilo[5];
        int * bif = (int*)malloc(2*sizeof(int));
        int * bif2 = (int*)malloc(2*sizeof(int));
        int * bif3 = (int*)malloc(2*sizeof(int));
        int * bif4 = (int*)malloc(2*sizeof(int));
        int * bif5 = (int*)malloc(2*sizeof(int));


        for(int i = 0; i < 5; i++){
            if(i == 0){
                bif[0] = v[0];
                bif[1] = v[1];
                if(pthread_create(&hilo[i], NULL, sumar2, (void *) bif)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }
            }
            else if(i == 1){
                bif2[0] = v[2];
                bif2[1] = v[3];
                if(pthread_create(&hilo[i], NULL, sumar2, (void *) bif2)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }
            }
            else if(i == 2){
                bif3[0] = v[4];
                bif3[1] = v[5];
                if(pthread_create(&hilo[i], NULL, sumar2, (void *) bif3)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }                
            }
            else if(i == 3){
                bif4[0] = v[6];
                bif4[1] = v[7];
                if(pthread_create(&hilo[i], NULL, sumar2, (void *) bif4)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }                
            }
            else if(i == 4){
                bif5[0] = v[8];
                bif5[1] = v[9];
                if(pthread_create(&hilo[i], NULL, sumar2, (void *) bif5)){
                    perror("ERROR DE HILO\n");
                    exit(EXIT_FAILURE);
                }                
            }
            
        }
        for(int i = 0; i < 5; i++){
            if(pthread_join(hilo[i], (void **)&semiresul)){
                perror("ERROR DE RECOGIDA\n");
                exit(EXIT_FAILURE);
            }
            total += *semiresul;
        }
        free(bif);
        free(bif2);
        free(bif3);
        free(bif4);
        free(bif5);        
    }
    printf("El resultado es %d\n", total);
}
