#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(){
    int status;
    pid_t zombi;
    zombi = fork();
    if(zombi == 0){
        printf("[HIJO ZOMBI]--> %ld\n", (long int)getpid());
        exit(EXIT_SUCCESS);
    }
    else if(zombi == -1){
        exit(EXIT_FAILURE);
    }
    else{
        sleep(5);
        printf("ESPERAO\n");
        wait(&status);
        printf("MANIN\n");
        
    }
    printf("CHAVEA\n");
    sleep(3);
    exit(EXIT_SUCCESS);
}