/*
 ============================================================================
 Name        : Ejercicio_1_6_2_17.c
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

	FILE *in_file1;
	FILE *in_file2;
	FILE *in_file3;
	char FILE_NAME1[50];
	char FILE_NAME2[50];
	char FILE_NAME3[50];
	char text1[30];
	char text2[30];

	printf("Ingrese el nombre del primer archivo: ");
	scanf("%s", &FILE_NAME1);
	printf("Ingrese el nombre del segundo archivo: ");
	scanf("%s", &FILE_NAME2);
	printf("Ingrese el nombre del tercer archivo: ");
	scanf("%s", &FILE_NAME3);

	in_file1 = fopen(FILE_NAME1, "w+");

	if(in_file1 == NULL)
	{
		printf("Cannot open %s\n", FILE_NAME1);
		exit(8);
	}

	in_file2 = fopen(FILE_NAME2, "r");

	if(in_file2 == NULL)
	{
		printf("Cannot open %s\n", FILE_NAME2);
		exit(8);
	}

	in_file3 = fopen(FILE_NAME3, "r");

		if(in_file3 == NULL)
		{
			printf("Cannot open %s\n", FILE_NAME3);
			exit(8);
		}

	fgets(text1, 30, in_file2);
	fprintf (in_file1, "%s", text1);


	printf("El texto que hay en el archivo 1 dice: %s\n", text1);

	fscanf(in_file3, "%s", &text2);
	printf("El texto que hay en el archivo 2 dice: %s\n", text2);
	fputs(text2, in_file1);

	fclose(in_file1);
	fclose(in_file2);
	fclose(in_file3);
	return 0;
}
