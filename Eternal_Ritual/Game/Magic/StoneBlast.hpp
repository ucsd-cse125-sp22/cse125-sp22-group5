//
//  StoneBlast.hpp
//
//  Created by futian Zhang on 4/24/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef StoneBlast_hpp
#define StoneBlast_hpp

#include <vector>
#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class StoneBlast final : public DamageableMagic{
public:
    std::vector<Animation*> waits;
    std::vector<Animation*> forwards;
    
    Texture* stone_D;
    Texture* stone_E;
    Texture* circleTexture;
    
    Animation* cleanup;
    Animation* createMagicCircle;
    Animation* removeMagicCircle;
    
    Animation* playArrow;
    
    std::vector<Node*> magicCircles;
    std::vector<AlphaShader*> circle_shaders;
    
    std::vector<glm::vec3> randomPositions;
    
    std::vector<glm::vec3> translatePosition;
    glm::vec3 rotationPosition;
    
    std::vector<glm::vec3> circleEmissions;
    glm::vec3 circleVariantion;
    
    Texture* shiningParticleTexture;
    std::vector<ParticleNode*> shinnings;
    
    std::vector<ParticleNode*> clouds;
    
    std::vector<Particle3DNode*> arrows;
    
    bool canDamage;
    
    StoneBlast();
    std::vector<int> rounds;
    void updateMagic() override;
    void play(CharNode* character) override;
    void hitWall() override {}
    void moveStones(int roundNum);
    void tryDamage(CharNode* character) override;
    ~StoneBlast() override;
};

#endif /* StoneBlast_hpp */
