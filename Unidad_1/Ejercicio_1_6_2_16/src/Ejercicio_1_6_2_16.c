/*
 ============================================================================
 Name        : Ejercicio_1_6_2_16.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{

	int count = 0;
	int ch;
	FILE *in_file1;
	FILE *in_file2;
	char FILE_NAME1[50];
	char FILE_NAME2[50];

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
	while(!feof(in_file1))
	{
		ch = fgetc(in_file1);
		if(ch != EOF){
			fputc(ch,in_file2);
			++count;
		}
	}
	printf("Number of characters written was %d\n", count);
	fclose(in_file1);
	fclose(in_file2);
	return 0;
}
