//
//  FireBall.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/29/22.
//

#include "FireBall.hpp"

FireBall::FireBall(){
    start = false;
    canDamage = false;
    this->position = vec3(0);
    this->acceleration = vec3(0, -0.004, 0);
    this->eulerAngles = vec3(0);
    this->actionName = "cast magic 1";
    this->stopTime = 2.0f;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    fireball = new ParticleNode(50, 0.3f, 0.0f);
    fireball->renderingOrder = 12.0f;
    fireball->isAdditive = true;
    fireball->rotatingSpeed = 360.0f;
    fireball->rotatingSpeedVariation = 180.0f;
    fireball->randomizeRotatingDirection = true;
    fireball->initialScale = 0.03f;
    fireball->initialScaleVariation = 0.03f;
    fireball->texture = new Texture("/Resources/Game/Effects/Core2.png");;
    fireball->setColorAnimation(vec4(1.0f, 0.4f, 0.0f, 0.0f), 0.0f);
    fireball->setColorAnimation(vec4(1.0f, 0.3f, 0.0f, 0.9f), 0.2f);
    fireball->setColorAnimation(vec4(1.0f, 0.2f, 0.0f, 0.9f), 0.6f);
    fireball->setColorAnimation(vec4(1.0f, 0.1f, 0.0f, 0.0f), 1.0f);
    this->addChildNode(fireball);
    flame = new ParticleNode(120, 0.5f, 0.3f);
    flame->setEmissionSphere(0.04f, 0.04f);
    flame->renderingOrder = 12.0f;
    flame->isAdditive = true;
    flame->randomizeRotatingDirection = true;
    flame->spreadingAngle = 30.0f;
    flame->randomizeRotatingDirection = true;
    flame->initialScale = 0.03f;
    flame->initialScaleVariation = 0.03f;
    flame->texture = new Texture("/Resources/Game/Effects/Trail3.png");
    flame->scalingSpeed = -0.06;
    flame->rotatingSpeed = 180.0f;
    flame->rotatingSpeedVariation = 90.0f;
    flame->setColorAnimation(vec4(1.0f, 0.4f, 0.0f, 0.0f), 0.0f);
    flame->setColorAnimation(vec4(1.0f, 0.3f, 0.0f, 0.9f), 0.2f);
    flame->setColorAnimation(vec4(1.0f, 0.2f, 0.0f, 0.9f), 0.6f);
    flame->setColorAnimation(vec4(1.0f, 0.1f, 0.0f, 0.0f), 1.0f);
    this->addChildNode(flame);
    light = new LightNode(vec3(1, 0.4, 0));
    light->setPointLight(2, 10);
    this->addChildNode(light);
    spark = new ParticleNode(300, 1, 0);
    spark->isDisabled = true;
    spark->setMaxAmount(100);
    spark->spreadingAngle = 360;
    spark->initialSpeed = 3;
    spark->speedAcceleration = -1.25;
    spark->initialSpeedVariation = 0.5;
    spark->isAdditive = true;
//    spark->setEmissionSphere(0.5, 1);
    spark->renderingOrder = 999l;
    spark->acceleration = vec3(0, -1, 0);
    spark->texture = new Texture("/Resources/Game/Effects/TeleportParticles.png");
    spark->setSpriteSheetAnimation(1, 8, 8, 1, 0);
    spark->initialScale = 0.1;
    spark->scalingSpeed = -0.05;
    spark->initialRotationVariation = 360;
    spark->color = vec4(0.3, 0.4, 1, 1);
    spark->initialScaleVariation = 0.05;
    spark->setColorAnimation(vec4(1, 0.7, 0.1, 1), 0.0f);
    spark->setColorAnimation(vec4(1, 0.4, 0.1, 0), 1.0f);
    this->addChildNode(spark);
    explosion = new ParticleNode(300, 1.3f, 0.0f);
    explosion->setColorAnimation(vec4(1.0f, 0.7f, 0.0f, 0.0f), 0.0f);
    explosion->setColorAnimation(vec4(1.0f, 0.6f, 0.0f, 0.9f), 0.2f);
    explosion->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 0.9f), 0.6f);
    explosion->setColorAnimation(vec4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    explosion->texture = new Texture("/Resources/Game/Effects/Explosion1.png");
    explosion->color = vec4(1, 0.4, 0.1, 1);
    explosion->isAdditive = true;
    explosion->initialRotationVariation = 60;
    explosion->renderingOrder = 1010;
    explosion->initialScale = 0.5;
    explosion->scalingSpeed = 4;
    explosion->setMaxAmount(50);
    explosion->setSpriteSheetAnimation(7, 12, 40, 100, 40);
    explosion->isDisabled = true;
    this->addChildNode(explosion);
    createFireball = new Animation("create fireball " + to_string(reinterpret_cast<long>(this)), 0.8);
    createFireball->setFloatAnimation(&fireball->initialScale, 0.4);
    createFlame = new Animation("create flame " + to_string(reinterpret_cast<long>(this)), 0.8);
    createFlame->setFloatAnimation(&flame->initialScale, 0.35);
    createFireball->setCompletionHandler([&]{
        threwOut = true;
        canDamage = true;
        this->position = getWorldPosition();
        this->removeFromParentNode();
        engine->addNode(this);
        flame->scalingSpeed = -0.4;
        Animation* threw = new Animation("threw " + to_string(reinterpret_cast<long>(this)), 4);
        this->updateTransform();
        if (this->caster->isLocked) {
            this->velocity = normalize((this->caster->target->getWorldPosition() - this->getWorldPosition()) * vec3(1, 0, 1));
            float len = distance(this->caster->target->getWorldPosition(), this->getWorldPosition());
            float speed = length(this->velocity) * 0.1f;
            float tick = len / speed;
            float up = 0.004 * tick / 2;
            this->velocity.y += fmin(up, 0.71);
        }
        threw->setCompletionHandler([&] {
            if (start) {
                canDamage = false;
                exploded = true;
                explodeDamage = true;
            }
        });
        Engine::main->playAnimation(threw);
    });

}
void FireBall::updateMagic(){
    if (threwOut) {
        position += velocity * 0.1f;
        velocity += acceleration;
        this->hitWall();
    }
    if (exploded) {
        exploded = false;
        spark->isDisabled = false;
        spark->reset();
        explosion->reset();
        explosion->isDisabled = false;
        Animation* fireBallLightIntensity = new Animation("fire ball light intensity 1 " + to_string(reinterpret_cast<long>(this)), 0.15);
        fireBallLightIntensity->setEaseInTimingMode();
        fireBallLightIntensity->setVec3Animation(&this->light->colorFactor, vec3(40, 16, 0));
        fireBallLightIntensity->setCompletionHandler([&] {
            Animation* fireBallLightIntensity2 = new Animation("fire ball light intensity 2 " + to_string(reinterpret_cast<long>(this)), 0.15);
            fireBallLightIntensity2->setEaseOutTimingMode();
            fireBallLightIntensity2->setVec3Animation(&this->light->colorFactor, vec3(0, 0, 0));
            Engine::main->playAnimation(fireBallLightIntensity2);
            fireBallLightIntensity2->setCompletionHandler([&] {
                canDamage = true;
                start = false;
                this->light->isDisabled = true;
            });
        });
        Engine::main->playAnimation(fireBallLightIntensity);
        fireball->isDisabled = true;
        flame->isDisabled = true;
    }
}
void FireBall::play(CharNode* character){
    if (!start){
        this->explosion->isDisabled = true;
        this->caster = character;
        velocity = character->modelNode->getRightVectorInWorld() + vec3(0, 0.2, 0);
        this->spark->isDisabled = true;
        threwOut = false;
        explodeDamage = false;
        flame->initialScale = 0.03f;
        this->exploded = false;
        fireball->initialScale = 0.03f;
        fireball->scalingSpeed = 0.0f;
        fireball->scalingSpeedVariation = 0.0f;
        this->position = vec3(0);
        this->start = true;
        this->isDisabled = false;
        fireball->isDisabled = false;
        flame->isDisabled = false;
        this->light->isDisabled = false;
        this->light->colorFactor = vec3(1, 0.4, 0);
        Engine::main->playAnimation(createFlame);
        Engine::main->playAnimation(createFireball);
    }
}
void FireBall::tryDamage(CharNode *character) {
    if (!explodeDamage && canDamage) {
        if (character->hitbox->testHit(this->getWorldPosition(), vec3(vec4(this->position + this->velocity, 1) * this->getWorldTransform()))) {
            character->receiveDamage(this->damage);
            canDamage = false;
            exploded = true;
            explodeDamage = true;
        }
    }
    if (explodeDamage && canDamage) {
        if (character->hitbox->testSphere(this->getWorldPosition(), 0.9)) {
            character->receiveDamage(this->damage);
        }
        canDamage = false;
    }
}
void FireBall::hitWall() {
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
FireBall::~FireBall(){
    
}
