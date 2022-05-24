//
//  ScatteredFire.cpp
//  Eternal_Ritual
//
//  Created by Zifan Zhang on 5/18/22.
//

#include "Game/Magic/ScatteredFire.hpp"

#include <string>
#include <glm/gtc/random.hpp>

#include "Game/Character/CharNode.hpp"

#define COOLDOWN 5
#define COST 300

using namespace std;
using namespace glm;

#define NUMBALLS 10

ScatteredFire::ScatteredFire() {
    start = false;
    this->actionName = "cast magic 3";
    this->stopTime = 1.8f;
    this->cooldown = COOLDOWN;
    this->cost = COST;
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    ballNode = new Node();
    ballNode->position.y = 1;
    this->addChildNode(ballNode);
    for (int k = 0; k < NUMBALLS; k++) {
        FireBall* fireBall = new FireBall();
        balls.push_back(fireBall);
    }
}
void ScatteredFire::play(CharNode* character, int seed){
    if (!start){
        this->caster = character;
        this->seed = seed;
        start = true;
        srand(seed);
        for (int k = 0; k < balls.size(); k++) {
            this->ballNode->addChildNode(balls[k]);
            balls[k]->velocityError = vec3((rand() / (RAND_MAX + 1.0f) - 0.5) * 0.5, (rand() / (RAND_MAX + 1.0f) - 0.5) * 0.5, (rand() / (RAND_MAX + 1.0f) - 0.5) * 0.5);
            balls[k]->play(this->caster, this->seed);
        }
        Animation* playNext = new Animation("throw fire balls " + to_string(reinterpret_cast<long>(&balls[0])), 0.75);
        playNext->setCompletionHandler([&] {
            for (int k = 0; k < balls.size(); k++) {
                balls[k]->setThrew();
            }
        });
        Engine::main->playAnimation(playNext);
        Animation* stop = new Animation("stop scattered fire " + to_string(reinterpret_cast<long>(&balls[0])), this->cooldown);
        stop->setCompletionHandler([&] {
            start = false;
        });
        Engine::main->playAnimation(stop);
        this->availableTime = Engine::main->getTime() + cooldown;
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
