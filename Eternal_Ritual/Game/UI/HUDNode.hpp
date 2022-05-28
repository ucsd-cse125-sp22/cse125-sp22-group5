#ifndef HUDNode_hpp
#define HUDNode_hpp

#include "KGLEngine/Engine.hpp"

#include "Game/Character/CharNode.hpp"
#include "Game/UI/BarNode.hpp"
#include "Game/UI/MagicButton.hpp"


class HUDNode {
protected:
    Engine* engine;

    // Main ============================
    SpriteNode* leftBack;
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

    // Tutorial
    SpriteNode* listTop;
    SpriteNode* listBottom;
    TextNode* tutorialText;

    UINode* parentNode;
    void selectMagic();
public:
    HUDNode(Engine* e, UINode* parentNode, bool isRed, Font* font, CharNode* selfChar, CharNode* ally);
    ~HUDNode() = default;
    void update();
    void updateMagic();
};

#endif
