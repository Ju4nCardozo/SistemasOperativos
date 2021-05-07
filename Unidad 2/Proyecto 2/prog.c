#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont = 0;

typedef struct personas{
    char nombre[21];
    char ocupacion[21];
    int edad;
}pers;

struct parametros_hilo {
    pers personas[100];
    char ruta[30];
};

void *ordeninverso(void* parametros){

    struct parametros_hilo* param = (struct parametros_hilo*) parametros;
    pers p[100];
	for(int i = 0; i < cont; i++)
	{
		strcpy(p[i].nombre, param->personas[i].nombre);
		strcpy(p[i].ocupacion, param->personas[i].ocupacion);
		p[i].edad = param->personas[i].edad;
	}
    FILE *in_file;

    for(int i = 0; i < cont/2; i++)
	{
		int tempv = p[i].edad;
		char tempn[21];
        char tempo[21];
        strncpy(tempn,p[i].nombre,20);
        strncpy(tempo,(p+i)->ocupacion,20);
        p[i].edad = p[cont-1-i].edad;
        strncpy(p[i].nombre, p[cont-1-i].nombre,20);
        strncpy(p[i].ocupacion, p[cont-1-i].ocupacion,20);
        strncpy(p[cont-1-i].nombre,tempn,20);
        strncpy(p[cont-1-i].ocupacion,tempo,20);
        p[cont-1-i].edad = tempv;
	}
	in_file = fopen(param->ruta, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %s %d\n", p[i].nombre, p[i].ocupacion, p[i].edad);
	}
	fclose(in_file);

    return NULL;
}

void *ordenalfabetico(void* parametros2){

   	struct parametros_hilo* param2 = (struct parametros_hilo*) parametros2;
    pers p2[100];
	for(int i = 0; i < cont; i++)
	{
		strcpy(p2[i].nombre, param2->personas[i].nombre);
		strcpy(p2[i].ocupacion, param2->personas[i].ocupacion);
		p2[i].edad = param2->personas[i].edad;
	}
    FILE *in_file;

    for(int i = 0; i < cont; i++){
        for(int j = 0; j < cont; j++){
            if(strcmp(p2[j].ocupacion,p2[i].ocupacion)>0){
                
                int tempv = p2[i].edad;
				char tempn[21];
                char tempo[21];
                strncpy(tempn,p2[i].nombre,20);
                strncpy(tempo,p2[i].ocupacion,20);
				p2[i].edad = p2[j].edad;
				strncpy(p2[i].ocupacion,p2[j].ocupacion,20);
                strncpy(p2[i].nombre,p2[j].nombre,20);
				p2[j].edad = tempv;
				strncpy(p2[j].ocupacion,tempo,20);
                strncpy(p2[j].nombre,tempn,20);
            }
        }
    }
    in_file = fopen(param2->ruta, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %s %d\n", p2[i].nombre, p2[i].ocupacion, p2[i].edad);
	}
	fclose(in_file);

    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t id_hilo1;
    pthread_t id_hilo2;
    pers pers3[100];
    struct parametros_hilo hilo1_param;
    struct parametros_hilo hilo2_param;
	char ruta[100]="/home/juancardozo/Documents/";
    char ruta1[100]="/home/juancardozo/Documents/";
    char ruta2[100]="/home/juancardozo/Documents/";
    FILE *in_file;
    
    
    strcat(ruta, argv[1]);

    in_file = fopen(ruta, "r");

	if(in_file == NULL)
	{
		printf("El archivo especificado no existe %s\n", argv[1]);
		exit(8);
	}

	while(!feof(in_file))
	{
        fscanf(in_file, "%s", &pers3[cont].nombre);
        fscanf(in_file, "%s", &pers3[cont].ocupacion);
        fscanf(in_file, "%d", &pers3[cont].edad);
		cont++;
	}
	fclose(in_file);
    cont--;

    for(int i = 0; i < cont; i++)
    {
        printf("%s %s %d\n",pers3[i].nombre, pers3[i].ocupacion, pers3[i].edad);
    }

    strcat(ruta1,argv[2]);
    strcpy(hilo1_param.ruta, ruta1);
    strcat(ruta2,argv[3]);
    strcpy(hilo2_param.ruta, ruta2);
    for(int i = 0; i < cont; i++)
	{
        strcpy(hilo1_param.personas[i].nombre, pers3[i].nombre);
		strcpy(hilo2_param.personas[i].nombre, pers3[i].nombre);
		strcpy(hilo1_param.personas[i].ocupacion, pers3[i].ocupacion);
		strcpy(hilo2_param.personas[i].ocupacion, pers3[i].ocupacion);
		hilo1_param.personas[i].edad = pers3[i].edad;
		hilo2_param.personas[i].edad = pers3[i].edad;
    }


    pthread_create (&id_hilo1,NULL, ordeninverso, &hilo1_param);
    pthread_create (&id_hilo2,NULL, ordenalfabetico, &hilo2_param);
    
    pthread_join(id_hilo1, NULL);
    pthread_join (id_hilo2, NULL);

    return 0;
}