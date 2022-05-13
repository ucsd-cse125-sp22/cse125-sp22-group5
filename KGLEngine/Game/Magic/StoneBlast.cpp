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
    
    this->translatePosition = {vec3(0,5,7), vec3(-3,5,4), vec3(3,5,4), vec3(-3,5,10), vec3(3,5,10)};
    this->rotationPosition = vec3(0,0,-90);
    
    this->circleEmissions = {vec3(0.5,-0.5,-0.5), vec3(0.3,-0.3,0), vec3(-0.3,0,-0.3), vec3(0.5,0,-0.5), vec3(0,0,0)};
    this->circleVariantion = vec3(0.1f);
    
    stone_D = new Texture("/Resources/Game/Magic/StoneBlast/StoneBlast_D.jpg", 2.0f, true);
    
    AlphaShader* stone_shader = new AlphaShader("/Resources/Game/Magic/ThousandBlade/Shader");
    
    Projectile* stone = new Projectile();
    stone->damage = this->damage;
    stone->loadModelFile("/Resources/Game/Magic/StoneBlast/arrow.fbx");
    stone->eulerAngles = vec3(0,0,0);
    stone->position = vec3(0,0,0);
    stone->scale = vec3(0.05);
    stone->geometries[0]->setShader(stone_shader);
    stone->geometries[0]->renderingOrder = 995;
    stone->isDisabled = true;
    
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
    
    ParticleNode* shiningParticle = new ParticleNode(10, 0.65f, 0.1f);
    shiningParticle->eulerAngles = vec3(0,0,90);
    shiningParticle->setMaxAmount(10);
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
        
        AlphaShader* newStoneShader = stone_shader->copy();
        newStoneShader->setTexture("diffuseMap", stone_D);
        newStoneShader->writeToDepthBuffer = false;
        //newStoneShader->setAdditive();
        newStoneShader->alpha = 1.0f;
        newStoneShader->emissionColor = (this->circleEmissions[i] + 0.6f) / 2.0f;
        this->stone_shaders.push_back(newStoneShader);
        
        Node* newCircle = circle->copy();
        newCircle->position = this->translatePosition[i];
        newCircle->eulerAngles = this->rotationPosition;
        newCircle->geometries[0]->setShader(newShader);
        magicCircles.push_back(newCircle);
        this->addChildNode(newCircle);
    }
    
    for (int i = 0; i < 250; i++ ){
        Projectile* newStone = stone->copy();
        newStone->geometries[0]->setShader(stone_shaders[i%5]);
        projectiles.push_back(newStone);
        magicCircles[i%5]->addChildNode(newStone);
        
        ParticleNode* shinning = (ParticleNode*)shiningParticle->copy();
        shinning->setColorAnimation(vec4(vec3(0.0f, 0.5f, 1.0f) + this->circleEmissions[i%5] * 2.0f, 1.0f), 0.0f);
        shinning->setColorAnimation(vec4(vec3(0.0f, 0.5f, 1.0f) + this->circleEmissions[i%5] * 2.0f, 0.0f), 0.75f);
        this->shinnings.push_back(shinning);
        newStone->addChildNode(shinning);
        
        Animation* forward = new Animation(this->name + " forward " + to_string(i), 2.0f);
        forwards.push_back(forward);
        
        Animation* forward2 = new Animation(this->name + " forward2 " + to_string(i), 2.0f);
        forwards.push_back(forward2);
        
        Animation* waitUntilPlay = new Animation(this->name + " wait " + to_string(i), (int)(i/5) * 0.04 + this->waitTime);
        waits.push_back(waitUntilPlay);
        
        waitUntilPlay->setCompletionHandler([&]{
            this->projectiles[this->rounds[0]]->isDisabled = false;
            
            this->shinnings[this->rounds[0]]->play();

            moveStones(0);
            
            this->projectiles[this->rounds[0]]->canDamage = true;
            this->projectiles[this->rounds[0]]->start = this->projectiles[this->rounds[0]]->getWorldPosition() + normalize(this->projectiles[this->rounds[0]]->getBackVectorInWorld()) * 0.2f;
            this->projectiles[this->rounds[0]]->end = this->projectiles[this->rounds[0]]->getWorldPosition() + normalize(this->projectiles[this->rounds[0]]->getFrontVectorInWorld()) * 0.2f;

            this->rounds[0] += 1;
        });
        
        forward->setCompletionHandler([&]{
            this->shinnings[this->rounds[1]]->reset();
            this->shinnings[this->rounds[1]]->play();
            moveStones(1);
            this->projectiles[this->rounds[1]]->damagedChar.clear();
            this->rounds[1] += 1;
        });
        
        forward2->setCompletionHandler([&]{
            this->projectiles[this->rounds[2]]->isDisabled = true;;
            this->projectiles[this->rounds[2]]->canDamage = false;
            this->rounds[2] += 1;
        });
        
        this->randomPositions.push_back(vec3(0));
    }
    
    createMagicCircle = new Animation(this->name + " create magic circle ", 0.5f);
    createMagicCircle->setCompletionHandler([&]{
        for (int i = 0; i < this->magicCircles.size(); i++){
            magicCircles[i]->isDisabled = false;
            Animation* appear = new Animation(this->name + " appear " + to_string(i), 0.5);
            appear->setFloatAnimation(&this->circle_shaders[i]->alpha, 1.0);
            Engine::main->playAnimation(appear);
        }
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
        }
        for (int i = 0; i < this->projectiles.size(); i++){
            this->projectiles[i]->isDisabled = true;
            this->projectiles[i]->canDamage = false;
            this->projectiles[i]->damagedChar.clear();
            this->shinnings[i]->reset();
        }
    });
    
    delete stone;
    delete circle;
    delete circle_shader;
    delete shiningParticle;
    delete stone_shader;
}
void StoneBlast::updateMagic(){
    if (start){
        for (int i = 0; i < this->rounds[0]; i++){
            this->projectiles[i]->start = this->projectiles[i]->getWorldPosition();
            this->projectiles[i]->end = this->projectiles[i]->getWorldPosition() + normalize(this->projectiles[i]->getUpVectorInWorld()) * 0.4f;
        }
        
        float time = Engine::main->getTime();
        for (int i = 0; i < this->magicCircles.size(); i++){
            if (!this->magicCircles[i]->isDisabled){
                this->circle_shaders[i]->emissionColor =  this->circleEmissions[i] + sin((time + i) * (3 + i * 0.2f)) * circleVariantion;
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
        for (int i = 0; i < waits.size(); i++){
            Engine::main->playAnimation(waits[i]);
            this->randomPositions[i] = vec3(0, glm::linearRand(-5.0f, 5.0f), glm::linearRand(-5.0f, 5.0f));
        }
        Engine::main->playAnimation(cleanup);
        Engine::main->playAnimation(createMagicCircle);
        Engine::main->playAnimation(removeMagicCircle);
    }
}
void StoneBlast:: moveStones(int roundNum){
    
    vec3 randomEuler = randomPositions[rounds[roundNum]];
    vec3 randomPosition = vec3(0, randomEuler.z/10, randomEuler.y/10);
    
    this->projectiles[rounds[roundNum]]->eulerAngles = randomEuler + vec3(0,0,-90);
    this->projectiles[rounds[roundNum]]->position = randomPosition;
    
    forwards[rounds[roundNum]*2 + roundNum]->
        setVec3Animation(&this->projectiles[rounds[roundNum]]->position,
                         this->projectiles[rounds[roundNum]]->position +
                         eulerToDirection(randomEuler) * 10.0f);
    Engine::main->playAnimation(forwards[rounds[roundNum]*2 + roundNum]);
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
        delete stone_shaders[i];
    }
}
