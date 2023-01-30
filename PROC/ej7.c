#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
void tratarSennal(int signo){
    if(signo == SIGUSR1)
        printf("KELOKEE \n");
    return;
}

int main(){
    int status, n = 0;
    
    pid_t hijo;
    hijo = fork();
    if(hijo == -1){
        exit(EXIT_FAILURE);
    }
    else if(hijo == 0){
        if(signal(SIGUSR1, tratarSennal) == SIG_ERR){
            perror("ERROR DE SENIAL\n");
            exit(EXIT_FAILURE);
        }
        printf("[HIJO] --> %ld con [PAPA] --> %ld\n", (long int)getpid(), (long int)getppid());
        while(n < 5){
            n++;
            pause();
        }       
        sleep(1);
        exit(EXIT_SUCCESS);
    }
    else{
        printf("Padre esperando al churumbel\n");
        n = 0;
        while(n < 5){
            sleep(1);
            n++;
            kill(hijo, SIGUSR1);
        } 
        sleep(1);
        kill(hijo, SIGKILL);
        sleep(10);
        wait(&status);
    }
    
    exit(EXIT_SUCCESS);
}