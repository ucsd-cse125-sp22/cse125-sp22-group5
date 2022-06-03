//
//  ScatteredFire.hpp
//  Eternal_Ritual
//
//  Created by Zifan Zhang on 5/18/22.
//

#ifndef ScatteredFire_hpp
#define ScatteredFire_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"
#include "Game/Magic/FireBall.hpp"

class CharNode;
class Circle;

class ScatteredFire final : public DamageableMagic{
public:
    static bool loaded;
    static AudioBuffer* castSound;
    static ParticleNode* metaShiny;
    static ParticleNode* metaWhirl;

public:
    std::vector<FireBall*> balls;
    Node* ballNode;
    void load();
    ScatteredFire();
    ~ScatteredFire() override = default;
    void hitWall() override {}
    void updateMagic() override;
    void play(CharNode* character, int seed) override;
    void tryDamage(CharNode* character) override;
};

#endif /* ScatteredFire_hpp */
