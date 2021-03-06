#ifndef StartSceneUI_hpp
#define StartSceneUI_hpp

#include "KGLEngine/Engine.hpp"
#include "Game/UI/Constant.hpp"
#include "Game/UI/ButtonNode.hpp"
#include "Game/UI/Cursor.hpp"

class StartSceneUI {
public:
    
    bool enabled = false;
    
	Engine* engine;
	UINode* parentNode;
	UINode* buttonBase;
	SpriteNode* nameBackground;
	SpriteNode* winBack;
	ButtonNode* startButton;
	ButtonNode* creditButton;
	ButtonNode* exitButton;
	ButtonNode* winCloseButton;
	SpriteNode* netWinBack;
	SpriteNode* creditBack;
	SpriteNode* blackScreen;
	TextNode* netText;
	TextNode* creditText;
	TextNode* name;
    Cursor* cursor;

public:
	StartSceneUI(Engine* e, Font* font, Font* smallFont, UINode* parentNode, UINode* buttonBase, Cursor* cursor);
	~StartSceneUI() = default;
	void isDisbled(bool t);
	int update(bool isWaiting);

};

#endif
