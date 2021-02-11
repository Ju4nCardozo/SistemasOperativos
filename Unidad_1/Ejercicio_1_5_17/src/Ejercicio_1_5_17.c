/*
 ============================================================================
 Name        : Ejercicio_6.17
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

int main(void) {

	float operando1;
	float operando2;
	char operacion;

	do {
		printf("Introduzca el primer operando\n");
		scanf("%f",&operando1);
		printf("Introduzca el segundo operando\n");
		scanf("%f",&operando2);
		printf("Indtroduzca la operación a realizar\n");
		scanf("%c");
		scanf("%c",&operacion);

		switch(operacion){
			case '+':
				printf("%f\n", operando1+operando2);
			case '-':
				printf("%f\n", operando1-operando2);
			case '*':
				printf("%f\n", operando1*operando2);
		}

		do{
			printf("Desea terminar s/n\n");
			scanf("%c");
			scanf("%c", &operacion);
		}while(operacion != 's' & operacion != 'n');

	}while(operacion=='n');


	return(0);
}
