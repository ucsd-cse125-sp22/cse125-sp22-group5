//
//  ThunderShock.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/10/22.
//

#include "ThunderShock.hpp"

ThunderShock::ThunderShock() {
    start = false;
    canDamage = false;
    this->position = vec3(0);
    this->eulerAngles = vec3(0);
    this->actionName = "cast magic 1";
    this->stopTime = 2.0f;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    Particle3DNode* discharge = new Particle3DNode("/Resources/Game/Effects/Sheet3.dae", 50, 0.8f, 0.3f);
    discharge->setMaxAmount(20);
    discharge->setEmissionSphere(0, 1.5);
    discharge->isDisabled = true;
    discharge->eulerAngles.z = 90;
    discharge->color = vec4(0.9, 0.9, 0.3, 1);
    discharge->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
    discharge->setSpriteSheetAnimation(5, 5, 20, 28, 4);
    discharge->initialRotationVariation = vec3(180, 45, 45);
    discharge->initialScaleVariation = vec3(0.5, 0, 0.5);
    discharge->initialSpeedVariation = 1;
    discharge->renderingOrder = 2000;
    discharge->useLocalSpace = true;
    discharge->isAdditive = true;
    this->addChildNode(discharge);
    this->base = discharge;
    this->light = new LightNode(vec3(0.5f, 0.5f, 0.2f));
    this->light->setPointLight(1.0f, 8.0f);
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
        Particle3DNode* lightning = new Particle3DNode("/Resources/Game/Effects/Sheet3.dae", 100, 0.2f, 0.3f);
        lightning->color = vec4(0.9, 0.9, 0.3, 1);
        lightning->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
        lightning->isAdditive = true;
        lightning->setMaxAmount(20);
        lightning->renderingOrder = 1010;
        lightning->initialScale = vec3(6, 1, 2 - 0.35 * k);
        lightning->initialScaleVariation = vec3(0, 0, 0);
        lightning->initialRotationVariation = vec3(180, 10 - 2 * k, 10 - 2 * k);
        lightning->setEmissionSphere(0, 0.5 - 0.1 * k);
        lightning->useLocalSpace = true;
        lightning->setSpriteSheetAnimation(5, 5, 20, 28, 4);
        lightning->isDisabled = true;
        lightningNode->addChildNode(lightning);
        lightnings.push_back(lightning);
    }
}

void ThunderShock::play(CharNode* character){
    if (!start){
        this->caster = character;
        this->light->colorFactor = vec3(20.0f, 20.0f, 5.0f);
        this->updateTransform();
        this->base->isDisabled = false;
        this->light->isDisabled = false;
        this->base->reset();
        Animation* shock = new Animation("shock " + to_string(reinterpret_cast<long>(this)), 0.5);
        shock->setCompletionHandler([&] {
            this->canDamage = true;
            for (int k = 0; k < this->lightnings.size(); k++) {
                this->lightnings[k]->updateTransform();
                this->lightnings[k]->reset();
                this->lightnings[k]->isDisabled = false;
            }
            this->light->colorFactor *= 60;
            Animation* dim = new Animation("thunder shock dim " + to_string(reinterpret_cast<long>(this)), 0.5);
            dim->setVec3Animation(&this->light->colorFactor, vec3(0));
            dim->setCompletionHandler([&] {
                this->light->isDisabled = true;
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
            canDamage = false;
        }
    }
}
