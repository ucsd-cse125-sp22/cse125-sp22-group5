//
//  HittableObject.hpp
//
//  Created by Kangming Yu on 5/11/22.
//

#ifndef HittableObject_hpp
#define HittableObject_hpp

#include <glm/glm.hpp>


class HittableObject {
public:
    glm::vec3 hit_point() const;
    glm::vec3 normal() const;
    float hit_time() const;
    virtual bool hitTest(const glm::vec3& start, const glm::vec3& end) = 0;
    virtual ~HittableObject() {}
    
protected:
    glm::vec3 hit_point_;
    glm::vec3 normal_;
    float hit_time_;
};


#endif /* HittableObject_hpp */
