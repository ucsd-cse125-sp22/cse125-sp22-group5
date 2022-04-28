//
//  Trajectory.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/27/22.
//

#ifndef Trajectory_hpp
#define Trajectory_hpp

#include "../../KGLEngine/Engine.hpp"
#include "../Character/CharNode.hpp"

class Trajectory final : public Node {
    Trajectory();
    ~Trajectory();
    
    bool canDamage;
    vec3 start;
    vec3 end;
    vector<Node*> damagedChar;
    int damage;
    
    void playAfter(int id, float time, std::function<void()> event);
    void tryDamageChar(CharNode* character);
};

#endif /* Trajectory_hpp */
