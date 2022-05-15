//
//  BaseMagic.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef BaseMagic_hpp
#define BaseMagic_hpp

#include "../includes.hpp"

class Projectile;
class DamageableMagic;
class BaseMagic : public Node{
public:
    vector<Projectile*> projectiles;
    bool start;
    string actionName;
    float stopTime;
    float waitTime;
    int damage;
    CharNode* caster;
    virtual void play(CharNode* character)=0;
    virtual void updateMagic()=0;
    virtual void hitWall(){}
};
class DamageableMagic : public BaseMagic {
public:
    virtual void tryDamage(CharNode* character){}
};

#endif /* BaseMagic_hpp */
