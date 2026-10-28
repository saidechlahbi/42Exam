// #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#include <sys/types.h> 
#include <stdio.h>
#include <string.h>


fd_set fds, rfds;
int ids[1024], idx[1024], fd_server, nfds, id = 0;
char buff[600020], msg[600000], clients[1024][600000];

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

void send_all(int fd)
{
    for (int i = 0; i < nfds; i++)
    {
        if (i != fd_server && i != fd)
        {
            send(i, buff, strlen(buff),0);
        }
    }
}

int main (int ac, char **av)
{
    if (ac != 2)
    {
        write (2, "Wrong number of arguments\n", ft_strlen("Wrong number of arguments\n"));
        exit(1);
    }
    fd_server = socket(AF_INET, SOCK_STREAM, 0);
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

    FD_ZERO(&fds);
    FD_SET(fd_server, &fds);
     nfds = fd_server + 1;

    while (1)
    {
        rfds = fds;
        if (select(nfds, &rfds, NULL, NULL,NULL) < 0)
        {
            write (2 , "Fatal error\n", ft_strlen("Fatal error\n"));
            exit(1);  
        }
        for (int fd = 0; fd < nfds;fd++)
        {
            if (!FD_ISSET(fd, &rfds))
                continue;
            if (fd == fd_server)
            {
                int client = accept (fd_server, NULL,NULL);
                if (client >= 0)
                {
                    FD_SET(client, &fds);
                    if (client >= nfds)
                        nfds = client + 1;
                    ids[client] = id++;
                    idx[client] = 0;
                    sprintf(buff, "server: client %d just arrived\n", ids[client]);
                    send_all(client);
                }
            }else
            {
                int r = recv(fd, msg, sizeof(msg) - 1, 0);
                if (r <= 0)
                {
                    sprintf(buff, "server: client %d just left\n", ids[fd]);
                    send_all(fd);
                    FD_CLR(fd, &fds);
                    close(fd);
                }
                else
                {
                    for(int i = 0; i < r;i++)
                    {
                        clients[fd][idx[fd]++] = msg[i];
                        if (msg[i] == '\n')
                        {
                            clients[fd][idx[fd]] = '\0';
                            sprintf(buff, "client %d: %s", ids[fd], clients[fd]);
                            send_all(fd);
                            idx[fd] = 0;
                        }
                    }
                }
            }
        }
    }
   
}