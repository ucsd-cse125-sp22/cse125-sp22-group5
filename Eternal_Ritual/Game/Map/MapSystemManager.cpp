//
//  MapSystemManager.cpp
//
//  Created by Zifan Zhang on 4/22/22.
//  Updated by Kangming Yu on 5/11/22.
//

#include "Game/Map/MapSystemManager.hpp"

#include <iostream>

using namespace glm;
using namespace std;


MapSystemManager* MapSystemManager::map_system_manager_ = nullptr;

MapSystemManager::MapSystemManager() : min_xyz_(INT_MAX), max_xyz_(INT_MIN) {}

bool MapSystemManager::hitTest(const vec3& start, const vec3& end, HitInfo& hitInfo) {
    bool isHit = false;
    float minTime = MAXFLOAT;
    float hitTime;
    for (auto& box : boxes_) {
        if (box->hitTest(start, end)) {
            isHit = true;
            hitTime = box->hit_time();
            if (hitTime < minTime) {
                hitInfo.hit_point = box->hit_point();
                hitInfo.normal = box->normal();
                hitInfo.hit_box = box;
                minTime = hitTime;
            }
        }
    }
    return isHit;
}

bool MapSystemManager::gridsHitTest(const vec3& start, const vec3& end, HitInfo& hitInfo) {
    if (start == end) return false;
    bool isHit = false;
    float minTime = MAXFLOAT;
    float hitTime;
    
    int widthIdx = (end.x - min_xyz_.x) / per_grid_width_;
    int lengthIdx = (end.z - min_xyz_.z) / per_grid_length_;
    int gridIdx = lengthIdx * NUM_WIDTH_GRIDS + widthIdx;
    for (auto& box : grids_[gridIdx]) {
        if (box->hitTest(start, end)) {
            isHit = true;
            hitTime = box->hit_time();
            if (hitTime < minTime) {
                hitInfo.hit_point = box->hit_point();
                hitInfo.normal = box->normal();
                hitInfo.hit_box = box;
                minTime = hitTime;
            }
        }
    }
    return isHit;
}


void MapSystemManager::addMapBox(MapBoxObject* mapBox) {
    boxes_.push_back(mapBox);
    
    min_xyz_ = min(min_xyz_, mapBox->min_xyz() - vec3(0.1));
    max_xyz_ = max(max_xyz_, mapBox->max_xyz() + vec3(0.1));
}


void MapSystemManager::updateGrids() {
    float width = max_xyz_.x - min_xyz_.x;
    float length = max_xyz_.z - min_xyz_.z;
    per_grid_width_ = width / NUM_WIDTH_GRIDS;
    per_grid_length_ = length / NUM_LENGTH_GRIDS;
    
    for (auto& box : boxes_) {
        vec3 boxMinXYZ = box->min_xyz();
        vec3 boxMaxXYZ = box->max_xyz();
        
        int widthIdx1 = (boxMinXYZ.x - min_xyz_.x) / per_grid_width_;
        int lengthIdx1 = (boxMinXYZ.z - min_xyz_.z) / per_grid_length_;
        int widthIdx2 = (boxMaxXYZ.x - min_xyz_.x) / per_grid_width_;
        int lengthIdx2 = (boxMaxXYZ.z - min_xyz_.z) / per_grid_length_;
        
        for (int i = widthIdx1; i <= widthIdx2; i++) {
            for (int j = lengthIdx1; j <= lengthIdx2; j++) {
                int gridIdx = j * NUM_WIDTH_GRIDS + i;
                grids_[gridIdx].push_back(box);
            }
        }
    }
}
