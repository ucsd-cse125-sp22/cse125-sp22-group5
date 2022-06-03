//
//  MapBoxObject.hpp
//
//  Created by Zifan Zhang on 4/22/22.
//  Updated by Kangming Yu on 5/11/22.
//

#ifndef MapBoxObject_hpp
#define MapBoxObject_hpp

#include <glm/glm.hpp>

#include "Game/Map/HittableObject.hpp"

namespace Map {
enum Type {
    WALL = 1,
    DOOR = 2,
    ELEVATOR = 4,
    AIR = 8
};
}


class MapBoxObject final : public HittableObject {
public:
    MapBoxObject(unsigned int boxType, glm::vec3& boxSize, glm::vec3& boxPosition, glm::vec3& boxEulerAngles);
    bool hitTest(const glm::vec3& start, const glm::vec3& end) override;
    glm::vec3 min_xyz() const;
    glm::vec3 max_xyz() const;
    glm::vec3 position() const;
    unsigned int type() {return type_;}
    
private:
    void updateTransMtx();
    void updateMostXYZ();
    /*
     type 0: normal box
     type 1: metal door
     type 2: elevator floor
     type 3: air wall
     */
    unsigned int type_;
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec3 euler_angles_;
    
    glm::vec3 min_xyz_;
    glm::vec3 max_xyz_;
    
    glm::mat4 trans_mtx_;
    glm::mat4 inv_trans_mtx_;
    glm::mat3 normal_inv_trans_mtx_;
};

#endif /* MapBoxObject_hpp */
