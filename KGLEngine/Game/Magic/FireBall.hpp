//
//  FireBall.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/29/22.
//

#ifndef FireBall_hpp
#define FireBall_hpp

#include "../includes.hpp"

class FireBall : public DamageableMagic{
public:
    vec3 velocity;
    vec3 acceleration;
    bool exploded;
    bool threwOut;
    bool canDamage;
    bool explodeDamage;
    ParticleNode* fireball;
    ParticleNode* flame;
    ParticleNode* explosion;
    CharNode* caster;
    LightNode* light;
    Animation* createFireball;
    Animation* createFlame;
    FireBall();
    ~FireBall();
    void updateMagic() override;
    void play(CharNode* character) override;
    void hitWall() override;
    void tryDamage(CharNode* character) override;
};

#endif /* FireBall_hpp */
