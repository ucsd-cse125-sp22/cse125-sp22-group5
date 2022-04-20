// Developed by Kelin Lyu.

#include "KGLEngine/Engine.hpp"
#include "Game/Character/CharNode.hpp"

int main(int argc, char** argv) {
    
    Engine* engine = new Engine("KGLEngine", 0.8f, false, 0, NULL);
    engine->workingDirectory = "/Users/zifanzhang/Documents/Personal/UCSD/2022/spring/CSE125";
    engine->lockCursor();
    
    Skybox* skybox = new Skybox("/Resources/Development/Skybox/AR.png", "/Resources/Development/Skybox/AL.png",
                                "/Resources/Development/Skybox/AT.png", "/Resources/Development/Skybox/ABo.png",
                                "/Resources/Development/Skybox/AF.png", "/Resources/Development/Skybox/AB.png",
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
    spotLight->lightMask = 2;
    engine->addNode(spotLight);
    
    Node* sceneNode = new Node();
    engine->addNode(sceneNode);
    
    Texture* reflection = new Texture("/Resources/Development/PBR/RF.png", 0.0f, false);
    
    PBRShader* mapShader = new PBRShader(0.5f, 0.5f);
    mapShader->setReflectionMap(reflection);
    
    Node* map = new Node();
    map->loadUnitCube();
    map->geometries[0]->setShader(mapShader);
    map->position = vec3(0.0f, -0.1f, 0.0f);
    map->scale = vec3(100.0f, 0.2f, 100.0f);
    sceneNode->addChildNode(map);
    
    Texture* mixamoD = new Texture("/Resources/Development/CharacterTest/Textures/Mixamo D.png", 2.0f, true);
    Texture* mixamoN = new Texture("/Resources/Development/CharacterTest/Textures/Mixamo N.png", 2.0f, true);
    Texture* mixamoM = new Texture("/Resources/Development/CharacterTest/Textures/Mixamo M.png", 2.0f, true);
    
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
    charModel->scale = vec3(0.005f);
    charModel->loadModelFile("/Resources/Development/CharacterTest/MT.fbx");
    charModel->geometries[0]->setShader(mixamoMaterial);
    charModel->geometries[1]->isHidden = true;
    charModel->isDisabled = false;
    engine->addNode(character);
    character->setModel(charModel);
    
    character->addAnimator("idle", "/Resources/Development/CharacterTest/Animations/Idle.dae");
    character->stopAndPlay("idle", 0.0f, 0.0f);
    
    character->addAnimator("running", "/Resources/Development/CharacterTest/Animations/Running.dae");
    
    character->addAnimator("back run", "/Resources/Development/CharacterTest/Animations/Back Run.fbx");
    
    character->addAnimator("left strafe", "/Resources/Development/CharacterTest/Animations/Left Strafe.fbx");
    
    character->addAnimator("right strafe", "/Resources/Development/CharacterTest/Animations/Right Strafe.fbx");
    
    character->addAnimator("roll", "/Resources/Development/CharacterTest/Animations/Roll.dae");
    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine->addNode(baseNode);
    character->setUINode(baseNode);
    character->setName("Player1");
    
    vector<CharNode*> enemies;
    
    CharNode* enemy = character->copy(vec3(2.0, 0.0f, 2.0f));
    enemy->name = "enemy1";
    enemy->setEularAngle(vec3(0,90.0f,0));
    
    enemy->modelNode->getAnimator("idle")->play(0.0f, 0.0f);
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
    weapon->loadModelFile("/Resources/Development/CharacterTest/MT.fbx");
    weapon->scale = vec3(0.7);
    weapon->geometries[0]->setShader(mixamoMaterial);
    weapon->geometries[1]->isHidden = true;
    weaponNode->addChildNode(weapon);
    
    
    vector<Node*> characters;
    
    
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
                character->stopAndPlay("roll", 0.5f, 1.f);
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
            
            for (int i = 0; i < enemies.size(); i++){
                enemies[i]->updatePosition();
                enemies[i]->updateTransform();
                cout << to_string(enemies[i]->getWorldTransform()) << endl;
            }
        
            
            engine->render();
            
        }
    }
    
    delete(engine);
    return(0);
}
