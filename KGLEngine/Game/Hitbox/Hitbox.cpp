//
//  Hitbox.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#include "Hitbox.hpp"

Hitbox::Hitbox(vec3 position, vec3 size){
    this->size = size;
    updatePosition(position);
}

void Hitbox::updatePosition(vec3 position){
    this->position = position;
    this->top = position.y + size.y;
    this->bottom = position.y;
    this->left = position.x - size.x / 2;
    this->right = position.x + size.x / 2;
    this->front = position.z - size.z / 2;
    this->back = position.z + size.z / 2;
}

bool Hitbox::testHit(vec3 start, vec3 end){
    vec3 direction = normalize(end - start);
    
    // Touch front
    float diff = this->front - start.z;
    vec3 touchPos = start + direction * diff / direction.z;
    if ((touchPos.z >= start.z && touchPos.z <= end.z) ||
        (touchPos.z <= start.z && touchPos.z >= end.z)){
        
        if (touchPos.x >= this->left && touchPos.x <= this->right &&
            touchPos.y >= this->bottom && touchPos.y <= this->top){
            return true;
        }
    }
    
    // Touch back
    diff = this->back - end.z;
    touchPos = start + direction * diff / direction.z;
    if ((touchPos.z >= start.z && touchPos.z <= end.z) ||
        (touchPos.z <= start.z && touchPos.z >= end.z)){
        
        if (touchPos.x >= this->left && touchPos.x <= this->right &&
            touchPos.y >= this->bottom && touchPos.y <= this->top){
            return true;
        }
    }
    
    // Touch top
    diff = this->top - end.y;
    touchPos = start + direction * diff / direction.y;
    if ((touchPos.y >= start.y && touchPos.y <= end.y) ||
        (touchPos.y <= start.y && touchPos.y >= end.y)){
        
        if (touchPos.x >= this->left && touchPos.x <= this->right &&
            touchPos.z >= this->front && touchPos.z <= this->back){
            return true;
        }
    }
    
    // Touch bottom
    diff = this->bottom - end.x;
    touchPos = start + direction * diff / direction.x;
    if ((touchPos.x >= start.x && touchPos.x <= end.x) ||
        (touchPos.x <= start.x && touchPos.x >= end.x)){
        
        if (touchPos.y >= this->bottom && touchPos.y <= this->top &&
            touchPos.z >= this->front && touchPos.z <= this->back){
            return true;
        }
    }
    
    // Touch left
    diff = this->left - end.y;
    touchPos = start + direction * diff / direction.y;
    if ((touchPos.y >= start.y && touchPos.y <= end.y) ||
        (touchPos.y <= start.y && touchPos.y >= end.y)){
        
        if (touchPos.x >= this->left && touchPos.x <= this->right &&
            touchPos.z >= this->front && touchPos.z <= this->back){
            return true;
        }
    }
    
    return false;
}
