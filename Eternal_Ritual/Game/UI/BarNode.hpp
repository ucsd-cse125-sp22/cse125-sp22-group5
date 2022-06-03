#ifndef BarNode_hpp
#define BarNode_hpp

#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"


class BarNode {
public:
    int id;
    Engine* engine;
    SpriteNode* bar;
    SpriteNode* fade;
    //Animation* ani;
    //Animation* fadeAni;
    UINode* baseNode;
    UINode* fadeBaseNode;
    UINode* background;
    float initValue;
    float curValue;
    bool barPlaying;
    bool fadePlaying;
public:
    BarNode(UINode* parentNode, float initValue, Texture* barTex, Texture* fadeTex, glm::vec2 barSize, glm::vec2 fadeSize, int id, bool left, Engine* e);
    ~BarNode() = default;
    void setPosition(glm::vec2 position);
    void update(float value);
};



#endif /* HPBarNode_hpp */
