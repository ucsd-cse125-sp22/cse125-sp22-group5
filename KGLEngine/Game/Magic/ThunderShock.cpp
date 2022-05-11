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
        this->updateTransform();
        for (int k = 0; k < lightnings.size(); k++) {
            lightnings[k]->updateTransform();
            lightnings[k]->reset();
            lightnings[k]->isDisabled = false;
        }
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
