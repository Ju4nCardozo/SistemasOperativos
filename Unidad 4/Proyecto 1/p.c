#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int booleano = 0;

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void leerdirectorio(char* ruta);

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(1);
    }

    leerdirectorio(argv[1]);

    exit(0);
}

void leerdirectorio(char* ruta)
{
    DIR *streamp; 
    char * direc = malloc(sizeof(char) * 200);

    struct dirent *dep;

    streamp = opendir(ruta);

    errno = 0;
    if(streamp != NULL){
    
        while ((dep = readdir(streamp)) != NULL) 
        { 
            if(strcmp(dep->d_name,".") != 0 && strcmp(dep->d_name,"..") != 0)
            {
                if(booleano > 0)
                {
                    for(int i = 0; i < booleano; i++)
                    {
                        printf("    ");
                    }
                }
                printf("|--%s\n", dep->d_name);

                if(dep->d_type == DT_DIR)
                {
                    sprintf(direc, "%s/%s", ruta, dep->d_name);
                    booleano +=1; 
                    leerdirectorio(direc);
                }
            }
        } 

        if (errno != 0)
            unix_error("readdir error");

        free(direc);
        closedir(streamp); 
        booleano = 0;
    }
}