#include "BarNode.hpp"

BarNode::BarNode(UINode* parentNode, float initValue, Texture* barTex, Texture* fadeTex, glm::vec2 barSize, glm::vec2 fadeSize, int id)
{
	baseNode = new UINode();
	fadeBaseNode = new UINode();
	background = new UINode();
	parentNode->addChildNode(background);
	background->renderingOrder = 1;
	bar = new SpriteNode(barSize);
	fade = new SpriteNode(fadeSize);
	bar->texture = barTex;
	fade->texture = fadeTex;
	fade->alpha = 0.8;
	background->addChildNode(fadeBaseNode);
	background->addChildNode(baseNode);
	fadeBaseNode->addChildNode(fade);
	baseNode->addChildNode(bar);
	ani = new Animation("bar"+std::to_string(id),1);
	fadeAni = new Animation("fadeBar" + std::to_string(id), 2);
	this->initValue = initValue;
	curValue = initValue;
}

void BarNode::setPosition(glm::vec2 position)
{
	background->parentCoordinatePosition = position;
}

void BarNode::update(float curValue, Engine* engine)
{
	if (curValue > initValue) { curValue = initValue; }
	if (curValue < 0) { curValue = 0; }
	ani->setVec2Animation(&(baseNode->scale),glm::vec2(curValue/initValue,1.0));
	fadeAni->setVec2Animation(&(fadeBaseNode->scale), glm::vec2(curValue / initValue, 1.0));
	engine->playAnimation(ani);
	engine->playAnimation(fadeAni);
}