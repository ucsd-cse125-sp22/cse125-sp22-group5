#include "StartSceneUI.hpp"
#include <iostream>

StartSceneUI::StartSceneUI(Engine* e, Font* font, Font* smallFont, UINode* parentNode, UINode* buttonBase, Cursor* cursor)
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
	netWinBack->screenPosition = glm::vec2(0.5, 0.5);
	netWinBack->scale = glm::vec2(0);

	netText = new TextNode(font,0.03,UISizes::netWinBackSize.x*0.8,0.1);
	netText->text = "Waiting for other players to join ...";
	netText->color = Color::textColor;
	
	netWinBack->addChildNode(netText);

	winBack = new SpriteNode(UISizes::creditWinBackSize);
	winBack->texture = new Texture("/Resources/Game/UI/win_back.png");
	winBack->alpha = 1;
	winBack->isDisabled = true;
	winBack->renderingOrder = 3;
	winBack->screenPosition = glm::vec2(0.5);
	winBack->scale = glm::vec2(0);

	creditText = new TextNode(smallFont, 0.035, 1.0, 0.02);
	creditText->text = "Kelin Lyu (Deze Lyu)\n Felix Zhang (Futian Zhang)\nJackie Li (Mengxuan Li)\nKelvin Yu (Kangming Yu)\nZifan Zhang.";
	creditText->color = Color::textColor;
	creditText->setCenterHorizontalAlignment();
	creditText->setCenterVerticalAlignment();
	creditText->position = glm::vec2(0, 0.03);
	winBack->addChildNode(creditText);

	winCloseButton = new ButtonNode(winBack, font);
	winCloseButton->setWinButton("Close");
	winCloseButton->setPosition(glm::vec2(0.5, 0.99));
	//winCloseButton->setScale(0.7);

	
	blackScreen = new SpriteNode(glm::vec2(e->getWindowResolution().x / e->getWindowResolution().y, 1.0));
	blackScreen->color = glm::vec4(0, 0, 0, 0.8);
	blackScreen->renderingOrder = 1;
	blackScreen->screenPosition = glm::vec2(0.5);
	blackScreen->alpha = 0;


	buttonBase->alpha = 0;
	buttonBase->isDisabled = true;
	parentNode->addChildNode(buttonBase);
	parentNode->addChildNode(netWinBack);
	parentNode->addChildNode(winBack);
	parentNode->addChildNode(blackScreen);
    this->cursor = cursor;
}

void StartSceneUI::isDisbled(bool t)
{
	parentNode->isDisabled = t;
	buttonBase->isDisabled = t;
}

int StartSceneUI::update(bool isWaiting) {
	glm::vec2 position = cursor->cursorScreenPosition;
	Input* input = engine->input;
	bool show = !netWinBack->isDisabled;
	bool creditShow = !winBack->isDisabled;

	if (show && !isWaiting) {
        Animation* netWinExit = new Animation("netWinExit", 0.3f);
		netWinExit->setVec2Animation(&netWinBack->scale, glm::vec2(0));
		netWinExit->setEaseInTimingMode();
        engine->playAnimation(netWinExit);
		return 1;
	}
    if (show && isWaiting) {
        return 5;
    }

	if (!show && !creditShow && enabled) {

		bool isReleased = input->wasKeyReleased(MOUSE_BUTTON_LEFT);

		if (startButton->checkState(position, input, isReleased)) {
            Animation* buttonExit = new Animation("buttonExit", 0.3f);
            buttonExit->setFloatAnimation(&buttonBase->alpha, 0.0f);
			buttonExit->setEaseInTimingMode();
            engine->playAnimation(buttonExit);
            netWinBack->isDisabled = false;
            Animation* netWinShow = new Animation("netWinShow", 0.3f);
			netWinShow->setVec2Animation(&netWinBack->scale,glm::vec2(1));
			netWinShow->setEaseOutTimingMode();
            engine->playAnimation(netWinShow);
			Animation* showBlackscreen = new Animation("showBlackscreen", 0.5);
			showBlackscreen->setFloatAnimation(&blackScreen->alpha, 1);
			showBlackscreen->setEaseOutTimingMode();
			engine->playAnimation(showBlackscreen);
            return 4;
		}

		if (creditButton->checkState(position, input, isReleased)) {
			winBack->isDisabled = false;
			Animation* showCredit = new Animation("showCredit", 0.5f);
			showCredit->setVec2Animation(&winBack->scale, glm::vec2(1));
			showCredit->setEaseOutTimingMode();
			engine->playAnimation(showCredit);
			Animation* showBlackscreen = new Animation("showBlackscreen", 0.5);
			showBlackscreen->setFloatAnimation(&blackScreen->alpha, 1);
			showBlackscreen->setEaseOutTimingMode();
			engine->playAnimation(showBlackscreen);
		}

		if (exitButton->checkState(position, input, isReleased)) {
			exit(0);
		}
	}

	if (creditShow) {
		bool isReleased = input->wasKeyReleased(MOUSE_BUTTON_LEFT);
		if (winCloseButton->checkState(position, input, isReleased)) {
			Animation* closeCredit = new Animation("closeCredit", 0.5f);
			closeCredit->setVec2Animation(&winBack->scale, glm::vec2(0));
			engine->playAnimation(closeCredit);
			closeCredit->setCompletionHandler([&] {
				winBack->isDisabled = true;
				});
			closeCredit->setEaseInTimingMode();
			Animation* closeBlackscreen = new Animation("closeBlackscreen", 0.5);
			closeBlackscreen->setFloatAnimation(&blackScreen->alpha, 0);
			closeBlackscreen->setEaseInTimingMode();
			engine->playAnimation(closeBlackscreen);
		}
	}
    
    return 3;
}
