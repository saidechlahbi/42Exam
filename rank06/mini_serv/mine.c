#include <stdio.h>
#include <stdlib.h>
#include <socket.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>



int main (int ac, char **av)
{
    if (ac != 2)
    {
        return 1;
    }
    int fd_Server = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_server == -1)
        return 0;
    sockaddr_in soc;
    bzero(&soc, sizeof(soc));
    soc.sin_
}