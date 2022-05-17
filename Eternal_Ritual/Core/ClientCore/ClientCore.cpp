//#include "Core/ClientCore/ClientCore.hpp"
//
//#include "Game/Map/ImportMapHelper.hpp"
//#include "Game/Character/ImportCharHelper.hpp"
//#include "Game/Magic/AllMagic.inc"
//
//using namespace glm;
//using namespace std;
//
//
//ClientCore* ClientCore::client_core_ = nullptr;
//
//ClientCore::ClientCore() {
//}
//
//
//ClientCore::~ClientCore() {
////    delete clientSocket;
////    delete statePb;
////    delete eventPb;
//
//    map_system_manager_->Destructor();
//    hit_controller_->Destructor();
//    delete engine_;
//}
//
//
//void ClientCore::initEngine() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 1 - Initial Engine --|" << std::endl;
//
//    engine_ = new Engine("KGLEngine", 0.8f, 0, NULL);
//    engine_->workingDirectory = "/Users/kang/Desktop/Week6/Client/KGLEngine";
//    engine_->lockCursor();
//}
//
//
//void ClientCore::loadSky() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 2 - Load Sky Box --|" << std::endl;
//
//    this->engine_->skybox = new Skybox("/Resources/Game/Skybox/AR.png", "/Resources/Game/Skybox/AL.png",
//                                "/Resources/Game/Skybox/AT.png", "/Resources/Game/Skybox/ABo.png",
//                                "/Resources/Game/Skybox/AF.png", "/Resources/Game/Skybox/AB.png",
//                                2.0f);
//}
//
//
//void ClientCore::loadLight() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 3 - Load Lights --|" << std::endl;
//
//    point_light_ = new LightNode(vec3(5.0f));
//    point_light_->setPointLight(2.0f, 20.0f);
//    point_light_->highlightIntensity = 0.0f;
//
//    ambient_light_ = new LightNode(vec3(0.5f));
//    ambient_light_->setAmbientLight();
//    engine_->addNode(ambient_light_);
//
//    directional_light_ = new LightNode(vec3(2.5f, 2.0f, 2.0f));
//    directional_light_->setDirectionalLight();
//    directional_light_->eulerAngles = vec3(0.0f, 135.0f, -45.0f);
//    engine_->addNode(directional_light_);
//
//}
//
//
//void ClientCore::loadMap() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 4 - Load Scene --|" << std::endl;
//
//    map_system_manager_ = MapSystemManager::Instance();
//
//    ImportMapHelper::importMapBox();
//    ImportMapHelper::importMapModel();
//}
//
//
//void ClientCore::loadCharacter() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 5 - Load Character --|" << std::endl;
//
//    character_ = new CharNode(vec3(0.0f, -1.0f, 0.0f));
//    character_->name = "main character";
//
//    Node* controlNode = new Node();
//    controlNode->position = vec3(0.0f, 1.0f, 0.0f);
//    character_->setControl(controlNode);
//
//    CameraNode* cameraNode = new CameraNode(60.0f, 0.1f, 1000.0f);
//    cameraNode->position = vec3(-2.0f, 0.0f, 0.0f);
//    cameraNode->addChildNode(point_light_);
//    character_->setCamera(cameraNode);
//    engine_->mainCameraNode = cameraNode;
//
//    ImportCharHelper::importCharModel(character_);
//
//    ImportCharHelper::importCharAnimation(character_);
//    character_->stopAndPlay("idle", 0.0f, 0.0f);;
//
//    engine_->addNode(character_);
//
//    UINode* baseNode = new UINode();
//    baseNode->renderingOrder = 1000.0f;
//    engine_->addNode(baseNode);
//    character_->setUINode(baseNode);
//    character_->setName("Player1");
//}
//
//
//void ClientCore::loadWeapon() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 6 - Load Weapon --|" << std::endl;
//
//    Node* characterRightHand = character_->generateBoneNode("RightHand");
//
//    weapon_node_ = new Node();
//    weapon_node_->scale = vec3(1);
//
//    characterRightHand->addChildNode(weapon_node_);
//}
//
//
//void ClientCore::loadEnemy() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 7 - Load Enemy --|" << std::endl;
//
//    CharNode* enemy = character_->copy(vec3(2.0, -1.0f, 2.0f));
//    enemy->name = "enemy1";
//    enemy->setEularAngle(vec3(0,90.0f,0));
//
//    enemy->stopAndPlay("idle", 0.0f, 0.0f);
//    engine_->addNode(enemy);
//    UINode* baseNode = new UINode();
//    baseNode->renderingOrder = 1000.0f;
//    engine_->addNode(baseNode);
//    enemy->setUINode(baseNode);
//    enemy->setName("Enemy");
//
//    enemies_.push_back(enemy);
//}
//
//
//void ClientCore::loadMagic() {
//    std::cout << std::endl;
//    std::cout << "|-- Stage 8 - Load Magic --|" << std::endl;
//
//    DamageableMagic* stoneBlast = new StoneBlast();
//    DamageableMagic* fireBall = new FireBall();
//    DamageableMagic* lightningSpear = new LightningSpear();
//    DamageableMagic* groundSmash = new GroundSmash();
//    DamageableMagic* thunder = new Thunder();
//    DamageableMagic* flame = new Flame();
//    DamageableMagic* thousandBlade = new ThousandBlade();
//
//    key_to_magic_[KEY_1] = Magic::STONEBLAST;
//    magic_to_key_[Magic::STONEBLAST] = KEY_1;
//    character_->addMagics(Magic::STONEBLAST, stoneBlast);
//    all_magics_.insert(stoneBlast);
//    key_to_magic_[KEY_2] = Magic::FIREBALL;
//    magic_to_key_[Magic::FIREBALL] = KEY_2;
//    character_->addMagics(Magic::FIREBALL, fireBall);
//    all_magics_.insert(fireBall);
//    key_to_magic_[KEY_3] = Magic::LIGHTNINGSPEAR;
//    magic_to_key_[Magic::LIGHTNINGSPEAR] = KEY_3;
//    character_->addMagics(Magic::LIGHTNINGSPEAR, lightningSpear);
//    all_magics_.insert(lightningSpear);
//    key_to_magic_[KEY_4] = Magic::THUNDER;
//    magic_to_key_[Magic::THUNDER] = KEY_4;
//    character_->addMagics(Magic::THUNDER, thunder);
//    all_magics_.insert(thunder);
//    key_to_magic_[KEY_5] = Magic::FLAME;
//    magic_to_key_[Magic::FLAME] = KEY_5;
//    character_->addMagics(Magic::FLAME, flame);
//    all_magics_.insert(flame);
//    key_to_magic_[KEY_6] = Magic::THOUSANDBLADE;
//    magic_to_key_[Magic::THOUSANDBLADE] = KEY_6;
//    character_->addMagics(Magic::THOUSANDBLADE, thousandBlade);
//    all_magics_.insert(thousandBlade);
//    key_to_magic_[KEY_7] = Magic::GROUNDSMASH;
//    magic_to_key_[Magic::GROUNDSMASH] = KEY_7;
//    character_->addMagics(Magic::GROUNDSMASH, groundSmash);
//    all_magics_.insert(groundSmash);
//
//    engine_->addNode(stoneBlast);
//    engine_->addNode(flame);
//    engine_->addNode(thunder);
//}
//
//
//void ClientCore::loadDamageSystem() {
//    hit_controller_ = HitController::Instance();
//
//    for (auto& magic : all_magics_) {
//        DamageableMagic* damageableMagic = dynamic_cast<DamageableMagic*>(magic);
//        if (damageableMagic == nullptr) {
//            perror("Magic to damageableMagic fail");
//            exit(1);
//        }
//        hit_controller_->addMagic(damageableMagic);
//    }
//
//    for (auto& enemy : enemies_) {
//        hit_controller_->addCharacter(enemy);
//    }
//}
//
//
//void ClientCore::noNetworkLoop() {
//    Particle3DNode* radiation = nullptr;
//    while(engine_->isRunning()) {
//        if(engine_->shouldUpdate()) {
//            if(engine_->input->wasKeyReleased(KEY_ESCAPE)) {
//                engine_->terminate();
//            }
//
//            if(engine_->input->isPressingKey(KEY_W)) {
//                character_->moveFront();
//            }else if(engine_->input->isPressingKey(KEY_S)) {
//                character_->moveBack();
//            }
//            if(engine_->input->isPressingKey(KEY_A)) {
//                character_->moveLeft();
//            }else if(engine_->input->isPressingKey(KEY_D)) {
//                character_->moveRight();
//            }
//            if(engine_->input->wasKeyReleased(KEY_SPACE)){
//                character_->toggleLock(enemies_);
//            }
//
//
//            if(engine_->input->wasKeyReleased(KEY_G)){
//                character_->toggleLock(enemies_);
//            }
//            character_->moveCamera(engine_->input->getMouseTranslation() * 0.1f);
//
//            character_->updatePosition();
//            character_->updateTransform();
//
//            if(engine_->input->wasKeyReleased(KEY_Q)){
//                enemies_[0]->characterTargetEulerAngles += vec3(0, 90, 0);
//            }
//
//            if(engine_->input->wasKeyReleased(KEY_1)){
//                character_->castMagic(key_to_magic_[KEY_1]);
//            }
//            if(engine_->input->wasKeyReleased(KEY_2)){
//                BaseMagic* magic = character_->magics[key_to_magic_[KEY_2]];
//                if (!magic->start) {
//                    magic->removeFromParentNode();
//                    character_->rightHand->addChildNode(magic);
//                    character_->castMagic(key_to_magic_[KEY_2]);
//                }
//            }
//            if (engine_->input->wasKeyPressed(KEY_3)) {
//                BaseMagic* magic = character_->magics[key_to_magic_[KEY_3]];
//                if (!magic->start) {
//                    magic->removeFromParentNode();
//                    character_->rightHand->addChildNode(magic);
//                    character_->castMagic(key_to_magic_[KEY_3]);
//                }
//            }
//            if (engine_->input->wasKeyPressed(KEY_4)) {
//                if (!lightningMagic->start) {
//                    character->castMagic(KEY_4);
//                }
//            }
//            if (engine->input->wasKeyPressed(KEY_5)) {
//                character->castMagic(KEY_5);
//            }
//            if (engine->input->wasKeyPressed(KEY_6)) {
//                character->castMagic(KEY_6);
////                ParticleNode* spark = new ParticleNode(130, 1, 0);
////                spark->setMaxAmount(100);
////                spark->spreadingAngle = 360;
////                spark->initialSpeed = 0.5;
////                spark->initialSpeedVariation = 0.3;
////                spark->isAdditive = true;
////                spark->setEmissionSphere(0.3, 0.5);
////                spark->renderingOrder = 999l;
////                spark->acceleration = vec3(0, -1, 0);
////                spark->texture = new Texture("/Resources/Game/Effects/TeleportParticles.png");
////                spark->setSpriteSheetAnimation(1, 8, 8, 1, 0);
////                spark->initialScale = 0.1;
////                spark->scalingSpeed = -0.05;
////                spark->initialRotationVariation = 360;
////                spark->color = vec4(0.3, 0.4, 1, 1);
////                spark->initialScaleVariation = 0.05;
////                spark->setColorAnimation(vec4(1, 0.7, 0.1, 1), 0.0f);
////                spark->setColorAnimation(vec4(1, 0.4, 0.1, 0), 1.0f);
////                engine->addNode(spark);
//            }
//            if (engine->input->wasKeyPressed(KEY_7)) {
//                character->castMagic(KEY_7);
//            }
//
//            for (int i = 0; i < enemies.size(); i++){
//                enemies[i]->updatePosition();
//                enemies[i]->updateTransform();
////                cout << to_string(enemies[i]->getWorldTransform()) << endl;
//            }
//            if (radiation != nullptr)
//                radiation->eulerAngles.y += 10;
//            stoneMagic->updateMagic();
//            fireMagic->updateMagic();
//            lightningMagic->updateMagic();
//            smashMagic->updateMagic();
//            swordMagic->updateMagic();
//
//
//            enemyHitController.checkHit();
//
////            vec3 position;
////            vec3 normalvec;
////            if (mapSystemManager->hitTest(cameraNode->getWorldPosition(), cameraNode->getWorldPosition() +
////                                          cameraNode->getFrontVectorInWorld() * 999.f, &position, &normalvec)) {
////                intersection->isDisabled = false;
////                intersection->position = position;
////                normalvec = normalize(normalvec);
////                float theta = -acos(dot(normalvec, vec3(0, 1, 0)));
////                vec3 axis = normalize(cross(normalvec, vec3(0, 1, 0)));
////                if (normalvec.y > 0.9)
////                    intersection->eulerAngles = vec3(0);
////                else if (normalvec.y < -0.9)
////                    intersection->eulerAngles = vec3(0, 0, 180);
////                else
////                    intersection->eulerAngles = glm_helper::getEularAngles(rotate(mat4(1), theta, axis));
////               intersection->eulerAngles.x = acos(dot((normalvec), vec3(0, 1, 0))) / M_PI * 180;
////               normal->position = intersection->position + normalvec;
////
////               intersection->getUpVectorInWorld()
////                //cout << "position: " << to_string(position) << endl;
////                //cout << "angle: " << to_string(intersection->eulerAngles) << endl;
////            }
////            else {
////                intersection->isDisabled = true;
////
//            engine->renderDirectionalLightShadowMap(directionalLight);
//
//            engine->render();
//
//        }
//    }
//}
//
//
//
//
//void destructClientCore(int signum) {
//    std::cout << "Game over" << std::endl;
//
////    ClientCore::Instance()->closeConnect();
//
//    ClientCore::Destructor();
//
//    exit(1);
//}
