//
//  ButtonNode.hpp
//  KGLEngine
//
//  Created by Jackie Li on 4/26/22.
//

#ifndef ButtonNode_hpp
#define ButtonNode_hpp

#include <stdio.h>
#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"

class SpriteNode;
class TextNode;
class UINode;
class Input;
class ButtonNode{
protected:
    SpriteNode* background;
    SpriteNode* glow;
    SpriteNode* overlay;
    SpriteNode* borderL;
    SpriteNode* borderR;
    TextNode* text;
public:
    ButtonNode(UINode* partentNode,Font* font, glm::vec2 size);
    ~ButtonNode() = default;
    void setText(std::string t);
    void switchOn();
    void switchOff();
    void restore();
    bool isHovered();
    bool isClicked();
    void setPosition(glm::vec2 position);
    void setSize(glm::vec2 size);
    bool checkState(glm::vec2 mousePosition, Input* input);
    void disable(bool disable);
};


#endif /* ButtonNode_hpp */
