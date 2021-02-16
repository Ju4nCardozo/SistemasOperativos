/*
 ============================================================================
 Name        : Ejercicio_1_6_2_18.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct materias
{
	char nombre[40];
	float nota;
	int creditos;
}materia;

int main(void) {

	int cont=0;
	int mganadas=0;
	int mperdidas=0;
	float suma = 0;
	float promedio=0;
	materia *materias;
	FILE *in_file1;
	FILE *in_file2;
	char FILE_NAME1[50];
	char FILE_NAME2[50];
	char var[40];
	char *pvar = &var;
	materias = (materia *)malloc(sizeof(materia));

	printf("Ingrese el nombre del primer archivo: ");
	scanf("%s", &FILE_NAME1);
	printf("Ingrese el nombre del segundo archivo: ");
	scanf("%s", &FILE_NAME2);

	in_file1 = fopen(FILE_NAME1, "r");

	if(in_file1 == NULL)
	{
		printf("Cannot open %s\n", FILE_NAME1);
		exit(8);
	}

	in_file2 = fopen(FILE_NAME2, "w");

	if(in_file2 == NULL)
	{
		printf("Cannot open %s\n", FILE_NAME2);
		exit(8);
	}

	while(1)
	{
		if(feof(in_file1))
		{
			break;
		}

		fscanf(in_file1, "%s", &var);
		if(strcmp(var,"Materia:")==0){
			fscanf(in_file1, "%s", &(materias+cont)->nombre);
		}else if(strcmp(var,"Nota:")==0){
			fscanf(in_file1, "%f", &(materias+cont)->nota);
		}else if(strcmp(var,"Creditos:")==0){
			fscanf(in_file1, "%d", &(materias+cont)->creditos);
			++cont;
			materias = (materia *)realloc(materias,((cont+1)*sizeof(materia)));
		}
		*pvar = "";
	}

	for(int i = 0; i < cont; i++)
	{
		if((materias+i)->nota >= 3)
		{
			++mganadas;
		}else
		{
			++mperdidas;
		}

		suma += (materias+i)->nota;
	}

	promedio = suma/cont;

	fputs("Materia	Nota	Creditos\n", in_file2);

	for(int i = 0; i < cont; i++)
	{
		fprintf(in_file2, "%s	  %.2f	%d\n", (materias+i)->nombre, (materias+i)->nota, (materias+i)->creditos);
	}

	fprintf(in_file2, "%s	%d\n", "Total de materias: ", cont-1);
	fprintf(in_file2, "%s	%d\n", "Materias ganadas: ", mganadas);
	fprintf(in_file2, "%s	%d\n", "Materias perdidas: ", mperdidas);
	fprintf(in_file2, "%s	%.2f\n", "Promedio ponderado: ", promedio);

	fclose(in_file1);
	fclose(in_file2);
	free(materias);

	return 0;
}
