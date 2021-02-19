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

int main(int argc, char* argv[])
{

   #ifdef CONDITION
   printf("CODIGO IF\n");
   #else
   printf("CODIGO ELSE\n");
   #endif
   return 0;
 }

