//
//  HitController.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef HitController_hpp
#define HitController_hpp

#include "Hitbox.hpp"
#include "../../KGLEngine/Engine.hpp"
#include "../Magic/BaseMagic.hpp"
#include "../Character/CharNode.hpp"

class HitController{
public:
    vector<CharNode*> characters;
    vector<BaseMagic*> magics;
    
    void checkHit();
};

#endif /* HitController_hpp */
