//
//  Flame.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/11/22.
//

#include "Flame.hpp"

Flame::Flame() {
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
    this->flame->renderingOrder = 1010;
    this->flame->initialScale = 2;
    this->flame->scalingSpeed = 7;
    this->flame->setMaxAmount(60);
    this->flame->setSpriteSheetAnimation(7, 12, 40, 120, 40);
    this->flame->isDisabled = true;
    this->addChildNode(this->flame);
}
void Flame::play(CharNode *character) {
    if (!start) {
        this->start = true;
        this->position = character->getWorldPosition() + vec3(0, 0.5, 0) + character->modelNode->getRightVectorInWorld() * 2.f;
        this->eulerAngles = character->modelNode->getWorldEulerAngles() - vec3(0, 90, 0);
        this->flame->isDisabled = false;
        this->flame->reset();
        Animation* coolDown = new Animation("flame magic cool down", 0.5);
        coolDown->setCompletionHandler([&] {
            this->start = false;
        });
        Engine::main->playAnimation(coolDown);
    }
}
void Flame::tryDamage(CharNode *character) {
    if (start) {
        
    }
}
