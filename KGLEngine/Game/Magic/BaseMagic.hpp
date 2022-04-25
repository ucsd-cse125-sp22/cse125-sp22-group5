//
//  BaseMagic.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef BaseMagic_hpp
#define BaseMagic_hpp

#include "../../KGLEngine/Engine.hpp"

struct hitLine{
    vec3 start;
    vec3 end;
};
class BaseMagic: public Node{
public:
    vector<hitLine> hits;
    float damage;
    virtual void play()=0;
    virtual void updateMagic()=0;
};

#endif /* BaseMagic_hpp */
