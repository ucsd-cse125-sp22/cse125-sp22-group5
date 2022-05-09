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
    vector<Animation*> spins;
    vector<Animation*> forwards;
    
    Texture* stone_D;
    Texture* stone_E;
    PBRShader* stone_shader;
    Texture* circleTexture;
    
    Animation* cleanup;
    Animation* createMagicCircle;
    Animation* removeMagicCircle;
    
    Node* magicCircle;
    PBRShader* circle_shader;
    
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
