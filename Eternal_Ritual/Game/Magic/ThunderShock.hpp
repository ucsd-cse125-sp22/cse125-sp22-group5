//
//  ThunderShock.hpp
//
//  Created by Zifan Zhang on 5/10/22.
//  Updated by Kangming Yu on 5/16/22.
//

#ifndef ThunderShock_hpp
#define ThunderShock_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"

class CharNode;


class ThunderShock final : public DamageableMagic{
private:
    static bool loaded;
    static Particle3DNode* metaLightning;
    static Particle3DNode* metaBase;
    static LightNode* metaLight;
    static AudioBuffer* electricImpact;
public:
    bool threwOut;
    bool canDamage;
    std::vector<Particle3DNode*> lightnings;
    Particle3DNode* base;
    LightNode* light;
    void load();
    ThunderShock();
    ~ThunderShock() override = default;
    void explode();
    void hitWall() override {}
    void updateMagic() override {}
    void play(CharNode* character, int seed) override;
    void tryDamage(CharNode* character) override;
};
#endif /* ThunderShock_hpp */
