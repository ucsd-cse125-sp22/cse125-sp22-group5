//
//  GroundSmash.hpp
//  KGLEngine
//
//  Created by futian Zhang on 5/11/22.
//

#ifndef GroundSmash_hpp
#define GroundSmash_hpp

#include "../includes.hpp"

class GroundSmash : public DamageableMagic {
public:
    
    string shaderFile;
    
    string hammerModelFile;
    string hammerTextureFile;
    
    AlphaShader* hammerShader;
    Texture* hammerTexture;
    
    Node* casterRightHandNode;
    
    vec3 hammerScale;
    vec3 hammerPosition;
    vec3 hammerInitPosition;
    vec3 hammerEmission;
    
    vec3 hammerEmissionVariation;
    
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
    
    GroundSmash();
    ~GroundSmash();
    void updateMagic() override;
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
    void hitWall() override {}
};

#endif /* GroundSmash_hpp */
