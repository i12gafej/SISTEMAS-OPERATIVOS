#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){
    if(argc != 2){
        perror("ARGS\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]), status, resultado = 0;
    pid_t flag;
    for(int i = 0; i < n; i++){
        switch(fork()){
            case -1:
                perror("FORK\n");
                exit(EXIT_FAILURE);
            case 0:
                printf("Padre %d con hijo %d\n", getppid(), getpid());
                exit(EXIT_SUCCESS);
            default:
                int valor = getpid()%10;
                while((flag = wait(&status))>0){
                    if (WIFEXITED(status)){
                        printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
                        resultado += WIFEXITED(status);
                    } 
                }
                
                printf("VALOR = %d\n", valor + resultado);
                resultado += valor;
                exit(resultado);
                /*int aux;
                aux = getpid()%10;
                int childpid;

                while((childpid = wait(&status))>0){
                    if(WIFEXITED(status)){
                        aux+=WEXITSTATUS(status);
                    }else if(WIFSIGNALED(status)){
                        printf("PID: %d signaled, status = %d\n", childpid, status);
                    }else if(WIFSTOPPED(status)){
                        printf("PID: %d stopped, status = %d\n", childpid, status);
                    }
                    printf("PID: %d. PID PADRE: %d. Valor recibido: %d\n", getpid(), getppid(), WEXITSTATUS(status));
                    exit(aux);
                }*/
        }
    }
    
    exit(EXIT_SUCCESS);
}