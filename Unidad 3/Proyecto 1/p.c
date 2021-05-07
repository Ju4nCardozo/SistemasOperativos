#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 20

int main(int argc, char *argv[])
{
    int pfd[2], pfd2[2]; /* Pipe file descriptors */
    char buf[BUF_SIZE];
    char text[BUF_SIZE];

    if (pipe(pfd) == -1){ /* Create the pipe */
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pfd2) == -1){ /* Create the pipe */
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
    case 0: /* Child  - reads from pipe */
        if (close(pfd[1]) == -1)
        { /* Write end is unused */
            perror("close - child");
            exit(EXIT_FAILURE);
        }
        if (close(pfd2[0]) == -1)
        { /* Read end is unused */
            perror("close - child");
            exit(EXIT_FAILURE);
        }
        for(;;)
        { /* Read data from pipe, echo on stdout */

            read(pfd[0], buf, BUF_SIZE);

            int i = 0;

            for(;;)
            {
                if(buf[i] != NULL)
                {
                    buf[i] = toupper(buf[i]);
                }else{
                    break;
                }
                i++;
            }
            
            if (write(pfd2[1], buf, BUF_SIZE) != BUF_SIZE)
            {
                perror("parent- partial/failed write");
                exit(EXIT_FAILURE);
            }
        }
        if (close(pfd2[1]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

        if (close(pfd[0]) == -1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
    
        exit(EXIT_SUCCESS);
    default: /* Parent - writes to pipe */

        if (close(pfd[0]) == -1)
        { /* Read end is unused */
            perror("close - parent");
            exit(EXIT_FAILURE);
        }
        if (close(pfd2[1]) == -1)
        { /* Write end is unused */
            perror("close - parent");
            exit(EXIT_FAILURE);
        }
        for(;;)
        {
            printf("Ingrese texto: ");
            scanf("%[^\n]",&text);
            getc(stdin);

            if (write(pfd[1], text, BUF_SIZE) != BUF_SIZE)
            {
                perror("parent- partial/failed write");
                exit(EXIT_FAILURE);
            }

            read(pfd2[0], buf, BUF_SIZE);

            printf("%s\n", buf);
        }
        if (close(pfd[1]) == -1)
        { /* Child will see EOF */
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (close(pfd2[0]) == -1)
            { /* Child will see EOF */
                perror("close");
                exit(EXIT_FAILURE);
            }
        wait(NULL); /* Wait for child to finish */
        exit(EXIT_SUCCESS);
    }  
}