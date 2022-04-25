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
}
void BurstStones::updateMagic(){
    
}
void BurstStones::play(){
    
}
BurstStones::~BurstStones(){
    
}
