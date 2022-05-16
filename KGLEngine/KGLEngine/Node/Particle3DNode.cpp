// Developed by Kelin Lyu.
#include "Node.hpp"
Particle3DNode::Particle3DNode(string modelFile, unsigned int birthrate, float duration, float durationVariation) {
    this->mesh = nullptr;
    Assimp::Importer importer;
    unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
    const aiScene* scene = importer.ReadFile(Engine::main->workingDirectory + modelFile, flags);
    if(scene == NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "\nFailed to load the 3D model file: "
        << Engine::main->workingDirectory + modelFile << "!\n" << endl;
        exit(0);
    }
    this->engineProcessNode2(scene->mRootNode, scene);
    this->engineInitializeNode();
    this->currentParticle3DNode = this;
    this->hasUnfreezableGeometries = true;
    this->isPlaying = true;
    this->hasLimit = false;
    this->maxAmount = 0;
    this->useEmissionColor = false;
    this->currentAmount = 0;
    this->birthrate = birthrate;
    this->duration = duration;
    this->durationVariation = durationVariation;
    this->productionAmount = (unsigned int)glm::max(1.0f, (float)birthrate / 60.0f);
    this->productionTime = 0.0f;
    this->productionTimeInterval = 1.0f / (float)birthrate;
    this->particleDuration = duration;
    this->particleDurationVariation = durationVariation;
    this->emissionShape = 0;
    this->emissionAlpha = 1;
    this->innerSphereRadius = 0.0f;
    this->outerSphereRadius = 0.0f;
    this->boxSize = vec3(0.0f);
    this->renderingOrder = 0.0f;
    this->useLocalSpace = false;
    this->isAdditive = false;
    this->youngestFirst = true;
    this->speedFactor = 1.0f;
    this->spreadingAngle = 0.0f;
    this->initialSpeed = 0.0f;
    this->initialSpeedVariation = 0.0f;
    this->speedAcceleration = 0.0f;
    this->speedAccelerationVariation = 0.0f;
    this->acceleration = vec3(0.0f);
    this->accelerationVariation = vec3(0.0f);
    this->initialRotation = vec3(0.0f);
    this->initialRotationVariation = vec3(0.0f);
    this->rotatingSpeed = vec3(0.0f);
    this->rotatingSpeedVariation = vec3(0.0f);
    this->randomizeRotatingDirection = false;
    this->initialScale = vec3(1.0f);
    this->initialScaleVariation = vec3(0.0f);
    this->scalingSpeed = vec3(0.0f);
    this->scalingSpeedVariation = vec3(0.0f);
    this->texture = NULL;
    this->color = vec4(1.0f);
    this->spriteSheetAnimationInitialFrameRange = 0;
    this->spriteSheetAnimationFPS = 0;
    this->spriteSheetAnimationFPSVariation = 0;
    float amount = birthrate * ((unsigned int)glm::floor(duration + durationVariation) + 1);
    this->renderer = new Particle3DRenderer(amount, this->mesh);
    this->shader = new Particle3DShader(this);
    this->renderer->setShader(this->shader);
}
void Particle3DNode::engineProcessNode2(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i += 1) {
        this->mesh = scene->mMeshes[node->mMeshes[i]];
    }
    for(unsigned int i = 0; i < node->mNumChildren; i += 1) {
        this->engineProcessNode2(node->mChildren[i], scene);
    }
}
Node* Particle3DNode::copy() {
    assert(false);
    Particle3DNode* node = new Particle3DNode(" ", this->birthrate, this->duration, this->durationVariation);// todo change model file
    node->isPlaying = this->isPlaying;
    node->hasLimit = this->hasLimit;
    node->maxAmount = this->maxAmount;
    node->currentAmount = this->currentAmount;
    node->emissionShape = this->emissionShape;
    node->innerSphereRadius = this->innerSphereRadius;
    node->outerSphereRadius = this->outerSphereRadius;
    node->boxSize = this->boxSize;
    node->colorKeys = this->colorKeys;
    node->progressKeys = this->progressKeys;
    node->spriteSheetAnimationInitialFrameRange = this->spriteSheetAnimationInitialFrameRange;
    node->spriteSheetAnimationFPS = this->spriteSheetAnimationFPS;
    node->spriteSheetAnimationFPSVariation = this->spriteSheetAnimationFPSVariation;
    node->renderingOrder = this->renderingOrder;
    node->useLocalSpace = this->useLocalSpace;
    node->isAdditive = this->isAdditive;
    node->youngestFirst = this->youngestFirst;
    node->speedFactor = this->speedFactor;
    node->spreadingAngle = this->spreadingAngle;
    node->initialSpeed = this->initialSpeed;
    node->initialSpeedVariation = this->initialSpeedVariation;
    node->speedAcceleration = this->speedAcceleration;
    node->speedAccelerationVariation = this->speedAccelerationVariation;
    node->acceleration = this->acceleration;
    node->accelerationVariation = this->accelerationVariation;
    node->initialRotation = this->initialRotation;
    node->initialRotationVariation = this->initialRotationVariation;
    node->rotatingSpeed = this->rotatingSpeed;
    node->rotatingSpeedVariation = this->rotatingSpeedVariation;
    node->randomizeRotatingDirection = this->randomizeRotatingDirection;
    node->initialScale = this->initialScale;
    node->initialScaleVariation = this->initialScaleVariation;
    node->scalingSpeed = this->scalingSpeed;
    node->scalingSpeedVariation = this->scalingSpeedVariation;
    node->texture = this->texture;
    node->color = this->color;
    node->name = this->name;
    node->isDisabled = this->isDisabled;
    node->position = this->position;
    node->eulerAngles = this->eulerAngles;
    node->scale = this->scale;
    node->orientationTargetNode = this->orientationTargetNode;
    for(unsigned int i = 0; i < this->animators.size(); i += 1) {
        node->animators.push_back(this->animators[i]->engineCopyAnimator());
    }
    for(unsigned int i = 0; i < this->geometries.size(); i += 1) {
        node->geometries.push_back(this->geometries[i]->copy(&node->animators));
    }
    for(unsigned int i = 0; i < this->childNodes.size(); i += 1) {
        Node* newNode = this->childNodes[i]->copy();
        node->addChildNode(newNode);
        map<string, Node*>::iterator iterator;
        for(iterator = this->boneNodes.begin(); iterator != this->boneNodes.end(); iterator++) {
            if(iterator->second == this->childNodes[i]) {
                node->boneNodes[iterator->first] = newNode;
                break;
            }
        }
    }
    return(node);
}
Node* Particle3DNode::clone() {
    return(this->copy());
}
void Particle3DNode::setUnlimitedAmount() {
    this->hasLimit = false;
}
void Particle3DNode::setMaxAmount(unsigned int amount) {
    this->hasLimit = true;
    this->maxAmount = amount;
}
void Particle3DNode::setEmissionSphere(float innerRadius, float outerRadius) {
    this->emissionShape = 0;
    this->innerSphereRadius = innerRadius;
    this->outerSphereRadius = outerRadius;
}
void Particle3DNode::setEmissionBox(vec3 size) {
    this->emissionShape = 1;
    this->boxSize = size;
}
void Particle3DNode::setColorAnimation(vec4 color, float progress) {
    for(unsigned int i = 0; i < this->colorKeys.size(); i += 1) {
        if(progress < this->progressKeys[i]) {
            this->colorKeys.insert(this->colorKeys.begin() + i, color);
            this->progressKeys.insert(this->progressKeys.begin() + i, progress);
            return;
        }
    }
    this->colorKeys.push_back(color);
    this->progressKeys.push_back(progress);
}
void Particle3DNode::setSpriteSheetAnimation(unsigned int rows, unsigned int columns,
                                           unsigned int initialFrameRange,
                                           unsigned int FPS, unsigned int FPSVariation) {
    this->spriteSheetAnimationInitialFrameRange = initialFrameRange;
    this->spriteSheetAnimationFPS = FPS;
    this->spriteSheetAnimationFPSVariation = FPSVariation;
    this->shader->engineSetSpriteSheetAnimation(rows, columns, initialFrameRange, FPS, FPSVariation);
}
void Particle3DNode::play() {
    this->isPlaying = true;
}
void Particle3DNode::stop() {
    this->isPlaying = false;
}
void Particle3DNode::reset() {
    this->currentAmount = 0;
    this->renderer->engineResetAllParticleData();
}
Particle3DNode::~Particle3DNode() {
    delete(this->renderer);
    delete(this->shader);
    this->renderer = NULL;
    this->shader = NULL;
    this->colorKeys.clear();
    this->progressKeys.clear();
}
void Particle3DNode::enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data, unsigned int renderingMode) {
    assert(this->spreadingAngle <= 90);
    if(this->isDisabled) {
        return;
    }
    this->Node::enginePrepareNodeForRendering(parentWorldTransform, data, renderingMode);
    if(renderingMode > 0) {
        return;
    }
    float currentTime = Engine::main->getTime();
    if(currentTime > this->productionTime) {
        this->productionTime = currentTime + this->productionTimeInterval;
        unsigned int currentAmount = (unsigned int)((this->productionAmount) * this->speedFactor);
        for(unsigned int counter = 0; counter < currentAmount; counter += 1) {
            if(!this->isPlaying) {
                break;
            }
            if(this->hasLimit && this->currentAmount >= this->maxAmount) {
                break;
            }
            Particle3DData* data = this->renderer->engineGetParticleData(this->youngestFirst);
            vec2 birthTimeAndDuration = data->birthTimeAndDuration;
            if(currentTime < birthTimeAndDuration.x + birthTimeAndDuration.y) {
                break;
            }
            float duration = this->particleDuration + glm::linearRand(-this->particleDurationVariation, this->particleDurationVariation);
            duration = duration / this->speedFactor;
            birthTimeAndDuration = vec2(currentTime, duration);
            data->birthTimeAndDuration = birthTimeAndDuration;
            vec3 initialPosition = vec3(0.0f);
            if(this->emissionShape == 0) {
                float radius = glm::linearRand(this->innerSphereRadius, this->outerSphereRadius);
                initialPosition = glm::sphericalRand(1.0f) * radius;
            }else if(this->emissionShape == 1) {
                initialPosition.x = glm::linearRand(-this->boxSize.x * 0.5f, this->boxSize.x * 0.5f);
                initialPosition.y = glm::linearRand(-this->boxSize.y * 0.5f, this->boxSize.y * 0.5f);
                initialPosition.z = glm::linearRand(-this->boxSize.z * 0.5f, this->boxSize.z * 0.5f);
            }
            if(!this->useLocalSpace) {
                initialPosition += this->getWorldPosition();
            }
            data->initialPosition = initialPosition;
            vec3 initialSpeed = vec3(0.0f);
            float polarAngle = glm::linearRand(0.0f, glm::radians(this->spreadingAngle));
            float alphaAngle = glm::linearRand(0.0f, glm::pi<float>() * 2.0f);
            initialSpeed.z = glm::sin(polarAngle) * glm::cos(alphaAngle);
            initialSpeed.y = glm::sin(polarAngle) * glm::sin(alphaAngle);
            initialSpeed.x = glm::cos(polarAngle);
            initialSpeed *= this->initialSpeed + glm::linearRand(-this->initialSpeedVariation, this->initialSpeedVariation);
            if(!this->useLocalSpace) {
                initialSpeed = this->convertLocalVectorToWorld(initialSpeed);
            }
            data->initialSpeed = initialSpeed;
            vec4 accelerationData = vec4(this->acceleration, 0.0f);
            accelerationData.x += glm::linearRand(-this->accelerationVariation.x, this->accelerationVariation.x);
            accelerationData.y += glm::linearRand(-this->accelerationVariation.y, this->accelerationVariation.y);
            accelerationData.z += glm::linearRand(-this->accelerationVariation.z, this->accelerationVariation.z);
            accelerationData.w = this->speedAcceleration;
            accelerationData.w += glm::linearRand(-this->speedAccelerationVariation, this->speedAccelerationVariation);
            data->accelerationData = accelerationData;
            vec3 rotationData = vec3(0, -(polarAngle) * glm::cos(alphaAngle), (polarAngle) * glm::sin(alphaAngle));
            vec3 rotationSpeedData = vec3(0.0f);
            rotationData += glm::radians(this->initialRotation);
            vec3 variationAngle = glm::radians(this->initialRotationVariation);
            rotationData += glm::linearRand(-variationAngle, variationAngle);
            rotationSpeedData = glm::radians(this->rotatingSpeed);
            if(this->randomizeRotatingDirection) {
                if(glm::linearRand(-1.0f, 1.0f) > 0.0f) {
                    rotationData.y = -rotationData.y;
                }
            }
            variationAngle = glm::radians(this->rotatingSpeedVariation);
            rotationData += glm::linearRand(-variationAngle, variationAngle);
            data->rotationData = rotationData;
            data->rotationSpeedData = rotationSpeedData;
            vec3 scaleData = vec3(1.0f);
            vec3 scaleSpeedData = vec3(0.0f);
            scaleData = this->initialScale;
            scaleData += glm::linearRand(-this->initialScaleVariation, this->initialScaleVariation);
            scaleSpeedData = this->scalingSpeed;
            scaleSpeedData += glm::linearRand(-this->scalingSpeedVariation, this->scalingSpeedVariation);
            vec2 spriteSheetAnimationData = vec2(0.0f);
            spriteSheetAnimationData.x = glm::floor(glm::linearRand(0.0f, (float)this->spriteSheetAnimationInitialFrameRange));
            spriteSheetAnimationData.y = (float)this->spriteSheetAnimationFPS;
            spriteSheetAnimationData.y += glm::linearRand(-(float)this->spriteSheetAnimationFPSVariation, (float)this->spriteSheetAnimationFPSVariation);
            data->spriteSheetAnimationData = spriteSheetAnimationData;
            data->scaleData = scaleData;
            data->scaleSpeedData = scaleSpeedData;
            if(this->hasLimit) {
                this->currentAmount += 1;
            }
        }
    }
    this->renderer->renderingOrder = this->renderingOrder;
    this->shader->engineSetParticleShaderColorAnimation(this->colorKeys, this->progressKeys);
    this->renderer->enginePrepareGeometryForRendering(this->worldTransform);
}
