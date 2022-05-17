// Developed by Kelin Lyu.
#ifndef Animator_hpp
#define Animator_hpp

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <assimp/scene.h>

#include "KGLEngine/SkeletalAnimation/Bone.hpp"


struct AnimationBoneNode final {
    std::string name;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    int index;
    std::vector<AnimationBoneNode*> children;
};

class Animator final {
private:
    unsigned int state;
    std::string name;
    float time;
    float duration;
    float baseSpeed;
    float fadeIn;
    float fadeOut;
    float currentBlendFactor;
    float startTime;
    float stateChangeTime;
    float stateChangeBlendFactor;
    AnimationBoneNode* rootAnimationBoneNode;
    std::vector<AnimationBoneNode*> animationBoneNodes;
    std::map<std::string, Bone*> bones;
public:
    unsigned int animatorBitMask;
    bool repeats;
    bool clamps;
    float timeOffset;
    float speed;
    float blendFactor;
    Animator() = default;
    Animator(std::string name, std::string file, std::vector<std::string>* boneNames, std::vector<glm::mat4>* boneTransforms);
    void reset();
    void play(float fadeIn, float fadeOut = 0.0f);
    void stop(float fadeOut);
    bool isPlaying();
    float getTime();
    float getDuration();
    float getCurrentBlendFactor();
    ~Animator();
    std::string engineGetAnimatorName();
    float engineGetAnimatorTime();
    float engineGetAnimatorCurrentBlendFactor();
    float engineGetAnimatorFadeInFactor(float progress);
    float engineGetAnimatorFadeOutFactor(float progress);
    void engineUpdateAnimator();
    Animator* engineCopyAnimator();
    AnimationBoneNode* engineCopyAnimationBoneNode(AnimationBoneNode* targetNode);
    void engineAnimatorProcessNode(AnimationBoneNode* targetNode, aiNode* node);
    void engineUpdateAnimatorBoneIndices(std::vector<std::string>* boneNames);
    AnimationBoneNode* engineAnimatorGetRootAnimationBoneNode();
    Bone* engineAnimatorGetBone(std::string name);
};
#endif
