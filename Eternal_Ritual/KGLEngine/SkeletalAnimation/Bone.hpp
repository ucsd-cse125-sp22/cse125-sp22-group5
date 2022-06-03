// Developed by Kelin Lyu.
#ifndef Bone_hpp
#define Bone_hpp

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <assimp/scene.h>


struct BoneInfo final {
    unsigned int id;
    glm::mat4 offset;
    int index;
};
struct BoneKeyFramePosition final {
    glm::vec3 position;
    float timestamp;
};
struct BoneKeyFrameRotation final {
    glm::quat orientation;
    float timestamp;
};
struct BoneKeyFrameScale final {
    glm::vec3 scale;
    float timestamp;
};
class Bone final {
public:
    std::string name;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    unsigned int currentKeyPositionIndex;
    unsigned int currentKeyRotationIndex;
    unsigned int currentKeyScaleIndex;
    std::vector<BoneKeyFramePosition> keyPositions;
    std::vector<BoneKeyFrameRotation> keyRotations;
    std::vector<BoneKeyFrameScale> keyScales;
public:
    Bone() = default;
    Bone(std::string name, aiNodeAnim* channel);
    ~Bone();
    std::string engineGetName() const;
    glm::vec3 engineGetBonePosition();
    glm::quat engineGetBoneRotation();
    glm::vec3 engineGetBoneScale();
    void engineUpdateBoneAnimation(float animationTime);
};
#endif
