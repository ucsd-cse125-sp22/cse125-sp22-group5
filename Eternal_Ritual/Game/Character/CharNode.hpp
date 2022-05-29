//
//  CharNode.hpp
//
//  Created by futian Zhang on 4/19/22.
//  Updated by Kangming Yu on 5/14/22.
//

#ifndef CharNode_hpp
#define CharNode_hpp

#include <vector>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"
#include "Game/Character/Hitbox.hpp"

#define MAXHP 1000
#define MAXMANA 1000
#define MAXMANAREGEN 4
#define ROLL_COST 200

namespace Bitmask {
enum Type {
    IDLE = 0x00000001,
    RUNNING = 0x00000002,
    WALKFWD = 0x00000004,
    WALKBCK = 0x00000008,
    WALKLEFT = 0x00000010,
    WALKRIGHT = 0x00000020,
    WALKFL = 0x00000040,
    WALKFR = 0x00000080,
    WALKBL = 0x00000100,
    WALKBR = 0x00000200,
    ROLL = 0x00000400,
    MAGIC_CAST_1 = 0x00000800,
    MAGIC_CAST_2 = 0x00001000,
    MAGIC_CAST_3 = 0x00002000,
    DRAGON_ATT = 0x00004000,
    DAMAGED = 0x00008000,
    DEAD = 0x00010000
};
}

namespace Direction {
enum Type{
    NONE = 0,
    FRONT = Bitmask::WALKFWD,
    BACK = Bitmask::WALKBCK,
    LEFT = Bitmask::WALKLEFT,
    RIGHT = Bitmask::WALKRIGHT,
    FRONTLEFT = Bitmask::WALKFL,
    FRONTRIGHT = Bitmask::WALKFR,
    BACKLEFT = Bitmask::WALKBL,
    BACKRIGHT = Bitmask::WALKBR
};
} // namespace Direction

namespace CharState {
enum Type{
    IDLE = 0,
    MOVING = 1,
    ROLLING = 2,
    COMBATING = 3,
    DAMAGED = 4,
    DEAD = 5
};
}



class CharNode final : public Node {
private:
    static bool loaded;
    static Node* metaModel;
    static Texture* bootsD;
    static Texture* bootsN;
    static Texture* bootsAO;
    static Texture* glovesD;
    static Texture* glovesN;
    static Texture* glovesAO;
    static Texture* bodyD;
    static Texture* bodyN;
    static Texture* bodyAO;
    static Texture* chestD;
    static Texture* chestN;
    static Texture* chestAO;
    static Texture* staffD;
    static Texture* staffN;
    static Texture* staffAO;
    static Texture* helmetD;
    static Texture* helmetN;
    static Texture* helmetAO;
    static Texture* eyeD;
    static Texture* headD;
    static Texture* headN;
    static Texture* headAO;
    static Texture* pantsD;
    static Texture* pantsN;
    static Texture* hairD;
    static Texture* hairBaseD;
    static AudioBuffer* footStep;
    static AudioBuffer* rollSound;
public:
    CharNode(glm::vec3 position);
    ~CharNode();
    Node* modelNode;
    void setModel(Node* model);
    glm::vec3 displacement;
    glm::vec3 acceleration;
    float health;
    float stamina;
    float stepAvailable;
    float mana;
    float manaRegen;
    Hitbox* hitbox;
    bool uninjurable;
    int currMagic;
    float scrollValue;
    std::vector<std::string> animatorNames;
    
    CameraNode* cameraNode;
    glm::vec3 characterTargetPosition;
    glm::vec3 characterTargetEulerAngles;
    glm::vec3 moveDirection;
    Direction::Type keyDirection;
    CharState::Type state;
    glm::vec3 cameraTargetEulerAngles;
    Node* controlNode;
    Node* headTop;
    UINode* uiNode;
    TextNode* nameNode;
    Node* generateBoneNode(std::string boneName);
    Node* rightHand;
    void setCamera(CameraNode* model);
    void setControl(Node* control);
    void setCharacterEularAngle(glm::vec3 eularAngle);
    void setCameraEularAngle(glm::vec3 eularAngle);
    void setCharacterPosition(glm::vec3 position);
    void setName(std::string name);
    void setUINode(UINode* uiNode);
    
    bool isLocked;
    bool refreshed;
    CharNode* target;
    void load();
    void lock(std::vector<CharNode*>& targets);
    void unlock();
    void toggleLock(std::vector<CharNode*>& enemies);
    glm::vec3 getLockAngle();
    void stopAndPlay(std::string name, float fade_in, float fade_out); // deprecated
    Animator* addAnimator(std::string name, std::string file);
    Animator* getAnimator(std::string name);
    void playAnimators(unsigned int mask, float fadeIn, float fadeOut = 0.0f);
    void stopAnimators(unsigned int mask, float fadeOut);
    CharNode* copy(glm::vec3 position);
    
    void moveCamera(glm::vec2 mouseTranslation);
    void moveFront();
    void moveBack();
    void moveLeft();
    void moveRight();
    void predictMoveTarget();
    void updatePosition();
    
    void genMana();
    std::vector<BaseMagic*> magics;
    void addMagics(BaseMagic* magic);
    BaseMagic* rmMagics();
    void castMagic();
    void chooseNextMagic();
    void chooseLastMagic();
    void scrollMagic(float acceleration);
    void setCurrMagic(int index);
    void roll();
    void receiveDamage(int damage);
};
#endif /* CharNode_hpp */
