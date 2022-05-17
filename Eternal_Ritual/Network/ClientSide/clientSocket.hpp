#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "common.hpp"


#define SERVER_PORT 8888
//#define SERVER_IP "70.95.147.7"
//#define SERVER_IP "100.81.38.56"
#define SERVER_IP "0.0.0.0"
#define MAX_BUFFER_SIZE 500


class ClientSocket {
public:
    ClientSocket();
    ~ClientSocket() {}

    void connectServer();
    void receiveData();
    void sendData(char* pbArr,int dataLen);
    void closeSockets();

private:
    int clientSocketFD;
    sockaddr_in serverAddr;
    char readBuffer[MAX_BUFFER_SIZE];
    char writeBuffer[MAX_BUFFER_SIZE];
};



#endif /* clientSocket_hpp */
