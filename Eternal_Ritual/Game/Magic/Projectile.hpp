//
//  Projectile.hpp
//
//  Created by futian Zhang on 4/27/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <vector>
#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"

class CharNode;


class Projectile final : public Node {
public:
    Projectile();
    ~Projectile();
    
    bool canDamage;
    glm::vec3 start;
    glm::vec3 end;
    std::vector<Node*> damagedChar;
    int damage;
    void tryDamageChar(CharNode* character);
    Projectile* copy();
    Projectile* clone();
};

#endif /* Projectile_hpp */
