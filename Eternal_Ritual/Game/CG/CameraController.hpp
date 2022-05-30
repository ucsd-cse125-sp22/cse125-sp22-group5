//
//  CameraController.hpp
//
//  Created by Kangming Yu on 5/29/22.
//

#ifndef CameraController_hpp
#define CameraController_hpp

#include <vector>
#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"


class CameraController final {
public:
    struct BezierCurve {
        std::vector<glm::vec3> controll_points;
        int level_of_detail = 5;
    };

    struct EularChangeInfo {
        glm::vec3 start_angle;
        glm::vec3 end_angle;
        bool is_clockwise = false;
    };
    
    CameraController(CameraNode* cameraNode, const BezierCurve& bezierCurve, const EularChangeInfo& eularChangeInfo, float moveAf, float maxSpeed);
    ~CameraController() = default;
    bool moveCamera();
    void reset();
    
public:
    CameraNode* camera_node_;
    
    BezierCurve bezier_curve_;
    EularChangeInfo eular_change_info_;
    
    float move_af_;
    float max_speed_;
    float curr_speed_ = 0.0f;
    float curr_distance_ = 0.0f;
    
    int acel_point_index_;
    int decel_point_index_;
    int curr_point_index_ = 0;
    std::vector<glm::vec3> curve_points_;
    size_t curve_points_size_;
    
    glm::vec3 per_angle_;
};

#endif /* CameraController_hpp */
