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
class BaseMagic : public Node{
public:
    vector<Projectile*> projectiles;
    bool start;
    string actionName;
    float stopTime;
    float waitTime;
    int damage;
    void tryDamage(CharNode* character);
    virtual void play(vec3 position, vec3 euler)=0;
    virtual void updateMagic()=0;
};

#endif /* BaseMagic_hpp */
