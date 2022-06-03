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
        bool is_clockwise_x = false;
        bool is_clockwise_y = false;
        bool is_clockwise_z = false;
    };
    
    struct SpeedChangeInfo {
        float move_af;
        float max_speed;
        float init_speed = 0.0f;
        float end_speed = 0.0f;
    };
    
    CameraController(CameraNode* cameraNode, const BezierCurve& bezierCurve, const EularChangeInfo& eularChangeInfo, const SpeedChangeInfo& speedChangeInfo);
    ~CameraController() = default;
    bool moveCamera();
    void reset();
    
    void showCurve();
    void hideCurve();
    void printControlNode();
    
public:
    glm::vec3 cameraTargetPosition = glm::vec3(0.0f);
    glm::vec3 cameraTargetRotation = glm::vec3(0.0f);
    CameraNode* camera_node_;
    
    BezierCurve bezier_curve_;
    EularChangeInfo eular_change_info_;
    SpeedChangeInfo speed_change_info_;
    
    float curr_speed_ = 0.0f;
    float curr_distance_ = 0.0f;
    
    int acel_point_index_;
    int decel_point_index_;
    int curr_point_index_ = 0;
    std::vector<glm::vec3> curve_points_;
    size_t curve_points_size_;
    
    glm::vec3 per_angle_;
    
    std::vector<Node*> show_curve_nodes_;
};

#endif /* CameraController_hpp */
