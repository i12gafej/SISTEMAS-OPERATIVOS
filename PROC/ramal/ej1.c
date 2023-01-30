//            a
//           / L
//           b  c
//              / L
//              e  f
//                  L
//                  g


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


    pid = fork();

    if(pid == -1){ // B <--A
        perror("ERROR DE PID\n");
        printf("ERNO (%d) s: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        printf("HIJO --> [%ld] B de PADRE -->[%ld] A\n", (long int)getpid(), (long int)getppid());
        exit(EXIT_SUCCESS);
    }
    
    pid = fork();
    if(pid == -1){ // C <--A
        perror("ERROR DE PID\n");
        printf("ERNO (%d) s: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ //C
        printf("HIJO --> [%ld] C de PADRE -->[%ld] A\n", (long int)getpid(), (long int)getppid());
        pid = fork();
        if(pid == -1){ // E <--C
            perror("ERROR DE PID\n");
            printf("ERNO (%d) s: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){
            printf("HIJO --> [%ld] E de PADRE -->[%ld] C\n", (long int)getpid(), (long int)getppid());
            
            exit(EXIT_SUCCESS);
        }
        pid = fork();
        if(pid == -1){ // F <--C
            perror("ERROR DE PID\n");
            printf("ERNO (%d) s: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){
            printf("HIJO --> [%ld] F de PADRE -->[%ld] C\n", (long int)getpid(), (long int)getppid());
            pid = fork();
            if(pid == -1){ // G <--F
                perror("ERROR DE PID\n");
                printf("ERNO (%d) s: %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
            }
            else if(pid == 0){
                printf("HIJO --> [%ld] G de PADRE -->[%ld] F\n", (long int)getpid(), (long int)getppid());
                
                exit(EXIT_SUCCESS);
            }
            else{
                int dato_f;
                while((flag=wait(&status))>0)
                {
                    dato_f=WEXITSTATUS(status);

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

                
                
                exit(dato_f + getpid()%10);
                //espera de f a g
            }
            exit(EXIT_SUCCESS);
        }
        else{
            int dato_f;
                while((flag=wait(&status))>0)
                {
                    dato_f=WEXITSTATUS(status);

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
                if(flag==(pid_t)-1 && errno==ECHILD)
                { 
                    printf("Valor del errno= %d, definido como %s\n",errno,strerror(errno));
                }
                else
                {
                    printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal\n");
                    exit(EXIT_FAILURE);
                } 
                exit(EXIT_SUCCESS);
            //espera de c a f
        }
        //
        exit(EXIT_SUCCESS);
    }
    else{
        int dato_f;
                while((flag=wait(&status))>0)
                {
                    dato_f=WEXITSTATUS(status);

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
                if(flag==(pid_t)-1 && errno==ECHILD)
                { 
                    printf("Valor del errno= %d, definido como %s\n",errno,strerror(errno));
                }
                else
                {
                    printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal\n");
                    exit(EXIT_FAILURE);
                } 
                exit(EXIT_SUCCESS);
        //espera de a a c
    }
}
