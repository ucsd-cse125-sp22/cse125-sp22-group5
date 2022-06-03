//
//  HPBarNode.hpp
//  KGLEngine
//
//  Created by Jackie Li on 4/27/22.
//

#ifndef HPBarNode_hpp
#define HPBarNode_hpp

#include <string>
#include <glm/glm.hpp>
#include "KGLEngine/Engine.hpp"
#include "Game/Character/CharNode.hpp"
#include "Game/UI/Constant.hpp"

class HPBarNode{
public:
    Engine* engine;
    UINode* baseNode;
    SpriteNode* background;
    SpriteNode* HpBar;
    SpriteNode* icon;
    TextNode* name;
    float initHp;
    //float curHp;
    CharNode* character;
public:
    HPBarNode(Engine* e, Font* font, bool isRed, CharNode* character);
    ~HPBarNode() = default;
    void update(float curHp);
};



#endif /* HPBarNode_hpp */
