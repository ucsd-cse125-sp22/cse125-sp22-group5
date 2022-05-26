//
//  ServerSocket.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <winsock2.h>
#include <vector>
#include <unordered_map>

#include "Network/NetworkSetting.inc"


class ServerSocket {
public:
    ServerSocket();
    ~ServerSocket() {}

    void startListen();
    std::vector<unsigned long> connectAllClients();
    void receiveData(unsigned long& playerIP, char*& pbArr, int& dataLen);
    void sendData(unsigned long playerIP, char* pbArr, int dataLen);
    void closeSockets();
    
    void show_client_info();

private:
    SOCKET server_socket_fd_;
    unsigned short player_count_;
    std::unordered_map<unsigned long, SOCKET> client_socket_fds_;
    sockaddr_in server_addr_;
    sockaddr_in client_addr_;
    char read_buffer_[MAX_BUFFER_SIZE];
    char write_buffer_[MAX_BUFFER_SIZE];
};


#endif /* serverSocket_hpp */
