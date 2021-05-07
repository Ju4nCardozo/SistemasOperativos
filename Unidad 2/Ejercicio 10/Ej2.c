#include <pthread.h>
#include <stdio.h>

/* Esta estructura sirve para pasae parámetros a el hilo */
struct parametros_hilo {
    /* Parametro 1: caracter a imprimir */
    char caracter;
    /* Parametro 2: número de veces que se desea imprimir */
    int contador;
};

/* Esta función imprime un número de caracteres a a salida de error,
tal y como lo indica el parámetro de la función */
void* imprimir_caracter (void* parametros){

    /*Se hace un casr al tipo de datos correcto */
    struct parametros_hilo* p = (struct parametros_hilo*) parametros;
    int i;
    for(i = 0; i < p->contador; ++i)
        fputc(p->caracter, stderr);
    return NULL;
}

/* Programa principal */
int main(){
    pthread_t id_hilo1;
    pthread_t id_hilo2;
    struct parametros_hilo hilo1_param;
    struct parametros_hilo hilo2_param;

/* Crea un hilo para imprimir 30,000 x */
    hilo1_param.caracter = 'x';
    hilo1_param.contador = 30000;
    pthread_create (&id_hilo1,NULL, &imprimir_caracter, &hilo1_param);

/*Crea un hilo para imprimir 20,000 0 */
    hilo2_param.caracter = '0';
    hilo2_param.contador = 20000;
    pthread_create (&id_hilo2,NULL, &imprimir_caracter, &hilo2_param);

/*------------------INSERTAR AQUÍ-----------------*/
pthread_join (id_hilo1, NULL);
pthread_join (id_hilo2, NULL);

return 0;
}