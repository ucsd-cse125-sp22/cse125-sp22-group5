//
//  CharacterController.hpp
//
//  Created by Kangming Yu on 6/3/22.
//

#ifndef CharacterController_hpp
#define CharacterController_hpp

#include <vector>
#include <glm/glm.hpp>

#include "Game/Character/CharNode.hpp"
#include "KGLEngine/Engine.hpp"


class CharacterController final {
public:
    struct BezierCurve {
        std::vector<glm::vec3> controll_points;
        int level_of_detail = 5;
    };
    
    CharacterController(CharNode* characterNode, const BezierCurve& bezierCurve);
    ~CharacterController() = default;
    bool moveCharacter();
    void reset();
    
public:
    CharNode* character_node_;
    
    BezierCurve bezier_curve_;
    
    int curr_point_index_ = 0;
    std::vector<glm::vec3> curve_points_;
    size_t curve_points_size_;
};

#endif /* CharacterController_hpp */
