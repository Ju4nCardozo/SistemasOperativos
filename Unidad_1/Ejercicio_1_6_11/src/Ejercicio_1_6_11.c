/*
 ============================================================================
 Name        : Ejercicio_1_6_11.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

float promedio(float A[]);
float float_rand( float min, float max );

int main(void) {

	float A[10];
	for(int i=0; i<=9;i++){
		A[i] = float_rand(0,100);
	}
	promedio(A);
	return 0;
}

float promedio(float A[]){

	float promedio;
	float suma;
	for(int i=0; i<=9;i++){
		suma += A[i];
	}
	promedio = suma/10;
	printf("promedio es: %f\n", promedio);
}

float float_rand( float min, float max )
{
    srand ( time(NULL) );
    float scale = rand() / (float) RAND_MAX;
    return min + scale * ( max - min );
}
