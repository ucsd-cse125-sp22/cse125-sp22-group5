//
//  MapBoxObject.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/22/22.
//
#include "../../KGLEngine/Engine.hpp"
#ifndef MapBoxObject_hpp
#define MapBoxObject_hpp

class MapBoxObject {
public:
    vec3 position, size, eulerAngles;
    float yRotation;
    void transform(mat4* matrix);
    bool hitTest(vec3 start, vec3 end, vec3* position, vec3* normal, float* timeHit);
};

#endif /* MapBoxObject_hpp */
