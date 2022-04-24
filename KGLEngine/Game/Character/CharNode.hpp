//
//  CharNode.hpp
//  KGLEngine
//
//  Created by futian Zhang on 4/19/22.
//

#ifndef CharNode_hpp
#define CharNode_hpp

#include "../../KGLEngine/Engine.hpp"

class Geometry;
class Animator;
class Node;
class CameraNode;
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
class CharNode : public Node {
public:
    CharNode(vec3 position);
    ~CharNode();
    Node* modelNode;
    void setModel(Node* model);
    int health;
    int stamina;
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
};
#endif /* CharNode_hpp */