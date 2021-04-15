#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <string.h>

void imprimirarchivo(char archivo[15]){

    FILE *in_file;
    char ruta[30] = "/home/juancardozo/Documents/";
    char registro[50];
    char aux[2];
    strcat(ruta,archivo);

    in_file = fopen(ruta, "r");

    if(in_file == NULL)
	{
		printf("El archivo especificado no existe %s\n", ruta);
		exit(8);
	}

    do{

        printf("%s", registro);
        fgets(registro, 49, in_file);
        

    }while(!feof(in_file));
}

int main(int argc, char *argv[]) {

    pid_t pid1, pid2;
    int status1, status2;

    
    if ( (pid1=fork()) == 0 )
    { 
        char *args[]={"./p1", argv[1], argv[2], NULL};
        execv(args[0],args);  
    }
    else
    { 
        if ((pid2=fork()) == 0 )
        {
            char *args[]={"./p2", argv[1], argv[3], NULL};
            execv(args[0],args); 
        }
        else
        {
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            printf("=========Registro 1=========\n");
            imprimirarchivo(argv[1]);
            printf("=========Registro 2=========\n");
            imprimirarchivo(argv[2]);
            printf("=========Registro 3=========\n");
            imprimirarchivo(argv[3]); 
            printf("Soy el padre con PID %d\n", getpid());
        }
    }
    
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
}