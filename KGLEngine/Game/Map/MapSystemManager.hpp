//
//  MapSystemManager.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/22/22.
//

#ifndef MapSystemManager_hpp
#define MapSystemManager_hpp
#include "../includes.hpp"

class MapBoxObject;
class MapSystemManager {
public:
    vector<MapBoxObject*> boxes;
    bool hitTest(vec3 start, vec3 end, vec3* position, vec3* normal);
};

#endif /* MapSystemManager_hpp */
