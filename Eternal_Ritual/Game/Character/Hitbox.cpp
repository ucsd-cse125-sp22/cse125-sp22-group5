//
//  Hitbox.cpp
//
//  Created by futian Zhang on 4/23/22.
//  Updated by Kangming Yu on 5/14/22.
//

#include "Game/Character/Hitbox.hpp"

#include <glm/gtx/norm.hpp>

using namespace std;
using namespace glm;


Hitbox::Hitbox(vec3 position, vec3 size){
    this->size = size;
    updatePosition(position);
}

void Hitbox::updatePosition(vec3 position){
    this->position = position;
    this->top = position.y + size.y;
    this->bottom = position.y;
    this->left = position.z - size.z / 2;
    this->right = position.z + size.z / 2;
    this->front = position.x - size.x / 2;
    this->back = position.x + size.x / 2;
}

bool Hitbox::testHit(vec3 start, vec3 end){
    vec3 direction = end - start;
    
    if ((start.x >= this->front && start.x <= this->back &&
        start.y >= this->bottom && start.y <= this->top &&
        start.z >= this->left && start.z <= this->right) ||
        (end.x >= this->front && end.x <= this->back &&
         end.y >= this->bottom && end.y <= this->top &&
         end.z >= this->left && end.z <= this->right)){
        return true;
    }
    
    // Touch front
    float diff = this->front - start.x;
    vec3 touchPos = start + direction * diff / direction.x;
    if ((touchPos.x >= start.x && touchPos.x <= end.x) ||
        (touchPos.x <= start.x && touchPos.x >= end.x)){
        
        if (touchPos.z >= this->left && touchPos.z <= this->right &&
            touchPos.y >= this->bottom && touchPos.y <= this->top){
            return true;
        }
    }
    
    // Touch back
    diff = this->back - start.x;
    touchPos = start + direction * diff / direction.x;
    if ((touchPos.x >= start.x && touchPos.x <= end.x) ||
        (touchPos.x <= start.x && touchPos.x >= end.x)){
        
        if (touchPos.z >= this->left && touchPos.z <= this->right &&
            touchPos.y >= this->bottom && touchPos.y <= this->top){
            return true;
        }
    }
    
    // Touch top
    diff = this->top - start.y;
    touchPos = start + direction * diff / direction.y;
    if ((touchPos.y >= start.y && touchPos.y <= end.y) ||
        (touchPos.y <= start.y && touchPos.y >= end.y)){
        
        if (touchPos.z >= this->left && touchPos.z <= this->right &&
            touchPos.x >= this->front && touchPos.x <= this->back){
            return true;
        }
    }
    
    // Touch bottom
    diff = this->bottom - start.y;
    touchPos = start + direction * diff / direction.y;
    if ((touchPos.y >= start.y && touchPos.y <= end.y) ||
        (touchPos.y <= start.y && touchPos.y >= end.y)){
        
        if (touchPos.z >= this->left && touchPos.z <= this->right &&
            touchPos.x >= this->front && touchPos.x <= this->back){
            return true;
        }
    }
    
    // Touch left
    diff = this->left - start.z;
    touchPos = start + direction * diff / direction.z;
    if ((touchPos.z >= start.z && touchPos.z <= end.z) ||
        (touchPos.z <= start.z && touchPos.z >= end.z)){
        
        if (touchPos.y >= this->bottom && touchPos.y <= this->top &&
            touchPos.x >= this->front && touchPos.x <= this->back){
            return true;
        }
    }
    
    // Touch right
    diff = this->right - start.z;
    touchPos = start + direction * diff / direction.z;
    if ((touchPos.z >= start.z && touchPos.z <= end.z) ||
        (touchPos.z <= start.z && touchPos.z >= end.z)){
        
        if (touchPos.y >= this->bottom && touchPos.y <= this->top &&
            touchPos.x >= this->front && touchPos.x <= this->back){
            return true;
        }
    }
    
    return false;
}

bool Hitbox::testSphere(vec3 center, float radius){
    
    float dist_squared = radius * radius;
    vec3 corner2 = position + size;
    /* assume C1 and C2 are element-wise sorted, if not, do that now */
    if (center.x < position.x) dist_squared -= length2(center.x - position.x);
    else if (center.x > corner2.x) dist_squared -= length2(center.x - corner2.x);
    if (center.y < position.y) dist_squared -= length2(center.y - position.y);
    else if (center.y > corner2.y) dist_squared -= length2(center.y - corner2.y);
    if (center.z < position.z) dist_squared -= length2(center.z - position.z);
    else if (center.z > corner2.z) dist_squared -= length2(center.z - corner2.z);
    return dist_squared > 0;
}
