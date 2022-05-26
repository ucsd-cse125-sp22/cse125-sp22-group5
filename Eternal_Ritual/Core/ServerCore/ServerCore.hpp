//
//  ServerCore.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef SERVERCORE_HPP
#define SERVERCORE_HPP

#ifdef _WIN64
#include <winsock2.h>
#include <windows.h>
#elif __APPLE__
#include <sys/time.h>
#endif


#include <unordered_map>
#include <vector>

#include "Network/Packet/StatePb.hpp"
#include "Network/Packet/EventPb.hpp"
#include "Network/ServerSide/ServerSocket.hpp"


class ServerCore {
public:
    static ServerCore* Instance() {
        if (server_core_ == nullptr) {
            server_core_ = new ServerCore();
        }
        return server_core_;
    }

    static void Destructor() {
        if (server_core_ != nullptr) {
            delete server_core_;
            server_core_ = nullptr;
        }
    }
    
    void openServer();
    
    void initPbPacket();
    
    void setTickEnd();
    void receiveData();
    void processData(unsigned long playerIP, char* pbArr, int dataLen);
    void updateState();
    void sendData();
    void waitTickEnd();
    void closeServer();

private:
    // Singleton pattern
    static ServerCore* server_core_;
    ServerCore();
    ~ServerCore();
    
    // Socket
    ServerSocket* server_socket_;
    
    // Pb
    std::vector<unsigned long> player_ips_;
    std::unordered_map<unsigned long, EventPb*> event_pbs_;
    StatePb* state_pb_;
    
    // Time
    timeval* tick_end_;
    timeval* curr_time_;
    unsigned long long server_cycle_ = 0;
    
    // Game
    bool start_game_ = true;
};

void destructClientCore(int signum);

#endif /* serverCore_hpp */
