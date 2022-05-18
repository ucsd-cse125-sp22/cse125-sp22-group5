//
//  ScatteredFire.cpp
//  Eternal_Ritual
//
//  Created by Zifan Zhang on 5/18/22.
//

#include "ScatteredFire.hpp"

#include <string>
#include <glm/gtc/random.hpp>

#include "Game/Character/CharNode.hpp"

using namespace std;
using namespace glm;

#define NUMSPEAR 6

ScatteredFire::ScatteredFire() {
    start = false;
    this->actionName = "cast magic 3";
    this->stopTime = 4.0f;
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    ballNode = new Node();
    ballNode->position.y = 1;
    this->addChildNode(ballNode);
    for (int k = 0; k < NUMSPEAR; k++) {
        FireBall* fireBall = new FireBall();
        balls.push_back(fireBall);
    }
}
void ScatteredFire::play(CharNode* character, int seed){
    if (!start){
        this->caster = character;
        this->seed = seed;
        srand(seed);
        for (int k = 0; k < balls.size(); k++) {
            this->ballNode->addChildNode(balls[k]);
            balls[k]->velocityError = vec3((rand() / (RAND_MAX + 1.0f) - 0.5) * 0.2, (rand() / (RAND_MAX + 1.0f) - 0.5) * 0.2, (rand() / (RAND_MAX + 1.0f) - 0.5) * 0.2);
            balls[k]->play(this->caster, this->seed);
        }
        Animation* playNext = new Animation("play first spear " + to_string(reinterpret_cast<long>(&balls[0])), 1);
        playNext->setCompletionHandler([&] {
            playNextSpear(0);
        });
        Engine::main->playAnimation(playNext);
    }
}
void ScatteredFire::playNextSpear(int index){
    if (index < balls.size()){
        balls[index]->setThrew();
        Animation* playNext = new Animation("play next spear " + to_string(reinterpret_cast<long>(&balls[index])), 0.4);
        playNext->setCompletionHandler([&, index] {
            playNextSpear(1 + index);
        });
        Engine::main->playAnimation(playNext);
    }
}
void ScatteredFire::updateMagic() {
    for (int k = 0; k < balls.size(); k++) {
        balls[k]->updateMagic();
    }
}
void ScatteredFire::tryDamage(CharNode *character) {
    for (int k = 0; k < balls.size(); k++) {
        balls[k]->tryDamage(character);
    }
}

