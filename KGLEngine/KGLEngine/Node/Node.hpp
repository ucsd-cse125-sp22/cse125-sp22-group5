// Developed by Kelin Lyu.
#ifndef Node_hpp
#define Node_hpp
#include "../Engine.hpp"
#define LIGHTS_LIMIT 10
struct FontCharacter;
class SpriteShader;
class ParticleShader;
class Geometry;
class ParticleRenderer;
class Sprite;
class TextRenderer;
class Animator;
class LightNode;
class UINode;
class Font;
class Node {
protected:
    mat4 worldTransform;
    map<string, Node*> boneNodes;
    vector<Animator*> animators;
    int geometryInstancingIndex;
    map<Geometry*, vector<unsigned int>> frozenNodeGeometryInstancingIndices;
public:
    string name;
    unsigned int tags;
    Node* parent;
    vector<Node*> childNodes;
    bool isDisabled;
    vec3 position;
    vec3 eulerAngles;
    vec3 scale;
    Node* orientationTargetNode;
    vector<Geometry*> geometries;
    Node();
    void addChildNode(Node* node);
    void removeFromParentNode();
    void loadUnitCube();
    void loadModelFile(string file);
    void loadAnimator(string name, string file);
    Node* generateBoneNode(string boneName);
    Node* copy();
    Node* clone();
    void freeze();
    Animator* getAnimator(string name);
    void updateTransform();
    mat4 getWorldTransform();
    vec3 getWorldPosition();
    vec3 getWorldEulerAngles();
    vec3 getWorldScale();
    vec3 convertLocalPositionToWorld(vec3 localPosition);
    vec3 convertLocalVectorToWorld(vec3 localVector);
    vec3 getFrontVectorInWorld();
    vec3 getBackVectorInWorld();
    vec3 getLeftVectorInWorld();
    vec3 getRightVectorInWorld();
    vec3 getUpVectorInWorld();
    vec3 getDownVectorInWorld();
    vec3 getPositionOnScreen();
    ~Node();
    void engineInitializeNode();
    void engineProcessNode(aiNode* node, const aiScene* scene);
    void engineUpdateNodeAnimators(mat4 parentWorldTransform);
    virtual void enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data);
    virtual void engineCalculateNodeWorldTransform(mat4 parentWorldTransform);
    void engineRecursivelyFreezeChildNodes(vector<Geometry*>* allGeometries, map<Geometry*, vector<unsigned int>>* indices);
};
class CameraNode final: public Node{
public:
    float field;
    float near;
    float far;
    CameraNode(float field, float near, float far);
    mat4 getOrthogonalProjectionTransform();
    mat4 getProjectionTransform();
    mat4 getViewTransform();
    ~CameraNode() = default;
};
class LightNode final: public Node {
private:
    unsigned int lightType;
    float cameraNodeDistance;
public:
    vec3 colorFactor;
    float highlightIntensity;
    float attenuationExponent;
    float range;
    float innerAngle;
    float outerAngle;
    unsigned int lightMask;
    LightNode(vec3 color);
    void setAmbientLight();
    void setDirectionalLight();
    void setPointLight(float attenuationExponent, float range);
    void setSpotLight(float attenuationExponent, float range, float innerAngle, float outerAngle);
    ~LightNode() = default;
    void enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data) override;
    void engineConfigurateShader(Shader* shader, int index);
};
class ParticleNode final: public Node {
private:
    bool isPlaying;
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
    vec3 boxSize;
    vector<vec4> colorKeys;
    vector<float> progressKeys;
    unsigned int spriteSheetAnimationInitialFrameRange;
    unsigned int spriteSheetAnimationFPS;
    unsigned int spriteSheetAnimationFPSVariation;
public:
    float renderingOrder;
    bool useLocalSpace;
    bool isAdditive;
    bool youngestFirst;
    float spreadingAngle;
    float initialSpeed;
    float initialSpeedVariation;
    float speedAcceleration;
    float speedAccelerationVariation;
    vec3 acceleration;
    vec3 accelerationVariation;
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
    vec4 color;
    ParticleNode(unsigned int birthrate, float duration, float durationVariation);
    void setEmissionSphere(float innerRadius, float outerRadius);
    void setEmissionBox(vec3 size);
    void setColorAnimation(vec4 color, float progress);
    void setSpriteSheetAnimation(unsigned int rows, unsigned int columns,
                                 unsigned int initialFrameRange,
                                 unsigned int FPS, unsigned int FPSVariation);
    void play();
    void stop();
    void reset();
    ~ParticleNode();
    void enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data) override;
};
class UINode: public Node {
private:
    mat4 renderingTransform;
public:
    vec2 screenPosition;
    vec2 position;
    float rotation;
    vec2 scale;
    vec2 size;
    float alpha;
    float renderingOrder;
    UINode();
    void loadSprite(Sprite* sprite);
    ~UINode() = default;
    void engineInitializeUINode();
    void enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data) override;
    void engineCalculateNodeWorldTransform(mat4 parentWorldTransform) override;
};
class SpriteNode: public UINode {
private:
    SpriteShader* spriteShader;
public:
    vec4 color;
    Texture* texture;
    vec3 multiplyColor;
    Texture* multiplyTexture;
    float multiplyIntensity;
    vec3 emissionColor;
    Texture* emissionTexture;
    float emissionIntensity;
    SpriteNode(vec2 size);
    void setSemitransparent();
    void setAdditive();
    ~SpriteNode();
    void enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data) override;
    void engineCalculateNodeWorldTransform(mat4 parentWorldTransform) override;
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
    vec4 currentColor;
    string currentText;
    TextRenderer* textRenderer;
public:
    vec4 color;
    string text;
    void setHorizontalAlignmentToLeft();
    void setHorizontalAlignmentToCenter();
    void setHorizontalAlignmentToRight();
    void setVerticalAlignmentToTop();
    void setVerticalAlignmentToCenter();
    void setVerticalAlignmentToBottom();
    TextNode(Font* font, float lineHeight, float lineLength, float lineDistance);
    ~TextNode();
    void enginePrepareNodeForRendering(mat4 parentWorldTransform, vec2 data) override;
    void engineCalculateNodeWorldTransform(mat4 parentWorldTransform) override;
};
#endif