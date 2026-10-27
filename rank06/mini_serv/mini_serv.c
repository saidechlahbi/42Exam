// #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#include <sys/types.h> 

typedef struct s_clients
{
    int id;
    char *input;
    char *output;
} t_clients;

t_clients clients[1024];
fd_set readfds, writefds, active;
int fdmax = 0;

int ft_strlen(char *str)
{
    int i = 0;
    while(*str)
    {
        i++;
        str++;
    }
    return i;
}


void add_message(int fd, char *message)
{

}

int main (int ac, char **av)
{
    if (ac != 2)
    {
        write (2, "Wrong number of arguments\n", ft_strlen("Wrong number of arguments\n"));
        exit(1);
    }
    int fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_server == -1)
    {
        write (2 , "Fatal error\n", ft_strlen("Fatal error\n"));
        exit(1);
    }


    struct sockaddr_in server_add;
    bzero(&server_add, sizeof(server_add));
    server_add.sin_family = AF_INET;
    server_add.sin_port = htons(atoi(av[1]));
    server_add.sin_addr.s_addr = htonl(INADDR_LOOPBACK);


    int aa = bind(fd_server, (const struct sockaddr *)&server_add, sizeof (server_add));
    if (aa < 0)
    {
        write (2 , "Fatal error\n", ft_strlen("Fatal error\n"));
        exit(1);  
    }
    int bb = listen(fd_server, 10);
    if (bb < 0)
    {
        write (2 , "Fatal error\n", ft_strlen("Fatal error\n"));
        exit(1);  
    }

    FD_ZERO(&active);
    FD_SET(fd_server, &active);
    fdmax = fd_server;
    int next_id = 0;


    char message[1024];
    while (1)
    {
        readfds = active;
        FD_ZERO(&writefds);
        int ready =  select(fdmax + 1, &readfds, &writefds, NULL, NULL);
        if (ready < 0)
        {
            write (2 , "Fatal error\n", ft_strlen("Fatal error\n"));
            exit(1);  
        }
        if (FD_ISSET(fd_server, &readfds))
        {
            socklen_t client_len = sizeof(server_add);
            int client_fd = accept(fd_server, (struct sockaddr *)&server_add, &client_len);
            if (client_fd < 0)
            {
                write(2, "Fatal error\n", ft_strlen("Fatal error\n"));
                exit(1);
            }
            clients[client_fd].id = next_id;
            next_id ++;
            FD_SET(client_fd, &active);
            if (client_fd > fdmax)
                fdmax = client_fd;
            sprintf(message, "server: client %d just arrived\n", clients[client_fd].id);

        }
        for (int fd = 0; fd <= fdmax; fd++)
        {
            if (fd != fd_server && FD_ISSET(fd, &readfds)) // This client sent data or disconnected.
            {
                strcat(clients[fd].msg, message);
                int received = recv(fd, buffer, sizeof(buffer) - 1, 0);
                if (received == -1)
                {
                    write(2, "Fatal error\n", ft_strlen("Fatal error\n"));
                    exit(1);     
                }
                else if (received == 0)
                {
                    close(fd);
                    FD_CLR(fd, &active);
                }
                else if(received > 0)
                {
                    buffer[received] = '\0';
                }
            }
        }

    }

}