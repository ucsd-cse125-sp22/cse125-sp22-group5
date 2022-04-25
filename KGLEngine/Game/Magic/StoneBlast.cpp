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
    this->actionName = "cast magic 1";
    this->stopTime = 2.0f;
    this->waitTime = 1.0f;
    this->position = vec3(0);
    this->eulerAngles = vec3(0);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    this->start = false;
    this->rounds = {0,0,0};
    
    stone_D = new Texture("/Resources/Game/Magic/StoneBlast/StoneBlast_D.jpg", 2.0f, true);
    stone_E = new Texture("/Resources/Game/Magic/StoneBlast/StoneBlast_E.jpg", 2.0f, true);
    
    stone_shader = new PBRShader(0.5, 0.5);
    //particle_shader->setAdditive();
    stone_shader->setDiffuseMap(stone_D);
    stone_shader->setEmissionMap(stone_E);
    stone_shader->setAdditive();
    
    stone = new Node();
    stone->loadModelFile("/Resources/Game/Magic/StoneBlast/StoneBlast.fbx");
    stone->eulerAngles = vec3(0,0,0);
    stone->position = vec3(0,0,0);
    stone->scale = vec3(0.2,0.2,0.2);
    stone->geometries[0]->setShader(stone_shader);
    stone->geometries[0]->cullFront();
    stone->geometries[0]->renderingOrder = 1000;
    
    circleTexture = new Texture("/Resources/Game/Magic/StoneBlast/Magic Circle.png", 2.0f, true);
    
    circle_shader = new PBRShader(0.5, 0.5);
    circle_shader->setDiffuseMap(circleTexture);
    circle_shader->setEmissionMap(circleTexture);
    circle_shader->setAdditive();
    
    magicCircle = new Node();
    magicCircle->scale = vec3(0.5);
    magicCircle->loadModelFile("/Resources/Game/Magic/StoneBlast/one_face.fbx");
    magicCircle->geometries[0]->setShader(circle_shader);
    magicCircle->geometries[0]->setDoubleSided();
    magicCircle->geometries[0]->renderingOrder = 1000;
    
    
    createMagicCircle = new Animation(this->name + " create magic circle ", 0.5f);
    createMagicCircle->setCompletionHandler([&]{
        this->addChildNode(magicCircle);
    });
    
    removeMagicCircle = new Animation(this->name + " remove magic circle ", 5.5f);
    removeMagicCircle->setCompletionHandler([&]{
        magicCircle->removeFromParentNode();
    });
    
    for (int i = 0; i < 50; i++ ){
        Node* newStone = stone->copy();

        stones.push_back(newStone);
        
        Animation* spin = new Animation(this->name + " spin " + to_string(i), 4.0f);
        spins.push_back(spin);
        
        Animation* forward = new Animation(this->name + " forward " + to_string(i), 2.0f);
        forward->setEaseInTimingMode();
        forwards.push_back(forward);
        
        Animation* forward2 = new Animation(this->name + " forward2 " + to_string(i), 2.0f);
        forward2->setEaseInTimingMode();
        forwards.push_back(forward2);
        
        Animation* waitUntilPlay = new Animation(this->name + " wait " + to_string(i), i * 0.04 + this->waitTime);
        waits.push_back(waitUntilPlay);
        
        waitUntilPlay->setCompletionHandler([&]{
            this->addChildNode(stones[this->rounds[0]]);
            
            spins[this->rounds[0]]->setFloatAnimation(&this->stones[this->rounds[0]]->eulerAngles.x, 36000);
            Engine::main->playAnimation(spins[this->rounds[0]]);

            moveStones(0);

            this->rounds[0] += 1;
        });
        
        forward->setCompletionHandler([&]{
            moveStones(1);
            
            this->rounds[1] += 1;
        });
        
        forward2->setCompletionHandler([&]{
            this->stones[this->rounds[2]]->removeFromParentNode();
            this->rounds[2] += 1;
        });
        
    }
    cleanup = new Animation(this->name + "cleanup", 6 + this->waitTime);
    cleanup->setCompletionHandler([&]{
        start = false;
        hits.clear();
        this->rounds = {0,0,0};
        for (int i = 0; i < stones.size(); i++){
            stones[i]->removeFromParentNode();
        }
        this->removeFromParentNode();
    });
}
void StoneBlast::updateMagic(){
    if (start){
        hits.clear();
        for (int i = 0; i < this->rounds[0]; i++){
            hitLine hit;
            hit.start = stones[i]->getWorldPosition() + stones[i]->getBackVectorInWorld() * 0.05f;
            hit.end = stones[i]->getWorldPosition() + stones[i]->getFrontVectorInWorld() *      0.05f;
            hits.push_back(hit);
        }
    }
}
void StoneBlast::play(vec3 position, vec3 euler){
    if (!start){
        this->start = true;
        this->position = vec3(position) + vec3(0, 0.5, 0);
        this->eulerAngles = vec3(euler);
        Engine::main->addNode(this);
        magicCircle->position = vec3(0.5, 0, 0);
        for (int i = 0; i < waits.size(); i++){
            Engine::main->playAnimation(waits[i]);
        }
        Engine::main->playAnimation(cleanup);
        Engine::main->playAnimation(createMagicCircle);
        Engine::main->playAnimation(removeMagicCircle);
    }
}
void StoneBlast:: moveStones(int roundNum){
    vec3 randomEuler = vec3(0, float(glm::linearRand(-500, 500))/100, float(glm::linearRand(-100, 100))/100);
    vec3 randomPosition = vec3(0.8, randomEuler.z/10, randomEuler.y/50);
    
    this->stones[rounds[roundNum]]->eulerAngles = randomEuler;
    this->stones[rounds[roundNum]]->position = randomPosition;
    
    forwards[rounds[roundNum]*2 + roundNum]->
        setVec3Animation(&this->stones[rounds[roundNum]]->position,
                         this->stones[rounds[roundNum]]->position +
                         eulerToDirection(randomEuler) * 100.0f);
    Engine::main->playAnimation(forwards[rounds[roundNum]*2 + roundNum]);
}

StoneBlast::~StoneBlast(){
    for (int i = 0; i < stones.size(); i++){
        delete stones[i];
    }
    
    delete stone_D;
    delete stone_E;
    delete stone_shader;
    delete stone;
    delete circleTexture;
}
