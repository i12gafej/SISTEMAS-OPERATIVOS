//      A
//   b  c   d
//   e  f g  h
//   i       j

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(){
    pid_t pid , flag;
    int status;

    for(int i = 0; i < 3; i++){
        pid = fork();

        if(pid == -1){ // B <--A
            perror("ERROR DE PID\n");
            printf("ERNO (%d) s: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){
            if(i == 0){//B
                printf("HIJO --> [%ld] B de PADRE -->[%ld] A\n", (long int)getpid(), (long int)getppid());
                 pid = fork();

                if(pid == -1){ // B <--A
                    perror("ERROR DE PID\n");
                    printf("ERNO (%d) s: %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                else if(pid == 0){
                    printf("HIJO --> [%ld] E de PADRE -->[%ld] B\n", (long int)getpid(), (long int)getppid());
                    exit(EXIT_SUCCESS);
                }
                else{
                    //espera B  a E
                    while((flag=wait(&status))>0){
                        if (WIFEXITED(status)) {
                            printf("child exited, status=%d\n", WEXITSTATUS(status));


                        } else if (WIFSIGNALED(status)) {
                            printf("child killed (signal %d)\n", WTERMSIG(status));


                        } else if (WIFSTOPPED(status)) {
                            printf("child stopped (signal %d)\n", WSTOPSIG(status));


                #ifdef WIFCONTINUED     /* Not all implementations support this */
                        } else if (WIFCONTINUED(status)) {
                            printf("child continued\n");
                #endif
                        } else {    /* Non-standard case -- may never happen */
                            printf("Unexpected status (0x%x)\n", status);
                        }
                    }
                    exit(EXIT_SUCCESS);
                }
            }
            if(i == 1){//C
                printf("HIJO --> [%ld] C de PADRE -->[%ld] A\n", (long int)getpid(), (long int)getppid());
                pid = fork();

                if(pid == -1){ // F <--C
                    perror("ERROR DE PID\n");
                    printf("ERNO (%d) s: %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                else if(pid == 0){
                    printf("HIJO --> [%ld] F de PADRE -->[%ld] C\n", (long int)getpid(), (long int)getppid());
                    exit(EXIT_SUCCESS);
                }
                
                pid = fork();

                if(pid == -1){ // G <-- C
                    perror("ERROR DE PID\n");
                    printf("ERNO (%d) s: %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                else if(pid == 0){
                    printf("HIJO --> [%ld] G de PADRE -->[%ld] C\n", (long int)getpid(), (long int)getppid());
                    exit(EXIT_SUCCESS);
                }
                else{
                    //espera C  a G
                    while((flag=wait(&status))>0){
                        if (WIFEXITED(status)) {
                            printf("child exited, status=%d\n", WEXITSTATUS(status));


                        } else if (WIFSIGNALED(status)) {
                            printf("child killed (signal %d)\n", WTERMSIG(status));


                        } else if (WIFSTOPPED(status)) {
                            printf("child stopped (signal %d)\n", WSTOPSIG(status));


                #ifdef WIFCONTINUED     /* Not all implementations support this */
                        } else if (WIFCONTINUED(status)) {
                            printf("child continued\n");
                #endif
                        } else {    /* Non-standard case -- may never happen */
                            printf("Unexpected status (0x%x)\n", status);
                        }
                    }
                    exit(EXIT_SUCCESS);
                }
            }
            if(i == 2){//D
                printf("HIJO --> [%ld] D de PADRE -->[%ld] A\n", (long int)getpid(), (long int)getppid());
                pid = fork();

                if(pid == -1){ // F <--C
                    perror("ERROR DE PID\n");
                    printf("ERNO (%d) s: %s\n", errno, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                else if(pid == 0){
                    printf("HIJO --> [%ld] G de PADRE -->[%ld] D\n", (long int)getpid(), (long int)getppid());
                    exit(EXIT_SUCCESS);
                }
                else{
                    while((flag=wait(&status))>0){
                        if (WIFEXITED(status)) {
                            printf("child exited, status=%d\n", WEXITSTATUS(status));


                        } else if (WIFSIGNALED(status)) {
                            printf("child killed (signal %d)\n", WTERMSIG(status));


                        } else if (WIFSTOPPED(status)) {
                            printf("child stopped (signal %d)\n", WSTOPSIG(status));


                #ifdef WIFCONTINUED     /* Not all implementations support this */
                        } else if (WIFCONTINUED(status)) {
                            printf("child continued\n");
                #endif
                        } else {    /* Non-standard case -- may never happen */
                            printf("Unexpected status (0x%x)\n", status);
                        }
                    }
                    exit(EXIT_SUCCESS);
                }
            }
            exit(EXIT_SUCCESS);
        }
        
    }

    for(int i = 0; i < 3; i++){
        while((flag = wait(&status))>0){
            if (WIFEXITED(status)) {
                printf("child exited, status=%d\n", WEXITSTATUS(status));


            } else if (WIFSIGNALED(status)) {
                printf("child killed (signal %d)\n", WTERMSIG(status));


            } else if (WIFSTOPPED(status)) {
                printf("child stopped (signal %d)\n", WSTOPSIG(status));


    #ifdef WIFCONTINUED     /* Not all implementations support this */
            } else if (WIFCONTINUED(status)) {
                printf("child continued\n");
    #endif
            } else {    /* Non-standard case -- may never happen */
                printf("Unexpected status (0x%x)\n", status);
            }
        }
        if(flag == (pid_t)-1 && errno == ECHILD){
            printf("PADRE -->[%ld] no espera mas(%s)\n",(long int)getpid(), strerror(errno));

        }
        else{
            printf("ERROR WAIT errno = %d (%s)\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}