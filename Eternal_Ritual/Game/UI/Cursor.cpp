#include "Cursor.hpp"

#include <iostream>

Cursor::Cursor(Engine* e)
{
	engine = e;
	cursor = new SpriteNode(UISizes::cursorSize);
	cursor->texture = new Texture("/Resources/Game/UI/cursor.png");
	cursor->renderingOrder = 20000;
	cursor->isDisabled = true;
	e->addNode(cursor);
	//e->input->engineSetMouseEvent(glm::vec2(0.5));
}

void Cursor::update()
{
    this->cursorScreenPosition += engine->input->getMouseTranslation() / Engine::main->getWindowResolution();
    this->cursorScreenPosition = glm::clamp(this->cursorScreenPosition, glm::vec2(0.0f), glm::vec2(1.0f));
	this->cursor->screenPosition = this->cursorScreenPosition + UISizes::cursorSize * 0.5f;
}

void Cursor::isDisable(bool t)
{
	cursor->isDisabled = t;
    if(t == false) {
        this->cursorScreenPosition = glm::vec2(0.5f);
    }
}
