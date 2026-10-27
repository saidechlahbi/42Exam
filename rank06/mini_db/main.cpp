#include <iostream>
#include <unordered_map>
#include <sys/socket.h>


#include <cstring>



 
int main (int ac, char **av)
{
    if (ac != 3)
        return 1;
    std::string port = av[1];
    for (int i = 0; i < port.length(); i++)
        if(!isdigit(port[i]))
            return 1;
    std::unordered_map<std::string , std::string > database;

    int fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (fd == -1)
        return 1;
    struct sockaddr_in serverAddr;
    // memset($serverAddr, 0, sizeof(serverAddr));




    int aa =  bind(fd, (sockaddr *) &serverAddr, sizeof(serverAddr) > 0);
    if (aa == -1)
        return 1;
    
    int bb = listen(fd, SOMAXCONN);
    if (bb == -1)
        return 1;

    std::cout << fd  << " good job"<< std::endl;
    return 0;
}