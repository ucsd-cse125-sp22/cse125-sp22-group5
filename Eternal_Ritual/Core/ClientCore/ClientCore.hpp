#ifndef CLIENTCORE_HPP
#define CLIENTCORE_HPP

#include "common.hpp"

#include "statePb.hpp"
#include "eventPb.hpp"
#include "clientSocket.hpp"
#include "../Game/includes.hpp"
#include "../Game/magics.hpp"


class ClientCore {
public:
    static ClientCore* Instance() {
        if (clientCore == nullptr) {
            clientCore = new ClientCore();
        }
        return clientCore;
    }

    static void Destructor() {
        if (clientCore != nullptr) {
            delete clientCore;
            clientCore = nullptr;
        }
    }
    
    void initEngine();
    void loadSky();
    void loadLight();
    void loadScene();
    void loadCharacter();
    void loadWeapon();
    
    void initPbPacket();
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
    static ClientCore* clientCore;
    ClientCore();
    ~ClientCore();
    
    // Socket
    ClientSocket* clientSocket;
    ulonglong clientCycle;
    
    // Pb
    EventPb* eventPb;
    StatePb* statePb;
    
    // Engine
    Engine* engine;
    
    // Sky
    Skybox* skybox;
    
    // Light
    LightNode* pointLight;
    LightNode* ambientLight;
    LightNode* directionalLight;
    LightNode* spotLight;
    
    // Texture
    Texture* reflection;
    Texture* mixamoD;
    Texture* mixamoN;
    Texture* mixamoM;
    
    // Shader
    PBRShader* mapShader;
    PBRShader* mixamoMaterial;
    
    // Scene
    Node* sceneNode;
    MapSystemManager* mapSystemManager;
    
    // Character
    CharNode* character;
    ulong characterIP;
    
    // Magic
    unordered_map<int, Magic> keyToMagic;
    unordered_map<Magic, int> magicToKey;
    unordered_set<BaseMagic*> allMagics;
    
    // Weapon
    Node* weaponNode;
    unordered_map<ulong, Node*> enemyWeapons;
    
    // Enemy
    unordered_map<ulong, CharNode*> enemies;
    vector<ulong> enemyIPs;
    
    // Game
    bool startGame = true;
};



#endif /* clientCore_hpp */
