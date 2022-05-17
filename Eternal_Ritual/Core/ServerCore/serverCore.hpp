#ifndef SERVERCORE_HPP
#define SERVERCORE_HPP

#include <sys/time.h>

#include "common.hpp"

#include "statePb.hpp"
#include "eventPb.hpp"
#include "serverSocket.hpp"
#include "../Game/includes.hpp"
#include "../Game/magics.hpp"


class ServerCore {
public:
    static ServerCore* Instance() {
        if (serverCore == nullptr) {
            serverCore = new ServerCore();
        }
        return serverCore;
    }

    static void Destructor() {
        if (serverCore != nullptr) {
            delete serverCore;
            serverCore = nullptr;
        }
    }
    
    void openServer();
    
    void initPbPacket();
    
    void initEngine();
    void loadScene();
    void loadCharacters();

    
    void setTickEnd();
    void receiveData();
    void processData(ulong playerIP, char* pbArr, int dataLen);
    void updateState();
    void sendData();
    void waitTickEnd();
    void closeServer();

private:
    // Singleton pattern
    static ServerCore* serverCore;
    ServerCore();
    ~ServerCore();
    
    // Socket
    ServerSocket* serverSocket;
    
    
    // Pb
    vector<ulong> playerIPs;
    unordered_map<ulong, EventPb*> eventPbs;
    StatePb* statePb;
    
    // Time
    timeval* tickEnd;
    timeval* currTime;
    ulonglong serverCycle;
    
    // Engine
    Engine* engine;
    
    // Scene
    Node* sceneNode;
    MapSystemManager* mapSystemManager;
    
    // Weapon
    unordered_map<ulong, Node*> characterWeapons;
    
    // Character
    unordered_map<ulong, CharNode*> characters;
    
    // Magic
    unordered_set<BaseMagic*> allMagics;
    
    // Game
    bool startGame = true;
};



#endif /* serverCore_hpp */
