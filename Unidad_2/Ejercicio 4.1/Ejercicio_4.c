/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {
 
    double promedio=0;
    int suma=0;
    int max=atoi(argv[1]);
    int min=atoi(argv[1]);
    
    for(int i = 1; i < argc; i++){
     
        suma = suma + atoi(argv[i]);
        
        if(max < atoi(argv[i])){
            max = atoi(argv[i]);
        }
        
        if(min > atoi(argv[i])){
            min = atoi(argv[i]);
        }
    }
    promedio = (double)suma/(argc-1);
    printf("El máximo es: %d\n", max);
    printf("El mínimo es: %d\n", min);
    printf("El promedio es: %f\n", promedio);
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
 }
