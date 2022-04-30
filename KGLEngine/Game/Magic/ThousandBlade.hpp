//
//  ThousandBlade.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef ThousandBlade_hpp
#define ThousandBlade_hpp

#include "../includes.hpp"

class ThousandBlade : public BaseMagic{
public:
    ThousandBlade(vec3 position, vec3 eularAngle);
    ~ThousandBlade();
    void updateMagic();
    void play(vec3 position, vec3 euler);
};

#endif /* ThousandBlade_hpp */
