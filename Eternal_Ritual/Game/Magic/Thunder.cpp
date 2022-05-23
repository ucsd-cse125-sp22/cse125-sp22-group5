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

using namespace std;
using namespace glm;


Thunder::Thunder() {
    start = false;
    canDamage = false;
    this->actionName = "cast magic 1";
    this->stopTime = 3.0f;
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    for (int k = 0; k < 12; k++) {
        ThunderShock* thunder = new ThunderShock();
        thunder->position.z = glm::log2((float)k + 2) / 2 + k;
        this->addChildNode(thunder);
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
    }
}
void Thunder::playNextThunder(int index){
    if (index < thunders.size()){
        thunders[index]->position.x = glm::log2(thunders[index]->position.z) * 0.1 * (rand() / (RAND_MAX + 1.0f) - 0.5);
        thunders[index]->play(this->caster, this->seed);
        Animation* playNext = new Animation("play next thunder " + to_string(reinterpret_cast<long>(&thunders[index])), 0.2);
        playNext->setCompletionHandler([&, index] {
            playNextThunder(1 + index);
        });
        Engine::main->playAnimation(playNext);
    }
}
void Thunder::tryDamage(CharNode *character) {
    for (int k = 0; k < thunders.size(); k++) {
        thunders[k]->tryDamage(character);
    }
}
