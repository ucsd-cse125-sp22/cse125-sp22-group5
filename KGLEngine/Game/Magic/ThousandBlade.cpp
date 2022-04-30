//
//  ThousandBlade.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#include "ThousandBlade.hpp"

ThousandBlade::ThousandBlade(vec3 position, vec3 eularAngle){
    this->position = position;
    this->eulerAngles = eularAngle;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    

}
void ThousandBlade::updateMagic(){
    
}
void ThousandBlade::play(vec3 position, vec3 euler){
    
}
ThousandBlade::~ThousandBlade(){
    
}
