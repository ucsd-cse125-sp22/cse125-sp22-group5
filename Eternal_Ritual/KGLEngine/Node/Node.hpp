// Developed by Kelin Lyu.
#ifndef Node_hpp
#define Node_hpp

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <SFML/Audio.hpp>
#include <assimp/scene.h>

#include "KGLEngine/System/Font.hpp"
#include "KGLEngine/System/AudioBuffer.hpp"
#include "KGLEngine/SkeletalAnimation/Animator.hpp"
#include "KGLEngine/System/Animation.hpp"
#include "KGLEngine/Shading/Shader.hpp"
#include "KGLEngine/Geometry/Geometry.hpp"

class CameraNode;
class LightNode;
class ParticleNode;
class Particle3DNode;
class UINode;
class SpriteNode;
class TextNode;


#define LIGHTS_LIMIT 30
#define SHADOWS_LIMIT 6
class Node {
protected:
    static unsigned int UID;
    unsigned int ID;
    glm::mat4 worldTransform;
    std::map<std::string, Node*> boneNodes;
    std::vector<Animator*> animators;
    int geometryInstancingIndex;
    std::map<Geometry*, std::vector<unsigned int>> frozenNodeGeometryInstancingIndices;
    bool hasUnfreezableGeometries;
    CameraNode* currentCameraNode;
    LightNode* currentLightNode;
    ParticleNode* currentParticleNode;
    Particle3DNode* currentParticle3DNode;
    UINode* currentUINode;
    SpriteNode* currentSpriteNode;
    TextNode* currentTextNode;
    std::vector<std::string> boneNames;
    std::vector<glm::mat4> boneTransforms;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, float> volumes;
public:
    std::string name;
    Node* parent;
    std::vector<Node*> childNodes;
    bool isDisabled;
    glm::vec3 position;
    glm::vec3 eulerAngles;
    glm::vec3 scale;
    Node* orientationTargetNode;
    std::vector<Geometry*> geometries;
    Node();
    void addChildNode(Node* node);
    void removeFromParentNode();
    void loadUnitCube();
    void loadModelFile(std::string file);
    Animator* loadAnimator(std::string name, std::string file);
    void loadAudioBuffer(std::string name, AudioBuffer* buffer, float minDistance = 1.0f, float attenuation = 1.0f);
    Node* generateBoneNode(std::string boneName);
    virtual Node* copy();
    virtual Node* clone();
    void freeze();
    Animator* getAnimator(std::string name);
    void playAnimators(unsigned int mask, float fadeIn, float fadeOut = 0.0f);
    void stopAnimators(unsigned int mask, float fadeOut);
    void updateTransform();
    Node* getChildNode(std::string name);
    glm::mat4 getWorldTransform();
    glm::vec3 getWorldPosition();
    glm::vec3 getWorldEulerAngles();
    glm::vec3 getWorldScale();
    glm::vec3 convertLocalPositionToWorld(glm::vec3 localPosition);
    glm::vec3 convertLocalVectorToWorld(glm::vec3 localVector);
    glm::vec3 getFrontVectorInWorld();
    glm::vec3 getBackVectorInWorld();
    glm::vec3 getLeftVectorInWorld();
    glm::vec3 getRightVectorInWorld();
    glm::vec3 getUpVectorInWorld();
    glm::vec3 getDownVectorInWorld();
    glm::vec3 getPositionOnScreen();
    CameraNode* convertToCameraNode();
    LightNode* convertToLightNode();
    ParticleNode* convertToParticleNode();
    Particle3DNode* convertToParticle3DNode();
    UINode* convertToUINode();
    SpriteNode* convertToSpriteNode();
    TextNode* convertToTextNode();
    void playAudio(std::string name);
    void pauseAudio(std::string name);
    void stopAudio(std::string name);
    float getAudioTime(std::string name);
    void changeAudioVolume(std::string name, float volume, float duration);
    ~Node();
    void engineInitializeNode();
    void engineProcessNode(aiNode* node, const aiScene* scene);
    void engineUpdateNodeAnimators(glm::mat4 parentWorldTransform);
    void engineNodeCalculateBoneTransforms(AnimationBoneNode *node, glm::mat4 parentTransform);
    virtual void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode);
    virtual void engineCalculateNodeWorldTransform(glm::mat4 parentWorldTransform);
    void engineRecursivelyFreezeChildNodes(std::vector<Geometry*>* allGeometries, std::map<Geometry*, std::vector<unsigned int>>* indices);
};
class CameraNode final: public Node{
public:
    float width;
    float height;
    float field;
    float near;
    float far;
    unsigned int renderingBitMask;
    CameraNode(float field, float near, float far);
    CameraNode(float width, float height, float near, float far);
    Node* copy() override;
    Node* clone() override;
    glm::mat4 getDirectionalLightSpaceMatrix();
    glm::mat4 getOrthogonalProjectionTransform();
    glm::mat4 getProjectionTransform();
    glm::mat4 getViewTransform();
    ~CameraNode() = default;
};
class LightNode final: public Node {
private:
    unsigned int lightType;
    float cameraNodeDistance;
    bool hasDirectionalLightShadow;
    CameraNode* directionalLightCameraNode;
    unsigned int shadowMapSize;
    unsigned int shadowBuffer;
    Texture* shadowMap;
    float shadowBias;
    int shadowSamples;
    int shadowIndex;
public:
    glm::vec3 colorFactor;
    float highlightIntensity;
    float attenuationExponent;
    float range;
    float penetrationRange;
    float innerAngle;
    float outerAngle;
    unsigned int lightingBitMask;
    unsigned int shadowBitMask;
    LightNode(glm::vec3 color);
    Node* copy() override;
    Node* clone() override;
    void setAmbientLight();
    void setDirectionalLight();
    void setPointLight(float attenuationExponent, float range);
    void setSpotLight(float attenuationExponent, float range, float innerAngle, float outerAngle);
    void activateDirectionalLightShadow(unsigned int mapSize, float projectionSize, float near, float far, float xOffset, float bias, int samples);
    ~LightNode() = default;
    void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode) override;
    void enginePrepareLightShadowForRendering();
    unsigned int engineGetLightType();
    CameraNode* engineGetDirectionalLightCameraNode();
    unsigned int engineLightNodeGetShadowMapSize();
    unsigned int engineLightNodeGetShadowBuffer();
    void engineConfigurateLightForShader(Shader* shader, int index);
    void engineConfigurateShadowForShader(Shader* shader, int index);
};
class ParticleNode final: public Node {
private:
    bool isPlaying;
    bool hasLimit;
    unsigned int maxAmount;
    unsigned int currentAmount;
    unsigned int birthrate;
    float duration;
    float durationVariation;
    ParticleRenderer* renderer;
    ParticleShader* shader;
    unsigned int productionAmount;
    float productionTime;
    float productionTimeInterval;
    float particleDuration;
    float particleDurationVariation;
    unsigned int emissionShape;
    float innerSphereRadius;
    float outerSphereRadius;
    glm::vec3 boxSize;
    std::vector<glm::vec4> colorKeys;
    std::vector<float> progressKeys;
    unsigned int spriteSheetAnimationInitialFrameRange;
    unsigned int spriteSheetAnimationFPS;
    unsigned int spriteSheetAnimationFPSVariation;
public:
    float renderingOrder;
    bool useLocalSpace;
    bool isAdditive;
    bool youngestFirst;
    float speedFactor;
    float spreadingAngle;
    float initialSpeed;
    float initialSpeedVariation;
    float speedAcceleration;
    float speedAccelerationVariation;
    glm::vec3 acceleration;
    glm::vec3 accelerationVariation;
    float initialRotation;
    float initialRotationVariation;
    float rotatingSpeed;
    float rotatingSpeedVariation;
    bool randomizeRotatingDirection;
    float initialScale;
    float initialScaleVariation;
    float scalingSpeed;
    float scalingSpeedVariation;
    Texture* texture;
    glm::vec4 color;
    ParticleNode(unsigned int birthrate, float duration, float durationVariation);
    Node* copy() override;
    Node* clone() override;
    void setUnlimitedAmount();
    void setMaxAmount(unsigned int amount);
    void setEmissionSphere(float innerRadius, float outerRadius);
    void setEmissionBox(glm::vec3 size);
    void setColorAnimation(glm::vec4 color, float progress);
    void setSpriteSheetAnimation(unsigned int rows, unsigned int columns,
                                 unsigned int initialFrameRange,
                                 unsigned int FPS, unsigned int FPSVariation);
    void play();
    void stop();
    void reset();
    ~ParticleNode();
    void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode) override;
};
class UINode: public Node {
private:
    glm::mat4 renderingTransform;
public:
    glm::vec2 screenPosition;
    glm::vec2 position;
    glm::vec2 parentCoordinatePosition;
    float rotation;
    glm::vec2 scale;
    glm::vec2 size;
    float alpha;
    float renderingOrder;
    UINode();
    Node* copy() override;
    Node* clone() override;
    void loadSprite(Sprite* sprite);
    glm::vec2 convertScreenPositionToLocal(glm::vec2 screenPosition);
    bool checkSizeIncludesScreenPosition(glm::vec2 screenPosition);
    ~UINode() = default;
    void engineInitializeUINode();
    void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode) override;
    void engineCalculateNodeWorldTransform(glm::mat4 parentWorldTransform) override;
};
class SpriteNode: public UINode {
private:
    SpriteShader* spriteShader;
public:
    glm::vec4 color;
    Texture* texture;
    glm::vec3 multiplyColor;
    Texture* multiplyTexture;
    float multiplyIntensity;
    glm::vec3 emissionColor;
    Texture* emissionTexture;
    float emissionIntensity;
    SpriteNode(glm::vec2 size);
    Node* copy() override;
    Node* clone() override;
    void setSemitransparent();
    void setAdditive();
    ~SpriteNode();
    void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode) override;
    void engineCalculateNodeWorldTransform(glm::mat4 parentWorldTransform) override;
};
class TextNode final: public UINode {
private:
    Font* font;
    float lineHeight;
    float lineLength;
    float lineDistance;
    int alignmentX;
    int alignmentY;
    float currentAlpha;
    glm::vec4 currentColor;
    std::string currentText;
    TextRenderer* textRenderer;
public:
    glm::vec4 color;
    std::string text;
    TextNode(Font* font, float lineHeight, float lineLength, float lineDistance);
    Node* copy() override;
    Node* clone() override;
    void setLeftHorizontalAlignment();
    void setCenterHorizontalAlignment();
    void setRightHorizontalAlignment();
    void setTopVerticalAlignment();
    void setCenterVerticalAlignment();
    void setBottomVerticalAlignment();
    ~TextNode();
    void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode) override;
    void engineCalculateNodeWorldTransform(glm::mat4 parentWorldTransform) override;
};
class Particle3DNode final: public Node {
private:
    bool isPlaying;
    bool hasLimit;
    unsigned int maxAmount;
    unsigned int currentAmount;
    unsigned int birthrate;
    float duration;
    float durationVariation;
    Particle3DRenderer* renderer;
    Particle3DShader* shader;
    unsigned int productionAmount;
    float productionTime;
    float productionTimeInterval;
    float particleDuration;
    float particleDurationVariation;
    unsigned int emissionShape;
    float innerSphereRadius;
    float outerSphereRadius;
    glm::vec3 boxSize;
    std::vector<glm::vec4> colorKeys;
    std::vector<float> progressKeys;
    unsigned int spriteSheetAnimationInitialFrameRange;
    unsigned int spriteSheetAnimationFPS;
    unsigned int spriteSheetAnimationFPSVariation;
public:
    aiMesh* mesh;
    float renderingOrder;
    bool useLocalSpace;
    bool isAdditive;
    bool youngestFirst;
    bool useEmissionColor;
    float emissionAlpha;
    float speedFactor;
    float spreadingAngle;
    float initialSpeed;
    float initialSpeedVariation;
    float speedAcceleration;
    float speedAccelerationVariation;
    glm::vec3 acceleration;
    glm::vec3 accelerationVariation;
    glm::vec3 initialRotation;
    glm::vec3 initialRotationVariation;
    glm::vec3 rotatingSpeed;
    glm::vec3 rotatingSpeedVariation;
    bool randomizeRotatingDirection;
    glm::vec3 initialScale;
    glm::vec3 initialScaleVariation;
    glm::vec3 scalingSpeed;
    glm::vec3 scalingSpeedVariation;
    Texture* texture;
    glm::vec4 color;
    Particle3DNode(unsigned int birthrate, float duration, float durationVariation);
    void loadModelFile(std::string file);
    void engineProcessNode2(aiNode *node, const aiScene *scene);
    Node* copy() override;
    Node* clone() override;
    void setUnlimitedAmount();
    void setMaxAmount(unsigned int amount);
    void setEmissionSphere(float innerRadius, float outerRadius);
    void setEmissionBox(glm::vec3 size);
    void setColorAnimation(glm::vec4 color, float progress);
    void setSpriteSheetAnimation(unsigned int rows, unsigned int columns,
                                 unsigned int initialFrameRange,
                                 unsigned int FPS, unsigned int FPSVariation);
    void play();
    void stop();
    void reset();
    ~Particle3DNode();
    void enginePrepareNodeForRendering(glm::mat4 parentWorldTransform, glm::vec2 data, unsigned int renderingMode) override;
};
#endif
