//
//  LightningPhalanx.cpp
//  Eternal_Ritual
//
//  Created by Zifan Zhang on 5/18/22.
//

#include "LightningPhalanx.hpp"

#include <string>
#include <glm/gtc/random.hpp>

#include "Game/Character/CharNode.hpp"

using namespace std;
using namespace glm;

#define NUMSPEAR 6

LightningPhalanx::LightningPhalanx() {
    start = false;
    this->actionName = "cast magic 2";
    this->stopTime = 3.0f;
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    for (int k = 0; k < NUMSPEAR; k++) {
        LightningSpear* lightningSpear = new LightningSpear();
        spears.push_back(lightningSpear);
        Node* spearNode = new Node();
        spearNode->position.x = sin(M_PI * k / (NUMSPEAR - 1)) / 1.5;
        spearNode->position.z = cos(M_PI * k / (NUMSPEAR - 1));
        spearNode->eulerAngles.z -= 90;
        spearNodes.push_back(spearNode);
        this->addChildNode(spearNode);
    }
}
void LightningPhalanx::play(CharNode* character, int seed){
    if (!start){
        this->caster = character;
        for (int k = 0; k < spears.size(); k++) {
            this->spearNodes[k]->addChildNode(spears[k]);
            spears[k]->play(this->caster, this->seed);
        }
        Animation* playNext = new Animation("play first spear " + to_string(reinterpret_cast<long>(&spears[0])), 1);
        playNext->setCompletionHandler([&] {
            playNextSpear(0);
        });
        Engine::main->playAnimation(playNext);
    }
}
void LightningPhalanx::playNextSpear(int index){
    if (index < spears.size()){
        spears[index]->setThrew();
        Animation* playNext = new Animation("play next spear " + to_string(reinterpret_cast<long>(&spears[index])), 0.4);
        playNext->setCompletionHandler([&, index] {
            playNextSpear(1 + index);
        });
        Engine::main->playAnimation(playNext);
    }
}
void LightningPhalanx::updateMagic() {
    for (int k = 0; k < spears.size(); k++) {
        spears[k]->updateMagic();
    }
}
void LightningPhalanx::tryDamage(CharNode *character) {
    for (int k = 0; k < spears.size(); k++) {
        spears[k]->tryDamage(character);
    }
}
