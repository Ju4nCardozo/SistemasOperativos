#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 

int factorial(int i)
{
    int fac=1;
    for(int j = 1; j < i; j++){
        fac = fac * j;
    }
    return fac;
}

int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3;
    int status1, status2, status3;
    
    if ( (pid1=fork()) == 0 )
    { 
        for(int i = 1; i <= 10; i++){
            printf("HIJO 1: fact(%d)= %d\n", i, factorial(i));
        }
    }
    else
    { 
        if ( (pid2=fork()) == 0 )
        {
            for(int i = 1; i <= 10; i++){
            printf("HIJO 2: fact(%d)= %d\n", i, factorial(i));
            }
        }
        else
        {
            if ( (pid3=fork()) == 0 )
            {
                for(int i = 1; i <= 10; i++){
                printf("HIJO 3: fact(%d)= %d\n", i, factorial(i));
                }
            }else
            {
                waitpid(pid1, &status1, 0);
                waitpid(pid2, &status2, 0);
                waitpid(pid3, &status3, 0);
                printf("Soy el padre con PID %d\n", getpid());
            }
        }
    }
    return 0;
}