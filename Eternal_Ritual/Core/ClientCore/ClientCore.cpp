//
//  ClientCore.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Core/ClientCore/ClientCore.hpp"

#include <iostream>
#include <string>

#include "Game/Map/ImportMapHelper.hpp"
#include "Game/Magic/AllMagic.inc"

using namespace glm;
using namespace std;


ClientCore* ClientCore::client_core_ = nullptr;

ClientCore::ClientCore() {
}


ClientCore::~ClientCore() {
    delete client_socket_;
    delete state_pb_;
    delete event_pb_;
    
    map_system_manager_->Destructor();
    hit_controller_->Destructor();
    delete engine_;
}


void ClientCore::initEngine() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 1 - Initial Engine --|" << std::endl;
    
    engine_ = new Engine("KGLEngine", 0.8f, 0, NULL);
    engine_->workingDirectory = "C:/Users/microsoft/Desktop/CSE_125/cse125-sp22-group5";
    engine_->lockCursor();
}


void ClientCore::loadSky() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 2 - Load Sky Box --|" << std::endl;
    
    engine_->skybox = new Skybox("/Resources/Game/Skybox/AR.png", "/Resources/Game/Skybox/AL.png",
                                "/Resources/Game/Skybox/AT.png", "/Resources/Game/Skybox/ABo.png",
                                "/Resources/Game/Skybox/AF.png", "/Resources/Game/Skybox/AB.png",
                                2.0f);
}


void ClientCore::loadLight() {
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


void ClientCore::loadScene() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 4 - Load Scene --|" << std::endl;

    map_system_manager_ = MapSystemManager::Instance();
    
    ImportMapHelper::importMapBox();
//    ImportMapHelper::importMapModel();
}


void ClientCore::loadCharacter() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 5 - Load Character --|" << std::endl;
    
    bool mainChar = true;
    
    for (int i = 0; i < PLAYER_CAPACITY; i++) {
        CharNode* newChar;
        if (mainChar) {
            newChar = new CharNode(vec3(0.0f, -1.0f, 0.0f));
            Node* controlNode = new Node();
            controlNode->position = vec3(0.0f, 1.2f, 0.0f);
            newChar->setControl(controlNode);
        }
        else {
            newChar = pre_chars_[0]->copy(vec3(0.0f, -1.0f, 0.0f));
        }
        newChar->name = "player" + to_string(i);
        
        CameraNode* cameraNode = new CameraNode(60.0f, 0.1f, 1000.0f);
        cameraNode->position = vec3(-2.5f, 0.0f, 0.0f);
        newChar->setCamera(cameraNode);
        if (mainChar) {
            character_ = newChar;
            cameraNode->addChildNode(point_light_);
            engine_->mainCameraNode = cameraNode;
            
            mainChar = false;
        }
        
        newChar->stopAndPlay("idle", 0.0f, 0.0f);;
        
        engine_->addNode(newChar);
        
        UINode* baseNode = new UINode();
        baseNode->renderingOrder = 1000.0f;
        engine_->addNode(baseNode);
        newChar->setUINode(baseNode);
        newChar->setName("player" + to_string(i) + "  " + to_string(newChar->health));
        
        pre_chars_.push_back(newChar);
    }
}

void ClientCore::loadMagic() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 6 - Load Magic --|" << std::endl;
    
    for (int i = 0; i < PLAYER_CAPACITY; i++) {
        DamageableMagic* stoneBlast = new StoneBlast();
        DamageableMagic* fireBall = new ScatteredFire();
        DamageableMagic* lightningSpear = new LightningPhalanx();
        DamageableMagic* groundSmash = new GroundSmash();
        DamageableMagic* thunder = new Thunder();
        DamageableMagic* flame = new Flame();
        DamageableMagic* thousandBlade = new ThousandBlade();
        DamageableMagic* dragon = new DragonMagic(pre_chars_[i]->modelNode);
        
        pre_chars_[i]->addMagics(stoneBlast);
        all_magics_.insert(stoneBlast);
        pre_chars_[i]->addMagics(fireBall);
        all_magics_.insert(fireBall);
        pre_chars_[i]->addMagics(lightningSpear);
        all_magics_.insert(lightningSpear);
        pre_chars_[i]->addMagics(thunder);
        all_magics_.insert(thunder);
        pre_chars_[i]->addMagics(flame);
        all_magics_.insert(flame);
        pre_chars_[i]->addMagics(thousandBlade);
        all_magics_.insert(thousandBlade);
        pre_chars_[i]->addMagics(groundSmash);
        all_magics_.insert(groundSmash);
        pre_chars_[i]->addMagics(dragon);
        all_magics_.insert(dragon);
        
        engine_->addNode(stoneBlast);
        engine_->addNode(flame);
        engine_->addNode(thunder);
    }
}

void ClientCore::loadDamageSystem() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 7 - Load Damage System --|" << std::endl;
    
    hit_controller_ = HitController::Instance();
    
    for (auto& magic : all_magics_) {
        DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
        if (damageableMagic != nullptr) {
            hit_controller_->addMagic(damageableMagic);
        }
    }
    
    for (auto& character : pre_chars_) {
        hit_controller_->addCharacter(character);
    }
}

void ClientCore::loadPbPacket() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 8 - Load ProtoBuf Packet --|" << std::endl;
    
    state_pb_ = new StatePb();
    event_pb_ = new EventPb();
}


void ClientCore::connectServer() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 9 - Connect to Server --|" << std::endl;
    
    client_socket_ = new ClientSocket();
    client_socket_->connectServer();
}


void ClientCore::handleEvent() {
//    std::cout << std::endl;
//    std::cout << "|-- Cycle Stage 1 - Handle Event --|" << std::endl;

    engine_->shouldUpdate();
    
    if (engine_->input->wasKeyReleased(KEY_ESCAPE)) {
        exit(1);
    }
    
    if (engine_->input->wasKeyPressed(KEY_MINUS)) {
        engine_->unlockCursor();
    }
    
    if (engine_->input->wasKeyPressed(KEY_EQUAL)) {
        engine_->lockCursor();
    }
    
    if (start_game_) {
        character_->setName(character_->name);
    }
    else {
        character_->moveCamera(engine_->input->getMouseTranslation() * 0.1f);
        event_pb_->setControlNodeEulerAngles(character_->controlNode->eulerAngles);
        
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
        
        event_pb_->setDirState(gameDataPb::DirState(character_->keyDirection));
        event_pb_->setMoveDirection(character_->moveDirection);
        
        event_pb_->setPlayerStyle(1);
        
        if (engine_->input->wasKeyPressed(KEY_8)) {
            key_to_magic_[KEY_1] = Magic::FIREBALL;
            magic_to_key_[Magic::FIREBALL] = KEY_1;
            key_to_magic_[KEY_2] = Magic::FLAME;
            magic_to_key_[Magic::FLAME] = KEY_2;
            key_to_magic_[KEY_3] = Magic::DRAGON;
            magic_to_key_[Magic::DRAGON] = KEY_3;
            
            event_pb_->setPlayerStyle(2);
        }
        
        if (engine_->input->wasKeyPressed(KEY_9)) {
            key_to_magic_[KEY_1] = Magic::LIGHTNINGSPEAR;
            magic_to_key_[Magic::LIGHTNINGSPEAR] = KEY_1;
            key_to_magic_[KEY_2] = Magic::THUNDER;
            magic_to_key_[Magic::THUNDER] = KEY_2;
            key_to_magic_[KEY_3] = Magic::THOUSANDBLADE;
            magic_to_key_[Magic::THOUSANDBLADE] = KEY_3;
            
            event_pb_->setPlayerStyle(3);
        }
        
        if (engine_->input->wasKeyPressed(KEY_0)) {
            key_to_magic_[KEY_1] = Magic::STONEBLAST;
            magic_to_key_[Magic::STONEBLAST] = KEY_1;
            key_to_magic_[KEY_2] = Magic::GROUNDSMASH;
            magic_to_key_[Magic::GROUNDSMASH] = KEY_2;
            key_to_magic_[KEY_3] = Magic::THOUSANDBLADE;
            magic_to_key_[Magic::THOUSANDBLADE] = KEY_3;
            
            event_pb_->setPlayerStyle(3);
        }
        
        if(engine_->input->wasKeyReleased(KEY_1)) {
            if (key_to_magic_.count(KEY_1)) {
                event_pb_->addMagicEvent(gameDataPb::MagicPb(key_to_magic_[KEY_1]));
            }
        }
        
        if(engine_->input->wasKeyReleased(KEY_2)) {
            if (key_to_magic_.count(KEY_2)) {
                event_pb_->addMagicEvent(gameDataPb::MagicPb(key_to_magic_[KEY_2]));
            }
        }
        
        if(engine_->input->wasKeyReleased(KEY_3)) {
            if (key_to_magic_.count(KEY_3)) {
                event_pb_->addMagicEvent(gameDataPb::MagicPb(key_to_magic_[KEY_3]));
            }
        }
        
        for (auto& it : all_chars_) {
            unsigned long character_ip = it.first;
            CharNode* character = it.second;
            event_pb_->setPlayerHP(character_ip, character->health);
        }
    }
}


void ClientCore::sendData() {
//    std::cout << std::endl;
//    std::cout << "|-- Cycle Stage 2 - Send Data --|" << std::endl;

    char* pbArr = event_pb_->sendData();
    int dataLen = event_pb_->data_len();
    
    client_socket_->sendData(pbArr, dataLen);
    event_pb_->clearData();
}


void ClientCore::receiveData() {
//    std::cout << std::endl;
//    std::cout << "|-- Cycle Stage 3 - Receive Data --|" << std::endl;
    
    char* pbArr;
    int dataLen;
    client_socket_->receiveData(pbArr, dataLen);

    processData(pbArr, dataLen);
}


void ClientCore::processData(char* pbArr, int dataLen) {
    state_pb_->clearData();
    state_pb_->readData(pbArr, dataLen);
}


void ClientCore::updateState() {
//    std::cout << std::endl;
//    std::cout << "|-- Cycle Stage 4 - Update State --|" << std::endl;

    if (start_game_) {
        character_ip_ = this->state_pb_->getPlayerIP();
        all_chars_[character_ip_] = character_;
        
        vector<unsigned long> enemyIPs = state_pb_->getEnemyIPs(this->character_ip_);
        
        for (auto enemyIP : enemyIPs) {
            cout << enemyIP << endl;
        }
        
        for (int i = 1; i < PLAYER_CAPACITY; i++) {
            all_chars_[enemyIPs[i - 1]] = pre_chars_[i];
        }

        start_game_ = false;
    }
    else {
        bool show = false;
        for (auto& it : all_chars_) {
            unsigned long character_ip = it.first;
            CharNode* character = it.second;
            
            character->controlNode->eulerAngles = state_pb_->getControlNodeEulerAngles(character_ip);
            character->keyDirection = Direction::Type(state_pb_->getDirState(character_ip));
            character->moveDirection = state_pb_->getMoveDirection(character_ip);
            character->updatePosition();
            character->updateTransform();
            
            character->health = state_pb_->getPlayerHP(character_ip);
            
            character->setName(character->name + "  " + to_string(character->health));
            
            if (character->health <= 0) {
                // Load the font file:
                FontLibrary* fontLibrary = new FontLibrary();
                Font* title = fontLibrary->loadFontFile("/Resources/Fonts/Cormorant/Cormorant.ttf", 100);
                delete(fontLibrary);
                
                // Create the base node that contains all the UI nodes:
                UINode* baseNode = new UINode();
                baseNode->screenPosition = vec2(0.5f);
                baseNode->renderingOrder = 1000.0f;
                engine_->addNode(baseNode);
                
                
                
                // Create the logo unit node that contains the logo image and a label:
                UINode* logoUnitNode = new UINode();
                baseNode->addChildNode(logoUnitNode);
                
                // Create the logo label node:
                TextNode* logoLabelNode = new TextNode(title, 0.06f, 1.0f, 0.0f);
                logoLabelNode->position = vec2(-0.165f, 0.0f);
                logoLabelNode->color = vec4(1.0f);
                
                
                if (character_ip != character_ip_) {
                    if (!show) {
                        logoLabelNode->text = "Victory !!";
                        show = true;
                    }
                }
                else {
                    if (!show) {
                        logoLabelNode->text = "Defeat !!";
                        show = true;
                    }
                }
                
                logoLabelNode->setLeftHorizontalAlignment();
                logoLabelNode->setTopVerticalAlignment();
                logoUnitNode->addChildNode(logoLabelNode);
                
                SpriteNode* backgroundNode = new SpriteNode(vec2(10.0f));
                backgroundNode->renderingOrder = -10.0f;
                backgroundNode->color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
                baseNode->addChildNode(backgroundNode);
            }
            
            
            if (state_pb_->hasMagicEvents(character_ip)) {
                vector<gameDataPb::MagicPb> magicEvents = state_pb_->getMagicEvents(character_ip);
                for (auto it : magicEvents) {
                    Magic::Type magicEvent = Magic::Type(it);
                    
                    BaseMagic* magic = character->magics[magicEvent];
                    if (magicEvent == Magic::STONEBLAST) {
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::FIREBALL) {
                        if (!magic->start) {
                            magic->removeFromParentNode();
                            character->rightHand->addChildNode(magic);
                            character->castMagic();
                        }
                    }
                    else if (magicEvent == Magic::LIGHTNINGSPEAR) {
                        if (!magic->start) {
                            magic->removeFromParentNode();
                            character->headTop->addChildNode(magic);
                            character->castMagic();
                        }
                    }
                    else if (magicEvent == Magic::THUNDER) {
                        if (!magic->start) {
                            character->castMagic();
                        }
                    }
                    else if (magicEvent == Magic::FLAME) {
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::THOUSANDBLADE) {
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::GROUNDSMASH) {
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::DRAGON) {
                        character->castMagic();
                    }
                }
            }
        }
        
        for (auto& magic : all_magics_) {
            magic->updateMagic();
        }
        
        hit_controller_->checkHit();
    }
}


void ClientCore::renderWorld() {
//    std::cout << std::endl;
//    std::cout << "|-- Cycle Stage 5 - Render World --|" << std::endl;
    
//    engine_->renderDirectionalLightShadowMap(directional_light_);
    
    engine_->render();
}


void ClientCore::closeConnect() {
    std::cout << std::endl;
    std::cout << "|-- Finsh - Close Connect --|" << std::endl;
    
    client_socket_->closeSockets();
}


void destructClientCore(int signum) {
    std::cout << "Game over" << std::endl;
    
    ClientCore::Instance()->closeConnect();
    
    ClientCore::Destructor();
    
    exit(1);
}
