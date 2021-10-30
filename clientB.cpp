#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

//Client side
int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cerr << "./usage ipAddress" << std::endl;
        return 0;
    }
    char *serverIp = argv[1];
    int port = 12345; //atoi(argv[2]);
    //create a message buffer
    char msg[1500];
    //setup a socket and connection tools
    struct hostent *host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (status < 0)
    {
        std::cout << "Error connecting to socket!" << std::endl;
        return 0;
    }

    //std::cout << "What is your message: ";
    std::string data = "B: Paul Silvestri";
    //getline(std::cin, data);

    memset(&msg, 0, sizeof(msg)); //clear the buffer
    strcpy(msg, data.c_str());
    send(clientSd, (char *)&msg, strlen(msg), 0);
    memset(&msg, 0, sizeof(msg)); //clear the buffer
    recv(clientSd, (char *)&msg, sizeof(msg), 0);

    std::cout << msg << std::endl;
    std::cout << data << std::endl;


    return 0;
}
