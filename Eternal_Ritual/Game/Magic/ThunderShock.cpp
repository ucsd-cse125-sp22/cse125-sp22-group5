//
//  ThunderShock.cpp
//
//  Created by Zifan Zhang on 5/10/22.
//  Updated by Kangming Yu on 5/16/22.
//

#include "Game/Magic/ThunderShock.hpp"

#include <string>

#include "Game/Character/CharNode.hpp"

#define DAMAGE 100

using namespace std;
using namespace glm;

bool ThunderShock::loaded = false;
LightNode* ThunderShock::metaLight = NULL;
Particle3DNode* ThunderShock::metaBase = NULL;
Particle3DNode* ThunderShock::metaLightning = NULL;
AudioBuffer* ThunderShock::electricImpact = NULL;

void ThunderShock::load() {
    metaBase = new Particle3DNode(50, 0.8f, 0.3f);
    metaBase->loadModelFile("/Resources/Game/Effects/Sheet3.dae");
    metaBase->setMaxAmount(20);
    metaBase->setEmissionSphere(0, 1.5);
    metaBase->isDisabled = true;
    metaBase->eulerAngles.z = 90;
    metaBase->color = vec4(0.9, 0.9, 0.3, 1);
    metaBase->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
    metaBase->setSpriteSheetAnimation(5, 5, 20, 28, 4);
    metaBase->initialRotationVariation = vec3(180, 45, 45);
    metaBase->initialScaleVariation = vec3(0.5, 0, 0.5);
    metaBase->initialSpeedVariation = 1;
    metaBase->renderingOrder = 2000;
    metaBase->useLocalSpace = true;
    metaBase->isAdditive = true;
    metaLightning = new Particle3DNode(100, 0.2f, 0.3f);
    metaLightning->loadModelFile("/Resources/Game/Effects/Sheet3.dae");
    metaLightning->color = vec4(0.9, 0.9, 0.3, 1);
    metaLightning->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
    metaLightning->isAdditive = true;
    metaLightning->setMaxAmount(20);
    metaLightning->renderingOrder = 1010;
    metaLightning->initialScaleVariation = vec3(0, 0, 0);
    metaLightning->useLocalSpace = true;
    metaLightning->setSpriteSheetAnimation(5, 5, 20, 28, 4);
    metaLightning->isDisabled = true;
    electricImpact = new AudioBuffer("/Resources/Game/Sound/Neutral_Electric_Impact_02.wav");
}

ThunderShock::ThunderShock() {
    if (!loaded) load();
    start = false;
    canDamage = false;
    this->loadAudioBuffer("electric impact", electricImpact, 2, 1);
    this->changeAudioVolume("electric impact", 0.7f, 0);
    this->position = vec3(0);
    this->eulerAngles = vec3(0);
    this->actionName = "cast magic 1";
    this->stopTime = 1.8f;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = DAMAGE;
    this->base = metaBase->copy()->convertToParticle3DNode();
    this->base->setSpriteSheetAnimation(5, 5, 20, 28, 4);
    this->addChildNode(this->base);
    this->light = new LightNode(vec3(0.5f, 0.5f, 0.2f));
    this->light->setPointLight(2.0f, 4.0f);
    this->light->penetrationRange = 0.0f;
    this->light->position = vec3(0.0f, 0.1f, 0.0f);
    this->light->isDisabled = true;
    this->addChildNode(this->light);
    for (int k = 0; k < 6; k++) {
        Node* lightningNode = new Node();
        this->addChildNode(lightningNode);
        lightningNode->eulerAngles.z = 90;
        lightningNode->isDisabled = false;
        lightningNode->position.y = 6.6 - 1.6 * k;
        Particle3DNode* lightning = metaLightning->copy()->convertToParticle3DNode();
        lightning->initialScale = vec3(6, 1, 2 - 0.35 * k);
        lightning->initialRotationVariation = vec3(180, 10 - 2 * k, 10 - 2 * k);
        lightning->setEmissionSphere(0, 0.5 - 0.1 * k);
        lightning->setSpriteSheetAnimation(5, 5, 20, 28, 4);
        lightning->isDisabled = true;
        lightningNode->addChildNode(lightning);
        lightnings.push_back(lightning);
    }
}

void ThunderShock::play(CharNode* character, int seed){
    if (!start){
        this->start = true;
        this->caster = character;
        this->light->colorFactor = vec3(20.0f, 20.0f, 2.0f);
        this->updateTransform();
        this->base->isDisabled = false;
        this->light->isDisabled = false;
        this->canDamage = false;
        this->base->reset();
        Animation* shock = new Animation("shock " + to_string(reinterpret_cast<long>(this)), 0.5);
        shock->setCompletionHandler([&] {
            this->canDamage = true;
            this->playAudio("electric impact");
            for (int k = 0; k < this->lightnings.size(); k++) {
                this->lightnings[k]->updateTransform();
                this->lightnings[k]->reset();
                this->lightnings[k]->isDisabled = false;
            }
            this->light->colorFactor *= 20;
            Animation* dim = new Animation("thunder shock dim " + to_string(reinterpret_cast<long>(this)), 0.5);
            dim->setVec3Animation(&this->light->colorFactor, vec3(0));
            dim->setCompletionHandler([&] {
                this->light->isDisabled = true;
                this->start = false;
                this->canDamage = false;
            });
            Engine::main->playAnimation(dim);
        });
        Engine::main->playAnimation(shock);
    }
}
void ThunderShock::tryDamage(CharNode *character) {
    if (canDamage) {
        vec3 position = this->getWorldPosition() * vec3(1, 0, 1);
        if (character->hitbox->testHit(position + vec3(0, -99999, 0), position + vec3(0, 99999, 0))) {
            character->receiveDamage(this->damage);
        }
        if (character->hitbox->testSphere(this->getWorldPosition(), 0.1)) {
            character->receiveDamage(this->damage);
        }
        canDamage = false;
    }
}
