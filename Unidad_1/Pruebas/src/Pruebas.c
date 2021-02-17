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

int main(void)
{
    char name[40];
    printf("What's your name? ");
    scanf("%39[^\n]", name);
    printf("Hello %s!\n", name);
}

