//
//  ThousandBlade.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef ThousandBlade_hpp
#define ThousandBlade_hpp

#include "../includes.hpp"

class ThousandBlade : public DamageableMagic{
public:
    ThousandBlade();
    
    string swordTextureFile;
    string shaderFile;
    string swordModelFile;
    vec3 swordEmission;
    vec3 swordScale;
    
    vec3 circleVariantion;
    
    string circleTextureFile;
    string circleModelFile;
    vec3 magicCirclePosition;
    vec3 magicCircleScale;
    vec3 circleEmission;
    
    string crackTextureFile;
    string circleParticleFile;
    string swordParticleFile;
    string shiningParticleFile;
    
    vector<float> randomAngles;
    vector<int> randomDistance;
    
    
    vector<AlphaShader*> swordShaders;
    vector<AlphaShader*> circleShaders;
    vector<AlphaShader*> crackShaders;
    
    vector<ParticleNode*> circleParticles;
    vector<ParticleNode*> swordParticles;
    vector<ParticleNode*> shiningParticles;
    
    vector<Node*> magicCircles;
    
    vector<Node*> cracks;
    
    Texture* sword_d;
    Texture* circleTexture;
    Texture* circleParticleTexture;
    Texture* swordParticleTexture;
    Texture* shiningParticleTexture;
    Texture* crackTexture;
    
    int number_groups;
    float variation_time;
    float circle_in_time;
    float circle_last_time;
    float circle_out_time;
    float sword_in_time;
    float sword_last_time;
    float sword_out_time;
    float cast_range;
    float total_time;
    
    float damage_range;
    
    vector<int> rounds;
    
    ~ThousandBlade();
    void updateMagic() override;
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
    void hitWall() override {}
};

#endif /* ThousandBlade_hpp */
