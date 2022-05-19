//
//  ClientSocket.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <arpa/inet.h>

#include "Network/NetworkSetting.inc"


class ClientSocket final {
public:
    ClientSocket();
    ~ClientSocket() {}

    void connectServer();
    void receiveData();
    void sendData(char* pbArr,int dataLen);
    void closeSockets();

private:
    int client_socket_fd_;
    sockaddr_in server_addr_;
    char read_buffer_[MAX_BUFFER_SIZE];
    char write_buffer_[MAX_BUFFER_SIZE];
};



#endif /* ClientSocket_hpp */
