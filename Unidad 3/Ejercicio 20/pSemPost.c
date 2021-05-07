#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>      /* For semaphores */
#include <fcntl.h>          /* For 0_* constants */
#include <sys/stat.h>       /* For mode constants */
#include <unistd.h>

int main(int argc, char *argv[]){

    //Note que ya no especifico el modo ni el valor.
    sem_t *sem = sem_open("semExample", 0);

    if(sem = SEM_FAILED){
        perror("pSemPost sem_open: ");
        exit(EXIT_FAILURE);
    }

    printf("pSemPost %d sem_post() ...\n", getpid());
    if(sem_post(sem) == -1){
        perror("pSemPost sem_post error: ");
        exit(EXIT_FAILURE);
    }
    printf("pSemPost %d succeeded\n", getpid());

    if(sem_close(sem) == -1){
        perror("pSempost sem_close fails: ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}