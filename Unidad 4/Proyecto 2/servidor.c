#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 6666
#define BUF_SIZE 128
#define _GNU_SOURCE

struct client_t{
    int socket;
    int rxState;
    int id;
};

int status1;
int status2;
int enable = 1;
int server_sd;
int contclients=0;
int client_sd[10];
pthread_t rxThreadId[10];
pthread_t cmdThread[10];
struct client_t clientes[10];

void * readThread(void *arg)
{
    struct client_t *client1 = ((struct client_t *)arg);
    struct client_t client = client1[0];
    ssize_t numOfBytes;
    char buf[BUF_SIZE];
    while(1)
    {
        if(contclients > 0)
        {
            numOfBytes = read(client.socket, buf, BUF_SIZE);
            if(0 == numOfBytes){
                printf("client closed the socket end\n");
                break;
            }
            else if(-1 == numOfBytes){
                perror("ReadThread read() fails1: ");
                break;
            }
            else
            {
                char broad[BUF_SIZE];
                char *num;
                broad[BUF_SIZE];
                asprintf(&num,"%d",client.socket);
                strcpy(broad, "From user ");
                strcat(broad, num);
                strcat(broad,": ");
                strcat(broad, buf);
                free(num);
                int aux = client.socket;
                for(int i = 0; i < contclients; i++)
                {
                    if(clientes[i].socket != aux){
                        
                        status1 = write(clientes[i].socket, broad, strlen(broad)+1);
                        if(-1 == status1)
                        {
                            perror("Error: ");
                            break;
                        }
                    } 
                }
                if(-1 < numOfBytes){
                    printf("from user %d: %s\n", client.socket, buf);
                }
            }
        }
    }
    printf("Terminate Pthread for reading\n");
    return NULL;
}

void disconnect_client(int id)
{
    int pos=0;
    printf("client %d disconnected\n", clientes[id-1].id);
    pos = clientes[id-1].id-1;
    clientes[id-1].rxState = 0;
    write(clientes[id-1].socket, ":exit",strlen(":exit")+1);
    close(clientes[id-1].socket);
    reorganize_clients(pos);
}

void reorganize_clients(int pos)
{
    contclients--;
    for(int i = pos; i < contclients; i++)
    {
        clientes[i] = clientes[i+1];
        client_sd[i] = client_sd[i+1];
        rxThreadId[i] = rxThreadId[i+1];
    }
    for(int i = 0; i < contclients; i++){
        clientes[i].id = i+1;
    }
}

void * commandThread()
{
    char command[30]; 
    while(1)
    {
        fgets(command,31,stdin);
	    command[strcspn(command, "\n")] = '\0';
	    char *token = strtok(command, " ");

        if(strcmp(token, "disconnect")==0)
        {
            int id;
            token = strtok(NULL, " ");
	    	id=atoi(token);
            disconnect_client(id);

        }else if(strcmp(token, "list")==0)
        {
            list();
        }else
        {
            printf("command error");
        }
    }
}

void list()
{
    printf("Users connected:\n");

    for(int i = 0; i < contclients; i++)
    {
        //printf("-User %d\n", clientes[i].socket);
        printf("%d. socket: %d \n", clientes[i].id, clientes[i].socket);
    }
}

int main(int argc, char *argv[])
{
    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);
    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1) {
        perror("Socket creation fails\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");
    // 3. turn off bind address checking
    status1 = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR,(int *) &enable, sizeof(enable));
    if (-1 == status1){
        perror("setsockopt error: ");
    }
    //4. BIND the socket to an address
    // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    status1 = bind(server_sd, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == status1) {
        perror("Bind fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    printf("Socket binded\n");
    // 5. Set backlog
    status1 = listen(server_sd, 1);
    if (-1 == status1) {
        perror("Listen fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening\n");

    pthread_create(&cmdThread,NULL,&commandThread,NULL);

    while(1)
    { 
        if(contclients <= 10)
        {
            int auxid = 0;
            int auxaccept;
            // 6. Accept:
            auxaccept = accept(server_sd, NULL, NULL);
            client_sd[contclients] = auxaccept;
            printf("Client connected\n");

            if(-1 == client_sd[contclients]){
                perror("Accept fails: ");
                close(server_sd);
                exit(EXIT_FAILURE);
            
            }
            auxid = contclients;
            // 7. Create a thread for receiving messages from client
            clientes[contclients].socket = client_sd[contclients];
            clientes[contclients].rxState = 1;
            clientes[contclients].id = auxid+1;
            status1 = pthread_create(&rxThreadId[contclients],NULL,&readThread,&clientes[contclients]);

            if(-1 == status1){
                perror("Pthread read fails: ");
                close(server_sd);
                exit(EXIT_FAILURE);
            }
            contclients++;
        }else
        {
            printf("El chat está ocupado");
        }
    }
    exit(EXIT_SUCCESS);
}