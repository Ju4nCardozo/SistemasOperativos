#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

    int max=atoi(argv[1]);

    for(int i = 1; i < argc; i++){
        if(max < atoi(argv[i])){
            max = atoi(argv[i]);
        }
    }
    printf("El máximo es: %d\n", max);
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
}