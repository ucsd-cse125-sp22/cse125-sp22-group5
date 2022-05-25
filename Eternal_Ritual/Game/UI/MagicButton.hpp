#ifndef MagicButton_hpp
#define MagicButton_hpp

#include <stdio.h>
#include "KGLEngine/Engine.hpp"
#include "Game/Magic/BaseMagic.hpp"
#include "Constant.hpp"

class MagicButton
{
private:
	SpriteNode* background;
	SpriteNode* magicIcon;
	SpriteNode* magicSelect;	
	UINode* parentNode;
	BaseMagic* magic;
public:
	MagicButton(UINode* parentNode, Texture* magicTex, glm::vec2 scale, BaseMagic* magic);
	void setPosition(glm::vec2 position);
	void toggleSelect(bool select);
};

#endif

