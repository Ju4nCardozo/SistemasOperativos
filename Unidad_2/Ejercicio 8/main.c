#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int main(int argc, char *argv[]) {
    
    pid_t pid1, pid2, pid3;
    int status1, status2, status3;
    
    if ( (pid1=fork()) == 0 )
    { 
        execv("./promedio",argv);   
    }
    else
    { 
        if ( (pid2=fork()) == 0 )
        {
            
            execv("./maximo",argv); 
            
        }
        else
        {
            if ( (pid3=fork()) == 0 )
            {
                
                execv("./minimo",argv); 
                
            }else
            {
                waitpid(pid1, &status1, 0);
                waitpid(pid2, &status2, 0);
                waitpid(pid3, &status3, 0);
                printf("Soy el padre con PID %d\n", getpid());
            }
        }
    }
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
}
