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

	regs *regsp2 = (regs*)malloc(sizeof(regs));
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
			regsp2 = (regs*)realloc(regsp2,((cont+1)*sizeof(regs)));
		}

		fscanf(in_file, "%s", &(regsp2+cont)->clave);
		fscanf(in_file, "%d", &(regsp2+cont)->valor);
		cont++;
	}
	fclose(in_file);

	cont--;

	regsp2 = (regs*)realloc(regsp2,((cont)*sizeof(regs)));

	for(int i = 0; i < cont/2; i++)
	{
		int tempv = (regsp2+i)->valor;
		char tempc[21];
        strncpy(tempc,(regsp2+i)->clave,20);
        (regsp2+i)->valor = (regsp2+(cont-1-i))->valor;
        strncpy((regsp2+i)->clave, (regsp2+(cont-1-i))->clave,20);
        strncpy((regsp2+(cont-1-i))->clave,tempc,20);
        (regsp2+(cont-1-i))->valor = tempv;
	}
    
	strcat(ruta2,argv[2]);
	in_file = fopen(ruta2, "w");
	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file,"%s %d\n", (regsp2+i)->clave, (regsp2+i)->valor);
	}
	fclose(in_file);
	free(regsp2);
}