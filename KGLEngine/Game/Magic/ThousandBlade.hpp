//
//  ThousandBlade.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/23/22.
//

#ifndef ThousandBlade_hpp
#define ThousandBlade_hpp

#include "../includes.hpp"

class ThousandBlade : public DamageableMagic{
public:
    ThousandBlade(vec3 position, vec3 eularAngle);
    ~ThousandBlade();
    void updateMagic() override;
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override {}
};

#endif /* ThousandBlade_hpp */