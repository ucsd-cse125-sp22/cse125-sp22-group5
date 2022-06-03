//
//  ButtonNode.hpp
//  KGLEngine
//
//  Created by Jackie Li on 4/26/22.
//

#ifndef ButtonNode_hpp
#define ButtonNode_hpp

#include <string>
#include <glm/glm.hpp>

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"


class SpriteNode;
class TextNode;
class UINode;
class Input;
class ButtonNode{
public:
    static AudioBuffer* hoverBuffer;
    static AudioBuffer* clickBuffer;
    SpriteNode* background;
    TextNode* text;
    Texture* normal;
    Texture* glow;
    Texture* dark;
    bool hover;
public:
    ButtonNode(UINode* partentNode,Font* font);
    ~ButtonNode() = default;
    void setText(std::string t);
    void setPosition(glm::vec2 position);
    void setScale(float i);
    bool checkState(glm::vec2 mousePosition, Input* input, bool isReleasd);
    void disable(bool disable);
    void setWinButton(std::string t);
};


#endif /* ButtonNode_hpp */
