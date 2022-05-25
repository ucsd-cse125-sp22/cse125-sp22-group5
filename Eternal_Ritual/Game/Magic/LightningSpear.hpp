//
//  LightningSpear.hpp
//
//  Created by Zifan Zhang on 5/3/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef LightningSpear_hpp
#define LightningSpear_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class LightningSpear final: public DamageableMagic{
public:
    glm::vec3 velocity;
    glm::vec3 acceleration;
    bool exploded;
    bool threwOut;
    bool canDamage;
    bool explodeDamage;
    Particle3DNode* spear;
    Particle3DNode* radiation;
    LightNode* light;
    LightningSpear();
    ~LightningSpear() override = default;
    void setThrew();
    void hitWall() override;
    void updateMagic() override;
    void play(CharNode* character, int seed) override;
    void tryDamage(CharNode* character) override;
};

#endif /* LightningSpear_hpp */
