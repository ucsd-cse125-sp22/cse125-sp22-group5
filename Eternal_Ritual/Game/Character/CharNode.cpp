//
//  charNode.cpp
//
//  Created by futian Zhang on 4/11/22.
//  Updated by Kangming Yu on 5/14/22.
//

#include "Game/Character/CharNode.hpp"

#include <iostream>
#include <cmath>
#include <glm/gtx/io.hpp>
#include "Game/Map/MapSystemManager.hpp"

using namespace std;
using namespace glm;


CharNode::CharNode(vec3 position){
    this->position = position;
    this->moveDirection = vec3(0);
    this->displacement = vec3(0);
    
    this->hitbox = new Hitbox(this->position, vec3(0.8, 1.6, 0.8));
    this->uninjurable = false;
    this->characterTargetPosition = position;
    this->eulerAngles = vec3(0.0f);
    this->characterTargetEulerAngles = vec3(0.0f);
    this->scale = vec3(1.0f);
    this->parent = NULL;
    this->isDisabled = false;
    this->target = NULL;
    this->isLocked = false;
    this->refreshed = true;
    this->uiNode = 0;
    this->state = CharState::IDLE;
    this->currMagic = 0;
    this->scrollValue = 0;
    
    this->health = 2000;
    this->mana = 100;
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
    this->headTop = generateBoneNode("head");
    this->rightHand = generateBoneNode("Weapon_r");
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
void CharNode::setEularAngle(vec3 eularAngle){
    this->modelNode->eulerAngles = eularAngle;
    this->characterTargetEulerAngles = eularAngle;
}
void CharNode::setName(string name) {
    this->nameNode->text = name;
}
void CharNode::setUINode(UINode* uiNode){
    this->uiNode = uiNode;
    FontLibrary* fontLibrary = new FontLibrary(); // todo move font global variable
    Font* font = fontLibrary->loadFontFile("/Resources/Fonts/Cormorant/Cormorant.ttf", 100);
    TextNode* nameNode = new TextNode(font, 0.05f, 1.0f, 0.0f);
    nameNode->color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    nameNode->text = "New Character";
    nameNode->setCenterHorizontalAlignment();
    nameNode->setTopVerticalAlignment();
    nameNode->position = vec2(0, -0.12f);
    uiNode->addChildNode(nameNode);
    this->nameNode = nameNode;
}

// Helper function
float calcAngle(vec3 a, vec3 b){
    return acos(dot(normalize(a), normalize(b)));
}

void CharNode::lock(vector<CharNode*>& targets){
    CharNode* target = NULL;
    float targetDist = MAXFLOAT;
    vec3 cameraPos = cameraNode->getWorldPosition();
    vec3 cameraFront = controlNode->getFrontVectorInWorld();
    for (int i = 0; i < targets.size(); i++) {
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
        this->moveDirection += vec3(this->controlNode->getFrontVectorInWorld());
        this->moveDirection.y = 0;
        this->keyDirection = Direction::FRONT;
        refreshed = false;
    }
}
void CharNode::moveBack(){
    if (state <= CharState::ROLLING){
        this->moveDirection += vec3(this->controlNode->getBackVectorInWorld());
        this->moveDirection.y = 0;
        this->keyDirection = Direction::BACK;
        refreshed = false;
    }
}
void CharNode::moveLeft(){
    if (state <= CharState::ROLLING){
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
    this->displacement *=  0.85f;
    if (length(this->moveDirection) > 0){
        if (this->isLocked && (state != CharState::ROLLING)){
            this->displacement += normalize(this->moveDirection) * 0.1f;
            this->characterTargetPosition += this->displacement * 0.1f;
            this->characterTargetEulerAngles = vec3(0, this->getLockAngle().y + 90.0f, 0);
        }else{
            this->displacement += normalize(this->moveDirection) * 0.15f;
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
        this->stopAnimators(0x000003fc, 0.4);
        this->stopAnimators(Bitmask::RUNNING, 0.4f);
        if (state < CharState::ROLLING) {
            if(length(this->characterTargetPosition - this->position) > 0.2f){
                if (this->isLocked){
                    this->playAnimators(this->keyDirection, 0.1f);
                    state = CharState::MOVING;
                }else{
                    this->playAnimators(Bitmask::RUNNING, 0.1f);
                    state = CharState::MOVING;
                }
            }else{
                this->playAnimators(1, 0.1);
                state = CharState::IDLE;
            }
        }
        this->position += (this->characterTargetPosition - this->position) * 0.1f;
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
    node->modelNode = this->modelNode->copy();
    node->uiNode = this->uiNode->copy()->convertToUINode();
    node->controlNode = this->controlNode->copy();
    node->health = this->health;
    node->stamina = this->stamina;

    for(unsigned int i = 0; i < this->animatorNames.size(); i += 1) {
        node->animatorNames.push_back(this->animatorNames[i]);
    }
    for(unsigned int i = 0; i < this->geometries.size(); i += 1) {
        node->geometries.push_back(this->geometries[i]->copy(&node->animators));
    }
    for(unsigned int i = 0; i < this->childNodes.size(); i += 1) {
        node->addChildNode(this->childNodes[i]->copy());
        if(node->childNodes[i]->name == "modelNode"){
            node->modelNode = node->childNodes[i];
        }
    }
    node->addChildNode(node->modelNode);
    node->addChildNode(node->controlNode);
    node->addChildNode(node->uiNode);
    node->headTop = node->generateBoneNode("head");
    node->rightHand = node->generateBoneNode("Weapon_r");
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
            state = CharState::COMBATING;
            this->moveDirection = vec3(0);
            stopAnimators(0xfffffffe, 0.2);
            this->getAnimator(magic->actionName)->play(0.5);
            magic->play(this, 30);
            Animation* resume = new Animation(this->name + " resume", magic->stopTime);
            resume->setCompletionHandler([&]{
                this->state = CharState::IDLE;
            });
            Engine::main->playAnimation(resume);
            cout << "remaining mana: " << mana << endl;
        }
    }
}

void CharNode::roll() {
    if (state < CharState::ROLLING) {
        state = CharState::ROLLING;
        stopAnimators(0xfffffffe, 0.2);
        playAnimators(Bitmask::ROLL, 0.2);
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
            }
        });
        Engine::main->playAnimation(resume);

    }
    cout << this->name << " health " << this->health << endl;
}
