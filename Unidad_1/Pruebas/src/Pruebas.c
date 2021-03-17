/*
 ============================================================================
 Name        : Pruebas.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{

	char cadena[] = "Hola,mundo,soy,una,cadena,separa,por,comas",
	delimitador[] = ",";
	char *token = strtok(cadena, delimitador);
	if(token != NULL){
	    while(token != NULL){
	         // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
	         printf("Token: %s\n", token);
	         token = strtok(NULL, delimitador);
	    }
	}
   return 0;
 }

