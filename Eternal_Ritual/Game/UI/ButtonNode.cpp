//
//  ButtonNode.cpp
//  KGLEngine
//
//  Created by Jackie Li on 4/26/22.
//

#include "Game/UI/ButtonNode.hpp"

#include "Game/UI/Constant.hpp"


ButtonNode::ButtonNode(UINode* parentNode,Font* font, glm::vec2 size){
    Texture* borderTexture = new Texture("/Resources/Game/UI/Button_RL_Border.png");
    
    background = new SpriteNode(size);
    background->texture = new Texture("/Resources/Game/UI/Button_RL_Background.png");
    background->multiplyColor = Color::ButtonBackground;
    
    overlay = new SpriteNode(size*0.96f);
    overlay->texture = new Texture("/Resources/Game/UI/Button_RL_Overlay.png");
    background->addChildNode(overlay);
    
    borderL = new SpriteNode(glm::vec2(size.x* 0.3,size.y*0.96));
    borderL->texture = borderTexture;
    borderL->position= glm::vec2(-0.385*size.x,0.0f);
    background->addChildNode(borderL);
    
    borderR = new SpriteNode(glm::vec2(-size.x* 0.3,size.y*0.96));
    borderR->texture = borderTexture;
    borderR->position= glm::vec2(0.385*size.x,0.0f);
    background->addChildNode(borderR);
    
    glow = new SpriteNode(size);
    glow->alpha = 0.1;
    glow->texture = new Texture("/Resources/Game/UI/Button_RL_Hover.png");
    glow->setAdditive();
    glow->isDisabled = true;
    background->addChildNode(glow);
    
    text = new TextNode(font, 0.45f, size.x * 10 ,0.01f);
    text->scale = glm::vec2(glm::min(background->size.x,background->size.y));
    text->setCenterVerticalAlignment();
    text->setCenterHorizontalAlignment();
    text->text = "Button";
    text->position = glm::vec2(0.0f,0.09f*size.y);
    background->addChildNode(text);
    
    parentNode->addChildNode(background);
    
}

void ButtonNode::disable(bool disable){background->isDisabled = disable;}

void ButtonNode::setText(std::string t){
    text->text = t;
}

void ButtonNode::setSize(glm::vec2 size){
    background->size = size;
    text->scale = glm::vec2(glm::min(background->size.x,background->size.y));
}

void ButtonNode::setPosition(glm::vec2 position){
    background->screenPosition = position;
}

void ButtonNode::switchOn(){
    glow->isDisabled = false;
    background->multiplyColor = Color::ButtonBackground;
}
void ButtonNode::switchOff(){background->multiplyColor = Color::ButtonBackgroundOff;}

void ButtonNode::restore(){
    glow->isDisabled = true;
    background->multiplyColor = Color::ButtonBackground;
}

bool ButtonNode::checkState(glm::vec2 mousePosition, Input* input){
    if(background->isDisabled){
        return false;
    }
    if(background->checkSizeIncludesScreenPosition(mousePosition)){
        if(input->isPressingKey(MOUSE_BUTTON_LEFT)){
            switchOff();
            return false;
        }else{
            switchOn();
            if(input->wasKeyReleased(MOUSE_BUTTON_LEFT)){
                return true;
            }
            return false;
        }
    }else{
        restore();
        return false;
    }
}

