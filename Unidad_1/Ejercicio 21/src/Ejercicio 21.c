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
#include <stdint.h>

uint8_t arrayCommon(int32_t* arr1, int32_t size1, int32_t* arr2, int32_t size2, int32_t* arrR, int32_t sizeR)
{
	int sizemax;
	int sizemin;
	int cont=0;

	if(size1 > size2)
	{
		sizemax = size1;
		sizemin = size2;
	}else if(size1 == size2)
	{
		sizemax = size1;
		sizemin = size2;
	}
	else
	{
		sizemax = size2;
		sizemin = size1;
	}

	for(int i = 0; i < sizemax; i++)
	{
		for(int j = 0; j < sizemin; j++)
		{
			if(*(arr1+i)==*(arr2+j))
			{
				*(arrR+cont)= *(arr1+i);
				cont++;
			}else
			{
				*(arrR+cont)=0;
			}
		}
	}
	return cont;
}

int main(void)
{

	int a1;
	int a2;
	int aR;

	printf("Ingrese  el tamaño del primer array:\n");
	scanf("%d", &a1);

	int arr1[a1];

	for(int i=0; i<a1; i++)
	{
		printf("Ingrese el valor para la posición arr1[%d]: ", i);
		scanf("%d", &arr1[i]);
	}

	printf("Ingrese el tamaño del segundo array:\n");
	scanf("%d", &a2);

	int arr2[a2];

	for(int i=0; i<a2; i++)
	{
		printf("Ingrese el valor para la posición arr1[%d]: ", i);
		scanf("%d", &arr2[i]);
	}

	if(a1 < a2)
	{
		aR = a1;

	}else
	{
		aR = a2;
	}

	int arrR[aR];

	printf("El número de elementos repetidos son: %d\n", arrayCommon(arr1, a1, arr2, a2, arrR, aR));

	for(int i = 0; i < aR; i++)
	{
		printf("%d ",arrR[i]);
	}

	return 0;
}
