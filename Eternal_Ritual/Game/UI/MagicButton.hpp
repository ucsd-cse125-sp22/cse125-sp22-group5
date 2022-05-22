#ifndef MagicButton_hpp
#define MagicButton_hpp

#include <stdio.h>
#include "KGLEngine/Engine.hpp"
//#include ""
#include "Constant.hpp"

class MagicButton
{
private:
	SpriteNode* background;
	SpriteNode* magicIcon;
	UINode* parentNode;
public:
	MagicButton(UINode* parentNode, Texture* magicTex, glm::vec2 scale);
	void setPosition(glm::vec2 position);
};

#endif

