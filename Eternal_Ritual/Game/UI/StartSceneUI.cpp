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

	netWinBack = new SpriteNode(UISizes::netWinBackSize);
	netWinBack->texture = new Texture("/Resources/Game/UI/net_back.png");
	netWinBack->isDisabled = true;
	netWinBack->renderingOrder = 3;
	netWinBack->screenPosition = glm::vec2(0.5, 0.6);

	netText = new TextNode(font,0.03,UISizes::netWinBackSize.x*0.8,0.1);
	//netText->parentCoordinatePosition = glm::vec2(0, 0.5);
	netText->text = "Waiting for other players to join ...";
	netText->color = Color::textColor;
	
	netWinBack->addChildNode(netText);

	buttonBase->alpha = 0;
	buttonBase->isDisabled = true;
	parentNode->addChildNode(buttonBase);
	parentNode->addChildNode(netWinBack);
}

void StartSceneUI::isDisbled(bool t)
{
	parentNode->isDisabled = t;
	buttonBase->isDisabled = t;
}

int StartSceneUI::update(bool isWaiting) {
	glm::vec2 position = engine->input->getMouseScreenPosition();
	Input* input = engine->input;
	bool show = !netWinBack->isDisabled;

	if (show && !isWaiting) {
        Animation* netWinExit = new Animation("netWinExit", 0.3f);
        netWinExit->setFloatAnimation(&netWinBack->alpha, 0.0f);
        engine->playAnimation(netWinExit);
		return 1;
	}
    if (show && isWaiting) {
        return 5;
    }

	if (!show) {

		bool isReleased = input->wasKeyReleased(MOUSE_BUTTON_LEFT);

		if (startButton->checkState(position, input, isReleased)) {
            Animation* buttonExit = new Animation("buttonExit", 0.3f);
            buttonExit->setFloatAnimation(&buttonBase->alpha, 0.0f);
            engine->playAnimation(buttonExit);
            netWinBack->isDisabled = false;
            Animation* netWinShow = new Animation("netWinShow", 0.3f);
            netWinShow->setFloatAnimation(&netWinBack->alpha, 1.0f);
            engine->playAnimation(netWinShow);
            return 4;
		}

		if (creditButton->checkState(position, input, isReleased)) {
			return 2;
		}

		if (exitButton->checkState(position, input, isReleased)) {
			engine->terminate();
		}
	}
    
    return 3;
}