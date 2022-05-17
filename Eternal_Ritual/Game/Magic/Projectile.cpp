//
//  Projectile.cpp
//
//  Created by futian Zhang on 4/27/22.
//  Updated by Kangming Yu on 5/14/22.
//

#include "Game/Magic/Projectile.hpp"

#include <algorithm>
#include <map>
#include <string>

#include "Game/Character/CharNode.hpp"

using namespace std;
using namespace glm;


Projectile::Projectile(){
    this->engineInitializeNode();
    this->canDamage = false;
}

Projectile::~Projectile(){
    this->removeFromParentNode();
    this->childNodes.clear();
    this->boneNodes.clear();
    for(unsigned int i = 0; i < this->animators.size(); i += 1) {
        delete(this->animators[i]);
    }
    this->animators.clear();
    if(this->frozenNodeGeometryInstancingIndices.size() > 0) {
        map<Geometry*, vector<unsigned int>>::iterator iterator;
        for(iterator = this->frozenNodeGeometryInstancingIndices.begin();
            iterator != this->frozenNodeGeometryInstancingIndices.end();
            iterator++) {
            for(unsigned i = 0; i < iterator->second.size(); i += 1) {
                iterator->first->engineUpdateGeometryInstanceTransform(iterator->second[i], mat4(0.0f), true);
            }
            iterator->second.clear();
        }
        this->frozenNodeGeometryInstancingIndices.clear();
    }else if(this->geometryInstancingIndex == -1) {
        for(unsigned int i = 0; i < this->geometries.size(); i += 1) {
            if(this->geometryInstancingIndex >= 0 && this->geometries[i]->engineGetGeometryInstanceCount() > 1) {
                this->geometries[i]->engineUpdateGeometryInstanceTransform(this->geometryInstancingIndex, mat4(0.0f), true);
            }else{
                delete(this->geometries[i]);
            }
        }
    }
    this->geometries.clear();
    this->childNodes.clear();
    this->parent = NULL;
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


Projectile* Projectile::clone(){
    Projectile* node = new Projectile();
    node->name = this->name;
    node->isDisabled = this->isDisabled;
    node->position = this->position;
    node->eulerAngles = this->eulerAngles;
    node->scale = this->scale;
    node->canDamage = this->canDamage;
    node->start = this->start;
    node->end = this->end;
    node->damage = this->damage;
    node->orientationTargetNode = this->orientationTargetNode;
    for(unsigned int i = 0; i < this->geometries.size(); i += 1) {
        if(this->geometries[i]->engineGetGeometryInstanceCount() == 0) {
            this->geometryInstancingIndex = this->geometries[i]->engineGeometryAddInstance();
        }
        node->geometryInstancingIndex = this->geometries[i]->engineGeometryAddInstance();
        node->geometries.push_back(this->geometries[i]);
    }
    for(unsigned int i = 0; i < this->childNodes.size(); i += 1) {
        Node* newNode = this->childNodes[i]->clone();
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
