//
//  Thunder.cpp
//
//  Created by Zifan Zhang on 5/10/22.
//  Updated by Kangming Yu on 5/16/22.
//

#include "Game/Magic/Thunder.hpp"

#include <string>
#include <glm/gtc/random.hpp>

#include "Game/Character/CharNode.hpp"

#define COOLDOWN 3
#define COST 250

using namespace std;
using namespace glm;


Thunder::Thunder() {
    start = false;
    canDamage = false;
    this->actionName = "cast magic 1";
    this->stopTime = 2.0f;
    this->cooldown = COOLDOWN;
    this->cost = COST;
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    left = new Node();
    middle = new Node();
    right = new Node();
    left->eulerAngles.y = 30;
    right->eulerAngles.y = -30;
    addChildNode(left);
    addChildNode(middle);
    addChildNode(right);
    for (int k = 0; k < 12; k++) {
        ThunderShock* thunder = new ThunderShock();
        thunder->position.z = glm::log2((float)k + 2) / 2 + k;
        left->addChildNode(thunder);
        thunders.push_back(thunder);
        thunder = new ThunderShock();
        thunder->position.z = glm::log2((float)k + 2) / 2 + k;
        middle->addChildNode(thunder);
        thunders.push_back(thunder);
        thunder = new ThunderShock();
        thunder->position.z = glm::log2((float)k + 2) / 2 + k;
        right->addChildNode(thunder);
        thunders.push_back(thunder);
    }
}
void Thunder::play(CharNode* character, int seed){
    if (!start){
        this->seed = seed;
        srand(seed);
        this->caster = character;
        this->position = character->getWorldPosition();
        this->updateTransform();
        this->eulerAngles = character->modelNode->getWorldEulerAngles();
        playNextThunder(0);
        Animation* dragonCoolDown = new Animation("thunder cool down " + to_string(reinterpret_cast<long>(this)), this->cooldown);
        Engine::main->playAnimation(dragonCoolDown);
        dragonCoolDown->setCompletionHandler([&] {
            start = false;
        });
        this->availableTime = Engine::main->getTime() + cooldown;
    }
}
void Thunder::playNextThunder(int index){
    if (index < thunders.size()){
        thunders[index]->position.x = glm::log2(thunders[index]->position.z) * 0.1 * (rand() / (RAND_MAX + 1.0f) - 0.5);
        thunders[index]->play(this->caster, this->seed);
        thunders[index + 1]->position.x = glm::log2(thunders[index]->position.z) * 0.1 * (rand() / (RAND_MAX + 1.0f) - 0.5);
        thunders[index + 1]->play(this->caster, this->seed);
        thunders[index + 2]->position.x = glm::log2(thunders[index]->position.z) * 0.1 * (rand() / (RAND_MAX + 1.0f) - 0.5);
        thunders[index + 2]->play(this->caster, this->seed);
        Animation* playNext = new Animation("play next thunder " + to_string(reinterpret_cast<long>(&thunders[index])), 0.2);
        playNext->setCompletionHandler([&, index] {
            playNextThunder(3 + index);
        });
        Engine::main->playAnimation(playNext);
    }
}
void Thunder::tryDamage(CharNode *character) {
    for (int k = 0; k < thunders.size(); k++) {
        thunders[k]->tryDamage(character);
    }
}
