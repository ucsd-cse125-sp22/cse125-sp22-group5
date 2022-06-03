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


CameraController::CameraController(CameraNode* cameraNode, const BezierCurve& bezierCurve, const EularChangeInfo& eularChangeInfo, const SpeedChangeInfo& speedChangeInfo) : camera_node_(cameraNode), bezier_curve_(bezierCurve), eular_change_info_(eularChangeInfo), speed_change_info_(speedChangeInfo) {
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
    if (eular_change_info_.is_clockwise_x) {
        eularAngleChange.x = (360.0f - (eular_change_info_.end_angle.x - eular_change_info_.start_angle.x));
        if (eularAngleChange.x >= 360.0f) {
            eularAngleChange.x -= 360.0f;
        }
    }
    else {
        eularAngleChange.x = (360.0f + (eular_change_info_.end_angle.x - eular_change_info_.start_angle.x));
        if (eularAngleChange.x >= 360.0f) {
            eularAngleChange.x -= 360.0f;
        }
    }
    if (eular_change_info_.is_clockwise_y) {
        eularAngleChange.y = (360.0f - (eular_change_info_.end_angle.y - eular_change_info_.start_angle.y));
        if (eularAngleChange.y >= 360.0f) {
            eularAngleChange.y -= 360.0f;
        }
    }
    else {
        eularAngleChange.y = (360.0f + (eular_change_info_.end_angle.y - eular_change_info_.start_angle.y));
        if (eularAngleChange.y >= 360.0f) {
            eularAngleChange.y -= 360.0f;
        }
    }
    if (eular_change_info_.is_clockwise_z) {
        eularAngleChange.z = (360.0f - (eular_change_info_.end_angle.z - eular_change_info_.start_angle.z));
        if (eularAngleChange.z >= 360.0f) {
            eularAngleChange.z -= 360.0f;
        }
    }
    else {
        eularAngleChange.z = (360.0f + (eular_change_info_.end_angle.z - eular_change_info_.start_angle.z));
        if (eularAngleChange.z >= 360.0f) {
            eularAngleChange.z -= 360.0f;
        }
    }
    
    
    per_angle_ = eularAngleChange / (float) curve_points_size_;
    
    acel_point_index_ = std::min((speed_change_info_.max_speed * speed_change_info_.max_speed - speed_change_info_.init_speed * speed_change_info_.init_speed)/(2 * speed_change_info_.move_af), curve_points_size_ / 2.0f);
    decel_point_index_ = std::max(curve_points_size_ - (speed_change_info_.max_speed * speed_change_info_.max_speed - speed_change_info_.end_speed * speed_change_info_.end_speed)/(2 * speed_change_info_.move_af), curve_points_size_ / 2.0f);
    
    curr_speed_ = speed_change_info_.init_speed;
}


bool CameraController::moveCamera() {
    int prePointIndex = curr_point_index_;
    
    if (curr_point_index_ < acel_point_index_) {
        curr_speed_ += speed_change_info_.move_af;
    }
    else if (curr_point_index_ > decel_point_index_){
        curr_speed_ -= speed_change_info_.move_af;
        curr_speed_ = std::max(0.0f, curr_speed_);
    }
    curr_distance_ += curr_speed_;
    curr_point_index_ = static_cast<int>(curr_distance_);
    
    if (prePointIndex < curve_points_size_ - 1) {
        if (curr_point_index_ >= curve_points_size_) {
            curr_point_index_ = static_cast<int>(curve_points_size_) - 1;
        }
        int diffIndex = curr_point_index_ - prePointIndex;
        camera_node_->position = curve_points_[curr_point_index_];
        
        if (eular_change_info_.is_clockwise_x){
            camera_node_->eulerAngles.x -= (per_angle_.x * (float) diffIndex);
            if (camera_node_->eulerAngles.x < -180.0f){
                camera_node_->eulerAngles.x += 360.0f;
            }
        }
        else {
            camera_node_->eulerAngles.x += (per_angle_.x * (float) diffIndex);
            if (camera_node_->eulerAngles.x > 180.0f){
                camera_node_->eulerAngles.x -= 360.0f;
            }
        }
        
        if (eular_change_info_.is_clockwise_y){
            camera_node_->eulerAngles.y -= (per_angle_.y * (float) diffIndex);
            if (camera_node_->eulerAngles.y < -180.0f){
                camera_node_->eulerAngles.y += 360.0f;
            }
        }
        else {
            camera_node_->eulerAngles.y += (per_angle_.y * (float) diffIndex);
            if (camera_node_->eulerAngles.y > 180.0f){
                camera_node_->eulerAngles.y -= 360.0f;
            }
        }
        
        if (eular_change_info_.is_clockwise_z){
            camera_node_->eulerAngles.z -= (per_angle_.z * (float) diffIndex);
            if (camera_node_->eulerAngles.z < -180.0f){
                camera_node_->eulerAngles.z += 360.0f;
            }
        }
        else {
            camera_node_->eulerAngles.z += (per_angle_.z * (float) diffIndex);
            if (camera_node_->eulerAngles.z > 180.0f){
                camera_node_->eulerAngles.z -= 360.0f;
            }
        }
        return true;
    }
    
    return false;
}


void CameraController::reset() {
    curr_speed_ = speed_change_info_.init_speed;
    curr_distance_ = 0.0f;
    curr_point_index_ = 0;
    
    camera_node_->position = bezier_curve_.controll_points[0];
    camera_node_->eulerAngles = eular_change_info_.start_angle;
}


void CameraController::showCurve() {
    for (auto& it : curve_points_) {
        PBRShader* cubeShader = new PBRShader(0.5f, 0.5f);
        Node* testNode = new Node();
        testNode->loadUnitCube();
        testNode->geometries[0]->setShader(cubeShader);
        testNode->scale = vec3(1);
        testNode->position = it;
        testNode->eulerAngles = vec3(0);
        show_curve_nodes_.push_back(testNode);
        Engine::main->addNode(testNode);
    }
}


void CameraController::hideCurve() {
    for (auto& it : show_curve_nodes_) {
        it->removeFromParentNode();
    }
}


void CameraController::printControlNode() {
    for (int i = 0; i < bezier_curve_.controll_points.size(); i++) {
        cout << "bezierCurve.controll_points.push_back(vec3(" << bezier_curve_.controll_points[i].x << ", " << bezier_curve_.controll_points[i].y << ", " <<  bezier_curve_.controll_points[i].z << "));" << endl;
    }
}
