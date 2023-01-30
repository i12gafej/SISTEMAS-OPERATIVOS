//            a
//           / L
//           b  c
//           |
//           d


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(){
    pid_t pid, flag;
    int status;

    printf("PROCESO %d\n", getpid());
    pid = fork();//C
    switch(pid){
        case -1:{
            perror("fork\n");
            exit(EXIT_FAILURE);
        }
        case 0:{
            printf("PADRE A [%d] --> HIJO C [%d]\n", getppid(), getpid());
            exit(EXIT_SUCCESS);
        }
    }

    pid = fork();//B
    switch(pid){
        case -1:{
            perror("fork\n");
            exit(EXIT_FAILURE);
        }
        case 0:{
            printf("PADRE A [%d] --> HIJO B [%d]\n", getppid(), getpid());
            pid = fork();//D
            switch(pid){
                case -1:{
                    perror("fork\n");
                    exit(EXIT_FAILURE);
                }
                case 0:{
                    printf("PADRE B [%d] --> HIJO D [%d]\n", getppid(), getpid());
                    exit(EXIT_SUCCESS);
                }
                default:{
                    while((flag = wait(&status))>0){
                        if (WIFEXITED(status)){
                            printf("PADRE B [%ld] espera a HIJO D[%ld], status=%d\n\n",(long int)getpid(), (long int)flag, WEXITSTATUS(status));
                        }
                    }
                    if(flag == (pid_t)-1 && errno == ECHILD){
                        printf("Padre %d no tiene a mas hijos que esperar. Errno = %d. Valor de errno: %s\n", getpid(), errno, strerror(errno));
                    }
                    else{
                        printf("Error al invocar wait o waitpid. Errno = %d. Valor de errno: %s\n", errno, strerror(errno));
                        exit(EXIT_FAILURE);
                    } 
                }                   
            }
            exit(EXIT_SUCCESS);
        }
        default:{
            while((flag = wait(&status))>0){
                if (WIFEXITED(status)){
                    printf("PADRE A [%ld] espera a HIJO [%ld], status=%d\n\n",(long int)getpid(), (long int)flag, WEXITSTATUS(status));
                }
            }
            if(flag == (pid_t)-1 && errno == ECHILD){
                printf("Padre %d no tiene a mas hijos que esperar. Errno = %d. Valor de errno: %s\n", getpid(), errno, strerror(errno));
            }
            else{
                printf("Error al invocar wait o waitpid. Errno = %d. Valor de errno: %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }
    
}