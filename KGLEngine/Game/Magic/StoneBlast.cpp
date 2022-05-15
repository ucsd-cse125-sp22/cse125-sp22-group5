//
//  StoneBlast.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/24/22.
//

#include "StoneBlast.hpp"
#include <glm/gtx/io.hpp>

vec3 eulerToDirection(vec3 euler){
    return normalize(vec3(cos(radians(euler.z))* cos(radians(euler.y)), sin(radians(euler.z))*cos(radians(euler.y)), sin(radians(euler.y))));
}

StoneBlast::StoneBlast(){
    this->name = "StoneBlast";
    this->actionName = "cast magic 2";
    this->stopTime = 2.0f;
    this->waitTime = 0.75f;
    this->position = vec3(0);
    this->eulerAngles = vec3(0);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    this->start = false;
    this->rounds = {0,0,0};
    this->isDisabled = true;
    this->canDamage = false;
    
    this->translatePosition = {vec3(0,5,7), vec3(-3,5,4), vec3(3,5,4), vec3(-3,5,10), vec3(3,5,10)};
    this->rotationPosition = vec3(0,0,-90);
    
    this->circleEmissions = {vec3(0.8,0,-0.6), vec3(0.5,-0.3,0), vec3(0.5,0.5,-0.3), vec3(0.8,-0.3,-0.3), vec3(0,0,0)};
    this->circleVariantion = vec3(0.1f);
    
    circleTexture = new Texture("/Resources/Game/Magic/StoneBlast/Magic Circle.png", 2.0f, true);
    
    AlphaShader* circle_shader = new AlphaShader("/Resources/Game/Magic/ThousandBlade/Shader");
    
    Node* circle = new Node();
    circle->scale = vec3(1.5);
    circle->loadModelFile("/Resources/Game/Magic/StoneBlast/one_face.fbx");
    circle->geometries[0]->setShader(circle_shader);
    circle->geometries[0]->setDoubleSided();
    circle->geometries[0]->renderingOrder = 1000;
    circle->isDisabled = true;
    
    shiningParticleTexture = new Texture("/Resources/Game/Magic/ThousandBlade/shining.png", 2.0f, true);
    
    ParticleNode* shiningParticle = new ParticleNode(20, 0.65f, 0.1f);
    shiningParticle->eulerAngles = vec3(0,0,90);
    shiningParticle->setMaxAmount(20);
    shiningParticle->renderingOrder = 1010;
    shiningParticle->texture = shiningParticleTexture;
    shiningParticle->isAdditive = true;
    shiningParticle->initialSpeed = 8.0f;
    shiningParticle->initialSpeedVariation = 2.0f;
    shiningParticle->initialScale = 0.5;
    shiningParticle->initialScaleVariation = 0.25;
    shiningParticle->accelerationVariation = vec3(0.2);
    shiningParticle->initialRotationVariation = 360.0f;
    shiningParticle->rotatingSpeed = 0.0f;
    shiningParticle->rotatingSpeedVariation = 180;
    
    for (int i = 0; i < 5; i++){
        AlphaShader* newShader = circle_shader->copy();
        newShader->setTexture("diffuseMap", circleTexture);
        newShader->setAdditive();
        newShader->setSemitransparent();
        newShader->writeToDepthBuffer = false;
        newShader->alpha = 0.0f;
        newShader->emissionColor = vec3(0);
        this->circle_shaders.push_back(newShader);
        
        Node* newCircle = circle->copy();
        newCircle->position = this->translatePosition[i];
        newCircle->eulerAngles = this->rotationPosition;
        newCircle->geometries[0]->setShader(newShader);
        magicCircles.push_back(newCircle);
        this->addChildNode(newCircle);
        
        Particle3DNode* arrow = new Particle3DNode("/Resources/Game/Magic/StoneBlast/arrow_simple.dae", 50, 10.0f, 0.0f);
        arrow->color = vec4(0, 0.5f, 1.0f, 1.0f);
        arrow->texture = new Texture("/Resources/Game/Magic/StoneBlast/Arrow_D.png");
        //arrow->isAdditive = true;
        arrow->setMaxAmount(100);
        arrow->renderingOrder = 1010;
        arrow->scale = vec3(0.15, 0.6, 0.15);
        arrow->initialScaleVariation = vec3(0.1, 0.1, 0.1);
        arrow->initialRotation = vec3(0, 0, 0);
        arrow->setEmissionSphere(0, 4);
        arrow->spreadingAngle = 5;
        arrow->initialSpeed = 10;
        arrow->useLocalSpace = true;
        arrow->speedAccelerationVariation = 0.1;
        arrow->eulerAngles = vec3(0,0,0);
        arrow->position = vec3(0,0,0);
        arrow->setColorAnimation(vec4(this->circleEmissions[i], 0.0f), 0.0f);
        arrow->setColorAnimation(vec4(this->circleEmissions[i], 0.9f), 0.2f);
        arrow->setColorAnimation(vec4(this->circleEmissions[i], 0.9f), 0.8f);
        arrow->setColorAnimation(vec4(this->circleEmissions[i], 0.0f), 1.0f);
        newCircle->addChildNode(arrow);
        arrows.push_back(arrow);
        
        ParticleNode* shinning = (ParticleNode*)shiningParticle->copy();
        shinning->setColorAnimation(vec4(vec3(0.0f, 0.5f, 1.0f) + this->circleEmissions[i%5] * 2.0f, 1.0f), 0.0f);
        shinning->setColorAnimation(vec4(vec3(0.0f, 0.5f, 1.0f) + this->circleEmissions[i%5] * 2.0f, 0.0f), 0.75f);
        this->shinnings.push_back(shinning);
        newCircle->addChildNode(shinning);
    }
    
    createMagicCircle = new Animation(this->name + " create magic circle ", 0.5f);
    createMagicCircle->setCompletionHandler([&]{
        for (int i = 0; i < this->magicCircles.size(); i++){
            magicCircles[i]->isDisabled = false;
            arrows[i]->stop();
            Animation* appear = new Animation(this->name + " appear " + to_string(i), 0.5);
            appear->setFloatAnimation(&this->circle_shaders[i]->alpha, 1.0);
            Engine::main->playAnimation(appear);
        }
    });
    
    playArrow = new Animation(this->name + " play arrow ", 1.5f);
    playArrow->setCompletionHandler([&]{
        for (int i = 0; i < this->magicCircles.size(); i++){
            arrows[i]->play();
        }
        this->canDamage = true;
    });
    
    removeMagicCircle = new Animation(this->name + " remove magic circle ", 5.5f);
    removeMagicCircle->setCompletionHandler([&]{
        for (int i = 0; i < this->magicCircles.size(); i++){
            Animation* disappear = new Animation(this->name + " disappear " + to_string(i), 0.5);
            disappear->setFloatAnimation(&this->circle_shaders[i]->alpha, 0.0);
            Engine::main->playAnimation(disappear);
        }
    });
    
    cleanup = new Animation(this->name + "cleanup", 6 + this->waitTime);
    cleanup->setCompletionHandler([&]{
        start = false;
        this->isDisabled = true;
        this->rounds = {0,0,0};
        for (int i = 0; i < this->magicCircles.size(); i++){
            this->magicCircles[i]->isDisabled = true;
            arrows[i]->reset();
        }
    });
    
    delete circle;
    delete circle_shader;
    delete shiningParticle;
}
void StoneBlast::updateMagic(){
    if (start){
//        for (int i = 0; i < this->rounds[0]; i++){
//            this->projectiles[i]->start = this->projectiles[i]->getWorldPosition();
//            this->projectiles[i]->end = this->projectiles[i]->getWorldPosition() + normalize(this->projectiles[i]->getUpVectorInWorld()) * 0.4f;
//        }
        
        float time = Engine::main->getTime();
        for (int i = 0; i < this->magicCircles.size(); i++){
            if (!this->magicCircles[i]->isDisabled){
                this->circle_shaders[i]->emissionColor =  this->circleEmissions[i] + sin((time + i) * (3 + i * 0.2f)) * circleVariantion;
                this->magicCircles[i]->eulerAngles = this->rotationPosition + vec3(0,(time + i)*10,0);
            }
        }
    }
}
void StoneBlast::play(CharNode* character){
    if (!start){
        this->start = true;
        this->isDisabled = false;
        this->position = vec3(character->modelNode->getWorldPosition());
        this->eulerAngles = vec3(character->modelNode->getWorldEulerAngles());
        Engine::main->playAnimation(playArrow);
        Engine::main->playAnimation(cleanup);
        Engine::main->playAnimation(createMagicCircle);
        Engine::main->playAnimation(removeMagicCircle);
    }
}

void StoneBlast::tryDamage(CharNode* character){
    if (this->start){
        for (int i = 0; i < this->projectiles.size(); i++){
            this->projectiles[i]->tryDamageChar(character);
        }
    }
}

StoneBlast::~StoneBlast(){
    for (int i = 0; i < projectiles.size(); i++){
        delete projectiles[i];
        delete shinnings[i];
    }
    
    delete stone_D;
    delete stone_E;
    delete circleTexture;
    
    delete shiningParticleTexture;
    
    for (int i = 0; i < magicCircles.size(); i++){
        delete circle_shaders[i];
        delete magicCircles[i];
    }
}
