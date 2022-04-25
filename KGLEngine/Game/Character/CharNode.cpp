//
//  charNode.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/11/22.
//

#include "CharNode.hpp"
#include <glm/gtx/io.hpp>

CharNode::CharNode(vec3 position){
    this->position = position;
    this->moveDirection = vec3(0);
    
    this->hitbox = new Hitbox(this->position, vec3(0.4, 0.8, 0.4));
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
    this->headTop = generateBoneNode("HeadTop_End");
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
    FontLibrary* fontLibrary = new FontLibrary();
    Font* font = fontLibrary->loadFontFile("/Resources/Fonts/Cormorant/Cormorant.ttf", 100);
    TextNode* nameNode = new TextNode(font, 0.05f, 1.0f, 0.0f);
    nameNode->color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    nameNode->text = "New Character";
    nameNode->setCenterHorizontalAlignment();
    nameNode->setTopVerticalAlignment();
    nameNode->position = vec2(0, -0.07f);
    uiNode->addChildNode(nameNode);
    this->nameNode = nameNode;
}

// Helper function
float calcAngle(vec3 a, vec3 b){
    return acos(dot(normalize(a), normalize(b)));
}

void CharNode::lock(vector<CharNode*>& targets){
    CharNode* target = NULL;
    float targetDist;
    vec3 cameraPos = cameraNode->getWorldPosition();
    vec3 cameraFront = controlNode->getFrontVectorInWorld();
    for (int i = 0; i < targets.size(); i++) {
        vec3 targetPos = targets[i]->getWorldPosition() + vec3(0, 0.2f, 0);
        vec3 diffVec = targetPos - cameraPos;
        float angle = acos(dot(normalize(diffVec), normalize(cameraFront)));
        if (angle < radians(30.0f) && length(diffVec) < 10){
            if (target == NULL || targetDist > diffVec.length()){
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
void CharNode::addAnimator(string name, string file){
    this->modelNode->loadAnimator(name, file);
    this->animatorNames.push_back(name);
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
}
void CharNode::moveFront(){
    this->moveDirection += vec3(this->controlNode->getFrontVectorInWorld().x, 0, this->controlNode->getFrontVectorInWorld().z);
    this->keyDirection = FRONT;
    refreshed = false;
}
void CharNode::moveBack(){
    this->moveDirection += vec3(this->controlNode->getBackVectorInWorld().x, 0, this->controlNode->getBackVectorInWorld().z);
    this->keyDirection = BACK;
    refreshed = false;
}
void CharNode::moveLeft(){
    this->moveDirection += vec3(this->controlNode->getLeftVectorInWorld().x, 0, this->controlNode->getLeftVectorInWorld().z);
    if (refreshed){
        keyDirection = LEFT;
    }else if (this->keyDirection == FRONT){
        keyDirection = FRONTLEFT;
    }else if (this->keyDirection == BACK){
        keyDirection = BACKLEFT;
    }
    refreshed = false;
}
void CharNode::moveRight(){
    this->moveDirection += vec3(this->controlNode->getRightVectorInWorld().x, 0, this->controlNode->getRightVectorInWorld().z);
    if (refreshed){
        keyDirection = RIGHT;
    }else if (this->keyDirection == RIGHT){
        keyDirection = FRONTRIGHT;
    }else if (this->keyDirection == BACK){
        keyDirection = BACKRIGHT;
    }
    refreshed = false;
}
void CharNode::predictMoveTarget(){
    if (length(this->moveDirection) != 0){
        this->characterTargetPosition += this->moveDirection * 0.1f;
        if (this->isLocked){
            this->characterTargetEulerAngles = vec3(0, this->getLockAngle().y + 90.0f, 0);
        }else{
            if (this->moveDirection.x >= 0){
                this->characterTargetEulerAngles = vec3(0, degrees(calcAngle(this->moveDirection, vec3(0,0,1))), 0);
            }else{
                this->characterTargetEulerAngles = -vec3(0, degrees(calcAngle(this->moveDirection, vec3(0,0,1))), 0);
            }
        }
    }
    this->moveDirection = vec3(0);

}

void CharNode::updatePosition(){
    predictMoveTarget();
    if(length(this->characterTargetPosition - this->position) > 0.1f){
        if (this->isLocked){
            if (this->keyDirection == LEFT){
                this->stopAndPlay("left strafe", 0.1f, 0.1f);
            }else if (this->keyDirection == RIGHT){
                this->stopAndPlay("right strafe", 0.1f, 0.1f);
            }else if (this->keyDirection == BACK){
                this->stopAndPlay("back run", 0.1f, 0.1f);
            }else{
                this->stopAndPlay("running", 0.1f, 0.1f);
            }
        }else{
            this->stopAndPlay("running", 0.1f, 0.1f);
        }
    }else{
        this->stopAndPlay("idle", 0.1f, 0.1f);
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
    this->uiNode->screenPosition = vec2(positionOnScreen);
    this->uiNode->scale = vec2(1/pow(distance(headTop->getWorldPosition(), cameraNode->getWorldPosition()), 0.5));
}
CharNode* CharNode::copy(vec3 position) {
    CharNode* node = new CharNode(position);
    node->name = this->name;
    node->isDisabled = this->isDisabled;
    node->eulerAngles = this->eulerAngles;
    node->scale = this->scale;
    for(unsigned int i = 0; i < this->animators.size(); i += 1) {
        node->animators.push_back(this->animators[i]->engineCopyAnimator());
    }
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
    node->headTop = node->generateBoneNode("HeadTop_End");
    node->cameraNode = this->cameraNode;
    return(node);
}

