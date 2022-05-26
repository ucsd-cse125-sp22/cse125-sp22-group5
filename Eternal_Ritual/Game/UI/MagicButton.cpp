#include "MagicButton.hpp"

MagicButton::MagicButton(UINode* parentNode, Texture* magicTex, glm::vec2 size, BaseMagic* magic)
{
	this->parentNode = parentNode;
	this->magic = magic;

	background = new SpriteNode(UISizes::magicButtonBackSize);
	background->texture = new Texture("/Resources/Game/UI/magic_back.png");
	magicSelect = new SpriteNode(UISizes::magicSelect);
	magicSelect->texture = new Texture("/Resources/Game/UI/magic_back_select.png");
	magicSelect->isDisabled = true;
	magicIcon = new SpriteNode(UISizes::magicIconSize);
	magicIcon->texture = magicTex;
	magicIcon->renderingOrder = 1;
	magicCooldown = new SpriteNode(UISizes::magicCooldownSize);
	magicCooldown->texture = new Texture("/Resources/Game/UI/magic_cooldown.png");
	magicCooldown->isDisabled = true;
	magicCooldown->renderingOrder = 2;
	progress = new Shader("/Resources/Game/UI/MagicShader");
	progress->setTexture("textureMap", new Texture("/Resources/Game/UI/magic_progess.png"));
	Sprite* s = new Sprite();
	s->setShader(progress);
	magicProgess = new UINode();
	magicProgess->loadSprite(s);
	magicProgess->isDisabled = true;
	magicProgess->renderingOrder = 3;
	
	background->scale = size;
	
	background->addChildNode(magicIcon);
	background->addChildNode(magicSelect);
	background->addChildNode(magicCooldown);
	background->addChildNode(magicProgess);
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

void MagicButton::setProgess()
{
	if (magic->availableTime - Engine::main->getTime() > 0) {
		magicCooldown->isDisabled = false;
		magicProgess->isDisabled = false;
		progress->setFloat("progess", magic->availableTime / magic->cooldown);
	}
	else {
		magicCooldown->isDisabled = true;
		magicProgess->isDisabled = true;
	}
}
