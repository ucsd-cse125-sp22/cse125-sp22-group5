//
//  ButtonNode.cpp
//  KGLEngine
//
//  Created by Jackie Li on 4/26/22.
//

#include "Game/UI/ButtonNode.hpp"
#include <iostream>

ButtonNode::ButtonNode(UINode* parentNode, Font* font){
    
    normal = new Texture("/Resources/Game/UI/btn_back.png");
    glow = new Texture("/Resources/Game/UI/btn_glow_back.png");
    dark = new Texture("/Resources/Game/UI/btn_dark_back.png");

    background = new SpriteNode(UISizes::buttonSize);
    background->texture = normal;
    
    background->scale = glm::vec2(0.8f);
    
    text = new TextNode(font, UISizes::buttonSize.y * 0.4f, UISizes::buttonSize.x, 0.01f);
    text->setCenterVerticalAlignment();
    text->setCenterHorizontalAlignment();
    text->parentCoordinatePosition = glm::vec2(0.5f, 0.6f);

    background->addChildNode(text);
    parentNode->addChildNode(background);
    Engine::main->loadMusic("click button", new AudioBuffer("/Resources/Game/Sound/Skill_Unlock_02.wav"));
    Engine::main->loadMusic("hover button", new AudioBuffer("/Resources/Game/Sound/Nail 6_4.wav"));
    hover = false;
    
}

void ButtonNode::disable(bool disable){background->isDisabled = disable;}

void ButtonNode::setWinButton(std::string t)
{
    normal = new Texture("/Resources/Game/UI/win_btn_back.png");
    glow = new Texture("/Resources/Game/UI/win_btn_glow_back.png");
    dark = new Texture("/Resources/Game/UI/win_btn_dark_back.png");
    text->text = t;
    background->scale = glm::vec2(0.7);
    text->scale = glm::vec2(1.3);
}

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

bool ButtonNode::checkState(glm::vec2 mousePosition, Input* input, bool isReleasd){
    if(background->isDisabled){
        return false;
    }

    if(background->checkSizeIncludesScreenPosition(mousePosition)){
        std::cout << text->text  + ": " << isReleasd << std::endl;
        if(input->isPressingKey(MOUSE_BUTTON_LEFT)){
            background->texture = dark;
            return false;
        }else if(isReleasd) {
            background->texture = normal;
            Engine::main->playMusic("click button");
            return true;
        }
        else {
            background->texture = glow;
            if (hover) {
                Engine::main->playMusic("hover button");
                hover = false;
            }
            return false;
        }
    }else{
        hover = true;
        background->texture = normal;
        return false;
    }

}

