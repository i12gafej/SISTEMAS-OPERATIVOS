#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
//ABANICO

int main(int argc, char **argv){
    
    int n = atoi(argv[1]), status;
    if(n < 2){
        perror("Argumentos insuficientes\n");
        exit(EXIT_FAILURE);
    }
    pid_t hijo, flag;
    for(int i = 0; i < n; i++){
        hijo = fork();
        switch(hijo){
            case 0:
                printf("[PADRE] |%ld| --> [HIJO] |%ld|\n",(long int)getppid(), (long int)getpid());
                exit(EXIT_SUCCESS);
            break;
            case 1:
                printf("[PADRE] --> |%ld|\n", (long int)getpid());
                break;
            case -1:
                printf("Error de parir con erno %d (%s)", errno, strerror(errno));
                exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < n ; i++){
        flag = wait(&status);
        if (WIFEXITED(status)){
            printf("[PADRE] --> |%ld|, [HIJO] |%ld|  finalizado, status = %d\n", (long int)getpid(), (long int)flag, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) //Para seniales como las de finalizar o matar
        {
            printf("[PADRE] --> |%ld|, [HIJO] |%ld|  finalizado al recibir la señal %d\n", (long int)getpid(), (long int)flag, WTERMSIG(status));
        } 
    }
    if (flag==(pid_t)-1 && errno==ECHILD) //Entra cuando vuelve al while y no hay más hijos que esperar
    {
        printf("[PADRE] --> |%ld|, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", (long int)getpid(), errno, strerror(errno));
    }	
    else
    {
        printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}