//
//  Flame.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/11/22.
//

#ifndef Flame_hpp
#define Flame_hpp

#include "../includes.hpp"

class Flame : public DamageableMagic{
public:
    bool canDamage;
    ParticleNode* flame;
    Flame();
    ~Flame();
    void updateMagic() override {}
    void play(CharNode* character) override;
    void hitWall() override {}
    void tryDamage(CharNode* character) override;
};
#endif /* Flame_hpp */
