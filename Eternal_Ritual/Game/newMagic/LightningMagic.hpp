//
//  LightningMagic.hpp
//
//  Created by Zifan Zhang on 4/27/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef LightningMagic_hpp
#define LightningMagic_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"


class LightningMagic final: public BaseMagic{
public:
    std::vector<Node*> stones;
    std::vector<Animation*> waits;
    std::vector<Animation*> spins;
    std::vector<Animation*> forwards;
    
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
    std::vector<int> rounds;
    void updateMagic() override;
    void play(CharNode* character) override;
    void moveStones(int roundNum);
    ~LightningMagic() override = default;
};

#endif /* LightningMagic_hpp */
