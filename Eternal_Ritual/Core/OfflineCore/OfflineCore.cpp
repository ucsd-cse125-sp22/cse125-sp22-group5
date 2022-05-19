#include "Core/OfflineCore/OfflineCore.hpp"

#include <iostream>

#include "Game/Map/ImportMapHelper.hpp"
#include "Game/Character/ImportCharHelper.hpp"
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
    
    engine_ = new Engine("KGLEngine", 0.8f, 0, NULL);
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

    ImportCharHelper::importCharModel(character_);
    
    ImportCharHelper::importCharAnimation(character_);
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
    
    DamageableMagic* stoneBlast = new StoneBlast();
    DamageableMagic* fireBall = new ScatteredFire();
    DamageableMagic* lightningSpear = new LightningPhalanx();
    DamageableMagic* groundSmash = new GroundSmash();
    DamageableMagic* thunder = new Thunder();
    DamageableMagic* flame = new Flame();
    DamageableMagic* thousandBlade = new ThousandBlade();
    DamageableMagic* dragon = new DragonMagic(character_->modelNode);
    
    key_to_magic_[KEY_1] = Magic::STONEBLAST;
    magic_to_key_[Magic::STONEBLAST] = KEY_1;
    character_->addMagics(Magic::STONEBLAST, stoneBlast);
    all_magics_.insert(stoneBlast);
    key_to_magic_[KEY_2] = Magic::FIREBALL;
    magic_to_key_[Magic::FIREBALL] = KEY_2;
    character_->addMagics(Magic::FIREBALL, fireBall);
    all_magics_.insert(fireBall);
    key_to_magic_[KEY_3] = Magic::LIGHTNINGSPEAR;
    magic_to_key_[Magic::LIGHTNINGSPEAR] = KEY_3;
    character_->addMagics(Magic::LIGHTNINGSPEAR, lightningSpear);
    all_magics_.insert(lightningSpear);
    key_to_magic_[KEY_4] = Magic::THUNDER;
    magic_to_key_[Magic::THUNDER] = KEY_4;
    character_->addMagics(Magic::THUNDER, thunder);
    all_magics_.insert(thunder);
    key_to_magic_[KEY_5] = Magic::FLAME;
    magic_to_key_[Magic::FLAME] = KEY_5;
    character_->addMagics(Magic::FLAME, flame);
    all_magics_.insert(flame);
    key_to_magic_[KEY_6] = Magic::THOUSANDBLADE;
    magic_to_key_[Magic::THOUSANDBLADE] = KEY_6;
    character_->addMagics(Magic::THOUSANDBLADE, thousandBlade);
    all_magics_.insert(thousandBlade);
    key_to_magic_[KEY_7] = Magic::GROUNDSMASH;
    magic_to_key_[Magic::GROUNDSMASH] = KEY_7;
    character_->addMagics(Magic::GROUNDSMASH, groundSmash);
    all_magics_.insert(groundSmash);
    key_to_magic_[KEY_8] = Magic::DRAGON;
    magic_to_key_[Magic::DRAGON] = KEY_8;
    character_->addMagics(Magic::DRAGON, dragon);
    all_magics_.insert(dragon);
    
    engine_->addNode(stoneBlast);
    engine_->addNode(flame);
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
        enemies_[0]->modelNode->getAnimator("roll")->play(0.5);
        enemies_[0]->uninjurable = true;
        cout << enemies_[0]->modelNode->getAnimator("roll")->isPlaying() << endl;
    }
    
    if(engine_->input->wasKeyReleased(KEY_G)){
        character_->toggleLock(enemies_);
    }
    
    if(engine_->input->wasKeyReleased(KEY_Q)){
        enemies_[0]->characterTargetEulerAngles += vec3(0, 90, 0);
    }
    
    if(engine_->input->wasKeyReleased(KEY_1)){
        character_->castMagic(key_to_magic_[KEY_1]);
    }
    if(engine_->input->wasKeyReleased(KEY_2)){
        BaseMagic* magic = character_->magics[key_to_magic_[KEY_2]];
        if (!magic->start) {
            magic->removeFromParentNode();
            character_->rightHand->addChildNode(magic);
            character_->castMagic(key_to_magic_[KEY_2]);
        }
    }
    if (engine_->input->wasKeyPressed(KEY_3)) {
        BaseMagic* magic = character_->magics[key_to_magic_[KEY_3]];
        if (!magic->start) {
            magic->removeFromParentNode();
            character_->headTop->addChildNode(magic);
            character_->castMagic(key_to_magic_[KEY_3]);
        }
    }
    if (engine_->input->wasKeyPressed(KEY_4)) {
        BaseMagic* magic = character_->magics[key_to_magic_[KEY_4]];
        if (!magic->start) {
            character_->castMagic(key_to_magic_[KEY_4]);
        }
    }
    if (engine_->input->wasKeyPressed(KEY_5)) {
        character_->castMagic(key_to_magic_[KEY_5]);
    }
    if (engine_->input->wasKeyPressed(KEY_6)) {
        character_->castMagic(key_to_magic_[KEY_6]);
    }
    if (engine_->input->wasKeyPressed(KEY_7)) {
        character_->castMagic(key_to_magic_[KEY_7]);
    }
    if (engine_->input->wasKeyPressed(KEY_8)) {
        character_->castMagic(key_to_magic_[KEY_8]);
    }
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
