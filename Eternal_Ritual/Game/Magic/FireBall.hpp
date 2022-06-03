//
//  FireBall.hpp
//
//  Created by Zifan Zhang on 4/29/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef FireBall_hpp
#define FireBall_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"


class CharNode;


class FireBall final : public DamageableMagic{
private:
    static bool loaded;
    static ParticleNode* metaFireball;
    static ParticleNode* metaFlame;
    static ParticleNode* metaExplosion;
    static ParticleNode* metaSpark;
    static LightNode* metaLight;
    static AudioBuffer* explodeSound;
    static AudioBuffer* flyingSound;
    glm::vec3 wallInt;
    bool hasInt;
    
public:
    glm::vec3 velocity;
    glm::vec3 velocityError;
    glm::vec3 acceleration;
    bool exploded;
    bool threwOut;
    bool canDamage;
    bool explodeDamage;
    ParticleNode* fireball;
    ParticleNode* flame;
    ParticleNode* explosion;
    ParticleNode* spark;
    LightNode* light;
    Animation* createFireball;
    Animation* createFlame;
    void load();
    FireBall();
    ~FireBall() override = default;
    void explode();
    void updateMagic() override;
    void play(CharNode* character, int seed) override;
    void tryDamage(CharNode* character) override;
    void setThrew();
    void hitWall() override;
};

#endif /* FireBall_hpp */
