#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

typedef struct registros{
	char clave[21];
	int valor; 
}regs;

int main(int argc, char *argv[]) {

	regs *regsp1 = (regs*)malloc(sizeof(regs));
    FILE *in_file;
    char nombre1[50];
    char nombre2[50];
	char ruta1[100]="/home/juancardozo/Documents/";
    char ruta2[100]="/home/juancardozo/Documents/";
	int cont=0;

	printf("Ingrese el nombre del archivo de entrada: \n");
	scanf("%s", nombre1);
	strcat(ruta1,nombre1);
	
	in_file = fopen(ruta1, "r");

	if(in_file == NULL)
	{
		printf("El archivo especificado no existe %s\n", nombre1);
		exit(8);
	}

	while(!feof(in_file))
	{

		if(cont>0)
		{
			regsp1 = (regs*)realloc(regsp1,((cont+1)*sizeof(regs)));
		}

		fscanf(in_file, "%s", &(regsp1+cont)->clave);
		fscanf(in_file, "%d", &(regsp1+cont)->valor);
		cont++;
	}
	fclose(in_file);

	cont--;

	regsp1 = (regs*)realloc(regsp1,((cont)*sizeof(regs)));

	for(int i = 0; i < cont/2; i++)
	{
		int tempv = (regsp1+i)->valor;
		char tempc[21];
        strncpy(tempc,(regsp1+i)->clave,20);
        (regsp1+i)->valor = (regsp1+(cont-1-i))->valor;
        strncpy((regsp1+i)->clave, (regsp1+(cont-1-i))->clave,20);
        strncpy((regsp1+(cont-1-i))->clave,tempc,20);
        (regsp1+(cont-1-i))->valor = tempv;
	}
    
	printf("Ingrese el nombre del archivo de salida: \n");
	scanf("%s", nombre2);
	strcat(ruta2,nombre2);
	in_file = fopen(ruta2, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %d\n", (regsp1+i)->clave, (regsp1+i)->valor);
	}
	fclose(in_file);
	free(regsp1);
}