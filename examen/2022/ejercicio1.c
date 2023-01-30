#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char **argv){
    pid_t pid, flag;
    int status;

    if(argc != 2){
        perror("arguments\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    pid = fork();
    if(pid == -1){
        perror("FORK\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        printf("PADRE [%d] --> HIJO [%d]\n", getppid(), getpid());
        for(int i = 0; i < n; i++){
            pid = fork();
            if(pid == -1){
                perror("FORK\n");
                exit(EXIT_FAILURE);
            }
            else if(pid == 0){
                printf("PADRE [%d] --> HIJO [%d]\n", getppid(), getpid());
                exit(EXIT_SUCCESS);
            }
            else{
                //printf("Esperando a hijo\n");
            }
        }
        while ( (flag=wait(&status)) > 0 ){
            if (WIFEXITED(status)){
                printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
            } 
        }
        exit(EXIT_SUCCESS);
    }
    

    while ( (flag=wait(&status)) > 0 ){
        if (WIFEXITED(status)){
            printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
        } 
    }
    if (flag==(pid_t)-1 && errno==ECHILD){ //Entra cuando vuelve al while y no hay más hijos que esperar
    
        printf("Proceso padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
    }	
    else{
        printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}

/*while ( (flag=wait(&status)) > 0 ){
        if (WIFEXITED(status)){
            printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)){ //Para seniales como las de finalizar o matar
            printf("Proceso padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)flag, WTERMSIG(status));
        } 
    }

    if (flag==(pid_t)-1 && errno==ECHILD){ //Entra cuando vuelve al while y no hay más hijos que esperar
    
        printf("Proceso padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
    }	
    else{
        printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }*/