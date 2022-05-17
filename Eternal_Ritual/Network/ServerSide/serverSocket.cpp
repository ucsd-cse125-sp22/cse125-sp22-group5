#include "serverSocket.hpp"
#include "serverCore.hpp"

ServerSocket::ServerSocket() {
    if((serverSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Create server socket error");
        exit(1);
    }
    
    playerCount = 0;
}

void ServerSocket::startListen() {
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(::bind(serverSocketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Server socket bind error");
        exit(1);
    }

    if(listen(serverSocketFD, LISTEN_QUEUE_SISE) < 0) {
        perror("Server socket listen error");
        exit(1);
    }
}

vector<ulong> ServerSocket::connectAllClients() {
    vector<ulong> playerIPs;
    
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    while(playerCount < PLAYER_CAPACITY) {
        int clientSocketFD = accept(serverSocketFD, (sockaddr*)&clientAddr, &clientAddrLen);
        
        if (clientSocketFD < 0) {
            perror("Client socket error");
            continue;
        }

        show_client_info();
        
        ulong clientIP = ntohl(clientAddr.sin_addr.s_addr) + ntohs(clientAddr.sin_port);
        playerIPs.emplace_back(clientIP);
        
        clientSocketFDs[clientIP] = clientSocketFD;
        
        ++ playerCount;
        
        cout << "Online Player: " << playerCount << "/" << PLAYER_CAPACITY << endl;
        cout << endl;
    }
    
    return playerIPs;
}

void ServerSocket::receiveData() {
    for (auto& clientSocketFD : clientSocketFDs) {
        int dataLen = static_cast<int> (read(clientSocketFD.second, readBuffer, MAX_BUFFER_SIZE));
//        std::cout <<clientSocketFD.second << std::endl;
        std::cout << std::endl;
        std::cout << "Receive" << dataLen << std::endl;
        std::cout << "Receive (string lenth): " << strlen(readBuffer) << std::endl;
        std::cout << "Receive: " << readBuffer << std::endl;

        if (dataLen > 0) {
            readBuffer[dataLen] = 0x00;
            ServerCore::Instance()->processData(clientSocketFD.first, readBuffer, dataLen);
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


void ServerSocket::sendData(ulong playerIP, char* pbArr,int dataLen) {
    memset(writeBuffer, 0, MAX_BUFFER_SIZE);
    memcpy(writeBuffer, pbArr, dataLen);
    
    long writeLen = write(clientSocketFDs[playerIP], writeBuffer, MAX_BUFFER_SIZE);
    if (writeLen != MAX_BUFFER_SIZE) {
        perror("Send to client error");
        exit(1);
    }
}


void ServerSocket::closeSockets() {
    for (auto& clientSocketFD : clientSocketFDs) {
        close(clientSocketFD.second);
        -- playerCount;
    }
    close(serverSocketFD);
}


void ServerSocket::show_client_info() {
    char ipAddr[16];
    memset(ipAddr, 0, sizeof(ipAddr));

    inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, ipAddr, sizeof(ipAddr));

    cout << "Connected by " << ipAddr << "(" << ntohs(clientAddr.sin_port) << ")" << std::endl;
}
