//
//  HPBarNode.cpp
//  KGLEngine
//
//  Created by Jackie Li on 4/27/22.
//

#include "Game/UI/HPBarNode.hpp"

#include "Game/UI/Constant.hpp"


int HPBarNode::id = 0;

HPBarNode::HPBarNode(UINode* parentNode,Font* font, float length,bool isEnemy,float initHp, float initMp,std::string playerName){
    
    glm::vec2 size = glm::vec2(length,length * 0.15);
    
    background = new SpriteNode(size);
    background->texture = new Texture("/Resources/Game/UI/transparent.png");

    Texture* backTexture = new Texture("/Resources/Game/UI/Nameplate_Background.png");
    Texture* barTexture = new Texture("/Resources/Game/UI/Nameplate_Bar_Primary.png");
    
    player = new TextNode(font, 0.45f, size.x * 10 ,0.01f);
    player->scale = glm::vec2(size.y);
    player->setLeftHorizontalAlignment();
    player->position = glm::vec2(-size.x*0.35,-size.y*0.5)
    ;    player->text = playerName;
    background->addChildNode(player);
    
    HpBar = new SpriteNode(size);
    HpBar->texture = backTexture;
    background->addChildNode(HpBar);
    
    MpBar = new SpriteNode(glm::vec2(size.x*0.85f,size.y*0.2));
    MpBar->texture = backTexture;
    MpBar->position = glm::vec2(-size.x*0.06f,size.y*0.46);
    background->addChildNode(MpBar);
    
    
    HpFadeNode = new UINode();
    HpFadeNode->parentCoordinatePosition= glm::vec2(0.0,0.5);
    HpBar->addChildNode(HpFadeNode);
    
    HpNode = new UINode();
    HpNode->parentCoordinatePosition= glm::vec2(0.0,0.5);
    HpBar->addChildNode(HpNode);
    
    MpNode = new UINode();
    MpNode->parentCoordinatePosition= glm::vec2(0.0,0.5);
    MpBar->addChildNode(MpNode);
    
    HpFade = new SpriteNode(glm::vec2(HpBar->size.x,HpBar->size.y * 0.75));
    HpFade->texture = barTexture;
    HpFade->alpha = 0.75;
    HpFade->position = glm::vec2(HpFade->size.x*0.5f,0.0);
    
    HpValue = new SpriteNode(glm::vec2(HpBar->size.x,HpBar->size.y * 0.75));
    HpValue->texture = barTexture;
    HpValue->multiplyColor = Color::Hp;
    HpValue->position = glm::vec2(HpValue->size.x*0.5f,0.0);
    
    MpValue = new SpriteNode(glm::vec2(MpBar->size.x,MpBar->size.y * 0.75));
    MpValue->texture = barTexture;
    MpValue->multiplyColor = Color::Mp;
    MpValue->position = glm::vec2(MpValue->size.x*0.5f,0.0);
    
    HpFadeNode->addChildNode(HpFade);
    HpNode->addChildNode(HpValue);
    MpNode->addChildNode(MpValue);
    
    
    icon = new SpriteNode(glm::vec2(size.y *1.5));
    icon->texture = new Texture("/Resources/Game/UI/Nameplate_LevelFrame.png");
    icon->position = glm::vec2(-size.x*0.45f,0.0);
    background->addChildNode(icon);
    
    Enemy = new SpriteNode(glm::vec2(size.y));
    Enemy->texture = new Texture("/Resources/Game/UI/Skull.png");
    icon->addChildNode(Enemy);
    
    if(!isEnemy){
        Enemy->multiplyColor = glm::vec4(0.1,0.1,3.0,1.0);
    }
    
    hpAni = new Animation("hpAni"+std::to_string(id),1);
    hpAni->setEaseOutTimingMode();
    hpFadeAni = new Animation("hpFadeAni"+std::to_string(id),2);
    hpFadeAni->setEaseOutTimingMode();
    mpAni = new Animation("mpAni"+std::to_string(id),1);
    mpAni->setEaseOutTimingMode();
    
    id += 1;
    
    
    this->initHp = initHp;
    this->initMp = initMp;
    curHp = initHp;
    curMp = initMp;
    this->parentNode = parentNode;
    
    parentNode->addChildNode(background);
}

void HPBarNode::setPosition(glm::vec2 position){
    background->screenPosition = position;
}

void HPBarNode::setText(std::string t){
    player->text = t;
}

void HPBarNode::updateHp(float value,bool isIncrease,Engine* engine){
    if(isIncrease){
        curHp = curHp + value;
        if(curHp>initHp){curHp = initHp;}
    }else{
        curHp = curHp - value;
        if(curHp<0){curHp=0;}
    }
    hpAni->setVec2Animation(&(HpNode->scale), glm::vec2(curHp/initHp,1.0));
    hpFadeAni->setVec2Animation(&(HpFadeNode->scale), glm::vec2(curHp/initHp,1.0));
    engine->playAnimation(hpAni);
    engine->playAnimation(hpFadeAni);
}

void HPBarNode::updateMp(float value,bool isIncrease,Engine* engine){
    if(isIncrease){
        curMp = curMp + value;
        if(curMp>initMp){curMp = initMp;}
    }else{
        curMp = curMp - value;
        if(curMp<0){curMp=0;}
    }
    mpAni->setVec2Animation(&(MpNode->scale), glm::vec2(curMp/initMp,1.0));
    engine->playAnimation(mpAni);
}

