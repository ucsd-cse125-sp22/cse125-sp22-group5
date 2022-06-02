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
	glm::vec2 m = engine->input->getMouseScreenPosition();
	cursor->screenPosition = glm::vec2(glm::min(glm::max(0.0f,m.x),1.0f), glm::min(glm::max(0.0f, m.y), 1.0f));
}

void Cursor::isDisable(bool t)
{
	cursor->isDisabled = t;
}
