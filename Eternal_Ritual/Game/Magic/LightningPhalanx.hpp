//
//  LightningPhalanx.hpp
//  Eternal_Ritual
//
//  Created by Zifan Zhang on 5/18/22.
//

#ifndef LightningPhalanx_hpp
#define LightningPhalanx_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"
#include "Game/Magic/LightningSpear.hpp"

class CharNode;


class LightningPhalanx final : public DamageableMagic{
public:
    std::vector<LightningSpear*> spears;
    std::vector<Node*> spearNodes;
    LightningPhalanx();
    ~LightningPhalanx() override = default;
    void playNextSpear(int index);
    void hitWall() override {}
    void updateMagic() override;
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
};

#endif /* LightningPhalanx_hpp */
