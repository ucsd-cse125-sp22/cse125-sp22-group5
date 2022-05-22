#include "MagicButton.hpp"

MagicButton::MagicButton(UINode* parentNode, Texture* magicTex, glm::vec2 size)
{
	this->parentNode = parentNode;

	background = new SpriteNode(UISizes::magicButtonBackSize);
	background->texture = new Texture("/Resources/Game/UI/magic_back.png");
	magicIcon = new SpriteNode(UISizes::magicIconSize);
	magicIcon->texture = magicTex;
	magicIcon->renderingOrder = 1;
	background->scale = size;
	
	background->addChildNode(magicIcon);
	parentNode->addChildNode(background);
}

void MagicButton::setPosition(glm::vec2 position)
{
	background->parentCoordinatePosition = position;
}
