#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t sem;

void rellenaVector(int v[], int camisetas)
{
	for (int i = 0; i < camisetas; ++i)
	{
		v[i] = rand()%100;
	}
}

void *funcionCliente(int *arg)
{
	int ;

	for (int i = 0; i < (*arg); ++i)
	{
		suma += (rand()%10);
	}
	printf("Cliente %lu, compro id %d unidades de la camiseta %d\n", );
	int retorno = (int)malloc(sizeof(int));//creamos puntero y reservamos memoria
	(*retorno) = ;//igualamos a lo que se va a retornar
	pthread_exit((void*)retorno);////retornamos
}

void *funcionProveedor(int *arg)
{
	int ;
	for (int i = 0; i < (*arg); ++i)
	{
		suma += (rand()%10);
	}
	printf("Proveedor %lu, suministro %d unidades de la camiseta %d\n", );
	int retorno = (int)malloc(sizeof(int));//creamos puntero y reservamos memoria
	(*retorno) = ;//igualamos a lo que se va a retornar
	pthread_exit((void*)retorno);////retornamos
}

int main(int argc, char const *argv[])
{
	if( argc != 3)
	{
		perror("Error en línea de argumentos, debe introducir 3 argumentos obligatoriamente.\n");
        printf("Error value = %d\n",errno);
        exit(EXIT_FAILURE);
	}

	int N=atoi(argv[1]);
	int M=atoi(argv[2]);

	pthread_t clientes[N], proveedores[M]; //creo vector de clientes y proveedores

	int arg[N];
	srand(time(NULL));

	rellenaVector(proveedores[M], M);

	if(pthread_mutex_init(&sem) != 0)
	{
		perror("Error en la espera del hilo %d.\n", j);
        printf("Error value = %d\n",errno);
        exit(EXIT_FAILURE);
	}

	for (int i = 0; i < N; ++i)
	{
		arg[i] = rand()%10:

		if(pthread_create(&id1[i], NULL, (void*) , ) != 0)
		{
			perror("Error en la creacion del hilo %d.\n", i);
	        printf("Error value = %d\n",errno);
	        exit(EXIT_FAILURE);
		}
	}

	for (int j = 0; j < M; ++j)
	{
		if (pthread_create(&id2[j], NULL, (void*) , ) != 0)
		{
			perror("Error en la creacion del hilo %d.\n", j);
	        printf("Error value = %d\n",errno);
	        exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < N; ++i)
	{
		if (pthread_join(clientes[i], (void**)NULL) != 0)
		{
			perror("Error en la espera del hilo %d.\n", i);
	        printf("Error value = %d\n",errno);
	        exit(EXIT_FAILURE);
		}
	}

	for (int j = 0; j < M; ++j)
	{
		if (pthread_join(proveedores[i], (void**)NULL) != 0)
		{
			perror("Error en la espera del hilo %d.\n", j);
	        printf("Error value = %d\n",errno);
	        exit(EXIT_FAILURE);
		}
	}

	if(pthread_mutex_destroy(&sem) != 0)
	{
		perror("Error en la espera del hilo %d.\n", j);
        printf("Error value = %d\n",errno);
        exit(EXIT_FAILURE);
	}

	return 0;
}