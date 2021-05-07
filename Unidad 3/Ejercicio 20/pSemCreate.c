#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>   /* for semaphores */
#include <fcntl.h>       /* For 0_* constants */
#include <sys/stat.h>    /* For mode constants */

int main (int argc, char *argv[]){

    mode_t perms = 0666;
    int flags = O_CREAT;
////////////////////////////////////////////////////////////////
    // OJO CON ESTE VALOR INICIAL, NO SIEMPRE ES 0,
    // DEPENDE DE LO QUE YO QUIERA: quiero que el semáforo 
    // Inicie cerrado o abierto?
    unsigned int value = 0;    
///////////////////////////////////////////////////////////////

    // (1) Crear el semáforo. Como el valor inicial es 0
    // Si alguien hace un wait se bloqueará. wait
    // es esquivalente a down.

    sem_t *sem = sem_open("semExample", flags, perms, value);

    if(sem == SEM_FAILED){
        perror("pSemCreate sem_open fails: ");
        exit(EXIT_FAILURE);
    }

    //Si el semáforo debe seguir disponible para otros procesos
    //solo hago close. Si además se debe destruir se hace también
    //el sem_unlink

    if(sem_close(sem) == -1){
        perror("pSemCreate sem_close fails: ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}