/*
 ============================================================================
 Name        : Proyecto.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int exitwhile = 1;
int opcion=0;
int size=0;
char *pnombre;
char nombrebd[20];
char loadbd[20];


typedef struct estudiantes
 {
     int cedula;
     char nombre[30];
     int semestre;
 }estudiante;

estudiante *estudiantesg;
FILE *in_file;

void mkdb(char *pnombre, int size)
{
	estudiantesg = (estudiante*)malloc(size*sizeof(estudiante));

	for(int i = 0; i < size; i++)
	{
		printf("Ingrese el nombre del estudiante: \n");
		scanf("%s", &(estudiantesg+i)->nombre);
		printf("Ingrese la cédula del estudiante: \n");
		scanf("%d", &(estudiantesg+i)->cedula);
		printf("Ingrese el semestre que está cursando el estudiante: \n");
		scanf("%d", &(estudiantesg+i)->semestre);
	}
}

void load(char *pnombre)
{
	estudiantesg = (estudiante*)malloc(size*sizeof(estudiante));
	char nombreb[100]="/home/juancardozo/Documents/";
	char ext[5]=".txt";
	int cont=0;

	strcat(nombreb,pnombre);
	strcat(nombreb,ext);
	loadbd = pnombre;

	in_file = fopen(nombreb, "r");

	if(in_file == NULL)
	{
		printf("El archivo especificado no existe %s\n", nombreb);
		exit(8);
	}

	while(1)
	{
		if(feof(in_file))
		{
			break;
		}

		if(cont%3==0)
		{

		}
		fscanf(in_file, "%d", &(estudiantesg+cont)->cedula);
		fscanf(in_file, "%s", &(estudiantesg+cont)->nombre);
		fscanf(in_file, "%d", &(estudiantesg+cont)->semestre);

		if(cont>0)
		{
			estudiantesg = (estudiante *)realloc(estudiantesg,((cont+1)*sizeof(estudiante)));
		}

		cont++;
	}
}

void savedb(char *pnombre)
{
	char nombreb[100]="/home/juancardozo/Documents/";
	char ext[5]=".txt";
	strcat(nombreb,pnombre);
	strcat(nombreb,ext);
	in_file = fopen(nombreb, "w");
	for(int i = 0; i < size; i++)
	{
		fprintf(in_file,"%d %s %d\n", (estudiantesg+i)->cedula, (estudiantesg+i)->nombre, (estudiantesg+i)->semestre);
	}
	fclose(in_file);
	free(estudiantesg);
}

void readall()
{

}

void readsize()
{

}

void mkreg(int cedula, char *pnombreE, int semestre)
{

}

void readreg(int cedula)
{

}

int exitp()
{
	return 0;
}

int main(void) {

	do
	{
		printf("Ingrese una opción:\n");
		printf("1. Crear una base de datos\n");
		printf("2. Cargar la base de datos en memoria\n");
		printf("3. Guardar base de datos\n");
		printf("4. Leer registros de la BD\n");
		printf("5. Obtener el número de registros de la BD\n");
		printf("6. Añadir un nuevo registro\n");
		printf("7. Imprimir registro\n");
		printf("8. Salir\n");

		printf("Ingrese una opción:\n");
		scanf("%d", &opcion);

		switch(opcion)
		{
			case 1:
				printf("Ingrese el nombre de la BD\n");
				scanf("%s", &nombrebd);
				printf("Ingrese la cantidad de registros de la BD\n");
				scanf("%d", &size);
				mkdb(nombrebd,size);
				break;
			case 2:

				break;
			case 3:
				printf("Ingrese el nombre de la BD\n");
				scanf("%s", &nombrebd);
				savedb(nombrebd);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				exitwhile = exitp();
				break;
		}


	}while(exitwhile!=0);
	return 0;
}
