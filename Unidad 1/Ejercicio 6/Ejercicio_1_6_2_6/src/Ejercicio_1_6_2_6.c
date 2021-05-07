/*
 ============================================================================
 Name        : Ejercicio_1_6_2_6.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point
{
	int x;
	int y;
}punto;

void printRect(struct point punto1, struct point punto2)
{
	int b;
	int h;
	int area;

	h = fabs(punto1.y - punto2.y);
	b = fabs(punto1.x - punto2.x);
	area = b * h;

	printf("El área del rectangulo es: %d", area);

}

int main(void)
{

	punto punto1 =  {0,0};
	punto punto2 =  {2,2};
	printRect(punto1, punto2);
	return 0;
}
