#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int n = atoi(argv[1]), m = n;
    if(n == 0){
        printf("FACTORIAL ES 1");
    }
    for(int i = 1; i < m; i++){
        n = n*i;
    }
    printf("FACTORIAL ES %d\n", n);
}
