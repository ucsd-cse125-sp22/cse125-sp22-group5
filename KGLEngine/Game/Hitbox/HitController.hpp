//
//  HitController.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef HitController_hpp
#define HitController_hpp

#include "../includes.hpp"

class CharNode;
class DamageableMagic;
class HitController{
public:
    vector<CharNode*> characters;
    vector<DamageableMagic*> magics;
    
    void checkHit();
};

#endif /* HitController_hpp */
