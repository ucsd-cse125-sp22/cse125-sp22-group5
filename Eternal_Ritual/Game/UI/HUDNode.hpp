#ifndef HUDNode_hpp
#define HUDNode_hpp

#include <stdio.h>
#include "KGLEngine/Engine.hpp"
#include "Game/Character/CharNode.hpp"
#include "BarNode.hpp"
#include "MagicButton.hpp"

class HUDNode {
protected:
    Engine* engine;

    // Main ============================
    SpriteNode* mainBackground;
    BarNode* mainHpBar;
    BarNode* mainMpBar;
    SpriteNode* mainAvatarBack;
    SpriteNode* mainAvatar;
    SpriteNode* mainAvatarTop;
    SpriteNode* mainIcon;
    TextNode* mainName;

    // Party ===============
    SpriteNode* partyBackground;
    BarNode* partyHpBar;
    BarNode* partyMpBar;
    SpriteNode* partyAvatarBack;
    SpriteNode* partyAvatar;
    SpriteNode* partyAvatarTop;
    SpriteNode* partyIcon;
    TextNode* partyName;
    
    // Magic =================
    SpriteNode* magicBack;
    MagicButton* magicLarge;
    MagicButton* magic1;
    MagicButton* magic2;
    MagicButton* magic3;

    // Enermy ================
    SpriteNode* enBackground;
    BarNode* enHpBar;
    SpriteNode* enAvatarBack;
    SpriteNode* enAvatar;
    SpriteNode* enAvatarTop;
    SpriteNode* enIcon;
    TextNode* enName;   

    // Character ============
    CharNode* selfChar;
    CharNode* ally;

    UINode* parentNode;
public:
    HUDNode(Engine* e, UINode* parentNode, bool isRed, Font* font, CharNode* selfChar, CharNode* ally);
    ~HUDNode() = default;
    void toggleEnermy(CharNode* chara);
    void updateChar(CharNode* en);
    void updateMagic();
};

#endif