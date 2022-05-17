//
//  Thunder.hpp
//
//  Created by Zifan Zhang on 5/10/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef Thunder_hpp
#define Thunder_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"
#include "Game/Magic/ThunderShock.hpp"

class CharNode;


class Thunder final : public DamageableMagic{
public:
    bool threwOut;
    bool canDamage;
    std::vector<ThunderShock*> thunders;
    LightNode* light;
    Animation* createFireball;
    Thunder();
    ~Thunder() override = default;
    void playNextThunder(int index);
    void hitWall() override {}
    void updateMagic() override {}
    void play(CharNode* character) override;
    void tryDamage(CharNode* character) override;
};
#endif /* Thunder_hpp */
