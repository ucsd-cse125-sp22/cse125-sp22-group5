//
//  LightningSpear.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/3/22.
//

#include "LightningSpear.hpp"

LightningSpear::LightningSpear(){
    start = false;
    canDamage = false;
    this->position = vec3(0);
    this->acceleration = vec3(0, 0, 0);
    this->eulerAngles = vec3(0);
    this->actionName = "cast magic 1";
    this->stopTime = 2.0f;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    this->spear = new Particle3DNode("/Resources/Game/Effects/Sheet3.dae", 120, 0.35, 0);
    this->spear->color = vec4(0.7, 0.7, 0.2, 0.8);
    this->spear->initialRotationVariation = vec3(180, 0, 0);
    this->spear->randomizeRotatingDirection = true;
    this->spear->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png", 2.0f, true);
    this->spear->setSpriteSheetAnimation(5, 5, 20, 28, 4);
    this->spear->isAdditive = true;
    this->spear->renderingOrder = 1000;
    this->spear->useLocalSpace = true;
    this->addChildNode(this->spear);
    light = new LightNode(vec4(1, 1, 0.2, 1));
    light->setPointLight(15, 30);
    this->addChildNode(light);
    this->radiation = new Particle3DNode("/Resources/Game/Effects/Sheet3.dae", 100, 0.3f, 0.3f);
    this->radiation->color = vec4(1, 1, 0.2, 1);
    this->radiation->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
    this->radiation->isAdditive = true;
    this->radiation->setMaxAmount(60);
    this->radiation->renderingOrder = 1010;
    radiation->initialScale = vec3(0.5, 1, 0.2);
    radiation->initialScaleVariation = vec3(0.3, 0, 0.1);
    radiation->initialRotation = vec3(0, 0, 0);
    radiation->setEmissionSphere(0, 1);
    radiation->spreadingAngle = 90;
    radiation->initialSpeed = 0.1;
    radiation->useLocalSpace = true;
    radiation->speedAccelerationVariation = 0.1;
    this->radiation->setSpriteSheetAnimation(5, 5, 20, 28, 4);
    this->radiation->isDisabled = true;
    this->addChildNode(this->radiation);

}
void LightningSpear::updateMagic(){
    if (threwOut) {
        position += velocity * 0.3f;
        velocity += acceleration;
        this->hitWall();
    }
    if (exploded) {
        exploded = false;
        radiation->isDisabled = false;
        spear->isDisabled = true;
        Animation* lightningSpearLightIntensity = new Animation("lightning spear light intensity 1 " + to_string(reinterpret_cast<long>(this)), 0.1);
        lightningSpearLightIntensity->setFloatAnimation(&light->attenuationExponent, 0.8);
        lightningSpearLightIntensity->setCompletionHandler([&] {
            Animation* lightningSpearLightIntensity2 = new Animation("lightning spear light intensity 2 " + to_string(reinterpret_cast<long>(this)), 0.1);
            lightningSpearLightIntensity2->setFloatAnimation(&light->attenuationExponent, 50);
            Engine::main->playAnimation(lightningSpearLightIntensity2);
            lightningSpearLightIntensity2->setCompletionHandler([&] {
                this->radiation->isDisabled = true;
                canDamage = true;
                this->isDisabled = true;
                start = false;
                this->removeFromParentNode();
            });
        });
        Engine::main->playAnimation(lightningSpearLightIntensity);
        light->setPointLight(0.4, 30);
    }
}
void LightningSpear::play(CharNode* character){
    if (!start){
        this->caster = character;
        this->spear->isDisabled = false;
        this->threwOut = false;
        velocity = character->modelNode->getRightVectorInWorld();
        explodeDamage = false;
        this->spear->initialScale = vec3(0.1);
        exploded = false;
        this->radiation->reset();
        this->position = vec3(0);
        this->eulerAngles = vec3(0);
        this->start = true;
        this->isDisabled = false;
        Animation* createSpear = new Animation("create spear " + caster->name, 0.8);
        createSpear->setVec3Animation(&this->spear->initialScale, vec3(6, 1, 0.6));
        createSpear->setEaseInEaseOutTimingMode();
        createSpear->setCompletionHandler([&]{
            this->eulerAngles = caster->modelNode->getWorldEulerAngles();
            this->eulerAngles.y += 90;
            this->position = this->getWorldPosition();
            this->removeFromParentNode();
            engine->addNode(this);
            this->updateTransform();
            if (this->caster->isLocked) {
                vec3 targetPos = inverse(this->getWorldTransform()) * vec4(this->caster->target->getWorldPosition() + vec3(0, 0.5, 0), 1);
                this->velocity = normalize(targetPos);
                vec3 front = vec3(-1, 0, 0);
                float dotProd = dot(targetPos, front);
                float polarAngle = acos(dot(this->velocity, front));
                vec3 coordinate = normalize(targetPos - front * dotProd);
                
                this->eulerAngles.z -= degrees(polarAngle) * coordinate.y;
                this->eulerAngles.y += degrees(polarAngle) * coordinate.z;
                this->velocity = this->convertLocalVectorToWorld(this->velocity);
            }
            threwOut = true;
            canDamage = true;
            Animation* threw = new Animation("light spear threw " + caster->name, 2);
            threw->setCompletionHandler([&] {
                if (start) {
                    canDamage = false;
                    exploded = true;
                    explodeDamage = true;
                }
            });
            Engine::main->playAnimation(threw);
        });
        Engine::main->playAnimation(createSpear);
    }
}
void LightningSpear::tryDamage(CharNode *character) {
    if (!explodeDamage && canDamage) {
        if (character->hitbox->testHit(this->getWorldPosition(), vec3(vec4(this->position + this->velocity, 1) * this->getWorldTransform()))) {
            character->receiveDamage(this->damage);
            canDamage = false;
            exploded = true;
            explodeDamage = true;
        }
    }
    if (explodeDamage && canDamage) {
        if (character->hitbox->testSphere(this->getWorldPosition(), 2)) {
            character->receiveDamage(this->damage);
        }
        canDamage = false;
    }
}
void LightningSpear::hitWall() {
    if (!explodeDamage && canDamage) {
        vec3 position;
        vec3 normalvec;
        this->updateTransform();
        if (mapSystemManager->hitTest(this->position, this->position + this->velocity, &position, &normalvec)) {
            canDamage = false;
            exploded = true;
            explodeDamage = true;
            threwOut = false;
        }
    }
}
LightningSpear::~LightningSpear(){
    
}
