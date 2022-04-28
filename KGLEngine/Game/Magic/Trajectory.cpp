//
//  Trajectory.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/27/22.
//

#include "Trajectory.hpp"

Trajectory::Trajectory(){
    this->engineInitializeNode();
}

void Trajectory::playAfter(int id, float time, std::function<void()> event){
    Animation* waitUntilPlay = new Animation(to_string(id), time);
    waitUntilPlay->setCompletionHandler(event);
}

void Trajectory::tryDamageChar(CharNode* character){
    if (this->canDamage &&
        find(this->damagedChar.begin(), this->damagedChar.end(), character) == this->damagedChar.end() &&
        character->hitbox->testHit(this->start, this->end)){
        character->receiveDamage(this->damage);
        damagedChar.push_back(character);
    }
}
