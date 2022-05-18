//
//  Flame.hpp
//
//  Created by Zifan Zhang on 5/11/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef Flame_hpp
#define Flame_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class Flame final : public DamageableMagic{
public:
    bool canDamage;
    ParticleNode* flame;
    ParticleNode* spark;
    Flame();
    ~Flame() override = default;
    void updateMagic() override {}
    void play(CharNode* character, int seed) override;
    void hitWall() override {}
    void tryDamage(CharNode* character) override;
};
#endif /* Flame_hpp */
