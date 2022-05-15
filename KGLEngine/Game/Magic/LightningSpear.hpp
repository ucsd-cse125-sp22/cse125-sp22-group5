//
//  LightningSpear.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/3/22.
//

#ifndef LightningSpear_hpp
#define LightningSpear_hpp

#include "../includes.hpp"

class LightningSpear : public DamageableMagic{
public:
    vec3 velocity;
    vec3 acceleration;
    bool exploded;
    bool threwOut;
    bool canDamage;
    bool explodeDamage;
    Particle3DNode* spear;
    Particle3DNode* radiation;
    LightNode* light;
    LightningSpear();
    ~LightningSpear();
    void hitWall() override;
    void updateMagic() override;
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
};

#endif /* LightningSpear_hpp */
