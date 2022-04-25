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
            if (magics[j]->start){
                for (int k = 0; k < magics[j]->hits.size(); k++){
                    if (magics[j]->hits[k].canDamage && find(magics[j]->hits[k].damagedChar.begin(),
                        magics[j]->hits[k].damagedChar.end(),
                        characters[i]) == magics[j]->hits[k].damagedChar.end() && characters[i]->hitbox->testHit(magics[j]->hits[k].start, magics[j]->hits[k].end)){
                        characters[i]->receiveDamage(magics[j]->damage);
                        magics[j]->hits[k].damagedChar.push_back(characters[i]);
                    }
                }
            }
        }
    }
}
