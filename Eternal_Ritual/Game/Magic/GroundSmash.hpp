//
//  GroundSmash.hpp
//
//  Created by futian Zhang on 5/11/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef GroundSmash_hpp
#define GroundSmash_hpp

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class GroundSmash final : public DamageableMagic {
public:
    std::string shaderFile;
    
    std::string hammerModelFile;
    std::string hammerTextureFile;
    
    AlphaShader* hammerShader;
    Texture* hammerTexture;
    
    Node* casterRightHandNode;
    
    glm::vec3 hammerScale;
    glm::vec3 hammerPosition;
    glm::vec3 hammerInitPosition;
    glm::vec3 hammerEmission;
    
    glm::vec3 hammerEmissionVariation;
    
    float hammerAlpha;
    
    float raiseTime;
    float holdTime;
    float smashTime;
    float downTime;
    float recoverTime;
    
    Texture* shiningTexture;
    ParticleNode* shiningParticle;
    
    Texture* spreadTexture;
    ParticleNode* spreadParticle;
    
    ParticleNode* explosion;
    
    bool boom;
    
    std::vector<CharNode*> boomedChar;
    
    GroundSmash();
    ~GroundSmash() override;
    void updateMagic() override;
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
    void hitWall() override {}
};

#endif /* GroundSmash_hpp */
