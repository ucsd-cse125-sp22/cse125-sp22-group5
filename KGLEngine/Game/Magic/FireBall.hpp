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
    ParticleNode* fireball;
    ParticleNode* flame;
    ParticleNode* explosion;
    LightNode* light;
    Animation* createFireball;
    Animation* createFlame;
    FireBall();
    ~FireBall();
    void updateMagic() override;
    void play(vec3 position, vec3 euler) override;
    void tryDamage(CharNode* character) override;
};

#endif /* FireBall_hpp */
