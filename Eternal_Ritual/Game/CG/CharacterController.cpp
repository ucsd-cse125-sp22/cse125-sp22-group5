//
//  CharacterController.cpp
//
//  Created by Kangming Yu on 6/3/22.
//

#include "Game/CG/CharacterController.hpp"

using namespace std;
using namespace glm;

CharacterController::CharacterController(CharNode* characterNode, const BezierCurve& bezierCurve) : character_node_(characterNode), bezier_curve_(bezierCurve) {
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
}

bool CharacterController::moveCharacter() {
    if (curr_point_index_ == curve_points_size_) {
        return false;
    }
    character_node_->characterTargetPosition = curve_points_[curr_point_index_++];
    character_node_->isLocked = true;
    character_node_->state = CharState::MOVING;
    return true;
}
