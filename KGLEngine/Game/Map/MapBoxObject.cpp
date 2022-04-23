//
//  MapBoxObject.cpp
//  KGLEngine
//
//  Created by Zifan Zhang on 4/22/22.
//

#include "MapBoxObject.hpp"


void MapBoxObject::transform(glm::mat4 *matrix) {
    *matrix = translate(mat4(1), position) * rotate(mat4(1), radians(yRotation), vec3(0, 1, 0)) * scale(mat4(1), size);
}

bool MapBoxObject::hitTest(glm::vec3 start, glm::vec3 end, glm::vec3 *position, glm::vec3 *normal, float *timeHit) {
    mat4 trans;
    transform(&trans);
    mat4 inv = inverse(trans);
    vec3 transtart = inv * vec4(start, 1);
    vec3 transend = inverse(trans) * vec4(end, 1);
    vec3 dir = normalize(transend - transtart);
    vec3 mynormal = normalize(vec3((transtart - transend).x, 0, 0));
    float maxt = distance(transtart, transend);
    float tmin = (-0.5 - transtart.x) / dir.x;
    float tmax = (0.5 - transtart.x) / dir.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (-0.5 - transtart.y) / dir.y;
    float tymax = (0.5 - transtart.y) / dir.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin) {
        mynormal = normalize(vec3(0, (transtart - transend).y, 0));
        tmin = tymin;
    }

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (-0.5 - transtart.z) / dir.z;
    float tzmax = (0.5 - transtart.z) / dir.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin) {
        mynormal = normalize(vec3(0, 0, (transtart - transend).z));
        tmin = tzmin;
    }

    if (tzmax < tmax)
        tmax = tzmax;

    if (maxt < tmin)
        return false;
    vec3 myposition = transtart + dir * tmin;
    *position = (trans) * vec4(myposition, 1);
    *normal = normalize(transpose(inverse(trans)) * vec4(mynormal, 0));
    *timeHit = distance(*position, start);
    return true;
}

