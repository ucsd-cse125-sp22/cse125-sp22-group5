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

#ifdef _WIN64
#define ROOT_PATH "D:/StudyProject/cse125-sp22-group5"
#elif __APPLE__
#define ROOT_PATH "."
#endif

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
    delete group_one_hit_controller_;
    delete group_two_hit_controller_;
    delete engine_;
}


void ClientCore::initEngine() {
    std::cout << std::endl;
    std::cout << "|-- Initial Stage 1 - Initial Engine --|" << std::endl;
    
    engine_ = new Engine("Eternal Ritual", 0.8f, 0, NULL);
    engine_->workingDirectory = ROOT_PATH;
    engine_->lockCursor();
}


void ClientCore::loadFont() {
    std::cout << std::endl;
    std::cout << "|-- Pre-Loading Stage 1 - Load Font --|" << std::endl;
    
    FontLibrary* fontLibrary = new FontLibrary();
    font_ = fontLibrary->loadFontFile("/Resources/Fonts/Cinzel/Cinzel.ttf", 50);
}


void ClientCore::displayLogo() {
    std::cout << std::endl;
    std::cout << "|-- Pre-Loading Stage 2 - Display logo --|" << std::endl;
    
    ui_base_ = new UINode();
    ui_base_->renderingOrder = 10000.0f;
    ui_base_->size = glm::vec2(1.0f);
    ui_camera_ = new CameraNode(60.0f, 0.1f, 1000.0f);
    ui_camera_->position = glm::vec3(-7.95262, 49.7237, 41.5025);
    ui_camera_->eulerAngles = glm::vec3(0, 91.6, -47.1);
    engine_->addNode(ui_camera_);
    engine_->mainCameraNode = ui_camera_;
    logo_ = new Logo(engine_,font_, ui_base_, &process_);
}
void ClientCore::playLogo() {
    logo_->play();
}


void ClientCore::updateLoad() {
    logo_->updateLoad(loading_progress_);
}


void ClientCore::loadSky() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 1 - Load Sky Box --|" << std::endl;
    
    this->engine_->skybox = new Skybox("/Resources/Game/Skybox/NML.png", "/Resources/Game/Skybox/NMR.png",
                                "/Resources/Game/Skybox/NMU.png", "/Resources/Game/Skybox/NMD.png",
                                "/Resources/Game/Skybox/NMF.png", "/Resources/Game/Skybox/NMB.png",
                                2.0f);
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.1;
}


void ClientCore::loadLight() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 2 - Load Lights --|" << std::endl;
    
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
    directional_light_->shadowBitMask = 0xfffffffe;
    engine_->addNode(directional_light_);
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.1;
}


void ClientCore::loadMap() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 3 - Load Map --|" << std::endl;

    map_system_manager_ = MapSystemManager::Instance();
    
    ImportMapHelper::importMapBox();
    ImportMapHelper::importMapModel();
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.2;
}


void ClientCore::loadCharacter() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 4 - Load Character --|" << std::endl;
    
    for (int i = 0; i < 4; i++) {
        CharNode* newChar;
        if (i == 0) {
            newChar = new CharNode(vec3(0));
            Node* controlNode = new Node();
            controlNode->position = vec3(0.0f, 1.2f, 0.0f);
            newChar->setControl(controlNode);
        }
        else {
            newChar = pre_chars_[0]->copy(vec3(0));
        }
        
        if (i == 3) {
            newChar->health = 0;
            newChar->mana = 0;
            newChar->manaRegen = 0;
        }
        
        newChar->isDisabled = true;
        newChar->uninjurable = true;
        
        CameraNode* cameraNode = new CameraNode(60.0f, 0.1f, 1000.0f);
        cameraNode->position = vec3(-2.5f, 0.0f, 0.0f);
        newChar->setCamera(cameraNode);
        
        engine_->addNode(newChar);
        
        UINode* baseNode = new UINode();
        baseNode->renderingOrder = 1000.0f;
        engine_->addNode(baseNode);
        newChar->setUINode(baseNode);
        
        pre_chars_.push_back(newChar);
    }
    
    enemies_[pre_chars_[0]].push_back(pre_chars_[1]);
    enemies_[pre_chars_[0]].push_back(pre_chars_[3]);
    enemies_[pre_chars_[1]].push_back(pre_chars_[0]);
    enemies_[pre_chars_[1]].push_back(pre_chars_[2]);
    enemies_[pre_chars_[2]].push_back(pre_chars_[1]);
    enemies_[pre_chars_[2]].push_back(pre_chars_[3]);
    enemies_[pre_chars_[3]].push_back(pre_chars_[0]);
    enemies_[pre_chars_[3]].push_back(pre_chars_[2]);
    
    if (PLAYER_CAPACITY >= 1) {
        if (PLAYER_CAPACITY == 1 || PLAYER_CAPACITY == 2) {
            pre_chars_[0]->setCharacterPosition(vec3(-46.0f, -1.0f, -1.4f));
            pre_chars_[0]->setCharacterEularAngle(vec3(0.0f, 85.5f, 0.0f));
            pre_chars_[0]->setCameraEularAngle(vec3(0.0f, -4.5f, -18.0f));
        }
        else if (PLAYER_CAPACITY == 3 || PLAYER_CAPACITY == 4) {
            pre_chars_[0]->setCharacterPosition(vec3(-46.0f, -1.0f, 1.9f));
            pre_chars_[0]->setCharacterEularAngle(vec3(0.0f, 85.5f, 0.0f));
            pre_chars_[0]->setCameraEularAngle(vec3(0.0f, -4.5f, -18.0f));
        }
        pre_chars_[0]->name = "Kelin";
        pre_chars_[0]->isDisabled = false;
        pre_chars_[0]->uninjurable = false;
    }
    if (PLAYER_CAPACITY >= 2) {
        if (PLAYER_CAPACITY == 2 || PLAYER_CAPACITY == 3) {
            pre_chars_[1]->setCharacterPosition(vec3(28.5f, -1.0f, -0.88f));
            pre_chars_[1]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
            pre_chars_[1]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        }
        else if (PLAYER_CAPACITY == 4) {
            pre_chars_[1]->setCharacterPosition(vec3(28.5f, -1.0f, -4.22f));
            pre_chars_[1]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
            pre_chars_[1]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        }
        pre_chars_[1]->name = "Zifan";
        pre_chars_[1]->isDisabled = false;
        pre_chars_[1]->uninjurable = false;
    }
    if (PLAYER_CAPACITY >= 3) {
        if (PLAYER_CAPACITY == 3 || PLAYER_CAPACITY == 4) {
            pre_chars_[2]->setCharacterPosition(vec3(-46.0f, -1.0f, -4.0f));
            pre_chars_[2]->setCharacterEularAngle(vec3(0.0f, 85.5f, 0.0f));
            pre_chars_[2]->setCameraEularAngle(vec3(0.0f, -4.5f, -18.0f));
        }
        pre_chars_[2]->name = "Kangming";
        pre_chars_[2]->isDisabled = false;
        pre_chars_[2]->uninjurable = false;
    }
    if (PLAYER_CAPACITY >= 4) {
        pre_chars_[3]->health = MAXHP;
        pre_chars_[3]->mana = MAXMANA;
        pre_chars_[3]->manaRegen = MAXMANAREGEN;
        pre_chars_[3]->setCharacterPosition(vec3(28.5f, -1.0f, 2.46f));
        pre_chars_[3]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
        pre_chars_[3]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        pre_chars_[3]->name = "Mengxuan";
        pre_chars_[3]->isDisabled = false;
        pre_chars_[3]->uninjurable = false;
    }
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.2;
}


void ClientCore::loadMagic() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 5 - Load Magic --|" << std::endl;
    
    for (int i = 0; i < 4; i++) {
        DamageableMagic* storm = new Storm();
        DamageableMagic* fireBall = new ScatteredFire();
        DamageableMagic* thunder = new Thunder();
        DamageableMagic* dragon = new DragonMagic(pre_chars_[i]->modelNode);
        
        pre_chars_[i]->addMagics(fireBall);
        all_magics_.insert(fireBall);
        pre_chars_[i]->addMagics(storm);
        all_magics_.insert(storm);
        pre_chars_[i]->addMagics(thunder);
        all_magics_.insert(thunder);
        pre_chars_[i]->addMagics(dragon);
        all_magics_.insert(dragon);
        
        engine_->addNode(thunder);
    }
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.2;
}


void ClientCore::loadDamageSystem() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 6 - Load Damage System --|" << std::endl;
    
    group_one_hit_controller_ = new HitController();
    group_two_hit_controller_ = new HitController();
    
    if (PLAYER_CAPACITY >= 1) {
        for (auto& magic : pre_chars_[0]->magics) {
            DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
            if (damageableMagic != nullptr) {
                group_two_hit_controller_->addMagic(damageableMagic);
            }
        }
        group_one_hit_controller_->addCharacter(pre_chars_[0]);
    }
    
    if (PLAYER_CAPACITY >= 2) {
        for (auto& magic : pre_chars_[1]->magics) {
            DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
            if (damageableMagic != nullptr) {
                group_one_hit_controller_->addMagic(damageableMagic);
            }
        }
        group_two_hit_controller_->addCharacter(pre_chars_[1]);
    }
    
    if (PLAYER_CAPACITY >= 3) {
        for (auto& magic : pre_chars_[2]->magics) {
            DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
            if (damageableMagic != nullptr) {
                group_two_hit_controller_->addMagic(damageableMagic);
            }
        }
        group_one_hit_controller_->addCharacter(pre_chars_[2]);
    }
    
    if (PLAYER_CAPACITY >= 4) {
        for (auto& magic : pre_chars_[3]->magics) {
            DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
            if (damageableMagic != nullptr) {
                group_one_hit_controller_->addMagic(damageableMagic);
            }
        }
        group_two_hit_controller_->addCharacter(pre_chars_[3]);
    }
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.1;
}


void ClientCore::loadStartScene() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 7 - Load Start Scene --|" << std::endl;
    
    cursor_ = new Cursor(engine_);
    button_base_ = new UINode();
    button_base_->size = glm::vec2(1.0);
    button_base_->screenPosition = glm::vec2(0.5);
    start_scene_ui_ = new StartSceneUI(engine_, font_, ui_base_, button_base_);
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.05;
}


void ClientCore::loadDeathScene() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 8 - Load Death Scene --|" << std::endl;
    
    death_scene_ = new DeathScene(engine_);

    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.05;
}


void ClientCore::displayStart() {
    std::cout << std::endl;
    std::cout << "|-- Pre-Game Stage 1 - Display Start Scene --|" << std::endl;
    
    enter_game_ = true;
    is_waiting_ = true;
    cursor_->isDisable(false);
    start_scene_ui_->isDisbled(false);
    Animation* startDelay = new Animation("startDelay",0.9);
    startDelay->setCompletionHandler([&] {
        Animation* showStart = new Animation("showStart", 1);
        showStart->setEaseInTimingMode();
        showStart->setFloatAnimation(&(button_base_->alpha), 1.0);
        engine_->playAnimation(showStart);
    });
    engine_->playAnimation(startDelay);
    
    process_ = 5;
}


void ClientCore::updateStart() {
    int state = start_scene_ui_->update(is_waiting_);
    if (state == 1) {
        process_ = 6;
        Animation* uiBaseExit = new Animation("uiBaseExit", 0.3f);
        uiBaseExit->setFloatAnimation(&ui_base_->alpha, 0.0f);
        uiBaseExit->setCompletionHandler([&] {ui_base_->isDisabled = true;});
        engine_->playAnimation(uiBaseExit);
    }
    if (state == 4) {
        cursor_->isDisable(true);
    }
    if (state == 5 && !is_net_delay_define_) {
        Animation* netDelay = new Animation("netDelay", 0.3f);
        is_net_delay_define_ = true;
        netDelay->setCompletionHandler([&] {
            loadPbPacket();
            connectServer();
            handleEvent();
            sendData();
            receiveData();
            updateState();
            CameraController::BezierCurve bezierCurve;
            bezierCurve.controll_points.push_back(vec3(-7.95262, 49.7237, 41.5025));
            bezierCurve.controll_points.push_back(vec3(48.43, 47.37, 55.37));
            bezierCurve.controll_points.push_back(vec3(57.97, 39.19, 2.22));
            bezierCurve.controll_points.push_back(vec3(30.45, 28.39, -2.33));
            bezierCurve.level_of_detail = 500;

            CameraController::EularChangeInfo eularChangeInfo;
            eularChangeInfo.is_clockwise = false;
            eularChangeInfo.start_angle = vec3(0.0f, 91.6, -47.1);
            eularChangeInfo.end_angle = vec3(0.0f, 179.3, -3.7);
            
            camera_controller_ = new CameraController(engine_->mainCameraNode, bezierCurve, eularChangeInfo, 0.1, 5.0);
            
            is_waiting_ = false;
        });
        engine_->playAnimation(netDelay);
    }
    
    cursor_->update();
}


void ClientCore::playCG() {
//    camera_controller_->moveCamera();
    hud_base_->isDisabled = false;
    char_camera_ = character_->cameraNode;
    engine_->mainCameraNode = char_camera_;
    enter_game_ = false;
    
    process_ = 7;
}


void ClientCore::loadHUD() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 8 - Load HUD --|" << std::endl;
    hud_base_ = new UINode();
    hud_base_->renderingOrder = 10000.0f;
    engine_->addNode(hud_base_);
    hud_ = new HUDNode(engine_, hud_base_, true, font_, character_, ally_);
    hud_base_->isDisabled = true;
}


void ClientCore::loadPbPacket() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 10 - Load ProtoBuf Packet --|" << std::endl;
    
    state_pb_ = new StatePb();
    event_pb_ = new EventPb();
}


void ClientCore::connectServer() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 11 - Connect to Server --|" << std::endl;
    
    client_socket_ = new ClientSocket();
    client_socket_->connectServer();
}


void ClientCore::handleEvent() {
    std::cout << std::endl;
    std::cout << "|-- Cycle Stage 1 - Handle Event --|" << std::endl;
    
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
        key_to_magic_[KEY_1] = Magic::FIREBALL;
        magic_to_key_[Magic::FIREBALL] = KEY_1;
        key_to_magic_[KEY_2] = Magic::STORM;
        magic_to_key_[Magic::STORM] = KEY_2;
        key_to_magic_[KEY_3] = Magic::THUNDER;
        magic_to_key_[Magic::THUNDER] = KEY_3;
        key_to_magic_[KEY_4] = Magic::DRAGON;
        magic_to_key_[Magic::DRAGON] = KEY_4;
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
        event_pb_->setCharStatePb(gameDataPb::CharStatePb(character_->state));
        

        if(engine_->input->wasKeyReleased(KEY_SPACE)){
            event_pb_->setRoll(true);
        }
        else {
            event_pb_->setRoll(false);
        }
        
        if(engine_->input->wasKeyReleased(KEY_G)){
            event_pb_->setToggleLock(true);
        }
        else {
            event_pb_->setToggleLock(false);
        }
        
        if(engine_->input->wasKeyReleased(KEY_C)){
            if (character_->health <= 0) {
                for (int i = 1; i < 4; i++) {
                    CharNode* currChar = pre_chars_[(char_camera_index_ + i) % 4];
                    if(!currChar->isDisabled) {
                        hud_->toggleViewDead(currChar);
                        engine_->mainCameraNode = currChar->cameraNode;
                        main_camera_ = false;
                        break;
                    }
                }
            }
            else {
                if (!ally_->isDisabled) {
                    if (main_camera_) {
                        engine_->mainCameraNode = ally_->cameraNode;
                        char_camera_index_ = ally_index_;
                    }
                    else {
                        engine_->mainCameraNode = character_->cameraNode;
                        char_camera_index_ = character_index_;
                    }
                    main_camera_ = !main_camera_;
                }
            }
        }
        
        if(engine_->input->wasKeyReleased(KEY_1)) {
            character_->setCurrMagic(key_to_magic_[KEY_1]);
        }
        
        if(engine_->input->wasKeyReleased(KEY_2)) {
            character_->setCurrMagic(key_to_magic_[KEY_2]);
        }
        
        if(engine_->input->wasKeyReleased(KEY_3)) {
            character_->setCurrMagic(key_to_magic_[KEY_3]);
        }
        if (engine_->input->wasKeyPressed(KEY_4)) {
            character_->setCurrMagic(key_to_magic_[KEY_4]);
        }
        
        character_->scrollMagic(engine_->input->getScrollWheelAcceleration());
        
        if (engine_->input->wasKeyPressed(MOUSE_BUTTON_LEFT)) {
            event_pb_->addMagicEvent(gameDataPb::MagicPb(character_->currMagic));
        }
        
        for (auto& it : all_chars_) {
            unsigned long character_ip = it.first;
            CharNode* character = it.second;
            event_pb_->setPlayerHP(character_ip, character->health);
            event_pb_->setPlayerMP(character_ip, character->mana);
        }
    }
}


void ClientCore::sendData() {
    std::cout << std::endl;
    std::cout << "|-- Cycle Stage 2 - Send Data --|" << std::endl;

    char* pbArr = event_pb_->sendData();
    int dataLen = event_pb_->data_len();
    
    client_socket_->sendData(pbArr, dataLen);
    event_pb_->clearData();
}


void ClientCore::receiveData() {
    std::cout << std::endl;
    std::cout << "|-- Cycle Stage 3 - Receive Data --|" << std::endl;
    
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
    std::cout << std::endl;
    std::cout << "|-- Cycle Stage 4 - Update State --|" << std::endl;

    if (start_game_) {
        character_ip_ = state_pb_->getPlayerIP();
        int mainGroupNum = state_pb_->getPlayerGroup(character_ip_);
        character_index_ = mainGroupNum;
        char_camera_index_ = character_index_;
        character_ = pre_chars_[character_index_];
        all_chars_[character_ip_] = character_;
        character_->cameraNode->addChildNode(point_light_);
        
        vector<unsigned long> enemyIPs = state_pb_->getEnemyIPs(character_ip_);
        
        ally_ = pre_chars_[3];
        for (int i = 0; i < PLAYER_CAPACITY - 1; i++) {
            unsigned long currPlayerIP = enemyIPs[i];
            int groupNum = state_pb_->getPlayerGroup(currPlayerIP);
            all_chars_[currPlayerIP] = pre_chars_[groupNum];
            if (groupNum % 2 == mainGroupNum % 2) {
                ally_index_ = groupNum;
                ally_ = pre_chars_[ally_index_];
            }
        }
        
        loadHUD();

        start_game_ = false;
    }
    else {
        for (auto& it : all_chars_) {
            unsigned long character_ip = it.first;
            CharNode* character = it.second;
            
            character->controlNode->eulerAngles = state_pb_->getControlNodeEulerAngles(character_ip);
            character->keyDirection = Direction::Type(state_pb_->getDirState(character_ip));
            character->moveDirection = state_pb_->getMoveDirection(character_ip);
            character->state = CharState::Type(state_pb_->getCharStatePb(character_ip));
            character->updatePosition();
            character->updateTransform();
            
            character->health = state_pb_->getPlayerHP(character_ip);
            character->mana = state_pb_->getPlayerMP(character_ip);
            
            if (state_pb_->getRoll(character_ip)) {
                character->roll();
            }
            
            if (state_pb_->getToggleLock(character_ip)) {
                character->toggleLock(enemies_[character]);
            }
            
            if (state_pb_->hasMagicEvents(character_ip)) {
                vector<gameDataPb::MagicPb> magicEvents = state_pb_->getMagicEvents(character_ip);
                for (auto it : magicEvents) {
                    Magic::Type magicEvent = Magic::Type(it);
                    
                    if (magicEvent == Magic::STORM) {
                        character->currMagic = Magic::STORM;
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::FIREBALL) {
                        character->currMagic = Magic::FIREBALL;
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::THUNDER) {
                        character->currMagic = Magic::THUNDER;
                        character->castMagic();
                    }
                    else if (magicEvent == Magic::DRAGON) {
                        character->currMagic = Magic::DRAGON;
                        character->castMagic();
                    }
                }
            }
        }
        
        for (auto& magic : all_magics_) {
            magic->updateMagic();
        }
        
        group_one_hit_controller_->checkHit();
        group_two_hit_controller_->checkHit();
        
        for (auto& it : all_chars_) {
            it.second->genMana();
        }
        
        hud_->update(!main_camera_);
        
        if (pre_chars_[0]->health <= 0 && pre_chars_[2]->health <= 0) {
            if (character_index_ == 0 || character_index_ == 2) {
                death_scene_->display(false, &process_);
            }
            else {
                death_scene_->display(true, &process_);
            }
            Animation* delay = new Animation("resetdelay", 1.5);
            engine_->playAnimation(delay);
            process_ = 9;
        }
        
        if (pre_chars_[1]->health <= 0 && pre_chars_[3]->health <= 0) {
            if (character_index_ == 1 || character_index_ == 3) {
                death_scene_->display(false, &process_);
            }
            else {
                death_scene_->display(true, &process_);
            }
            Animation* delay = new Animation("resetdelay", 1.5);
            engine_->playAnimation(delay);
            process_ = 9;
        }
    }
}


void ClientCore::renderWorld() {
    std::cout << std::endl;
    std::cout << "|-- Cycle Stage 5 - Render World --|" << std::endl;
    
    engine_->renderDirectionalLightShadowMap(directional_light_);
    
//    cout << "position: " << character_->modelNode->getWorldPosition().x << " " << character_->modelNode->getWorldPosition().y << " " << character_->modelNode->getWorldPosition().z << endl;
//
//    cout << "Angle: " << character_->modelNode->getWorldEulerAngles().x << " " << character_->modelNode->getWorldEulerAngles().y << " " << character_->modelNode->getWorldEulerAngles().z << endl;
    
    engine_->render();
}


void ClientCore::resetGame() {
    engine_->mainCameraNode = ui_camera_;
}


void ClientCore::closeConnect() {
    std::cout << std::endl;
    std::cout << "|-- Finsh - Close Connect --|" << std::endl;
    
    client_socket_->closeSockets();
}


int ClientCore::process() {
    return process_;
}

void ClientCore::set_process(int process) {
    process_ = process;
}


int ClientCore::load_state() {
    return load_state_;
}


void destructClientCore(int signum) {
    std::cout << "Game over" << std::endl;
    
    ClientCore::Instance()->closeConnect();
    
    ClientCore::Destructor();
    
    exit(1);
}
