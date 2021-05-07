/*
 ============================================================================
 Name        : Ejercicio_1_6_15.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct materias{
	char nombre[40];
	float nota;
	int num_creditos;
}materia;

int main(void) {

	materia *materias;
	int n=0;
	float suma;
	float promedio;
	printf("Ingrese el número de materias vistas en el semestre: ");
	scanf("%d",&n);
	materias = (materia*)malloc(n*sizeof(materia));

	for(int i = 0; i < n; ++i)
	{
		printf("Ingrese el nombre de la materia: ");
		scanf("%s", &(materias+i)->nombre);
		printf("Ingrese la nota de la materia: ");
		scanf("%f", &(materias+i)->nota);
		printf("Ingrese los creditos de la materia: ");
		scanf("%d", &(materias+i)->num_creditos);
	}

	printf("\n ||materia||Nota||Créditos||\n");
	printf(" ==========================\n");
	for(int i = 0; i < n; ++i)
	{
		printf(" ||%7.7s||%4.1lf||%8d||\n", (materias+i)->nombre, (materias+i)->nota, (materias+i)->num_creditos);
		suma += (materias+i)->nota;
		printf(" ==========================\n");
	}

	promedio = suma/n;
	printf(" ||Promedio: %.1f          ||\n", promedio );
	printf(" ==========================\n");

	free(materias);

	return 0;
}
