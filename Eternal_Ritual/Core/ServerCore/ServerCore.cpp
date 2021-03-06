//
//  ServerCore.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Core/ServerCore/ServerCore.hpp"

#include <time.h>
#include <iostream>

using namespace std;


#ifdef _WIN64
int gettimeofday(struct timeval* tp, void* tzp);
#endif

ServerCore* ServerCore::server_core_ = nullptr;

ServerCore::ServerCore() {
    tick_end_ = new timeval();
    curr_time_ = new timeval();
}


ServerCore::~ServerCore() {
    for (auto& eventPb : event_pbs_) {
        delete eventPb.second;
    }
    delete state_pb_;
    delete server_socket_;
    delete tick_end_;
    delete curr_time_;
}


void ServerCore::openServer() {
    server_socket_ = new ServerSocket();
    server_socket_->startListen();
    
    std::cout << "Ready to connect all clients..." << std::endl;
    std::cout << std::endl;
    
    player_ips_ = server_socket_->connectAllClients();
    
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Game Begin " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << std::endl;
}


void ServerCore::initPbPacket() {
    for (auto playerIP : player_ips_) {
        event_pbs_[playerIP] = new EventPb();
    }
    state_pb_ = new StatePb();
}


void ServerCore::setTickEnd() {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Server Cycle " << ++server_cycle_ << ":" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    gettimeofday(tick_end_, NULL);
    tick_end_->tv_usec += 15000;
    if (tick_end_->tv_usec >= 1000000) {
        tick_end_->tv_usec -= 1000000;
        tick_end_->tv_sec += 1;
    }
}


void ServerCore::receiveData() {
    std::cout << std::endl;
    std::cout << "|-- Stage 1 - Receive data --|" << std::endl;
    
    vector<unsigned long> playerIP;
    vector<int> dataLen;
    server_socket_->receiveData(playerIP, read_buffer_, dataLen);
    
    for (int i = 0; i < playerIP.size(); i++) {
        processData(playerIP[i], read_buffer_[i], dataLen[i]);
    }
}


void ServerCore::processData(unsigned long playerIP, char* pbArr, int dataLen) {
    if (event_pbs_.count(playerIP)) {
    
        event_pbs_[playerIP]->clearData();
        event_pbs_[playerIP]->readData(pbArr, dataLen);
    }
}


void ServerCore::updateState() {
    std::cout << std::endl;
    std::cout << "|-- Stage 2 - Updata state --|" << std::endl;
    
    unordered_map<unsigned long, int> tempPlayerHPs;
    unordered_map<unsigned long, int> tempPlayerMPs;
    for (int i = 0; i < player_ips_.size(); i++) {
        unsigned long playerIP = player_ips_[i];
        EventPb* event_pb = event_pbs_[playerIP];
        if (start_game_) {
            state_pb_->setPlayerGroup(playerIP, i);
        }
        else {
            state_pb_->setControlNodeEulerAngles(playerIP, event_pb->getControlNodeEulerAngles());
            state_pb_->setMoveDirection(playerIP, event_pb->getMoveDirection());
            state_pb_->setDirState(playerIP, event_pb->getDirState());
            state_pb_->setCharStatePb(playerIP, event_pb->getCharStatePb());
            state_pb_->setPlayerStyle(playerIP, event_pb->getPlayerStyle());
            state_pb_->setRoll(playerIP, event_pb->getRoll());
            state_pb_->setToggleLock(playerIP, event_pb->getToggleLock());
            
            if (event_pb->hasMagicEvents()) {
                vector<gameDataPb::MagicPb> magicEvents = event_pb->getMagicEvents();
                for (auto& magicEvent : magicEvents) {
                    state_pb_->addMagicEvent(playerIP, magicEvent);
                }
            }
            
            for (auto& tempPlayerIP : player_ips_) {
                tempPlayerHPs[tempPlayerIP] += event_pb->getPlayerHP(tempPlayerIP);
                tempPlayerMPs[tempPlayerIP] += event_pb->getPlayerMP(tempPlayerIP);
            }
        }
    }
    
    if (!start_game_) {
        for (auto& it : tempPlayerHPs) {
            state_pb_->setPlayerHP(it.first, it.second / PLAYER_CAPACITY);
        }
        for (auto& it : tempPlayerMPs) {
            state_pb_->setPlayerMP(it.first, it.second / PLAYER_CAPACITY);
        }
    }
}


void ServerCore::sendData() {
    std::cout << std::endl;
    std::cout << "|-- Stage 3 - Send data --|" << std::endl;
    
    if (start_game_) {
        for (auto& playerIP : this->player_ips_) {
            state_pb_->setPlayerIP(playerIP);
            
            char* pbArr = state_pb_->sendData();
            int dataLen = state_pb_->data_len();
            
            server_socket_->sendData(playerIP, pbArr, dataLen);
        }
        
        this->start_game_ = false;
    }
    else {
        char* pbArr = state_pb_->sendData();
        int dataLen = state_pb_->data_len();
        
//        std::cout << std::endl;
//        std::cout << "datalen: " << dataLen << std::endl;
        
        for (auto& playerIP : this->player_ips_) {
            server_socket_->sendData(playerIP, pbArr, dataLen);
        }
    }
    
    state_pb_->clearData();
}


inline long timeval_usecdiff(timeval* start_time, timeval* finish_time) {
    long usec;
    usec = (finish_time->tv_sec - start_time->tv_sec) * 1000000;
    usec += (finish_time->tv_usec - start_time->tv_usec);
    return usec;
}

void ServerCore::waitTickEnd() {
    std::cout << std::endl;
    std::cout << "|-- Stage 4 - Wait tick end --|" << std::endl;
    
    do {
        gettimeofday(curr_time_, NULL);
    } while (timeval_usecdiff(curr_time_, tick_end_) > 0);
}


void ServerCore::closeServer() {
    server_socket_->closeSockets();
}


void destructClientCore(int signum) {
    std::cout << "Game over" << std::endl;
    
    ServerCore::Instance()->closeServer();
    
    ServerCore::Destructor();
    
    exit(1);
}


#ifdef _WIN64
int gettimeofday(struct timeval *tp, void *tzp)
{
  time_t clock;
  struct tm tm;
  SYSTEMTIME wtm;
  GetLocalTime(&wtm);
  tm.tm_year   = wtm.wYear - 1900;
  tm.tm_mon   = wtm.wMonth - 1;
  tm.tm_mday   = wtm.wDay;
  tm.tm_hour   = wtm.wHour;
  tm.tm_min   = wtm.wMinute;
  tm.tm_sec   = wtm.wSecond;
  tm. tm_isdst  = -1;
  clock = mktime(&tm);
  tp->tv_sec = clock;
  tp->tv_usec = wtm.wMilliseconds * 1000;
  return (0);
}
#endif
