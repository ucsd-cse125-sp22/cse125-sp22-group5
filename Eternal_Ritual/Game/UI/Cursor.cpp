#include "Cursor.hpp"

#include <iostream>

Cursor::Cursor(Engine* e)
{
	engine = e;
	cursor = new SpriteNode(UISizes::cursorSize);
	cursor->texture = new Texture("/Resources/Game/UI/cursor.png");
	cursor->renderingOrder = 20000;
	cursor->alpha = 0.0f;
	e->addNode(cursor);
}

void Cursor::update()
{
    this->cursorScreenPosition += engine->input->getMouseTranslation() / Engine::main->getWindowResolution();
    this->cursorScreenPosition = glm::clamp(this->cursorScreenPosition, glm::vec2(0.0f), glm::vec2(1.0f));
	this->cursor->screenPosition = this->cursorScreenPosition + glm::vec2(UISizes::cursorSize.x * 0.3f, UISizes::cursorSize.y * 0.5f);
}

void Cursor::isDisable(bool t)
{
	Animation* cursorAnimation = new Animation("cursorAnimation", 0.5f);
    if(t == false) {
		cursorAnimation->setEaseInTimingMode();
		cursorAnimation->setFloatAnimation(&this->cursor->alpha, 1.0f);
        this->cursorScreenPosition = glm::vec2(0.5f);
	} else {
		cursorAnimation->setEaseOutTimingMode();
		cursorAnimation->setFloatAnimation(&this->cursor->alpha, 0.0f);
	}
	engine->playAnimation(cursorAnimation);
}
