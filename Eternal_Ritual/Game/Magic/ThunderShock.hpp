//
//  ThunderShock.hpp
//
//  Created by Zifan Zhang on 5/10/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef ThunderShock_hpp
#define ThunderShock_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class ThunderShock final : public DamageableMagic{
public:
    bool threwOut;
    bool canDamage;
    std::vector<Particle3DNode*> lightnings;
    Particle3DNode* base;
    LightNode* light;
    ThunderShock();
    ~ThunderShock() override = default;
    void explode();
    void hitWall() override {}
    void updateMagic() override {}
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
};
#endif /* ThunderShock_hpp */
