//
//  ClientSocket.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#ifdef _WIN64
#include <winsock2.h>
#define SOCKET SOCKET
#elif __APPLE__
#include <arpa/inet.h>
#define SOCKET int
#endif

#include "Network/NetworkSetting.inc"


class ClientSocket final {
public:
    ClientSocket();
    ~ClientSocket() {}

    void connectServer();
    void receiveData(char*& pbArr, int& dataLen);
    void sendData(char* pbArr,int dataLen);
    void closeSockets();

private:
    SOCKET client_socket_fd_;
    sockaddr_in server_addr_;
    char read_buffer_[MAX_BUFFER_SIZE];
    char write_buffer_[MAX_BUFFER_SIZE];
};



#endif /* ClientSocket_hpp */
