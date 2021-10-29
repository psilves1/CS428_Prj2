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
using namespace std;
//Server side
int main(int argc, char *argv[])
{

    //grab the port number
    int port = 12345; //atoi(argv[1]);
    //buffer to send and receive messages with
    char msg[1500];
    char msg2[1500];
     
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error with the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }


    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr2;
    socklen_t newSockAddrSize2 = sizeof(newSockAddr2);
    //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSd2 = accept(serverSd, (sockaddr *)&newSockAddr2, &newSockAddrSize2);
    if(newSd2 < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }

    memset(&msg, 0, sizeof(msg));//clear the buffer
    memset(&msg2, 0, sizeof(msg2));//clear the buffer

    int first = 0;

    recv(newSd, (char*)&msg, sizeof(msg), 0);
    recv(newSd2, (char*)&msg2, sizeof(msg2), 0);

    std::cout << msg << std::endl;
    std::cout << msg2 << std::endl;
    
  

    string s = " received before ";

    string msg3= msg + s + msg2;

    std::cout << msg3 << std::endl;

    char msg4[1500];

    strcpy(msg4, msg3.c_str());

    send(newSd, (char *)&msg4, strlen(msg4), 0);
    send(newSd2, (char *)&msg4, strlen(msg4), 0);



    return 0;   
}