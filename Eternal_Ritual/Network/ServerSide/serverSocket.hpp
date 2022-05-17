#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "common.hpp"

#define SERVER_PORT 8888
#define LISTEN_QUEUE_SISE 10
#define MAX_BUFFER_SIZE 500
#define PLAYER_CAPACITY 4


class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket() {}

    void startListen();
    vector<ulong> connectAllClients();
    void receiveData();
    void sendData(ulong playerIP, char* pbArr,int dataLen);
    void closeSockets();
    
    void show_client_info();

private:
    int serverSocketFD;
    ushort playerCount;
    unordered_map<ulong, int> clientSocketFDs;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    char readBuffer[MAX_BUFFER_SIZE];
    char writeBuffer[MAX_BUFFER_SIZE];
};


#endif /* serverSocket_hpp */
