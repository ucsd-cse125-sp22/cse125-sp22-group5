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
#include "Game/Magic/Circle.hpp"

#define COOLDOWN 5
#define COST 300

using namespace std;
using namespace glm;

#define NUMBALLS 10

bool ScatteredFire::loaded = false;
AudioBuffer* ScatteredFire::castSound = NULL;
ParticleNode* ScatteredFire::metaShiny = NULL;
ParticleNode* ScatteredFire::metaWhirl = NULL;


void ScatteredFire::load() {
    loaded = true;
    castSound = new AudioBuffer("/Resources/Game/Sound/Fire Spelll 22.wav");
    metaShiny = new ParticleNode(200, 1.5, 0);
    metaShiny->texture = new Texture("/Resources/Game/Effects/Particle1.png");
    metaShiny->setEmissionStorm(0, 2, 0.2);
    metaShiny->eulerAngles = vec3(0,0,90);
    metaShiny->setMaxAmount(160);
    metaShiny->initialSpeed = 0.8f;
    metaShiny->initialSpeedVariation = 0.025f;
    metaShiny->initialScale = 0.1;
    metaShiny->initialScaleVariation = 0.05;
    metaShiny->accelerationVariation = vec3(0.1,0.8,0.1);
    metaShiny->setColorAnimation(vec4(1, 0.6, 0.5, 0), 0);
    metaShiny->setColorAnimation(vec4(1, 0.6, 0.5, 1), 0.5);
    metaShiny->setColorAnimation(vec4(1, 0.6, 0.5, 0), 1);
    metaShiny->isAdditive = true;
    metaShiny->renderingOrder = 1000;
    metaShiny->isDisabled = true;
    metaWhirl = new ParticleNode(1, 1, 0);
    metaWhirl->texture = new Texture("/Resources/Game/Effects/Explosion1.png");
    metaWhirl->setSpriteSheetAnimation(7, 12, 40, 100, 40);
}

ScatteredFire::ScatteredFire() {
    if (!loaded) load();
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
    this->shiny = metaShiny->copy()->convertToParticleNode();
    Engine::main->addNode(shiny);
    this->circle = new Circle();
    this->circle->setColor(vec3(1, 0.7, 0.5));
    this->circle->isDisabled = true;
    this->circle->scale = vec3(2.5);
    Engine::main->addNode(circle);
    this->loadAudioBuffer("cast", castSound, 2.0f, 1.0f);
}
void ScatteredFire::play(CharNode* character, int seed){
    if (!start){
        this->caster = character;
        this->playAudio("cast");
        this->seed = seed;
        start = true;
        this->circle->isDisabled = false;
        circle->position = character->modelNode->getWorldPosition() + character->modelNode->getRightVectorInWorld() * 1.5f + vec3(0, 1.2, 0);
        circle->eulerAngles = character->modelNode->eulerAngles + vec3(90, 0, 0);
        this->circle->setColor(vec3(0));
        srand(seed);
        for (int k = 0; k < balls.size(); k++) {
            this->ballNode->addChildNode(balls[k]);
            balls[k]->velocityError = vec3((rand() / (RAND_MAX + 1.0f) - 0.5) * 0.5, (rand() / (RAND_MAX + 1.0f) - 0.5) * 0.5, (rand() / (RAND_MAX + 1.0f) - 0.5) * 0.5);
            balls[k]->play(this->caster, this->seed);
        }
        Animation* playNext = new Animation("throw fire balls " + to_string(reinterpret_cast<long>(&balls[0])), 0.75);
        playNext->setVec3Animation(&circle->shader->multiplyColor, vec3(1, 0.7, 0.5));
        playNext->setCompletionHandler([&] {
            for (int k = 0; k < balls.size(); k++) {
                balls[k]->setThrew();
            }
            Animation* circleDim = new Animation("fire circle dim " + to_string(reinterpret_cast<long>(&balls[0])), 1);
            circleDim->setVec3Animation(&circle->shader->multiplyColor, vec3(0));
            circleDim->setCompletionHandler([&] {
                this->circle->isDisabled = true;
            });
            Engine::main->playAnimation(circleDim);
        });
        Engine::main->playAnimation(playNext);
        Animation* stop = new Animation("stop scattered fire " + to_string(reinterpret_cast<long>(&balls[0])), this->cooldown);
        stop->setCompletionHandler([&] {
            start = false;
        });
        Engine::main->playAnimation(stop);
        this->availableTime = Engine::main->getTime() + cooldown;
        shiny->position = character->getWorldPosition();
        shiny->isDisabled = false;
        shiny->reset();
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

