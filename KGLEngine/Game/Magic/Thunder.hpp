//
//  Thunder.hpp
//  KGLEngine
//
//  Created by Zifan Zhang on 5/10/22.
//

#ifndef Thunder_hpp
#define Thunder_hpp

#include "../includes.hpp"
#include "./ThunderShock.hpp"

class Thunder : public DamageableMagic{
public:
    bool threwOut;
    bool canDamage;
    vector<ThunderShock*> thunders;
    LightNode* light;
    Animation* createFireball;
    Thunder();
    ~Thunder();
    void playNextThunder(int index);
    void hitWall() override {}
    void updateMagic() override {}
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
};
#endif /* Thunder_hpp */
