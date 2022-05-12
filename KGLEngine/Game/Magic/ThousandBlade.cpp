//
//  ThousandBlade.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#include "ThousandBlade.hpp"
#include <glm/gtx/io.hpp>

vec3 randomPosition(float angle, float closest_rang, float cast_range){
    float random_angle = glm::linearRand(-angle, angle);
    float random_dist = cast_range * sqrt(glm::linearRand(closest_rang/cast_range, 1.0f));
    return vec3(cos(radians(random_angle)) * random_dist, 0, sin(radians(random_angle)) * random_dist);
}

ThousandBlade::ThousandBlade(){
    this->position = vec3(0);
    this->eulerAngles = vec3(1);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->damage = 1;
    this->start = false;
    this->name = "Thousand Blade";
    this->actionName = "cast magic 1";
    
    this->swordTextureFile = "/Resources/Game/Magic/ThousandBlade/sword_texture_D.png";
    this->shaderFile = "/Resources/Game/Magic/ThousandBlade/Shader";
    this->swordModelFile = "/Resources/Game/Magic/ThousandBlade/50sword.dae";
    
    this->circleTextureFile = "/Resources/Game/Magic/ThousandBlade/magic_circle.png";
    this->circleModelFile = "/Resources/Game/Magic/ThousandBlade/one_face.dae";
    
    this->circleParticleFile = "/Resources/Game/Magic/ThousandBlade/circle_particle.png";
    this->swordParticleFile = "/Resources/Game/Magic/ThousandBlade/sword_particle.png";
    this->shiningParticleFile = "/Resources/Game/Magic/ThousandBlade/shining.png";
    
    this->crackTextureFile = "/Resources/Game/Magic/ThousandBlade/crack.png";
    
    this->swordEmission = vec3(0.83, 0.68, 0.21);
    this->swordScale = vec3(0.5);
    this->circleEmission = vec3(0.60, 0.49, 0);
    this->circleVariantion = vec3(0.1, 0.1, 0);
    this->magicCircleScale = vec3(4);
    this->magicCirclePosition = vec3(0,0.1,0);
    
    this->number_groups = 10;
    this->stopTime = 2.0f;
    this->waitTime = 1.0f;
    
    this->variation_time = 2.0f;
    this->circle_in_time = 0.5f;
    this->circle_last_time = 2.0f;
    this->circle_out_time = 0.2f;
    this->sword_in_time = 0.2f;
    this->sword_last_time = 2.0f;
    this->sword_out_time = 0.5f;
    this->total_time = this->waitTime + this->variation_time + this->circle_last_time +
                     this->sword_last_time;
    
    this->cast_range = 15.0f;
    this->damage_range = 4.0f;
    
    this->rounds = {0,0,0,0};
    
    sword_d = new Texture(this->swordTextureFile, 2.0f, true);
   
    AlphaShader* swordShader = new AlphaShader(this->shaderFile);
                
    Projectile* sword = new Projectile();
    sword->loadModelFile(this->swordModelFile);
    sword->geometries[0]->setShader(swordShader);
    sword->geometries[0]->setDoubleSided();
    sword->geometries[0]->renderingOrder = 1000;
    sword->geometries[0]->lightingBitMask = 0;
    sword->isDisabled = true;
    sword->scale = this->swordScale;
    sword->damage = this->damage;
    
    circleTexture = new Texture(this->circleTextureFile, 2.0f, true);
    
    AlphaShader* circle_shader = new AlphaShader(this->shaderFile);
    
    Node* magicCircle = new Node();
    magicCircle->scale = this->magicCircleScale;
    magicCircle->loadModelFile(this->circleModelFile);
    magicCircle->geometries[0]->setShader(circle_shader);
    magicCircle->geometries[0]->setDoubleSided();
    magicCircle->geometries[0]->renderingOrder = 990;
    magicCircle->geometries[0]->lightingBitMask = 0;
    magicCircle->isDisabled = true;
    
    crackTexture = new Texture(this->crackTextureFile, 2.0f, true);
    
    AlphaShader* crackShader = new AlphaShader(this->shaderFile);
    
    Node* crack = new Node();
    crack->scale = this->magicCircleScale;
    crack->loadModelFile(this->circleModelFile);
    crack->geometries[0]->setShader(crackShader);
    crack->geometries[0]->setDoubleSided();
    crack->geometries[0]->renderingOrder = 990;
    crack->geometries[0]->lightingBitMask = 0;
    crack->isDisabled = true;
    
    circleParticleTexture = new Texture(this->circleParticleFile, 2.0f, true);
    
    ParticleNode* circleParticle = new ParticleNode(50, 1.5f, 0.5f);
    circleParticle->eulerAngles = vec3(0,0,90);
    circleParticle->setMaxAmount(50);
    circleParticle->renderingOrder = 995;
    circleParticle->texture = circleParticleTexture;
    circleParticle->isAdditive = true;
    circleParticle->setColorAnimation(vec4(this->swordEmission, 1.0f), 0.0f);
    circleParticle->setColorAnimation(vec4(this->circleEmission, 0.0f), 2.0f);
    circleParticle->initialSpeed = 0.05f;
    circleParticle->initialSpeedVariation = 0.025f;
    circleParticle->initialScale = 0.3;
    circleParticle->initialScaleVariation = 0.1;
    circleParticle->accelerationVariation = vec3(0.1,0,0.1);
    
    swordParticleTexture = new Texture(this->swordParticleFile, 2.0f, true);
    
    ParticleNode* swordParticle = new ParticleNode(500, 0.2f, 0.1f);
    swordParticle->eulerAngles = vec3(0,0,90);
    swordParticle->setMaxAmount(5);
    swordParticle->renderingOrder = 995;
    swordParticle->texture = swordParticleTexture;
    swordParticle->isAdditive = true;
    swordParticle->setColorAnimation(vec4(this->circleEmission + this->circleVariantion, 1.0f), 0.0f);
    swordParticle->setColorAnimation(vec4(this->circleEmission + this->circleVariantion, 0.0f), 0.5f);
    swordParticle->initialSpeed = 1.0f;
    swordParticle->initialSpeedVariation = 0.5f;
    swordParticle->initialScale = 0.75;
    swordParticle->initialScaleVariation = 0.25;
    swordParticle->accelerationVariation = vec3(1);
    swordParticle->initialRotationVariation = 15.0f;
    
    shiningParticleTexture = new Texture(this->shiningParticleFile, 2.0f, true);
    
    ParticleNode* shiningParticle = new ParticleNode(500, 2.0f, 1.0f);
    shiningParticle->eulerAngles = vec3(0,0,90);
    shiningParticle->setMaxAmount(750);
    shiningParticle->renderingOrder = 995;
    shiningParticle->texture = swordParticleTexture;
    shiningParticle->isAdditive = true;
    shiningParticle->setColorAnimation(vec4(this->circleEmission + this->circleVariantion, 1.0f), 0.0f);
    shiningParticle->setColorAnimation(vec4(this->circleEmission + this->circleVariantion, 0.0f), 0.5f);
    shiningParticle->initialSpeed = 0.1f;
    shiningParticle->initialSpeedVariation = 0.1f;
    shiningParticle->initialScale = 0.075;
    shiningParticle->initialScaleVariation = 0.025;
    shiningParticle->accelerationVariation = vec3(0.2);
    shiningParticle->initialRotationVariation = 360.0f;
    shiningParticle->rotatingSpeed = 0.0f;
    shiningParticle->rotatingSpeedVariation = 720.0f;
    
    
    for (int i = 0; i < this->number_groups; i++){
        projectiles.push_back(sword->copy());
        magicCircles.push_back(magicCircle->copy());
        cracks.push_back(crack->copy());
        
        circleParticles.push_back((ParticleNode*)circleParticle->copy());
        magicCircles[i]->addChildNode(circleParticles[i]);
        
        for (int j = 0; j < 10; j++){
            ParticleNode* newParticle = (ParticleNode*)swordParticle->copy();
            newParticle->position = randomPosition(180, 0, 0.6) + vec3(0, 0.2, 0);
            swordParticles.push_back(newParticle);
            magicCircles[i]->addChildNode(newParticle);
        }
        
        shiningParticles.push_back((ParticleNode*)shiningParticle->copy());
        magicCircles[i]->addChildNode(shiningParticles[i]);
        
        AlphaShader* newSwordShader = swordShader->copy();
        newSwordShader->setTexture("diffuseMap", sword_d);
        newSwordShader->setSemitransparent();
        newSwordShader->writeToDepthBuffer = false;
        newSwordShader->alpha = 0.0f;
        newSwordShader->emissionColor = this->swordEmission;
        this->swordShaders.push_back(newSwordShader);
        this->projectiles[i]->geometries[0]->setShader(newSwordShader);
        
        AlphaShader* newCircleShader = circle_shader->copy();
        newCircleShader->setTexture("diffuseMap", circleTexture);
        newCircleShader->setSemitransparent();
        newCircleShader->writeToDepthBuffer = false;
        newCircleShader->alpha = 0.0f;
        newCircleShader->emissionColor = this->circleEmission;
        this->circleShaders.push_back(newCircleShader);
        this->magicCircles[i]->geometries[0]->setShader(newCircleShader);
        
        AlphaShader* newCrackShader = crackShader->copy();
        newCrackShader->setTexture("diffuseMap", crackTexture);
        newCrackShader->setSemitransparent();
        newCrackShader->writeToDepthBuffer = false;
        newCrackShader->alpha = 1.0f;
        newCrackShader->emissionColor = vec3(0);
        this->crackShaders.push_back(newCrackShader);
        this->cracks[i]->geometries[0]->setShader(newCrackShader);
        
        this->addChildNode(projectiles[i]);
        this->addChildNode(magicCircles[i]);
        this->addChildNode(cracks[i]);
        
    }
    
    this->isDisabled = true;
    Engine::main->addNode(this);
    
    delete swordShader;
    delete sword;
    delete magicCircle;
    delete circle_shader;
    delete circleParticle;
    delete swordParticle;
    delete shiningParticle;
}

void ThousandBlade::updateMagic(){
    if (start){
        float time = Engine::main->getTime();
        for (int i = 0; i < this->number_groups; i++){
            if (!this->magicCircles[i]->isDisabled){
                this->circleShaders[i]->emissionColor = circleEmission + sin((time + i) * 10) * circleVariantion;
                this->circleParticles[i]->position = randomPosition(180, 0, 0.4);
                this->shiningParticles[i]->position = (randomPosition(180, 0, 0.5) + vec3(0,0.2,0) + this->projectiles[i]->position.y/8) * this->projectiles[i]->scale.x * 2.0f;
            }
        }
    }
}

float distanceBetween(vec3 a, vec3 b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z));
}

void ThousandBlade::play(CharNode* character){
    if (!start){
        start = true;
        this->isDisabled = false;
        this->position = vec3(character->modelNode->getWorldPosition());
        this->eulerAngles = vec3(character->modelNode->getWorldEulerAngles()) - vec3(0, 90, 0);
        vector<vec3> positions;
        
        for (int i = 0; i < this->number_groups; i++){
            vec3 position = randomPosition(60, 2.0f, this->cast_range);
            bool pass = true;
            int count = 0;
            while (pass) {
                pass = false;
                for (int i = 0; i < positions.size(); i++){
                    if (distanceBetween(positions[i], position) < damage_range){
                        position = randomPosition(60, 2.0f, this->cast_range);
                        pass = true;
                        break;
                    }
                }
                count++;
                if (count > 100){
                    break;
                }
            }
            positions.push_back(position);
            float random_rotate = glm::linearRand(0.0f, 360.0f);
            this->projectiles[i]->position = position + vec3(0, 20, 0);
            this->projectiles[i]->eulerAngles = vec3(0,random_rotate,0);
            this->projectiles[i]->scale = vec3(glm::linearRand(1.0f, 1.1f)) * this->swordScale;
            this->magicCircles[i]->position = position + magicCirclePosition;
            this->cracks[i]->position = position + magicCirclePosition;
            this->cracks[i]->scale = this->projectiles[i]->scale * 12.0f;

            
            Animation* wait = new Animation(this->name + " wait " + to_string(i), this->waitTime + this->variation_time / this->number_groups * i);
            
            wait->setCompletionHandler([&]{
                this->magicCircles[this->rounds[0]]->isDisabled = false;
                
                this->circleParticles[this->rounds[0]]->play();
                for (int j = 0; j < 10; j++){
                    this->swordParticles[this->rounds[0] * 10 + j]->stop();
                }
                this->shiningParticles[this->rounds[0]]->stop();
                
                Animation* circle_in = new Animation(this->name + " circle in " + to_string(this->rounds[0]), this->circle_in_time);
                circle_in->setFloatAnimation(&this->circleShaders[this->rounds[0]]->alpha, 1.0f);
                Engine::main->playAnimation(circle_in);
                
                Animation* circle_wait = new Animation(this->name + " circle wait " + to_string(this->rounds[0]), this->circle_last_time);
                circle_wait->setCompletionHandler([&]{
                    this->projectiles[this->rounds[1]]->isDisabled = false;
                    
                    Animation* sword_in = new Animation(this->name + " sword in " + to_string(this->rounds[1]), this->sword_in_time);
                    sword_in->setFloatAnimation(&this->swordShaders[this->rounds[1]]->alpha, 1.0f);

                    Engine::main->playAnimation(sword_in);
                    
                    Animation* sword_up = new Animation(this->name + " sword up " + to_string(this->rounds[1]), this->sword_in_time);
                    sword_up->setFloatAnimation(&this->projectiles[this->rounds[1]]->position.y, glm::linearRand(0.0f, 0.5f));
                    sword_up->setEaseInTimingMode();
                    Engine::main->playAnimation(sword_up);
                    
                    sword_up->setCompletionHandler([&]{
                        
                        this->cracks[this->rounds[2]]->isDisabled = false;
                        
                        for (int j = 0; j < 10; j++){
                            this->swordParticles[this->rounds[2]*10+j]->position.y = (0.20
                            + this->projectiles[this->rounds[2]]->position.y/8) * this->projectiles[this->rounds[2]]->scale.x * 2.0f;
                            this->swordParticles[this->rounds[2]*10+j]->play();
                        }
                        this->shiningParticles[this->rounds[2]]->play();
                        
                        this->projectiles[this->rounds[2]]->canDamage = true;
                        Animation* circle_out = new Animation(this->name + " circle out " + to_string(this->rounds[2]), this->circle_out_time);
                        circle_out->setFloatAnimation(&this->circleShaders[this->rounds[2]]->alpha, 0.0f);
                        Engine::main->playAnimation(circle_out);
                        this->rounds[2] += 1;
                    });
                    
                    Animation* sword_wait = new Animation(this->name + " sword wait " + to_string(this->rounds[1]), this->sword_last_time);
                    sword_wait->setCompletionHandler([&]{
                        this->projectiles[this->rounds[3]]->canDamage = false;
                        
                        Animation* sword_out = new Animation(this->name + " sword out " + to_string(this->rounds[3]), this->sword_out_time);
                        sword_out->setFloatAnimation(&this->swordShaders[this->rounds[3]]->alpha, 0.0f);
                        Engine::main->playAnimation(sword_out);
                        
                        Animation* crack_out = new Animation(this->name + " crack out " + to_string(this->rounds[3]), this->sword_out_time);
                        crack_out->setFloatAnimation(&this->crackShaders[this->rounds[3]]->alpha, 0.0f);
                        Engine::main->playAnimation(crack_out);
                        
                        this->rounds[3] += 1;
                    });
                    Engine::main->playAnimation(sword_wait);
                    
                    this->rounds[1] += 1;
                });
                Engine::main->playAnimation(circle_wait);
                this->rounds[0] += 1;
            });
            Engine::main->playAnimation(wait);
        }
        
        Animation* cleanup = new Animation(this->name + " cleanup", this->total_time + 1.0f);
        cleanup->setCompletionHandler([&]{
            this->start = false;
            this->isDisabled = true;
            for (int i=0; i < this->number_groups; i++){
                this->projectiles[i]->isDisabled = true;
                this->projectiles[i]->canDamage = false;
                this->projectiles[i]->damagedChar.clear();
                this->magicCircles[i]->isDisabled = true;
                this->cracks[i]->isDisabled = true;
                this->crackShaders[i]->alpha = 1.0f;
                this->circleParticles[i]->reset();
                for (int j = 0; j < 10; j++){
                    this->swordParticles[i*10+j]->reset();
                }
                this->shiningParticles[i]->reset();
            }
            this->rounds = {0,0,0,0};
        });
        Engine::main->playAnimation(cleanup);
    }
}

void ThousandBlade::tryDamage(CharNode* character){
    if (this->start){
        for (int i = 0; i < this->projectiles.size(); i++){
            if (this->projectiles[i]->canDamage && find(this->projectiles[i]->damagedChar.begin(), this->projectiles[i]->damagedChar.end(), character) == this->projectiles[i]->damagedChar.end() &&
                character->hitbox->testSphere(projectiles[i]->getWorldPosition(), this->damage_range * this->projectiles[i]->scale.x)){
                
                character->receiveDamage(this->damage);
                this->projectiles[i]->damagedChar.push_back(character);
            }
        }
    }
}

ThousandBlade::~ThousandBlade(){
    delete sword_d;
    delete circleTexture;
    delete circleParticleTexture;
    delete crackTexture;
    for (int i = 0; i < this->number_groups; i++){
        delete magicCircles[i];
        delete projectiles[i];
        delete circleParticles[i];
        delete swordParticles[i];
        delete cracks[i];
    }
}
