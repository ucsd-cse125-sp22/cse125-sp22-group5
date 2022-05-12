//
//  GroundSmash.cpp
//  KGLEngine
//
//  Created by futian Zhang on 5/11/22.
//

#include "GroundSmash.hpp"

GroundSmash::GroundSmash(){
    this->position = vec3(0);
    this->eulerAngles = vec3(1);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = true;
    this->damage = 1;
    this->start = false;
    this->name = "Smash Ground";
    this->actionName = "smash ground";
    
    this->stopTime = 3.0f;
    this->waitTime = 0.0f;
    
    this->raiseTime = 0.5f;
    this->holdTime = 1.0f;
    this->smashTime = 0.33f;
    this->downTime = 0.5f;
    this->recoverTime = 0.5f;
    
    this->hammerEmission = vec3(0.68,0.85,0.90);
    
    this->hammerEmissionVariation = -vec3(0.2, 0.2, 0.2);
    
    this->shaderFile = "/Resources/Game/Magic/ThousandBlade/Shader";
    
    this->hammerModelFile = "/Resources/Game/Magic/GroundSmash/hammer.dae";
    this->hammerTextureFile = "/Resources/Game/Magic/GroundSmash/hammer_D.jpg";
    
    this->hammerTexture = new Texture(hammerTextureFile, 2.0f, true);
    
    this->hammerShader = new AlphaShader(shaderFile);
    hammerShader->setTexture("diffuseMap", this->hammerTexture);
    hammerShader->setSemitransparent();
    hammerShader->writeToDepthBuffer = false;
    hammerShader->alpha = 0.0f;
    hammerShader->emissionColor = this->hammerEmission;
    
    this->hammerScale = vec3(0.5);
    this->hammerInitPosition = vec3(-0.1f,0,0.5);
    this->hammerPosition = vec3(-0.1,0,1.5);
    this->hammerAlpha = 0.8;
    
    Projectile* hammer = new Projectile();
    hammer->loadModelFile(this->hammerModelFile);
    hammer->geometries[0]->setShader(hammerShader);
    hammer->geometries[0]->renderingOrder = 990;
    hammer->geometries[0]->lightingBitMask = 0;
    hammer->isDisabled = true;
    hammer->scale = vec3(0);
    hammer->damage = this->damage;
    hammer->position = this->hammerInitPosition;
    hammer->eulerAngles = vec3(180,0,0);
    
    vec3 relativePosition = vec3(-0.5,0,-1.5);
    
    shiningTexture = new Texture("/Resources/Game/Magic/ThousandBlade/shining.png", 2.0f, true);
    
    shiningParticle = new ParticleNode(4000, 1.0f, 1.0f);
    shiningParticle->position = relativePosition;
    shiningParticle->initialRotationVariation = 360.0f;
    shiningParticle->speedFactor = 0.1;
    shiningParticle->texture = shiningTexture;
    shiningParticle->setMaxAmount(400);
    shiningParticle->isAdditive = true;
    shiningParticle->renderingOrder = 995;
    shiningParticle->initialScale = 0.25;
    shiningParticle->initialScaleVariation = 0.05;
    shiningParticle->initialSpeed = 10.0f;
    shiningParticle->speedAcceleration = -0.6f;
    shiningParticle->speedAccelerationVariation = 0.1f;
    shiningParticle->spreadingAngle = 90;
    shiningParticle->rotatingSpeedVariation = 100;
    shiningParticle->setColorAnimation(vec4(this->hammerEmission, 1.0f), 0.0f);
    shiningParticle->setColorAnimation(vec4(this->hammerEmission + this->hammerEmissionVariation, 0.0f), 1.5f);
    hammer->addChildNode(shiningParticle);
    
    spreadTexture = new Texture("/Resources/Game/Magic/GroundSmash/spread.png", 2.0f, true);
    
    spreadParticle = new ParticleNode(500, 0.5, 0.1);
    spreadParticle->position = relativePosition;
    spreadParticle->setMaxAmount(100);
    spreadParticle->isAdditive = true;
    spreadParticle->texture = spreadTexture;
    spreadParticle->initialRotationVariation = 90;
    spreadParticle->initialScaleVariation = 0.2;
    spreadParticle->speedAccelerationVariation = 1.0f;
    spreadParticle->renderingOrder = 996;
    spreadParticle->setColorAnimation(vec4(this->hammerEmission + this->hammerEmissionVariation, 0.5f), 0.0f);
    spreadParticle->setColorAnimation(vec4(this->hammerEmission, 0.0f), 0.75f);
    hammer->addChildNode(spreadParticle);
    
    explosion = new ParticleNode(300, 1.0f, 0.0f);
    explosion->position = relativePosition;
    explosion->setColorAnimation(vec4(this->hammerEmission, 0.0f), 0.0f);
    explosion->setColorAnimation(vec4(this->hammerEmission + this->hammerEmissionVariation, 0.9f), 0.2f);
    explosion->setColorAnimation(vec4(this->hammerEmission + this->hammerEmissionVariation * 2.0f, 0.9f), 0.6f);
    explosion->setColorAnimation(vec4(this->hammerEmission + this->hammerEmissionVariation * 3.0f, 0.0f), 1.0f);
    explosion->texture = new Texture("/Resources/Game/Effects/Explosion1.png");
    explosion->isAdditive = true;
    explosion->initialRotationVariation = 60;
    explosion->renderingOrder = 1010;
    explosion->initialScale = 1.0;
    explosion->initialScale = 2.0;
    explosion->scalingSpeed = 7;
    explosion->setMaxAmount(50);
    explosion->spreadingAngle = 90;
    explosion->setSpriteSheetAnimation(7, 12, 40, 120, 40);
    hammer->addChildNode(explosion);
    
    this->projectiles.push_back(hammer);
    this->addChildNode(hammer);
}
GroundSmash::~GroundSmash(){
    delete hammerShader;
    delete hammerTexture;
    delete projectiles[0];
}
void GroundSmash::updateMagic(){
    if (start){
        this->projectiles[0]->start = this->projectiles[0]->getWorldPosition() + this->projectiles[0]->getLeftVectorInWorld() * 2.0f;
        this->projectiles[0]->end = this->projectiles[0]->getWorldPosition() + this->projectiles[0]->getRightVectorInWorld() * 4.0f;
    }
}
void GroundSmash::play(CharNode* character){
    if (!start){
        this->start = true;
        this->isDisabled = false;
        this->projectiles[0]->scale = vec3(0);
        this->hammerShader->alpha = 0;
        this->projectiles[0]->isDisabled = false;
        character->rightHand->addChildNode(this);
        this->projectiles[0]->start = this->projectiles[0]->getWorldPosition() + this->projectiles[0]->getLeftVectorInWorld() * 2.0f;
        this->projectiles[0]->end = this->projectiles[0]->getWorldPosition() + this->projectiles[0]->getRightVectorInWorld() * 4.0f;
        
        shiningParticle->stop();
        spreadParticle->stop();
        explosion->stop();
        
        Animation* raise = new Animation(this->name + " raise", this->raiseTime);
        raise->setCompletionHandler([&]{
            
            Animation* speed = new Animation(this->name + " speed", this->holdTime);
            speed->setEaseOutTimingMode();
            speed->setFloatAnimation(&this->shiningParticle->speedFactor, 1.0f);
            Engine::main->playAnimation(speed);
            
            Animation* show = new Animation(this->name + " show", this->holdTime);
            show->setEaseOutTimingMode();
            show->setFloatAnimation(&this->hammerShader->alpha, this->hammerAlpha);
            Engine::main->playAnimation(show);
            
            Animation* color = new Animation(this->name + " color", this->holdTime);
            color->setEaseOutTimingMode();
            color->setVec3Animation(&this->hammerShader->emissionColor, this->hammerEmission + this->hammerEmissionVariation);
            Engine::main->playAnimation(color);
            
            Animation* scale = new Animation(this->name + " scale", this->holdTime);
            scale->setEaseOutTimingMode();
            scale->setVec3Animation(&this->projectiles[0]->scale, this->hammerScale);
            Engine::main->playAnimation(scale);
            
            Animation* translate = new Animation(this->name + " translate", this->holdTime);
            translate->setEaseInTimingMode();
            translate->setVec3Animation(&this->projectiles[0]->position, this->hammerPosition);
            Engine::main->playAnimation(translate);
            
            Animation* down = new Animation(this->name + " down", this->holdTime + this->downTime - 0.2f);
            down->setCompletionHandler([&]{
                explosion->play();
                spreadParticle->play();
                
                shiningParticle->play();
            });
            Engine::main->playAnimation(down);
            
            Animation* wait = new Animation(this->name + " wait", this->holdTime + this->downTime + this->smashTime);
            wait->setCompletionHandler([&]{
                this->projectiles[0]->canDamage = true;
                
                Animation* disappear = new Animation(this->name + " disappear", this->recoverTime);
                disappear->setEaseInTimingMode();
                disappear->setFloatAnimation(&this->hammerShader->alpha, 0);
                Engine::main->playAnimation(disappear);
            });
            Engine::main->playAnimation(wait);
        });
        Engine::main->playAnimation(raise);
        
        Animation* cleanup = new Animation(this->name + " cleanup", this->stopTime);
        cleanup->setCompletionHandler([&]{
            this->start = false;
            this->isDisabled = true;
            this->projectiles[0]->isDisabled = true;
            this->projectiles[0]->scale = vec3(0);
            this->projectiles[0]->position = this->hammerInitPosition;
            this->hammerShader->emissionColor = this->hammerEmission;
            this->hammerShader->alpha = 0;
            this->shiningParticle->reset();
            this->spreadParticle->reset();
            this->explosion->reset();
            this->shiningParticle->speedFactor = 0.1;
            this->removeFromParentNode();
        });
        Engine::main->playAnimation(cleanup);
    }
}
void GroundSmash::tryDamage(CharNode* character){
    if (this->start){
        this->projectiles[0]->tryDamageChar(character);
    }
}
