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

#define DAMAGE 50
#define COOLDOWN 6
#define COST 400

using namespace std;
using namespace glm;

bool Storm::loaded = false;
ParticleNode* Storm::metaCloud = NULL;
ParticleNode* Storm::metaDust = NULL;
ParticleNode* Storm::metaHail = NULL;
ParticleNode* Storm::metaLightning = NULL;
ParticleNode* Storm::metaShiny = NULL;
LightNode* Storm::metaLight = NULL;
AudioBuffer* Storm::stormSound = NULL;
AudioBuffer* Storm::electricSound = NULL;
AudioBuffer* Storm::castSound = NULL;
void Storm::load() {
    loaded = true;
    metaCloud = new ParticleNode(200, 1.0f, 0.0f);
//    cloud->position = vec3(0.5f,0,0);
    metaCloud->texture = new Texture("/Resources/Game/Magic/StoneBlast/cloud.png");
    metaCloud->setMaxAmount(1000);
    metaCloud->initialScaleVariation = 1.0;
    metaCloud->renderingOrder = 990;
    metaCloud->useLocalSpace = true;
    metaCloud->setColorAnimation(vec4(0.8, 0.8, 0.8, 0), 0);
    metaCloud->setColorAnimation(vec4(0.8, 0.8, 0.8, 0.3), 0.5);
    metaCloud->setColorAnimation(vec4(0.8, 0.8, 0.8, 0), 1);
    metaDust = new ParticleNode(200, 1.0f, 0.0f);
    metaDust->texture = new Texture("/Resources/Game/Magic/StoneBlast/cloud.png");
    metaDust->setMaxAmount(1000);
    metaDust->initialScaleVariation = 1.0;
    metaDust->renderingOrder = 990;
    metaDust->useLocalSpace = true;
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
    metaHail->initialRotationVariation = 360;
    metaHail->initialScaleVariation = 0.05;
    metaHail->setColorAnimation(vec4(0.5, 0.6, 1, 0), 0);
    metaHail->setColorAnimation(vec4(0.5, 0.6, 1, 0.7), 0.5);
    metaHail->setColorAnimation(vec4(0.5, 0.6, 1, 0), 1);
    metaLightning = new ParticleNode(10, 0.3, 0);
    metaLightning->isAdditive = true;
    metaLightning->renderingOrder = 999l;
    metaLightning->acceleration = vec3(0, -1, 0);
    metaLightning->texture = new Texture("/Resources/Game/Effects/Lightning5-sheet.png");
    metaLightning->setSpriteSheetAnimation(5, 5, 25, 1, 0);
    metaLightning->initialRotation = 90;
    metaLightning->initialRotationVariation = 30;
    metaLightning->initialScale = 1.9;
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 0), 0);
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 0.9), 0.5);
    metaLightning->setColorAnimation(vec4(0.2, 0.2, 1, 0), 1);
    metaShiny = new ParticleNode(200, 1.5, 0);
    metaShiny->texture = new Texture("/Resources/Game/Effects/Particle1.png");
    metaShiny->renderingOrder = 1000;
    metaShiny->setEmissionStorm(0, 4, 1);
    metaShiny->eulerAngles = vec3(0,0,90);
    metaShiny->setMaxAmount(200);
    metaShiny->initialSpeed = 0.8f;
    metaShiny->initialSpeedVariation = 0.025f;
    metaShiny->initialScale = 0.1;
    metaShiny->initialScaleVariation = 0.05;
    metaShiny->accelerationVariation = vec3(0.1,0.8,0.1);
    metaShiny->setColorAnimation(vec4(0.5, 0.6, 1, 0), 0);
    metaShiny->setColorAnimation(vec4(0.5, 0.6, 1, 1), 0.5);
    metaShiny->setColorAnimation(vec4(0.5, 0.6, 1, 0), 1);
    metaShiny->isAdditive = true;
    metaShiny->isDisabled = true;
    stormSound = new AudioBuffer("/Resources/Game/Sound/Neutral_Ice_Loop.wav");
    electricSound = new AudioBuffer("/Resources/Game/Sound/Neutral_Electric_Storm_Loop.wav");
    castSound = new AudioBuffer("/Resources/Game/Sound/Neutral_Ice_Cast.wav");
}
Storm::Storm() {
    if(!loaded) load();
    this->loadAudioBuffer("storm sound", stormSound, 2.0f, 1.0f);
    this->changeAudioVolume("storm sound", 0, 0);
    this->sounds["storm sound"].setLoop(true);
    this->loadAudioBuffer("electric sound", electricSound, 2.0f, 1.0f);
    this->changeAudioVolume("electric sound", 0, 0);
    this->sounds["electric sound"].setLoop(true);
    this->loadAudioBuffer("cast", castSound, 2.0f, 1.0f);
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
    spinning->addChildNode(hail);
    spinning->addChildNode(lightning);
    start = false;
    Engine::main->addNode(this);
    this->availableTime = 0;
    cooldown = COOLDOWN;
    damage = DAMAGE;
    cost = COST;
    this->circle = new Circle();
    this->circle->setColor(vec3(0.5, 0.7, 1));
    Engine::main->addNode(circle);
    this->circle->isDisabled = true;
    this->shiny = metaShiny->copy()->convertToParticleNode();
    Engine::main->addNode(shiny);
}
void Storm::play(CharNode *character, int seed) {
    if (!start) {
        this->playAudio("storm sound");
        this->changeAudioVolume("storm sound", 1, 1);
        this->playAudio("electric sound");
        this->changeAudioVolume("electric sound", 1, 1);
        this->playAudio("cast");
        start = true;
        caster = character;
        velocity = normalize(character->modelNode->getRightVectorInWorld() * vec3(1, 0, 1));
        position = character->headTop->getWorldPosition();
        spinning->isDisabled = false;
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
        circle->isDisabled = false;
        this->circle->setColor(vec3(0.8, 1, 1.3));
        circle->position = character->getWorldPosition() + vec3(0, 1.6, 0);
        circle->scale = vec3(1);
        shiny->position = character->getWorldPosition();
        shiny->isDisabled = false;
        shiny->reset();
        Animation* circleExpand = new Animation("circle expand " + to_string(reinterpret_cast<long>(this)), 0.6);
        circleExpand->setVec3Animation(&circle->scale, vec3(2));
        Engine::main->playAnimation(circleExpand);
        circleExpand->setCompletionHandler([&] {
            circle->position = circle->getWorldPosition();
            circle->removeFromParentNode();
            Engine::main->addNode(circle);
            Animation* circleFall = new Animation("circle fall " + to_string(reinterpret_cast<long>(this)), 0.2);
            circleFall->setVec3Animation(&circle->position, this->caster->getWorldPosition() + vec3(0, 0.1, 0));
            circleFall->setEaseInTimingMode();
            circleFall->setCompletionHandler([&] {
                Animation* circleDim = new Animation("circle dim " + to_string(reinterpret_cast<long>(this)), 1.5);
                circleDim->setVec3Animation(&circle->shader->multiplyColor, vec3(0));
                Engine::main->playAnimation(circleDim);
            });
            Engine::main->playAnimation(circleFall);
            Animation* circleExpand2 = new Animation("circle expand 2 " + to_string(reinterpret_cast<long>(this)), 0.2);
            circleExpand2->setVec3Animation(&circle->scale, vec3(6));
            circleExpand2->setEaseInTimingMode();
            Engine::main->playAnimation(circleExpand2);
        });
        Animation* casting = new Animation("casting storm " + to_string(reinterpret_cast<long>(this)), 0.6);
        Animation* expanding = new Animation("expanding storm " + to_string(reinterpret_cast<long>(this)), 6);
        expanding->setCompletionHandler([&] {
            this->changeAudioVolume("storm sound", 0, 1);
            this->changeAudioVolume("electric sound", 0, 1);
        });
        expanding->setEaseOutTimingMode();
        expanding->setFloatAnimation(&radius, 1.5);
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
            lightning->isDisabled = true;
        });
        this->availableTime = Engine::main->getTime() + cooldown;
    }
}
void Storm::updateMagic() {
    spinning->eulerAngles.y += 5;
    if (spinning->eulerAngles.y > 360) spinning->eulerAngles.y -= 360;
    if (start) {
        spinning->position.y = radius * 2;
        lightning->initialScale = radius * 2;
        cloud->initialScale = radius * 4;
        dust->initialScale = radius * 4;
        dust->position.y = - spinning->position.y - 0.2;
        lightning->position.y = radius;
        lightning->setEmissionBox(vec3(radius * 4, radius, radius * 4));
        cloud->setEmissionStorm(radius * 2, radius * 4, radius * 2);
        dust->setEmissionStorm(radius * 3, radius * 5, radius);
        hail->setEmissionStorm(radius, radius * 6, radius * 2);
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
