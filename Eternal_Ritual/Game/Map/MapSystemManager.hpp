//
//  MapSystemManager.hpp
//
//  Created by Zifan Zhang on 4/22/22.
//  Updated by Kangming Yu on 5/11/22.
//

#ifndef MapSystemManager_hpp
#define MapSystemManager_hpp

#include <vector>
#include <glm/glm.hpp>

#include "Game/Map/MapBoxObject.hpp"

#define NUM_WIDTH_GRIDS 30
#define NUM_LENGTH_GRIDS 30


struct HitInfo {
    glm::vec3 hit_point = glm::vec3(0);
    glm::vec3 normal = glm::vec3(0);
    MapBoxObject* hit_box = nullptr;
};


class MapSystemManager final {
public:
    static MapSystemManager* Instance() {
        if (map_system_manager_ == nullptr) {
            map_system_manager_ = new MapSystemManager();
        }
        return map_system_manager_;
    }

    static void Destructor() {
        if (map_system_manager_ != nullptr) {
            delete map_system_manager_;
            map_system_manager_ = nullptr;
        }
    }
    
    bool hitTest(const glm::vec3& start, const glm::vec3& end, HitInfo& hitInfo);
    bool gridsHitTest(const glm::vec3& start, const glm::vec3& end, HitInfo& hitInfo);
    void addMapBox(MapBoxObject* mapBox);
    void updateGrids();
    
public:
    // Singleton pattern
    static MapSystemManager* map_system_manager_;
    MapSystemManager();
    ~MapSystemManager() {}
    
    std::vector<MapBoxObject*> boxes_;
    
    glm::vec3 min_xyz_;
    glm::vec3 max_xyz_;

    float per_grid_width_;
    float per_grid_length_;
    int num_grids_ = NUM_WIDTH_GRIDS * NUM_LENGTH_GRIDS;
    std::vector<MapBoxObject*> grids_[NUM_WIDTH_GRIDS * NUM_LENGTH_GRIDS];
};

#endif /* MapSystemManager_hpp */
