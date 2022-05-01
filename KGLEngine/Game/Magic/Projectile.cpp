//
//  Projectile.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/27/22.
//

#include "Projectile.hpp"

Projectile::Projectile(){
    this->engineInitializeNode();
    this->canDamage = false;
}

Projectile::~Projectile(){
}

void Projectile::tryDamageChar(CharNode* character){
    if (this->canDamage &&
        find(this->damagedChar.begin(), this->damagedChar.end(), character) == this->damagedChar.end() &&
        character->hitbox->testHit(this->start, this->end)){
        character->receiveDamage(this->damage);
        damagedChar.push_back(character);
    }
}

Projectile* Projectile::copy(){
    Projectile* node = new Projectile();
    node->name = this->name;
    node->damage = this->damage;
    node->canDamage = this->canDamage;
    node->start = this->start;
    node->end = this->end;
    node->isDisabled = this->isDisabled;
//    node->renderingBitMask = this->renderingBitMask;
    node->position = this->position;
    node->eulerAngles = this->eulerAngles;
    node->scale = this->scale;
    node->orientationTargetNode = this->orientationTargetNode;
    node->boneNames = this->boneNames;
    node->boneTransforms = this->boneTransforms;
    for(unsigned int i = 0; i < this->animators.size(); i += 1) {
        node->animators.push_back(this->animators[i]->engineCopyAnimator());
    }
    for(unsigned int i = 0; i < this->geometries.size(); i += 1) {
        node->geometries.push_back(this->geometries[i]->copy(&node->animators));
    }
    for(unsigned int i = 0; i < this->childNodes.size(); i += 1) {
        Node* newNode = this->childNodes[i]->copy();
        node->addChildNode(newNode);
        map<string, Node*>::iterator iterator;
        for(iterator = this->boneNodes.begin(); iterator != this->boneNodes.end(); iterator++) {
            if(iterator->second == this->childNodes[i]) {
                node->boneNodes[iterator->first] = newNode;
                break;
            }
        }
    }
    return(node);
}
