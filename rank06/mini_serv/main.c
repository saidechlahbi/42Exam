#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

typedef struct s_client
{
    int id;
    char *input;
    char *output;
}	t_client;

t_client clients[1024];
fd_set active;
fd_set readfds;
fd_set writefds;
int fdmax;

void fatal_error(void)
{
    write(2, "Fatal error\n", 12);
    exit(1);
}

int append_data(char **destination, char *source, int length)
{
    int old_length;
    int index;
    char *new_data;

    old_length = 0;
    if (*destination)
        old_length = strlen(*destination);
    new_data = realloc(*destination, old_length + length + 1);
    if (!new_data)
        return (0);
    index = 0;
    while (index < length)
    {
        new_data[old_length + index] = source[index];
        index++;
    }
    new_data[old_length + length] = '\0';
    *destination = new_data;
    return (1);
}

void free_client_data(int fd)
{
    free(clients[fd].input);
    free(clients[fd].output);
    clients[fd].input = NULL;
    clients[fd].output = NULL;
}

int main(int argc, char **argv)
{
    struct sockaddr_in server_address;
    int server_fd;
    int next_id;

    if (argc != 2)
    {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        fatal_error();

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[1]));
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(server_fd, (struct sockaddr *)&server_address,
            sizeof(server_address)) < 0)
        fatal_error();
    if (listen(server_fd, 10) < 0)
        fatal_error();

    FD_ZERO(&active);
    FD_SET(server_fd, &active);
    fdmax = server_fd;
    next_id = 0;

    while (1)
    {
        int fd;

        readfds = active;
        FD_ZERO(&writefds);
        fd = 0;
        while (fd <= fdmax)
        {
            if (fd != server_fd && clients[fd].output)
                FD_SET(fd, &writefds);
            fd++;
        }

        if (select(fdmax + 1, &readfds, &writefds, NULL, NULL) < 0)
            fatal_error();

        if (FD_ISSET(server_fd, &readfds))
        {
            struct sockaddr_in client_address;
            socklen_t address_length;
            int client_fd;
            char message[1024];
            int message_length;

            address_length = sizeof(client_address);
            client_fd = accept(server_fd,
                    (struct sockaddr *)&client_address, &address_length);
            if (client_fd < 0)
                fatal_error();

            clients[client_fd].id = next_id;
            clients[client_fd].input = NULL;
            clients[client_fd].output = NULL;
            next_id++;

            FD_SET(client_fd, &active);
            if (client_fd > fdmax)
                fdmax = client_fd;

            message_length = sprintf(message,
                    "server: client %d just arrived\n",
                    clients[client_fd].id);

            fd = 0;
            while (fd <= fdmax)
            {
                if (fd != server_fd && fd != client_fd
                    && FD_ISSET(fd, &active))
                {
                    if (!append_data(&clients[fd].output,
                            message, message_length))
                        fatal_error();
                }
                fd++;
            }
        }

        fd = 0;
        while (fd <= fdmax)
        {
            if (fd != server_fd && FD_ISSET(fd, &readfds))
            {
                char buffer[1024];
                int received;

                received = recv(fd, buffer, sizeof(buffer), 0);
                if (received < 0)
                    fatal_error();

                if (received == 0)
                {
                    char message[1024];
                    int message_length;
                    int other_fd;

                    message_length = sprintf(message,
                            "server: client %d just left\n",
                            clients[fd].id);

                    other_fd = 0;
                    while (other_fd <= fdmax)
                    {
                        if (other_fd != fd && other_fd != server_fd
                            && FD_ISSET(other_fd, &active))
                        {
                            if (!append_data(&clients[other_fd].output,
                                    message, message_length))
                                fatal_error();
                        }
                        other_fd++;
                    }

                    free_client_data(fd);
                    close(fd);
                    FD_CLR(fd, &active);
                }
                else if (!append_data(&clients[fd].input, buffer, received))
                    fatal_error();
                else
                {
                    char *newline;

                    newline = strstr(clients[fd].input, "\n");
                    while (newline)
                    {
                        char prefix[1024];
                        int prefix_length;
                        int line_length;
                        int remaining_length;
                        char *remaining;
                        int other_fd;

                        line_length = newline - clients[fd].input + 1;
                        prefix_length = sprintf(prefix,
                                "client %d: ", clients[fd].id);

                        other_fd = 0;
                        while (other_fd <= fdmax)
                        {
                            if (other_fd != fd && other_fd != server_fd
                                && FD_ISSET(other_fd, &active))
                            {
                                if (!append_data(&clients[other_fd].output,
                                        prefix, prefix_length)
                                    || !append_data(&clients[other_fd].output,
                                        clients[fd].input, line_length))
                                    fatal_error();
                            }
                            other_fd++;
                        }

                        remaining_length = strlen(clients[fd].input)
                            - line_length;
                        remaining = NULL;
                        if (remaining_length > 0)
                        {
                            remaining = malloc(remaining_length + 1);
                            if (!remaining)
                                fatal_error();
                            strcpy(remaining,
                                clients[fd].input + line_length);
                        }

                        free(clients[fd].input);
                        clients[fd].input = remaining;
                        if (clients[fd].input)
                            newline = strstr(clients[fd].input, "\n");
                        else
                            newline = NULL;
                    }
                }
            }
            fd++;
        }

        fd = 0;
        while (fd <= fdmax)
        {
            if (fd != server_fd && FD_ISSET(fd, &writefds))
            {
                int sent;
                int remaining_length;
                char *remaining;

                sent = send(fd, clients[fd].output,
                        strlen(clients[fd].output), 0);
                if (sent < 0)
                    fatal_error();

                remaining_length = strlen(clients[fd].output) - sent;
                remaining = NULL;
                if (remaining_length > 0)
                {
                    remaining = malloc(remaining_length + 1);
                    if (!remaining)
                        fatal_error();
                    strcpy(remaining, clients[fd].output + sent);
                }

                free(clients[fd].output);
                clients[fd].output = remaining;
            }
            fd++;
        }
    }
}