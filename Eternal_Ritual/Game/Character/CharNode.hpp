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


namespace Direction {

enum Type{
    NONE = 0,
    FRONT = 1,
    BACK = 2,
    LEFT = 3,
    RIGHT = 4,
    FRONTLEFT = 5,
    FRONTRIGHT = 6,
    BACKLEFT = 7,
    BACKRIGHT = 8
};

} // namespace Direction

class CharNode final : public Node {
public:
    CharNode(glm::vec3 position);
    ~CharNode();
    Node* modelNode;
    void setModel(Node* model);
    int health;
    int stamina;
    Hitbox* hitbox;
    bool uninjurable;
    std::vector<std::string> animatorNames;
    
    CameraNode* cameraNode;
    glm::vec3 characterTargetPosition;
    glm::vec3 characterTargetEulerAngles;
    glm::vec3 moveDirection;
    Direction::Type keyDirection;
    glm::vec3 cameraTargetEulerAngles;
    Node* controlNode;
    Node* headTop;
    UINode* uiNode;
    TextNode* nameNode;
    Node* generateBoneNode(std::string boneName);
    Node* rightHand;
    void setCamera(CameraNode* model);
    void setControl(Node* control);
    void setEularAngle(glm::vec3 eularAngle);
    void setName(std::string name);
    void setUINode(UINode* uiNode);
    
    bool isLocked;
    bool refreshed;
    CharNode* target;
    void lock(std::vector<CharNode*>& targets);
    void unlock();
    void toggleLock(std::vector<CharNode*>& enemies);
    glm::vec3 getLockAngle();
    void stopAndPlay(std::string name, float fade_in, float fade_out);
    void addAnimator(std::string name, std::string file);
    CharNode* copy(glm::vec3 position);
    void moveCamera(glm::vec2 mouseTranslation);
    void moveFront();
    void moveBack();
    void moveLeft();
    void moveRight();
    void predictMoveTarget();
    void updatePosition();
    
    bool allowAction;
    
    
    std::unordered_map<Magic::Type, BaseMagic*> magics;
    void addMagics(Magic::Type magicKey, BaseMagic* magic);
    BaseMagic* rmMagics(Magic::Type magicKey);
    void castMagic(Magic::Type magicKey);
    void receiveDamage(int damage);
};
#endif /* CharNode_hpp */
