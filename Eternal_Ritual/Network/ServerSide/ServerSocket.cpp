//
//  ServerSocket.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Network/ServerSide/ServerSocket.hpp"

#ifdef _WIN64
#pragma comment (lib, "ws2_32.lib") 
#elif __APPLE__
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <iostream>

using namespace std;

#ifdef _WIN64
ServerSocket::ServerSocket() {
    WORD sockVersion = MAKEWORD(2,2);  
    WSADATA wsaData;  
    if(WSAStartup(sockVersion, &wsaData) != 0) {  
        perror("Create server socket startup error");
        exit(1);
    }  
    if((server_socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        perror("Create server socket error");
        exit(1);
    }
    
    player_count_ = 0;
}
#elif __APPLE__
ServerSocket::ServerSocket() {
    if ((server_socket_fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Create server socket error");
        exit(1);
    }

    player_count_ = 0;
}
#endif


#ifdef _WIN64
void ServerSocket::startListen() {
    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(SERVER_PORT);
    server_addr_.sin_addr.S_un.S_addr = INADDR_ANY;
    
    if(::bind(server_socket_fd_, (struct sockaddr*)&server_addr_, sizeof(server_addr_)) == SOCKET_ERROR) {
        perror("Server socket bind error");
        exit(1);
    }

    if(listen(server_socket_fd_, LISTEN_QUEUE_SISE) == SOCKET_ERROR) {
        perror("Server socket listen error");
        exit(1);
    }
}
#elif __APPLE__
void ServerSocket::startListen() {
    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(SERVER_PORT);
    server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(server_socket_fd_, (struct sockaddr*)&server_addr_, sizeof(server_addr_)) < 0) {
        perror("Server socket bind error");
        exit(1);
    }

    if (listen(server_socket_fd_, LISTEN_QUEUE_SISE) < 0) {
        perror("Server socket listen error");
        exit(1);
    }
}
#endif


#ifdef _WIN64
vector<unsigned long> ServerSocket::connectAllClients() {
    vector<unsigned long> playerIPs;
    
    int clientAddrLen = sizeof(client_addr_);
    
    while(player_count_ < PLAYER_CAPACITY) {
        int clientSocketFD = accept(server_socket_fd_, (sockaddr*)&client_addr_, &clientAddrLen);
        
        if (clientSocketFD == INVALID_SOCKET) {
            perror("Client socket error");
            continue;
        }

        show_client_info();
        
        unsigned long clientIP = ntohl(client_addr_.sin_addr.s_addr) + ntohs(client_addr_.sin_port);
        playerIPs.emplace_back(clientIP);
        
        client_socket_fds_[clientIP] = clientSocketFD;
        
        ++ player_count_;
        
        cout << "Online Player: " << player_count_ << "/" << PLAYER_CAPACITY << endl;
        cout << endl;
    }
    
    return playerIPs;
}
#elif __APPLE__
vector<unsigned long> ServerSocket::connectAllClients() {
    vector<unsigned long> playerIPs;

    socklen_t clientAddrLen = sizeof(client_addr_);

    while (player_count_ < PLAYER_CAPACITY) {
        int clientSocketFD = accept(server_socket_fd_, (sockaddr*)&client_addr_, &clientAddrLen);

        if (clientSocketFD < 0) {
            perror("Client socket error");
            continue;
        }

        show_client_info();

        unsigned long clientIP = ntohl(client_addr_.sin_addr.s_addr) + ntohs(client_addr_.sin_port);
        playerIPs.emplace_back(clientIP);

        client_socket_fds_[clientIP] = clientSocketFD;

        ++player_count_;

        cout << "Online Player: " << player_count_ << "/" << PLAYER_CAPACITY << endl;
        cout << endl;
    }

    return playerIPs;
}
#endif


#ifdef _WIN64
void ServerSocket::receiveData(vector<unsigned long>& playerIP, char (*readBuffer)[MAX_BUFFER_SIZE], vector<int>& dataLen)  {
    int i = 0;
    for (auto& clientSocketFD : client_socket_fds_) {
        int newDataLen = static_cast<int> (recv(clientSocketFD.second, read_buffer_, MAX_BUFFER_SIZE, 0));
//        std::cout <<clientSocketFD.second << std::endl;
//        std::cout << std::endl;
//        std::cout << "Receive" << dataLen << std::endl;
//        std::cout << "Receive (string lenth): " << strlen(read_buffer_) << std::endl;
//        std::cout << "Receive: " << read_buffer_ << std::endl;

        if (newDataLen > 0) {
            read_buffer_[newDataLen] = 0x00;
            playerIP.push_back(clientSocketFD.first);
            memcpy(readBuffer[i++], read_buffer_, MAX_BUFFER_SIZE);
            dataLen.push_back(newDataLen);
        }
        else {
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << "Game Over " << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            exit(1);
        }
    }
}
#elif __APPLE__
void ServerSocket::receiveData(vector<unsigned long>& playerIP, char (*readBuffer)[MAX_BUFFER_SIZE], vector<int>& dataLen) {
    int i = 0;
    for (auto& clientSocketFD : client_socket_fds_) {
        int newDataLen = static_cast<int> (read(clientSocketFD.second, read_buffer_, MAX_BUFFER_SIZE));
//                std::cout <<clientSocketFD.second << std::endl;
//                std::cout << std::endl;
//                std::cout << "Receive" << newDataLen << std::endl;
//                std::cout << "Receive (string lenth): " << strlen(read_buffer_) << std::endl;
//                std::cout << "Receive: " << read_buffer_ << std::endl;

        if (newDataLen > 0) {
            read_buffer_[newDataLen] = 0x00;
            playerIP.push_back(clientSocketFD.first);
            memcpy(readBuffer[i++], read_buffer_, MAX_BUFFER_SIZE);
            dataLen.push_back(newDataLen);
        }
        else {
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << "Game Over " << endl;
            cout << "-----------------------------" << endl;
            cout << endl;
            exit(1);
        }
    }
}
#endif


#ifdef _WIN64
void ServerSocket::sendData(unsigned long playerIP, char* pbArr,int dataLen) {
    memset(write_buffer_, 0, MAX_BUFFER_SIZE);
    memcpy(write_buffer_, pbArr, dataLen);
    
    long writeLen = send(client_socket_fds_[playerIP], write_buffer_, MAX_BUFFER_SIZE, 0);
    if (writeLen != MAX_BUFFER_SIZE) {
        perror("Send to client error");
        exit(1);
    }
}
#elif __APPLE__
void ServerSocket::sendData(unsigned long playerIP, char* pbArr, int dataLen) {
    memset(write_buffer_, 0, MAX_BUFFER_SIZE);
    memcpy(write_buffer_, pbArr, dataLen);

    long writeLen = write(client_socket_fds_[playerIP], write_buffer_, MAX_BUFFER_SIZE);
    if (writeLen != MAX_BUFFER_SIZE) {
        perror("Send to client error");
        exit(1);
    }
}
#endif


#ifdef _WIN64
void ServerSocket::closeSockets() {
    for (auto& clientSocketFD : client_socket_fds_) {
        closesocket(clientSocketFD.second);
        -- player_count_;
    }
    closesocket(server_socket_fd_);
    WSACleanup(); 
}
#elif __APPLE__
void ServerSocket::closeSockets() {
    for (auto& clientSocketFD : client_socket_fds_) {
        close(clientSocketFD.second);
        --player_count_;
    }
    close(server_socket_fd_);
}
#endif


#ifdef _WIN64
void ServerSocket::show_client_info() {
    char* ipAddr = inet_ntoa(client_addr_.sin_addr);

    cout << "Connected by " << ipAddr << "(" << ntohs(client_addr_.sin_port) << ")" << std::endl;
}
#elif __APPLE__
void ServerSocket::show_client_info() {
    char ipAddr[16];
    memset(ipAddr, 0, sizeof(ipAddr));

    inet_ntop(AF_INET, &client_addr_.sin_addr.s_addr, ipAddr, sizeof(ipAddr));

    cout << "Connected by " << ipAddr << "(" << ntohs(client_addr_.sin_port) << ")" << std::endl;
}
#endif
