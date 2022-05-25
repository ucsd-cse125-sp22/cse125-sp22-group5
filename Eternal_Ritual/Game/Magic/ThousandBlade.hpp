//
//  ThousandBlade.hpp
//
//  Created by futian Zhang on 4/23/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef ThousandBlade_hpp
#define ThousandBlade_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class ThousandBlade final : public DamageableMagic {
public:
    ThousandBlade();
    
    std::string swordTextureFile;
    std::string shaderFile;
    std::string swordModelFile;
    glm::vec3 swordEmission;
    glm::vec3 swordScale;
    
    glm::vec3 circleVariantion;
    
    std::string circleTextureFile;
    std::string circleModelFile;
    glm::vec3 magicCirclePosition;
    glm::vec3 magicCircleScale;
    glm::vec3 circleEmission;
    
    std::string crackTextureFile;
    std::string circleParticleFile;
    std::string swordParticleFile;
    std::string shiningParticleFile;
    
    std::vector<float> randomAngles;
    std::vector<int> randomDistance;
    
    
    std::vector<AlphaShader*> swordShaders;
    std::vector<AlphaShader*> circleShaders;
    std::vector<AlphaShader*> crackShaders;
    
    std::vector<ParticleNode*> circleParticles;
    std::vector<ParticleNode*> swordParticles;
    std::vector<ParticleNode*> shiningParticles;
    
    std::vector<Node*> magicCircles;
    
    std::vector<Node*> cracks;
    
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
    
    std::vector<int> rounds;
    
    ~ThousandBlade() override;
    void updateMagic() override;
    void play(CharNode* character, int seed) override;
    void tryDamage(CharNode* character) override;
    void hitWall() override {}
};

#endif /* ThousandBlade_hpp */
