#include <stdio.h>

int main(){
    char *fichero = "fich1.txt";
    FILE *f = fopen(fichero, "rt");
    char ca[200];
    int nlineas = 0;
    printf("ILLOO\n");
    while(fgets(ca, 200, f) != NULL){
        printf("ILLOO\n");
        (nlineas)++;
    }
    printf("Las lienas son %d\n", nlineas);
}