//
//  CharNode.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/19/22.
//

#ifndef CharNode_hpp
#define CharNode_hpp

#include "../includes.hpp"

class Geometry;
class Animator;
class Node;
class CameraNode;
class Hitbox;
class BaseMagic;
enum direction{
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
class CharNode final : public Node {
public:
    CharNode(vec3 position);
    ~CharNode();
    Node* modelNode;
    void setModel(Node* model);
    int health;
    int stamina;
    Hitbox* hitbox;
    bool uninjurable;
    vector<string> animatorNames;
    
    CameraNode* cameraNode;
    vec3 characterTargetPosition;
    vec3 characterTargetEulerAngles;
    vec3 moveDirection;
    direction keyDirection;
    vec3 cameraTargetEulerAngles;
    Node* controlNode;
    Node* headTop;
    UINode* uiNode;
    TextNode* nameNode;
    Node* generateBoneNode(string boneName);
    
    Node* rightHand;
    
    void setCamera(CameraNode* model);
    void setControl(Node* control);
    void setEularAngle(vec3 eularAngle);
    void setName(string name);
    void setUINode(UINode* uiNode);
    
    bool isLocked;
    bool refreshed;
    CharNode* target;
    void lock(vector<CharNode*>& targets);
    void unlock();
    void toggleLock(vector<CharNode*>& enemies);
    vec3 getLockAngle();
    void stopAndPlay(string name, float fade_in, float fade_out);
    void addAnimator(string name, string file);
    CharNode* copy(vec3 position);
    void moveCamera(vec2 mouseTranslation);
    void moveFront();
    void moveBack();
    void moveLeft();
    void moveRight();
    void predictMoveTarget();
    void updatePosition();
    
    bool allowAction;
    
    map<int, BaseMagic*> keyBind;
    void addMagics(BaseMagic* magic, int key);
    void castMagic(int key);
    void receiveDamage(int damage);
};
#endif /* CharNode_hpp */
