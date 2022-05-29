//
//  ButtonNode.cpp
//  KGLEngine
//
//  Created by Jackie Li on 4/26/22.
//

#include "Game/UI/ButtonNode.hpp"

ButtonNode::ButtonNode(UINode* parentNode,Font* font){
    
    normal = new Texture("/Resources/Game/UI/btn_back.png");
    glow = new Texture("/Resources/Game/UI/btn_glow_back.png");
    dark = new Texture("/Resources/Game/UI/btn_dark_back.png");

    background = new SpriteNode(UISizes::buttonSize);
    background->texture = normal;
    
    text = new TextNode(font, UISizes::buttonSize.y/3, UISizes::buttonSize.x,0.01f);
    text->setCenterVerticalAlignment();
    text->setCenterHorizontalAlignment();
    text->parentCoordinatePosition = glm::vec2(0.5,0.6);

    background->addChildNode(text);
    parentNode->addChildNode(background);
    
}

void ButtonNode::disable(bool disable){background->isDisabled = disable;}

void ButtonNode::setText(std::string t){
    text->text = t;
}

void ButtonNode::setPosition(glm::vec2 position){
    background->parentCoordinatePosition = position;
}

void ButtonNode::setScale(float i)
{
    background->scale = glm::vec2(i);
    text->scale = glm::vec2(i);
}

void ButtonNode::switchOn(){
    background->multiplyColor = glm::vec4(1.5);
}
void ButtonNode::switchOff(){
    background->multiplyColor = glm::vec4(0.5,0.5,0.5,1.0);
}

void ButtonNode::restore(){
    background->multiplyColor = glm::vec4(1);
}

bool ButtonNode::checkState(glm::vec2 mousePosition, Input* input){
    if(background->isDisabled){
        return false;
    }

    bool isReleased = input->wasKeyReleased(MOUSE_BUTTON_LEFT);

    if(background->checkSizeIncludesScreenPosition(mousePosition)){
        if(input->isPressingKey(MOUSE_BUTTON_LEFT)){
            background->texture = dark;
            return false;
        }else if(isReleased) {
            background->texture = normal;
            return true;
        }
        else {
            background->texture = glow;
            return false;
        }
    }else{
        background->texture = normal;
        return false;
        isReleased = false;
    }

}

