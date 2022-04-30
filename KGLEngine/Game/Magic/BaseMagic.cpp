//
//  BaseMagic.cpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#include "BaseMagic.hpp"

void BaseMagic::tryDamage(CharNode* character){
    if (this->start){
        for (int i = 0; i < this->projectiles.size(); i++){
            this->projectiles[i]->tryDamageChar(character);
        }
    }
}
