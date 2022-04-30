//
//  HitController.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#include "HitController.hpp"

void HitController::checkHit(){
    for (int i = 0; i < characters.size(); i++){
        if (characters[i]->uninjurable){
            continue;
        }
        for (int j = 0; j < magics.size(); j++){
            magics[j]->tryDamage(characters[i]);
        }
    }
}
