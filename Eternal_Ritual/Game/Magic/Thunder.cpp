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
#include "Game/Magic/Circle.hpp"

#define COOLDOWN 3
#define COST 250

using namespace std;
using namespace glm;

bool Thunder::loaded = false;
AudioBuffer* Thunder::castSound = NULL;
ParticleNode* Thunder::metaShiny = NULL;
ParticleNode* Thunder::metaShimmer = NULL;


void Thunder::load() {
    loaded = true;
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
    metaShiny->setColorAnimation(vec4(1, 1, 0.5, 0), 0);
    metaShiny->setColorAnimation(vec4(1, 1, 0.5, 1), 0.5);
    metaShiny->setColorAnimation(vec4(1, 1, 0.5, 0), 1);
    metaShiny->renderingOrder = 1000;
    metaShiny->isAdditive = true;
    metaShiny->isDisabled = true;
    metaShimmer = new ParticleNode(100, 0.3, 0);
    metaShimmer->texture = new Texture("/Resources/Game/Effects/Particle1.png");
    metaShimmer->useLocalSpace = true;
    metaShimmer->setEmissionSphere(0, 0.1);
    metaShimmer->setMaxAmount(70);
    metaShimmer->initialScale = 0.1;
    metaShimmer->initialScaleVariation = 0.05;
    metaShimmer->setColorAnimation(vec4(1, 1, 0.5, 0), 0);
    metaShimmer->setColorAnimation(vec4(1, 1, 0.5, 1), 0.5);
    metaShimmer->setColorAnimation(vec4(1, 1, 0.5, 0), 1);
    metaShimmer->renderingOrder = 1000;
    metaShimmer->isAdditive = true;
    metaShimmer->isDisabled = true;
    castSound = new AudioBuffer("/Resources/Game/Sound/Positive Effect 1_", "wav", 1, 3);
}
Thunder::Thunder() {
    if (!loaded) load();
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
    this->circle = new Circle();
    this->circle->setColor(vec3(1, 1, 0.5));
    this->circle->isDisabled = true;
    this->circle->scale = vec3(3);
    Engine::main->addNode(circle);
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
    this->shiny = metaShiny->copy()->convertToParticleNode();
    Engine::main->addNode(shiny);
    this->shimmer = metaShimmer->copy()->convertToParticleNode();
    this->loadAudioBuffer("cast", castSound, 2.0f, 1.0f);
}
void Thunder::play(CharNode* character, int seed){
    if (!start){
        this->start = true;
        this->playAudio("cast");
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
        shiny->position = character->getWorldPosition();
        shiny->isDisabled = false;
        shiny->reset();
        shimmer->removeFromParentNode();
        character->leftHand->addChildNode(shimmer);
        shimmer->isDisabled = false;
        shimmer->reset();
        circle->isDisabled = false;
        this->circle->setColor(vec3(1, 1, 0.5));
        circle->position = character->getWorldPosition() + vec3(0, 0.1, 0);
        circle->scale = vec3(1);
        Animation* circleExpand = new Animation("circle expand " + to_string(reinterpret_cast<long>(this)), 0.8);
        circleExpand->setVec3Animation(&circle->scale, vec3(4));
        Engine::main->playAnimation(circleExpand);
        circleExpand->setCompletionHandler([&] {
            circle->position = circle->getWorldPosition();
            circle->removeFromParentNode();
            Engine::main->addNode(circle);
            Animation* circleDim = new Animation("circle dim " + to_string(reinterpret_cast<long>(this)), 1.5);
            circleDim->setVec3Animation(&circle->shader->multiplyColor, vec3(0));
            Engine::main->playAnimation(circleDim);
        });
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
