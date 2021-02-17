/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

void imprimirArreglo(int *parr, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("arr[%d]: %d\n", i, *(parr+i));
	}
}

int main(void)
{

	int n;
	int pos;

	printf("Ingrese el tamaño del arreglo:\n");
	scanf("%d",&n);

	int arr[n];

	for(int i=0; i < n; i++)
	{
		printf("Ingrese el valor de la posición %d del array:\n", i);
		scanf("%d", &arr[i]);
	}

	imprimirArreglo(arr,n);

	printf("¿Que posición del array desea cambiar?\n");
	scanf("%d", &pos);
	pos--;

	for(int i=n-1; i >= pos; i--)
	{
		arr[i+1] = arr[i];
	}

	printf("Ingrese el valor de la posición la cual desea cambiar:\n");
	scanf("%d", &arr[pos]);

	imprimirArreglo(arr,n+1);

	return 0;
}

