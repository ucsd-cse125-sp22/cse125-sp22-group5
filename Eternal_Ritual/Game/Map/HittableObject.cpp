//
//  HittableObject.cpp
//
//  Created by Kangming Yu on 5/11/22.
//

#include "Game/Map/HittableObject.hpp"

using namespace glm;


vec3 HittableObject::hit_point() const {
    return hit_point_;
}


vec3 HittableObject::normal() const {
    return normal_;
}


float HittableObject::hit_time() const {
    return hit_time_;
}
