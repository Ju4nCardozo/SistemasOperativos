/*
 ============================================================================
 Name        : Ejercicio_1_6_2_5.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

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

struct cdsMusica{

		char titulo[40];
		char artista[40];
		char genero[15];
		int numCanciones;
		int lanzamiento;
		int precio;
};

void printStruct(struct cdsMusica cd){
	printf(" Titulo: %s\n Artista: %s\n Genero:%s\n Número de canciones:%d\n Fecha de lanzamiento:%d\n Precio:%d\n ", cd.titulo, cd.artista, cd.genero, cd.numCanciones, cd.lanzamiento, cd.precio);
}

int main(void)
{

	struct cdsMusica cd1 = {"Brindo con el alma", "Diomedez Díaz", "Vallenato", 11, 1986, 19900};
	printStruct(cd1);

	return 0;
}
