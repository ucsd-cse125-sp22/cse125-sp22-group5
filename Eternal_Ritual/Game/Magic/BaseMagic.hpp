//
//  BaseMagic.hpp
//
//  Created by futian Zhang on 4/23/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef BaseMagic_hpp
#define BaseMagic_hpp

#include <vector>
#include <string>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/Projectile.hpp"

class CharNode;


namespace Magic {

enum Type {
    FIREBALL = 0,
    STORM = 1,
    THUNDER = 2,
    DRAGON = 3,
    LIGHTNINGSPEAR = 4,
    GROUNDSMASH = 5,
    FLAME = 6,
    THOUSANDBLADE = 7,
    STONEBLAST = 8
};

} // namespace Magic

class BaseMagic : public Node {
public:
    std::vector<Projectile*> projectiles;
    bool start;
    std::string actionName;
    float stopTime;
    float waitTime;
    float cooldown;
    float cost;
    float availableTime;
    int damage;
    int seed;
    CharNode* caster;
    virtual void play(CharNode* character, int seed) = 0;
    virtual void updateMagic() = 0;
    virtual void hitWall() = 0;
    
    virtual ~BaseMagic() = 0;
};


class DamageableMagic : public BaseMagic {
public:
    virtual void tryDamage(CharNode* character) = 0;
    
    virtual ~DamageableMagic() override = 0;
};

#endif /* BaseMagic_hpp */
