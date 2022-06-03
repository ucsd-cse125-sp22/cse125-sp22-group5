// Developed by Kelin Lyu.

#include "Game/Magic/DragonMagic.hpp"

#include "Game/Character/CharNode.hpp"
#include "Game/Map/MapSystemManager.hpp"

#define COOLDOWN 5.5
#define COST 800
#define DAMAGE 200

using namespace std;
using namespace glm;

int DragonMagic::UID = 0;
bool DragonMagic::loaded = false;
Node* DragonMagic::templateDragonNode = NULL;
Shader* DragonMagic::templateDragonShader = NULL;
Texture* DragonMagic::diffuseMap = NULL;
Texture* DragonMagic::normalMap = NULL;
Texture* DragonMagic::emissionMap = NULL;
Texture* DragonMagic::noiseMap = NULL;
Texture* DragonMagic::maskMap = NULL;
Node* DragonMagic::templateBeamNode = NULL;
Shader* DragonMagic::templateBeamShader = NULL;
Texture* DragonMagic::beamMap = NULL;
ParticleNode* DragonMagic::fireTemplate = NULL;
ParticleNode* DragonMagic::smokeTemplate = NULL;
ParticleNode* DragonMagic::lineTemplate = NULL;
ParticleNode* DragonMagic::sparkTemplate = NULL;
ParticleNode* DragonMagic::fragmentTemplate = NULL;
ParticleNode* DragonMagic::magicTemplate = NULL;
AudioBuffer* DragonMagic::growl = NULL;
AudioBuffer* DragonMagic::castSound = NULL;
AudioBuffer* DragonMagic::flyingSound = NULL;

void DragonMagic::load() {
    DragonMagic::templateDragonNode = new Node();
    DragonMagic::templateDragonShader = new Shader("/Resources/Game/Magic/Dragon/Dragon");
    DragonMagic::diffuseMap = new Texture("/Resources/Game/Magic/Dragon/DragonD.png", 2.0f, true);
    DragonMagic::normalMap = new Texture("/Resources/Game/Magic/Dragon/DragonN.png", 1.0f, true);
    DragonMagic::emissionMap = new Texture("/Resources/Game/Magic/Dragon/DragonE.png", 1.0f, true);
    DragonMagic::noiseMap = new Texture("/Resources/Game/Magic/Dragon/Noise.png", 1.0f, true);
    DragonMagic::maskMap = new Texture("/Resources/Game/Magic/Dragon/Mask.png", 1.0f, true);
    
    DragonMagic::templateDragonNode->loadModelFile("/Resources/Game/Magic/Dragon/Dragon.dae");
    DragonMagic::templateDragonNode->geometries[0]->setDoubleSided();
    Animator* attack = DragonMagic::templateDragonNode->loadAnimator("attack", "/Resources/Game/Magic/Dragon/Attack.dae");
    attack->repeats = false;
    attack->clamps = true;
    
    DragonMagic::templateBeamNode = new Node();
    DragonMagic::templateBeamShader = new Shader("/Resources/Game/Magic/Dragon/Beam");
    DragonMagic::beamMap = new Texture("/Resources/Game/Magic/Dragon/Beam.png", 1.0f, true);
    
    DragonMagic::templateBeamNode->loadModelFile("/Resources/Game/Magic/Dragon/Beam.dae");
    DragonMagic::templateBeamNode->geometries[0]->setDoubleSided();
    
    Texture* fireMap = new Texture("/Resources/Game/Magic/Dragon/Fire.png");
    Texture* smokeMap = new Texture("/Resources/Game/Magic/Dragon/Smoke.png");
    Texture* lineMap = new Texture("/Resources/Game/Magic/Dragon/Line.png");
    Texture* sparkMap = new Texture("/Resources/Game/Magic/Dragon/Spark.png");
    Texture* fragmentMap = new Texture("/Resources/Game/Magic/Dragon/Fragment.png");
    
    DragonMagic::fireTemplate = new ParticleNode(120, 0.2f, 0.1f);
    DragonMagic::fireTemplate->renderingOrder = dragonMagicBaseRenderingOrder + 0.02f;
    DragonMagic::fireTemplate->useLocalSpace = true;
    DragonMagic::fireTemplate->isAdditive = true;
    DragonMagic::fireTemplate->setEmissionSphere(0.0f, 0.0f);
    DragonMagic::fireTemplate->spreadingAngle = 0.0f;
    DragonMagic::fireTemplate->initialSpeed = 15.0f;
    DragonMagic::fireTemplate->initialSpeedVariation = 5.0f;
    DragonMagic::fireTemplate->initialRotationVariation = 180.0f;
    DragonMagic::fireTemplate->rotatingSpeed = 180.0f;
    DragonMagic::fireTemplate->rotatingSpeedVariation = 90.0f;
    DragonMagic::fireTemplate->randomizeRotatingDirection = true;
    DragonMagic::fireTemplate->initialScale = 0.6f;
    DragonMagic::fireTemplate->initialScaleVariation = 0.4f;
    DragonMagic::fireTemplate->scalingSpeed = -2.0f;
    DragonMagic::fireTemplate->scalingSpeedVariation = 0.2f;
    DragonMagic::fireTemplate->texture = fireMap;
    DragonMagic::fireTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 1.0f), 0.0f);
    DragonMagic::fireTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 0.0f), 1.0f);
    
    DragonMagic::smokeTemplate = new ParticleNode(15, 2.5f, 0.5f);
    DragonMagic::smokeTemplate->renderingOrder = dragonMagicBaseRenderingOrder + 0.01f;
    DragonMagic::smokeTemplate->spreadingAngle = 10.0;
    DragonMagic::smokeTemplate->initialSpeed = 0.5f;
    DragonMagic::smokeTemplate->initialSpeedVariation = 0.2f;
    DragonMagic::smokeTemplate->acceleration = vec3(0.0f, 0.5f, 0.0f);
    DragonMagic::smokeTemplate->accelerationVariation = vec3(0.05f, 0.2f, 0.05f);
    DragonMagic::smokeTemplate->initialRotationVariation = 360.0f;
    DragonMagic::smokeTemplate->rotatingSpeedVariation = 180.0f;
    DragonMagic::smokeTemplate->initialScale = 0.6f;
    DragonMagic::smokeTemplate->initialScaleVariation = 0.2f;
    DragonMagic::smokeTemplate->scalingSpeed = 0.2f;
    DragonMagic::smokeTemplate->scalingSpeedVariation = 0.2f;
    DragonMagic::smokeTemplate->texture = smokeMap;
    DragonMagic::smokeTemplate->setColorAnimation(vec4(1.0f, 1.0f, 1.0f, 0.0f), 0.0f);
    DragonMagic::smokeTemplate->setColorAnimation(vec4(1.0f, 1.0f, 1.0f, 0.2f), 0.2f);
    DragonMagic::smokeTemplate->setColorAnimation(vec4(0.5f, 0.5f, 0.5f, 0.2f), 0.7f);
    DragonMagic::smokeTemplate->setColorAnimation(vec4(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    
    DragonMagic::lineTemplate = new ParticleNode(20, 1.0f, 0.2f);
    DragonMagic::lineTemplate->renderingOrder = dragonMagicBaseRenderingOrder + 0.03f;
    DragonMagic::lineTemplate->useLocalSpace = true;
    DragonMagic::lineTemplate->isAdditive = true;
    DragonMagic::lineTemplate->setEmissionSphere(0.0f, 0.0f);
    DragonMagic::lineTemplate->spreadingAngle = 0.0f;
    DragonMagic::lineTemplate->initialSpeed = 0.0f;
    DragonMagic::lineTemplate->initialSpeedVariation = 0.0f;
    DragonMagic::lineTemplate->initialRotationVariation = 40.0f;
    DragonMagic::lineTemplate->rotatingSpeed = 20.0f;
    DragonMagic::lineTemplate->rotatingSpeedVariation = 10.0f;
    DragonMagic::lineTemplate->randomizeRotatingDirection = true;
    DragonMagic::lineTemplate->initialScale = 1.5f;
    DragonMagic::lineTemplate->initialScaleVariation = 1.5f;
    DragonMagic::lineTemplate->scalingSpeed = 0.0f;
    DragonMagic::lineTemplate->scalingSpeedVariation = 0.2f;
    DragonMagic::lineTemplate->texture = lineMap;
    DragonMagic::lineTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 0.0f), 0.0f);
    DragonMagic::lineTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 1.0f), 0.5f);
    DragonMagic::lineTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 0.0f), 1.0f);
    
    DragonMagic::sparkTemplate = new ParticleNode(60, 0.5f, 0.2f);
    DragonMagic::sparkTemplate->renderingOrder = dragonMagicBaseRenderingOrder + 0.04f;
    DragonMagic::sparkTemplate->isAdditive = true;
    DragonMagic::sparkTemplate->setEmissionSphere(0.0f, 0.0f);
    DragonMagic::sparkTemplate->spreadingAngle = 60.0f;
    DragonMagic::sparkTemplate->initialSpeed = 5.0f;
    DragonMagic::sparkTemplate->initialSpeedVariation = 2.0f;
    DragonMagic::sparkTemplate->acceleration = vec3(0.0f, 2.0f, 0.0f);
    DragonMagic::sparkTemplate->accelerationVariation = vec3(0.5f, 2.0f, 0.5f);
    DragonMagic::sparkTemplate->initialRotationVariation = 360.0f;
    DragonMagic::sparkTemplate->rotatingSpeed = 270.0f;
    DragonMagic::sparkTemplate->rotatingSpeedVariation = 180.0f;
    DragonMagic::sparkTemplate->randomizeRotatingDirection = true;
    DragonMagic::sparkTemplate->initialScale = 0.6f;
    DragonMagic::sparkTemplate->initialScaleVariation = 0.2f;
    DragonMagic::sparkTemplate->scalingSpeed = -0.1f;
    DragonMagic::sparkTemplate->scalingSpeedVariation = 0.1f;
    DragonMagic::sparkTemplate->texture = sparkMap;
    DragonMagic::sparkTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 1.0f), 0.0f);
    DragonMagic::sparkTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 1.0f), 0.8f);
    DragonMagic::sparkTemplate->setColorAnimation(vec4(1.0f, 0.5f, 0.0f, 0.0f), 1.0f);
    
    DragonMagic::fragmentTemplate = new ParticleNode(180, 0.5f, 0.4f);
    DragonMagic::fragmentTemplate->renderingOrder = dragonMagicBaseRenderingOrder - 0.01f;
    DragonMagic::fragmentTemplate->isAdditive = true;
    DragonMagic::fragmentTemplate->setEmissionSphere(0.2f, 0.3f);
    DragonMagic::fragmentTemplate->spreadingAngle = 180.0;
    DragonMagic::fragmentTemplate->initialSpeed = 0.5f;
    DragonMagic::fragmentTemplate->initialSpeedVariation = 0.5f;
    DragonMagic::fragmentTemplate->acceleration = vec3(0.0f, 1.0f, 0.0f);
    DragonMagic::fragmentTemplate->accelerationVariation = vec3(0.2f, 1.0f, 0.2f);
    DragonMagic::fragmentTemplate->initialRotationVariation = 360.0f;
    DragonMagic::fragmentTemplate->rotatingSpeed = 270.0f;
    DragonMagic::fragmentTemplate->rotatingSpeedVariation = 180.0f;
    DragonMagic::fragmentTemplate->randomizeRotatingDirection = true;
    DragonMagic::fragmentTemplate->initialScale = 0.1f;
    DragonMagic::fragmentTemplate->initialScaleVariation = 0.1f;
    DragonMagic::fragmentTemplate->scalingSpeed = 0.0f;
    DragonMagic::fragmentTemplate->scalingSpeedVariation = 0.0f;
    DragonMagic::fragmentTemplate->texture = fragmentMap;
    DragonMagic::fragmentTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 0.0f), 0.0f);
    DragonMagic::fragmentTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.1f);
    DragonMagic::fragmentTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    
    DragonMagic::magicTemplate = new ParticleNode(300, 0.8f, 0.2f);
    DragonMagic::magicTemplate->renderingOrder = dragonMagicBaseRenderingOrder - 0.01f;
    DragonMagic::magicTemplate->isAdditive = true;
    DragonMagic::magicTemplate->setEmissionSphere(0.5f, 1.0f);
    DragonMagic::magicTemplate->spreadingAngle = 0.0f;
    DragonMagic::magicTemplate->initialSpeed = 0.0f;
    DragonMagic::magicTemplate->initialSpeedVariation = 0.0f;
    DragonMagic::magicTemplate->acceleration = vec3(0.0f, -0.1f, 0.0f);
    DragonMagic::magicTemplate->accelerationVariation = vec3(0.05f, 0.1f, 0.05f);
    DragonMagic::magicTemplate->initialRotationVariation = 360.0f;
    DragonMagic::magicTemplate->rotatingSpeed = 0.0f;
    DragonMagic::magicTemplate->rotatingSpeedVariation = 30.0f;
    DragonMagic::magicTemplate->randomizeRotatingDirection = true;
    DragonMagic::magicTemplate->initialScale = 0.15f;
    DragonMagic::magicTemplate->initialScaleVariation = 0.1f;
    DragonMagic::magicTemplate->scalingSpeed = -0.05f;
    DragonMagic::magicTemplate->scalingSpeedVariation = 0.0f;
    DragonMagic::magicTemplate->texture = fragmentMap;
    DragonMagic::magicTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 0.0f), 0.0f);
    DragonMagic::magicTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.2f);
    DragonMagic::magicTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.8f);
    DragonMagic::magicTemplate->setColorAnimation(vec4(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);
    growl = new AudioBuffer("/Resources/Game/Sound/Large Creature 13 - Long ", "wav", 1, 3);
    castSound = new AudioBuffer("/Resources/Game/Sound/Nature Spell 20.wav");
    flyingSound = new AudioBuffer("/Resources/Game/Sound/Fire Spelll 27.wav");
}

DragonMagic::DragonMagic(Node* characterNode) {
    if (!loaded) { load(); loaded = true; }
    this->loadAudioBuffer("growl", growl, 2.0f, 1.0f);
    this->loadAudioBuffer("cast", castSound, 2.0f, 1.0f);
    this->loadAudioBuffer("flying sound", flyingSound);
    this->actionName = "dragon attack";
    this->availableTime = 0;
    this->stopTime = 3.0f;
    this->damage = DAMAGE;
    this->cooldown = COOLDOWN;
    this->cost = COST;
    this->ID = DragonMagic::UID;
    DragonMagic::UID += 1;
    this->characterNode = characterNode;
    this->dragonNode = DragonMagic::templateDragonNode->copy();
    this->dragonShader = DragonMagic::templateDragonShader->copy();
    
    this->dragonShader->setTexture("diffuseMap", DragonMagic::diffuseMap);
    this->dragonShader->setTexture("normalMap", DragonMagic::normalMap);
    this->dragonShader->setTexture("emissionMap", DragonMagic::emissionMap);
    this->dragonShader->setFloat("metallic", 0.6f);
    this->dragonShader->setFloat("roughness", 0.4f);
    this->dragonShader->setTexture("noiseMap", DragonMagic::noiseMap);
    this->dragonShader->setFloat("deathFactor", 0.0f);
    this->dragonShader->setTexture("maskMap", DragonMagic::maskMap);
    
    this->dragonNode->geometries[0]->setShader(this->dragonShader);
    this->dragonNode->isDisabled = true;
    this->attack = this->dragonNode->getAnimator("attack");
    
    Node* headNode = this->dragonNode->generateBoneNode("BLACK_DRAGON_FBXASC032Head");
    this->beamBaseNode = new Node();
    this->beamBaseNode->position = vec3(0.05f, 0.0f, 0.0f);
    this->beamBaseNode->eulerAngles = vec3(0.0f, 0.0f, 72.0f);
    headNode->addChildNode(this->beamBaseNode);
    
    this->beamNode = DragonMagic::templateBeamNode->copy();
    this->beamNode->eulerAngles = vec3(0.0f, 90.0f, 0.0f);
    this->beamBaseNode->addChildNode(this->beamNode);
    
    this->beamShader = DragonMagic::templateBeamShader->copy();
    this->beamShader->setAdditive();
    this->beamShader->writeToDepthBuffer = false;
    this->beamShader->setTexture("beamMap", DragonMagic::beamMap);
    this->beamNode->geometries[0]->setShader(this->beamShader);
    this->beamNode->geometries[0]->renderingOrder = dragonMagicBaseRenderingOrder;
    this->range = 10000;
    
    this->emission = DragonMagic::fireTemplate->copy()->convertToParticleNode();
    this->emission->position = vec3(0.5f, 0.0f, 0.0f);
    this->emission->stop();
    this->beamBaseNode->addChildNode(this->emission);
    
    this->emissionLine = DragonMagic::lineTemplate->copy()->convertToParticleNode();
    this->emissionLine->position = vec3(0.6f, 0.0f, 0.0f);
    this->emissionLine->stop();
    this->beamBaseNode->addChildNode(this->emissionLine);
    
    this->emissionLight = new LightNode(vec3(0.0f));
    this->emissionLight->setPointLight(2.0f, 4.0f);
    this->emissionLight->penetrationRange = 4.0f;
    this->emissionLight->position = vec3(1.0f, 0.0f, 0.0f);
    this->beamBaseNode->addChildNode(this->emissionLight);
    
    this->contact = DragonMagic::fireTemplate->copy()->convertToParticleNode();
    this->contact->initialSpeed = 0.0f;
    this->contact->initialSpeedVariation = 0.0f;
    this->contact->initialScale = 0.3f;
    this->contact->initialScaleVariation = 0.2f;
    this->contact->stop();
    Engine::main->addNode(this->contact);
    
    this->emissionSmoke = DragonMagic::smokeTemplate->copy()->convertToParticleNode();
    this->emissionSmoke->position = vec3(0.5f, 0.0f, 0.0f);
    this->emissionSmoke->stop();
    this->beamBaseNode->addChildNode(this->emissionSmoke);
    
    this->emissionSpark = DragonMagic::sparkTemplate->copy()->convertToParticleNode();
    this->emissionSpark->position = vec3(0.5f, 0.0f, 0.0f);
    this->emissionSpark->stop();
    this->beamBaseNode->addChildNode(this->emissionSpark);
    
    std::vector<std::string> list;
    list.push_back("BLACK_DRAGON_FBXASC032Neck2");
    list.push_back("BLACK_DRAGON_FBXASC032Neck4");
    list.push_back("BLACK_DRAGON_FBXASC032QueueFBXASC032deFBXASC032chevalFBXASC0321");
    
    for(const std::string& name : list) {
        Node* boneNode = this->dragonNode->generateBoneNode(name);
        ParticleNode* particleNode = DragonMagic::fragmentTemplate->copy()->convertToParticleNode();
        particleNode->setSpriteSheetAnimation(1, 8, 8, 0, 0);
        particleNode->stop();
        boneNode->addChildNode(particleNode);
        this->fragments.push_back(particleNode);
    }
    
    this->magic = DragonMagic::magicTemplate->copy()->convertToParticleNode();
    this->magic->setSpriteSheetAnimation(1, 8, 8, 0, 0);
    this->magic->setMaxAmount(120);
    this->magic->stop();
    Engine::main->addNode(this->magic);
    
    Engine::main->addNode(this->dragonNode);
}

void DragonMagic::play() {
    this->dragonNode->isDisabled = false;
    this->dragonNode->position = this->characterNode->getWorldPosition();
    this->dragonNode->eulerAngles = this->characterNode->getWorldEulerAngles();
    this->dragonNode->scale = this->characterNode->getWorldScale();
    this->deathFactor = 0.0f;
    
    this->magic->position = this->characterNode->getWorldPosition() + vec3(0.0f, 1.0f, 0.0f);
    this->magic->reset();
    this->magic->play();
    
    this->rangeFactor = 0.0f;
    
    this->attack->reset();
    this->attack->play(0.0f);
    this->playAudio("cast");
    
    Animation* delay1 = new Animation(this->getAnimationName("Delay1"), 2.5f);
    delay1->setCompletionHandler([&] {
        Animation* die = new Animation(this->getAnimationName("Die"), 1.5f);
        die->setFloatAnimation(&this->deathFactor, 1.0f);
        die->setEaseInTimingMode();
        Engine::main->playAnimation(die);
    });
    Engine::main->playAnimation(delay1);
    
    Animation* delay2 = new Animation(this->getAnimationName("Delay2"), 1.0f);
    delay2->setCompletionHandler([&] {
        Animation* range1 = new Animation(this->getAnimationName("Range1"), 0.1f);
        this->playAudio("growl");
        this->playAudio("flying sound");
        range1->setFloatAnimation(&this->rangeFactor, 1.0f);
        range1->setEaseInTimingMode();
        Engine::main->playAnimation(range1);
        
        Animation* emissionLight1 = new Animation(this->getAnimationName("EmissionLight1"), 0.2f);
        emissionLight1->setVec3Animation(&this->emissionLight->colorFactor, vec3(20.0f, 10.0f, 0.0f));
        emissionLight1->setEaseInTimingMode();
        Engine::main->playAnimation(emissionLight1);
        
        this->emission->play();
        this->emissionSmoke->play();
        this->emissionLine->play();
        this->emissionSpark->play();
    });
    Engine::main->playAnimation(delay2);
    
    Animation* delay3 = new Animation(this->getAnimationName("Delay3"), 2.5f);
    delay3->setCompletionHandler([&] {
        Animation* range2 = new Animation(this->getAnimationName("Range2"), 0.1f);
        range2->setFloatAnimation(&this->rangeFactor, 0.0f);
        range2->setEaseInTimingMode();
        Engine::main->playAnimation(range2);
        
        Animation* emissionLight2 = new Animation(this->getAnimationName("EmissionLight2"), 0.2f);
        emissionLight2->setVec3Animation(&this->emissionLight->colorFactor, vec3(0.0f));
        emissionLight2->setEaseInTimingMode();
        Engine::main->playAnimation(emissionLight2);
        
        this->emission->stop();
    });
    Engine::main->playAnimation(delay3);
    
    Animation* delay4 = new Animation(this->getAnimationName("Delay4"), 1.6f);
    delay4->setCompletionHandler([&] {
        this->emissionLine->stop();
    });
    Engine::main->playAnimation(delay4);
    
    Animation* delay5 = new Animation(this->getAnimationName("Delay5"), 3.0f);
    delay5->setCompletionHandler([&] {
        this->emissionSmoke->stop();
        this->emissionSpark->stop();
    });
    Engine::main->playAnimation(delay5);
    
    Animation* delay6 = new Animation(this->getAnimationName("Delay6"), 0.9f);
    delay6->setCompletionHandler([&] {
        this->fragments[0]->play();
    });
    Engine::main->playAnimation(delay6);
    
    Animation* delay7 = new Animation(this->getAnimationName("Delay7"), 2.9f);
    delay7->setCompletionHandler([&] {
        for(ParticleNode* particleNode : this->fragments) {
            particleNode->play();
        }
    });
    Engine::main->playAnimation(delay7);
    
    Animation* delay8 = new Animation(this->getAnimationName("Delay8"), 3.5f);
    delay8->setCompletionHandler([&] {
        for(ParticleNode* particleNode : this->fragments) {
            particleNode->stop();
        }
    });
    Engine::main->playAnimation(delay8);
    
    Animation* completion1 = new Animation(this->getAnimationName("Completion1"), 4.0f);
    completion1->setCompletionHandler([&] {
        this->attack->reset();
    });
    Engine::main->playAnimation(completion1);
    
    Animation* completion2 = new Animation(this->getAnimationName("Completion2"), 5.0f);
    completion2->setCompletionHandler([&] {
        this->dragonNode->isDisabled = true;
    });
    Engine::main->playAnimation(completion2);
}

void DragonMagic::play(CharNode * character, int seed) {
    if (!start) {
        start = true;
        play();
        Animation* dragonCoolDown = new Animation("dragon cool down " + to_string(reinterpret_cast<long>(this)), this->cooldown);
        Engine::main->playAnimation(dragonCoolDown);
        dragonCoolDown->setCompletionHandler([&] {
            start = false;
        });
        this->availableTime = Engine::main->getTime() + cooldown;
    }
}

void DragonMagic::update() {
    this->dragonShader->setFloat("time", Engine::main->getTime());
    this->dragonShader->setFloat("deathFactor", this->deathFactor);
    
    this->beamShader->setFloat("range", this->range * this->rangeFactor);
    this->beamShader->setFloat("time", Engine::main->getTime());
    this->beamShader->setVec3("start", this->getBeamPosition());
    this->beamShader->setVec3("end", this->getBeamPosition() + this->getBeamDirection() * this->range * this->rangeFactor);
    
    this->beamNode->position = vec3(this->range * this->rangeFactor * 0.5f, 0.0f, 0.0f);
    this->beamNode->scale = vec3(0.8f, 0.8f, this->range * this->rangeFactor);
    
    if(this->rangeFactor >= 0.99f) {
        this->contact->play();
        this->contact->position = this->getBeamPosition() + this->getBeamDirection() * (this->range - 1.0f);
    }else{
        this->contact->stop();
    }
}

void DragonMagic::updateMagic() {
    if (rangeFactor > 0.5) {
        hitWall();
    }
    update();
}

void DragonMagic::tryDamage(CharNode * character) {
    vec3 startPosition = this->getBeamPosition();
    vec3 endPosition = this->getBeamPosition() + this->getBeamDirection() * this->range * this->rangeFactor;
    
    if (this->rangeFactor > 0.1) {
        if (character->hitbox->testHit(startPosition, endPosition)) {
            character->receiveDamage(this->damage);
        }
    }
    
}

std::string DragonMagic::getAnimationName(std::string name) {
    return("dragonMagic" + std::to_string(this->ID) + name);
}

vec3 DragonMagic::getBeamPosition() {
    return(this->beamBaseNode->getWorldPosition());
}

vec3 DragonMagic::getBeamDirection() {
    return(this->beamBaseNode->getFrontVectorInWorld());
}

void DragonMagic::setRange(float range) {
    this->range = glm::clamp(range, 0.0f, 10000.0f);
}

void DragonMagic::hitWall() {
    HitInfo hitInfo;
    this->updateTransform();
    vec3 startPosition = this->getBeamPosition();
    vec3 endPosition = this->getBeamPosition() + this->getBeamDirection() * 10000.0f * this->rangeFactor;
    if (MapSystemManager::Instance()->hitTest(startPosition, endPosition, hitInfo, 7)) {
        this->setRange(glm::length(hitInfo.hit_point - this->getBeamPosition()));
    }else{
        this->setRange(10000.0f);
    }
}
