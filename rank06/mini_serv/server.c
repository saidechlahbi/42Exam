#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#include <sys/types.h> 
#include <stdio.h>
#include <string.h>
    
     


// fd_set fds, rfds;
// int fd_server, id = 0, nfds;
// int idx[1024], ids[1024];
// char client[1024][600000], msg[600000], buffer[600020];

// void send_all(int au)
// {
//     for (int fd = 0; fd < nfds; fd++)
//     {
//         if (fd != fd_server && fd != au)
//         {
//             send(fd, buffer, strlen(buffer ), 0);
//         }
//     }
// }

// int main (int ac, char **av)
// {
//     if (ac != 2)
//     {
//         write (2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
//         exit(1);
//     }
//     fd_server = socket(AF_INET, SOCK_STREAM, 0);
//     if (fd_server == -1)
//     {
//         write (2 , "Fatal error\n", strlen("Fatal error\n"));
//         exit(1);
//     }


//     struct sockaddr_in server_add;
//     bzero(&server_add, sizeof(server_add));
//     server_add.sin_family = AF_INET;
//     server_add.sin_port = htons(atoi(av[1]));
//     server_add.sin_addr.s_addr = htonl(INADDR_LOOPBACK);


//     int aa = bind(fd_server, (const struct sockaddr *)&server_add, sizeof (server_add));
//     if (aa < 0)
//     {
//         write (2 , "Fatal error\n", strlen("Fatal error\n"));
//         exit(1);  
//     }
//     int bb = listen(fd_server, 10);
//     if (bb < 0)
//     {
//         write (2 , "Fatal error\n", strlen("Fatal error\n"));
//         exit(1);  
//     }
//     FD_ZERO(&fds);
//     FD_SET(fd_server, &fds);
//     nfds = fd_server + 1;
//     while (1)
//     {
//         rfds = fds;
//         if (select(nfds, &rfds, NULL, NULL, NULL) < 0)
//         {
//             write (2 , "Fatal error\n", strlen("Fatal error\n"));
//             exit(1);    
//         }
//         for (int fd = 0; fd < nfds; fd++)
//         {
//             if (!FD_ISSET(fd, &rfds))
//                 continue;
//             if (fd == fd_server)
//             {
//                 int client  =  accept(fd_server, NULL, NULL);
//                 if (client >= 0)
//                 {
//                     FD_SET(client , &fds);
//                     if (client >= nfds)
//                         nfds = client + 1;
//                     ids[fd] = id++;
//                     idx[fd] = 0;
//                     sprintf(buffer, "server : client %d just arrived\n", ids[fd]);
//                     send_all(client);
//                 }
//             }else
//             {
//                 int r  = recv(fd, msg, sizeof(msg) - 1, 0);
//                 if (r <= 0)
//                 {
//                     sprintf(buffer, "server: client %d just left\n", ids[fd]);
//                     send_all(fd);
//                     FD_CLR(fd,&fds);
//                     close(fd);
//                 }
//                 else
//                 {
//                     for (int i = 0; i < r; i++)
//                     {
//                         client[fd][idx[fd]++] = msg[i];
//                         if (msg[i] == '\n')
//                         {
//                             client[fd][idx[fd]] = '\0';
//                             sprintf(buffer, "cleint %d %s", ids[fd], client[fd]);
//                             send_all(fd);
//                             idx[fd] = 0;
//                         }
//                     }
//                 }
//             }

//         }
//     }


// }
int nfds, id = 0, idx[1024], ids[1024];
int server_fd;
fd_set fds, rfds;
char buffer[600020], msg[600000], clients[1024][600000];

void out(char *str)
{
    write (2, str, strlen(str));
    exit(1);
}

void send_all(int au)
{
    for (int fd = 0; fd < nfds; fd++)
    {
        if (fd != server_fd && fd!= au)
        {
            send(fd, buffer, strlen(buffer), 0);
        }
    }
}

int main(int ac ,char **av)
{
    if(ac !=2)
        out("eeee");
    struct sockaddr_in server_addrr;
    server_addrr.sin_family = AF_INET;
    server_addrr.sin_port = htons(atoi(av[1]));
    server_addrr.sin_addr.s_addr =  htonl(INADDR_LOOPBACK);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        out("FF");
    if (bind(server_fd, (const struct sockaddr *)&server_addrr, sizeof(server_addrr)) < 0)
        out("GG");
    if (listen(server_fd, 10) < 0)
        out ("dd");
    FD_ZERO(&fds);
    FD_SET(server_fd, &fds);
    nfds = server_fd +1;
    while (1)
    {
        rfds = fds;
        if (select(nfds, &rfds, NULL, NULL, NULL) < 0)
            out ("GGG");
        for (int fd = 0; fd < nfds; fd++)
        {
            if (!FD_ISSET(fd, &rfds))
                continue;
            if (fd == server_fd)
            {
                int client =  accept(server_fd, NULL, NULL);
                if (client >= 0)
                {
                    FD_SET(client, &fds);
                    if (client >= nfds)
                        nfds = client + 1;
                    idx[fd] = 0;
                    ids[client] = id;
                    id++;
                    sprintf(buffer, "Server: %d just arrived\n", ids[fd]);
                    send_all(client);
                }
            }
            else{
                int r = recv(fd, msg, sizeof(msg) - 1, 0);
                if (r <= 0)
                {
                    sprintf(buffer, "Server: %d just left\n", ids[fd]);
                    send_all(fd);
                    FD_CLR(fd, &fds);
                    close(fd);
                }
                else{
                    for (int i = 0; i < r; i++)
                    {
                        clients[fd][idx[fd]++] = msg[i];
                        if(msg[i] == '\n')
                        {
                             clients[fd][idx[fd]] = '\0';
                             sprintf(buffer, "Client %d %s", ids[fd], clients[fd]);
                             send_all(fd);
                             idx[fd] = 0;
                        }
                    }
                }
            }
        }
    }

}