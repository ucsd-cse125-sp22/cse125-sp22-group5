// Developed by Kelin Lyu.

#ifndef DragonMagic_hpp
#define DragonMagic_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

const float dragonMagicBaseRenderingOrder = 100.0f;

class CharNode;
class DragonMagic final : public DamageableMagic {
    
private:
    
    static int UID;
    
    static bool loaded;
    static Node* templateDragonNode;
    static Shader* templateDragonShader;
    static Texture* diffuseMap;
    static Texture* normalMap;
    static Texture* emissionMap;
    static Texture* noiseMap;
    static Texture* maskMap;
    
    static Node* templateBeamNode;
    static Shader* templateBeamShader;
    static Texture* beamMap;
    
    static ParticleNode* fireTemplate;
    static ParticleNode* smokeTemplate;
    static ParticleNode* lineTemplate;
    static ParticleNode* sparkTemplate;
    static ParticleNode* fragmentTemplate;
    static ParticleNode* magicTemplate;
    
    int ID;
    Node* characterNode;
    
    Node* dragonNode;
    Shader* dragonShader;
    Animator* attack;
    float deathFactor;
    
    Node* beamBaseNode;
    Node* beamNode;
    Shader* beamShader;
    float range;
    float rangeFactor;
    
    ParticleNode* emission;
    LightNode* emissionLight;
    ParticleNode* contact;
    ParticleNode* emissionSmoke;
    ParticleNode* emissionLine;
    ParticleNode* emissionSpark;
    
    std::vector<ParticleNode*> fragments;
    
    ParticleNode* magic;
    
    std::string getAnimationName(std::string name);
    
public:
    static void load();
    DragonMagic(Node* characterNode);
    ~DragonMagic() override = default;
    void play();
    void play(CharNode* character, int seed) override;
    void update();
    void updateMagic() override;
    void hitWall() override;
    
    glm::vec3 getBeamPosition();
    glm::vec3 getBeamDirection();
    void setRange(float range);
    void tryDamage(CharNode* character) override;
};

#endif
