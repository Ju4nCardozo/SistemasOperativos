/*
 ============================================================================
 Name        : Ejercicio_1_6_2_7.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct estudiante
{
	char Nombre[40];
	int numEstudiantes;
	int agnoMatricula;
	float nota;
}estudiante;

void actualizarMiembros(estudiante *);

int main(void)
{
	estudiante estud1 = {"Jose", 4, 2009, 4.5};
	estudiante *ptrEstruct;
	ptrEstruct=&estud1;
	char c;
	printf(" El nombre del estudiante es: %s\n Id del estudiante: %d\n El año en que se matriculó el estudiante fué: %d\n La nota de estud1 es %.2f\n", ptrEstruct->Nombre, ptrEstruct->numEstudiantes, ptrEstruct->agnoMatricula, ptrEstruct->nota);
	printf("Ingrese r para actualizar u otra tecla para salir: ");
	scanf("%c",&c);
	if(c=='r')
	{
		actualizarMiembros(ptrEstruct);
		printf(" El nombre del estudiante es: %s\n Id del estudiante: %d\n El año en que se matriculó el estudiante fué: %d\n La nota de estud1 es %.2f\n", ptrEstruct->Nombre, ptrEstruct->numEstudiantes, ptrEstruct->agnoMatricula, ptrEstruct->nota);
	}
	else
	{
		return 0;
	}
	return 0;
}

void actualizarMiembros(estudiante *ptrEstruct)
{
	printf("Ingrese el nombre del estudiante, el Id, el año en que ingreso y su nota ");
	scanf("%s %d %d %f", &ptrEstruct->Nombre, &ptrEstruct->numEstudiantes, &ptrEstruct->agnoMatricula, &ptrEstruct->nota);
}
