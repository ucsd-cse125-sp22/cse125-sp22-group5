//
//  OfflineCore.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Core/OfflineCore/OfflineCore.hpp"

#include <iostream>

#include "Game/Map/ImportMapHelper.hpp"
#include "Game/Magic/AllMagic.inc"

using namespace glm;
using namespace std;


OfflineCore* OfflineCore::offline_core_ = nullptr;

OfflineCore::OfflineCore() {
}


OfflineCore::~OfflineCore() {
    map_system_manager_->Destructor();
    hit_controller_->Destructor();
    delete engine_;
}


void OfflineCore::initEngine() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 1 - Initial Engine --|" << std::endl;
    
    engine_ = new Engine("KGLEngine", 0.5f, 0, NULL);
    engine_->workingDirectory = ".";
    engine_->lockCursor();
}


void OfflineCore::loadSky() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 2 - Load Sky Box --|" << std::endl;
    
    this->engine_->skybox = new Skybox("/Resources/Game/Skybox/AR.png", "/Resources/Game/Skybox/AL.png",
                                "/Resources/Game/Skybox/AT.png", "/Resources/Game/Skybox/ABo.png",
                                "/Resources/Game/Skybox/AF.png", "/Resources/Game/Skybox/AB.png",
                                2.0f);
}


void OfflineCore::loadLight() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 3 - Load Lights --|" << std::endl;
    
    point_light_ = new LightNode(vec3(5.0f));
    point_light_->setPointLight(2.0f, 20.0f);
    point_light_->highlightIntensity = 0.0f;
    
    ambient_light_ = new LightNode(vec3(0.5f));
    ambient_light_->setAmbientLight();
    engine_->addNode(ambient_light_);
    
    directional_light_ = new LightNode(vec3(1.0f, 1.0f, 1.0f));
    directional_light_->setDirectionalLight();
    directional_light_->eulerAngles = vec3(0.0f, 135.0f, -45.0f);
    directional_light_->activateDirectionalLightShadow(4096, 100.0f, 0.1f, 200.0f, -100.0f, 0.002f, 1);
    engine_->addNode(directional_light_);
    
}


void OfflineCore::loadMap() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 4 - Load Scene --|" << std::endl;

    map_system_manager_ = MapSystemManager::Instance();
    
    ImportMapHelper::importMapBox();
//    ImportMapHelper::importMapModel();
}


void OfflineCore::loadCharacter() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 5 - Load Character --|" << std::endl;
    
    character_ = new CharNode(vec3(0.0f, -1.0f, 0.0f));
    character_->name = "main character";
    
    Node* controlNode = new Node();
    controlNode->position = vec3(0.0f, 1.2f, 0.0f);
    character_->setControl(controlNode);
    
    CameraNode* cameraNode = new CameraNode(60.0f, 0.1f, 1000.0f);
    cameraNode->position = vec3(-2.5f, 0.0f, 0.0f);
    cameraNode->addChildNode(point_light_);
    character_->setCamera(cameraNode);
    engine_->mainCameraNode = cameraNode;
    
    character_->stopAndPlay("idle", 0.0f, 0.0f);;
    
    engine_->addNode(character_);
    
    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine_->addNode(baseNode);
    character_->setUINode(baseNode);
    character_->setName("Player1");
}


void OfflineCore::loadEnemy() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 6 - Load Enemy --|" << std::endl;
    
    CharNode* enemy = character_->copy(vec3(2.0, -1.0f, 2.0f));
    enemy->name = "enemy1";
    enemy->setEularAngle(vec3(0,90.0f,0));
    
    enemy->stopAndPlay("idle", 0.0f, 0.0f);
    engine_->addNode(enemy);
    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine_->addNode(baseNode);
    enemy->setUINode(baseNode);
    enemy->setName("Enemy");
    
    enemies_.push_back(enemy);
}


void OfflineCore::loadMagic() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 7 - Load Magic --|" << std::endl;
    int magicIndex = 0;
    
    DamageableMagic* stoneBlast = new StoneBlast();
    DamageableMagic* fireBall = new ScatteredFire();
    DamageableMagic* thunder = new Thunder();
    DamageableMagic* dragon = new DragonMagic(character_->modelNode);
    
    key_to_magic_[KEY_1] = magicIndex;
    magic_to_key_[magicIndex] = KEY_1;
    character_->addMagics(fireBall);
    magicIndex++;
    all_magics_.insert(fireBall);
    key_to_magic_[KEY_2] = magicIndex;
    magic_to_key_[magicIndex] = KEY_2;
    character_->addMagics(stoneBlast);
    magicIndex++;
    all_magics_.insert(stoneBlast);
    key_to_magic_[KEY_3] = magicIndex;
    magic_to_key_[magicIndex] = KEY_3;
    character_->addMagics(thunder);
    magicIndex++;
    all_magics_.insert(thunder);
    key_to_magic_[KEY_4] = magicIndex;
    magic_to_key_[magicIndex] = KEY_4;
    character_->addMagics(dragon);
    magicIndex++;
    all_magics_.insert(dragon);
    
    engine_->addNode(thunder);
}


void OfflineCore::loadDamageSystem() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 8 - Load Damage System --|" << std::endl;
    
    hit_controller_ = HitController::Instance();
    
    for (auto& magic : all_magics_) {
        DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
        if (damageableMagic != nullptr) {
            hit_controller_->addMagic(damageableMagic);
        }
    }
    
    for (auto& enemy : enemies_) {
        hit_controller_->addCharacter(enemy);
    }
}


void OfflineCore::handleEvent() {
    if(engine_->input->wasKeyReleased(KEY_ESCAPE)) {
        engine_->terminate();
    }
    
    if(engine_->input->isPressingKey(KEY_W)) {
        character_->moveFront();
    }else if(engine_->input->isPressingKey(KEY_S)) {
        character_->moveBack();
    }
    if(engine_->input->isPressingKey(KEY_A)) {
        character_->moveLeft();
    }else if(engine_->input->isPressingKey(KEY_D)) {
        character_->moveRight();
    }
    if(engine_->input->wasKeyReleased(KEY_SPACE)){
        character_->roll();
    }
    
    if(engine_->input->wasKeyReleased(KEY_G)){
        character_->toggleLock(enemies_);
    }
    
    if(engine_->input->wasKeyReleased(KEY_Q)){
        enemies_[0]->characterTargetEulerAngles += vec3(0, 90, 0);
    }
    
    if(engine_->input->wasKeyReleased(KEY_1)){
        character_->setCurrMagic(key_to_magic_[KEY_1]);
    }
    if(engine_->input->wasKeyReleased(KEY_2)){
        character_->setCurrMagic(key_to_magic_[KEY_2]);
    }
    if (engine_->input->wasKeyPressed(KEY_3)) {
        character_->setCurrMagic(key_to_magic_[KEY_3]);
    }
    if (engine_->input->wasKeyPressed(KEY_4)) {
        character_->setCurrMagic(key_to_magic_[KEY_4]);
    }
    if (engine_->input->wasKeyPressed(MOUSE_BUTTON_LEFT)) {
        character_->castMagic();
    }
    character_->scrollMagic(engine_->input->getScrollWheelAcceleration());
}


void OfflineCore::updateState() {
    character_->moveCamera(engine_->input->getMouseTranslation() * 0.1f);
    character_->updatePosition();
    character_->updateTransform();

    for (int i = 0; i < enemies_.size(); i++){
        enemies_[i]->updatePosition();
        enemies_[i]->updateTransform();
    }
    
    
    for (auto& magic : all_magics_) {
        magic->updateMagic();
    }

    hit_controller_->checkHit();
    character_->genMana();
}


void OfflineCore::renderWorld() {
    engine_->renderDirectionalLightShadowMap(directional_light_);
    
    engine_->render();
}



void destructOfflineCore(int signum) {
    std::cout << "Game over" << std::endl;
    
    OfflineCore::Destructor();
    
    exit(1);
}