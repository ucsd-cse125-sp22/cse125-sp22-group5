//
//  Projectile.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/27/22.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include "../includes.hpp"

class Projectile final : public Node {
public:
    Projectile();
    ~Projectile();
    
    bool canDamage;
    vec3 start;
    vec3 end;
    vector<Node*> damagedChar;
    int damage;
    void tryDamageChar(CharNode* character);
    Projectile* copy();
};

#endif /* Projectile_hpp */
