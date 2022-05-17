//
//  MapSystemManager.cpp
//
//  Created by Zifan Zhang on 4/22/22.
//  Updated by Kangming Yu on 5/11/22.
//

#include "Game/Map/MapSystemManager.hpp"

using namespace glm;


MapSystemManager* MapSystemManager::mapSystemManager = nullptr;

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
    bool isHit = false;
    float minTime = MAXFLOAT;
    float hitTime;
    
    int widthIdx = (end.x - min_xyz_.x) / per_grid_width_;
    int lengthIdx = (end.z - min_xyz_.z) / per_grid_length_;
    int gridIdx = lengthIdx * 3 + widthIdx;
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
    
    min_xyz_ = min(min_xyz_, mapBox->min_xyz());
    max_xyz_ = max(max_xyz_, mapBox->max_xyz());
}


void MapSystemManager::updateGrids() {
    float width = max_xyz_.x - min_xyz_.x;
    float length = max_xyz_.z - min_xyz_.z;
    per_grid_width_ = width / 3;
    per_grid_length_ = length / 3;
    float width1 = min_xyz_.x + per_grid_width_;
    float width2 = max_xyz_.x - per_grid_width_;
    float length1 = min_xyz_.z + per_grid_length_;
    float length2 = max_xyz_.z - per_grid_length_;
    
    for (auto& box : boxes_) {
        vec3 boxMinXYZ = box->min_xyz();
        vec3 boxMaxXYZ = box->max_xyz();
        
        if (boxMinXYZ.x <= width1) {
            if (boxMinXYZ.z <= length1) {
                grids_[0].push_back(box);
            }
            if (boxMaxXYZ.z >= length2) {
                grids_[2].push_back(box);
            }
            if (!(boxMaxXYZ.z <= length1 || boxMinXYZ.z >= length2)) {
                grids_[1].push_back(box);
            }
        }
        if (boxMaxXYZ.x >= width2) {
            if (boxMinXYZ.z <= length1) {
                grids_[6].push_back(box);
            }
            if (boxMaxXYZ.z >= length2) {
                grids_[8].push_back(box);
            }
            if (!(boxMaxXYZ.z <= length1 || boxMinXYZ.z >= length2)) {
                grids_[7].push_back(box);
            }
        }
        if (!(boxMaxXYZ.x <= width1 || boxMinXYZ.x >= width2)) {
            if (boxMinXYZ.z <= length1) {
                grids_[3].push_back(box);
            }
            if (boxMaxXYZ.z >= length2) {
                grids_[5].push_back(box);
            }
            if (!(boxMaxXYZ.z <= length1 || boxMinXYZ.z >= length2)) {
                grids_[4].push_back(box);
            }
        }
    }
}
