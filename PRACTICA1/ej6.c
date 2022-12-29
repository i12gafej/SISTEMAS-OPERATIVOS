#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
void controlar(int signo){
    printf("SHtire, SHtire la camisete\n");
}
unsigned int f(int nsecs){
    alarm(nsecs);
    pause();
}
int main(){
    if(signal(SIGALRM, controlar) == SIG_ERR){
        perror("ERROR DE SENIAL\n");
        exit(EXIT_FAILURE);
    }
    printf("Primer ring\n");
    f(5);
    printf("Segundo ring\n");
    f(3);
    int n = 0;
    while(1){
        n++;
        printf("TIMBRE %d: ", n);
        f(1);
        
        if(n == 4){
            kill(getpid(), SIGKILL);
        }
    }
    exit(EXIT_SUCCESS);
}
