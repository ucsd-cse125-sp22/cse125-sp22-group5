//
//  HitController.hpp
//
//  Created by futian Zhang on 4/23/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef HitController_hpp
#define HitController_hpp

#include <vector>

#include "Game/Magic/BaseMagic.hpp"
#include "Game/Character/CharNode.hpp"


class HitController final {
public:
    HitController(){}
    ~HitController(){}
    void addMagic(DamageableMagic* damageableMagic);
    void addCharacter(CharNode* charNode);
    void checkHit();
    
public:
    std::vector<CharNode*> characters_;
    std::vector<DamageableMagic*> magics_;
};

#endif /* HitController_hpp */
