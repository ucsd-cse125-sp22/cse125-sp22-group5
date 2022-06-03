//
//  Storm.hpp
//  Eternal_Ritual_Offline
//
//  Created by Zifan Zhang on 5/24/22.
//

#ifndef Storm_hpp
#define Storm_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"


class CharNode;


class Storm final : public DamageableMagic{
public:
    static bool loaded;
    static ParticleNode* metaCloud;
    static ParticleNode* metaHail;
    static ParticleNode* metaLightning;
    static ParticleNode* metaDust;
    static LightNode* metaLight;
    static AudioBuffer* stormSound;
public:
    glm::vec3 velocity;
    float radius;
    bool threw;
    bool canDamage;
    bool explodeDamage;
    Node* spinning;
    Node* fastSpin;
    ParticleNode* cloud;
    ParticleNode* hail;
    ParticleNode* lightning;
    ParticleNode* dust;
    LightNode* light;
    void load();
    Storm();
    ~Storm() override = default;
    void explode();
    void updateMagic() override;
    void play(CharNode* character, int seed) override;
    void tryDamage(CharNode* character) override;
    void setThrew();
    void hitWall() override;
};

#endif /* Storm_hpp */
