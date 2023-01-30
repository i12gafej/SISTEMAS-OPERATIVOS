#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int factorial(int x){
    if(x == 0){
        return 1;
    }
    else if(x < 0)
        return -1;
    else{
        int f = 1;
        for(int i = 1; i <= x; i++){
            f = f*i;
        }
        return f;
    }
}
int main(int argc, char ** argv){
    if(argc != 2){
        perror("args\n");
        exit(EXIT_FAILURE);
    }
    int A = atoi(argv[1]), status;
    pid_t pid, flag;

    for(int i = 0; i < 2; i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("fork\n");
                exit(EXIT_FAILURE);
            case 0:
                if(i == 0){
                    printf("Padre %d con hijo %d y factorial de A es %d\n", getppid(), getpid(), factorial(A));
                }
                else{
                    printf("Padre %d con hijo %d\n", getppid(), getpid());
                    execlp("gnome-calculator","gnome-calculator", NULL);
                }
                exit(EXIT_SUCCESS);
            default:
                printf("Padre %d espera a hijo\n", getpid());
                break;
        }
    }
    while((flag = wait(&status))>0){
        if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));
        }
    }
    if(errno == ECHILD && flag == (pid_t)-1){
        printf("Proceso padre %d no tiene a mas hijos a los que esperar. Errno = %d, valor de errno: %s\n", getpid(), errno, strerror(errno));
    }
    else{
        printf("Error al invocar wait o waitpid. Errno = %d, valor de errno: %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}