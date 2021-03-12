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

// Attribute structure
struct estudiantes
{
	int cedula;
	char nombre[30];
	int semestre;
};

//Memory allocator
struct estudiantes* estudiante_new()
{
	return (struct estudiantes*)malloc(sizeof(struct estudiantes));
}

// Constructor
void est_ctor(struct estudiantes* estudiante, char *nombre, int cedula, int semestre)
{
	strcpy(estudiante->cedula,nombre);
	estudiante->cedula=cedula;
	estudiante->semestre=semestre;
}

// Destructor
void est_dtor(struct estudiantes* estudiante) {
	//free();
}

// Attribute structure
struct databases
{
	char nombre[30];
	int size;
	int cant_reg;
	struct estudiantes* registros;
};

//Memory allocator
struct databases* db_new()
{
	return (struct databases*)malloc(sizeof(struct databases));
}

// Constructor
void db_ctor(struct databases* database, char *nombre, int size)
{
	strcpy(database->nombre, nombre);
	database->size = size;
	database->cant_reg = 0;
	database->registros = malloc(database->size*sizeof(struct estudiantes));;
}

// Destructor
void db_dtor(struct databases* database) {
	//free();
}

// Attribute structure
struct gestores
{
	char nombre[30];
	int sizeg;
	struct databases** bases;
};

//Memory allocator
struct gestores* gestor_new()
{
	return (struct gestores*)malloc(sizeof(struct gestores));
}

// Constructor
void gestor_ctor(struct gestores* gestor, char *nombre, int sizeg)
{
	strcpy(gestor->nombre, nombre);
	gestor->sizeg=sizeg;
	gestor->bases = (struct databases*)malloc(sizeg*sizeof(struct databases));
}

// Destructor
void gestor_dtor(struct gestores* gestor) {
	//free();
}

void mdb(struct gestores* gestor,int contdb,char *nombre, int size)
{
	struct databases* database = db_new();
	db_ctor(database,nombre,size);
	gestor->bases[contdb] = database;
}

void ldb(struct gestores* gestor,int contdb,char *pnombre)
{
	struct databases* database = db_new();
	char nombreb[100]="/home/juancardozo/Documents/";
	int cont=0;

	strcat(nombreb,pnombre);

	FILE *in_file;

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

		if(cont==0)
		{
			fscanf(in_file, "%s", &(database->nombre));
		}else if(cont==1)
		{
			fscanf(in_file, "%d", &(database->size));
			database->registros = malloc(database->size*sizeof(struct estudiantes));

		}else if(cont>=2)
		{
			fscanf(in_file, "%d", &database->registros[cont-2].cedula);
			fscanf(in_file, "%s", database->registros[cont-2].nombre);
			fscanf(in_file, "%d", &database->registros[cont-2].semestre);
		}

		cont++;
	}

	database->cant_reg=(cont-3);
	gestor->bases[contdb]= database;

	fclose(in_file);

}

void lsdbs(struct gestores* gestor)
{
	int i=0;
	while(gestor->bases[i]!= NULL)
	{
		printf("Base de datos número: %d\n", (i+1));
		printf("Nombre: %s\n", gestor->bases[i]->nombre);
		printf("Tamaño: %d\n", gestor->bases[i]->size);
		printf("Cantidad de registros: %d\n", gestor->bases[i]->cant_reg);
		i++;
	}
}

void gdb(struct gestores* gestor,int index)
{
	int i=0;
	while(gestor->bases[i]!= NULL)
	{
		i++;
	}
	printf("El nombre de la bd activa es: %s\n", gestor->bases[index]->nombre);
	printf("El tamaño de la bd activa es: %d\n", gestor->bases[index]->size);
	printf("Cantidad de registros disponibles: %d\n", (gestor->bases[index]->size-gestor->bases[index]->cant_reg));
}

int sdb(struct gestores* gestor,char* nombre)
{
	int i=0;
	int index;
	char nom_tmp1[30];
	char nom_tmp2[30];
	strcpy(nom_tmp1, nombre);
	while(gestor->bases[i]!= NULL)
	{
		strcpy(nom_tmp2, gestor->bases[i]->nombre);
		if(strcmp(nom_tmp1,nom_tmp2)==0){
			index=i;
			printf("%d\n",index);
		}
		i++;
	}
	return index;
}

void svdb(struct gestores* gestor, int index)
{
	FILE *in_file;
	char nombrearch[30];
	char nombreb[100]="/home/juancardozo/Documents/";
	strcpy(nombrearch,gestor->bases[index]->nombre);
	int i=0;
	strcat(nombreb,nombrearch);
	in_file = fopen(nombreb, "w");
	fprintf(in_file,"%s\n", gestor->bases[index]->nombre);
	fprintf(in_file, "%d\n", gestor->bases[index]->cant_reg);
	while(i < gestor->bases[index]->cant_reg){
		fprintf(in_file,"%d %s %d\n", gestor->bases[index]->registros[i].cedula, gestor->bases[index]->registros[i].nombre, gestor->bases[index]->registros[i].semestre);
		i++;
	}
	fclose(in_file);
}

void radb(struct gestores* gestor, int index)
{
	int i=0;
	while(i < gestor->bases[index]->cant_reg)
	{
		printf("Registro %d\n", i+1);
		printf("Nombre: %s\n", gestor->bases[index]->registros[i].nombre);
		printf("Cédula: %d\n", gestor->bases[index]->registros[i].cedula);
		printf("Semestre: %d\n", gestor->bases[index]->registros[i].semestre);
		i++;
	}

	if(i==0){
	    printf("No hay registros\n");
	}
}

int rsdb(struct gestores* gestor, int index)
{
	int i=0;
	while(i < gestor->bases[index]->cant_reg)
	{
		i++;
	}
	printf("%d\n", i);

	if(i==0){
		printf("No hay registros\n");
	}
	return i;
}

void mreg(struct gestores* gestor, int index, int cedula, char *pnombreE, int semestre)
{
	int i = 0;
	while(1)
	{
		if(i == gestor->bases[index]->cant_reg)
		{
			strcpy(gestor->bases[index]->registros[i].nombre,pnombreE);
			gestor->bases[index]->registros[i].cedula = cedula;
			gestor->bases[index]->registros[i].semestre = semestre;
			gestor->bases[index]->cant_reg += 1;
			break;
		}
		i++;
	}
}

void rr(struct gestores* gestor, int index, int cedula)
{
	int i=0;
	while(i < gestor->bases[index]->cant_reg)
	{
		if(gestor->bases[index]->registros[i].cedula == cedula)
		{
			printf("Nombre: %s\n", gestor->bases[index]->registros[i].nombre);
			printf("Cédula: %d\n", gestor->bases[index]->registros[i].cedula);
			printf("Semestre: %d\n", gestor->bases[index]->registros[i].semestre);
		}
		i++;
	}
}

int exitp()
{
	return 0;
}

int main(void) {

	char comando[30];
	char del[]=" ";
	int contdb=0;
	int index=0;

	struct gestores* gestor = gestor_new();
	gestor_ctor(gestor, "popsql", 5);

	do
	{
		fgets(comando,31,stdin);
	    comando[strcspn(comando, "\n")] = '\0';
		char *token = strtok(comando, del);

		if(strcmp(token, "mdb")==0)
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
				}else if(cont==1)
				{
					strcpy(arg2,token);
				}
				cont++;
			}
			mdb(gestor,contdb,arg1,atoi(arg2));
			contdb++;
		}else if(strcmp(token, "ldb")==0)
		{
			char arg1[20];

			token = strtok(NULL, " ");
			strcpy(arg1,token);

			ldb(gestor,contdb,arg1);
			contdb++;
		}else if(strcmp(token, "lsdbs")==0)
		{
			lsdbs(gestor);
		}else if(strcmp(token, "gdb")==0)
		{
			gdb(gestor,index);
		}else if(strcmp(token, "sdb")==0)
		{
			char arg1[20];
			int cont=0;

			token = strtok(NULL, " ");
			strcpy(arg1,token);

			index=sdb(gestor,arg1);
		}else if(strcmp(token,"svdb")==0)
		{
			svdb(gestor, index);

		}else if(strcmp(token,"radb")==0)
		{
			radb(gestor,index);

		}else if(strcmp(token,"rsdb")==0)
		{
			rsdb(gestor,index);

		}else if(strcmp(token, "mreg")==0)
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
				}else if(cont==1)
				{
					strcpy(arg1,token);
				}else if(cont==2){
					strcpy(arg3,token);
				}
				cont++;
			}
			mreg(gestor,index,atoi(arg2),arg1,atoi(arg3));
		}else if(strcmp(token, "rr")==0)
		{
			char arg1[30];
			int cont=0;

			token = strtok(NULL, " ");
			strcpy(arg1,token);
			rr(gestor,index,atoi(arg1));

		}else if(strcmp(token, "exit")==0)
		{
			exitwhile=exitp();
		}else
		{
			printf("Error en el comando\n");
		}

	}while(exitwhile!=0);
	return 0;
}
