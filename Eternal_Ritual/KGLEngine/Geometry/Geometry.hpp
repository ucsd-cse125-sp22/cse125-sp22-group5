// Developed by Kelin Lyu.
#ifndef Geometry_hpp
#define Geometry_hpp

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "KGLEngine/SkeletalAnimation/Bone.hpp"
#include "KGLEngine/SkeletalAnimation/Animator.hpp"
#include "KGLEngine/Shading/Texture.hpp"
#include "KGLEngine/Shading/Shader.hpp"

class LightNode;


#define MAX_BONE_INFLUENCE 4
#define BONES_LIMIT 120
struct GeometryVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    int boneIDs[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];
};
struct ParticleData {
    glm::vec2 birthTimeAndDuration;
    glm::vec3 initialPosition;
    glm::vec3 initialSpeed;
    glm::vec4 accelerationData;
    glm::vec2 rotationData;
    glm::vec2 scaleData;
    glm::vec2 spriteSheetAnimationData;
};
struct Particle3DData {
    glm::vec2 birthTimeAndDuration;
    glm::vec3 initialPosition;
    glm::vec3 initialSpeed;
    glm::vec4 accelerationData;
    glm::vec3 rotationData;
    glm::vec3 rotationSpeedData;
    glm::vec3 scaleData;
    glm::vec3 scaleSpeedData;
    glm::vec2 spriteSheetAnimationData;
};
struct Particle3DVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};
class Geometry {
protected:
    bool updated;
    bool prepared;
    unsigned int cullMode;
    Shader* shader;
    unsigned int vertexArrays;
    unsigned int vertexBuffers;
    unsigned int elementBuffers;
    unsigned int indiceCount;
    unsigned int boneCount;
    std::vector<std::string> boneNames;
    std::vector<BoneInfo> boneInfos;
    std::vector<glm::mat4> boneTransforms;
    bool skeletalAnimationUpdated;
    glm::mat4 modelTransform;
    unsigned int modelTransformBuffers;
    unsigned int normalTransformBuffers;
    unsigned int instanceCount;
    std::vector<bool> frozenTransforms;
    std::vector<glm::mat4> modelTransforms;
    std::vector<glm::mat4> normalTransforms;
    bool requiresInstanceUpdate;
    bool hasBoundingSphereInformation;
public:
    bool isHidden;
    float renderingOrder;
    unsigned int renderingBitMask;
    unsigned int lightingBitMask;
    glm::vec3 boundingSpherePosition;
    float boundingSphereRadius;
    unsigned int affectedLightCount;
    Geometry() = default;
    Geometry(aiMesh* mesh);
    Geometry* copy(std::vector<Animator*>* animators);
    void cullBack();
    void cullFront();
    void setDoubleSided();
    void setShader(Shader* shader);
    virtual ~Geometry();
    void engineInitializeGeometry();
    glm::mat4 engineGetGeometryModelTransform();
    unsigned int engineGetGeometryVertexArrays();
    unsigned int engineGetGeometryIndiceCount();
    bool engineCheckWhetherGeometryHasBones();
    std::vector<glm::mat4>* engineGetGeometryBoneTransforms();
    glm::mat4 engineGetGeometryBoneTransform(std::string name);
    void engineUpdateGeometryBoneIndices(std::vector<std::string>* boneNames);
    void engineUpdateGeometrySkeletalAnimations(std::vector<glm::mat4> boneTransforms);
    bool engineCheckWhetherGeometryHasUpdatedSkeletalAnimations();
    void enginePrepareGeometryForRendering(glm::mat4 worldTransform);
    virtual void engineRenderGeometry(unsigned int renderingMode);
    unsigned int engineGeometryAddInstance();
    void engineUpdateGeometryInstanceTransform(unsigned int index, glm::mat4 modelTransform, bool freeze);
    virtual unsigned int engineGetGeometryInstanceCount();
    bool engineCheckWhetherGeometryIsAffectedByLightNode(LightNode* lightNode);
};
class UnitCube final: public Geometry {
public:
    UnitCube();
    ~UnitCube() override = default;
};
class ParticleRenderer final: public Geometry {
private:
    unsigned int particleAmount;
    unsigned int dataBuffers;
    std::vector<ParticleData> dataVector;
public:
    ParticleRenderer(unsigned int amount);
    ~ParticleRenderer() override;
    void engineResetAllParticleData();
    void engineRenderGeometry(unsigned int renderingMode) override;
    ParticleData* engineGetParticleData(bool front);
    unsigned int engineGetGeometryInstanceCount() override;
};
class Particle3DRenderer final: public Geometry {
private:
    unsigned int particleAmount;
    unsigned int dataBuffers;
    std::vector<Particle3DData> dataVector;
public:
    Particle3DRenderer() = default;
    Particle3DRenderer(unsigned int amount, aiMesh* mesh);
    Particle3DRenderer* copy();
    ~Particle3DRenderer() override;
    void engineResetAllParticleData();
    void engineRenderGeometry(unsigned int renderingMode) override;
    Particle3DData* engineGetParticleData(bool front);
    unsigned int engineGetGeometryInstanceCount() override;
};
class Skybox final: public Geometry {
private:
    Texture* texture;
public:
    Skybox(std::string right, std::string left,
           std::string top, std::string bottom,
           std::string front, std::string back,
           float maxAnisotropy);
    ~Skybox() override;
    void engineRenderGeometry(unsigned int renderingMode) override;
};
class Sprite final: public Geometry {
public:
    Sprite();
    ~Sprite() override = default;
};
class TextRenderer final: public Geometry {
private:
    std::vector<Texture*> textures;
    std::vector<glm::mat4> transforms;
    glm::mat4 mainTransform;
public:
    TextRenderer();
    ~TextRenderer() override;
    void engineRenderGeometry(unsigned int renderingMode) override;
    void engineSetTextRendererAlpha(float alpha);
    void engineSetTextRendererColor(glm::vec4 color);
    void engineSetTextRendererTexturesAndTransforms(std::vector<Texture*> textures, std::vector<glm::mat4> transforms);
    void engineClearTextRendererTexturesAndTransforms();
    void engineSetTextRendererMainTransform(glm::mat4 mainTransform);
};
#endif
