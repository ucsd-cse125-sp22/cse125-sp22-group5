//
//  StoneBlast.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/24/22.
//

#ifndef StoneBlast_hpp
#define StoneBlast_hpp

#include <stdio.h>

#include "BaseMagic.hpp"

class StoneBlast : public BaseMagic{
public:
    vector<Node*> stones;
    vector<Animation*> waits;
    vector<Animation*> spins;
    vector<Animation*> forwards;
    
    Texture* stone_D;
    Texture* stone_E;
    PBRShader* stone_shader;
    Node* stone;
    Texture* circleTexture;
    
    Animation* cleanup;
    Animation* createMagicCircle;
    Animation* removeMagicCircle;
    
    Node* magicCircle;
    PBRShader* circle_shader;
    
    StoneBlast();
    vector<int> rounds;
    void updateMagic();
    void play(vec3 position, vec3 euler);
    void moveStones(int roundNum);
    ~StoneBlast();
};

#endif /* StoneBlast_hpp */
