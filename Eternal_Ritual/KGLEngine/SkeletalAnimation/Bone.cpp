// Developed by Kelin Lyu.
#include "KGLEngine/SkeletalAnimation/Bone.hpp"

#include "KGLEngine/Toolkit/assimp_helper.h"

using namespace std;
using namespace glm;


Bone::Bone(string name, aiNodeAnim* channel) {
    this->name = name;
    this->position = vec3(0.0f);
    this->rotation = quat(0.0f, 0.0f, 0.0f, 0.0f);
    this->scale = vec3(0.0f);
    this->currentKeyPositionIndex = 0;
    this->currentKeyRotationIndex = 0;
    this->currentKeyScaleIndex = 0;
    for(unsigned int i = 0; i < channel->mNumPositionKeys; i += 1) {
        aiVector3D aiPosition = channel->mPositionKeys[i].mValue;
        float timestamp = channel->mPositionKeys[i].mTime;
        BoneKeyFramePosition data;
        data.position = assimp_helper::getVec3(aiPosition);
        data.timestamp = timestamp;
        this->keyPositions.push_back(data);
    }
    for(unsigned int i = 0; i < channel->mNumRotationKeys; i += 1) {
        aiQuaternion aiOrientation = channel->mRotationKeys[i].mValue;
        float timestamp = channel->mRotationKeys[i].mTime;
        BoneKeyFrameRotation data;
        data.orientation = assimp_helper::getQuat(aiOrientation);
        data.timestamp = timestamp;
        this->keyRotations.push_back(data);
    }
    for(unsigned int i = 0; i < channel->mNumScalingKeys; i += 1) {
        aiVector3D scale = channel->mScalingKeys[i].mValue;
        float timestamp = channel->mScalingKeys[i].mTime;
        BoneKeyFrameScale data;
        data.scale = assimp_helper::getVec3(scale);
        data.timestamp = timestamp;
        this->keyScales.push_back(data);
    }
}
Bone::~Bone() {
    this->keyPositions.clear();
    this->keyRotations.clear();
    this->keyScales.clear();
}
string Bone::engineGetName() const {
    return(this->name);
}
vec3 Bone::engineGetBonePosition() {
    return(this->position);
}
quat Bone::engineGetBoneRotation() {
    return(this->rotation);
}
vec3 Bone::engineGetBoneScale() {
    return(this->scale);
}
void Bone::engineUpdateBoneAnimation(float animationTime) {
    if(this->keyPositions.size() == 1) {
        this->position = this->keyPositions[0].position;
    }else{
        int index = this->currentKeyPositionIndex;
        if(animationTime < this->keyPositions[index].timestamp) {
            index = 0;
        }
        for(unsigned int i = index; i < this->keyPositions.size() - 1; i += 1) {
            if(animationTime < this->keyPositions[i + 1].timestamp) {
                index = i;
                this->currentKeyPositionIndex = index;
                break;
            }
        }
        float base = this->keyPositions[index + 1].timestamp - this->keyPositions[index].timestamp;
        float factor = (animationTime - this->keyPositions[index].timestamp) / base;
        this->position = glm::mix(this->keyPositions[index].position, this->keyPositions[index + 1].position, factor);
    }
    if(this->keyRotations.size() == 1) {
        this->rotation = glm::normalize(this->keyRotations[0].orientation);
    }else{
        int index = this->currentKeyRotationIndex;
        if(animationTime < this->keyRotations[index].timestamp) {
            index = 0;
        }
        for(unsigned int i = index; i < this->keyRotations.size() - 1; i += 1) {
            if(animationTime < this->keyRotations[i + 1].timestamp) {
                index = i;
                this->currentKeyRotationIndex = index;
                break;
            }
        }
        float base = this->keyRotations[index + 1].timestamp - this->keyRotations[index].timestamp;
        float factor = (animationTime - this->keyRotations[index].timestamp) / base;
        quat rotation = glm::slerp(keyRotations[index].orientation, keyRotations[index + 1].orientation, factor);
        this->rotation = glm::normalize(rotation);
    }
    if(this->keyScales.size() == 1) {
        this->scale = this->keyScales[0].scale;
    }else{
        int index = this->currentKeyScaleIndex;
        if(animationTime < this->keyScales[index].timestamp) {
            index = 0;
        }
        for(unsigned int i = index; i < this->keyScales.size() - 1; i += 1) {
            if(animationTime < this->keyScales[i + 1].timestamp) {
                index = i;
                this->currentKeyScaleIndex = index;
                break;
            }
        }
        float base = this->keyScales[index + 1].timestamp - this->keyScales[index].timestamp;
        float factor = (animationTime - this->keyScales[index].timestamp) / base;
        this->scale = glm::mix(this->keyScales[index].scale, this->keyScales[index + 1].scale, factor);
    }
}
