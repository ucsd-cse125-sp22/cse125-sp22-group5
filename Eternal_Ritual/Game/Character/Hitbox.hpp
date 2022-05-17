//
//  Hitbox.hpp
//
//  Created by futian Zhang on 4/23/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef Hitbox_hpp
#define Hitbox_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"


class Hitbox final {
public:
    Hitbox(glm::vec3 position, glm::vec3 size);
    void updatePosition(glm::vec3 position);
    bool testHit(glm::vec3 start, glm::vec3 end);
    bool testSphere(glm::vec3 center, float radius);
    
private:
    glm::vec3 position, size;
    Node* cube;
    float front, back, left, right, top, bottom;
};

#endif /* Hitbox_hpp */
