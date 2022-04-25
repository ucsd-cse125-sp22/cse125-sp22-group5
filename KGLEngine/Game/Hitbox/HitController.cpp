//
//  HitController.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#include "HitController.hpp"

BaseMagic* HitController::checkHit(){
    for (int i = 0; i < characters.size(); i++){
        if (characters[i]->uninjurable){
            continue;
        }
        for (int j = 0; j < magics.size(); j++){
            for (int k = 0; k < magics[j]->hits.size(); k++){
                if (characters[i]->hitbox->testHit(magics[j]->hits[k].start, magics[j]->hits[k].end)){
                    return magics[j];
                }
            }
        }
    }
    return NULL;
}
