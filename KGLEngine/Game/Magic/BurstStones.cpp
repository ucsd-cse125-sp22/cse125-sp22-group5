//
//  BurstStones.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/24/22.
//

#include "BurstStones.hpp"
BurstStones::BurstStones(vec3 position, vec3 eularAngle){
    this->position = position;
    this->eulerAngles = eularAngle;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    
    Texture* stone_D = new Texture("/Resources/Game/Magic/Magic1/magic_D.jpg", 2.0f, true);
    Texture* stone_E = new Texture("/Resources/Game/Magic/Magic1/magic_E.jpg", 2.0f, true);
    
    PBRShader* stone_shader = new PBRShader(0.5, 0.5);
    //particle_shader->setAdditive();
    stone_shader->setDiffuseMap(stone_D);
    stone_shader->setEmissionMap(stone_E);
    Node* stone = new Node();
    stone->loadModelFile("/Resources/Game/Magic/Magic1/magic.fbx");
    stone->eulerAngles = vec3(0,0,45);
    stone->position = vec3(1,1,0);
    stone->scale = vec3(1, 1, 1);
    stone->geometries[0]->setShader(stone_shader);
    stone->geometries[0]->cullFront();
    stone->geometries[0]->renderingOrder = 1000;
}
void BurstStones::updateMagic(){
    
}
void BurstStones::play(){
    
}
BurstStones::~BurstStones(){
    
}
