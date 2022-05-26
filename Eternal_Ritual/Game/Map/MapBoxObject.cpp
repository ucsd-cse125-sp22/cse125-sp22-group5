//
//  MapBoxObject.cpp
//
//  Created by Zifan Zhang on 4/22/22.
//  Updated by Kangming Yu on 5/11/22.
//

#include "Game/Map/MapBoxObject.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;


MapBoxObject::MapBoxObject(unsigned int boxType, vec3& boxSize, vec3& boxPosition, vec3& boxEulerAngles) : type_(boxType), size_(boxSize), position_(boxPosition), euler_angles_(boxEulerAngles) {
    updateTransMtx();
    updateMostXYZ();
}


bool MapBoxObject::hitTest(const vec3& start, const vec3& end) {
    vec3 transtart = inv_trans_mtx_ * vec4(start, 1);
    vec3 transend = inv_trans_mtx_ * vec4(end, 1);
    vec3 dir = normalize(transend - transtart);
    vec3 mynormal = normalize(vec3(-dir.x, 0, 0));
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
        mynormal = normalize(vec3(0, -dir.y, 0));
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
        mynormal = normalize(vec3(0, 0, -dir.z));
        tmin = tzmin;
    }

    if (tzmax < tmax)
        tmax = tzmax;

    if (maxt < tmin || tmax < 0)
        return false;
    
    vec3 myposition = transtart + dir * tmin;
    hit_point_ = (trans_mtx_) * vec4(myposition, 1);
    normal_ = normalize(normal_inv_trans_mtx_ * mynormal);
    hit_time_ = distance(hit_point_, start);
    return true;
}


vec3 MapBoxObject::min_xyz() const {
    return min_xyz_;
}


vec3 MapBoxObject::max_xyz() const {
    return max_xyz_;
}


void MapBoxObject::updateMostXYZ() {
    min_xyz_ = vec3(INT_MAX);
    max_xyz_ = vec3(INT_MIN);
    
    vec3 corner1(0.5, 0.5, 0.5);
    corner1 = trans_mtx_ * vec4(corner1, 1);
    min_xyz_ = min(min_xyz_, corner1);
    max_xyz_ = max(max_xyz_, corner1);
    vec3 corner2(0.5, 0.5, -0.5);
    corner2 = trans_mtx_ * vec4(corner2, 1);
    min_xyz_ = min(min_xyz_, corner2);
    max_xyz_ = max(max_xyz_, corner2);
    vec3 corner3(0.5, -0.5, 0.5);
    corner3 = trans_mtx_ * vec4(corner3, 1);
    min_xyz_ = min(min_xyz_, corner3);
    max_xyz_ = max(max_xyz_, corner3);
    vec3 corner4(-0.5, 0.5, 0.5);
    corner4 = trans_mtx_ * vec4(corner4, 1);
    min_xyz_ = min(min_xyz_, corner4);
    max_xyz_ = max(max_xyz_, corner4);
    vec3 corner5(-0.5, -0.5, 0.5);
    corner5 = trans_mtx_ * vec4(corner5, 1);
    min_xyz_ = min(min_xyz_, corner5);
    max_xyz_ = max(max_xyz_, corner5);
    vec3 corner6(-0.5, 0.5, -0.5);
    corner6 = trans_mtx_ * vec4(corner6, 1);
    min_xyz_ = min(min_xyz_, corner6);
    max_xyz_ = max(max_xyz_, corner6);
    vec3 corner7(0.5, -0.5, -0.5);
    corner7 = trans_mtx_ * vec4(corner7, 1);
    min_xyz_ = min(min_xyz_, corner7);
    max_xyz_ = max(max_xyz_, corner7);
    vec3 corner8(-0.5, -0.5, -0.5);
    corner8 = trans_mtx_ * vec4(corner8, 1);
    min_xyz_ = min(min_xyz_, corner8);
    max_xyz_ = max(max_xyz_, corner8);
}


void MapBoxObject::updateTransMtx() {
    trans_mtx_ = translate(mat4(1), position_) *
                eulerAngleYZX(radians(euler_angles_.y),
                              radians(euler_angles_.z),
                              radians(euler_angles_.x)) *
                scale(mat4(1), size_);
    inv_trans_mtx_ = inverse(trans_mtx_);
    normal_inv_trans_mtx_ = transpose(mat3(inv_trans_mtx_));
}


vec3 MapBoxObject::position() const {
    return position_;
}
