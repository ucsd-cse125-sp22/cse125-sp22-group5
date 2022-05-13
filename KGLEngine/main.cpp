// Developed by Kelin Lyu.

#include "KGLEngine/Engine.hpp"
#define MAINPROGRAM
#include "Game/includes.hpp"
#include "Game/magics.hpp"

int main(int argc, char** argv) {
    
    engine = new Engine("KGLEngine", 0.8f, 0, NULL);
    engine->workingDirectory = "/Users/zifanzhang/Documents/Personal/UCSD/2022/spring/CSE125/cse125-sp22-group5/KGLEngine";
    engine->lockCursor();
    
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
    spotLight->lightingBitMask = 2;
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
//
//    Node* box = new Node();
//    box->loadUnitCube();
//    PBRShader* box1shader = new PBRShader(0.5, 0.5);
//    box1shader->diffuseColor = vec4(0.3, 0.5, 1,1);
//    box->geometries[0]->setShader(box1shader);
//    box->position = vec3(0.0f, -0.1f, 0.0f);
//    box->eulerAngles = vec3(0, 30, 0);
//    box->scale = vec3(2.0f, 1.f, 2.0f);
//    sceneNode->addChildNode(box);
//
//    MapBoxObject* mapBox2 = new MapBoxObject();
//    mapBox2->size = box->scale;
//    mapBox2->position = box->position ;
//    mapBox2->eulerAngles = box->eulerAngles;
//
//    Node* box2 = new Node();
//    box2->loadUnitCube();
//    PBRShader* box2shader = new PBRShader(0.5, 0.5);
//    box2shader->diffuseColor = vec4(0.5, 1, 0.3,1);
//    box2->geometries[0]->setShader(box2shader);
//    box2->position = vec3(3.0f, -0.1f, -3.0f);
//    box2->scale = vec3(2.0f, 8.f, 4.0f);
//    box2->eulerAngles = vec3(0, 45, 0);
//    sceneNode->addChildNode(box2);
//
//    MapBoxObject* mapBox3 = new MapBoxObject();
//    mapBox3->size = box2->scale;
//    mapBox3->position = box2->position ;
//    mapBox3->eulerAngles = box2->eulerAngles;
//
//    Node* box3 = new Node();
//    box3->loadUnitCube();
//    PBRShader* box3shader = new PBRShader(0.5, 0.5);
//    box3shader->diffuseColor = vec4(1, 0.3, 0.5,0.5);
//    box3->geometries[0]->setShader(box3shader);
//    box3->position = vec3(-3.0f, 3.f, 3.0f);
//    box3->scale = vec3(3.0f, 4.f, 5.0f);
//    box3->eulerAngles = vec3(0, 60, 0);
//    sceneNode->addChildNode(box3);
//
//    MapBoxObject* mapBox4 = new MapBoxObject();
//    mapBox4->size = box3->scale;
//    mapBox4->position = box3->position ;
//    mapBox4->eulerAngles = box3->eulerAngles;
//
//    Node* box4 = new Node();
//    box4->loadUnitCube();
//    PBRShader* box4shader = new PBRShader(0.5, 0.5);
//    box4shader->diffuseColor = vec4(0.9, 0.9, 0.3,1);
//    box4->geometries[0]->setShader(box4shader);
//    box4->position = vec3(0.0f, 1.0f, 0.0f);
//    box4->scale = vec3(0.5f, 2.f, 1.0f);
//    box4->eulerAngles = vec3(45, 45, 45);
//    sceneNode->addChildNode(box4);
//
//    MapBoxObject* mapBox5 = new MapBoxObject();
//    mapBox5->size = box4->scale;
//    mapBox5->position = box4->position ;
//    mapBox5->eulerAngles = box4->eulerAngles;
//
    mapSystemManager = new MapSystemManager();
////    mapSystemManager->boxes.push_back(mapBox);
//    mapSystemManager->boxes.push_back(mapBox2);
//    mapSystemManager->boxes.push_back(mapBox3);
//    mapSystemManager->boxes.push_back(mapBox4);
//    mapSystemManager->boxes.push_back(mapBox5);
    
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
    
    CharNode* character = new CharNode(vec3(0.0f, -1.0f, 0.0f));
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

    character->addAnimator("smash ground", "/Resources/Game/Character/Animations/Smash Ground.fbx");

    UINode* baseNode = new UINode();
    baseNode->renderingOrder = 1000.0f;
    engine->addNode(baseNode);
    character->setUINode(baseNode);
    character->setName("Player1");
    cout << to_string(character->getDownVectorInWorld()) << endl;
    
    vector<CharNode*> enemies;
    
    CharNode* enemy = character->copy(vec3(2.0, -1.0f, 2.0f));
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
    
    //Node* characterRightHand = character->generateBoneNode("RightHand");
    
//    Node* weaponNode = new Node();
//    weaponNode->scale = vec3(1);
//    characterRightHand->addChildNode(weaponNode);
    

    
//
//    Node* weapon = new Node();
//    weapon->loadModelFile("/Resources/Game/Character/MT.fbx");
//    weapon->scale = vec3(0.005);
//    weapon->geometries[0]->setShader(mixamoMaterial);
//    weapon->geometries[1]->isHidden = true;
//    weaponNode->addChildNode(weapon);
//
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
    


    MapBoxObject* mapBoxObject1 = new MapBoxObject();
    mapBoxObject1->type = 1;
    mapBoxObject1->size = vec3(20.0f, 20.0f, 20.0f);
    mapBoxObject1->position = vec3(0.0f, 9.0f, 60.0f);
    mapBoxObject1->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject1);
    MapBoxObject* mapBoxObject2 = new MapBoxObject();
    mapBoxObject2->type = 0;
    mapBoxObject2->size = vec3(20.0f, 1.0f, 40.0f);
    mapBoxObject2->position = vec3(0.0f, -1.5f, 30.0f);
    mapBoxObject2->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject2);
    MapBoxObject* mapBoxObject3 = new MapBoxObject();
    mapBoxObject3->type = 0;
    mapBoxObject3->size = vec3(100.0f, 1.0f, 20.0f);
    mapBoxObject3->position = vec3(0.0f, -1.5f, 0.0f);
    mapBoxObject3->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject3);
    MapBoxObject* mapBoxObject4 = new MapBoxObject();
    mapBoxObject4->type = 0;
    mapBoxObject4->size = vec3(20.0f, 1.0f, 40.0f);
    mapBoxObject4->position = vec3(0.0f, -1.5f, -30.0f);
    mapBoxObject4->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject4);
    MapBoxObject* mapBoxObject5 = new MapBoxObject();
    mapBoxObject5->type = 0;
    mapBoxObject5->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject5->position = vec3(36.339744567871094f, -1.5f, 13.65999984741211f);
    mapBoxObject5->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject5);
    MapBoxObject* mapBoxObject6 = new MapBoxObject();
    mapBoxObject6->type = 0;
    mapBoxObject6->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject6->position = vec3(26.200000762939453f, -1.5f, 27.0f);
    mapBoxObject6->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject6);
    MapBoxObject* mapBoxObject7 = new MapBoxObject();
    mapBoxObject7->type = 0;
    mapBoxObject7->size = vec3(19.999998092651367f, 1.0f, 20.0f);
    mapBoxObject7->position = vec3(13.65999984741211f, -1.5f, 36.34000015258789f);
    mapBoxObject7->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject7);
    MapBoxObject* mapBoxObject8 = new MapBoxObject();
    mapBoxObject8->type = 0;
    mapBoxObject8->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject8->position = vec3(20.0f, -1.5f, 20.0f);
    mapBoxObject8->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject8);
    MapBoxObject* mapBoxObject9 = new MapBoxObject();
    mapBoxObject9->type = 0;
    mapBoxObject9->size = vec3(19.999998092651367f, 1.0f, 20.0f);
    mapBoxObject9->position = vec3(-13.600000381469727f, -1.5f, -36.33000183105469f);
    mapBoxObject9->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject9);
    MapBoxObject* mapBoxObject10 = new MapBoxObject();
    mapBoxObject10->type = 0;
    mapBoxObject10->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject10->position = vec3(-36.34000015258789f, -1.5f, -13.600000381469727f);
    mapBoxObject10->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject10);
    MapBoxObject* mapBoxObject11 = new MapBoxObject();
    mapBoxObject11->type = 0;
    mapBoxObject11->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject11->position = vec3(-26.95877456665039f, -1.5f, -26.158771514892578f);
    mapBoxObject11->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject11);
    MapBoxObject* mapBoxObject12 = new MapBoxObject();
    mapBoxObject12->type = 0;
    mapBoxObject12->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject12->position = vec3(-20.0f, -1.5f, -20.0f);
    mapBoxObject12->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject12);
    MapBoxObject* mapBoxObject13 = new MapBoxObject();
    mapBoxObject13->type = 0;
    mapBoxObject13->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject13->position = vec3(20.0f, -1.5f, -20.0f);
    mapBoxObject13->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject13);
    MapBoxObject* mapBoxObject14 = new MapBoxObject();
    mapBoxObject14->type = 0;
    mapBoxObject14->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject14->position = vec3(-20.0f, -1.5f, 20.0f);
    mapBoxObject14->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject14);
    MapBoxObject* mapBoxObject15 = new MapBoxObject();
    mapBoxObject15->type = 0;
    mapBoxObject15->size = vec3(19.999998092651367f, 1.0f, 20.0f);
    mapBoxObject15->position = vec3(-13.731363296508789f, -1.5f, 36.58491516113281f);
    mapBoxObject15->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject15);
    MapBoxObject* mapBoxObject16 = new MapBoxObject();
    mapBoxObject16->type = 0;
    mapBoxObject16->size = vec3(19.999998092651367f, 1.0f, 20.0f);
    mapBoxObject16->position = vec3(-36.34000015258789f, -1.5f, 13.601505279541016f);
    mapBoxObject16->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject16);
    MapBoxObject* mapBoxObject17 = new MapBoxObject();
    mapBoxObject17->type = 0;
    mapBoxObject17->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject17->position = vec3(-26.481189727783203f, -1.5f, 26.653076171875f);
    mapBoxObject17->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject17);
    MapBoxObject* mapBoxObject18 = new MapBoxObject();
    mapBoxObject18->type = 0;
    mapBoxObject18->size = vec3(19.999998092651367f, 1.0f, 20.0f);
    mapBoxObject18->position = vec3(13.596307754516602f, -1.5f, -36.33232116699219f);
    mapBoxObject18->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject18);
    MapBoxObject* mapBoxObject19 = new MapBoxObject();
    mapBoxObject19->type = 0;
    mapBoxObject19->size = vec3(20.0f, 1.0f, 20.0f);
    mapBoxObject19->position = vec3(26.81570053100586f, -1.5f, -26.241455078125f);
    mapBoxObject19->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject19);
    MapBoxObject* mapBoxObject20 = new MapBoxObject();
    mapBoxObject20->type = 0;
    mapBoxObject20->size = vec3(19.999998092651367f, 1.0f, 20.0f);
    mapBoxObject20->position = vec3(36.2993278503418f, -1.5f, -13.646175384521484f);
    mapBoxObject20->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject20);
    MapBoxObject* mapBoxObject21 = new MapBoxObject();
    mapBoxObject21->type = 1;
    mapBoxObject21->size = vec3(20.0f, 20.0f, 20.0f);
    mapBoxObject21->position = vec3(0.0f, 9.0f, -60.0f);
    mapBoxObject21->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject21);
    MapBoxObject* mapBoxObject22 = new MapBoxObject();
    mapBoxObject22->type = 1;
    mapBoxObject22->size = vec3(5.0f, 30.0f, 20.0f);
    mapBoxObject22->position = vec3(-19.679931640625f, 13.0f, 47.426387786865234f);
    mapBoxObject22->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject22);
    MapBoxObject* mapBoxObject23 = new MapBoxObject();
    mapBoxObject23->type = 1;
    mapBoxObject23->size = vec3(5.0f, 30.0f, 20.0f);
    mapBoxObject23->position = vec3(-35.30475616455078f, 13.0f, 35.362510681152344f);
    mapBoxObject23->eulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject23);
    MapBoxObject* mapBoxObject24 = new MapBoxObject();
    mapBoxObject24->type = 1;
    mapBoxObject24->size = vec3(20.0f, 30.0f, 5.0f);
    mapBoxObject24->position = vec3(-47.292022705078125f, 13.0f, 19.538402557373047f);
    mapBoxObject24->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject24);
    MapBoxObject* mapBoxObject25 = new MapBoxObject();
    mapBoxObject25->type = 1;
    mapBoxObject25->size = vec3(19.9999942779541f, 30.0f, 4.999998569488525f);
    mapBoxObject25->position = vec3(-52.50025177001953f, 13.0f, -0.058162689208984375f);
    mapBoxObject25->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject25);
    MapBoxObject* mapBoxObject26 = new MapBoxObject();
    mapBoxObject26->type = 1;
    mapBoxObject26->size = vec3(20.0f, 30.0f, 5.0f);
    mapBoxObject26->position = vec3(-47.196224212646484f, 13.0f, -19.518991470336914f);
    mapBoxObject26->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject26);
    MapBoxObject* mapBoxObject27 = new MapBoxObject();
    mapBoxObject27->type = 1;
    mapBoxObject27->size = vec3(5.0f, 30.0f, 20.0f);
    mapBoxObject27->position = vec3(-35.77626037597656f, 13.0f, -34.86589431762695f);
    mapBoxObject27->eulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject27);
    MapBoxObject* mapBoxObject28 = new MapBoxObject();
    mapBoxObject28->type = 1;
    mapBoxObject28->size = vec3(5.0f, 30.0f, 20.0f);
    mapBoxObject28->position = vec3(-19.81863021850586f, 13.0f, -47.04525375366211f);
    mapBoxObject28->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject28);
    MapBoxObject* mapBoxObject29 = new MapBoxObject();
    mapBoxObject29->type = 1;
    mapBoxObject29->size = vec3(5.0f, 30.0f, 5.0f);
    mapBoxObject29->position = vec3(14.256914138793945f, 14.0f, 40.71234130859375f);
    mapBoxObject29->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject29);
    MapBoxObject* mapBoxObject30 = new MapBoxObject();
    mapBoxObject30->type = 1;
    mapBoxObject30->size = vec3(29.999935150146484f, 2.999999523162842f, 16.999998092651367f);
    mapBoxObject30->position = vec3(-36.28617477416992f, -1.132124423980713f, -18.673717498779297f);
    mapBoxObject30->eulerAngles = vec3(9.99999970909292f, 60.00000849984128f, -1.707547699614187e-06f);
    mapSystemManager->boxes.push_back(mapBoxObject30);
    MapBoxObject* mapBoxObject31 = new MapBoxObject();
    mapBoxObject31->type = 1;
    mapBoxObject31->size = vec3(5.0f, 30.0f, 5.0f);
    mapBoxObject31->position = vec3(27.738876342773438f, 14.0f, 30.06119155883789f);
    mapBoxObject31->eulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject31);
    MapBoxObject* mapBoxObject32 = new MapBoxObject();
    mapBoxObject32->type = 1;
    mapBoxObject32->size = vec3(5.0f, 7.0f, 5.0f);
    mapBoxObject32->position = vec3(27.201324462890625f, 2.5f, -26.600440979003906f);
    mapBoxObject32->eulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject32);
    MapBoxObject* mapBoxObject33 = new MapBoxObject();
    mapBoxObject33->type = 1;
    mapBoxObject33->size = vec3(9.999994277954102f, 2.5f, 14.99999713897705f);
    mapBoxObject33->position = vec3(-19.002153396606445f, 0.24999995529651642f, 24.259979248046875f);
    mapBoxObject33->eulerAngles = vec3(0.0f, 59.99999483946294f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject33);
    MapBoxObject* mapBoxObject34 = new MapBoxObject();
    mapBoxObject34->type = 1;
    mapBoxObject34->size = vec3(4.999887943267822f, 4.999917030334473f, 22.999780654907227f);
    mapBoxObject34->position = vec3(34.57914733886719f, 2.5202579498291016f, -17.966392517089844f);
    mapBoxObject34->eulerAngles = vec3(13.46300038716412f, 38.7630003512636f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject34);
    MapBoxObject* mapBoxObject35 = new MapBoxObject();
    mapBoxObject35->type = 1;
    mapBoxObject35->size = vec3(9.999835968017578f, 2.499964952468872f, 14.999848365783691f);
    mapBoxObject35->position = vec3(12.881000518798828f, 0.24999994039535522f, -10.011907577514648f);
    mapBoxObject35->eulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject35);
    MapBoxObject* mapBoxObject36 = new MapBoxObject();
    mapBoxObject36->type = 1;
    mapBoxObject36->size = vec3(4.999978542327881f, 3.000000238418579f, 17.00000762939453f);
    mapBoxObject36->position = vec3(-5.298661231994629f, -1.336275339126587f, 31.8536376953125f);
    mapBoxObject36->eulerAngles = vec3(8.999993420258647f, 60.00000849984128f, -5.122643913064559e-06f);
    mapSystemManager->boxes.push_back(mapBoxObject36);
    MapBoxObject* mapBoxObject37 = new MapBoxObject();
    mapBoxObject37->type = 1;
    mapBoxObject37->size = vec3(0.5f, 2.0f, 5.0f);
    mapBoxObject37->position = vec3(10.21187973022461f, 0.0f, 21.193662643432617f);
    mapBoxObject37->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject37);
    MapBoxObject* mapBoxObject38 = new MapBoxObject();
    mapBoxObject38->type = 1;
    mapBoxObject38->size = vec3(0.4999998211860657f, 1.0f, 9.99999713897705f);
    mapBoxObject38->position = vec3(25.113908767700195f, -0.5f, 11.59774398803711f);
    mapBoxObject38->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject38);
    MapBoxObject* mapBoxObject39 = new MapBoxObject();
    mapBoxObject39->type = 2;
    mapBoxObject39->size = vec3(0.5f, 1.0f, 10.0f);
    mapBoxObject39->position = vec3(4.626926422119141f, -0.5f, 7.29351806640625f);
    mapBoxObject39->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject39);
    MapBoxObject* mapBoxObject40 = new MapBoxObject();
    mapBoxObject40->type = 1;
    mapBoxObject40->size = vec3(5.000000953674316f, 3.0f, 17.0f);
    mapBoxObject40->position = vec3(5.108200550079346f, -1.3108752965927124f, -21.101150512695312f);
    mapBoxObject40->eulerAngles = vec3(-9.000000250447817f, 19.99999771063855f, 5.6785429905125e-07f);
    mapSystemManager->boxes.push_back(mapBoxObject40);
    MapBoxObject* mapBoxObject41 = new MapBoxObject();
    mapBoxObject41->type = 2;
    mapBoxObject41->size = vec3(0.5f, 2.0f, 10.0f);
    mapBoxObject41->position = vec3(-6.175685882568359f, 0.0f, -4.580935478210449f);
    mapBoxObject41->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject41);
    MapBoxObject* mapBoxObject42 = new MapBoxObject();
    mapBoxObject42->type = 1;
    mapBoxObject42->size = vec3(0.5f, 2.0f, 7.0f);
    mapBoxObject42->position = vec3(-10.48333740234375f, 0.0f, 9.90719985961914f);
    mapBoxObject42->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject42);
    MapBoxObject* mapBoxObject43 = new MapBoxObject();
    mapBoxObject43->type = 1;
    mapBoxObject43->size = vec3(0.4999997913837433f, 1.0f, 3.999999761581421f);
    mapBoxObject43->position = vec3(2.3769264221191406f, -0.5f, 6.538968086242676f);
    mapBoxObject43->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject43);
    MapBoxObject* mapBoxObject44 = new MapBoxObject();
    mapBoxObject44->type = 1;
    mapBoxObject44->size = vec3(0.5f, 2.0f, 5.0f);
    mapBoxObject44->position = vec3(-9.59457778930664f, 0.0f, -1.830935001373291f);
    mapBoxObject44->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject44);
    MapBoxObject* mapBoxObject45 = new MapBoxObject();
    mapBoxObject45->type = 2;
    mapBoxObject45->size = vec3(4.9999680519104f, 0.9999958872795105f, 6.999967098236084f);
    mapBoxObject45->position = vec3(-12.002592086791992f, -0.4999999701976776f, -18.14734649658203f);
    mapBoxObject45->eulerAngles = vec3(0.0f, 33.53639957949186f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject45);
    MapBoxObject* mapBoxObject46 = new MapBoxObject();
    mapBoxObject46->type = 2;
    mapBoxObject46->size = vec3(2.9999992847442627f, 2.0f, 3.9999990463256836f);
    mapBoxObject46->position = vec3(-7.776100158691406f, 0.0f, -15.409856796264648f);
    mapBoxObject46->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject46);
    MapBoxObject* mapBoxObject47 = new MapBoxObject();
    mapBoxObject47->type = 2;
    mapBoxObject47->size = vec3(4.999841690063477f, 4.0f, 5.0f);
    mapBoxObject47->position = vec3(40.72988510131836f, 0.9999867081642151f, 2.3642375469207764f);
    mapBoxObject47->eulerAngles = vec3(179.999991348578f, 20.135100559968695f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject47);
    MapBoxObject* mapBoxObject48 = new MapBoxObject();
    mapBoxObject48->type = 2;
    mapBoxObject48->size = vec3(4.999831199645996f, 3.0f, 4.9999918937683105f);
    mapBoxObject48->position = vec3(39.35308837890625f, 0.5000176429748535f, 7.0984416007995605f);
    mapBoxObject48->eulerAngles = vec3(179.999991348578f, -14.096251130778096f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject48);
    MapBoxObject* mapBoxObject49 = new MapBoxObject();
    mapBoxObject49->type = 2;
    mapBoxObject49->size = vec3(4.999912738800049f, 4.0f, 5.00007438659668f);
    mapBoxObject49->position = vec3(39.572853088378906f, 0.9999866485595703f, 11.962966918945312f);
    mapBoxObject49->eulerAngles = vec3(179.999991348578f, -71.10730310925103f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject49);
    MapBoxObject* mapBoxObject50 = new MapBoxObject();
    mapBoxObject50->type = 2;
    mapBoxObject50->size = vec3(3.0f, 2.999999761581421f, 3.0f);
    mapBoxObject50->position = vec3(-13.633177757263184f, 2.999999761581421f, 23.612285614013672f);
    mapBoxObject50->eulerAngles = vec3(179.999991348578f, -71.10728261868353f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject50);
    MapBoxObject* mapBoxObject51 = new MapBoxObject();
    mapBoxObject51->type = 2;
    mapBoxObject51->size = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    mapBoxObject51->position = vec3(-21.799108505249023f, 2.0f, 18.328943252563477f);
    mapBoxObject51->eulerAngles = vec3(179.999991348578f, -23.733391063798567f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject51);
    MapBoxObject* mapBoxObject52 = new MapBoxObject();
    mapBoxObject52->type = 2;
    mapBoxObject52->size = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    mapBoxObject52->position = vec3(-21.782814025878906f, 2.0f, 18.312650680541992f);
    mapBoxObject52->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject52);
    MapBoxObject* mapBoxObject53 = new MapBoxObject();
    mapBoxObject53->type = 2;
    mapBoxObject53->size = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    mapBoxObject53->position = vec3(-21.2570743560791f, 2.0f, 19.338041305541992f);
    mapBoxObject53->eulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject53);
    MapBoxObject* mapBoxObject54 = new MapBoxObject();
    mapBoxObject54->type = 2;
    mapBoxObject54->size = vec3(1.0000003576278687f, 0.9999999403953552f, 1.0000003576278687f);
    mapBoxObject54->position = vec3(-19.967870712280273f, 1.9999998807907104f, 19.419044494628906f);
    mapBoxObject54->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject54);
    MapBoxObject* mapBoxObject55 = new MapBoxObject();
    mapBoxObject55->type = 2;
    mapBoxObject55->size = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    mapBoxObject55->position = vec3(-18.6903018951416f, 2.0f, 20.22953224182129f);
    mapBoxObject55->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject55);
    MapBoxObject* mapBoxObject56 = new MapBoxObject();
    mapBoxObject56->type = 2;
    mapBoxObject56->size = vec3(1.0000005960464478f, 0.9999999403953552f, 1.0000005960464478f);
    mapBoxObject56->position = vec3(-22.858861923217773f, 1.9999998807907104f, 18.720481872558594f);
    mapBoxObject56->eulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject56);
    MapBoxObject* mapBoxObject57 = new MapBoxObject();
    mapBoxObject57->type = 2;
    mapBoxObject57->size = vec3(9.0f, 4.0f, 5.0f);
    mapBoxObject57->position = vec3(-22.26280975341797f, 0.9999867081642151f, -0.05115675926208496f);
    mapBoxObject57->eulerAngles = vec3(179.999991348578f, 0.0f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject57);
    MapBoxObject* mapBoxObject58 = new MapBoxObject();
    mapBoxObject58->type = 1;
    mapBoxObject58->size = vec3(20.0f, 20.0f, 20.0f);
    mapBoxObject58->position = vec3(0.0f, 9.0f, 60.0f);
    mapBoxObject58->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject58);
    MapBoxObject* mapBoxObject59 = new MapBoxObject();
    mapBoxObject59->type = 2;
    mapBoxObject59->size = vec3(2.999969720840454f, 1.9999911785125732f, 3.999952793121338f);
    mapBoxObject59->position = vec3(-17.134122848510742f, 0.0f, 2.518460988998413f);
    mapBoxObject59->eulerAngles = vec3(0.0f, 60.457330645908655f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject59);
    MapBoxObject* mapBoxObject60 = new MapBoxObject();
    mapBoxObject60->type = 2;
    mapBoxObject60->size = vec3(4.999832630157471f, 3.0f, 4.999993324279785f);
    mapBoxObject60->position = vec3(18.351093292236328f, 0.5000176429748535f, 8.719722747802734f);
    mapBoxObject60->eulerAngles = vec3(179.999991348578f, -14.096249423230805f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject60);
    MapBoxObject* mapBoxObject61 = new MapBoxObject();
    mapBoxObject61->type = 1;
    mapBoxObject61->size = vec3(0.5f, 2.0f, 7.0f);
    mapBoxObject61->position = vec3(-10.890523910522461f, 0.0f, -35.301090240478516f);
    mapBoxObject61->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject61);
    MapBoxObject* mapBoxObject62 = new MapBoxObject();
    mapBoxObject62->type = 1;
    mapBoxObject62->size = vec3(4.0f, 3.0f, 2.0f);
    mapBoxObject62->position = vec3(-49.953739166259766f, 0.5f, 5.168451309204102f);
    mapBoxObject62->eulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject62);
    MapBoxObject* mapBoxObject63 = new MapBoxObject();
    mapBoxObject63->type = 1;
    mapBoxObject63->size = vec3(4.0f, 7.0f, 1.999990463256836f);
    mapBoxObject63->position = vec3(-44.0306396484375f, 2.5f, 20.40106964111328f);
    mapBoxObject63->eulerAngles = vec3(0.0f, -45.95227305651143f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject63);
    MapBoxObject* mapBoxObject64 = new MapBoxObject();
    mapBoxObject64->type = 1;
    mapBoxObject64->size = vec3(4.999993324279785f, 6.999980926513672f, 4.999993324279785f);
    mapBoxObject64->position = vec3(14.83809757232666f, 2.499999761581421f, -37.63517761230469f);
    mapBoxObject64->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject64);
    MapBoxObject* mapBoxObject65 = new MapBoxObject();
    mapBoxObject65->type = 2;
    mapBoxObject65->size = vec3(3.000000238418579f, 2.999999761581421f, 3.000000238418579f);
    mapBoxObject65->position = vec3(17.829620361328125f, 2.9999845027923584f, -9.80679702758789f);
    mapBoxObject65->eulerAngles = vec3(179.999991348578f, -71.10726895830518f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject65);
    MapBoxObject* mapBoxObject66 = new MapBoxObject();
    mapBoxObject66->type = 2;
    mapBoxObject66->size = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    mapBoxObject66->position = vec3(13.097940444946289f, 1.9999847412109375f, -6.686174392700195f);
    mapBoxObject66->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject66);
    MapBoxObject* mapBoxObject67 = new MapBoxObject();
    mapBoxObject67->type = 2;
    mapBoxObject67->size = vec3(1.0000169277191162f, 0.9999843239784241f, 1.0000169277191162f);
    mapBoxObject67->position = vec3(7.924259662628174f, 1.9999691247940063f, -6.570480823516846f);
    mapBoxObject67->eulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject67);
    MapBoxObject* mapBoxObject68 = new MapBoxObject();
    mapBoxObject68->type = 2;
    mapBoxObject68->size = vec3(1.0000169277191162f, 0.9999842643737793f, 1.0000169277191162f);
    mapBoxObject68->position = vec3(9.213461875915527f, 1.9999690055847168f, -6.489477634429932f);
    mapBoxObject68->eulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject68);
    MapBoxObject* mapBoxObject69 = new MapBoxObject();
    mapBoxObject69->type = 2;
    mapBoxObject69->size = vec3(1.0000022649765015f, 0.9999843239784241f, 1.0000022649765015f);
    mapBoxObject69->position = vec3(10.4910306930542f, 1.9999691247940063f, -5.678989887237549f);
    mapBoxObject69->eulerAngles = vec3(0.0f, -84.12957785625727f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject69);
    MapBoxObject* mapBoxObject70 = new MapBoxObject();
    mapBoxObject70->type = 2;
    mapBoxObject70->size = vec3(1.0000008344650269f, 0.9999999403953552f, 1.0000008344650269f);
    mapBoxObject70->position = vec3(12.021892547607422f, 1.999984622001648f, -6.278343200683594f);
    mapBoxObject70->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    mapSystemManager->boxes.push_back(mapBoxObject70);
    MapBoxObject* mapBoxObject71 = new MapBoxObject();
    mapBoxObject71->type = 1;
    mapBoxObject71->size = vec3(3.9999682903289795f, 2.9999806880950928f, 1.9999841451644897f);
    mapBoxObject71->position = vec3(-23.76885414123535f, 0.4999694526195526f, 41.0047492980957f);
    mapBoxObject71->eulerAngles = vec3(0.0f, 90.00000250447816f, 0.0f);
    mapSystemManager->boxes.push_back(mapBoxObject71);




    PBRShader* cubeShader = new PBRShader(0.5f, 0.5f);
    Node* testNode1 = new Node();
    testNode1->loadUnitCube();
    testNode1->geometries[0]->setShader(cubeShader);
    testNode1->scale = vec3(20.0f, 20.0f, 20.0f);
    testNode1->position = vec3(0.0f, 9.0f, 60.0f);
    testNode1->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode1);
    Node* testNode2 = new Node();
    testNode2->loadUnitCube();
    testNode2->geometries[0]->setShader(cubeShader);
    testNode2->scale = vec3(20.0f, 1.0f, 40.0f);
    testNode2->position = vec3(0.0f, -1.5f, 30.0f);
    testNode2->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode2);
    Node* testNode3 = new Node();
    testNode3->loadUnitCube();
    testNode3->geometries[0]->setShader(cubeShader);
    testNode3->scale = vec3(100.0f, 1.0f, 20.0f);
    testNode3->position = vec3(0.0f, -1.5f, 0.0f);
    testNode3->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode3);
    Node* testNode4 = new Node();
    testNode4->loadUnitCube();
    testNode4->geometries[0]->setShader(cubeShader);
    testNode4->scale = vec3(20.0f, 1.0f, 40.0f);
    testNode4->position = vec3(0.0f, -1.5f, -30.0f);
    testNode4->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode4);
    Node* testNode5 = new Node();
    testNode5->loadUnitCube();
    testNode5->geometries[0]->setShader(cubeShader);
    testNode5->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode5->position = vec3(36.339744567871094f, -1.5f, 13.65999984741211f);
    testNode5->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode5);
    Node* testNode6 = new Node();
    testNode6->loadUnitCube();
    testNode6->geometries[0]->setShader(cubeShader);
    testNode6->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode6->position = vec3(26.200000762939453f, -1.5f, 27.0f);
    testNode6->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    engine->addNode(testNode6);
    Node* testNode7 = new Node();
    testNode7->loadUnitCube();
    testNode7->geometries[0]->setShader(cubeShader);
    testNode7->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode7->position = vec3(13.65999984741211f, -1.5f, 36.34000015258789f);
    testNode7->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode7);
    Node* testNode8 = new Node();
    testNode8->loadUnitCube();
    testNode8->geometries[0]->setShader(cubeShader);
    testNode8->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode8->position = vec3(20.0f, -1.5f, 20.0f);
    testNode8->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode8);
    Node* testNode9 = new Node();
    testNode9->loadUnitCube();
    testNode9->geometries[0]->setShader(cubeShader);
    testNode9->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode9->position = vec3(-13.600000381469727f, -1.5f, -36.33000183105469f);
    testNode9->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode9);
    Node* testNode10 = new Node();
    testNode10->loadUnitCube();
    testNode10->geometries[0]->setShader(cubeShader);
    testNode10->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode10->position = vec3(-36.34000015258789f, -1.5f, -13.600000381469727f);
    testNode10->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode10);
    Node* testNode11 = new Node();
    testNode11->loadUnitCube();
    testNode11->geometries[0]->setShader(cubeShader);
    testNode11->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode11->position = vec3(-26.95877456665039f, -1.5f, -26.158771514892578f);
    testNode11->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    engine->addNode(testNode11);
    Node* testNode12 = new Node();
    testNode12->loadUnitCube();
    testNode12->geometries[0]->setShader(cubeShader);
    testNode12->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode12->position = vec3(-20.0f, -1.5f, -20.0f);
    testNode12->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode12);
    Node* testNode13 = new Node();
    testNode13->loadUnitCube();
    testNode13->geometries[0]->setShader(cubeShader);
    testNode13->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode13->position = vec3(20.0f, -1.5f, -20.0f);
    testNode13->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode13);
    Node* testNode14 = new Node();
    testNode14->loadUnitCube();
    testNode14->geometries[0]->setShader(cubeShader);
    testNode14->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode14->position = vec3(-20.0f, -1.5f, 20.0f);
    testNode14->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode14);
    Node* testNode15 = new Node();
    testNode15->loadUnitCube();
    testNode15->geometries[0]->setShader(cubeShader);
    testNode15->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode15->position = vec3(-13.731363296508789f, -1.5f, 36.58491516113281f);
    testNode15->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode15);
    Node* testNode16 = new Node();
    testNode16->loadUnitCube();
    testNode16->geometries[0]->setShader(cubeShader);
    testNode16->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode16->position = vec3(-36.34000015258789f, -1.5f, 13.601505279541016f);
    testNode16->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode16);
    Node* testNode17 = new Node();
    testNode17->loadUnitCube();
    testNode17->geometries[0]->setShader(cubeShader);
    testNode17->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode17->position = vec3(-26.481189727783203f, -1.5f, 26.653076171875f);
    testNode17->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    engine->addNode(testNode17);
    Node* testNode18 = new Node();
    testNode18->loadUnitCube();
    testNode18->geometries[0]->setShader(cubeShader);
    testNode18->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode18->position = vec3(13.596307754516602f, -1.5f, -36.33232116699219f);
    testNode18->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode18);
    Node* testNode19 = new Node();
    testNode19->loadUnitCube();
    testNode19->geometries[0]->setShader(cubeShader);
    testNode19->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode19->position = vec3(26.81570053100586f, -1.5f, -26.241455078125f);
    testNode19->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    engine->addNode(testNode19);
    Node* testNode20 = new Node();
    testNode20->loadUnitCube();
    testNode20->geometries[0]->setShader(cubeShader);
    testNode20->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode20->position = vec3(36.2993278503418f, -1.5f, -13.646175384521484f);
    testNode20->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode20);
    Node* testNode21 = new Node();
    testNode21->loadUnitCube();
    testNode21->geometries[0]->setShader(cubeShader);
    testNode21->scale = vec3(20.0f, 20.0f, 20.0f);
    testNode21->position = vec3(0.0f, 9.0f, -60.0f);
    testNode21->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode21);
    Node* testNode22 = new Node();
    testNode22->loadUnitCube();
    testNode22->geometries[0]->setShader(cubeShader);
    testNode22->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode22->position = vec3(-19.679931640625f, 13.0f, 47.426387786865234f);
    testNode22->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode22);
    Node* testNode23 = new Node();
    testNode23->loadUnitCube();
    testNode23->geometries[0]->setShader(cubeShader);
    testNode23->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode23->position = vec3(-35.30475616455078f, 13.0f, 35.362510681152344f);
    testNode23->eulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    engine->addNode(testNode23);
    Node* testNode24 = new Node();
    testNode24->loadUnitCube();
    testNode24->geometries[0]->setShader(cubeShader);
    testNode24->scale = vec3(20.0f, 30.0f, 5.0f);
    testNode24->position = vec3(-47.292022705078125f, 13.0f, 19.538402557373047f);
    testNode24->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode24);
    Node* testNode25 = new Node();
    testNode25->loadUnitCube();
    testNode25->geometries[0]->setShader(cubeShader);
    testNode25->scale = vec3(19.9999942779541f, 30.0f, 4.999998569488525f);
    testNode25->position = vec3(-52.50025177001953f, 13.0f, -0.058162689208984375f);
    testNode25->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode25);
    Node* testNode26 = new Node();
    testNode26->loadUnitCube();
    testNode26->geometries[0]->setShader(cubeShader);
    testNode26->scale = vec3(20.0f, 30.0f, 5.0f);
    testNode26->position = vec3(-47.196224212646484f, 13.0f, -19.518991470336914f);
    testNode26->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode26);
    Node* testNode27 = new Node();
    testNode27->loadUnitCube();
    testNode27->geometries[0]->setShader(cubeShader);
    testNode27->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode27->position = vec3(-35.77626037597656f, 13.0f, -34.86589431762695f);
    testNode27->eulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    engine->addNode(testNode27);
    Node* testNode28 = new Node();
    testNode28->loadUnitCube();
    testNode28->geometries[0]->setShader(cubeShader);
    testNode28->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode28->position = vec3(-19.81863021850586f, 13.0f, -47.04525375366211f);
    testNode28->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode28);
    Node* testNode29 = new Node();
    testNode29->loadUnitCube();
    testNode29->geometries[0]->setShader(cubeShader);
    testNode29->scale = vec3(5.0f, 30.0f, 5.0f);
    testNode29->position = vec3(14.256914138793945f, 14.0f, 40.71234130859375f);
    testNode29->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    engine->addNode(testNode29);
    Node* testNode30 = new Node();
    testNode30->loadUnitCube();
    testNode30->geometries[0]->setShader(cubeShader);
    testNode30->scale = vec3(29.999935150146484f, 2.999999523162842f, 16.999998092651367f);
    testNode30->position = vec3(-36.28617477416992f, -1.132124423980713f, -18.673717498779297f);
    testNode30->eulerAngles = vec3(9.99999970909292f, 60.00000849984128f, -1.707547699614187e-06f);
    engine->addNode(testNode30);
    Node* testNode31 = new Node();
    testNode31->loadUnitCube();
    testNode31->geometries[0]->setShader(cubeShader);
    testNode31->scale = vec3(5.0f, 30.0f, 5.0f);
    testNode31->position = vec3(27.738876342773438f, 14.0f, 30.06119155883789f);
    testNode31->eulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    engine->addNode(testNode31);
    Node* testNode32 = new Node();
    testNode32->loadUnitCube();
    testNode32->geometries[0]->setShader(cubeShader);
    testNode32->scale = vec3(5.0f, 7.0f, 5.0f);
    testNode32->position = vec3(27.201324462890625f, 2.5f, -26.600440979003906f);
    testNode32->eulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    engine->addNode(testNode32);
    Node* testNode33 = new Node();
    testNode33->loadUnitCube();
    testNode33->geometries[0]->setShader(cubeShader);
    testNode33->scale = vec3(9.999994277954102f, 2.5f, 14.99999713897705f);
    testNode33->position = vec3(-19.002153396606445f, 0.24999995529651642f, 24.259979248046875f);
    testNode33->eulerAngles = vec3(0.0f, 59.99999483946294f, 0.0f);
    engine->addNode(testNode33);
    Node* testNode34 = new Node();
    testNode34->loadUnitCube();
    testNode34->geometries[0]->setShader(cubeShader);
    testNode34->scale = vec3(4.999887943267822f, 4.999917030334473f, 22.999780654907227f);
    testNode34->position = vec3(34.57914733886719f, 2.5202579498291016f, -17.966392517089844f);
    testNode34->eulerAngles = vec3(13.46300038716412f, 38.7630003512636f, 0.0f);
    engine->addNode(testNode34);
    Node* testNode35 = new Node();
    testNode35->loadUnitCube();
    testNode35->geometries[0]->setShader(cubeShader);
    testNode35->scale = vec3(9.999835968017578f, 2.499964952468872f, 14.999848365783691f);
    testNode35->position = vec3(12.881000518798828f, 0.24999994039535522f, -10.011907577514648f);
    testNode35->eulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    engine->addNode(testNode35);
    Node* testNode36 = new Node();
    testNode36->loadUnitCube();
    testNode36->geometries[0]->setShader(cubeShader);
    testNode36->scale = vec3(4.999978542327881f, 3.000000238418579f, 17.00000762939453f);
    testNode36->position = vec3(-5.298661231994629f, -1.336275339126587f, 31.8536376953125f);
    testNode36->eulerAngles = vec3(8.999993420258647f, 60.00000849984128f, -5.122643913064559e-06f);
    engine->addNode(testNode36);
    Node* testNode37 = new Node();
    testNode37->loadUnitCube();
    testNode37->geometries[0]->setShader(cubeShader);
    testNode37->scale = vec3(0.5f, 2.0f, 5.0f);
    testNode37->position = vec3(10.21187973022461f, 0.0f, 21.193662643432617f);
    testNode37->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode37);
    Node* testNode38 = new Node();
    testNode38->loadUnitCube();
    testNode38->geometries[0]->setShader(cubeShader);
    testNode38->scale = vec3(0.4999998211860657f, 1.0f, 9.99999713897705f);
    testNode38->position = vec3(25.113908767700195f, -0.5f, 11.59774398803711f);
    testNode38->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode38);
    Node* testNode39 = new Node();
    testNode39->loadUnitCube();
    testNode39->geometries[0]->setShader(cubeShader);
    testNode39->scale = vec3(0.5f, 1.0f, 10.0f);
    testNode39->position = vec3(4.626926422119141f, -0.5f, 7.29351806640625f);
    testNode39->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode39);
    Node* testNode40 = new Node();
    testNode40->loadUnitCube();
    testNode40->geometries[0]->setShader(cubeShader);
    testNode40->scale = vec3(5.000000953674316f, 3.0f, 17.0f);
    testNode40->position = vec3(5.108200550079346f, -1.3108752965927124f, -21.101150512695312f);
    testNode40->eulerAngles = vec3(-9.000000250447817f, 19.99999771063855f, 5.6785429905125e-07f);
    engine->addNode(testNode40);
    Node* testNode41 = new Node();
    testNode41->loadUnitCube();
    testNode41->geometries[0]->setShader(cubeShader);
    testNode41->scale = vec3(0.5f, 2.0f, 10.0f);
    testNode41->position = vec3(-6.175685882568359f, 0.0f, -4.580935478210449f);
    testNode41->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode41);
    Node* testNode42 = new Node();
    testNode42->loadUnitCube();
    testNode42->geometries[0]->setShader(cubeShader);
    testNode42->scale = vec3(0.5f, 2.0f, 7.0f);
    testNode42->position = vec3(-10.48333740234375f, 0.0f, 9.90719985961914f);
    testNode42->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode42);
    Node* testNode43 = new Node();
    testNode43->loadUnitCube();
    testNode43->geometries[0]->setShader(cubeShader);
    testNode43->scale = vec3(0.4999997913837433f, 1.0f, 3.999999761581421f);
    testNode43->position = vec3(2.3769264221191406f, -0.5f, 6.538968086242676f);
    testNode43->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode43);
    Node* testNode44 = new Node();
    testNode44->loadUnitCube();
    testNode44->geometries[0]->setShader(cubeShader);
    testNode44->scale = vec3(0.5f, 2.0f, 5.0f);
    testNode44->position = vec3(-9.59457778930664f, 0.0f, -1.830935001373291f);
    testNode44->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode44);
    Node* testNode45 = new Node();
    testNode45->loadUnitCube();
    testNode45->geometries[0]->setShader(cubeShader);
    testNode45->scale = vec3(4.9999680519104f, 0.9999958872795105f, 6.999967098236084f);
    testNode45->position = vec3(-12.002592086791992f, -0.4999999701976776f, -18.14734649658203f);
    testNode45->eulerAngles = vec3(0.0f, 33.53639957949186f, 0.0f);
    engine->addNode(testNode45);
    Node* testNode46 = new Node();
    testNode46->loadUnitCube();
    testNode46->geometries[0]->setShader(cubeShader);
    testNode46->scale = vec3(2.9999992847442627f, 2.0f, 3.9999990463256836f);
    testNode46->position = vec3(-7.776100158691406f, 0.0f, -15.409856796264648f);
    testNode46->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode46);
    Node* testNode47 = new Node();
    testNode47->loadUnitCube();
    testNode47->geometries[0]->setShader(cubeShader);
    testNode47->scale = vec3(4.999841690063477f, 4.0f, 5.0f);
    testNode47->position = vec3(40.72988510131836f, 0.9999867081642151f, 2.3642375469207764f);
    testNode47->eulerAngles = vec3(179.999991348578f, 20.135100559968695f, 179.999991348578f);
    engine->addNode(testNode47);
    Node* testNode48 = new Node();
    testNode48->loadUnitCube();
    testNode48->geometries[0]->setShader(cubeShader);
    testNode48->scale = vec3(4.999831199645996f, 3.0f, 4.9999918937683105f);
    testNode48->position = vec3(39.35308837890625f, 0.5000176429748535f, 7.0984416007995605f);
    testNode48->eulerAngles = vec3(179.999991348578f, -14.096251130778096f, 179.999991348578f);
    engine->addNode(testNode48);
    Node* testNode49 = new Node();
    testNode49->loadUnitCube();
    testNode49->geometries[0]->setShader(cubeShader);
    testNode49->scale = vec3(4.999912738800049f, 4.0f, 5.00007438659668f);
    testNode49->position = vec3(39.572853088378906f, 0.9999866485595703f, 11.962966918945312f);
    testNode49->eulerAngles = vec3(179.999991348578f, -71.10730310925103f, 179.999991348578f);
    engine->addNode(testNode49);
    Node* testNode50 = new Node();
    testNode50->loadUnitCube();
    testNode50->geometries[0]->setShader(cubeShader);
    testNode50->scale = vec3(3.0f, 2.999999761581421f, 3.0f);
    testNode50->position = vec3(-13.633177757263184f, 2.999999761581421f, 23.612285614013672f);
    testNode50->eulerAngles = vec3(179.999991348578f, -71.10728261868353f, 179.999991348578f);
    engine->addNode(testNode50);
    Node* testNode51 = new Node();
    testNode51->loadUnitCube();
    testNode51->geometries[0]->setShader(cubeShader);
    testNode51->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode51->position = vec3(-21.799108505249023f, 2.0f, 18.328943252563477f);
    testNode51->eulerAngles = vec3(179.999991348578f, -23.733391063798567f, 179.999991348578f);
    engine->addNode(testNode51);
    Node* testNode52 = new Node();
    testNode52->loadUnitCube();
    testNode52->geometries[0]->setShader(cubeShader);
    testNode52->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode52->position = vec3(-21.782814025878906f, 2.0f, 18.312650680541992f);
    testNode52->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    engine->addNode(testNode52);
    Node* testNode53 = new Node();
    testNode53->loadUnitCube();
    testNode53->geometries[0]->setShader(cubeShader);
    testNode53->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode53->position = vec3(-21.2570743560791f, 2.0f, 19.338041305541992f);
    testNode53->eulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    engine->addNode(testNode53);
    Node* testNode54 = new Node();
    testNode54->loadUnitCube();
    testNode54->geometries[0]->setShader(cubeShader);
    testNode54->scale = vec3(1.0000003576278687f, 0.9999999403953552f, 1.0000003576278687f);
    testNode54->position = vec3(-19.967870712280273f, 1.9999998807907104f, 19.419044494628906f);
    testNode54->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    engine->addNode(testNode54);
    Node* testNode55 = new Node();
    testNode55->loadUnitCube();
    testNode55->geometries[0]->setShader(cubeShader);
    testNode55->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode55->position = vec3(-18.6903018951416f, 2.0f, 20.22953224182129f);
    testNode55->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    engine->addNode(testNode55);
    Node* testNode56 = new Node();
    testNode56->loadUnitCube();
    testNode56->geometries[0]->setShader(cubeShader);
    testNode56->scale = vec3(1.0000005960464478f, 0.9999999403953552f, 1.0000005960464478f);
    testNode56->position = vec3(-22.858861923217773f, 1.9999998807907104f, 18.720481872558594f);
    testNode56->eulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    engine->addNode(testNode56);
    Node* testNode57 = new Node();
    testNode57->loadUnitCube();
    testNode57->geometries[0]->setShader(cubeShader);
    testNode57->scale = vec3(9.0f, 4.0f, 5.0f);
    testNode57->position = vec3(-22.26280975341797f, 0.9999867081642151f, -0.05115675926208496f);
    testNode57->eulerAngles = vec3(179.999991348578f, 0.0f, 179.999991348578f);
    engine->addNode(testNode57);
    Node* testNode58 = new Node();
    testNode58->loadUnitCube();
    testNode58->geometries[0]->setShader(cubeShader);
    testNode58->scale = vec3(20.0f, 20.0f, 20.0f);
    testNode58->position = vec3(0.0f, 9.0f, 60.0f);
    testNode58->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    engine->addNode(testNode58);
    Node* testNode59 = new Node();
    testNode59->loadUnitCube();
    testNode59->geometries[0]->setShader(cubeShader);
    testNode59->scale = vec3(2.999969720840454f, 1.9999911785125732f, 3.999952793121338f);
    testNode59->position = vec3(-17.134122848510742f, 0.0f, 2.518460988998413f);
    testNode59->eulerAngles = vec3(0.0f, 60.457330645908655f, 0.0f);
    engine->addNode(testNode59);
    Node* testNode60 = new Node();
    testNode60->loadUnitCube();
    testNode60->geometries[0]->setShader(cubeShader);
    testNode60->scale = vec3(4.999832630157471f, 3.0f, 4.999993324279785f);
    testNode60->position = vec3(18.351093292236328f, 0.5000176429748535f, 8.719722747802734f);
    testNode60->eulerAngles = vec3(179.999991348578f, -14.096249423230805f, 179.999991348578f);
    engine->addNode(testNode60);
    Node* testNode61 = new Node();
    testNode61->loadUnitCube();
    testNode61->geometries[0]->setShader(cubeShader);
    testNode61->scale = vec3(0.5f, 2.0f, 7.0f);
    testNode61->position = vec3(-10.890523910522461f, 0.0f, -35.301090240478516f);
    testNode61->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    engine->addNode(testNode61);
    Node* testNode62 = new Node();
    testNode62->loadUnitCube();
    testNode62->geometries[0]->setShader(cubeShader);
    testNode62->scale = vec3(4.0f, 3.0f, 2.0f);
    testNode62->position = vec3(-49.953739166259766f, 0.5f, 5.168451309204102f);
    testNode62->eulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    engine->addNode(testNode62);
    Node* testNode63 = new Node();
    testNode63->loadUnitCube();
    testNode63->geometries[0]->setShader(cubeShader);
    testNode63->scale = vec3(4.0f, 7.0f, 1.999990463256836f);
    testNode63->position = vec3(-44.0306396484375f, 2.5f, 20.40106964111328f);
    testNode63->eulerAngles = vec3(0.0f, -45.95227305651143f, 0.0f);
    engine->addNode(testNode63);
    Node* testNode64 = new Node();
    testNode64->loadUnitCube();
    testNode64->geometries[0]->setShader(cubeShader);
    testNode64->scale = vec3(4.999993324279785f, 6.999980926513672f, 4.999993324279785f);
    testNode64->position = vec3(14.83809757232666f, 2.499999761581421f, -37.63517761230469f);
    testNode64->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    engine->addNode(testNode64);
    Node* testNode65 = new Node();
    testNode65->loadUnitCube();
    testNode65->geometries[0]->setShader(cubeShader);
    testNode65->scale = vec3(3.000000238418579f, 2.999999761581421f, 3.000000238418579f);
    testNode65->position = vec3(17.829620361328125f, 2.9999845027923584f, -9.80679702758789f);
    testNode65->eulerAngles = vec3(179.999991348578f, -71.10726895830518f, 179.999991348578f);
    engine->addNode(testNode65);
    Node* testNode66 = new Node();
    testNode66->loadUnitCube();
    testNode66->geometries[0]->setShader(cubeShader);
    testNode66->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode66->position = vec3(13.097940444946289f, 1.9999847412109375f, -6.686174392700195f);
    testNode66->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    engine->addNode(testNode66);
    Node* testNode67 = new Node();
    testNode67->loadUnitCube();
    testNode67->geometries[0]->setShader(cubeShader);
    testNode67->scale = vec3(1.0000169277191162f, 0.9999843239784241f, 1.0000169277191162f);
    testNode67->position = vec3(7.924259662628174f, 1.9999691247940063f, -6.570480823516846f);
    testNode67->eulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    engine->addNode(testNode67);
    Node* testNode68 = new Node();
    testNode68->loadUnitCube();
    testNode68->geometries[0]->setShader(cubeShader);
    testNode68->scale = vec3(1.0000169277191162f, 0.9999842643737793f, 1.0000169277191162f);
    testNode68->position = vec3(9.213461875915527f, 1.9999690055847168f, -6.489477634429932f);
    testNode68->eulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    engine->addNode(testNode68);
    Node* testNode69 = new Node();
    testNode69->loadUnitCube();
    testNode69->geometries[0]->setShader(cubeShader);
    testNode69->scale = vec3(1.0000022649765015f, 0.9999843239784241f, 1.0000022649765015f);
    testNode69->position = vec3(10.4910306930542f, 1.9999691247940063f, -5.678989887237549f);
    testNode69->eulerAngles = vec3(0.0f, -84.12957785625727f, 0.0f);
    engine->addNode(testNode69);
    Node* testNode70 = new Node();
    testNode70->loadUnitCube();
    testNode70->geometries[0]->setShader(cubeShader);
    testNode70->scale = vec3(1.0000008344650269f, 0.9999999403953552f, 1.0000008344650269f);
    testNode70->position = vec3(12.021892547607422f, 1.999984622001648f, -6.278343200683594f);
    testNode70->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    engine->addNode(testNode70);
    Node* testNode71 = new Node();
    testNode71->loadUnitCube();
    testNode71->geometries[0]->setShader(cubeShader);
    testNode71->scale = vec3(3.9999682903289795f, 2.9999806880950928f, 1.9999841451644897f);
    testNode71->position = vec3(-23.76885414123535f, 0.4999694526195526f, 41.0047492980957f);
    testNode71->eulerAngles = vec3(0.0f, 90.00000250447816f, 0.0f);
    engine->addNode(testNode71);









    vector<Node*> characters;
    


    StoneBlast* stoneMagic = new StoneBlast();
    FireBall* fireMagic = new FireBall();
    LightningSpear* lightningMagic = new LightningSpear();
    GroundSmash* smashMagic = new GroundSmash();
    Thunder* thunderMagic = new Thunder();
    Flame* flameMagic = new Flame();
    character->addMagics(stoneMagic, KEY_1);
    character->addMagics(fireMagic, KEY_2);
    character->addMagics(lightningMagic, KEY_3);
    character->addMagics(smashMagic, KEY_7);
    character->addMagics(thunderMagic, KEY_4);
    character->addMagics(flameMagic, KEY_5);

    engine->addNode(stoneMagic);
    engine->addNode(flameMagic);
    engine->addNode(thunderMagic);

    HitController enemyHitController;

    enemyHitController.magics.push_back(stoneMagic);
    enemyHitController.magics.push_back(fireMagic);
    enemyHitController.magics.push_back(lightningMagic);
    enemyHitController.magics.push_back(smashMagic);
    enemyHitController.magics.push_back(thunderMagic);
    enemyHitController.magics.push_back(flameMagic);
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
            if(engine->input->wasKeyReleased(KEY_2)){
                if (!fireMagic->start) {
                    character->rightHand->addChildNode(fireMagic);
                    character->castMagic(KEY_2);
                }
            }
            if (engine->input->wasKeyPressed(KEY_3)) {
                if (!lightningMagic->start) {
                    character->rightHand->addChildNode(lightningMagic);
                    character->castMagic(KEY_3);
                }
            }
            if (engine->input->wasKeyPressed(KEY_4)) {
                if (!lightningMagic->start) {
                    character->castMagic(KEY_4);
                }
            }
            if (engine->input->wasKeyPressed(KEY_5)) {
                character->castMagic(KEY_5);
            }
            if (engine->input->wasKeyPressed(KEY_6)) {
                Particle3DNode* shield = new Particle3DNode("/Resources/Game/Effects/shield.dae", 1, 10.0f, 0);
                shield->color = vec4(0.4, 0.4, 1, 0.4);
                shield->position.y -= 0.4;
                shield->isAdditive = true;
                shield->setMaxAmount(1);
                shield->renderingOrder = 2010;
                shield->initialScale = vec3(5, 4, 4);
                shield->isDisabled = false;
                engine->addNode(shield);
            }
            if (engine->input->wasKeyPressed(KEY_7)) {
                character->castMagic(KEY_7);
            }

            for (int i = 0; i < enemies.size(); i++){
                enemies[i]->updatePosition();
                enemies[i]->updateTransform();
//                cout << to_string(enemies[i]->getWorldTransform()) << endl;
            }
            
            stoneMagic->updateMagic();
            fireMagic->updateMagic();
            lightningMagic->updateMagic();


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
