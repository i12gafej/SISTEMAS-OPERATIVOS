#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){
    
    int n = atoi(argv[1]), status;
    if(argc < 2){
        perror("Argumentos insuficientes\n");
        exit(EXIT_FAILURE);
    }
    pid_t hijo, flag;
    for(int i = 0; i < n; i++){
        hijo = fork();
        switch(hijo){
            case -1:
                printf("Error de parir con erno %d (%s)", errno, strerror(errno));
                exit(EXIT_FAILURE);
            
            case 0:
                printf("[PADRE] |%ld| --> [HIJO] |%ld|\n",(long int)getppid(), (long int)getpid());
            break;
            default:
                printf("[PADRE] --> |%ld|\n", (long int)getpid());
                while ( (flag=waitpid(-1,&status,WUNTRACED | WCONTINUED)) > 0 ) 
                {
                    if (WIFEXITED(status)) 
                    {
                        printf("[PADRE] --> %d, [HIJO] --> %ld RECOGIDO, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
                    } 
                    else if (WIFSIGNALED(status))  
                    {
                        printf("[PADRE] --> %d, [HIJO] --> %ld RECOGIDO POR SEÑAL --> %d\n", getpid(), (long int)flag, WTERMSIG(status));
                    } 
                    else if (WIFSTOPPED(status))  //Para cuando se para un proceso. Con wait() no nos serviria.
                    {
                        printf("[PADRE] --> %d, [HIJO] --> %ld PARADO POR SEÑAL --> %d\n", getpid(), (long int)flag,WSTOPSIG(status));
                    } 
                    else if (WIFCONTINUED(status))  //Para cuando se reanuda un proceso parado. Con wait() no nos serviria.
                    {
                        printf("[PADRE] --> %d, [HIJO] --> %ld reanudado\n", getpid(), (long int) flag);		  
                    }
                }//while

                if (flag==(pid_t)-1 && errno==ECHILD)
                {
                    printf("[PADRE] --> %d, HAS ESPERADO A TODOS. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
                }
                else
                {
                    printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }	 
                exit(EXIT_SUCCESS);
        }
    }
}
