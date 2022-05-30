//
//  CameraController.cpp
//
//  Created by Kangming Yu on 5/29/22.
//

#include "Game/CG/CameraController.hpp"

#include <cmath>
#include <iostream>

using namespace std;
using namespace glm;


CameraController::CameraController(CameraNode* cameraNode, const BezierCurve& bezierCurve, const EularChangeInfo& eularChangeInfo, float moveAf, float maxSpeed) : camera_node_(cameraNode), bezier_curve_(bezierCurve), eular_change_info_(eularChangeInfo), move_af_(moveAf), max_speed_(maxSpeed) {
    if (bezier_curve_.controll_points.size() > 1) {
        for (int i = 0; i <= bezier_curve_.level_of_detail; i++) {
            float t = i / (float) bezier_curve_.level_of_detail;
            vector<vec3> pointsCurrList = bezier_curve_.controll_points;
            size_t level = pointsCurrList.size();
            for (int j = 1; j < level; j++) {
                vector<vec3> pointsNewList;
                for (auto it = pointsCurrList.begin(); it != pointsCurrList.end() - 1; it++) {
                    vec3 newPoint = (1 - t) * *it + t * *(it + 1);
                    pointsNewList.push_back(newPoint);
                }
                pointsCurrList = pointsNewList;
            }
            curve_points_.push_back(pointsCurrList.front());
        }
    }
    curve_points_size_ = curve_points_.size();
    
    vec3 eularAngleChange;
    if (eular_change_info_.is_clockwise) {
        eularAngleChange = (vec3(360.0f) - (eular_change_info_.end_angle - eular_change_info_.start_angle));
        if (eularAngleChange.x >= 360.0f) {
            eularAngleChange.x -= 360.0f;
        }
        if (eularAngleChange.y >= 360.0f) {
            eularAngleChange.y -= 360.0f;
        }
        if (eularAngleChange.z >= 360.0f) {
            eularAngleChange.z -= 360.0f;
        }
    }
    else {
        eularAngleChange = (vec3(360.0f) + (eular_change_info_.end_angle - eular_change_info_.start_angle));
        if (eularAngleChange.x >= 360.0f) {
            eularAngleChange.x -= 360.0f;
        }
        if (eularAngleChange.y >= 360.0f) {
            eularAngleChange.y -= 360.0f;
        }
        if (eularAngleChange.z >= 360.0f) {
            eularAngleChange.z -= 360.0f;
        }
        
    }
    
    per_angle_ = eularAngleChange / (float) curve_points_size_;
    
    acel_point_index_ = std::min((max_speed_ * max_speed_) / (2 * move_af_), curve_points_size_ / 2.0f);
    decel_point_index_ = std::max(curve_points_size_ - (max_speed_ * max_speed_) / (2 * move_af_), curve_points_size_ / 2.0f);
}


bool CameraController::moveCamera() {
    int prePointIndex = curr_point_index_;
    
    if (curr_point_index_ < acel_point_index_) {
        curr_speed_ += move_af_;
    }
    else if (curr_point_index_ > decel_point_index_){
        curr_speed_ -= move_af_;
        curr_speed_ = std::max(0.0f, curr_speed_);
    }
    curr_distance_ += curr_speed_;
    curr_point_index_ = static_cast<int>(curr_distance_);
    
    if (prePointIndex != curr_point_index_) {
        if (curr_point_index_ >= curve_points_size_) {
            return false;
        }
        int diffIndex = curr_point_index_ - prePointIndex;
        camera_node_->position = curve_points_[curr_point_index_];
        
        if (eular_change_info_.is_clockwise){
            camera_node_->eulerAngles -= (per_angle_ * (float) diffIndex);
            if (camera_node_->eulerAngles.x < -180.0f){
                camera_node_->eulerAngles.x += 360.0f;
            }
            if (camera_node_->eulerAngles.y < -180.0f){
                camera_node_->eulerAngles.y += 360.0f;
            }
            if (camera_node_->eulerAngles.z < -180.0f){
                camera_node_->eulerAngles.z += 360.0f;
            }
        }
        else {
            camera_node_->eulerAngles += (per_angle_ * (float) diffIndex);
            if (camera_node_->eulerAngles.x > 180.0f){
                camera_node_->eulerAngles.x -= 360.0f;
            }
            if (camera_node_->eulerAngles.y > 180.0f){
                camera_node_->eulerAngles.y -= 360.0f;
            }
            if (camera_node_->eulerAngles.z > 180.0f){
                camera_node_->eulerAngles.z -= 360.0f;
            }
        }
        
    }
    
    return true;
}


void CameraController::reset() {
    curr_speed_ = 0.0f;
    curr_distance_ = 0.0f;
    curr_point_index_ = 0;
    
    camera_node_->position = bezier_curve_.controll_points[0];
    camera_node_->eulerAngles = eular_change_info_.start_angle;
}
