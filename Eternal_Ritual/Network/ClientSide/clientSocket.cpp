#include "clientSocket.hpp"
#include "clientCore.hpp"

ClientSocket::ClientSocket() {
    if ((clientSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client socket error");
        exit(1);
    }
}

void ClientSocket::connectServer() {
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);
    
    if(connect(clientSocketFD, (sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection error");
        exit(1);
    }
}

void ClientSocket::receiveData() {
    int dataLen = static_cast<int> (read(clientSocketFD, readBuffer, MAX_BUFFER_SIZE));
    
    std::cout << std::endl;
    std::cout << "Receive" << dataLen << std::endl;
    
    if (dataLen > 0) {
        ClientCore::Instance()->processData(readBuffer, dataLen);
    }
}

void ClientSocket::sendData(char* pbArr,int dataLen) {
    memset(writeBuffer, 0, MAX_BUFFER_SIZE);
    memcpy(writeBuffer, pbArr, dataLen);
    
    long writeLen = write(clientSocketFD, writeBuffer, MAX_BUFFER_SIZE);
    
    std::cout << std::endl;
    std::cout << "Sending: " << writeLen << std::endl;
    
    if (writeLen != MAX_BUFFER_SIZE) {
        perror("Send to client error");
        exit(1);
    }
}

void ClientSocket::closeSockets() {
    close(clientSocketFD);
}
