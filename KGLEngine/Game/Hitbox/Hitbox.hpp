//
//  Hitbox.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef Hitbox_hpp
#define Hitbox_hpp

#include "../includes.hpp"

class Hitbox {
private:
    vec3 position, size;
    Node* cube;
    float front, back, left, right, top, bottom;
public:
    Hitbox(vec3 position, vec3 size);
    void updatePosition(vec3 position);
    bool testHit(vec3 start, vec3 end);
    bool testSphere(vec3 center, float radius);
};

#endif /* Hitbox_hpp */
