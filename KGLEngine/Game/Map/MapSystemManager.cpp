//
//  MapSystemManager.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/22/22.
//

#include "MapSystemManager.hpp"


bool MapSystemManager::hitTest(glm::vec3 start, glm::vec3 end, glm::vec3 *position, glm::vec3 *normal) {
    bool hit = false;
    float mint = MAXFLOAT;
    float thit;
    vec3 myposition, mynormal;
    for (auto box = boxes.begin(); box != boxes.end(); box++) {
        if ((*box)->hitTest(start, end, &myposition, &mynormal, &thit)) {
            hit = true;
            if (thit < mint) {
                *position = myposition;
                *normal = mynormal;
                mint = thit;
            }
        }
    }
    return hit;
}
