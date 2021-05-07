#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>      /* For semphores */
#include <fcntl.h>          /* For 0_* constants */
#include <sys/stat.h>       /* For mode constants */
#include <unistd.h>

int main(int argc, char *argv[]){

    //Note que ya no especificó el modo ni el valor.
    sem_t *sem = sem_open("semExample", 0);

    if(sem == SEM_FAILED){
        perror("pSemWait sem opne: ");
        exit(EXIT_FAILURE);
    }

    printf("pSemWait %d semwait() ...\n", getpid());
    if(sem_wait(sem) == -1){
        perror("pSemWait sem_wait error: ");
        exit(EXIT_FAILURE);
    }
    printf("pSemWait %d succeeded\n", getpid());

    if(sem_close(sem) == -1){
        perror("pSemWait sem_close fails: ");
        exit(EXIT_FAILURE);
    }

    if(sem_unlink("semExample") == -1){
        perror("pSemWait sem_unlink fails: ");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}