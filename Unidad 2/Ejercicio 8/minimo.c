 #include <stdio.h>
 #include <stdlib.h>

 int main(int argc, char *argv[]) {

    int min=atoi(argv[1]);

    for(int i = 1; i < argc; i++){

        if(min > atoi(argv[i])){
            min = atoi(argv[i]);
        }
    }
    printf("El mínimo es: %d\n", min);
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
 }