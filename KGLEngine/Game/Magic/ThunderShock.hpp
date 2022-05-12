//
//  ThunderShock.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/10/22.
//

#ifndef ThunderShock_hpp
#define ThunderShock_hpp

#include "../includes.hpp"

class ThunderShock : public DamageableMagic{
public:
    bool threwOut;
    bool canDamage;
    vector<Particle3DNode*> lightnings;
    Node* base;
    CharNode* caster;
    ThunderShock();
    ~ThunderShock();
    void explode();
    void hitWall() override {}
    void updateMagic() override {}
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
};
#endif /* ThunderShock_hpp */
