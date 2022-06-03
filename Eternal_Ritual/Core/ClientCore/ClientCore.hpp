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
#include "Game/UI/AllUI.inc"
#include "Game/CG/CameraController.hpp"


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
    void loadFont();
    void displayLogo();
    void playLogo();
    
    void updateLoad();
    
    void loadSky();
    void loadLight();
    void loadMap();
    void loadCharacter();
    void loadMagic();
    void loadDamageSystem();
    void loadStartScene();
    void loadDeathScene();
    
    void displayStart();
    void updateStart();
    void playCG();
    
    void loadHUD();
    void loadPbPacket();
    void connectServer();
    void handleEvent();
    void sendData();
    void receiveData();
    void processData(char* pbArr, int dataLen);
    void updateState();
    void renderWorld();
    
    void resetGame();
    
    void closeConnect();
    
    int process();
    void set_process(int process);
    int load_state();

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
    LightNode* verticle_light_;
    
    // Map
    MapSystemManager* map_system_manager_;
    
    // Camera
    CameraNode* ui_camera_;
    CameraNode* char_camera_;
    bool main_camera_ = true;
    int char_camera_index_;
    
    // Character
    CharNode* character_;
    unsigned long character_ip_;
    int character_index_;
    
    // Ally
    CharNode* ally_;
    int ally_index_;
    
    // enemy
    std::unordered_map<CharNode*, std::vector<CharNode*>> enemies_;
    
    // Magic
    std::unordered_map<int, Magic::Type> key_to_magic_;
    std::unordered_map<Magic::Type, int> magic_to_key_;
    std::unordered_set<BaseMagic*> all_magics_;
    
    // All Characters
    std::vector<CharNode*> pre_chars_;
    std::unordered_map<unsigned long, CharNode*> all_chars_;
    
    // HitController
    HitController*  group_one_hit_controller_;
    HitController*  group_two_hit_controller_;
    
    // UI
    HUDNode* hud_;
    UINode* hud_base_;
    UINode* ui_base_;
    UINode* button_base_;
    StartSceneUI* start_scene_ui_;
    DeathScene* death_scene_;
    bool is_net_delay_define_ = false;
    
    // CG
    CameraController* camera_controller_1_;
    CameraController* camera_controller_2_;
    bool is_cg_finished_ = false;
    bool is_set_cg_animation_ = false;
    

    // Font
    Font* font_;
    
    // Logo
    Logo* logo_;
    
    // Cursor
    Cursor* cursor_;
    
    // Game
    bool start_game_ = true;
    bool is_waiting_;
    bool enter_game_;
    
    // Logics
    int process_ = -1;
    int load_state_ = 1;
    float loading_progress_ = 0.0f;
};

void destructClientCore(int signum);

#endif /* ClientCore_hpp */
