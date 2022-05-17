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

#define NUM_GRIDS 9


struct HitInfo {
    glm::vec3 hit_point;
    glm::vec3 normal;
    MapBoxObject* hit_box;
};


class MapSystemManager final {
public:
    static MapSystemManager* Instance() {
        if (mapSystemManager == nullptr) {
            mapSystemManager = new MapSystemManager();
        }
        return mapSystemManager;
    }

    static void Destructor() {
        if (mapSystemManager != nullptr) {
            delete mapSystemManager;
            mapSystemManager = nullptr;
        }
    }
    
    bool hitTest(const glm::vec3& start, const glm::vec3& end, HitInfo& hitInfo);
    bool gridsHitTest(const glm::vec3& start, const glm::vec3& end, HitInfo& hitInfo);
    void addMapBox(MapBoxObject* mapBox);
    void updateGrids();
    
private:
    // Singleton pattern
    static MapSystemManager* mapSystemManager;
    MapSystemManager();
    ~MapSystemManager(){};
    
    std::vector<MapBoxObject*> boxes_;
    
    glm::vec3 min_xyz_;
    glm::vec3 max_xyz_;

    float per_grid_width_;
    float per_grid_length_;
    std::vector<MapBoxObject*> grids_[NUM_GRIDS];
};

#endif /* MapSystemManager_hpp */
