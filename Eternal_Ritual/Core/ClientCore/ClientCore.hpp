//
//  ClientCore.hpp
//
//  Created by Kangming Yu on 4/15/22.
//

#ifndef CLIENTCORE_HPP
#define CLIENTCORE_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "KGLEngine/Engine.hpp"

#include "Network/Packet/StatePb.hpp"
#include "Network/Packet/EventPb.hpp"
#include "Network/ClientSide/ClientSocket.hpp"
#include "Game/Map/MapSystemManager.hpp"
#include "Game/Character/HitController.hpp"
#include "Game/Character/CharNode.hpp"
#include "Game/Magic/BaseMagic.hpp"


class ClientCore {
public:
    static ClientCore* Instance() {
        if (client_core_ == nullptr) {
            client_core_ = new ClientCore();
        }
        return client_core_;
    }

    static void Destructor() {
        if (client_core_ != nullptr) {
            delete client_core_;
            client_core_ = nullptr;
        }
    }
    
    void initEngine();
    void loadSky();
    void loadLight();
    void loadScene();
    void loadCharacter();
    void loadMagic();
    void loadDamageSystem();
    
    void loadPbPacket();
    void connectServer();
    void handleEvent();
    void sendData();
    void receiveData();
    void processData(char* pbArr, int dataLen);
    void updateState();
    void renderWorld();
    void closeConnect();

private:
    // Singleton pattern
    static ClientCore* client_core_;
    ClientCore();
    ~ClientCore();
    
    // Socket
    ClientSocket* client_socket_;
    unsigned long long client_cycle_ = 0;
    
    // Pb
    EventPb* event_pb_;
    StatePb* state_pb_;
    
    // Engine
    Engine* engine_;
    
    // Light
    LightNode* point_light_;
    LightNode* ambient_light_;
    LightNode* directional_light_;
    LightNode* spot_light_;
    
    // Map
    MapSystemManager* map_system_manager_;
    
    // Character
    CharNode* character_;
    unsigned long character_ip_;
    
    // Magic
    std::unordered_map<int, Magic::Type> key_to_magic_;
    std::unordered_map<Magic::Type, int> magic_to_key_;
    std::unordered_set<BaseMagic*> all_magics_;
    
    // All Characters
    std::vector<CharNode*> pre_chars_;
    std::unordered_map<unsigned long, CharNode*> all_chars_;
    
    // HitController
    HitController*  hit_controller_;
    
    // Game
    bool start_game_ = true;
};

void destructClientCore(int signum);

#endif /* ClientCore_hpp */
