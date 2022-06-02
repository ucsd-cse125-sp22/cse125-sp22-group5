//
//  charNode.cpp
//
//  Created by futian Zhang on 4/11/22.
//  Updated by Kangming Yu on 5/14/22.
//

#include "Game/Character/CharNode.hpp"

#include <iostream>
#include <cmath>
#include <cfloat>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game/Map/MapSystemManager.hpp"

#define RUN_STEP_TIME 0.4
#define WALK_STEP_TIME 0.5

using namespace std;
using namespace glm;


bool CharNode::loaded = false;
Node* CharNode::metaModel = NULL;
Texture* CharNode::bootsD = NULL;
Texture* CharNode::bootsN = NULL;
Texture* CharNode::bootsAO = NULL;
Texture* CharNode::glovesD = NULL;
Texture* CharNode::glovesN = NULL;
Texture* CharNode::glovesAO = NULL;
Texture* CharNode::bodyD = NULL;
Texture* CharNode::bodyN = NULL;
Texture* CharNode::bodyAO = NULL;
Texture* CharNode::chestD = NULL;
Texture* CharNode::chestN = NULL;
Texture* CharNode::chestAO = NULL;
Texture* CharNode::staffD = NULL;
Texture* CharNode::staffN = NULL;
Texture* CharNode::staffAO = NULL;
Texture* CharNode::helmetD = NULL;
Texture* CharNode::helmetN = NULL;
Texture* CharNode::helmetAO = NULL;
Texture* CharNode::eyeD = NULL;
Texture* CharNode::headD = NULL;
Texture* CharNode::headN = NULL;
Texture* CharNode::headAO = NULL;
Texture* CharNode::pantsD = NULL;
Texture* CharNode::pantsN = NULL;
Texture* CharNode::hairD = NULL;
Texture* CharNode::hairBaseD = NULL;
AudioBuffer* CharNode::footStep = NULL;
AudioBuffer* CharNode::rollSound = NULL;

void CharNode::load() {
    loaded = true;
    metaModel = new Node();
    metaModel->scale = vec3(0.5f);
    metaModel->loadModelFile("/Resources/Game/Character/Character.dae");
    if(true) {
        PBRShader* shader = new PBRShader(0.2f, 0.8f);
        bootsD = new Texture("/Resources/Game/Character/BootsD.png", 2.0f, true);
        bootsN = new Texture("/Resources/Game/Character/BootsN.png", 2.0f, true);
        bootsAO = new Texture("/Resources/Game/Character/BootsAO.png", 2.0f, true);
        shader->setDiffuseMap(bootsD);
        shader->setNormalMap(bootsN);
        shader->setAmbientOcclusionMap(bootsAO);
        metaModel->geometries[0]->setShader(shader);
        metaModel->geometries[1]->setShader(shader);
        metaModel->geometries[6]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.2f, 0.8f);
        glovesD = new Texture("/Resources/Game/Character/GlovesD.png", 2.0f, true);
        glovesN = new Texture("/Resources/Game/Character/GlovesN.png", 2.0f, true);
        glovesAO = new Texture("/Resources/Game/Character/GlovesAO.png", 2.0f, true);
        shader->setDiffuseMap(glovesD);
        shader->setNormalMap(glovesN);
        shader->setAmbientOcclusionMap(glovesAO);
        metaModel->geometries[2]->setShader(shader);
        metaModel->geometries[3]->setShader(shader);
        metaModel->geometries[4]->setShader(shader);
        metaModel->geometries[5]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader("/Resources/Game/Character/Character", 0.1f, 0.9f);
        bodyD = new Texture("/Resources/Game/Character/BodyD.png", 2.0f, true);
        bodyN = new Texture("/Resources/Game/Character/BodyN.png", 2.0f, true);
        bodyAO = new Texture("/Resources/Game/Character/BodyAO.png", 2.0f, true);
        shader->setDiffuseMap(bodyD);
        shader->setNormalMap(bodyN);
        shader->setAmbientOcclusionMap(bodyAO);
        shader->setFloat("shadowBias", 0.05f);
        metaModel->geometries[7]->setShader(shader);
        metaModel->geometries[13]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader("/Resources/Game/Character/Character", 0.4f, 0.4f);
        chestD = new Texture("/Resources/Game/Character/ChestD.png", 2.0f, true);
        chestN = new Texture("/Resources/Game/Character/ChestN.png", 1.0f, true);
        chestAO = new Texture("/Resources/Game/Character/ChestAO.png", 1.0f, true);
        shader->setDiffuseMap(chestD);
        shader->setNormalMap(chestN);
        shader->setAmbientOcclusionMap(chestAO);
        shader->setFloat("shadowBias", 0.01f);
        metaModel->geometries[8]->setShader(shader);
        metaModel->geometries[9]->setShader(shader);
        metaModel->geometries[10]->setShader(shader);
        metaModel->geometries[11]->setShader(shader);
        metaModel->geometries[12]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.8f, 0.2f);
        staffD = new Texture("/Resources/Game/Character/StaffD.png", 2.0f, true);
        staffN = new Texture("/Resources/Game/Character/StaffN.png", 1.0f, true);
        staffAO = new Texture("/Resources/Game/Character/StaffAO.png", 1.0f, true);
        shader->setDiffuseMap(staffD);
        shader->setNormalMap(staffN);
        shader->setAmbientOcclusionMap(staffAO);
        metaModel->geometries[14]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.8f, 0.2f);
        helmetD = new Texture("/Resources/Game/Character/HelmetD.png", 2.0f, true);
        helmetN = new Texture("/Resources/Game/Character/HelmetN.png", 1.0f, true);
        helmetAO = new Texture("/Resources/Game/Character/HelmetAO.png", 1.0f, true);
        shader->setDiffuseMap(helmetD);
        shader->setNormalMap(helmetN);
        shader->setAmbientOcclusionMap(helmetAO);
        metaModel->geometries[15]->setShader(shader);
        metaModel->geometries[16]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.2f, 0.2f);
        eyeD = new Texture("/Resources/Game/Character/EyeD.png", 2.0f, true);
        shader->setDiffuseMap(eyeD);
        metaModel->geometries[17]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader("/Resources/Game/Character/Character", 0.1f, 0.9f);
        headD = new Texture("/Resources/Game/Character/HeadD.png", 2.0f, true);
        headN = new Texture("/Resources/Game/Character/HeadN.png", 1.0f, true);
        headAO = new Texture("/Resources/Game/Character/HeadAO.png", 1.0f, true);
        shader->setDiffuseMap(headD);
        shader->setNormalMap(headN);
        shader->setAmbientOcclusionMap(headAO);
        shader->setFloat("shadowBias", 0.5f);
        metaModel->geometries[18]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.5f, 0.5f);
        pantsD = new Texture("/Resources/Game/Character/PantsD.png", 2.0f, true);
        shader->setDiffuseMap(pantsD);
        pantsN = new Texture("/Resources/Game/Character/PantsN.png", 1.0f, true);
        shader->setNormalMap(pantsN);
        metaModel->geometries[19]->setShader(shader);
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.0f, 1.0f);
        hairD = new Texture("/Resources/Game/Character/HairD.png", 1.0f, true);
        shader->setDiffuseMap(hairD);
        metaModel->geometries[20]->setShader(shader);
        metaModel->geometries[20]->setDoubleSided();
        metaModel->geometries[21]->setShader(shader);
        metaModel->geometries[21]->setDoubleSided();
        metaModel->geometries[22]->setShader(shader);
        metaModel->geometries[22]->setDoubleSided();
        metaModel->geometries[23]->setShader(shader);
        metaModel->geometries[23]->setDoubleSided();
    }
    if(true) {
        PBRShader* shader = new PBRShader(0.0f, 1.0f);
        hairBaseD = new Texture("/Resources/Game/Character/HairBaseD.png", 1.0f, true);
        shader->setDiffuseMap(hairBaseD);
        metaModel->geometries[24]->setShader(shader);
    }
    metaModel->position = vec3(0.0f, 0.01f, 0.0f);
    metaModel->eulerAngles = vec3(0.0f, 45.0f, 0.0f);
    metaModel->scale = vec3(0.9f);
    Animator* idle = metaModel->loadAnimator("idle", "/Resources/Game/Character/Animations/Idle.dae");
    idle->play(0.2);
    idle->animatorBitMask = Bitmask::IDLE;
    Animator* running = metaModel->loadAnimator("running", "/Resources/Game/Character/Animations/Running.dae");
    running->animatorBitMask = Bitmask::RUNNING;
    Animator* fwdWalk = metaModel->loadAnimator("fwd walk", "/Resources/Game/Character/Animations/Walk Fwd.dae");
    fwdWalk->animatorBitMask = Bitmask::WALKFWD;
    Animator* backWalk = metaModel->loadAnimator("back walk", "/Resources/Game/Character/Animations/Walk Bck.dae");
    backWalk->animatorBitMask = Bitmask::WALKBCK;
    Animator* leftStrafe = metaModel->loadAnimator("left strafe", "/Resources/Game/Character/Animations/Left Strafe.dae");
    leftStrafe->animatorBitMask = Bitmask::WALKLEFT;
    Animator* rightStrafe = metaModel->loadAnimator("right strafe", "/Resources/Game/Character/Animations/Right Strafe.dae");
    rightStrafe->animatorBitMask = Bitmask::WALKRIGHT;
    Animator* frontRight = metaModel->loadAnimator("front right", "/Resources/Game/Character/Animations/Front Right.dae");
    frontRight->animatorBitMask = Bitmask::WALKFR;
    Animator* frontLeft = metaModel->loadAnimator("front left", "/Resources/Game/Character/Animations/Front Left.dae");
    frontLeft->animatorBitMask = Bitmask::WALKFL;
    Animator* backLeft = metaModel->loadAnimator("back left", "/Resources/Game/Character/Animations/Back Left.dae");
    backLeft->animatorBitMask = Bitmask::WALKBL;
    Animator* backRight = metaModel->loadAnimator("back right", "/Resources/Game/Character/Animations/Back Right.dae");
    backRight->animatorBitMask = Bitmask::WALKBR;
    Animator* roll = metaModel->loadAnimator("roll", "/Resources/Game/Character/Animations/Roll Fwd.dae");
    roll->animatorBitMask = Bitmask::ROLL;
    roll->speed = 1.5;
    roll->repeats = false;
    Animator* dragonAttack = metaModel->loadAnimator("dragon attack", "/Resources/Game/Character/Animations/DragonAttack.dae");
    dragonAttack->animatorBitMask = Bitmask::DRAGON_ATT;
    dragonAttack->repeats = false;
    Animator* castMagic1 = metaModel->loadAnimator("cast magic 1", "/Resources/Game/Character/Animations/CastMagic1.dae");
    castMagic1->animatorBitMask = Bitmask::MAGIC_CAST_1;
    castMagic1->repeats = false;
    Animator* castMagic2 = metaModel->loadAnimator("cast magic 2", "/Resources/Game/Character/Animations/CastMagic5.dae");
    castMagic2->animatorBitMask = Bitmask::MAGIC_CAST_2;
    castMagic2->repeats = false;
    Animator* castMagic3 = metaModel->loadAnimator("cast magic 3", "/Resources/Game/Character/Animations/CastMagic3.dae");
    castMagic3->animatorBitMask = Bitmask::MAGIC_CAST_3;
    castMagic3->repeats = false;
    Animator* damaged = metaModel->loadAnimator("damaged", "/Resources/Game/Character/Animations/Damaged.dae");
    damaged->animatorBitMask = Bitmask::DAMAGED;
    damaged->repeats = false;
    Animator* death = metaModel->loadAnimator("death", "/Resources/Game/Character/Animations/Death.dae");
    death->animatorBitMask = Bitmask::DEAD;
    death->repeats = false;
    death->clamps = true;
    footStep = new AudioBuffer("/Resources/Game/Sound/footstep", "wav", 1, 9);
    rollSound = new AudioBuffer("/Resources/Game/Sound/roll", "wav", 1, 3);
}

CharNode::CharNode(vec3 position){
    if (!loaded) load();
    this->setModel(metaModel->copy());
    this->modelNode->isDisabled = false;
    this->position = position;
    this->moveDirection = vec3(0);
    this->displacement = vec3(0);
    
    this->hitbox = new Hitbox(this->position, vec3(0.8, 1.6, 0.8));
    this->uninjurable = false;
    this->characterTargetPosition = position;
    this->eulerAngles = vec3(0.0f);
    this->characterTargetEulerAngles = vec3(0.0f);
    this->cameraTargetEulerAngles = vec3(0.0f);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->target = NULL;
    this->isLocked = false;
    this->refreshed = true;
    this->uiNode = 0;
    this->state = CharState::IDLE;
    this->keyDirection = Direction::NONE;
    this->currMagic = 0;
    this->scrollValue = 0;
    this->loadAudioBuffer("foot step", footStep, 2, 1);
    this->loadAudioBuffer("roll", rollSound, 2, 1);
    this->changeAudioVolume("roll", 0.2, 0);
    
    this->health = MAXHP;
    this->mana = MAXMANA;
    this->manaRegen = MAXMANAREGEN;
    this->stepAvailable = 0;
}
void CharNode::reset() {
    this->moveDirection = vec3(0);
    this->displacement = vec3(0);
    
    this->hitbox = new Hitbox(this->position, vec3(0.8, 1.6, 0.8));
    this->uninjurable = false;
    this->characterTargetPosition = position;
    this->eulerAngles = vec3(0.0f);
    this->characterTargetEulerAngles = vec3(0.0f);
    this->cameraTargetEulerAngles = vec3(0.0f);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    stopAnimators(0xffffffff, 0.2);
    playAnimators(Bitmask::IDLE, 0.1);
    this->target = NULL;
    this->isLocked = false;
    this->refreshed = true;
    this->uiNode = 0;
    this->state = CharState::IDLE;
    this->keyDirection = Direction::NONE;
    this->currMagic = 0;
    this->scrollValue = 0;
    
    this->health = MAXHP;
    this->mana = MAXMANA;
    this->manaRegen = MAXMANAREGEN;
    this->stepAvailable = 0;
    
}
CharNode::~CharNode(){
    
}
Node* CharNode::generateBoneNode(string boneName) {
    return this->modelNode->generateBoneNode(boneName);
}
void CharNode::setModel(Node* model){
    this->modelNode = model;
    this->modelNode->name = "modelNode";
    this->addChildNode(model);
    Node* rootNode = generateBoneNode("root");
    this->headTop = new Node();
    headTop->position.z = 1.7;
    rootNode->addChildNode(headTop);
    this->rightHand = generateBoneNode("Weapon_r");
    this->leftHand = generateBoneNode("Weapon_l");
}
void CharNode::setControl(Node* control){
    this->controlNode = control;
    this->addChildNode(control);
    this->cameraTargetEulerAngles = controlNode->eulerAngles;
}
void CharNode::setCamera(CameraNode* camera){
    this->cameraNode = camera;
    this->controlNode->addChildNode(camera);
}
void CharNode::setCharacterEularAngle(vec3 eularAngle){
    this->modelNode->eulerAngles = eularAngle;
    this->characterTargetEulerAngles = eularAngle;
}
void CharNode::setCameraEularAngle(vec3 eularAngle){
    this->controlNode->eulerAngles = eularAngle;
    this->cameraTargetEulerAngles = eularAngle;
}
void CharNode::setCharacterPosition(vec3 position) {
    this->position = position;
    this->characterTargetPosition = position;
}
void CharNode::setName(string name) {
//    this->nameNode->text = name;
}

void CharNode::setUINode(UINode* uiNode){
    this->uiNode = uiNode;
    //FontLibrary* fontLibrary = new FontLibrary(); // todo move font global variable
    //Font* font = fontLibrary->loadFontFile("/Resources/Fonts/Cormorant/Cormorant.ttf", 100);
  /*  TextNode* nameNode = new TextNode(font, 0.05f, 1.0f, 0.0f);
    nameNode->color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    nameNode->text = "New Character";
    nameNode->setCenterHorizontalAlignment();
    nameNode->setTopVerticalAlignment();
    nameNode->position = vec2(0, -0.12f);
    uiNode->addChildNode(nameNode);*/
    //this->nameNode = nameNode;
}

// Helper function
float calcAngle(vec3 a, vec3 b){
    return acos(dot(normalize(a), normalize(b)));
}

void CharNode::lock(vector<CharNode*>& targets){
    CharNode* target = NULL;
    float targetDist = FLT_MAX;
    vec3 cameraPos = cameraNode->getWorldPosition();
    vec3 cameraFront = controlNode->getFrontVectorInWorld();
    for (int i = 0; i < targets.size(); i++) {
        if (!targets[i]->isDisabled) {
            vec3 targetPos = targets[i]->getWorldPosition() + vec3(0, 0.2f, 0);
            vec3 diffVec = targetPos - cameraPos;
            float angle = acos(dot(normalize(diffVec), normalize(cameraFront)));
            if (angle < radians(30.0f) && length(diffVec) < 20){
                if (targetDist > diffVec.length()){
                    target = targets[i];
                    targetDist = diffVec.length();
                }
            }
        }
    }
    if(target != NULL){
        this->target = target;
        this->isLocked = true;
        cout << "Lock " << target->name << endl;
    }
}
void CharNode::unlock(){
    cout << "Unlock " << target->name << endl;
    this->target = NULL;
    this->isLocked = false;
}
void CharNode::toggleLock(vector<CharNode*>& enemies){
    if(this->isLocked){
        this->unlock();
    }else{
        this->lock(enemies);
    }
}
vec3 CharNode::getLockAngle(){
    vec3 targetPos = target->getWorldPosition();
    vec3 diffVec = targetPos - this->getWorldPosition() - vec3(0, 0.5f, 0);
    vec3 eularAngle;
    if (diffVec.z >= 0){
        eularAngle = vec3(0, -degrees(calcAngle(vec3(diffVec.x, 0, diffVec.z), vec3(1.0f, 0, 0))), 90.0f - degrees(calcAngle(diffVec, vec3(0, 1.0f, 0))));
    }else {
        eularAngle = vec3(0, degrees(calcAngle(vec3(diffVec.x, 0, diffVec.z), vec3(1.0f, 0, 0))), 90.0f - degrees(calcAngle(diffVec, vec3(0, 1.0f, 0))));
    }
    if (length(diffVec) > 15){
        this->unlock();
    }
    return eularAngle;
}
Animator* CharNode::addAnimator(string name, string file){
    this->animatorNames.push_back(name);
    return this->modelNode->loadAnimator(name, file);
}
Animator* CharNode::getAnimator(std::string name){
    return this->modelNode->getAnimator(name);
}
void CharNode::playAnimators(unsigned int mask, float fadeIn, float fadeOut) {
    this->modelNode->playAnimators(mask, fadeIn, fadeOut);
}
void CharNode::stopAnimators(unsigned int mask, float fadeOut) {
    this->modelNode->stopAnimators(mask, fadeOut);
}
void CharNode::stopAndPlay(string name, float fade_in, float fade_out){
    for (int i = 0; i < this->animatorNames.size(); i++){
        if (this->animatorNames[i] != name && this->modelNode->getAnimator(this->animatorNames[i])->isPlaying()){
            this->modelNode->getAnimator(this->animatorNames[i])->stop(fade_out);
        }
    }
    this->modelNode->getAnimator(name)->play(fade_in);
}
void CharNode::moveCamera(vec2 mouseTranslation){
    if(this->isLocked){
        this->cameraTargetEulerAngles = this->getLockAngle();
    }else{
        this->cameraTargetEulerAngles.y -= mouseTranslation.x;
        this->cameraTargetEulerAngles.z -= mouseTranslation.y;
    }
    this->cameraTargetEulerAngles.z = glm::max(-60.0f, glm::min(this->cameraTargetEulerAngles.z, 60.0f));
    
    vec3 naiveMove = this->cameraTargetEulerAngles - this->controlNode->eulerAngles;
    vec3 moreMove = this->cameraTargetEulerAngles - this->controlNode->eulerAngles + vec3(0,360,0);
    vec3 lessMove = this->cameraTargetEulerAngles - this->controlNode->eulerAngles - vec3(0,360,0);
    if (length(naiveMove) < length(moreMove) && length(naiveMove) < length(lessMove)){
        controlNode->eulerAngles += naiveMove * 0.2f;
    }else if (length(moreMove) < length(lessMove)){
        controlNode->eulerAngles += moreMove * 0.2f;
    }else{
        controlNode->eulerAngles += lessMove * 0.2f;
    }
    
    if (this->cameraTargetEulerAngles.y > 180){
        this->cameraTargetEulerAngles.y -= 360;
    }
    if (this->cameraTargetEulerAngles.y < -180){
        this->cameraTargetEulerAngles.y += 360;
    }
    
    if (controlNode->eulerAngles.y > 180){
        controlNode->eulerAngles.y -= 360;
    }
    if (controlNode->eulerAngles.y < -180){
        controlNode->eulerAngles.y += 360;
    }
    HitInfo hitInfo;
    if (MapSystemManager::Instance()->hitTest(this->controlNode->getWorldPosition(), this->cameraNode->getWorldPosition() + normalize(this->cameraNode->getWorldPosition() - this->controlNode->getWorldPosition()) * 0.3f, hitInfo)) {
        this->cameraNode->position.x = std::max(-length(hitInfo.hit_point - this->controlNode->getWorldPosition()) + 0.1f, -2.5f);
    }
    else {
        this->cameraNode->position.x = -2.5;
    }
}
void CharNode::moveFront(){
    if (state <= CharState::ROLLING){
        if (state != CharState::ROLLING) {
            state = CharState::MOVING;
        }
        this->moveDirection += vec3(this->controlNode->getFrontVectorInWorld());
        this->moveDirection.y = 0;
        this->keyDirection = Direction::FRONT;
        refreshed = false;
    }
}
void CharNode::moveBack(){
    if (state <= CharState::ROLLING){
        if (state != CharState::ROLLING) {
            state = CharState::MOVING;
        }
        this->moveDirection += vec3(this->controlNode->getBackVectorInWorld());
        this->moveDirection.y = 0;
        this->keyDirection = Direction::BACK;
        refreshed = false;
    }
}
void CharNode::moveLeft(){
    if (state <= CharState::ROLLING){
        if (state != CharState::ROLLING) {
            state = CharState::MOVING;
        }
        this->moveDirection += vec3(this->controlNode->getLeftVectorInWorld());
        this->moveDirection.y = 0;
        if (refreshed){
            keyDirection = Direction::LEFT;
        }else if (this->keyDirection == Direction::FRONT){
            keyDirection = Direction::FRONTLEFT;
        }else if (this->keyDirection == Direction::BACK){
            keyDirection = Direction::BACKLEFT;
        }
        refreshed = false;
    }
}
void CharNode::moveRight(){
    if (state <= CharState::ROLLING){
        if (state != CharState::ROLLING) {
            state = CharState::MOVING;
        }
        this->moveDirection += vec3(this->controlNode->getRightVectorInWorld());
        this->moveDirection.y = 0;
        if (refreshed){
            keyDirection = Direction::RIGHT;
        }else if (this->keyDirection == Direction::FRONT){
            keyDirection = Direction::FRONTRIGHT;
        }else if (this->keyDirection == Direction::BACK){
            keyDirection = Direction::BACKRIGHT;
        }
        refreshed = false;
    }
}
void CharNode::predictMoveTarget(){
    this->displacement *=  0.0f;
    if (length(this->moveDirection) > 0){
        if (this->isLocked && (state != CharState::ROLLING)){
            this->displacement = normalize(this->moveDirection) * 0.5f;
            this->characterTargetPosition += this->displacement * 0.1f;
            this->characterTargetEulerAngles = vec3(0, this->getLockAngle().y + 90.0f, 0);
        }else{
            this->displacement = normalize(this->moveDirection) * 1.f;
            this->characterTargetPosition += this->displacement * 0.1f;
            if (this->moveDirection.x >= 0){
                this->characterTargetEulerAngles = vec3(0, degrees(calcAngle(this->displacement, vec3(0,0,1))), 0);
            }else{
                this->characterTargetEulerAngles = -vec3(0, degrees(calcAngle(this->displacement, vec3(0,0,1))), 0);
            }
        }
    }
    if (state < CharState::ROLLING){
        this->moveDirection = vec3(0);
    }

}

void CharNode::updatePosition(){
    if (state <= CharState::COMBATING){
        predictMoveTarget();
        this->stopAnimators(0x000003fe, 0.4);
        if (state < CharState::ROLLING) {
            if(state == CharState::MOVING){
                if (this->isLocked){
                    this->playAnimators(this->keyDirection, 0.1f);
                    if (Engine::main->getTime() > this->stepAvailable) {
                        this->playAudio("foot step");
                        this->stepAvailable = Engine::main->getTime() + WALK_STEP_TIME;
                    }
                }else{
                    this->playAnimators(Bitmask::RUNNING, 0.1f);
                    if (Engine::main->getTime() > this->stepAvailable) {
                        this->playAudio("foot step");
                        this->stepAvailable = Engine::main->getTime() + RUN_STEP_TIME;
                    }
                }
                state = CharState::IDLE;
            }else{
                this->playAnimators(1, 0.1);
            }
        }
        
        // Hit map test
        vec3 movement = this->characterTargetPosition - this->position;
        vec3 movementNorm;
        if (length(movement) < 0.00001) {
            movementNorm = vec3(0);
        }
        else {
            movementNorm = normalize(movement);
        }

        HitInfo leftBottomHitInfo, rightBottomHitInfo, midBottomHitInfo, leftTopHitInfo, rightTopHitInfo;
        vec3 modelWorldPosition = this->modelNode->getWorldPosition();
        vec3 startBottom = modelWorldPosition + vec3(0.0f, 0.3f, 0.0f);
        vec3 startTop = modelWorldPosition + vec3(0.0f, 1.6f, 0.0f);
        
        mat4 trans = mat4(1.0f);
        mat3 rotationMtx = glm::rotate(trans, radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
        vec3 midDir = movementNorm * 0.8f;
        vec3 leftDir = rotationMtx * movementNorm * 0.7f;
        rotationMtx = glm::rotate(trans, radians(-45.0f), vec3(0.0f, 1.0f, 0.0f));
        vec3 rightDir = rotationMtx * movementNorm * 0.7f;
        
        bool midBottomHit = MapSystemManager::Instance()->gridsHitTest(startBottom, startBottom + midDir, midBottomHitInfo);
        
        bool leftBottomHit = MapSystemManager::Instance()->gridsHitTest(startBottom, startBottom + leftDir, leftBottomHitInfo);
        
        bool rightBottomHit = MapSystemManager::Instance()->gridsHitTest(startBottom,  startBottom + rightDir, rightBottomHitInfo);
        
        bool leftTopHit = MapSystemManager::Instance()->gridsHitTest(startTop, startTop + leftDir, leftTopHitInfo);

        bool rightTopHit = MapSystemManager::Instance()->gridsHitTest(startTop, startTop + rightDir, rightTopHitInfo);
        
        if (leftBottomHit && rightBottomHit) {
            this->characterTargetPosition = this->position;
        }
        else if (leftBottomHit) {
            vec3 hitNormal = normalize(vec3(leftBottomHitInfo.normal.x, 0.0f, leftBottomHitInfo.normal.z));
            this->characterTargetPosition -= dot(hitNormal, movement) * hitNormal;
        }
        else if (rightBottomHit) {
            vec3 hitNormal = normalize(vec3(rightBottomHitInfo.normal.x, 0.0f, rightBottomHitInfo.normal.z));
            this->characterTargetPosition -= dot(hitNormal, movement) * hitNormal;
        }
        else if (midBottomHit) {
            this->characterTargetPosition = this->position;
        }
        else if (leftTopHit) {
            vec3 hitNormal = normalize(vec3(leftTopHitInfo.normal.x, 0.0f, leftTopHitInfo.normal.z));
            this->characterTargetPosition -= dot(hitNormal, movement) * hitNormal;
        }
        else if (rightTopHit) {
            vec3 hitNormal = normalize(vec3(rightTopHitInfo.normal.x, 0.0f, rightTopHitInfo.normal.z));
            this->characterTargetPosition -= dot(hitNormal, movement) * hitNormal;
        }
        
        
        HitInfo heightHitInfo;
        vec3 startHeight = startBottom + vec3(0.0f, 0.1f, 0.0f);
        vec3 endHeight = vec3(startHeight.x, startHeight.y - 10.0f, startHeight.z);
        MapSystemManager::Instance()->gridsHitTest(startHeight, endHeight, heightHitInfo);
        vec3 hitPoint = heightHitInfo.hit_point;
        if (hitPoint.y < modelWorldPosition.y - 0.08f) {
            this->characterTargetPosition.y = hitPoint.y;
//            this->isFall = true;
        }
        else {
            this->position.y = hitPoint.y;
            this->characterTargetPosition.y = hitPoint.y;
//            this->isFall = false;
        }
        
        
        this->position.x += (this->characterTargetPosition.x - this->position.x) * 0.5f;
        this->position.z += (this->characterTargetPosition.z - this->position.z) * 0.5f;
        this->position.y += (this->characterTargetPosition.y - this->position.y) * 0.9f;
        
        
        this->hitbox->updatePosition(this->position);
        vec3 naiveMove = this->characterTargetEulerAngles - this->modelNode->eulerAngles;
        vec3 moreMove = this->characterTargetEulerAngles - this->modelNode->eulerAngles + vec3(0,360,0);
        vec3 lessMove = this->characterTargetEulerAngles - this->modelNode->eulerAngles - vec3(0,360,0);
        if (length(naiveMove) < length(moreMove) && length(naiveMove) < length(lessMove)){
            this->modelNode->eulerAngles += naiveMove * 0.2f;
        }else if (length(moreMove) < length(lessMove)){
            this->modelNode->eulerAngles += moreMove * 0.2f;
        }else{
            this->modelNode->eulerAngles += lessMove * 0.2f;
        }
        
        if (this->characterTargetEulerAngles.y > 180){
            this->characterTargetEulerAngles.y -= 360;
        }
        if (this->characterTargetEulerAngles.y < -180){
            this->characterTargetEulerAngles.y += 360;
        }
        
        if (this->modelNode->eulerAngles.y > 180){
            this->modelNode->eulerAngles.y -= 360;
        }
        if (this->modelNode->eulerAngles.y < -180){
            this->modelNode->eulerAngles.y += 360;
        }
        this->refreshed = true;
        vec3 positionOnScreen = headTop->getPositionOnScreen();
        this->uiNode->screenPosition = vec2(positionOnScreen.x, positionOnScreen.y);
        this->uiNode->scale = vec2(1/pow(positionOnScreen.z, 0.5));
    }

}
CharNode* CharNode::copy(vec3 position) {
    CharNode* node = new CharNode(position);
    node->name = this->name;
    node->isDisabled = this->isDisabled;
    node->eulerAngles = this->eulerAngles;
    node->scale = this->scale;
    node->state = this->state;
    node->uiNode = this->uiNode->copy()->convertToUINode();
    node->controlNode = this->controlNode->copy();
    node->health = this->health;
    node->stamina = this->stamina;
    node->mana = this->mana;
    node->manaRegen = this->manaRegen;

    for(unsigned int i = 0; i < this->animatorNames.size(); i += 1) {
        node->animatorNames.push_back(this->animatorNames[i]);
    }
    for(unsigned int i = 0; i < this->geometries.size(); i += 1) {
        node->geometries.push_back(this->geometries[i]->copy(&node->animators));
    }
    node->addChildNode(node->controlNode);
    node->addChildNode(node->uiNode);
//    node->cameraNode = this->cameraNode;
    return(node);
}


void CharNode::addMagics(BaseMagic* magic){
    this->magics.push_back(magic);
}

BaseMagic* CharNode::rmMagics() {
    BaseMagic* temp = this->magics[currMagic];
    this->magics.erase(this->magics.begin()+currMagic);
    return temp;
}

void CharNode::chooseNextMagic() {
    this->currMagic++;
    this->currMagic %= this->magics.size();
}

void CharNode::chooseLastMagic() {
    this->currMagic+= this->magics.size();
    this->currMagic--;
    this->currMagic %= this->magics.size();
}

void CharNode::scrollMagic(float acceleration) {
    scrollValue += std::min(acceleration, 0.5f);
    if (abs(scrollValue) > 2) {
        this->currMagic += round(scrollValue / abs(scrollValue)) + this->magics.size();
        this->currMagic = this->currMagic % this->magics.size();
        this->scrollValue = 0;
    }
}

void CharNode::setCurrMagic(int index) {
    if (index < this->magics.size()) {
        this->currMagic = index;
        scrollValue = 0;
    }
}

void CharNode::castMagic(){
    if (state < CharState::ROLLING && !this->magics[currMagic]->start){
        BaseMagic* magic = this->magics[currMagic];
        if (mana > magic->cost && Engine::main->getTime() > magic->availableTime) {
            mana -= magic->cost;
            manaRegen = 0;
            Animation* manaGen = new Animation(to_string(reinterpret_cast<long>(this)) + "mana regen ", 1);
            manaGen->setFloatAnimation(&(this->manaRegen), MAXMANAREGEN);
            manaGen->setEaseInTimingMode();
            Engine::main->playAnimation(manaGen);
            state = CharState::COMBATING;
            this->moveDirection = vec3(0);
            stopAnimators(0xfffffffe, 0.2);
            this->getAnimator(magic->actionName)->play(0.5);
            magic->play(this, 30);
            Animation* resume = new Animation(this->name + " resume", magic->stopTime);
            resume->setCompletionHandler([&, magic]{
                this->state = CharState::IDLE;
                this->getAnimator(magic->actionName)->stop(0.4);
            });
            Engine::main->playAnimation(resume);
//            cout << "remaining mana: " << mana << endl;
        }
    }
}

void CharNode::genMana() {
    if (state < CharState::ROLLING && mana < MAXMANA) {
        mana = std::min((float)MAXMANA, mana + manaRegen);
//        cout << "curr mana: " << mana << endl;
    }
}

void CharNode::roll() {
    if (state < CharState::ROLLING && this->mana > MAXMANA / 10) {
        state = CharState::ROLLING;
        this->playAudio("roll");
        stopAnimators(0xfffffffe, 0.2);
        playAnimators(Bitmask::ROLL, 0.2);
        mana -= ROLL_COST;
        manaRegen = 0;
        Animation* manaGen = new Animation(to_string(reinterpret_cast<long>(this)) + "mana regen ", 1);
        manaGen->setFloatAnimation(&(this->manaRegen), MAXMANAREGEN);
        manaGen->setEaseInTimingMode();
        Engine::main->playAnimation(manaGen);
        Animation* resume = new Animation(this->name + " resume", 0.7);
        this->moveDirection = this->modelNode->getRightVectorInWorld();
        this->moveDirection.y = 0;
        this->moveDirection = normalize(this->moveDirection);
        this->uninjurable = true;
        resume->setCompletionHandler([&]{
            this->state = CharState::IDLE;
            this->moveDirection = vec3(0);
            stopAnimators(Bitmask::ROLL, 0.3);
            this->uninjurable = false;
        });
        Engine::main->playAnimation(resume);
    }
}


void CharNode::receiveDamage(int damage){
    if (!uninjurable && this->state < CharState::DAMAGED) {
        this->health -= damage;
        state = CharState::DAMAGED;
        stopAnimators(0xffff8000, 0.2);
        playAnimators(Bitmask::DAMAGED, 0.1);
        this->state = CharState::COMBATING;
        this->displacement = vec3(0);
        this->moveDirection = vec3(0);
        Animation* resume = new Animation(this->name + " resume", 0.5);
        this->uninjurable = true;
        resume->setCompletionHandler([&]{
            this->state = CharState::IDLE;
            stopAnimators(Bitmask::DAMAGED, 0.2);
            this->uninjurable = false;
            if (this->health <= 0) {
                stopAnimators(0xffffffff, 0.2);
                playAnimators(Bitmask::DEAD, 0.1);
                this->state = CharState::DEAD;
                this->uiNode->isDisabled = true;
                this->hitbox = new Hitbox(this->position, vec3(0, 0, 0));
            }
        });
        Engine::main->playAnimation(resume);

    }
//    cout << this->name << " health " << this->health << endl;
}
