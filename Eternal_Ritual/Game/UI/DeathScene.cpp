#include "DeathScene.hpp"
#include <iostream>

DeathScene::DeathScene(Engine* e)
{
	blackout = new SpriteNode(glm::vec2(e->getWindowResolution().x / e->getWindowResolution().y, 1.0));
	blackout->color = glm::vec4(0, 0, 0, 1);
	blackout->renderingOrder = 11001;
	blackout->screenPosition = glm::vec2(0.5);
	engine = e;
	background = new SpriteNode(glm::vec2(e->getWindowResolution().x / e->getWindowResolution().y, 1.0));
	background->color = glm::vec4(0, 0, 0, 1);
	background->alpha = 0;
	background->isDisabled = true;
	background->renderingOrder = 11000;
	background->screenPosition = glm::vec2(0.5);
	logo = new SpriteNode(UISizes::endLogoSize);
	logo->scale = glm::vec2(0);
	defeat= new Texture("/Resources/Game/UI/end_defeat.png");
	victory = new Texture("/Resources/Game/UI/end_victory.png");
	
	background->addChildNode(logo);
	engine->addNode(background);
	blackout->isDisabled = true;
	blackout->alpha = 0;
	engine->addNode(blackout);
}

void DeathScene::display(bool win, int* pro)
{
	background->isDisabled = false;
	if (win) {
		logo->texture = victory;
	}
	else {
		logo->texture = defeat;
	}
	Animation* back = new Animation("backAlpha", 0.3);
	back->setFloatAnimation(&background->alpha, 1);
	back->setCompletionHandler([&] {
		Animation* endScale = new Animation("endScale", 0.1);
		endScale->setEaseInEaseOutTimingMode();
		endScale->setVec2Animation(&logo->scale, glm::vec2(1.5));
		endScale->setCompletionHandler([&] {
			Animation* delay = new Animation("endDelay", 1);
			delay->setCompletionHandler([&] {
				blackout->isDisabled = false;
				Animation* blackoutAni = new Animation("blackout", 0.5);
				blackoutAni->setFloatAnimation(&blackout->alpha, 1);
				blackoutAni->setCompletionHandler([&] {
					Animation* liftBlack = new Animation("liftBlack", 0.5);
					liftBlack->setFloatAnimation(&blackout->alpha, 0);
					engine->playAnimation(liftBlack);
					background->isDisabled = true;
					background->alpha = 0;
					logo->scale = glm::vec2(0);
					});
				engine->playAnimation(blackoutAni);
				});
			engine->playAnimation(delay);
			});
		engine->playAnimation(endScale);
		});
	engine->playAnimation(back);
}
