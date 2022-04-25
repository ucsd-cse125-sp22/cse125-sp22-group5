//
//  BurstStones.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/24/22.
//

#ifndef BurstStones_hpp
#define BurstStones_hpp

#include <stdio.h>

#include "BaseMagic.hpp"

class BurstStones : public BaseMagic{
    BurstStones(vec3 position, vec3 eularAngle);
    void updateMagic();
    void play();
    ~BurstStones();
};

#endif /* BurstStones_hpp */
