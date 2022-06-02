#include "Game/UI/BarNode.hpp"

#include <string>
#include <iostream>

BarNode::BarNode(UINode* parentNode, float initValue, Texture* barTex, Texture* fadeTex, glm::vec2 barSize, glm::vec2 fadeSize, int id,bool left, Engine* e)
{
	engine = e;
	baseNode = new UINode();
	baseNode->parentCoordinatePosition = glm::vec2(0, 0.5);
	fadeBaseNode = new UINode();
	fadeBaseNode->parentCoordinatePosition = glm::vec2(0, 0.5);
	background = new UINode();
	background->size = barSize;
	parentNode->addChildNode(background);
	background->renderingOrder = 1;
	bar = new SpriteNode(barSize);
	fade = new SpriteNode(fadeSize);
	bar->texture = barTex;
	fade->texture = fadeTex;
	fade->alpha = 0.8;
	bar->position = glm::vec2(barSize.x/2,0.0);
	fade->position = glm::vec2(fadeSize.x/2, 0.0);
	if (!left) {
		fadeBaseNode->parentCoordinatePosition = glm::vec2(1, 0.5);
		baseNode->parentCoordinatePosition = glm::vec2(1, 0.5);
		bar->position = glm::vec2(-barSize.x / 2, 0.0);
		fade->position = glm::vec2(-fadeSize.x / 2, 0.0);
	}
	background->addChildNode(fadeBaseNode);
	background->addChildNode(baseNode);
	fadeBaseNode->addChildNode(fade);
	baseNode->addChildNode(bar);
	this->initValue = initValue;
	curValue = initValue;
}

void BarNode::setPosition(glm::vec2 position)
{
	background->parentCoordinatePosition = position;
}

void BarNode::update(float value)
{
	if (value == curValue) { return; }
	bool isincrease = this->curValue < value;
	if (value > initValue) { value = initValue; }
	if (value < 0) { value = 0; }
	float scale = value / initValue;
	if (isincrease) {
		Animation* ani = new Animation("hudBarIncrease" + std::to_string(id), 0.5);
		ani->setVec2Animation(&baseNode->scale, glm::vec2(scale, 1.0));
		Animation* fadeAni = new Animation("fadeincrease" + std::to_string(id), 0.5);
		fadeAni->setVec2Animation(&fadeBaseNode->scale, glm::vec2(scale, 1.0));
		engine->playAnimation(ani);
		engine->playAnimation(fadeAni);
	}
	else {
		Animation* ani = new Animation("hudBar" + std::to_string(id), 1);
		ani->setVec2Animation(&baseNode->scale, glm::vec2(scale, 1.0));
		engine->playAnimation(ani);
		Animation* delay = new Animation("fadebardelay" + std::to_string(id), 0.4);
		delay->setCompletionHandler([=] {
			Animation* fadeAni = new Animation("fade" + std::to_string(id), 0.5);
			std::cout << "cur: " << value << std::endl;
			std::cout << "init: " << initValue << std::endl;
			std::cout << "scale: " << scale << std::endl;
			fadeAni->setVec2Animation(&fadeBaseNode->scale, glm::vec2(scale, 1.0));
			fadeAni->setEaseInTimingMode();
			engine->playAnimation(fadeAni);
			});
		engine->playAnimation(delay);
	}
	curValue = value;
}
