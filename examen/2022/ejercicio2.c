#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int global = 1;
pthread_mutex_t semaforo;


void * h1(int * arg){
	int * retorno = (int *)malloc(sizeof(int));
	if(pthread_mutex_lock(&semaforo) != 0){
		perror("semaforo\n");
		exit(EXIT_FAILURE);
	}

	global += (*arg);
	printf("VAlor en %lu de global: %d\n", pthread_self(), global);

	if(global%2 == 0)
		*retorno = 0;
	else
	 	*retorno = 1;

	if(pthread_mutex_unlock(&semaforo) != 0){
		perror("semaforo\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void * )retorno);

}

void * h2(int * arg){
	int * retorno = (int *)malloc(sizeof(int));
	if(pthread_mutex_lock(&semaforo) != 0){
		perror("semaforo\n");
		exit(EXIT_FAILURE);
	}

	global *= (*arg);
	printf("VAlor en %lu de global: %d\n", pthread_self(), global);
	if(global%2 == 0)
		*retorno = 0;
	else
	 	*retorno = 1;

	if(pthread_mutex_unlock(&semaforo) != 0){
		perror("semaforo\n");
		exit(EXIT_FAILURE);
	}
	pthread_exit((void * )retorno);

}

int main(int argc, char** argv){
	if(argc != 3){
		perror("error de argumentos\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_mutex_init(&semaforo, NULL) != 0){
		perror("error inicio semaforo\n");
		exit(EXIT_FAILURE);
	}
	int ent1 = atoi(argv[1]);
	int ent2 = atoi(argv[2]);
	int *retorno;
	int res;

	pthread_t hilo1, hilo2;
	if(pthread_create(&hilo1, NULL, (void* )h1, &ent1) != 0){
		perror("pthread create\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&hilo2, NULL, (void* )h2, &ent2) != 0){
		perror("pthread create\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_join(hilo1, (void **)&retorno) != 0){
		perror("join\n");
		exit(EXIT_FAILURE);
	}
	res = *retorno;
	free(retorno);

	printf("Para el hilo %lu el resultado es: %d\n", (long int)hilo1, res);

	if(pthread_join(hilo2, (void **)&retorno) != 0){
		perror("join\n");
		exit(EXIT_FAILURE);
	}

	res = *retorno;
	free(retorno);

	printf("Para el hilo %lu el resultado es: %d\n", (long int)hilo2, res);

	if(pthread_mutex_destroy(&semaforo) != 0){
		perror("semaforo\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);

}
