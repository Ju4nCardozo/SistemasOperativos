#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    double promedio=0;
    int suma=0;

    for(int i = 1; i < argc; i++){
     
        suma = suma + atoi(argv[i]);
    }
    promedio = (double)suma/(argc-1);
    printf("El promedio es: %f\n", promedio);
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
}
