/*
 ============================================================================
 Name        : Proyecto.c
 Author      : JuanCardozo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exitwhile = 1;
int size;
char nombrebd[20];

typedef struct estudiantes
{
     int cedula;
     char nombre[30];
     int semestre;
}estudiante;

estudiante *estudiantesg;
FILE *in_file;

void mkbd(char *nombre, int sizef)
{
	size = sizef;
	estudiantesg = (estudiante*)malloc(sizef*sizeof(estudiante));

	for(int i = 0; i < sizef; i++)
	{
		printf("Ingrese el nombre del estudiante: \n");
		scanf("%s", &(estudiantesg+i)->nombre);
		printf("Ingrese la cédula del estudiante: \n");
		scanf("%d", &(estudiantesg+i)->cedula);
		printf("Ingrese el semestre que está cursando el estudiante: \n");
		scanf("%d", &(estudiantesg+i)->semestre);
	}
}

void loadbd(char *pnombre)
{
	estudiantesg = (estudiante*)malloc(sizeof(estudiante));
	char nombreb[100]="/home/juancardozo/Documents/";
	char ext[5]=".txt";
	int cont=0;

	strcat(nombreb,pnombre);
	strcat(nombreb,ext);

	in_file = fopen(nombreb, "r");

	if(in_file == NULL)
	{
		printf("El archivo especificado no existe %s\n", nombreb);
		exit(8);
	}

	while(1)
	{
		if(feof(in_file))
		{
			break;
		}

		if(cont>0)
		{
			estudiantesg = (estudiante *)realloc(estudiantesg,((cont+1)*sizeof(estudiante)));
		}

		fscanf(in_file, "%d", &(estudiantesg+cont)->cedula);
		fscanf(in_file, "%s", &(estudiantesg+cont)->nombre);
		fscanf(in_file, "%d", &(estudiantesg+cont)->semestre);

		cont++;
	}
	size=cont-1;
	printf("%d", size);
	fclose(in_file);
}

void savebd(char *pnombre)
{
	char nombreb[100]="/home/juancardozo/Documents/";
	char ext[5]=".txt";
	strcat(nombreb,pnombre);
	strcat(nombreb,ext);
	in_file = fopen(nombreb, "w");
	for(int i = 0; i < size; i++)
	{
		fprintf(in_file,"%d %s %d\n", (estudiantesg+i)->cedula, (estudiantesg+i)->nombre, (estudiantesg+i)->semestre);
	}
	fclose(in_file);
	free(estudiantesg);
}

void readall()
{
	for(int i=0; i<size;i++){

		printf("Nombre: %s\n", (estudiantesg+i)->nombre);
		printf("Cédula: %d\n", (estudiantesg+i)->cedula);
		printf("Semestre: %d\n", (estudiantesg+i)->semestre);
	}
}
int readsize()
{
	return size;
}

void mkreg(int cedula, char *pnombreE, int semestre)
{
	size += 1;
	estudiantesg = (estudiante *)realloc(estudiantesg,((size)*sizeof(estudiante)));
	strcpy((estudiantesg+(size-1))->nombre,pnombreE);
	(estudiantesg+(size-1))->cedula = cedula;
	(estudiantesg+(size-1))->semestre = semestre;

}

void readreg(int cedula)
{
	for(int i = 0; i < size; i++)
	{
		if((estudiantesg+i)->cedula == cedula)
		{
			printf("Nombre: %s\n", (estudiantesg+i)->nombre);
			printf("Cédula: %d\n", (estudiantesg+i)->cedula);
			printf("Semestre: %d\n", (estudiantesg+i)->semestre);
		}
	}
}

int exitp()
{
	return 0;
}

 int main() {

	char comando[30];
	char del[]=" ";

	do
	{
		fgets(comando,31,stdin);
		printf("%s\n", "Ingrese un comando:");
		fgets(comando,31,stdin);
	    comando[strcspn(comando, "\n")] = '\0';
		char *token = strtok(comando, del);

		if(strcmp(token, "mkbd")==0)
		{
			char arg1[20];
			char arg2[10];
			int cont=0;

			while( token != NULL )
			{
				token = strtok(NULL, " ");
				if(cont==0)
				{
					strcpy(arg1,token);
					printf("%s\n", arg1);
				}else if(cont==1)
				{
					strcpy(arg2,token);
					printf("%s\n", arg2);
				}
				cont++;
			}
			mkbd(arg1,atoi(arg2));
		}else if(strcmp(token, "loadbd")==0)
		{
			char arg1[20];
			int cont=0;

			token = strtok(NULL, " ");
			strcpy(arg1,token);
			printf("%s\n", arg1);
			cont++;

			loadbd(arg1);
		}else if(strcmp(token,"savebd")==0)
		{
			char arg1[20];
			int cont=0;

			token = strtok(NULL, " ");
			strcpy(arg1,token);
			printf("%s\n", arg1);
			cont++;
			savebd(arg1);

		}else if(strcmp(token,"readall")==0)
		{
			readall();
		}else if(strcmp(token,"readsize")==0)
		{
			printf("%d",readsize());
		}else if(strcmp(token, "mkreg")==0)
		{
			char arg1[20];
			char arg2[30];
			char arg3[3];
			int cont=0;

			while( token != NULL )
			{
				token = strtok(NULL, " ");
				if(cont==0)
				{
					strcpy(arg2,token);
					printf("%s\n", arg2);
				}else if(cont==1)
				{
					strcpy(arg1,token);
					printf("%s\n", arg1);
				}else if(cont==2){
					strcpy(arg3,token);
					printf("%s\n", arg3);
				}
				cont++;
			}
			mkreg(atoi(arg2),arg1,atoi(arg3));
		}else if(strcmp(token, "readreg")==0)
		{
			char arg1[30];
			int cont=0;

			token = strtok(NULL, " ");
			strcpy(arg1,token);
			printf("%s\n", arg1);
			readreg(atoi(arg1));

		}else if(strcmp(token, "exit")==0)
		{
			exitwhile=exitp();
		}else
		{
			printf("Error en el comando");
		}
	}while(exitwhile!=0);
	return 0;
}
