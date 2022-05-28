//
//  HitController.cpp
//
//  Created by futian Zhang on 4/23/22.
//  Updated by Kangming Yu on 5/14/22.
//

#include "Game/Character/HitController.hpp"


void HitController::addMagic(DamageableMagic* damageableMagic) {
    magics_.push_back(damageableMagic);
}

void HitController::addCharacter(CharNode* charNode) {
    characters_.push_back(charNode);
}

void HitController::checkHit(){
    for (int i = 0; i < characters_.size(); i++){
        if (characters_[i]->uninjurable){
            continue;
        }
        for (int j = 0; j < magics_.size(); j++){
            magics_[j]->tryDamage(characters_[i]);
        }
    }
}

