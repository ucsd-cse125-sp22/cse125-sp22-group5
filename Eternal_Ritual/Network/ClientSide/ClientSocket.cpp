//
//  ClientSocket.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Network/ClientSide/ClientSocket.hpp"

#pragma comment (lib, "ws2_32.lib") 

#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;


ClientSocket::ClientSocket() {
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if(WSAStartup(sockVersion, &data)!=0) {
		perror("Client socket startup error");
        exit(1);
	}

    if ((client_socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        perror("Client socket error");
        exit(1);
    }
}

void ClientSocket::connectServer() {
    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
    server_addr_.sin_port = htons(SERVER_PORT);
    
    if(connect(client_socket_fd_, (sockaddr*) &server_addr_, sizeof(server_addr_)) == SOCKET_ERROR) {
        perror("Connection error");
        closesocket(client_socket_fd_);
        exit(1);
    }
}

void ClientSocket::receiveData(char*& pbArr, int& dataLen) {
    int newDataLen = static_cast<int> (recv(client_socket_fd_, read_buffer_, MAX_BUFFER_SIZE, 0));
    
//    std::cout << std::endl;
//    std::cout << "Receive" << dataLen << std::endl;
    
    if (newDataLen > 0) {
        // ClientCore::Instance()->processData(read_buffer_, dataLen);
        pbArr = read_buffer_;
        dataLen = newDataLen;
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

void ClientSocket::sendData(char* pbArr,int dataLen) {
    memset(write_buffer_, 0, MAX_BUFFER_SIZE);
    memcpy(write_buffer_, pbArr, dataLen);
    
    long writeLen = send(client_socket_fd_, write_buffer_, MAX_BUFFER_SIZE, 0);
    
//    std::cout << std::endl;
//    std::cout << "Sending: " << writeLen << std::endl;
    
    if (writeLen != MAX_BUFFER_SIZE) {
        perror("Send to client error");
        exit(1);
    }
}

void ClientSocket::closeSockets() {
    closesocket(client_socket_fd_);
    WSACleanup();
}
