#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <string.h>

typedef struct registros{
	char clave[21];
	int valor; 
}regs;

int main(int argc, char *argv[]) {

	regs *regsp1 = (regs*)malloc(sizeof(regs));
    FILE *in_file;
	char ruta1[100]="/home/juancardozo/Documents/";
    char ruta2[100]="/home/juancardozo/Documents/";
	int cont=0;

	strcat(ruta1,argv[1]);
	
	in_file = fopen(ruta1, "r");

	if(in_file == NULL)
	{
		printf("El archivo especificado no existe %s\n", argv[1]);
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

	for(int i = 0; i < cont; i++)
	{
		for(int j = 0;j < cont; j++)
		{
			if((regsp1+i)->valor > (regsp1+j)->valor)
			{
				int tempv = (regsp1+i)->valor;
				char tempc[21];
				strncpy(tempc,(regsp1+i)->clave,20);
				(regsp1+i)->valor = (regsp1+j)->valor;
				strncpy((regsp1+i)->clave,(regsp1+j)->clave,20);
				(regsp1+j)->valor = tempv;
				strncpy((regsp1+j)->clave,tempc,20);
			}
		}
	}

	strcat(ruta2,argv[2]);
	in_file = fopen(ruta2, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %d\n", (regsp1+i)->clave, (regsp1+i)->valor);
	}
	fclose(in_file);
	free(regsp1);
}