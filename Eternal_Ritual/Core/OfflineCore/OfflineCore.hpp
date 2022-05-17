#ifndef OFFLINECORE_HPP
#define OFFLINECORE_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "KGLEngine/Engine.hpp"

#include "Game/Map/MapSystemManager.hpp"
#include "Game/Character/HitController.hpp"
#include "Game/Character/CharNode.hpp"
#include "Game/Magic/BaseMagic.hpp"


class OfflineCore final{
public:
    static OfflineCore* Instance() {
        if (offline_core_ == nullptr) {
            offline_core_ = new OfflineCore();
        }
        return offline_core_;
    }

    static void Destructor() {
        if (offline_core_ != nullptr) {
            delete offline_core_;
            offline_core_ = nullptr;
        }
    }
    
    void initEngine();
    void loadSky();
    void loadLight();
    void loadMap();
    void loadCharacter();
    void loadEnemy();
    void loadMagic();
    void loadDamageSystem();
    
    void handleEvent();
    void updateState();
    void renderWorld();
    
private:
    // Singleton pattern
    static OfflineCore* offline_core_;
    OfflineCore();
    ~OfflineCore();
    
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
    
    // Magic
    std::unordered_map<int, Magic::Type> key_to_magic_;
    std::unordered_map<Magic::Type, int> magic_to_key_;
    std::unordered_set<BaseMagic*> all_magics_;
    
    // Enemy
    std::vector<CharNode*> enemies_;
    
    // HitController
    HitController*  hit_controller_;
};


void destructOfflineCore(int signum);

#endif /* OfflineCore_hpp */
