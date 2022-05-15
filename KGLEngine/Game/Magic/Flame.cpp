//
//  Flame.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/11/22.
//

#include "Flame.hpp"

Flame::Flame() {
    this->damage = 1.5;
    this->start = false;
    this->actionName = "cast magic 1";
    this->flame = new ParticleNode(300, 1.5f, 0.0f);
    this->flame->setColorAnimation(vec4(1.0f, 0.7f, 0.05f, 0.0f), 0.0f);
    this->flame->setColorAnimation(vec4(1.0f, 0.6f, 0.05f, 0.9f), 0.2f);
    this->flame->setColorAnimation(vec4(1.0f, 0.5f, 0.05f, 0.9f), 0.6f);
    this->flame->setColorAnimation(vec4(1.0f, 0.4f, 0.05f, 0.0f), 1.0f);
    this->flame->texture = new Texture("/Resources/Game/Effects/explosion1.png");
    this->flame->color = vec4(1, 0.4, 0.1, 1);
    this->flame->isAdditive = true;
    this->flame->spreadingAngle = 60;
    this->flame->initialSpeed = 5;
    this->flame->speedAcceleration = -1;
    this->flame->renderingOrder = 1010;
    this->flame->initialScale = 2;
    this->flame->scalingSpeed = 5;
    this->flame->setMaxAmount(60);
    this->flame->setSpriteSheetAnimation(7, 12, 40, 120, 40);
    this->flame->isDisabled = true;
    this->addChildNode(this->flame);
    spark = new ParticleNode(600, 1.2, 0);
    spark->isDisabled = true;
    spark->setMaxAmount(120);
    spark->spreadingAngle = 60;
    this->spark->initialSpeed = 4;
    spark->speedAcceleration = -1.25;
    spark->initialSpeedVariation = 0.5;
    spark->isAdditive = true;
//    spark->setEmissionSphere(0.5, 1);
    spark->renderingOrder = 999l;
    spark->acceleration = vec3(0, -0.3, 0);
    spark->texture = new Texture("/Resources/Game/Effects/Particle1.png");
    spark->initialScale = 0.05;
    spark->scalingSpeed = -0.01;
    spark->initialRotationVariation = 360;
    spark->color = vec4(0.3, 0.4, 1, 1);
    spark->initialScaleVariation = 0.02;
    spark->setColorAnimation(vec4(1, 0.7, 0.1, 1), 0.0f);
    spark->setColorAnimation(vec4(1, 0.4, 0.1, 0), 1.0f);
    this->addChildNode(spark);
}
void Flame::play(CharNode *character) {
    if (!start) {
        this->start = true;
        this->canDamage = true;
        this->position = character->getWorldPosition() + vec3(0, 0.5, 0) + character->modelNode->getRightVectorInWorld() * 2.f;
        this->eulerAngles = character->modelNode->getWorldEulerAngles() - vec3(0, 90, 0);
        this->flame->isDisabled = false;
        this->spark->isDisabled = false;
        this->spark->reset();
        this->flame->reset();
        Animation* coolDown = new Animation("flame magic cool down " + to_string(reinterpret_cast<long>(this)), 0.5);
        coolDown->setCompletionHandler([&] {
            this->start = false;
        });
        Engine::main->playAnimation(coolDown);
    }
}
void Flame::tryDamage(CharNode *character) {
    if (start) {
        
        if (canDamage) {
            vec3 hitpos = this->getWorldPosition();
            if (character->hitbox->testSphere(hitpos + this->getFrontVectorInWorld(), 1.2)) {
                character->receiveDamage(this->damage);
            }
            canDamage = false;
        }
    }
}
