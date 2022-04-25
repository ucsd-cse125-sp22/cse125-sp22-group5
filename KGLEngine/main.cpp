// Developed by Kelin Lyu.

#include "KGLEngine/Engine.hpp"
#include "Game/Character/CharNode.hpp"
#include "Game/Map/MapSystemManager.hpp"
#include "Game/Magic/StoneBlast.hpp"
#include "Game/Hitbox/HitController.hpp"

int main(int argc, char** argv) {
    
    Engine* engine = new Engine("KGLEngine", 0.8f, false, 0, NULL);
    engine->workingDirectory = ".";
    //engine->lockCursor();
    
    Skybox* skybox = new Skybox("/Resources/Game/Skybox/AR.png", "/Resources/Game/Skybox/AL.png",
                                "/Resources/Game/Skybox/AT.png", "/Resources/Game/Skybox/ABo.png",
                                "/Resources/Game/Skybox/AF.png", "/Resources/Game/Skybox/AB.png",
                                2.0f);
    engine->skybox = skybox;
    
    LightNode* pointLight = new LightNode(vec3(5.0f));
    pointLight->setPointLight(2.0f, 20.0f);
    pointLight->highlightIntensity = 0.0f;
    
    
    LightNode* ambientLight = new LightNode(vec3(0.5f));
    ambientLight->setAmbientLight();
    engine->addNode(ambientLight);
    
    LightNode* directionalLight = new LightNode(vec3(2.5f, 2.0f, 2.0f));
    directionalLight->setDirectionalLight();
    directionalLight->eulerAngles = vec3(0.0f, 135.0f, -45.0f);
    engine->addNode(directionalLight);
    
    LightNode* spotLight = new LightNode(vec3(20.0f, 0.5f, 0.5f));
    spotLight->setSpotLight(1.0f, 20.0f, 20.0f, 30.0f);
    spotLight->position = vec3(0.0f, 2.0f, 0.0f);
    spotLight->eulerAngles = vec3(0.0f, 0.0f, -30.0f);
    engine->addNode(spotLight);
    
    Node* sceneNode = new Node();
    engine->addNode(sceneNode);
    
    Texture* reflection = new Texture("/Resources/Game/PBR/RF.png", 0.0f, false);
    
    PBRShader* mapShader = new PBRShader(0.5f, 0.5f);
    mapShader->setReflectionMap(reflection);
//
//    Node* map = new Node();
//    map->loadUnitCube();
//    map->geometries[0]->setShader(mapShader);
//    map->position = vec3(0.0f, -0.1f, 0.0f);
//    map->scale = vec3(100.0f, 0.2f, 100.0f);
//    sceneNode->addChildNode(map);
//
//    MapBoxObject* mapBox = new MapBoxObject();
//    mapBox->size = map->scale;
//    mapBox->position = map->position ;
//    mapBox->yRotation = 0;
    
    Node* box = new Node();
    box->loadUnitCube();
    PBRShader* box1shader = new PBRShader(0.5, 0.5);
    box1shader->diffuseColor = vec4(0.3, 0.5, 1,1);
    box->geometries[0]->setShader(box1shader);
    box->position = vec3(0.0f, -0.1f, 0.0f);
    box->scale = vec3(100.0f, 0.2f, 100.0f);
    //box->eulerAngles.y = 30;
    sceneNode->addChildNode(box);
    
    MapBoxObject* mapBox2 = new MapBoxObject();
    mapBox2->size = box->scale;
    mapBox2->position = box->position ;
    mapBox2->eulerAngles = box->eulerAngles;
    
    Node* box2 = new Node();
    box2->loadUnitCube();
    PBRShader* box2shader = new PBRShader(0.5, 0.5);
    box2shader->diffuseColor = vec4(0.5, 1, 0.3,1);
    box2->geometries[0]->setShader(box2shader);
    box2->position = vec3(10.0f, 4.0f, 10.0f);
    box2->scale = vec3(20.0f, 8.f, 2.0f);
    box2->eulerAngles.y = 45;
    sceneNode->addChildNode(box2);
    
    MapBoxObject* mapBox3 = new MapBoxObject();
    mapBox3->size = box2->scale;
    mapBox3->position = box2->position ;
    mapBox3->eulerAngles = box2->eulerAngles;
    
    Node* box3 = new Node();
    box3->loadUnitCube();
    PBRShader* box3shader = new PBRShader(0.5, 0.5);
    box3shader->diffuseColor = vec4(1, 0.3, 0.5,0.5);
    box3->geometries[0]->setShader(box3shader);
    box3->position = vec3(-5.0f, 2, 5.0f);
    box3->scale = vec3(3.0f, 4.f, 5.0f);
    box3->eulerAngles = vec3(0, 60, 0);
    sceneNode->addChildNode(box3);
    
    MapBoxObject* mapBox4 = new MapBoxObject();
    mapBox4->size = box3->scale;
    mapBox4->position = box3->position ;
    mapBox4->eulerAngles = box3->eulerAngles;
    
    Node* box4 = new Node();
    box4->loadUnitCube();
    PBRShader* box4shader = new PBRShader(0.5, 0.5);
    box4shader->diffuseColor = vec4(0.9, 0.9, 0.3,1);
    box4->geometries[0]->setShader(box4shader);
    box4->position = vec3(5.0f, 1.0f, -5.0f);
    box4->scale = vec3(0.5f, 2.f, 1.0f);
    box4->eulerAngles = vec3(45, 45, 45);
    sceneNode->addChildNode(box4);
    
    MapBoxObject* mapBox5 = new MapBoxObject();
    mapBox5->size = box4->scale;
    mapBox5->position = box4->position ;
    mapBox5->eulerAngles = box4->eulerAngles;
    
    MapSystemManager* mapSystemManager = new MapSystemManager();
//    mapSystemManager->boxes.push_back(mapBox);
    mapSystemManager->boxes.push_back(mapBox2);
    mapSystemManager->boxes.push_back(mapBox3);
    mapSystemManager->boxes.push_back(mapBox4);
    mapSystemManager->boxes.push_back(mapBox5);
    
    Texture* mixamoD = new Texture("/Resources/Game/Character/Textures/Mixamo D.png", 2.0f, true);
    Texture* mixamoN = new Texture("/Resources/Game/Character/Textures/Mixamo N.png", 2.0f, true);
    Texture* mixamoM = new Texture("/Resources/Game/Character/Textures/Mixamo M.png", 2.0f, true);
    
    PBRShader* mixamoMaterial = new PBRShader(0.0f, 0.0f);
    mixamoMaterial->setDiffuseMap(mixamoD);
    mixamoMaterial->setNormalMap(mixamoN);
    mixamoMaterial->setMetallicMap(mixamoM);
    mixamoMaterial->metallicIntensity = 2.0f;
    mixamoMaterial->setRoughnessMap(mixamoM);
    mixamoMaterial->invertRoughness = true;
    mixamoMaterial->setReflectionMap(reflection);
    
    CharNode* character = new CharNode(vec3(0.0f, 0.0f, 0.0f));
    character->name = "main character";
    
    Node* controlNode = new Node();
    controlNode->position = vec3(0.0f, 1.0f, 0.0f);
    character->setControl(controlNode);
    
    CameraNode* cameraNode = new CameraNode(60.0f, 0.1f, 1000.0f);
    cameraNode->position = vec3(-2.0f, 0.0f, 0.0f);
    character->setCamera(cameraNode);
    
    cameraNode->addChildNode(pointLight);

    //engine->addNode(cameraNode);
    engine->mainCameraNode = cameraNode;
    
    Node* charModel = new Node();
    charModel->scale = vec3(0.5f);
    charModel->loadModelFile("/Resources/Game/Character/MT.fbx");
    charModel->geometries[0]->setShader(mixamoMaterial);
    charModel->geometries[1]->isHidden = true;
    charModel->isDisabled = false;
    engine->addNode(character);
    character->setModel(charModel);
    
    character->addAnimator("idle", "/Resources/Game/Character/Animations/Idle.dae");
    character->stopAndPlay("idle", 0.0f, 0.0f);
    
    character->addAnimator("running", "/Resources/Game/Character/Animations/Running.dae");
    
    character->addAnimator("back run", "/Resources/Game/Character/Animations/Back Run.fbx");
    
    character->addAnimator("left strafe", "/Resources/Game/Character/Animations/Left Strafe.fbx");
    
    character->addAnimator("right strafe", "/Resources/Game/Character/Animations/Right Strafe.fbx");
    
    character->addAnimator("roll", "/Resources/Game/Character/Animations/Roll.dae");
    
    character->addAnimator("cast magic 1", "/Resources/Game/Character/Animations/Cast Magic 1.fbx");
    
    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine->addNode(baseNode);
    character->setUINode(baseNode);
    character->setName("Player1");
    cout << to_string(character->getDownVectorInWorld()) << endl;
    
    vector<CharNode*> enemies;
    
    CharNode* enemy = character->copy(vec3(2.0, 0.0f, 2.0f));
    enemy->name = "enemy1";
    enemy->setEularAngle(vec3(0,90.0f,0));
    
    enemy->stopAndPlay("idle", 0.0f, 0.0f);
    engine->addNode(enemy);
    baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine->addNode(baseNode);
    enemy->setUINode(baseNode);
    enemy->setName("Enemy");
    enemies.push_back(enemy);
    
    Node* characterRightHand = character->generateBoneNode("RightHand");
    
    Node* weaponNode = new Node();
    weaponNode->scale = vec3(1);
    characterRightHand->addChildNode(weaponNode);
    
    
    Node* weapon = new Node();
    weapon->loadModelFile("/Resources/Game/Character/MT.fbx");
    weapon->scale = vec3(0.005);
    weapon->geometries[0]->setShader(mixamoMaterial);
    weapon->geometries[1]->isHidden = true;
    weaponNode->addChildNode(weapon);
    
//    Node* intersection = new Node();
//    intersection->loadModelFile("/Resources/Game/Character/MT.fbx");
//    intersection->scale = vec3(0.002);
//    intersection->geometries[0]->setShader(mixamoMaterial);
//    intersection->geometries[1]->isHidden = true;
//    engine->addNode(intersection);
//
//    Node* normal = new Node();
//    normal->loadUnitCube();
//    normal->scale = vec3(0.05);
//    PBRShader* normalShader = new PBRShader(0.5, 0.5);
//    normalShader->diffuseColor = vec4(0.2, 0.2, 1,1);
//    normal->geometries[0]->setShader(normalShader);
//    engine->addNode(normal);
    
    
    vector<Node*> characters;
    

    
    StoneBlast* stoneMagic = new StoneBlast();
    character->addMagics(stoneMagic, KEY_1);
    
    
    HitController enemyHitController;
    
    enemyHitController.magics.push_back(stoneMagic);
    enemyHitController.characters.push_back(enemy);
    
    while(engine->isRunning()) {
        if(engine->shouldUpdate()) {
            
            if(engine->input->wasKeyReleased(KEY_ESCAPE)) {
                engine->terminate();
            }
            
            if(engine->input->isPressingKey(KEY_W)) {
                character->moveFront();
            }else if(engine->input->isPressingKey(KEY_S)) {
                character->moveBack();
            }
            if(engine->input->isPressingKey(KEY_A)) {
                character->moveLeft();
            }else if(engine->input->isPressingKey(KEY_D)) {
                character->moveRight();
            }
            if(engine->input->wasKeyReleased(KEY_SPACE)){
                character->toggleLock(enemies);
            }
            
            
            if(engine->input->wasKeyReleased(KEY_G)){
                character->toggleLock(enemies);
            }
            character->moveCamera(engine->input->getMouseTranslation() * 0.1f);
            
            character->updatePosition();
            character->updateTransform();
            
            if(engine->input->wasKeyReleased(KEY_Q)){
                enemies[0]->characterTargetEulerAngles += vec3(0, 90, 0);
            }
            
            if(engine->input->wasKeyReleased(KEY_1)){
                character->castMagic(KEY_1);
            }
            
            for (int i = 0; i < enemies.size(); i++){
                enemies[i]->updatePosition();
                enemies[i]->updateTransform();
//                cout << to_string(enemies[i]->getWorldTransform()) << endl;
            }
            
            stoneMagic->updateMagic();
            
            enemyHitController.checkHit();
            
//            vec3 position;
//            vec3 normalvec;
//            if (mapSystemManager->hitTest(cameraNode->getWorldPosition(), cameraNode->getWorldPosition() +
//                                          cameraNode->getFrontVectorInWorld() * 999.f, &position, &normalvec)) {
//                intersection->isDisabled = false;
//                intersection->position = position;
//                normalvec = normalize(normalvec);
//                float theta = -acos(dot(normalvec, vec3(0, 1, 0)));
//                vec3 axis = normalize(cross(normalvec, vec3(0, 1, 0)));
//                if (normalvec.y > 0.9)
//                    intersection->eulerAngles = vec3(0);
//                else if (normalvec.y < -0.9)
//                    intersection->eulerAngles = vec3(0, 0, 180);
//                else
//                    intersection->eulerAngles = glm_helper::getEularAngles(rotate(mat4(1), theta, axis));
//               intersection->eulerAngles.x = acos(dot((normalvec), vec3(0, 1, 0))) / M_PI * 180;
//               normal->position = intersection->position + normalvec;
//
//               intersection->getUpVectorInWorld()
//                //cout << "position: " << to_string(position) << endl;
//                //cout << "angle: " << to_string(intersection->eulerAngles) << endl;
//            }
//            else {
//                intersection->isDisabled = true;
//            }
            
            
            engine->render();
            
        }
    }
    
    delete(engine);
    return(0);
}
