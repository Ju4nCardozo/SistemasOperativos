
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
    pers *personas;
    char ruta[30];
};

void ordeninverso(void* parametros){

    struct parametros_hilo* param = (struct parametros_hilo*) parametros;
    pers *p;
    p = (struct parametros_hilo*) param->personas;
    FILE *in_file;

    for(int i = 0; i < cont/2; i++)
	{
		int tempv = (p+i)->edad;
		char tempn[21];
        char tempo[21];
        strncpy(tempn,(p+i)->nombre,20);
        strncpy(tempo,(p+i)->ocupacion,20);
        (p+i)->edad = (p+(cont-1-i))->edad;
        strncpy((p+i)->nombre, (p+(cont-1-i))->nombre,20);
        strncpy((p+i)->ocupacion, (p+(cont-1-i))->ocupacion,20);
        strncpy((p+(cont-1-i))->nombre,tempn,20);
        strncpy((p+(cont-1-i))->ocupacion,tempo,20);
        (p+(cont-1-i))->edad = tempv;
	}

	in_file = fopen(param->ruta, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %s %d\n", (p+i)->nombre, (p+i)->ocupacion, (p+i)->edad);
	}
	fclose(in_file);
}

void ordenalfabetico(void* parametros){

    struct parametros_hilo* param = (struct parametros_hilo*) parametros;
    pers *p;
    p = (struct parametros_hilo*) param->personas;
    FILE *in_file;

    for(int i = 0; i < cont; i++){
        for(int j = 0; j < cont; j++){
            if(strcmp((p+j)->ocupacion,(p+i)->ocupacion)>0){
                
                int tempv = (p+i)->edad;
				char tempn[21];
                char tempo[21];
                strncpy(tempn,(p+i)->nombre,20);
                strncpy(tempo,(p+i)->ocupacion,20);
				(p+i)->edad = (p+j)->edad;
				strncpy((p+i)->ocupacion,(p+j)->ocupacion,20);
                strncpy((p+i)->nombre,(p+j)->nombre,20);
				(p+j)->edad = tempv;
				strncpy((p+j)->ocupacion,tempo,20);
                strncpy((p+j)->nombre,tempn,20);
            }
        }
    }

    in_file = fopen(param->ruta, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %s %d\n", (p+i)->nombre, (p+i)->ocupacion, (p+i)->edad);
	}
	fclose(in_file);
}

int main(int argc, char *argv[]) {

    pthread_t id_hilo1;
    pthread_t id_hilo2;
    pers *pers1 = (pers*)malloc(sizeof(pers));
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

		if(cont>0)
		{
			pers1 = (pers*)realloc(pers1,((cont+1)*sizeof(pers)));
		}

		fscanf(in_file, "%s", &(pers1+cont)->nombre);
		fscanf(in_file, "%s", &(pers1+cont)->ocupacion);
        fscanf(in_file, "%d", &(pers1+cont)->edad);
		cont++;
	}
	fclose(in_file);

    cont--;

	pers1 = (pers*)realloc(pers1,((cont)*sizeof(pers)));
    pers *pers2 = (pers*)malloc(cont*sizeof(pers));

    for(int i = 0; i < cont; i++)
    {
        printf("%s %s %d\n",(pers1+i)->nombre, (pers1+i)->ocupacion, (pers1+i)->edad);
    }

    for(int i = 0; i < cont; i++)
    {
        strcpy((pers2+i)->nombre, (pers1+i)->nombre);
        strcpy((pers2+i)->ocupacion, (pers1+i)->ocupacion);
        (pers2+i)->edad = (pers1+i)->edad;
    }

    strcat(ruta1,argv[2]);
    strcpy(hilo1_param.ruta, ruta1);
    strcat(ruta2,argv[3]);
    strcpy(hilo2_param.ruta, ruta2);
    hilo1_param.personas = pers1;
    hilo2_param.personas = pers2;
    pthread_create (&id_hilo1,NULL, &ordeninverso, &hilo1_param);
    pthread_create (&id_hilo2,NULL, &ordenalfabetico, &hilo2_param);

    pthread_join(id_hilo1, NULL);
    pthread_join (id_hilo2, NULL);

    free(pers1);
    free(pers2);

    return 0;
}