//
//  StoneBlast.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/24/22.
//

#ifndef StoneBlast_hpp
#define StoneBlast_hpp

#include "../includes.hpp"

class StoneBlast : public DamageableMagic{
public:
    vector<Animation*> waits;
    vector<Animation*> forwards;
    
    Texture* stone_D;
    Texture* stone_E;
    Texture* circleTexture;
    
    Animation* cleanup;
    Animation* createMagicCircle;
    Animation* removeMagicCircle;
    
    Animation* playArrow;
    
    vector<Node*> magicCircles;
    vector<AlphaShader*> circle_shaders;
    
    vector<vec3> randomPositions;
    
    vector<vec3> translatePosition;
    vec3 rotationPosition;
    
    vector<vec3> circleEmissions;
    vec3 circleVariantion;
    
    Texture* shiningParticleTexture;
    vector<ParticleNode*> shinnings;
    
    vector<Particle3DNode*> arrows;
    
    bool canDamage;
    
    StoneBlast();
    vector<int> rounds;
    void updateMagic() override;
    void play(CharNode* character) override;
    void hitWall() override {}
    void moveStones(int roundNum);
    void tryDamage(CharNode* character) override;
    ~StoneBlast();
};

#endif /* StoneBlast_hpp */
