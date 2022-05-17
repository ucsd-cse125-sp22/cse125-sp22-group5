//
//  ImportCharHelper.cpp
//
//  Created by Kangming Yu on 5/16/22.
//

#include "Game/Character/ImportCharHelper.hpp"

#include "KGLEngine/Engine.hpp"

using namespace glm;


namespace ImportCharHelper {

void importCharModel(CharNode* character) {
    Texture* mixamoD = new Texture("/Resources/Game/Character/Textures/Mixamo D.png", 2.0f, true);
    Texture* mixamoN = new Texture("/Resources/Game/Character/Textures/Mixamo N.png", 2.0f, true);
    Texture* mixamoM = new Texture("/Resources/Game/Character/Textures/Mixamo M.png", 2.0f, true);
    Texture* reflection = new Texture("/Resources/Game/PBR/RF.png", 0.0f, false);
    
    PBRShader* mixamoMaterial = new PBRShader(0.0f, 0.0f);
    mixamoMaterial->setDiffuseMap(mixamoD);
    mixamoMaterial->setNormalMap(mixamoN);
    mixamoMaterial->setMetallicMap(mixamoM);
    mixamoMaterial->metallicIntensity = 2.0f;
    mixamoMaterial->setRoughnessMap(mixamoM);
    mixamoMaterial->invertRoughness = true;
    mixamoMaterial->setReflectionMap(reflection);
    
    
    Node* charModel = new Node();
    charModel->scale = vec3(0.5f);
    charModel->loadModelFile("/Resources/Game/Character/MT.fbx");
    charModel->geometries[0]->setShader(mixamoMaterial);
    charModel->geometries[1]->isHidden = true;
    charModel->isDisabled = false;
    
    character->setModel(charModel);
}


void importCharAnimation(CharNode* character) {
    character->addAnimator("idle", "/Resources/Game/Character/Animations/Idle.dae");
    character->addAnimator("running", "/Resources/Game/Character/Animations/Running.dae");
    character->addAnimator("back run", "/Resources/Game/Character/Animations/Back Run.fbx");
    character->addAnimator("left strafe", "/Resources/Game/Character/Animations/Left Strafe.fbx");
    character->addAnimator("right strafe", "/Resources/Game/Character/Animations/Right Strafe.fbx");
    character->addAnimator("roll", "/Resources/Game/Character/Animations/Roll.dae");
    character->addAnimator("cast magic 1", "/Resources/Game/Character/Animations/Cast Magic 1.fbx");
    character->addAnimator("cast magic 2", "/Resources/Game/Character/Animations/Cast Magic 2.fbx");
    character->addAnimator("smash ground", "/Resources/Game/Character/Animations/Smash Ground.fbx");
}


} // namespace ImportCharHelper
