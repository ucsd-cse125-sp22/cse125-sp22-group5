#include "Game/UI/MagicButton.hpp"

#include <iostream>

#include "Game/UI/Constant.hpp"


MagicButton::MagicButton(UINode* parentNode, Texture* magicTex, glm::vec2 size, BaseMagic* magic)
{
	this->parentNode = parentNode;
	this->magic = magic;

	base = new UINode();
	background = new SpriteNode(UISizes::magicButtonBackSize);
	background->texture = new Texture("/Resources/Game/UI/magic_back.png");	
	magicSelect = new SpriteNode(UISizes::magicSelect);
	magicSelect->texture = new Texture("/Resources/Game/UI/magic_back_select.png");
	magicSelect->isDisabled = true;
	magicIcon = new SpriteNode(UISizes::magicIconSize);
	magicIcon->texture = magicTex;
	magicIcon->renderingOrder = 1;
	progress = new Shader("/Resources/Game/UI/MagicShader");
	progress->setTexture("textureMap", new Texture("/Resources/Game/UI/magic_progess.png"));
	progress->setUIShader();
	Sprite* s = new Sprite();
	s->setShader(progress);
	magicProgess = new UINode();
	magicProgess->loadSprite(s);
	magicProgess->renderingOrder = 2;
	magicProgess->size = UISizes::magicPorgessSize;
	
	background->scale = size;
	
	background->addChildNode(magicSelect);
	background->addChildNode(magicIcon);
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

void MagicButton::setProgess(float mpleft)
{

	float cd = magic->availableTime - Engine::main->getTime();
	if (cd > 0) {
		magicIcon->multiplyColor = glm::vec3(0.5,0.5,0.5);
		magicProgess->isDisabled = false;
		float p = cd / magic->cooldown;
		progress->setFloat("progess", 1-p);	
	}
	else {
		magicIcon->multiplyColor = glm::vec3(1);
		magicProgess->isDisabled = true;
	}

	if (mpleft < magic->cost) {
		magicIcon->multiplyColor = glm::vec3(0.5, 0.5, 0.5);
	}
}
