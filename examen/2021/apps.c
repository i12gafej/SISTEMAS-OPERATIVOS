#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ./apps xclock gnome-calculator 
int main(int argc, char ** argv){
    int n, status;
    pid_t pid, childpid;

    if(argc != 3){
        perror("argumentos\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 2; i++){
        pid = fork();
        switch(pid){
            case 0:{
                printf("Padre %d con hijo %d\n", getppid(), getpid());
                if(i == 0){
                    execlp(argv[1], argv[1], NULL);
                }
                else{
                    execlp(argv[2], argv[2], NULL);
                }
                exit(EXIT_SUCCESS);
            }
            case -1:
                printf("Error fork. Errno = %d\n", errno);
                exit(EXIT_FAILURE);
            default:
                printf("Padre %d espera hijo\n", getpid());
                break;
        }
    }
    while((childpid = wait(&status))>0){
        
        if(WIFEXITED(status)){
            printf("Padre %ld ha esperado a hijo %ld exitosamente, status=%d\n",(long int)getpid(), (long int)childpid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) //Para seniales como las de finalizar o matar
        {
            printf("[PADRE] --> |%ld|, [HIJO] |%ld|  finalizado al recibir la señal %d\n", (long int)getpid(), (long int)childpid, WTERMSIG(status));
        } 
    }
    if(childpid==(pid_t)-1 && errno == ECHILD){
        printf("Proceso padre %d no tiene mas hijos a los que esperar.Valor de errno %d, definido como %s\n", getpid(), errno, strerror(errno));
    }
    else{
        printf("Erro en la invocacion de wait o waitpid. Valor de errno %d, definido como %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}