//
//  OfflineCore.cpp
//
//  Created by Kangming Yu on 4/15/22.
//

#include "Core/OfflineCore/OfflineCore.hpp"

#include <iostream>

#include "Game/Map/ImportMapHelper.hpp"
#include "Game/Magic/AllMagic.inc"

#ifdef _WIN64
#define ROOT_PATH "D:/StudyProject/Eternal_Ritual/VSProject/cse125-sp22-group5"
#elif __APPLE__
#define ROOT_PATH "."
#endif

using namespace glm;
using namespace std;


OfflineCore* OfflineCore::offline_core_ = nullptr;

OfflineCore::OfflineCore() {
}


OfflineCore::~OfflineCore() {
    map_system_manager_->Destructor();
    delete hit_controller_;
    delete engine_;
}


void OfflineCore::initEngine(int* p, int* l) {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 1 - Initial Engine --|" << std::endl;

    pro = p;
    loadState = l;
    loadingProgress = 0;

    engine_ = new Engine("KGLEngine", 0.7f, 0, NULL);
    engine_->workingDirectory = ROOT_PATH;
    //engine_->lockCursor();
}

void OfflineCore::loadFont()
{
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 6 - Load Font --|" << std::endl;
    FontLibrary* fontLibrary = new FontLibrary();
    font_ = fontLibrary->loadFontFile("/Resources/Fonts/Cinzel/Cinzel.ttf", 50);
}

void OfflineCore::loadHUD()
{
    mainCamera = true;

    std::cout << std::endl;
    std::cout << "|-- Loading Stage 6 - Load HUD --|" << std::endl;
    HUDbase_ = new UINode();
    HUDbase_->renderingOrder = 10000;
    engine_->addNode(HUDbase_);
    HUD_ = new HUDNode(engine_, HUDbase_, true, font_, character_, ally_);
    HUDbase_->isDisabled = true;
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
}

void OfflineCore::loadAlly()
{
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 6 - Load Ally --|" << std::endl;

    ally_ = character_->copy(vec3(-2.0, -1.0f, -2.0f));
    ally_->name = "Ally";
    ally_->setEularAngle(vec3(0, 90.0f, 0));

    ally_->stopAndPlay("idle", 0.0f, 0.0f);
    engine_->addNode(ally_);
    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine_->addNode(baseNode);
    ally_->setUINode(baseNode);
    ally_->setName("Ally");
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
}

void OfflineCore::displayLogo()
{
    UIBase_ = new UINode();
    UIBase_->renderingOrder = 10000;
    UIBase_->size = glm::vec2(1.0);
    UIcam = new CameraNode(60.0f, 0.1f, 1000.0f);
    UIcam->position = glm::vec3(-7.95262, 49.7237, 41.5025);
    UIcam->eulerAngles = glm::vec3(0, 91.6, -47.1);
    engine_->addNode(UIcam);
    engine_->mainCameraNode = UIcam;
    logo_ = new Logo(engine_,font_, UIBase_, pro);
    logo_->play();
}

void OfflineCore::updateLoad()
{
    logo_->updateLoad(loadingProgress);
}

void OfflineCore::loadStartScene()
{
    cursor_ = new Cursor(engine_);
    ButtonBase_ = new UINode();
    ButtonBase_->size = glm::vec2(1.0);
    ButtonBase_->screenPosition = glm::vec2(0.5);
    
    startSceneUI_ = new StartSceneUI(engine_, font_, UIBase_,ButtonBase_);
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.05;
}

void OfflineCore::displayStart()
{
    enterGame = true;
    isWaiting = false;
    cursor_->isDisable(false);
    startSceneUI_->isDisbled(false);
    Animation* startDelay = new Animation("startDelay",0.9);
    startDelay->setCompletionHandler([&] {
        Animation* showStart = new Animation("showStart", 1);
        showStart->setEaseInTimingMode();
        showStart->setFloatAnimation(&(ButtonBase_->alpha), 1.0);
        engine_->playAnimation(showStart);
    });
    engine_->playAnimation(startDelay);
    *pro = 5;
}

void OfflineCore::updateStart()
{
    int state = startSceneUI_->update(isWaiting);
    if (state == 1) {
        *pro = 6;
    }

    //engine_->mainCameraNode->position = glm::vec3(-7.95262, 49.7237, 41.5025);
    //engine_->mainCameraNode->eulerAngles = glm::vec3(0, 91.6, -47.1);

    cursor_->update();

    if (engine_->input->wasKeyPressed(KEY_1)) {
        isWaiting = false;
    }
}

void OfflineCore::loadEnd()
{
    deathScene_ = new DeathScene(engine_);
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.05;
}

void OfflineCore::displayEnd()
{
    deathScene_->display(true,pro);
    (* pro)++;
}

void OfflineCore::reset()
{
    enterGame = true;
    character_->health = 1000;
    HUD_->reset();
    engine_->mainCameraNode = UIcam;
    /*engine_->mainCameraNode->position = glm::vec3(-7.95262, 49.7237, 41.5025);
    engine_->mainCameraNode->eulerAngles = glm::vec3(0, 91.6, -47.1);*/
    HUDbase_->isDisabled = true;
    *pro = 4;
}


void OfflineCore::loadSky() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 2 - Load Sky Box --|" << std::endl;
    
    this->engine_->skybox = new Skybox("/Resources/Game/Skybox/NMF.png", "/Resources/Game/Skybox/NMB.png",
                                "/Resources/Game/Skybox/NMU.png", "/Resources/Game/Skybox/NMD.png",
                                "/Resources/Game/Skybox/NMR.png", "/Resources/Game/Skybox/NML.png",
                                2.0f);
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
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
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
}


void OfflineCore::loadMap() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 4 - Load Scene --|" << std::endl;

    map_system_manager_ = MapSystemManager::Instance();
    
    ImportMapHelper::importMapBox();
    ImportMapHelper::importMapModel();
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
}


void OfflineCore::loadCharacter() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 5 - Load Character --|" << std::endl;
    
    character_ = new CharNode(vec3(0.0f, -1.0f, 0.0f));
    character_->name = "main character";
    
    Node* controlNode = new Node();
    controlNode->position = vec3(0.0f, 1.2f, 0.0f);
    character_->setControl(controlNode);
    
    charcam = new CameraNode(60.0f, 0.1f, 1000.0f);
    charcam->position = vec3(-2.5f, 0.0f, 0.0f);
    charcam->addChildNode(point_light_);
    character_->setCamera(charcam);
    //engine_->mainCameraNode = cameraNode;

    character_->stopAndPlay("idle", 0.0f, 0.0f);;
    
    engine_->addNode(character_);
    
    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine_->addNode(baseNode);
    character_->setUINode(baseNode);
    character_->setName("Player1");
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
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
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
}


void OfflineCore::loadMagic() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 7 - Load Magic --|" << std::endl;
    int magicIndex = 0;
    
    DamageableMagic* stoneBlast = new Storm();
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
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
}

void OfflineCore::loadDamageSystem() {
    std::cout << std::endl;
    std::cout << "|-- Loading Stage 11 - Load Damage System --|" << std::endl;
    
    hit_controller_ = new HitController();
    
    for (auto& magic : all_magics_) {
        DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
        if (damageableMagic != nullptr) {
            hit_controller_->addMagic(damageableMagic);
        }
    }
    
    for (auto& enemy : enemies_) {
        hit_controller_->addCharacter(enemy);
    }
    *pro = 2;
    (*loadState)++;
    loadingProgress += 0.1;
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



    if (engine_->input->wasKeyPressed(KEY_P)) {
        character_->health = 0;
    }
    if (engine_->input->wasKeyPressed(KEY_L)) {
        mainCamera = true;
    }
    if (engine_->input->wasKeyPressed(KEY_K)) {
        mainCamera = false;
    }
    if (engine_->input->wasKeyPressed(KEY_O)) {
        HUD_->toggleViewDead(enemies_[0]);
    }
    if (engine_->input->wasKeyPressed(KEY_I)) {
        HUD_->toggleViewDead(ally_);
    }
    if (engine_->input->wasKeyPressed(KEY_U)) {
        HUD_->toggleViewDead(character_);
    }
    if (engine_->input->wasKeyPressed(KEY_J)) {
        deathScene_->display(true, pro);
        Animation* delay = new Animation("resetdelay", 1.5);
        delay->setCompletionHandler([&] {
            *pro = 7;
            });
        engine_->playAnimation(delay);
    }
}


void OfflineCore::cameraHandle() {

    if (engine_->input->wasKeyReleased(KEY_ESCAPE)) {
        engine_->terminate();
    }

    glm::vec3 cameraTargetPosition = engine_->mainCameraNode->position;

    // Update target position:
    if (engine_->input->isPressingKey(KEY_W)) {
        cameraTargetPosition += engine_->mainCameraNode->getFrontVectorInWorld() * 0.2f;
    }
    else if (engine_->input->isPressingKey(KEY_S)) {
        cameraTargetPosition += engine_->mainCameraNode->getBackVectorInWorld() * 0.2f;
    }
    if (engine_->input->isPressingKey(KEY_A)) {
        cameraTargetPosition += engine_->mainCameraNode->getLeftVectorInWorld() * 0.2f;
    }
    else if (engine_->input->isPressingKey(KEY_D)) {
        cameraTargetPosition += engine_->mainCameraNode->getRightVectorInWorld() * 0.2f;
    }
    if (engine_->input->isPressingKey(KEY_E)) {
        cameraTargetPosition += engine_->mainCameraNode->getUpVectorInWorld() * 0.2f;
    }
    else if (engine_->input->isPressingKey(KEY_Q)) {
        cameraTargetPosition += engine_->mainCameraNode->getDownVectorInWorld() * 0.2f;
    }

    glm::vec3 cameraTargetEulerAngles = engine_->mainCameraNode->eulerAngles;
    // Update target euler angles:
    vec2 mouseTranslation = engine_->input->getMouseTranslation() * 0.1f;
    cameraTargetEulerAngles.y -= mouseTranslation.x;
    cameraTargetEulerAngles.z -= mouseTranslation.y;
    cameraTargetEulerAngles.z = glm::max(-60.0f, glm::min(cameraTargetEulerAngles.z, 60.0f));


    engine_->mainCameraNode->position = cameraTargetPosition;
    engine_->mainCameraNode->eulerAngles = cameraTargetEulerAngles;
    //// Smooth rotation:
    std::cout << "p: " << UIcam->position.x << "," << UIcam->position.y << "," << UIcam->position.z << std::endl;
    std::cout << "p: " << engine_->mainCameraNode->position.x << "," << engine_->mainCameraNode->position.y << "," << engine_->mainCameraNode->position.z << std::endl;
    std::cout << "A: " << cameraTargetEulerAngles.x << "," << cameraTargetEulerAngles.y << "," << cameraTargetEulerAngles.z << std::endl;
}



void OfflineCore::updateState() {
    
    cursor_->isDisable(true);

    if (enterGame) {
        UIBase_->isDisabled = true;
        HUDbase_->isDisabled = false;
        engine_->mainCameraNode = charcam;
        enterGame = false;
    }

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

    HUD_->update(!mainCamera);
}


void OfflineCore::renderWorld() {
    engine_->renderDirectionalLightShadowMap(directional_light_);
}

void OfflineCore::render() {
    engine_->render();
}

void destructOfflineCore(int signum) {
    std::cout << "Game over" << std::endl;
    
    OfflineCore::Destructor();
    
    exit(1);
}
