// Developed by Kelin Lyu.
#ifndef Shader_hpp
#define Shader_hpp

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "KGLEngine/Shading/Texture.hpp"

class Geometry;
class ParticleNode;
class Particle3DNode;


class Shader {
protected:
    static int currentProgramID;
    static int currentBlendMode;
    static int currentWriteToDepthBuffer;
    static int currentDepthFunction;
    unsigned int programID;
    unsigned int blendMode;
    std::string vertexShaderSourceCode;
    std::string fragmentShaderSourceCode;
    std::vector<Texture*> textures;
    std::vector<std::string> uniformTextureNames;
    glm::mat4 currentModelTransform;
    bool isUIShader;
    bool isParticleShader;
public:
    bool writeToDepthBuffer;
    bool clearDepthBuffer;
    Shader();
    Shader(std::string shaderFile);
    Shader(std::string vertexShaderCode, std::string fragmentShaderCode);
    Shader* copy();
    void activateShader();
    void setUIShader();
    void setOpaque();
    void setAdditive();
    void setSemitransparent();
    void setBool(std::string name, bool value);
    void setInt(std::string name, int value);
    void setFloat(std::string name, float value);
    void setVec2(std::string name, glm::vec2 value);
    void setVec3(std::string name, glm::vec3 value);
    void setVec4(std::string name, glm::vec4 value);
    void setMat2(std::string name, glm::mat2 mat);
    void setMat3(std::string name, glm::mat3 mat);
    void setMat4(std::string name, glm::mat4 mat);
    void setTexture(std::string name, Texture* texture);
    virtual ~Shader();
    void engineInitializeShader(std::string vertexShaderCode, std::string fragmentShaderCode);
    bool engineCheckCompileErrors(unsigned int shader, std::string type);
    virtual void engineRenderShader(Geometry* geometry, unsigned int renderingMode);
};
class PBRShader final: public Shader {
private:
    float currentOpacity;
    glm::vec4 currentDiffuseColor;
    float currentDiffuseIntensity;
    float currentAlphaCutThreshold;
    float currentNormalIntensity;
    float currentHeightIntensity;
    glm::vec2 currentHeightLayerRange;
    float currentMetallic;
    float currentMetallicIntensity;
    int currentinvertMetallic;
    float currentRoughness;
    float currentRoughnessIntensity;
    int currentinvertRoughness;
    float currentReflectionIntensity;
    float currentAmbientOcclusionIntensity;
    glm::vec3 currentMultiplyColor;
    float currentMultiplyIntensity;
    glm::vec3 currentEmissionColor;
    float currentEmissionIntensity;
public:
    float opacity;
    glm::vec4 diffuseColor;
    float diffuseIntensity;
    float alphaCutThreshold;
    float normalIntensity;
    float heightIntensity;
    glm::vec2 heightLayerRange;
    float metallic;
    float metallicIntensity;
    bool invertMetallic;
    float roughness;
    float roughnessIntensity;
    bool invertRoughness;
    float reflectionIntensity;
    float ambientOcclusionIntensity;
    glm::vec3 multiplyColor;
    float multiplyIntensity;
    glm::vec3 emissionColor;
    float emissionIntensity;
    PBRShader(float metallic, float roughness);
    PBRShader(std::string shaderFile, float metallic, float roughness);
    PBRShader* copy();
    void setDiffuseMap(Texture* texture);
    void setNormalMap(Texture* texture);
    void setHeightMap(Texture* texture);
    void setMetallicMap(Texture* texture);
    void setRoughnessMap(Texture* texture);
    void setReflectionMap(Texture* texture);
    void setAmbientOcclusionMap(Texture* texture);
    void setMultiplyMap(Texture* texture);
    void setEmissionMap(Texture* texture);
    void setORMMap(Texture* texture);
    ~PBRShader() override = default;
    void engineRenderShader(Geometry* geometry, unsigned int renderingMode) override;
};
class SpriteShader final: public Shader {
private:
    float currentAlpha;
    glm::vec4 currentDefaultColor;
    Texture* currentTextureMap;
    glm::vec3 currentDefaultMultiplyColor;
    Texture* currentMultiplyTextureMap;
    float currentMultiplyIntensity;
    glm::vec3 currentDefaultEmissionColor;
    Texture* currentEmissionTextureMap;
    float currentEmissionIntensity;
public:
    float alpha;
    glm::vec4 defaultColor;
    Texture* textureMap;
    glm::vec3 defaultMultiplyColor;
    Texture* multiplyTextureMap;
    float multiplyIntensity;
    glm::vec3 defaultEmissionColor;
    Texture* emissionTextureMap;
    float emissionIntensity;
    SpriteShader();
    ~SpriteShader() override;
    void engineRenderShader(Geometry* geometry, unsigned int renderingMode) override;
};
class ParticleShader final: public Shader {
private:
    ParticleNode* particleNode;
    int currentUseLocalSpace;
    int currentIsAdditive;
    Texture* currentTexture;
    glm::vec4 currentColor;
    bool colorAnimationVectorsChanged;
    std::vector<glm::vec4> colorKeys;
    std::vector<float> progressKeys;
    bool spriteSheetAnimationChanged;
    bool hasSpriteSheetAnimation;
    unsigned int spriteSheetAnimationRows;
    unsigned int spriteSheetAnimationColumns;
    unsigned int spriteSheetAnimationInitialFrameRange;
    float spriteSheetAnimationFPS;
    float spriteSheetAnimationFPSVariation;
public:
    ParticleShader(ParticleNode* particleNode);
    ~ParticleShader() override;
    void engineSetParticleShaderColorAnimation(std::vector<glm::vec4> colorKeys, std::vector<float> progressKeys);
    void engineSetSpriteSheetAnimation(unsigned int rows, unsigned int columns,
                                       unsigned int initialFrameRange,
                                       unsigned int FPS, unsigned int FPSVariation);
    void engineRenderShader(Geometry* geometry, unsigned int renderingMode) override;
};
class Particle3DShader final: public Shader {
private:
    Particle3DNode* particleNode;
    int currentUseLocalSpace;
    int currentIsAdditive;
    Texture* currentTexture;
    glm::vec4 currentColor;
    bool colorAnimationVectorsChanged;
    bool useEmissionColor;
    float emissionAlpha;
    std::vector<glm::vec4> colorKeys;
    std::vector<float> progressKeys;
    bool spriteSheetAnimationChanged;
    bool hasSpriteSheetAnimation;
    unsigned int spriteSheetAnimationRows;
    unsigned int spriteSheetAnimationColumns;
    unsigned int spriteSheetAnimationInitialFrameRange;
    float spriteSheetAnimationFPS;
    float spriteSheetAnimationFPSVariation;
public:
    Particle3DShader(Particle3DNode* particle3DNode);
    ~Particle3DShader() override;
    void engineSetParticleShaderColorAnimation(std::vector<glm::vec4> colorKeys, std::vector<float> progressKeys);
    void engineSetSpriteSheetAnimation(unsigned int rows, unsigned int columns,
                                       unsigned int initialFrameRange,
                                       unsigned int FPS, unsigned int FPSVariation);
    void engineRenderShader(Geometry* geometry, unsigned int renderingMode) override;
};
class AlphaShader final : public Shader {
public:
    AlphaShader(std::string shaderFile);
    std::string fileName;
    float alpha;
    glm::vec3 emissionColor;
    AlphaShader* copy();
    void engineRenderShader(Geometry* geometry, unsigned int renderingMode) override;
    ~AlphaShader() override = default;
private:
    float currentAlpha;
    glm::vec3 currenEmissiontColor;
};
#endif
