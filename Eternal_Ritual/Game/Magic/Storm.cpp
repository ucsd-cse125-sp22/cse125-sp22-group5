//
//  Storm.cpp
//  Eternal_Ritual_Offline
//
//  Created by Zifan Zhang on 5/24/22.
//

#include "Storm.hpp"

#include <string>
#include <cmath>

#include "Game/Character/CharNode.hpp"
#include "Game/Magic/Circle.hpp"
#include "Game/Map/MapSystemManager.hpp"

#define DAMAGE 10
#define COOLDOWN 10
#define COST 400

using namespace std;
using namespace glm;

bool Storm::loaded = false;
ParticleNode* Storm::metaCloud = NULL;
ParticleNode* Storm::metaDust = NULL;
ParticleNode* Storm::metaHail = NULL;
ParticleNode* Storm::metaLightning = NULL;
LightNode* Storm::metaLight = NULL;
AudioBuffer* Storm::stormSound = NULL;
void Storm::load() {
    loaded = true;
    metaCloud = new ParticleNode(200, 1.0f, 0.0f);
//    cloud->position = vec3(0.5f,0,0);
    metaCloud->texture = new Texture("/Resources/Game/Magic/StoneBlast/cloud.png");
    metaCloud->setMaxAmount(1000);
    metaCloud->initialScaleVariation = 1.0;
    metaCloud->renderingOrder = 990;
    metaCloud->useLocalSpace = true;
    metaCloud->initialRotationVariation = 360.0f;
    metaCloud->rotatingSpeedVariation = 180.0f;
    metaCloud->setColorAnimation(vec4(0.8, 0.8, 0.8, 0), 0);
    metaCloud->setColorAnimation(vec4(0.8, 0.8, 0.8, 0.3), 0.5);
    metaCloud->setColorAnimation(vec4(0.8, 0.8, 0.8, 0), 1);

    metaDust = new ParticleNode(200, 1.0f, 0.0f);
    metaDust->texture = new Texture("/Resources/Game/Magic/StoneBlast/cloud.png");
    metaDust->setMaxAmount(1000);
    metaDust->initialScaleVariation = 1.0;
    metaDust->renderingOrder = 990;
    metaDust->useLocalSpace = true;
    metaDust->initialRotationVariation = 360.0f;
    metaDust->rotatingSpeedVariation = 180.0f;
    metaDust->setColorAnimation(vec4(0.5, 0.5, 0.5, 0), 0);
    metaDust->setColorAnimation(vec4(0.5, 0.5, 0.5, 0.7), 0.5);
    metaDust->setColorAnimation(vec4(0.5, 0.5, 0.5, 0), 1);
    
    metaHail = new ParticleNode(200, 2, 0);
    metaHail->setMaxAmount(1000);
    metaHail->useLocalSpace = true;
    metaHail->isAdditive = true;
    metaHail->renderingOrder = 999l;
    metaHail->acceleration = vec3(0, -1, 0);
    metaHail->texture = new Texture("/Resources/Game/Effects/TeleportParticles.png");
    metaHail->setSpriteSheetAnimation(1, 8, 8, 1, 0);
    metaHail->initialScale = 0.2;
    metaHail->scalingSpeed = -0.05;
    
    metaHail->rotatingSpeed = 180;
    metaHail->rotatingSpeedVariation = 90;
    metaHail->randomizeRotatingDirection = true;
    
    metaHail->initialScaleVariation = 0.05;
    metaHail->setColorAnimation(vec4(0.5, 0.6, 1, 0), 0);
    metaHail->setColorAnimation(vec4(0.5, 0.6, 1, 0.7), 0.5);
    metaHail->setColorAnimation(vec4(0.5, 0.6, 1, 0), 1);
    
    metaLightning = new ParticleNode(30, 0.1, 0.05);
    metaLightning->isAdditive = true;
    metaLightning->renderingOrder = 999l;
    metaLightning->acceleration = vec3(0, -1, 0);
    metaLightning->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
    metaLightning->setSpriteSheetAnimation(5, 5, 25, 1, 0);
    metaLightning->initialRotation = 90;
    metaLightning->initialRotationVariation = 30;
    metaLightning->initialScale = 4.0f;
    metaLightning->initialScaleVariation = 2.0f;
    
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 0), 0);
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 1), 0.2);
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 1), 0.8);
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 0), 1);
    
    stormSound = new AudioBuffer("/Resources/Game/Sound/Storm.wav");
}
Storm::Storm() {
    if(!loaded) load();
    this->loadAudioBuffer("storm sound", stormSound, 3.0f, 0.5f);
    this->stopTime = 2.0f;
    this->actionName = "cast magic 2";
    this->cloud = metaCloud->copy()->convertToParticleNode();
    this->dust = metaDust->copy()->convertToParticleNode();
    this->hail = metaHail->copy()->convertToParticleNode();
    hail->setSpriteSheetAnimation(1, 8, 8, 1, 0);
    this->lightning = metaLightning->copy()->convertToParticleNode();
    lightning->setSpriteSheetAnimation(5, 5, 25, 1, 0);
    spinning = new Node();
    this->addChildNode(spinning);
    spinning->isDisabled = true;
    spinning->addChildNode(dust);
    spinning->addChildNode(cloud);
    spinning->addChildNode(lightning);
    fastSpin = new Node();
    this->addChildNode(fastSpin);
    fastSpin->addChildNode(hail);
    fastSpin->isDisabled = true;
    start = false;
    Engine::main->addNode(this);
    this->availableTime = 0;
    cooldown = COOLDOWN;
    damage = DAMAGE;
    cost = COST;
}
void Storm::play(CharNode *character, int seed) {
    if (!start) {
        this->playAudio("storm sound");
        start = true;
        caster = character;
        velocity = normalize(character->modelNode->getRightVectorInWorld() * vec3(1, 0, 1));
        position = character->headTop->getWorldPosition();
        spinning->isDisabled = false;
        fastSpin->isDisabled = false;
        lightning->isDisabled = false;
        cloud->reset();
        dust->reset();
        hail->reset();
        radius = 0.25;
        threw = false;
        lightning->initialScale = radius * 2;
        cloud->initialScale = radius * 4;
        dust->initialScale = radius * 4;
        lightning->setEmissionStorm(0, radius, radius * 2);
        cloud->setEmissionStorm(radius * 2, radius * 4, radius * 2);
        dust->setEmissionStorm(radius * 3, radius * 6, radius);
        hail->setEmissionStorm(radius * 2, radius * 4, radius * 2);
        Animation* casting = new Animation("casting storm " + to_string(reinterpret_cast<long>(this)), 0.6);
        Animation* expanding = new Animation("expanding storm " + to_string(reinterpret_cast<long>(this)), 8.5);
        expanding->setEaseOutTimingMode();
        expanding->setFloatAnimation(&radius, 1.5);
        expanding->setCompletionHandler([&] {
            lightning->isDisabled = true;
        });
        Engine::main->playAnimation(expanding);
        casting->setCompletionHandler([&] {
            threw = true;
            Animation* moving = new Animation("moving storm " + to_string(reinterpret_cast<long>(this)), 5);
//            moving->setEaseOutTimingMode();
            moving->setVec3Animation(&position, position + velocity * 15.f);
            Engine::main->playAnimation(moving);
        });
        Engine::main->playAnimation(casting);
        Animation* stormCoolDown = new Animation("storm cool down " + to_string(reinterpret_cast<long>(this)), this->cooldown);
        Engine::main->playAnimation(stormCoolDown);
        stormCoolDown->setCompletionHandler([&] {
            start = false;
        });
        this->availableTime = Engine::main->getTime() + cooldown;
    }
}
void Storm::updateMagic() {
    spinning->eulerAngles.y += 5;
    fastSpin->eulerAngles.y += 10;
    if (spinning->eulerAngles.y > 360) spinning->eulerAngles.y -= 360;
    if (fastSpin->eulerAngles.y > 360) fastSpin->eulerAngles.y -= 360;
    if (start) {
        spinning->position.y = radius * 2;
        fastSpin->position.y = radius * 2 - 0.2f;
        lightning->initialScale = radius * 2;
        cloud->initialScale = radius * 4;
        dust->initialScale = radius * 4;
        dust->position.y = - spinning->position.y - 0.2;
        lightning->position.y = radius;
        lightning->setEmissionBox(vec3(radius * 4, radius, radius * 4));
        cloud->setEmissionStorm(radius * 2, radius * 4, radius * 2);
        dust->setEmissionStorm(radius * 3, radius * 5, radius);
        hail->setEmissionStorm(radius * 2, radius * 6, radius * 2);
        this->hitWall();
    }
    
}
void Storm::tryDamage(CharNode *character) {
    
    if (start) {
        if (character->hitbox->testSphere(this->getWorldPosition(), radius * 4)) {
            character->receiveDamage(this->damage);
        }
    }
}
void Storm::hitWall() {
    HitInfo hitInfo;
    this->updateTransform();
    if (MapSystemManager::Instance()->hitTest(this->getWorldPosition(), this->getWorldPosition() + this->velocity * radius * 4.f, hitInfo, 7)) {
        Animation* moving = new Animation("moving storm " + to_string(reinterpret_cast<long>(this)), 5);
        Engine::main->playAnimation(moving);
    }
}
