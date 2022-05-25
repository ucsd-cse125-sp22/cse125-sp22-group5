//
//  FireBall.cpp
//
//  Created by Zifan Zhang on 4/29/22.
//  Updated by Kangming Yu on 5/14/22.
//

#include "Game/Magic/FireBall.hpp"

#include <string>
#include <cmath>

#include "Game/Character/CharNode.hpp"
#include "Game/Map/MapSystemManager.hpp"

#define DAMAGE 50

using namespace std;
using namespace glm;

bool FireBall::loaded = false;
ParticleNode* FireBall::metaFireball = NULL;
ParticleNode* FireBall::metaFlame = NULL;
ParticleNode* FireBall::metaExplosion = NULL;
ParticleNode* FireBall::metaSpark = NULL;
LightNode* FireBall::metaLight = NULL;

void FireBall::load() {
    loaded = true;
    metaFireball = new ParticleNode(60, 0.1f, 0.0f);
    metaFireball->renderingOrder = 12.0f;
    metaFireball->isAdditive = true;
    metaFireball->rotatingSpeed = 360.0f;
    metaFireball->rotatingSpeedVariation = 180.0f;
    metaFireball->randomizeRotatingDirection = true;
    metaFireball->initialScale = 0.03f;
    metaFireball->initialScaleVariation = 0.03f;
    metaFireball->texture = new Texture("/Resources/Game/Effects/Core2.png");
    metaFireball->setColorAnimation(vec4(1.0f, 0.4f, 0.0f, 0.0f), 0.0f);
    metaFireball->setColorAnimation(vec4(1.0f, 0.3f, 0.0f, 0.9f), 0.2f);
    metaFireball->setColorAnimation(vec4(1.0f, 0.2f, 0.0f, 0.9f), 0.6f);
    metaFireball->setColorAnimation(vec4(1.0f, 0.1f, 0.0f, 0.0f), 1.0f);
    metaFlame = new ParticleNode(60, 0.5f, 0.3f);
    metaFlame->setEmissionSphere(0.04f, 0.04f);
    metaFlame->renderingOrder = 12.0f;
    metaFlame->isAdditive = true;
    metaFlame->randomizeRotatingDirection = true;
    metaFlame->spreadingAngle = 30.0f;
    metaFlame->randomizeRotatingDirection = true;
    metaFlame->initialScale = 0.03f;
    metaFlame->initialScaleVariation = 0.03f;
    metaFlame->texture = new Texture("/Resources/Game/Effects/Trail3.png");
    metaFlame->scalingSpeed = -0.06;
    metaFlame->rotatingSpeed = 180.0f;
    metaFlame->rotatingSpeedVariation = 90.0f;
    metaFlame->setColorAnimation(vec4(1.0f, 0.4f, 0.0f, 0.0f), 0.0f);
    metaFlame->setColorAnimation(vec4(1.0f, 0.3f, 0.0f, 0.9f), 0.2f);
    metaFlame->setColorAnimation(vec4(1.0f, 0.2f, 0.0f, 0.9f), 0.6f);
    metaFlame->setColorAnimation(vec4(1.0f, 0.1f, 0.0f, 0.0f), 1.0f);
    metaLight = new LightNode(vec3(1, 0.4, 0));
    metaLight->setPointLight(2, 10);
    metaSpark = new ParticleNode(300, 1, 0);
    metaSpark->isDisabled = true;
    metaSpark->setMaxAmount(100);
    metaSpark->spreadingAngle = 360;
    metaSpark->initialSpeed = 3;
    metaSpark->speedAcceleration = -1.25;
    metaSpark->initialSpeedVariation = 0.5;
    metaSpark->isAdditive = true;
    metaSpark->renderingOrder = 999l;
    metaSpark->acceleration = vec3(0, -1, 0);
    metaSpark->texture = new Texture("/Resources/Game/Effects/TeleportParticles.png");
    metaSpark->setSpriteSheetAnimation(1, 8, 8, 1, 0);
    metaSpark->initialScale = 0.1;
    metaSpark->scalingSpeed = -0.05;
    metaSpark->initialRotationVariation = 360;
    metaSpark->color = vec4(0.3, 0.4, 1, 1);
    metaSpark->initialScaleVariation = 0.05;
    metaSpark->setColorAnimation(vec4(1, 0.7, 0.1, 1), 0.0f);
    metaSpark->setColorAnimation(vec4(1, 0.4, 0.1, 0), 1.0f);
    metaExplosion = new ParticleNode(300, 1.3f, 0.0f);
    metaExplosion->setColorAnimation(vec4(1.0f, 0.7f, 0.0f, 0.0f), 0.0f);
    metaExplosion->setColorAnimation(vec4(1.0f, 0.6f, 0.0f, 0.9f), 0.2f);
    metaExplosion->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 0.9f), 0.6f);
    metaExplosion->setColorAnimation(vec4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    metaExplosion->texture = new Texture("/Resources/Game/Effects/Explosion1.png");
    metaExplosion->color = vec4(1, 0.4, 0.1, 1);
    metaExplosion->isAdditive = true;
    metaExplosion->initialRotationVariation = 60;
    metaExplosion->renderingOrder = 1010;
    metaExplosion->initialScale = 0.5;
    metaExplosion->scalingSpeed = 5;
    metaExplosion->setMaxAmount(50);
    metaExplosion->setSpriteSheetAnimation(7, 12, 40, 100, 40);
    metaExplosion->isDisabled = true;
}

FireBall::FireBall(){
    if (!loaded) load();
    start = false;
    canDamage = false;
    this->cooldown = 0;
    this->cost = 0;
    this->position = vec3(0);
    this->acceleration = vec3(0, -0.01, 0);
    this->velocityError = vec3(0);
    this->eulerAngles = vec3(0);
    this->actionName = "cast magic 3";
    this->stopTime = 2.0f;
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = DAMAGE;
    fireball = metaFireball->copy()->convertToParticleNode();
    this->addChildNode(fireball);
    flame = metaFlame->copy()->convertToParticleNode();
    this->addChildNode(flame);
    light = metaLight->copy()->convertToLightNode();
    this->addChildNode(light);
    spark = metaSpark->copy()->convertToParticleNode();
    spark->setSpriteSheetAnimation(1, 8, 8, 1, 0);
    this->addChildNode(spark);
    explosion = metaExplosion->copy()->convertToParticleNode();
    explosion->setSpriteSheetAnimation(7, 12, 40, 100, 40);
    this->addChildNode(explosion);
    createFireball = new Animation("create fireball " + to_string(reinterpret_cast<long>(this)), 0.8);
    createFireball->setFloatAnimation(&fireball->initialScale, 0.5);
    createFlame = new Animation("create flame " + to_string(reinterpret_cast<long>(this)), 0.8);
    createFlame->setFloatAnimation(&flame->initialScale, 0.4);

}
void FireBall::updateMagic(){
    if (threwOut) {
        position += velocity * 0.15f;
        velocity += acceleration;
        this->hitWall();
    }
}
void FireBall::play(CharNode* character, int seed){
    if (!start){
        this->removeFromParentNode();
        Node* staffTop = new Node();
        staffTop->position.y = 1;
        character->rightHand->addChildNode(staffTop);
        staffTop->addChildNode(this);
        this->seed = seed;
        this->explosion->isDisabled = true;
        this->caster = character;
        velocity = normalize((character->modelNode->getRightVectorInWorld() + vec3(0, 0.2, 0)) + velocityError);
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
        Animation* fireBallCoolDown = new Animation("fire ball cool down " + to_string(reinterpret_cast<long>(this)), this->cooldown);
        Engine::main->playAnimation(fireBallCoolDown);
        fireBallCoolDown->setCompletionHandler([&] {
            start = false;
        });
        this->availableTime = Engine::main->getTime() + cooldown;
    }
}
void FireBall::explode() {
    exploded = true;
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
            this->light->isDisabled = true;
        });
    });
    Engine::main->playAnimation(fireBallLightIntensity);
    fireball->isDisabled = true;
    flame->isDisabled = true;
}
void FireBall::setThrew() {
    threwOut = true;
    canDamage = true;
    this->position = getWorldPosition();
    this->removeFromParentNode();
    Engine::main->addNode(this);
    flame->scalingSpeed = -0.4;
    Animation* threw = new Animation("threw " + to_string(reinterpret_cast<long>(this)), 4);
    this->updateTransform();
    if (this->caster->isLocked) {
        this->velocity = normalize((this->caster->target->getWorldPosition() - this->getWorldPosition()) + velocityError * 5.f);
        float len = distance(this->caster->target->getWorldPosition(), this->getWorldPosition());
        float tick = len * 10;
        float up = 0.01 * tick / 2;
        this->velocity.y += fmin(up, 0.71);
    }
    threw->setCompletionHandler([&] {
        if (start) {
            canDamage = false;
            explodeDamage = true;
            if (!exploded) {
                explode();
            }
        }
    });
    Engine::main->playAnimation(threw);
}
void FireBall::tryDamage(CharNode *character) {
    if (!explodeDamage && canDamage) {
        if (character->hitbox->testHit(this->getWorldPosition(), vec3(vec4(this->position + this->velocity, 1) * this->getWorldTransform()))) {
            character->receiveDamage(this->damage);
            canDamage = false;
            explodeDamage = true;
            if (!exploded) {
                explode();
            }
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
        HitInfo hitInfo;
        this->updateTransform();
        if (MapSystemManager::Instance()->hitTest(this->position, this->position + this->velocity, hitInfo)) {
            canDamage = false;
            explodeDamage = true;
            threwOut = false;
            if (!exploded) {
                explode();
            }
        }
    }
}
