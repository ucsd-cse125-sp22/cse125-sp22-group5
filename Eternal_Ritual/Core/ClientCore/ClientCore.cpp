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
#define ROOT_PATH "C:/Users/mel001/cse125-sp22-group5"
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
    
    engine_ = new Engine("Eternal Ritual", 1.0f, 0, NULL);
    engine_->workingDirectory = ROOT_PATH;
    engine_->lockCursor();
}


void ClientCore::loadFont() {
    std::cout << std::endl;
    std::cout << "|-- Pre-Loading Stage 1 - Load Font --|" << std::endl;
    
    FontLibrary* fontLibrary = new FontLibrary();
    font_ = fontLibrary->loadFontFile("/Resources/Fonts/Cinzel/Cinzel.ttf", 50);
    fontSmall_ = fontLibrary->loadFontFile("/Resources/Fonts/GentiumPlus-Regular.ttf", 50);
}


void ClientCore::displayLogo() {
    std::cout << std::endl;
    std::cout << "|-- Pre-Loading Stage 2 - Display logo --|" << std::endl;
    
    ui_base_ = new UINode();
    ui_base_->renderingOrder = 10000.0f;
    ui_base_->size = glm::vec2(1.0f);
    ui_camera_ = new CameraNode(60.0f, 0.1f, 1000.0f);
    ui_camera_->position = glm::vec3(-12.3641, 14.8889, 36.8971);
    ui_camera_->eulerAngles = glm::vec3(0.0, 87.9956, -18.941);
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
    
    map_system_manager_ = MapSystemManager::Instance();
    
    ImportMapHelper::importMapBox(cg_used_box_);
    
    ImportMapHelper::importMapModel1();
}


void ClientCore::loadLight() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 2 - Load Lights --|" << std::endl;
    point_light_ = new LightNode(vec3(1));
    point_light_->setPointLight(2.0f, 20.0f);
    point_light_->highlightIntensity = 0.0f;
    
    ambient_light_ = new LightNode(vec3(0));
    ambient_light_->setAmbientLight();
   // engine_->addNode(ambient_light_);
    
    directional_light_ = new LightNode(vec3(1.5, 2.5, 5));
    directional_light_->setDirectionalLight();
    directional_light_->eulerAngles = vec3(0.0f, 95.0f, -25.0f);
    directional_light_->activateDirectionalLightShadow(4096, 100.0f, 0.1f, 200.0f, -100.0f, 0.002f, 1);
    directional_light_->shadowBitMask = 0xfffffffe;
    engine_->addNode(directional_light_);
    
    ImportMapHelper::importMapModel2();
    
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.1;
}


void ClientCore::loadMap() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 3 - Load Map --|" << std::endl;

    ImportMapHelper::importMapModel3(cg_used_node_);
        
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
//            pre_chars_[0]->setCharacterPosition(vec3(-46.40f, 23.07f, -1.4f));
            pre_chars_[0]->setCharacterPosition(vec3(-46.40f, 23.07f, 0.60f));
            pre_chars_[0]->setCharacterEularAngle(vec3(0.0f, 85.5f, 0.0f));
//            pre_chars_[0]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
            pre_chars_[0]->setCameraEularAngle(vec3(0.0f, -4.5f, -18.0f));
//            pre_chars_[0]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        }
        else if (PLAYER_CAPACITY == 3 || PLAYER_CAPACITY == 4) {
            pre_chars_[0]->setCharacterPosition(vec3(-46.40f, 23.07f, 0.60f));
            pre_chars_[0]->setCharacterEularAngle(vec3(0.0f, 85.5f, 0.0f));
            pre_chars_[0]->setCameraEularAngle(vec3(0.0f, -4.5f, -18.0f));
        }
        pre_chars_[0]->name = "Kelin";
        pre_chars_[0]->isDisabled = false;
        pre_chars_[0]->uninjurable = false;
    }
    if (PLAYER_CAPACITY >= 2) {
        if (PLAYER_CAPACITY == 2 || PLAYER_CAPACITY == 3) {
//            pre_chars_[1]->setCharacterPosition(vec3(28.36f, 23.07f, -0.88f));
            pre_chars_[1]->setCharacterPosition(vec3(28.36f, 23.07f, -2.63f));
            pre_chars_[1]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
            pre_chars_[1]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        }
        else if (PLAYER_CAPACITY == 4) {
            pre_chars_[1]->setCharacterPosition(vec3(28.36f, 23.07f, -2.63f));
            pre_chars_[1]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
            pre_chars_[1]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        }
        pre_chars_[1]->name = "Zifan";
        pre_chars_[1]->isDisabled = false;
        pre_chars_[1]->uninjurable = false;
    }
    if (PLAYER_CAPACITY >= 3) {
        if (PLAYER_CAPACITY == 3 || PLAYER_CAPACITY == 4) {
            pre_chars_[2]->setCharacterPosition(vec3(-46.40f, 23.07f, -2.76f));
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
        pre_chars_[3]->setCharacterPosition(vec3(28.36f, 23.07f, 0.49f));
        pre_chars_[3]->setCharacterEularAngle(vec3(0.0f, -92.6f, 0.0f));
        pre_chars_[3]->setCameraEularAngle(vec3(0.0f, 177.4f, -18.0f));
        pre_chars_[3]->name = "Mengxuan";
        pre_chars_[3]->isDisabled = false;
        pre_chars_[3]->uninjurable = false;
    }
    pre_chars_[3]->setTeamWhite();
    pre_chars_[1]->setTeamWhite();
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
    start_scene_ui_ = new StartSceneUI(engine_, font_, fontSmall_, ui_base_, button_base_, cursor_);
    
    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.05;
    AudioBuffer* elevatorSound = new AudioBuffer("/Resources/Game/Sound/Machine_Gears_Loop05.wav");
    Engine::main->loadMusic("elevator sound", elevatorSound);
    AudioBuffer* elevatorFinish = new AudioBuffer("/Resources/Game/Sound/Stone Move 5_2.wav");
    Engine::main->loadMusic("elevator finish", elevatorFinish);
    AudioBuffer* ambientSound = new AudioBuffer("/Resources/Game/Sound/Ambient.wav");
    Engine::main->loadMusic("ambient sound 1", ambientSound);
    Engine::main->loadMusic("ambient sound 2", ambientSound);
    Engine::main->musicNode->sounds["elevator sound"].setLoop(true);
    Engine::main->musicNode->changeAudioVolume("elevator sound", 0.5, 0);
}


void ClientCore::loadDeathScene() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 8 - Load Death Scene --|" << std::endl;
    
    death_scene_ = new DeathScene(engine_);

    process_ = 2;
    load_state_ ++;
    loading_progress_ += 0.05;
}

void playNextAmbientTrack(bool track1) {
    if (track1) {
        Engine::main->playMusic("ambient sound 1");
        Animation* ambientPlaying = new Animation("ambient playing 1", 33);
        ambientPlaying->setCompletionHandler([&] {
            playNextAmbientTrack(false);
        });
        Engine::main->playAnimation(ambientPlaying);
    }
    else {
        Engine::main->playMusic("ambient sound 2");
        Animation* ambientPlaying = new Animation("ambient playing 2", 33);
        ambientPlaying->setCompletionHandler([&] {
            playNextAmbientTrack(true);
        });
        Engine::main->playAnimation(ambientPlaying);
    }
}

void ClientCore::displayStart() {
    std::cout << std::endl;
    std::cout << "|-- Pre-Game Stage 1 - Display Start Scene --|" << std::endl;
    
    start_scene_ui_->enabled = false;
    
    enter_game_ = true;
    is_waiting_ = true;
    cursor_->isDisable(false);
    start_scene_ui_->isDisbled(false);
    playNextAmbientTrack(true);
    Animation* startDelay = new Animation("startDelay", 1.0f);
    startDelay->setCompletionHandler([&] {
        Animation* showStart = new Animation("showStart", 1.0f);
        showStart->setEaseInTimingMode();
        showStart->setFloatAnimation(&(button_base_->alpha), 1.0f);
        showStart->setCompletionHandler([&] {
            start_scene_ui_->enabled = true;
        });
        engine_->playAnimation(showStart);
    });
    engine_->playAnimation(startDelay);
    
    process_ = 5;
}


void ClientCore::updateStart() {
    
    int state = start_scene_ui_->update(is_waiting_);
    if (state == 1) {
        process_ = 6;
        Animation* uiBaseExit = new Animation("uiBaseExit", 0.5f);
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
            
//            CharacterController::BezierCurve charBezierCurve2;
//            charBezierCurve2.controll_points.push_back(vec3(28.36f, -0.7f, -2.63f));
//            charBezierCurve2.controll_points.push_back(vec3(27.0582, -0.7f, -1.96449));
//            charBezierCurve2.controll_points.push_back(vec3(24.0796, -0.7f, 0.659909));
//            charBezierCurve2.controll_points.push_back(vec3(19.3051, -0.7f, 0.166199));
//            charBezierCurve2.controll_points.push_back(vec3(17.431, -0.7f, -4.85999));
//            charBezierCurve2.controll_points.push_back(vec3(15.2216, -0.7f, -6.83952));
//            charBezierCurve2.controll_points.push_back(vec3(13.125, -0.7f, -7.0875));
//            charBezierCurve2.level_of_detail = 200;
//
//            character_controller_2_ = new CharacterController(pre_chars_[1], charBezierCurve2);
            
            
            if (character_index_ == 0 || character_index_ == 2) {
                CameraController::BezierCurve bezierCurve1;
//                bezierCurve1.controll_points.push_back(vec3(-12.3641, 14.8889, 36.8971));
//                bezierCurve1.controll_points.push_back(vec3(-27.1926, 6.21359, 21.2189));
//                bezierCurve1.controll_points.push_back(vec3(-36.0384, 2.60817, 7.98844));
//                bezierCurve1.controll_points.push_back(vec3(-36.0166, 1.10242, -6.21638));
//                bezierCurve1.controll_points.push_back(vec3(-31.6031, 5.20109, -20.6809));
//                bezierCurve1.controll_points.push_back(vec3(-17.0633, 9.00687, -27.9127));
//                bezierCurve1.controll_points.push_back(vec3(1.22698, 14.1855, -28.7259));
//                bezierCurve1.controll_points.push_back(vec3(12.1842, 18.3501, -22.6672));
//                bezierCurve1.controll_points.push_back(vec3(21.9861, 22.5582, -10.2729));
//                bezierCurve1.controll_points.push_back(vec3(19.7959, 23.3058, 0.89875));
                
                bezierCurve1.controll_points.push_back(vec3(-12.3641, 14.8889, 36.8971));
                bezierCurve1.controll_points.push_back(vec3(-27.1926, 6.21359, 21.2189));
                bezierCurve1.controll_points.push_back(vec3(-27.1926, 6.21359, 21.2189));
                bezierCurve1.controll_points.push_back(vec3(-36.0384, 2.60817, 7.98844));
                bezierCurve1.controll_points.push_back(vec3(-36.0166, 1.10242, -6.21638));
                bezierCurve1.controll_points.push_back(vec3(-31.6031, 5.20109, -20.6809));
                bezierCurve1.controll_points.push_back(vec3(-17.0633, 9.00687, -27.9127));
                bezierCurve1.controll_points.push_back(vec3(1.22698, 14.1855, -28.7259));
                bezierCurve1.controll_points.push_back(vec3(12.1842, 18.3501, -22.6672));
                bezierCurve1.controll_points.push_back(vec3(21.9861, 22.5582, -10.2729));
                bezierCurve1.controll_points.push_back(vec3(21.9861, 22.5582, -10.2729));
                bezierCurve1.controll_points.push_back(vec3(19.7959, 23.3058, 0.89875));
                bezierCurve1.controll_points.push_back(vec3(19.7959, 23.3058, 0.89875));
                
                
                bezierCurve1.level_of_detail = 800;
                
                CameraController::EularChangeInfo eularChangeInfo1;
                eularChangeInfo1.is_clockwise_x = true;
                eularChangeInfo1.is_clockwise_y = true;
                eularChangeInfo1.is_clockwise_z = true;
                eularChangeInfo1.start_angle = vec3(0.0, 87.9956, -18.941);
                eularChangeInfo1.end_angle = vec3(0.0, 180.0, -25.0);
                
                CameraController::SpeedChangeInfo speedChangeInfo1;
                speedChangeInfo1.init_speed = 0.0f;
                speedChangeInfo1.max_speed = 2.8f;
                speedChangeInfo1.move_af = 0.04f;
                speedChangeInfo1.end_speed = 2.5f;
                
                camera_controller_1_ = new CameraController(engine_->mainCameraNode, bezierCurve1, eularChangeInfo1, speedChangeInfo1);
                
                
                CameraController::BezierCurve bezierCurve2;
                
                bezierCurve2.controll_points.push_back(vec3(19.7959, 23.3058, 0.89875));
                bezierCurve2.controll_points.push_back(vec3(19.7959, 23.3058, 0.89875));
                bezierCurve2.controll_points.push_back(vec3(19.7959, 23.3058, 0.89875));
                bezierCurve2.controll_points.push_back(vec3(22.9861, 24.1623, 14.5142));
                bezierCurve2.controll_points.push_back(vec3(22.1413, 27.3614, 32.8735));
                bezierCurve2.controll_points.push_back(vec3(7.42197, 27.9976, 46.6137));
                bezierCurve2.controll_points.push_back(vec3(-8.83625, 28.0162, 50.435));
                bezierCurve2.controll_points.push_back(vec3(-31.7806, 27.7042, 48.2877));
                bezierCurve2.controll_points.push_back(vec3(-43.6527, 27.1449, 41.8651));
                bezierCurve2.controll_points.push_back(vec3(-65.4234, 29.673, 22.5053));
                bezierCurve2.controll_points.push_back(vec3(-65.0254, 29.523, -0.545633));
                if (character_index_ == 0) {
                    bezierCurve2.controll_points.push_back(vec3(-48.7703, 25.0334, 0.413452));
                    bezierCurve2.controll_points.push_back(vec3(-48.7703, 25.0334, 0.413452));
                }
                else if (character_index_ == 2) {
                    bezierCurve2.controll_points.push_back(vec3(-48.7703, 25.0334, -2.94655));
                    bezierCurve2.controll_points.push_back(vec3(-48.7703, 25.0334, -2.94655));
                }

                bezierCurve2.level_of_detail = 800;
                
                CameraController::EularChangeInfo eularChangeInfo2;
                eularChangeInfo2.is_clockwise_x = true;
                eularChangeInfo2.is_clockwise_y = true;
                eularChangeInfo2.is_clockwise_z = false;
                eularChangeInfo2.start_angle = vec3(0.0, 180.0, -25.0);
                eularChangeInfo2.end_angle = vec3(0.0f, -4.5f, -18.0);
                
                CameraController::SpeedChangeInfo speedChangeInfo2;
                speedChangeInfo2.init_speed = 3.0f;
                speedChangeInfo2.max_speed = 3.1f;
                speedChangeInfo2.move_af = 0.04f;
                speedChangeInfo2.end_speed = 0.0f;
                
                camera_controller_2_ = new CameraController(engine_->mainCameraNode, bezierCurve2, eularChangeInfo2, speedChangeInfo2);
            }
            else {
                CameraController::BezierCurve bezierCurve1;
//                bezierCurve1.controll_points.push_back(vec3(-12.3641, 14.8889, 36.8971));
//                bezierCurve1.controll_points.push_back(vec3(4.87323, 4.37399, 26.4333));
//                bezierCurve1.controll_points.push_back(vec3(15.571, 0.519317, 6.87387));
//                bezierCurve1.controll_points.push_back(vec3(15.077, 2.89697, -10.9622));
//                bezierCurve1.controll_points.push_back(vec3(4.47728, 7.27986, -25.2025));
//                bezierCurve1.controll_points.push_back(vec3(-9.13663, 12.6829, -27.7081));
//                bezierCurve1.controll_points.push_back(vec3(-21.067, 14.726, -26.6613));
//                bezierCurve1.controll_points.push_back(vec3(-35.091, 15.7257, -19.702));
//                bezierCurve1.controll_points.push_back(vec3(-35.5757, 19.3824, -12.499));
//                bezierCurve1.controll_points.push_back(vec3(-37.699, 21.2707, -1.3718));
                bezierCurve1.controll_points.push_back(vec3(-12.3641, 14.8889, 36.8971));
                bezierCurve1.controll_points.push_back(vec3(4.87323, 4.37399, 26.4333));
                bezierCurve1.controll_points.push_back(vec3(4.87323, 4.37399, 26.4333));
                bezierCurve1.controll_points.push_back(vec3(15.571, 0.519317, 6.87387));
                bezierCurve1.controll_points.push_back(vec3(15.077, 2.89697, -10.9622));
                bezierCurve1.controll_points.push_back(vec3(4.47728, 7.27986, -25.2025));
                bezierCurve1.controll_points.push_back(vec3(-9.13663, 12.6829, -27.7081));
                bezierCurve1.controll_points.push_back(vec3(-21.067, 14.726, -26.6613));
                bezierCurve1.controll_points.push_back(vec3(-35.091, 15.7257, -19.702));
                bezierCurve1.controll_points.push_back(vec3(-35.5757, 19.3824, -12.499));
                bezierCurve1.controll_points.push_back(vec3(-35.5757, 19.3824, -12.499));
                bezierCurve1.controll_points.push_back(vec3(-37.699, 21.2707, -1.3718));
                bezierCurve1.controll_points.push_back(vec3(-37.699, 21.2707, -1.3718));
                bezierCurve1.level_of_detail = 800;
                
                CameraController::EularChangeInfo eularChangeInfo1;
                eularChangeInfo1.is_clockwise_x = true;
                eularChangeInfo1.is_clockwise_y = false;
                eularChangeInfo1.is_clockwise_z = true;
                eularChangeInfo1.start_angle = vec3(0.0, 87.9956, -18.941);
                eularChangeInfo1.end_angle = vec3(0.0, 0.0,-24.6152);
                
                CameraController::SpeedChangeInfo speedChangeInfo1;
                speedChangeInfo1.init_speed = 0.0f;
                speedChangeInfo1.max_speed = 2.8f;
                speedChangeInfo1.move_af = 0.04f;
                speedChangeInfo1.end_speed = 2.5f;
                
                camera_controller_1_ = new CameraController(engine_->mainCameraNode, bezierCurve1, eularChangeInfo1, speedChangeInfo1);
                CameraController::BezierCurve bezierCurve2;
                bezierCurve2.controll_points.push_back(vec3(-37.699, 21.2707, -1.3718));
                bezierCurve2.controll_points.push_back(vec3(-37.699, 21.2707, -1.3718));
                bezierCurve2.controll_points.push_back(vec3(-37.699, 21.2707, -1.3718));
                bezierCurve2.controll_points.push_back(vec3(-40.149, 23.8911, 12.6656));
                bezierCurve2.controll_points.push_back(vec3(-37.0909, 25.369, 27.3833));
                bezierCurve2.controll_points.push_back(vec3(-29.3621, 27.1266, 40.7915));
                bezierCurve2.controll_points.push_back(vec3(-21.9414, 28.3229, 49.0625));
                bezierCurve2.controll_points.push_back(vec3(-12.5228, 28.3229, 50.7738));
                bezierCurve2.controll_points.push_back(vec3(2.40476, 27.9317, 48.6534));
                bezierCurve2.controll_points.push_back(vec3(24.6695, 28.3048, 40.8248));
                bezierCurve2.controll_points.push_back(vec3(46.2194, 27.7195, 16.297));
                bezierCurve2.controll_points.push_back(vec3(51.1604, 30.8945, -0.92693));
                bezierCurve2.controll_points.push_back(vec3(32.3742, 28.5622, -0.616311));
                if (character_index_ == 1) {
                    bezierCurve2.controll_points.push_back(vec3(30.7352, 25.0334, -2.52214));
                    bezierCurve2.controll_points.push_back(vec3(30.7352, 25.0334, -2.52214));
                }
                else if (character_index_ == 3) {
                    bezierCurve2.controll_points.push_back(vec3(30.7352, 25.0334, 0.597857));
                    bezierCurve2.controll_points.push_back(vec3(30.7352, 25.0334, -2.52214));
                }
                bezierCurve2.level_of_detail = 800;
                
                CameraController::EularChangeInfo eularChangeInfo2;
                eularChangeInfo2.is_clockwise_x = true;
                eularChangeInfo2.is_clockwise_y = false;
                eularChangeInfo2.is_clockwise_z = false;
                eularChangeInfo2.start_angle = vec3(0.0, 0.0,-24.6152);
                eularChangeInfo2.end_angle = vec3(0.0f, 177.4, -18.0);
                
                CameraController::SpeedChangeInfo speedChangeInfo2;
                speedChangeInfo2.init_speed = 3.0f;
                speedChangeInfo2.max_speed = 3.1f;
                speedChangeInfo2.move_af = 0.04f;
                speedChangeInfo2.end_speed = 0.0f;
                
                camera_controller_2_ = new CameraController(engine_->mainCameraNode, bezierCurve2, eularChangeInfo2, speedChangeInfo2);
            }
            
            is_waiting_ = false;
        });
        engine_->playAnimation(netDelay);
    }
    
    cursor_->update();
}


void ClientCore::playCG() {
    if (cg_stage_ == 0 && !camera_controller_1_->moveCamera()) {
        if (!camera_controller_2_->moveCamera()) {
            cg_stage_ = 1;
        }
    }
    
    else if (cg_stage_ == 1) {
        char_camera_ = character_->cameraNode;
        engine_->mainCameraNode = char_camera_;
        
        Animation* startDelay = new Animation("startDelay",0.9);
        startDelay->setCompletionHandler([&] {
            Engine::main->playMusic("elevator sound");
            Animation* elevatorFinishAni = new Animation("elevatorfinish1", 8.5);
            elevatorFinishAni->setCompletionHandler([&] {
                Engine::main->playMusic("elevator finish");
            });
            engine_->playAnimation(elevatorFinishAni);
            Animation* elevatorNodeMove1 = new Animation("elevatorNodeMove1", 9);
            elevatorNodeMove1->setCompletionHandler([&] {
                Engine::main->stopMusic("elevator sound");
            });
            elevatorNodeMove1->setEaseInEaseOutTimingMode();
            elevatorNodeMove1->setFloatAnimation(&(cg_used_node_[0]->position.y), -0.7f);
            engine_->playAnimation(elevatorNodeMove1);
            Animation* elevatorNodeMove2 = new Animation("elevatorNodeMove2", 9);
            elevatorNodeMove2->setEaseInEaseOutTimingMode();
            elevatorNodeMove2->setFloatAnimation(&(cg_used_node_[1]->position.y), -0.7f);
            engine_->playAnimation(elevatorNodeMove2);
            
            Animation* elevatorBoxMove1 = new Animation("elevatorBoxMove1", 9);
            elevatorBoxMove1->setEaseInEaseOutTimingMode();
            elevatorBoxMove1->setFloatAnimation(&(cg_used_box_[0]->position_.y), -1.2f);
            engine_->playAnimation(elevatorBoxMove1);
            Animation* elevatorBoxMove2 = new Animation("elevatorBoxMove2", 9);
            elevatorBoxMove2->setEaseInEaseOutTimingMode();
            elevatorBoxMove2->setFloatAnimation(&(cg_used_box_[1]->position_.y), -1.2f);
            engine_->playAnimation(elevatorBoxMove2);
            
            elevatorBoxMove2->setCompletionHandler([&] {
                Animation* gateNodeMove1 = new Animation("gateNodeMove1", 9);
                gateNodeMove1->setEaseInEaseOutTimingMode();
                gateNodeMove1->setFloatAnimation(&(cg_used_node_[2]->position.y), 3.3f);
                engine_->playAnimation(gateNodeMove1);
                Animation* gateNodeMove2 = new Animation("gateNodeMove2", 9);
                gateNodeMove2->setEaseInEaseOutTimingMode();
                gateNodeMove2->setFloatAnimation(&(cg_used_node_[3]->position.y), 3.3f);
                engine_->playAnimation(gateNodeMove2);
                
                Animation* gateBoxMove1 = new Animation("gateBoxMove1", 9);
                gateBoxMove1->setEaseInEaseOutTimingMode();
                gateBoxMove1->setFloatAnimation(&(cg_used_box_[2]->position_.y), 5.0f);
                engine_->playAnimation(gateBoxMove1);
                Animation* gateBoxMove2 = new Animation("gateBoxMove2", 9);
                gateBoxMove2->setEaseInEaseOutTimingMode();
                gateBoxMove2->setFloatAnimation(&(cg_used_box_[3]->position_.y), 5.0f);
                engine_->playAnimation(gateBoxMove2);
                
                gateBoxMove2->setCompletionHandler([&] {
                    cg_stage_ = 3;
                });
            });
        });
        engine_->playAnimation(startDelay);
        
        cg_stage_ = 2;
    }
    
    else if (cg_stage_ == 2) {
        for (auto& box : cg_used_box_) {
            box->updateTransMtx();
            box->updateMostXYZ();
        }
    }
    
//    else if (cg_stage_ == 3) {
//        if (!character_controller_2_->moveCharacter()) {
//            pre_chars_[1]->isLocked = true;
//            pre_chars_[1]->state = CharState::IDLE;
//            cg_stage_ = 4;
//        }
//    }
    
    else if (cg_stage_ == 3) {
        hud_base_->isDisabled = false;
        Animation* showHUDBase = new Animation("showHUDBase", 0.5);
        showHUDBase->setFloatAnimation(&hud_base_->alpha, 1);
        showHUDBase->setEaseOutTimingMode();
        engine_->playAnimation(showHUDBase);
        enter_game_ = false;
        process_ = 7;
    }
    
    for (auto& it : all_chars_) {
        it.second->updatePosition();
    }
}


void ClientCore::loadHUD() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 8 - Load HUD --|" << std::endl;
    hud_base_ = new UINode();
    hud_base_->renderingOrder = 10000.0f;
    engine_->addNode(hud_base_);
    hud_ = new HUDNode(engine_, hud_base_, true, font_, fontSmall_,character_, ally_);
    hud_base_->isDisabled = true;
    hud_base_->alpha = 0;
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
        

        if(engine_->input->wasKeyPressed(KEY_SPACE)){
            event_pb_->setRoll(true);
        }
        else {
            event_pb_->setRoll(false);
        }
        
        if(engine_->input->wasKeyPressed(KEY_G)){
            event_pb_->setToggleLock(true);
        }
        else {
            event_pb_->setToggleLock(false);
        }
        
        if (engine_->input->wasKeyPressed(KEY_ESCAPE)) {
            exit(1);
        }
        
        if(engine_->input->wasKeyPressed(KEY_C)){
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
        
        if(engine_->input->wasKeyPressed(KEY_1)) {
            character_->setCurrMagic(key_to_magic_[KEY_1]);
        }
        
        if(engine_->input->wasKeyPressed(KEY_2)) {
            character_->setCurrMagic(key_to_magic_[KEY_2]);
        }
        
        if(engine_->input->wasKeyPressed(KEY_3)) {
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
        
        
        if (pre_chars_[0]->health <= 0 && pre_chars_[2]->health <= 0) {
            if (character_index_ == 0 || character_index_ == 2) {
                is_win_game_ = 2;
            }
            else {
                is_win_game_ = 1;
            }
        }
        if (pre_chars_[1]->health <= 0 && pre_chars_[3]->health <= 0) {
            if (character_index_ == 1 || character_index_ == 3) {
                is_win_game_ = 2;
            }
            else {
                is_win_game_ = 1;
            }
        }
        
        hud_->update(!main_camera_, is_win_game_);
    }
}


void ClientCore::renderWorld() {
    std::cout << std::endl;
    std::cout << "|-- Cycle Stage 5 - Render World --|" << std::endl;
    
    engine_->renderDirectionalLightShadowMap(directional_light_);
    
    if (!enter_game_) {
//    cout << "position: " << character_->modelNode->getWorldPosition().x << " " << character_->modelNode->getWorldPosition().y << " " << character_->modelNode->getWorldPosition().z << endl;
////
//    cout << "Angle: " << character_->modelNode->getWorldEulerAngles().x << " " << character_->modelNode->getWorldEulerAngles().y << " " << character_->modelNode->getWorldEulerAngles().z << endl;
        
//        cout << "position: " << engine_->mainCameraNode->getWorldPosition().x << " " << engine_->mainCameraNode->getWorldPosition().y << " " << engine_->mainCameraNode->getWorldPosition().z << endl;
//    //
//        cout << "Angle: " << engine_->mainCameraNode->getWorldEulerAngles().x << " " << engine_->mainCameraNode->getWorldEulerAngles().y << " " << engine_->mainCameraNode->getWorldEulerAngles().z << endl;
    }
    
    float time1 = systemTime();
    
    engine_->render();
    
    float time2 = systemTime();
    
    print("FPS:", 1.0f / (time2 - time1));
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
