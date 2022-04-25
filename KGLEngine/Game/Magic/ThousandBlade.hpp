//
//  ThousandBlade.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef ThousandBlade_hpp
#define ThousandBlade_hpp

#include "BaseMagic.hpp"

class ThousandBlade : public BaseMagic{
    ThousandBlade(vec3 position, vec3 eularAngle);
    void updateMagic();
    void play();
    ~ThousandBlade();
};

#endif /* ThousandBlade_hpp */
