#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>
#define text 100

int shared_fd = -1;
char * ptr;
int unlinkt = 0;
int len;
sem_t* semaphore1 = NULL;
sem_t* semaphore2 = NULL;


void init_control_mechanism() {
    semaphore1 = sem_open("sem1", 1);
    if (semaphore1 == SEM_FAILED) {
        perror("Opening the semaphore failed: ");
        exit(EXIT_FAILURE);
    }
    semaphore2 = sem_open("sem2", 1);
    if (semaphore2 == SEM_FAILED) {
        perror("Opening the semaphore failed: ");
        exit(EXIT_FAILURE);
    }
}

void shutdown_control_mechanism() {
    if (sem_close(semaphore1) < 0) {
        perror("Closing the semaphore failed: ");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink("sem1") < 0) {
        perror("Unlinking failed: ");
        exit(EXIT_FAILURE);
    }
    if (sem_close(semaphore2) < 0) {
        perror("Closing the semaphore failed: ");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink("sem2") < 0) {
        perror("Unlinking failed: ");
        exit(EXIT_FAILURE);
    }
}

void init_shared_resource() 
{
    shared_fd = shm_open("shm0", O_RDWR, 0666);
    if (shared_fd < 0) {
        perror("Failed to create shared memory: ");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shared_fd);
}

void shutdown_shared_resource() 
{
    if (shm_unlink("/shm0") < 0) {
        perror("Unlinking shared memory failed: ");
        exit(EXIT_FAILURE);
    }
}

void write_thread(char *ptr)
{
    for(;;)
    {
        fgets(ptr, text , stdin);
        len = strlen(ptr);
        if (ptr[len-1] == '\n') ptr[len-1] = '\0';
        sem_post(semaphore2);
        if(strcmp(ptr,"quit")==0){
            break;
        }
    }
}

void read_thread()
{
    for(;;)
    {
        sem_wait(semaphore1);
        if(strcmp(ptr,"quit")==0)
        {
            break;
        }
        printf("User1: %s\n", ptr);
    }
}

int main(int argc, char * argv[])
{
    init_shared_resource();
    init_control_mechanism();
    sem_wait(semaphore1);

    if (ftruncate(shared_fd, text * sizeof(char)) < 0) {
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
    }

    void* map = mmap(0, text, PROT_WRITE, MAP_SHARED, shared_fd, 0);

    if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

    ptr = (char*)map;

    

    pthread_t id_hilo1;
    pthread_t id_hilo2;
    pthread_create (&id_hilo1,NULL, &write_thread, (void*)ptr);
    pthread_create (&id_hilo2,NULL, &read_thread, NULL);
    
    pthread_join(id_hilo1, NULL);
    pthread_join (id_hilo2, NULL);


    if (munmap(ptr, text) < 0) {
        perror("Unmapping failed: ");
        exit(EXIT_FAILURE);
    }


    if (close(shared_fd) < 0) {
        perror("Closing shm failed: ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}