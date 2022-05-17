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
    static HitController* Instance() {
        if (hit_controller_ == nullptr) {
            hit_controller_ = new HitController();
        }
        return hit_controller_;
    }

    static void Destructor() {
        if (hit_controller_ != nullptr) {
            delete hit_controller_;
            hit_controller_ = nullptr;
        }
    }
    
    void addMagic(DamageableMagic* damageableMagic);
    void addCharacter(CharNode* charNode);
    void checkHit();
    
private:
    // Singleton pattern
    static HitController* hit_controller_;
    HitController(){}
    ~HitController(){}
    
    std::vector<CharNode*> characters_;
    std::vector<DamageableMagic*> magics_;
};

#endif /* HitController_hpp */
