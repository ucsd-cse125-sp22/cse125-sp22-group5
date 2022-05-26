//
//  HPBarNode.hpp
//  KGLEngine
//
//  Created by Jackie Li on 4/27/22.
//

#ifndef HPBarNode_hpp
#define HPBarNode_hpp

#include <stdio.h>
#include "KGLEngine/Engine.hpp"
#include "Game/UI/UI.hpp"

class HPBarNode{
protected:
    static int id;
    SpriteNode* background;
    SpriteNode* HpBar;
    SpriteNode* MpBar;
    SpriteNode* HpValue;
    SpriteNode* MpValue;
    SpriteNode* HpFade;
    SpriteNode* icon;
    SpriteNode* Enemy;
    TextNode* player;
    Animation* hpAni;
    Animation* hpFadeAni;
    Animation* mpAni;
    UINode* HpNode;
    UINode* HpFadeNode;
    UINode* MpNode;
    float initHp;
    float initMp;
    float curHp;
    float curMp;
    UINode* parentNode;
public:
    HPBarNode(UINode* parentNode, Font* font,float length, bool isEnemy,float initHp, float initMp,std::string playerName);
    ~HPBarNode() = default;
    void setPosition(glm::vec2 position);
    void setText(std::string t);
    void updateHp(float value,bool isIncrease,Engine* engine);
    void updateMp(float value,bool isIncrease,Engine* engine);
};



#endif /* HPBarNode_hpp */
