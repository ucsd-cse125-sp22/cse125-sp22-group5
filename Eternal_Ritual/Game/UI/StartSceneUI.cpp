#include "StartSceneUI.hpp"
#include <iostream>

StartSceneUI::StartSceneUI(Engine* e, Font* font, UINode* parentNode, UINode* buttonBase)
{
	this->parentNode = parentNode;
	this->buttonBase = buttonBase;
	this->engine = e;

	float scale = 1.1;

	startButton = new ButtonNode(buttonBase,font);
	startButton->setText("Start");
	startButton->setPosition(glm::vec2(0.5,0.5));
	startButton->setScale(scale);

	creditButton = new ButtonNode(buttonBase, font);
	creditButton->setText("Credit");
	creditButton->setPosition(glm::vec2(0.5, 0.65));
	creditButton->setScale(scale);

	exitButton = new ButtonNode(buttonBase, font);
	exitButton->setText("Exit");
	exitButton->setPosition(glm::vec2(0.5, 0.8));
	exitButton->setScale(scale);

	buttonBase->alpha = 0;
	buttonBase->isDisabled = true;
	parentNode->addChildNode(buttonBase);
}

void StartSceneUI::isDisbled(bool t)
{
	parentNode->isDisabled = t;
	buttonBase->isDisabled = t;
}

int StartSceneUI::update() {

	glm::vec2 position = engine->input->getMouseScreenPosition();
	Input* input = engine->input;

	if (startButton->checkState(position, input)) {
		return 1;
	}

	if (exitButton->checkState(position,input)) {
		engine->terminate();
	}

	if (creditButton->checkState(position, input)) {
		return 2;
	}
	
}