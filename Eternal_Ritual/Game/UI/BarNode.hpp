#ifndef BarNode_hpp
#define BarNode_hpp

#include <stdio.h>
#include "KGLEngine/Engine.hpp"

class BarNode {
protected:
    int id;
    SpriteNode* bar;
    SpriteNode* fade;
    Animation* ani;
    Animation* fadeAni;
    UINode* baseNode;
    UINode* fadeBaseNode;
    UINode* background;
    float initValue;
    float curValue;
public:
    BarNode(UINode* parentNode, float initValue, Texture* barTex, Texture* fadeTex, glm::vec2 barSize, glm::vec2 fadeSize, int id, bool left);
    ~BarNode() = default;
    void setPosition(glm::vec2 position);
    void update(float value, Engine* engine);
};



#endif /* HPBarNode_hpp */
