//
//  LightningMagic.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/27/22.
//

#ifndef LightningMagic_hpp
#define LightningMagic_hpp

#include "BaseMagic.hpp"
class LightningMagic : public BaseMagic{
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
    
    LightningMagic();
    vector<int> rounds;
    void updateMagic();
    void play(vec3 position, vec3 euler);
    void moveStones(int roundNum);
    ~LightningMagic();
};

#endif /* LightningMagic_hpp */
