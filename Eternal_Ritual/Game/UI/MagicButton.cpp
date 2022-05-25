#include "MagicButton.hpp"

MagicButton::MagicButton(UINode* parentNode, Texture* magicTex, glm::vec2 size, BaseMagic* magic)
{
	this->parentNode = parentNode;

	background = new SpriteNode(UISizes::magicButtonBackSize);
	background->texture = new Texture("/Resources/Game/UI/magic_back.png");
	magicSelect = new SpriteNode(UISizes::magicSelect);
	magicSelect->texture = new Texture("/Resources/Game/UI/magic_back_select.png");
	magicSelect->isDisabled = true;
	magicIcon = new SpriteNode(UISizes::magicIconSize);
	magicIcon->texture = magicTex;
	magicIcon->renderingOrder = 1;
	background->scale = size;
	
	background->addChildNode(magicIcon);
	background->addChildNode(magicSelect);
	parentNode->addChildNode(background);
}

void MagicButton::setPosition(glm::vec2 position)
{
	background->parentCoordinatePosition = position;
}

void MagicButton::toggleSelect(bool select) {
	if (select) {
		magicSelect->isDisabled = false;
	}
	else {
		magicSelect->isDisabled = true;
	}
}
